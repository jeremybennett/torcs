@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

if exist .\src\interfaces\*.* call .\create_dir .\export
if exist .\src\interfaces\*.* call .\create_dir .\export\include
if exist .\src\interfaces\car.h copy .\src\interfaces\car.h .\export\include\car.h
if exist .\src\interfaces\graphic.h copy .\src\interfaces\graphic.h .\export\include\graphic.h
if exist .\src\interfaces\js.h copy .\src\interfaces\js.h .\export\include\js.h
if exist .\src\interfaces\playerpref.h copy .\src\interfaces\playerpref.h .\export\include\playerpref.h
if exist .\src\interfaces\raceman.h copy .\src\interfaces\raceman.h .\export\include\raceman.h
if exist .\src\interfaces\replay.h copy .\src\interfaces\replay.h .\export\include\replay.h
if exist .\src\interfaces\robot.h copy .\src\interfaces\robot.h .\export\include\robot.h
if exist .\src\interfaces\simu.h copy .\src\interfaces\simu.h .\export\include\simu.h
if exist .\src\interfaces\telemetry.h copy .\src\interfaces\telemetry.h .\export\include\telemetry.h
if exist .\src\interfaces\track.h copy .\src\interfaces\track.h .\export\include\track.h

if exist .\src\libs\txml\*.* call .\create_dir .\export
if exist .\src\libs\txml\*.* call .\create_dir .\export\include
if exist .\src\libs\txml\xml.h copy .\src\libs\txml\xml.h .\export\include\xml.h
if exist .\src\libs\txml\xmlparse.h copy .\src\libs\txml\xmlparse.h .\export\include\xmlparse.h

if exist .\src\libs\tgf\*.* call .\create_dir .\export
if exist .\src\libs\tgf\*.* call .\create_dir .\export\include
if exist .\src\libs\tgf\tgf.h copy .\src\libs\tgf\tgf.h .\export\include\tgf.h
if exist .\src\libs\tgf\os.h copy .\src\libs\tgf\os.h .\export\include\os.h

if exist .\src\libs\tgfclient\*.* call .\create_dir .\export
if exist .\src\libs\tgfclient\*.* call .\create_dir .\export\include
if exist .\src\libs\tgfclient\tgfclient.h copy .\src\libs\tgfclient\tgfclient.h .\export\include\tgfclient.h
if exist .\src\libs\tgfclient\screen_properties.h copy .\src\libs\tgfclient\screen_properties.h .\export\include\screen_properties.h

if exist .\src\libs\client\*.* call .\create_dir .\export
if exist .\src\libs\client\*.* call .\create_dir .\export\include
if exist .\src\libs\client\client.h copy .\src\libs\client\client.h .\export\include\client.h
if exist .\src\libs\client\exitmenu.h copy .\src\libs\client\exitmenu.h .\export\include\exitmenu.h

if exist .\src\libs\confscreens\*.* call .\create_dir .\export
if exist .\src\libs\confscreens\*.* call .\create_dir .\export\include
if exist .\src\libs\confscreens\confscreens.h copy .\src\libs\confscreens\confscreens.h .\export\include\confscreens.h
if exist .\src\libs\confscreens\driverconfig.h copy .\src\libs\confscreens\driverconfig.h .\export\include\driverconfig.h
if exist .\src\libs\confscreens\joystickconfig.h copy .\src\libs\confscreens\joystickconfig.h .\export\include\joystickconfig.h
if exist .\src\libs\confscreens\mouseconfig.h copy .\src\libs\confscreens\mouseconfig.h .\export\include\mouseconfig.h
if exist .\src\libs\confscreens\controlconfig.h copy .\src\libs\confscreens\controlconfig.h .\export\include\controlconfig.h
if exist .\src\libs\confscreens\graphconfig.h copy .\src\libs\confscreens\graphconfig.h .\export\include\graphconfig.h

if exist .\src\libs\racescreens\*.* call .\create_dir .\export
if exist .\src\libs\racescreens\*.* call .\create_dir .\export\include
if exist .\src\libs\racescreens\racescreens.h copy .\src\libs\racescreens\racescreens.h .\export\include\racescreens.h

if exist .\src\libs\robottools\*.* call .\create_dir .\export
if exist .\src\libs\robottools\*.* call .\create_dir .\export\include
if exist .\src\libs\robottools\robottools.h copy .\src\libs\robottools\robottools.h .\export\include\robottools.h

if exist .\src\libs\raceengineclient\*.* call .\create_dir .\export
if exist .\src\libs\raceengineclient\*.* call .\create_dir .\export\include
if exist .\src\libs\raceengineclient\singleplayer.h copy .\src\libs\raceengineclient\singleplayer.h .\export\include\singleplayer.h

if exist .\src\linux\*.* call .\create_dir .\export
if exist .\src\linux\*.* call .\create_dir .\export\include
if exist .\src\windows\osspec.h copy .\src\windows\osspec.h .\export\include\osspec.h

if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\*.* call .\create_dir .\export
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\*.* call .\create_dir .\export\include
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\*.* call .\create_dir .\export\include\3D
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Basic.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Basic.h .\export\include\3D\Basic.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Matrix.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Matrix.h .\export\include\3D\Matrix.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Point.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Point.h .\export\include\3D\Point.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Quaternion.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Quaternion.h .\export\include\3D\Quaternion.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Tuple3.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Tuple3.h .\export\include\3D\Tuple3.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Tuple4.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Tuple4.h .\export\include\3D\Tuple4.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Vector.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Vector.h .\export\include\3D\Vector.h

if exist .\src\modules\simu\simuv2\SOLID-2.0\include\SOLID\*.* call .\create_dir .\export
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\SOLID\*.* call .\create_dir .\export\include
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\SOLID\*.* call .\create_dir .\export\include\SOLID
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\SOLID\solid.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\SOLID\solid.h .\export\include\SOLID\solid.h

if exist .\src\drivers\astigot\0\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\0\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\0\practice\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\0\practice\*.* call .\create_dir .\runtime\drivers\astigot\0
if exist .\src\drivers\astigot\0\practice\*.* call .\create_dir .\runtime\drivers\astigot\0\practice
if exist .\src\drivers\astigot\0\practice\aalborg.xml copy .\src\drivers\astigot\0\practice\aalborg.xml .\runtime\drivers\astigot\0\practice\aalborg.xml
if exist .\src\drivers\astigot\0\practice\alpine-1.xml copy .\src\drivers\astigot\0\practice\alpine-1.xml .\runtime\drivers\astigot\0\practice\alpine-1.xml
if exist .\src\drivers\astigot\0\practice\a-speedway.xml copy .\src\drivers\astigot\0\practice\a-speedway.xml .\runtime\drivers\astigot\0\practice\a-speedway.xml
if exist .\src\drivers\astigot\0\practice\eroad.xml copy .\src\drivers\astigot\0\practice\eroad.xml .\runtime\drivers\astigot\0\practice\eroad.xml
if exist .\src\drivers\astigot\0\practice\e-track-1.xml copy .\src\drivers\astigot\0\practice\e-track-1.xml .\runtime\drivers\astigot\0\practice\e-track-1.xml
if exist .\src\drivers\astigot\0\practice\e-track-2.xml copy .\src\drivers\astigot\0\practice\e-track-2.xml .\runtime\drivers\astigot\0\practice\e-track-2.xml
if exist .\src\drivers\astigot\0\practice\e-track-3.xml copy .\src\drivers\astigot\0\practice\e-track-3.xml .\runtime\drivers\astigot\0\practice\e-track-3.xml
if exist .\src\drivers\astigot\0\practice\e-track-4.xml copy .\src\drivers\astigot\0\practice\e-track-4.xml .\runtime\drivers\astigot\0\practice\e-track-4.xml
if exist .\src\drivers\astigot\0\practice\e-track-5.xml copy .\src\drivers\astigot\0\practice\e-track-5.xml .\runtime\drivers\astigot\0\practice\e-track-5.xml
if exist .\src\drivers\astigot\0\practice\e-track-6.xml copy .\src\drivers\astigot\0\practice\e-track-6.xml .\runtime\drivers\astigot\0\practice\e-track-6.xml
if exist .\src\drivers\astigot\0\practice\g-track-1.xml copy .\src\drivers\astigot\0\practice\g-track-1.xml .\runtime\drivers\astigot\0\practice\g-track-1.xml
if exist .\src\drivers\astigot\0\practice\g-track-2.xml copy .\src\drivers\astigot\0\practice\g-track-2.xml .\runtime\drivers\astigot\0\practice\g-track-2.xml
if exist .\src\drivers\astigot\0\practice\g-track-3.xml copy .\src\drivers\astigot\0\practice\g-track-3.xml .\runtime\drivers\astigot\0\practice\g-track-3.xml
if exist .\src\drivers\astigot\0\practice\michigan.xml copy .\src\drivers\astigot\0\practice\michigan.xml .\runtime\drivers\astigot\0\practice\michigan.xml
if exist .\src\drivers\astigot\0\practice\wheel-1.xml copy .\src\drivers\astigot\0\practice\wheel-1.xml .\runtime\drivers\astigot\0\practice\wheel-1.xml

if exist .\src\drivers\astigot\0\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\0\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\0\qualifying\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\0\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\0
if exist .\src\drivers\astigot\0\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\0\qualifying
if exist .\src\drivers\astigot\0\qualifying\aalborg.xml copy .\src\drivers\astigot\0\qualifying\aalborg.xml .\runtime\drivers\astigot\0\qualifying\aalborg.xml
if exist .\src\drivers\astigot\0\qualifying\alpine-1.xml copy .\src\drivers\astigot\0\qualifying\alpine-1.xml .\runtime\drivers\astigot\0\qualifying\alpine-1.xml
if exist .\src\drivers\astigot\0\qualifying\a-speedway.xml copy .\src\drivers\astigot\0\qualifying\a-speedway.xml .\runtime\drivers\astigot\0\qualifying\a-speedway.xml
if exist .\src\drivers\astigot\0\qualifying\eroad.xml copy .\src\drivers\astigot\0\qualifying\eroad.xml .\runtime\drivers\astigot\0\qualifying\eroad.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-1.xml copy .\src\drivers\astigot\0\qualifying\e-track-1.xml .\runtime\drivers\astigot\0\qualifying\e-track-1.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-2.xml copy .\src\drivers\astigot\0\qualifying\e-track-2.xml .\runtime\drivers\astigot\0\qualifying\e-track-2.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-3.xml copy .\src\drivers\astigot\0\qualifying\e-track-3.xml .\runtime\drivers\astigot\0\qualifying\e-track-3.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-4.xml copy .\src\drivers\astigot\0\qualifying\e-track-4.xml .\runtime\drivers\astigot\0\qualifying\e-track-4.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-5.xml copy .\src\drivers\astigot\0\qualifying\e-track-5.xml .\runtime\drivers\astigot\0\qualifying\e-track-5.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-6.xml copy .\src\drivers\astigot\0\qualifying\e-track-6.xml .\runtime\drivers\astigot\0\qualifying\e-track-6.xml
if exist .\src\drivers\astigot\0\qualifying\g-track-1.xml copy .\src\drivers\astigot\0\qualifying\g-track-1.xml .\runtime\drivers\astigot\0\qualifying\g-track-1.xml
if exist .\src\drivers\astigot\0\qualifying\g-track-2.xml copy .\src\drivers\astigot\0\qualifying\g-track-2.xml .\runtime\drivers\astigot\0\qualifying\g-track-2.xml
if exist .\src\drivers\astigot\0\qualifying\g-track-3.xml copy .\src\drivers\astigot\0\qualifying\g-track-3.xml .\runtime\drivers\astigot\0\qualifying\g-track-3.xml
if exist .\src\drivers\astigot\0\qualifying\michigan.xml copy .\src\drivers\astigot\0\qualifying\michigan.xml .\runtime\drivers\astigot\0\qualifying\michigan.xml
if exist .\src\drivers\astigot\0\qualifying\wheel-1.xml copy .\src\drivers\astigot\0\qualifying\wheel-1.xml .\runtime\drivers\astigot\0\qualifying\wheel-1.xml

if exist .\src\drivers\astigot\0\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\0\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\0\race\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\0\race\*.* call .\create_dir .\runtime\drivers\astigot\0
if exist .\src\drivers\astigot\0\race\*.* call .\create_dir .\runtime\drivers\astigot\0\race
if exist .\src\drivers\astigot\0\race\aalborg.xml copy .\src\drivers\astigot\0\race\aalborg.xml .\runtime\drivers\astigot\0\race\aalborg.xml
if exist .\src\drivers\astigot\0\race\alpine-1.xml copy .\src\drivers\astigot\0\race\alpine-1.xml .\runtime\drivers\astigot\0\race\alpine-1.xml
if exist .\src\drivers\astigot\0\race\a-speedway.xml copy .\src\drivers\astigot\0\race\a-speedway.xml .\runtime\drivers\astigot\0\race\a-speedway.xml
if exist .\src\drivers\astigot\0\race\eroad.xml copy .\src\drivers\astigot\0\race\eroad.xml .\runtime\drivers\astigot\0\race\eroad.xml
if exist .\src\drivers\astigot\0\race\e-track-1.xml copy .\src\drivers\astigot\0\race\e-track-1.xml .\runtime\drivers\astigot\0\race\e-track-1.xml
if exist .\src\drivers\astigot\0\race\e-track-2.xml copy .\src\drivers\astigot\0\race\e-track-2.xml .\runtime\drivers\astigot\0\race\e-track-2.xml
if exist .\src\drivers\astigot\0\race\e-track-3.xml copy .\src\drivers\astigot\0\race\e-track-3.xml .\runtime\drivers\astigot\0\race\e-track-3.xml
if exist .\src\drivers\astigot\0\race\e-track-4.xml copy .\src\drivers\astigot\0\race\e-track-4.xml .\runtime\drivers\astigot\0\race\e-track-4.xml
if exist .\src\drivers\astigot\0\race\e-track-5.xml copy .\src\drivers\astigot\0\race\e-track-5.xml .\runtime\drivers\astigot\0\race\e-track-5.xml
if exist .\src\drivers\astigot\0\race\e-track-6.xml copy .\src\drivers\astigot\0\race\e-track-6.xml .\runtime\drivers\astigot\0\race\e-track-6.xml
if exist .\src\drivers\astigot\0\race\g-track-1.xml copy .\src\drivers\astigot\0\race\g-track-1.xml .\runtime\drivers\astigot\0\race\g-track-1.xml
if exist .\src\drivers\astigot\0\race\g-track-2.xml copy .\src\drivers\astigot\0\race\g-track-2.xml .\runtime\drivers\astigot\0\race\g-track-2.xml
if exist .\src\drivers\astigot\0\race\g-track-3.xml copy .\src\drivers\astigot\0\race\g-track-3.xml .\runtime\drivers\astigot\0\race\g-track-3.xml
if exist .\src\drivers\astigot\0\race\michigan.xml copy .\src\drivers\astigot\0\race\michigan.xml .\runtime\drivers\astigot\0\race\michigan.xml
if exist .\src\drivers\astigot\0\race\wheel-1.xml copy .\src\drivers\astigot\0\race\wheel-1.xml .\runtime\drivers\astigot\0\race\wheel-1.xml

if exist .\src\drivers\astigot\0\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\0\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\0\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\0\*.* call .\create_dir .\runtime\drivers\astigot\0
if exist .\src\drivers\astigot\0\default.xml copy .\src\drivers\astigot\0\default.xml .\runtime\drivers\astigot\0\default.xml
if exist .\src\drivers\astigot\0\cg-nascar-rwd.rgb copy .\src\drivers\astigot\0\cg-nascar-rwd.rgb .\runtime\drivers\astigot\0\cg-nascar-rwd.rgb

if exist .\src\drivers\astigot\1\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\1\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\1\practice\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\1\practice\*.* call .\create_dir .\runtime\drivers\astigot\1
if exist .\src\drivers\astigot\1\practice\*.* call .\create_dir .\runtime\drivers\astigot\1\practice
if exist .\src\drivers\astigot\1\practice\aalborg.xml copy .\src\drivers\astigot\1\practice\aalborg.xml .\runtime\drivers\astigot\1\practice\aalborg.xml
if exist .\src\drivers\astigot\1\practice\alpine-1.xml copy .\src\drivers\astigot\1\practice\alpine-1.xml .\runtime\drivers\astigot\1\practice\alpine-1.xml
if exist .\src\drivers\astigot\1\practice\eroad.xml copy .\src\drivers\astigot\1\practice\eroad.xml .\runtime\drivers\astigot\1\practice\eroad.xml
if exist .\src\drivers\astigot\1\practice\e-track-1.xml copy .\src\drivers\astigot\1\practice\e-track-1.xml .\runtime\drivers\astigot\1\practice\e-track-1.xml
if exist .\src\drivers\astigot\1\practice\e-track-2.xml copy .\src\drivers\astigot\1\practice\e-track-2.xml .\runtime\drivers\astigot\1\practice\e-track-2.xml
if exist .\src\drivers\astigot\1\practice\e-track-3.xml copy .\src\drivers\astigot\1\practice\e-track-3.xml .\runtime\drivers\astigot\1\practice\e-track-3.xml
if exist .\src\drivers\astigot\1\practice\e-track-4.xml copy .\src\drivers\astigot\1\practice\e-track-4.xml .\runtime\drivers\astigot\1\practice\e-track-4.xml
if exist .\src\drivers\astigot\1\practice\e-track-6.xml copy .\src\drivers\astigot\1\practice\e-track-6.xml .\runtime\drivers\astigot\1\practice\e-track-6.xml
if exist .\src\drivers\astigot\1\practice\g-track-2.xml copy .\src\drivers\astigot\1\practice\g-track-2.xml .\runtime\drivers\astigot\1\practice\g-track-2.xml
if exist .\src\drivers\astigot\1\practice\g-track-3.xml copy .\src\drivers\astigot\1\practice\g-track-3.xml .\runtime\drivers\astigot\1\practice\g-track-3.xml
if exist .\src\drivers\astigot\1\practice\wheel-1.xml copy .\src\drivers\astigot\1\practice\wheel-1.xml .\runtime\drivers\astigot\1\practice\wheel-1.xml

if exist .\src\drivers\astigot\1\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\1\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\1\qualifying\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\1\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\1
if exist .\src\drivers\astigot\1\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\1\qualifying
if exist .\src\drivers\astigot\1\qualifying\aalborg.xml copy .\src\drivers\astigot\1\qualifying\aalborg.xml .\runtime\drivers\astigot\1\qualifying\aalborg.xml
if exist .\src\drivers\astigot\1\qualifying\alpine-1.xml copy .\src\drivers\astigot\1\qualifying\alpine-1.xml .\runtime\drivers\astigot\1\qualifying\alpine-1.xml
if exist .\src\drivers\astigot\1\qualifying\eroad.xml copy .\src\drivers\astigot\1\qualifying\eroad.xml .\runtime\drivers\astigot\1\qualifying\eroad.xml
if exist .\src\drivers\astigot\1\qualifying\e-track-1.xml copy .\src\drivers\astigot\1\qualifying\e-track-1.xml .\runtime\drivers\astigot\1\qualifying\e-track-1.xml
if exist .\src\drivers\astigot\1\qualifying\e-track-2.xml copy .\src\drivers\astigot\1\qualifying\e-track-2.xml .\runtime\drivers\astigot\1\qualifying\e-track-2.xml
if exist .\src\drivers\astigot\1\qualifying\e-track-3.xml copy .\src\drivers\astigot\1\qualifying\e-track-3.xml .\runtime\drivers\astigot\1\qualifying\e-track-3.xml
if exist .\src\drivers\astigot\1\qualifying\e-track-4.xml copy .\src\drivers\astigot\1\qualifying\e-track-4.xml .\runtime\drivers\astigot\1\qualifying\e-track-4.xml
if exist .\src\drivers\astigot\1\qualifying\e-track-6.xml copy .\src\drivers\astigot\1\qualifying\e-track-6.xml .\runtime\drivers\astigot\1\qualifying\e-track-6.xml
if exist .\src\drivers\astigot\1\qualifying\g-track-2.xml copy .\src\drivers\astigot\1\qualifying\g-track-2.xml .\runtime\drivers\astigot\1\qualifying\g-track-2.xml
if exist .\src\drivers\astigot\1\qualifying\g-track-3.xml copy .\src\drivers\astigot\1\qualifying\g-track-3.xml .\runtime\drivers\astigot\1\qualifying\g-track-3.xml
if exist .\src\drivers\astigot\1\qualifying\wheel-1.xml copy .\src\drivers\astigot\1\qualifying\wheel-1.xml .\runtime\drivers\astigot\1\qualifying\wheel-1.xml

if exist .\src\drivers\astigot\1\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\1\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\1\race\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\1\race\*.* call .\create_dir .\runtime\drivers\astigot\1
if exist .\src\drivers\astigot\1\race\*.* call .\create_dir .\runtime\drivers\astigot\1\race
if exist .\src\drivers\astigot\1\race\aalborg.xml copy .\src\drivers\astigot\1\race\aalborg.xml .\runtime\drivers\astigot\1\race\aalborg.xml
if exist .\src\drivers\astigot\1\race\alpine-1.xml copy .\src\drivers\astigot\1\race\alpine-1.xml .\runtime\drivers\astigot\1\race\alpine-1.xml
if exist .\src\drivers\astigot\1\race\eroad.xml copy .\src\drivers\astigot\1\race\eroad.xml .\runtime\drivers\astigot\1\race\eroad.xml
if exist .\src\drivers\astigot\1\race\e-track-1.xml copy .\src\drivers\astigot\1\race\e-track-1.xml .\runtime\drivers\astigot\1\race\e-track-1.xml
if exist .\src\drivers\astigot\1\race\e-track-2.xml copy .\src\drivers\astigot\1\race\e-track-2.xml .\runtime\drivers\astigot\1\race\e-track-2.xml
if exist .\src\drivers\astigot\1\race\e-track-3.xml copy .\src\drivers\astigot\1\race\e-track-3.xml .\runtime\drivers\astigot\1\race\e-track-3.xml
if exist .\src\drivers\astigot\1\race\e-track-4.xml copy .\src\drivers\astigot\1\race\e-track-4.xml .\runtime\drivers\astigot\1\race\e-track-4.xml
if exist .\src\drivers\astigot\1\race\e-track-6.xml copy .\src\drivers\astigot\1\race\e-track-6.xml .\runtime\drivers\astigot\1\race\e-track-6.xml
if exist .\src\drivers\astigot\1\race\g-track-2.xml copy .\src\drivers\astigot\1\race\g-track-2.xml .\runtime\drivers\astigot\1\race\g-track-2.xml
if exist .\src\drivers\astigot\1\race\g-track-3.xml copy .\src\drivers\astigot\1\race\g-track-3.xml .\runtime\drivers\astigot\1\race\g-track-3.xml
if exist .\src\drivers\astigot\1\race\wheel-1.xml copy .\src\drivers\astigot\1\race\wheel-1.xml .\runtime\drivers\astigot\1\race\wheel-1.xml

if exist .\src\drivers\astigot\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\1\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\1\*.* call .\create_dir .\runtime\drivers\astigot\1
if exist .\src\drivers\astigot\1\default.xml copy .\src\drivers\astigot\1\default.xml .\runtime\drivers\astigot\1\default.xml
if exist .\src\drivers\astigot\1\viper-gts-r.rgb copy .\src\drivers\astigot\1\viper-gts-r.rgb .\runtime\drivers\astigot\1\viper-gts-r.rgb

if exist .\src\drivers\astigot\2\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\2\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\2\practice\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\2\practice\*.* call .\create_dir .\runtime\drivers\astigot\2
if exist .\src\drivers\astigot\2\practice\*.* call .\create_dir .\runtime\drivers\astigot\2\practice
if exist .\src\drivers\astigot\2\practice\aalborg.xml copy .\src\drivers\astigot\2\practice\aalborg.xml .\runtime\drivers\astigot\2\practice\aalborg.xml
if exist .\src\drivers\astigot\2\practice\alpine-1.xml copy .\src\drivers\astigot\2\practice\alpine-1.xml .\runtime\drivers\astigot\2\practice\alpine-1.xml
if exist .\src\drivers\astigot\2\practice\eroad.xml copy .\src\drivers\astigot\2\practice\eroad.xml .\runtime\drivers\astigot\2\practice\eroad.xml
if exist .\src\drivers\astigot\2\practice\e-track-1.xml copy .\src\drivers\astigot\2\practice\e-track-1.xml .\runtime\drivers\astigot\2\practice\e-track-1.xml
if exist .\src\drivers\astigot\2\practice\e-track-2.xml copy .\src\drivers\astigot\2\practice\e-track-2.xml .\runtime\drivers\astigot\2\practice\e-track-2.xml
if exist .\src\drivers\astigot\2\practice\e-track-3.xml copy .\src\drivers\astigot\2\practice\e-track-3.xml .\runtime\drivers\astigot\2\practice\e-track-3.xml
if exist .\src\drivers\astigot\2\practice\e-track-4.xml copy .\src\drivers\astigot\2\practice\e-track-4.xml .\runtime\drivers\astigot\2\practice\e-track-4.xml
if exist .\src\drivers\astigot\2\practice\e-track-6.xml copy .\src\drivers\astigot\2\practice\e-track-6.xml .\runtime\drivers\astigot\2\practice\e-track-6.xml
if exist .\src\drivers\astigot\2\practice\g-track-2.xml copy .\src\drivers\astigot\2\practice\g-track-2.xml .\runtime\drivers\astigot\2\practice\g-track-2.xml
if exist .\src\drivers\astigot\2\practice\g-track-3.xml copy .\src\drivers\astigot\2\practice\g-track-3.xml .\runtime\drivers\astigot\2\practice\g-track-3.xml
if exist .\src\drivers\astigot\2\practice\wheel-1.xml copy .\src\drivers\astigot\2\practice\wheel-1.xml .\runtime\drivers\astigot\2\practice\wheel-1.xml

if exist .\src\drivers\astigot\2\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\2\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\2\qualifying\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\2\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\2
if exist .\src\drivers\astigot\2\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\2\qualifying
if exist .\src\drivers\astigot\2\qualifying\aalborg.xml copy .\src\drivers\astigot\2\qualifying\aalborg.xml .\runtime\drivers\astigot\2\qualifying\aalborg.xml
if exist .\src\drivers\astigot\2\qualifying\alpine-1.xml copy .\src\drivers\astigot\2\qualifying\alpine-1.xml .\runtime\drivers\astigot\2\qualifying\alpine-1.xml
if exist .\src\drivers\astigot\2\qualifying\eroad.xml copy .\src\drivers\astigot\2\qualifying\eroad.xml .\runtime\drivers\astigot\2\qualifying\eroad.xml
if exist .\src\drivers\astigot\2\qualifying\e-track-1.xml copy .\src\drivers\astigot\2\qualifying\e-track-1.xml .\runtime\drivers\astigot\2\qualifying\e-track-1.xml
if exist .\src\drivers\astigot\2\qualifying\e-track-2.xml copy .\src\drivers\astigot\2\qualifying\e-track-2.xml .\runtime\drivers\astigot\2\qualifying\e-track-2.xml
if exist .\src\drivers\astigot\2\qualifying\e-track-3.xml copy .\src\drivers\astigot\2\qualifying\e-track-3.xml .\runtime\drivers\astigot\2\qualifying\e-track-3.xml
if exist .\src\drivers\astigot\2\qualifying\e-track-4.xml copy .\src\drivers\astigot\2\qualifying\e-track-4.xml .\runtime\drivers\astigot\2\qualifying\e-track-4.xml
if exist .\src\drivers\astigot\2\qualifying\e-track-6.xml copy .\src\drivers\astigot\2\qualifying\e-track-6.xml .\runtime\drivers\astigot\2\qualifying\e-track-6.xml
if exist .\src\drivers\astigot\2\qualifying\g-track-2.xml copy .\src\drivers\astigot\2\qualifying\g-track-2.xml .\runtime\drivers\astigot\2\qualifying\g-track-2.xml
if exist .\src\drivers\astigot\2\qualifying\g-track-3.xml copy .\src\drivers\astigot\2\qualifying\g-track-3.xml .\runtime\drivers\astigot\2\qualifying\g-track-3.xml
if exist .\src\drivers\astigot\2\qualifying\wheel-1.xml copy .\src\drivers\astigot\2\qualifying\wheel-1.xml .\runtime\drivers\astigot\2\qualifying\wheel-1.xml

if exist .\src\drivers\astigot\2\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\2\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\2\race\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\2\race\*.* call .\create_dir .\runtime\drivers\astigot\2
if exist .\src\drivers\astigot\2\race\*.* call .\create_dir .\runtime\drivers\astigot\2\race
if exist .\src\drivers\astigot\2\race\aalborg.xml copy .\src\drivers\astigot\2\race\aalborg.xml .\runtime\drivers\astigot\2\race\aalborg.xml
if exist .\src\drivers\astigot\2\race\alpine-1.xml copy .\src\drivers\astigot\2\race\alpine-1.xml .\runtime\drivers\astigot\2\race\alpine-1.xml
if exist .\src\drivers\astigot\2\race\eroad.xml copy .\src\drivers\astigot\2\race\eroad.xml .\runtime\drivers\astigot\2\race\eroad.xml
if exist .\src\drivers\astigot\2\race\e-track-1.xml copy .\src\drivers\astigot\2\race\e-track-1.xml .\runtime\drivers\astigot\2\race\e-track-1.xml
if exist .\src\drivers\astigot\2\race\e-track-2.xml copy .\src\drivers\astigot\2\race\e-track-2.xml .\runtime\drivers\astigot\2\race\e-track-2.xml
if exist .\src\drivers\astigot\2\race\e-track-3.xml copy .\src\drivers\astigot\2\race\e-track-3.xml .\runtime\drivers\astigot\2\race\e-track-3.xml
if exist .\src\drivers\astigot\2\race\e-track-4.xml copy .\src\drivers\astigot\2\race\e-track-4.xml .\runtime\drivers\astigot\2\race\e-track-4.xml
if exist .\src\drivers\astigot\2\race\e-track-6.xml copy .\src\drivers\astigot\2\race\e-track-6.xml .\runtime\drivers\astigot\2\race\e-track-6.xml
if exist .\src\drivers\astigot\2\race\g-track-2.xml copy .\src\drivers\astigot\2\race\g-track-2.xml .\runtime\drivers\astigot\2\race\g-track-2.xml
if exist .\src\drivers\astigot\2\race\g-track-3.xml copy .\src\drivers\astigot\2\race\g-track-3.xml .\runtime\drivers\astigot\2\race\g-track-3.xml
if exist .\src\drivers\astigot\2\race\wheel-1.xml copy .\src\drivers\astigot\2\race\wheel-1.xml .\runtime\drivers\astigot\2\race\wheel-1.xml

if exist .\src\drivers\astigot\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\2\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\2\*.* call .\create_dir .\runtime\drivers\astigot\2
if exist .\src\drivers\astigot\2\default.xml copy .\src\drivers\astigot\2\default.xml .\runtime\drivers\astigot\2\default.xml

if exist .\src\drivers\astigot\3\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\3\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\3\practice\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\3\practice\*.* call .\create_dir .\runtime\drivers\astigot\3
if exist .\src\drivers\astigot\3\practice\*.* call .\create_dir .\runtime\drivers\astigot\3\practice
if exist .\src\drivers\astigot\3\practice\aalborg.xml copy .\src\drivers\astigot\3\practice\aalborg.xml .\runtime\drivers\astigot\3\practice\aalborg.xml
if exist .\src\drivers\astigot\3\practice\alpine-1.xml copy .\src\drivers\astigot\3\practice\alpine-1.xml .\runtime\drivers\astigot\3\practice\alpine-1.xml
if exist .\src\drivers\astigot\3\practice\dirt-1.xml copy .\src\drivers\astigot\3\practice\dirt-1.xml .\runtime\drivers\astigot\3\practice\dirt-1.xml
if exist .\src\drivers\astigot\3\practice\dirt-2.xml copy .\src\drivers\astigot\3\practice\dirt-2.xml .\runtime\drivers\astigot\3\practice\dirt-2.xml
if exist .\src\drivers\astigot\3\practice\dirt-3.xml copy .\src\drivers\astigot\3\practice\dirt-3.xml .\runtime\drivers\astigot\3\practice\dirt-3.xml
if exist .\src\drivers\astigot\3\practice\dirt-4.xml copy .\src\drivers\astigot\3\practice\dirt-4.xml .\runtime\drivers\astigot\3\practice\dirt-4.xml
if exist .\src\drivers\astigot\3\practice\dirt-5.xml copy .\src\drivers\astigot\3\practice\dirt-5.xml .\runtime\drivers\astigot\3\practice\dirt-5.xml
if exist .\src\drivers\astigot\3\practice\dirt-6.xml copy .\src\drivers\astigot\3\practice\dirt-6.xml .\runtime\drivers\astigot\3\practice\dirt-6.xml
if exist .\src\drivers\astigot\3\practice\eroad.xml copy .\src\drivers\astigot\3\practice\eroad.xml .\runtime\drivers\astigot\3\practice\eroad.xml
if exist .\src\drivers\astigot\3\practice\e-track-1.xml copy .\src\drivers\astigot\3\practice\e-track-1.xml .\runtime\drivers\astigot\3\practice\e-track-1.xml
if exist .\src\drivers\astigot\3\practice\e-track-2.xml copy .\src\drivers\astigot\3\practice\e-track-2.xml .\runtime\drivers\astigot\3\practice\e-track-2.xml
if exist .\src\drivers\astigot\3\practice\e-track-3.xml copy .\src\drivers\astigot\3\practice\e-track-3.xml .\runtime\drivers\astigot\3\practice\e-track-3.xml
if exist .\src\drivers\astigot\3\practice\e-track-4.xml copy .\src\drivers\astigot\3\practice\e-track-4.xml .\runtime\drivers\astigot\3\practice\e-track-4.xml
if exist .\src\drivers\astigot\3\practice\e-track-6.xml copy .\src\drivers\astigot\3\practice\e-track-6.xml .\runtime\drivers\astigot\3\practice\e-track-6.xml
if exist .\src\drivers\astigot\3\practice\g-track-2.xml copy .\src\drivers\astigot\3\practice\g-track-2.xml .\runtime\drivers\astigot\3\practice\g-track-2.xml
if exist .\src\drivers\astigot\3\practice\g-track-3.xml copy .\src\drivers\astigot\3\practice\g-track-3.xml .\runtime\drivers\astigot\3\practice\g-track-3.xml
if exist .\src\drivers\astigot\3\practice\mixed-1.xml copy .\src\drivers\astigot\3\practice\mixed-1.xml .\runtime\drivers\astigot\3\practice\mixed-1.xml
if exist .\src\drivers\astigot\3\practice\mixed-2.xml copy .\src\drivers\astigot\3\practice\mixed-2.xml .\runtime\drivers\astigot\3\practice\mixed-2.xml
if exist .\src\drivers\astigot\3\practice\wheel-1.xml copy .\src\drivers\astigot\3\practice\wheel-1.xml .\runtime\drivers\astigot\3\practice\wheel-1.xml

if exist .\src\drivers\astigot\3\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\3\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\3\qualifying\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\3\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\3
if exist .\src\drivers\astigot\3\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\3\qualifying
if exist .\src\drivers\astigot\3\qualifying\aalborg.xml copy .\src\drivers\astigot\3\qualifying\aalborg.xml .\runtime\drivers\astigot\3\qualifying\aalborg.xml
if exist .\src\drivers\astigot\3\qualifying\alpine-1.xml copy .\src\drivers\astigot\3\qualifying\alpine-1.xml .\runtime\drivers\astigot\3\qualifying\alpine-1.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-1.xml copy .\src\drivers\astigot\3\qualifying\dirt-1.xml .\runtime\drivers\astigot\3\qualifying\dirt-1.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-2.xml copy .\src\drivers\astigot\3\qualifying\dirt-2.xml .\runtime\drivers\astigot\3\qualifying\dirt-2.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-3.xml copy .\src\drivers\astigot\3\qualifying\dirt-3.xml .\runtime\drivers\astigot\3\qualifying\dirt-3.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-4.xml copy .\src\drivers\astigot\3\qualifying\dirt-4.xml .\runtime\drivers\astigot\3\qualifying\dirt-4.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-5.xml copy .\src\drivers\astigot\3\qualifying\dirt-5.xml .\runtime\drivers\astigot\3\qualifying\dirt-5.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-6.xml copy .\src\drivers\astigot\3\qualifying\dirt-6.xml .\runtime\drivers\astigot\3\qualifying\dirt-6.xml
if exist .\src\drivers\astigot\3\qualifying\eroad.xml copy .\src\drivers\astigot\3\qualifying\eroad.xml .\runtime\drivers\astigot\3\qualifying\eroad.xml
if exist .\src\drivers\astigot\3\qualifying\e-track-1.xml copy .\src\drivers\astigot\3\qualifying\e-track-1.xml .\runtime\drivers\astigot\3\qualifying\e-track-1.xml
if exist .\src\drivers\astigot\3\qualifying\e-track-2.xml copy .\src\drivers\astigot\3\qualifying\e-track-2.xml .\runtime\drivers\astigot\3\qualifying\e-track-2.xml
if exist .\src\drivers\astigot\3\qualifying\e-track-3.xml copy .\src\drivers\astigot\3\qualifying\e-track-3.xml .\runtime\drivers\astigot\3\qualifying\e-track-3.xml
if exist .\src\drivers\astigot\3\qualifying\e-track-4.xml copy .\src\drivers\astigot\3\qualifying\e-track-4.xml .\runtime\drivers\astigot\3\qualifying\e-track-4.xml
if exist .\src\drivers\astigot\3\qualifying\e-track-6.xml copy .\src\drivers\astigot\3\qualifying\e-track-6.xml .\runtime\drivers\astigot\3\qualifying\e-track-6.xml
if exist .\src\drivers\astigot\3\qualifying\g-track-2.xml copy .\src\drivers\astigot\3\qualifying\g-track-2.xml .\runtime\drivers\astigot\3\qualifying\g-track-2.xml
if exist .\src\drivers\astigot\3\qualifying\g-track-3.xml copy .\src\drivers\astigot\3\qualifying\g-track-3.xml .\runtime\drivers\astigot\3\qualifying\g-track-3.xml
if exist .\src\drivers\astigot\3\qualifying\mixed-1.xml copy .\src\drivers\astigot\3\qualifying\mixed-1.xml .\runtime\drivers\astigot\3\qualifying\mixed-1.xml
if exist .\src\drivers\astigot\3\qualifying\mixed-2.xml copy .\src\drivers\astigot\3\qualifying\mixed-2.xml .\runtime\drivers\astigot\3\qualifying\mixed-2.xml
if exist .\src\drivers\astigot\3\qualifying\wheel-1.xml copy .\src\drivers\astigot\3\qualifying\wheel-1.xml .\runtime\drivers\astigot\3\qualifying\wheel-1.xml

if exist .\src\drivers\astigot\3\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\3\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\3\race\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\3\race\*.* call .\create_dir .\runtime\drivers\astigot\3
if exist .\src\drivers\astigot\3\race\*.* call .\create_dir .\runtime\drivers\astigot\3\race
if exist .\src\drivers\astigot\3\race\aalborg.xml copy .\src\drivers\astigot\3\race\aalborg.xml .\runtime\drivers\astigot\3\race\aalborg.xml
if exist .\src\drivers\astigot\3\race\alpine-1.xml copy .\src\drivers\astigot\3\race\alpine-1.xml .\runtime\drivers\astigot\3\race\alpine-1.xml
if exist .\src\drivers\astigot\3\race\dirt-1.xml copy .\src\drivers\astigot\3\race\dirt-1.xml .\runtime\drivers\astigot\3\race\dirt-1.xml
if exist .\src\drivers\astigot\3\race\dirt-2.xml copy .\src\drivers\astigot\3\race\dirt-2.xml .\runtime\drivers\astigot\3\race\dirt-2.xml
if exist .\src\drivers\astigot\3\race\dirt-3.xml copy .\src\drivers\astigot\3\race\dirt-3.xml .\runtime\drivers\astigot\3\race\dirt-3.xml
if exist .\src\drivers\astigot\3\race\dirt-4.xml copy .\src\drivers\astigot\3\race\dirt-4.xml .\runtime\drivers\astigot\3\race\dirt-4.xml
if exist .\src\drivers\astigot\3\race\dirt-5.xml copy .\src\drivers\astigot\3\race\dirt-5.xml .\runtime\drivers\astigot\3\race\dirt-5.xml
if exist .\src\drivers\astigot\3\race\dirt-6.xml copy .\src\drivers\astigot\3\race\dirt-6.xml .\runtime\drivers\astigot\3\race\dirt-6.xml
if exist .\src\drivers\astigot\3\race\eroad.xml copy .\src\drivers\astigot\3\race\eroad.xml .\runtime\drivers\astigot\3\race\eroad.xml
if exist .\src\drivers\astigot\3\race\e-track-1.xml copy .\src\drivers\astigot\3\race\e-track-1.xml .\runtime\drivers\astigot\3\race\e-track-1.xml
if exist .\src\drivers\astigot\3\race\e-track-2.xml copy .\src\drivers\astigot\3\race\e-track-2.xml .\runtime\drivers\astigot\3\race\e-track-2.xml
if exist .\src\drivers\astigot\3\race\e-track-3.xml copy .\src\drivers\astigot\3\race\e-track-3.xml .\runtime\drivers\astigot\3\race\e-track-3.xml
if exist .\src\drivers\astigot\3\race\e-track-4.xml copy .\src\drivers\astigot\3\race\e-track-4.xml .\runtime\drivers\astigot\3\race\e-track-4.xml
if exist .\src\drivers\astigot\3\race\e-track-6.xml copy .\src\drivers\astigot\3\race\e-track-6.xml .\runtime\drivers\astigot\3\race\e-track-6.xml
if exist .\src\drivers\astigot\3\race\g-track-2.xml copy .\src\drivers\astigot\3\race\g-track-2.xml .\runtime\drivers\astigot\3\race\g-track-2.xml
if exist .\src\drivers\astigot\3\race\g-track-3.xml copy .\src\drivers\astigot\3\race\g-track-3.xml .\runtime\drivers\astigot\3\race\g-track-3.xml
if exist .\src\drivers\astigot\3\race\mixed-1.xml copy .\src\drivers\astigot\3\race\mixed-1.xml .\runtime\drivers\astigot\3\race\mixed-1.xml
if exist .\src\drivers\astigot\3\race\mixed-2.xml copy .\src\drivers\astigot\3\race\mixed-2.xml .\runtime\drivers\astigot\3\race\mixed-2.xml
if exist .\src\drivers\astigot\3\race\wheel-1.xml copy .\src\drivers\astigot\3\race\wheel-1.xml .\runtime\drivers\astigot\3\race\wheel-1.xml

if exist .\src\drivers\astigot\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\3\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\3\*.* call .\create_dir .\runtime\drivers\astigot\3
if exist .\src\drivers\astigot\3\default.xml copy .\src\drivers\astigot\3\default.xml .\runtime\drivers\astigot\3\default.xml
if exist .\src\drivers\astigot\3\buggy.rgb copy .\src\drivers\astigot\3\buggy.rgb .\runtime\drivers\astigot\3\buggy.rgb

if exist .\src\drivers\astigot\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\astigot.xml copy .\src\drivers\astigot\astigot.xml .\runtime\drivers\astigot\astigot.xml
if exist .\src\drivers\astigot\logo.rgb copy .\src\drivers\astigot\logo.rgb .\runtime\drivers\astigot\logo.rgb

if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers\berniw\1
if exist .\src\drivers\berniw\1\cg-nascar-rwd.rgb copy .\src\drivers\berniw\1\cg-nascar-rwd.rgb .\runtime\drivers\berniw\1\cg-nascar-rwd.rgb
if exist .\src\drivers\berniw\1\aalborg.xml copy .\src\drivers\berniw\1\aalborg.xml .\runtime\drivers\berniw\1\aalborg.xml
if exist .\src\drivers\berniw\1\alpine-1.xml copy .\src\drivers\berniw\1\alpine-1.xml .\runtime\drivers\berniw\1\alpine-1.xml
if exist .\src\drivers\berniw\1\a-speedway.xml copy .\src\drivers\berniw\1\a-speedway.xml .\runtime\drivers\berniw\1\a-speedway.xml
if exist .\src\drivers\berniw\1\dirt-1.xml copy .\src\drivers\berniw\1\dirt-1.xml .\runtime\drivers\berniw\1\dirt-1.xml
if exist .\src\drivers\berniw\1\dirt-2.xml copy .\src\drivers\berniw\1\dirt-2.xml .\runtime\drivers\berniw\1\dirt-2.xml
if exist .\src\drivers\berniw\1\dirt-3.xml copy .\src\drivers\berniw\1\dirt-3.xml .\runtime\drivers\berniw\1\dirt-3.xml
if exist .\src\drivers\berniw\1\dirt-4.xml copy .\src\drivers\berniw\1\dirt-4.xml .\runtime\drivers\berniw\1\dirt-4.xml
if exist .\src\drivers\berniw\1\dirt-5.xml copy .\src\drivers\berniw\1\dirt-5.xml .\runtime\drivers\berniw\1\dirt-5.xml
if exist .\src\drivers\berniw\1\dirt-6.xml copy .\src\drivers\berniw\1\dirt-6.xml .\runtime\drivers\berniw\1\dirt-6.xml
if exist .\src\drivers\berniw\1\eroad.xml copy .\src\drivers\berniw\1\eroad.xml .\runtime\drivers\berniw\1\eroad.xml
if exist .\src\drivers\berniw\1\e-track-1.xml copy .\src\drivers\berniw\1\e-track-1.xml .\runtime\drivers\berniw\1\e-track-1.xml
if exist .\src\drivers\berniw\1\e-track-2.xml copy .\src\drivers\berniw\1\e-track-2.xml .\runtime\drivers\berniw\1\e-track-2.xml
if exist .\src\drivers\berniw\1\e-track-3.xml copy .\src\drivers\berniw\1\e-track-3.xml .\runtime\drivers\berniw\1\e-track-3.xml
if exist .\src\drivers\berniw\1\e-track-4.xml copy .\src\drivers\berniw\1\e-track-4.xml .\runtime\drivers\berniw\1\e-track-4.xml
if exist .\src\drivers\berniw\1\e-track-5.xml copy .\src\drivers\berniw\1\e-track-5.xml .\runtime\drivers\berniw\1\e-track-5.xml
if exist .\src\drivers\berniw\1\e-track-6.xml copy .\src\drivers\berniw\1\e-track-6.xml .\runtime\drivers\berniw\1\e-track-6.xml
if exist .\src\drivers\berniw\1\g-track-1.xml copy .\src\drivers\berniw\1\g-track-1.xml .\runtime\drivers\berniw\1\g-track-1.xml
if exist .\src\drivers\berniw\1\g-track-2.xml copy .\src\drivers\berniw\1\g-track-2.xml .\runtime\drivers\berniw\1\g-track-2.xml
if exist .\src\drivers\berniw\1\g-track-3.xml copy .\src\drivers\berniw\1\g-track-3.xml .\runtime\drivers\berniw\1\g-track-3.xml
if exist .\src\drivers\berniw\1\michigan.xml copy .\src\drivers\berniw\1\michigan.xml .\runtime\drivers\berniw\1\michigan.xml
if exist .\src\drivers\berniw\1\mixed-1.xml copy .\src\drivers\berniw\1\mixed-1.xml .\runtime\drivers\berniw\1\mixed-1.xml
if exist .\src\drivers\berniw\1\mixed-2.xml copy .\src\drivers\berniw\1\mixed-2.xml .\runtime\drivers\berniw\1\mixed-2.xml
if exist .\src\drivers\berniw\1\spring.xml copy .\src\drivers\berniw\1\spring.xml .\runtime\drivers\berniw\1\spring.xml
if exist .\src\drivers\berniw\1\wheel-1.xml copy .\src\drivers\berniw\1\wheel-1.xml .\runtime\drivers\berniw\1\wheel-1.xml

if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers\berniw\10
if exist .\src\drivers\berniw\10\buggy.rgb copy .\src\drivers\berniw\10\buggy.rgb .\runtime\drivers\berniw\10\buggy.rgb
if exist .\src\drivers\berniw\10\aalborg.xml copy .\src\drivers\berniw\10\aalborg.xml .\runtime\drivers\berniw\10\aalborg.xml
if exist .\src\drivers\berniw\10\alpine-1.xml copy .\src\drivers\berniw\10\alpine-1.xml .\runtime\drivers\berniw\10\alpine-1.xml
if exist .\src\drivers\berniw\10\a-speedway.xml copy .\src\drivers\berniw\10\a-speedway.xml .\runtime\drivers\berniw\10\a-speedway.xml
if exist .\src\drivers\berniw\10\dirt-1.xml copy .\src\drivers\berniw\10\dirt-1.xml .\runtime\drivers\berniw\10\dirt-1.xml
if exist .\src\drivers\berniw\10\dirt-2.xml copy .\src\drivers\berniw\10\dirt-2.xml .\runtime\drivers\berniw\10\dirt-2.xml
if exist .\src\drivers\berniw\10\dirt-3.xml copy .\src\drivers\berniw\10\dirt-3.xml .\runtime\drivers\berniw\10\dirt-3.xml
if exist .\src\drivers\berniw\10\dirt-4.xml copy .\src\drivers\berniw\10\dirt-4.xml .\runtime\drivers\berniw\10\dirt-4.xml
if exist .\src\drivers\berniw\10\dirt-5.xml copy .\src\drivers\berniw\10\dirt-5.xml .\runtime\drivers\berniw\10\dirt-5.xml
if exist .\src\drivers\berniw\10\dirt-6.xml copy .\src\drivers\berniw\10\dirt-6.xml .\runtime\drivers\berniw\10\dirt-6.xml
if exist .\src\drivers\berniw\10\eroad.xml copy .\src\drivers\berniw\10\eroad.xml .\runtime\drivers\berniw\10\eroad.xml
if exist .\src\drivers\berniw\10\e-track-1.xml copy .\src\drivers\berniw\10\e-track-1.xml .\runtime\drivers\berniw\10\e-track-1.xml
if exist .\src\drivers\berniw\10\e-track-2.xml copy .\src\drivers\berniw\10\e-track-2.xml .\runtime\drivers\berniw\10\e-track-2.xml
if exist .\src\drivers\berniw\10\e-track-3.xml copy .\src\drivers\berniw\10\e-track-3.xml .\runtime\drivers\berniw\10\e-track-3.xml
if exist .\src\drivers\berniw\10\e-track-4.xml copy .\src\drivers\berniw\10\e-track-4.xml .\runtime\drivers\berniw\10\e-track-4.xml
if exist .\src\drivers\berniw\10\e-track-5.xml copy .\src\drivers\berniw\10\e-track-5.xml .\runtime\drivers\berniw\10\e-track-5.xml
if exist .\src\drivers\berniw\10\e-track-6.xml copy .\src\drivers\berniw\10\e-track-6.xml .\runtime\drivers\berniw\10\e-track-6.xml
if exist .\src\drivers\berniw\10\g-track-1.xml copy .\src\drivers\berniw\10\g-track-1.xml .\runtime\drivers\berniw\10\g-track-1.xml
if exist .\src\drivers\berniw\10\g-track-2.xml copy .\src\drivers\berniw\10\g-track-2.xml .\runtime\drivers\berniw\10\g-track-2.xml
if exist .\src\drivers\berniw\10\g-track-3.xml copy .\src\drivers\berniw\10\g-track-3.xml .\runtime\drivers\berniw\10\g-track-3.xml
if exist .\src\drivers\berniw\10\michigan.xml copy .\src\drivers\berniw\10\michigan.xml .\runtime\drivers\berniw\10\michigan.xml
if exist .\src\drivers\berniw\10\mixed-1.xml copy .\src\drivers\berniw\10\mixed-1.xml .\runtime\drivers\berniw\10\mixed-1.xml
if exist .\src\drivers\berniw\10\mixed-2.xml copy .\src\drivers\berniw\10\mixed-2.xml .\runtime\drivers\berniw\10\mixed-2.xml
if exist .\src\drivers\berniw\10\spring.xml copy .\src\drivers\berniw\10\spring.xml .\runtime\drivers\berniw\10\spring.xml
if exist .\src\drivers\berniw\10\wheel-1.xml copy .\src\drivers\berniw\10\wheel-1.xml .\runtime\drivers\berniw\10\wheel-1.xml

if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers\berniw\2
if exist .\src\drivers\berniw\2\cg-nascar-rwd.rgb copy .\src\drivers\berniw\2\cg-nascar-rwd.rgb .\runtime\drivers\berniw\2\cg-nascar-rwd.rgb
if exist .\src\drivers\berniw\2\aalborg.xml copy .\src\drivers\berniw\2\aalborg.xml .\runtime\drivers\berniw\2\aalborg.xml
if exist .\src\drivers\berniw\2\alpine-1.xml copy .\src\drivers\berniw\2\alpine-1.xml .\runtime\drivers\berniw\2\alpine-1.xml
if exist .\src\drivers\berniw\2\a-speedway.xml copy .\src\drivers\berniw\2\a-speedway.xml .\runtime\drivers\berniw\2\a-speedway.xml
if exist .\src\drivers\berniw\2\dirt-1.xml copy .\src\drivers\berniw\2\dirt-1.xml .\runtime\drivers\berniw\2\dirt-1.xml
if exist .\src\drivers\berniw\2\dirt-2.xml copy .\src\drivers\berniw\2\dirt-2.xml .\runtime\drivers\berniw\2\dirt-2.xml
if exist .\src\drivers\berniw\2\dirt-3.xml copy .\src\drivers\berniw\2\dirt-3.xml .\runtime\drivers\berniw\2\dirt-3.xml
if exist .\src\drivers\berniw\2\dirt-4.xml copy .\src\drivers\berniw\2\dirt-4.xml .\runtime\drivers\berniw\2\dirt-4.xml
if exist .\src\drivers\berniw\2\dirt-5.xml copy .\src\drivers\berniw\2\dirt-5.xml .\runtime\drivers\berniw\2\dirt-5.xml
if exist .\src\drivers\berniw\2\dirt-6.xml copy .\src\drivers\berniw\2\dirt-6.xml .\runtime\drivers\berniw\2\dirt-6.xml
if exist .\src\drivers\berniw\2\eroad.xml copy .\src\drivers\berniw\2\eroad.xml .\runtime\drivers\berniw\2\eroad.xml
if exist .\src\drivers\berniw\2\e-track-1.xml copy .\src\drivers\berniw\2\e-track-1.xml .\runtime\drivers\berniw\2\e-track-1.xml
if exist .\src\drivers\berniw\2\e-track-2.xml copy .\src\drivers\berniw\2\e-track-2.xml .\runtime\drivers\berniw\2\e-track-2.xml
if exist .\src\drivers\berniw\2\e-track-3.xml copy .\src\drivers\berniw\2\e-track-3.xml .\runtime\drivers\berniw\2\e-track-3.xml
if exist .\src\drivers\berniw\2\e-track-4.xml copy .\src\drivers\berniw\2\e-track-4.xml .\runtime\drivers\berniw\2\e-track-4.xml
if exist .\src\drivers\berniw\2\e-track-5.xml copy .\src\drivers\berniw\2\e-track-5.xml .\runtime\drivers\berniw\2\e-track-5.xml
if exist .\src\drivers\berniw\2\e-track-6.xml copy .\src\drivers\berniw\2\e-track-6.xml .\runtime\drivers\berniw\2\e-track-6.xml
if exist .\src\drivers\berniw\2\g-track-1.xml copy .\src\drivers\berniw\2\g-track-1.xml .\runtime\drivers\berniw\2\g-track-1.xml
if exist .\src\drivers\berniw\2\g-track-2.xml copy .\src\drivers\berniw\2\g-track-2.xml .\runtime\drivers\berniw\2\g-track-2.xml
if exist .\src\drivers\berniw\2\g-track-3.xml copy .\src\drivers\berniw\2\g-track-3.xml .\runtime\drivers\berniw\2\g-track-3.xml
if exist .\src\drivers\berniw\2\michigan.xml copy .\src\drivers\berniw\2\michigan.xml .\runtime\drivers\berniw\2\michigan.xml
if exist .\src\drivers\berniw\2\mixed-1.xml copy .\src\drivers\berniw\2\mixed-1.xml .\runtime\drivers\berniw\2\mixed-1.xml
if exist .\src\drivers\berniw\2\mixed-2.xml copy .\src\drivers\berniw\2\mixed-2.xml .\runtime\drivers\berniw\2\mixed-2.xml
if exist .\src\drivers\berniw\2\spring.xml copy .\src\drivers\berniw\2\spring.xml .\runtime\drivers\berniw\2\spring.xml
if exist .\src\drivers\berniw\2\wheel-1.xml copy .\src\drivers\berniw\2\wheel-1.xml .\runtime\drivers\berniw\2\wheel-1.xml

if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers\berniw\3
if exist .\src\drivers\berniw\3\porsche-gt1.rgb copy .\src\drivers\berniw\3\porsche-gt1.rgb .\runtime\drivers\berniw\3\porsche-gt1.rgb
if exist .\src\drivers\berniw\3\aalborg.xml copy .\src\drivers\berniw\3\aalborg.xml .\runtime\drivers\berniw\3\aalborg.xml
if exist .\src\drivers\berniw\3\alpine-1.xml copy .\src\drivers\berniw\3\alpine-1.xml .\runtime\drivers\berniw\3\alpine-1.xml
if exist .\src\drivers\berniw\3\a-speedway.xml copy .\src\drivers\berniw\3\a-speedway.xml .\runtime\drivers\berniw\3\a-speedway.xml
if exist .\src\drivers\berniw\3\dirt-1.xml copy .\src\drivers\berniw\3\dirt-1.xml .\runtime\drivers\berniw\3\dirt-1.xml
if exist .\src\drivers\berniw\3\dirt-2.xml copy .\src\drivers\berniw\3\dirt-2.xml .\runtime\drivers\berniw\3\dirt-2.xml
if exist .\src\drivers\berniw\3\dirt-3.xml copy .\src\drivers\berniw\3\dirt-3.xml .\runtime\drivers\berniw\3\dirt-3.xml
if exist .\src\drivers\berniw\3\dirt-4.xml copy .\src\drivers\berniw\3\dirt-4.xml .\runtime\drivers\berniw\3\dirt-4.xml
if exist .\src\drivers\berniw\3\dirt-5.xml copy .\src\drivers\berniw\3\dirt-5.xml .\runtime\drivers\berniw\3\dirt-5.xml
if exist .\src\drivers\berniw\3\dirt-6.xml copy .\src\drivers\berniw\3\dirt-6.xml .\runtime\drivers\berniw\3\dirt-6.xml
if exist .\src\drivers\berniw\3\eroad.xml copy .\src\drivers\berniw\3\eroad.xml .\runtime\drivers\berniw\3\eroad.xml
if exist .\src\drivers\berniw\3\e-track-1.xml copy .\src\drivers\berniw\3\e-track-1.xml .\runtime\drivers\berniw\3\e-track-1.xml
if exist .\src\drivers\berniw\3\e-track-2.xml copy .\src\drivers\berniw\3\e-track-2.xml .\runtime\drivers\berniw\3\e-track-2.xml
if exist .\src\drivers\berniw\3\e-track-3.xml copy .\src\drivers\berniw\3\e-track-3.xml .\runtime\drivers\berniw\3\e-track-3.xml
if exist .\src\drivers\berniw\3\e-track-4.xml copy .\src\drivers\berniw\3\e-track-4.xml .\runtime\drivers\berniw\3\e-track-4.xml
if exist .\src\drivers\berniw\3\e-track-5.xml copy .\src\drivers\berniw\3\e-track-5.xml .\runtime\drivers\berniw\3\e-track-5.xml
if exist .\src\drivers\berniw\3\e-track-6.xml copy .\src\drivers\berniw\3\e-track-6.xml .\runtime\drivers\berniw\3\e-track-6.xml
if exist .\src\drivers\berniw\3\g-track-1.xml copy .\src\drivers\berniw\3\g-track-1.xml .\runtime\drivers\berniw\3\g-track-1.xml
if exist .\src\drivers\berniw\3\g-track-2.xml copy .\src\drivers\berniw\3\g-track-2.xml .\runtime\drivers\berniw\3\g-track-2.xml
if exist .\src\drivers\berniw\3\g-track-3.xml copy .\src\drivers\berniw\3\g-track-3.xml .\runtime\drivers\berniw\3\g-track-3.xml
if exist .\src\drivers\berniw\3\michigan.xml copy .\src\drivers\berniw\3\michigan.xml .\runtime\drivers\berniw\3\michigan.xml
if exist .\src\drivers\berniw\3\mixed-1.xml copy .\src\drivers\berniw\3\mixed-1.xml .\runtime\drivers\berniw\3\mixed-1.xml
if exist .\src\drivers\berniw\3\mixed-2.xml copy .\src\drivers\berniw\3\mixed-2.xml .\runtime\drivers\berniw\3\mixed-2.xml
if exist .\src\drivers\berniw\3\spring.xml copy .\src\drivers\berniw\3\spring.xml .\runtime\drivers\berniw\3\spring.xml
if exist .\src\drivers\berniw\3\wheel-1.xml copy .\src\drivers\berniw\3\wheel-1.xml .\runtime\drivers\berniw\3\wheel-1.xml

if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers\berniw\4
if exist .\src\drivers\berniw\4\viper-gts-r.rgb copy .\src\drivers\berniw\4\viper-gts-r.rgb .\runtime\drivers\berniw\4\viper-gts-r.rgb
if exist .\src\drivers\berniw\4\aalborg.xml copy .\src\drivers\berniw\4\aalborg.xml .\runtime\drivers\berniw\4\aalborg.xml
if exist .\src\drivers\berniw\4\alpine-1.xml copy .\src\drivers\berniw\4\alpine-1.xml .\runtime\drivers\berniw\4\alpine-1.xml
if exist .\src\drivers\berniw\4\a-speedway.xml copy .\src\drivers\berniw\4\a-speedway.xml .\runtime\drivers\berniw\4\a-speedway.xml
if exist .\src\drivers\berniw\4\dirt-1.xml copy .\src\drivers\berniw\4\dirt-1.xml .\runtime\drivers\berniw\4\dirt-1.xml
if exist .\src\drivers\berniw\4\dirt-2.xml copy .\src\drivers\berniw\4\dirt-2.xml .\runtime\drivers\berniw\4\dirt-2.xml
if exist .\src\drivers\berniw\4\dirt-3.xml copy .\src\drivers\berniw\4\dirt-3.xml .\runtime\drivers\berniw\4\dirt-3.xml
if exist .\src\drivers\berniw\4\dirt-4.xml copy .\src\drivers\berniw\4\dirt-4.xml .\runtime\drivers\berniw\4\dirt-4.xml
if exist .\src\drivers\berniw\4\dirt-5.xml copy .\src\drivers\berniw\4\dirt-5.xml .\runtime\drivers\berniw\4\dirt-5.xml
if exist .\src\drivers\berniw\4\dirt-6.xml copy .\src\drivers\berniw\4\dirt-6.xml .\runtime\drivers\berniw\4\dirt-6.xml
if exist .\src\drivers\berniw\4\eroad.xml copy .\src\drivers\berniw\4\eroad.xml .\runtime\drivers\berniw\4\eroad.xml
if exist .\src\drivers\berniw\4\e-track-1.xml copy .\src\drivers\berniw\4\e-track-1.xml .\runtime\drivers\berniw\4\e-track-1.xml
if exist .\src\drivers\berniw\4\e-track-2.xml copy .\src\drivers\berniw\4\e-track-2.xml .\runtime\drivers\berniw\4\e-track-2.xml
if exist .\src\drivers\berniw\4\e-track-3.xml copy .\src\drivers\berniw\4\e-track-3.xml .\runtime\drivers\berniw\4\e-track-3.xml
if exist .\src\drivers\berniw\4\e-track-4.xml copy .\src\drivers\berniw\4\e-track-4.xml .\runtime\drivers\berniw\4\e-track-4.xml
if exist .\src\drivers\berniw\4\e-track-5.xml copy .\src\drivers\berniw\4\e-track-5.xml .\runtime\drivers\berniw\4\e-track-5.xml
if exist .\src\drivers\berniw\4\e-track-6.xml copy .\src\drivers\berniw\4\e-track-6.xml .\runtime\drivers\berniw\4\e-track-6.xml
if exist .\src\drivers\berniw\4\g-track-1.xml copy .\src\drivers\berniw\4\g-track-1.xml .\runtime\drivers\berniw\4\g-track-1.xml
if exist .\src\drivers\berniw\4\g-track-2.xml copy .\src\drivers\berniw\4\g-track-2.xml .\runtime\drivers\berniw\4\g-track-2.xml
if exist .\src\drivers\berniw\4\g-track-3.xml copy .\src\drivers\berniw\4\g-track-3.xml .\runtime\drivers\berniw\4\g-track-3.xml
if exist .\src\drivers\berniw\4\michigan.xml copy .\src\drivers\berniw\4\michigan.xml .\runtime\drivers\berniw\4\michigan.xml
if exist .\src\drivers\berniw\4\mixed-1.xml copy .\src\drivers\berniw\4\mixed-1.xml .\runtime\drivers\berniw\4\mixed-1.xml
if exist .\src\drivers\berniw\4\mixed-2.xml copy .\src\drivers\berniw\4\mixed-2.xml .\runtime\drivers\berniw\4\mixed-2.xml
if exist .\src\drivers\berniw\4\spring.xml copy .\src\drivers\berniw\4\spring.xml .\runtime\drivers\berniw\4\spring.xml
if exist .\src\drivers\berniw\4\wheel-1.xml copy .\src\drivers\berniw\4\wheel-1.xml .\runtime\drivers\berniw\4\wheel-1.xml

if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers\berniw\5
if exist .\src\drivers\berniw\5\gt40.rgb copy .\src\drivers\berniw\5\gt40.rgb .\runtime\drivers\berniw\5\gt40.rgb
if exist .\src\drivers\berniw\5\aalborg.xml copy .\src\drivers\berniw\5\aalborg.xml .\runtime\drivers\berniw\5\aalborg.xml
if exist .\src\drivers\berniw\5\alpine-1.xml copy .\src\drivers\berniw\5\alpine-1.xml .\runtime\drivers\berniw\5\alpine-1.xml
if exist .\src\drivers\berniw\5\a-speedway.xml copy .\src\drivers\berniw\5\a-speedway.xml .\runtime\drivers\berniw\5\a-speedway.xml
if exist .\src\drivers\berniw\5\dirt-1.xml copy .\src\drivers\berniw\5\dirt-1.xml .\runtime\drivers\berniw\5\dirt-1.xml
if exist .\src\drivers\berniw\5\dirt-2.xml copy .\src\drivers\berniw\5\dirt-2.xml .\runtime\drivers\berniw\5\dirt-2.xml
if exist .\src\drivers\berniw\5\dirt-3.xml copy .\src\drivers\berniw\5\dirt-3.xml .\runtime\drivers\berniw\5\dirt-3.xml
if exist .\src\drivers\berniw\5\dirt-4.xml copy .\src\drivers\berniw\5\dirt-4.xml .\runtime\drivers\berniw\5\dirt-4.xml
if exist .\src\drivers\berniw\5\dirt-5.xml copy .\src\drivers\berniw\5\dirt-5.xml .\runtime\drivers\berniw\5\dirt-5.xml
if exist .\src\drivers\berniw\5\dirt-6.xml copy .\src\drivers\berniw\5\dirt-6.xml .\runtime\drivers\berniw\5\dirt-6.xml
if exist .\src\drivers\berniw\5\eroad.xml copy .\src\drivers\berniw\5\eroad.xml .\runtime\drivers\berniw\5\eroad.xml
if exist .\src\drivers\berniw\5\e-track-1.xml copy .\src\drivers\berniw\5\e-track-1.xml .\runtime\drivers\berniw\5\e-track-1.xml
if exist .\src\drivers\berniw\5\e-track-2.xml copy .\src\drivers\berniw\5\e-track-2.xml .\runtime\drivers\berniw\5\e-track-2.xml
if exist .\src\drivers\berniw\5\e-track-3.xml copy .\src\drivers\berniw\5\e-track-3.xml .\runtime\drivers\berniw\5\e-track-3.xml
if exist .\src\drivers\berniw\5\e-track-4.xml copy .\src\drivers\berniw\5\e-track-4.xml .\runtime\drivers\berniw\5\e-track-4.xml
if exist .\src\drivers\berniw\5\e-track-5.xml copy .\src\drivers\berniw\5\e-track-5.xml .\runtime\drivers\berniw\5\e-track-5.xml
if exist .\src\drivers\berniw\5\e-track-6.xml copy .\src\drivers\berniw\5\e-track-6.xml .\runtime\drivers\berniw\5\e-track-6.xml
if exist .\src\drivers\berniw\5\g-track-1.xml copy .\src\drivers\berniw\5\g-track-1.xml .\runtime\drivers\berniw\5\g-track-1.xml
if exist .\src\drivers\berniw\5\g-track-2.xml copy .\src\drivers\berniw\5\g-track-2.xml .\runtime\drivers\berniw\5\g-track-2.xml
if exist .\src\drivers\berniw\5\g-track-3.xml copy .\src\drivers\berniw\5\g-track-3.xml .\runtime\drivers\berniw\5\g-track-3.xml
if exist .\src\drivers\berniw\5\michigan.xml copy .\src\drivers\berniw\5\michigan.xml .\runtime\drivers\berniw\5\michigan.xml
if exist .\src\drivers\berniw\5\mixed-1.xml copy .\src\drivers\berniw\5\mixed-1.xml .\runtime\drivers\berniw\5\mixed-1.xml
if exist .\src\drivers\berniw\5\mixed-2.xml copy .\src\drivers\berniw\5\mixed-2.xml .\runtime\drivers\berniw\5\mixed-2.xml
if exist .\src\drivers\berniw\5\spring.xml copy .\src\drivers\berniw\5\spring.xml .\runtime\drivers\berniw\5\spring.xml
if exist .\src\drivers\berniw\5\wheel-1.xml copy .\src\drivers\berniw\5\wheel-1.xml .\runtime\drivers\berniw\5\wheel-1.xml

if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers\berniw\6
if exist .\src\drivers\berniw\6\155-DTM.rgb copy .\src\drivers\berniw\6\155-DTM.rgb .\runtime\drivers\berniw\6\155-DTM.rgb
if exist .\src\drivers\berniw\6\aalborg.xml copy .\src\drivers\berniw\6\aalborg.xml .\runtime\drivers\berniw\6\aalborg.xml
if exist .\src\drivers\berniw\6\alpine-1.xml copy .\src\drivers\berniw\6\alpine-1.xml .\runtime\drivers\berniw\6\alpine-1.xml
if exist .\src\drivers\berniw\6\a-speedway.xml copy .\src\drivers\berniw\6\a-speedway.xml .\runtime\drivers\berniw\6\a-speedway.xml
if exist .\src\drivers\berniw\6\dirt-1.xml copy .\src\drivers\berniw\6\dirt-1.xml .\runtime\drivers\berniw\6\dirt-1.xml
if exist .\src\drivers\berniw\6\dirt-2.xml copy .\src\drivers\berniw\6\dirt-2.xml .\runtime\drivers\berniw\6\dirt-2.xml
if exist .\src\drivers\berniw\6\dirt-3.xml copy .\src\drivers\berniw\6\dirt-3.xml .\runtime\drivers\berniw\6\dirt-3.xml
if exist .\src\drivers\berniw\6\dirt-4.xml copy .\src\drivers\berniw\6\dirt-4.xml .\runtime\drivers\berniw\6\dirt-4.xml
if exist .\src\drivers\berniw\6\dirt-5.xml copy .\src\drivers\berniw\6\dirt-5.xml .\runtime\drivers\berniw\6\dirt-5.xml
if exist .\src\drivers\berniw\6\dirt-6.xml copy .\src\drivers\berniw\6\dirt-6.xml .\runtime\drivers\berniw\6\dirt-6.xml
if exist .\src\drivers\berniw\6\eroad.xml copy .\src\drivers\berniw\6\eroad.xml .\runtime\drivers\berniw\6\eroad.xml
if exist .\src\drivers\berniw\6\e-track-1.xml copy .\src\drivers\berniw\6\e-track-1.xml .\runtime\drivers\berniw\6\e-track-1.xml
if exist .\src\drivers\berniw\6\e-track-2.xml copy .\src\drivers\berniw\6\e-track-2.xml .\runtime\drivers\berniw\6\e-track-2.xml
if exist .\src\drivers\berniw\6\e-track-3.xml copy .\src\drivers\berniw\6\e-track-3.xml .\runtime\drivers\berniw\6\e-track-3.xml
if exist .\src\drivers\berniw\6\e-track-4.xml copy .\src\drivers\berniw\6\e-track-4.xml .\runtime\drivers\berniw\6\e-track-4.xml
if exist .\src\drivers\berniw\6\e-track-5.xml copy .\src\drivers\berniw\6\e-track-5.xml .\runtime\drivers\berniw\6\e-track-5.xml
if exist .\src\drivers\berniw\6\e-track-6.xml copy .\src\drivers\berniw\6\e-track-6.xml .\runtime\drivers\berniw\6\e-track-6.xml
if exist .\src\drivers\berniw\6\g-track-1.xml copy .\src\drivers\berniw\6\g-track-1.xml .\runtime\drivers\berniw\6\g-track-1.xml
if exist .\src\drivers\berniw\6\g-track-2.xml copy .\src\drivers\berniw\6\g-track-2.xml .\runtime\drivers\berniw\6\g-track-2.xml
if exist .\src\drivers\berniw\6\g-track-3.xml copy .\src\drivers\berniw\6\g-track-3.xml .\runtime\drivers\berniw\6\g-track-3.xml
if exist .\src\drivers\berniw\6\michigan.xml copy .\src\drivers\berniw\6\michigan.xml .\runtime\drivers\berniw\6\michigan.xml
if exist .\src\drivers\berniw\6\mixed-1.xml copy .\src\drivers\berniw\6\mixed-1.xml .\runtime\drivers\berniw\6\mixed-1.xml
if exist .\src\drivers\berniw\6\mixed-2.xml copy .\src\drivers\berniw\6\mixed-2.xml .\runtime\drivers\berniw\6\mixed-2.xml
if exist .\src\drivers\berniw\6\spring.xml copy .\src\drivers\berniw\6\spring.xml .\runtime\drivers\berniw\6\spring.xml
if exist .\src\drivers\berniw\6\wheel-1.xml copy .\src\drivers\berniw\6\wheel-1.xml .\runtime\drivers\berniw\6\wheel-1.xml

if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers\berniw\7
if exist .\src\drivers\berniw\7\lotus-gt1.rgb copy .\src\drivers\berniw\7\lotus-gt1.rgb .\runtime\drivers\berniw\7\lotus-gt1.rgb
if exist .\src\drivers\berniw\7\aalborg.xml copy .\src\drivers\berniw\7\aalborg.xml .\runtime\drivers\berniw\7\aalborg.xml
if exist .\src\drivers\berniw\7\alpine-1.xml copy .\src\drivers\berniw\7\alpine-1.xml .\runtime\drivers\berniw\7\alpine-1.xml
if exist .\src\drivers\berniw\7\a-speedway.xml copy .\src\drivers\berniw\7\a-speedway.xml .\runtime\drivers\berniw\7\a-speedway.xml
if exist .\src\drivers\berniw\7\dirt-1.xml copy .\src\drivers\berniw\7\dirt-1.xml .\runtime\drivers\berniw\7\dirt-1.xml
if exist .\src\drivers\berniw\7\dirt-2.xml copy .\src\drivers\berniw\7\dirt-2.xml .\runtime\drivers\berniw\7\dirt-2.xml
if exist .\src\drivers\berniw\7\dirt-3.xml copy .\src\drivers\berniw\7\dirt-3.xml .\runtime\drivers\berniw\7\dirt-3.xml
if exist .\src\drivers\berniw\7\dirt-4.xml copy .\src\drivers\berniw\7\dirt-4.xml .\runtime\drivers\berniw\7\dirt-4.xml
if exist .\src\drivers\berniw\7\dirt-5.xml copy .\src\drivers\berniw\7\dirt-5.xml .\runtime\drivers\berniw\7\dirt-5.xml
if exist .\src\drivers\berniw\7\dirt-6.xml copy .\src\drivers\berniw\7\dirt-6.xml .\runtime\drivers\berniw\7\dirt-6.xml
if exist .\src\drivers\berniw\7\eroad.xml copy .\src\drivers\berniw\7\eroad.xml .\runtime\drivers\berniw\7\eroad.xml
if exist .\src\drivers\berniw\7\e-track-1.xml copy .\src\drivers\berniw\7\e-track-1.xml .\runtime\drivers\berniw\7\e-track-1.xml
if exist .\src\drivers\berniw\7\e-track-2.xml copy .\src\drivers\berniw\7\e-track-2.xml .\runtime\drivers\berniw\7\e-track-2.xml
if exist .\src\drivers\berniw\7\e-track-3.xml copy .\src\drivers\berniw\7\e-track-3.xml .\runtime\drivers\berniw\7\e-track-3.xml
if exist .\src\drivers\berniw\7\e-track-4.xml copy .\src\drivers\berniw\7\e-track-4.xml .\runtime\drivers\berniw\7\e-track-4.xml
if exist .\src\drivers\berniw\7\e-track-5.xml copy .\src\drivers\berniw\7\e-track-5.xml .\runtime\drivers\berniw\7\e-track-5.xml
if exist .\src\drivers\berniw\7\e-track-6.xml copy .\src\drivers\berniw\7\e-track-6.xml .\runtime\drivers\berniw\7\e-track-6.xml
if exist .\src\drivers\berniw\7\g-track-1.xml copy .\src\drivers\berniw\7\g-track-1.xml .\runtime\drivers\berniw\7\g-track-1.xml
if exist .\src\drivers\berniw\7\g-track-2.xml copy .\src\drivers\berniw\7\g-track-2.xml .\runtime\drivers\berniw\7\g-track-2.xml
if exist .\src\drivers\berniw\7\g-track-3.xml copy .\src\drivers\berniw\7\g-track-3.xml .\runtime\drivers\berniw\7\g-track-3.xml
if exist .\src\drivers\berniw\7\michigan.xml copy .\src\drivers\berniw\7\michigan.xml .\runtime\drivers\berniw\7\michigan.xml
if exist .\src\drivers\berniw\7\mixed-1.xml copy .\src\drivers\berniw\7\mixed-1.xml .\runtime\drivers\berniw\7\mixed-1.xml
if exist .\src\drivers\berniw\7\mixed-2.xml copy .\src\drivers\berniw\7\mixed-2.xml .\runtime\drivers\berniw\7\mixed-2.xml
if exist .\src\drivers\berniw\7\spring.xml copy .\src\drivers\berniw\7\spring.xml .\runtime\drivers\berniw\7\spring.xml
if exist .\src\drivers\berniw\7\wheel-1.xml copy .\src\drivers\berniw\7\wheel-1.xml .\runtime\drivers\berniw\7\wheel-1.xml

if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers\berniw\8
if exist .\src\drivers\berniw\8\baja-bug.rgb copy .\src\drivers\berniw\8\baja-bug.rgb .\runtime\drivers\berniw\8\baja-bug.rgb
if exist .\src\drivers\berniw\8\aalborg.xml copy .\src\drivers\berniw\8\aalborg.xml .\runtime\drivers\berniw\8\aalborg.xml
if exist .\src\drivers\berniw\8\alpine-1.xml copy .\src\drivers\berniw\8\alpine-1.xml .\runtime\drivers\berniw\8\alpine-1.xml
if exist .\src\drivers\berniw\8\a-speedway.xml copy .\src\drivers\berniw\8\a-speedway.xml .\runtime\drivers\berniw\8\a-speedway.xml
if exist .\src\drivers\berniw\8\dirt-1.xml copy .\src\drivers\berniw\8\dirt-1.xml .\runtime\drivers\berniw\8\dirt-1.xml
if exist .\src\drivers\berniw\8\dirt-2.xml copy .\src\drivers\berniw\8\dirt-2.xml .\runtime\drivers\berniw\8\dirt-2.xml
if exist .\src\drivers\berniw\8\dirt-3.xml copy .\src\drivers\berniw\8\dirt-3.xml .\runtime\drivers\berniw\8\dirt-3.xml
if exist .\src\drivers\berniw\8\dirt-4.xml copy .\src\drivers\berniw\8\dirt-4.xml .\runtime\drivers\berniw\8\dirt-4.xml
if exist .\src\drivers\berniw\8\dirt-5.xml copy .\src\drivers\berniw\8\dirt-5.xml .\runtime\drivers\berniw\8\dirt-5.xml
if exist .\src\drivers\berniw\8\dirt-6.xml copy .\src\drivers\berniw\8\dirt-6.xml .\runtime\drivers\berniw\8\dirt-6.xml
if exist .\src\drivers\berniw\8\eroad.xml copy .\src\drivers\berniw\8\eroad.xml .\runtime\drivers\berniw\8\eroad.xml
if exist .\src\drivers\berniw\8\e-track-1.xml copy .\src\drivers\berniw\8\e-track-1.xml .\runtime\drivers\berniw\8\e-track-1.xml
if exist .\src\drivers\berniw\8\e-track-2.xml copy .\src\drivers\berniw\8\e-track-2.xml .\runtime\drivers\berniw\8\e-track-2.xml
if exist .\src\drivers\berniw\8\e-track-3.xml copy .\src\drivers\berniw\8\e-track-3.xml .\runtime\drivers\berniw\8\e-track-3.xml
if exist .\src\drivers\berniw\8\e-track-4.xml copy .\src\drivers\berniw\8\e-track-4.xml .\runtime\drivers\berniw\8\e-track-4.xml
if exist .\src\drivers\berniw\8\e-track-5.xml copy .\src\drivers\berniw\8\e-track-5.xml .\runtime\drivers\berniw\8\e-track-5.xml
if exist .\src\drivers\berniw\8\e-track-6.xml copy .\src\drivers\berniw\8\e-track-6.xml .\runtime\drivers\berniw\8\e-track-6.xml
if exist .\src\drivers\berniw\8\g-track-1.xml copy .\src\drivers\berniw\8\g-track-1.xml .\runtime\drivers\berniw\8\g-track-1.xml
if exist .\src\drivers\berniw\8\g-track-2.xml copy .\src\drivers\berniw\8\g-track-2.xml .\runtime\drivers\berniw\8\g-track-2.xml
if exist .\src\drivers\berniw\8\g-track-3.xml copy .\src\drivers\berniw\8\g-track-3.xml .\runtime\drivers\berniw\8\g-track-3.xml
if exist .\src\drivers\berniw\8\michigan.xml copy .\src\drivers\berniw\8\michigan.xml .\runtime\drivers\berniw\8\michigan.xml
if exist .\src\drivers\berniw\8\mixed-1.xml copy .\src\drivers\berniw\8\mixed-1.xml .\runtime\drivers\berniw\8\mixed-1.xml
if exist .\src\drivers\berniw\8\mixed-2.xml copy .\src\drivers\berniw\8\mixed-2.xml .\runtime\drivers\berniw\8\mixed-2.xml
if exist .\src\drivers\berniw\8\spring.xml copy .\src\drivers\berniw\8\spring.xml .\runtime\drivers\berniw\8\spring.xml
if exist .\src\drivers\berniw\8\wheel-1.xml copy .\src\drivers\berniw\8\wheel-1.xml .\runtime\drivers\berniw\8\wheel-1.xml

if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers\berniw\9
if exist .\src\drivers\berniw\9\mclaren-f1.rgb copy .\src\drivers\berniw\9\mclaren-f1.rgb .\runtime\drivers\berniw\9\mclaren-f1.rgb
if exist .\src\drivers\berniw\9\aalborg.xml copy .\src\drivers\berniw\9\aalborg.xml .\runtime\drivers\berniw\9\aalborg.xml
if exist .\src\drivers\berniw\9\alpine-1.xml copy .\src\drivers\berniw\9\alpine-1.xml .\runtime\drivers\berniw\9\alpine-1.xml
if exist .\src\drivers\berniw\9\a-speedway.xml copy .\src\drivers\berniw\9\a-speedway.xml .\runtime\drivers\berniw\9\a-speedway.xml
if exist .\src\drivers\berniw\9\dirt-1.xml copy .\src\drivers\berniw\9\dirt-1.xml .\runtime\drivers\berniw\9\dirt-1.xml
if exist .\src\drivers\berniw\9\dirt-2.xml copy .\src\drivers\berniw\9\dirt-2.xml .\runtime\drivers\berniw\9\dirt-2.xml
if exist .\src\drivers\berniw\9\dirt-3.xml copy .\src\drivers\berniw\9\dirt-3.xml .\runtime\drivers\berniw\9\dirt-3.xml
if exist .\src\drivers\berniw\9\dirt-4.xml copy .\src\drivers\berniw\9\dirt-4.xml .\runtime\drivers\berniw\9\dirt-4.xml
if exist .\src\drivers\berniw\9\dirt-5.xml copy .\src\drivers\berniw\9\dirt-5.xml .\runtime\drivers\berniw\9\dirt-5.xml
if exist .\src\drivers\berniw\9\dirt-6.xml copy .\src\drivers\berniw\9\dirt-6.xml .\runtime\drivers\berniw\9\dirt-6.xml
if exist .\src\drivers\berniw\9\eroad.xml copy .\src\drivers\berniw\9\eroad.xml .\runtime\drivers\berniw\9\eroad.xml
if exist .\src\drivers\berniw\9\e-track-1.xml copy .\src\drivers\berniw\9\e-track-1.xml .\runtime\drivers\berniw\9\e-track-1.xml
if exist .\src\drivers\berniw\9\e-track-2.xml copy .\src\drivers\berniw\9\e-track-2.xml .\runtime\drivers\berniw\9\e-track-2.xml
if exist .\src\drivers\berniw\9\e-track-3.xml copy .\src\drivers\berniw\9\e-track-3.xml .\runtime\drivers\berniw\9\e-track-3.xml
if exist .\src\drivers\berniw\9\e-track-4.xml copy .\src\drivers\berniw\9\e-track-4.xml .\runtime\drivers\berniw\9\e-track-4.xml
if exist .\src\drivers\berniw\9\e-track-5.xml copy .\src\drivers\berniw\9\e-track-5.xml .\runtime\drivers\berniw\9\e-track-5.xml
if exist .\src\drivers\berniw\9\e-track-6.xml copy .\src\drivers\berniw\9\e-track-6.xml .\runtime\drivers\berniw\9\e-track-6.xml
if exist .\src\drivers\berniw\9\g-track-1.xml copy .\src\drivers\berniw\9\g-track-1.xml .\runtime\drivers\berniw\9\g-track-1.xml
if exist .\src\drivers\berniw\9\g-track-2.xml copy .\src\drivers\berniw\9\g-track-2.xml .\runtime\drivers\berniw\9\g-track-2.xml
if exist .\src\drivers\berniw\9\g-track-3.xml copy .\src\drivers\berniw\9\g-track-3.xml .\runtime\drivers\berniw\9\g-track-3.xml
if exist .\src\drivers\berniw\9\michigan.xml copy .\src\drivers\berniw\9\michigan.xml .\runtime\drivers\berniw\9\michigan.xml
if exist .\src\drivers\berniw\9\mixed-1.xml copy .\src\drivers\berniw\9\mixed-1.xml .\runtime\drivers\berniw\9\mixed-1.xml
if exist .\src\drivers\berniw\9\mixed-2.xml copy .\src\drivers\berniw\9\mixed-2.xml .\runtime\drivers\berniw\9\mixed-2.xml
if exist .\src\drivers\berniw\9\spring.xml copy .\src\drivers\berniw\9\spring.xml .\runtime\drivers\berniw\9\spring.xml
if exist .\src\drivers\berniw\9\wheel-1.xml copy .\src\drivers\berniw\9\wheel-1.xml .\runtime\drivers\berniw\9\wheel-1.xml

if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\berniw.xml copy .\src\drivers\berniw\berniw.xml .\runtime\drivers\berniw\berniw.xml
if exist .\src\drivers\berniw\logo.rgb copy .\src\drivers\berniw\logo.rgb .\runtime\drivers\berniw\logo.rgb
if exist .\src\drivers\berniw\parameter.dat copy .\src\drivers\berniw\parameter.dat .\runtime\drivers\berniw\parameter.dat
if exist .\src\drivers\berniw\intsinsqr.dat copy .\src\drivers\berniw\intsinsqr.dat .\runtime\drivers\berniw\intsinsqr.dat
if exist .\src\drivers\berniw\intcossqr.dat copy .\src\drivers\berniw\intcossqr.dat .\runtime\drivers\berniw\intcossqr.dat

if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers\berniw2\1
if exist .\src\drivers\berniw2\1\aalborg.xml copy .\src\drivers\berniw2\1\aalborg.xml .\runtime\drivers\berniw2\1\aalborg.xml
if exist .\src\drivers\berniw2\1\alpine-1.xml copy .\src\drivers\berniw2\1\alpine-1.xml .\runtime\drivers\berniw2\1\alpine-1.xml
if exist .\src\drivers\berniw2\1\a-speedway.xml copy .\src\drivers\berniw2\1\a-speedway.xml .\runtime\drivers\berniw2\1\a-speedway.xml
if exist .\src\drivers\berniw2\1\default.xml copy .\src\drivers\berniw2\1\default.xml .\runtime\drivers\berniw2\1\default.xml
if exist .\src\drivers\berniw2\1\dirt-1.xml copy .\src\drivers\berniw2\1\dirt-1.xml .\runtime\drivers\berniw2\1\dirt-1.xml
if exist .\src\drivers\berniw2\1\dirt-2.xml copy .\src\drivers\berniw2\1\dirt-2.xml .\runtime\drivers\berniw2\1\dirt-2.xml
if exist .\src\drivers\berniw2\1\dirt-3.xml copy .\src\drivers\berniw2\1\dirt-3.xml .\runtime\drivers\berniw2\1\dirt-3.xml
if exist .\src\drivers\berniw2\1\dirt-4.xml copy .\src\drivers\berniw2\1\dirt-4.xml .\runtime\drivers\berniw2\1\dirt-4.xml
if exist .\src\drivers\berniw2\1\dirt-5.xml copy .\src\drivers\berniw2\1\dirt-5.xml .\runtime\drivers\berniw2\1\dirt-5.xml
if exist .\src\drivers\berniw2\1\dirt-6.xml copy .\src\drivers\berniw2\1\dirt-6.xml .\runtime\drivers\berniw2\1\dirt-6.xml
if exist .\src\drivers\berniw2\1\eroad.xml copy .\src\drivers\berniw2\1\eroad.xml .\runtime\drivers\berniw2\1\eroad.xml
if exist .\src\drivers\berniw2\1\e-track-1.xml copy .\src\drivers\berniw2\1\e-track-1.xml .\runtime\drivers\berniw2\1\e-track-1.xml
if exist .\src\drivers\berniw2\1\e-track-2.xml copy .\src\drivers\berniw2\1\e-track-2.xml .\runtime\drivers\berniw2\1\e-track-2.xml
if exist .\src\drivers\berniw2\1\e-track-3.xml copy .\src\drivers\berniw2\1\e-track-3.xml .\runtime\drivers\berniw2\1\e-track-3.xml
if exist .\src\drivers\berniw2\1\e-track-4.xml copy .\src\drivers\berniw2\1\e-track-4.xml .\runtime\drivers\berniw2\1\e-track-4.xml
if exist .\src\drivers\berniw2\1\e-track-5.xml copy .\src\drivers\berniw2\1\e-track-5.xml .\runtime\drivers\berniw2\1\e-track-5.xml
if exist .\src\drivers\berniw2\1\e-track-6.xml copy .\src\drivers\berniw2\1\e-track-6.xml .\runtime\drivers\berniw2\1\e-track-6.xml
if exist .\src\drivers\berniw2\1\g-track-1.xml copy .\src\drivers\berniw2\1\g-track-1.xml .\runtime\drivers\berniw2\1\g-track-1.xml
if exist .\src\drivers\berniw2\1\g-track-2.xml copy .\src\drivers\berniw2\1\g-track-2.xml .\runtime\drivers\berniw2\1\g-track-2.xml
if exist .\src\drivers\berniw2\1\g-track-3.xml copy .\src\drivers\berniw2\1\g-track-3.xml .\runtime\drivers\berniw2\1\g-track-3.xml
if exist .\src\drivers\berniw2\1\michigan.xml copy .\src\drivers\berniw2\1\michigan.xml .\runtime\drivers\berniw2\1\michigan.xml
if exist .\src\drivers\berniw2\1\mixed-1.xml copy .\src\drivers\berniw2\1\mixed-1.xml .\runtime\drivers\berniw2\1\mixed-1.xml
if exist .\src\drivers\berniw2\1\mixed-2.xml copy .\src\drivers\berniw2\1\mixed-2.xml .\runtime\drivers\berniw2\1\mixed-2.xml
if exist .\src\drivers\berniw2\1\spring.xml copy .\src\drivers\berniw2\1\spring.xml .\runtime\drivers\berniw2\1\spring.xml
if exist .\src\drivers\berniw2\1\wheel-1.xml copy .\src\drivers\berniw2\1\wheel-1.xml .\runtime\drivers\berniw2\1\wheel-1.xml

if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers\berniw2\10
if exist .\src\drivers\berniw2\10\360-modena.rgb copy .\src\drivers\berniw2\10\360-modena.rgb .\runtime\drivers\berniw2\10\360-modena.rgb
if exist .\src\drivers\berniw2\10\aalborg.xml copy .\src\drivers\berniw2\10\aalborg.xml .\runtime\drivers\berniw2\10\aalborg.xml
if exist .\src\drivers\berniw2\10\alpine-1.xml copy .\src\drivers\berniw2\10\alpine-1.xml .\runtime\drivers\berniw2\10\alpine-1.xml
if exist .\src\drivers\berniw2\10\a-speedway.xml copy .\src\drivers\berniw2\10\a-speedway.xml .\runtime\drivers\berniw2\10\a-speedway.xml
if exist .\src\drivers\berniw2\10\default.xml copy .\src\drivers\berniw2\10\default.xml .\runtime\drivers\berniw2\10\default.xml
if exist .\src\drivers\berniw2\10\dirt-1.xml copy .\src\drivers\berniw2\10\dirt-1.xml .\runtime\drivers\berniw2\10\dirt-1.xml
if exist .\src\drivers\berniw2\10\dirt-2.xml copy .\src\drivers\berniw2\10\dirt-2.xml .\runtime\drivers\berniw2\10\dirt-2.xml
if exist .\src\drivers\berniw2\10\dirt-3.xml copy .\src\drivers\berniw2\10\dirt-3.xml .\runtime\drivers\berniw2\10\dirt-3.xml
if exist .\src\drivers\berniw2\10\dirt-4.xml copy .\src\drivers\berniw2\10\dirt-4.xml .\runtime\drivers\berniw2\10\dirt-4.xml
if exist .\src\drivers\berniw2\10\dirt-5.xml copy .\src\drivers\berniw2\10\dirt-5.xml .\runtime\drivers\berniw2\10\dirt-5.xml
if exist .\src\drivers\berniw2\10\dirt-6.xml copy .\src\drivers\berniw2\10\dirt-6.xml .\runtime\drivers\berniw2\10\dirt-6.xml
if exist .\src\drivers\berniw2\10\eroad.xml copy .\src\drivers\berniw2\10\eroad.xml .\runtime\drivers\berniw2\10\eroad.xml
if exist .\src\drivers\berniw2\10\e-track-1.xml copy .\src\drivers\berniw2\10\e-track-1.xml .\runtime\drivers\berniw2\10\e-track-1.xml
if exist .\src\drivers\berniw2\10\e-track-2.xml copy .\src\drivers\berniw2\10\e-track-2.xml .\runtime\drivers\berniw2\10\e-track-2.xml
if exist .\src\drivers\berniw2\10\e-track-3.xml copy .\src\drivers\berniw2\10\e-track-3.xml .\runtime\drivers\berniw2\10\e-track-3.xml
if exist .\src\drivers\berniw2\10\e-track-4.xml copy .\src\drivers\berniw2\10\e-track-4.xml .\runtime\drivers\berniw2\10\e-track-4.xml
if exist .\src\drivers\berniw2\10\e-track-5.xml copy .\src\drivers\berniw2\10\e-track-5.xml .\runtime\drivers\berniw2\10\e-track-5.xml
if exist .\src\drivers\berniw2\10\e-track-6.xml copy .\src\drivers\berniw2\10\e-track-6.xml .\runtime\drivers\berniw2\10\e-track-6.xml
if exist .\src\drivers\berniw2\10\g-track-1.xml copy .\src\drivers\berniw2\10\g-track-1.xml .\runtime\drivers\berniw2\10\g-track-1.xml
if exist .\src\drivers\berniw2\10\g-track-2.xml copy .\src\drivers\berniw2\10\g-track-2.xml .\runtime\drivers\berniw2\10\g-track-2.xml
if exist .\src\drivers\berniw2\10\g-track-3.xml copy .\src\drivers\berniw2\10\g-track-3.xml .\runtime\drivers\berniw2\10\g-track-3.xml
if exist .\src\drivers\berniw2\10\michigan.xml copy .\src\drivers\berniw2\10\michigan.xml .\runtime\drivers\berniw2\10\michigan.xml
if exist .\src\drivers\berniw2\10\mixed-1.xml copy .\src\drivers\berniw2\10\mixed-1.xml .\runtime\drivers\berniw2\10\mixed-1.xml
if exist .\src\drivers\berniw2\10\mixed-2.xml copy .\src\drivers\berniw2\10\mixed-2.xml .\runtime\drivers\berniw2\10\mixed-2.xml
if exist .\src\drivers\berniw2\10\spring.xml copy .\src\drivers\berniw2\10\spring.xml .\runtime\drivers\berniw2\10\spring.xml
if exist .\src\drivers\berniw2\10\wheel-1.xml copy .\src\drivers\berniw2\10\wheel-1.xml .\runtime\drivers\berniw2\10\wheel-1.xml

if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers\berniw2\2
if exist .\src\drivers\berniw2\2\aalborg.xml copy .\src\drivers\berniw2\2\aalborg.xml .\runtime\drivers\berniw2\2\aalborg.xml
if exist .\src\drivers\berniw2\2\alpine-1.xml copy .\src\drivers\berniw2\2\alpine-1.xml .\runtime\drivers\berniw2\2\alpine-1.xml
if exist .\src\drivers\berniw2\2\a-speedway.xml copy .\src\drivers\berniw2\2\a-speedway.xml .\runtime\drivers\berniw2\2\a-speedway.xml
if exist .\src\drivers\berniw2\2\default.xml copy .\src\drivers\berniw2\2\default.xml .\runtime\drivers\berniw2\2\default.xml
if exist .\src\drivers\berniw2\2\dirt-1.xml copy .\src\drivers\berniw2\2\dirt-1.xml .\runtime\drivers\berniw2\2\dirt-1.xml
if exist .\src\drivers\berniw2\2\dirt-2.xml copy .\src\drivers\berniw2\2\dirt-2.xml .\runtime\drivers\berniw2\2\dirt-2.xml
if exist .\src\drivers\berniw2\2\dirt-3.xml copy .\src\drivers\berniw2\2\dirt-3.xml .\runtime\drivers\berniw2\2\dirt-3.xml
if exist .\src\drivers\berniw2\2\dirt-4.xml copy .\src\drivers\berniw2\2\dirt-4.xml .\runtime\drivers\berniw2\2\dirt-4.xml
if exist .\src\drivers\berniw2\2\dirt-5.xml copy .\src\drivers\berniw2\2\dirt-5.xml .\runtime\drivers\berniw2\2\dirt-5.xml
if exist .\src\drivers\berniw2\2\dirt-6.xml copy .\src\drivers\berniw2\2\dirt-6.xml .\runtime\drivers\berniw2\2\dirt-6.xml
if exist .\src\drivers\berniw2\2\eroad.xml copy .\src\drivers\berniw2\2\eroad.xml .\runtime\drivers\berniw2\2\eroad.xml
if exist .\src\drivers\berniw2\2\e-track-1.xml copy .\src\drivers\berniw2\2\e-track-1.xml .\runtime\drivers\berniw2\2\e-track-1.xml
if exist .\src\drivers\berniw2\2\e-track-2.xml copy .\src\drivers\berniw2\2\e-track-2.xml .\runtime\drivers\berniw2\2\e-track-2.xml
if exist .\src\drivers\berniw2\2\e-track-3.xml copy .\src\drivers\berniw2\2\e-track-3.xml .\runtime\drivers\berniw2\2\e-track-3.xml
if exist .\src\drivers\berniw2\2\e-track-4.xml copy .\src\drivers\berniw2\2\e-track-4.xml .\runtime\drivers\berniw2\2\e-track-4.xml
if exist .\src\drivers\berniw2\2\e-track-5.xml copy .\src\drivers\berniw2\2\e-track-5.xml .\runtime\drivers\berniw2\2\e-track-5.xml
if exist .\src\drivers\berniw2\2\e-track-6.xml copy .\src\drivers\berniw2\2\e-track-6.xml .\runtime\drivers\berniw2\2\e-track-6.xml
if exist .\src\drivers\berniw2\2\g-track-1.xml copy .\src\drivers\berniw2\2\g-track-1.xml .\runtime\drivers\berniw2\2\g-track-1.xml
if exist .\src\drivers\berniw2\2\g-track-2.xml copy .\src\drivers\berniw2\2\g-track-2.xml .\runtime\drivers\berniw2\2\g-track-2.xml
if exist .\src\drivers\berniw2\2\g-track-3.xml copy .\src\drivers\berniw2\2\g-track-3.xml .\runtime\drivers\berniw2\2\g-track-3.xml
if exist .\src\drivers\berniw2\2\michigan.xml copy .\src\drivers\berniw2\2\michigan.xml .\runtime\drivers\berniw2\2\michigan.xml
if exist .\src\drivers\berniw2\2\mixed-1.xml copy .\src\drivers\berniw2\2\mixed-1.xml .\runtime\drivers\berniw2\2\mixed-1.xml
if exist .\src\drivers\berniw2\2\mixed-2.xml copy .\src\drivers\berniw2\2\mixed-2.xml .\runtime\drivers\berniw2\2\mixed-2.xml
if exist .\src\drivers\berniw2\2\spring.xml copy .\src\drivers\berniw2\2\spring.xml .\runtime\drivers\berniw2\2\spring.xml
if exist .\src\drivers\berniw2\2\wheel-1.xml copy .\src\drivers\berniw2\2\wheel-1.xml .\runtime\drivers\berniw2\2\wheel-1.xml

if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers\berniw2\3
if exist .\src\drivers\berniw2\3\aalborg.xml copy .\src\drivers\berniw2\3\aalborg.xml .\runtime\drivers\berniw2\3\aalborg.xml
if exist .\src\drivers\berniw2\3\alpine-1.xml copy .\src\drivers\berniw2\3\alpine-1.xml .\runtime\drivers\berniw2\3\alpine-1.xml
if exist .\src\drivers\berniw2\3\a-speedway.xml copy .\src\drivers\berniw2\3\a-speedway.xml .\runtime\drivers\berniw2\3\a-speedway.xml
if exist .\src\drivers\berniw2\3\default.xml copy .\src\drivers\berniw2\3\default.xml .\runtime\drivers\berniw2\3\default.xml
if exist .\src\drivers\berniw2\3\dirt-1.xml copy .\src\drivers\berniw2\3\dirt-1.xml .\runtime\drivers\berniw2\3\dirt-1.xml
if exist .\src\drivers\berniw2\3\dirt-2.xml copy .\src\drivers\berniw2\3\dirt-2.xml .\runtime\drivers\berniw2\3\dirt-2.xml
if exist .\src\drivers\berniw2\3\dirt-3.xml copy .\src\drivers\berniw2\3\dirt-3.xml .\runtime\drivers\berniw2\3\dirt-3.xml
if exist .\src\drivers\berniw2\3\dirt-4.xml copy .\src\drivers\berniw2\3\dirt-4.xml .\runtime\drivers\berniw2\3\dirt-4.xml
if exist .\src\drivers\berniw2\3\dirt-5.xml copy .\src\drivers\berniw2\3\dirt-5.xml .\runtime\drivers\berniw2\3\dirt-5.xml
if exist .\src\drivers\berniw2\3\dirt-6.xml copy .\src\drivers\berniw2\3\dirt-6.xml .\runtime\drivers\berniw2\3\dirt-6.xml
if exist .\src\drivers\berniw2\3\eroad.xml copy .\src\drivers\berniw2\3\eroad.xml .\runtime\drivers\berniw2\3\eroad.xml
if exist .\src\drivers\berniw2\3\e-track-1.xml copy .\src\drivers\berniw2\3\e-track-1.xml .\runtime\drivers\berniw2\3\e-track-1.xml
if exist .\src\drivers\berniw2\3\e-track-2.xml copy .\src\drivers\berniw2\3\e-track-2.xml .\runtime\drivers\berniw2\3\e-track-2.xml
if exist .\src\drivers\berniw2\3\e-track-3.xml copy .\src\drivers\berniw2\3\e-track-3.xml .\runtime\drivers\berniw2\3\e-track-3.xml
if exist .\src\drivers\berniw2\3\e-track-4.xml copy .\src\drivers\berniw2\3\e-track-4.xml .\runtime\drivers\berniw2\3\e-track-4.xml
if exist .\src\drivers\berniw2\3\e-track-5.xml copy .\src\drivers\berniw2\3\e-track-5.xml .\runtime\drivers\berniw2\3\e-track-5.xml
if exist .\src\drivers\berniw2\3\e-track-6.xml copy .\src\drivers\berniw2\3\e-track-6.xml .\runtime\drivers\berniw2\3\e-track-6.xml
if exist .\src\drivers\berniw2\3\g-track-1.xml copy .\src\drivers\berniw2\3\g-track-1.xml .\runtime\drivers\berniw2\3\g-track-1.xml
if exist .\src\drivers\berniw2\3\g-track-2.xml copy .\src\drivers\berniw2\3\g-track-2.xml .\runtime\drivers\berniw2\3\g-track-2.xml
if exist .\src\drivers\berniw2\3\g-track-3.xml copy .\src\drivers\berniw2\3\g-track-3.xml .\runtime\drivers\berniw2\3\g-track-3.xml
if exist .\src\drivers\berniw2\3\michigan.xml copy .\src\drivers\berniw2\3\michigan.xml .\runtime\drivers\berniw2\3\michigan.xml
if exist .\src\drivers\berniw2\3\mixed-1.xml copy .\src\drivers\berniw2\3\mixed-1.xml .\runtime\drivers\berniw2\3\mixed-1.xml
if exist .\src\drivers\berniw2\3\mixed-2.xml copy .\src\drivers\berniw2\3\mixed-2.xml .\runtime\drivers\berniw2\3\mixed-2.xml
if exist .\src\drivers\berniw2\3\spring.xml copy .\src\drivers\berniw2\3\spring.xml .\runtime\drivers\berniw2\3\spring.xml
if exist .\src\drivers\berniw2\3\wheel-1.xml copy .\src\drivers\berniw2\3\wheel-1.xml .\runtime\drivers\berniw2\3\wheel-1.xml

if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers\berniw2\4
if exist .\src\drivers\berniw2\4\aalborg.xml copy .\src\drivers\berniw2\4\aalborg.xml .\runtime\drivers\berniw2\4\aalborg.xml
if exist .\src\drivers\berniw2\4\alpine-1.xml copy .\src\drivers\berniw2\4\alpine-1.xml .\runtime\drivers\berniw2\4\alpine-1.xml
if exist .\src\drivers\berniw2\4\a-speedway.xml copy .\src\drivers\berniw2\4\a-speedway.xml .\runtime\drivers\berniw2\4\a-speedway.xml
if exist .\src\drivers\berniw2\4\default.xml copy .\src\drivers\berniw2\4\default.xml .\runtime\drivers\berniw2\4\default.xml
if exist .\src\drivers\berniw2\4\dirt-1.xml copy .\src\drivers\berniw2\4\dirt-1.xml .\runtime\drivers\berniw2\4\dirt-1.xml
if exist .\src\drivers\berniw2\4\dirt-2.xml copy .\src\drivers\berniw2\4\dirt-2.xml .\runtime\drivers\berniw2\4\dirt-2.xml
if exist .\src\drivers\berniw2\4\dirt-3.xml copy .\src\drivers\berniw2\4\dirt-3.xml .\runtime\drivers\berniw2\4\dirt-3.xml
if exist .\src\drivers\berniw2\4\dirt-4.xml copy .\src\drivers\berniw2\4\dirt-4.xml .\runtime\drivers\berniw2\4\dirt-4.xml
if exist .\src\drivers\berniw2\4\dirt-5.xml copy .\src\drivers\berniw2\4\dirt-5.xml .\runtime\drivers\berniw2\4\dirt-5.xml
if exist .\src\drivers\berniw2\4\dirt-6.xml copy .\src\drivers\berniw2\4\dirt-6.xml .\runtime\drivers\berniw2\4\dirt-6.xml
if exist .\src\drivers\berniw2\4\eroad.xml copy .\src\drivers\berniw2\4\eroad.xml .\runtime\drivers\berniw2\4\eroad.xml
if exist .\src\drivers\berniw2\4\e-track-1.xml copy .\src\drivers\berniw2\4\e-track-1.xml .\runtime\drivers\berniw2\4\e-track-1.xml
if exist .\src\drivers\berniw2\4\e-track-2.xml copy .\src\drivers\berniw2\4\e-track-2.xml .\runtime\drivers\berniw2\4\e-track-2.xml
if exist .\src\drivers\berniw2\4\e-track-3.xml copy .\src\drivers\berniw2\4\e-track-3.xml .\runtime\drivers\berniw2\4\e-track-3.xml
if exist .\src\drivers\berniw2\4\e-track-4.xml copy .\src\drivers\berniw2\4\e-track-4.xml .\runtime\drivers\berniw2\4\e-track-4.xml
if exist .\src\drivers\berniw2\4\e-track-5.xml copy .\src\drivers\berniw2\4\e-track-5.xml .\runtime\drivers\berniw2\4\e-track-5.xml
if exist .\src\drivers\berniw2\4\e-track-6.xml copy .\src\drivers\berniw2\4\e-track-6.xml .\runtime\drivers\berniw2\4\e-track-6.xml
if exist .\src\drivers\berniw2\4\g-track-1.xml copy .\src\drivers\berniw2\4\g-track-1.xml .\runtime\drivers\berniw2\4\g-track-1.xml
if exist .\src\drivers\berniw2\4\g-track-2.xml copy .\src\drivers\berniw2\4\g-track-2.xml .\runtime\drivers\berniw2\4\g-track-2.xml
if exist .\src\drivers\berniw2\4\g-track-3.xml copy .\src\drivers\berniw2\4\g-track-3.xml .\runtime\drivers\berniw2\4\g-track-3.xml
if exist .\src\drivers\berniw2\4\michigan.xml copy .\src\drivers\berniw2\4\michigan.xml .\runtime\drivers\berniw2\4\michigan.xml
if exist .\src\drivers\berniw2\4\mixed-1.xml copy .\src\drivers\berniw2\4\mixed-1.xml .\runtime\drivers\berniw2\4\mixed-1.xml
if exist .\src\drivers\berniw2\4\mixed-2.xml copy .\src\drivers\berniw2\4\mixed-2.xml .\runtime\drivers\berniw2\4\mixed-2.xml
if exist .\src\drivers\berniw2\4\spring.xml copy .\src\drivers\berniw2\4\spring.xml .\runtime\drivers\berniw2\4\spring.xml
if exist .\src\drivers\berniw2\4\wheel-1.xml copy .\src\drivers\berniw2\4\wheel-1.xml .\runtime\drivers\berniw2\4\wheel-1.xml

if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers\berniw2\5
if exist .\src\drivers\berniw2\5\aalborg.xml copy .\src\drivers\berniw2\5\aalborg.xml .\runtime\drivers\berniw2\5\aalborg.xml
if exist .\src\drivers\berniw2\5\alpine-1.xml copy .\src\drivers\berniw2\5\alpine-1.xml .\runtime\drivers\berniw2\5\alpine-1.xml
if exist .\src\drivers\berniw2\5\a-speedway.xml copy .\src\drivers\berniw2\5\a-speedway.xml .\runtime\drivers\berniw2\5\a-speedway.xml
if exist .\src\drivers\berniw2\5\default.xml copy .\src\drivers\berniw2\5\default.xml .\runtime\drivers\berniw2\5\default.xml
if exist .\src\drivers\berniw2\5\dirt-1.xml copy .\src\drivers\berniw2\5\dirt-1.xml .\runtime\drivers\berniw2\5\dirt-1.xml
if exist .\src\drivers\berniw2\5\dirt-2.xml copy .\src\drivers\berniw2\5\dirt-2.xml .\runtime\drivers\berniw2\5\dirt-2.xml
if exist .\src\drivers\berniw2\5\dirt-3.xml copy .\src\drivers\berniw2\5\dirt-3.xml .\runtime\drivers\berniw2\5\dirt-3.xml
if exist .\src\drivers\berniw2\5\dirt-4.xml copy .\src\drivers\berniw2\5\dirt-4.xml .\runtime\drivers\berniw2\5\dirt-4.xml
if exist .\src\drivers\berniw2\5\dirt-5.xml copy .\src\drivers\berniw2\5\dirt-5.xml .\runtime\drivers\berniw2\5\dirt-5.xml
if exist .\src\drivers\berniw2\5\dirt-6.xml copy .\src\drivers\berniw2\5\dirt-6.xml .\runtime\drivers\berniw2\5\dirt-6.xml
if exist .\src\drivers\berniw2\5\eroad.xml copy .\src\drivers\berniw2\5\eroad.xml .\runtime\drivers\berniw2\5\eroad.xml
if exist .\src\drivers\berniw2\5\e-track-1.xml copy .\src\drivers\berniw2\5\e-track-1.xml .\runtime\drivers\berniw2\5\e-track-1.xml
if exist .\src\drivers\berniw2\5\e-track-2.xml copy .\src\drivers\berniw2\5\e-track-2.xml .\runtime\drivers\berniw2\5\e-track-2.xml
if exist .\src\drivers\berniw2\5\e-track-3.xml copy .\src\drivers\berniw2\5\e-track-3.xml .\runtime\drivers\berniw2\5\e-track-3.xml
if exist .\src\drivers\berniw2\5\e-track-4.xml copy .\src\drivers\berniw2\5\e-track-4.xml .\runtime\drivers\berniw2\5\e-track-4.xml
if exist .\src\drivers\berniw2\5\e-track-5.xml copy .\src\drivers\berniw2\5\e-track-5.xml .\runtime\drivers\berniw2\5\e-track-5.xml
if exist .\src\drivers\berniw2\5\e-track-6.xml copy .\src\drivers\berniw2\5\e-track-6.xml .\runtime\drivers\berniw2\5\e-track-6.xml
if exist .\src\drivers\berniw2\5\g-track-1.xml copy .\src\drivers\berniw2\5\g-track-1.xml .\runtime\drivers\berniw2\5\g-track-1.xml
if exist .\src\drivers\berniw2\5\g-track-2.xml copy .\src\drivers\berniw2\5\g-track-2.xml .\runtime\drivers\berniw2\5\g-track-2.xml
if exist .\src\drivers\berniw2\5\g-track-3.xml copy .\src\drivers\berniw2\5\g-track-3.xml .\runtime\drivers\berniw2\5\g-track-3.xml
if exist .\src\drivers\berniw2\5\michigan.xml copy .\src\drivers\berniw2\5\michigan.xml .\runtime\drivers\berniw2\5\michigan.xml
if exist .\src\drivers\berniw2\5\mixed-1.xml copy .\src\drivers\berniw2\5\mixed-1.xml .\runtime\drivers\berniw2\5\mixed-1.xml
if exist .\src\drivers\berniw2\5\mixed-2.xml copy .\src\drivers\berniw2\5\mixed-2.xml .\runtime\drivers\berniw2\5\mixed-2.xml
if exist .\src\drivers\berniw2\5\spring.xml copy .\src\drivers\berniw2\5\spring.xml .\runtime\drivers\berniw2\5\spring.xml
if exist .\src\drivers\berniw2\5\wheel-1.xml copy .\src\drivers\berniw2\5\wheel-1.xml .\runtime\drivers\berniw2\5\wheel-1.xml

if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers\berniw2\6
if exist .\src\drivers\berniw2\6\aalborg.xml copy .\src\drivers\berniw2\6\aalborg.xml .\runtime\drivers\berniw2\6\aalborg.xml
if exist .\src\drivers\berniw2\6\alpine-1.xml copy .\src\drivers\berniw2\6\alpine-1.xml .\runtime\drivers\berniw2\6\alpine-1.xml
if exist .\src\drivers\berniw2\6\a-speedway.xml copy .\src\drivers\berniw2\6\a-speedway.xml .\runtime\drivers\berniw2\6\a-speedway.xml
if exist .\src\drivers\berniw2\6\default.xml copy .\src\drivers\berniw2\6\default.xml .\runtime\drivers\berniw2\6\default.xml
if exist .\src\drivers\berniw2\6\dirt-1.xml copy .\src\drivers\berniw2\6\dirt-1.xml .\runtime\drivers\berniw2\6\dirt-1.xml
if exist .\src\drivers\berniw2\6\dirt-2.xml copy .\src\drivers\berniw2\6\dirt-2.xml .\runtime\drivers\berniw2\6\dirt-2.xml
if exist .\src\drivers\berniw2\6\dirt-3.xml copy .\src\drivers\berniw2\6\dirt-3.xml .\runtime\drivers\berniw2\6\dirt-3.xml
if exist .\src\drivers\berniw2\6\dirt-4.xml copy .\src\drivers\berniw2\6\dirt-4.xml .\runtime\drivers\berniw2\6\dirt-4.xml
if exist .\src\drivers\berniw2\6\dirt-5.xml copy .\src\drivers\berniw2\6\dirt-5.xml .\runtime\drivers\berniw2\6\dirt-5.xml
if exist .\src\drivers\berniw2\6\dirt-6.xml copy .\src\drivers\berniw2\6\dirt-6.xml .\runtime\drivers\berniw2\6\dirt-6.xml
if exist .\src\drivers\berniw2\6\eroad.xml copy .\src\drivers\berniw2\6\eroad.xml .\runtime\drivers\berniw2\6\eroad.xml
if exist .\src\drivers\berniw2\6\e-track-1.xml copy .\src\drivers\berniw2\6\e-track-1.xml .\runtime\drivers\berniw2\6\e-track-1.xml
if exist .\src\drivers\berniw2\6\e-track-2.xml copy .\src\drivers\berniw2\6\e-track-2.xml .\runtime\drivers\berniw2\6\e-track-2.xml
if exist .\src\drivers\berniw2\6\e-track-3.xml copy .\src\drivers\berniw2\6\e-track-3.xml .\runtime\drivers\berniw2\6\e-track-3.xml
if exist .\src\drivers\berniw2\6\e-track-4.xml copy .\src\drivers\berniw2\6\e-track-4.xml .\runtime\drivers\berniw2\6\e-track-4.xml
if exist .\src\drivers\berniw2\6\e-track-5.xml copy .\src\drivers\berniw2\6\e-track-5.xml .\runtime\drivers\berniw2\6\e-track-5.xml
if exist .\src\drivers\berniw2\6\e-track-6.xml copy .\src\drivers\berniw2\6\e-track-6.xml .\runtime\drivers\berniw2\6\e-track-6.xml
if exist .\src\drivers\berniw2\6\g-track-1.xml copy .\src\drivers\berniw2\6\g-track-1.xml .\runtime\drivers\berniw2\6\g-track-1.xml
if exist .\src\drivers\berniw2\6\g-track-2.xml copy .\src\drivers\berniw2\6\g-track-2.xml .\runtime\drivers\berniw2\6\g-track-2.xml
if exist .\src\drivers\berniw2\6\g-track-3.xml copy .\src\drivers\berniw2\6\g-track-3.xml .\runtime\drivers\berniw2\6\g-track-3.xml
if exist .\src\drivers\berniw2\6\michigan.xml copy .\src\drivers\berniw2\6\michigan.xml .\runtime\drivers\berniw2\6\michigan.xml
if exist .\src\drivers\berniw2\6\mixed-1.xml copy .\src\drivers\berniw2\6\mixed-1.xml .\runtime\drivers\berniw2\6\mixed-1.xml
if exist .\src\drivers\berniw2\6\mixed-2.xml copy .\src\drivers\berniw2\6\mixed-2.xml .\runtime\drivers\berniw2\6\mixed-2.xml
if exist .\src\drivers\berniw2\6\spring.xml copy .\src\drivers\berniw2\6\spring.xml .\runtime\drivers\berniw2\6\spring.xml
if exist .\src\drivers\berniw2\6\wheel-1.xml copy .\src\drivers\berniw2\6\wheel-1.xml .\runtime\drivers\berniw2\6\wheel-1.xml

if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers\berniw2\7
if exist .\src\drivers\berniw2\7\porsche-gt3rs.rgb copy .\src\drivers\berniw2\7\porsche-gt3rs.rgb .\runtime\drivers\berniw2\7\porsche-gt3rs.rgb
if exist .\src\drivers\berniw2\7\aalborg.xml copy .\src\drivers\berniw2\7\aalborg.xml .\runtime\drivers\berniw2\7\aalborg.xml
if exist .\src\drivers\berniw2\7\alpine-1.xml copy .\src\drivers\berniw2\7\alpine-1.xml .\runtime\drivers\berniw2\7\alpine-1.xml
if exist .\src\drivers\berniw2\7\a-speedway.xml copy .\src\drivers\berniw2\7\a-speedway.xml .\runtime\drivers\berniw2\7\a-speedway.xml
if exist .\src\drivers\berniw2\7\default.xml copy .\src\drivers\berniw2\7\default.xml .\runtime\drivers\berniw2\7\default.xml
if exist .\src\drivers\berniw2\7\dirt-1.xml copy .\src\drivers\berniw2\7\dirt-1.xml .\runtime\drivers\berniw2\7\dirt-1.xml
if exist .\src\drivers\berniw2\7\dirt-2.xml copy .\src\drivers\berniw2\7\dirt-2.xml .\runtime\drivers\berniw2\7\dirt-2.xml
if exist .\src\drivers\berniw2\7\dirt-3.xml copy .\src\drivers\berniw2\7\dirt-3.xml .\runtime\drivers\berniw2\7\dirt-3.xml
if exist .\src\drivers\berniw2\7\dirt-4.xml copy .\src\drivers\berniw2\7\dirt-4.xml .\runtime\drivers\berniw2\7\dirt-4.xml
if exist .\src\drivers\berniw2\7\dirt-5.xml copy .\src\drivers\berniw2\7\dirt-5.xml .\runtime\drivers\berniw2\7\dirt-5.xml
if exist .\src\drivers\berniw2\7\dirt-6.xml copy .\src\drivers\berniw2\7\dirt-6.xml .\runtime\drivers\berniw2\7\dirt-6.xml
if exist .\src\drivers\berniw2\7\eroad.xml copy .\src\drivers\berniw2\7\eroad.xml .\runtime\drivers\berniw2\7\eroad.xml
if exist .\src\drivers\berniw2\7\e-track-1.xml copy .\src\drivers\berniw2\7\e-track-1.xml .\runtime\drivers\berniw2\7\e-track-1.xml
if exist .\src\drivers\berniw2\7\e-track-2.xml copy .\src\drivers\berniw2\7\e-track-2.xml .\runtime\drivers\berniw2\7\e-track-2.xml
if exist .\src\drivers\berniw2\7\e-track-3.xml copy .\src\drivers\berniw2\7\e-track-3.xml .\runtime\drivers\berniw2\7\e-track-3.xml
if exist .\src\drivers\berniw2\7\e-track-4.xml copy .\src\drivers\berniw2\7\e-track-4.xml .\runtime\drivers\berniw2\7\e-track-4.xml
if exist .\src\drivers\berniw2\7\e-track-5.xml copy .\src\drivers\berniw2\7\e-track-5.xml .\runtime\drivers\berniw2\7\e-track-5.xml
if exist .\src\drivers\berniw2\7\e-track-6.xml copy .\src\drivers\berniw2\7\e-track-6.xml .\runtime\drivers\berniw2\7\e-track-6.xml
if exist .\src\drivers\berniw2\7\g-track-1.xml copy .\src\drivers\berniw2\7\g-track-1.xml .\runtime\drivers\berniw2\7\g-track-1.xml
if exist .\src\drivers\berniw2\7\g-track-2.xml copy .\src\drivers\berniw2\7\g-track-2.xml .\runtime\drivers\berniw2\7\g-track-2.xml
if exist .\src\drivers\berniw2\7\g-track-3.xml copy .\src\drivers\berniw2\7\g-track-3.xml .\runtime\drivers\berniw2\7\g-track-3.xml
if exist .\src\drivers\berniw2\7\michigan.xml copy .\src\drivers\berniw2\7\michigan.xml .\runtime\drivers\berniw2\7\michigan.xml
if exist .\src\drivers\berniw2\7\mixed-1.xml copy .\src\drivers\berniw2\7\mixed-1.xml .\runtime\drivers\berniw2\7\mixed-1.xml
if exist .\src\drivers\berniw2\7\mixed-2.xml copy .\src\drivers\berniw2\7\mixed-2.xml .\runtime\drivers\berniw2\7\mixed-2.xml
if exist .\src\drivers\berniw2\7\spring.xml copy .\src\drivers\berniw2\7\spring.xml .\runtime\drivers\berniw2\7\spring.xml
if exist .\src\drivers\berniw2\7\wheel-1.xml copy .\src\drivers\berniw2\7\wheel-1.xml .\runtime\drivers\berniw2\7\wheel-1.xml

if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers\berniw2\8
if exist .\src\drivers\berniw2\8\clkdtm.rgb copy .\src\drivers\berniw2\8\clkdtm.rgb .\runtime\drivers\berniw2\8\clkdtm.rgb
if exist .\src\drivers\berniw2\8\aalborg.xml copy .\src\drivers\berniw2\8\aalborg.xml .\runtime\drivers\berniw2\8\aalborg.xml
if exist .\src\drivers\berniw2\8\alpine-1.xml copy .\src\drivers\berniw2\8\alpine-1.xml .\runtime\drivers\berniw2\8\alpine-1.xml
if exist .\src\drivers\berniw2\8\a-speedway.xml copy .\src\drivers\berniw2\8\a-speedway.xml .\runtime\drivers\berniw2\8\a-speedway.xml
if exist .\src\drivers\berniw2\8\default.xml copy .\src\drivers\berniw2\8\default.xml .\runtime\drivers\berniw2\8\default.xml
if exist .\src\drivers\berniw2\8\dirt-1.xml copy .\src\drivers\berniw2\8\dirt-1.xml .\runtime\drivers\berniw2\8\dirt-1.xml
if exist .\src\drivers\berniw2\8\dirt-2.xml copy .\src\drivers\berniw2\8\dirt-2.xml .\runtime\drivers\berniw2\8\dirt-2.xml
if exist .\src\drivers\berniw2\8\dirt-3.xml copy .\src\drivers\berniw2\8\dirt-3.xml .\runtime\drivers\berniw2\8\dirt-3.xml
if exist .\src\drivers\berniw2\8\dirt-4.xml copy .\src\drivers\berniw2\8\dirt-4.xml .\runtime\drivers\berniw2\8\dirt-4.xml
if exist .\src\drivers\berniw2\8\dirt-5.xml copy .\src\drivers\berniw2\8\dirt-5.xml .\runtime\drivers\berniw2\8\dirt-5.xml
if exist .\src\drivers\berniw2\8\dirt-6.xml copy .\src\drivers\berniw2\8\dirt-6.xml .\runtime\drivers\berniw2\8\dirt-6.xml
if exist .\src\drivers\berniw2\8\eroad.xml copy .\src\drivers\berniw2\8\eroad.xml .\runtime\drivers\berniw2\8\eroad.xml
if exist .\src\drivers\berniw2\8\e-track-1.xml copy .\src\drivers\berniw2\8\e-track-1.xml .\runtime\drivers\berniw2\8\e-track-1.xml
if exist .\src\drivers\berniw2\8\e-track-2.xml copy .\src\drivers\berniw2\8\e-track-2.xml .\runtime\drivers\berniw2\8\e-track-2.xml
if exist .\src\drivers\berniw2\8\e-track-3.xml copy .\src\drivers\berniw2\8\e-track-3.xml .\runtime\drivers\berniw2\8\e-track-3.xml
if exist .\src\drivers\berniw2\8\e-track-4.xml copy .\src\drivers\berniw2\8\e-track-4.xml .\runtime\drivers\berniw2\8\e-track-4.xml
if exist .\src\drivers\berniw2\8\e-track-5.xml copy .\src\drivers\berniw2\8\e-track-5.xml .\runtime\drivers\berniw2\8\e-track-5.xml
if exist .\src\drivers\berniw2\8\e-track-6.xml copy .\src\drivers\berniw2\8\e-track-6.xml .\runtime\drivers\berniw2\8\e-track-6.xml
if exist .\src\drivers\berniw2\8\g-track-1.xml copy .\src\drivers\berniw2\8\g-track-1.xml .\runtime\drivers\berniw2\8\g-track-1.xml
if exist .\src\drivers\berniw2\8\g-track-2.xml copy .\src\drivers\berniw2\8\g-track-2.xml .\runtime\drivers\berniw2\8\g-track-2.xml
if exist .\src\drivers\berniw2\8\g-track-3.xml copy .\src\drivers\berniw2\8\g-track-3.xml .\runtime\drivers\berniw2\8\g-track-3.xml
if exist .\src\drivers\berniw2\8\michigan.xml copy .\src\drivers\berniw2\8\michigan.xml .\runtime\drivers\berniw2\8\michigan.xml
if exist .\src\drivers\berniw2\8\mixed-1.xml copy .\src\drivers\berniw2\8\mixed-1.xml .\runtime\drivers\berniw2\8\mixed-1.xml
if exist .\src\drivers\berniw2\8\mixed-2.xml copy .\src\drivers\berniw2\8\mixed-2.xml .\runtime\drivers\berniw2\8\mixed-2.xml
if exist .\src\drivers\berniw2\8\spring.xml copy .\src\drivers\berniw2\8\spring.xml .\runtime\drivers\berniw2\8\spring.xml
if exist .\src\drivers\berniw2\8\wheel-1.xml copy .\src\drivers\berniw2\8\wheel-1.xml .\runtime\drivers\berniw2\8\wheel-1.xml

if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers\berniw2\9
if exist .\src\drivers\berniw2\9\mclaren-f1.rgb copy .\src\drivers\berniw2\9\mclaren-f1.rgb .\runtime\drivers\berniw2\9\mclaren-f1.rgb
if exist .\src\drivers\berniw2\9\aalborg.xml copy .\src\drivers\berniw2\9\aalborg.xml .\runtime\drivers\berniw2\9\aalborg.xml
if exist .\src\drivers\berniw2\9\alpine-1.xml copy .\src\drivers\berniw2\9\alpine-1.xml .\runtime\drivers\berniw2\9\alpine-1.xml
if exist .\src\drivers\berniw2\9\a-speedway.xml copy .\src\drivers\berniw2\9\a-speedway.xml .\runtime\drivers\berniw2\9\a-speedway.xml
if exist .\src\drivers\berniw2\9\default.xml copy .\src\drivers\berniw2\9\default.xml .\runtime\drivers\berniw2\9\default.xml
if exist .\src\drivers\berniw2\9\dirt-1.xml copy .\src\drivers\berniw2\9\dirt-1.xml .\runtime\drivers\berniw2\9\dirt-1.xml
if exist .\src\drivers\berniw2\9\dirt-2.xml copy .\src\drivers\berniw2\9\dirt-2.xml .\runtime\drivers\berniw2\9\dirt-2.xml
if exist .\src\drivers\berniw2\9\dirt-3.xml copy .\src\drivers\berniw2\9\dirt-3.xml .\runtime\drivers\berniw2\9\dirt-3.xml
if exist .\src\drivers\berniw2\9\dirt-4.xml copy .\src\drivers\berniw2\9\dirt-4.xml .\runtime\drivers\berniw2\9\dirt-4.xml
if exist .\src\drivers\berniw2\9\dirt-5.xml copy .\src\drivers\berniw2\9\dirt-5.xml .\runtime\drivers\berniw2\9\dirt-5.xml
if exist .\src\drivers\berniw2\9\dirt-6.xml copy .\src\drivers\berniw2\9\dirt-6.xml .\runtime\drivers\berniw2\9\dirt-6.xml
if exist .\src\drivers\berniw2\9\eroad.xml copy .\src\drivers\berniw2\9\eroad.xml .\runtime\drivers\berniw2\9\eroad.xml
if exist .\src\drivers\berniw2\9\e-track-1.xml copy .\src\drivers\berniw2\9\e-track-1.xml .\runtime\drivers\berniw2\9\e-track-1.xml
if exist .\src\drivers\berniw2\9\e-track-2.xml copy .\src\drivers\berniw2\9\e-track-2.xml .\runtime\drivers\berniw2\9\e-track-2.xml
if exist .\src\drivers\berniw2\9\e-track-3.xml copy .\src\drivers\berniw2\9\e-track-3.xml .\runtime\drivers\berniw2\9\e-track-3.xml
if exist .\src\drivers\berniw2\9\e-track-4.xml copy .\src\drivers\berniw2\9\e-track-4.xml .\runtime\drivers\berniw2\9\e-track-4.xml
if exist .\src\drivers\berniw2\9\e-track-5.xml copy .\src\drivers\berniw2\9\e-track-5.xml .\runtime\drivers\berniw2\9\e-track-5.xml
if exist .\src\drivers\berniw2\9\e-track-6.xml copy .\src\drivers\berniw2\9\e-track-6.xml .\runtime\drivers\berniw2\9\e-track-6.xml
if exist .\src\drivers\berniw2\9\g-track-1.xml copy .\src\drivers\berniw2\9\g-track-1.xml .\runtime\drivers\berniw2\9\g-track-1.xml
if exist .\src\drivers\berniw2\9\g-track-2.xml copy .\src\drivers\berniw2\9\g-track-2.xml .\runtime\drivers\berniw2\9\g-track-2.xml
if exist .\src\drivers\berniw2\9\g-track-3.xml copy .\src\drivers\berniw2\9\g-track-3.xml .\runtime\drivers\berniw2\9\g-track-3.xml
if exist .\src\drivers\berniw2\9\michigan.xml copy .\src\drivers\berniw2\9\michigan.xml .\runtime\drivers\berniw2\9\michigan.xml
if exist .\src\drivers\berniw2\9\mixed-1.xml copy .\src\drivers\berniw2\9\mixed-1.xml .\runtime\drivers\berniw2\9\mixed-1.xml
if exist .\src\drivers\berniw2\9\mixed-2.xml copy .\src\drivers\berniw2\9\mixed-2.xml .\runtime\drivers\berniw2\9\mixed-2.xml
if exist .\src\drivers\berniw2\9\spring.xml copy .\src\drivers\berniw2\9\spring.xml .\runtime\drivers\berniw2\9\spring.xml
if exist .\src\drivers\berniw2\9\wheel-1.xml copy .\src\drivers\berniw2\9\wheel-1.xml .\runtime\drivers\berniw2\9\wheel-1.xml

if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\berniw2.xml copy .\src\drivers\berniw2\berniw2.xml .\runtime\drivers\berniw2\berniw2.xml
if exist .\src\drivers\berniw2\logo.rgb copy .\src\drivers\berniw2\logo.rgb .\runtime\drivers\berniw2\logo.rgb
if exist .\src\drivers\berniw2\parameter.dat copy .\src\drivers\berniw2\parameter.dat .\runtime\drivers\berniw2\parameter.dat
if exist .\src\drivers\berniw2\intsinsqr.dat copy .\src\drivers\berniw2\intsinsqr.dat .\runtime\drivers\berniw2\intsinsqr.dat
if exist .\src\drivers\berniw2\intcossqr.dat copy .\src\drivers\berniw2\intcossqr.dat .\runtime\drivers\berniw2\intcossqr.dat

if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtime\drivers\cylos1
if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtime\drivers\cylos1\tracksdata
if exist .\src\drivers\cylos1\tracksdata\car_e-track-3.xml copy .\src\drivers\cylos1\tracksdata\car_e-track-3.xml .\runtime\drivers\cylos1\tracksdata\car_e-track-3.xml
if exist .\src\drivers\cylos1\tracksdata\car_lemans.xml copy .\src\drivers\cylos1\tracksdata\car_lemans.xml .\runtime\drivers\cylos1\tracksdata\car_lemans.xml
if exist .\src\drivers\cylos1\tracksdata\car_test-1.xml copy .\src\drivers\cylos1\tracksdata\car_test-1.xml .\runtime\drivers\cylos1\tracksdata\car_test-1.xml
if exist .\src\drivers\cylos1\tracksdata\lemans.xml copy .\src\drivers\cylos1\tracksdata\lemans.xml .\runtime\drivers\cylos1\tracksdata\lemans.xml
if exist .\src\drivers\cylos1\tracksdata\michigan.xml copy .\src\drivers\cylos1\tracksdata\michigan.xml .\runtime\drivers\cylos1\tracksdata\michigan.xml

if exist .\src\drivers\cylos1\*.* call .\create_dir .\runtime
if exist .\src\drivers\cylos1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\cylos1\*.* call .\create_dir .\runtime\drivers\cylos1
if exist .\src\drivers\cylos1\cylos1.xml copy .\src\drivers\cylos1\cylos1.xml .\runtime\drivers\cylos1\cylos1.xml
if exist .\src\drivers\cylos1\car1.xml copy .\src\drivers\cylos1\car1.xml .\runtime\drivers\cylos1\car1.xml
if exist .\src\drivers\cylos1\cg-nascar-rwd.rgb copy .\src\drivers\cylos1\cg-nascar-rwd.rgb .\runtime\drivers\cylos1\cg-nascar-rwd.rgb
if exist .\src\drivers\cylos1\logo.rgb copy .\src\drivers\cylos1\logo.rgb .\runtime\drivers\cylos1\logo.rgb

if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtime\drivers\cylos1
if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtime\drivers\cylos1\tracksdata
if exist .\src\drivers\cylos2\tracksdata\car_e-track-3.xml copy .\src\drivers\cylos2\tracksdata\car_e-track-3.xml .\runtime\drivers\cylos1\tracksdata\car_e-track-3.xml
if exist .\src\drivers\cylos2\tracksdata\michigan.xml copy .\src\drivers\cylos2\tracksdata\michigan.xml .\runtime\drivers\cylos1\tracksdata\michigan.xml

if exist .\src\drivers\cylos2\*.* call .\create_dir .\runtime
if exist .\src\drivers\cylos2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\cylos2\*.* call .\create_dir .\runtime\drivers\cylos2
if exist .\src\drivers\cylos2\cylos2.xml copy .\src\drivers\cylos2\cylos2.xml .\runtime\drivers\cylos2\cylos2.xml
if exist .\src\drivers\cylos2\car1.xml copy .\src\drivers\cylos2\car1.xml .\runtime\drivers\cylos2\car1.xml
if exist .\src\drivers\cylos2\cg-nascar-rwd.rgb copy .\src\drivers\cylos2\cg-nascar-rwd.rgb .\runtime\drivers\cylos2\cg-nascar-rwd.rgb
if exist .\src\drivers\cylos2\logo.rgb copy .\src\drivers\cylos2\logo.rgb .\runtime\drivers\cylos2\logo.rgb

if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers\damned\1
if exist .\src\drivers\damned\1\car.xml copy .\src\drivers\damned\1\car.xml .\runtime\drivers\damned\1\car.xml
if exist .\src\drivers\damned\1\car-dirt.xml copy .\src\drivers\damned\1\car-dirt.xml .\runtime\drivers\damned\1\car-dirt.xml
if exist .\src\drivers\damned\1\buggy.rgb copy .\src\drivers\damned\1\buggy.rgb .\runtime\drivers\damned\1\buggy.rgb
if exist .\src\drivers\damned\1\logo.rgb copy .\src\drivers\damned\1\logo.rgb .\runtime\drivers\damned\1\logo.rgb

if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtime\drivers\damned\10
if exist .\src\drivers\damned\10\car.xml copy .\src\drivers\damned\10\car.xml .\runtime\drivers\damned\10\car.xml
if exist .\src\drivers\damned\10\logo.rgb copy .\src\drivers\damned\10\logo.rgb .\runtime\drivers\damned\10\logo.rgb
if exist .\src\drivers\damned\10\155-DTM.rgb copy .\src\drivers\damned\10\155-DTM.rgb .\runtime\drivers\damned\10\155-DTM.rgb

if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers\damned\2
if exist .\src\drivers\damned\2\car.xml copy .\src\drivers\damned\2\car.xml .\runtime\drivers\damned\2\car.xml
if exist .\src\drivers\damned\2\car-dirt.xml copy .\src\drivers\damned\2\car-dirt.xml .\runtime\drivers\damned\2\car-dirt.xml
if exist .\src\drivers\damned\2\buggy.rgb copy .\src\drivers\damned\2\buggy.rgb .\runtime\drivers\damned\2\buggy.rgb
if exist .\src\drivers\damned\2\logo.rgb copy .\src\drivers\damned\2\logo.rgb .\runtime\drivers\damned\2\logo.rgb

if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers\damned\3
if exist .\src\drivers\damned\3\p406.rgb copy .\src\drivers\damned\3\p406.rgb .\runtime\drivers\damned\3\p406.rgb
if exist .\src\drivers\damned\3\car.xml copy .\src\drivers\damned\3\car.xml .\runtime\drivers\damned\3\car.xml
if exist .\src\drivers\damned\3\car-dirt.xml copy .\src\drivers\damned\3\car-dirt.xml .\runtime\drivers\damned\3\car-dirt.xml
if exist .\src\drivers\damned\3\logo.rgb copy .\src\drivers\damned\3\logo.rgb .\runtime\drivers\damned\3\logo.rgb

if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers\damned\4
if exist .\src\drivers\damned\4\p406.rgb copy .\src\drivers\damned\4\p406.rgb .\runtime\drivers\damned\4\p406.rgb
if exist .\src\drivers\damned\4\car.xml copy .\src\drivers\damned\4\car.xml .\runtime\drivers\damned\4\car.xml
if exist .\src\drivers\damned\4\car-dirt.xml copy .\src\drivers\damned\4\car-dirt.xml .\runtime\drivers\damned\4\car-dirt.xml
if exist .\src\drivers\damned\4\torcs.rgb copy .\src\drivers\damned\4\torcs.rgb .\runtime\drivers\damned\4\torcs.rgb
if exist .\src\drivers\damned\4\logo.rgb copy .\src\drivers\damned\4\logo.rgb .\runtime\drivers\damned\4\logo.rgb

if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers\damned\5
if exist .\src\drivers\damned\5\car.xml copy .\src\drivers\damned\5\car.xml .\runtime\drivers\damned\5\car.xml
if exist .\src\drivers\damned\5\car-dirt.xml copy .\src\drivers\damned\5\car-dirt.xml .\runtime\drivers\damned\5\car-dirt.xml
if exist .\src\drivers\damned\5\acura-nsx-sz.rgb copy .\src\drivers\damned\5\acura-nsx-sz.rgb .\runtime\drivers\damned\5\acura-nsx-sz.rgb
if exist .\src\drivers\damned\5\logo.rgb copy .\src\drivers\damned\5\logo.rgb .\runtime\drivers\damned\5\logo.rgb

if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers\damned\6
if exist .\src\drivers\damned\6\car.xml copy .\src\drivers\damned\6\car.xml .\runtime\drivers\damned\6\car.xml
if exist .\src\drivers\damned\6\car-dirt.xml copy .\src\drivers\damned\6\car-dirt.xml .\runtime\drivers\damned\6\car-dirt.xml
if exist .\src\drivers\damned\6\logo.rgb copy .\src\drivers\damned\6\logo.rgb .\runtime\drivers\damned\6\logo.rgb

if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers\damned\7
if exist .\src\drivers\damned\7\porsche-gt1.rgb copy .\src\drivers\damned\7\porsche-gt1.rgb .\runtime\drivers\damned\7\porsche-gt1.rgb
if exist .\src\drivers\damned\7\logo.rgb copy .\src\drivers\damned\7\logo.rgb .\runtime\drivers\damned\7\logo.rgb
if exist .\src\drivers\damned\7\car.xml copy .\src\drivers\damned\7\car.xml .\runtime\drivers\damned\7\car.xml
if exist .\src\drivers\damned\7\car-dirt.xml copy .\src\drivers\damned\7\car-dirt.xml .\runtime\drivers\damned\7\car-dirt.xml

if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers\damned\8
if exist .\src\drivers\damned\8\car.xml copy .\src\drivers\damned\8\car.xml .\runtime\drivers\damned\8\car.xml
if exist .\src\drivers\damned\8\logo.rgb copy .\src\drivers\damned\8\logo.rgb .\runtime\drivers\damned\8\logo.rgb
if exist .\src\drivers\damned\8\mclaren-f1.rgb copy .\src\drivers\damned\8\mclaren-f1.rgb .\runtime\drivers\damned\8\mclaren-f1.rgb

if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers\damned\9
if exist .\src\drivers\damned\9\logo.rgb copy .\src\drivers\damned\9\logo.rgb .\runtime\drivers\damned\9\logo.rgb
if exist .\src\drivers\damned\9\car.xml copy .\src\drivers\damned\9\car.xml .\runtime\drivers\damned\9\car.xml
if exist .\src\drivers\damned\9\360-modena.rgb copy .\src\drivers\damned\9\360-modena.rgb .\runtime\drivers\damned\9\360-modena.rgb

if exist .\src\drivers\damned\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\damned.xml copy .\src\drivers\damned\damned.xml .\runtime\drivers\damned\damned.xml
if exist .\src\drivers\damned\car1.xml copy .\src\drivers\damned\car1.xml .\runtime\drivers\damned\car1.xml

if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-1
if exist .\src\drivers\human\tracks\dirt-1\car-torcs.xml copy .\src\drivers\human\tracks\dirt-1\car-torcs.xml .\runtime\drivers\human\tracks\dirt-1\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-2
if exist .\src\drivers\human\tracks\dirt-2\car-torcs.xml copy .\src\drivers\human\tracks\dirt-2\car-torcs.xml .\runtime\drivers\human\tracks\dirt-2\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-3
if exist .\src\drivers\human\tracks\dirt-3\car-torcs.xml copy .\src\drivers\human\tracks\dirt-3\car-torcs.xml .\runtime\drivers\human\tracks\dirt-3\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-4
if exist .\src\drivers\human\tracks\dirt-4\car-torcs.xml copy .\src\drivers\human\tracks\dirt-4\car-torcs.xml .\runtime\drivers\human\tracks\dirt-4\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-5
if exist .\src\drivers\human\tracks\dirt-5\car-torcs.xml copy .\src\drivers\human\tracks\dirt-5\car-torcs.xml .\runtime\drivers\human\tracks\dirt-5\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-6
if exist .\src\drivers\human\tracks\dirt-6\car-porsche-gt3rs.xml copy .\src\drivers\human\tracks\dirt-6\car-porsche-gt3rs.xml .\runtime\drivers\human\tracks\dirt-6\car-porsche-gt3rs.xml
if exist .\src\drivers\human\tracks\dirt-6\car-torcs.xml copy .\src\drivers\human\tracks\dirt-6\car-torcs.xml .\runtime\drivers\human\tracks\dirt-6\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-1
if exist .\src\drivers\human\tracks\e-track-1\car-torcs.xml copy .\src\drivers\human\tracks\e-track-1\car-torcs.xml .\runtime\drivers\human\tracks\e-track-1\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-2
if exist .\src\drivers\human\tracks\e-track-2\car-206W10.xml copy .\src\drivers\human\tracks\e-track-2\car-206W10.xml .\runtime\drivers\human\tracks\e-track-2\car-206W10.xml
if exist .\src\drivers\human\tracks\e-track-2\car-torcs.xml copy .\src\drivers\human\tracks\e-track-2\car-torcs.xml .\runtime\drivers\human\tracks\e-track-2\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-3
if exist .\src\drivers\human\tracks\e-track-3\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-3\car-porsche-gt1.xml .\runtime\drivers\human\tracks\e-track-3\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-3\car-torcs.xml copy .\src\drivers\human\tracks\e-track-3\car-torcs.xml .\runtime\drivers\human\tracks\e-track-3\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-4
if exist .\src\drivers\human\tracks\e-track-4\car-360-modena.xml copy .\src\drivers\human\tracks\e-track-4\car-360-modena.xml .\runtime\drivers\human\tracks\e-track-4\car-360-modena.xml
if exist .\src\drivers\human\tracks\e-track-4\car-mclaren-f1.xml copy .\src\drivers\human\tracks\e-track-4\car-mclaren-f1.xml .\runtime\drivers\human\tracks\e-track-4\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\e-track-4\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-4\car-porsche-gt1.xml .\runtime\drivers\human\tracks\e-track-4\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml copy .\src\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml .\runtime\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml
if exist .\src\drivers\human\tracks\e-track-4\car-torcs.xml copy .\src\drivers\human\tracks\e-track-4\car-torcs.xml .\runtime\drivers\human\tracks\e-track-4\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-5
if exist .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml copy .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml .\runtime\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml
if exist .\src\drivers\human\tracks\e-track-5\car-torcs.xml copy .\src\drivers\human\tracks\e-track-5\car-torcs.xml .\runtime\drivers\human\tracks\e-track-5\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-6
if exist .\src\drivers\human\tracks\e-track-6\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-6\car-porsche-gt1.xml .\runtime\drivers\human\tracks\e-track-6\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-6\car-torcs.xml copy .\src\drivers\human\tracks\e-track-6\car-torcs.xml .\runtime\drivers\human\tracks\e-track-6\car-torcs.xml

if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtime\drivers\human\tracks\g-track-2
if exist .\src\drivers\human\tracks\g-track-2\car-360-modena.xml copy .\src\drivers\human\tracks\g-track-2\car-360-modena.xml .\runtime\drivers\human\tracks\g-track-2\car-360-modena.xml
if exist .\src\drivers\human\tracks\g-track-2\car-mclaren-f1.xml copy .\src\drivers\human\tracks\g-track-2\car-mclaren-f1.xml .\runtime\drivers\human\tracks\g-track-2\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\g-track-2\car-porsche-gt1.xml copy .\src\drivers\human\tracks\g-track-2\car-porsche-gt1.xml .\runtime\drivers\human\tracks\g-track-2\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml copy .\src\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml .\runtime\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml
if exist .\src\drivers\human\tracks\g-track-2\car-torcs.xml copy .\src\drivers\human\tracks\g-track-2\car-torcs.xml .\runtime\drivers\human\tracks\g-track-2\car-torcs.xml

if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtime\drivers\human\tracks\g-track-3
if exist .\src\drivers\human\tracks\g-track-3\car-206W10.xml copy .\src\drivers\human\tracks\g-track-3\car-206W10.xml .\runtime\drivers\human\tracks\g-track-3\car-206W10.xml

if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtime\drivers\human\tracks\mixed-1
if exist .\src\drivers\human\tracks\mixed-1\car-torcs.xml copy .\src\drivers\human\tracks\mixed-1\car-torcs.xml .\runtime\drivers\human\tracks\mixed-1\car-torcs.xml

if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtime\drivers\human\tracks\mixed-2
if exist .\src\drivers\human\tracks\mixed-2\car-torcs.xml copy .\src\drivers\human\tracks\mixed-2\car-torcs.xml .\runtime\drivers\human\tracks\mixed-2\car-torcs.xml

if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtime\drivers\human\tracks\spring
if exist .\src\drivers\human\tracks\spring\car-206W10.xml copy .\src\drivers\human\tracks\spring\car-206W10.xml .\runtime\drivers\human\tracks\spring\car-206W10.xml

if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtime\drivers\human\tracks\wheel-1
if exist .\src\drivers\human\tracks\wheel-1\car-mclaren-f1.xml copy .\src\drivers\human\tracks\wheel-1\car-mclaren-f1.xml .\runtime\drivers\human\tracks\wheel-1\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\wheel-1\car-porsche-gt1.xml copy .\src\drivers\human\tracks\wheel-1\car-porsche-gt1.xml .\runtime\drivers\human\tracks\wheel-1\car-porsche-gt1.xml

if exist .\src\drivers\human\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\car-155-DTM.xml copy .\src\drivers\human\car-155-DTM.xml .\runtime\drivers\human\car-155-DTM.xml
if exist .\src\drivers\human\car-206W10.xml copy .\src\drivers\human\car-206W10.xml .\runtime\drivers\human\car-206W10.xml
if exist .\src\drivers\human\car-360-modena.xml copy .\src\drivers\human\car-360-modena.xml .\runtime\drivers\human\car-360-modena.xml
if exist .\src\drivers\human\car-acura-nsx-sz.xml copy .\src\drivers\human\car-acura-nsx-sz.xml .\runtime\drivers\human\car-acura-nsx-sz.xml
if exist .\src\drivers\human\car-alpha-156-rk.xml copy .\src\drivers\human\car-alpha-156-rk.xml .\runtime\drivers\human\car-alpha-156-rk.xml
if exist .\src\drivers\human\car-buggy.xml copy .\src\drivers\human\car-buggy.xml .\runtime\drivers\human\car-buggy.xml
if exist .\src\drivers\human\car-cg-gt-rwd.xml copy .\src\drivers\human\car-cg-gt-rwd.xml .\runtime\drivers\human\car-cg-gt-rwd.xml
if exist .\src\drivers\human\car-cg-nascar-fwd.xml copy .\src\drivers\human\car-cg-nascar-fwd.xml .\runtime\drivers\human\car-cg-nascar-fwd.xml
if exist .\src\drivers\human\car-cg-nascar-rwd.xml copy .\src\drivers\human\car-cg-nascar-rwd.xml .\runtime\drivers\human\car-cg-nascar-rwd.xml
if exist .\src\drivers\human\car-clkdtm.xml copy .\src\drivers\human\car-clkdtm.xml .\runtime\drivers\human\car-clkdtm.xml
if exist .\src\drivers\human\car-corvette.xml copy .\src\drivers\human\car-corvette.xml .\runtime\drivers\human\car-corvette.xml
if exist .\src\drivers\human\car-fs-02h2.xml copy .\src\drivers\human\car-fs-02h2.xml .\runtime\drivers\human\car-fs-02h2.xml
if exist .\src\drivers\human\car-lotus-gt1.xml copy .\src\drivers\human\car-lotus-gt1.xml .\runtime\drivers\human\car-lotus-gt1.xml
if exist .\src\drivers\human\car-mclaren-f1.xml copy .\src\drivers\human\car-mclaren-f1.xml .\runtime\drivers\human\car-mclaren-f1.xml
if exist .\src\drivers\human\car-p406.xml copy .\src\drivers\human\car-p406.xml .\runtime\drivers\human\car-p406.xml
if exist .\src\drivers\human\car-porsche-gt1.xml copy .\src\drivers\human\car-porsche-gt1.xml .\runtime\drivers\human\car-porsche-gt1.xml
if exist .\src\drivers\human\car-porsche-gt3rs.xml copy .\src\drivers\human\car-porsche-gt3rs.xml .\runtime\drivers\human\car-porsche-gt3rs.xml
if exist .\src\drivers\human\car-torcs.xml copy .\src\drivers\human\car-torcs.xml .\runtime\drivers\human\car-torcs.xml
if exist .\src\drivers\human\car-viper-gts-r.xml copy .\src\drivers\human\car-viper-gts-r.xml .\runtime\drivers\human\car-viper-gts-r.xml
if exist .\src\drivers\human\car-vm-x2.xml copy .\src\drivers\human\car-vm-x2.xml .\runtime\drivers\human\car-vm-x2.xml
if exist .\src\drivers\human\car-vm-x4.xml copy .\src\drivers\human\car-vm-x4.xml .\runtime\drivers\human\car-vm-x4.xml
if exist .\src\drivers\human\car.xml copy .\src\drivers\human\car.xml .\runtime\drivers\human\car.xml
if exist .\src\drivers\human\human.xml copy .\src\drivers\human\human.xml .\runtime\drivers\human\human.xml
if exist .\src\drivers\human\preferences.xml copy .\src\drivers\human\preferences.xml .\runtime\drivers\human\preferences.xml
if exist .\src\drivers\human\logo.rgb copy .\src\drivers\human\logo.rgb .\runtime\drivers\human\logo.rgb
if exist .\src\drivers\human\mclaren-f1.rgb copy .\src\drivers\human\mclaren-f1.rgb .\runtime\drivers\human\mclaren-f1.rgb

if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\1
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\1\tracksdata
if exist .\src\drivers\inferno\1\tracksdata\aalborg.xml copy .\src\drivers\inferno\1\tracksdata\aalborg.xml .\runtime\drivers\inferno\1\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\1\tracksdata\alpine-1.xml copy .\src\drivers\inferno\1\tracksdata\alpine-1.xml .\runtime\drivers\inferno\1\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\1\tracksdata\a-speedway.xml copy .\src\drivers\inferno\1\tracksdata\a-speedway.xml .\runtime\drivers\inferno\1\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\1\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\1\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\1\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\1\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\1\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\car_eroad.xml copy .\src\drivers\inferno\1\tracksdata\car_eroad.xml .\runtime\drivers\inferno\1\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\1\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\1\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\1\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\1\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\1\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\car_michigan.xml copy .\src\drivers\inferno\1\tracksdata\car_michigan.xml .\runtime\drivers\inferno\1\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\1\tracksdata\car_s2.xml copy .\src\drivers\inferno\1\tracksdata\car_s2.xml .\runtime\drivers\inferno\1\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\1\tracksdata\car_test-1.xml copy .\src\drivers\inferno\1\tracksdata\car_test-1.xml .\runtime\drivers\inferno\1\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\1\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\1\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\1\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\1\tracksdata\city-1.xml copy .\src\drivers\inferno\1\tracksdata\city-1.xml .\runtime\drivers\inferno\1\tracksdata\city-1.xml
if exist .\src\drivers\inferno\1\tracksdata\eroad.xml copy .\src\drivers\inferno\1\tracksdata\eroad.xml .\runtime\drivers\inferno\1\tracksdata\eroad.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-1.xml copy .\src\drivers\inferno\1\tracksdata\e-track-1.xml .\runtime\drivers\inferno\1\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-2.xml copy .\src\drivers\inferno\1\tracksdata\e-track-2.xml .\runtime\drivers\inferno\1\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-3.xml copy .\src\drivers\inferno\1\tracksdata\e-track-3.xml .\runtime\drivers\inferno\1\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-4.xml copy .\src\drivers\inferno\1\tracksdata\e-track-4.xml .\runtime\drivers\inferno\1\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-5.xml copy .\src\drivers\inferno\1\tracksdata\e-track-5.xml .\runtime\drivers\inferno\1\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-6.xml copy .\src\drivers\inferno\1\tracksdata\e-track-6.xml .\runtime\drivers\inferno\1\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\1\tracksdata\g-track-1.xml copy .\src\drivers\inferno\1\tracksdata\g-track-1.xml .\runtime\drivers\inferno\1\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\g-track-2.xml copy .\src\drivers\inferno\1\tracksdata\g-track-2.xml .\runtime\drivers\inferno\1\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\michigan.xml copy .\src\drivers\inferno\1\tracksdata\michigan.xml .\runtime\drivers\inferno\1\tracksdata\michigan.xml
if exist .\src\drivers\inferno\1\tracksdata\s2.xml copy .\src\drivers\inferno\1\tracksdata\s2.xml .\runtime\drivers\inferno\1\tracksdata\s2.xml
if exist .\src\drivers\inferno\1\tracksdata\wheel-1.xml copy .\src\drivers\inferno\1\tracksdata\wheel-1.xml .\runtime\drivers\inferno\1\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers\inferno\1
if exist .\src\drivers\inferno\1\defaultcar.xml copy .\src\drivers\inferno\1\defaultcar.xml .\runtime\drivers\inferno\1\defaultcar.xml
if exist .\src\drivers\inferno\1\default.xml copy .\src\drivers\inferno\1\default.xml .\runtime\drivers\inferno\1\default.xml
if exist .\src\drivers\inferno\1\logo.rgb copy .\src\drivers\inferno\1\logo.rgb .\runtime\drivers\inferno\1\logo.rgb
if exist .\src\drivers\inferno\1\Makefile copy .\src\drivers\inferno\1\Makefile .\runtime\drivers\inferno\1\Makefile
if exist .\src\drivers\inferno\1\mclaren-f1.rgb copy .\src\drivers\inferno\1\mclaren-f1.rgb .\runtime\drivers\inferno\1\mclaren-f1.rgb

if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\10
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\10\tracksdata
if exist .\src\drivers\inferno\10\tracksdata\aalborg.xml copy .\src\drivers\inferno\10\tracksdata\aalborg.xml .\runtime\drivers\inferno\10\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\10\tracksdata\a-speedway.xml copy .\src\drivers\inferno\10\tracksdata\a-speedway.xml .\runtime\drivers\inferno\10\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\10\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\10\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\10\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\10\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\10\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\10\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\10\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\10\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\10\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\10\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\10\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\10\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\10\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\10\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\eroad.xml copy .\src\drivers\inferno\10\tracksdata\eroad.xml .\runtime\drivers\inferno\10\tracksdata\eroad.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-1.xml copy .\src\drivers\inferno\10\tracksdata\e-track-1.xml .\runtime\drivers\inferno\10\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-2.xml copy .\src\drivers\inferno\10\tracksdata\e-track-2.xml .\runtime\drivers\inferno\10\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-3.xml copy .\src\drivers\inferno\10\tracksdata\e-track-3.xml .\runtime\drivers\inferno\10\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-4.xml copy .\src\drivers\inferno\10\tracksdata\e-track-4.xml .\runtime\drivers\inferno\10\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-5.xml copy .\src\drivers\inferno\10\tracksdata\e-track-5.xml .\runtime\drivers\inferno\10\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-6.xml copy .\src\drivers\inferno\10\tracksdata\e-track-6.xml .\runtime\drivers\inferno\10\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\10\tracksdata\g-track-1.xml copy .\src\drivers\inferno\10\tracksdata\g-track-1.xml .\runtime\drivers\inferno\10\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\10\tracksdata\g-track-2.xml copy .\src\drivers\inferno\10\tracksdata\g-track-2.xml .\runtime\drivers\inferno\10\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\michigan.xml copy .\src\drivers\inferno\10\tracksdata\michigan.xml .\runtime\drivers\inferno\10\tracksdata\michigan.xml
if exist .\src\drivers\inferno\10\tracksdata\wheel-1.xml copy .\src\drivers\inferno\10\tracksdata\wheel-1.xml .\runtime\drivers\inferno\10\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers\inferno\10
if exist .\src\drivers\inferno\10\defaultcar.xml copy .\src\drivers\inferno\10\defaultcar.xml .\runtime\drivers\inferno\10\defaultcar.xml
if exist .\src\drivers\inferno\10\default.xml copy .\src\drivers\inferno\10\default.xml .\runtime\drivers\inferno\10\default.xml
if exist .\src\drivers\inferno\10\logo.rgb copy .\src\drivers\inferno\10\logo.rgb .\runtime\drivers\inferno\10\logo.rgb
if exist .\src\drivers\inferno\10\Makefile copy .\src\drivers\inferno\10\Makefile .\runtime\drivers\inferno\10\Makefile
if exist .\src\drivers\inferno\10\vm-x4.rgb copy .\src\drivers\inferno\10\vm-x4.rgb .\runtime\drivers\inferno\10\vm-x4.rgb

if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\2
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\2\tracksdata
if exist .\src\drivers\inferno\2\tracksdata\aalborg.xml copy .\src\drivers\inferno\2\tracksdata\aalborg.xml .\runtime\drivers\inferno\2\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\2\tracksdata\a-speedway.xml copy .\src\drivers\inferno\2\tracksdata\a-speedway.xml .\runtime\drivers\inferno\2\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\2\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\2\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\2\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\2\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\2\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\car_eroad.xml copy .\src\drivers\inferno\2\tracksdata\car_eroad.xml .\runtime\drivers\inferno\2\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\2\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\2\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\2\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\2\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\2\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\car_michigan.xml copy .\src\drivers\inferno\2\tracksdata\car_michigan.xml .\runtime\drivers\inferno\2\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\2\tracksdata\car_s2.xml copy .\src\drivers\inferno\2\tracksdata\car_s2.xml .\runtime\drivers\inferno\2\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\2\tracksdata\car_test-1.xml copy .\src\drivers\inferno\2\tracksdata\car_test-1.xml .\runtime\drivers\inferno\2\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\2\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\2\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\2\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\2\tracksdata\eroad.xml copy .\src\drivers\inferno\2\tracksdata\eroad.xml .\runtime\drivers\inferno\2\tracksdata\eroad.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-1.xml copy .\src\drivers\inferno\2\tracksdata\e-track-1.xml .\runtime\drivers\inferno\2\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-2.xml copy .\src\drivers\inferno\2\tracksdata\e-track-2.xml .\runtime\drivers\inferno\2\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-3.xml copy .\src\drivers\inferno\2\tracksdata\e-track-3.xml .\runtime\drivers\inferno\2\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-4.xml copy .\src\drivers\inferno\2\tracksdata\e-track-4.xml .\runtime\drivers\inferno\2\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-5.xml copy .\src\drivers\inferno\2\tracksdata\e-track-5.xml .\runtime\drivers\inferno\2\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-6.xml copy .\src\drivers\inferno\2\tracksdata\e-track-6.xml .\runtime\drivers\inferno\2\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\2\tracksdata\g-track-1.xml copy .\src\drivers\inferno\2\tracksdata\g-track-1.xml .\runtime\drivers\inferno\2\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\g-track-2.xml copy .\src\drivers\inferno\2\tracksdata\g-track-2.xml .\runtime\drivers\inferno\2\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\michigan.xml copy .\src\drivers\inferno\2\tracksdata\michigan.xml .\runtime\drivers\inferno\2\tracksdata\michigan.xml
if exist .\src\drivers\inferno\2\tracksdata\s2.xml copy .\src\drivers\inferno\2\tracksdata\s2.xml .\runtime\drivers\inferno\2\tracksdata\s2.xml
if exist .\src\drivers\inferno\2\tracksdata\wheel-1.xml copy .\src\drivers\inferno\2\tracksdata\wheel-1.xml .\runtime\drivers\inferno\2\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers\inferno\2
if exist .\src\drivers\inferno\2\360-modena.rgb copy .\src\drivers\inferno\2\360-modena.rgb .\runtime\drivers\inferno\2\360-modena.rgb
if exist .\src\drivers\inferno\2\defaultcar.xml copy .\src\drivers\inferno\2\defaultcar.xml .\runtime\drivers\inferno\2\defaultcar.xml
if exist .\src\drivers\inferno\2\default.xml copy .\src\drivers\inferno\2\default.xml .\runtime\drivers\inferno\2\default.xml
if exist .\src\drivers\inferno\2\logo.rgb copy .\src\drivers\inferno\2\logo.rgb .\runtime\drivers\inferno\2\logo.rgb
if exist .\src\drivers\inferno\2\Makefile copy .\src\drivers\inferno\2\Makefile .\runtime\drivers\inferno\2\Makefile

if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\3
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\3\tracksdata
if exist .\src\drivers\inferno\3\tracksdata\aalborg.xml copy .\src\drivers\inferno\3\tracksdata\aalborg.xml .\runtime\drivers\inferno\3\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\3\tracksdata\alpine-1.xml copy .\src\drivers\inferno\3\tracksdata\alpine-1.xml .\runtime\drivers\inferno\3\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\3\tracksdata\a-speedway.xml copy .\src\drivers\inferno\3\tracksdata\a-speedway.xml .\runtime\drivers\inferno\3\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\3\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\3\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\3\tracksdata\car_alpine-1.xml copy .\src\drivers\inferno\3\tracksdata\car_alpine-1.xml .\runtime\drivers\inferno\3\tracksdata\car_alpine-1.xml
if exist .\src\drivers\inferno\3\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\3\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\3\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_eroad.xml copy .\src\drivers\inferno\3\tracksdata\car_eroad.xml .\runtime\drivers\inferno\3\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\3\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\3\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\3\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\3\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\3\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\car_michigan.xml copy .\src\drivers\inferno\3\tracksdata\car_michigan.xml .\runtime\drivers\inferno\3\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\3\tracksdata\car_spring.xml copy .\src\drivers\inferno\3\tracksdata\car_spring.xml .\runtime\drivers\inferno\3\tracksdata\car_spring.xml
if exist .\src\drivers\inferno\3\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\3\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\3\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\3\tracksdata\eroad.xml copy .\src\drivers\inferno\3\tracksdata\eroad.xml .\runtime\drivers\inferno\3\tracksdata\eroad.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-1.xml copy .\src\drivers\inferno\3\tracksdata\e-track-1.xml .\runtime\drivers\inferno\3\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-2.xml copy .\src\drivers\inferno\3\tracksdata\e-track-2.xml .\runtime\drivers\inferno\3\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-3.xml copy .\src\drivers\inferno\3\tracksdata\e-track-3.xml .\runtime\drivers\inferno\3\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-4.xml copy .\src\drivers\inferno\3\tracksdata\e-track-4.xml .\runtime\drivers\inferno\3\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-5.xml copy .\src\drivers\inferno\3\tracksdata\e-track-5.xml .\runtime\drivers\inferno\3\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-6.xml copy .\src\drivers\inferno\3\tracksdata\e-track-6.xml .\runtime\drivers\inferno\3\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\3\tracksdata\g-track-1.xml copy .\src\drivers\inferno\3\tracksdata\g-track-1.xml .\runtime\drivers\inferno\3\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\g-track-2.xml copy .\src\drivers\inferno\3\tracksdata\g-track-2.xml .\runtime\drivers\inferno\3\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\michigan.xml copy .\src\drivers\inferno\3\tracksdata\michigan.xml .\runtime\drivers\inferno\3\tracksdata\michigan.xml
if exist .\src\drivers\inferno\3\tracksdata\spring.xml copy .\src\drivers\inferno\3\tracksdata\spring.xml .\runtime\drivers\inferno\3\tracksdata\spring.xml
if exist .\src\drivers\inferno\3\tracksdata\wheel-1.xml copy .\src\drivers\inferno\3\tracksdata\wheel-1.xml .\runtime\drivers\inferno\3\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers\inferno\3
if exist .\src\drivers\inferno\3\defaultcar.xml copy .\src\drivers\inferno\3\defaultcar.xml .\runtime\drivers\inferno\3\defaultcar.xml
if exist .\src\drivers\inferno\3\default.xml copy .\src\drivers\inferno\3\default.xml .\runtime\drivers\inferno\3\default.xml
if exist .\src\drivers\inferno\3\logo.rgb copy .\src\drivers\inferno\3\logo.rgb .\runtime\drivers\inferno\3\logo.rgb
if exist .\src\drivers\inferno\3\Makefile copy .\src\drivers\inferno\3\Makefile .\runtime\drivers\inferno\3\Makefile
if exist .\src\drivers\inferno\3\porsche-gt1.rgb copy .\src\drivers\inferno\3\porsche-gt1.rgb .\runtime\drivers\inferno\3\porsche-gt1.rgb

if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\4
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\4\tracksdata
if exist .\src\drivers\inferno\4\tracksdata\aalborg.xml copy .\src\drivers\inferno\4\tracksdata\aalborg.xml .\runtime\drivers\inferno\4\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\4\tracksdata\alpine-1.xml copy .\src\drivers\inferno\4\tracksdata\alpine-1.xml .\runtime\drivers\inferno\4\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\4\tracksdata\a-speedway.xml copy .\src\drivers\inferno\4\tracksdata\a-speedway.xml .\runtime\drivers\inferno\4\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\4\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\4\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\4\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\4\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\4\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\car_eroad.xml copy .\src\drivers\inferno\4\tracksdata\car_eroad.xml .\runtime\drivers\inferno\4\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\4\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\4\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\4\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\4\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\4\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\car_g-track-3.xml copy .\src\drivers\inferno\4\tracksdata\car_g-track-3.xml .\runtime\drivers\inferno\4\tracksdata\car_g-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\car_michigan.xml copy .\src\drivers\inferno\4\tracksdata\car_michigan.xml .\runtime\drivers\inferno\4\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\4\tracksdata\car_test-1.xml copy .\src\drivers\inferno\4\tracksdata\car_test-1.xml .\runtime\drivers\inferno\4\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\4\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\4\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\4\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\4\tracksdata\dirt-2.xml copy .\src\drivers\inferno\4\tracksdata\dirt-2.xml .\runtime\drivers\inferno\4\tracksdata\dirt-2.xml
if exist .\src\drivers\inferno\4\tracksdata\eroad.xml copy .\src\drivers\inferno\4\tracksdata\eroad.xml .\runtime\drivers\inferno\4\tracksdata\eroad.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-1.xml copy .\src\drivers\inferno\4\tracksdata\e-track-1.xml .\runtime\drivers\inferno\4\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-2.xml copy .\src\drivers\inferno\4\tracksdata\e-track-2.xml .\runtime\drivers\inferno\4\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-3.xml copy .\src\drivers\inferno\4\tracksdata\e-track-3.xml .\runtime\drivers\inferno\4\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-4.xml copy .\src\drivers\inferno\4\tracksdata\e-track-4.xml .\runtime\drivers\inferno\4\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-5.xml copy .\src\drivers\inferno\4\tracksdata\e-track-5.xml .\runtime\drivers\inferno\4\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-6.xml copy .\src\drivers\inferno\4\tracksdata\e-track-6.xml .\runtime\drivers\inferno\4\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\4\tracksdata\g-track-1.xml copy .\src\drivers\inferno\4\tracksdata\g-track-1.xml .\runtime\drivers\inferno\4\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\g-track-2.xml copy .\src\drivers\inferno\4\tracksdata\g-track-2.xml .\runtime\drivers\inferno\4\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\g-track-3.xml copy .\src\drivers\inferno\4\tracksdata\g-track-3.xml .\runtime\drivers\inferno\4\tracksdata\g-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\michigan.xml copy .\src\drivers\inferno\4\tracksdata\michigan.xml .\runtime\drivers\inferno\4\tracksdata\michigan.xml
if exist .\src\drivers\inferno\4\tracksdata\wheel-1.xml copy .\src\drivers\inferno\4\tracksdata\wheel-1.xml .\runtime\drivers\inferno\4\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers\inferno\4
if exist .\src\drivers\inferno\4\clkdtm.rgb copy .\src\drivers\inferno\4\clkdtm.rgb .\runtime\drivers\inferno\4\clkdtm.rgb
if exist .\src\drivers\inferno\4\defaultcar.xml copy .\src\drivers\inferno\4\defaultcar.xml .\runtime\drivers\inferno\4\defaultcar.xml
if exist .\src\drivers\inferno\4\default.xml copy .\src\drivers\inferno\4\default.xml .\runtime\drivers\inferno\4\default.xml
if exist .\src\drivers\inferno\4\logo.rgb copy .\src\drivers\inferno\4\logo.rgb .\runtime\drivers\inferno\4\logo.rgb
if exist .\src\drivers\inferno\4\Makefile copy .\src\drivers\inferno\4\Makefile .\runtime\drivers\inferno\4\Makefile

if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\5
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\5\tracksdata
if exist .\src\drivers\inferno\5\tracksdata\aalborg.xml copy .\src\drivers\inferno\5\tracksdata\aalborg.xml .\runtime\drivers\inferno\5\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\5\tracksdata\a-speedway.xml copy .\src\drivers\inferno\5\tracksdata\a-speedway.xml .\runtime\drivers\inferno\5\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\5\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\5\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\5\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\5\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\5\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\5\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\5\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\5\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\5\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\5\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\5\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\5\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\5\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\5\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\eroad.xml copy .\src\drivers\inferno\5\tracksdata\eroad.xml .\runtime\drivers\inferno\5\tracksdata\eroad.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-1.xml copy .\src\drivers\inferno\5\tracksdata\e-track-1.xml .\runtime\drivers\inferno\5\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-2.xml copy .\src\drivers\inferno\5\tracksdata\e-track-2.xml .\runtime\drivers\inferno\5\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-3.xml copy .\src\drivers\inferno\5\tracksdata\e-track-3.xml .\runtime\drivers\inferno\5\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-4.xml copy .\src\drivers\inferno\5\tracksdata\e-track-4.xml .\runtime\drivers\inferno\5\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-5.xml copy .\src\drivers\inferno\5\tracksdata\e-track-5.xml .\runtime\drivers\inferno\5\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-6.xml copy .\src\drivers\inferno\5\tracksdata\e-track-6.xml .\runtime\drivers\inferno\5\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\5\tracksdata\g-track-1.xml copy .\src\drivers\inferno\5\tracksdata\g-track-1.xml .\runtime\drivers\inferno\5\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\5\tracksdata\g-track-2.xml copy .\src\drivers\inferno\5\tracksdata\g-track-2.xml .\runtime\drivers\inferno\5\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\michigan.xml copy .\src\drivers\inferno\5\tracksdata\michigan.xml .\runtime\drivers\inferno\5\tracksdata\michigan.xml
if exist .\src\drivers\inferno\5\tracksdata\wheel-1.xml copy .\src\drivers\inferno\5\tracksdata\wheel-1.xml .\runtime\drivers\inferno\5\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers\inferno\5
if exist .\src\drivers\inferno\5\defaultcar.xml copy .\src\drivers\inferno\5\defaultcar.xml .\runtime\drivers\inferno\5\defaultcar.xml
if exist .\src\drivers\inferno\5\default.xml copy .\src\drivers\inferno\5\default.xml .\runtime\drivers\inferno\5\default.xml
if exist .\src\drivers\inferno\5\gt40.rgb copy .\src\drivers\inferno\5\gt40.rgb .\runtime\drivers\inferno\5\gt40.rgb
if exist .\src\drivers\inferno\5\logo.rgb copy .\src\drivers\inferno\5\logo.rgb .\runtime\drivers\inferno\5\logo.rgb
if exist .\src\drivers\inferno\5\Makefile copy .\src\drivers\inferno\5\Makefile .\runtime\drivers\inferno\5\Makefile

if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\6
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\6\tracksdata
if exist .\src\drivers\inferno\6\tracksdata\aalborg.xml copy .\src\drivers\inferno\6\tracksdata\aalborg.xml .\runtime\drivers\inferno\6\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\6\tracksdata\a-speedway.xml copy .\src\drivers\inferno\6\tracksdata\a-speedway.xml .\runtime\drivers\inferno\6\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\6\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\6\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\6\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\6\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\6\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\6\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\6\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\6\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\6\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\6\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\6\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\6\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\6\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\car_g-track-3.xml copy .\src\drivers\inferno\6\tracksdata\car_g-track-3.xml .\runtime\drivers\inferno\6\tracksdata\car_g-track-3.xml
if exist .\src\drivers\inferno\6\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\6\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\6\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\6\tracksdata\eroad.xml copy .\src\drivers\inferno\6\tracksdata\eroad.xml .\runtime\drivers\inferno\6\tracksdata\eroad.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-1.xml copy .\src\drivers\inferno\6\tracksdata\e-track-1.xml .\runtime\drivers\inferno\6\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-2.xml copy .\src\drivers\inferno\6\tracksdata\e-track-2.xml .\runtime\drivers\inferno\6\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-3.xml copy .\src\drivers\inferno\6\tracksdata\e-track-3.xml .\runtime\drivers\inferno\6\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-4.xml copy .\src\drivers\inferno\6\tracksdata\e-track-4.xml .\runtime\drivers\inferno\6\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-5.xml copy .\src\drivers\inferno\6\tracksdata\e-track-5.xml .\runtime\drivers\inferno\6\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-6.xml copy .\src\drivers\inferno\6\tracksdata\e-track-6.xml .\runtime\drivers\inferno\6\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\6\tracksdata\g-track-1.xml copy .\src\drivers\inferno\6\tracksdata\g-track-1.xml .\runtime\drivers\inferno\6\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\6\tracksdata\g-track-2.xml copy .\src\drivers\inferno\6\tracksdata\g-track-2.xml .\runtime\drivers\inferno\6\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\g-track-3.xml copy .\src\drivers\inferno\6\tracksdata\g-track-3.xml .\runtime\drivers\inferno\6\tracksdata\g-track-3.xml
if exist .\src\drivers\inferno\6\tracksdata\michigan.xml copy .\src\drivers\inferno\6\tracksdata\michigan.xml .\runtime\drivers\inferno\6\tracksdata\michigan.xml
if exist .\src\drivers\inferno\6\tracksdata\wheel-1.xml copy .\src\drivers\inferno\6\tracksdata\wheel-1.xml .\runtime\drivers\inferno\6\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers\inferno\6
if exist .\src\drivers\inferno\6\defaultcar.xml copy .\src\drivers\inferno\6\defaultcar.xml .\runtime\drivers\inferno\6\defaultcar.xml
if exist .\src\drivers\inferno\6\default.xml copy .\src\drivers\inferno\6\default.xml .\runtime\drivers\inferno\6\default.xml
if exist .\src\drivers\inferno\6\logo.rgb copy .\src\drivers\inferno\6\logo.rgb .\runtime\drivers\inferno\6\logo.rgb
if exist .\src\drivers\inferno\6\Makefile copy .\src\drivers\inferno\6\Makefile .\runtime\drivers\inferno\6\Makefile
if exist .\src\drivers\inferno\6\porsche-gt3rs.rgb copy .\src\drivers\inferno\6\porsche-gt3rs.rgb .\runtime\drivers\inferno\6\porsche-gt3rs.rgb

if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\7
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\7\tracksdata
if exist .\src\drivers\inferno\7\tracksdata\aalborg.xml copy .\src\drivers\inferno\7\tracksdata\aalborg.xml .\runtime\drivers\inferno\7\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\7\tracksdata\alpine-1.xml copy .\src\drivers\inferno\7\tracksdata\alpine-1.xml .\runtime\drivers\inferno\7\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\7\tracksdata\a-speedway.xml copy .\src\drivers\inferno\7\tracksdata\a-speedway.xml .\runtime\drivers\inferno\7\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\7\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\7\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\7\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\7\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\7\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\car_eroad.xml copy .\src\drivers\inferno\7\tracksdata\car_eroad.xml .\runtime\drivers\inferno\7\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\7\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\7\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\7\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\7\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\7\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\car_michigan.xml copy .\src\drivers\inferno\7\tracksdata\car_michigan.xml .\runtime\drivers\inferno\7\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\7\tracksdata\car_s2.xml copy .\src\drivers\inferno\7\tracksdata\car_s2.xml .\runtime\drivers\inferno\7\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\7\tracksdata\car_test-1.xml copy .\src\drivers\inferno\7\tracksdata\car_test-1.xml .\runtime\drivers\inferno\7\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\7\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\7\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\7\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\7\tracksdata\city-1.xml copy .\src\drivers\inferno\7\tracksdata\city-1.xml .\runtime\drivers\inferno\7\tracksdata\city-1.xml
if exist .\src\drivers\inferno\7\tracksdata\eroad.xml copy .\src\drivers\inferno\7\tracksdata\eroad.xml .\runtime\drivers\inferno\7\tracksdata\eroad.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-1.xml copy .\src\drivers\inferno\7\tracksdata\e-track-1.xml .\runtime\drivers\inferno\7\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-2.xml copy .\src\drivers\inferno\7\tracksdata\e-track-2.xml .\runtime\drivers\inferno\7\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-3.xml copy .\src\drivers\inferno\7\tracksdata\e-track-3.xml .\runtime\drivers\inferno\7\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-4.xml copy .\src\drivers\inferno\7\tracksdata\e-track-4.xml .\runtime\drivers\inferno\7\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-5.xml copy .\src\drivers\inferno\7\tracksdata\e-track-5.xml .\runtime\drivers\inferno\7\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-6.xml copy .\src\drivers\inferno\7\tracksdata\e-track-6.xml .\runtime\drivers\inferno\7\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\7\tracksdata\g-track-1.xml copy .\src\drivers\inferno\7\tracksdata\g-track-1.xml .\runtime\drivers\inferno\7\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\g-track-2.xml copy .\src\drivers\inferno\7\tracksdata\g-track-2.xml .\runtime\drivers\inferno\7\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\michigan.xml copy .\src\drivers\inferno\7\tracksdata\michigan.xml .\runtime\drivers\inferno\7\tracksdata\michigan.xml
if exist .\src\drivers\inferno\7\tracksdata\s2.xml copy .\src\drivers\inferno\7\tracksdata\s2.xml .\runtime\drivers\inferno\7\tracksdata\s2.xml
if exist .\src\drivers\inferno\7\tracksdata\wheel-1.xml copy .\src\drivers\inferno\7\tracksdata\wheel-1.xml .\runtime\drivers\inferno\7\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers\inferno\7
if exist .\src\drivers\inferno\7\defaultcar.xml copy .\src\drivers\inferno\7\defaultcar.xml .\runtime\drivers\inferno\7\defaultcar.xml
if exist .\src\drivers\inferno\7\default.xml copy .\src\drivers\inferno\7\default.xml .\runtime\drivers\inferno\7\default.xml
if exist .\src\drivers\inferno\7\logo.rgb copy .\src\drivers\inferno\7\logo.rgb .\runtime\drivers\inferno\7\logo.rgb
if exist .\src\drivers\inferno\7\lotus-gt1.rgb copy .\src\drivers\inferno\7\lotus-gt1.rgb .\runtime\drivers\inferno\7\lotus-gt1.rgb
if exist .\src\drivers\inferno\7\Makefile copy .\src\drivers\inferno\7\Makefile .\runtime\drivers\inferno\7\Makefile

if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\8
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\8\tracksdata
if exist .\src\drivers\inferno\8\tracksdata\aalborg.xml copy .\src\drivers\inferno\8\tracksdata\aalborg.xml .\runtime\drivers\inferno\8\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\8\tracksdata\alpine-1.xml copy .\src\drivers\inferno\8\tracksdata\alpine-1.xml .\runtime\drivers\inferno\8\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\8\tracksdata\a-speedway.xml copy .\src\drivers\inferno\8\tracksdata\a-speedway.xml .\runtime\drivers\inferno\8\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-1.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-1.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-1.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-2.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-2.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-2.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-3.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-3.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-3.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-4.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-4.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-4.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-5.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-5.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-5.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-6.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-6.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-6.xml
if exist .\src\drivers\inferno\8\tracksdata\car_g-track-3.xml copy .\src\drivers\inferno\8\tracksdata\car_g-track-3.xml .\runtime\drivers\inferno\8\tracksdata\car_g-track-3.xml
if exist .\src\drivers\inferno\8\tracksdata\car_mixed-1.xml copy .\src\drivers\inferno\8\tracksdata\car_mixed-1.xml .\runtime\drivers\inferno\8\tracksdata\car_mixed-1.xml
if exist .\src\drivers\inferno\8\tracksdata\car_mixed-2.xml copy .\src\drivers\inferno\8\tracksdata\car_mixed-2.xml .\runtime\drivers\inferno\8\tracksdata\car_mixed-2.xml
if exist .\src\drivers\inferno\8\tracksdata\eroad.xml copy .\src\drivers\inferno\8\tracksdata\eroad.xml .\runtime\drivers\inferno\8\tracksdata\eroad.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-1.xml copy .\src\drivers\inferno\8\tracksdata\e-track-1.xml .\runtime\drivers\inferno\8\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-2.xml copy .\src\drivers\inferno\8\tracksdata\e-track-2.xml .\runtime\drivers\inferno\8\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-3.xml copy .\src\drivers\inferno\8\tracksdata\e-track-3.xml .\runtime\drivers\inferno\8\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-4.xml copy .\src\drivers\inferno\8\tracksdata\e-track-4.xml .\runtime\drivers\inferno\8\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-5.xml copy .\src\drivers\inferno\8\tracksdata\e-track-5.xml .\runtime\drivers\inferno\8\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-6.xml copy .\src\drivers\inferno\8\tracksdata\e-track-6.xml .\runtime\drivers\inferno\8\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\8\tracksdata\g-track-1.xml copy .\src\drivers\inferno\8\tracksdata\g-track-1.xml .\runtime\drivers\inferno\8\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\8\tracksdata\g-track-2.xml copy .\src\drivers\inferno\8\tracksdata\g-track-2.xml .\runtime\drivers\inferno\8\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\8\tracksdata\g-track-3.xml copy .\src\drivers\inferno\8\tracksdata\g-track-3.xml .\runtime\drivers\inferno\8\tracksdata\g-track-3.xml
if exist .\src\drivers\inferno\8\tracksdata\michigan.xml copy .\src\drivers\inferno\8\tracksdata\michigan.xml .\runtime\drivers\inferno\8\tracksdata\michigan.xml
if exist .\src\drivers\inferno\8\tracksdata\spring.xml copy .\src\drivers\inferno\8\tracksdata\spring.xml .\runtime\drivers\inferno\8\tracksdata\spring.xml
if exist .\src\drivers\inferno\8\tracksdata\wheel-1.xml copy .\src\drivers\inferno\8\tracksdata\wheel-1.xml .\runtime\drivers\inferno\8\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers\inferno\8
if exist .\src\drivers\inferno\8\defaultcar.xml copy .\src\drivers\inferno\8\defaultcar.xml .\runtime\drivers\inferno\8\defaultcar.xml
if exist .\src\drivers\inferno\8\default.xml copy .\src\drivers\inferno\8\default.xml .\runtime\drivers\inferno\8\default.xml
if exist .\src\drivers\inferno\8\logo.rgb copy .\src\drivers\inferno\8\logo.rgb .\runtime\drivers\inferno\8\logo.rgb
if exist .\src\drivers\inferno\8\Makefile copy .\src\drivers\inferno\8\Makefile .\runtime\drivers\inferno\8\Makefile
if exist .\src\drivers\inferno\8\p406.rgb copy .\src\drivers\inferno\8\p406.rgb .\runtime\drivers\inferno\8\p406.rgb

if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\9
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\9\tracksdata
if exist .\src\drivers\inferno\9\tracksdata\aalborg.xml copy .\src\drivers\inferno\9\tracksdata\aalborg.xml .\runtime\drivers\inferno\9\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\9\tracksdata\alpine-1.xml copy .\src\drivers\inferno\9\tracksdata\alpine-1.xml .\runtime\drivers\inferno\9\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\9\tracksdata\a-speedway.xml copy .\src\drivers\inferno\9\tracksdata\a-speedway.xml .\runtime\drivers\inferno\9\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\9\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\9\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\9\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\9\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\9\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\car_eroad.xml copy .\src\drivers\inferno\9\tracksdata\car_eroad.xml .\runtime\drivers\inferno\9\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\9\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\9\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\9\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\9\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\9\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\car_michigan.xml copy .\src\drivers\inferno\9\tracksdata\car_michigan.xml .\runtime\drivers\inferno\9\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\9\tracksdata\car_s2.xml copy .\src\drivers\inferno\9\tracksdata\car_s2.xml .\runtime\drivers\inferno\9\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\9\tracksdata\car_test-1.xml copy .\src\drivers\inferno\9\tracksdata\car_test-1.xml .\runtime\drivers\inferno\9\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\9\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\9\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\9\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\9\tracksdata\city-1.xml copy .\src\drivers\inferno\9\tracksdata\city-1.xml .\runtime\drivers\inferno\9\tracksdata\city-1.xml
if exist .\src\drivers\inferno\9\tracksdata\eroad.xml copy .\src\drivers\inferno\9\tracksdata\eroad.xml .\runtime\drivers\inferno\9\tracksdata\eroad.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-1.xml copy .\src\drivers\inferno\9\tracksdata\e-track-1.xml .\runtime\drivers\inferno\9\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-2.xml copy .\src\drivers\inferno\9\tracksdata\e-track-2.xml .\runtime\drivers\inferno\9\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-3.xml copy .\src\drivers\inferno\9\tracksdata\e-track-3.xml .\runtime\drivers\inferno\9\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-4.xml copy .\src\drivers\inferno\9\tracksdata\e-track-4.xml .\runtime\drivers\inferno\9\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-5.xml copy .\src\drivers\inferno\9\tracksdata\e-track-5.xml .\runtime\drivers\inferno\9\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-6.xml copy .\src\drivers\inferno\9\tracksdata\e-track-6.xml .\runtime\drivers\inferno\9\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\9\tracksdata\g-track-1.xml copy .\src\drivers\inferno\9\tracksdata\g-track-1.xml .\runtime\drivers\inferno\9\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\g-track-2.xml copy .\src\drivers\inferno\9\tracksdata\g-track-2.xml .\runtime\drivers\inferno\9\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\michigan.xml copy .\src\drivers\inferno\9\tracksdata\michigan.xml .\runtime\drivers\inferno\9\tracksdata\michigan.xml
if exist .\src\drivers\inferno\9\tracksdata\s2.xml copy .\src\drivers\inferno\9\tracksdata\s2.xml .\runtime\drivers\inferno\9\tracksdata\s2.xml
if exist .\src\drivers\inferno\9\tracksdata\wheel-1.xml copy .\src\drivers\inferno\9\tracksdata\wheel-1.xml .\runtime\drivers\inferno\9\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers\inferno\9
if exist .\src\drivers\inferno\9\defaultcar.xml copy .\src\drivers\inferno\9\defaultcar.xml .\runtime\drivers\inferno\9\defaultcar.xml
if exist .\src\drivers\inferno\9\default.xml copy .\src\drivers\inferno\9\default.xml .\runtime\drivers\inferno\9\default.xml
if exist .\src\drivers\inferno\9\logo.rgb copy .\src\drivers\inferno\9\logo.rgb .\runtime\drivers\inferno\9\logo.rgb
if exist .\src\drivers\inferno\9\Makefile copy .\src\drivers\inferno\9\Makefile .\runtime\drivers\inferno\9\Makefile
if exist .\src\drivers\inferno\9\vm-x2.rgb copy .\src\drivers\inferno\9\vm-x2.rgb .\runtime\drivers\inferno\9\vm-x2.rgb

if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\inferno.xml copy .\src\drivers\inferno\inferno.xml .\runtime\drivers\inferno\inferno.xml
if exist .\src\drivers\inferno\car1.xml copy .\src\drivers\inferno\car1.xml .\runtime\drivers\inferno\car1.xml
if exist .\src\drivers\inferno\logo.rgb copy .\src\drivers\inferno\logo.rgb .\runtime\drivers\inferno\logo.rgb
if exist .\src\drivers\inferno\mclaren-f1.rgb copy .\src\drivers\inferno\mclaren-f1.rgb .\runtime\drivers\inferno\mclaren-f1.rgb

if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\inferno2.xml copy .\src\drivers\inferno2\inferno2.xml .\runtime\drivers\inferno2\inferno2.xml
if exist .\src\drivers\inferno2\car1.xml copy .\src\drivers\inferno2\car1.xml .\runtime\drivers\inferno2\car1.xml
if exist .\src\drivers\inferno2\logo.rgb copy .\src\drivers\inferno2\logo.rgb .\runtime\drivers\inferno2\logo.rgb

if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtime\drivers\K1999
if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtime\drivers\K1999\1
if exist .\src\drivers\K1999\1\buggy.rgb copy .\src\drivers\K1999\1\buggy.rgb .\runtime\drivers\K1999\1\buggy.rgb
if exist .\src\drivers\K1999\1\settings.xml copy .\src\drivers\K1999\1\settings.xml .\runtime\drivers\K1999\1\settings.xml

if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtime\drivers\K1999
if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtime\drivers\K1999\2
if exist .\src\drivers\K1999\2\cg-nascar-rwd.rgb copy .\src\drivers\K1999\2\cg-nascar-rwd.rgb .\runtime\drivers\K1999\2\cg-nascar-rwd.rgb
if exist .\src\drivers\K1999\2\settings.xml copy .\src\drivers\K1999\2\settings.xml .\runtime\drivers\K1999\2\settings.xml

if exist .\src\drivers\K1999\*.* call .\create_dir .\runtime
if exist .\src\drivers\K1999\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\K1999\*.* call .\create_dir .\runtime\drivers\K1999
if exist .\src\drivers\K1999\K1999.xml copy .\src\drivers\K1999\K1999.xml .\runtime\drivers\K1999\K1999.xml
if exist .\src\drivers\K1999\logo.rgb copy .\src\drivers\K1999\logo.rgb .\runtime\drivers\K1999\logo.rgb

if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtime\drivers\lliaw\tracksdata
if exist .\src\drivers\lliaw\tracksdata\car_e-track-3.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-3.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-3.xml
if exist .\src\drivers\lliaw\tracksdata\car_e-track-4.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-4.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-4.xml
if exist .\src\drivers\lliaw\tracksdata\car_e-track-6.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-6.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-6.xml
if exist .\src\drivers\lliaw\tracksdata\car_eroad.xml copy .\src\drivers\lliaw\tracksdata\car_eroad.xml .\runtime\drivers\lliaw\tracksdata\car_eroad.xml
if exist .\src\drivers\lliaw\tracksdata\car_g-track-3.xml copy .\src\drivers\lliaw\tracksdata\car_g-track-3.xml .\runtime\drivers\lliaw\tracksdata\car_g-track-3.xml

if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\lliaw.xml copy .\src\drivers\lliaw\lliaw.xml .\runtime\drivers\lliaw\lliaw.xml
if exist .\src\drivers\lliaw\car.xml copy .\src\drivers\lliaw\car.xml .\runtime\drivers\lliaw\car.xml
if exist .\src\drivers\lliaw\viper-gts-r.rgb copy .\src\drivers\lliaw\viper-gts-r.rgb .\runtime\drivers\lliaw\viper-gts-r.rgb
if exist .\src\drivers\lliaw\logo.rgb copy .\src\drivers\lliaw\logo.rgb .\runtime\drivers\lliaw\logo.rgb

if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtime
if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtime\drivers\sparkle
if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtime\drivers\sparkle\0
if exist .\src\drivers\sparkle\0\baja-bug.rgb copy .\src\drivers\sparkle\0\baja-bug.rgb .\runtime\drivers\sparkle\0\baja-bug.rgb
if exist .\src\drivers\sparkle\0\default.xml copy .\src\drivers\sparkle\0\default.xml .\runtime\drivers\sparkle\0\default.xml

if exist .\src\drivers\sparkle\*.* call .\create_dir .\runtime
if exist .\src\drivers\sparkle\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\sparkle\*.* call .\create_dir .\runtime\drivers\sparkle
if exist .\src\drivers\sparkle\sparkle.xml copy .\src\drivers\sparkle\sparkle.xml .\runtime\drivers\sparkle\sparkle.xml
if exist .\src\drivers\sparkle\logo.rgb copy .\src\drivers\sparkle\logo.rgb .\runtime\drivers\sparkle\logo.rgb

if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtime\drivers\tanhoj
if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtime\drivers\tanhoj\tracksdata
if exist .\src\drivers\tanhoj\tracksdata\aalborg.xml copy .\src\drivers\tanhoj\tracksdata\aalborg.xml .\runtime\drivers\tanhoj\tracksdata\aalborg.xml
if exist .\src\drivers\tanhoj\tracksdata\a-speedway.xml copy .\src\drivers\tanhoj\tracksdata\a-speedway.xml .\runtime\drivers\tanhoj\tracksdata\a-speedway.xml
if exist .\src\drivers\tanhoj\tracksdata\car_aalborg.xml copy .\src\drivers\tanhoj\tracksdata\car_aalborg.xml .\runtime\drivers\tanhoj\tracksdata\car_aalborg.xml
if exist .\src\drivers\tanhoj\tracksdata\car_a-speedway.xml copy .\src\drivers\tanhoj\tracksdata\car_a-speedway.xml .\runtime\drivers\tanhoj\tracksdata\car_a-speedway.xml
if exist .\src\drivers\tanhoj\tracksdata\car_eroad.xml copy .\src\drivers\tanhoj\tracksdata\car_eroad.xml .\runtime\drivers\tanhoj\tracksdata\car_eroad.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-1.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-1.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-2.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-2.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-2.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-3.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-3.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-4.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-4.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-4.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-5.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-5.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-5.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-6.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-6.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-6.xml
if exist .\src\drivers\tanhoj\tracksdata\car_g-track-1.xml copy .\src\drivers\tanhoj\tracksdata\car_g-track-1.xml .\runtime\drivers\tanhoj\tracksdata\car_g-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\car_g-track-3.xml copy .\src\drivers\tanhoj\tracksdata\car_g-track-3.xml .\runtime\drivers\tanhoj\tracksdata\car_g-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\car_michigan.xml copy .\src\drivers\tanhoj\tracksdata\car_michigan.xml .\runtime\drivers\tanhoj\tracksdata\car_michigan.xml
if exist .\src\drivers\tanhoj\tracksdata\car_s2.xml copy .\src\drivers\tanhoj\tracksdata\car_s2.xml .\runtime\drivers\tanhoj\tracksdata\car_s2.xml
if exist .\src\drivers\tanhoj\tracksdata\car_test-1.xml copy .\src\drivers\tanhoj\tracksdata\car_test-1.xml .\runtime\drivers\tanhoj\tracksdata\car_test-1.xml
if exist .\src\drivers\tanhoj\tracksdata\car_wheel-1.xml copy .\src\drivers\tanhoj\tracksdata\car_wheel-1.xml .\runtime\drivers\tanhoj\tracksdata\car_wheel-1.xml
if exist .\src\drivers\tanhoj\tracksdata\city-1.xml copy .\src\drivers\tanhoj\tracksdata\city-1.xml .\runtime\drivers\tanhoj\tracksdata\city-1.xml
if exist .\src\drivers\tanhoj\tracksdata\dirt-2.xml copy .\src\drivers\tanhoj\tracksdata\dirt-2.xml .\runtime\drivers\tanhoj\tracksdata\dirt-2.xml
if exist .\src\drivers\tanhoj\tracksdata\eroad.xml copy .\src\drivers\tanhoj\tracksdata\eroad.xml .\runtime\drivers\tanhoj\tracksdata\eroad.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-1.xml copy .\src\drivers\tanhoj\tracksdata\e-track-1.xml .\runtime\drivers\tanhoj\tracksdata\e-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-2.xml copy .\src\drivers\tanhoj\tracksdata\e-track-2.xml .\runtime\drivers\tanhoj\tracksdata\e-track-2.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-3.xml copy .\src\drivers\tanhoj\tracksdata\e-track-3.xml .\runtime\drivers\tanhoj\tracksdata\e-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-4.xml copy .\src\drivers\tanhoj\tracksdata\e-track-4.xml .\runtime\drivers\tanhoj\tracksdata\e-track-4.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-5.xml copy .\src\drivers\tanhoj\tracksdata\e-track-5.xml .\runtime\drivers\tanhoj\tracksdata\e-track-5.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-6.xml copy .\src\drivers\tanhoj\tracksdata\e-track-6.xml .\runtime\drivers\tanhoj\tracksdata\e-track-6.xml
if exist .\src\drivers\tanhoj\tracksdata\g-track-1.xml copy .\src\drivers\tanhoj\tracksdata\g-track-1.xml .\runtime\drivers\tanhoj\tracksdata\g-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\g-track-3.xml copy .\src\drivers\tanhoj\tracksdata\g-track-3.xml .\runtime\drivers\tanhoj\tracksdata\g-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\michigan.xml copy .\src\drivers\tanhoj\tracksdata\michigan.xml .\runtime\drivers\tanhoj\tracksdata\michigan.xml
if exist .\src\drivers\tanhoj\tracksdata\s2.xml copy .\src\drivers\tanhoj\tracksdata\s2.xml .\runtime\drivers\tanhoj\tracksdata\s2.xml
if exist .\src\drivers\tanhoj\tracksdata\wheel-1.xml copy .\src\drivers\tanhoj\tracksdata\wheel-1.xml .\runtime\drivers\tanhoj\tracksdata\wheel-1.xml

if exist .\src\drivers\tanhoj\*.* call .\create_dir .\runtime
if exist .\src\drivers\tanhoj\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tanhoj\*.* call .\create_dir .\runtime\drivers\tanhoj
if exist .\src\drivers\tanhoj\tanhoj.xml copy .\src\drivers\tanhoj\tanhoj.xml .\runtime\drivers\tanhoj\tanhoj.xml
if exist .\src\drivers\tanhoj\car1.xml copy .\src\drivers\tanhoj\car1.xml .\runtime\drivers\tanhoj\car1.xml
if exist .\src\drivers\tanhoj\logo.rgb copy .\src\drivers\tanhoj\logo.rgb .\runtime\drivers\tanhoj\logo.rgb
if exist .\src\drivers\tanhoj\cg-nascar-rwd.rgb copy .\src\drivers\tanhoj\cg-nascar-rwd.rgb .\runtime\drivers\tanhoj\cg-nascar-rwd.rgb

if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtime\drivers\tita\tracksdata
if exist .\src\drivers\tita\tracksdata\aalborg.xml copy .\src\drivers\tita\tracksdata\aalborg.xml .\runtime\drivers\tita\tracksdata\aalborg.xml
if exist .\src\drivers\tita\tracksdata\a-speedway.xml copy .\src\drivers\tita\tracksdata\a-speedway.xml .\runtime\drivers\tita\tracksdata\a-speedway.xml
if exist .\src\drivers\tita\tracksdata\car_aalborg.xml copy .\src\drivers\tita\tracksdata\car_aalborg.xml .\runtime\drivers\tita\tracksdata\car_aalborg.xml
if exist .\src\drivers\tita\tracksdata\car_a-speedway.xml copy .\src\drivers\tita\tracksdata\car_a-speedway.xml .\runtime\drivers\tita\tracksdata\car_a-speedway.xml
if exist .\src\drivers\tita\tracksdata\car_eroad.xml copy .\src\drivers\tita\tracksdata\car_eroad.xml .\runtime\drivers\tita\tracksdata\car_eroad.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-1.xml copy .\src\drivers\tita\tracksdata\car_e-track-1.xml .\runtime\drivers\tita\tracksdata\car_e-track-1.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-2.xml copy .\src\drivers\tita\tracksdata\car_e-track-2.xml .\runtime\drivers\tita\tracksdata\car_e-track-2.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-3.xml copy .\src\drivers\tita\tracksdata\car_e-track-3.xml .\runtime\drivers\tita\tracksdata\car_e-track-3.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-4.xml copy .\src\drivers\tita\tracksdata\car_e-track-4.xml .\runtime\drivers\tita\tracksdata\car_e-track-4.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-5.xml copy .\src\drivers\tita\tracksdata\car_e-track-5.xml .\runtime\drivers\tita\tracksdata\car_e-track-5.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-6.xml copy .\src\drivers\tita\tracksdata\car_e-track-6.xml .\runtime\drivers\tita\tracksdata\car_e-track-6.xml
if exist .\src\drivers\tita\tracksdata\car_g-track-1.xml copy .\src\drivers\tita\tracksdata\car_g-track-1.xml .\runtime\drivers\tita\tracksdata\car_g-track-1.xml
if exist .\src\drivers\tita\tracksdata\car_g-track-3.xml copy .\src\drivers\tita\tracksdata\car_g-track-3.xml .\runtime\drivers\tita\tracksdata\car_g-track-3.xml
if exist .\src\drivers\tita\tracksdata\car_michigan.xml copy .\src\drivers\tita\tracksdata\car_michigan.xml .\runtime\drivers\tita\tracksdata\car_michigan.xml
if exist .\src\drivers\tita\tracksdata\car_s2.xml copy .\src\drivers\tita\tracksdata\car_s2.xml .\runtime\drivers\tita\tracksdata\car_s2.xml
if exist .\src\drivers\tita\tracksdata\car_test-1.xml copy .\src\drivers\tita\tracksdata\car_test-1.xml .\runtime\drivers\tita\tracksdata\car_test-1.xml
if exist .\src\drivers\tita\tracksdata\car_wheel-1.xml copy .\src\drivers\tita\tracksdata\car_wheel-1.xml .\runtime\drivers\tita\tracksdata\car_wheel-1.xml
if exist .\src\drivers\tita\tracksdata\city-1.xml copy .\src\drivers\tita\tracksdata\city-1.xml .\runtime\drivers\tita\tracksdata\city-1.xml
if exist .\src\drivers\tita\tracksdata\eroad.xml copy .\src\drivers\tita\tracksdata\eroad.xml .\runtime\drivers\tita\tracksdata\eroad.xml
if exist .\src\drivers\tita\tracksdata\e-track-1.xml copy .\src\drivers\tita\tracksdata\e-track-1.xml .\runtime\drivers\tita\tracksdata\e-track-1.xml
if exist .\src\drivers\tita\tracksdata\e-track-2.xml copy .\src\drivers\tita\tracksdata\e-track-2.xml .\runtime\drivers\tita\tracksdata\e-track-2.xml
if exist .\src\drivers\tita\tracksdata\e-track-3.xml copy .\src\drivers\tita\tracksdata\e-track-3.xml .\runtime\drivers\tita\tracksdata\e-track-3.xml
if exist .\src\drivers\tita\tracksdata\e-track-4.xml copy .\src\drivers\tita\tracksdata\e-track-4.xml .\runtime\drivers\tita\tracksdata\e-track-4.xml
if exist .\src\drivers\tita\tracksdata\e-track-5.xml copy .\src\drivers\tita\tracksdata\e-track-5.xml .\runtime\drivers\tita\tracksdata\e-track-5.xml
if exist .\src\drivers\tita\tracksdata\e-track-6.xml copy .\src\drivers\tita\tracksdata\e-track-6.xml .\runtime\drivers\tita\tracksdata\e-track-6.xml
if exist .\src\drivers\tita\tracksdata\g-track-1.xml copy .\src\drivers\tita\tracksdata\g-track-1.xml .\runtime\drivers\tita\tracksdata\g-track-1.xml
if exist .\src\drivers\tita\tracksdata\g-track-3.xml copy .\src\drivers\tita\tracksdata\g-track-3.xml .\runtime\drivers\tita\tracksdata\g-track-3.xml
if exist .\src\drivers\tita\tracksdata\michigan.xml copy .\src\drivers\tita\tracksdata\michigan.xml .\runtime\drivers\tita\tracksdata\michigan.xml
if exist .\src\drivers\tita\tracksdata\s2.xml copy .\src\drivers\tita\tracksdata\s2.xml .\runtime\drivers\tita\tracksdata\s2.xml
if exist .\src\drivers\tita\tracksdata\wheel-1.xml copy .\src\drivers\tita\tracksdata\wheel-1.xml .\runtime\drivers\tita\tracksdata\wheel-1.xml

if exist .\src\drivers\tita\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\tita.xml copy .\src\drivers\tita\tita.xml .\runtime\drivers\tita\tita.xml
if exist .\src\drivers\tita\car.xml copy .\src\drivers\tita\car.xml .\runtime\drivers\tita\car.xml
if exist .\src\drivers\tita\logo.rgb copy .\src\drivers\tita\logo.rgb .\runtime\drivers\tita\logo.rgb
if exist .\src\drivers\tita\lotus-gt1.rgb copy .\src\drivers\tita\lotus-gt1.rgb .\runtime\drivers\tita\lotus-gt1.rgb

if exist .\src\drivers\tutorial1\*.* call .\create_dir .\runtime
if exist .\src\drivers\tutorial1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tutorial1\*.* call .\create_dir .\runtime\drivers\tutorial1
if exist .\src\drivers\tutorial1\tutorial1.xml copy .\src\drivers\tutorial1\tutorial1.xml .\runtime\drivers\tutorial1\tutorial1.xml

if exist .\src\drivers\tutorial2\*.* call .\create_dir .\runtime
if exist .\src\drivers\tutorial2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tutorial2\*.* call .\create_dir .\runtime\drivers\tutorial2
if exist .\src\drivers\tutorial2\tutorial2.xml copy .\src\drivers\tutorial2\tutorial2.xml .\runtime\drivers\tutorial2\tutorial2.xml

if exist .\src\libs\raceengineclient\*.* call .\create_dir .\runtime
if exist .\src\libs\raceengineclient\*.* call .\create_dir .\runtime\config
if exist .\src\libs\raceengineclient\raceengine.xml copy .\src\libs\raceengineclient\raceengine.xml .\runtime\config\raceengine.xml

if exist .\src\libs\tgf\*.* call .\create_dir .\runtime
if exist .\src\libs\tgf\*.* call .\create_dir .\runtime\config
if exist .\src\libs\tgf\params.dtd copy .\src\libs\tgf\params.dtd .\runtime\config\params.dtd

if exist .\src\libs\tgfclient\*.* call .\create_dir .\runtime
if exist .\src\libs\tgfclient\*.* call .\create_dir .\runtime\config
if exist .\src\libs\tgfclient\screen.xml copy .\src\libs\tgfclient\screen.xml .\runtime\config\screen.xml

if exist .\src\modules\graphic\ssggraph\*.* call .\create_dir .\runtime
if exist .\src\modules\graphic\ssggraph\*.* call .\create_dir .\runtime\config
if exist .\src\modules\graphic\ssggraph\graph.xml copy .\src\modules\graphic\ssggraph\graph.xml .\runtime\config\graph.xml

if exist .\src\modules\telemetry\*.* call .\create_dir .\runtime
if exist .\src\modules\telemetry\*.* call .\create_dir .\runtime\telemetry
if exist .\src\modules\telemetry\telemetry.sh copy .\src\modules\telemetry\telemetry.sh .\runtime\telemetry\telemetry.sh

if exist .\src\raceman\*.* call .\create_dir .\runtime
if exist .\src\raceman\*.* call .\create_dir .\runtime\config
if exist .\src\raceman\*.* call .\create_dir .\runtime\config\raceman
if exist .\src\raceman\champ.xml copy .\src\raceman\champ.xml .\runtime\config\raceman\champ.xml
if exist .\src\raceman\dtmrace.xml copy .\src\raceman\dtmrace.xml .\runtime\config\raceman\dtmrace.xml
if exist .\src\raceman\endrace.xml copy .\src\raceman\endrace.xml .\runtime\config\raceman\endrace.xml
if exist .\src\raceman\ncrace.xml copy .\src\raceman\ncrace.xml .\runtime\config\raceman\ncrace.xml
if exist .\src\raceman\practice.xml copy .\src\raceman\practice.xml .\runtime\config\raceman\practice.xml
if exist .\src\raceman\quickrace.xml copy .\src\raceman\quickrace.xml .\runtime\config\raceman\quickrace.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\champ

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\dtmrace

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\endrace

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\ncrace

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\practice

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\quickrace

if exist .\src\drivers\astigot\0\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\0\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\0\practice\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\0\practice\*.* call .\create_dir .\runtime\drivers\astigot\0
if exist .\src\drivers\astigot\0\practice\*.* call .\create_dir .\runtime\drivers\astigot\0\practice
if exist .\src\drivers\astigot\0\practice\aalborg.xml copy .\src\drivers\astigot\0\practice\aalborg.xml .\runtime\drivers\astigot\0\practice\aalborg.xml
if exist .\src\drivers\astigot\0\practice\alpine-1.xml copy .\src\drivers\astigot\0\practice\alpine-1.xml .\runtime\drivers\astigot\0\practice\alpine-1.xml
if exist .\src\drivers\astigot\0\practice\a-speedway.xml copy .\src\drivers\astigot\0\practice\a-speedway.xml .\runtime\drivers\astigot\0\practice\a-speedway.xml
if exist .\src\drivers\astigot\0\practice\eroad.xml copy .\src\drivers\astigot\0\practice\eroad.xml .\runtime\drivers\astigot\0\practice\eroad.xml
if exist .\src\drivers\astigot\0\practice\e-track-1.xml copy .\src\drivers\astigot\0\practice\e-track-1.xml .\runtime\drivers\astigot\0\practice\e-track-1.xml
if exist .\src\drivers\astigot\0\practice\e-track-2.xml copy .\src\drivers\astigot\0\practice\e-track-2.xml .\runtime\drivers\astigot\0\practice\e-track-2.xml
if exist .\src\drivers\astigot\0\practice\e-track-3.xml copy .\src\drivers\astigot\0\practice\e-track-3.xml .\runtime\drivers\astigot\0\practice\e-track-3.xml
if exist .\src\drivers\astigot\0\practice\e-track-4.xml copy .\src\drivers\astigot\0\practice\e-track-4.xml .\runtime\drivers\astigot\0\practice\e-track-4.xml
if exist .\src\drivers\astigot\0\practice\e-track-5.xml copy .\src\drivers\astigot\0\practice\e-track-5.xml .\runtime\drivers\astigot\0\practice\e-track-5.xml
if exist .\src\drivers\astigot\0\practice\e-track-6.xml copy .\src\drivers\astigot\0\practice\e-track-6.xml .\runtime\drivers\astigot\0\practice\e-track-6.xml
if exist .\src\drivers\astigot\0\practice\g-track-1.xml copy .\src\drivers\astigot\0\practice\g-track-1.xml .\runtime\drivers\astigot\0\practice\g-track-1.xml
if exist .\src\drivers\astigot\0\practice\g-track-2.xml copy .\src\drivers\astigot\0\practice\g-track-2.xml .\runtime\drivers\astigot\0\practice\g-track-2.xml
if exist .\src\drivers\astigot\0\practice\g-track-3.xml copy .\src\drivers\astigot\0\practice\g-track-3.xml .\runtime\drivers\astigot\0\practice\g-track-3.xml
if exist .\src\drivers\astigot\0\practice\michigan.xml copy .\src\drivers\astigot\0\practice\michigan.xml .\runtime\drivers\astigot\0\practice\michigan.xml
if exist .\src\drivers\astigot\0\practice\wheel-1.xml copy .\src\drivers\astigot\0\practice\wheel-1.xml .\runtime\drivers\astigot\0\practice\wheel-1.xml

if exist .\src\drivers\astigot\0\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\0\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\0\qualifying\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\0\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\0
if exist .\src\drivers\astigot\0\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\0\qualifying
if exist .\src\drivers\astigot\0\qualifying\aalborg.xml copy .\src\drivers\astigot\0\qualifying\aalborg.xml .\runtime\drivers\astigot\0\qualifying\aalborg.xml
if exist .\src\drivers\astigot\0\qualifying\alpine-1.xml copy .\src\drivers\astigot\0\qualifying\alpine-1.xml .\runtime\drivers\astigot\0\qualifying\alpine-1.xml
if exist .\src\drivers\astigot\0\qualifying\a-speedway.xml copy .\src\drivers\astigot\0\qualifying\a-speedway.xml .\runtime\drivers\astigot\0\qualifying\a-speedway.xml
if exist .\src\drivers\astigot\0\qualifying\eroad.xml copy .\src\drivers\astigot\0\qualifying\eroad.xml .\runtime\drivers\astigot\0\qualifying\eroad.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-1.xml copy .\src\drivers\astigot\0\qualifying\e-track-1.xml .\runtime\drivers\astigot\0\qualifying\e-track-1.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-2.xml copy .\src\drivers\astigot\0\qualifying\e-track-2.xml .\runtime\drivers\astigot\0\qualifying\e-track-2.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-3.xml copy .\src\drivers\astigot\0\qualifying\e-track-3.xml .\runtime\drivers\astigot\0\qualifying\e-track-3.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-4.xml copy .\src\drivers\astigot\0\qualifying\e-track-4.xml .\runtime\drivers\astigot\0\qualifying\e-track-4.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-5.xml copy .\src\drivers\astigot\0\qualifying\e-track-5.xml .\runtime\drivers\astigot\0\qualifying\e-track-5.xml
if exist .\src\drivers\astigot\0\qualifying\e-track-6.xml copy .\src\drivers\astigot\0\qualifying\e-track-6.xml .\runtime\drivers\astigot\0\qualifying\e-track-6.xml
if exist .\src\drivers\astigot\0\qualifying\g-track-1.xml copy .\src\drivers\astigot\0\qualifying\g-track-1.xml .\runtime\drivers\astigot\0\qualifying\g-track-1.xml
if exist .\src\drivers\astigot\0\qualifying\g-track-2.xml copy .\src\drivers\astigot\0\qualifying\g-track-2.xml .\runtime\drivers\astigot\0\qualifying\g-track-2.xml
if exist .\src\drivers\astigot\0\qualifying\g-track-3.xml copy .\src\drivers\astigot\0\qualifying\g-track-3.xml .\runtime\drivers\astigot\0\qualifying\g-track-3.xml
if exist .\src\drivers\astigot\0\qualifying\michigan.xml copy .\src\drivers\astigot\0\qualifying\michigan.xml .\runtime\drivers\astigot\0\qualifying\michigan.xml
if exist .\src\drivers\astigot\0\qualifying\wheel-1.xml copy .\src\drivers\astigot\0\qualifying\wheel-1.xml .\runtime\drivers\astigot\0\qualifying\wheel-1.xml

if exist .\src\drivers\astigot\0\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\0\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\0\race\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\0\race\*.* call .\create_dir .\runtime\drivers\astigot\0
if exist .\src\drivers\astigot\0\race\*.* call .\create_dir .\runtime\drivers\astigot\0\race
if exist .\src\drivers\astigot\0\race\aalborg.xml copy .\src\drivers\astigot\0\race\aalborg.xml .\runtime\drivers\astigot\0\race\aalborg.xml
if exist .\src\drivers\astigot\0\race\alpine-1.xml copy .\src\drivers\astigot\0\race\alpine-1.xml .\runtime\drivers\astigot\0\race\alpine-1.xml
if exist .\src\drivers\astigot\0\race\a-speedway.xml copy .\src\drivers\astigot\0\race\a-speedway.xml .\runtime\drivers\astigot\0\race\a-speedway.xml
if exist .\src\drivers\astigot\0\race\eroad.xml copy .\src\drivers\astigot\0\race\eroad.xml .\runtime\drivers\astigot\0\race\eroad.xml
if exist .\src\drivers\astigot\0\race\e-track-1.xml copy .\src\drivers\astigot\0\race\e-track-1.xml .\runtime\drivers\astigot\0\race\e-track-1.xml
if exist .\src\drivers\astigot\0\race\e-track-2.xml copy .\src\drivers\astigot\0\race\e-track-2.xml .\runtime\drivers\astigot\0\race\e-track-2.xml
if exist .\src\drivers\astigot\0\race\e-track-3.xml copy .\src\drivers\astigot\0\race\e-track-3.xml .\runtime\drivers\astigot\0\race\e-track-3.xml
if exist .\src\drivers\astigot\0\race\e-track-4.xml copy .\src\drivers\astigot\0\race\e-track-4.xml .\runtime\drivers\astigot\0\race\e-track-4.xml
if exist .\src\drivers\astigot\0\race\e-track-5.xml copy .\src\drivers\astigot\0\race\e-track-5.xml .\runtime\drivers\astigot\0\race\e-track-5.xml
if exist .\src\drivers\astigot\0\race\e-track-6.xml copy .\src\drivers\astigot\0\race\e-track-6.xml .\runtime\drivers\astigot\0\race\e-track-6.xml
if exist .\src\drivers\astigot\0\race\g-track-1.xml copy .\src\drivers\astigot\0\race\g-track-1.xml .\runtime\drivers\astigot\0\race\g-track-1.xml
if exist .\src\drivers\astigot\0\race\g-track-2.xml copy .\src\drivers\astigot\0\race\g-track-2.xml .\runtime\drivers\astigot\0\race\g-track-2.xml
if exist .\src\drivers\astigot\0\race\g-track-3.xml copy .\src\drivers\astigot\0\race\g-track-3.xml .\runtime\drivers\astigot\0\race\g-track-3.xml
if exist .\src\drivers\astigot\0\race\michigan.xml copy .\src\drivers\astigot\0\race\michigan.xml .\runtime\drivers\astigot\0\race\michigan.xml
if exist .\src\drivers\astigot\0\race\wheel-1.xml copy .\src\drivers\astigot\0\race\wheel-1.xml .\runtime\drivers\astigot\0\race\wheel-1.xml

if exist .\src\drivers\astigot\0\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\0\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\0\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\0\*.* call .\create_dir .\runtime\drivers\astigot\0
if exist .\src\drivers\astigot\0\default.xml copy .\src\drivers\astigot\0\default.xml .\runtime\drivers\astigot\0\default.xml
if exist .\src\drivers\astigot\0\cg-nascar-rwd.rgb copy .\src\drivers\astigot\0\cg-nascar-rwd.rgb .\runtime\drivers\astigot\0\cg-nascar-rwd.rgb

if exist .\src\drivers\astigot\1\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\1\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\1\practice\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\1\practice\*.* call .\create_dir .\runtime\drivers\astigot\1
if exist .\src\drivers\astigot\1\practice\*.* call .\create_dir .\runtime\drivers\astigot\1\practice
if exist .\src\drivers\astigot\1\practice\aalborg.xml copy .\src\drivers\astigot\1\practice\aalborg.xml .\runtime\drivers\astigot\1\practice\aalborg.xml
if exist .\src\drivers\astigot\1\practice\alpine-1.xml copy .\src\drivers\astigot\1\practice\alpine-1.xml .\runtime\drivers\astigot\1\practice\alpine-1.xml
if exist .\src\drivers\astigot\1\practice\eroad.xml copy .\src\drivers\astigot\1\practice\eroad.xml .\runtime\drivers\astigot\1\practice\eroad.xml
if exist .\src\drivers\astigot\1\practice\e-track-1.xml copy .\src\drivers\astigot\1\practice\e-track-1.xml .\runtime\drivers\astigot\1\practice\e-track-1.xml
if exist .\src\drivers\astigot\1\practice\e-track-2.xml copy .\src\drivers\astigot\1\practice\e-track-2.xml .\runtime\drivers\astigot\1\practice\e-track-2.xml
if exist .\src\drivers\astigot\1\practice\e-track-3.xml copy .\src\drivers\astigot\1\practice\e-track-3.xml .\runtime\drivers\astigot\1\practice\e-track-3.xml
if exist .\src\drivers\astigot\1\practice\e-track-4.xml copy .\src\drivers\astigot\1\practice\e-track-4.xml .\runtime\drivers\astigot\1\practice\e-track-4.xml
if exist .\src\drivers\astigot\1\practice\e-track-6.xml copy .\src\drivers\astigot\1\practice\e-track-6.xml .\runtime\drivers\astigot\1\practice\e-track-6.xml
if exist .\src\drivers\astigot\1\practice\g-track-2.xml copy .\src\drivers\astigot\1\practice\g-track-2.xml .\runtime\drivers\astigot\1\practice\g-track-2.xml
if exist .\src\drivers\astigot\1\practice\g-track-3.xml copy .\src\drivers\astigot\1\practice\g-track-3.xml .\runtime\drivers\astigot\1\practice\g-track-3.xml
if exist .\src\drivers\astigot\1\practice\wheel-1.xml copy .\src\drivers\astigot\1\practice\wheel-1.xml .\runtime\drivers\astigot\1\practice\wheel-1.xml

if exist .\src\drivers\astigot\1\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\1\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\1\qualifying\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\1\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\1
if exist .\src\drivers\astigot\1\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\1\qualifying
if exist .\src\drivers\astigot\1\qualifying\aalborg.xml copy .\src\drivers\astigot\1\qualifying\aalborg.xml .\runtime\drivers\astigot\1\qualifying\aalborg.xml
if exist .\src\drivers\astigot\1\qualifying\alpine-1.xml copy .\src\drivers\astigot\1\qualifying\alpine-1.xml .\runtime\drivers\astigot\1\qualifying\alpine-1.xml
if exist .\src\drivers\astigot\1\qualifying\eroad.xml copy .\src\drivers\astigot\1\qualifying\eroad.xml .\runtime\drivers\astigot\1\qualifying\eroad.xml
if exist .\src\drivers\astigot\1\qualifying\e-track-1.xml copy .\src\drivers\astigot\1\qualifying\e-track-1.xml .\runtime\drivers\astigot\1\qualifying\e-track-1.xml
if exist .\src\drivers\astigot\1\qualifying\e-track-2.xml copy .\src\drivers\astigot\1\qualifying\e-track-2.xml .\runtime\drivers\astigot\1\qualifying\e-track-2.xml
if exist .\src\drivers\astigot\1\qualifying\e-track-3.xml copy .\src\drivers\astigot\1\qualifying\e-track-3.xml .\runtime\drivers\astigot\1\qualifying\e-track-3.xml
if exist .\src\drivers\astigot\1\qualifying\e-track-4.xml copy .\src\drivers\astigot\1\qualifying\e-track-4.xml .\runtime\drivers\astigot\1\qualifying\e-track-4.xml
if exist .\src\drivers\astigot\1\qualifying\e-track-6.xml copy .\src\drivers\astigot\1\qualifying\e-track-6.xml .\runtime\drivers\astigot\1\qualifying\e-track-6.xml
if exist .\src\drivers\astigot\1\qualifying\g-track-2.xml copy .\src\drivers\astigot\1\qualifying\g-track-2.xml .\runtime\drivers\astigot\1\qualifying\g-track-2.xml
if exist .\src\drivers\astigot\1\qualifying\g-track-3.xml copy .\src\drivers\astigot\1\qualifying\g-track-3.xml .\runtime\drivers\astigot\1\qualifying\g-track-3.xml
if exist .\src\drivers\astigot\1\qualifying\wheel-1.xml copy .\src\drivers\astigot\1\qualifying\wheel-1.xml .\runtime\drivers\astigot\1\qualifying\wheel-1.xml

if exist .\src\drivers\astigot\1\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\1\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\1\race\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\1\race\*.* call .\create_dir .\runtime\drivers\astigot\1
if exist .\src\drivers\astigot\1\race\*.* call .\create_dir .\runtime\drivers\astigot\1\race
if exist .\src\drivers\astigot\1\race\aalborg.xml copy .\src\drivers\astigot\1\race\aalborg.xml .\runtime\drivers\astigot\1\race\aalborg.xml
if exist .\src\drivers\astigot\1\race\alpine-1.xml copy .\src\drivers\astigot\1\race\alpine-1.xml .\runtime\drivers\astigot\1\race\alpine-1.xml
if exist .\src\drivers\astigot\1\race\eroad.xml copy .\src\drivers\astigot\1\race\eroad.xml .\runtime\drivers\astigot\1\race\eroad.xml
if exist .\src\drivers\astigot\1\race\e-track-1.xml copy .\src\drivers\astigot\1\race\e-track-1.xml .\runtime\drivers\astigot\1\race\e-track-1.xml
if exist .\src\drivers\astigot\1\race\e-track-2.xml copy .\src\drivers\astigot\1\race\e-track-2.xml .\runtime\drivers\astigot\1\race\e-track-2.xml
if exist .\src\drivers\astigot\1\race\e-track-3.xml copy .\src\drivers\astigot\1\race\e-track-3.xml .\runtime\drivers\astigot\1\race\e-track-3.xml
if exist .\src\drivers\astigot\1\race\e-track-4.xml copy .\src\drivers\astigot\1\race\e-track-4.xml .\runtime\drivers\astigot\1\race\e-track-4.xml
if exist .\src\drivers\astigot\1\race\e-track-6.xml copy .\src\drivers\astigot\1\race\e-track-6.xml .\runtime\drivers\astigot\1\race\e-track-6.xml
if exist .\src\drivers\astigot\1\race\g-track-2.xml copy .\src\drivers\astigot\1\race\g-track-2.xml .\runtime\drivers\astigot\1\race\g-track-2.xml
if exist .\src\drivers\astigot\1\race\g-track-3.xml copy .\src\drivers\astigot\1\race\g-track-3.xml .\runtime\drivers\astigot\1\race\g-track-3.xml
if exist .\src\drivers\astigot\1\race\wheel-1.xml copy .\src\drivers\astigot\1\race\wheel-1.xml .\runtime\drivers\astigot\1\race\wheel-1.xml

if exist .\src\drivers\astigot\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\1\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\1\*.* call .\create_dir .\runtime\drivers\astigot\1
if exist .\src\drivers\astigot\1\default.xml copy .\src\drivers\astigot\1\default.xml .\runtime\drivers\astigot\1\default.xml
if exist .\src\drivers\astigot\1\viper-gts-r.rgb copy .\src\drivers\astigot\1\viper-gts-r.rgb .\runtime\drivers\astigot\1\viper-gts-r.rgb

if exist .\src\drivers\astigot\2\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\2\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\2\practice\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\2\practice\*.* call .\create_dir .\runtime\drivers\astigot\2
if exist .\src\drivers\astigot\2\practice\*.* call .\create_dir .\runtime\drivers\astigot\2\practice
if exist .\src\drivers\astigot\2\practice\aalborg.xml copy .\src\drivers\astigot\2\practice\aalborg.xml .\runtime\drivers\astigot\2\practice\aalborg.xml
if exist .\src\drivers\astigot\2\practice\alpine-1.xml copy .\src\drivers\astigot\2\practice\alpine-1.xml .\runtime\drivers\astigot\2\practice\alpine-1.xml
if exist .\src\drivers\astigot\2\practice\eroad.xml copy .\src\drivers\astigot\2\practice\eroad.xml .\runtime\drivers\astigot\2\practice\eroad.xml
if exist .\src\drivers\astigot\2\practice\e-track-1.xml copy .\src\drivers\astigot\2\practice\e-track-1.xml .\runtime\drivers\astigot\2\practice\e-track-1.xml
if exist .\src\drivers\astigot\2\practice\e-track-2.xml copy .\src\drivers\astigot\2\practice\e-track-2.xml .\runtime\drivers\astigot\2\practice\e-track-2.xml
if exist .\src\drivers\astigot\2\practice\e-track-3.xml copy .\src\drivers\astigot\2\practice\e-track-3.xml .\runtime\drivers\astigot\2\practice\e-track-3.xml
if exist .\src\drivers\astigot\2\practice\e-track-4.xml copy .\src\drivers\astigot\2\practice\e-track-4.xml .\runtime\drivers\astigot\2\practice\e-track-4.xml
if exist .\src\drivers\astigot\2\practice\e-track-6.xml copy .\src\drivers\astigot\2\practice\e-track-6.xml .\runtime\drivers\astigot\2\practice\e-track-6.xml
if exist .\src\drivers\astigot\2\practice\g-track-2.xml copy .\src\drivers\astigot\2\practice\g-track-2.xml .\runtime\drivers\astigot\2\practice\g-track-2.xml
if exist .\src\drivers\astigot\2\practice\g-track-3.xml copy .\src\drivers\astigot\2\practice\g-track-3.xml .\runtime\drivers\astigot\2\practice\g-track-3.xml
if exist .\src\drivers\astigot\2\practice\wheel-1.xml copy .\src\drivers\astigot\2\practice\wheel-1.xml .\runtime\drivers\astigot\2\practice\wheel-1.xml

if exist .\src\drivers\astigot\2\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\2\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\2\qualifying\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\2\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\2
if exist .\src\drivers\astigot\2\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\2\qualifying
if exist .\src\drivers\astigot\2\qualifying\aalborg.xml copy .\src\drivers\astigot\2\qualifying\aalborg.xml .\runtime\drivers\astigot\2\qualifying\aalborg.xml
if exist .\src\drivers\astigot\2\qualifying\alpine-1.xml copy .\src\drivers\astigot\2\qualifying\alpine-1.xml .\runtime\drivers\astigot\2\qualifying\alpine-1.xml
if exist .\src\drivers\astigot\2\qualifying\eroad.xml copy .\src\drivers\astigot\2\qualifying\eroad.xml .\runtime\drivers\astigot\2\qualifying\eroad.xml
if exist .\src\drivers\astigot\2\qualifying\e-track-1.xml copy .\src\drivers\astigot\2\qualifying\e-track-1.xml .\runtime\drivers\astigot\2\qualifying\e-track-1.xml
if exist .\src\drivers\astigot\2\qualifying\e-track-2.xml copy .\src\drivers\astigot\2\qualifying\e-track-2.xml .\runtime\drivers\astigot\2\qualifying\e-track-2.xml
if exist .\src\drivers\astigot\2\qualifying\e-track-3.xml copy .\src\drivers\astigot\2\qualifying\e-track-3.xml .\runtime\drivers\astigot\2\qualifying\e-track-3.xml
if exist .\src\drivers\astigot\2\qualifying\e-track-4.xml copy .\src\drivers\astigot\2\qualifying\e-track-4.xml .\runtime\drivers\astigot\2\qualifying\e-track-4.xml
if exist .\src\drivers\astigot\2\qualifying\e-track-6.xml copy .\src\drivers\astigot\2\qualifying\e-track-6.xml .\runtime\drivers\astigot\2\qualifying\e-track-6.xml
if exist .\src\drivers\astigot\2\qualifying\g-track-2.xml copy .\src\drivers\astigot\2\qualifying\g-track-2.xml .\runtime\drivers\astigot\2\qualifying\g-track-2.xml
if exist .\src\drivers\astigot\2\qualifying\g-track-3.xml copy .\src\drivers\astigot\2\qualifying\g-track-3.xml .\runtime\drivers\astigot\2\qualifying\g-track-3.xml
if exist .\src\drivers\astigot\2\qualifying\wheel-1.xml copy .\src\drivers\astigot\2\qualifying\wheel-1.xml .\runtime\drivers\astigot\2\qualifying\wheel-1.xml

if exist .\src\drivers\astigot\2\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\2\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\2\race\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\2\race\*.* call .\create_dir .\runtime\drivers\astigot\2
if exist .\src\drivers\astigot\2\race\*.* call .\create_dir .\runtime\drivers\astigot\2\race
if exist .\src\drivers\astigot\2\race\aalborg.xml copy .\src\drivers\astigot\2\race\aalborg.xml .\runtime\drivers\astigot\2\race\aalborg.xml
if exist .\src\drivers\astigot\2\race\alpine-1.xml copy .\src\drivers\astigot\2\race\alpine-1.xml .\runtime\drivers\astigot\2\race\alpine-1.xml
if exist .\src\drivers\astigot\2\race\eroad.xml copy .\src\drivers\astigot\2\race\eroad.xml .\runtime\drivers\astigot\2\race\eroad.xml
if exist .\src\drivers\astigot\2\race\e-track-1.xml copy .\src\drivers\astigot\2\race\e-track-1.xml .\runtime\drivers\astigot\2\race\e-track-1.xml
if exist .\src\drivers\astigot\2\race\e-track-2.xml copy .\src\drivers\astigot\2\race\e-track-2.xml .\runtime\drivers\astigot\2\race\e-track-2.xml
if exist .\src\drivers\astigot\2\race\e-track-3.xml copy .\src\drivers\astigot\2\race\e-track-3.xml .\runtime\drivers\astigot\2\race\e-track-3.xml
if exist .\src\drivers\astigot\2\race\e-track-4.xml copy .\src\drivers\astigot\2\race\e-track-4.xml .\runtime\drivers\astigot\2\race\e-track-4.xml
if exist .\src\drivers\astigot\2\race\e-track-6.xml copy .\src\drivers\astigot\2\race\e-track-6.xml .\runtime\drivers\astigot\2\race\e-track-6.xml
if exist .\src\drivers\astigot\2\race\g-track-2.xml copy .\src\drivers\astigot\2\race\g-track-2.xml .\runtime\drivers\astigot\2\race\g-track-2.xml
if exist .\src\drivers\astigot\2\race\g-track-3.xml copy .\src\drivers\astigot\2\race\g-track-3.xml .\runtime\drivers\astigot\2\race\g-track-3.xml
if exist .\src\drivers\astigot\2\race\wheel-1.xml copy .\src\drivers\astigot\2\race\wheel-1.xml .\runtime\drivers\astigot\2\race\wheel-1.xml

if exist .\src\drivers\astigot\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\2\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\2\*.* call .\create_dir .\runtime\drivers\astigot\2
if exist .\src\drivers\astigot\2\default.xml copy .\src\drivers\astigot\2\default.xml .\runtime\drivers\astigot\2\default.xml

if exist .\src\drivers\astigot\3\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\3\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\3\practice\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\3\practice\*.* call .\create_dir .\runtime\drivers\astigot\3
if exist .\src\drivers\astigot\3\practice\*.* call .\create_dir .\runtime\drivers\astigot\3\practice
if exist .\src\drivers\astigot\3\practice\aalborg.xml copy .\src\drivers\astigot\3\practice\aalborg.xml .\runtime\drivers\astigot\3\practice\aalborg.xml
if exist .\src\drivers\astigot\3\practice\alpine-1.xml copy .\src\drivers\astigot\3\practice\alpine-1.xml .\runtime\drivers\astigot\3\practice\alpine-1.xml
if exist .\src\drivers\astigot\3\practice\dirt-1.xml copy .\src\drivers\astigot\3\practice\dirt-1.xml .\runtime\drivers\astigot\3\practice\dirt-1.xml
if exist .\src\drivers\astigot\3\practice\dirt-2.xml copy .\src\drivers\astigot\3\practice\dirt-2.xml .\runtime\drivers\astigot\3\practice\dirt-2.xml
if exist .\src\drivers\astigot\3\practice\dirt-3.xml copy .\src\drivers\astigot\3\practice\dirt-3.xml .\runtime\drivers\astigot\3\practice\dirt-3.xml
if exist .\src\drivers\astigot\3\practice\dirt-4.xml copy .\src\drivers\astigot\3\practice\dirt-4.xml .\runtime\drivers\astigot\3\practice\dirt-4.xml
if exist .\src\drivers\astigot\3\practice\dirt-5.xml copy .\src\drivers\astigot\3\practice\dirt-5.xml .\runtime\drivers\astigot\3\practice\dirt-5.xml
if exist .\src\drivers\astigot\3\practice\dirt-6.xml copy .\src\drivers\astigot\3\practice\dirt-6.xml .\runtime\drivers\astigot\3\practice\dirt-6.xml
if exist .\src\drivers\astigot\3\practice\eroad.xml copy .\src\drivers\astigot\3\practice\eroad.xml .\runtime\drivers\astigot\3\practice\eroad.xml
if exist .\src\drivers\astigot\3\practice\e-track-1.xml copy .\src\drivers\astigot\3\practice\e-track-1.xml .\runtime\drivers\astigot\3\practice\e-track-1.xml
if exist .\src\drivers\astigot\3\practice\e-track-2.xml copy .\src\drivers\astigot\3\practice\e-track-2.xml .\runtime\drivers\astigot\3\practice\e-track-2.xml
if exist .\src\drivers\astigot\3\practice\e-track-3.xml copy .\src\drivers\astigot\3\practice\e-track-3.xml .\runtime\drivers\astigot\3\practice\e-track-3.xml
if exist .\src\drivers\astigot\3\practice\e-track-4.xml copy .\src\drivers\astigot\3\practice\e-track-4.xml .\runtime\drivers\astigot\3\practice\e-track-4.xml
if exist .\src\drivers\astigot\3\practice\e-track-6.xml copy .\src\drivers\astigot\3\practice\e-track-6.xml .\runtime\drivers\astigot\3\practice\e-track-6.xml
if exist .\src\drivers\astigot\3\practice\g-track-2.xml copy .\src\drivers\astigot\3\practice\g-track-2.xml .\runtime\drivers\astigot\3\practice\g-track-2.xml
if exist .\src\drivers\astigot\3\practice\g-track-3.xml copy .\src\drivers\astigot\3\practice\g-track-3.xml .\runtime\drivers\astigot\3\practice\g-track-3.xml
if exist .\src\drivers\astigot\3\practice\mixed-1.xml copy .\src\drivers\astigot\3\practice\mixed-1.xml .\runtime\drivers\astigot\3\practice\mixed-1.xml
if exist .\src\drivers\astigot\3\practice\mixed-2.xml copy .\src\drivers\astigot\3\practice\mixed-2.xml .\runtime\drivers\astigot\3\practice\mixed-2.xml
if exist .\src\drivers\astigot\3\practice\wheel-1.xml copy .\src\drivers\astigot\3\practice\wheel-1.xml .\runtime\drivers\astigot\3\practice\wheel-1.xml

if exist .\src\drivers\astigot\3\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\3\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\3\qualifying\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\3\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\3
if exist .\src\drivers\astigot\3\qualifying\*.* call .\create_dir .\runtime\drivers\astigot\3\qualifying
if exist .\src\drivers\astigot\3\qualifying\aalborg.xml copy .\src\drivers\astigot\3\qualifying\aalborg.xml .\runtime\drivers\astigot\3\qualifying\aalborg.xml
if exist .\src\drivers\astigot\3\qualifying\alpine-1.xml copy .\src\drivers\astigot\3\qualifying\alpine-1.xml .\runtime\drivers\astigot\3\qualifying\alpine-1.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-1.xml copy .\src\drivers\astigot\3\qualifying\dirt-1.xml .\runtime\drivers\astigot\3\qualifying\dirt-1.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-2.xml copy .\src\drivers\astigot\3\qualifying\dirt-2.xml .\runtime\drivers\astigot\3\qualifying\dirt-2.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-3.xml copy .\src\drivers\astigot\3\qualifying\dirt-3.xml .\runtime\drivers\astigot\3\qualifying\dirt-3.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-4.xml copy .\src\drivers\astigot\3\qualifying\dirt-4.xml .\runtime\drivers\astigot\3\qualifying\dirt-4.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-5.xml copy .\src\drivers\astigot\3\qualifying\dirt-5.xml .\runtime\drivers\astigot\3\qualifying\dirt-5.xml
if exist .\src\drivers\astigot\3\qualifying\dirt-6.xml copy .\src\drivers\astigot\3\qualifying\dirt-6.xml .\runtime\drivers\astigot\3\qualifying\dirt-6.xml
if exist .\src\drivers\astigot\3\qualifying\eroad.xml copy .\src\drivers\astigot\3\qualifying\eroad.xml .\runtime\drivers\astigot\3\qualifying\eroad.xml
if exist .\src\drivers\astigot\3\qualifying\e-track-1.xml copy .\src\drivers\astigot\3\qualifying\e-track-1.xml .\runtime\drivers\astigot\3\qualifying\e-track-1.xml
if exist .\src\drivers\astigot\3\qualifying\e-track-2.xml copy .\src\drivers\astigot\3\qualifying\e-track-2.xml .\runtime\drivers\astigot\3\qualifying\e-track-2.xml
if exist .\src\drivers\astigot\3\qualifying\e-track-3.xml copy .\src\drivers\astigot\3\qualifying\e-track-3.xml .\runtime\drivers\astigot\3\qualifying\e-track-3.xml
if exist .\src\drivers\astigot\3\qualifying\e-track-4.xml copy .\src\drivers\astigot\3\qualifying\e-track-4.xml .\runtime\drivers\astigot\3\qualifying\e-track-4.xml
if exist .\src\drivers\astigot\3\qualifying\e-track-6.xml copy .\src\drivers\astigot\3\qualifying\e-track-6.xml .\runtime\drivers\astigot\3\qualifying\e-track-6.xml
if exist .\src\drivers\astigot\3\qualifying\g-track-2.xml copy .\src\drivers\astigot\3\qualifying\g-track-2.xml .\runtime\drivers\astigot\3\qualifying\g-track-2.xml
if exist .\src\drivers\astigot\3\qualifying\g-track-3.xml copy .\src\drivers\astigot\3\qualifying\g-track-3.xml .\runtime\drivers\astigot\3\qualifying\g-track-3.xml
if exist .\src\drivers\astigot\3\qualifying\mixed-1.xml copy .\src\drivers\astigot\3\qualifying\mixed-1.xml .\runtime\drivers\astigot\3\qualifying\mixed-1.xml
if exist .\src\drivers\astigot\3\qualifying\mixed-2.xml copy .\src\drivers\astigot\3\qualifying\mixed-2.xml .\runtime\drivers\astigot\3\qualifying\mixed-2.xml
if exist .\src\drivers\astigot\3\qualifying\wheel-1.xml copy .\src\drivers\astigot\3\qualifying\wheel-1.xml .\runtime\drivers\astigot\3\qualifying\wheel-1.xml

if exist .\src\drivers\astigot\3\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\3\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\3\race\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\3\race\*.* call .\create_dir .\runtime\drivers\astigot\3
if exist .\src\drivers\astigot\3\race\*.* call .\create_dir .\runtime\drivers\astigot\3\race
if exist .\src\drivers\astigot\3\race\aalborg.xml copy .\src\drivers\astigot\3\race\aalborg.xml .\runtime\drivers\astigot\3\race\aalborg.xml
if exist .\src\drivers\astigot\3\race\alpine-1.xml copy .\src\drivers\astigot\3\race\alpine-1.xml .\runtime\drivers\astigot\3\race\alpine-1.xml
if exist .\src\drivers\astigot\3\race\dirt-1.xml copy .\src\drivers\astigot\3\race\dirt-1.xml .\runtime\drivers\astigot\3\race\dirt-1.xml
if exist .\src\drivers\astigot\3\race\dirt-2.xml copy .\src\drivers\astigot\3\race\dirt-2.xml .\runtime\drivers\astigot\3\race\dirt-2.xml
if exist .\src\drivers\astigot\3\race\dirt-3.xml copy .\src\drivers\astigot\3\race\dirt-3.xml .\runtime\drivers\astigot\3\race\dirt-3.xml
if exist .\src\drivers\astigot\3\race\dirt-4.xml copy .\src\drivers\astigot\3\race\dirt-4.xml .\runtime\drivers\astigot\3\race\dirt-4.xml
if exist .\src\drivers\astigot\3\race\dirt-5.xml copy .\src\drivers\astigot\3\race\dirt-5.xml .\runtime\drivers\astigot\3\race\dirt-5.xml
if exist .\src\drivers\astigot\3\race\dirt-6.xml copy .\src\drivers\astigot\3\race\dirt-6.xml .\runtime\drivers\astigot\3\race\dirt-6.xml
if exist .\src\drivers\astigot\3\race\eroad.xml copy .\src\drivers\astigot\3\race\eroad.xml .\runtime\drivers\astigot\3\race\eroad.xml
if exist .\src\drivers\astigot\3\race\e-track-1.xml copy .\src\drivers\astigot\3\race\e-track-1.xml .\runtime\drivers\astigot\3\race\e-track-1.xml
if exist .\src\drivers\astigot\3\race\e-track-2.xml copy .\src\drivers\astigot\3\race\e-track-2.xml .\runtime\drivers\astigot\3\race\e-track-2.xml
if exist .\src\drivers\astigot\3\race\e-track-3.xml copy .\src\drivers\astigot\3\race\e-track-3.xml .\runtime\drivers\astigot\3\race\e-track-3.xml
if exist .\src\drivers\astigot\3\race\e-track-4.xml copy .\src\drivers\astigot\3\race\e-track-4.xml .\runtime\drivers\astigot\3\race\e-track-4.xml
if exist .\src\drivers\astigot\3\race\e-track-6.xml copy .\src\drivers\astigot\3\race\e-track-6.xml .\runtime\drivers\astigot\3\race\e-track-6.xml
if exist .\src\drivers\astigot\3\race\g-track-2.xml copy .\src\drivers\astigot\3\race\g-track-2.xml .\runtime\drivers\astigot\3\race\g-track-2.xml
if exist .\src\drivers\astigot\3\race\g-track-3.xml copy .\src\drivers\astigot\3\race\g-track-3.xml .\runtime\drivers\astigot\3\race\g-track-3.xml
if exist .\src\drivers\astigot\3\race\mixed-1.xml copy .\src\drivers\astigot\3\race\mixed-1.xml .\runtime\drivers\astigot\3\race\mixed-1.xml
if exist .\src\drivers\astigot\3\race\mixed-2.xml copy .\src\drivers\astigot\3\race\mixed-2.xml .\runtime\drivers\astigot\3\race\mixed-2.xml
if exist .\src\drivers\astigot\3\race\wheel-1.xml copy .\src\drivers\astigot\3\race\wheel-1.xml .\runtime\drivers\astigot\3\race\wheel-1.xml

if exist .\src\drivers\astigot\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\3\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\3\*.* call .\create_dir .\runtime\drivers\astigot\3
if exist .\src\drivers\astigot\3\default.xml copy .\src\drivers\astigot\3\default.xml .\runtime\drivers\astigot\3\default.xml
if exist .\src\drivers\astigot\3\buggy.rgb copy .\src\drivers\astigot\3\buggy.rgb .\runtime\drivers\astigot\3\buggy.rgb

if exist .\src\drivers\astigot\*.* call .\create_dir .\runtime
if exist .\src\drivers\astigot\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\astigot\*.* call .\create_dir .\runtime\drivers\astigot
if exist .\src\drivers\astigot\astigot.xml copy .\src\drivers\astigot\astigot.xml .\runtime\drivers\astigot\astigot.xml
if exist .\src\drivers\astigot\logo.rgb copy .\src\drivers\astigot\logo.rgb .\runtime\drivers\astigot\logo.rgb

if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers\berniw\1
if exist .\src\drivers\berniw\1\cg-nascar-rwd.rgb copy .\src\drivers\berniw\1\cg-nascar-rwd.rgb .\runtime\drivers\berniw\1\cg-nascar-rwd.rgb
if exist .\src\drivers\berniw\1\aalborg.xml copy .\src\drivers\berniw\1\aalborg.xml .\runtime\drivers\berniw\1\aalborg.xml
if exist .\src\drivers\berniw\1\alpine-1.xml copy .\src\drivers\berniw\1\alpine-1.xml .\runtime\drivers\berniw\1\alpine-1.xml
if exist .\src\drivers\berniw\1\a-speedway.xml copy .\src\drivers\berniw\1\a-speedway.xml .\runtime\drivers\berniw\1\a-speedway.xml
if exist .\src\drivers\berniw\1\dirt-1.xml copy .\src\drivers\berniw\1\dirt-1.xml .\runtime\drivers\berniw\1\dirt-1.xml
if exist .\src\drivers\berniw\1\dirt-2.xml copy .\src\drivers\berniw\1\dirt-2.xml .\runtime\drivers\berniw\1\dirt-2.xml
if exist .\src\drivers\berniw\1\dirt-3.xml copy .\src\drivers\berniw\1\dirt-3.xml .\runtime\drivers\berniw\1\dirt-3.xml
if exist .\src\drivers\berniw\1\dirt-4.xml copy .\src\drivers\berniw\1\dirt-4.xml .\runtime\drivers\berniw\1\dirt-4.xml
if exist .\src\drivers\berniw\1\dirt-5.xml copy .\src\drivers\berniw\1\dirt-5.xml .\runtime\drivers\berniw\1\dirt-5.xml
if exist .\src\drivers\berniw\1\dirt-6.xml copy .\src\drivers\berniw\1\dirt-6.xml .\runtime\drivers\berniw\1\dirt-6.xml
if exist .\src\drivers\berniw\1\eroad.xml copy .\src\drivers\berniw\1\eroad.xml .\runtime\drivers\berniw\1\eroad.xml
if exist .\src\drivers\berniw\1\e-track-1.xml copy .\src\drivers\berniw\1\e-track-1.xml .\runtime\drivers\berniw\1\e-track-1.xml
if exist .\src\drivers\berniw\1\e-track-2.xml copy .\src\drivers\berniw\1\e-track-2.xml .\runtime\drivers\berniw\1\e-track-2.xml
if exist .\src\drivers\berniw\1\e-track-3.xml copy .\src\drivers\berniw\1\e-track-3.xml .\runtime\drivers\berniw\1\e-track-3.xml
if exist .\src\drivers\berniw\1\e-track-4.xml copy .\src\drivers\berniw\1\e-track-4.xml .\runtime\drivers\berniw\1\e-track-4.xml
if exist .\src\drivers\berniw\1\e-track-5.xml copy .\src\drivers\berniw\1\e-track-5.xml .\runtime\drivers\berniw\1\e-track-5.xml
if exist .\src\drivers\berniw\1\e-track-6.xml copy .\src\drivers\berniw\1\e-track-6.xml .\runtime\drivers\berniw\1\e-track-6.xml
if exist .\src\drivers\berniw\1\g-track-1.xml copy .\src\drivers\berniw\1\g-track-1.xml .\runtime\drivers\berniw\1\g-track-1.xml
if exist .\src\drivers\berniw\1\g-track-2.xml copy .\src\drivers\berniw\1\g-track-2.xml .\runtime\drivers\berniw\1\g-track-2.xml
if exist .\src\drivers\berniw\1\g-track-3.xml copy .\src\drivers\berniw\1\g-track-3.xml .\runtime\drivers\berniw\1\g-track-3.xml
if exist .\src\drivers\berniw\1\michigan.xml copy .\src\drivers\berniw\1\michigan.xml .\runtime\drivers\berniw\1\michigan.xml
if exist .\src\drivers\berniw\1\mixed-1.xml copy .\src\drivers\berniw\1\mixed-1.xml .\runtime\drivers\berniw\1\mixed-1.xml
if exist .\src\drivers\berniw\1\mixed-2.xml copy .\src\drivers\berniw\1\mixed-2.xml .\runtime\drivers\berniw\1\mixed-2.xml
if exist .\src\drivers\berniw\1\spring.xml copy .\src\drivers\berniw\1\spring.xml .\runtime\drivers\berniw\1\spring.xml
if exist .\src\drivers\berniw\1\wheel-1.xml copy .\src\drivers\berniw\1\wheel-1.xml .\runtime\drivers\berniw\1\wheel-1.xml

if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers\berniw\10
if exist .\src\drivers\berniw\10\buggy.rgb copy .\src\drivers\berniw\10\buggy.rgb .\runtime\drivers\berniw\10\buggy.rgb
if exist .\src\drivers\berniw\10\aalborg.xml copy .\src\drivers\berniw\10\aalborg.xml .\runtime\drivers\berniw\10\aalborg.xml
if exist .\src\drivers\berniw\10\alpine-1.xml copy .\src\drivers\berniw\10\alpine-1.xml .\runtime\drivers\berniw\10\alpine-1.xml
if exist .\src\drivers\berniw\10\a-speedway.xml copy .\src\drivers\berniw\10\a-speedway.xml .\runtime\drivers\berniw\10\a-speedway.xml
if exist .\src\drivers\berniw\10\dirt-1.xml copy .\src\drivers\berniw\10\dirt-1.xml .\runtime\drivers\berniw\10\dirt-1.xml
if exist .\src\drivers\berniw\10\dirt-2.xml copy .\src\drivers\berniw\10\dirt-2.xml .\runtime\drivers\berniw\10\dirt-2.xml
if exist .\src\drivers\berniw\10\dirt-3.xml copy .\src\drivers\berniw\10\dirt-3.xml .\runtime\drivers\berniw\10\dirt-3.xml
if exist .\src\drivers\berniw\10\dirt-4.xml copy .\src\drivers\berniw\10\dirt-4.xml .\runtime\drivers\berniw\10\dirt-4.xml
if exist .\src\drivers\berniw\10\dirt-5.xml copy .\src\drivers\berniw\10\dirt-5.xml .\runtime\drivers\berniw\10\dirt-5.xml
if exist .\src\drivers\berniw\10\dirt-6.xml copy .\src\drivers\berniw\10\dirt-6.xml .\runtime\drivers\berniw\10\dirt-6.xml
if exist .\src\drivers\berniw\10\eroad.xml copy .\src\drivers\berniw\10\eroad.xml .\runtime\drivers\berniw\10\eroad.xml
if exist .\src\drivers\berniw\10\e-track-1.xml copy .\src\drivers\berniw\10\e-track-1.xml .\runtime\drivers\berniw\10\e-track-1.xml
if exist .\src\drivers\berniw\10\e-track-2.xml copy .\src\drivers\berniw\10\e-track-2.xml .\runtime\drivers\berniw\10\e-track-2.xml
if exist .\src\drivers\berniw\10\e-track-3.xml copy .\src\drivers\berniw\10\e-track-3.xml .\runtime\drivers\berniw\10\e-track-3.xml
if exist .\src\drivers\berniw\10\e-track-4.xml copy .\src\drivers\berniw\10\e-track-4.xml .\runtime\drivers\berniw\10\e-track-4.xml
if exist .\src\drivers\berniw\10\e-track-5.xml copy .\src\drivers\berniw\10\e-track-5.xml .\runtime\drivers\berniw\10\e-track-5.xml
if exist .\src\drivers\berniw\10\e-track-6.xml copy .\src\drivers\berniw\10\e-track-6.xml .\runtime\drivers\berniw\10\e-track-6.xml
if exist .\src\drivers\berniw\10\g-track-1.xml copy .\src\drivers\berniw\10\g-track-1.xml .\runtime\drivers\berniw\10\g-track-1.xml
if exist .\src\drivers\berniw\10\g-track-2.xml copy .\src\drivers\berniw\10\g-track-2.xml .\runtime\drivers\berniw\10\g-track-2.xml
if exist .\src\drivers\berniw\10\g-track-3.xml copy .\src\drivers\berniw\10\g-track-3.xml .\runtime\drivers\berniw\10\g-track-3.xml
if exist .\src\drivers\berniw\10\michigan.xml copy .\src\drivers\berniw\10\michigan.xml .\runtime\drivers\berniw\10\michigan.xml
if exist .\src\drivers\berniw\10\mixed-1.xml copy .\src\drivers\berniw\10\mixed-1.xml .\runtime\drivers\berniw\10\mixed-1.xml
if exist .\src\drivers\berniw\10\mixed-2.xml copy .\src\drivers\berniw\10\mixed-2.xml .\runtime\drivers\berniw\10\mixed-2.xml
if exist .\src\drivers\berniw\10\spring.xml copy .\src\drivers\berniw\10\spring.xml .\runtime\drivers\berniw\10\spring.xml
if exist .\src\drivers\berniw\10\wheel-1.xml copy .\src\drivers\berniw\10\wheel-1.xml .\runtime\drivers\berniw\10\wheel-1.xml

if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers\berniw\2
if exist .\src\drivers\berniw\2\cg-nascar-rwd.rgb copy .\src\drivers\berniw\2\cg-nascar-rwd.rgb .\runtime\drivers\berniw\2\cg-nascar-rwd.rgb
if exist .\src\drivers\berniw\2\aalborg.xml copy .\src\drivers\berniw\2\aalborg.xml .\runtime\drivers\berniw\2\aalborg.xml
if exist .\src\drivers\berniw\2\alpine-1.xml copy .\src\drivers\berniw\2\alpine-1.xml .\runtime\drivers\berniw\2\alpine-1.xml
if exist .\src\drivers\berniw\2\a-speedway.xml copy .\src\drivers\berniw\2\a-speedway.xml .\runtime\drivers\berniw\2\a-speedway.xml
if exist .\src\drivers\berniw\2\dirt-1.xml copy .\src\drivers\berniw\2\dirt-1.xml .\runtime\drivers\berniw\2\dirt-1.xml
if exist .\src\drivers\berniw\2\dirt-2.xml copy .\src\drivers\berniw\2\dirt-2.xml .\runtime\drivers\berniw\2\dirt-2.xml
if exist .\src\drivers\berniw\2\dirt-3.xml copy .\src\drivers\berniw\2\dirt-3.xml .\runtime\drivers\berniw\2\dirt-3.xml
if exist .\src\drivers\berniw\2\dirt-4.xml copy .\src\drivers\berniw\2\dirt-4.xml .\runtime\drivers\berniw\2\dirt-4.xml
if exist .\src\drivers\berniw\2\dirt-5.xml copy .\src\drivers\berniw\2\dirt-5.xml .\runtime\drivers\berniw\2\dirt-5.xml
if exist .\src\drivers\berniw\2\dirt-6.xml copy .\src\drivers\berniw\2\dirt-6.xml .\runtime\drivers\berniw\2\dirt-6.xml
if exist .\src\drivers\berniw\2\eroad.xml copy .\src\drivers\berniw\2\eroad.xml .\runtime\drivers\berniw\2\eroad.xml
if exist .\src\drivers\berniw\2\e-track-1.xml copy .\src\drivers\berniw\2\e-track-1.xml .\runtime\drivers\berniw\2\e-track-1.xml
if exist .\src\drivers\berniw\2\e-track-2.xml copy .\src\drivers\berniw\2\e-track-2.xml .\runtime\drivers\berniw\2\e-track-2.xml
if exist .\src\drivers\berniw\2\e-track-3.xml copy .\src\drivers\berniw\2\e-track-3.xml .\runtime\drivers\berniw\2\e-track-3.xml
if exist .\src\drivers\berniw\2\e-track-4.xml copy .\src\drivers\berniw\2\e-track-4.xml .\runtime\drivers\berniw\2\e-track-4.xml
if exist .\src\drivers\berniw\2\e-track-5.xml copy .\src\drivers\berniw\2\e-track-5.xml .\runtime\drivers\berniw\2\e-track-5.xml
if exist .\src\drivers\berniw\2\e-track-6.xml copy .\src\drivers\berniw\2\e-track-6.xml .\runtime\drivers\berniw\2\e-track-6.xml
if exist .\src\drivers\berniw\2\g-track-1.xml copy .\src\drivers\berniw\2\g-track-1.xml .\runtime\drivers\berniw\2\g-track-1.xml
if exist .\src\drivers\berniw\2\g-track-2.xml copy .\src\drivers\berniw\2\g-track-2.xml .\runtime\drivers\berniw\2\g-track-2.xml
if exist .\src\drivers\berniw\2\g-track-3.xml copy .\src\drivers\berniw\2\g-track-3.xml .\runtime\drivers\berniw\2\g-track-3.xml
if exist .\src\drivers\berniw\2\michigan.xml copy .\src\drivers\berniw\2\michigan.xml .\runtime\drivers\berniw\2\michigan.xml
if exist .\src\drivers\berniw\2\mixed-1.xml copy .\src\drivers\berniw\2\mixed-1.xml .\runtime\drivers\berniw\2\mixed-1.xml
if exist .\src\drivers\berniw\2\mixed-2.xml copy .\src\drivers\berniw\2\mixed-2.xml .\runtime\drivers\berniw\2\mixed-2.xml
if exist .\src\drivers\berniw\2\spring.xml copy .\src\drivers\berniw\2\spring.xml .\runtime\drivers\berniw\2\spring.xml
if exist .\src\drivers\berniw\2\wheel-1.xml copy .\src\drivers\berniw\2\wheel-1.xml .\runtime\drivers\berniw\2\wheel-1.xml

if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers\berniw\3
if exist .\src\drivers\berniw\3\porsche-gt1.rgb copy .\src\drivers\berniw\3\porsche-gt1.rgb .\runtime\drivers\berniw\3\porsche-gt1.rgb
if exist .\src\drivers\berniw\3\aalborg.xml copy .\src\drivers\berniw\3\aalborg.xml .\runtime\drivers\berniw\3\aalborg.xml
if exist .\src\drivers\berniw\3\alpine-1.xml copy .\src\drivers\berniw\3\alpine-1.xml .\runtime\drivers\berniw\3\alpine-1.xml
if exist .\src\drivers\berniw\3\a-speedway.xml copy .\src\drivers\berniw\3\a-speedway.xml .\runtime\drivers\berniw\3\a-speedway.xml
if exist .\src\drivers\berniw\3\dirt-1.xml copy .\src\drivers\berniw\3\dirt-1.xml .\runtime\drivers\berniw\3\dirt-1.xml
if exist .\src\drivers\berniw\3\dirt-2.xml copy .\src\drivers\berniw\3\dirt-2.xml .\runtime\drivers\berniw\3\dirt-2.xml
if exist .\src\drivers\berniw\3\dirt-3.xml copy .\src\drivers\berniw\3\dirt-3.xml .\runtime\drivers\berniw\3\dirt-3.xml
if exist .\src\drivers\berniw\3\dirt-4.xml copy .\src\drivers\berniw\3\dirt-4.xml .\runtime\drivers\berniw\3\dirt-4.xml
if exist .\src\drivers\berniw\3\dirt-5.xml copy .\src\drivers\berniw\3\dirt-5.xml .\runtime\drivers\berniw\3\dirt-5.xml
if exist .\src\drivers\berniw\3\dirt-6.xml copy .\src\drivers\berniw\3\dirt-6.xml .\runtime\drivers\berniw\3\dirt-6.xml
if exist .\src\drivers\berniw\3\eroad.xml copy .\src\drivers\berniw\3\eroad.xml .\runtime\drivers\berniw\3\eroad.xml
if exist .\src\drivers\berniw\3\e-track-1.xml copy .\src\drivers\berniw\3\e-track-1.xml .\runtime\drivers\berniw\3\e-track-1.xml
if exist .\src\drivers\berniw\3\e-track-2.xml copy .\src\drivers\berniw\3\e-track-2.xml .\runtime\drivers\berniw\3\e-track-2.xml
if exist .\src\drivers\berniw\3\e-track-3.xml copy .\src\drivers\berniw\3\e-track-3.xml .\runtime\drivers\berniw\3\e-track-3.xml
if exist .\src\drivers\berniw\3\e-track-4.xml copy .\src\drivers\berniw\3\e-track-4.xml .\runtime\drivers\berniw\3\e-track-4.xml
if exist .\src\drivers\berniw\3\e-track-5.xml copy .\src\drivers\berniw\3\e-track-5.xml .\runtime\drivers\berniw\3\e-track-5.xml
if exist .\src\drivers\berniw\3\e-track-6.xml copy .\src\drivers\berniw\3\e-track-6.xml .\runtime\drivers\berniw\3\e-track-6.xml
if exist .\src\drivers\berniw\3\g-track-1.xml copy .\src\drivers\berniw\3\g-track-1.xml .\runtime\drivers\berniw\3\g-track-1.xml
if exist .\src\drivers\berniw\3\g-track-2.xml copy .\src\drivers\berniw\3\g-track-2.xml .\runtime\drivers\berniw\3\g-track-2.xml
if exist .\src\drivers\berniw\3\g-track-3.xml copy .\src\drivers\berniw\3\g-track-3.xml .\runtime\drivers\berniw\3\g-track-3.xml
if exist .\src\drivers\berniw\3\michigan.xml copy .\src\drivers\berniw\3\michigan.xml .\runtime\drivers\berniw\3\michigan.xml
if exist .\src\drivers\berniw\3\mixed-1.xml copy .\src\drivers\berniw\3\mixed-1.xml .\runtime\drivers\berniw\3\mixed-1.xml
if exist .\src\drivers\berniw\3\mixed-2.xml copy .\src\drivers\berniw\3\mixed-2.xml .\runtime\drivers\berniw\3\mixed-2.xml
if exist .\src\drivers\berniw\3\spring.xml copy .\src\drivers\berniw\3\spring.xml .\runtime\drivers\berniw\3\spring.xml
if exist .\src\drivers\berniw\3\wheel-1.xml copy .\src\drivers\berniw\3\wheel-1.xml .\runtime\drivers\berniw\3\wheel-1.xml

if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers\berniw\4
if exist .\src\drivers\berniw\4\viper-gts-r.rgb copy .\src\drivers\berniw\4\viper-gts-r.rgb .\runtime\drivers\berniw\4\viper-gts-r.rgb
if exist .\src\drivers\berniw\4\aalborg.xml copy .\src\drivers\berniw\4\aalborg.xml .\runtime\drivers\berniw\4\aalborg.xml
if exist .\src\drivers\berniw\4\alpine-1.xml copy .\src\drivers\berniw\4\alpine-1.xml .\runtime\drivers\berniw\4\alpine-1.xml
if exist .\src\drivers\berniw\4\a-speedway.xml copy .\src\drivers\berniw\4\a-speedway.xml .\runtime\drivers\berniw\4\a-speedway.xml
if exist .\src\drivers\berniw\4\dirt-1.xml copy .\src\drivers\berniw\4\dirt-1.xml .\runtime\drivers\berniw\4\dirt-1.xml
if exist .\src\drivers\berniw\4\dirt-2.xml copy .\src\drivers\berniw\4\dirt-2.xml .\runtime\drivers\berniw\4\dirt-2.xml
if exist .\src\drivers\berniw\4\dirt-3.xml copy .\src\drivers\berniw\4\dirt-3.xml .\runtime\drivers\berniw\4\dirt-3.xml
if exist .\src\drivers\berniw\4\dirt-4.xml copy .\src\drivers\berniw\4\dirt-4.xml .\runtime\drivers\berniw\4\dirt-4.xml
if exist .\src\drivers\berniw\4\dirt-5.xml copy .\src\drivers\berniw\4\dirt-5.xml .\runtime\drivers\berniw\4\dirt-5.xml
if exist .\src\drivers\berniw\4\dirt-6.xml copy .\src\drivers\berniw\4\dirt-6.xml .\runtime\drivers\berniw\4\dirt-6.xml
if exist .\src\drivers\berniw\4\eroad.xml copy .\src\drivers\berniw\4\eroad.xml .\runtime\drivers\berniw\4\eroad.xml
if exist .\src\drivers\berniw\4\e-track-1.xml copy .\src\drivers\berniw\4\e-track-1.xml .\runtime\drivers\berniw\4\e-track-1.xml
if exist .\src\drivers\berniw\4\e-track-2.xml copy .\src\drivers\berniw\4\e-track-2.xml .\runtime\drivers\berniw\4\e-track-2.xml
if exist .\src\drivers\berniw\4\e-track-3.xml copy .\src\drivers\berniw\4\e-track-3.xml .\runtime\drivers\berniw\4\e-track-3.xml
if exist .\src\drivers\berniw\4\e-track-4.xml copy .\src\drivers\berniw\4\e-track-4.xml .\runtime\drivers\berniw\4\e-track-4.xml
if exist .\src\drivers\berniw\4\e-track-5.xml copy .\src\drivers\berniw\4\e-track-5.xml .\runtime\drivers\berniw\4\e-track-5.xml
if exist .\src\drivers\berniw\4\e-track-6.xml copy .\src\drivers\berniw\4\e-track-6.xml .\runtime\drivers\berniw\4\e-track-6.xml
if exist .\src\drivers\berniw\4\g-track-1.xml copy .\src\drivers\berniw\4\g-track-1.xml .\runtime\drivers\berniw\4\g-track-1.xml
if exist .\src\drivers\berniw\4\g-track-2.xml copy .\src\drivers\berniw\4\g-track-2.xml .\runtime\drivers\berniw\4\g-track-2.xml
if exist .\src\drivers\berniw\4\g-track-3.xml copy .\src\drivers\berniw\4\g-track-3.xml .\runtime\drivers\berniw\4\g-track-3.xml
if exist .\src\drivers\berniw\4\michigan.xml copy .\src\drivers\berniw\4\michigan.xml .\runtime\drivers\berniw\4\michigan.xml
if exist .\src\drivers\berniw\4\mixed-1.xml copy .\src\drivers\berniw\4\mixed-1.xml .\runtime\drivers\berniw\4\mixed-1.xml
if exist .\src\drivers\berniw\4\mixed-2.xml copy .\src\drivers\berniw\4\mixed-2.xml .\runtime\drivers\berniw\4\mixed-2.xml
if exist .\src\drivers\berniw\4\spring.xml copy .\src\drivers\berniw\4\spring.xml .\runtime\drivers\berniw\4\spring.xml
if exist .\src\drivers\berniw\4\wheel-1.xml copy .\src\drivers\berniw\4\wheel-1.xml .\runtime\drivers\berniw\4\wheel-1.xml

if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers\berniw\5
if exist .\src\drivers\berniw\5\gt40.rgb copy .\src\drivers\berniw\5\gt40.rgb .\runtime\drivers\berniw\5\gt40.rgb
if exist .\src\drivers\berniw\5\aalborg.xml copy .\src\drivers\berniw\5\aalborg.xml .\runtime\drivers\berniw\5\aalborg.xml
if exist .\src\drivers\berniw\5\alpine-1.xml copy .\src\drivers\berniw\5\alpine-1.xml .\runtime\drivers\berniw\5\alpine-1.xml
if exist .\src\drivers\berniw\5\a-speedway.xml copy .\src\drivers\berniw\5\a-speedway.xml .\runtime\drivers\berniw\5\a-speedway.xml
if exist .\src\drivers\berniw\5\dirt-1.xml copy .\src\drivers\berniw\5\dirt-1.xml .\runtime\drivers\berniw\5\dirt-1.xml
if exist .\src\drivers\berniw\5\dirt-2.xml copy .\src\drivers\berniw\5\dirt-2.xml .\runtime\drivers\berniw\5\dirt-2.xml
if exist .\src\drivers\berniw\5\dirt-3.xml copy .\src\drivers\berniw\5\dirt-3.xml .\runtime\drivers\berniw\5\dirt-3.xml
if exist .\src\drivers\berniw\5\dirt-4.xml copy .\src\drivers\berniw\5\dirt-4.xml .\runtime\drivers\berniw\5\dirt-4.xml
if exist .\src\drivers\berniw\5\dirt-5.xml copy .\src\drivers\berniw\5\dirt-5.xml .\runtime\drivers\berniw\5\dirt-5.xml
if exist .\src\drivers\berniw\5\dirt-6.xml copy .\src\drivers\berniw\5\dirt-6.xml .\runtime\drivers\berniw\5\dirt-6.xml
if exist .\src\drivers\berniw\5\eroad.xml copy .\src\drivers\berniw\5\eroad.xml .\runtime\drivers\berniw\5\eroad.xml
if exist .\src\drivers\berniw\5\e-track-1.xml copy .\src\drivers\berniw\5\e-track-1.xml .\runtime\drivers\berniw\5\e-track-1.xml
if exist .\src\drivers\berniw\5\e-track-2.xml copy .\src\drivers\berniw\5\e-track-2.xml .\runtime\drivers\berniw\5\e-track-2.xml
if exist .\src\drivers\berniw\5\e-track-3.xml copy .\src\drivers\berniw\5\e-track-3.xml .\runtime\drivers\berniw\5\e-track-3.xml
if exist .\src\drivers\berniw\5\e-track-4.xml copy .\src\drivers\berniw\5\e-track-4.xml .\runtime\drivers\berniw\5\e-track-4.xml
if exist .\src\drivers\berniw\5\e-track-5.xml copy .\src\drivers\berniw\5\e-track-5.xml .\runtime\drivers\berniw\5\e-track-5.xml
if exist .\src\drivers\berniw\5\e-track-6.xml copy .\src\drivers\berniw\5\e-track-6.xml .\runtime\drivers\berniw\5\e-track-6.xml
if exist .\src\drivers\berniw\5\g-track-1.xml copy .\src\drivers\berniw\5\g-track-1.xml .\runtime\drivers\berniw\5\g-track-1.xml
if exist .\src\drivers\berniw\5\g-track-2.xml copy .\src\drivers\berniw\5\g-track-2.xml .\runtime\drivers\berniw\5\g-track-2.xml
if exist .\src\drivers\berniw\5\g-track-3.xml copy .\src\drivers\berniw\5\g-track-3.xml .\runtime\drivers\berniw\5\g-track-3.xml
if exist .\src\drivers\berniw\5\michigan.xml copy .\src\drivers\berniw\5\michigan.xml .\runtime\drivers\berniw\5\michigan.xml
if exist .\src\drivers\berniw\5\mixed-1.xml copy .\src\drivers\berniw\5\mixed-1.xml .\runtime\drivers\berniw\5\mixed-1.xml
if exist .\src\drivers\berniw\5\mixed-2.xml copy .\src\drivers\berniw\5\mixed-2.xml .\runtime\drivers\berniw\5\mixed-2.xml
if exist .\src\drivers\berniw\5\spring.xml copy .\src\drivers\berniw\5\spring.xml .\runtime\drivers\berniw\5\spring.xml
if exist .\src\drivers\berniw\5\wheel-1.xml copy .\src\drivers\berniw\5\wheel-1.xml .\runtime\drivers\berniw\5\wheel-1.xml

if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers\berniw\6
if exist .\src\drivers\berniw\6\155-DTM.rgb copy .\src\drivers\berniw\6\155-DTM.rgb .\runtime\drivers\berniw\6\155-DTM.rgb
if exist .\src\drivers\berniw\6\aalborg.xml copy .\src\drivers\berniw\6\aalborg.xml .\runtime\drivers\berniw\6\aalborg.xml
if exist .\src\drivers\berniw\6\alpine-1.xml copy .\src\drivers\berniw\6\alpine-1.xml .\runtime\drivers\berniw\6\alpine-1.xml
if exist .\src\drivers\berniw\6\a-speedway.xml copy .\src\drivers\berniw\6\a-speedway.xml .\runtime\drivers\berniw\6\a-speedway.xml
if exist .\src\drivers\berniw\6\dirt-1.xml copy .\src\drivers\berniw\6\dirt-1.xml .\runtime\drivers\berniw\6\dirt-1.xml
if exist .\src\drivers\berniw\6\dirt-2.xml copy .\src\drivers\berniw\6\dirt-2.xml .\runtime\drivers\berniw\6\dirt-2.xml
if exist .\src\drivers\berniw\6\dirt-3.xml copy .\src\drivers\berniw\6\dirt-3.xml .\runtime\drivers\berniw\6\dirt-3.xml
if exist .\src\drivers\berniw\6\dirt-4.xml copy .\src\drivers\berniw\6\dirt-4.xml .\runtime\drivers\berniw\6\dirt-4.xml
if exist .\src\drivers\berniw\6\dirt-5.xml copy .\src\drivers\berniw\6\dirt-5.xml .\runtime\drivers\berniw\6\dirt-5.xml
if exist .\src\drivers\berniw\6\dirt-6.xml copy .\src\drivers\berniw\6\dirt-6.xml .\runtime\drivers\berniw\6\dirt-6.xml
if exist .\src\drivers\berniw\6\eroad.xml copy .\src\drivers\berniw\6\eroad.xml .\runtime\drivers\berniw\6\eroad.xml
if exist .\src\drivers\berniw\6\e-track-1.xml copy .\src\drivers\berniw\6\e-track-1.xml .\runtime\drivers\berniw\6\e-track-1.xml
if exist .\src\drivers\berniw\6\e-track-2.xml copy .\src\drivers\berniw\6\e-track-2.xml .\runtime\drivers\berniw\6\e-track-2.xml
if exist .\src\drivers\berniw\6\e-track-3.xml copy .\src\drivers\berniw\6\e-track-3.xml .\runtime\drivers\berniw\6\e-track-3.xml
if exist .\src\drivers\berniw\6\e-track-4.xml copy .\src\drivers\berniw\6\e-track-4.xml .\runtime\drivers\berniw\6\e-track-4.xml
if exist .\src\drivers\berniw\6\e-track-5.xml copy .\src\drivers\berniw\6\e-track-5.xml .\runtime\drivers\berniw\6\e-track-5.xml
if exist .\src\drivers\berniw\6\e-track-6.xml copy .\src\drivers\berniw\6\e-track-6.xml .\runtime\drivers\berniw\6\e-track-6.xml
if exist .\src\drivers\berniw\6\g-track-1.xml copy .\src\drivers\berniw\6\g-track-1.xml .\runtime\drivers\berniw\6\g-track-1.xml
if exist .\src\drivers\berniw\6\g-track-2.xml copy .\src\drivers\berniw\6\g-track-2.xml .\runtime\drivers\berniw\6\g-track-2.xml
if exist .\src\drivers\berniw\6\g-track-3.xml copy .\src\drivers\berniw\6\g-track-3.xml .\runtime\drivers\berniw\6\g-track-3.xml
if exist .\src\drivers\berniw\6\michigan.xml copy .\src\drivers\berniw\6\michigan.xml .\runtime\drivers\berniw\6\michigan.xml
if exist .\src\drivers\berniw\6\mixed-1.xml copy .\src\drivers\berniw\6\mixed-1.xml .\runtime\drivers\berniw\6\mixed-1.xml
if exist .\src\drivers\berniw\6\mixed-2.xml copy .\src\drivers\berniw\6\mixed-2.xml .\runtime\drivers\berniw\6\mixed-2.xml
if exist .\src\drivers\berniw\6\spring.xml copy .\src\drivers\berniw\6\spring.xml .\runtime\drivers\berniw\6\spring.xml
if exist .\src\drivers\berniw\6\wheel-1.xml copy .\src\drivers\berniw\6\wheel-1.xml .\runtime\drivers\berniw\6\wheel-1.xml

if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers\berniw\7
if exist .\src\drivers\berniw\7\lotus-gt1.rgb copy .\src\drivers\berniw\7\lotus-gt1.rgb .\runtime\drivers\berniw\7\lotus-gt1.rgb
if exist .\src\drivers\berniw\7\aalborg.xml copy .\src\drivers\berniw\7\aalborg.xml .\runtime\drivers\berniw\7\aalborg.xml
if exist .\src\drivers\berniw\7\alpine-1.xml copy .\src\drivers\berniw\7\alpine-1.xml .\runtime\drivers\berniw\7\alpine-1.xml
if exist .\src\drivers\berniw\7\a-speedway.xml copy .\src\drivers\berniw\7\a-speedway.xml .\runtime\drivers\berniw\7\a-speedway.xml
if exist .\src\drivers\berniw\7\dirt-1.xml copy .\src\drivers\berniw\7\dirt-1.xml .\runtime\drivers\berniw\7\dirt-1.xml
if exist .\src\drivers\berniw\7\dirt-2.xml copy .\src\drivers\berniw\7\dirt-2.xml .\runtime\drivers\berniw\7\dirt-2.xml
if exist .\src\drivers\berniw\7\dirt-3.xml copy .\src\drivers\berniw\7\dirt-3.xml .\runtime\drivers\berniw\7\dirt-3.xml
if exist .\src\drivers\berniw\7\dirt-4.xml copy .\src\drivers\berniw\7\dirt-4.xml .\runtime\drivers\berniw\7\dirt-4.xml
if exist .\src\drivers\berniw\7\dirt-5.xml copy .\src\drivers\berniw\7\dirt-5.xml .\runtime\drivers\berniw\7\dirt-5.xml
if exist .\src\drivers\berniw\7\dirt-6.xml copy .\src\drivers\berniw\7\dirt-6.xml .\runtime\drivers\berniw\7\dirt-6.xml
if exist .\src\drivers\berniw\7\eroad.xml copy .\src\drivers\berniw\7\eroad.xml .\runtime\drivers\berniw\7\eroad.xml
if exist .\src\drivers\berniw\7\e-track-1.xml copy .\src\drivers\berniw\7\e-track-1.xml .\runtime\drivers\berniw\7\e-track-1.xml
if exist .\src\drivers\berniw\7\e-track-2.xml copy .\src\drivers\berniw\7\e-track-2.xml .\runtime\drivers\berniw\7\e-track-2.xml
if exist .\src\drivers\berniw\7\e-track-3.xml copy .\src\drivers\berniw\7\e-track-3.xml .\runtime\drivers\berniw\7\e-track-3.xml
if exist .\src\drivers\berniw\7\e-track-4.xml copy .\src\drivers\berniw\7\e-track-4.xml .\runtime\drivers\berniw\7\e-track-4.xml
if exist .\src\drivers\berniw\7\e-track-5.xml copy .\src\drivers\berniw\7\e-track-5.xml .\runtime\drivers\berniw\7\e-track-5.xml
if exist .\src\drivers\berniw\7\e-track-6.xml copy .\src\drivers\berniw\7\e-track-6.xml .\runtime\drivers\berniw\7\e-track-6.xml
if exist .\src\drivers\berniw\7\g-track-1.xml copy .\src\drivers\berniw\7\g-track-1.xml .\runtime\drivers\berniw\7\g-track-1.xml
if exist .\src\drivers\berniw\7\g-track-2.xml copy .\src\drivers\berniw\7\g-track-2.xml .\runtime\drivers\berniw\7\g-track-2.xml
if exist .\src\drivers\berniw\7\g-track-3.xml copy .\src\drivers\berniw\7\g-track-3.xml .\runtime\drivers\berniw\7\g-track-3.xml
if exist .\src\drivers\berniw\7\michigan.xml copy .\src\drivers\berniw\7\michigan.xml .\runtime\drivers\berniw\7\michigan.xml
if exist .\src\drivers\berniw\7\mixed-1.xml copy .\src\drivers\berniw\7\mixed-1.xml .\runtime\drivers\berniw\7\mixed-1.xml
if exist .\src\drivers\berniw\7\mixed-2.xml copy .\src\drivers\berniw\7\mixed-2.xml .\runtime\drivers\berniw\7\mixed-2.xml
if exist .\src\drivers\berniw\7\spring.xml copy .\src\drivers\berniw\7\spring.xml .\runtime\drivers\berniw\7\spring.xml
if exist .\src\drivers\berniw\7\wheel-1.xml copy .\src\drivers\berniw\7\wheel-1.xml .\runtime\drivers\berniw\7\wheel-1.xml

if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers\berniw\8
if exist .\src\drivers\berniw\8\baja-bug.rgb copy .\src\drivers\berniw\8\baja-bug.rgb .\runtime\drivers\berniw\8\baja-bug.rgb
if exist .\src\drivers\berniw\8\aalborg.xml copy .\src\drivers\berniw\8\aalborg.xml .\runtime\drivers\berniw\8\aalborg.xml
if exist .\src\drivers\berniw\8\alpine-1.xml copy .\src\drivers\berniw\8\alpine-1.xml .\runtime\drivers\berniw\8\alpine-1.xml
if exist .\src\drivers\berniw\8\a-speedway.xml copy .\src\drivers\berniw\8\a-speedway.xml .\runtime\drivers\berniw\8\a-speedway.xml
if exist .\src\drivers\berniw\8\dirt-1.xml copy .\src\drivers\berniw\8\dirt-1.xml .\runtime\drivers\berniw\8\dirt-1.xml
if exist .\src\drivers\berniw\8\dirt-2.xml copy .\src\drivers\berniw\8\dirt-2.xml .\runtime\drivers\berniw\8\dirt-2.xml
if exist .\src\drivers\berniw\8\dirt-3.xml copy .\src\drivers\berniw\8\dirt-3.xml .\runtime\drivers\berniw\8\dirt-3.xml
if exist .\src\drivers\berniw\8\dirt-4.xml copy .\src\drivers\berniw\8\dirt-4.xml .\runtime\drivers\berniw\8\dirt-4.xml
if exist .\src\drivers\berniw\8\dirt-5.xml copy .\src\drivers\berniw\8\dirt-5.xml .\runtime\drivers\berniw\8\dirt-5.xml
if exist .\src\drivers\berniw\8\dirt-6.xml copy .\src\drivers\berniw\8\dirt-6.xml .\runtime\drivers\berniw\8\dirt-6.xml
if exist .\src\drivers\berniw\8\eroad.xml copy .\src\drivers\berniw\8\eroad.xml .\runtime\drivers\berniw\8\eroad.xml
if exist .\src\drivers\berniw\8\e-track-1.xml copy .\src\drivers\berniw\8\e-track-1.xml .\runtime\drivers\berniw\8\e-track-1.xml
if exist .\src\drivers\berniw\8\e-track-2.xml copy .\src\drivers\berniw\8\e-track-2.xml .\runtime\drivers\berniw\8\e-track-2.xml
if exist .\src\drivers\berniw\8\e-track-3.xml copy .\src\drivers\berniw\8\e-track-3.xml .\runtime\drivers\berniw\8\e-track-3.xml
if exist .\src\drivers\berniw\8\e-track-4.xml copy .\src\drivers\berniw\8\e-track-4.xml .\runtime\drivers\berniw\8\e-track-4.xml
if exist .\src\drivers\berniw\8\e-track-5.xml copy .\src\drivers\berniw\8\e-track-5.xml .\runtime\drivers\berniw\8\e-track-5.xml
if exist .\src\drivers\berniw\8\e-track-6.xml copy .\src\drivers\berniw\8\e-track-6.xml .\runtime\drivers\berniw\8\e-track-6.xml
if exist .\src\drivers\berniw\8\g-track-1.xml copy .\src\drivers\berniw\8\g-track-1.xml .\runtime\drivers\berniw\8\g-track-1.xml
if exist .\src\drivers\berniw\8\g-track-2.xml copy .\src\drivers\berniw\8\g-track-2.xml .\runtime\drivers\berniw\8\g-track-2.xml
if exist .\src\drivers\berniw\8\g-track-3.xml copy .\src\drivers\berniw\8\g-track-3.xml .\runtime\drivers\berniw\8\g-track-3.xml
if exist .\src\drivers\berniw\8\michigan.xml copy .\src\drivers\berniw\8\michigan.xml .\runtime\drivers\berniw\8\michigan.xml
if exist .\src\drivers\berniw\8\mixed-1.xml copy .\src\drivers\berniw\8\mixed-1.xml .\runtime\drivers\berniw\8\mixed-1.xml
if exist .\src\drivers\berniw\8\mixed-2.xml copy .\src\drivers\berniw\8\mixed-2.xml .\runtime\drivers\berniw\8\mixed-2.xml
if exist .\src\drivers\berniw\8\spring.xml copy .\src\drivers\berniw\8\spring.xml .\runtime\drivers\berniw\8\spring.xml
if exist .\src\drivers\berniw\8\wheel-1.xml copy .\src\drivers\berniw\8\wheel-1.xml .\runtime\drivers\berniw\8\wheel-1.xml

if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers\berniw\9
if exist .\src\drivers\berniw\9\mclaren-f1.rgb copy .\src\drivers\berniw\9\mclaren-f1.rgb .\runtime\drivers\berniw\9\mclaren-f1.rgb
if exist .\src\drivers\berniw\9\aalborg.xml copy .\src\drivers\berniw\9\aalborg.xml .\runtime\drivers\berniw\9\aalborg.xml
if exist .\src\drivers\berniw\9\alpine-1.xml copy .\src\drivers\berniw\9\alpine-1.xml .\runtime\drivers\berniw\9\alpine-1.xml
if exist .\src\drivers\berniw\9\a-speedway.xml copy .\src\drivers\berniw\9\a-speedway.xml .\runtime\drivers\berniw\9\a-speedway.xml
if exist .\src\drivers\berniw\9\dirt-1.xml copy .\src\drivers\berniw\9\dirt-1.xml .\runtime\drivers\berniw\9\dirt-1.xml
if exist .\src\drivers\berniw\9\dirt-2.xml copy .\src\drivers\berniw\9\dirt-2.xml .\runtime\drivers\berniw\9\dirt-2.xml
if exist .\src\drivers\berniw\9\dirt-3.xml copy .\src\drivers\berniw\9\dirt-3.xml .\runtime\drivers\berniw\9\dirt-3.xml
if exist .\src\drivers\berniw\9\dirt-4.xml copy .\src\drivers\berniw\9\dirt-4.xml .\runtime\drivers\berniw\9\dirt-4.xml
if exist .\src\drivers\berniw\9\dirt-5.xml copy .\src\drivers\berniw\9\dirt-5.xml .\runtime\drivers\berniw\9\dirt-5.xml
if exist .\src\drivers\berniw\9\dirt-6.xml copy .\src\drivers\berniw\9\dirt-6.xml .\runtime\drivers\berniw\9\dirt-6.xml
if exist .\src\drivers\berniw\9\eroad.xml copy .\src\drivers\berniw\9\eroad.xml .\runtime\drivers\berniw\9\eroad.xml
if exist .\src\drivers\berniw\9\e-track-1.xml copy .\src\drivers\berniw\9\e-track-1.xml .\runtime\drivers\berniw\9\e-track-1.xml
if exist .\src\drivers\berniw\9\e-track-2.xml copy .\src\drivers\berniw\9\e-track-2.xml .\runtime\drivers\berniw\9\e-track-2.xml
if exist .\src\drivers\berniw\9\e-track-3.xml copy .\src\drivers\berniw\9\e-track-3.xml .\runtime\drivers\berniw\9\e-track-3.xml
if exist .\src\drivers\berniw\9\e-track-4.xml copy .\src\drivers\berniw\9\e-track-4.xml .\runtime\drivers\berniw\9\e-track-4.xml
if exist .\src\drivers\berniw\9\e-track-5.xml copy .\src\drivers\berniw\9\e-track-5.xml .\runtime\drivers\berniw\9\e-track-5.xml
if exist .\src\drivers\berniw\9\e-track-6.xml copy .\src\drivers\berniw\9\e-track-6.xml .\runtime\drivers\berniw\9\e-track-6.xml
if exist .\src\drivers\berniw\9\g-track-1.xml copy .\src\drivers\berniw\9\g-track-1.xml .\runtime\drivers\berniw\9\g-track-1.xml
if exist .\src\drivers\berniw\9\g-track-2.xml copy .\src\drivers\berniw\9\g-track-2.xml .\runtime\drivers\berniw\9\g-track-2.xml
if exist .\src\drivers\berniw\9\g-track-3.xml copy .\src\drivers\berniw\9\g-track-3.xml .\runtime\drivers\berniw\9\g-track-3.xml
if exist .\src\drivers\berniw\9\michigan.xml copy .\src\drivers\berniw\9\michigan.xml .\runtime\drivers\berniw\9\michigan.xml
if exist .\src\drivers\berniw\9\mixed-1.xml copy .\src\drivers\berniw\9\mixed-1.xml .\runtime\drivers\berniw\9\mixed-1.xml
if exist .\src\drivers\berniw\9\mixed-2.xml copy .\src\drivers\berniw\9\mixed-2.xml .\runtime\drivers\berniw\9\mixed-2.xml
if exist .\src\drivers\berniw\9\spring.xml copy .\src\drivers\berniw\9\spring.xml .\runtime\drivers\berniw\9\spring.xml
if exist .\src\drivers\berniw\9\wheel-1.xml copy .\src\drivers\berniw\9\wheel-1.xml .\runtime\drivers\berniw\9\wheel-1.xml

if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\berniw.xml copy .\src\drivers\berniw\berniw.xml .\runtime\drivers\berniw\berniw.xml
if exist .\src\drivers\berniw\logo.rgb copy .\src\drivers\berniw\logo.rgb .\runtime\drivers\berniw\logo.rgb
if exist .\src\drivers\berniw\parameter.dat copy .\src\drivers\berniw\parameter.dat .\runtime\drivers\berniw\parameter.dat
if exist .\src\drivers\berniw\intsinsqr.dat copy .\src\drivers\berniw\intsinsqr.dat .\runtime\drivers\berniw\intsinsqr.dat
if exist .\src\drivers\berniw\intcossqr.dat copy .\src\drivers\berniw\intcossqr.dat .\runtime\drivers\berniw\intcossqr.dat

if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers\berniw2\1
if exist .\src\drivers\berniw2\1\aalborg.xml copy .\src\drivers\berniw2\1\aalborg.xml .\runtime\drivers\berniw2\1\aalborg.xml
if exist .\src\drivers\berniw2\1\alpine-1.xml copy .\src\drivers\berniw2\1\alpine-1.xml .\runtime\drivers\berniw2\1\alpine-1.xml
if exist .\src\drivers\berniw2\1\a-speedway.xml copy .\src\drivers\berniw2\1\a-speedway.xml .\runtime\drivers\berniw2\1\a-speedway.xml
if exist .\src\drivers\berniw2\1\default.xml copy .\src\drivers\berniw2\1\default.xml .\runtime\drivers\berniw2\1\default.xml
if exist .\src\drivers\berniw2\1\dirt-1.xml copy .\src\drivers\berniw2\1\dirt-1.xml .\runtime\drivers\berniw2\1\dirt-1.xml
if exist .\src\drivers\berniw2\1\dirt-2.xml copy .\src\drivers\berniw2\1\dirt-2.xml .\runtime\drivers\berniw2\1\dirt-2.xml
if exist .\src\drivers\berniw2\1\dirt-3.xml copy .\src\drivers\berniw2\1\dirt-3.xml .\runtime\drivers\berniw2\1\dirt-3.xml
if exist .\src\drivers\berniw2\1\dirt-4.xml copy .\src\drivers\berniw2\1\dirt-4.xml .\runtime\drivers\berniw2\1\dirt-4.xml
if exist .\src\drivers\berniw2\1\dirt-5.xml copy .\src\drivers\berniw2\1\dirt-5.xml .\runtime\drivers\berniw2\1\dirt-5.xml
if exist .\src\drivers\berniw2\1\dirt-6.xml copy .\src\drivers\berniw2\1\dirt-6.xml .\runtime\drivers\berniw2\1\dirt-6.xml
if exist .\src\drivers\berniw2\1\eroad.xml copy .\src\drivers\berniw2\1\eroad.xml .\runtime\drivers\berniw2\1\eroad.xml
if exist .\src\drivers\berniw2\1\e-track-1.xml copy .\src\drivers\berniw2\1\e-track-1.xml .\runtime\drivers\berniw2\1\e-track-1.xml
if exist .\src\drivers\berniw2\1\e-track-2.xml copy .\src\drivers\berniw2\1\e-track-2.xml .\runtime\drivers\berniw2\1\e-track-2.xml
if exist .\src\drivers\berniw2\1\e-track-3.xml copy .\src\drivers\berniw2\1\e-track-3.xml .\runtime\drivers\berniw2\1\e-track-3.xml
if exist .\src\drivers\berniw2\1\e-track-4.xml copy .\src\drivers\berniw2\1\e-track-4.xml .\runtime\drivers\berniw2\1\e-track-4.xml
if exist .\src\drivers\berniw2\1\e-track-5.xml copy .\src\drivers\berniw2\1\e-track-5.xml .\runtime\drivers\berniw2\1\e-track-5.xml
if exist .\src\drivers\berniw2\1\e-track-6.xml copy .\src\drivers\berniw2\1\e-track-6.xml .\runtime\drivers\berniw2\1\e-track-6.xml
if exist .\src\drivers\berniw2\1\g-track-1.xml copy .\src\drivers\berniw2\1\g-track-1.xml .\runtime\drivers\berniw2\1\g-track-1.xml
if exist .\src\drivers\berniw2\1\g-track-2.xml copy .\src\drivers\berniw2\1\g-track-2.xml .\runtime\drivers\berniw2\1\g-track-2.xml
if exist .\src\drivers\berniw2\1\g-track-3.xml copy .\src\drivers\berniw2\1\g-track-3.xml .\runtime\drivers\berniw2\1\g-track-3.xml
if exist .\src\drivers\berniw2\1\michigan.xml copy .\src\drivers\berniw2\1\michigan.xml .\runtime\drivers\berniw2\1\michigan.xml
if exist .\src\drivers\berniw2\1\mixed-1.xml copy .\src\drivers\berniw2\1\mixed-1.xml .\runtime\drivers\berniw2\1\mixed-1.xml
if exist .\src\drivers\berniw2\1\mixed-2.xml copy .\src\drivers\berniw2\1\mixed-2.xml .\runtime\drivers\berniw2\1\mixed-2.xml
if exist .\src\drivers\berniw2\1\spring.xml copy .\src\drivers\berniw2\1\spring.xml .\runtime\drivers\berniw2\1\spring.xml
if exist .\src\drivers\berniw2\1\wheel-1.xml copy .\src\drivers\berniw2\1\wheel-1.xml .\runtime\drivers\berniw2\1\wheel-1.xml

if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers\berniw2\10
if exist .\src\drivers\berniw2\10\360-modena.rgb copy .\src\drivers\berniw2\10\360-modena.rgb .\runtime\drivers\berniw2\10\360-modena.rgb
if exist .\src\drivers\berniw2\10\aalborg.xml copy .\src\drivers\berniw2\10\aalborg.xml .\runtime\drivers\berniw2\10\aalborg.xml
if exist .\src\drivers\berniw2\10\alpine-1.xml copy .\src\drivers\berniw2\10\alpine-1.xml .\runtime\drivers\berniw2\10\alpine-1.xml
if exist .\src\drivers\berniw2\10\a-speedway.xml copy .\src\drivers\berniw2\10\a-speedway.xml .\runtime\drivers\berniw2\10\a-speedway.xml
if exist .\src\drivers\berniw2\10\default.xml copy .\src\drivers\berniw2\10\default.xml .\runtime\drivers\berniw2\10\default.xml
if exist .\src\drivers\berniw2\10\dirt-1.xml copy .\src\drivers\berniw2\10\dirt-1.xml .\runtime\drivers\berniw2\10\dirt-1.xml
if exist .\src\drivers\berniw2\10\dirt-2.xml copy .\src\drivers\berniw2\10\dirt-2.xml .\runtime\drivers\berniw2\10\dirt-2.xml
if exist .\src\drivers\berniw2\10\dirt-3.xml copy .\src\drivers\berniw2\10\dirt-3.xml .\runtime\drivers\berniw2\10\dirt-3.xml
if exist .\src\drivers\berniw2\10\dirt-4.xml copy .\src\drivers\berniw2\10\dirt-4.xml .\runtime\drivers\berniw2\10\dirt-4.xml
if exist .\src\drivers\berniw2\10\dirt-5.xml copy .\src\drivers\berniw2\10\dirt-5.xml .\runtime\drivers\berniw2\10\dirt-5.xml
if exist .\src\drivers\berniw2\10\dirt-6.xml copy .\src\drivers\berniw2\10\dirt-6.xml .\runtime\drivers\berniw2\10\dirt-6.xml
if exist .\src\drivers\berniw2\10\eroad.xml copy .\src\drivers\berniw2\10\eroad.xml .\runtime\drivers\berniw2\10\eroad.xml
if exist .\src\drivers\berniw2\10\e-track-1.xml copy .\src\drivers\berniw2\10\e-track-1.xml .\runtime\drivers\berniw2\10\e-track-1.xml
if exist .\src\drivers\berniw2\10\e-track-2.xml copy .\src\drivers\berniw2\10\e-track-2.xml .\runtime\drivers\berniw2\10\e-track-2.xml
if exist .\src\drivers\berniw2\10\e-track-3.xml copy .\src\drivers\berniw2\10\e-track-3.xml .\runtime\drivers\berniw2\10\e-track-3.xml
if exist .\src\drivers\berniw2\10\e-track-4.xml copy .\src\drivers\berniw2\10\e-track-4.xml .\runtime\drivers\berniw2\10\e-track-4.xml
if exist .\src\drivers\berniw2\10\e-track-5.xml copy .\src\drivers\berniw2\10\e-track-5.xml .\runtime\drivers\berniw2\10\e-track-5.xml
if exist .\src\drivers\berniw2\10\e-track-6.xml copy .\src\drivers\berniw2\10\e-track-6.xml .\runtime\drivers\berniw2\10\e-track-6.xml
if exist .\src\drivers\berniw2\10\g-track-1.xml copy .\src\drivers\berniw2\10\g-track-1.xml .\runtime\drivers\berniw2\10\g-track-1.xml
if exist .\src\drivers\berniw2\10\g-track-2.xml copy .\src\drivers\berniw2\10\g-track-2.xml .\runtime\drivers\berniw2\10\g-track-2.xml
if exist .\src\drivers\berniw2\10\g-track-3.xml copy .\src\drivers\berniw2\10\g-track-3.xml .\runtime\drivers\berniw2\10\g-track-3.xml
if exist .\src\drivers\berniw2\10\michigan.xml copy .\src\drivers\berniw2\10\michigan.xml .\runtime\drivers\berniw2\10\michigan.xml
if exist .\src\drivers\berniw2\10\mixed-1.xml copy .\src\drivers\berniw2\10\mixed-1.xml .\runtime\drivers\berniw2\10\mixed-1.xml
if exist .\src\drivers\berniw2\10\mixed-2.xml copy .\src\drivers\berniw2\10\mixed-2.xml .\runtime\drivers\berniw2\10\mixed-2.xml
if exist .\src\drivers\berniw2\10\spring.xml copy .\src\drivers\berniw2\10\spring.xml .\runtime\drivers\berniw2\10\spring.xml
if exist .\src\drivers\berniw2\10\wheel-1.xml copy .\src\drivers\berniw2\10\wheel-1.xml .\runtime\drivers\berniw2\10\wheel-1.xml

if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers\berniw2\2
if exist .\src\drivers\berniw2\2\aalborg.xml copy .\src\drivers\berniw2\2\aalborg.xml .\runtime\drivers\berniw2\2\aalborg.xml
if exist .\src\drivers\berniw2\2\alpine-1.xml copy .\src\drivers\berniw2\2\alpine-1.xml .\runtime\drivers\berniw2\2\alpine-1.xml
if exist .\src\drivers\berniw2\2\a-speedway.xml copy .\src\drivers\berniw2\2\a-speedway.xml .\runtime\drivers\berniw2\2\a-speedway.xml
if exist .\src\drivers\berniw2\2\default.xml copy .\src\drivers\berniw2\2\default.xml .\runtime\drivers\berniw2\2\default.xml
if exist .\src\drivers\berniw2\2\dirt-1.xml copy .\src\drivers\berniw2\2\dirt-1.xml .\runtime\drivers\berniw2\2\dirt-1.xml
if exist .\src\drivers\berniw2\2\dirt-2.xml copy .\src\drivers\berniw2\2\dirt-2.xml .\runtime\drivers\berniw2\2\dirt-2.xml
if exist .\src\drivers\berniw2\2\dirt-3.xml copy .\src\drivers\berniw2\2\dirt-3.xml .\runtime\drivers\berniw2\2\dirt-3.xml
if exist .\src\drivers\berniw2\2\dirt-4.xml copy .\src\drivers\berniw2\2\dirt-4.xml .\runtime\drivers\berniw2\2\dirt-4.xml
if exist .\src\drivers\berniw2\2\dirt-5.xml copy .\src\drivers\berniw2\2\dirt-5.xml .\runtime\drivers\berniw2\2\dirt-5.xml
if exist .\src\drivers\berniw2\2\dirt-6.xml copy .\src\drivers\berniw2\2\dirt-6.xml .\runtime\drivers\berniw2\2\dirt-6.xml
if exist .\src\drivers\berniw2\2\eroad.xml copy .\src\drivers\berniw2\2\eroad.xml .\runtime\drivers\berniw2\2\eroad.xml
if exist .\src\drivers\berniw2\2\e-track-1.xml copy .\src\drivers\berniw2\2\e-track-1.xml .\runtime\drivers\berniw2\2\e-track-1.xml
if exist .\src\drivers\berniw2\2\e-track-2.xml copy .\src\drivers\berniw2\2\e-track-2.xml .\runtime\drivers\berniw2\2\e-track-2.xml
if exist .\src\drivers\berniw2\2\e-track-3.xml copy .\src\drivers\berniw2\2\e-track-3.xml .\runtime\drivers\berniw2\2\e-track-3.xml
if exist .\src\drivers\berniw2\2\e-track-4.xml copy .\src\drivers\berniw2\2\e-track-4.xml .\runtime\drivers\berniw2\2\e-track-4.xml
if exist .\src\drivers\berniw2\2\e-track-5.xml copy .\src\drivers\berniw2\2\e-track-5.xml .\runtime\drivers\berniw2\2\e-track-5.xml
if exist .\src\drivers\berniw2\2\e-track-6.xml copy .\src\drivers\berniw2\2\e-track-6.xml .\runtime\drivers\berniw2\2\e-track-6.xml
if exist .\src\drivers\berniw2\2\g-track-1.xml copy .\src\drivers\berniw2\2\g-track-1.xml .\runtime\drivers\berniw2\2\g-track-1.xml
if exist .\src\drivers\berniw2\2\g-track-2.xml copy .\src\drivers\berniw2\2\g-track-2.xml .\runtime\drivers\berniw2\2\g-track-2.xml
if exist .\src\drivers\berniw2\2\g-track-3.xml copy .\src\drivers\berniw2\2\g-track-3.xml .\runtime\drivers\berniw2\2\g-track-3.xml
if exist .\src\drivers\berniw2\2\michigan.xml copy .\src\drivers\berniw2\2\michigan.xml .\runtime\drivers\berniw2\2\michigan.xml
if exist .\src\drivers\berniw2\2\mixed-1.xml copy .\src\drivers\berniw2\2\mixed-1.xml .\runtime\drivers\berniw2\2\mixed-1.xml
if exist .\src\drivers\berniw2\2\mixed-2.xml copy .\src\drivers\berniw2\2\mixed-2.xml .\runtime\drivers\berniw2\2\mixed-2.xml
if exist .\src\drivers\berniw2\2\spring.xml copy .\src\drivers\berniw2\2\spring.xml .\runtime\drivers\berniw2\2\spring.xml
if exist .\src\drivers\berniw2\2\wheel-1.xml copy .\src\drivers\berniw2\2\wheel-1.xml .\runtime\drivers\berniw2\2\wheel-1.xml

if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers\berniw2\3
if exist .\src\drivers\berniw2\3\aalborg.xml copy .\src\drivers\berniw2\3\aalborg.xml .\runtime\drivers\berniw2\3\aalborg.xml
if exist .\src\drivers\berniw2\3\alpine-1.xml copy .\src\drivers\berniw2\3\alpine-1.xml .\runtime\drivers\berniw2\3\alpine-1.xml
if exist .\src\drivers\berniw2\3\a-speedway.xml copy .\src\drivers\berniw2\3\a-speedway.xml .\runtime\drivers\berniw2\3\a-speedway.xml
if exist .\src\drivers\berniw2\3\default.xml copy .\src\drivers\berniw2\3\default.xml .\runtime\drivers\berniw2\3\default.xml
if exist .\src\drivers\berniw2\3\dirt-1.xml copy .\src\drivers\berniw2\3\dirt-1.xml .\runtime\drivers\berniw2\3\dirt-1.xml
if exist .\src\drivers\berniw2\3\dirt-2.xml copy .\src\drivers\berniw2\3\dirt-2.xml .\runtime\drivers\berniw2\3\dirt-2.xml
if exist .\src\drivers\berniw2\3\dirt-3.xml copy .\src\drivers\berniw2\3\dirt-3.xml .\runtime\drivers\berniw2\3\dirt-3.xml
if exist .\src\drivers\berniw2\3\dirt-4.xml copy .\src\drivers\berniw2\3\dirt-4.xml .\runtime\drivers\berniw2\3\dirt-4.xml
if exist .\src\drivers\berniw2\3\dirt-5.xml copy .\src\drivers\berniw2\3\dirt-5.xml .\runtime\drivers\berniw2\3\dirt-5.xml
if exist .\src\drivers\berniw2\3\dirt-6.xml copy .\src\drivers\berniw2\3\dirt-6.xml .\runtime\drivers\berniw2\3\dirt-6.xml
if exist .\src\drivers\berniw2\3\eroad.xml copy .\src\drivers\berniw2\3\eroad.xml .\runtime\drivers\berniw2\3\eroad.xml
if exist .\src\drivers\berniw2\3\e-track-1.xml copy .\src\drivers\berniw2\3\e-track-1.xml .\runtime\drivers\berniw2\3\e-track-1.xml
if exist .\src\drivers\berniw2\3\e-track-2.xml copy .\src\drivers\berniw2\3\e-track-2.xml .\runtime\drivers\berniw2\3\e-track-2.xml
if exist .\src\drivers\berniw2\3\e-track-3.xml copy .\src\drivers\berniw2\3\e-track-3.xml .\runtime\drivers\berniw2\3\e-track-3.xml
if exist .\src\drivers\berniw2\3\e-track-4.xml copy .\src\drivers\berniw2\3\e-track-4.xml .\runtime\drivers\berniw2\3\e-track-4.xml
if exist .\src\drivers\berniw2\3\e-track-5.xml copy .\src\drivers\berniw2\3\e-track-5.xml .\runtime\drivers\berniw2\3\e-track-5.xml
if exist .\src\drivers\berniw2\3\e-track-6.xml copy .\src\drivers\berniw2\3\e-track-6.xml .\runtime\drivers\berniw2\3\e-track-6.xml
if exist .\src\drivers\berniw2\3\g-track-1.xml copy .\src\drivers\berniw2\3\g-track-1.xml .\runtime\drivers\berniw2\3\g-track-1.xml
if exist .\src\drivers\berniw2\3\g-track-2.xml copy .\src\drivers\berniw2\3\g-track-2.xml .\runtime\drivers\berniw2\3\g-track-2.xml
if exist .\src\drivers\berniw2\3\g-track-3.xml copy .\src\drivers\berniw2\3\g-track-3.xml .\runtime\drivers\berniw2\3\g-track-3.xml
if exist .\src\drivers\berniw2\3\michigan.xml copy .\src\drivers\berniw2\3\michigan.xml .\runtime\drivers\berniw2\3\michigan.xml
if exist .\src\drivers\berniw2\3\mixed-1.xml copy .\src\drivers\berniw2\3\mixed-1.xml .\runtime\drivers\berniw2\3\mixed-1.xml
if exist .\src\drivers\berniw2\3\mixed-2.xml copy .\src\drivers\berniw2\3\mixed-2.xml .\runtime\drivers\berniw2\3\mixed-2.xml
if exist .\src\drivers\berniw2\3\spring.xml copy .\src\drivers\berniw2\3\spring.xml .\runtime\drivers\berniw2\3\spring.xml
if exist .\src\drivers\berniw2\3\wheel-1.xml copy .\src\drivers\berniw2\3\wheel-1.xml .\runtime\drivers\berniw2\3\wheel-1.xml

if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers\berniw2\4
if exist .\src\drivers\berniw2\4\aalborg.xml copy .\src\drivers\berniw2\4\aalborg.xml .\runtime\drivers\berniw2\4\aalborg.xml
if exist .\src\drivers\berniw2\4\alpine-1.xml copy .\src\drivers\berniw2\4\alpine-1.xml .\runtime\drivers\berniw2\4\alpine-1.xml
if exist .\src\drivers\berniw2\4\a-speedway.xml copy .\src\drivers\berniw2\4\a-speedway.xml .\runtime\drivers\berniw2\4\a-speedway.xml
if exist .\src\drivers\berniw2\4\default.xml copy .\src\drivers\berniw2\4\default.xml .\runtime\drivers\berniw2\4\default.xml
if exist .\src\drivers\berniw2\4\dirt-1.xml copy .\src\drivers\berniw2\4\dirt-1.xml .\runtime\drivers\berniw2\4\dirt-1.xml
if exist .\src\drivers\berniw2\4\dirt-2.xml copy .\src\drivers\berniw2\4\dirt-2.xml .\runtime\drivers\berniw2\4\dirt-2.xml
if exist .\src\drivers\berniw2\4\dirt-3.xml copy .\src\drivers\berniw2\4\dirt-3.xml .\runtime\drivers\berniw2\4\dirt-3.xml
if exist .\src\drivers\berniw2\4\dirt-4.xml copy .\src\drivers\berniw2\4\dirt-4.xml .\runtime\drivers\berniw2\4\dirt-4.xml
if exist .\src\drivers\berniw2\4\dirt-5.xml copy .\src\drivers\berniw2\4\dirt-5.xml .\runtime\drivers\berniw2\4\dirt-5.xml
if exist .\src\drivers\berniw2\4\dirt-6.xml copy .\src\drivers\berniw2\4\dirt-6.xml .\runtime\drivers\berniw2\4\dirt-6.xml
if exist .\src\drivers\berniw2\4\eroad.xml copy .\src\drivers\berniw2\4\eroad.xml .\runtime\drivers\berniw2\4\eroad.xml
if exist .\src\drivers\berniw2\4\e-track-1.xml copy .\src\drivers\berniw2\4\e-track-1.xml .\runtime\drivers\berniw2\4\e-track-1.xml
if exist .\src\drivers\berniw2\4\e-track-2.xml copy .\src\drivers\berniw2\4\e-track-2.xml .\runtime\drivers\berniw2\4\e-track-2.xml
if exist .\src\drivers\berniw2\4\e-track-3.xml copy .\src\drivers\berniw2\4\e-track-3.xml .\runtime\drivers\berniw2\4\e-track-3.xml
if exist .\src\drivers\berniw2\4\e-track-4.xml copy .\src\drivers\berniw2\4\e-track-4.xml .\runtime\drivers\berniw2\4\e-track-4.xml
if exist .\src\drivers\berniw2\4\e-track-5.xml copy .\src\drivers\berniw2\4\e-track-5.xml .\runtime\drivers\berniw2\4\e-track-5.xml
if exist .\src\drivers\berniw2\4\e-track-6.xml copy .\src\drivers\berniw2\4\e-track-6.xml .\runtime\drivers\berniw2\4\e-track-6.xml
if exist .\src\drivers\berniw2\4\g-track-1.xml copy .\src\drivers\berniw2\4\g-track-1.xml .\runtime\drivers\berniw2\4\g-track-1.xml
if exist .\src\drivers\berniw2\4\g-track-2.xml copy .\src\drivers\berniw2\4\g-track-2.xml .\runtime\drivers\berniw2\4\g-track-2.xml
if exist .\src\drivers\berniw2\4\g-track-3.xml copy .\src\drivers\berniw2\4\g-track-3.xml .\runtime\drivers\berniw2\4\g-track-3.xml
if exist .\src\drivers\berniw2\4\michigan.xml copy .\src\drivers\berniw2\4\michigan.xml .\runtime\drivers\berniw2\4\michigan.xml
if exist .\src\drivers\berniw2\4\mixed-1.xml copy .\src\drivers\berniw2\4\mixed-1.xml .\runtime\drivers\berniw2\4\mixed-1.xml
if exist .\src\drivers\berniw2\4\mixed-2.xml copy .\src\drivers\berniw2\4\mixed-2.xml .\runtime\drivers\berniw2\4\mixed-2.xml
if exist .\src\drivers\berniw2\4\spring.xml copy .\src\drivers\berniw2\4\spring.xml .\runtime\drivers\berniw2\4\spring.xml
if exist .\src\drivers\berniw2\4\wheel-1.xml copy .\src\drivers\berniw2\4\wheel-1.xml .\runtime\drivers\berniw2\4\wheel-1.xml

if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers\berniw2\5
if exist .\src\drivers\berniw2\5\aalborg.xml copy .\src\drivers\berniw2\5\aalborg.xml .\runtime\drivers\berniw2\5\aalborg.xml
if exist .\src\drivers\berniw2\5\alpine-1.xml copy .\src\drivers\berniw2\5\alpine-1.xml .\runtime\drivers\berniw2\5\alpine-1.xml
if exist .\src\drivers\berniw2\5\a-speedway.xml copy .\src\drivers\berniw2\5\a-speedway.xml .\runtime\drivers\berniw2\5\a-speedway.xml
if exist .\src\drivers\berniw2\5\default.xml copy .\src\drivers\berniw2\5\default.xml .\runtime\drivers\berniw2\5\default.xml
if exist .\src\drivers\berniw2\5\dirt-1.xml copy .\src\drivers\berniw2\5\dirt-1.xml .\runtime\drivers\berniw2\5\dirt-1.xml
if exist .\src\drivers\berniw2\5\dirt-2.xml copy .\src\drivers\berniw2\5\dirt-2.xml .\runtime\drivers\berniw2\5\dirt-2.xml
if exist .\src\drivers\berniw2\5\dirt-3.xml copy .\src\drivers\berniw2\5\dirt-3.xml .\runtime\drivers\berniw2\5\dirt-3.xml
if exist .\src\drivers\berniw2\5\dirt-4.xml copy .\src\drivers\berniw2\5\dirt-4.xml .\runtime\drivers\berniw2\5\dirt-4.xml
if exist .\src\drivers\berniw2\5\dirt-5.xml copy .\src\drivers\berniw2\5\dirt-5.xml .\runtime\drivers\berniw2\5\dirt-5.xml
if exist .\src\drivers\berniw2\5\dirt-6.xml copy .\src\drivers\berniw2\5\dirt-6.xml .\runtime\drivers\berniw2\5\dirt-6.xml
if exist .\src\drivers\berniw2\5\eroad.xml copy .\src\drivers\berniw2\5\eroad.xml .\runtime\drivers\berniw2\5\eroad.xml
if exist .\src\drivers\berniw2\5\e-track-1.xml copy .\src\drivers\berniw2\5\e-track-1.xml .\runtime\drivers\berniw2\5\e-track-1.xml
if exist .\src\drivers\berniw2\5\e-track-2.xml copy .\src\drivers\berniw2\5\e-track-2.xml .\runtime\drivers\berniw2\5\e-track-2.xml
if exist .\src\drivers\berniw2\5\e-track-3.xml copy .\src\drivers\berniw2\5\e-track-3.xml .\runtime\drivers\berniw2\5\e-track-3.xml
if exist .\src\drivers\berniw2\5\e-track-4.xml copy .\src\drivers\berniw2\5\e-track-4.xml .\runtime\drivers\berniw2\5\e-track-4.xml
if exist .\src\drivers\berniw2\5\e-track-5.xml copy .\src\drivers\berniw2\5\e-track-5.xml .\runtime\drivers\berniw2\5\e-track-5.xml
if exist .\src\drivers\berniw2\5\e-track-6.xml copy .\src\drivers\berniw2\5\e-track-6.xml .\runtime\drivers\berniw2\5\e-track-6.xml
if exist .\src\drivers\berniw2\5\g-track-1.xml copy .\src\drivers\berniw2\5\g-track-1.xml .\runtime\drivers\berniw2\5\g-track-1.xml
if exist .\src\drivers\berniw2\5\g-track-2.xml copy .\src\drivers\berniw2\5\g-track-2.xml .\runtime\drivers\berniw2\5\g-track-2.xml
if exist .\src\drivers\berniw2\5\g-track-3.xml copy .\src\drivers\berniw2\5\g-track-3.xml .\runtime\drivers\berniw2\5\g-track-3.xml
if exist .\src\drivers\berniw2\5\michigan.xml copy .\src\drivers\berniw2\5\michigan.xml .\runtime\drivers\berniw2\5\michigan.xml
if exist .\src\drivers\berniw2\5\mixed-1.xml copy .\src\drivers\berniw2\5\mixed-1.xml .\runtime\drivers\berniw2\5\mixed-1.xml
if exist .\src\drivers\berniw2\5\mixed-2.xml copy .\src\drivers\berniw2\5\mixed-2.xml .\runtime\drivers\berniw2\5\mixed-2.xml
if exist .\src\drivers\berniw2\5\spring.xml copy .\src\drivers\berniw2\5\spring.xml .\runtime\drivers\berniw2\5\spring.xml
if exist .\src\drivers\berniw2\5\wheel-1.xml copy .\src\drivers\berniw2\5\wheel-1.xml .\runtime\drivers\berniw2\5\wheel-1.xml

if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers\berniw2\6
if exist .\src\drivers\berniw2\6\aalborg.xml copy .\src\drivers\berniw2\6\aalborg.xml .\runtime\drivers\berniw2\6\aalborg.xml
if exist .\src\drivers\berniw2\6\alpine-1.xml copy .\src\drivers\berniw2\6\alpine-1.xml .\runtime\drivers\berniw2\6\alpine-1.xml
if exist .\src\drivers\berniw2\6\a-speedway.xml copy .\src\drivers\berniw2\6\a-speedway.xml .\runtime\drivers\berniw2\6\a-speedway.xml
if exist .\src\drivers\berniw2\6\default.xml copy .\src\drivers\berniw2\6\default.xml .\runtime\drivers\berniw2\6\default.xml
if exist .\src\drivers\berniw2\6\dirt-1.xml copy .\src\drivers\berniw2\6\dirt-1.xml .\runtime\drivers\berniw2\6\dirt-1.xml
if exist .\src\drivers\berniw2\6\dirt-2.xml copy .\src\drivers\berniw2\6\dirt-2.xml .\runtime\drivers\berniw2\6\dirt-2.xml
if exist .\src\drivers\berniw2\6\dirt-3.xml copy .\src\drivers\berniw2\6\dirt-3.xml .\runtime\drivers\berniw2\6\dirt-3.xml
if exist .\src\drivers\berniw2\6\dirt-4.xml copy .\src\drivers\berniw2\6\dirt-4.xml .\runtime\drivers\berniw2\6\dirt-4.xml
if exist .\src\drivers\berniw2\6\dirt-5.xml copy .\src\drivers\berniw2\6\dirt-5.xml .\runtime\drivers\berniw2\6\dirt-5.xml
if exist .\src\drivers\berniw2\6\dirt-6.xml copy .\src\drivers\berniw2\6\dirt-6.xml .\runtime\drivers\berniw2\6\dirt-6.xml
if exist .\src\drivers\berniw2\6\eroad.xml copy .\src\drivers\berniw2\6\eroad.xml .\runtime\drivers\berniw2\6\eroad.xml
if exist .\src\drivers\berniw2\6\e-track-1.xml copy .\src\drivers\berniw2\6\e-track-1.xml .\runtime\drivers\berniw2\6\e-track-1.xml
if exist .\src\drivers\berniw2\6\e-track-2.xml copy .\src\drivers\berniw2\6\e-track-2.xml .\runtime\drivers\berniw2\6\e-track-2.xml
if exist .\src\drivers\berniw2\6\e-track-3.xml copy .\src\drivers\berniw2\6\e-track-3.xml .\runtime\drivers\berniw2\6\e-track-3.xml
if exist .\src\drivers\berniw2\6\e-track-4.xml copy .\src\drivers\berniw2\6\e-track-4.xml .\runtime\drivers\berniw2\6\e-track-4.xml
if exist .\src\drivers\berniw2\6\e-track-5.xml copy .\src\drivers\berniw2\6\e-track-5.xml .\runtime\drivers\berniw2\6\e-track-5.xml
if exist .\src\drivers\berniw2\6\e-track-6.xml copy .\src\drivers\berniw2\6\e-track-6.xml .\runtime\drivers\berniw2\6\e-track-6.xml
if exist .\src\drivers\berniw2\6\g-track-1.xml copy .\src\drivers\berniw2\6\g-track-1.xml .\runtime\drivers\berniw2\6\g-track-1.xml
if exist .\src\drivers\berniw2\6\g-track-2.xml copy .\src\drivers\berniw2\6\g-track-2.xml .\runtime\drivers\berniw2\6\g-track-2.xml
if exist .\src\drivers\berniw2\6\g-track-3.xml copy .\src\drivers\berniw2\6\g-track-3.xml .\runtime\drivers\berniw2\6\g-track-3.xml
if exist .\src\drivers\berniw2\6\michigan.xml copy .\src\drivers\berniw2\6\michigan.xml .\runtime\drivers\berniw2\6\michigan.xml
if exist .\src\drivers\berniw2\6\mixed-1.xml copy .\src\drivers\berniw2\6\mixed-1.xml .\runtime\drivers\berniw2\6\mixed-1.xml
if exist .\src\drivers\berniw2\6\mixed-2.xml copy .\src\drivers\berniw2\6\mixed-2.xml .\runtime\drivers\berniw2\6\mixed-2.xml
if exist .\src\drivers\berniw2\6\spring.xml copy .\src\drivers\berniw2\6\spring.xml .\runtime\drivers\berniw2\6\spring.xml
if exist .\src\drivers\berniw2\6\wheel-1.xml copy .\src\drivers\berniw2\6\wheel-1.xml .\runtime\drivers\berniw2\6\wheel-1.xml

if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers\berniw2\7
if exist .\src\drivers\berniw2\7\porsche-gt3rs.rgb copy .\src\drivers\berniw2\7\porsche-gt3rs.rgb .\runtime\drivers\berniw2\7\porsche-gt3rs.rgb
if exist .\src\drivers\berniw2\7\aalborg.xml copy .\src\drivers\berniw2\7\aalborg.xml .\runtime\drivers\berniw2\7\aalborg.xml
if exist .\src\drivers\berniw2\7\alpine-1.xml copy .\src\drivers\berniw2\7\alpine-1.xml .\runtime\drivers\berniw2\7\alpine-1.xml
if exist .\src\drivers\berniw2\7\a-speedway.xml copy .\src\drivers\berniw2\7\a-speedway.xml .\runtime\drivers\berniw2\7\a-speedway.xml
if exist .\src\drivers\berniw2\7\default.xml copy .\src\drivers\berniw2\7\default.xml .\runtime\drivers\berniw2\7\default.xml
if exist .\src\drivers\berniw2\7\dirt-1.xml copy .\src\drivers\berniw2\7\dirt-1.xml .\runtime\drivers\berniw2\7\dirt-1.xml
if exist .\src\drivers\berniw2\7\dirt-2.xml copy .\src\drivers\berniw2\7\dirt-2.xml .\runtime\drivers\berniw2\7\dirt-2.xml
if exist .\src\drivers\berniw2\7\dirt-3.xml copy .\src\drivers\berniw2\7\dirt-3.xml .\runtime\drivers\berniw2\7\dirt-3.xml
if exist .\src\drivers\berniw2\7\dirt-4.xml copy .\src\drivers\berniw2\7\dirt-4.xml .\runtime\drivers\berniw2\7\dirt-4.xml
if exist .\src\drivers\berniw2\7\dirt-5.xml copy .\src\drivers\berniw2\7\dirt-5.xml .\runtime\drivers\berniw2\7\dirt-5.xml
if exist .\src\drivers\berniw2\7\dirt-6.xml copy .\src\drivers\berniw2\7\dirt-6.xml .\runtime\drivers\berniw2\7\dirt-6.xml
if exist .\src\drivers\berniw2\7\eroad.xml copy .\src\drivers\berniw2\7\eroad.xml .\runtime\drivers\berniw2\7\eroad.xml
if exist .\src\drivers\berniw2\7\e-track-1.xml copy .\src\drivers\berniw2\7\e-track-1.xml .\runtime\drivers\berniw2\7\e-track-1.xml
if exist .\src\drivers\berniw2\7\e-track-2.xml copy .\src\drivers\berniw2\7\e-track-2.xml .\runtime\drivers\berniw2\7\e-track-2.xml
if exist .\src\drivers\berniw2\7\e-track-3.xml copy .\src\drivers\berniw2\7\e-track-3.xml .\runtime\drivers\berniw2\7\e-track-3.xml
if exist .\src\drivers\berniw2\7\e-track-4.xml copy .\src\drivers\berniw2\7\e-track-4.xml .\runtime\drivers\berniw2\7\e-track-4.xml
if exist .\src\drivers\berniw2\7\e-track-5.xml copy .\src\drivers\berniw2\7\e-track-5.xml .\runtime\drivers\berniw2\7\e-track-5.xml
if exist .\src\drivers\berniw2\7\e-track-6.xml copy .\src\drivers\berniw2\7\e-track-6.xml .\runtime\drivers\berniw2\7\e-track-6.xml
if exist .\src\drivers\berniw2\7\g-track-1.xml copy .\src\drivers\berniw2\7\g-track-1.xml .\runtime\drivers\berniw2\7\g-track-1.xml
if exist .\src\drivers\berniw2\7\g-track-2.xml copy .\src\drivers\berniw2\7\g-track-2.xml .\runtime\drivers\berniw2\7\g-track-2.xml
if exist .\src\drivers\berniw2\7\g-track-3.xml copy .\src\drivers\berniw2\7\g-track-3.xml .\runtime\drivers\berniw2\7\g-track-3.xml
if exist .\src\drivers\berniw2\7\michigan.xml copy .\src\drivers\berniw2\7\michigan.xml .\runtime\drivers\berniw2\7\michigan.xml
if exist .\src\drivers\berniw2\7\mixed-1.xml copy .\src\drivers\berniw2\7\mixed-1.xml .\runtime\drivers\berniw2\7\mixed-1.xml
if exist .\src\drivers\berniw2\7\mixed-2.xml copy .\src\drivers\berniw2\7\mixed-2.xml .\runtime\drivers\berniw2\7\mixed-2.xml
if exist .\src\drivers\berniw2\7\spring.xml copy .\src\drivers\berniw2\7\spring.xml .\runtime\drivers\berniw2\7\spring.xml
if exist .\src\drivers\berniw2\7\wheel-1.xml copy .\src\drivers\berniw2\7\wheel-1.xml .\runtime\drivers\berniw2\7\wheel-1.xml

if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers\berniw2\8
if exist .\src\drivers\berniw2\8\clkdtm.rgb copy .\src\drivers\berniw2\8\clkdtm.rgb .\runtime\drivers\berniw2\8\clkdtm.rgb
if exist .\src\drivers\berniw2\8\aalborg.xml copy .\src\drivers\berniw2\8\aalborg.xml .\runtime\drivers\berniw2\8\aalborg.xml
if exist .\src\drivers\berniw2\8\alpine-1.xml copy .\src\drivers\berniw2\8\alpine-1.xml .\runtime\drivers\berniw2\8\alpine-1.xml
if exist .\src\drivers\berniw2\8\a-speedway.xml copy .\src\drivers\berniw2\8\a-speedway.xml .\runtime\drivers\berniw2\8\a-speedway.xml
if exist .\src\drivers\berniw2\8\default.xml copy .\src\drivers\berniw2\8\default.xml .\runtime\drivers\berniw2\8\default.xml
if exist .\src\drivers\berniw2\8\dirt-1.xml copy .\src\drivers\berniw2\8\dirt-1.xml .\runtime\drivers\berniw2\8\dirt-1.xml
if exist .\src\drivers\berniw2\8\dirt-2.xml copy .\src\drivers\berniw2\8\dirt-2.xml .\runtime\drivers\berniw2\8\dirt-2.xml
if exist .\src\drivers\berniw2\8\dirt-3.xml copy .\src\drivers\berniw2\8\dirt-3.xml .\runtime\drivers\berniw2\8\dirt-3.xml
if exist .\src\drivers\berniw2\8\dirt-4.xml copy .\src\drivers\berniw2\8\dirt-4.xml .\runtime\drivers\berniw2\8\dirt-4.xml
if exist .\src\drivers\berniw2\8\dirt-5.xml copy .\src\drivers\berniw2\8\dirt-5.xml .\runtime\drivers\berniw2\8\dirt-5.xml
if exist .\src\drivers\berniw2\8\dirt-6.xml copy .\src\drivers\berniw2\8\dirt-6.xml .\runtime\drivers\berniw2\8\dirt-6.xml
if exist .\src\drivers\berniw2\8\eroad.xml copy .\src\drivers\berniw2\8\eroad.xml .\runtime\drivers\berniw2\8\eroad.xml
if exist .\src\drivers\berniw2\8\e-track-1.xml copy .\src\drivers\berniw2\8\e-track-1.xml .\runtime\drivers\berniw2\8\e-track-1.xml
if exist .\src\drivers\berniw2\8\e-track-2.xml copy .\src\drivers\berniw2\8\e-track-2.xml .\runtime\drivers\berniw2\8\e-track-2.xml
if exist .\src\drivers\berniw2\8\e-track-3.xml copy .\src\drivers\berniw2\8\e-track-3.xml .\runtime\drivers\berniw2\8\e-track-3.xml
if exist .\src\drivers\berniw2\8\e-track-4.xml copy .\src\drivers\berniw2\8\e-track-4.xml .\runtime\drivers\berniw2\8\e-track-4.xml
if exist .\src\drivers\berniw2\8\e-track-5.xml copy .\src\drivers\berniw2\8\e-track-5.xml .\runtime\drivers\berniw2\8\e-track-5.xml
if exist .\src\drivers\berniw2\8\e-track-6.xml copy .\src\drivers\berniw2\8\e-track-6.xml .\runtime\drivers\berniw2\8\e-track-6.xml
if exist .\src\drivers\berniw2\8\g-track-1.xml copy .\src\drivers\berniw2\8\g-track-1.xml .\runtime\drivers\berniw2\8\g-track-1.xml
if exist .\src\drivers\berniw2\8\g-track-2.xml copy .\src\drivers\berniw2\8\g-track-2.xml .\runtime\drivers\berniw2\8\g-track-2.xml
if exist .\src\drivers\berniw2\8\g-track-3.xml copy .\src\drivers\berniw2\8\g-track-3.xml .\runtime\drivers\berniw2\8\g-track-3.xml
if exist .\src\drivers\berniw2\8\michigan.xml copy .\src\drivers\berniw2\8\michigan.xml .\runtime\drivers\berniw2\8\michigan.xml
if exist .\src\drivers\berniw2\8\mixed-1.xml copy .\src\drivers\berniw2\8\mixed-1.xml .\runtime\drivers\berniw2\8\mixed-1.xml
if exist .\src\drivers\berniw2\8\mixed-2.xml copy .\src\drivers\berniw2\8\mixed-2.xml .\runtime\drivers\berniw2\8\mixed-2.xml
if exist .\src\drivers\berniw2\8\spring.xml copy .\src\drivers\berniw2\8\spring.xml .\runtime\drivers\berniw2\8\spring.xml
if exist .\src\drivers\berniw2\8\wheel-1.xml copy .\src\drivers\berniw2\8\wheel-1.xml .\runtime\drivers\berniw2\8\wheel-1.xml

if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers\berniw2\9
if exist .\src\drivers\berniw2\9\mclaren-f1.rgb copy .\src\drivers\berniw2\9\mclaren-f1.rgb .\runtime\drivers\berniw2\9\mclaren-f1.rgb
if exist .\src\drivers\berniw2\9\aalborg.xml copy .\src\drivers\berniw2\9\aalborg.xml .\runtime\drivers\berniw2\9\aalborg.xml
if exist .\src\drivers\berniw2\9\alpine-1.xml copy .\src\drivers\berniw2\9\alpine-1.xml .\runtime\drivers\berniw2\9\alpine-1.xml
if exist .\src\drivers\berniw2\9\a-speedway.xml copy .\src\drivers\berniw2\9\a-speedway.xml .\runtime\drivers\berniw2\9\a-speedway.xml
if exist .\src\drivers\berniw2\9\default.xml copy .\src\drivers\berniw2\9\default.xml .\runtime\drivers\berniw2\9\default.xml
if exist .\src\drivers\berniw2\9\dirt-1.xml copy .\src\drivers\berniw2\9\dirt-1.xml .\runtime\drivers\berniw2\9\dirt-1.xml
if exist .\src\drivers\berniw2\9\dirt-2.xml copy .\src\drivers\berniw2\9\dirt-2.xml .\runtime\drivers\berniw2\9\dirt-2.xml
if exist .\src\drivers\berniw2\9\dirt-3.xml copy .\src\drivers\berniw2\9\dirt-3.xml .\runtime\drivers\berniw2\9\dirt-3.xml
if exist .\src\drivers\berniw2\9\dirt-4.xml copy .\src\drivers\berniw2\9\dirt-4.xml .\runtime\drivers\berniw2\9\dirt-4.xml
if exist .\src\drivers\berniw2\9\dirt-5.xml copy .\src\drivers\berniw2\9\dirt-5.xml .\runtime\drivers\berniw2\9\dirt-5.xml
if exist .\src\drivers\berniw2\9\dirt-6.xml copy .\src\drivers\berniw2\9\dirt-6.xml .\runtime\drivers\berniw2\9\dirt-6.xml
if exist .\src\drivers\berniw2\9\eroad.xml copy .\src\drivers\berniw2\9\eroad.xml .\runtime\drivers\berniw2\9\eroad.xml
if exist .\src\drivers\berniw2\9\e-track-1.xml copy .\src\drivers\berniw2\9\e-track-1.xml .\runtime\drivers\berniw2\9\e-track-1.xml
if exist .\src\drivers\berniw2\9\e-track-2.xml copy .\src\drivers\berniw2\9\e-track-2.xml .\runtime\drivers\berniw2\9\e-track-2.xml
if exist .\src\drivers\berniw2\9\e-track-3.xml copy .\src\drivers\berniw2\9\e-track-3.xml .\runtime\drivers\berniw2\9\e-track-3.xml
if exist .\src\drivers\berniw2\9\e-track-4.xml copy .\src\drivers\berniw2\9\e-track-4.xml .\runtime\drivers\berniw2\9\e-track-4.xml
if exist .\src\drivers\berniw2\9\e-track-5.xml copy .\src\drivers\berniw2\9\e-track-5.xml .\runtime\drivers\berniw2\9\e-track-5.xml
if exist .\src\drivers\berniw2\9\e-track-6.xml copy .\src\drivers\berniw2\9\e-track-6.xml .\runtime\drivers\berniw2\9\e-track-6.xml
if exist .\src\drivers\berniw2\9\g-track-1.xml copy .\src\drivers\berniw2\9\g-track-1.xml .\runtime\drivers\berniw2\9\g-track-1.xml
if exist .\src\drivers\berniw2\9\g-track-2.xml copy .\src\drivers\berniw2\9\g-track-2.xml .\runtime\drivers\berniw2\9\g-track-2.xml
if exist .\src\drivers\berniw2\9\g-track-3.xml copy .\src\drivers\berniw2\9\g-track-3.xml .\runtime\drivers\berniw2\9\g-track-3.xml
if exist .\src\drivers\berniw2\9\michigan.xml copy .\src\drivers\berniw2\9\michigan.xml .\runtime\drivers\berniw2\9\michigan.xml
if exist .\src\drivers\berniw2\9\mixed-1.xml copy .\src\drivers\berniw2\9\mixed-1.xml .\runtime\drivers\berniw2\9\mixed-1.xml
if exist .\src\drivers\berniw2\9\mixed-2.xml copy .\src\drivers\berniw2\9\mixed-2.xml .\runtime\drivers\berniw2\9\mixed-2.xml
if exist .\src\drivers\berniw2\9\spring.xml copy .\src\drivers\berniw2\9\spring.xml .\runtime\drivers\berniw2\9\spring.xml
if exist .\src\drivers\berniw2\9\wheel-1.xml copy .\src\drivers\berniw2\9\wheel-1.xml .\runtime\drivers\berniw2\9\wheel-1.xml

if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\berniw2.xml copy .\src\drivers\berniw2\berniw2.xml .\runtime\drivers\berniw2\berniw2.xml
if exist .\src\drivers\berniw2\logo.rgb copy .\src\drivers\berniw2\logo.rgb .\runtime\drivers\berniw2\logo.rgb
if exist .\src\drivers\berniw2\parameter.dat copy .\src\drivers\berniw2\parameter.dat .\runtime\drivers\berniw2\parameter.dat
if exist .\src\drivers\berniw2\intsinsqr.dat copy .\src\drivers\berniw2\intsinsqr.dat .\runtime\drivers\berniw2\intsinsqr.dat
if exist .\src\drivers\berniw2\intcossqr.dat copy .\src\drivers\berniw2\intcossqr.dat .\runtime\drivers\berniw2\intcossqr.dat

if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtime\drivers\cylos1
if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtime\drivers\cylos1\tracksdata
if exist .\src\drivers\cylos1\tracksdata\car_e-track-3.xml copy .\src\drivers\cylos1\tracksdata\car_e-track-3.xml .\runtime\drivers\cylos1\tracksdata\car_e-track-3.xml
if exist .\src\drivers\cylos1\tracksdata\car_lemans.xml copy .\src\drivers\cylos1\tracksdata\car_lemans.xml .\runtime\drivers\cylos1\tracksdata\car_lemans.xml
if exist .\src\drivers\cylos1\tracksdata\car_test-1.xml copy .\src\drivers\cylos1\tracksdata\car_test-1.xml .\runtime\drivers\cylos1\tracksdata\car_test-1.xml
if exist .\src\drivers\cylos1\tracksdata\lemans.xml copy .\src\drivers\cylos1\tracksdata\lemans.xml .\runtime\drivers\cylos1\tracksdata\lemans.xml
if exist .\src\drivers\cylos1\tracksdata\michigan.xml copy .\src\drivers\cylos1\tracksdata\michigan.xml .\runtime\drivers\cylos1\tracksdata\michigan.xml

if exist .\src\drivers\cylos1\*.* call .\create_dir .\runtime
if exist .\src\drivers\cylos1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\cylos1\*.* call .\create_dir .\runtime\drivers\cylos1
if exist .\src\drivers\cylos1\cylos1.xml copy .\src\drivers\cylos1\cylos1.xml .\runtime\drivers\cylos1\cylos1.xml
if exist .\src\drivers\cylos1\car1.xml copy .\src\drivers\cylos1\car1.xml .\runtime\drivers\cylos1\car1.xml
if exist .\src\drivers\cylos1\cg-nascar-rwd.rgb copy .\src\drivers\cylos1\cg-nascar-rwd.rgb .\runtime\drivers\cylos1\cg-nascar-rwd.rgb
if exist .\src\drivers\cylos1\logo.rgb copy .\src\drivers\cylos1\logo.rgb .\runtime\drivers\cylos1\logo.rgb

if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtime\drivers\cylos1
if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtime\drivers\cylos1\tracksdata
if exist .\src\drivers\cylos2\tracksdata\car_e-track-3.xml copy .\src\drivers\cylos2\tracksdata\car_e-track-3.xml .\runtime\drivers\cylos1\tracksdata\car_e-track-3.xml
if exist .\src\drivers\cylos2\tracksdata\michigan.xml copy .\src\drivers\cylos2\tracksdata\michigan.xml .\runtime\drivers\cylos1\tracksdata\michigan.xml

if exist .\src\drivers\cylos2\*.* call .\create_dir .\runtime
if exist .\src\drivers\cylos2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\cylos2\*.* call .\create_dir .\runtime\drivers\cylos2
if exist .\src\drivers\cylos2\cylos2.xml copy .\src\drivers\cylos2\cylos2.xml .\runtime\drivers\cylos2\cylos2.xml
if exist .\src\drivers\cylos2\car1.xml copy .\src\drivers\cylos2\car1.xml .\runtime\drivers\cylos2\car1.xml
if exist .\src\drivers\cylos2\cg-nascar-rwd.rgb copy .\src\drivers\cylos2\cg-nascar-rwd.rgb .\runtime\drivers\cylos2\cg-nascar-rwd.rgb
if exist .\src\drivers\cylos2\logo.rgb copy .\src\drivers\cylos2\logo.rgb .\runtime\drivers\cylos2\logo.rgb

if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers\damned\1
if exist .\src\drivers\damned\1\car.xml copy .\src\drivers\damned\1\car.xml .\runtime\drivers\damned\1\car.xml
if exist .\src\drivers\damned\1\car-dirt.xml copy .\src\drivers\damned\1\car-dirt.xml .\runtime\drivers\damned\1\car-dirt.xml
if exist .\src\drivers\damned\1\buggy.rgb copy .\src\drivers\damned\1\buggy.rgb .\runtime\drivers\damned\1\buggy.rgb
if exist .\src\drivers\damned\1\logo.rgb copy .\src\drivers\damned\1\logo.rgb .\runtime\drivers\damned\1\logo.rgb

if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtime\drivers\damned\10
if exist .\src\drivers\damned\10\car.xml copy .\src\drivers\damned\10\car.xml .\runtime\drivers\damned\10\car.xml
if exist .\src\drivers\damned\10\logo.rgb copy .\src\drivers\damned\10\logo.rgb .\runtime\drivers\damned\10\logo.rgb
if exist .\src\drivers\damned\10\155-DTM.rgb copy .\src\drivers\damned\10\155-DTM.rgb .\runtime\drivers\damned\10\155-DTM.rgb

if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers\damned\2
if exist .\src\drivers\damned\2\car.xml copy .\src\drivers\damned\2\car.xml .\runtime\drivers\damned\2\car.xml
if exist .\src\drivers\damned\2\car-dirt.xml copy .\src\drivers\damned\2\car-dirt.xml .\runtime\drivers\damned\2\car-dirt.xml
if exist .\src\drivers\damned\2\buggy.rgb copy .\src\drivers\damned\2\buggy.rgb .\runtime\drivers\damned\2\buggy.rgb
if exist .\src\drivers\damned\2\logo.rgb copy .\src\drivers\damned\2\logo.rgb .\runtime\drivers\damned\2\logo.rgb

if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers\damned\3
if exist .\src\drivers\damned\3\p406.rgb copy .\src\drivers\damned\3\p406.rgb .\runtime\drivers\damned\3\p406.rgb
if exist .\src\drivers\damned\3\car.xml copy .\src\drivers\damned\3\car.xml .\runtime\drivers\damned\3\car.xml
if exist .\src\drivers\damned\3\car-dirt.xml copy .\src\drivers\damned\3\car-dirt.xml .\runtime\drivers\damned\3\car-dirt.xml
if exist .\src\drivers\damned\3\logo.rgb copy .\src\drivers\damned\3\logo.rgb .\runtime\drivers\damned\3\logo.rgb

if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers\damned\4
if exist .\src\drivers\damned\4\p406.rgb copy .\src\drivers\damned\4\p406.rgb .\runtime\drivers\damned\4\p406.rgb
if exist .\src\drivers\damned\4\car.xml copy .\src\drivers\damned\4\car.xml .\runtime\drivers\damned\4\car.xml
if exist .\src\drivers\damned\4\car-dirt.xml copy .\src\drivers\damned\4\car-dirt.xml .\runtime\drivers\damned\4\car-dirt.xml
if exist .\src\drivers\damned\4\torcs.rgb copy .\src\drivers\damned\4\torcs.rgb .\runtime\drivers\damned\4\torcs.rgb
if exist .\src\drivers\damned\4\logo.rgb copy .\src\drivers\damned\4\logo.rgb .\runtime\drivers\damned\4\logo.rgb

if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers\damned\5
if exist .\src\drivers\damned\5\car.xml copy .\src\drivers\damned\5\car.xml .\runtime\drivers\damned\5\car.xml
if exist .\src\drivers\damned\5\car-dirt.xml copy .\src\drivers\damned\5\car-dirt.xml .\runtime\drivers\damned\5\car-dirt.xml
if exist .\src\drivers\damned\5\acura-nsx-sz.rgb copy .\src\drivers\damned\5\acura-nsx-sz.rgb .\runtime\drivers\damned\5\acura-nsx-sz.rgb
if exist .\src\drivers\damned\5\logo.rgb copy .\src\drivers\damned\5\logo.rgb .\runtime\drivers\damned\5\logo.rgb

if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers\damned\6
if exist .\src\drivers\damned\6\car.xml copy .\src\drivers\damned\6\car.xml .\runtime\drivers\damned\6\car.xml
if exist .\src\drivers\damned\6\car-dirt.xml copy .\src\drivers\damned\6\car-dirt.xml .\runtime\drivers\damned\6\car-dirt.xml
if exist .\src\drivers\damned\6\logo.rgb copy .\src\drivers\damned\6\logo.rgb .\runtime\drivers\damned\6\logo.rgb

if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers\damned\7
if exist .\src\drivers\damned\7\porsche-gt1.rgb copy .\src\drivers\damned\7\porsche-gt1.rgb .\runtime\drivers\damned\7\porsche-gt1.rgb
if exist .\src\drivers\damned\7\logo.rgb copy .\src\drivers\damned\7\logo.rgb .\runtime\drivers\damned\7\logo.rgb
if exist .\src\drivers\damned\7\car.xml copy .\src\drivers\damned\7\car.xml .\runtime\drivers\damned\7\car.xml
if exist .\src\drivers\damned\7\car-dirt.xml copy .\src\drivers\damned\7\car-dirt.xml .\runtime\drivers\damned\7\car-dirt.xml

if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers\damned\8
if exist .\src\drivers\damned\8\car.xml copy .\src\drivers\damned\8\car.xml .\runtime\drivers\damned\8\car.xml
if exist .\src\drivers\damned\8\logo.rgb copy .\src\drivers\damned\8\logo.rgb .\runtime\drivers\damned\8\logo.rgb
if exist .\src\drivers\damned\8\mclaren-f1.rgb copy .\src\drivers\damned\8\mclaren-f1.rgb .\runtime\drivers\damned\8\mclaren-f1.rgb

if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers\damned\9
if exist .\src\drivers\damned\9\logo.rgb copy .\src\drivers\damned\9\logo.rgb .\runtime\drivers\damned\9\logo.rgb
if exist .\src\drivers\damned\9\car.xml copy .\src\drivers\damned\9\car.xml .\runtime\drivers\damned\9\car.xml
if exist .\src\drivers\damned\9\360-modena.rgb copy .\src\drivers\damned\9\360-modena.rgb .\runtime\drivers\damned\9\360-modena.rgb

if exist .\src\drivers\damned\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\damned.xml copy .\src\drivers\damned\damned.xml .\runtime\drivers\damned\damned.xml
if exist .\src\drivers\damned\car1.xml copy .\src\drivers\damned\car1.xml .\runtime\drivers\damned\car1.xml

if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-1
if exist .\src\drivers\human\tracks\dirt-1\car-torcs.xml copy .\src\drivers\human\tracks\dirt-1\car-torcs.xml .\runtime\drivers\human\tracks\dirt-1\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-2
if exist .\src\drivers\human\tracks\dirt-2\car-torcs.xml copy .\src\drivers\human\tracks\dirt-2\car-torcs.xml .\runtime\drivers\human\tracks\dirt-2\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-3
if exist .\src\drivers\human\tracks\dirt-3\car-torcs.xml copy .\src\drivers\human\tracks\dirt-3\car-torcs.xml .\runtime\drivers\human\tracks\dirt-3\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-4
if exist .\src\drivers\human\tracks\dirt-4\car-torcs.xml copy .\src\drivers\human\tracks\dirt-4\car-torcs.xml .\runtime\drivers\human\tracks\dirt-4\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-5
if exist .\src\drivers\human\tracks\dirt-5\car-torcs.xml copy .\src\drivers\human\tracks\dirt-5\car-torcs.xml .\runtime\drivers\human\tracks\dirt-5\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-6
if exist .\src\drivers\human\tracks\dirt-6\car-porsche-gt3rs.xml copy .\src\drivers\human\tracks\dirt-6\car-porsche-gt3rs.xml .\runtime\drivers\human\tracks\dirt-6\car-porsche-gt3rs.xml
if exist .\src\drivers\human\tracks\dirt-6\car-torcs.xml copy .\src\drivers\human\tracks\dirt-6\car-torcs.xml .\runtime\drivers\human\tracks\dirt-6\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-1
if exist .\src\drivers\human\tracks\e-track-1\car-torcs.xml copy .\src\drivers\human\tracks\e-track-1\car-torcs.xml .\runtime\drivers\human\tracks\e-track-1\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-2
if exist .\src\drivers\human\tracks\e-track-2\car-206W10.xml copy .\src\drivers\human\tracks\e-track-2\car-206W10.xml .\runtime\drivers\human\tracks\e-track-2\car-206W10.xml
if exist .\src\drivers\human\tracks\e-track-2\car-torcs.xml copy .\src\drivers\human\tracks\e-track-2\car-torcs.xml .\runtime\drivers\human\tracks\e-track-2\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-3
if exist .\src\drivers\human\tracks\e-track-3\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-3\car-porsche-gt1.xml .\runtime\drivers\human\tracks\e-track-3\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-3\car-torcs.xml copy .\src\drivers\human\tracks\e-track-3\car-torcs.xml .\runtime\drivers\human\tracks\e-track-3\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-4
if exist .\src\drivers\human\tracks\e-track-4\car-360-modena.xml copy .\src\drivers\human\tracks\e-track-4\car-360-modena.xml .\runtime\drivers\human\tracks\e-track-4\car-360-modena.xml
if exist .\src\drivers\human\tracks\e-track-4\car-mclaren-f1.xml copy .\src\drivers\human\tracks\e-track-4\car-mclaren-f1.xml .\runtime\drivers\human\tracks\e-track-4\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\e-track-4\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-4\car-porsche-gt1.xml .\runtime\drivers\human\tracks\e-track-4\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml copy .\src\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml .\runtime\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml
if exist .\src\drivers\human\tracks\e-track-4\car-torcs.xml copy .\src\drivers\human\tracks\e-track-4\car-torcs.xml .\runtime\drivers\human\tracks\e-track-4\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-5
if exist .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml copy .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml .\runtime\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml
if exist .\src\drivers\human\tracks\e-track-5\car-torcs.xml copy .\src\drivers\human\tracks\e-track-5\car-torcs.xml .\runtime\drivers\human\tracks\e-track-5\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtime\drivers\human\tracks\e-track-6
if exist .\src\drivers\human\tracks\e-track-6\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-6\car-porsche-gt1.xml .\runtime\drivers\human\tracks\e-track-6\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-6\car-torcs.xml copy .\src\drivers\human\tracks\e-track-6\car-torcs.xml .\runtime\drivers\human\tracks\e-track-6\car-torcs.xml

if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtime\drivers\human\tracks\g-track-2
if exist .\src\drivers\human\tracks\g-track-2\car-360-modena.xml copy .\src\drivers\human\tracks\g-track-2\car-360-modena.xml .\runtime\drivers\human\tracks\g-track-2\car-360-modena.xml
if exist .\src\drivers\human\tracks\g-track-2\car-mclaren-f1.xml copy .\src\drivers\human\tracks\g-track-2\car-mclaren-f1.xml .\runtime\drivers\human\tracks\g-track-2\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\g-track-2\car-porsche-gt1.xml copy .\src\drivers\human\tracks\g-track-2\car-porsche-gt1.xml .\runtime\drivers\human\tracks\g-track-2\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml copy .\src\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml .\runtime\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml
if exist .\src\drivers\human\tracks\g-track-2\car-torcs.xml copy .\src\drivers\human\tracks\g-track-2\car-torcs.xml .\runtime\drivers\human\tracks\g-track-2\car-torcs.xml

if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtime\drivers\human\tracks\g-track-3
if exist .\src\drivers\human\tracks\g-track-3\car-206W10.xml copy .\src\drivers\human\tracks\g-track-3\car-206W10.xml .\runtime\drivers\human\tracks\g-track-3\car-206W10.xml

if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtime\drivers\human\tracks\mixed-1
if exist .\src\drivers\human\tracks\mixed-1\car-torcs.xml copy .\src\drivers\human\tracks\mixed-1\car-torcs.xml .\runtime\drivers\human\tracks\mixed-1\car-torcs.xml

if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtime\drivers\human\tracks\mixed-2
if exist .\src\drivers\human\tracks\mixed-2\car-torcs.xml copy .\src\drivers\human\tracks\mixed-2\car-torcs.xml .\runtime\drivers\human\tracks\mixed-2\car-torcs.xml

if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtime\drivers\human\tracks\spring
if exist .\src\drivers\human\tracks\spring\car-206W10.xml copy .\src\drivers\human\tracks\spring\car-206W10.xml .\runtime\drivers\human\tracks\spring\car-206W10.xml

if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtime\drivers\human\tracks\wheel-1
if exist .\src\drivers\human\tracks\wheel-1\car-mclaren-f1.xml copy .\src\drivers\human\tracks\wheel-1\car-mclaren-f1.xml .\runtime\drivers\human\tracks\wheel-1\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\wheel-1\car-porsche-gt1.xml copy .\src\drivers\human\tracks\wheel-1\car-porsche-gt1.xml .\runtime\drivers\human\tracks\wheel-1\car-porsche-gt1.xml

if exist .\src\drivers\human\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\car-155-DTM.xml copy .\src\drivers\human\car-155-DTM.xml .\runtime\drivers\human\car-155-DTM.xml
if exist .\src\drivers\human\car-206W10.xml copy .\src\drivers\human\car-206W10.xml .\runtime\drivers\human\car-206W10.xml
if exist .\src\drivers\human\car-360-modena.xml copy .\src\drivers\human\car-360-modena.xml .\runtime\drivers\human\car-360-modena.xml
if exist .\src\drivers\human\car-acura-nsx-sz.xml copy .\src\drivers\human\car-acura-nsx-sz.xml .\runtime\drivers\human\car-acura-nsx-sz.xml
if exist .\src\drivers\human\car-alpha-156-rk.xml copy .\src\drivers\human\car-alpha-156-rk.xml .\runtime\drivers\human\car-alpha-156-rk.xml
if exist .\src\drivers\human\car-buggy.xml copy .\src\drivers\human\car-buggy.xml .\runtime\drivers\human\car-buggy.xml
if exist .\src\drivers\human\car-cg-gt-rwd.xml copy .\src\drivers\human\car-cg-gt-rwd.xml .\runtime\drivers\human\car-cg-gt-rwd.xml
if exist .\src\drivers\human\car-cg-nascar-fwd.xml copy .\src\drivers\human\car-cg-nascar-fwd.xml .\runtime\drivers\human\car-cg-nascar-fwd.xml
if exist .\src\drivers\human\car-cg-nascar-rwd.xml copy .\src\drivers\human\car-cg-nascar-rwd.xml .\runtime\drivers\human\car-cg-nascar-rwd.xml
if exist .\src\drivers\human\car-clkdtm.xml copy .\src\drivers\human\car-clkdtm.xml .\runtime\drivers\human\car-clkdtm.xml
if exist .\src\drivers\human\car-corvette.xml copy .\src\drivers\human\car-corvette.xml .\runtime\drivers\human\car-corvette.xml
if exist .\src\drivers\human\car-fs-02h2.xml copy .\src\drivers\human\car-fs-02h2.xml .\runtime\drivers\human\car-fs-02h2.xml
if exist .\src\drivers\human\car-lotus-gt1.xml copy .\src\drivers\human\car-lotus-gt1.xml .\runtime\drivers\human\car-lotus-gt1.xml
if exist .\src\drivers\human\car-mclaren-f1.xml copy .\src\drivers\human\car-mclaren-f1.xml .\runtime\drivers\human\car-mclaren-f1.xml
if exist .\src\drivers\human\car-p406.xml copy .\src\drivers\human\car-p406.xml .\runtime\drivers\human\car-p406.xml
if exist .\src\drivers\human\car-porsche-gt1.xml copy .\src\drivers\human\car-porsche-gt1.xml .\runtime\drivers\human\car-porsche-gt1.xml
if exist .\src\drivers\human\car-porsche-gt3rs.xml copy .\src\drivers\human\car-porsche-gt3rs.xml .\runtime\drivers\human\car-porsche-gt3rs.xml
if exist .\src\drivers\human\car-torcs.xml copy .\src\drivers\human\car-torcs.xml .\runtime\drivers\human\car-torcs.xml
if exist .\src\drivers\human\car-viper-gts-r.xml copy .\src\drivers\human\car-viper-gts-r.xml .\runtime\drivers\human\car-viper-gts-r.xml
if exist .\src\drivers\human\car-vm-x2.xml copy .\src\drivers\human\car-vm-x2.xml .\runtime\drivers\human\car-vm-x2.xml
if exist .\src\drivers\human\car-vm-x4.xml copy .\src\drivers\human\car-vm-x4.xml .\runtime\drivers\human\car-vm-x4.xml
if exist .\src\drivers\human\car.xml copy .\src\drivers\human\car.xml .\runtime\drivers\human\car.xml
if exist .\src\drivers\human\human.xml copy .\src\drivers\human\human.xml .\runtime\drivers\human\human.xml
if exist .\src\drivers\human\preferences.xml copy .\src\drivers\human\preferences.xml .\runtime\drivers\human\preferences.xml
if exist .\src\drivers\human\logo.rgb copy .\src\drivers\human\logo.rgb .\runtime\drivers\human\logo.rgb
if exist .\src\drivers\human\mclaren-f1.rgb copy .\src\drivers\human\mclaren-f1.rgb .\runtime\drivers\human\mclaren-f1.rgb

if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\1
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\1\tracksdata
if exist .\src\drivers\inferno\1\tracksdata\aalborg.xml copy .\src\drivers\inferno\1\tracksdata\aalborg.xml .\runtime\drivers\inferno\1\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\1\tracksdata\alpine-1.xml copy .\src\drivers\inferno\1\tracksdata\alpine-1.xml .\runtime\drivers\inferno\1\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\1\tracksdata\a-speedway.xml copy .\src\drivers\inferno\1\tracksdata\a-speedway.xml .\runtime\drivers\inferno\1\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\1\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\1\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\1\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\1\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\1\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\car_eroad.xml copy .\src\drivers\inferno\1\tracksdata\car_eroad.xml .\runtime\drivers\inferno\1\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\1\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\1\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\1\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\1\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\1\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\1\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\car_michigan.xml copy .\src\drivers\inferno\1\tracksdata\car_michigan.xml .\runtime\drivers\inferno\1\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\1\tracksdata\car_s2.xml copy .\src\drivers\inferno\1\tracksdata\car_s2.xml .\runtime\drivers\inferno\1\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\1\tracksdata\car_test-1.xml copy .\src\drivers\inferno\1\tracksdata\car_test-1.xml .\runtime\drivers\inferno\1\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\1\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\1\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\1\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\1\tracksdata\city-1.xml copy .\src\drivers\inferno\1\tracksdata\city-1.xml .\runtime\drivers\inferno\1\tracksdata\city-1.xml
if exist .\src\drivers\inferno\1\tracksdata\eroad.xml copy .\src\drivers\inferno\1\tracksdata\eroad.xml .\runtime\drivers\inferno\1\tracksdata\eroad.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-1.xml copy .\src\drivers\inferno\1\tracksdata\e-track-1.xml .\runtime\drivers\inferno\1\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-2.xml copy .\src\drivers\inferno\1\tracksdata\e-track-2.xml .\runtime\drivers\inferno\1\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-3.xml copy .\src\drivers\inferno\1\tracksdata\e-track-3.xml .\runtime\drivers\inferno\1\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-4.xml copy .\src\drivers\inferno\1\tracksdata\e-track-4.xml .\runtime\drivers\inferno\1\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-5.xml copy .\src\drivers\inferno\1\tracksdata\e-track-5.xml .\runtime\drivers\inferno\1\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-6.xml copy .\src\drivers\inferno\1\tracksdata\e-track-6.xml .\runtime\drivers\inferno\1\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\1\tracksdata\g-track-1.xml copy .\src\drivers\inferno\1\tracksdata\g-track-1.xml .\runtime\drivers\inferno\1\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\g-track-2.xml copy .\src\drivers\inferno\1\tracksdata\g-track-2.xml .\runtime\drivers\inferno\1\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\michigan.xml copy .\src\drivers\inferno\1\tracksdata\michigan.xml .\runtime\drivers\inferno\1\tracksdata\michigan.xml
if exist .\src\drivers\inferno\1\tracksdata\s2.xml copy .\src\drivers\inferno\1\tracksdata\s2.xml .\runtime\drivers\inferno\1\tracksdata\s2.xml
if exist .\src\drivers\inferno\1\tracksdata\wheel-1.xml copy .\src\drivers\inferno\1\tracksdata\wheel-1.xml .\runtime\drivers\inferno\1\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers\inferno\1
if exist .\src\drivers\inferno\1\defaultcar.xml copy .\src\drivers\inferno\1\defaultcar.xml .\runtime\drivers\inferno\1\defaultcar.xml
if exist .\src\drivers\inferno\1\default.xml copy .\src\drivers\inferno\1\default.xml .\runtime\drivers\inferno\1\default.xml
if exist .\src\drivers\inferno\1\logo.rgb copy .\src\drivers\inferno\1\logo.rgb .\runtime\drivers\inferno\1\logo.rgb
if exist .\src\drivers\inferno\1\Makefile copy .\src\drivers\inferno\1\Makefile .\runtime\drivers\inferno\1\Makefile
if exist .\src\drivers\inferno\1\mclaren-f1.rgb copy .\src\drivers\inferno\1\mclaren-f1.rgb .\runtime\drivers\inferno\1\mclaren-f1.rgb

if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\10
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\10\tracksdata
if exist .\src\drivers\inferno\10\tracksdata\aalborg.xml copy .\src\drivers\inferno\10\tracksdata\aalborg.xml .\runtime\drivers\inferno\10\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\10\tracksdata\a-speedway.xml copy .\src\drivers\inferno\10\tracksdata\a-speedway.xml .\runtime\drivers\inferno\10\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\10\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\10\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\10\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\10\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\10\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\10\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\10\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\10\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\10\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\10\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\10\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\10\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\10\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\10\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\eroad.xml copy .\src\drivers\inferno\10\tracksdata\eroad.xml .\runtime\drivers\inferno\10\tracksdata\eroad.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-1.xml copy .\src\drivers\inferno\10\tracksdata\e-track-1.xml .\runtime\drivers\inferno\10\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-2.xml copy .\src\drivers\inferno\10\tracksdata\e-track-2.xml .\runtime\drivers\inferno\10\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-3.xml copy .\src\drivers\inferno\10\tracksdata\e-track-3.xml .\runtime\drivers\inferno\10\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-4.xml copy .\src\drivers\inferno\10\tracksdata\e-track-4.xml .\runtime\drivers\inferno\10\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-5.xml copy .\src\drivers\inferno\10\tracksdata\e-track-5.xml .\runtime\drivers\inferno\10\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-6.xml copy .\src\drivers\inferno\10\tracksdata\e-track-6.xml .\runtime\drivers\inferno\10\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\10\tracksdata\g-track-1.xml copy .\src\drivers\inferno\10\tracksdata\g-track-1.xml .\runtime\drivers\inferno\10\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\10\tracksdata\g-track-2.xml copy .\src\drivers\inferno\10\tracksdata\g-track-2.xml .\runtime\drivers\inferno\10\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\michigan.xml copy .\src\drivers\inferno\10\tracksdata\michigan.xml .\runtime\drivers\inferno\10\tracksdata\michigan.xml
if exist .\src\drivers\inferno\10\tracksdata\wheel-1.xml copy .\src\drivers\inferno\10\tracksdata\wheel-1.xml .\runtime\drivers\inferno\10\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers\inferno\10
if exist .\src\drivers\inferno\10\defaultcar.xml copy .\src\drivers\inferno\10\defaultcar.xml .\runtime\drivers\inferno\10\defaultcar.xml
if exist .\src\drivers\inferno\10\default.xml copy .\src\drivers\inferno\10\default.xml .\runtime\drivers\inferno\10\default.xml
if exist .\src\drivers\inferno\10\logo.rgb copy .\src\drivers\inferno\10\logo.rgb .\runtime\drivers\inferno\10\logo.rgb
if exist .\src\drivers\inferno\10\Makefile copy .\src\drivers\inferno\10\Makefile .\runtime\drivers\inferno\10\Makefile
if exist .\src\drivers\inferno\10\vm-x4.rgb copy .\src\drivers\inferno\10\vm-x4.rgb .\runtime\drivers\inferno\10\vm-x4.rgb

if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\2
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\2\tracksdata
if exist .\src\drivers\inferno\2\tracksdata\aalborg.xml copy .\src\drivers\inferno\2\tracksdata\aalborg.xml .\runtime\drivers\inferno\2\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\2\tracksdata\a-speedway.xml copy .\src\drivers\inferno\2\tracksdata\a-speedway.xml .\runtime\drivers\inferno\2\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\2\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\2\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\2\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\2\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\2\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\car_eroad.xml copy .\src\drivers\inferno\2\tracksdata\car_eroad.xml .\runtime\drivers\inferno\2\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\2\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\2\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\2\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\2\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\2\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\2\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\car_michigan.xml copy .\src\drivers\inferno\2\tracksdata\car_michigan.xml .\runtime\drivers\inferno\2\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\2\tracksdata\car_s2.xml copy .\src\drivers\inferno\2\tracksdata\car_s2.xml .\runtime\drivers\inferno\2\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\2\tracksdata\car_test-1.xml copy .\src\drivers\inferno\2\tracksdata\car_test-1.xml .\runtime\drivers\inferno\2\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\2\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\2\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\2\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\2\tracksdata\eroad.xml copy .\src\drivers\inferno\2\tracksdata\eroad.xml .\runtime\drivers\inferno\2\tracksdata\eroad.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-1.xml copy .\src\drivers\inferno\2\tracksdata\e-track-1.xml .\runtime\drivers\inferno\2\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-2.xml copy .\src\drivers\inferno\2\tracksdata\e-track-2.xml .\runtime\drivers\inferno\2\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-3.xml copy .\src\drivers\inferno\2\tracksdata\e-track-3.xml .\runtime\drivers\inferno\2\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-4.xml copy .\src\drivers\inferno\2\tracksdata\e-track-4.xml .\runtime\drivers\inferno\2\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-5.xml copy .\src\drivers\inferno\2\tracksdata\e-track-5.xml .\runtime\drivers\inferno\2\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-6.xml copy .\src\drivers\inferno\2\tracksdata\e-track-6.xml .\runtime\drivers\inferno\2\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\2\tracksdata\g-track-1.xml copy .\src\drivers\inferno\2\tracksdata\g-track-1.xml .\runtime\drivers\inferno\2\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\g-track-2.xml copy .\src\drivers\inferno\2\tracksdata\g-track-2.xml .\runtime\drivers\inferno\2\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\michigan.xml copy .\src\drivers\inferno\2\tracksdata\michigan.xml .\runtime\drivers\inferno\2\tracksdata\michigan.xml
if exist .\src\drivers\inferno\2\tracksdata\s2.xml copy .\src\drivers\inferno\2\tracksdata\s2.xml .\runtime\drivers\inferno\2\tracksdata\s2.xml
if exist .\src\drivers\inferno\2\tracksdata\wheel-1.xml copy .\src\drivers\inferno\2\tracksdata\wheel-1.xml .\runtime\drivers\inferno\2\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers\inferno\2
if exist .\src\drivers\inferno\2\360-modena.rgb copy .\src\drivers\inferno\2\360-modena.rgb .\runtime\drivers\inferno\2\360-modena.rgb
if exist .\src\drivers\inferno\2\defaultcar.xml copy .\src\drivers\inferno\2\defaultcar.xml .\runtime\drivers\inferno\2\defaultcar.xml
if exist .\src\drivers\inferno\2\default.xml copy .\src\drivers\inferno\2\default.xml .\runtime\drivers\inferno\2\default.xml
if exist .\src\drivers\inferno\2\logo.rgb copy .\src\drivers\inferno\2\logo.rgb .\runtime\drivers\inferno\2\logo.rgb
if exist .\src\drivers\inferno\2\Makefile copy .\src\drivers\inferno\2\Makefile .\runtime\drivers\inferno\2\Makefile

if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\3
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\3\tracksdata
if exist .\src\drivers\inferno\3\tracksdata\aalborg.xml copy .\src\drivers\inferno\3\tracksdata\aalborg.xml .\runtime\drivers\inferno\3\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\3\tracksdata\alpine-1.xml copy .\src\drivers\inferno\3\tracksdata\alpine-1.xml .\runtime\drivers\inferno\3\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\3\tracksdata\a-speedway.xml copy .\src\drivers\inferno\3\tracksdata\a-speedway.xml .\runtime\drivers\inferno\3\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\3\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\3\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\3\tracksdata\car_alpine-1.xml copy .\src\drivers\inferno\3\tracksdata\car_alpine-1.xml .\runtime\drivers\inferno\3\tracksdata\car_alpine-1.xml
if exist .\src\drivers\inferno\3\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\3\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\3\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_eroad.xml copy .\src\drivers\inferno\3\tracksdata\car_eroad.xml .\runtime\drivers\inferno\3\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\3\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\3\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\3\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\3\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\3\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\3\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\car_michigan.xml copy .\src\drivers\inferno\3\tracksdata\car_michigan.xml .\runtime\drivers\inferno\3\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\3\tracksdata\car_spring.xml copy .\src\drivers\inferno\3\tracksdata\car_spring.xml .\runtime\drivers\inferno\3\tracksdata\car_spring.xml
if exist .\src\drivers\inferno\3\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\3\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\3\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\3\tracksdata\eroad.xml copy .\src\drivers\inferno\3\tracksdata\eroad.xml .\runtime\drivers\inferno\3\tracksdata\eroad.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-1.xml copy .\src\drivers\inferno\3\tracksdata\e-track-1.xml .\runtime\drivers\inferno\3\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-2.xml copy .\src\drivers\inferno\3\tracksdata\e-track-2.xml .\runtime\drivers\inferno\3\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-3.xml copy .\src\drivers\inferno\3\tracksdata\e-track-3.xml .\runtime\drivers\inferno\3\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-4.xml copy .\src\drivers\inferno\3\tracksdata\e-track-4.xml .\runtime\drivers\inferno\3\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-5.xml copy .\src\drivers\inferno\3\tracksdata\e-track-5.xml .\runtime\drivers\inferno\3\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-6.xml copy .\src\drivers\inferno\3\tracksdata\e-track-6.xml .\runtime\drivers\inferno\3\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\3\tracksdata\g-track-1.xml copy .\src\drivers\inferno\3\tracksdata\g-track-1.xml .\runtime\drivers\inferno\3\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\g-track-2.xml copy .\src\drivers\inferno\3\tracksdata\g-track-2.xml .\runtime\drivers\inferno\3\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\michigan.xml copy .\src\drivers\inferno\3\tracksdata\michigan.xml .\runtime\drivers\inferno\3\tracksdata\michigan.xml
if exist .\src\drivers\inferno\3\tracksdata\spring.xml copy .\src\drivers\inferno\3\tracksdata\spring.xml .\runtime\drivers\inferno\3\tracksdata\spring.xml
if exist .\src\drivers\inferno\3\tracksdata\wheel-1.xml copy .\src\drivers\inferno\3\tracksdata\wheel-1.xml .\runtime\drivers\inferno\3\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers\inferno\3
if exist .\src\drivers\inferno\3\defaultcar.xml copy .\src\drivers\inferno\3\defaultcar.xml .\runtime\drivers\inferno\3\defaultcar.xml
if exist .\src\drivers\inferno\3\default.xml copy .\src\drivers\inferno\3\default.xml .\runtime\drivers\inferno\3\default.xml
if exist .\src\drivers\inferno\3\logo.rgb copy .\src\drivers\inferno\3\logo.rgb .\runtime\drivers\inferno\3\logo.rgb
if exist .\src\drivers\inferno\3\Makefile copy .\src\drivers\inferno\3\Makefile .\runtime\drivers\inferno\3\Makefile
if exist .\src\drivers\inferno\3\porsche-gt1.rgb copy .\src\drivers\inferno\3\porsche-gt1.rgb .\runtime\drivers\inferno\3\porsche-gt1.rgb

if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\4
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\4\tracksdata
if exist .\src\drivers\inferno\4\tracksdata\aalborg.xml copy .\src\drivers\inferno\4\tracksdata\aalborg.xml .\runtime\drivers\inferno\4\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\4\tracksdata\alpine-1.xml copy .\src\drivers\inferno\4\tracksdata\alpine-1.xml .\runtime\drivers\inferno\4\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\4\tracksdata\a-speedway.xml copy .\src\drivers\inferno\4\tracksdata\a-speedway.xml .\runtime\drivers\inferno\4\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\4\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\4\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\4\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\4\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\4\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\car_eroad.xml copy .\src\drivers\inferno\4\tracksdata\car_eroad.xml .\runtime\drivers\inferno\4\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\4\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\4\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\4\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\4\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\4\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\4\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\car_g-track-3.xml copy .\src\drivers\inferno\4\tracksdata\car_g-track-3.xml .\runtime\drivers\inferno\4\tracksdata\car_g-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\car_michigan.xml copy .\src\drivers\inferno\4\tracksdata\car_michigan.xml .\runtime\drivers\inferno\4\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\4\tracksdata\car_test-1.xml copy .\src\drivers\inferno\4\tracksdata\car_test-1.xml .\runtime\drivers\inferno\4\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\4\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\4\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\4\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\4\tracksdata\dirt-2.xml copy .\src\drivers\inferno\4\tracksdata\dirt-2.xml .\runtime\drivers\inferno\4\tracksdata\dirt-2.xml
if exist .\src\drivers\inferno\4\tracksdata\eroad.xml copy .\src\drivers\inferno\4\tracksdata\eroad.xml .\runtime\drivers\inferno\4\tracksdata\eroad.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-1.xml copy .\src\drivers\inferno\4\tracksdata\e-track-1.xml .\runtime\drivers\inferno\4\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-2.xml copy .\src\drivers\inferno\4\tracksdata\e-track-2.xml .\runtime\drivers\inferno\4\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-3.xml copy .\src\drivers\inferno\4\tracksdata\e-track-3.xml .\runtime\drivers\inferno\4\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-4.xml copy .\src\drivers\inferno\4\tracksdata\e-track-4.xml .\runtime\drivers\inferno\4\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-5.xml copy .\src\drivers\inferno\4\tracksdata\e-track-5.xml .\runtime\drivers\inferno\4\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-6.xml copy .\src\drivers\inferno\4\tracksdata\e-track-6.xml .\runtime\drivers\inferno\4\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\4\tracksdata\g-track-1.xml copy .\src\drivers\inferno\4\tracksdata\g-track-1.xml .\runtime\drivers\inferno\4\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\g-track-2.xml copy .\src\drivers\inferno\4\tracksdata\g-track-2.xml .\runtime\drivers\inferno\4\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\g-track-3.xml copy .\src\drivers\inferno\4\tracksdata\g-track-3.xml .\runtime\drivers\inferno\4\tracksdata\g-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\michigan.xml copy .\src\drivers\inferno\4\tracksdata\michigan.xml .\runtime\drivers\inferno\4\tracksdata\michigan.xml
if exist .\src\drivers\inferno\4\tracksdata\wheel-1.xml copy .\src\drivers\inferno\4\tracksdata\wheel-1.xml .\runtime\drivers\inferno\4\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers\inferno\4
if exist .\src\drivers\inferno\4\clkdtm.rgb copy .\src\drivers\inferno\4\clkdtm.rgb .\runtime\drivers\inferno\4\clkdtm.rgb
if exist .\src\drivers\inferno\4\defaultcar.xml copy .\src\drivers\inferno\4\defaultcar.xml .\runtime\drivers\inferno\4\defaultcar.xml
if exist .\src\drivers\inferno\4\default.xml copy .\src\drivers\inferno\4\default.xml .\runtime\drivers\inferno\4\default.xml
if exist .\src\drivers\inferno\4\logo.rgb copy .\src\drivers\inferno\4\logo.rgb .\runtime\drivers\inferno\4\logo.rgb
if exist .\src\drivers\inferno\4\Makefile copy .\src\drivers\inferno\4\Makefile .\runtime\drivers\inferno\4\Makefile

if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\5
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\5\tracksdata
if exist .\src\drivers\inferno\5\tracksdata\aalborg.xml copy .\src\drivers\inferno\5\tracksdata\aalborg.xml .\runtime\drivers\inferno\5\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\5\tracksdata\a-speedway.xml copy .\src\drivers\inferno\5\tracksdata\a-speedway.xml .\runtime\drivers\inferno\5\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\5\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\5\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\5\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\5\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\5\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\5\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\5\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\5\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\5\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\5\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\5\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\5\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\5\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\5\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\eroad.xml copy .\src\drivers\inferno\5\tracksdata\eroad.xml .\runtime\drivers\inferno\5\tracksdata\eroad.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-1.xml copy .\src\drivers\inferno\5\tracksdata\e-track-1.xml .\runtime\drivers\inferno\5\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-2.xml copy .\src\drivers\inferno\5\tracksdata\e-track-2.xml .\runtime\drivers\inferno\5\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-3.xml copy .\src\drivers\inferno\5\tracksdata\e-track-3.xml .\runtime\drivers\inferno\5\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-4.xml copy .\src\drivers\inferno\5\tracksdata\e-track-4.xml .\runtime\drivers\inferno\5\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-5.xml copy .\src\drivers\inferno\5\tracksdata\e-track-5.xml .\runtime\drivers\inferno\5\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-6.xml copy .\src\drivers\inferno\5\tracksdata\e-track-6.xml .\runtime\drivers\inferno\5\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\5\tracksdata\g-track-1.xml copy .\src\drivers\inferno\5\tracksdata\g-track-1.xml .\runtime\drivers\inferno\5\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\5\tracksdata\g-track-2.xml copy .\src\drivers\inferno\5\tracksdata\g-track-2.xml .\runtime\drivers\inferno\5\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\michigan.xml copy .\src\drivers\inferno\5\tracksdata\michigan.xml .\runtime\drivers\inferno\5\tracksdata\michigan.xml
if exist .\src\drivers\inferno\5\tracksdata\wheel-1.xml copy .\src\drivers\inferno\5\tracksdata\wheel-1.xml .\runtime\drivers\inferno\5\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers\inferno\5
if exist .\src\drivers\inferno\5\defaultcar.xml copy .\src\drivers\inferno\5\defaultcar.xml .\runtime\drivers\inferno\5\defaultcar.xml
if exist .\src\drivers\inferno\5\default.xml copy .\src\drivers\inferno\5\default.xml .\runtime\drivers\inferno\5\default.xml
if exist .\src\drivers\inferno\5\gt40.rgb copy .\src\drivers\inferno\5\gt40.rgb .\runtime\drivers\inferno\5\gt40.rgb
if exist .\src\drivers\inferno\5\logo.rgb copy .\src\drivers\inferno\5\logo.rgb .\runtime\drivers\inferno\5\logo.rgb
if exist .\src\drivers\inferno\5\Makefile copy .\src\drivers\inferno\5\Makefile .\runtime\drivers\inferno\5\Makefile

if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\6
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\6\tracksdata
if exist .\src\drivers\inferno\6\tracksdata\aalborg.xml copy .\src\drivers\inferno\6\tracksdata\aalborg.xml .\runtime\drivers\inferno\6\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\6\tracksdata\a-speedway.xml copy .\src\drivers\inferno\6\tracksdata\a-speedway.xml .\runtime\drivers\inferno\6\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\6\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\6\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\6\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\6\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\6\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\6\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\6\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\6\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\6\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\6\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\6\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\6\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\6\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\car_g-track-3.xml copy .\src\drivers\inferno\6\tracksdata\car_g-track-3.xml .\runtime\drivers\inferno\6\tracksdata\car_g-track-3.xml
if exist .\src\drivers\inferno\6\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\6\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\6\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\6\tracksdata\eroad.xml copy .\src\drivers\inferno\6\tracksdata\eroad.xml .\runtime\drivers\inferno\6\tracksdata\eroad.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-1.xml copy .\src\drivers\inferno\6\tracksdata\e-track-1.xml .\runtime\drivers\inferno\6\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-2.xml copy .\src\drivers\inferno\6\tracksdata\e-track-2.xml .\runtime\drivers\inferno\6\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-3.xml copy .\src\drivers\inferno\6\tracksdata\e-track-3.xml .\runtime\drivers\inferno\6\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-4.xml copy .\src\drivers\inferno\6\tracksdata\e-track-4.xml .\runtime\drivers\inferno\6\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-5.xml copy .\src\drivers\inferno\6\tracksdata\e-track-5.xml .\runtime\drivers\inferno\6\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-6.xml copy .\src\drivers\inferno\6\tracksdata\e-track-6.xml .\runtime\drivers\inferno\6\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\6\tracksdata\g-track-1.xml copy .\src\drivers\inferno\6\tracksdata\g-track-1.xml .\runtime\drivers\inferno\6\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\6\tracksdata\g-track-2.xml copy .\src\drivers\inferno\6\tracksdata\g-track-2.xml .\runtime\drivers\inferno\6\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\g-track-3.xml copy .\src\drivers\inferno\6\tracksdata\g-track-3.xml .\runtime\drivers\inferno\6\tracksdata\g-track-3.xml
if exist .\src\drivers\inferno\6\tracksdata\michigan.xml copy .\src\drivers\inferno\6\tracksdata\michigan.xml .\runtime\drivers\inferno\6\tracksdata\michigan.xml
if exist .\src\drivers\inferno\6\tracksdata\wheel-1.xml copy .\src\drivers\inferno\6\tracksdata\wheel-1.xml .\runtime\drivers\inferno\6\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers\inferno\6
if exist .\src\drivers\inferno\6\defaultcar.xml copy .\src\drivers\inferno\6\defaultcar.xml .\runtime\drivers\inferno\6\defaultcar.xml
if exist .\src\drivers\inferno\6\default.xml copy .\src\drivers\inferno\6\default.xml .\runtime\drivers\inferno\6\default.xml
if exist .\src\drivers\inferno\6\logo.rgb copy .\src\drivers\inferno\6\logo.rgb .\runtime\drivers\inferno\6\logo.rgb
if exist .\src\drivers\inferno\6\Makefile copy .\src\drivers\inferno\6\Makefile .\runtime\drivers\inferno\6\Makefile
if exist .\src\drivers\inferno\6\porsche-gt3rs.rgb copy .\src\drivers\inferno\6\porsche-gt3rs.rgb .\runtime\drivers\inferno\6\porsche-gt3rs.rgb

if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\7
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\7\tracksdata
if exist .\src\drivers\inferno\7\tracksdata\aalborg.xml copy .\src\drivers\inferno\7\tracksdata\aalborg.xml .\runtime\drivers\inferno\7\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\7\tracksdata\alpine-1.xml copy .\src\drivers\inferno\7\tracksdata\alpine-1.xml .\runtime\drivers\inferno\7\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\7\tracksdata\a-speedway.xml copy .\src\drivers\inferno\7\tracksdata\a-speedway.xml .\runtime\drivers\inferno\7\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\7\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\7\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\7\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\7\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\7\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\car_eroad.xml copy .\src\drivers\inferno\7\tracksdata\car_eroad.xml .\runtime\drivers\inferno\7\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\7\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\7\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\7\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\7\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\7\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\7\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\car_michigan.xml copy .\src\drivers\inferno\7\tracksdata\car_michigan.xml .\runtime\drivers\inferno\7\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\7\tracksdata\car_s2.xml copy .\src\drivers\inferno\7\tracksdata\car_s2.xml .\runtime\drivers\inferno\7\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\7\tracksdata\car_test-1.xml copy .\src\drivers\inferno\7\tracksdata\car_test-1.xml .\runtime\drivers\inferno\7\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\7\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\7\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\7\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\7\tracksdata\city-1.xml copy .\src\drivers\inferno\7\tracksdata\city-1.xml .\runtime\drivers\inferno\7\tracksdata\city-1.xml
if exist .\src\drivers\inferno\7\tracksdata\eroad.xml copy .\src\drivers\inferno\7\tracksdata\eroad.xml .\runtime\drivers\inferno\7\tracksdata\eroad.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-1.xml copy .\src\drivers\inferno\7\tracksdata\e-track-1.xml .\runtime\drivers\inferno\7\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-2.xml copy .\src\drivers\inferno\7\tracksdata\e-track-2.xml .\runtime\drivers\inferno\7\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-3.xml copy .\src\drivers\inferno\7\tracksdata\e-track-3.xml .\runtime\drivers\inferno\7\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-4.xml copy .\src\drivers\inferno\7\tracksdata\e-track-4.xml .\runtime\drivers\inferno\7\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-5.xml copy .\src\drivers\inferno\7\tracksdata\e-track-5.xml .\runtime\drivers\inferno\7\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-6.xml copy .\src\drivers\inferno\7\tracksdata\e-track-6.xml .\runtime\drivers\inferno\7\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\7\tracksdata\g-track-1.xml copy .\src\drivers\inferno\7\tracksdata\g-track-1.xml .\runtime\drivers\inferno\7\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\g-track-2.xml copy .\src\drivers\inferno\7\tracksdata\g-track-2.xml .\runtime\drivers\inferno\7\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\michigan.xml copy .\src\drivers\inferno\7\tracksdata\michigan.xml .\runtime\drivers\inferno\7\tracksdata\michigan.xml
if exist .\src\drivers\inferno\7\tracksdata\s2.xml copy .\src\drivers\inferno\7\tracksdata\s2.xml .\runtime\drivers\inferno\7\tracksdata\s2.xml
if exist .\src\drivers\inferno\7\tracksdata\wheel-1.xml copy .\src\drivers\inferno\7\tracksdata\wheel-1.xml .\runtime\drivers\inferno\7\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers\inferno\7
if exist .\src\drivers\inferno\7\defaultcar.xml copy .\src\drivers\inferno\7\defaultcar.xml .\runtime\drivers\inferno\7\defaultcar.xml
if exist .\src\drivers\inferno\7\default.xml copy .\src\drivers\inferno\7\default.xml .\runtime\drivers\inferno\7\default.xml
if exist .\src\drivers\inferno\7\logo.rgb copy .\src\drivers\inferno\7\logo.rgb .\runtime\drivers\inferno\7\logo.rgb
if exist .\src\drivers\inferno\7\lotus-gt1.rgb copy .\src\drivers\inferno\7\lotus-gt1.rgb .\runtime\drivers\inferno\7\lotus-gt1.rgb
if exist .\src\drivers\inferno\7\Makefile copy .\src\drivers\inferno\7\Makefile .\runtime\drivers\inferno\7\Makefile

if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\8
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\8\tracksdata
if exist .\src\drivers\inferno\8\tracksdata\aalborg.xml copy .\src\drivers\inferno\8\tracksdata\aalborg.xml .\runtime\drivers\inferno\8\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\8\tracksdata\alpine-1.xml copy .\src\drivers\inferno\8\tracksdata\alpine-1.xml .\runtime\drivers\inferno\8\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\8\tracksdata\a-speedway.xml copy .\src\drivers\inferno\8\tracksdata\a-speedway.xml .\runtime\drivers\inferno\8\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-1.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-1.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-1.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-2.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-2.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-2.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-3.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-3.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-3.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-4.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-4.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-4.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-5.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-5.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-5.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-6.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-6.xml .\runtime\drivers\inferno\8\tracksdata\car_dirt-6.xml
if exist .\src\drivers\inferno\8\tracksdata\car_g-track-3.xml copy .\src\drivers\inferno\8\tracksdata\car_g-track-3.xml .\runtime\drivers\inferno\8\tracksdata\car_g-track-3.xml
if exist .\src\drivers\inferno\8\tracksdata\car_mixed-1.xml copy .\src\drivers\inferno\8\tracksdata\car_mixed-1.xml .\runtime\drivers\inferno\8\tracksdata\car_mixed-1.xml
if exist .\src\drivers\inferno\8\tracksdata\car_mixed-2.xml copy .\src\drivers\inferno\8\tracksdata\car_mixed-2.xml .\runtime\drivers\inferno\8\tracksdata\car_mixed-2.xml
if exist .\src\drivers\inferno\8\tracksdata\eroad.xml copy .\src\drivers\inferno\8\tracksdata\eroad.xml .\runtime\drivers\inferno\8\tracksdata\eroad.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-1.xml copy .\src\drivers\inferno\8\tracksdata\e-track-1.xml .\runtime\drivers\inferno\8\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-2.xml copy .\src\drivers\inferno\8\tracksdata\e-track-2.xml .\runtime\drivers\inferno\8\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-3.xml copy .\src\drivers\inferno\8\tracksdata\e-track-3.xml .\runtime\drivers\inferno\8\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-4.xml copy .\src\drivers\inferno\8\tracksdata\e-track-4.xml .\runtime\drivers\inferno\8\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-5.xml copy .\src\drivers\inferno\8\tracksdata\e-track-5.xml .\runtime\drivers\inferno\8\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-6.xml copy .\src\drivers\inferno\8\tracksdata\e-track-6.xml .\runtime\drivers\inferno\8\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\8\tracksdata\g-track-1.xml copy .\src\drivers\inferno\8\tracksdata\g-track-1.xml .\runtime\drivers\inferno\8\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\8\tracksdata\g-track-2.xml copy .\src\drivers\inferno\8\tracksdata\g-track-2.xml .\runtime\drivers\inferno\8\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\8\tracksdata\g-track-3.xml copy .\src\drivers\inferno\8\tracksdata\g-track-3.xml .\runtime\drivers\inferno\8\tracksdata\g-track-3.xml
if exist .\src\drivers\inferno\8\tracksdata\michigan.xml copy .\src\drivers\inferno\8\tracksdata\michigan.xml .\runtime\drivers\inferno\8\tracksdata\michigan.xml
if exist .\src\drivers\inferno\8\tracksdata\spring.xml copy .\src\drivers\inferno\8\tracksdata\spring.xml .\runtime\drivers\inferno\8\tracksdata\spring.xml
if exist .\src\drivers\inferno\8\tracksdata\wheel-1.xml copy .\src\drivers\inferno\8\tracksdata\wheel-1.xml .\runtime\drivers\inferno\8\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers\inferno\8
if exist .\src\drivers\inferno\8\defaultcar.xml copy .\src\drivers\inferno\8\defaultcar.xml .\runtime\drivers\inferno\8\defaultcar.xml
if exist .\src\drivers\inferno\8\default.xml copy .\src\drivers\inferno\8\default.xml .\runtime\drivers\inferno\8\default.xml
if exist .\src\drivers\inferno\8\logo.rgb copy .\src\drivers\inferno\8\logo.rgb .\runtime\drivers\inferno\8\logo.rgb
if exist .\src\drivers\inferno\8\Makefile copy .\src\drivers\inferno\8\Makefile .\runtime\drivers\inferno\8\Makefile
if exist .\src\drivers\inferno\8\p406.rgb copy .\src\drivers\inferno\8\p406.rgb .\runtime\drivers\inferno\8\p406.rgb

if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\9
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtime\drivers\inferno\9\tracksdata
if exist .\src\drivers\inferno\9\tracksdata\aalborg.xml copy .\src\drivers\inferno\9\tracksdata\aalborg.xml .\runtime\drivers\inferno\9\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\9\tracksdata\alpine-1.xml copy .\src\drivers\inferno\9\tracksdata\alpine-1.xml .\runtime\drivers\inferno\9\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\9\tracksdata\a-speedway.xml copy .\src\drivers\inferno\9\tracksdata\a-speedway.xml .\runtime\drivers\inferno\9\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\9\tracksdata\car_aalborg.xml .\runtime\drivers\inferno\9\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\9\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\9\tracksdata\car_a-speedway.xml .\runtime\drivers\inferno\9\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\car_eroad.xml copy .\src\drivers\inferno\9\tracksdata\car_eroad.xml .\runtime\drivers\inferno\9\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-1.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-2.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-3.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-4.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-5.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-6.xml .\runtime\drivers\inferno\9\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\9\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\9\tracksdata\car_g-track-1.xml .\runtime\drivers\inferno\9\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\9\tracksdata\car_g-track-2.xml .\runtime\drivers\inferno\9\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\car_michigan.xml copy .\src\drivers\inferno\9\tracksdata\car_michigan.xml .\runtime\drivers\inferno\9\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\9\tracksdata\car_s2.xml copy .\src\drivers\inferno\9\tracksdata\car_s2.xml .\runtime\drivers\inferno\9\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\9\tracksdata\car_test-1.xml copy .\src\drivers\inferno\9\tracksdata\car_test-1.xml .\runtime\drivers\inferno\9\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\9\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\9\tracksdata\car_wheel-1.xml .\runtime\drivers\inferno\9\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\9\tracksdata\city-1.xml copy .\src\drivers\inferno\9\tracksdata\city-1.xml .\runtime\drivers\inferno\9\tracksdata\city-1.xml
if exist .\src\drivers\inferno\9\tracksdata\eroad.xml copy .\src\drivers\inferno\9\tracksdata\eroad.xml .\runtime\drivers\inferno\9\tracksdata\eroad.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-1.xml copy .\src\drivers\inferno\9\tracksdata\e-track-1.xml .\runtime\drivers\inferno\9\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-2.xml copy .\src\drivers\inferno\9\tracksdata\e-track-2.xml .\runtime\drivers\inferno\9\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-3.xml copy .\src\drivers\inferno\9\tracksdata\e-track-3.xml .\runtime\drivers\inferno\9\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-4.xml copy .\src\drivers\inferno\9\tracksdata\e-track-4.xml .\runtime\drivers\inferno\9\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-5.xml copy .\src\drivers\inferno\9\tracksdata\e-track-5.xml .\runtime\drivers\inferno\9\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-6.xml copy .\src\drivers\inferno\9\tracksdata\e-track-6.xml .\runtime\drivers\inferno\9\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\9\tracksdata\g-track-1.xml copy .\src\drivers\inferno\9\tracksdata\g-track-1.xml .\runtime\drivers\inferno\9\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\g-track-2.xml copy .\src\drivers\inferno\9\tracksdata\g-track-2.xml .\runtime\drivers\inferno\9\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\michigan.xml copy .\src\drivers\inferno\9\tracksdata\michigan.xml .\runtime\drivers\inferno\9\tracksdata\michigan.xml
if exist .\src\drivers\inferno\9\tracksdata\s2.xml copy .\src\drivers\inferno\9\tracksdata\s2.xml .\runtime\drivers\inferno\9\tracksdata\s2.xml
if exist .\src\drivers\inferno\9\tracksdata\wheel-1.xml copy .\src\drivers\inferno\9\tracksdata\wheel-1.xml .\runtime\drivers\inferno\9\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers\inferno\9
if exist .\src\drivers\inferno\9\defaultcar.xml copy .\src\drivers\inferno\9\defaultcar.xml .\runtime\drivers\inferno\9\defaultcar.xml
if exist .\src\drivers\inferno\9\default.xml copy .\src\drivers\inferno\9\default.xml .\runtime\drivers\inferno\9\default.xml
if exist .\src\drivers\inferno\9\logo.rgb copy .\src\drivers\inferno\9\logo.rgb .\runtime\drivers\inferno\9\logo.rgb
if exist .\src\drivers\inferno\9\Makefile copy .\src\drivers\inferno\9\Makefile .\runtime\drivers\inferno\9\Makefile
if exist .\src\drivers\inferno\9\vm-x2.rgb copy .\src\drivers\inferno\9\vm-x2.rgb .\runtime\drivers\inferno\9\vm-x2.rgb

if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\inferno.xml copy .\src\drivers\inferno\inferno.xml .\runtime\drivers\inferno\inferno.xml
if exist .\src\drivers\inferno\car1.xml copy .\src\drivers\inferno\car1.xml .\runtime\drivers\inferno\car1.xml
if exist .\src\drivers\inferno\logo.rgb copy .\src\drivers\inferno\logo.rgb .\runtime\drivers\inferno\logo.rgb
if exist .\src\drivers\inferno\mclaren-f1.rgb copy .\src\drivers\inferno\mclaren-f1.rgb .\runtime\drivers\inferno\mclaren-f1.rgb

if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\inferno2.xml copy .\src\drivers\inferno2\inferno2.xml .\runtime\drivers\inferno2\inferno2.xml
if exist .\src\drivers\inferno2\car1.xml copy .\src\drivers\inferno2\car1.xml .\runtime\drivers\inferno2\car1.xml
if exist .\src\drivers\inferno2\logo.rgb copy .\src\drivers\inferno2\logo.rgb .\runtime\drivers\inferno2\logo.rgb

if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtime\drivers\K1999
if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtime\drivers\K1999\1
if exist .\src\drivers\K1999\1\buggy.rgb copy .\src\drivers\K1999\1\buggy.rgb .\runtime\drivers\K1999\1\buggy.rgb
if exist .\src\drivers\K1999\1\settings.xml copy .\src\drivers\K1999\1\settings.xml .\runtime\drivers\K1999\1\settings.xml

if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtime\drivers\K1999
if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtime\drivers\K1999\2
if exist .\src\drivers\K1999\2\cg-nascar-rwd.rgb copy .\src\drivers\K1999\2\cg-nascar-rwd.rgb .\runtime\drivers\K1999\2\cg-nascar-rwd.rgb
if exist .\src\drivers\K1999\2\settings.xml copy .\src\drivers\K1999\2\settings.xml .\runtime\drivers\K1999\2\settings.xml

if exist .\src\drivers\K1999\*.* call .\create_dir .\runtime
if exist .\src\drivers\K1999\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\K1999\*.* call .\create_dir .\runtime\drivers\K1999
if exist .\src\drivers\K1999\K1999.xml copy .\src\drivers\K1999\K1999.xml .\runtime\drivers\K1999\K1999.xml
if exist .\src\drivers\K1999\logo.rgb copy .\src\drivers\K1999\logo.rgb .\runtime\drivers\K1999\logo.rgb

if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtime\drivers\lliaw\tracksdata
if exist .\src\drivers\lliaw\tracksdata\car_e-track-3.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-3.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-3.xml
if exist .\src\drivers\lliaw\tracksdata\car_e-track-4.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-4.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-4.xml
if exist .\src\drivers\lliaw\tracksdata\car_e-track-6.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-6.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-6.xml
if exist .\src\drivers\lliaw\tracksdata\car_eroad.xml copy .\src\drivers\lliaw\tracksdata\car_eroad.xml .\runtime\drivers\lliaw\tracksdata\car_eroad.xml
if exist .\src\drivers\lliaw\tracksdata\car_g-track-3.xml copy .\src\drivers\lliaw\tracksdata\car_g-track-3.xml .\runtime\drivers\lliaw\tracksdata\car_g-track-3.xml

if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\lliaw.xml copy .\src\drivers\lliaw\lliaw.xml .\runtime\drivers\lliaw\lliaw.xml
if exist .\src\drivers\lliaw\car.xml copy .\src\drivers\lliaw\car.xml .\runtime\drivers\lliaw\car.xml
if exist .\src\drivers\lliaw\viper-gts-r.rgb copy .\src\drivers\lliaw\viper-gts-r.rgb .\runtime\drivers\lliaw\viper-gts-r.rgb
if exist .\src\drivers\lliaw\logo.rgb copy .\src\drivers\lliaw\logo.rgb .\runtime\drivers\lliaw\logo.rgb

if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtime
if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtime\drivers\sparkle
if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtime\drivers\sparkle\0
if exist .\src\drivers\sparkle\0\baja-bug.rgb copy .\src\drivers\sparkle\0\baja-bug.rgb .\runtime\drivers\sparkle\0\baja-bug.rgb
if exist .\src\drivers\sparkle\0\default.xml copy .\src\drivers\sparkle\0\default.xml .\runtime\drivers\sparkle\0\default.xml

if exist .\src\drivers\sparkle\*.* call .\create_dir .\runtime
if exist .\src\drivers\sparkle\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\sparkle\*.* call .\create_dir .\runtime\drivers\sparkle
if exist .\src\drivers\sparkle\sparkle.xml copy .\src\drivers\sparkle\sparkle.xml .\runtime\drivers\sparkle\sparkle.xml
if exist .\src\drivers\sparkle\logo.rgb copy .\src\drivers\sparkle\logo.rgb .\runtime\drivers\sparkle\logo.rgb

if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtime\drivers\tanhoj
if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtime\drivers\tanhoj\tracksdata
if exist .\src\drivers\tanhoj\tracksdata\aalborg.xml copy .\src\drivers\tanhoj\tracksdata\aalborg.xml .\runtime\drivers\tanhoj\tracksdata\aalborg.xml
if exist .\src\drivers\tanhoj\tracksdata\a-speedway.xml copy .\src\drivers\tanhoj\tracksdata\a-speedway.xml .\runtime\drivers\tanhoj\tracksdata\a-speedway.xml
if exist .\src\drivers\tanhoj\tracksdata\car_aalborg.xml copy .\src\drivers\tanhoj\tracksdata\car_aalborg.xml .\runtime\drivers\tanhoj\tracksdata\car_aalborg.xml
if exist .\src\drivers\tanhoj\tracksdata\car_a-speedway.xml copy .\src\drivers\tanhoj\tracksdata\car_a-speedway.xml .\runtime\drivers\tanhoj\tracksdata\car_a-speedway.xml
if exist .\src\drivers\tanhoj\tracksdata\car_eroad.xml copy .\src\drivers\tanhoj\tracksdata\car_eroad.xml .\runtime\drivers\tanhoj\tracksdata\car_eroad.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-1.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-1.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-2.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-2.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-2.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-3.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-3.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-4.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-4.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-4.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-5.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-5.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-5.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-6.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-6.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-6.xml
if exist .\src\drivers\tanhoj\tracksdata\car_g-track-1.xml copy .\src\drivers\tanhoj\tracksdata\car_g-track-1.xml .\runtime\drivers\tanhoj\tracksdata\car_g-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\car_g-track-3.xml copy .\src\drivers\tanhoj\tracksdata\car_g-track-3.xml .\runtime\drivers\tanhoj\tracksdata\car_g-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\car_michigan.xml copy .\src\drivers\tanhoj\tracksdata\car_michigan.xml .\runtime\drivers\tanhoj\tracksdata\car_michigan.xml
if exist .\src\drivers\tanhoj\tracksdata\car_s2.xml copy .\src\drivers\tanhoj\tracksdata\car_s2.xml .\runtime\drivers\tanhoj\tracksdata\car_s2.xml
if exist .\src\drivers\tanhoj\tracksdata\car_test-1.xml copy .\src\drivers\tanhoj\tracksdata\car_test-1.xml .\runtime\drivers\tanhoj\tracksdata\car_test-1.xml
if exist .\src\drivers\tanhoj\tracksdata\car_wheel-1.xml copy .\src\drivers\tanhoj\tracksdata\car_wheel-1.xml .\runtime\drivers\tanhoj\tracksdata\car_wheel-1.xml
if exist .\src\drivers\tanhoj\tracksdata\city-1.xml copy .\src\drivers\tanhoj\tracksdata\city-1.xml .\runtime\drivers\tanhoj\tracksdata\city-1.xml
if exist .\src\drivers\tanhoj\tracksdata\dirt-2.xml copy .\src\drivers\tanhoj\tracksdata\dirt-2.xml .\runtime\drivers\tanhoj\tracksdata\dirt-2.xml
if exist .\src\drivers\tanhoj\tracksdata\eroad.xml copy .\src\drivers\tanhoj\tracksdata\eroad.xml .\runtime\drivers\tanhoj\tracksdata\eroad.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-1.xml copy .\src\drivers\tanhoj\tracksdata\e-track-1.xml .\runtime\drivers\tanhoj\tracksdata\e-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-2.xml copy .\src\drivers\tanhoj\tracksdata\e-track-2.xml .\runtime\drivers\tanhoj\tracksdata\e-track-2.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-3.xml copy .\src\drivers\tanhoj\tracksdata\e-track-3.xml .\runtime\drivers\tanhoj\tracksdata\e-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-4.xml copy .\src\drivers\tanhoj\tracksdata\e-track-4.xml .\runtime\drivers\tanhoj\tracksdata\e-track-4.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-5.xml copy .\src\drivers\tanhoj\tracksdata\e-track-5.xml .\runtime\drivers\tanhoj\tracksdata\e-track-5.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-6.xml copy .\src\drivers\tanhoj\tracksdata\e-track-6.xml .\runtime\drivers\tanhoj\tracksdata\e-track-6.xml
if exist .\src\drivers\tanhoj\tracksdata\g-track-1.xml copy .\src\drivers\tanhoj\tracksdata\g-track-1.xml .\runtime\drivers\tanhoj\tracksdata\g-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\g-track-3.xml copy .\src\drivers\tanhoj\tracksdata\g-track-3.xml .\runtime\drivers\tanhoj\tracksdata\g-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\michigan.xml copy .\src\drivers\tanhoj\tracksdata\michigan.xml .\runtime\drivers\tanhoj\tracksdata\michigan.xml
if exist .\src\drivers\tanhoj\tracksdata\s2.xml copy .\src\drivers\tanhoj\tracksdata\s2.xml .\runtime\drivers\tanhoj\tracksdata\s2.xml
if exist .\src\drivers\tanhoj\tracksdata\wheel-1.xml copy .\src\drivers\tanhoj\tracksdata\wheel-1.xml .\runtime\drivers\tanhoj\tracksdata\wheel-1.xml

if exist .\src\drivers\tanhoj\*.* call .\create_dir .\runtime
if exist .\src\drivers\tanhoj\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tanhoj\*.* call .\create_dir .\runtime\drivers\tanhoj
if exist .\src\drivers\tanhoj\tanhoj.xml copy .\src\drivers\tanhoj\tanhoj.xml .\runtime\drivers\tanhoj\tanhoj.xml
if exist .\src\drivers\tanhoj\car1.xml copy .\src\drivers\tanhoj\car1.xml .\runtime\drivers\tanhoj\car1.xml
if exist .\src\drivers\tanhoj\logo.rgb copy .\src\drivers\tanhoj\logo.rgb .\runtime\drivers\tanhoj\logo.rgb
if exist .\src\drivers\tanhoj\cg-nascar-rwd.rgb copy .\src\drivers\tanhoj\cg-nascar-rwd.rgb .\runtime\drivers\tanhoj\cg-nascar-rwd.rgb

if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtime\drivers\tita\tracksdata
if exist .\src\drivers\tita\tracksdata\aalborg.xml copy .\src\drivers\tita\tracksdata\aalborg.xml .\runtime\drivers\tita\tracksdata\aalborg.xml
if exist .\src\drivers\tita\tracksdata\a-speedway.xml copy .\src\drivers\tita\tracksdata\a-speedway.xml .\runtime\drivers\tita\tracksdata\a-speedway.xml
if exist .\src\drivers\tita\tracksdata\car_aalborg.xml copy .\src\drivers\tita\tracksdata\car_aalborg.xml .\runtime\drivers\tita\tracksdata\car_aalborg.xml
if exist .\src\drivers\tita\tracksdata\car_a-speedway.xml copy .\src\drivers\tita\tracksdata\car_a-speedway.xml .\runtime\drivers\tita\tracksdata\car_a-speedway.xml
if exist .\src\drivers\tita\tracksdata\car_eroad.xml copy .\src\drivers\tita\tracksdata\car_eroad.xml .\runtime\drivers\tita\tracksdata\car_eroad.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-1.xml copy .\src\drivers\tita\tracksdata\car_e-track-1.xml .\runtime\drivers\tita\tracksdata\car_e-track-1.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-2.xml copy .\src\drivers\tita\tracksdata\car_e-track-2.xml .\runtime\drivers\tita\tracksdata\car_e-track-2.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-3.xml copy .\src\drivers\tita\tracksdata\car_e-track-3.xml .\runtime\drivers\tita\tracksdata\car_e-track-3.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-4.xml copy .\src\drivers\tita\tracksdata\car_e-track-4.xml .\runtime\drivers\tita\tracksdata\car_e-track-4.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-5.xml copy .\src\drivers\tita\tracksdata\car_e-track-5.xml .\runtime\drivers\tita\tracksdata\car_e-track-5.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-6.xml copy .\src\drivers\tita\tracksdata\car_e-track-6.xml .\runtime\drivers\tita\tracksdata\car_e-track-6.xml
if exist .\src\drivers\tita\tracksdata\car_g-track-1.xml copy .\src\drivers\tita\tracksdata\car_g-track-1.xml .\runtime\drivers\tita\tracksdata\car_g-track-1.xml
if exist .\src\drivers\tita\tracksdata\car_g-track-3.xml copy .\src\drivers\tita\tracksdata\car_g-track-3.xml .\runtime\drivers\tita\tracksdata\car_g-track-3.xml
if exist .\src\drivers\tita\tracksdata\car_michigan.xml copy .\src\drivers\tita\tracksdata\car_michigan.xml .\runtime\drivers\tita\tracksdata\car_michigan.xml
if exist .\src\drivers\tita\tracksdata\car_s2.xml copy .\src\drivers\tita\tracksdata\car_s2.xml .\runtime\drivers\tita\tracksdata\car_s2.xml
if exist .\src\drivers\tita\tracksdata\car_test-1.xml copy .\src\drivers\tita\tracksdata\car_test-1.xml .\runtime\drivers\tita\tracksdata\car_test-1.xml
if exist .\src\drivers\tita\tracksdata\car_wheel-1.xml copy .\src\drivers\tita\tracksdata\car_wheel-1.xml .\runtime\drivers\tita\tracksdata\car_wheel-1.xml
if exist .\src\drivers\tita\tracksdata\city-1.xml copy .\src\drivers\tita\tracksdata\city-1.xml .\runtime\drivers\tita\tracksdata\city-1.xml
if exist .\src\drivers\tita\tracksdata\eroad.xml copy .\src\drivers\tita\tracksdata\eroad.xml .\runtime\drivers\tita\tracksdata\eroad.xml
if exist .\src\drivers\tita\tracksdata\e-track-1.xml copy .\src\drivers\tita\tracksdata\e-track-1.xml .\runtime\drivers\tita\tracksdata\e-track-1.xml
if exist .\src\drivers\tita\tracksdata\e-track-2.xml copy .\src\drivers\tita\tracksdata\e-track-2.xml .\runtime\drivers\tita\tracksdata\e-track-2.xml
if exist .\src\drivers\tita\tracksdata\e-track-3.xml copy .\src\drivers\tita\tracksdata\e-track-3.xml .\runtime\drivers\tita\tracksdata\e-track-3.xml
if exist .\src\drivers\tita\tracksdata\e-track-4.xml copy .\src\drivers\tita\tracksdata\e-track-4.xml .\runtime\drivers\tita\tracksdata\e-track-4.xml
if exist .\src\drivers\tita\tracksdata\e-track-5.xml copy .\src\drivers\tita\tracksdata\e-track-5.xml .\runtime\drivers\tita\tracksdata\e-track-5.xml
if exist .\src\drivers\tita\tracksdata\e-track-6.xml copy .\src\drivers\tita\tracksdata\e-track-6.xml .\runtime\drivers\tita\tracksdata\e-track-6.xml
if exist .\src\drivers\tita\tracksdata\g-track-1.xml copy .\src\drivers\tita\tracksdata\g-track-1.xml .\runtime\drivers\tita\tracksdata\g-track-1.xml
if exist .\src\drivers\tita\tracksdata\g-track-3.xml copy .\src\drivers\tita\tracksdata\g-track-3.xml .\runtime\drivers\tita\tracksdata\g-track-3.xml
if exist .\src\drivers\tita\tracksdata\michigan.xml copy .\src\drivers\tita\tracksdata\michigan.xml .\runtime\drivers\tita\tracksdata\michigan.xml
if exist .\src\drivers\tita\tracksdata\s2.xml copy .\src\drivers\tita\tracksdata\s2.xml .\runtime\drivers\tita\tracksdata\s2.xml
if exist .\src\drivers\tita\tracksdata\wheel-1.xml copy .\src\drivers\tita\tracksdata\wheel-1.xml .\runtime\drivers\tita\tracksdata\wheel-1.xml

if exist .\src\drivers\tita\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\tita.xml copy .\src\drivers\tita\tita.xml .\runtime\drivers\tita\tita.xml
if exist .\src\drivers\tita\car.xml copy .\src\drivers\tita\car.xml .\runtime\drivers\tita\car.xml
if exist .\src\drivers\tita\logo.rgb copy .\src\drivers\tita\logo.rgb .\runtime\drivers\tita\logo.rgb
if exist .\src\drivers\tita\lotus-gt1.rgb copy .\src\drivers\tita\lotus-gt1.rgb .\runtime\drivers\tita\lotus-gt1.rgb

if exist .\src\drivers\tutorial1\*.* call .\create_dir .\runtime
if exist .\src\drivers\tutorial1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tutorial1\*.* call .\create_dir .\runtime\drivers\tutorial1
if exist .\src\drivers\tutorial1\tutorial1.xml copy .\src\drivers\tutorial1\tutorial1.xml .\runtime\drivers\tutorial1\tutorial1.xml

if exist .\src\drivers\tutorial2\*.* call .\create_dir .\runtime
if exist .\src\drivers\tutorial2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tutorial2\*.* call .\create_dir .\runtime\drivers\tutorial2
if exist .\src\drivers\tutorial2\tutorial2.xml copy .\src\drivers\tutorial2\tutorial2.xml .\runtime\drivers\tutorial2\tutorial2.xml

if exist .\src\libs\raceengineclient\*.* call .\create_dir .\runtime
if exist .\src\libs\raceengineclient\*.* call .\create_dir .\runtime\config
if exist .\src\libs\raceengineclient\raceengine.xml copy .\src\libs\raceengineclient\raceengine.xml .\runtime\config\raceengine.xml

if exist .\src\libs\tgf\*.* call .\create_dir .\runtime
if exist .\src\libs\tgf\*.* call .\create_dir .\runtime\config
if exist .\src\libs\tgf\params.dtd copy .\src\libs\tgf\params.dtd .\runtime\config\params.dtd

if exist .\src\libs\tgfclient\*.* call .\create_dir .\runtime
if exist .\src\libs\tgfclient\*.* call .\create_dir .\runtime\config
if exist .\src\libs\tgfclient\screen.xml copy .\src\libs\tgfclient\screen.xml .\runtime\config\screen.xml

if exist .\src\modules\graphic\ssggraph\*.* call .\create_dir .\runtime
if exist .\src\modules\graphic\ssggraph\*.* call .\create_dir .\runtime\config
if exist .\src\modules\graphic\ssggraph\graph.xml copy .\src\modules\graphic\ssggraph\graph.xml .\runtime\config\graph.xml

if exist .\src\modules\telemetry\*.* call .\create_dir .\runtime
if exist .\src\modules\telemetry\*.* call .\create_dir .\runtime\telemetry
if exist .\src\modules\telemetry\telemetry.sh copy .\src\modules\telemetry\telemetry.sh .\runtime\telemetry\telemetry.sh

if exist .\src\raceman\*.* call .\create_dir .\runtime
if exist .\src\raceman\*.* call .\create_dir .\runtime\config
if exist .\src\raceman\*.* call .\create_dir .\runtime\config\raceman
if exist .\src\raceman\champ.xml copy .\src\raceman\champ.xml .\runtime\config\raceman\champ.xml
if exist .\src\raceman\dtmrace.xml copy .\src\raceman\dtmrace.xml .\runtime\config\raceman\dtmrace.xml
if exist .\src\raceman\endrace.xml copy .\src\raceman\endrace.xml .\runtime\config\raceman\endrace.xml
if exist .\src\raceman\ncrace.xml copy .\src\raceman\ncrace.xml .\runtime\config\raceman\ncrace.xml
if exist .\src\raceman\practice.xml copy .\src\raceman\practice.xml .\runtime\config\raceman\practice.xml
if exist .\src\raceman\quickrace.xml copy .\src\raceman\quickrace.xml .\runtime\config\raceman\quickrace.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\champ

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\dtmrace

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\endrace

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\ncrace

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\practice

call .\create_dir .\runtime
call .\create_dir .\runtime\results
call .\create_dir .\runtime\results\quickrace

if exist .\*.* call .\create_dir .\runtime
if exist .\*.* call .\create_dir .\runtime\.
if exist .\setup_linux.sh copy .\setup_linux.sh .\runtime\.\setup_linux.sh

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\astigot

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\berniw

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\berniw2

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\cylos1

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\cylos2

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\inferno

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\inferno2

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\K1999

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\lliaw

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\sparkle

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tanhoj

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tita

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tutorial1

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tutorial2

call .\create_dir .\runtime
call .\create_dir .\runtime\.

call .\create_dir .\runtime
call .\create_dir .\runtime\.

call .\create_dir .\runtime
call .\create_dir .\runtime\.

call .\create_dir .\runtime
call .\create_dir .\runtime\.

call .\create_dir .\runtime
call .\create_dir .\runtime\.

call .\create_dir .\runtime
call .\create_dir .\runtime\.

call .\create_dir .\runtime
call .\create_dir .\runtime\.

call .\create_dir .\runtime
call .\create_dir .\runtime\.

call .\create_dir .\runtime
call .\create_dir .\runtime\modules
call .\create_dir .\runtime\modules\graphic

call .\create_dir .\runtime
call .\create_dir .\runtime\modules
call .\create_dir .\runtime\modules\simu

call .\create_dir .\runtime
call .\create_dir .\runtime\modules
call .\create_dir .\runtime\modules\telemetry

call .\create_dir .\runtime
call .\create_dir .\runtime\modules
call .\create_dir .\runtime\modules\track
