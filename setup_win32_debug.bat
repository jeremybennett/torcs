@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\2
copy .\src\drivers\damned\2\car.xml .\runtimed\drivers\damned\2\car.xml
copy .\src\drivers\damned\2\car-dirt.xml .\runtimed\drivers\damned\2\car-dirt.xml
copy .\src\drivers\damned\2\buggy.rgb .\runtimed\drivers\damned\2\buggy.rgb
copy .\src\drivers\damned\2\logo.rgb .\runtimed\drivers\damned\2\logo.rgb
