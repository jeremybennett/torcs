@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

call .\create_dir .\runtimed
call .\create_dir .\runtimed\config
call .\create_dir .\runtimed\config\quickrace
copy .\src\modules\raceman\quickrace\qrace.xml .\runtimed\config\quickrace\qrace.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\raceman
