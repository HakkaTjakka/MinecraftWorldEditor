ffmpeg -y -i %1 -vf fps=10,scale=320:-1:flags=lanczos,palettegen %1.png
ffmpeg -y -i %1 -i %1.png -filter_complex "fps=10,scale=320:-1:flags=lanczos[x];[x][1:v]paletteuse" %1.gif

rem ffmpeg -i %1 -filter_complex "[0:v] palettegen" palette.png
rem ffmpeg -i %1 -i palette.png -filter_complex "[0:v][1:v] paletteuse" out.gif

rem ffmpeg -i %1 -filter_complex "[0:v] fps=12,scale=w=480:h=-1,split [a][b];[a] palettegen=stats_mode=single [p];[b][p] paletteuse=new=1" out.gif