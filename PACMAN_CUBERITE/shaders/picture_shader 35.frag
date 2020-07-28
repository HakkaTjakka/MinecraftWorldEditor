//shader 35 Arbitrary Weave

uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform vec2 pos_pacman;

/*


	Arbitrary Weave
	---------------

	Using randomly-rotated hexagonal Truchet tiles with varied patterns to create an arbitrary
	looking weave design. BigWIngs has already produced one (link below), so this is just my
	take on it. This particular example was written from scratch, and is based on some old
	code of mine, but the concept is essentially the same.

	I put in a few additions, and partly addressed BigWIngs's UV coordinate mapping concerns.
	The little portal lights are rendered using UV coordinates,	which work for the wrappable
	dot pattern I chose, but I wouldn't say it's a robust solution. However, it would be with a
	little extra work.

	Considering the time of year, I put in a half hearted attempt to give it a mild Christmas
	feel - Redish background, green Christmas lights... It's a very abstract representation. :)
	I find green and red a challenging combination to work with, but I think I got away with it.

	Algorithmically speaking, constructing one of these patterns is not difficult: Instead of
	using just the standard triple-arc hexagonal Truchet tile, you mix in other combinations,
	such as overlapping arcs, straight lines, etc. Uncomment the "SHOW_GRID" directive, and you
	should be able to make out a few. Some of the tile combinations involve arcs and lines that
	cross over one another, which gives the weave effect. Elements that cross over necessitate
	a rendering order requirement, but that's not particularly difficult to implement.

	The pattern is rendered in a pseudo-3D vector-graphics style. The cool thing about 2D
	distance field values is that you can use them to produce some simple -- but effective --
	oldschool Photoshop effects: Layers, drop shadows, highlights, bevels, edging, etc. All are
	very cheap, and a lot of the time, just involve an extra "mix" and "smoothstep" combination,
	and sometimes, an extra distance function call. This example was produced using these
	simple methods.

	Related references:

	// The original: Much less code, so if you're trying to get a handle on how to make
	// a random hexagonal weave pattern, this is the one you should be looking at.
	BigWIngs - Hexagonal Truchet Weaving
	https://www.shadertoy.com/view/llByzz


*/

//#define SHOW_GRID
//#define MULTICOLORED_LIGHTS

// Standard 2D rotation formula.
mat2 r2(in float a){ float c = cos(a), s = sin(a); return mat2(c, -s, s, c); }

// Helper vector. If you're doing anything that involves regular triangles or hexagons, the
// 30-60-90 triangle will be involved in some way, which has sides of 1, sqrt(3) and 2.
const vec2 s = vec2(1, 1.7320508);

// Standard float to float hash - Based on IQ's original.
float hash(float n){ return fract(sin(n)*43758.5453); }


// Standard vec2 to float hash - Based on IQ's original.
float hash21(vec2 p){ return fract(sin(dot(p, vec2(141.187, 289.973)))*43758.5453); }

// This is a rewrite of IQ's original. It's self contained, which makes it much
// easier to copy and paste. I've also tried my best to minimize the amount of
// operations to lessen the work the GPU has to do, but I think there's room for
// improvement.
//
float noise3D(vec3 p){

    // Just some random figures, analogous to stride. You can change this, if you want.
	const vec3 s = vec3(7, 157, 113);

	vec3 ip = floor(p); // Unique unit cell ID.

    // Setting up the stride vector for randomization and interpolation, kind of.
    // All kinds of shortcuts are taken here. Refer to IQ's original formula.
    vec4 h = vec4(0., s.yz, s.y + s.z) + dot(ip, s);

	p -= ip; // Cell's fractional component.

    // A bit of cubic smoothing, to give the noise that rounded look.
    p = p*p*(3. - 2.*p);

    // Standard 3D noise stuff. Retrieving 8 random scalar values for each cube corner,
    // then interpolating along X. There are countless ways to randomize, but this is
    // the way most are familar with: fract(sin(x)*largeNumber).
    h = mix(fract(sin(h)*43758.5453), fract(sin(h + s.x)*43758.5453), p.x);

    // Interpolating along Y.
    h.xy = mix(h.xz, h.yw, p.y);

    // Interpolating along Z, and returning the 3D noise value.
    return mix(h.x, h.y, p.z); // Range: [0, 1].

}



