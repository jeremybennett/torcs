@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

call .\create_dir ./runtime
call .\create_dir ./runtime/tracks
call .\create_dir ./runtime/tracks/road
call .\create_dir ./runtime/tracks/road/g-track-2
