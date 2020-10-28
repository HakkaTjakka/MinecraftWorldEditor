https://www.facebook.com/110607880303634/videos/2890693617828393/

This batch file is used to merge several Minecraft 1.12.2 worlds up each other for use with Cubic 
Chunks mod.

Especially used for BUILD THE EARTH 121 (scale 1 to 1) project, in combination with the Google 3d 
object downloader, and the 3d wavefront to Minecraft 1.12.2 voxelizer.



File:	CONVERTER.jar : 

		- cubicchunksconverter-1.75.0-SNAPSHOT-all.jar from .\CubicChunksConverter\build\libs

		- build under Powershell Ubuntu with ./gradlew build

Dir: 	TEST0 :

		- Minecraft 1.12.2 world directory with floor 0 (0-255)

		TEST1 :

		- floor 1 (256-511)

		TEST2 :

		- floor 2 (512-768)

		TEST-1 :

		- cellar 1 (-256 - -1)

		TEST-2 :

		- cellar 2 (-257 - -512)

Dir: 	RESULT1 - RESULT4 :

		- Intermediate directories shifted floors/worlds

Dir: 	RESULT5 :

		- Resulting Cubic World with floor 0 bottom at 0 (Last one, needs not to be shifted when using 
		  TEST_FASTEST.BAT)



		- DELETE RESULT1 - RESULT5 BEFORE CONVERTING!!!



File:	TEST_FASTEST.BAT :

		- Conversion dos cmd batch file.

		- Converts TEST-2 (cellar 2) to RESULT1

		- Shifts RESULT1 one floor up (16 chunks,256 blocks) down to RESULT2

		- Converts TEST-1 (cellar 1) and merges to RESULT2

		- Shifts RESULT2 three floors down (48 chunks) down to RESULT3

		- Converts TEST2 (floor 2) and merges to RESULT3

		- Shifts RESULT3 one floor down (16 chunks) down to RESULT4

		- Converts TEST1 (floor 1) and merges to RESULT4

		- Shifts RESULT4 one floor down (16 chunks) down to RESULT5

		- Converts TEST0 (ground 0) and merges to RESULT5 (final)

		- TEST0 base world is last because its assumed largest. (Needs not to be shifted when using 
		  this order for 5 floors)

		- Injected vanilla 1.12.2 world is placed at 0-255 in cubic chunks format, THEN! shifted with 
		  second command.

		  (Both doesn't work in one convertion run. relocatingConfig.txt is only used when converting 
		  Cubic Chunks -> Cubic Chunks (Relocating)).

File: 	- relocatingConfig.txt :

		- File with relocating data.

Dir:	div/mods : 

		- Used BTE mods plus shader/replay mods

		div/data :

		- Some recursive command block floodfill functions 1.12 (also replace specific block with 
		  command block with command included) and/or 1.13+

		

(Cubic Chunks Converter)

	- https://github.com/OpenCubicChunks/CubicChunksConverter



(Build The Earth 121 Project)

	- https://buildtheearth.net/



(MinecraftWorldEditor: c/c++ fokking fast 3d Wavefront .obj/.mtl/textures to Minecraft 1.12.2 voxelizer) :

	- Includes multi threaded textures loader, compressed .nbt 3d data, voxelizer, Google 3d 
	  downloader, poster generator, .mca/.nbt reader/writer/editor, large canvas, and much more (c/c++ 
	  source code, experimental prototyping machine)

	- https://github.com/HakkaTjakka/MinecraftWorldEditor

	- https://www.youtube.com/channel/UCdmRlIxcrXmkC7puY4s9Jzg

	- https://www.facebook.com/Minecraft-Worldeditor-110607880303634/

	

(Google 3d maps wavefront 3d format downloader, also included in MinecraftWorldEditor for bulk downloading)	

	- https://github.com/retroplasma/earth-reverse-engineering	



Build The Earth project automated:

	- Download with the EARTH Javascript whole cities / areas from Google 3d Maps/Earth server in bulk.

	- Convert downloaded data with dos/linux shell scripts, convert and intergrate data with Minecraft 
	  World Editor.

	- Voxelize 3d Wavefront data from Google 3d and convert to Minecraft 1.12.2 world(s) (floors) to 
	  BTE scale / coordinates (tpll).

	- Convert several layers of voxelized data into one Cubic Chunks format.

	- The resulting Minecraft Cubic Chunks format can be used as a MOLD for BTE 121 project. (TOS 
	  Google 3d)

	  Unclear if the resuling voxelized Google 3d to Minecraft 1.12.2 can be used as display in BTE 
	  because of copyright (Terms Of Service).

	  So result needs to be edited. This whole tool is assistant to that. Except automated from Google 
	  3d to BTE 121 goes with millions of blocks per second. No builder can beat that with his/her 
	  pointing finger and mouse.... Just try it.
