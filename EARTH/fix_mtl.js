"use strict";

// centers and scales all *.obj and saves results as *.2.obj
// can also keep 3d viewers from jittering

const fs = require('fs');
const readline = require('readline');
const path = require('path');
const OBJ_DIR = './downloaded_files/new';

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
			if (!/\.obj$/.test(j) || /\.fixed\.obj$/.test(j)) {
				if (/\.original\.obj$/.test(j)) {
					n = n + 1;
					console.error(n + ` skipping: ` + j);
				} 
				continue;
			} else if (fs.statSync(j).isFile()) {
				let file_out = `${j.match(/(.*)\.obj$/)[1]}.fixed.obj`;
				if (fs.existsSync(j) && !fs.existsSync(file_out) ) {
					n = n + 1;
					readyfreddy = 0;
					console.error(n + ` converting: ` + j);
					scaleMoveObj( j, file_out);
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

		const enschede_x=3875099.0;
		const enschede_y=468154.0;
		const enschede_z=5035344.0;

		const io = readline.createInterface({
			input: fs.createReadStream(file_in),
			output: fs.createWriteStream(file_out),
		});
		var usemtl_line = '';
		io.on('line', line => {
			if (/^usemtl /.test(line)) {
				usemtl_line = line;
			} else if (/^# faces/.test(line)) {
				io.output.write(`${usemtl_line}\n`);
				io.output.write(`${line}\n`);
				usemtl_line = 'Error usemtl conversion';
			} else {
				io.output.write(`${line}\n`);
			}
		}).on('close', () => {
			console.error('done.');
			readyfreddy=1;
		});

}

function sleep(ms){
    return new Promise(resolve=>{
        setTimeout(resolve,ms)
    })
}