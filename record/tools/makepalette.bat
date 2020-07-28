ffmpeg -y -i %1 -vf fps=10,scale=400:-1:flags=lanczos,palettegen %1.png
ffmpeg -y -i %1 -i %1.png -filter_complex "fps=10,scale=400:-1:flags=lanczos[x];[x][1:v]paletteuse" %1.gif