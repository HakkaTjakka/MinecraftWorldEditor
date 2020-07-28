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

		const enschede_x=3875099.0;
		const enschede_y=468154.0;
		const enschede_z=5035344.0;

		const io = readline.createInterface({
			input: fs.createReadStream(file_in),
			output: fs.createWriteStream(file_out),
		});
		io.on('line', line => {
			if (/^v /.test(line)) {
				let [x, y, z] = line.split(' ').slice(1).map(parseFloat);
				x =  ((x - enschede_x)/100.0 );
				y =  ((y - enschede_y)/100.0 );
				z =  ((z - enschede_z)/100.0 );
				x = Math.round( x * 1000000 )/1000000;  //dont use this one, use center_scale_obj.js 
				y = Math.round( y * 1000000 )/1000000;
				z = Math.round( z * 1000000 )/1000000;
				io.output.write(`v ${x} ${y} ${z}\n`);
			} else if (/^vt /.test(line)) {
				let [x, y] = line.split(' ').slice(1).map(parseFloat);
				x = Math.round( x * 1000000 )/1000000;
				y = Math.round( y * 1000000 )/1000000;
				io.output.write(`vt ${x} ${y}\n`);
			} else if (/^vn /.test(line)) {
				let [x, y, z] = line.split(' ').slice(1).map(parseFloat);
				x = Math.round( x * 1000000 )/1000000;
				y = Math.round( y * 1000000 )/1000000;
				z = Math.round( z * 1000000 )/1000000;
				io.output.write(`vn ${x} ${y} ${z}\n`);
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