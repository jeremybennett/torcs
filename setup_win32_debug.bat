@echo off
echo Checking directories ...


call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tanhoj
call .\create_dir .\runtimed\drivers\tanhoj\tracksdata
copy .\src\drivers\tanhoj\tracksdata\aalborg.xml .\runtimed\drivers\tanhoj\tracksdata\aalborg.xml
copy .\src\drivers\tanhoj\tracksdata\a-speedway.xml .\runtimed\drivers\tanhoj\tracksdata\a-speedway.xml
copy .\src\drivers\tanhoj\tracksdata\car_aalborg.xml .\runtimed\drivers\tanhoj\tracksdata\car_aalborg.xml
copy .\src\drivers\tanhoj\tracksdata\car_a-speedway.xml .\runtimed\drivers\tanhoj\tracksdata\car_a-speedway.xml
copy .\src\drivers\tanhoj\tracksdata\car_eroad.xml .\runtimed\drivers\tanhoj\tracksdata\car_eroad.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-1.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-2.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-2.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-3.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-3.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-4.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-4.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-5.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-5.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-6.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-6.xml
copy .\src\drivers\tanhoj\tracksdata\car_g-track-1.xml .\runtimed\drivers\tanhoj\tracksdata\car_g-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_michigan.xml .\runtimed\drivers\tanhoj\tracksdata\car_michigan.xml
copy .\src\drivers\tanhoj\tracksdata\car_s2.xml .\runtimed\drivers\tanhoj\tracksdata\car_s2.xml
copy .\src\drivers\tanhoj\tracksdata\car_test-1.xml .\runtimed\drivers\tanhoj\tracksdata\car_test-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_wheel-1.xml .\runtimed\drivers\tanhoj\tracksdata\car_wheel-1.xml
copy .\src\drivers\tanhoj\tracksdata\eroad.xml .\runtimed\drivers\tanhoj\tracksdata\eroad.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-1.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-2.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-2.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-3.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-3.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-4.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-4.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-5.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-5.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-6.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-6.xml
copy .\src\drivers\tanhoj\tracksdata\g-track-1.xml .\runtimed\drivers\tanhoj\tracksdata\g-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\michigan.xml .\runtimed\drivers\tanhoj\tracksdata\michigan.xml
copy .\src\drivers\tanhoj\tracksdata\s2.xml .\runtimed\drivers\tanhoj\tracksdata\s2.xml
copy .\src\drivers\tanhoj\tracksdata\wheel-1.xml .\runtimed\drivers\tanhoj\tracksdata\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tanhoj
copy .\src\drivers\tanhoj\tanhoj.xml .\runtimed\drivers\tanhoj\tanhoj.xml
copy .\src\drivers\tanhoj\car1.xml .\runtimed\drivers\tanhoj\car1.xml
copy .\src\drivers\tanhoj\logo.rgb .\runtimed\drivers\tanhoj\logo.rgb
copy .\src\drivers\tanhoj\cg-nascar-rwd.rgb .\runtimed\drivers\tanhoj\cg-nascar-rwd.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tanhoj
