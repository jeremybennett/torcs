@echo off
echo Checking directories ...


call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tanhoj
call .\create_dir .\runtime\drivers\tanhoj\tracksdata
copy .\src\drivers\tanhoj\tracksdata\aalborg.xml .\runtime\drivers\tanhoj\tracksdata\aalborg.xml
copy .\src\drivers\tanhoj\tracksdata\a-speedway.xml .\runtime\drivers\tanhoj\tracksdata\a-speedway.xml
copy .\src\drivers\tanhoj\tracksdata\car_aalborg.xml .\runtime\drivers\tanhoj\tracksdata\car_aalborg.xml
copy .\src\drivers\tanhoj\tracksdata\car_a-speedway.xml .\runtime\drivers\tanhoj\tracksdata\car_a-speedway.xml
copy .\src\drivers\tanhoj\tracksdata\car_eroad.xml .\runtime\drivers\tanhoj\tracksdata\car_eroad.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-1.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-2.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-2.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-3.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-3.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-4.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-4.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-5.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-5.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-6.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-6.xml
copy .\src\drivers\tanhoj\tracksdata\car_g-track-1.xml .\runtime\drivers\tanhoj\tracksdata\car_g-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_michigan.xml .\runtime\drivers\tanhoj\tracksdata\car_michigan.xml
copy .\src\drivers\tanhoj\tracksdata\car_s2.xml .\runtime\drivers\tanhoj\tracksdata\car_s2.xml
copy .\src\drivers\tanhoj\tracksdata\car_test-1.xml .\runtime\drivers\tanhoj\tracksdata\car_test-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_wheel-1.xml .\runtime\drivers\tanhoj\tracksdata\car_wheel-1.xml
copy .\src\drivers\tanhoj\tracksdata\eroad.xml .\runtime\drivers\tanhoj\tracksdata\eroad.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-1.xml .\runtime\drivers\tanhoj\tracksdata\e-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-2.xml .\runtime\drivers\tanhoj\tracksdata\e-track-2.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-3.xml .\runtime\drivers\tanhoj\tracksdata\e-track-3.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-4.xml .\runtime\drivers\tanhoj\tracksdata\e-track-4.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-5.xml .\runtime\drivers\tanhoj\tracksdata\e-track-5.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-6.xml .\runtime\drivers\tanhoj\tracksdata\e-track-6.xml
copy .\src\drivers\tanhoj\tracksdata\g-track-1.xml .\runtime\drivers\tanhoj\tracksdata\g-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\michigan.xml .\runtime\drivers\tanhoj\tracksdata\michigan.xml
copy .\src\drivers\tanhoj\tracksdata\s2.xml .\runtime\drivers\tanhoj\tracksdata\s2.xml
copy .\src\drivers\tanhoj\tracksdata\wheel-1.xml .\runtime\drivers\tanhoj\tracksdata\wheel-1.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tanhoj
copy .\src\drivers\tanhoj\tanhoj.xml .\runtime\drivers\tanhoj\tanhoj.xml
copy .\src\drivers\tanhoj\car1.xml .\runtime\drivers\tanhoj\car1.xml
copy .\src\drivers\tanhoj\logo.rgb .\runtime\drivers\tanhoj\logo.rgb
copy .\src\drivers\tanhoj\cg-nascar-rwd.rgb .\runtime\drivers\tanhoj\cg-nascar-rwd.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tanhoj
