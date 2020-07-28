"use strict";

// centers and scales all *.obj and saves results as *.2.obj
// can also keep 3d viewers from jittering

const fs = require('fs');
const readline = require('readline');
const path = require('path');
const OBJ_DIR = './downloaded_files/new/NEWYORK';

let readyfreddy=0;
let n=0;

const SCALE = 10;
do_all();

async function do_all() {
	for (let i of fs.readdirSync(OBJ_DIR)) {
		i = path.resolve(OBJ_DIR, i);
		if (!fs.statSync(i).isDirectory()) continue;

		for (let j of fs.readdirSync(i)) {
			j = path.resolve(i, j);
			if (!/\.obj$/.test(j) || /\.2\.obj$/.test(j)) {
				if (/\.2\.obj$/.test(j)) {
					n = n + 1;
					console.error(n + ` skipping: ` + j);
				}
				continue;
			} else if (fs.statSync(j).isFile()) {
				let file_out = `${j.match(/(.*)\.obj$/)[1]}.2.obj`;
				if (!fs.existsSync(file_out)) {
					n = n + 1;
					readyfreddy = 0;
					console.error(n + ` converting: ` + j);
					scaleMoveObj(j, `${j.match(/(.*)\.obj$/)[1]}.2.obj`);
					while (readyfreddy === 0) {
//						console.error(` waiting for: ` + j);
						await sleep(100);
					}
					fs.unlinkSync(j);
//					console.log('File deleted!');
					fs.renameSync(file_out,j);
//					console.log('File Renamed.');
				}
			}
		}
	}
}

async function scaleMoveObj(file_in, file_out) {

	if (fs.existsSync(file_out)) {
		fs.unlinkSync(file_out);
	}

//	const io = readline.createInterface({
//		input: fs.createReadStream(file_in),
//		terminal: false,
//	});


//	let min_x = Infinity, max_x = -Infinity;
//	let min_y = Infinity, max_y = -Infinity;
//	let min_z = Infinity, max_z = -Infinity;

//	io.on('line', line => {
//		return;
//		if (!/^v /.test(line))
//			return;
//		let [x, y, z] = line.split(' ').slice(1).map(parseFloat);
//		min_x = Math.min(x, min_x);
//		min_y = Math.min(y, min_y);
//		min_z = Math.min(z, min_z);
//		max_x = Math.max(x, max_x);
//		max_y = Math.max(y, max_y);
//		max_z = Math.max(z, max_z);
//	}).on('close', () => {
//		const center_x = (max_x + min_x) / 2;
//		const center_y = (max_y + min_y) / 2;
//		const center_z = (max_z + min_z) / 2;
//		const distance_x = Math.abs(max_x - min_x);
//		const distance_y = Math.abs(max_y - min_y);
//		const distance_z = Math.abs(max_z - min_z);
//		const max_distance = Math.max(distance_x, distance_y, distance_z);

//		const enschede_x=center_x;
//		const enschede_y=center_y;
//		const enschede_z=center_z;


		const io = readline.createInterface({
			input: fs.createReadStream(file_in),
			output: fs.createWriteStream(file_out),
		});
		
//enschede		
//		const enschede_x=3875099.0;
//		const enschede_y=468154.0;
//		const enschede_z=5035344.0;
//amsterdam....		
//		const amsterdam_x=3876534.0
//		const amsterdam_y=331582.0
//		const amsterdam_z=5045027.0		
//restore error....		NEW YORK

//v 1132193.9487452654 179257.10415958147 -2380.442785577383


		const adapt_x=1132193.9487452654;
		const adapt_y=179257.10415958147;
		const adapt_z=-2380.442785577383;

		io.on('line', line => {
			if (/^v /.test(line)) {
				let [x, y, z] = line.split(' ').slice(1).map(parseFloat);
				x =  ((x - adapt_x));
				y =  ((y - adapt_y) );
				z =  ((z - adapt_z) );
//				x =  ((x - enschede_x));
//				y =  ((y - enschede_y) );
//				z =  ((z - enschede_z) );
//				x = Math.round( x * 1000000 )/1000000; // DON'T ROUND BUT ADAPT (SUBTRACT MIDDLE OF LOADED DATA) HERE OR WHEN READING IN .OBJ FILE (TO MUCH SIGN. NUMBERS GET LOST) BY SUBTRACTING AVERAGE MIDDLE POINT NUMBERS WILL GET SMALLER WITH LESS NUMBERS....
//				y = Math.round( y * 1000000 )/1000000;
//				z = Math.round( z * 1000000 )/1000000;
				io.output.write(`v ${x} ${y} ${z}\n`);
//			} else if (/^vt /.test(line)) {
//				let [x, y] = line.split(' ').slice(1).map(parseFloat);
//				x = Math.round( x * 1000000 )/1000000;
//				y = Math.round( y * 1000000 )/1000000;
//				io.output.write(`vt ${x} ${y}\n`);
//			} else if (/^vn /.test(line)) {
//				let [x, y, z] = line.split(' ').slice(1).map(parseFloat);
//				x = Math.round( x * 1000000 )/1000000;
//				y = Math.round( y * 1000000 )/1000000;
//				z = Math.round( z * 1000000 )/1000000;
//				io.output.write(`vn ${x} ${y} ${z}\n`);
			} else {
				return io.output.write(`${line}\n`);
			}
		}).on('close', () => {
//			console.error(`done. saved as ${file_out}`);
			readyfreddy=1;
		});

//	});
}

function sleep(ms){
    return new Promise(resolve=>{
        setTimeout(resolve,ms)
    })
}