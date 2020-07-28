"use strict"

/**************************** config ****************************/
const PLANET = 'earth';
const path = require('path');
const URL_PREFIX = `https://kh.google.com/rt/${PLANET}/`;
const MAX_LEVEL = 17;
/****************************************************************/

const utils = require('./lib/utils')({
	URL_PREFIX, DUMP_JSON_DIR: null, DUMP_RAW_DIR: null, DUMP_JSON: false, DUMP_RAW: false
});

const latLongToOctant = require('./lib/convert-lat-long-to-octant')(utils);

/***************************** main *****************************/

const	colorFG = '\u001b[31m';
const	resetFG = '\u001b[39m';

const sleep = (waitTimeInMs) => new Promise(resolve => setTimeout(resolve, waitTimeInMs));

let color = {
    byNum: (mess, fgNum, bgNum) => {
        mess = mess || '';
        fgNum = fgNum === undefined ? 31 : fgNum;
        bgNum = bgNum === undefined ? 47 : bgNum;
        return '\u001b[' + fgNum + 'm' + '\u001b[' + bgNum + 'm' + mess + '\u001b[39m\u001b[49m';
    },
    black: (mess, fgNum) => color.byNum(mess, 30, fgNum),
    red: (mess, fgNum) => color.byNum(mess, 31, fgNum),
    green: (mess, fgNum) => color.byNum(mess, 32, fgNum),
    yellow: (mess, fgNum) => color.byNum(mess, 33, fgNum),
    blue: (mess, fgNum) => color.byNum(mess, 34, fgNum),
    magenta: (mess, fgNum) => color.byNum(mess, 35, fgNum),
    cyan: (mess, fgNum) => color.byNum(mess, 36, fgNum),
    white: (mess, fgNum) => color.byNum(mess, 37, fgNum)
};

let out = process.stdout;
// Set the position of a cursor
let setCur = (x, y) => {
    x = x || 0;
    y = y || 0;
    out.write('\u001b[' + y + ';' + x + 'H');
}
let clearScreen = () => {
    out.write('\u001b[2J');
}
let colorsSet = () => {
    out.write('\u001b[47m');
    out.write('\u001b[30m');
};
let colorsDefault = () => {
    out.write('\u001b[39m\u001b[49m');
};
// draw the area and at symbol
let draw = (opt) => {
    opt = opt || {};
    opt.x = opt.x || 1;
    opt.y = opt.y || 1;
    clearScreen();
    setCur(1, 1);
    colorsSet();
    // draw area
    out.write('..........\n');
    out.write('..........\n');
    out.write('..........\n');
    out.write('..........\n');
    out.write('move: wasd; exit: x');
    // draw at symbol
    setCur(opt.x, opt.y);
    out.write('@');
    colorsDefault();
};
// start position
let pos = {
    x: 1,
    y: 1,
    w: 10,
    h: 4
};

async function doScreen() {  
	'use strict';
	
//	process.stdout.write('\x1Bc'); 
	process.stdout.write("\u001b[2J\u001b[0;0H");
//	process.stdout.write(colorFG + "hello" + resetFG);
//	process.stdout.write(color.red("HELLO"));

//	process.stdout.write('\033c');
//    console.log("\033[H\033[2J");  
}  