// Dot pattern.
float dots(in vec2 p){


	p = abs(fract(p) - .5);

    return length(p); // Circles.

    //return (p.x + p.y)/1.5 + .035; // Diamonds.

    //return max(p.x, p.y);// + .03; // Squares.

    //return max(p.x*.8660254 + p.y*.5, p.y) + .01; // Hexagons.

    //return min((p.x + p.y)*.7071, max(p.x, p.y)) + .05; // Stars.

}


// The 2D hexagonal isosuface function: If you were to render a horizontal line and one that
// slopes at 60 degrees, mirror, then combine them, you'd arrive at the following. As an aside,
// the function may be a bound - as opposed to a Euclidean distance representation, but either
// way, the result is hexagonal boundary lines.
float hex(in vec2 p){

    p = abs(p);

    // Below is equivalent to:
    return max(max(p.x*.5 + p.y*.8660254, p.x), 0.);

    //p = vec2(p.y*.8660254 + p.x*.5, p.x);
    //return min(max(p.x, p.y), 0.) + length(max(p, 0.));


}

// This function returns the hexagonal grid coordinate for the grid cell, and the corresponding
// hexagon cell ID - in the form of the central hexagonal point. That's basically all you need to
// produce a hexagonal grid.
//
// When working with 2D, I guess it's not that important to streamline this particular function.
// However, if you need to raymarch a hexagonal grid, the number of operations tend to matter.
// This one has minimal setup, one "floor" call, a couple of "dot" calls, a ternary operator, etc.
// To use it to raymarch, you'd have to double up on everything - in order to deal with
// overlapping fields from neighboring cells, so the fewer operations the better.
vec4 getHex(vec2 p){

    // The hexagon centers: Two sets of repeat hexagons are required to fill in the space, and
    // the two sets are stored in a "vec4" in order to group some calculations together. The hexagon
    // center we'll eventually use will depend upon which is closest to the current point. Since
    // the central hexagon point is unique, it doubles as the unique hexagon ID.
    vec4 hC = floor(vec4(p, p - vec2(.5, 1))/s.xyxy) + vec4(.5, .5, 1, 1.5);

    // Centering the coordinates with the hexagon centers above.
    vec4 h = vec4(p - hC.xy*s, p - (hC.zw + vec2(0, -.5))*s );

    // Nearest hexagon center (with respect to p) to the current point. In other words, when
    // "h.xy" is zero, we're at the center. We're also returning the corresponding hexagon ID -
    // in the form of the hexagonal central point. Note that a random constant has been added to
    // "hC.zw" to further distinguish it from "hC.xy."
    //
    // On a side note, I sometimes compare hex distances, but I noticed that Iomateron compared
    // the squared Euclidian version, which seems neater, so I've adopted that.
    return dot(h.xy, h.xy)<dot(h.zw, h.zw) ? vec4(h.xy, hC.xy) : vec4(h.zw, hC.zw);
    //return hex(h.xy)<hex(h.zw) ? vec4(h.xy, hC.xy) : vec4(h.zw, hC.zw);

}


