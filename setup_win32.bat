@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\SWRC62
copy .\data\cars\models\SWRC62\SWRC62.xml .\runtime\cars\SWRC62\SWRC62.xml
copy .\data\cars\models\SWRC62\SWRC62.rgb .\runtime\cars\SWRC62\SWRC62.rgb
copy .\data\cars\models\SWRC62\tex-wheel.rgb .\runtime\cars\SWRC62\tex-wheel.rgb
copy .\data\cars\models\SWRC62\SWRC62.ac .\runtime\cars\SWRC62\SWRC62.ac
copy .\data\cars\models\SWRC62\readme.txt .\runtime\cars\SWRC62\readme.txt
