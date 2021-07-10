"use strict"

const fs = require('fs-extra');
const path = require('path');
const decodeTexture = require('./lib/decode-texture');

/**************************** config ****************************/
const PLANET = 'earth';
const URL_PREFIX = `https://kh.google.com/rt/${PLANET}/`;

//Keep an eye on the directory paths because they might change during git push...

const DL_DIR = './downloaded_files';
const [ DUMP_NEW_NEW_DIR,	DUMP_NEW_DIR,		DUMP_NEW_DIR_UTRECHT,	DUMP_NEW_DIR_RIO,		DUMP_NEW_DIR_MIAMI,		DUMP_NEW_DIR_AZORES,		DUMP_NEW_DIR_DENHAAG,		DUMP_NEW_DIR_SCHWEIZ,		DUMP_NEW_DIR_NEWYORK,		DUMP_NEW_DIR_BRUSSEL,		DUMP_NEW_DIR_ENSCHEDE,		DUMP_NEW_DIR_LA,		DUMP_NEW_DIR_AMSTERDAM,		DUMP_OBJ_DIR,		DUMP_JSON_DIR,		DUMP_RAW_DIR	] =
	  [	'new/new',			'new',			  	'new/Utrecht',			'new/Rio',				'new/Miami',			'new/Azores',				'new/DenHaag',				'new/Schweiz',				'new/NewYork',	  			'new/Brussel',	  			'new/Enschede',	  			'new/LA',				'new/Amsterdam',			'obj',				'json',				'raw' 		  	].map(x => path.join(DL_DIR, x));
                                                                        
const DL_DIR1 = 'D:/PACMAN/EARTH/downloaded_files';                     
const [ DUMP_NEW_NEW_DIR1,	DUMP_NEW_DIR1,		DUMP_NEW_DIR_UTRECHT1,	DUMP_NEW_DIR_RIO1,		DUMP_NEW_DIR_MIAMI1,	DUMP_NEW_DIR_AZORES1,		DUMP_NEW_DIR_DENHAAG1,		DUMP_NEW_DIR_SCHWEIZ1,		DUMP_NEW_DIR_NEWYORK1,		DUMP_NEW_DIR_BRUSSEL1,		DUMP_NEW_DIR_ENSCHEDE1,		DUMP_NEW_DIR_LA1,		DUMP_NEW_DIR_AMSTERDAM1,	DUMP_OBJ_DIR1,		DUMP_JSON_DIR1,		DUMP_RAW_DIR1	] =
	  [	'new/new',			'new',			  	'new/Utrecht',			'new/Rio',				'new/Miami',			'new/Azores',				'new/DenHaag',				'new/Schweiz',				'new/NewYork',	  			'new/Brussel',	  			'new/Enschede',	  			'new/LA',				'new/Amsterdam',			'obj',				'json',				'raw' 		  	].map(x => path.join(DL_DIR1, x));
                                                                        
const DL_DIR2 = 'F:/PACMAN/EARTH/downloaded_files'; 
const [ DUMP_NEW_NEW_DIR2,	DUMP_NEW_DIR2,		DUMP_NEW_DIR_UTRECHT2,	DUMP_NEW_DIR_RIO2,		DUMP_NEW_DIR_MIAMI2,	DUMP_NEW_DIR_AZORES2,		DUMP_NEW_DIR_DENHAAG2,		DUMP_NEW_DIR_SCHWEIZ2,		DUMP_NEW_DIR_NEWYORK2,		DUMP_NEW_DIR_BRUSSEL2,		DUMP_NEW_DIR_ENSCHEDE2,		DUMP_NEW_DIR_LA2,		DUMP_NEW_DIR_AMSTERDAM2,	DUMP_OBJ_DIR2,		DUMP_JSON_DIR2,		DUMP_RAW_DIR2	] =
	  [	'new/new',			'new',			  	'new/Utrecht',			'new/Rio',				'new/Miami',			'new/Azores',				'new/DenHaag',				'new/Schweiz',				'new/NewYork',	  			'new/Brussel',	  			'new/Enschede',	  			'new/LA',				'new/Amsterdam',			'obj',				'json',				'raw' 		  	].map(x => path.join(DL_DIR2, x));
                                                                        
const DL_DIR3 = 'G:/PACMAN/EARTH/downloaded_files';
const [ DUMP_NEW_NEW_DIR3,	DUMP_NEW_DIR3,		DUMP_NEW_DIR_UTRECHT3,	DUMP_NEW_DIR_RIO3,		DUMP_NEW_DIR_MIAMI3,	DUMP_NEW_DIR_AZORES3,		DUMP_NEW_DIR_DENHAAG3,		DUMP_NEW_DIR_SCHWEIZ3,		DUMP_NEW_DIR_NEWYORK3,		DUMP_NEW_DIR_BRUSSEL3,		DUMP_NEW_DIR_ENSCHEDE3,		DUMP_NEW_DIR_LA3,		DUMP_NEW_DIR_AMSTERDAM3,	DUMP_OBJ_DIR3,		DUMP_JSON_DIR3,		DUMP_RAW_DIR3	] =
	  [	'new/new',			'new',			  	'new/Utrecht',			'new/Rio',				'new/Miami',			'new/Azores',				'new/DenHaag',				'new/Schweiz',				'new/NewYork',	  			'new/Brussel',	  			'new/Enschede',	  			'new/LA',				'new/Amsterdam',			'obj',				'json',				'raw' 		  	].map(x => path.join(DL_DIR3, x));

const { OCTANTS, MAX_LEVEL, CITYNAME, DUMP_JSON, DUMP_RAW, PARALLEL_SEARCH } = require('./lib/parse-command-line2')(__filename);
const DUMP_OBJ = !(DUMP_JSON || DUMP_RAW);
/****************************************************************/

