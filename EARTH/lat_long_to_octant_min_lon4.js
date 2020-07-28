"use strict"

/**************************** config ****************************/
const PLANET = 'earth';
const path = require('path');
const URL_PREFIX = `https://kh.google.com/rt/${PLANET}/`;
const MAX_LEVEL = 22;
/****************************************************************/

const utils = require('./lib/utils')({
	URL_PREFIX, DUMP_JSON_DIR: null, DUMP_RAW_DIR: null, DUMP_JSON: false, DUMP_RAW: false
});

const latLongToOctant = require('./lib/convert-lat-long-to-octant')(utils);

/***************************** main *****************************/

async function run() {
	let [lat, lon] = [process.argv[2], process.argv[3]];


	if ([lat, lon].includes(undefined)) {

//New York
	let lat0=40.785429;
	let lon0=73.837601;
	let lat1=40.569668;
	let lon1=74.192954;

//LA
//	let lat0=34.081049;
//	let lon0=118.143811;
//	let lat1=34.013811;
//	let lon1=118.258214;

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
			middle_lon=middle_lon;
            lat = middle_lat;
            lon = middle_lon;
        } else {
            console.log('Not found: ' + lat + ',' + lon);
        }
        var num_lats=0.0;
        var num_lons=0.0;
        if (size_lat>0) num_lats=(lat0-lat1)/size_lat+1;
        if (size_lon>0) num_lons=(lon1-lon0)/size_lon+1;
		num_lats = Math.round(num_lats);
		num_lons = Math.round(num_lons);

        var line = '';
        var prev_line = '';
//		console.log("(" + num_lons.toString().padStart(3, ' ') +","+num_lats.toString().padStart(3, ' ')+") (           NORTH,           WEST,           SOUTH,           EAST) (OCTANT(S)        )");

//		console.log("(  X,  Y) (           NORTH,           WEST,           SOUTH,           EAST) (OCTANT(S)        )");
//		console.log("-------------------------------------------------------------------------------------------------");

        var lat_count=0;
        console.log('static std::string *octants['+num_lats+'];');
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

        for (let lat=middle_lat; lat<lat0; lat=lat+size_lat) {
            var ok;
            var row = '';
            var row_cc = '{';
            var sub_line = '';
            var prev_level = '';
            var lon_count=0;
            let set=0;
            for (let lon=-middle_lon; lon<lon1; lon=lon+size_lon) {
                [lat, lon] = [parseFloat(lat), parseFloat(lon)];
                let foundOctants = await latLongToOctant(lat, -lon, MAX_LEVEL);
                for (let octantLevel in foundOctants) {
                    let octants = foundOctants[octantLevel].octants;
                    let box = foundOctants[octantLevel].box;
                    let set_sub=0;
                    if ( octantLevel === '17' ) {
                        ok=0;
                        let line_start= "["+lat_count.toString().padStart(3, ' ')+"]["+lon_count.toString().padStart(3, ' ')+"] (" + box.n.toFixed(13) + "," + box.w.toFixed(13) + "," + box.s.toFixed(13) + "," + box.e.toFixed(13) + ")";
//                        let line_start= "("+lon_count.toString().padStart(3, ' ')+","+lat_count.toString().padStart(3, ' ')+") (" + box.n.toFixed(13) + "," + box.w.toFixed(13) + "," + box.s.toFixed(13) + "," + box.e.toFixed(13) + ")";
                        let line_end="";
//                        let set=0;
                        for (let i = 0; i < octants.length; i++) {
                            ok=1;
                        }
                        if (set_sub===1) row=row+' ';
                        if (set===1) row_cc=row_cc+',';
                        set_sub=1;
                        row=row+line_end+' ';




//columns
						indexedOctants[numberOffoundOctants]=line_end;
						middle_lats[numberOffoundOctants] = lat;
						middle_lons[numberOffoundOctants] = lon;
						

//la
//						fy=middle_lat -lat0 -      1.561 *  (lat_number*size_lat *48.5/1.561  - 1.0);
//						fx=middle_lon -lon1  - 1.6 * (lon_number*size_lon *1.5/1.6   - 1.0);


						fx=((lon)-(lon1+lon0)/2.0); 
						fy=((lat)-(lat0+lat1)/2.0);

                                                                                        
                                                                                        
						f=Math.sqrt(fx*fx+fy*fy);                                      
                                                                                       
                                                                                       
						out[index]=f;                                                  
						out_x[index]=lon_count;                                       
						out_y[index]=lat_count;                                       
						out_index[index]=index;                                        


//						fx=(lon1+lon0)/2.0 - lon - (lon1-lon0);


//						fx=lon -2.0*middle_lon + (lon1+lon0)/2.0;

//						fy=lat -0.0*middle_lat - (lat0+lat1)/2.0;

//						console.log( "fx=" + fx + " fy=" + fy + " "+f);

						console.log("[#"+index.toFixed(0)+"]"+
							 "["+lon_count.toFixed(0)+
							 "/"+num_lons.toFixed(0)+"]"+
							 "["+lat_count.toFixed(0)+
							 "/"+num_lats.toFixed(0)+"]="+
							 indexedOctants[numberOffoundOctants]+
							 " lat="+(middle_lats[numberOffoundOctants]).toFixed(6)+
							 " lon="+(middle_lons[numberOffoundOctants]).toFixed(6)+
							 " fy=" + (Math.round(fy*1000000)/1000000).toString().padStart(4, ' ')+
							 " fx=" + (Math.round(fx*1000000)/1000000).toString().padStart(4, ' ')+
							 " f=" + (Math.round(f*1000000)/1000000).toString().padStart(8, ' ') );

						numberOffoundOctants++;

                        row_cc=row_cc+"\""+line_end+"\""
//                        console.log(line_start+" ("+line_end+")" );
                        size_lat=(box.n-box.s);
                        size_lon=(box.e-box.w);
						middle_lat=(box.n+box.s)/2.0;
						middle_lon=-(box.e+box.w)/2.0;
						num_lats=Math.round((lat0-lat1)/size_lat);
						num_lons=Math.round((lon1-lon0)/size_lon);

						index=index+1;

//columns
//                        console.log(line_end+'-21');

                        row_cc=row_cc+"\""+line_end+"\""
//                        console.log(line_start+" ("+line_end+")" );
                        size_lat=(box.n-box.s);
                        size_lon=(box.e-box.w);
                    }
                }
                set=1;
                if (prev_level!=row) sub_line=sub_line+row;
                prev_level=row;
                if (ok === 0) {
                    console.log('Not found:' + lat + ',' + lon);
                }
                lon_count++;
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
        }
    //	console.log( 'total: ' + line );


		var fi=0;
		var ok=0;
//		index=(num_lats)*(num_lons);
//		for (let i=0; i<index; i++) {
//			out_index[i] = i;
//		}
		while (ok===0) {
			ok=1;
			for (let i=0; i<index-1; i++) {
				if (out[i+1]<out[i]) {
					ok=0;
					let tussen=indexedOctants[i];
					indexedOctants[i]=indexedOctants[i+1];
					indexedOctants[i+1]=tussen;

					let tussen_x=out_x[i];
					out_x[i]=out_x[i+1];
					out_x[i+1]=tussen_x;

					let tussen_out_index=out_index[i];
					out_index[i]=out_index[i+1];
					out_index[i+1]=tussen_out_index;

					let tussen_y=out_y[i];
					out_y[i]=out_y[i+1];
					out_y[i+1]=tussen_y;

					let tussen_out=out[i];
					out[i]=out[i+1];
					out[i+1]=tussen_out;

					let tussen_middle_lats=middle_lats[i];
					middle_lats[i]=middle_lats[i+1];
					middle_lats[i+1]=tussen_middle_lats;

					let tussen_middle_lons=middle_lons[i];
					middle_lons[i]=middle_lons[i+1];
					middle_lons[i+1]=tussen_middle_lons;
				}
			}
		}

		for (let i=0; i<index; i++) {
			console.log( i.toString().padStart(5, ' ')+
				"<-"+out_index[i].toString().padStart(5, ' ')+
				"["+out_x[i].toString().padStart(5, ' ')+"/"+num_lons.toString().padStart(5, ' ')+"]="+
				" ["+out_y[i].toString().padStart(5, ' ')+"/"+num_lats.toString().padStart(5, ' ')+"]"+
				indexedOctants[i]+
				" lat="+middle_lats[i].toString().padStart(8, ' ')+
				" lon="+middle_lons[i].toString().padStart(8, ' ')+
				" dlat="+ (Math.round((middle_lats[i] +0.0*middle_lat - (lat0+lat1)/2.0)*1000000)/1000000).toString().padStart(8, ' ') +
				" dlon="+ (Math.round((middle_lons[i] -2.0*middle_lon + (lon1+lon0)/2.0)*1000000)/1000000).toString().padStart(8, ' ') +
				" f=" + (Math.round(out[i]*1000000)).toString().padStart(8, ' ') );				 

//						fx=lon -2.0*middle_lon + (lon1+lon0)/2.0;
//						fy=lat +0.0*middle_lat - (lat0+lat1)/2.0;
//							 " fx=" + (Math.round(fx*1000000)/1000000).toString().padStart(8, ' ')+
//							 " fy=" + (Math.round(fy*1000000)/1000000).toString().padStart(8, ' ')+


	
		}
		for (let i=0; i<index; i++) {
			console.log(
				"node dump_obj_center.js "+indexedOctants[i]+" 21 --parallel-search");
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
