@echo off
echo Checking directories ...


call .\create_dir .\runtime
call .\create_dir .\runtime\config
call .\create_dir .\runtime\config\quickrace
copy .\src\modules\raceman\quickrace\qrace.xml .\runtime\config\quickrace\qrace.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\modules
call .\create_dir .\runtime\modules\raceman
