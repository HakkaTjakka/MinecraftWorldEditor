CC = g++
CFLAGS = -std=c++11 -Ofast -Wno-unused-result
LIBS = globals.cpp NBTCoder.cpp MCACoder.cpp MCEditor.cpp

default:
	$(CC) $(LIBS) test.cpp $(CFLAGS) -lz -O TEST.EXE

paint:
	$(CC) $(LIBS) paint.cpp $(CFLAGS) -lz -O PAINT.EXE

music:
	$(CC) $(LIBS) music.cpp $(CFLAGS) -lz -O MUSIC.EXE

video:
	$(CC) $(LIBS) video.cpp $(CFLAGS) -lz -O VIDEO.EXE

video2:
	$(CC) $(LIBS) video2.cpp $(CFLAGS) -lz -O VIDEO2.EXE

clean:
	rm *.out
