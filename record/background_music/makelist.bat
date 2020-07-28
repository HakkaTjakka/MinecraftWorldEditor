rem echo RANDOM=ON> list.txt
rem dir /b /s /a-d /on ..\record\*.mp4 >> list.txt 
rem dir /b /s /a-d /on c:\muziek\*.mp3 >> list.txt
rem dir /b /s /a-d /on files\*.* > list.txt
rem dir /b /s /a-d /on c:\movies\green\*.* >> list.txt
rem dir /b /s /a-d /on c:\movies\cartoon\*.* >> list.txt
rem                                   !!! (>) !!!
rem dir /b /s /a-d /o-s c:\movies\movies\*.mkv > list.txt
rem dir /b /s /a-d /o-s c:\movies\movies\*.mp4 >> list.txt
rem dir /b /s /a-d /o-s c:\movies\movies\*.avi >> list.txt
rem dir /b /s /a-d /o-s D:\utorrent\klaar\*.mkv >> list.txt 
rem dir /b /s /a-d /o-s D:\utorrent\klaar\*.mp4 >> list.txt 
rem dir /b /s /a-d /o-s D:\utorrent\klaar\*.avi >> list.txt 

dir /b /s /a-d /od out*.mp4 > list.txt