async function run() {
	let [lat, lon] = [process.argv[2], process.argv[3]];


	if ([lat, lon].includes(undefined)) {

//New York
//	let lat0=40.685429;
//	let lon0=73.937601;
//	let lat1=40.669668;
//	let lon1=74.082954;

/*
	let lat0=40.785429;
	let lon0=73.837601;
	let lat1=40.569668;
	let lon1=74.192954;
*/

//	let lat0=40.78;
//	let lon0=73.83;
//	let lat1=40.76;
//	let lon1=73.85;

//LA
	let lat0=34.081049;
	let lon0=118.143811;
	let lat1=34.013811;
	let lon1=118.258214;

//enschede
/*
	let lat0=52.247224;
	let lon0= 6.841952;
	let lat1=52.191311;
	let lon1= 6.943110;
*/

//amsterdam
/*
        let lat0=52.439745;
        let lon0= 4.750032;
        let lat1=52.286213;
        let lon1= 5.032107;
*/
        let [lat, lon] = [lat1, lon0];
        [lat, lon] = [parseFloat(lat), parseFloat(lon)];

        let init_foundOctants = await latLongToOctant(lat, -lon, MAX_LEVEL);
        var match=0;
        for (let octantLevel in init_foundOctants) {
//            console.log('octantLevel=' + octantLevel + ' #octants=' + init_foundOctants[octantLevel].octants.length);
            if (octantLevel === '17') match=1;
        }

        var size_lat=0.0; var size_lon=0.0;
        var middle_lat=0.0; var middle_lon=0.0;
        var from_lat=0.0; var from_lon=0.0;
        var to_lat=0.0; var to_lon=0.0;


        if (match === 1) {
            let init_octants = init_foundOctants[17].octants;
            let init_box = init_foundOctants[17].box;
//            console.log('found:   (lat,lon): ' + lat.toFixed(13) + ',' + lon.toFixed(13));
            from_lat=init_box.n; to_lat=init_box.s;
            from_lon=init_box.w; to_lon=init_box.e;
//            console.log("lat/lon: (n,w,s,e): " + init_box.n.toFixed(13) + "," + init_box.w.toFixed(13) + "," + init_box.s.toFixed(13) + "," + init_box.e.toFixed(13));
            middle_lat=(init_box.n+init_box.s)/2.0;
            middle_lon=(init_box.e+init_box.w)/2.0;
//            console.log("middle:  (lat,lon): " + (middle_lat).toFixed(13) + "," + (middle_lon).toFixed(13));
            size_lat=(init_box.n-init_box.s);
            size_lon=(init_box.e-init_box.w);
//            console.log("size:    (lat,lon): " + (size_lat).toFixed(13) + "," + (size_lon).toFixed(13));
//            for (let i = 0; i < init_octants.length; i++) {
//                console.log("octant(s):"+init_octants[i]);
//            }
            lat = middle_lat;
            lon = middle_lon;
        } else {
            console.log('Not found: ' + lat + ',' + lon);
        }
		
		var fx,fy,f,x,y;
		let out_x = {}
		let out_y = {}
		let out = {}
		let out_index = {}
		let index=0;
		let indexedOctants = {}
		let middle_lons = {}
		let middle_lats = {}
		let numberOffoundOctants = 0;
		
        var num_lats=0;
        var num_lons=0;
        if (size_lat>0) num_lats=Math.round((lat0-lat1)/size_lat);
        if (size_lon>0) num_lons=Math.round((lon1-lon0)/size_lon);
		num_lats = Math.round(num_lats);
		num_lons = Math.round(num_lons);

        var line = '';
        var prev_line = '';
//		console.log("(" + num_lons.toString().padStart(3, ' ') +","+num_lats.toString().padStart(3, ' ')+") (           NORTH,           WEST,           SOUTH,           EAST) (OCTANT(S)        )");

//		console.log("(  X,  Y) (           NORTH,           WEST,           SOUTH,           EAST) (OCTANT(S)        )");
//		console.log("-------------------------------------------------------------------------------------------------");

        var lat_count=0;
        console.log('static std::string *octants['+num_lats+'];');
//new
		lat = middle_lat;
		var fx,fy,f,x,y;

		for (let lat_number=0; lat_number<num_lats; lat_number++) {
//		for (let lat=middle_lat; lat<lat0; lat=lat+size_lat) {


            var ok;
            var row = '';
            var row_cc = '{';
            var sub_line = '';
            var prev_level = '';
            var lon_count=0;
            let set=0;
//            for (lon=-middle_lon; lon<lon1; lon=lon+size_lon) {
			lon = middle_lon;
			
	        for (let lon_number=0; lon_number<num_lons; lon_number++) {
                [lat, lon] = [parseFloat(lat), parseFloat(lon)];

                let foundOctants = await latLongToOctant(lat, -lon, MAX_LEVEL);
                for (let octantLevel in foundOctants) {
                    let octants = foundOctants[octantLevel].octants;
                    let set_sub=0;
                    if ( octantLevel === '17' ) {
						let box = foundOctants[octantLevel].box;	
						if (lon_number===0) size_lat=(box.n-box.s);

                        ok=0;
                        let line_start= "["+lat_number.toString().padStart(3, ' ')+
						"]["+lon_number.toString().padStart(3, ' ')+"] (" + box.n.toFixed(13) + "," + box.w.toFixed(13) + "," + box.s.toFixed(13) + "," + box.e.toFixed(13) + ")";
//                        let line_start= "("+lon_count.toString().padStart(3, ' ')+","+lat_count.toString().padStart(3, ' ')+") (" + box.n.toFixed(13) + "," + box.w.toFixed(13) + "," + box.s.toFixed(13) + "," + box.e.toFixed(13) + ")";
                        let line_end="";
//                        let set=0;
                        for (let i = 0; i < octants.length; i++) {
                            ok=1;
    //						console.log(box.w.toFixed(13) + " (lat From)");
    //						console.log(box.n.toFixed(13) + " (lon From)");
    //						console.log(box.e.toFixed(13) + " (lat To)");
    //						console.log(box.s.toFixed(13) + " (lon To)");
//                            if (set===1) line_end=line_end+",";
//take last one....
                            line_end=octants[i];
//                            line_end=line_end+octants[i];
//                            set = 1;
//    						console.log("(" + box.n.toFixed(13) + "," + box.w.toFixed(13) + "," + box.s.toFixed(13) + "," + box.e.toFixed(13) + ") (" +  i + "," + octants[i] +") ("+lat_count.toString().padStart(3, ' ')+","+lon_count.toString().padStart(3, ' ')+")");
//    						console.log("lat/lon (n,w,s,e) (oct,#) pos (x,y): (" + box.n.toFixed(13) + "," + box.w.toFixed(13) + "," + box.s.toFixed(13) + "," + box.e.toFixed(13) + ") ("+octants[i] + "," + i +") ("+lat_count.toString().padStart(3, ' ')+","+lon_count.toString().padStart(3, ' ')+")");
    //						console.log("lat/lon (w,n,e,s): ",box.w,box.n,box.e,box.s,octants[i]);
    //						console.log(octants[i]);
//take last one....

//                            row=row+octants[i]+' ';

    //						row=`${row} ${octants[i]}`;
    //						const meshName = `${nodeName}_${meshIndex}`;

    //						`${OCTANTS.join('+')}-${MAX_LEVEL}-${rootEpoch}`


						indexedOctants[numberOffoundOctants]=line_end;
						middle_lats[numberOffoundOctants] = lat;
						middle_lons[numberOffoundOctants] = lon;

//						fx=lon- middle_lon*2.0 - (lon1+lon0)/2.0;
//						fy=lat- (lat0+lat1)/2.0;
						fx=(lon - (lon1+lon0)/2.0);
						fy=(lat - (lat0+lat1)/2.0)*2.0; //lat -90 : +90, long -180 : +180
						f=Math.sqrt(fx*fx+fy*fy);

						out[numberOffoundOctants] = f;
						out_x[numberOffoundOctants]=lon_count;
						out_y[numberOffoundOctants]=lat_count;
						out_index[numberOffoundOctants] = numberOffoundOctants;

//						console.log( "fx=" + fx + " fy=" + fy + " "+f);


						console.log(
							 "["+lon_count.toString().padStart(3, ' ')+"/"+num_lons.toString().padStart(3, ' ')+"]"
							+"["+lat_count.toString().padStart(3, ' ')+"/"+num_lats.toString().padStart(3, ' ')+"]="+indexedOctants[numberOffoundOctants]+
							" lat="+middle_lats[numberOffoundOctants]+
							" lon="+middle_lons[numberOffoundOctants]+
							" flat=" + (Math.round(fy*1000000)).toString().padStart(8, ' ')+
							" flon=" + (Math.round(fx*1000000)).toString().padStart(8, ' ')+
							" f=" + (Math.round(f*1000000)).toString().padStart(8, ' ') );


						numberOffoundOctants++;


                        }
                        if (set_sub===1) row=row+' ';
                        if (set===1) row_cc=row_cc+',';
                        set_sub=1;
                        row=row+line_end+' ';
//columns
//                        console.log(line_end+'-21');

//new
//						console.log("longtid="+lon);

						indexedOctants[numberOffoundOctants]=line_end;
						middle_lats[numberOffoundOctants] = lat;
						middle_lons[numberOffoundOctants] = lon;

//						fx=middle_lons[index] - middle_lon*2.0 - (lon1+lon0)/2.0;
//						fy=middle_lats[index]- (lat0+lat1)/2.0;

						fx=lon- middle_lon*2.0 - (lon1+lon0)/2.0;
						fy=lat- middle_lat*2.0 - (lat0+lat1)/2.0;
//						fy=lat- (lat0+lat1)/2.0;
						f=Math.sqrt(fx*fx+fy*fy);
//						console.log( "fx=" + fx + " fy=" + fy + " "+f);


						console.log(
							 "["+lon_number.toString().padStart(3, ' ')+
							 "/"+num_lons.toString().padStart(3, ' ')+"]"+
							 "["+lat_number.toString().padStart(3, ' ')+
							 "/"+num_lats.toString().padStart(3, ' ')+"]="+
							 indexedOctants[numberOffoundOctants]+
							 " lat="+middle_lats[numberOffoundOctants].toString().padStart(7, ' ')+
							 " lon="+middle_lons[numberOffoundOctants].toString().padStart(7, ' ')+
							 " fx=" + (Math.round(fx*1000000)/1000000).toString().padStart(8, ' ')+
							 " fy=" + (Math.round(fy*1000000)/1000000).toString().padStart(8, ' ')+
							 " f=" + (Math.round(f*1000000)/1000000).toString().padStart(8, ' ') );

						numberOffoundOctants++;
							 
                        row_cc=row_cc+"\""+line_end+"\""
//                        console.log(line_start+" ("+line_end+")" );
                        size_lat=(box.n-box.s);
                        size_lon=(box.e-box.w);
						middle_lat=(box.n+box.s)/2.0;
						middle_lon=(box.e+box.w)/2.0;
						num_lats=Math.round((lat0-lat1)/size_lat);
						num_lons=Math.round((lon1-lon0)/size_lon);


                    }
                }
                set=1;
				if (prev_level!=row) sub_line=sub_line+row;
                prev_level=row;
                if (ok === 0) {
                    console.log('Not found:' + lat + ',' + lon);
                }
                lon_count++;
				lon = +size_lon*lon_count;

			}
            if (prev_line!=sub_line) {
                line=line+'\n'+sub_line;
//rows
//                console.log( sub_line );
            }
            row_cc=row_cc+"};";

//C++
//            console.log('octants['+lat_count+']=new std::string['+num_lons+'] '+row_cc);


//            console.log('octants['+lat_count+']='+row_cc);
            prev_line=sub_line;
            sub_line='';
            lat_count++;
			lat = middle_lat*2.0+size_lat;
			
        }

    //	console.log( 'total: ' + line );

//						indexedOctants[numberOffoundOctants]=line_end;
//						middle_lats[lat_count] = lat;
//						middle_lons[lon_count] = lon;



		ok=0;
		while (ok===0) {
			ok=1;
			for (let i=0; i<numberOffoundOctants-1; i++) {
				out_index[i]
				if (out[i+1]<out[i]) {
					ok=0;
					let tussen=indexedOctants[i];					indexedOctants[i]=indexedOctants[i+1];					indexedOctants[i+1]=tussen;
					let tussen_x=out_x[i];							out_x[i]=out_x[i+1];									out_x[i+1]=tussen_x;
					let tussen_y=out_y[i];							out_y[i]=out_y[i+1];									out_y[i+1]=tussen_y;
					let tussen_out_index=out_index[i];				out_index[i]=out_index[i+1];							out_index[i+1]=tussen_out_index;
					let tussen_out=out[i];							out[i]=out[i+1];										out[i+1]=tussen_out;
					let tussen_middle_lats=middle_lats[i];			middle_lats[i]=middle_lats[i+1];						middle_lats[i+1]=tussen_middle_lats;
					let tussen_middle_lons=middle_lons[i];			middle_lons[i]=middle_lons[i+1];						middle_lons[i+1]=tussen_middle_lons;
				}
			}
		}

		for (let i=0; i<numberOffoundOctants; i++) {
			console.log( i.toString().padStart(5, ' ')+
				"<-"+out_index[i].toString().padStart(5, ' ')+
				" ["+out_x[i].toString().padStart(5, ' ')+"/"+num_lons.toString().padStart(5, ' ')+"]"+
				"["+out_y[i].toString().padStart(5, ' ')+"/"+num_lats.toString().padStart(5, ' ')+"]="+
				indexedOctants[i]+
				" lat="+middle_lats[i]+
				" lon="+middle_lons[i]+
				" dlat="+ Math.round((middle_lats[i]-(lat0+lat1)/2.0)*1000000).toString().padStart(8, ' ') +
				" dlon="+ Math.round((middle_lons[i]-(lon0+lon1)/2.0)*1000000).toString().padStart(8, ' ') +
				 " f=" + Math.round(out[i]*1000000).toString().padStart(8, ' ') );
		}
		var fmin=99999999999.9;
		var fmax=0.0;
		for (let i=0; i<numberOffoundOctants; i++) {
			console.log(
				"node dump_obj_CITYNAME.js "+indexedOctants[i]+" 21 --parallel-search");
			if (out[i]<fmin) fmin=out[i];
			if (out[i]>fmax) fmax=out[i];
		}
		clearScreen();
		console.log("fmin="+Math.round((fmin)*1000000).toString().padStart(8, ' ')+"  "+
					"fmax="+Math.round((fmax)*1000000).toString().padStart(8, ' '))
					
		for (let y=0; y<lat_count; y++) {
			for (let x=0; x<lon_count; x++) {
				let i=x+y*lon_count;
//				setCur(out_x[i]*5+1, out_y[i]*2+2);
//				process.stdout.write(color.red("OOOO"));
				setCur(out_x[i]+1, out_y[i]+1);
				process.stdout.write(color.blue("O"));
			}
		}
		var a;
		for (let i=0; i<numberOffoundOctants+500; i++) {
			a=0;
			if (i>=a && (i-a<numberOffoundOctants)) {
				setCur(out_x[i-a]+1, out_y[i-a]+1);
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+2);
//				process.stdout.write(color.green((i-a).toString().padStart(4, ' ')));
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+3);
//				process.stdout.write(color.red(out_index[i-a].toString().padStart(4, ' ')));
				process.stdout.write(color.red("O"));
			}
			a=100
			if (i>=a && (i-a<numberOffoundOctants)) {
				setCur(out_x[i-a]+1, out_y[i-a]+1);
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+2);
//				process.stdout.write(color.blue((i-a).toString().padStart(4, ' ')));
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+3);
//				process.stdout.write(color.green(out_index[i-a].toString().padStart(4, ' ')));
				process.stdout.write(color.red("O"));
			}
			a=200;
			if (i>=a && (i-a<numberOffoundOctants)) {
				setCur(out_x[i-a]+1, out_y[i-a]+1);
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+2);
//				process.stdout.write(color.magenta((i-a).toString().padStart(4, ' ')));
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+3);
//				process.stdout.write(color.blue(out_index[i-a].toString().padStart(4, ' ')));
				process.stdout.write(color.blue("O"));
			}
			a=300;
			if (i>=a && (i-a<numberOffoundOctants)) {
				setCur(out_x[i-a]+1, out_y[i-a]+1);
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+2);
//				process.stdout.write(color.yellow((i-a).toString().padStart(4, ' ')));
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+3);
//				process.stdout.write(color.magenta(out_index[i-a].toString().padStart(4, ' ')));
				process.stdout.write(color.magenta("O"));
			}
			a=400;
			if (i>=a && (i-a<numberOffoundOctants)) {
				setCur(out_x[i-a]+1, out_y[i-a]+1);
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+2);
//				process.stdout.write(color.green((i-a).toString().padStart(4, ' ')));
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+3);
//				process.stdout.write(color.yellow(out_index[i-a].toString().padStart(4, ' ')));
				process.stdout.write(color.yellow("O"));

			}
			a=500;
			if (i>=a && (i-a<numberOffoundOctants)) {
				setCur(out_x[i-a]+1, out_y[i-a]+1);
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+2);
//				process.stdout.write(color.red((i-a).toString().padStart(4, ' ')));
//				setCur(out_x[i-a]*5+1, out_y[i-a]*2+3);
//				process.stdout.write(color.green(out_index[i-a].toString().padStart(4, ' ')));
				process.stdout.write(color.green("O"));

			}
			await sleep(10);
		}
		

		


