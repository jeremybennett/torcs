@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

call .\create_dir ./runtime
call .\create_dir ./runtime/cars
call .\create_dir ./runtime/cars/gt40