// Object rendering: Scene color (col), object distance field (d), pattern value (c),
// sample spread shade values (d2), object ID (objID), random ID (rnd).
vec3 doObject(vec3 col, float d, float c, vec2 d2, float objID, float rnd){

    // The object is either a pipe (objID = 1.) or a join (objID = 0.), so rendering colors,
    // etc, are dependant upon that. I probably could have written two seperate functions.

    // Shade values taken from two different sample points - The rendering point and one in the
    // opposite direction to the shadow. The difference gives you the beveled look and gives the
    // impression that the object is being lit from the light causing the shadow. Very cheap bump
    // mapping of sorts, and all fake.
    float cF = objID>.5? 13. : 15.;
    float sh = abs(clamp(d2.x, -cF, cF))*16.; //sh = pow(sh, 2.)*1.4;
    float sh2 = abs(clamp(d2.y, -cF, cF))*16.; //sh2 = pow(sh2, 2.)*1.4;

    // The gradient or bump value, used for highlighting. It's based on directional derivative
    // lighting and is somewhat analogous to diffuse lighting.
    float b = clamp(sh - sh2, 0., 1.)*4.;

    // I gave the join a differnet alpha value. Not sure why, because, I didn't need it in the end,
    // but I thought I'd blened it into the pipe ever so slighly.
    float alpha = 1.;
    if(objID<.5) alpha = .95;

    // Object edge shadowing - Not to be confused with the drop shadow. In a way, it's a very lame
    // attempt to give an ambient occlusion effect.
    col = mix(col, vec3(0), (1. - smoothstep(0., .075*alpha, max(d, -(d + .015)) - .025))*.5*alpha);

    // Dark edges. This line, combined with the one immediately above is a Photoshop staple.
    col = mix(col, vec3(0), (1. - smoothstep(0., .015,  max(d, -(d + .015)) - .025))*alpha);

    // The pipe color is gray, and the join color is slightly copper, or something... I make this
    // stuff up as I go along. :)
    vec3 oCol = vec3(.45);
    if(objID<.5) oCol = vec3(.6, .45, .3);

    // Combining the term above to produce the object's color. Shading, diffuse and ambience. Not
    // much different to normal object coloring.
    oCol = oCol*max(.75 - sh*.25, 0.)*.7 + vec3(.5, .7, 1)*b*2. + vec3(1, .6, .2)*b*b;

    // Applying the color to the shadow and edges.
    col = mix(col, oCol, (1. - smoothstep(0., .01, d))*alpha);

    // Some extra lines near the pipe edges, just to add a little more detail.
    col = mix(col, vec3(0),  (1. - smoothstep(0., .015, max(d + .035, -(d + .035 + .01))))*.55);


    // Each portal object has a unique ID attached to it, which can be used to produce a
    // blinking light effect.
    float hRnd = hash(rnd);

    #ifdef MULTICOLORED_LIGHTS
    vec3 lCol = hRnd>.666? vec3(2, 5, 1) : hRnd>.333? vec3(6, 3, 1) : vec3(1, 2.5, 7);
    #else
    vec3 lCol = vec3(2, 5, 1);
    #endif

    float blink = smoothstep(.5, .75, sin(rnd*6.283 + iTime*5.));


    // Apply the textured dot pattern - where applicable - to the pipes.
    if(objID>.5){

        lCol = mix(vec3(1), lCol, blink);
        // Adding some light color around the portals for a bevelled effect. Photoshop 101. :)
        col = mix(col, vec3(1), (1. - smoothstep(0., .03, d))*(1. - smoothstep(0., .03, c - .14))*.25);
        // Dark edges. Also a Photoshop staple.
    	col = mix(col, vec3(0), (1. - smoothstep(0., .015, d))*(1. - smoothstep(0., .03, c - .09)));

        // The light color. Roled in with object masking.
    	col = mix(col, vec3(max(max(.5 - sh*.5, 0.)*.15 + lCol*b*.45, 0.)), (1. - smoothstep(0., .01, d))*(1. - smoothstep(0., .03, c)));
    }

    // Return the color for the object.
    return col;



}

// Swap functions. Put together in a hurry to deal with elements that couldn't be swizzled.
// I'll improve the logic at some stage and get rid of them.
void swap(inout float a, inout float b, inout float c){

    vec3 v = vec3(a, b, c);
    a = v.y, b = v.z, c = v.x;
}

void swap(inout float a, inout float b){

    vec2 v = vec2(a, b);
    a = v.y, b = v.x;
}


// The overall scene function - consisting of the Truchet object and the join object.
//
// The logic here is sound, but a bit of it was hacked together as I went along, so there'd be
// some grouping opportunities, etc, missed. However, when I get more time, I'll get in amongst
// it and tidy it up a bit. If it were not for the texture coordinates and custom shading values,
// this would be a much shorter function.
//
// Anyway, the premise behind the function is very simple: Instead of using just the standard
// triple-arc hexagonal Truchet tile, you mix in other combinations (outlined in the function
// below), such as overlapping arcs,  straight lines, etc. Produce a few random numbers, then use
// them to choose and produce a tile combination, randomly rotate by multiples of 60 degrees, and
// if applicable, rotate the order in which you render certain tile elements. For a visual,
// uncomment the "SHOW_GRID" directive to view some of the possible combinations.


