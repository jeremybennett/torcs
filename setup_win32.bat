@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\2
copy .\src\drivers\damned\2\car.xml .\runtime\drivers\damned\2\car.xml
copy .\src\drivers\damned\2\car-dirt.xml .\runtime\drivers\damned\2\car-dirt.xml
copy .\src\drivers\damned\2\buggy.rgb .\runtime\drivers\damned\2\buggy.rgb
copy .\src\drivers\damned\2\logo.rgb .\runtime\drivers\damned\2\logo.rgb
