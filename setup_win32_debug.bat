@echo off
echo Checking directories ...


call .\create_dir .\runtimed
call .\create_dir .\runtimed\tracks
call .\create_dir .\runtimed\tracks\wheel-1
copy .\data\tracks\wheel-1\wheel-1.xml .\runtimed\tracks\wheel-1\wheel-1.xml
copy .\data\tracks\wheel-1\background.png .\runtimed\tracks\wheel-1\background.png
copy .\data\tracks\wheel-1\env.rgb .\runtimed\tracks\wheel-1\env.rgb
copy .\data\tracks\wheel-1\wheel-1.ac .\runtimed\tracks\wheel-1\wheel-1.ac