/*		const invoc = `node ${require('path').basename(__filename)}`;
		console.error(`Usage:`);
		console.error(`  ${invoc} [latitude] [longitude]`);
		console.error(`  ${invoc} 37.420806884765625 -122.08419799804688`);
		process.exit(1);
*/
	} else {
        [lat, lon] = [parseFloat(lat), parseFloat(lon)];

        const foundOctants = await latLongToOctant(lat, lon, MAX_LEVEL);
        for (let octantLevel in foundOctants) {
            let octants = foundOctants[octantLevel].octants;
            let box = foundOctants[octantLevel].box;
    //		console.log("Octant Level:", octantLevel);
    //		console.log(box);
    //		console.log("Level:", octantLevel);
//            if ( octantLevel === '17' ) {
                for (let i = 0; i < octants.length; i++) {
    //				ok=1;
                    console.log("Level: "+octantLevel+" lat/lon (w,n,e,s): ",box.w,box.n,box.e,box.s,octants[i]);
    //				console.log(octants[i]);
    //				console.log( "octants[" + octantLevel + "][" + i + "]=" + octants[i]);
                }
//            }
        }
	}



//	console.log(lat + ', ' + lon);
//	console.log('-------------');

/*
*/
}

/****************************************************************/
(async function program() {
	await run();
})().then(() => {
	process.exit(0);
}).catch(e => {
	console.error(e);
	process.exit(1);
});
