@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-2
copy .\src\drivers\human\tracks\e-track-2\car-206W10.xml .\runtimed\drivers\human\tracks\e-track-2\car-206W10.xml
copy .\src\drivers\human\tracks\e-track-2\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-2\car-torcs.xml
