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

async function doScreen() {  
	process.stdout.write("\u001b[2J\u001b[0;0H");
}  


async function run() {
//	let [lat, lon] = [process.argv[2], process.argv[3]];

	let CITY=process.argv[2];
	let NO_EXTRA=0;
//	if ([lat, lon].includes(undefined) || lat=="--ENSCHEDE" || lat=="--LA" || lat=="--AMSTERDAM" || lat=="--NEWYORK" || lat=="--MAIMI" || lat=="--BRUSSEL") {
	if (CITY=="--ENSCHEDE" || CITY=="--LA" || CITY=="--AMSTERDAM" || CITY=="--NEWYORK" || CITY=="--MIAMI" || CITY=="--BRUSSEL") {
		let CITY_NAME="";
		let lat0=0.0;
		let lon0=0.0;
		let lat1=0.0;
		let lon1=0.0;
		if (CITY=="--ENSCHEDE") {
			CITY_NAME="ENSCHEDE"
			lat0=52.252913;
			lon0= 6.813080;
			lat1=52.178402;
			lon1= 6.974389;
		} else if (CITY=="--LA") {
			CITY_NAME="LA"
			lat0=34.081049;
			lon0= -118.258214;
			lat1=34.013811;
			lon1=-118.143811;
		} else if (CITY=="--MIAMI") {
			CITY_NAME="MIAMI"
			lat0=25.90;
			lon0= -80.30;
			lat1=25.67;
			lon1=-80.10;
		} else if (CITY=="--BRUSSEL") {
			CITY_NAME="BRUSSEL"
			lat0=50.921320;
			lon0= 4.223007;
			lat1=50.809327;
			lon1= 4.538091;
		} else if (CITY=="--NEWYORK") {
			CITY_NAME="NEWYORK"
			lat0=40.785429;
			lon0=-74.192954;
			lat1=40.569668;
			lon1=-73.837601;
		} else if (CITY=="--AMSTERDAM") {
			CITY_NAME="AMSTERDAM"
			NO_EXTRA=1;
			lat0=52.439745;
			lon0= 4.750032;
			lat1=52.286213;
			lon1= 5.032107;
		} else {
			console.log('Add area first....');
			process.exit(1);
		}

//Brussel

/*
	let CITY_NAME="BRUSSEL"
	let lat0=50.921320;
	let lon0= 4.223007;
	let lat1=50.809327;
	let lon1= 4.538091;
*/

//New York

/*
	let CITY_NAME="NEWYORK"
	let lat0=40.785429;
	let lon0=-74.192954;
	let lat1=40.569668;
	let lon1=-73.837601;
*/

//LA
/*
	let CITY_NAME="LA"
	let lat0=34.081049;
	let lon0= -118.258214;
	let lat1=34.013811;
	let lon1=-118.143811;
*/

//MIAMI

/*
	let CITY_NAME="MIAMI"
	let lat0=25.90;
	let lon0= -80.30;
	let lat1=25.67;
	let lon1=-80.10;
*/	


//Enschede larger
/*
	let CITY_NAME="ENSCHEDE"
	let lat0=52.252913;
	let lon0= 6.813080;
	let lat1=52.178402;
	let lon1= 6.974389;
*/

//Enschede
/*
	let CITY_NAME="ENSCHEDE"
	let lat0=52.247224;
	let lon0= 6.841952;
	let lat1=52.191311;
	let lon1= 6.943110;
*/

//Amsterdam
/*
	let CITY_NAME="AMSTERDAM"
        let lat0=52.439745;
        let lon0= 4.750032;
        let lat1=52.286213;
        let lon1= 5.032107;
*/

//Jocelyn
/*
	let CITY_NAME="JOCELYN"
        let lat0=20.020408;
        let lon0= 120.792236;
        let lat1=14.895820;
        let lon1= 120.977658;
*/		

        let [lat, lon] = [lat1, lon0];
        [lat, lon] = [parseFloat(lat), parseFloat(lon)];

        let init_foundOctants = await latLongToOctant(lat, lon, MAX_LEVEL);
        var match=0;
        for (let octantLevel in init_foundOctants) {
            if (octantLevel === '17') match=1;
        }

        var size_lat=0.0; var size_lon=0.0;
        var middle_lat=0.0; var middle_lon=0.0;
        var from_lat=0.0; var from_lon=0.0;
        var to_lat=0.0; var to_lon=0.0;

        if (match === 1) {
            let init_octants = init_foundOctants[17].octants;
            let init_box = init_foundOctants[17].box;
            from_lat=init_box.n; to_lat=init_box.s;
            from_lon=init_box.w; to_lon=init_box.e;
            middle_lat=(init_box.n+init_box.s)/2.0;
            middle_lon=(init_box.e+init_box.w)/2.0;
            size_lat=(init_box.n-init_box.s);
            size_lon=(init_box.e-init_box.w);
            lat = middle_lat;
            lon = middle_lon;
        } else {
            console.log('Not found: ' + lat + ',' + lon);
        }
		var fx,fy,f,x,y;
		var out_cplusplus = [];
		var out_cplusplus_lat_lon = [];
		let out_x = {}
		let out_y = {}
		let out = {}
		let out_index = {}
		let index=0;
		let indexedOctants = {}
		let indexedOctants_extra = {}
		let middle_lons = {}
		let middle_lats = {}
		let out_box = {}
		let numberOffoundOctants = 0;
		let numberOffoundOctants_extra = 0;
        let set_extra=0;
        var num_lats=0.0;
        var num_lons=0.0;
        if (size_lat>0) num_lats=(lat0-lat1)/size_lat+1;
        if (size_lon>0) num_lons=(lon1-lon0)/size_lon+1;
		num_lats = Math.round(num_lats);
		num_lons = Math.round(num_lons);
        var line = '';
        var prev_line = '';
        var row_cc_extra = '{';
		lon=from_lon+size_lon/2.0;
		for (let lon_count=0; lon_count<num_lons; lon_count++) {
            var ok;
//            var row = '';
            var row_cc = '{';
            var row_cc_lat_lon = '{';
            var sub_line = '';
            var prev_level = '';
            let set=0;
			lat=from_lat+size_lat/2.0;
			for (let lat_count=0; lat_count<num_lats; lat_count++) {
                [lat, lon] = [parseFloat(lat), parseFloat(lon)];
                let foundOctants = await latLongToOctant(lat, lon, MAX_LEVEL);
                for (let octantLevel in foundOctants) {
                    let octants = foundOctants[octantLevel].octants;
                    let box = foundOctants[octantLevel].box;
                    if ( octantLevel === '17' ) {
                        ok=0;
                        let line_start= "["+lat_count.toString().padStart(3, ' ')+"]["+lon_count.toString().padStart(3, ' ')+"] (" + box.n.toFixed(13) + "," + box.w.toFixed(13) + "," + box.s.toFixed(13) + "," + box.e.toFixed(13) + ")";
                        let line_end="";
                        let line_end2="";
                        for (let i = 0; i < octants.length; i++) {
                            ok=1;
                            if (i===octants.length-1) {
								line_end=octants[i];
								if (set===1) {
									row_cc=row_cc+',';
									row_cc_lat_lon=row_cc_lat_lon+',';
								}
								set = 1;
								indexedOctants[numberOffoundOctants]=line_end;
								middle_lats[numberOffoundOctants] = lat;
								middle_lons[numberOffoundOctants] = lon;
								out_index[numberOffoundOctants]=numberOffoundOctants;
								out_x[numberOffoundOctants]=lon_count;
								out_y[numberOffoundOctants]=lat_count;
								fx=(lon-  (lon1+lon0)/2.0);
								fy=(lat-  (lat0+lat1)/2.0)*2.0;

								if (fx*fx<fy*fy) out[numberOffoundOctants]=fx;					//quadratic around center (block)
								else out[numberOffoundOctants]=fy;
//
								f=Math.sqrt(fx*fx+fy*fy);						//circle around center (round)
//								out[numberOffoundOctants]=f;

								console.log("["+numberOffoundOctants.toString().padStart(5, ' ')+"]"+
									 "["+lon_count.toString().padStart(3, ' ')+"]"+
									 "["+lat_count.toString().padStart(3, ' ')+"]="+
									 indexedOctants[numberOffoundOctants]+line_end2+
									 " lat="+box.n.toString()+	" to "+box.s.toString()+
									 " lon="+box.w.toString()+	" to "+box.e.toString()
								);

								numberOffoundOctants++;
								row_cc=row_cc+"\""+line_end+"\""
								row_cc_lat_lon=row_cc_lat_lon+"\""+"N="+box.n+" S="+box.s+" W="+box.w+" E="+box.e+"\""
								size_lat=(box.n-box.s);
								size_lon=(box.e-box.w);
								middle_lat=(box.n+box.s)/2.0;
								middle_lon=(box.e+box.w)/2.0;
								num_lats=Math.round((lat0-lat1)/size_lat);
								num_lons=Math.round((lon1-lon0)/size_lon);
							} else {
								console.log("[EXTRA]"+
									 "["+num_lats.toString().padStart(3, ' ')+"]"+
									 "["+numberOffoundOctants_extra.toString().padStart(3, ' ')+"]="+
									 octants[i]+
									 " lat="+box.n.toString()+	" to "+box.s.toString()+
									 " lon="+box.w.toString()+	" to "+box.e.toString()
								);

								line_end2=line_end2+','+octants[i];
								indexedOctants_extra[numberOffoundOctants_extra]=octants[i];
								numberOffoundOctants_extra++;
								if (set_extra===1) row_cc_extra=row_cc_extra+',';
								row_cc_extra=row_cc_extra+"\""+octants[i]+"\""
								set_extra = 1;
							}
                        }
                    }
                }
                set=1;
                if (ok === 0) {
                    console.log('Not found:' + lat + ',' + lon);
                }
				lat=lat+size_lat;
            }
            row_cc=row_cc+"};";
			row_cc='octants['+lon_count+']=new std::string['+num_lats+'] '+row_cc;
			out_cplusplus.push(row_cc);
            row_cc_lat_lon=row_cc_lat_lon+"};";
			row_cc_lat_lon='lat_lon['+lon_count+']=new std::string['+num_lats+'] '+row_cc_lat_lon;
			out_cplusplus_lat_lon.push(row_cc_lat_lon);
			lon=lon+size_lon
        }
		ok=0;
		while (ok===0) {
			ok=1;
			for (let i=0; i<numberOffoundOctants-1; i++) {
//				out_index[i]
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
		if (NO_EXTRA>0) numberOffoundOctants_extra=0;
/*
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
*/		
		console.log('std::string get_octant_'+CITY_NAME+'(int &x, int &y) {');
		if (numberOffoundOctants_extra>0) {
			console.log('	static std::string *octants['+(num_lons+1)+'];');
		} else {
			console.log('	static std::string *octants['+(num_lons)+'];');
		}
		console.log('	static std::string *lat_lon['+(num_lons)+'];');
		console.log('	static int first_do=1;');
		console.log('	if (x<0 || y<0) {');
        console.log('		x='+num_lons+';y='+num_lats+';');
		console.log('		extra_octants='+(numberOffoundOctants_extra)+';');
        console.log('		return "";');
		console.log('	}');
		console.log('	bool OK=false;');
		if (numberOffoundOctants_extra>0) {
			console.log('	if (x=='+(num_lons)+' && y>'+(numberOffoundOctants_extra-1)+') printf("Out of bound: %s X=%d Y=%d\\n",area.c_str(),x,y);');
			console.log('	else if (!(x=='+(num_lons)+') && (x>'+(num_lons)+' || y>'+(num_lats-1)+')) printf("Out of bound: %s X=%d Y=%d\\n",area.c_str(),x,y);');
			console.log('	else OK=true;');
		} else {
			console.log('	if (x>'+(num_lons-1)+' || y>'+(num_lats-1)+') printf("Out of bound: %s X=%d Y=%d\\n",area.c_str(),x,y);');
			console.log('	else OK=true;');
		}
		console.log('	if (!OK) return "";');
		console.log('	if  (first_do==1) {');
        console.log('		first_do=0;');


		for (let i=0; i<num_lons; i++) {
			console.log('		'+out_cplusplus[i]);
		}
		if (numberOffoundOctants_extra>0) {
            row_cc_extra=row_cc_extra+"};";
			row_cc_extra='		octants['+num_lons+']=new std::string['+numberOffoundOctants_extra+'] '+row_cc_extra;
			console.log(row_cc_extra);
		}
		for (let i=0; i<num_lons; i++) {
			console.log('		'+out_cplusplus_lat_lon[i]);
		}
		console.log('	}');

		if (numberOffoundOctants_extra>0) {
			console.log('	if (!(x=='+(num_lons)+')) latitude_longditude=lat_lon[x][y];');
			console.log('	else latitude_longditude="";');
		} else {
			console.log('	latitude_longditude=lat_lon[x][y];');
		}
		console.log('	std::string subdir=octants[x][y].substr(0,14)+"/";');

		console.log('	return_root = std::string()+EARTH_ROOT1+"/'+CITY_NAME+'/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT2+"/'+CITY_NAME+'/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT3+"/'+CITY_NAME+'/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');

		console.log('	return_root = std::string()+EARTH_ROOT1+"/'+CITY_NAME+'/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT2+"/'+CITY_NAME+'/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT3+"/'+CITY_NAME+'/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');

		console.log('	return_root = std::string()+EARTH_ROOT1+"/'+CITY_NAME+'/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT2+"/'+CITY_NAME+'/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT3+"/'+CITY_NAME+'/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');

		console.log('	return_root = std::string()+EARTH_ROOT1+"/'+CITY_NAME+'/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT2+"/'+CITY_NAME+'/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT3+"/'+CITY_NAME+'/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');

		console.log('	return_root = std::string()+EARTH_ROOT1+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT2+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT3+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;');

		console.log('	return_root = std::string()+EARTH_ROOT1+"/'+CITY_NAME+'/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT2+"/'+CITY_NAME+'/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT3+"/'+CITY_NAME+'/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');

		console.log('	return_root = std::string()+EARTH_ROOT1+"/'+CITY_NAME+'/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT2+"/'+CITY_NAME+'/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT3+"/'+CITY_NAME+'/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');

		console.log('	return_root = std::string()+EARTH_ROOT1+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT2+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');
		console.log('	return_root = std::string()+EARTH_ROOT3+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;');

		console.log('	printf("Directory not found on search paths: %s-21\\n",octants[x][y].c_str());');
		console.log('	return "";');
		console.log('}');

		var fmin=99999999999.9;
		var fmax=0.0;
		for (let i=0; i<numberOffoundOctants; i++) {
			console.log(
				"node DUMP_OBJ_CITY.js "+indexedOctants[i]+" 21 --parallel-search "+"--"+CITY_NAME);
			if (out[i]<fmin) fmin=out[i];
			if (out[i]>fmax) fmax=out[i];
		}
		console.log('REM EXTRA:');
		for (let i=0; i<numberOffoundOctants_extra; i++) {
			console.log(
				"node DUMP_OBJ_CITY.js "+indexedOctants_extra[i]+" 21 --parallel-search "+"--"+CITY_NAME);
		}

/*
		console.log("fmin="+Math.round((fmin)*1000000).toString().padStart(8, ' ')+"  "+
					"fmax="+Math.round((fmax)*1000000).toString().padStart(8, ' '))
*/					
					
/*
		var str1='';
		var str2='';
		for (let y=0; y<num_lats; y++) {
			for (let x=0; x<num_lons; x++) {
				let i=x+y*num_lons;
				str1=str1+(i).toString().padStart(5, ' ');
				str2=str2+(out_index[i]).toString().padStart(5, ' ');
			}
			console.log(str1); str1='';
			console.log(str2); str2='';
			console.log("");
		}
*/

/*
		clearScreen();
					
		for (let y=0; y<num_lats; y++) {
			for (let x=0; x<num_lons; x++) {
				let i=x+y*num_lons;
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

*/


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
