@ECHO OFF

java -Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M -jar converter.jar --headless -- "srcWorld './test-2'" "dstWorld './RESULT1'" "inFormat Anvil" "outFormat CubicChunks" "converter Default"
echo move all by 0 -16 0 > relocatingConfig.txt
java -Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M -jar converter.jar --headless -- "srcWorld './RESULT1'" "dstWorld './RESULT2'" "inFormat CubicChunks" "outFormat CubicChunks" "converter Relocating"

java -Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M -jar converter.jar --headless -- "srcWorld './test-1'" "dstWorld './RESULT2'" "inFormat Anvil" "outFormat CubicChunks" "converter Default"
echo move all by 0 -16 0 > relocatingConfig.txt
java -Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M -jar converter.jar --headless -- "srcWorld './RESULT2'" "dstWorld './RESULT3'" "inFormat CubicChunks" "outFormat CubicChunks" "converter Relocating"

java -Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M -jar converter.jar --headless -- "srcWorld './test0'" "dstWorld './RESULT3'" "inFormat Anvil" "outFormat CubicChunks" "converter Default"
echo move all by 0 -16 0 > relocatingConfig.txt
java -Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M -jar converter.jar --headless -- "srcWorld './RESULT3'" "dstWorld './RESULT4'" "inFormat CubicChunks" "outFormat CubicChunks" "converter Relocating"

java -Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M -jar converter.jar --headless -- "srcWorld './test1'" "dstWorld './RESULT4'" "inFormat Anvil" "outFormat CubicChunks" "converter Default"
echo move all by 0 -16 0 > relocatingConfig.txt
java -Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M -jar converter.jar --headless -- "srcWorld './RESULT4'" "dstWorld './RESULT5'" "inFormat CubicChunks" "outFormat CubicChunks" "converter Relocating"

java -Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M -jar converter.jar --headless -- "srcWorld './test2'" "dstWorld './RESULT5'" "inFormat Anvil" "outFormat CubicChunks" "converter Default"
echo move all by 0 32 0 > relocatingConfig.txt
java -Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M -jar converter.jar --headless -- "srcWorld './RESULT5'" "dstWorld './RESULT'" "inFormat CubicChunks" "outFormat CubicChunks" "converter Relocating"

pause

exit /b

rem cubicchunksconverter --headless

rem dstWorld
	rem dst

rem inFormat
	rem Anvil
	rem CubicChunks
	rem RobintonCubicChunks

rem outFormat
	rem Anvil
	rem CubicChunks
	
rem srcWorld
	rem src
	
rem converter
	rem Default
	rem Relocating

rem            "srcWorld=" + srcWorld +
rem            ", dstWorld=" + dstWorld +
rem            ", inFormat='" + inFormat + '\'' +
rem            ", outFormat='" + outFormat + '\'' +
rem            ", converterName='" + converterName + '\'' +

REM java -jar cubicchunksconverter-1.75.0-SNAPSHOT-all.jar --headless -- "srcWorld './New World'" "dstWorld './New WorldCC'" "inFormat Anvil" "outFormat CubicChunks"