// Shade, pattern and random ID globals. Hacked in along the way. I might tidy these up later.
vec4 ds, pat, gRnd;

vec4 scene(vec2 p){


    ds = gRnd = pat = vec4(0);

    // Rotate the XY axis slightly to give the pattern more randomness. The idea is that the
    // view can't quite discern the horizontal and vertical nature of the pattern.
    //p = r2(3.14159265/12.)*p;


    // Scaling, translating, then converting the input to a hexagonal grid cell coordinate and
    // a unique coordinate ID. The resultant vector contains everything you need to produce a
    // pretty pattern, so what you do from here is up to you.
    vec4 h = getHex(p);

    // Offset hexagonal variable - used to render the joins. You could render them using the
    // value above, but sometimes, pixelated seem lines can appear at the hexagonal boundaries
    // when trying to perform offset diffuse calculations... It's a long story, but creating
    // an offset grid ensures no artefacts.
    vec4 h2 = getHex(p - vec2(0, .8660254*2./3.));

    // Using the idetifying coordinate - stored in "h.zw," to produce a unique random number
    // for the hexagonal grid cell.
    vec4 rnd;
    rnd.x = hash21(h.zw + 11.67);
    //rnd.x = sin(rnd.x*6.283 + floor(iTime))*.5 + .5; // Peridically changes the patten formation.

    // More random numbers.
    rnd.y = hash21(h.zw + vec2(45.37, 91.63) + rnd.x);
    rnd.z = hash21(h.zw - vec2(12.74 + rnd.y, 13.78 + rnd.x));
    rnd.w = hash21(h.zw + vec2(32.97 + rnd.x, 45.87 - rnd.y + rnd.z));

    // Store the hexagonal coordinates in "p" to save some writing. "p" tends to be the universal
    // shader variable for "point," so it reads a little better too.
    p = h.xy;


    float a;

    // Constants used for the Truchet pattern. The arc thickness, the small are radius and the large
    // arc radius.
    const float th = .14;
    const float rSm = .8660254/3.;
    const float rLg = .8660254;


    // Randomly rotate the tile.
    p = r2(floor(rnd.x*6.)*3.14159265/3.)*p;


    // Distance field variable, and a hacky flag to turn off pattern rendering - Basically, to stop the
    // portals being rendered under the joins.
    vec4 d, noPat = vec4(0);

    // Utils for point storage and the UV coordinates for each of the shapes.
    vec2 p1, p2, p3, tu1, tu2, tu3;


    // DISTANCE FIELD, SHADE, ID, AND TEXTURE CALCULATIONS

    // If one of the random variables is above a certain threshold, render one of the
    // tiles. The thresholds are distributed according to how much weighting you'd like
    // to give a certain kind of tile. For instance, I wanted more curves, so gave more
    // weighting to the arc tiles than the straight line ones.

    if(rnd.y>.8){ // Three small arcs segments. So-called standard hexagonal Truchet.

        // Small arc one.
		p1 = p - vec2(.5, .8660254/3.);
        d.x = length(p1) - rSm;
        ds.x = d.x;
        d.x = abs(d.x) - th;
        a = atan(p1.y, p1.x);
        // One dot per small arc segment. Three make up a circle.
        gRnd.x = hash21(h.zw + floor(a/6.283*6.) + .37);
        a = mod(a/3.14159265, 2.) - 1.;
        if(a<.0 || a > .333) noPat.x = 1.;
        tu1 = vec2(a, ds.x + .5);

        // Small arc two.
        p2 = p - vec2(-.5, .8660254/3.);
        d.y = length(p2) - rSm;
        ds.y = d.y;
        d.y = abs(d.y) - th;
        a = atan(p2.y, p2.x);
        gRnd.y = hash21(h.zw + floor(a/6.283*6.) + 7.45);
        a = mod(a/3.14159265, 2.) - 1.;
        if(a<.666) noPat.y = 1.;
        tu2 = vec2(a, ds.y + .5);

        // Small arc three.
        p3 = p - vec2(0, -.8660254*2./3.);
        d.z = length(p3) - rSm;
        ds.z = d.z;
        d.z = abs(d.z) - th;
        a = atan(p3.y, p3.x);
        gRnd.z = hash21(h.zw + floor(a/6.283*6.) + 9.23);
        a = mod(a/3.14159265, 2.) - 1.;
        if(a<-.666  || a>-.333) noPat.z = 1.;
        tu3 = vec2(a, ds.z + .5);

        // No overlap, so no render order flipping is necessary.


    }
    else if(rnd.y>.65){ // Two long arcs, straight line, with crossover.


		// Large arc one.
        p1 = p - vec2(1, 0);
        d.x = length(p1) - rLg;
        ds.x = d.x;
        d.x = abs(d.x) - th;
        // Three dots per long arc segment.
        a = atan(p1.y, p1.x)*3.;
        // 6 Segments make up 2PI. Accounting for the "3" above. Hence, the "6" factor.
        // Makes sense now - after stuffing around for ten minutes. :)
        gRnd.x = hash21(h.zw + floor(a/6.283*6.) + 6.72);
        a = mod(a/3.14159265, 2.) - 1.;
        if(abs(a)>.333) noPat.x = 1.;
        tu1 = vec2(a, ds.x + .5);

		// Large arc two.
        p2 = p - vec2(-1, 0);
        d.y = length(p2) - rLg;
        ds.y = d.y;
        d.y = abs(d.y) - th;
        a = atan(p2.y, p2.x)*3.;
        gRnd.y = hash21(h.zw + floor(a/6.283*6.) + 3.37);
        a = mod(a/3.14159265, 2.) - 1.;
        if(abs(a)<.666) noPat.y = 1.;
        tu2 = vec2(a, ds.y + .5);

        // Straight line.
        d.z = abs(p.y);
        ds.z = d.z;
        d.z = (d.z) - th;
        a = mod(p.x, 1.);
        // Three dots per line segment.
        gRnd.z = hash21(h.zw + floor(a*3.) + 1.83);
        if(a<.666 && a>.333) noPat.z = 1.;
        tu3 = vec2(a, ds.z + .5);


        // Render order flipping.

        if(rnd.w>.75) { // d3, d1, d2
            d.xz = d.zx;
            ds.xz = ds.zx;
            swap(tu1.x, tu3.x); swap(tu1.y, tu3.y);
            noPat.xz = noPat.zx;
            gRnd.xz = gRnd.zx;
        }
        else if(rnd.w>.5) {  // d1, d3, d2
            d.yz = d.zy;
            ds.yz = ds.zy;
            swap(tu2.x, tu3.x);  swap(tu2.y, tu3.y);
            noPat.yz = noPat.zy;
            gRnd.yz = gRnd.zy;
        }
        else if(rnd.w>.25) { // d2, d3, d1
            d.xyz = d.yzx;
            ds.xyz = ds.yzx;
            swap(tu3.x, tu1.x, tu2.x); swap(tu3.y, tu1.y, tu2.y);
            noPat.xyz = noPat.yzx;
            gRnd.xyz = gRnd.yzx;
        }


    }
    else if(rnd.y>.55){ // Two short arcs, straight line, no crossover.


		// Small arc one.
		p1 = p - vec2(0, .8660254*2./3.);
        d.x = length(p1) - rSm;
        ds.x = d.x;
        d.x = abs(d.x) - th;
        a = atan(p1.y, p1.x);
        // One dot per small arc segment. Three make up a circle.
        gRnd.x = hash21(h.zw + floor(a/6.283*6.));
        a = mod(a/3.14159265, 2.) - 1.;
        if(a<.333 || a>.666) noPat.x = 1.;
        tu1 = vec2(a, ds.x + .5);

        // Small arc two.
        p2 = p - vec2(0, -.8660254*2./3.);
        d.y = length(p2) - rSm;
        ds.y = d.y;
        d.y = abs(d.y) - th;
        a = atan(p2.y, p2.x);
        gRnd.y = hash21(h.zw + floor(a/6.283*6.) + 4.78);
        a = mod(a/3.14159265, 2.) - 1.;
        if(a<-.666 || a>-.333) noPat.y = 1.;
        tu2 = vec2(a, ds.y + .5);

        // Straight line.
        d.z = abs(p.y);
        ds.z = d.z;
        d.z = (d.z) - th;
        a = mod(p.x, 1.);
        // Three dots per line segment.
        gRnd.z = hash21(h.zw + floor(a*3.) + 3.96);
        if(a<.666 && a>.333) noPat.z = 1.;
        tu3 = vec2(a, ds.z + .5);

		// No overlap, so no rendering order flipping is necessary.


    }
    else if(rnd.y>.45){ // Three straight lines.


        // Straight line one.
        d.x = abs(p.y);
        ds.x = d.x;
        d.x = (d.x) - th;
        a = mod(p.x, 1.);
        gRnd.x = hash21(h.zw + floor(a*3.) + 2.92);
        if(a<.666 && a>.333) noPat.x = 1.;
        tu1 = vec2(a, ds.x + .5);

        // Straight line two.
        d.y = abs(p.y*.5 - p.x*.8660254);
        ds.y = d.y;
        d.y = (d.y) - th;
        a = mod(p.x*.5 + p.y*.8660254, 1.);
        gRnd.y = hash21(h.zw + floor(a*3.) + 5.38);
        if(a<.666 && a>.333) noPat.y = 1.;
        tu2 = vec2(a, ds.y + .5);

        // Straight line three.
        d.z = abs(p.y*.5 + p.x*.8660254);
        ds.z = d.z;
        d.z = abs(d.z) - th;
        a = mod(p.x*.5 - p.y*.8660254, 1.);
        gRnd.z = hash21(h.zw + floor(a*3.) + 1.27);
        if(a<.666 && a>.333) noPat.z = 1.;
        tu3 = vec2(a, ds.z + .5);


        // Render order flipping.

        //rnd.w = fract(rnd.w + .37);

        if(rnd.w>.75) { // d3, d1, d2
            d.xz = d.zx;
            ds.xz = ds.zx;
            swap(tu1.x, tu3.x); swap(tu1.y, tu3.y);
            noPat.xz = noPat.zx;
            gRnd.xz = gRnd.zx;
        }
        else if(rnd.w>.5) {  // d1, d3, d2
            d.yz = d.zy;
            ds.yz = ds.zy;
            swap(tu2.x, tu3.x);  swap(tu2.y, tu3.y);
            noPat.yz = noPat.zy;
            gRnd.yz = gRnd.zy;
        }
        else if(rnd.w>.25) { // d2, d3, d1
            d.xyz = d.yzx;
            ds.xyz = ds.yzx;
            swap(tu3.x, tu1.x, tu2.x); swap(tu3.y, tu1.y, tu2.y);
            noPat.xyz = noPat.yzx;
            gRnd.xyz = gRnd.yzx;
        }


    }
	else { // Two cross over large arcs, and one small one.


        // Large arc one.
        p1 = p - vec2(1, 0);
        d.x = length(p1) - rLg;
        ds.x = d.x;
        d.x = abs(d.x) - th;
        a = atan(p1.y, p1.x)*3.; // Longer arc factor of three.
        gRnd.x = hash21(h.zw + floor(a/6.283*6.) + 8.71);
        a = mod(a/3.14159265, 2.) - 1.;
        if(a > .333 || a<-.333) noPat.x = 1.;
        tu1 = vec2(a, ds.x + .5);

 		// Large arc two.
        p2 = p - r2(3.14159265/3.)*vec2(1, 0);
        d.y = length(p2) - rLg;
        ds.y = d.y;
        d.y = abs(d.y) - th;
        a = atan(p2.y, p2.x)*3.; // Longer arc factor of three.
        gRnd.y = hash21(h.zw + floor(a/6.283*6.) + 3.87);
        a = mod(a/3.14159265, 2.) - 1.;
        if(abs(a)<.666) noPat.y = 1.;
        tu2 = vec2(a, ds.y + .5);

        // Small arc.
        p3 = p - r2(-3.14159265/3.)*vec2(0, .57735);
        d.z = length(p3) - rSm;
        ds.z = d.z;
        d.z = abs(d.z) - th;
        a = atan(p3.y, p3.x); // Smaller arc.
        gRnd.z = hash21(h.zw + floor(a/6.283*6.) + 5.54);
        a = mod(a/3.14159265, 2.) - 1.;
        if(a<.666) noPat.z = 1.;
        tu3 = vec2(a,  ds.z + .5);


        // Render order flipping.
        //rnd.w = fract(rnd.w + .71);

        if(rnd.w>.5) {
            d.xy = d.yx;
            ds.xy = ds.yx;
            swap(tu1.x, tu2.x); swap(tu1.y, tu2.y);
            noPat.xy = noPat.yx;
            gRnd.xy = gRnd.yx;
        }


    }


/////

    // JOINER BLOCKS
    //
    // The joins need to be rendered seperately using an offset hexagonal grid, due to pixelated
    // mismatching at the hexagonal boundaries when highlighting... It's a long story... :)
    //
    // Three blocks, arranged in a tri blade propellor scheme.
    //
    vec2 q = h2.xy;
    float blc = abs(length(q) - .8660254/3.) - th;

    q = r2(3.14159/6.)*q;
    a = atan(q.y, q.x);
    float ia = floor(a/6.283*3.) + .5;
    q = r2(ia*6.283/3.)*q;
    q.x -= .8660254/3.;

    q = abs(q);// - vec2(th, .04);

    // Holding the joiner block distance field value in a global variable to be
    // used elsewhere.
    // The weird mix function gives the joins a slight pinch at the ends to feed the illusion a little more.
    d.w = mix(length(q) - .04, max(q.x - .16, q.y - .04), .9);
    //float blocks = mix(length(q) - .04, min(max(q.x - .15, q.y - .04), 0.) + length(max(q - vec2(.15, .04), 0.)), .9);
    // The shade value (used for highlighting) has been tweaked in an unnatural way to give the reflected
    // look I was after, but I wouldn't put too much stock in it.
    ds.w = mix(length(q), min(max(q.x, q.y), 0.) + length(max(q - vec2(0, .0), 0.)), .9);



//////

    // TEXTURE PATTERN
    // The textured dot pattern to make the portals. Stored in a global variable "pat" to be used
    // elsewhere.

    vec2 sc = vec2(3., 3);
    pat.x = dots(tu1*sc); // Dot pattern.
    pat.x = pat.x - .135; // Distance field.
    if(noPat.x > .5) pat.x = 1.;

    pat.y = dots(tu2*sc);
    pat.y = pat.y - .135;
    if(noPat.y > .5) pat.y = 1.;

    pat.z = dots(tu3*sc);
    pat.z = pat.z - .135;
    if(noPat.z > .5) pat.z = 1.;

    // Block pattern. Just a dummy variable for completeness, as the as blocks won't be textured.
    pat.w = 1.;

/*
	// Actual textures. Line UV changes, and changes in the "doObject" function are required.
    pat.x = texture(iChannel0, tu1*1.).x;
    pat.y = texture(iChannel0, tu2*1.).x;
    pat.z = texture(iChannel0, tu3*1.).x;
	pat = pat*pat;
*/

//////

    return d;


}


