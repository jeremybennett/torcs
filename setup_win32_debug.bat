@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

call .\create_dir .\runtimed
call .\create_dir .\runtimed\cars
call .\create_dir .\runtimed\cars\SWRC62
copy .\data\cars\models\SWRC62\SWRC62.xml .\runtimed\cars\SWRC62\SWRC62.xml
copy .\data\cars\models\SWRC62\SWRC62.rgb .\runtimed\cars\SWRC62\SWRC62.rgb
copy .\data\cars\models\SWRC62\tex-wheel.rgb .\runtimed\cars\SWRC62\tex-wheel.rgb
copy .\data\cars\models\SWRC62\SWRC62.ac .\runtimed\cars\SWRC62\SWRC62.ac
copy .\data\cars\models\SWRC62\readme.txt .\runtimed\cars\SWRC62\readme.txt
