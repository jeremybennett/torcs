@echo off
echo Checking directories ...


call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\wheel-1
copy .\data\tracks\wheel-1\wheel-1.xml .\runtime\tracks\wheel-1\wheel-1.xml
copy .\data\tracks\wheel-1\background.png .\runtime\tracks\wheel-1\background.png
copy .\data\tracks\wheel-1\env.rgb .\runtime\tracks\wheel-1\env.rgb
copy .\data\tracks\wheel-1\wheel-1.ac .\runtime\tracks\wheel-1\wheel-1.ac
