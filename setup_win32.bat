@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-2
copy .\src\drivers\human\tracks\e-track-2\car-206W10.xml .\runtime\drivers\human\tracks\e-track-2\car-206W10.xml
copy .\src\drivers\human\tracks\e-track-2\car-torcs.xml .\runtime\drivers\human\tracks\e-track-2\car-torcs.xml