const { getPlanetoid, getBulk, getNode, bulk: { getIndexByPath, hasBulkMetadataAtIndex, hasNodeAtIndex } } = require('./lib/utils')({
	URL_PREFIX, DUMP_JSON_DIR, DUMP_RAW_DIR, DUMP_JSON, DUMP_RAW
});

/***************************** main *****************************/
async function pathExists (pad) {
  return fs.access(pad).then(() => 1).catch(() => 0)
}

var offset_x=0.0;
var offset_y=0.0;
var offset_z=0.0;

var max_x_x=0.0; var max_x_y=0.0; var max_x_z=0.0; 
var max_y_x=0.0; var max_y_y=0.0; var max_y_z=0.0; 
var max_z_x=0.0; var max_z_y=0.0; var max_z_z=0.0; 
var min_x_x=0.0; var min_x_y=0.0; var min_x_z=0.0; 
var min_y_x=0.0; var min_y_y=0.0; var min_y_z=0.0; 
var min_z_x=0.0; var min_z_y=0.0; var min_z_z=0.0; 

let num_vertices=0;
let num_objects=0;
let num_normals=0;
let num_faces=0;
let num_materials=0;
 
async function run() {
//	console.log(CITYNAME[0]);

	const subdir			= `${OCTANTS}`.substr(0,14);
	const newDir  			= path.join(DUMP_NEW_DIR, 				`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newnewDir  		= path.join(DUMP_NEW_NEW_DIR, 			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AMSTERDAM  = path.join(DUMP_NEW_DIR_AMSTERDAM,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_RIO  		= path.join(DUMP_NEW_DIR_RIO,			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_UTRECHT	= path.join(DUMP_NEW_DIR_UTRECHT,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_BRUSSEL 	= path.join(DUMP_NEW_DIR_BRUSSEL, 		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_ENSCHEDE	= path.join(DUMP_NEW_DIR_ENSCHEDE,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_LA			= path.join(DUMP_NEW_DIR_LA, 			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_NEWYORK	= path.join(DUMP_NEW_DIR_NEWYORK,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_MIAMI 		= path.join(DUMP_NEW_DIR_MIAMI,			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_DENHAAG 	= path.join(DUMP_NEW_DIR_DENHAAG,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_SCHWEIZ	= path.join(DUMP_NEW_DIR_SCHWEIZ,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AZORES		= path.join(DUMP_NEW_DIR_AZORES,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const objDir			= path.join(DUMP_OBJ_DIR,				`${OCTANTS.join('+')}-${MAX_LEVEL}`);

	const newDir_RIOb 		= path.join(DUMP_NEW_DIR_RIO,			`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AMSTERDAMb = path.join(DUMP_NEW_DIR_AMSTERDAM,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_UTRECHTb 	= path.join(DUMP_NEW_DIR_UTRECHT,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_BRUSSELb 	= path.join(DUMP_NEW_DIR_BRUSSEL, 		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_ENSCHEDEb	= path.join(DUMP_NEW_DIR_ENSCHEDE,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_LAb		= path.join(DUMP_NEW_DIR_LA, 			`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_NEWYORKb	= path.join(DUMP_NEW_DIR_NEWYORK,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_MIAMIb		= path.join(DUMP_NEW_DIR_MIAMI,			`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_DENHAAGb 	= path.join(DUMP_NEW_DIR_DENHAAG,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AZORESb 	= path.join(DUMP_NEW_DIR_AZORES,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_SCHWEIZb	= path.join(DUMP_NEW_DIR_SCHWEIZ,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);

	const newDir1  			= path.join(DUMP_NEW_DIR1, 				`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newnewDir1  		= path.join(DUMP_NEW_NEW_DIR1, 			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_BRUSSEL1 	= path.join(DUMP_NEW_DIR_BRUSSEL1, 		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_ENSCHEDE1	= path.join(DUMP_NEW_DIR_ENSCHEDE1,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_LA1		= path.join(DUMP_NEW_DIR_LA1, 			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AMSTERDAM1 = path.join(DUMP_NEW_DIR_AMSTERDAM1,	`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_RIO1 		= path.join(DUMP_NEW_DIR_RIO1,			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_UTRECHT1 	= path.join(DUMP_NEW_DIR_UTRECHT1,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_NEWYORK1	= path.join(DUMP_NEW_DIR_NEWYORK1,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_MIAMI1 	= path.join(DUMP_NEW_DIR_MIAMI1,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_DENHAAG1 	= path.join(DUMP_NEW_DIR_DENHAAG1,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_SCHWEIZ1	= path.join(DUMP_NEW_DIR_SCHWEIZ1,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AZORES1	= path.join(DUMP_NEW_DIR_AZORES1,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const objDir1			= path.join(DUMP_OBJ_DIR1,				`${OCTANTS.join('+')}-${MAX_LEVEL}`);

	const newDir_AMSTERDAMb1= path.join(DUMP_NEW_DIR_AMSTERDAM1,	`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_RIOb1		= path.join(DUMP_NEW_DIR_RIO1,			`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_UTRECHTb1	= path.join(DUMP_NEW_DIR_UTRECHT1,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_BRUSSELb1	= path.join(DUMP_NEW_DIR_BRUSSEL1, 		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_ENSCHEDEb1 = path.join(DUMP_NEW_DIR_ENSCHEDE1,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_LAb1		= path.join(DUMP_NEW_DIR_LA1, 			`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_NEWYORKb1	= path.join(DUMP_NEW_DIR_NEWYORK1,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_MIAMIb1	= path.join(DUMP_NEW_DIR_MIAMI1,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_DENHAAGb1 	= path.join(DUMP_NEW_DIR_DENHAAG1,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_SCHWEIZb1	= path.join(DUMP_NEW_DIR_SCHWEIZ1,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AZORESb1	= path.join(DUMP_NEW_DIR_AZORES1,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);

	const newDir2  			= path.join(DUMP_NEW_DIR2, 				`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newnewDir2  		= path.join(DUMP_NEW_NEW_DIR2, 			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_BRUSSEL2 	= path.join(DUMP_NEW_DIR_BRUSSEL2, 		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_ENSCHEDE2	= path.join(DUMP_NEW_DIR_ENSCHEDE2,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_LA2		= path.join(DUMP_NEW_DIR_LA2, 			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AMSTERDAM2 = path.join(DUMP_NEW_DIR_AMSTERDAM2,	`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_RIO2 		= path.join(DUMP_NEW_DIR_RIO2,			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_UTRECHT2 	= path.join(DUMP_NEW_DIR_UTRECHT2,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_NEWYORK2	= path.join(DUMP_NEW_DIR_NEWYORK2,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_MIAMI2 	= path.join(DUMP_NEW_DIR_MIAMI2,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_DENHAAG2 	= path.join(DUMP_NEW_DIR_DENHAAG2,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_SCHWEIZ2	= path.join(DUMP_NEW_DIR_SCHWEIZ2,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AZORES2	= path.join(DUMP_NEW_DIR_AZORES2,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const objDir2			= path.join(DUMP_OBJ_DIR2,				`${OCTANTS.join('+')}-${MAX_LEVEL}`);

	const newDir_AMSTERDAMb2= path.join(DUMP_NEW_DIR_AMSTERDAM2,	`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_RIOb2		= path.join(DUMP_NEW_DIR_RIO2,			`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_UTRECHTb2	= path.join(DUMP_NEW_DIR_UTRECHT2,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_BRUSSELb2	= path.join(DUMP_NEW_DIR_BRUSSEL2, 		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_ENSCHEDEb2 = path.join(DUMP_NEW_DIR_ENSCHEDE2,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_LAb2		= path.join(DUMP_NEW_DIR_LA2, 			`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_NEWYORKb2	= path.join(DUMP_NEW_DIR_NEWYORK2,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_MIAMIb2	= path.join(DUMP_NEW_DIR_MIAMI2,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_DENHAAGb2 	= path.join(DUMP_NEW_DIR_DENHAAG2,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_SCHWEIZb2	= path.join(DUMP_NEW_DIR_SCHWEIZ2,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AZORESb2	= path.join(DUMP_NEW_DIR_AZORES2,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);

	const newDir3  			= path.join(DUMP_NEW_DIR3, 				`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newnewDir3  		= path.join(DUMP_NEW_NEW_DIR3, 			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_BRUSSEL3 	= path.join(DUMP_NEW_DIR_BRUSSEL3, 		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_ENSCHEDE3	= path.join(DUMP_NEW_DIR_ENSCHEDE3,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_LA3		= path.join(DUMP_NEW_DIR_LA3, 			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AMSTERDAM3 = path.join(DUMP_NEW_DIR_AMSTERDAM3,	`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_RIO3 		= path.join(DUMP_NEW_DIR_RIO3,			`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_UTRECHT3 	= path.join(DUMP_NEW_DIR_UTRECHT3,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_NEWYORK3	= path.join(DUMP_NEW_DIR_NEWYORK3,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_MIAMI3 	= path.join(DUMP_NEW_DIR_MIAMI3,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_DENHAAG3 	= path.join(DUMP_NEW_DIR_DENHAAG3,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_SCHWEIZ3	= path.join(DUMP_NEW_DIR_SCHWEIZ3,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AZORES3	= path.join(DUMP_NEW_DIR_AZORES3,		`${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const objDir3			= path.join(DUMP_OBJ_DIR3,				`${OCTANTS.join('+')}-${MAX_LEVEL}`);

	const newDir_AMSTERDAMb3= path.join(DUMP_NEW_DIR_AMSTERDAM3,	`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_RIOb3		= path.join(DUMP_NEW_DIR_RIO3,			`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_UTRECHTb3	= path.join(DUMP_NEW_DIR_UTRECHT3,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_BRUSSELb3	= path.join(DUMP_NEW_DIR_BRUSSEL3, 		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_ENSCHEDEb3 = path.join(DUMP_NEW_DIR_ENSCHEDE3,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_LAb3		= path.join(DUMP_NEW_DIR_LA3, 			`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_NEWYORKb3	= path.join(DUMP_NEW_DIR_NEWYORK3,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_MIAMIb3	= path.join(DUMP_NEW_DIR_MIAMI3,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_DENHAAGb3 	= path.join(DUMP_NEW_DIR_DENHAAG3,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_SCHWEIZb3	= path.join(DUMP_NEW_DIR_SCHWEIZ3,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);
	const newDir_AZORESb3	= path.join(DUMP_NEW_DIR_AZORES3,		`${subdir}/${OCTANTS.join('+')}-${MAX_LEVEL}`);


	if (DUMP_OBJ) {
			 if (fs.existsSync(newDir) )			{	console.log('exists in: ' + newDir);			return;		}
		else if (fs.existsSync(newnewDir) ) 		{	console.log('exists in: ' + newnewDir);			return;		}
		else if (fs.existsSync(newDir_AMSTERDAM) ) 	{	console.log('exists in: ' + newDir_AMSTERDAM);	return;		}
		else if (fs.existsSync(newDir_RIO) )	 	{	console.log('exists in: ' + newDir_RIO);		return;		}
		else if (fs.existsSync(newDir_UTRECHT) ) 	{	console.log('exists in: ' + newDir_UTRECHT);	return;		}
		else if (fs.existsSync(newDir_BRUSSEL) ) 	{	console.log('exists in: ' + newDir_BRUSSEL);	return;		}
		else if (fs.existsSync(newDir_ENSCHEDE) ) 	{	console.log('exists in: ' + newDir_ENSCHEDE);	return;		}
		else if (fs.existsSync(newDir_LA) ) 		{	console.log('exists in: ' + newDir_LA);			return;		}
		else if (fs.existsSync(newDir_NEWYORK) ) 	{	console.log('exists in: ' + newDir_NEWYORK);	return;		}
		else if (fs.existsSync(newDir_MIAMI) ) 		{	console.log('exists in: ' + newDir_MIAMI);		return;		}
		else if (fs.existsSync(newDir_DENHAAG) ) 	{	console.log('exists in: ' + newDir_DENHAAG);	return;		}
		else if (fs.existsSync(newDir_SCHWEIZ) ) 	{	console.log('exists in: ' + newDir_SCHWEIZ);	return;		}
		else if (fs.existsSync(newDir_AZORES) ) 	{	console.log('exists in: ' + newDir_AZORES);		return;		}

		else if (fs.existsSync(objDir)) 			{	console.log('exists in: ' + objDir);			return;		}
		else if (fs.existsSync(newDir_AMSTERDAMb) )	{	console.log('exists in: ' + newDir_AMSTERDAMb);	return;		}
		else if (fs.existsSync(newDir_RIOb) )		{	console.log('exists in: ' + newDir_RIOb);		return;		}
		else if (fs.existsSync(newDir_UTRECHTb) )	{	console.log('exists in: ' + newDir_UTRECHTb);	return;		}
		else if (fs.existsSync(newDir_BRUSSELb) ) 	{	console.log('exists in: ' + newDir_BRUSSELb);	return;		}
		else if (fs.existsSync(newDir_ENSCHEDEb) ) 	{	console.log('exists in: ' + newDir_ENSCHEDEb);	return;		}
		else if (fs.existsSync(newDir_LAb) ) 		{	console.log('exists in: ' + newDir_LAb);		return;		}
		else if (fs.existsSync(newDir_NEWYORKb) ) 	{	console.log('exists in: ' + newDir_NEWYORKb);	return;		}
		else if (fs.existsSync(newDir_MIAMIb) ) 	{	console.log('exists in: ' + newDir_MIAMIb);	return;		}
		else if (fs.existsSync(newDir_DENHAAGb) ) 	{	console.log('exists in: ' + newDir_DENHAAGb);	return;		}
		else if (fs.existsSync(newDir_SCHWEIZb) ) 	{	console.log('exists in: ' + newDir_SCHWEIZb);	return;		}
		else if (fs.existsSync(newDir_AZORESb) ) 	{	console.log('exists in: ' + newDir_AZORESb);	return;		}
//		else 										{	console.log('not exist: ' + objDir);	}
//		else 										{	console.log('not exist: ' + DL_DIR);	}

			 if (fs.existsSync(newDir1) )			{	console.log('exists in: ' + newDir1);			return;		}
		else if (fs.existsSync(newnewDir1) ) 		{	console.log('exists in: ' + newnewDir1);		return;		}
		else if (fs.existsSync(newDir_BRUSSEL1) ) 	{	console.log('exists in: ' + newDir_BRUSSEL1);	return;		}
		else if (fs.existsSync(newDir_ENSCHEDE1) ) 	{	console.log('exists in: ' + newDir_ENSCHEDE1);	return;		}
		else if (fs.existsSync(newDir_LA1) ) 		{	console.log('exists in: ' + newDir_LA1);		return;		}
		else if (fs.existsSync(newDir_AMSTERDAM1) )	{	console.log('exists in: ' + newDir_AMSTERDAM1);	return;		}
		else if (fs.existsSync(newDir_RIO1) )		{	console.log('exists in: ' + newDir_RIO1);		return;		}
		else if (fs.existsSync(newDir_UTRECHT1) )	{	console.log('exists in: ' + newDir_UTRECHT1);	return;		}
		else if (fs.existsSync(newDir_NEWYORK1) ) 	{	console.log('exists in: ' + newDir_NEWYORK1);	return;		}
		else if (fs.existsSync(newDir_MIAMI1) ) 	{	console.log('exists in: ' + newDir_MIAMI1);		return;		}
		else if (fs.existsSync(newDir_DENHAAG1) ) 	{	console.log('exists in: ' + newDir_DENHAAG1);	return;		}
		else if (fs.existsSync(newDir_SCHWEIZ1) ) 	{	console.log('exists in: ' + newDir_SCHWEIZ1);	return;		}
		else if (fs.existsSync(newDir_AZORES1) ) 	{	console.log('exists in: ' + newDir_AZORES1);	return;		}
		else if (fs.existsSync(objDir1)) 			{	console.log('exists in: ' + objDir1);			return;		}
		
		else if (fs.existsSync(newDir_AMSTERDAMb1) ){	console.log('exists in: ' + newDir_AMSTERDAMb1);return;		}
		else if (fs.existsSync(newDir_RIOb1) )		{	console.log('exists in: ' + newDir_RIOb1);		return;		}
		else if (fs.existsSync(newDir_UTRECHTb1) )	{	console.log('exists in: ' + newDir_UTRECHTb1);	return;		}
		else if (fs.existsSync(newDir_BRUSSELb1) )	{	console.log('exists in: ' + newDir_BRUSSELb1);	return;		}
		else if (fs.existsSync(newDir_ENSCHEDEb1) ) {	console.log('exists in: ' + newDir_ENSCHEDEb1);	return;		}
		else if (fs.existsSync(newDir_LAb1) ) 		{	console.log('exists in: ' + newDir_LAb1);		return;		}
		else if (fs.existsSync(newDir_NEWYORKb1) ) 	{	console.log('exists in: ' + newDir_NEWYORKb1);	return;		}
		else if (fs.existsSync(newDir_MIAMIb1) ) 	{	console.log('exists in: ' + newDir_MIAMIb1);	return;		}
		else if (fs.existsSync(newDir_DENHAAGb1) ) 	{	console.log('exists in: ' + newDir_DENHAAGb1);	return;		}
		else if (fs.existsSync(newDir_SCHWEIZb1) ) 	{	console.log('exists in: ' + newDir_SCHWEIZb1);	return;		}
		else if (fs.existsSync(newDir_AZORESb1) ) 	{	console.log('exists in: ' + newDir_AZORESb1);	return;		}
//		else 										{	console.log('not exist: ' + objDir1);	}
//		else 										{	console.log('not exist: ' + DL_DIR1);	}

			 if (fs.existsSync(newDir2) )			{	console.log('exists in: ' + newDir2);			return;		}
		else if (fs.existsSync(newnewDir2) ) 		{	console.log('exists in: ' + newnewDir2);		return;		}
		else if (fs.existsSync(newDir_BRUSSEL2) ) 	{	console.log('exists in: ' + newDir_BRUSSEL2);	return;		}
		else if (fs.existsSync(newDir_ENSCHEDE2) ) 	{	console.log('exists in: ' + newDir_ENSCHEDE2);	return;		}
		else if (fs.existsSync(newDir_LA2) ) 		{	console.log('exists in: ' + newDir_LA2);		return;		}
		else if (fs.existsSync(newDir_AMSTERDAM2) )	{	console.log('exists in: ' + newDir_AMSTERDAM2);	return;		}
		else if (fs.existsSync(newDir_RIO2) )		{	console.log('exists in: ' + newDir_RIO2);		return;		}
		else if (fs.existsSync(newDir_UTRECHT2) )	{	console.log('exists in: ' + newDir_UTRECHT2);	return;		}
		else if (fs.existsSync(newDir_NEWYORK2) ) 	{	console.log('exists in: ' + newDir_NEWYORK2);	return;		}
		else if (fs.existsSync(newDir_MIAMI2) ) 	{	console.log('exists in: ' + newDir_MIAMI2);		return;		}
		else if (fs.existsSync(newDir_DENHAAG2) ) 	{	console.log('exists in: ' + newDir_DENHAAG2);	return;		}
		else if (fs.existsSync(newDir_SCHWEIZ2) ) 	{	console.log('exists in: ' + newDir_SCHWEIZ2);	return;		}
		else if (fs.existsSync(newDir_AZORES2) ) 	{	console.log('exists in: ' + newDir_AZORES2);	return;		}
		else if (fs.existsSync(objDir2)) 			{	console.log('exists in: ' + objDir2);			return;		}
		
		else if (fs.existsSync(newDir_AMSTERDAMb2) ){	console.log('exists in: ' + newDir_AMSTERDAMb2);return;		}
		else if (fs.existsSync(newDir_RIOb2) )		{	console.log('exists in: ' + newDir_RIOb2);		return;		}
		else if (fs.existsSync(newDir_UTRECHTb2) )	{	console.log('exists in: ' + newDir_UTRECHTb2);	return;		}
		else if (fs.existsSync(newDir_BRUSSELb2) )	{	console.log('exists in: ' + newDir_BRUSSELb2);	return;		}
		else if (fs.existsSync(newDir_ENSCHEDEb2) ) {	console.log('exists in: ' + newDir_ENSCHEDEb2);	return;		}
		else if (fs.existsSync(newDir_LAb2) ) 		{	console.log('exists in: ' + newDir_LAb2);		return;		}
		else if (fs.existsSync(newDir_NEWYORKb2) ) 	{	console.log('exists in: ' + newDir_NEWYORKb2);	return;		}
		else if (fs.existsSync(newDir_MIAMIb2) ) 	{	console.log('exists in: ' + newDir_MIAMIb2);	return;		}
		else if (fs.existsSync(newDir_DENHAAGb2) ) 	{	console.log('exists in: ' + newDir_DENHAAGb2);	return;		}
		else if (fs.existsSync(newDir_SCHWEIZb2) ) 	{	console.log('exists in: ' + newDir_SCHWEIZb2);	return;		}
		else if (fs.existsSync(newDir_AZORESb2) ) 	{	console.log('exists in: ' + newDir_AZORESb2);	return;		}
//		else 										{	console.log('not exist: ' + objDir2);	}
//		else 										{	console.log('not exist: ' + DL_DIR2);	}

			 if (fs.existsSync(newDir3) )			{	console.log('exists in: ' + newDir3);			return;		}
		else if (fs.existsSync(newnewDir3) ) 		{	console.log('exists in: ' + newnewDir3);		return;		}
		else if (fs.existsSync(newDir_BRUSSEL3) ) 	{	console.log('exists in: ' + newDir_BRUSSEL3);	return;		}
		else if (fs.existsSync(newDir_ENSCHEDE3) ) 	{	console.log('exists in: ' + newDir_ENSCHEDE3);	return;		}
		else if (fs.existsSync(newDir_LA3) ) 		{	console.log('exists in: ' + newDir_LA3);		return;		}
		else if (fs.existsSync(newDir_RIO3) )		{	console.log('exists in: ' + newDir_RIO3);		return;		}
		else if (fs.existsSync(newDir_AMSTERDAM3) )	{	console.log('exists in: ' + newDir_AMSTERDAM3);	return;		}
		else if (fs.existsSync(newDir_UTRECHT3) )	{	console.log('exists in: ' + newDir_UTRECHT3);	return;		}
		else if (fs.existsSync(newDir_NEWYORK3) ) 	{	console.log('exists in: ' + newDir_NEWYORK3);	return;		}
		else if (fs.existsSync(newDir_MIAMI3) ) 	{	console.log('exists in: ' + newDir_MIAMI3);		return;		}
		else if (fs.existsSync(newDir_DENHAAG3) ) 	{	console.log('exists in: ' + newDir_DENHAAG3);	return;		}
		else if (fs.existsSync(newDir_SCHWEIZ3) ) 	{	console.log('exists in: ' + newDir_SCHWEIZ3);	return;		}
		else if (fs.existsSync(newDir_AZORES3) ) 	{	console.log('exists in: ' + newDir_AZORES3);	return;		}
		else if (fs.existsSync(objDir3)) 			{	console.log('exists in: ' + objDir3);			return;		}
		
		else if (fs.existsSync(newDir_AMSTERDAMb3) ){	console.log('exists in: ' + newDir_AMSTERDAMb3);return;		}
		else if (fs.existsSync(newDir_RIOb3) )		{	console.log('exists in: ' + newDir_RIOb3);		return;		}
		else if (fs.existsSync(newDir_UTRECHTb3) )	{	console.log('exists in: ' + newDir_UTRECHTb3);	return;		}
		else if (fs.existsSync(newDir_BRUSSELb3) )	{	console.log('exists in: ' + newDir_BRUSSELb3);	return;		}
		else if (fs.existsSync(newDir_ENSCHEDEb3) ) {	console.log('exists in: ' + newDir_ENSCHEDEb3);	return;		}
		else if (fs.existsSync(newDir_LAb3) ) 		{	console.log('exists in: ' + newDir_LAb3);		return;		}
		else if (fs.existsSync(newDir_NEWYORKb3) ) 	{	console.log('exists in: ' + newDir_NEWYORKb3);	return;		}
		else if (fs.existsSync(newDir_MIAMIb3) ) 	{	console.log('exists in: ' + newDir_MIAMIb3);	return;		}
		else if (fs.existsSync(newDir_DENHAAGb3) ) 	{	console.log('exists in: ' + newDir_DENHAAGb3);	return;		}
		else if (fs.existsSync(newDir_SCHWEIZb3) ) 	{	console.log('exists in: ' + newDir_SCHWEIZb3);	return;		}
		else if (fs.existsSync(newDir_AZORESb3) ) 	{	console.log('exists in: ' + newDir_AZORESb3);	return;		}
//		else 										{	console.log('not exist: ' + objDir3);	}
//		else 										{	console.log('not exist: ' + DL_DIR3);	}
	}

	if (CITYNAME[0]=="--ENSCHEDE")			{	offset_x=3875099.0;					offset_y=468154.0;				offset_z=5035344.0; }
	else if (CITYNAME[0]=="--UTRECHT")		{	offset_x=3899275.0;					offset_y=348997.0;				offset_z=5026376.0; }
	else if (CITYNAME[0]=="--AMSTERDAM")	{	offset_x=3876534.0;					offset_y=331582.0;				offset_z=5045027.0; }
//planet_037062636161604273407_0 4279407.080373702 -4011609.541706613 -2486650.8940397883
	else if (CITYNAME[0]=="--RIO")			{	offset_x=4279407;					offset_y=-4011609;				offset_z=-2486650; }
	else if (CITYNAME[0]=="--BRUSSEL")		{	offset_x=4014897.0; 				offset_y=296156.0; 				offset_z=4937953.0; }
	else if (CITYNAME[0]=="--LA")			{	offset_x=-2490962;					offset_y=-4656517; 				offset_z=3564040; }
	else if (CITYNAME[0]=="--NEWYORK")		{	offset_x=1323854.370856056; 		offset_y=-4649129.837542839; 	offset_z=4150030.4071031474; } 
	else if (CITYNAME[0]=="--JOCELYN")		{	offset_x=-3151877; 					offset_y=5289017; 				offset_z=1637629; }
	else if (CITYNAME[0]=="--MIAMI")		{	offset_x=975859; 					offset_y=-5652918; 				offset_z=2771644; }
	else if (CITYNAME[0]=="--DENHAAG")		{	offset_x=3904479.2616487066; 		offset_y=294625.81305996777;	offset_z=5025795.962117693; }
	else if (CITYNAME[0]=="--SCHWEIZ")		{	offset_x=4386153.408482799; 		offset_y=576284.5001272303; 	offset_z=4587395.669652603; }
	else if (CITYNAME[0]=="--AZORES")		{	offset_x=4547134.555436776;	 		offset_y=-2165128.87501796;		offset_z=3903020.5406996952; }
 	else {
		console.log('NO OFFSET DATA!!! ');
		return false;
	}

	console.log("OFFSET X="+offset_x);
	console.log("OFFSET Y="+offset_y);
	console.log("OFFSET Z="+offset_z);

	const planetoid = await getPlanetoid();
	const rootEpoch = planetoid.bulkMetadataEpoch[0];

	max_x_x=-9999999999999999.9;
	max_y_y=-9999999999999999.9;
	max_z_z=-9999999999999999.9;
	min_x_x=9999999999999999.9;
	min_y_y=9999999999999999.9;
	min_z_z=9999999999999999.9;
	
	let data_file="";

	let objCtx;

	if (DUMP_OBJ) {
		fs.removeSync(objDir);
		fs.ensureDirSync(objDir);
		objCtx = initCtxOBJ(objDir);
	}

	let octants = 0;

	const search = initNodeSearch(rootEpoch, PARALLEL_SEARCH ? 8 : 1,
		function nodeFound(path) {
			console.log('found     ', path);
			octants++;
		},
		function nodeDownloaded(path, node, octantsToExclude) {
			console.log('downloaded', path);
			DUMP_OBJ && writeNodeOBJ(objCtx, node, path, octantsToExclude);
		}
	);

	for (const oct of OCTANTS) {
		await search(oct, MAX_LEVEL);
	}

	data_file=
	"MIN X: X="+min_x_x+" Y="+min_x_y+" Z="+min_x_z+"\n"+
	"MIN Y: X="+min_y_x+" Y="+min_y_y+" Z="+min_y_z+"\n"+
	"MIN Z: X="+min_z_x+" Y="+min_z_y+" Z="+min_z_z+"\n"+
	"MAX X: X="+max_x_x+" Y="+max_x_y+" Z="+max_x_z+"\n"+
	"MAX Y: X="+max_y_x+" Y="+max_y_y+" Z="+max_y_z+"\n"+
	"MAX Z: X="+max_z_x+" Y="+max_z_y+" Z="+max_z_z+"\n"+
	"VERTICES="+num_vertices+"\n"+
	"OBJECTS="+num_objects+"\n"+
	"NORMALS="+num_normals+"\n"+
	"FACES="+num_faces+"\n"+
	"MATERIALS="+num_materials+"\n";

	fs.writeFileSync(path.join(objCtx.objDir, OCTANTS+'.dat'), data_file);

	console.log('octants', octants)
}
/****************************************************************/

/**************************** search ****************************/
function initNodeSearch(rootEpoch, numParallelBranches = 1, nodeFound = null, nodeDownloaded = null) {
	const sem = semaphore(numParallelBranches - 1);

	return async function search(k, maxLevel = 999) {
		if (k.length > maxLevel) return false;

		let check;
		try {
			check = await checkNodeAtNodePath(rootEpoch, k);
			if (check === null) return false;
		} catch (ex) {
			console.error(ex);
			return false;
		}

		try {
			nodeFound && nodeFound(k);
		} catch (ex) {
			console.error('Unhandled nodeFound callback error', ex);
			return false;
		}

		const [promises, results] = [[], []];

		for (const oct of [0, 1, 2, 3, 4, 5, 6, 7]) {
			promises.push((async function fn() {
				try {
					results.push({ oct, res: await search(k + oct, maxLevel) });
					if (results.length === 8) {
						const octs = results.filter(({ res }) => res).map(({ oct }) => oct)
						const node = await getNode(k, check.bulk, check.index);
						try {
							nodeDownloaded && nodeDownloaded(k, node, octs);
						} catch (ex) {
							console.error('Unhandled nodeDownload callback error');
							throw ex;
						}
					}
				} finally {
					await new Promise((r, _) => setImmediate(r));
					sem.signal();
				}
			})());

			await sem.wait(true);
		}

		try {
			await Promise.all(promises);
		} catch (ex) {
			console.error(ex);
			return false;
		}
		return true;
	};
}

async function checkNodeAtNodePath(rootEpoch, nodePath) {
	let bulk = null, index = -1;
	for (let epoch = rootEpoch, i = 4; i < nodePath.length + 4; i += 4) {
		const bulkPath = nodePath.substring(0, i - 4);
		const subPath = nodePath.substring(0, i);

		if (bulk) {
			const idx = getIndexByPath(bulk, bulkPath);
			if (hasBulkMetadataAtIndex(bulk, idx)) return null;
		}

		const nextBulk = await getBulk(bulkPath, epoch);

		bulk = nextBulk;
		index = getIndexByPath(bulk, subPath);
		epoch = bulk.bulkMetadataEpoch[index];
	}
	if (index < 0) return null;
	if (!hasNodeAtIndex(bulk, index)) return null;
	return { bulk, index };
}
/****************************************************************/

/**************************** export ****************************/
function initCtxOBJ(dir) {
	fs.writeFileSync(path.join(dir, OCTANTS+'.obj'), 'mtllib ' + OCTANTS + '.mtl\n');
		console.log('found     ', dir);
	return { objDir: dir, c_v: 0, c_n: 0, c_u: 0 };
}

function writeNodeOBJ(ctx, node, nodeName, exclude) {
	
	for (const [meshIndex, mesh] of Object.entries(node.meshes)) {
		const meshName = `${nodeName}_${meshIndex}`;
		const tex = mesh.texture;
		const texName = `tex_${nodeName}_${meshIndex}`;

		const obj = writeMeshOBJ(ctx, meshName, texName, node, mesh, exclude);
		fs.appendFileSync(path.join(ctx.objDir, OCTANTS+'.obj'), obj);

		num_objects=num_objects+1;
		num_materials=num_materials+1;

		const { buffer: buf, extension: ext } = decodeTexture(tex);
		fs.appendFileSync(path.join(ctx.objDir, OCTANTS+'.mtl'), `
			newmtl ${texName}
			Ka 1.000000 1.000000 1.000000
			Kd 1.000000 1.000000 1.000000
			Ks 0.000000 0.000000 0.000000
			Tr 1.000000
			illum 1
			Ns 0.000000
			map_Kd ${texName}.${ext}
		`.split('\n').map(s => s.trim()).join('\n'));

		fs.writeFileSync(path.join(ctx.objDir, `${texName}.${ext}`), buf);
	}
}

function writeMeshOBJ(ctx, meshName, texName, payload, mesh, exclude) {

	function shouldExclude(w) {
		return (exclude instanceof Array)
			? exclude.indexOf(w) >= 0
			: false;
	}

	let str = "";
	const indices = mesh.indices;
	const vertices = mesh.vertices;
	const normals = mesh.normals;

	const _c_v = ctx.c_v;
	const _c_n = ctx.c_n;
	const _c_u = ctx.c_u;

	let c_v = _c_v;
	let c_n = _c_n;
	let c_u = _c_u;

	const console = { log: function (s) { str += s + "\n" } };

//	console.log(`usemtl ${texName}`);
	console.log(`o planet_${meshName}`);

	console.log("# vertices");
	let first = 1;
	for (let i = 0; i < vertices.length; i += 8) {
		num_vertices=num_vertices+1;

		let x = vertices[i + 0]
		let y = vertices[i + 1]
		let z = vertices[i + 2]
		let w = 1;

		let _x = 0;
		let _y = 0;
		let _z = 0;
		let _w = 0;

		const ma = payload.matrixGlobeFromMesh;
		_x = x * ma[0] + y * ma[4] + z * ma[8] + w * ma[12];
		_y = x * ma[1] + y * ma[5] + z * ma[9] + w * ma[13];
		_z = x * ma[2] + y * ma[6] + z * ma[10] + w * ma[14];
		_w = x * ma[3] + y * ma[7] + z * ma[11] + w * ma[15];

		x = _x;
		y = _y;
		z = _z;

		x =  ((x - offset_x) );
		y =  ((y - offset_y) );
		z =  ((z - offset_z) );
		
		if (x<min_x_x) { min_x_x=x; min_x_y=y; min_x_z=z; }
		if (x>max_x_x) { max_x_x=x; max_x_y=y; max_x_z=z; }
		if (y<min_y_y) { min_y_x=x; min_y_y=y; min_y_z=z; }
		if (y>max_y_y) { max_y_x=x; max_y_y=y; max_y_z=z; }
		if (z<min_z_z) { min_z_x=x; min_z_y=y; min_z_z=z; }
		if (z>max_z_z) { max_z_x=x; max_z_y=y; max_z_z=z; }

		console.log(`v ${x} ${y} ${z}`);

		c_v++;
	}

	if (mesh.uvOffsetAndScale) {
		console.log("# UV");
		for (let i = 0; i < vertices.length; i += 8) {
			const u1 = vertices[i + 4];
			const u2 = vertices[i + 5];
			const v1 = vertices[i + 6];
			const v2 = vertices[i + 7];

			const u = u2 * 256 + u1;
			const v = v2 * 256 + v1;

			let ut = (u + mesh.uvOffsetAndScale[0]) * mesh.uvOffsetAndScale[2];
			let vt = (v + mesh.uvOffsetAndScale[1]) * mesh.uvOffsetAndScale[3];

			const tex = mesh.texture;
			if (tex.textureFormat == 6) {
				vt = 1 - vt;
				console.log(`vt ${ut} ${vt}`)
			}
			else {
				console.log(`vt ${ut} ${vt}`)
			}
			c_u++;
		}
	}

	console.log("# Normals");
	for (let i = 0; i < normals.length; i += 4) {

		num_normals=num_normals+1;

		let x = normals[i + 0] - 127;
		let y = normals[i + 1] - 127;
		let z = normals[i + 2] - 127;
		let w = 0;

		let _x = 0;
		let _y = 0;
		let _z = 0;
		let _w = 0;

		const ma = payload.matrixGlobeFromMesh;
		_x = x * ma[0] + y * ma[4] + z * ma[8] + w * ma[12];
		_y = x * ma[1] + y * ma[5] + z * ma[9] + w * ma[13];
		_z = x * ma[2] + y * ma[6] + z * ma[10] + w * ma[14];
		_w = x * ma[3] + y * ma[7] + z * ma[11] + w * ma[15];

		x = _x;
		y = _y;
		z = _z;

		console.log(`vn ${x} ${y} ${z}`)
		c_n++;
	}
	console.log(`usemtl ${texName}`);

	console.log("# faces");

	const triangle_groups = {};
	for (let i = 0; i < indices.length - 2; i += 1) {
		num_faces=num_faces+1;
		if (i === mesh.layerBounds[3]) break;
		const a = indices[i + 0];
		const b = indices[i + 1];
		const c = indices[i + 2];
		if (a == b || a == c || b == c) {
			continue;
		}

		if (!(vertices[a * 8 + 3] === vertices[b * 8 + 3] && vertices[b * 8 + 3] === vertices[c * 8 + 3])) {
			throw new Error("vertex w mismatch");
		}
		const w = vertices[a * 8 + 3];

		if (shouldExclude(w)) continue;
		triangle_groups[w] = [].concat(triangle_groups[w] || [], [(i & 1) ? [a, c, b] : [a, b, c]]);
	}

	for (let k in triangle_groups) {
		if (!triangle_groups.hasOwnProperty(k)) throw new Error("no k property");
		const triangles = triangle_groups[k];

		for (let t in triangles) {
			if (!triangles.hasOwnProperty(t)) throw new Error("no t property");
			const v = triangles[t];
			const a = v[0] + 1, b = v[1] + 1, c = v[2] + 1;

			if (mesh.uvOffsetAndScale) {
				console.log(`f ${a + _c_v}/${a + _c_u}/${a + _c_n} ${b + _c_v}/${b + _c_u}/${b + _c_n} ${c + _c_v}/${c + _c_u}/${c + _c_n}`)
			} else {
				console.log(`f ${a + _c_v} ${b + _c_v} ${c + _c_v}`)
			}

		}
	}

	ctx.c_v = c_v;
	ctx.c_u = c_u;
	ctx.c_n = c_n;

	return str;
}
/****************************************************************/

/**************************** helper ****************************/
function semaphore(num) {
	let concurrent = num;
	const waiting = [];
	return {
		wait(highestPriority = false) {
			return new Promise((resolve, reject) => {
				if (concurrent <= 0) {
					if (highestPriority) {
						waiting.splice(0, 0, { resolve, reject });
					} else {
						waiting.push(({ resolve, reject }));
					}
				} else {
					concurrent--;
					resolve();
				}
			})
		},
		signal() {
			concurrent++;
			if (concurrent > 0) {
				if (waiting.length > 0) {
					concurrent--;
					waiting.splice(0, 1)[0].resolve();
				}
			}
		}
	};
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