void main(){


    //vec2 fC = floor(fragCoord*4.)/4.;
    // Aspect correct screen coordinates.
	vec2 u = ((gl_FragCoord.xy - pos_correction.xy) - iResolution.xy*.5)/clamp(iResolution.y, 300., 650.);

    vec2 p = u*4. ;
//    vec2 p = u*4. + s.yx*iTime/4.;

    vec3 tx = texture(texture_in, p/5.).xyz;//r2(3.14159265/9.)*
    tx *= tx;
    //tx = smoothstep(.05, .5, tx);

    vec3 bg = vec3(1, .05, .15)*max(1. - length(u)*.25, 0.);
    bg = mix(bg, vec3(0), (1. - clamp(sin((p.x*.8660254 + p.y*.5)*6.283*32.)*2. + 1.25, 0., 1.))*.35);




    // Truchet shadow. We're only after an overall distance field value, so the texturing,
    // shade values, etc, aren't needed. It's a bit wasteful, but the function is only
    // called once per pass, so the GPU should barely notice.
    vec4 ds3 = scene(p + .1);

    float dShad = min(min(ds3.x, ds3.y), min(ds3.z, ds3.w));

    // Applying the Truchet shadow to the background.
    bg = mix(bg, vec3(0), (1. - smoothstep(0., .1, dShad))*.85);

    // Set the scene color to the background texture.
    vec3 col = bg;


    // Obtaining an offset shade value, which will be combined with the local shade value to
    // produce a bit of highlighting. It's based off of directional derivative lighting, and
    // is just a cheap way to produce something anologous to diffuse light.
    //
    // As mentioned above, it's a bit wasteful recalating everything (distance fields, texture
    // coordinates, etc) just to obtain a shade value, but this isn't a GPU intensive example,
    // so some extra trig calls, and so forth, shouldn't matter.
    vec4 d2 = scene(p - .008);
    // The shade value is global (another hack), so we need to store it before making the
    // function call again.
    vec4 ds2 = ds;

    // The main distance field function - It's called after the offset ones, because there are some
    // global shade and pattern values that needed: Obtaining the four distance field values. The first
    // three field values returned depend upon the hexagonal tile used, so will consist of mixtures
    // or small arcs, large arcs or lines. The fourth value retuned is the join.
    vec4 d = scene(p);

    // Plugging in the object variables, and rendering them accordingly. Depending on the hexagonal tile
    // configuration, the objects consist of small arcs, large arcs and lines. In some cases, object are
    // rendered over one another. Hence, the necessity to make three rendering calls in succession.
    col = doObject(col, d.x, pat.x, vec2(ds.x, ds2.x), 1., gRnd.x);
	col = doObject(col, d.y, pat.y, vec2(ds.y, ds2.y), 1., gRnd.y);
    col = doObject(col, d.z, pat.z, vec2(ds.z, ds2.z), 1., gRnd.z);

    // The joiner blocks. They're drawn on top, so are rendered last.
    col = doObject(col, d.w, pat.w, vec2(ds.w, ds2.w)/1., 0., gRnd.w);


    // Adding some grunge, just to break things up a little. Comment this section
    // out, and the example looks too clean.
    float fBm = noise3D(vec3(p*32., 1. - col.x))*.66 + noise3D(vec3(p*64., 2. - 2.*col.x))*.34;
    col *= fBm*.65 + .65;



    #ifdef SHOW_GRID
    // Putting in the grid borders.
    float eDist = hex(getHex(p).xy);
    //col = mix(col, vec3(1), smoothstep(0., .01, min(min(d.x, d.y), d.z))*smoothstep(0., .02, eDist - .5 + .02));
    col = mix(col, vec3(.3, 1, .2)*2., (smoothstep(0., .01, min(min(d.x, d.y), d.z) - .04))*smoothstep(0., .03, eDist - .5 + .02)*.7);
  	#endif

    // The separate offset grid that the blocks are produce in.
	//float eDist2 = hex(getHex(p - vec2(0, .8660254*2./3.)).xy);
    //col = mix(col, vec3(.5, .7, 1)*2., smoothstep(0., .03, eDist2 - .5 + .02)*.7);

        // Subtle vignette.
    u = gl_FragCoord.xy/iResolution.xy;
    col *= pow(16.*u.x*u.y*(1. - u.x)*(1. - u.y) , .125)*.65 + .35;
    // Colored varation.
    //col = mix(pow(min(vec3(1.5, 1, 1).zyx*col, 1.), vec3(1, 3, 16)), col,
             //pow(16.*u.x*u.y*(1. - u.x)*(1. - u.y) , .125));



    // Rough gamma correction.
	gl_FragColor = vec4(sqrt(max(col, 0.)), 1);

}
