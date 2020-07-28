d:
cd \pacman\pacman
copy /Y Pacman.exe ..\pacman2\Pacman.exe
del data.txt
start Pacman.exe server udp 40002

cd ..\pacman2
del data.txt
start Pacman.exe client 127.0.0.1 udp 40002


