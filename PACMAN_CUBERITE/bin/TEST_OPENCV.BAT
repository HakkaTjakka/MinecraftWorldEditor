@ECHO OFF
REM This program demonstrates the use of cv::CascadeClassifier class to detect objects (Face + eyes). You can use Haar or LBP features.
REM This classifier can recognize many kinds of rigid objects, once the appropriate classifier is trained.
REM It's most known use is for faces.
REM Usage:
REM ./facedetect [--cascade=<cascade_path> this is the primary trained classifier such as frontal face]
REM    [--nested-cascade[=nested_cascade_path this an optional secondary classifier such as eyes]]
REM    [--scale=<image scale greater or equal to 1, try 1.3 for example>]
REM    [--try-flip]
REM    [filename|camera_index]

REM see facedetect.cmd for one call:
REM ./facedetect --cascade="data/haarcascades/haarcascade_frontalface_alt.xml" --nested-cascade="data/haarcascades/haarcascade_eye_tree_eyeglasses.xml" --scale=1.3

REM During execution:
REM 	Hit any key to quit.
REM 	Using OpenCV version 3.4.6

opencv.exe --cascade="C:/opencv-3.4.6/data/haarcascades/haarcascade_frontalface_alt.xml" --nested-cascade="C:/opencv-3.4.6/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml" --scale=1.3 %1
