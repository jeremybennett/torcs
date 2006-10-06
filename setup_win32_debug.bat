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
if exist .\src\libs\tgfclient\glfeatures.h copy .\src\libs\tgfclient\glfeatures.h .\export\include\glfeatures.h

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
if exist .\src\libs\confscreens\soundconfig.h copy .\src\libs\confscreens\soundconfig.h .\export\include\soundconfig.h
if exist .\src\libs\confscreens\simuconfig.h copy .\src\libs\confscreens\simuconfig.h .\export\include\simuconfig.h
if exist .\src\libs\confscreens\openglconfig.h copy .\src\libs\confscreens\openglconfig.h .\export\include\openglconfig.h

if exist .\src\libs\racescreens\*.* call .\create_dir .\export
if exist .\src\libs\racescreens\*.* call .\create_dir .\export\include
if exist .\src\libs\racescreens\racescreens.h copy .\src\libs\racescreens\racescreens.h .\export\include\racescreens.h

if exist .\src\libs\robottools\*.* call .\create_dir .\export
if exist .\src\libs\robottools\*.* call .\create_dir .\export\include
if exist .\src\libs\robottools\robottools.h copy .\src\libs\robottools\robottools.h .\export\include\robottools.h

if exist .\src\libs\raceengineclient\*.* call .\create_dir .\export
if exist .\src\libs\raceengineclient\*.* call .\create_dir .\export\include
if exist .\src\libs\raceengineclient\singleplayer.h copy .\src\libs\raceengineclient\singleplayer.h .\export\include\singleplayer.h
if exist .\src\libs\raceengineclient\raceinit.h copy .\src\libs\raceengineclient\raceinit.h .\export\include\raceinit.h

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

if exist .\src\libs\math\*.* call .\create_dir .\export
if exist .\src\libs\math\*.* call .\create_dir .\export\include
if exist .\src\libs\math\*.* call .\create_dir .\export\include\tmath
if exist .\src\libs\math\linalg_t.h copy .\src\libs\math\linalg_t.h .\export\include\tmath\linalg_t.h
if exist .\src\libs\math\straight2_t.h copy .\src\libs\math\straight2_t.h .\export\include\tmath\straight2_t.h
if exist .\src\libs\math\v4_t.h copy .\src\libs\math\v4_t.h .\export\include\tmath\v4_t.h
if exist .\src\libs\math\v3_t.h copy .\src\libs\math\v3_t.h .\export\include\tmath\v3_t.h
if exist .\src\libs\math\v2_t.h copy .\src\libs\math\v2_t.h .\export\include\tmath\v2_t.h

if exist .\src\libs\learning\*.* call .\create_dir .\export
if exist .\src\libs\learning\*.* call .\create_dir .\export\include
if exist .\src\libs\learning\*.* call .\create_dir .\export\include\learning
if exist .\src\libs\learning\policy.h copy .\src\libs\learning\policy.h .\export\include\learning\policy.h
if exist .\src\libs\learning\ann_policy.h copy .\src\libs\learning\ann_policy.h .\export\include\learning\ann_policy.h
if exist .\src\libs\learning\ANN.h copy .\src\libs\learning\ANN.h .\export\include\learning\ANN.h
if exist .\src\libs\learning\learn_debug.h copy .\src\libs\learning\learn_debug.h .\export\include\learning\learn_debug.h
if exist .\src\libs\learning\real.h copy .\src\libs\learning\real.h .\export\include\learning\real.h
if exist .\src\libs\learning\string_utils.h copy .\src\libs\learning\string_utils.h .\export\include\learning\string_utils.h
if exist .\src\libs\learning\List.h copy .\src\libs\learning\List.h .\export\include\learning\List.h
if exist .\src\libs\learning\MathFunctions.h copy .\src\libs\learning\MathFunctions.h .\export\include\learning\MathFunctions.h
if exist .\src\libs\learning\Distribution.h copy .\src\libs\learning\Distribution.h .\export\include\learning\Distribution.h
rem if exist .\src\libs\learning\SmartAssert.h copy .\src\libs\learning\SmartAssert.h .\export\include\learning\SmartAssert.h

if exist .\src\libs\portability\*.* call .\create_dir .\export
if exist .\src\libs\portability\*.* call .\create_dir .\export\include
if exist .\src\libs\portability\portability.h copy .\src\libs\portability\portability.h .\export\include\portability.h

if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtimed\drivers\berniw\1
if exist .\src\drivers\berniw\1\cg-nascar-rwd.rgb copy .\src\drivers\berniw\1\cg-nascar-rwd.rgb .\runtimed\drivers\berniw\1\cg-nascar-rwd.rgb
if exist .\src\drivers\berniw\1\aalborg.xml copy .\src\drivers\berniw\1\aalborg.xml .\runtimed\drivers\berniw\1\aalborg.xml
if exist .\src\drivers\berniw\1\alpine-1.xml copy .\src\drivers\berniw\1\alpine-1.xml .\runtimed\drivers\berniw\1\alpine-1.xml
if exist .\src\drivers\berniw\1\a-speedway.xml copy .\src\drivers\berniw\1\a-speedway.xml .\runtimed\drivers\berniw\1\a-speedway.xml
if exist .\src\drivers\berniw\1\default.xml copy .\src\drivers\berniw\1\default.xml .\runtimed\drivers\berniw\1\default.xml
if exist .\src\drivers\berniw\1\dirt-1.xml copy .\src\drivers\berniw\1\dirt-1.xml .\runtimed\drivers\berniw\1\dirt-1.xml
if exist .\src\drivers\berniw\1\dirt-2.xml copy .\src\drivers\berniw\1\dirt-2.xml .\runtimed\drivers\berniw\1\dirt-2.xml
if exist .\src\drivers\berniw\1\dirt-3.xml copy .\src\drivers\berniw\1\dirt-3.xml .\runtimed\drivers\berniw\1\dirt-3.xml
if exist .\src\drivers\berniw\1\dirt-4.xml copy .\src\drivers\berniw\1\dirt-4.xml .\runtimed\drivers\berniw\1\dirt-4.xml
if exist .\src\drivers\berniw\1\dirt-5.xml copy .\src\drivers\berniw\1\dirt-5.xml .\runtimed\drivers\berniw\1\dirt-5.xml
if exist .\src\drivers\berniw\1\dirt-6.xml copy .\src\drivers\berniw\1\dirt-6.xml .\runtimed\drivers\berniw\1\dirt-6.xml
if exist .\src\drivers\berniw\1\eroad.xml copy .\src\drivers\berniw\1\eroad.xml .\runtimed\drivers\berniw\1\eroad.xml
if exist .\src\drivers\berniw\1\e-track-1.xml copy .\src\drivers\berniw\1\e-track-1.xml .\runtimed\drivers\berniw\1\e-track-1.xml
if exist .\src\drivers\berniw\1\e-track-2.xml copy .\src\drivers\berniw\1\e-track-2.xml .\runtimed\drivers\berniw\1\e-track-2.xml
if exist .\src\drivers\berniw\1\e-track-3.xml copy .\src\drivers\berniw\1\e-track-3.xml .\runtimed\drivers\berniw\1\e-track-3.xml
if exist .\src\drivers\berniw\1\e-track-4.xml copy .\src\drivers\berniw\1\e-track-4.xml .\runtimed\drivers\berniw\1\e-track-4.xml
if exist .\src\drivers\berniw\1\e-track-5.xml copy .\src\drivers\berniw\1\e-track-5.xml .\runtimed\drivers\berniw\1\e-track-5.xml
if exist .\src\drivers\berniw\1\e-track-6.xml copy .\src\drivers\berniw\1\e-track-6.xml .\runtimed\drivers\berniw\1\e-track-6.xml
if exist .\src\drivers\berniw\1\g-track-1.xml copy .\src\drivers\berniw\1\g-track-1.xml .\runtimed\drivers\berniw\1\g-track-1.xml
if exist .\src\drivers\berniw\1\g-track-2.xml copy .\src\drivers\berniw\1\g-track-2.xml .\runtimed\drivers\berniw\1\g-track-2.xml
if exist .\src\drivers\berniw\1\g-track-3.xml copy .\src\drivers\berniw\1\g-track-3.xml .\runtimed\drivers\berniw\1\g-track-3.xml
if exist .\src\drivers\berniw\1\michigan.xml copy .\src\drivers\berniw\1\michigan.xml .\runtimed\drivers\berniw\1\michigan.xml
if exist .\src\drivers\berniw\1\mixed-1.xml copy .\src\drivers\berniw\1\mixed-1.xml .\runtimed\drivers\berniw\1\mixed-1.xml
if exist .\src\drivers\berniw\1\mixed-2.xml copy .\src\drivers\berniw\1\mixed-2.xml .\runtimed\drivers\berniw\1\mixed-2.xml
if exist .\src\drivers\berniw\1\spring.xml copy .\src\drivers\berniw\1\spring.xml .\runtimed\drivers\berniw\1\spring.xml
if exist .\src\drivers\berniw\1\wheel-1.xml copy .\src\drivers\berniw\1\wheel-1.xml .\runtimed\drivers\berniw\1\wheel-1.xml

if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtimed\drivers\berniw\10
if exist .\src\drivers\berniw\10\buggy.rgb copy .\src\drivers\berniw\10\buggy.rgb .\runtimed\drivers\berniw\10\buggy.rgb
if exist .\src\drivers\berniw\10\aalborg.xml copy .\src\drivers\berniw\10\aalborg.xml .\runtimed\drivers\berniw\10\aalborg.xml
if exist .\src\drivers\berniw\10\alpine-1.xml copy .\src\drivers\berniw\10\alpine-1.xml .\runtimed\drivers\berniw\10\alpine-1.xml
if exist .\src\drivers\berniw\10\a-speedway.xml copy .\src\drivers\berniw\10\a-speedway.xml .\runtimed\drivers\berniw\10\a-speedway.xml
if exist .\src\drivers\berniw\10\default.xml copy .\src\drivers\berniw\10\default.xml .\runtimed\drivers\berniw\10\default.xml
if exist .\src\drivers\berniw\10\dirt-1.xml copy .\src\drivers\berniw\10\dirt-1.xml .\runtimed\drivers\berniw\10\dirt-1.xml
if exist .\src\drivers\berniw\10\dirt-2.xml copy .\src\drivers\berniw\10\dirt-2.xml .\runtimed\drivers\berniw\10\dirt-2.xml
if exist .\src\drivers\berniw\10\dirt-3.xml copy .\src\drivers\berniw\10\dirt-3.xml .\runtimed\drivers\berniw\10\dirt-3.xml
if exist .\src\drivers\berniw\10\dirt-4.xml copy .\src\drivers\berniw\10\dirt-4.xml .\runtimed\drivers\berniw\10\dirt-4.xml
if exist .\src\drivers\berniw\10\dirt-5.xml copy .\src\drivers\berniw\10\dirt-5.xml .\runtimed\drivers\berniw\10\dirt-5.xml
if exist .\src\drivers\berniw\10\dirt-6.xml copy .\src\drivers\berniw\10\dirt-6.xml .\runtimed\drivers\berniw\10\dirt-6.xml
if exist .\src\drivers\berniw\10\eroad.xml copy .\src\drivers\berniw\10\eroad.xml .\runtimed\drivers\berniw\10\eroad.xml
if exist .\src\drivers\berniw\10\e-track-1.xml copy .\src\drivers\berniw\10\e-track-1.xml .\runtimed\drivers\berniw\10\e-track-1.xml
if exist .\src\drivers\berniw\10\e-track-2.xml copy .\src\drivers\berniw\10\e-track-2.xml .\runtimed\drivers\berniw\10\e-track-2.xml
if exist .\src\drivers\berniw\10\e-track-3.xml copy .\src\drivers\berniw\10\e-track-3.xml .\runtimed\drivers\berniw\10\e-track-3.xml
if exist .\src\drivers\berniw\10\e-track-4.xml copy .\src\drivers\berniw\10\e-track-4.xml .\runtimed\drivers\berniw\10\e-track-4.xml
if exist .\src\drivers\berniw\10\e-track-5.xml copy .\src\drivers\berniw\10\e-track-5.xml .\runtimed\drivers\berniw\10\e-track-5.xml
if exist .\src\drivers\berniw\10\e-track-6.xml copy .\src\drivers\berniw\10\e-track-6.xml .\runtimed\drivers\berniw\10\e-track-6.xml
if exist .\src\drivers\berniw\10\g-track-1.xml copy .\src\drivers\berniw\10\g-track-1.xml .\runtimed\drivers\berniw\10\g-track-1.xml
if exist .\src\drivers\berniw\10\g-track-2.xml copy .\src\drivers\berniw\10\g-track-2.xml .\runtimed\drivers\berniw\10\g-track-2.xml
if exist .\src\drivers\berniw\10\g-track-3.xml copy .\src\drivers\berniw\10\g-track-3.xml .\runtimed\drivers\berniw\10\g-track-3.xml
if exist .\src\drivers\berniw\10\michigan.xml copy .\src\drivers\berniw\10\michigan.xml .\runtimed\drivers\berniw\10\michigan.xml
if exist .\src\drivers\berniw\10\mixed-1.xml copy .\src\drivers\berniw\10\mixed-1.xml .\runtimed\drivers\berniw\10\mixed-1.xml
if exist .\src\drivers\berniw\10\mixed-2.xml copy .\src\drivers\berniw\10\mixed-2.xml .\runtimed\drivers\berniw\10\mixed-2.xml
if exist .\src\drivers\berniw\10\spring.xml copy .\src\drivers\berniw\10\spring.xml .\runtimed\drivers\berniw\10\spring.xml
if exist .\src\drivers\berniw\10\wheel-1.xml copy .\src\drivers\berniw\10\wheel-1.xml .\runtimed\drivers\berniw\10\wheel-1.xml

if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtimed\drivers\berniw\2
if exist .\src\drivers\berniw\2\cg-nascar-rwd.rgb copy .\src\drivers\berniw\2\cg-nascar-rwd.rgb .\runtimed\drivers\berniw\2\cg-nascar-rwd.rgb
if exist .\src\drivers\berniw\2\aalborg.xml copy .\src\drivers\berniw\2\aalborg.xml .\runtimed\drivers\berniw\2\aalborg.xml
if exist .\src\drivers\berniw\2\alpine-1.xml copy .\src\drivers\berniw\2\alpine-1.xml .\runtimed\drivers\berniw\2\alpine-1.xml
if exist .\src\drivers\berniw\2\a-speedway.xml copy .\src\drivers\berniw\2\a-speedway.xml .\runtimed\drivers\berniw\2\a-speedway.xml
if exist .\src\drivers\berniw\2\default.xml copy .\src\drivers\berniw\2\default.xml .\runtimed\drivers\berniw\2\default.xml
if exist .\src\drivers\berniw\2\dirt-1.xml copy .\src\drivers\berniw\2\dirt-1.xml .\runtimed\drivers\berniw\2\dirt-1.xml
if exist .\src\drivers\berniw\2\dirt-2.xml copy .\src\drivers\berniw\2\dirt-2.xml .\runtimed\drivers\berniw\2\dirt-2.xml
if exist .\src\drivers\berniw\2\dirt-3.xml copy .\src\drivers\berniw\2\dirt-3.xml .\runtimed\drivers\berniw\2\dirt-3.xml
if exist .\src\drivers\berniw\2\dirt-4.xml copy .\src\drivers\berniw\2\dirt-4.xml .\runtimed\drivers\berniw\2\dirt-4.xml
if exist .\src\drivers\berniw\2\dirt-5.xml copy .\src\drivers\berniw\2\dirt-5.xml .\runtimed\drivers\berniw\2\dirt-5.xml
if exist .\src\drivers\berniw\2\dirt-6.xml copy .\src\drivers\berniw\2\dirt-6.xml .\runtimed\drivers\berniw\2\dirt-6.xml
if exist .\src\drivers\berniw\2\eroad.xml copy .\src\drivers\berniw\2\eroad.xml .\runtimed\drivers\berniw\2\eroad.xml
if exist .\src\drivers\berniw\2\e-track-1.xml copy .\src\drivers\berniw\2\e-track-1.xml .\runtimed\drivers\berniw\2\e-track-1.xml
if exist .\src\drivers\berniw\2\e-track-2.xml copy .\src\drivers\berniw\2\e-track-2.xml .\runtimed\drivers\berniw\2\e-track-2.xml
if exist .\src\drivers\berniw\2\e-track-3.xml copy .\src\drivers\berniw\2\e-track-3.xml .\runtimed\drivers\berniw\2\e-track-3.xml
if exist .\src\drivers\berniw\2\e-track-4.xml copy .\src\drivers\berniw\2\e-track-4.xml .\runtimed\drivers\berniw\2\e-track-4.xml
if exist .\src\drivers\berniw\2\e-track-5.xml copy .\src\drivers\berniw\2\e-track-5.xml .\runtimed\drivers\berniw\2\e-track-5.xml
if exist .\src\drivers\berniw\2\e-track-6.xml copy .\src\drivers\berniw\2\e-track-6.xml .\runtimed\drivers\berniw\2\e-track-6.xml
if exist .\src\drivers\berniw\2\g-track-1.xml copy .\src\drivers\berniw\2\g-track-1.xml .\runtimed\drivers\berniw\2\g-track-1.xml
if exist .\src\drivers\berniw\2\g-track-2.xml copy .\src\drivers\berniw\2\g-track-2.xml .\runtimed\drivers\berniw\2\g-track-2.xml
if exist .\src\drivers\berniw\2\g-track-3.xml copy .\src\drivers\berniw\2\g-track-3.xml .\runtimed\drivers\berniw\2\g-track-3.xml
if exist .\src\drivers\berniw\2\michigan.xml copy .\src\drivers\berniw\2\michigan.xml .\runtimed\drivers\berniw\2\michigan.xml
if exist .\src\drivers\berniw\2\mixed-1.xml copy .\src\drivers\berniw\2\mixed-1.xml .\runtimed\drivers\berniw\2\mixed-1.xml
if exist .\src\drivers\berniw\2\mixed-2.xml copy .\src\drivers\berniw\2\mixed-2.xml .\runtimed\drivers\berniw\2\mixed-2.xml
if exist .\src\drivers\berniw\2\spring.xml copy .\src\drivers\berniw\2\spring.xml .\runtimed\drivers\berniw\2\spring.xml
if exist .\src\drivers\berniw\2\wheel-1.xml copy .\src\drivers\berniw\2\wheel-1.xml .\runtimed\drivers\berniw\2\wheel-1.xml

if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtimed\drivers\berniw\3
if exist .\src\drivers\berniw\3\porsche-gt1.rgb copy .\src\drivers\berniw\3\porsche-gt1.rgb .\runtimed\drivers\berniw\3\porsche-gt1.rgb
if exist .\src\drivers\berniw\3\aalborg.xml copy .\src\drivers\berniw\3\aalborg.xml .\runtimed\drivers\berniw\3\aalborg.xml
if exist .\src\drivers\berniw\3\alpine-1.xml copy .\src\drivers\berniw\3\alpine-1.xml .\runtimed\drivers\berniw\3\alpine-1.xml
if exist .\src\drivers\berniw\3\a-speedway.xml copy .\src\drivers\berniw\3\a-speedway.xml .\runtimed\drivers\berniw\3\a-speedway.xml
if exist .\src\drivers\berniw\3\default.xml copy .\src\drivers\berniw\3\default.xml .\runtimed\drivers\berniw\3\default.xml
if exist .\src\drivers\berniw\3\dirt-1.xml copy .\src\drivers\berniw\3\dirt-1.xml .\runtimed\drivers\berniw\3\dirt-1.xml
if exist .\src\drivers\berniw\3\dirt-2.xml copy .\src\drivers\berniw\3\dirt-2.xml .\runtimed\drivers\berniw\3\dirt-2.xml
if exist .\src\drivers\berniw\3\dirt-3.xml copy .\src\drivers\berniw\3\dirt-3.xml .\runtimed\drivers\berniw\3\dirt-3.xml
if exist .\src\drivers\berniw\3\dirt-4.xml copy .\src\drivers\berniw\3\dirt-4.xml .\runtimed\drivers\berniw\3\dirt-4.xml
if exist .\src\drivers\berniw\3\dirt-5.xml copy .\src\drivers\berniw\3\dirt-5.xml .\runtimed\drivers\berniw\3\dirt-5.xml
if exist .\src\drivers\berniw\3\dirt-6.xml copy .\src\drivers\berniw\3\dirt-6.xml .\runtimed\drivers\berniw\3\dirt-6.xml
if exist .\src\drivers\berniw\3\eroad.xml copy .\src\drivers\berniw\3\eroad.xml .\runtimed\drivers\berniw\3\eroad.xml
if exist .\src\drivers\berniw\3\e-track-1.xml copy .\src\drivers\berniw\3\e-track-1.xml .\runtimed\drivers\berniw\3\e-track-1.xml
if exist .\src\drivers\berniw\3\e-track-2.xml copy .\src\drivers\berniw\3\e-track-2.xml .\runtimed\drivers\berniw\3\e-track-2.xml
if exist .\src\drivers\berniw\3\e-track-3.xml copy .\src\drivers\berniw\3\e-track-3.xml .\runtimed\drivers\berniw\3\e-track-3.xml
if exist .\src\drivers\berniw\3\e-track-4.xml copy .\src\drivers\berniw\3\e-track-4.xml .\runtimed\drivers\berniw\3\e-track-4.xml
if exist .\src\drivers\berniw\3\e-track-5.xml copy .\src\drivers\berniw\3\e-track-5.xml .\runtimed\drivers\berniw\3\e-track-5.xml
if exist .\src\drivers\berniw\3\e-track-6.xml copy .\src\drivers\berniw\3\e-track-6.xml .\runtimed\drivers\berniw\3\e-track-6.xml
if exist .\src\drivers\berniw\3\g-track-1.xml copy .\src\drivers\berniw\3\g-track-1.xml .\runtimed\drivers\berniw\3\g-track-1.xml
if exist .\src\drivers\berniw\3\g-track-2.xml copy .\src\drivers\berniw\3\g-track-2.xml .\runtimed\drivers\berniw\3\g-track-2.xml
if exist .\src\drivers\berniw\3\g-track-3.xml copy .\src\drivers\berniw\3\g-track-3.xml .\runtimed\drivers\berniw\3\g-track-3.xml
if exist .\src\drivers\berniw\3\michigan.xml copy .\src\drivers\berniw\3\michigan.xml .\runtimed\drivers\berniw\3\michigan.xml
if exist .\src\drivers\berniw\3\mixed-1.xml copy .\src\drivers\berniw\3\mixed-1.xml .\runtimed\drivers\berniw\3\mixed-1.xml
if exist .\src\drivers\berniw\3\mixed-2.xml copy .\src\drivers\berniw\3\mixed-2.xml .\runtimed\drivers\berniw\3\mixed-2.xml
if exist .\src\drivers\berniw\3\spring.xml copy .\src\drivers\berniw\3\spring.xml .\runtimed\drivers\berniw\3\spring.xml
if exist .\src\drivers\berniw\3\wheel-1.xml copy .\src\drivers\berniw\3\wheel-1.xml .\runtimed\drivers\berniw\3\wheel-1.xml

if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtimed\drivers\berniw\4
if exist .\src\drivers\berniw\4\viper-gts-r.rgb copy .\src\drivers\berniw\4\viper-gts-r.rgb .\runtimed\drivers\berniw\4\viper-gts-r.rgb
if exist .\src\drivers\berniw\4\aalborg.xml copy .\src\drivers\berniw\4\aalborg.xml .\runtimed\drivers\berniw\4\aalborg.xml
if exist .\src\drivers\berniw\4\alpine-1.xml copy .\src\drivers\berniw\4\alpine-1.xml .\runtimed\drivers\berniw\4\alpine-1.xml
if exist .\src\drivers\berniw\4\a-speedway.xml copy .\src\drivers\berniw\4\a-speedway.xml .\runtimed\drivers\berniw\4\a-speedway.xml
if exist .\src\drivers\berniw\4\default.xml copy .\src\drivers\berniw\4\default.xml .\runtimed\drivers\berniw\4\default.xml
if exist .\src\drivers\berniw\4\dirt-1.xml copy .\src\drivers\berniw\4\dirt-1.xml .\runtimed\drivers\berniw\4\dirt-1.xml
if exist .\src\drivers\berniw\4\dirt-2.xml copy .\src\drivers\berniw\4\dirt-2.xml .\runtimed\drivers\berniw\4\dirt-2.xml
if exist .\src\drivers\berniw\4\dirt-3.xml copy .\src\drivers\berniw\4\dirt-3.xml .\runtimed\drivers\berniw\4\dirt-3.xml
if exist .\src\drivers\berniw\4\dirt-4.xml copy .\src\drivers\berniw\4\dirt-4.xml .\runtimed\drivers\berniw\4\dirt-4.xml
if exist .\src\drivers\berniw\4\dirt-5.xml copy .\src\drivers\berniw\4\dirt-5.xml .\runtimed\drivers\berniw\4\dirt-5.xml
if exist .\src\drivers\berniw\4\dirt-6.xml copy .\src\drivers\berniw\4\dirt-6.xml .\runtimed\drivers\berniw\4\dirt-6.xml
if exist .\src\drivers\berniw\4\eroad.xml copy .\src\drivers\berniw\4\eroad.xml .\runtimed\drivers\berniw\4\eroad.xml
if exist .\src\drivers\berniw\4\e-track-1.xml copy .\src\drivers\berniw\4\e-track-1.xml .\runtimed\drivers\berniw\4\e-track-1.xml
if exist .\src\drivers\berniw\4\e-track-2.xml copy .\src\drivers\berniw\4\e-track-2.xml .\runtimed\drivers\berniw\4\e-track-2.xml
if exist .\src\drivers\berniw\4\e-track-3.xml copy .\src\drivers\berniw\4\e-track-3.xml .\runtimed\drivers\berniw\4\e-track-3.xml
if exist .\src\drivers\berniw\4\e-track-4.xml copy .\src\drivers\berniw\4\e-track-4.xml .\runtimed\drivers\berniw\4\e-track-4.xml
if exist .\src\drivers\berniw\4\e-track-5.xml copy .\src\drivers\berniw\4\e-track-5.xml .\runtimed\drivers\berniw\4\e-track-5.xml
if exist .\src\drivers\berniw\4\e-track-6.xml copy .\src\drivers\berniw\4\e-track-6.xml .\runtimed\drivers\berniw\4\e-track-6.xml
if exist .\src\drivers\berniw\4\g-track-1.xml copy .\src\drivers\berniw\4\g-track-1.xml .\runtimed\drivers\berniw\4\g-track-1.xml
if exist .\src\drivers\berniw\4\g-track-2.xml copy .\src\drivers\berniw\4\g-track-2.xml .\runtimed\drivers\berniw\4\g-track-2.xml
if exist .\src\drivers\berniw\4\g-track-3.xml copy .\src\drivers\berniw\4\g-track-3.xml .\runtimed\drivers\berniw\4\g-track-3.xml
if exist .\src\drivers\berniw\4\michigan.xml copy .\src\drivers\berniw\4\michigan.xml .\runtimed\drivers\berniw\4\michigan.xml
if exist .\src\drivers\berniw\4\mixed-1.xml copy .\src\drivers\berniw\4\mixed-1.xml .\runtimed\drivers\berniw\4\mixed-1.xml
if exist .\src\drivers\berniw\4\mixed-2.xml copy .\src\drivers\berniw\4\mixed-2.xml .\runtimed\drivers\berniw\4\mixed-2.xml
if exist .\src\drivers\berniw\4\spring.xml copy .\src\drivers\berniw\4\spring.xml .\runtimed\drivers\berniw\4\spring.xml
if exist .\src\drivers\berniw\4\wheel-1.xml copy .\src\drivers\berniw\4\wheel-1.xml .\runtimed\drivers\berniw\4\wheel-1.xml
if exist .\src\drivers\berniw\4\ole-road-1.xml copy .\src\drivers\berniw\4\ole-road-1.xml .\runtimed\drivers\berniw\4\ole-road-1.xml

if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtimed\drivers\berniw\5
if exist .\src\drivers\berniw\5\gt40.rgb copy .\src\drivers\berniw\5\gt40.rgb .\runtimed\drivers\berniw\5\gt40.rgb
if exist .\src\drivers\berniw\5\aalborg.xml copy .\src\drivers\berniw\5\aalborg.xml .\runtimed\drivers\berniw\5\aalborg.xml
if exist .\src\drivers\berniw\5\alpine-1.xml copy .\src\drivers\berniw\5\alpine-1.xml .\runtimed\drivers\berniw\5\alpine-1.xml
if exist .\src\drivers\berniw\5\a-speedway.xml copy .\src\drivers\berniw\5\a-speedway.xml .\runtimed\drivers\berniw\5\a-speedway.xml
if exist .\src\drivers\berniw\5\default.xml copy .\src\drivers\berniw\5\default.xml .\runtimed\drivers\berniw\5\default.xml
if exist .\src\drivers\berniw\5\dirt-1.xml copy .\src\drivers\berniw\5\dirt-1.xml .\runtimed\drivers\berniw\5\dirt-1.xml
if exist .\src\drivers\berniw\5\dirt-2.xml copy .\src\drivers\berniw\5\dirt-2.xml .\runtimed\drivers\berniw\5\dirt-2.xml
if exist .\src\drivers\berniw\5\dirt-3.xml copy .\src\drivers\berniw\5\dirt-3.xml .\runtimed\drivers\berniw\5\dirt-3.xml
if exist .\src\drivers\berniw\5\dirt-4.xml copy .\src\drivers\berniw\5\dirt-4.xml .\runtimed\drivers\berniw\5\dirt-4.xml
if exist .\src\drivers\berniw\5\dirt-5.xml copy .\src\drivers\berniw\5\dirt-5.xml .\runtimed\drivers\berniw\5\dirt-5.xml
if exist .\src\drivers\berniw\5\dirt-6.xml copy .\src\drivers\berniw\5\dirt-6.xml .\runtimed\drivers\berniw\5\dirt-6.xml
if exist .\src\drivers\berniw\5\eroad.xml copy .\src\drivers\berniw\5\eroad.xml .\runtimed\drivers\berniw\5\eroad.xml
if exist .\src\drivers\berniw\5\e-track-1.xml copy .\src\drivers\berniw\5\e-track-1.xml .\runtimed\drivers\berniw\5\e-track-1.xml
if exist .\src\drivers\berniw\5\e-track-2.xml copy .\src\drivers\berniw\5\e-track-2.xml .\runtimed\drivers\berniw\5\e-track-2.xml
if exist .\src\drivers\berniw\5\e-track-3.xml copy .\src\drivers\berniw\5\e-track-3.xml .\runtimed\drivers\berniw\5\e-track-3.xml
if exist .\src\drivers\berniw\5\e-track-4.xml copy .\src\drivers\berniw\5\e-track-4.xml .\runtimed\drivers\berniw\5\e-track-4.xml
if exist .\src\drivers\berniw\5\e-track-5.xml copy .\src\drivers\berniw\5\e-track-5.xml .\runtimed\drivers\berniw\5\e-track-5.xml
if exist .\src\drivers\berniw\5\e-track-6.xml copy .\src\drivers\berniw\5\e-track-6.xml .\runtimed\drivers\berniw\5\e-track-6.xml
if exist .\src\drivers\berniw\5\g-track-1.xml copy .\src\drivers\berniw\5\g-track-1.xml .\runtimed\drivers\berniw\5\g-track-1.xml
if exist .\src\drivers\berniw\5\g-track-2.xml copy .\src\drivers\berniw\5\g-track-2.xml .\runtimed\drivers\berniw\5\g-track-2.xml
if exist .\src\drivers\berniw\5\g-track-3.xml copy .\src\drivers\berniw\5\g-track-3.xml .\runtimed\drivers\berniw\5\g-track-3.xml
if exist .\src\drivers\berniw\5\michigan.xml copy .\src\drivers\berniw\5\michigan.xml .\runtimed\drivers\berniw\5\michigan.xml
if exist .\src\drivers\berniw\5\mixed-1.xml copy .\src\drivers\berniw\5\mixed-1.xml .\runtimed\drivers\berniw\5\mixed-1.xml
if exist .\src\drivers\berniw\5\mixed-2.xml copy .\src\drivers\berniw\5\mixed-2.xml .\runtimed\drivers\berniw\5\mixed-2.xml
if exist .\src\drivers\berniw\5\spring.xml copy .\src\drivers\berniw\5\spring.xml .\runtimed\drivers\berniw\5\spring.xml
if exist .\src\drivers\berniw\5\wheel-1.xml copy .\src\drivers\berniw\5\wheel-1.xml .\runtimed\drivers\berniw\5\wheel-1.xml

if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtimed\drivers\berniw\6
if exist .\src\drivers\berniw\6\155-DTM.rgb copy .\src\drivers\berniw\6\155-DTM.rgb .\runtimed\drivers\berniw\6\155-DTM.rgb
if exist .\src\drivers\berniw\6\aalborg.xml copy .\src\drivers\berniw\6\aalborg.xml .\runtimed\drivers\berniw\6\aalborg.xml
if exist .\src\drivers\berniw\6\alpine-1.xml copy .\src\drivers\berniw\6\alpine-1.xml .\runtimed\drivers\berniw\6\alpine-1.xml
if exist .\src\drivers\berniw\6\a-speedway.xml copy .\src\drivers\berniw\6\a-speedway.xml .\runtimed\drivers\berniw\6\a-speedway.xml
if exist .\src\drivers\berniw\6\default.xml copy .\src\drivers\berniw\6\default.xml .\runtimed\drivers\berniw\6\default.xml
if exist .\src\drivers\berniw\6\dirt-1.xml copy .\src\drivers\berniw\6\dirt-1.xml .\runtimed\drivers\berniw\6\dirt-1.xml
if exist .\src\drivers\berniw\6\dirt-2.xml copy .\src\drivers\berniw\6\dirt-2.xml .\runtimed\drivers\berniw\6\dirt-2.xml
if exist .\src\drivers\berniw\6\dirt-3.xml copy .\src\drivers\berniw\6\dirt-3.xml .\runtimed\drivers\berniw\6\dirt-3.xml
if exist .\src\drivers\berniw\6\dirt-4.xml copy .\src\drivers\berniw\6\dirt-4.xml .\runtimed\drivers\berniw\6\dirt-4.xml
if exist .\src\drivers\berniw\6\dirt-5.xml copy .\src\drivers\berniw\6\dirt-5.xml .\runtimed\drivers\berniw\6\dirt-5.xml
if exist .\src\drivers\berniw\6\dirt-6.xml copy .\src\drivers\berniw\6\dirt-6.xml .\runtimed\drivers\berniw\6\dirt-6.xml
if exist .\src\drivers\berniw\6\eroad.xml copy .\src\drivers\berniw\6\eroad.xml .\runtimed\drivers\berniw\6\eroad.xml
if exist .\src\drivers\berniw\6\e-track-1.xml copy .\src\drivers\berniw\6\e-track-1.xml .\runtimed\drivers\berniw\6\e-track-1.xml
if exist .\src\drivers\berniw\6\e-track-2.xml copy .\src\drivers\berniw\6\e-track-2.xml .\runtimed\drivers\berniw\6\e-track-2.xml
if exist .\src\drivers\berniw\6\e-track-3.xml copy .\src\drivers\berniw\6\e-track-3.xml .\runtimed\drivers\berniw\6\e-track-3.xml
if exist .\src\drivers\berniw\6\e-track-4.xml copy .\src\drivers\berniw\6\e-track-4.xml .\runtimed\drivers\berniw\6\e-track-4.xml
if exist .\src\drivers\berniw\6\e-track-5.xml copy .\src\drivers\berniw\6\e-track-5.xml .\runtimed\drivers\berniw\6\e-track-5.xml
if exist .\src\drivers\berniw\6\e-track-6.xml copy .\src\drivers\berniw\6\e-track-6.xml .\runtimed\drivers\berniw\6\e-track-6.xml
if exist .\src\drivers\berniw\6\g-track-1.xml copy .\src\drivers\berniw\6\g-track-1.xml .\runtimed\drivers\berniw\6\g-track-1.xml
if exist .\src\drivers\berniw\6\g-track-2.xml copy .\src\drivers\berniw\6\g-track-2.xml .\runtimed\drivers\berniw\6\g-track-2.xml
if exist .\src\drivers\berniw\6\g-track-3.xml copy .\src\drivers\berniw\6\g-track-3.xml .\runtimed\drivers\berniw\6\g-track-3.xml
if exist .\src\drivers\berniw\6\michigan.xml copy .\src\drivers\berniw\6\michigan.xml .\runtimed\drivers\berniw\6\michigan.xml
if exist .\src\drivers\berniw\6\mixed-1.xml copy .\src\drivers\berniw\6\mixed-1.xml .\runtimed\drivers\berniw\6\mixed-1.xml
if exist .\src\drivers\berniw\6\mixed-2.xml copy .\src\drivers\berniw\6\mixed-2.xml .\runtimed\drivers\berniw\6\mixed-2.xml
if exist .\src\drivers\berniw\6\spring.xml copy .\src\drivers\berniw\6\spring.xml .\runtimed\drivers\berniw\6\spring.xml
if exist .\src\drivers\berniw\6\wheel-1.xml copy .\src\drivers\berniw\6\wheel-1.xml .\runtimed\drivers\berniw\6\wheel-1.xml

if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtimed\drivers\berniw\7
if exist .\src\drivers\berniw\7\lotus-gt1.rgb copy .\src\drivers\berniw\7\lotus-gt1.rgb .\runtimed\drivers\berniw\7\lotus-gt1.rgb
if exist .\src\drivers\berniw\7\aalborg.xml copy .\src\drivers\berniw\7\aalborg.xml .\runtimed\drivers\berniw\7\aalborg.xml
if exist .\src\drivers\berniw\7\alpine-1.xml copy .\src\drivers\berniw\7\alpine-1.xml .\runtimed\drivers\berniw\7\alpine-1.xml
if exist .\src\drivers\berniw\7\a-speedway.xml copy .\src\drivers\berniw\7\a-speedway.xml .\runtimed\drivers\berniw\7\a-speedway.xml
if exist .\src\drivers\berniw\7\default.xml copy .\src\drivers\berniw\7\default.xml .\runtimed\drivers\berniw\7\default.xml
if exist .\src\drivers\berniw\7\dirt-1.xml copy .\src\drivers\berniw\7\dirt-1.xml .\runtimed\drivers\berniw\7\dirt-1.xml
if exist .\src\drivers\berniw\7\dirt-2.xml copy .\src\drivers\berniw\7\dirt-2.xml .\runtimed\drivers\berniw\7\dirt-2.xml
if exist .\src\drivers\berniw\7\dirt-3.xml copy .\src\drivers\berniw\7\dirt-3.xml .\runtimed\drivers\berniw\7\dirt-3.xml
if exist .\src\drivers\berniw\7\dirt-4.xml copy .\src\drivers\berniw\7\dirt-4.xml .\runtimed\drivers\berniw\7\dirt-4.xml
if exist .\src\drivers\berniw\7\dirt-5.xml copy .\src\drivers\berniw\7\dirt-5.xml .\runtimed\drivers\berniw\7\dirt-5.xml
if exist .\src\drivers\berniw\7\dirt-6.xml copy .\src\drivers\berniw\7\dirt-6.xml .\runtimed\drivers\berniw\7\dirt-6.xml
if exist .\src\drivers\berniw\7\eroad.xml copy .\src\drivers\berniw\7\eroad.xml .\runtimed\drivers\berniw\7\eroad.xml
if exist .\src\drivers\berniw\7\e-track-1.xml copy .\src\drivers\berniw\7\e-track-1.xml .\runtimed\drivers\berniw\7\e-track-1.xml
if exist .\src\drivers\berniw\7\e-track-2.xml copy .\src\drivers\berniw\7\e-track-2.xml .\runtimed\drivers\berniw\7\e-track-2.xml
if exist .\src\drivers\berniw\7\e-track-3.xml copy .\src\drivers\berniw\7\e-track-3.xml .\runtimed\drivers\berniw\7\e-track-3.xml
if exist .\src\drivers\berniw\7\e-track-4.xml copy .\src\drivers\berniw\7\e-track-4.xml .\runtimed\drivers\berniw\7\e-track-4.xml
if exist .\src\drivers\berniw\7\e-track-5.xml copy .\src\drivers\berniw\7\e-track-5.xml .\runtimed\drivers\berniw\7\e-track-5.xml
if exist .\src\drivers\berniw\7\e-track-6.xml copy .\src\drivers\berniw\7\e-track-6.xml .\runtimed\drivers\berniw\7\e-track-6.xml
if exist .\src\drivers\berniw\7\g-track-1.xml copy .\src\drivers\berniw\7\g-track-1.xml .\runtimed\drivers\berniw\7\g-track-1.xml
if exist .\src\drivers\berniw\7\g-track-2.xml copy .\src\drivers\berniw\7\g-track-2.xml .\runtimed\drivers\berniw\7\g-track-2.xml
if exist .\src\drivers\berniw\7\g-track-3.xml copy .\src\drivers\berniw\7\g-track-3.xml .\runtimed\drivers\berniw\7\g-track-3.xml
if exist .\src\drivers\berniw\7\michigan.xml copy .\src\drivers\berniw\7\michigan.xml .\runtimed\drivers\berniw\7\michigan.xml
if exist .\src\drivers\berniw\7\mixed-1.xml copy .\src\drivers\berniw\7\mixed-1.xml .\runtimed\drivers\berniw\7\mixed-1.xml
if exist .\src\drivers\berniw\7\mixed-2.xml copy .\src\drivers\berniw\7\mixed-2.xml .\runtimed\drivers\berniw\7\mixed-2.xml
if exist .\src\drivers\berniw\7\spring.xml copy .\src\drivers\berniw\7\spring.xml .\runtimed\drivers\berniw\7\spring.xml
if exist .\src\drivers\berniw\7\wheel-1.xml copy .\src\drivers\berniw\7\wheel-1.xml .\runtimed\drivers\berniw\7\wheel-1.xml

if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtimed\drivers\berniw\8
if exist .\src\drivers\berniw\8\baja-bug.rgb copy .\src\drivers\berniw\8\baja-bug.rgb .\runtimed\drivers\berniw\8\baja-bug.rgb
if exist .\src\drivers\berniw\8\aalborg.xml copy .\src\drivers\berniw\8\aalborg.xml .\runtimed\drivers\berniw\8\aalborg.xml
if exist .\src\drivers\berniw\8\alpine-1.xml copy .\src\drivers\berniw\8\alpine-1.xml .\runtimed\drivers\berniw\8\alpine-1.xml
if exist .\src\drivers\berniw\8\a-speedway.xml copy .\src\drivers\berniw\8\a-speedway.xml .\runtimed\drivers\berniw\8\a-speedway.xml
if exist .\src\drivers\berniw\8\default.xml copy .\src\drivers\berniw\8\default.xml .\runtimed\drivers\berniw\8\default.xml
if exist .\src\drivers\berniw\8\dirt-1.xml copy .\src\drivers\berniw\8\dirt-1.xml .\runtimed\drivers\berniw\8\dirt-1.xml
if exist .\src\drivers\berniw\8\dirt-2.xml copy .\src\drivers\berniw\8\dirt-2.xml .\runtimed\drivers\berniw\8\dirt-2.xml
if exist .\src\drivers\berniw\8\dirt-3.xml copy .\src\drivers\berniw\8\dirt-3.xml .\runtimed\drivers\berniw\8\dirt-3.xml
if exist .\src\drivers\berniw\8\dirt-4.xml copy .\src\drivers\berniw\8\dirt-4.xml .\runtimed\drivers\berniw\8\dirt-4.xml
if exist .\src\drivers\berniw\8\dirt-5.xml copy .\src\drivers\berniw\8\dirt-5.xml .\runtimed\drivers\berniw\8\dirt-5.xml
if exist .\src\drivers\berniw\8\dirt-6.xml copy .\src\drivers\berniw\8\dirt-6.xml .\runtimed\drivers\berniw\8\dirt-6.xml
if exist .\src\drivers\berniw\8\eroad.xml copy .\src\drivers\berniw\8\eroad.xml .\runtimed\drivers\berniw\8\eroad.xml
if exist .\src\drivers\berniw\8\e-track-1.xml copy .\src\drivers\berniw\8\e-track-1.xml .\runtimed\drivers\berniw\8\e-track-1.xml
if exist .\src\drivers\berniw\8\e-track-2.xml copy .\src\drivers\berniw\8\e-track-2.xml .\runtimed\drivers\berniw\8\e-track-2.xml
if exist .\src\drivers\berniw\8\e-track-3.xml copy .\src\drivers\berniw\8\e-track-3.xml .\runtimed\drivers\berniw\8\e-track-3.xml
if exist .\src\drivers\berniw\8\e-track-4.xml copy .\src\drivers\berniw\8\e-track-4.xml .\runtimed\drivers\berniw\8\e-track-4.xml
if exist .\src\drivers\berniw\8\e-track-5.xml copy .\src\drivers\berniw\8\e-track-5.xml .\runtimed\drivers\berniw\8\e-track-5.xml
if exist .\src\drivers\berniw\8\e-track-6.xml copy .\src\drivers\berniw\8\e-track-6.xml .\runtimed\drivers\berniw\8\e-track-6.xml
if exist .\src\drivers\berniw\8\g-track-1.xml copy .\src\drivers\berniw\8\g-track-1.xml .\runtimed\drivers\berniw\8\g-track-1.xml
if exist .\src\drivers\berniw\8\g-track-2.xml copy .\src\drivers\berniw\8\g-track-2.xml .\runtimed\drivers\berniw\8\g-track-2.xml
if exist .\src\drivers\berniw\8\g-track-3.xml copy .\src\drivers\berniw\8\g-track-3.xml .\runtimed\drivers\berniw\8\g-track-3.xml
if exist .\src\drivers\berniw\8\michigan.xml copy .\src\drivers\berniw\8\michigan.xml .\runtimed\drivers\berniw\8\michigan.xml
if exist .\src\drivers\berniw\8\mixed-1.xml copy .\src\drivers\berniw\8\mixed-1.xml .\runtimed\drivers\berniw\8\mixed-1.xml
if exist .\src\drivers\berniw\8\mixed-2.xml copy .\src\drivers\berniw\8\mixed-2.xml .\runtimed\drivers\berniw\8\mixed-2.xml
if exist .\src\drivers\berniw\8\spring.xml copy .\src\drivers\berniw\8\spring.xml .\runtimed\drivers\berniw\8\spring.xml
if exist .\src\drivers\berniw\8\wheel-1.xml copy .\src\drivers\berniw\8\wheel-1.xml .\runtimed\drivers\berniw\8\wheel-1.xml

if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtimed\drivers\berniw\9
if exist .\src\drivers\berniw\9\mclaren-f1.rgb copy .\src\drivers\berniw\9\mclaren-f1.rgb .\runtimed\drivers\berniw\9\mclaren-f1.rgb
if exist .\src\drivers\berniw\9\aalborg.xml copy .\src\drivers\berniw\9\aalborg.xml .\runtimed\drivers\berniw\9\aalborg.xml
if exist .\src\drivers\berniw\9\alpine-1.xml copy .\src\drivers\berniw\9\alpine-1.xml .\runtimed\drivers\berniw\9\alpine-1.xml
if exist .\src\drivers\berniw\9\a-speedway.xml copy .\src\drivers\berniw\9\a-speedway.xml .\runtimed\drivers\berniw\9\a-speedway.xml
if exist .\src\drivers\berniw\9\default.xml copy .\src\drivers\berniw\9\default.xml .\runtimed\drivers\berniw\9\default.xml
if exist .\src\drivers\berniw\9\dirt-1.xml copy .\src\drivers\berniw\9\dirt-1.xml .\runtimed\drivers\berniw\9\dirt-1.xml
if exist .\src\drivers\berniw\9\dirt-2.xml copy .\src\drivers\berniw\9\dirt-2.xml .\runtimed\drivers\berniw\9\dirt-2.xml
if exist .\src\drivers\berniw\9\dirt-3.xml copy .\src\drivers\berniw\9\dirt-3.xml .\runtimed\drivers\berniw\9\dirt-3.xml
if exist .\src\drivers\berniw\9\dirt-4.xml copy .\src\drivers\berniw\9\dirt-4.xml .\runtimed\drivers\berniw\9\dirt-4.xml
if exist .\src\drivers\berniw\9\dirt-5.xml copy .\src\drivers\berniw\9\dirt-5.xml .\runtimed\drivers\berniw\9\dirt-5.xml
if exist .\src\drivers\berniw\9\dirt-6.xml copy .\src\drivers\berniw\9\dirt-6.xml .\runtimed\drivers\berniw\9\dirt-6.xml
if exist .\src\drivers\berniw\9\eroad.xml copy .\src\drivers\berniw\9\eroad.xml .\runtimed\drivers\berniw\9\eroad.xml
if exist .\src\drivers\berniw\9\e-track-1.xml copy .\src\drivers\berniw\9\e-track-1.xml .\runtimed\drivers\berniw\9\e-track-1.xml
if exist .\src\drivers\berniw\9\e-track-2.xml copy .\src\drivers\berniw\9\e-track-2.xml .\runtimed\drivers\berniw\9\e-track-2.xml
if exist .\src\drivers\berniw\9\e-track-3.xml copy .\src\drivers\berniw\9\e-track-3.xml .\runtimed\drivers\berniw\9\e-track-3.xml
if exist .\src\drivers\berniw\9\e-track-4.xml copy .\src\drivers\berniw\9\e-track-4.xml .\runtimed\drivers\berniw\9\e-track-4.xml
if exist .\src\drivers\berniw\9\e-track-5.xml copy .\src\drivers\berniw\9\e-track-5.xml .\runtimed\drivers\berniw\9\e-track-5.xml
if exist .\src\drivers\berniw\9\e-track-6.xml copy .\src\drivers\berniw\9\e-track-6.xml .\runtimed\drivers\berniw\9\e-track-6.xml
if exist .\src\drivers\berniw\9\g-track-1.xml copy .\src\drivers\berniw\9\g-track-1.xml .\runtimed\drivers\berniw\9\g-track-1.xml
if exist .\src\drivers\berniw\9\g-track-2.xml copy .\src\drivers\berniw\9\g-track-2.xml .\runtimed\drivers\berniw\9\g-track-2.xml
if exist .\src\drivers\berniw\9\g-track-3.xml copy .\src\drivers\berniw\9\g-track-3.xml .\runtimed\drivers\berniw\9\g-track-3.xml
if exist .\src\drivers\berniw\9\michigan.xml copy .\src\drivers\berniw\9\michigan.xml .\runtimed\drivers\berniw\9\michigan.xml
if exist .\src\drivers\berniw\9\mixed-1.xml copy .\src\drivers\berniw\9\mixed-1.xml .\runtimed\drivers\berniw\9\mixed-1.xml
if exist .\src\drivers\berniw\9\mixed-2.xml copy .\src\drivers\berniw\9\mixed-2.xml .\runtimed\drivers\berniw\9\mixed-2.xml
if exist .\src\drivers\berniw\9\spring.xml copy .\src\drivers\berniw\9\spring.xml .\runtimed\drivers\berniw\9\spring.xml
if exist .\src\drivers\berniw\9\wheel-1.xml copy .\src\drivers\berniw\9\wheel-1.xml .\runtimed\drivers\berniw\9\wheel-1.xml

if exist .\src\drivers\berniw\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw\*.* call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\berniw.xml copy .\src\drivers\berniw\berniw.xml .\runtimed\drivers\berniw\berniw.xml
if exist .\src\drivers\berniw\logo.rgb copy .\src\drivers\berniw\logo.rgb .\runtimed\drivers\berniw\logo.rgb
if exist .\src\drivers\berniw\parameter.dat copy .\src\drivers\berniw\parameter.dat .\runtimed\drivers\berniw\parameter.dat
if exist .\src\drivers\berniw\intsinsqr.dat copy .\src\drivers\berniw\intsinsqr.dat .\runtimed\drivers\berniw\intsinsqr.dat
if exist .\src\drivers\berniw\intcossqr.dat copy .\src\drivers\berniw\intcossqr.dat .\runtimed\drivers\berniw\intcossqr.dat

if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtimed\drivers\berniw2\1
if exist .\src\drivers\berniw2\1\aalborg.xml copy .\src\drivers\berniw2\1\aalborg.xml .\runtimed\drivers\berniw2\1\aalborg.xml
if exist .\src\drivers\berniw2\1\alpine-1.xml copy .\src\drivers\berniw2\1\alpine-1.xml .\runtimed\drivers\berniw2\1\alpine-1.xml
if exist .\src\drivers\berniw2\1\a-speedway.xml copy .\src\drivers\berniw2\1\a-speedway.xml .\runtimed\drivers\berniw2\1\a-speedway.xml
if exist .\src\drivers\berniw2\1\default.xml copy .\src\drivers\berniw2\1\default.xml .\runtimed\drivers\berniw2\1\default.xml
if exist .\src\drivers\berniw2\1\dirt-1.xml copy .\src\drivers\berniw2\1\dirt-1.xml .\runtimed\drivers\berniw2\1\dirt-1.xml
if exist .\src\drivers\berniw2\1\dirt-2.xml copy .\src\drivers\berniw2\1\dirt-2.xml .\runtimed\drivers\berniw2\1\dirt-2.xml
if exist .\src\drivers\berniw2\1\dirt-3.xml copy .\src\drivers\berniw2\1\dirt-3.xml .\runtimed\drivers\berniw2\1\dirt-3.xml
if exist .\src\drivers\berniw2\1\dirt-4.xml copy .\src\drivers\berniw2\1\dirt-4.xml .\runtimed\drivers\berniw2\1\dirt-4.xml
if exist .\src\drivers\berniw2\1\dirt-5.xml copy .\src\drivers\berniw2\1\dirt-5.xml .\runtimed\drivers\berniw2\1\dirt-5.xml
if exist .\src\drivers\berniw2\1\dirt-6.xml copy .\src\drivers\berniw2\1\dirt-6.xml .\runtimed\drivers\berniw2\1\dirt-6.xml
if exist .\src\drivers\berniw2\1\eroad.xml copy .\src\drivers\berniw2\1\eroad.xml .\runtimed\drivers\berniw2\1\eroad.xml
if exist .\src\drivers\berniw2\1\e-track-1.xml copy .\src\drivers\berniw2\1\e-track-1.xml .\runtimed\drivers\berniw2\1\e-track-1.xml
if exist .\src\drivers\berniw2\1\e-track-2.xml copy .\src\drivers\berniw2\1\e-track-2.xml .\runtimed\drivers\berniw2\1\e-track-2.xml
if exist .\src\drivers\berniw2\1\e-track-3.xml copy .\src\drivers\berniw2\1\e-track-3.xml .\runtimed\drivers\berniw2\1\e-track-3.xml
if exist .\src\drivers\berniw2\1\e-track-4.xml copy .\src\drivers\berniw2\1\e-track-4.xml .\runtimed\drivers\berniw2\1\e-track-4.xml
if exist .\src\drivers\berniw2\1\e-track-5.xml copy .\src\drivers\berniw2\1\e-track-5.xml .\runtimed\drivers\berniw2\1\e-track-5.xml
if exist .\src\drivers\berniw2\1\e-track-6.xml copy .\src\drivers\berniw2\1\e-track-6.xml .\runtimed\drivers\berniw2\1\e-track-6.xml
if exist .\src\drivers\berniw2\1\g-track-1.xml copy .\src\drivers\berniw2\1\g-track-1.xml .\runtimed\drivers\berniw2\1\g-track-1.xml
if exist .\src\drivers\berniw2\1\g-track-2.xml copy .\src\drivers\berniw2\1\g-track-2.xml .\runtimed\drivers\berniw2\1\g-track-2.xml
if exist .\src\drivers\berniw2\1\g-track-3.xml copy .\src\drivers\berniw2\1\g-track-3.xml .\runtimed\drivers\berniw2\1\g-track-3.xml
if exist .\src\drivers\berniw2\1\michigan.xml copy .\src\drivers\berniw2\1\michigan.xml .\runtimed\drivers\berniw2\1\michigan.xml
if exist .\src\drivers\berniw2\1\mixed-1.xml copy .\src\drivers\berniw2\1\mixed-1.xml .\runtimed\drivers\berniw2\1\mixed-1.xml
if exist .\src\drivers\berniw2\1\mixed-2.xml copy .\src\drivers\berniw2\1\mixed-2.xml .\runtimed\drivers\berniw2\1\mixed-2.xml
if exist .\src\drivers\berniw2\1\spring.xml copy .\src\drivers\berniw2\1\spring.xml .\runtimed\drivers\berniw2\1\spring.xml
if exist .\src\drivers\berniw2\1\wheel-1.xml copy .\src\drivers\berniw2\1\wheel-1.xml .\runtimed\drivers\berniw2\1\wheel-1.xml

if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtimed\drivers\berniw2\10
if exist .\src\drivers\berniw2\10\360-modena.rgb copy .\src\drivers\berniw2\10\360-modena.rgb .\runtimed\drivers\berniw2\10\360-modena.rgb
if exist .\src\drivers\berniw2\10\aalborg.xml copy .\src\drivers\berniw2\10\aalborg.xml .\runtimed\drivers\berniw2\10\aalborg.xml
if exist .\src\drivers\berniw2\10\alpine-1.xml copy .\src\drivers\berniw2\10\alpine-1.xml .\runtimed\drivers\berniw2\10\alpine-1.xml
if exist .\src\drivers\berniw2\10\a-speedway.xml copy .\src\drivers\berniw2\10\a-speedway.xml .\runtimed\drivers\berniw2\10\a-speedway.xml
if exist .\src\drivers\berniw2\10\default.xml copy .\src\drivers\berniw2\10\default.xml .\runtimed\drivers\berniw2\10\default.xml
if exist .\src\drivers\berniw2\10\dirt-1.xml copy .\src\drivers\berniw2\10\dirt-1.xml .\runtimed\drivers\berniw2\10\dirt-1.xml
if exist .\src\drivers\berniw2\10\dirt-2.xml copy .\src\drivers\berniw2\10\dirt-2.xml .\runtimed\drivers\berniw2\10\dirt-2.xml
if exist .\src\drivers\berniw2\10\dirt-3.xml copy .\src\drivers\berniw2\10\dirt-3.xml .\runtimed\drivers\berniw2\10\dirt-3.xml
if exist .\src\drivers\berniw2\10\dirt-4.xml copy .\src\drivers\berniw2\10\dirt-4.xml .\runtimed\drivers\berniw2\10\dirt-4.xml
if exist .\src\drivers\berniw2\10\dirt-5.xml copy .\src\drivers\berniw2\10\dirt-5.xml .\runtimed\drivers\berniw2\10\dirt-5.xml
if exist .\src\drivers\berniw2\10\dirt-6.xml copy .\src\drivers\berniw2\10\dirt-6.xml .\runtimed\drivers\berniw2\10\dirt-6.xml
if exist .\src\drivers\berniw2\10\eroad.xml copy .\src\drivers\berniw2\10\eroad.xml .\runtimed\drivers\berniw2\10\eroad.xml
if exist .\src\drivers\berniw2\10\e-track-1.xml copy .\src\drivers\berniw2\10\e-track-1.xml .\runtimed\drivers\berniw2\10\e-track-1.xml
if exist .\src\drivers\berniw2\10\e-track-2.xml copy .\src\drivers\berniw2\10\e-track-2.xml .\runtimed\drivers\berniw2\10\e-track-2.xml
if exist .\src\drivers\berniw2\10\e-track-3.xml copy .\src\drivers\berniw2\10\e-track-3.xml .\runtimed\drivers\berniw2\10\e-track-3.xml
if exist .\src\drivers\berniw2\10\e-track-4.xml copy .\src\drivers\berniw2\10\e-track-4.xml .\runtimed\drivers\berniw2\10\e-track-4.xml
if exist .\src\drivers\berniw2\10\e-track-5.xml copy .\src\drivers\berniw2\10\e-track-5.xml .\runtimed\drivers\berniw2\10\e-track-5.xml
if exist .\src\drivers\berniw2\10\e-track-6.xml copy .\src\drivers\berniw2\10\e-track-6.xml .\runtimed\drivers\berniw2\10\e-track-6.xml
if exist .\src\drivers\berniw2\10\g-track-1.xml copy .\src\drivers\berniw2\10\g-track-1.xml .\runtimed\drivers\berniw2\10\g-track-1.xml
if exist .\src\drivers\berniw2\10\g-track-2.xml copy .\src\drivers\berniw2\10\g-track-2.xml .\runtimed\drivers\berniw2\10\g-track-2.xml
if exist .\src\drivers\berniw2\10\g-track-3.xml copy .\src\drivers\berniw2\10\g-track-3.xml .\runtimed\drivers\berniw2\10\g-track-3.xml
if exist .\src\drivers\berniw2\10\michigan.xml copy .\src\drivers\berniw2\10\michigan.xml .\runtimed\drivers\berniw2\10\michigan.xml
if exist .\src\drivers\berniw2\10\mixed-1.xml copy .\src\drivers\berniw2\10\mixed-1.xml .\runtimed\drivers\berniw2\10\mixed-1.xml
if exist .\src\drivers\berniw2\10\mixed-2.xml copy .\src\drivers\berniw2\10\mixed-2.xml .\runtimed\drivers\berniw2\10\mixed-2.xml
if exist .\src\drivers\berniw2\10\spring.xml copy .\src\drivers\berniw2\10\spring.xml .\runtimed\drivers\berniw2\10\spring.xml
if exist .\src\drivers\berniw2\10\wheel-1.xml copy .\src\drivers\berniw2\10\wheel-1.xml .\runtimed\drivers\berniw2\10\wheel-1.xml

if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtimed\drivers\berniw2\2
if exist .\src\drivers\berniw2\2\aalborg.xml copy .\src\drivers\berniw2\2\aalborg.xml .\runtimed\drivers\berniw2\2\aalborg.xml
if exist .\src\drivers\berniw2\2\alpine-1.xml copy .\src\drivers\berniw2\2\alpine-1.xml .\runtimed\drivers\berniw2\2\alpine-1.xml
if exist .\src\drivers\berniw2\2\a-speedway.xml copy .\src\drivers\berniw2\2\a-speedway.xml .\runtimed\drivers\berniw2\2\a-speedway.xml
if exist .\src\drivers\berniw2\2\default.xml copy .\src\drivers\berniw2\2\default.xml .\runtimed\drivers\berniw2\2\default.xml
if exist .\src\drivers\berniw2\2\dirt-1.xml copy .\src\drivers\berniw2\2\dirt-1.xml .\runtimed\drivers\berniw2\2\dirt-1.xml
if exist .\src\drivers\berniw2\2\dirt-2.xml copy .\src\drivers\berniw2\2\dirt-2.xml .\runtimed\drivers\berniw2\2\dirt-2.xml
if exist .\src\drivers\berniw2\2\dirt-3.xml copy .\src\drivers\berniw2\2\dirt-3.xml .\runtimed\drivers\berniw2\2\dirt-3.xml
if exist .\src\drivers\berniw2\2\dirt-4.xml copy .\src\drivers\berniw2\2\dirt-4.xml .\runtimed\drivers\berniw2\2\dirt-4.xml
if exist .\src\drivers\berniw2\2\dirt-5.xml copy .\src\drivers\berniw2\2\dirt-5.xml .\runtimed\drivers\berniw2\2\dirt-5.xml
if exist .\src\drivers\berniw2\2\dirt-6.xml copy .\src\drivers\berniw2\2\dirt-6.xml .\runtimed\drivers\berniw2\2\dirt-6.xml
if exist .\src\drivers\berniw2\2\eroad.xml copy .\src\drivers\berniw2\2\eroad.xml .\runtimed\drivers\berniw2\2\eroad.xml
if exist .\src\drivers\berniw2\2\e-track-1.xml copy .\src\drivers\berniw2\2\e-track-1.xml .\runtimed\drivers\berniw2\2\e-track-1.xml
if exist .\src\drivers\berniw2\2\e-track-2.xml copy .\src\drivers\berniw2\2\e-track-2.xml .\runtimed\drivers\berniw2\2\e-track-2.xml
if exist .\src\drivers\berniw2\2\e-track-3.xml copy .\src\drivers\berniw2\2\e-track-3.xml .\runtimed\drivers\berniw2\2\e-track-3.xml
if exist .\src\drivers\berniw2\2\e-track-4.xml copy .\src\drivers\berniw2\2\e-track-4.xml .\runtimed\drivers\berniw2\2\e-track-4.xml
if exist .\src\drivers\berniw2\2\e-track-5.xml copy .\src\drivers\berniw2\2\e-track-5.xml .\runtimed\drivers\berniw2\2\e-track-5.xml
if exist .\src\drivers\berniw2\2\e-track-6.xml copy .\src\drivers\berniw2\2\e-track-6.xml .\runtimed\drivers\berniw2\2\e-track-6.xml
if exist .\src\drivers\berniw2\2\g-track-1.xml copy .\src\drivers\berniw2\2\g-track-1.xml .\runtimed\drivers\berniw2\2\g-track-1.xml
if exist .\src\drivers\berniw2\2\g-track-2.xml copy .\src\drivers\berniw2\2\g-track-2.xml .\runtimed\drivers\berniw2\2\g-track-2.xml
if exist .\src\drivers\berniw2\2\g-track-3.xml copy .\src\drivers\berniw2\2\g-track-3.xml .\runtimed\drivers\berniw2\2\g-track-3.xml
if exist .\src\drivers\berniw2\2\michigan.xml copy .\src\drivers\berniw2\2\michigan.xml .\runtimed\drivers\berniw2\2\michigan.xml
if exist .\src\drivers\berniw2\2\mixed-1.xml copy .\src\drivers\berniw2\2\mixed-1.xml .\runtimed\drivers\berniw2\2\mixed-1.xml
if exist .\src\drivers\berniw2\2\mixed-2.xml copy .\src\drivers\berniw2\2\mixed-2.xml .\runtimed\drivers\berniw2\2\mixed-2.xml
if exist .\src\drivers\berniw2\2\spring.xml copy .\src\drivers\berniw2\2\spring.xml .\runtimed\drivers\berniw2\2\spring.xml
if exist .\src\drivers\berniw2\2\wheel-1.xml copy .\src\drivers\berniw2\2\wheel-1.xml .\runtimed\drivers\berniw2\2\wheel-1.xml

if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtimed\drivers\berniw2\3
if exist .\src\drivers\berniw2\3\aalborg.xml copy .\src\drivers\berniw2\3\aalborg.xml .\runtimed\drivers\berniw2\3\aalborg.xml
if exist .\src\drivers\berniw2\3\alpine-1.xml copy .\src\drivers\berniw2\3\alpine-1.xml .\runtimed\drivers\berniw2\3\alpine-1.xml
if exist .\src\drivers\berniw2\3\a-speedway.xml copy .\src\drivers\berniw2\3\a-speedway.xml .\runtimed\drivers\berniw2\3\a-speedway.xml
if exist .\src\drivers\berniw2\3\default.xml copy .\src\drivers\berniw2\3\default.xml .\runtimed\drivers\berniw2\3\default.xml
if exist .\src\drivers\berniw2\3\dirt-1.xml copy .\src\drivers\berniw2\3\dirt-1.xml .\runtimed\drivers\berniw2\3\dirt-1.xml
if exist .\src\drivers\berniw2\3\dirt-2.xml copy .\src\drivers\berniw2\3\dirt-2.xml .\runtimed\drivers\berniw2\3\dirt-2.xml
if exist .\src\drivers\berniw2\3\dirt-3.xml copy .\src\drivers\berniw2\3\dirt-3.xml .\runtimed\drivers\berniw2\3\dirt-3.xml
if exist .\src\drivers\berniw2\3\dirt-4.xml copy .\src\drivers\berniw2\3\dirt-4.xml .\runtimed\drivers\berniw2\3\dirt-4.xml
if exist .\src\drivers\berniw2\3\dirt-5.xml copy .\src\drivers\berniw2\3\dirt-5.xml .\runtimed\drivers\berniw2\3\dirt-5.xml
if exist .\src\drivers\berniw2\3\dirt-6.xml copy .\src\drivers\berniw2\3\dirt-6.xml .\runtimed\drivers\berniw2\3\dirt-6.xml
if exist .\src\drivers\berniw2\3\eroad.xml copy .\src\drivers\berniw2\3\eroad.xml .\runtimed\drivers\berniw2\3\eroad.xml
if exist .\src\drivers\berniw2\3\e-track-1.xml copy .\src\drivers\berniw2\3\e-track-1.xml .\runtimed\drivers\berniw2\3\e-track-1.xml
if exist .\src\drivers\berniw2\3\e-track-2.xml copy .\src\drivers\berniw2\3\e-track-2.xml .\runtimed\drivers\berniw2\3\e-track-2.xml
if exist .\src\drivers\berniw2\3\e-track-3.xml copy .\src\drivers\berniw2\3\e-track-3.xml .\runtimed\drivers\berniw2\3\e-track-3.xml
if exist .\src\drivers\berniw2\3\e-track-4.xml copy .\src\drivers\berniw2\3\e-track-4.xml .\runtimed\drivers\berniw2\3\e-track-4.xml
if exist .\src\drivers\berniw2\3\e-track-5.xml copy .\src\drivers\berniw2\3\e-track-5.xml .\runtimed\drivers\berniw2\3\e-track-5.xml
if exist .\src\drivers\berniw2\3\e-track-6.xml copy .\src\drivers\berniw2\3\e-track-6.xml .\runtimed\drivers\berniw2\3\e-track-6.xml
if exist .\src\drivers\berniw2\3\g-track-1.xml copy .\src\drivers\berniw2\3\g-track-1.xml .\runtimed\drivers\berniw2\3\g-track-1.xml
if exist .\src\drivers\berniw2\3\g-track-2.xml copy .\src\drivers\berniw2\3\g-track-2.xml .\runtimed\drivers\berniw2\3\g-track-2.xml
if exist .\src\drivers\berniw2\3\g-track-3.xml copy .\src\drivers\berniw2\3\g-track-3.xml .\runtimed\drivers\berniw2\3\g-track-3.xml
if exist .\src\drivers\berniw2\3\michigan.xml copy .\src\drivers\berniw2\3\michigan.xml .\runtimed\drivers\berniw2\3\michigan.xml
if exist .\src\drivers\berniw2\3\mixed-1.xml copy .\src\drivers\berniw2\3\mixed-1.xml .\runtimed\drivers\berniw2\3\mixed-1.xml
if exist .\src\drivers\berniw2\3\mixed-2.xml copy .\src\drivers\berniw2\3\mixed-2.xml .\runtimed\drivers\berniw2\3\mixed-2.xml
if exist .\src\drivers\berniw2\3\spring.xml copy .\src\drivers\berniw2\3\spring.xml .\runtimed\drivers\berniw2\3\spring.xml
if exist .\src\drivers\berniw2\3\wheel-1.xml copy .\src\drivers\berniw2\3\wheel-1.xml .\runtimed\drivers\berniw2\3\wheel-1.xml

if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtimed\drivers\berniw2\4
if exist .\src\drivers\berniw2\4\aalborg.xml copy .\src\drivers\berniw2\4\aalborg.xml .\runtimed\drivers\berniw2\4\aalborg.xml
if exist .\src\drivers\berniw2\4\alpine-1.xml copy .\src\drivers\berniw2\4\alpine-1.xml .\runtimed\drivers\berniw2\4\alpine-1.xml
if exist .\src\drivers\berniw2\4\a-speedway.xml copy .\src\drivers\berniw2\4\a-speedway.xml .\runtimed\drivers\berniw2\4\a-speedway.xml
if exist .\src\drivers\berniw2\4\default.xml copy .\src\drivers\berniw2\4\default.xml .\runtimed\drivers\berniw2\4\default.xml
if exist .\src\drivers\berniw2\4\dirt-1.xml copy .\src\drivers\berniw2\4\dirt-1.xml .\runtimed\drivers\berniw2\4\dirt-1.xml
if exist .\src\drivers\berniw2\4\dirt-2.xml copy .\src\drivers\berniw2\4\dirt-2.xml .\runtimed\drivers\berniw2\4\dirt-2.xml
if exist .\src\drivers\berniw2\4\dirt-3.xml copy .\src\drivers\berniw2\4\dirt-3.xml .\runtimed\drivers\berniw2\4\dirt-3.xml
if exist .\src\drivers\berniw2\4\dirt-4.xml copy .\src\drivers\berniw2\4\dirt-4.xml .\runtimed\drivers\berniw2\4\dirt-4.xml
if exist .\src\drivers\berniw2\4\dirt-5.xml copy .\src\drivers\berniw2\4\dirt-5.xml .\runtimed\drivers\berniw2\4\dirt-5.xml
if exist .\src\drivers\berniw2\4\dirt-6.xml copy .\src\drivers\berniw2\4\dirt-6.xml .\runtimed\drivers\berniw2\4\dirt-6.xml
if exist .\src\drivers\berniw2\4\eroad.xml copy .\src\drivers\berniw2\4\eroad.xml .\runtimed\drivers\berniw2\4\eroad.xml
if exist .\src\drivers\berniw2\4\e-track-1.xml copy .\src\drivers\berniw2\4\e-track-1.xml .\runtimed\drivers\berniw2\4\e-track-1.xml
if exist .\src\drivers\berniw2\4\e-track-2.xml copy .\src\drivers\berniw2\4\e-track-2.xml .\runtimed\drivers\berniw2\4\e-track-2.xml
if exist .\src\drivers\berniw2\4\e-track-3.xml copy .\src\drivers\berniw2\4\e-track-3.xml .\runtimed\drivers\berniw2\4\e-track-3.xml
if exist .\src\drivers\berniw2\4\e-track-4.xml copy .\src\drivers\berniw2\4\e-track-4.xml .\runtimed\drivers\berniw2\4\e-track-4.xml
if exist .\src\drivers\berniw2\4\e-track-5.xml copy .\src\drivers\berniw2\4\e-track-5.xml .\runtimed\drivers\berniw2\4\e-track-5.xml
if exist .\src\drivers\berniw2\4\e-track-6.xml copy .\src\drivers\berniw2\4\e-track-6.xml .\runtimed\drivers\berniw2\4\e-track-6.xml
if exist .\src\drivers\berniw2\4\g-track-1.xml copy .\src\drivers\berniw2\4\g-track-1.xml .\runtimed\drivers\berniw2\4\g-track-1.xml
if exist .\src\drivers\berniw2\4\g-track-2.xml copy .\src\drivers\berniw2\4\g-track-2.xml .\runtimed\drivers\berniw2\4\g-track-2.xml
if exist .\src\drivers\berniw2\4\g-track-3.xml copy .\src\drivers\berniw2\4\g-track-3.xml .\runtimed\drivers\berniw2\4\g-track-3.xml
if exist .\src\drivers\berniw2\4\michigan.xml copy .\src\drivers\berniw2\4\michigan.xml .\runtimed\drivers\berniw2\4\michigan.xml
if exist .\src\drivers\berniw2\4\mixed-1.xml copy .\src\drivers\berniw2\4\mixed-1.xml .\runtimed\drivers\berniw2\4\mixed-1.xml
if exist .\src\drivers\berniw2\4\mixed-2.xml copy .\src\drivers\berniw2\4\mixed-2.xml .\runtimed\drivers\berniw2\4\mixed-2.xml
if exist .\src\drivers\berniw2\4\spring.xml copy .\src\drivers\berniw2\4\spring.xml .\runtimed\drivers\berniw2\4\spring.xml
if exist .\src\drivers\berniw2\4\wheel-1.xml copy .\src\drivers\berniw2\4\wheel-1.xml .\runtimed\drivers\berniw2\4\wheel-1.xml

if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtimed\drivers\berniw2\5
if exist .\src\drivers\berniw2\5\aalborg.xml copy .\src\drivers\berniw2\5\aalborg.xml .\runtimed\drivers\berniw2\5\aalborg.xml
if exist .\src\drivers\berniw2\5\alpine-1.xml copy .\src\drivers\berniw2\5\alpine-1.xml .\runtimed\drivers\berniw2\5\alpine-1.xml
if exist .\src\drivers\berniw2\5\a-speedway.xml copy .\src\drivers\berniw2\5\a-speedway.xml .\runtimed\drivers\berniw2\5\a-speedway.xml
if exist .\src\drivers\berniw2\5\default.xml copy .\src\drivers\berniw2\5\default.xml .\runtimed\drivers\berniw2\5\default.xml
if exist .\src\drivers\berniw2\5\dirt-1.xml copy .\src\drivers\berniw2\5\dirt-1.xml .\runtimed\drivers\berniw2\5\dirt-1.xml
if exist .\src\drivers\berniw2\5\dirt-2.xml copy .\src\drivers\berniw2\5\dirt-2.xml .\runtimed\drivers\berniw2\5\dirt-2.xml
if exist .\src\drivers\berniw2\5\dirt-3.xml copy .\src\drivers\berniw2\5\dirt-3.xml .\runtimed\drivers\berniw2\5\dirt-3.xml
if exist .\src\drivers\berniw2\5\dirt-4.xml copy .\src\drivers\berniw2\5\dirt-4.xml .\runtimed\drivers\berniw2\5\dirt-4.xml
if exist .\src\drivers\berniw2\5\dirt-5.xml copy .\src\drivers\berniw2\5\dirt-5.xml .\runtimed\drivers\berniw2\5\dirt-5.xml
if exist .\src\drivers\berniw2\5\dirt-6.xml copy .\src\drivers\berniw2\5\dirt-6.xml .\runtimed\drivers\berniw2\5\dirt-6.xml
if exist .\src\drivers\berniw2\5\eroad.xml copy .\src\drivers\berniw2\5\eroad.xml .\runtimed\drivers\berniw2\5\eroad.xml
if exist .\src\drivers\berniw2\5\e-track-1.xml copy .\src\drivers\berniw2\5\e-track-1.xml .\runtimed\drivers\berniw2\5\e-track-1.xml
if exist .\src\drivers\berniw2\5\e-track-2.xml copy .\src\drivers\berniw2\5\e-track-2.xml .\runtimed\drivers\berniw2\5\e-track-2.xml
if exist .\src\drivers\berniw2\5\e-track-3.xml copy .\src\drivers\berniw2\5\e-track-3.xml .\runtimed\drivers\berniw2\5\e-track-3.xml
if exist .\src\drivers\berniw2\5\e-track-4.xml copy .\src\drivers\berniw2\5\e-track-4.xml .\runtimed\drivers\berniw2\5\e-track-4.xml
if exist .\src\drivers\berniw2\5\e-track-5.xml copy .\src\drivers\berniw2\5\e-track-5.xml .\runtimed\drivers\berniw2\5\e-track-5.xml
if exist .\src\drivers\berniw2\5\e-track-6.xml copy .\src\drivers\berniw2\5\e-track-6.xml .\runtimed\drivers\berniw2\5\e-track-6.xml
if exist .\src\drivers\berniw2\5\g-track-1.xml copy .\src\drivers\berniw2\5\g-track-1.xml .\runtimed\drivers\berniw2\5\g-track-1.xml
if exist .\src\drivers\berniw2\5\g-track-2.xml copy .\src\drivers\berniw2\5\g-track-2.xml .\runtimed\drivers\berniw2\5\g-track-2.xml
if exist .\src\drivers\berniw2\5\g-track-3.xml copy .\src\drivers\berniw2\5\g-track-3.xml .\runtimed\drivers\berniw2\5\g-track-3.xml
if exist .\src\drivers\berniw2\5\michigan.xml copy .\src\drivers\berniw2\5\michigan.xml .\runtimed\drivers\berniw2\5\michigan.xml
if exist .\src\drivers\berniw2\5\mixed-1.xml copy .\src\drivers\berniw2\5\mixed-1.xml .\runtimed\drivers\berniw2\5\mixed-1.xml
if exist .\src\drivers\berniw2\5\mixed-2.xml copy .\src\drivers\berniw2\5\mixed-2.xml .\runtimed\drivers\berniw2\5\mixed-2.xml
if exist .\src\drivers\berniw2\5\spring.xml copy .\src\drivers\berniw2\5\spring.xml .\runtimed\drivers\berniw2\5\spring.xml
if exist .\src\drivers\berniw2\5\wheel-1.xml copy .\src\drivers\berniw2\5\wheel-1.xml .\runtimed\drivers\berniw2\5\wheel-1.xml

if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtimed\drivers\berniw2\6
if exist .\src\drivers\berniw2\6\aalborg.xml copy .\src\drivers\berniw2\6\aalborg.xml .\runtimed\drivers\berniw2\6\aalborg.xml
if exist .\src\drivers\berniw2\6\alpine-1.xml copy .\src\drivers\berniw2\6\alpine-1.xml .\runtimed\drivers\berniw2\6\alpine-1.xml
if exist .\src\drivers\berniw2\6\a-speedway.xml copy .\src\drivers\berniw2\6\a-speedway.xml .\runtimed\drivers\berniw2\6\a-speedway.xml
if exist .\src\drivers\berniw2\6\default.xml copy .\src\drivers\berniw2\6\default.xml .\runtimed\drivers\berniw2\6\default.xml
if exist .\src\drivers\berniw2\6\dirt-1.xml copy .\src\drivers\berniw2\6\dirt-1.xml .\runtimed\drivers\berniw2\6\dirt-1.xml
if exist .\src\drivers\berniw2\6\dirt-2.xml copy .\src\drivers\berniw2\6\dirt-2.xml .\runtimed\drivers\berniw2\6\dirt-2.xml
if exist .\src\drivers\berniw2\6\dirt-3.xml copy .\src\drivers\berniw2\6\dirt-3.xml .\runtimed\drivers\berniw2\6\dirt-3.xml
if exist .\src\drivers\berniw2\6\dirt-4.xml copy .\src\drivers\berniw2\6\dirt-4.xml .\runtimed\drivers\berniw2\6\dirt-4.xml
if exist .\src\drivers\berniw2\6\dirt-5.xml copy .\src\drivers\berniw2\6\dirt-5.xml .\runtimed\drivers\berniw2\6\dirt-5.xml
if exist .\src\drivers\berniw2\6\dirt-6.xml copy .\src\drivers\berniw2\6\dirt-6.xml .\runtimed\drivers\berniw2\6\dirt-6.xml
if exist .\src\drivers\berniw2\6\eroad.xml copy .\src\drivers\berniw2\6\eroad.xml .\runtimed\drivers\berniw2\6\eroad.xml
if exist .\src\drivers\berniw2\6\e-track-1.xml copy .\src\drivers\berniw2\6\e-track-1.xml .\runtimed\drivers\berniw2\6\e-track-1.xml
if exist .\src\drivers\berniw2\6\e-track-2.xml copy .\src\drivers\berniw2\6\e-track-2.xml .\runtimed\drivers\berniw2\6\e-track-2.xml
if exist .\src\drivers\berniw2\6\e-track-3.xml copy .\src\drivers\berniw2\6\e-track-3.xml .\runtimed\drivers\berniw2\6\e-track-3.xml
if exist .\src\drivers\berniw2\6\e-track-4.xml copy .\src\drivers\berniw2\6\e-track-4.xml .\runtimed\drivers\berniw2\6\e-track-4.xml
if exist .\src\drivers\berniw2\6\e-track-5.xml copy .\src\drivers\berniw2\6\e-track-5.xml .\runtimed\drivers\berniw2\6\e-track-5.xml
if exist .\src\drivers\berniw2\6\e-track-6.xml copy .\src\drivers\berniw2\6\e-track-6.xml .\runtimed\drivers\berniw2\6\e-track-6.xml
if exist .\src\drivers\berniw2\6\g-track-1.xml copy .\src\drivers\berniw2\6\g-track-1.xml .\runtimed\drivers\berniw2\6\g-track-1.xml
if exist .\src\drivers\berniw2\6\g-track-2.xml copy .\src\drivers\berniw2\6\g-track-2.xml .\runtimed\drivers\berniw2\6\g-track-2.xml
if exist .\src\drivers\berniw2\6\g-track-3.xml copy .\src\drivers\berniw2\6\g-track-3.xml .\runtimed\drivers\berniw2\6\g-track-3.xml
if exist .\src\drivers\berniw2\6\michigan.xml copy .\src\drivers\berniw2\6\michigan.xml .\runtimed\drivers\berniw2\6\michigan.xml
if exist .\src\drivers\berniw2\6\mixed-1.xml copy .\src\drivers\berniw2\6\mixed-1.xml .\runtimed\drivers\berniw2\6\mixed-1.xml
if exist .\src\drivers\berniw2\6\mixed-2.xml copy .\src\drivers\berniw2\6\mixed-2.xml .\runtimed\drivers\berniw2\6\mixed-2.xml
if exist .\src\drivers\berniw2\6\spring.xml copy .\src\drivers\berniw2\6\spring.xml .\runtimed\drivers\berniw2\6\spring.xml
if exist .\src\drivers\berniw2\6\wheel-1.xml copy .\src\drivers\berniw2\6\wheel-1.xml .\runtimed\drivers\berniw2\6\wheel-1.xml

if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtimed\drivers\berniw2\7
if exist .\src\drivers\berniw2\7\porsche-gt3rs.rgb copy .\src\drivers\berniw2\7\porsche-gt3rs.rgb .\runtimed\drivers\berniw2\7\porsche-gt3rs.rgb
if exist .\src\drivers\berniw2\7\aalborg.xml copy .\src\drivers\berniw2\7\aalborg.xml .\runtimed\drivers\berniw2\7\aalborg.xml
if exist .\src\drivers\berniw2\7\alpine-1.xml copy .\src\drivers\berniw2\7\alpine-1.xml .\runtimed\drivers\berniw2\7\alpine-1.xml
if exist .\src\drivers\berniw2\7\a-speedway.xml copy .\src\drivers\berniw2\7\a-speedway.xml .\runtimed\drivers\berniw2\7\a-speedway.xml
if exist .\src\drivers\berniw2\7\default.xml copy .\src\drivers\berniw2\7\default.xml .\runtimed\drivers\berniw2\7\default.xml
if exist .\src\drivers\berniw2\7\dirt-1.xml copy .\src\drivers\berniw2\7\dirt-1.xml .\runtimed\drivers\berniw2\7\dirt-1.xml
if exist .\src\drivers\berniw2\7\dirt-2.xml copy .\src\drivers\berniw2\7\dirt-2.xml .\runtimed\drivers\berniw2\7\dirt-2.xml
if exist .\src\drivers\berniw2\7\dirt-3.xml copy .\src\drivers\berniw2\7\dirt-3.xml .\runtimed\drivers\berniw2\7\dirt-3.xml
if exist .\src\drivers\berniw2\7\dirt-4.xml copy .\src\drivers\berniw2\7\dirt-4.xml .\runtimed\drivers\berniw2\7\dirt-4.xml
if exist .\src\drivers\berniw2\7\dirt-5.xml copy .\src\drivers\berniw2\7\dirt-5.xml .\runtimed\drivers\berniw2\7\dirt-5.xml
if exist .\src\drivers\berniw2\7\dirt-6.xml copy .\src\drivers\berniw2\7\dirt-6.xml .\runtimed\drivers\berniw2\7\dirt-6.xml
if exist .\src\drivers\berniw2\7\eroad.xml copy .\src\drivers\berniw2\7\eroad.xml .\runtimed\drivers\berniw2\7\eroad.xml
if exist .\src\drivers\berniw2\7\e-track-1.xml copy .\src\drivers\berniw2\7\e-track-1.xml .\runtimed\drivers\berniw2\7\e-track-1.xml
if exist .\src\drivers\berniw2\7\e-track-2.xml copy .\src\drivers\berniw2\7\e-track-2.xml .\runtimed\drivers\berniw2\7\e-track-2.xml
if exist .\src\drivers\berniw2\7\e-track-3.xml copy .\src\drivers\berniw2\7\e-track-3.xml .\runtimed\drivers\berniw2\7\e-track-3.xml
if exist .\src\drivers\berniw2\7\e-track-4.xml copy .\src\drivers\berniw2\7\e-track-4.xml .\runtimed\drivers\berniw2\7\e-track-4.xml
if exist .\src\drivers\berniw2\7\e-track-5.xml copy .\src\drivers\berniw2\7\e-track-5.xml .\runtimed\drivers\berniw2\7\e-track-5.xml
if exist .\src\drivers\berniw2\7\e-track-6.xml copy .\src\drivers\berniw2\7\e-track-6.xml .\runtimed\drivers\berniw2\7\e-track-6.xml
if exist .\src\drivers\berniw2\7\g-track-1.xml copy .\src\drivers\berniw2\7\g-track-1.xml .\runtimed\drivers\berniw2\7\g-track-1.xml
if exist .\src\drivers\berniw2\7\g-track-2.xml copy .\src\drivers\berniw2\7\g-track-2.xml .\runtimed\drivers\berniw2\7\g-track-2.xml
if exist .\src\drivers\berniw2\7\g-track-3.xml copy .\src\drivers\berniw2\7\g-track-3.xml .\runtimed\drivers\berniw2\7\g-track-3.xml
if exist .\src\drivers\berniw2\7\michigan.xml copy .\src\drivers\berniw2\7\michigan.xml .\runtimed\drivers\berniw2\7\michigan.xml
if exist .\src\drivers\berniw2\7\mixed-1.xml copy .\src\drivers\berniw2\7\mixed-1.xml .\runtimed\drivers\berniw2\7\mixed-1.xml
if exist .\src\drivers\berniw2\7\mixed-2.xml copy .\src\drivers\berniw2\7\mixed-2.xml .\runtimed\drivers\berniw2\7\mixed-2.xml
if exist .\src\drivers\berniw2\7\spring.xml copy .\src\drivers\berniw2\7\spring.xml .\runtimed\drivers\berniw2\7\spring.xml
if exist .\src\drivers\berniw2\7\wheel-1.xml copy .\src\drivers\berniw2\7\wheel-1.xml .\runtimed\drivers\berniw2\7\wheel-1.xml

if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtimed\drivers\berniw2\8
if exist .\src\drivers\berniw2\8\clkdtm.rgb copy .\src\drivers\berniw2\8\clkdtm.rgb .\runtimed\drivers\berniw2\8\clkdtm.rgb
if exist .\src\drivers\berniw2\8\aalborg.xml copy .\src\drivers\berniw2\8\aalborg.xml .\runtimed\drivers\berniw2\8\aalborg.xml
if exist .\src\drivers\berniw2\8\alpine-1.xml copy .\src\drivers\berniw2\8\alpine-1.xml .\runtimed\drivers\berniw2\8\alpine-1.xml
if exist .\src\drivers\berniw2\8\a-speedway.xml copy .\src\drivers\berniw2\8\a-speedway.xml .\runtimed\drivers\berniw2\8\a-speedway.xml
if exist .\src\drivers\berniw2\8\default.xml copy .\src\drivers\berniw2\8\default.xml .\runtimed\drivers\berniw2\8\default.xml
if exist .\src\drivers\berniw2\8\dirt-1.xml copy .\src\drivers\berniw2\8\dirt-1.xml .\runtimed\drivers\berniw2\8\dirt-1.xml
if exist .\src\drivers\berniw2\8\dirt-2.xml copy .\src\drivers\berniw2\8\dirt-2.xml .\runtimed\drivers\berniw2\8\dirt-2.xml
if exist .\src\drivers\berniw2\8\dirt-3.xml copy .\src\drivers\berniw2\8\dirt-3.xml .\runtimed\drivers\berniw2\8\dirt-3.xml
if exist .\src\drivers\berniw2\8\dirt-4.xml copy .\src\drivers\berniw2\8\dirt-4.xml .\runtimed\drivers\berniw2\8\dirt-4.xml
if exist .\src\drivers\berniw2\8\dirt-5.xml copy .\src\drivers\berniw2\8\dirt-5.xml .\runtimed\drivers\berniw2\8\dirt-5.xml
if exist .\src\drivers\berniw2\8\dirt-6.xml copy .\src\drivers\berniw2\8\dirt-6.xml .\runtimed\drivers\berniw2\8\dirt-6.xml
if exist .\src\drivers\berniw2\8\eroad.xml copy .\src\drivers\berniw2\8\eroad.xml .\runtimed\drivers\berniw2\8\eroad.xml
if exist .\src\drivers\berniw2\8\e-track-1.xml copy .\src\drivers\berniw2\8\e-track-1.xml .\runtimed\drivers\berniw2\8\e-track-1.xml
if exist .\src\drivers\berniw2\8\e-track-2.xml copy .\src\drivers\berniw2\8\e-track-2.xml .\runtimed\drivers\berniw2\8\e-track-2.xml
if exist .\src\drivers\berniw2\8\e-track-3.xml copy .\src\drivers\berniw2\8\e-track-3.xml .\runtimed\drivers\berniw2\8\e-track-3.xml
if exist .\src\drivers\berniw2\8\e-track-4.xml copy .\src\drivers\berniw2\8\e-track-4.xml .\runtimed\drivers\berniw2\8\e-track-4.xml
if exist .\src\drivers\berniw2\8\e-track-5.xml copy .\src\drivers\berniw2\8\e-track-5.xml .\runtimed\drivers\berniw2\8\e-track-5.xml
if exist .\src\drivers\berniw2\8\e-track-6.xml copy .\src\drivers\berniw2\8\e-track-6.xml .\runtimed\drivers\berniw2\8\e-track-6.xml
if exist .\src\drivers\berniw2\8\g-track-1.xml copy .\src\drivers\berniw2\8\g-track-1.xml .\runtimed\drivers\berniw2\8\g-track-1.xml
if exist .\src\drivers\berniw2\8\g-track-2.xml copy .\src\drivers\berniw2\8\g-track-2.xml .\runtimed\drivers\berniw2\8\g-track-2.xml
if exist .\src\drivers\berniw2\8\g-track-3.xml copy .\src\drivers\berniw2\8\g-track-3.xml .\runtimed\drivers\berniw2\8\g-track-3.xml
if exist .\src\drivers\berniw2\8\michigan.xml copy .\src\drivers\berniw2\8\michigan.xml .\runtimed\drivers\berniw2\8\michigan.xml
if exist .\src\drivers\berniw2\8\mixed-1.xml copy .\src\drivers\berniw2\8\mixed-1.xml .\runtimed\drivers\berniw2\8\mixed-1.xml
if exist .\src\drivers\berniw2\8\mixed-2.xml copy .\src\drivers\berniw2\8\mixed-2.xml .\runtimed\drivers\berniw2\8\mixed-2.xml
if exist .\src\drivers\berniw2\8\spring.xml copy .\src\drivers\berniw2\8\spring.xml .\runtimed\drivers\berniw2\8\spring.xml
if exist .\src\drivers\berniw2\8\wheel-1.xml copy .\src\drivers\berniw2\8\wheel-1.xml .\runtimed\drivers\berniw2\8\wheel-1.xml

if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtimed\drivers\berniw2\9
if exist .\src\drivers\berniw2\9\mclaren-f1.rgb copy .\src\drivers\berniw2\9\mclaren-f1.rgb .\runtimed\drivers\berniw2\9\mclaren-f1.rgb
if exist .\src\drivers\berniw2\9\aalborg.xml copy .\src\drivers\berniw2\9\aalborg.xml .\runtimed\drivers\berniw2\9\aalborg.xml
if exist .\src\drivers\berniw2\9\alpine-1.xml copy .\src\drivers\berniw2\9\alpine-1.xml .\runtimed\drivers\berniw2\9\alpine-1.xml
if exist .\src\drivers\berniw2\9\a-speedway.xml copy .\src\drivers\berniw2\9\a-speedway.xml .\runtimed\drivers\berniw2\9\a-speedway.xml
if exist .\src\drivers\berniw2\9\default.xml copy .\src\drivers\berniw2\9\default.xml .\runtimed\drivers\berniw2\9\default.xml
if exist .\src\drivers\berniw2\9\dirt-1.xml copy .\src\drivers\berniw2\9\dirt-1.xml .\runtimed\drivers\berniw2\9\dirt-1.xml
if exist .\src\drivers\berniw2\9\dirt-2.xml copy .\src\drivers\berniw2\9\dirt-2.xml .\runtimed\drivers\berniw2\9\dirt-2.xml
if exist .\src\drivers\berniw2\9\dirt-3.xml copy .\src\drivers\berniw2\9\dirt-3.xml .\runtimed\drivers\berniw2\9\dirt-3.xml
if exist .\src\drivers\berniw2\9\dirt-4.xml copy .\src\drivers\berniw2\9\dirt-4.xml .\runtimed\drivers\berniw2\9\dirt-4.xml
if exist .\src\drivers\berniw2\9\dirt-5.xml copy .\src\drivers\berniw2\9\dirt-5.xml .\runtimed\drivers\berniw2\9\dirt-5.xml
if exist .\src\drivers\berniw2\9\dirt-6.xml copy .\src\drivers\berniw2\9\dirt-6.xml .\runtimed\drivers\berniw2\9\dirt-6.xml
if exist .\src\drivers\berniw2\9\eroad.xml copy .\src\drivers\berniw2\9\eroad.xml .\runtimed\drivers\berniw2\9\eroad.xml
if exist .\src\drivers\berniw2\9\e-track-1.xml copy .\src\drivers\berniw2\9\e-track-1.xml .\runtimed\drivers\berniw2\9\e-track-1.xml
if exist .\src\drivers\berniw2\9\e-track-2.xml copy .\src\drivers\berniw2\9\e-track-2.xml .\runtimed\drivers\berniw2\9\e-track-2.xml
if exist .\src\drivers\berniw2\9\e-track-3.xml copy .\src\drivers\berniw2\9\e-track-3.xml .\runtimed\drivers\berniw2\9\e-track-3.xml
if exist .\src\drivers\berniw2\9\e-track-4.xml copy .\src\drivers\berniw2\9\e-track-4.xml .\runtimed\drivers\berniw2\9\e-track-4.xml
if exist .\src\drivers\berniw2\9\e-track-5.xml copy .\src\drivers\berniw2\9\e-track-5.xml .\runtimed\drivers\berniw2\9\e-track-5.xml
if exist .\src\drivers\berniw2\9\e-track-6.xml copy .\src\drivers\berniw2\9\e-track-6.xml .\runtimed\drivers\berniw2\9\e-track-6.xml
if exist .\src\drivers\berniw2\9\g-track-1.xml copy .\src\drivers\berniw2\9\g-track-1.xml .\runtimed\drivers\berniw2\9\g-track-1.xml
if exist .\src\drivers\berniw2\9\g-track-2.xml copy .\src\drivers\berniw2\9\g-track-2.xml .\runtimed\drivers\berniw2\9\g-track-2.xml
if exist .\src\drivers\berniw2\9\g-track-3.xml copy .\src\drivers\berniw2\9\g-track-3.xml .\runtimed\drivers\berniw2\9\g-track-3.xml
if exist .\src\drivers\berniw2\9\michigan.xml copy .\src\drivers\berniw2\9\michigan.xml .\runtimed\drivers\berniw2\9\michigan.xml
if exist .\src\drivers\berniw2\9\mixed-1.xml copy .\src\drivers\berniw2\9\mixed-1.xml .\runtimed\drivers\berniw2\9\mixed-1.xml
if exist .\src\drivers\berniw2\9\mixed-2.xml copy .\src\drivers\berniw2\9\mixed-2.xml .\runtimed\drivers\berniw2\9\mixed-2.xml
if exist .\src\drivers\berniw2\9\spring.xml copy .\src\drivers\berniw2\9\spring.xml .\runtimed\drivers\berniw2\9\spring.xml
if exist .\src\drivers\berniw2\9\wheel-1.xml copy .\src\drivers\berniw2\9\wheel-1.xml .\runtimed\drivers\berniw2\9\wheel-1.xml

if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\berniw2.xml copy .\src\drivers\berniw2\berniw2.xml .\runtimed\drivers\berniw2\berniw2.xml
if exist .\src\drivers\berniw2\logo.rgb copy .\src\drivers\berniw2\logo.rgb .\runtimed\drivers\berniw2\logo.rgb
if exist .\src\drivers\berniw2\parameter.dat copy .\src\drivers\berniw2\parameter.dat .\runtimed\drivers\berniw2\parameter.dat
if exist .\src\drivers\berniw2\intsinsqr.dat copy .\src\drivers\berniw2\intsinsqr.dat .\runtimed\drivers\berniw2\intsinsqr.dat
if exist .\src\drivers\berniw2\intcossqr.dat copy .\src\drivers\berniw2\intcossqr.dat .\runtimed\drivers\berniw2\intcossqr.dat

if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtimed\drivers\berniw3
if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtimed\drivers\berniw3\1
if exist .\src\drivers\berniw3\1\default.xml copy .\src\drivers\berniw3\1\default.xml .\runtimed\drivers\berniw3\1\default.xml

if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtimed\drivers\berniw3
if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtimed\drivers\berniw3\10
if exist .\src\drivers\berniw3\10\default.xml copy .\src\drivers\berniw3\10\default.xml .\runtimed\drivers\berniw3\10\default.xml

if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtimed\drivers\berniw3
if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtimed\drivers\berniw3\2
if exist .\src\drivers\berniw3\2\default.xml copy .\src\drivers\berniw3\2\default.xml .\runtimed\drivers\berniw3\2\default.xml

if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtimed\drivers\berniw3
if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtimed\drivers\berniw3\3
if exist .\src\drivers\berniw3\3\default.xml copy .\src\drivers\berniw3\3\default.xml .\runtimed\drivers\berniw3\3\default.xml

if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtimed\drivers\berniw3
if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtimed\drivers\berniw3\4
if exist .\src\drivers\berniw3\4\default.xml copy .\src\drivers\berniw3\4\default.xml .\runtimed\drivers\berniw3\4\default.xml

if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtimed\drivers\berniw3
if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtimed\drivers\berniw3\5
if exist .\src\drivers\berniw3\5\default.xml copy .\src\drivers\berniw3\5\default.xml .\runtimed\drivers\berniw3\5\default.xml

if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtimed\drivers\berniw3
if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtimed\drivers\berniw3\6
if exist .\src\drivers\berniw3\6\default.xml copy .\src\drivers\berniw3\6\default.xml .\runtimed\drivers\berniw3\6\default.xml

if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtimed\drivers\berniw3
if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtimed\drivers\berniw3\7
if exist .\src\drivers\berniw3\7\default.xml copy .\src\drivers\berniw3\7\default.xml .\runtimed\drivers\berniw3\7\default.xml

if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtimed\drivers\berniw3
if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtimed\drivers\berniw3\8
if exist .\src\drivers\berniw3\8\default.xml copy .\src\drivers\berniw3\8\default.xml .\runtimed\drivers\berniw3\8\default.xml

if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtimed\drivers\berniw3
if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtimed\drivers\berniw3\9
if exist .\src\drivers\berniw3\9\default.xml copy .\src\drivers\berniw3\9\default.xml .\runtimed\drivers\berniw3\9\default.xml

if exist .\src\drivers\berniw3\*.* call .\create_dir .\runtimed
if exist .\src\drivers\berniw3\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\berniw3\*.* call .\create_dir .\runtimed\drivers\berniw3
if exist .\src\drivers\berniw3\berniw3.xml copy .\src\drivers\berniw3\berniw3.xml .\runtimed\drivers\berniw3\berniw3.xml
if exist .\src\drivers\berniw3\logo.rgb copy .\src\drivers\berniw3\logo.rgb .\runtimed\drivers\berniw3\logo.rgb
if exist .\src\drivers\berniw3\parameter.dat copy .\src\drivers\berniw3\parameter.dat .\runtimed\drivers\berniw3\parameter.dat
if exist .\src\drivers\berniw3\intsinsqr.dat copy .\src\drivers\berniw3\intsinsqr.dat .\runtimed\drivers\berniw3\intsinsqr.dat
if exist .\src\drivers\berniw3\intcossqr.dat copy .\src\drivers\berniw3\intcossqr.dat .\runtimed\drivers\berniw3\intcossqr.dat

if exist .\src\drivers\billy\0\practice\*.* call .\create_dir .\runtimed
if exist .\src\drivers\billy\0\practice\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\billy\0\practice\*.* call .\create_dir .\runtimed\drivers\billy
if exist .\src\drivers\billy\0\practice\*.* call .\create_dir .\runtimed\drivers\billy\0
if exist .\src\drivers\billy\0\practice\*.* call .\create_dir .\runtimed\drivers\billy\0\practice
if exist .\src\drivers\billy\0\practice\g-track-3.xml copy .\src\drivers\billy\0\practice\g-track-3.xml .\runtimed\drivers\billy\0\practice\g-track-3.xml

if exist .\src\drivers\billy\0\qualifying\*.* call .\create_dir .\runtimed
if exist .\src\drivers\billy\0\qualifying\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\billy\0\qualifying\*.* call .\create_dir .\runtimed\drivers\billy
if exist .\src\drivers\billy\0\qualifying\*.* call .\create_dir .\runtimed\drivers\billy\0
if exist .\src\drivers\billy\0\qualifying\*.* call .\create_dir .\runtimed\drivers\billy\0\qualifying
if exist .\src\drivers\billy\0\qualifying\g-track-3.xml copy .\src\drivers\billy\0\qualifying\g-track-3.xml .\runtimed\drivers\billy\0\qualifying\g-track-3.xml

if exist .\src\drivers\billy\0\race\*.* call .\create_dir .\runtimed
if exist .\src\drivers\billy\0\race\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\billy\0\race\*.* call .\create_dir .\runtimed\drivers\billy
if exist .\src\drivers\billy\0\race\*.* call .\create_dir .\runtimed\drivers\billy\0
if exist .\src\drivers\billy\0\race\*.* call .\create_dir .\runtimed\drivers\billy\0\race
if exist .\src\drivers\billy\0\race\g-track-3.xml copy .\src\drivers\billy\0\race\g-track-3.xml .\runtimed\drivers\billy\0\race\g-track-3.xml

if exist .\src\drivers\billy\0\*.* call .\create_dir .\runtimed
if exist .\src\drivers\billy\0\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\billy\0\*.* call .\create_dir .\runtimed\drivers\billy
if exist .\src\drivers\billy\0\*.* call .\create_dir .\runtimed\drivers\billy\0
if exist .\src\drivers\billy\0\default.xml copy .\src\drivers\billy\0\default.xml .\runtimed\drivers\billy\0\default.xml
if exist .\src\drivers\billy\0\clkdtm.rgb copy .\src\drivers\billy\0\clkdtm.rgb .\runtimed\drivers\billy\0\clkdtm.rgb

if exist .\src\drivers\billy\*.* call .\create_dir .\runtimed
if exist .\src\drivers\billy\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\billy\*.* call .\create_dir .\runtimed\drivers\billy
if exist .\src\drivers\billy\billy.xml copy .\src\drivers\billy\billy.xml .\runtimed\drivers\billy\billy.xml
if exist .\src\drivers\billy\logo.rgb copy .\src\drivers\billy\logo.rgb .\runtimed\drivers\billy\logo.rgb

if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtimed\drivers\bt\0
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtimed\drivers\bt\0\practice
if exist .\src\drivers\bt\0\practice\g-track-3.xml copy .\src\drivers\bt\0\practice\g-track-3.xml .\runtimed\drivers\bt\0\practice\g-track-3.xml
if exist .\src\drivers\bt\0\practice\michigan.xml copy .\src\drivers\bt\0\practice\michigan.xml .\runtimed\drivers\bt\0\practice\michigan.xml
if exist .\src\drivers\bt\0\practice\wheel-1.xml copy .\src\drivers\bt\0\practice\wheel-1.xml .\runtimed\drivers\bt\0\practice\wheel-1.xml

if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtimed\drivers\bt\0
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtimed\drivers\bt\0\qualifying
if exist .\src\drivers\bt\0\qualifying\g-track-3.xml copy .\src\drivers\bt\0\qualifying\g-track-3.xml .\runtimed\drivers\bt\0\qualifying\g-track-3.xml

if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtimed\drivers\bt\0
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtimed\drivers\bt\0\race
if exist .\src\drivers\bt\0\race\g-track-3.xml copy .\src\drivers\bt\0\race\g-track-3.xml .\runtimed\drivers\bt\0\race\g-track-3.xml
if exist .\src\drivers\bt\0\race\wheel-1.xml copy .\src\drivers\bt\0\race\wheel-1.xml .\runtimed\drivers\bt\0\race\wheel-1.xml

if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtimed\drivers\bt\0
if exist .\src\drivers\bt\0\default.xml copy .\src\drivers\bt\0\default.xml .\runtimed\drivers\bt\0\default.xml
if exist .\src\drivers\bt\0\cg-nascar-rwd.rgb copy .\src\drivers\bt\0\cg-nascar-rwd.rgb .\runtimed\drivers\bt\0\cg-nascar-rwd.rgb

if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtimed\drivers\bt\1
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtimed\drivers\bt\1\practice
if exist .\src\drivers\bt\1\practice\g-track-3.xml copy .\src\drivers\bt\1\practice\g-track-3.xml .\runtimed\drivers\bt\1\practice\g-track-3.xml
if exist .\src\drivers\bt\1\practice\michigan.xml copy .\src\drivers\bt\1\practice\michigan.xml .\runtimed\drivers\bt\1\practice\michigan.xml
if exist .\src\drivers\bt\1\practice\wheel-1.xml copy .\src\drivers\bt\1\practice\wheel-1.xml .\runtimed\drivers\bt\1\practice\wheel-1.xml

if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtimed\drivers\bt\1
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtimed\drivers\bt\1\qualifying
if exist .\src\drivers\bt\1\qualifying\g-track-3.xml copy .\src\drivers\bt\1\qualifying\g-track-3.xml .\runtimed\drivers\bt\1\qualifying\g-track-3.xml

if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtimed\drivers\bt\1
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtimed\drivers\bt\1\race
if exist .\src\drivers\bt\1\race\g-track-3.xml copy .\src\drivers\bt\1\race\g-track-3.xml .\runtimed\drivers\bt\1\race\g-track-3.xml
if exist .\src\drivers\bt\1\race\wheel-1.xml copy .\src\drivers\bt\1\race\wheel-1.xml .\runtimed\drivers\bt\1\race\wheel-1.xml

if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtimed\drivers\bt\1
if exist .\src\drivers\bt\1\default.xml copy .\src\drivers\bt\1\default.xml .\runtimed\drivers\bt\1\default.xml
if exist .\src\drivers\bt\1\cg-nascar-rwd.rgb copy .\src\drivers\bt\1\cg-nascar-rwd.rgb .\runtimed\drivers\bt\1\cg-nascar-rwd.rgb

if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtimed\drivers\bt\2
if exist .\src\drivers\bt\2\default.xml copy .\src\drivers\bt\2\default.xml .\runtimed\drivers\bt\2\default.xml

if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtimed\drivers\bt\3
if exist .\src\drivers\bt\3\default.xml copy .\src\drivers\bt\3\default.xml .\runtimed\drivers\bt\3\default.xml

if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtimed\drivers\bt\4
if exist .\src\drivers\bt\4\default.xml copy .\src\drivers\bt\4\default.xml .\runtimed\drivers\bt\4\default.xml

if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtimed\drivers\bt\5
if exist .\src\drivers\bt\5\default.xml copy .\src\drivers\bt\5\default.xml .\runtimed\drivers\bt\5\default.xml

if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtimed\drivers\bt\6
if exist .\src\drivers\bt\6\default.xml copy .\src\drivers\bt\6\default.xml .\runtimed\drivers\bt\6\default.xml

if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtimed\drivers\bt\7
if exist .\src\drivers\bt\7\default.xml copy .\src\drivers\bt\7\default.xml .\runtimed\drivers\bt\7\default.xml

if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtimed\drivers\bt\8
if exist .\src\drivers\bt\8\default.xml copy .\src\drivers\bt\8\default.xml .\runtimed\drivers\bt\8\default.xml

if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtimed\drivers\bt\9
if exist .\src\drivers\bt\9\default.xml copy .\src\drivers\bt\9\default.xml .\runtimed\drivers\bt\9\default.xml

if exist .\src\drivers\bt\*.* call .\create_dir .\runtimed
if exist .\src\drivers\bt\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\bt\*.* call .\create_dir .\runtimed\drivers\bt
if exist .\src\drivers\bt\bt.xml copy .\src\drivers\bt\bt.xml .\runtimed\drivers\bt\bt.xml
if exist .\src\drivers\bt\logo.rgb copy .\src\drivers\bt\logo.rgb .\runtimed\drivers\bt\logo.rgb

if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtimed\drivers\cylos1
if exist .\src\drivers\cylos1\tracksdata\*.* call .\create_dir .\runtimed\drivers\cylos1\tracksdata
if exist .\src\drivers\cylos1\tracksdata\car_e-track-3.xml copy .\src\drivers\cylos1\tracksdata\car_e-track-3.xml .\runtimed\drivers\cylos1\tracksdata\car_e-track-3.xml
if exist .\src\drivers\cylos1\tracksdata\car_lemans.xml copy .\src\drivers\cylos1\tracksdata\car_lemans.xml .\runtimed\drivers\cylos1\tracksdata\car_lemans.xml
if exist .\src\drivers\cylos1\tracksdata\car_test-1.xml copy .\src\drivers\cylos1\tracksdata\car_test-1.xml .\runtimed\drivers\cylos1\tracksdata\car_test-1.xml
if exist .\src\drivers\cylos1\tracksdata\lemans.xml copy .\src\drivers\cylos1\tracksdata\lemans.xml .\runtimed\drivers\cylos1\tracksdata\lemans.xml
if exist .\src\drivers\cylos1\tracksdata\michigan.xml copy .\src\drivers\cylos1\tracksdata\michigan.xml .\runtimed\drivers\cylos1\tracksdata\michigan.xml

if exist .\src\drivers\cylos1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\cylos1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\cylos1\*.* call .\create_dir .\runtimed\drivers\cylos1
if exist .\src\drivers\cylos1\cylos1.xml copy .\src\drivers\cylos1\cylos1.xml .\runtimed\drivers\cylos1\cylos1.xml
if exist .\src\drivers\cylos1\car1.xml copy .\src\drivers\cylos1\car1.xml .\runtimed\drivers\cylos1\car1.xml
if exist .\src\drivers\cylos1\cg-nascar-rwd.rgb copy .\src\drivers\cylos1\cg-nascar-rwd.rgb .\runtimed\drivers\cylos1\cg-nascar-rwd.rgb
if exist .\src\drivers\cylos1\logo.rgb copy .\src\drivers\cylos1\logo.rgb .\runtimed\drivers\cylos1\logo.rgb

if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtimed\drivers\cylos1
if exist .\src\drivers\cylos2\tracksdata\*.* call .\create_dir .\runtimed\drivers\cylos1\tracksdata
if exist .\src\drivers\cylos2\tracksdata\car_e-track-3.xml copy .\src\drivers\cylos2\tracksdata\car_e-track-3.xml .\runtimed\drivers\cylos1\tracksdata\car_e-track-3.xml
if exist .\src\drivers\cylos2\tracksdata\michigan.xml copy .\src\drivers\cylos2\tracksdata\michigan.xml .\runtimed\drivers\cylos1\tracksdata\michigan.xml

if exist .\src\drivers\cylos2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\cylos2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\cylos2\*.* call .\create_dir .\runtimed\drivers\cylos2
if exist .\src\drivers\cylos2\cylos2.xml copy .\src\drivers\cylos2\cylos2.xml .\runtimed\drivers\cylos2\cylos2.xml
if exist .\src\drivers\cylos2\car1.xml copy .\src\drivers\cylos2\car1.xml .\runtimed\drivers\cylos2\car1.xml
if exist .\src\drivers\cylos2\cg-nascar-rwd.rgb copy .\src\drivers\cylos2\cg-nascar-rwd.rgb .\runtimed\drivers\cylos2\cg-nascar-rwd.rgb
if exist .\src\drivers\cylos2\logo.rgb copy .\src\drivers\cylos2\logo.rgb .\runtimed\drivers\cylos2\logo.rgb

if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtimed\drivers\damned\1
if exist .\src\drivers\damned\1\car.xml copy .\src\drivers\damned\1\car.xml .\runtimed\drivers\damned\1\car.xml
if exist .\src\drivers\damned\1\car-dirt.xml copy .\src\drivers\damned\1\car-dirt.xml .\runtimed\drivers\damned\1\car-dirt.xml
if exist .\src\drivers\damned\1\buggy.rgb copy .\src\drivers\damned\1\buggy.rgb .\runtimed\drivers\damned\1\buggy.rgb
if exist .\src\drivers\damned\1\logo.rgb copy .\src\drivers\damned\1\logo.rgb .\runtimed\drivers\damned\1\logo.rgb

if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtimed
if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\10\*.* call .\create_dir .\runtimed\drivers\damned\10
if exist .\src\drivers\damned\10\car.xml copy .\src\drivers\damned\10\car.xml .\runtimed\drivers\damned\10\car.xml
if exist .\src\drivers\damned\10\logo.rgb copy .\src\drivers\damned\10\logo.rgb .\runtimed\drivers\damned\10\logo.rgb
if exist .\src\drivers\damned\10\155-DTM.rgb copy .\src\drivers\damned\10\155-DTM.rgb .\runtimed\drivers\damned\10\155-DTM.rgb

if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtimed\drivers\damned\2
if exist .\src\drivers\damned\2\car.xml copy .\src\drivers\damned\2\car.xml .\runtimed\drivers\damned\2\car.xml
if exist .\src\drivers\damned\2\car-dirt.xml copy .\src\drivers\damned\2\car-dirt.xml .\runtimed\drivers\damned\2\car-dirt.xml
if exist .\src\drivers\damned\2\buggy.rgb copy .\src\drivers\damned\2\buggy.rgb .\runtimed\drivers\damned\2\buggy.rgb
if exist .\src\drivers\damned\2\logo.rgb copy .\src\drivers\damned\2\logo.rgb .\runtimed\drivers\damned\2\logo.rgb

if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtimed
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtimed\drivers\damned\3
if exist .\src\drivers\damned\3\p406.rgb copy .\src\drivers\damned\3\p406.rgb .\runtimed\drivers\damned\3\p406.rgb
if exist .\src\drivers\damned\3\car.xml copy .\src\drivers\damned\3\car.xml .\runtimed\drivers\damned\3\car.xml
if exist .\src\drivers\damned\3\car-dirt.xml copy .\src\drivers\damned\3\car-dirt.xml .\runtimed\drivers\damned\3\car-dirt.xml
if exist .\src\drivers\damned\3\logo.rgb copy .\src\drivers\damned\3\logo.rgb .\runtimed\drivers\damned\3\logo.rgb

if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtimed
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtimed\drivers\damned\4
if exist .\src\drivers\damned\4\p406.rgb copy .\src\drivers\damned\4\p406.rgb .\runtimed\drivers\damned\4\p406.rgb
if exist .\src\drivers\damned\4\car.xml copy .\src\drivers\damned\4\car.xml .\runtimed\drivers\damned\4\car.xml
if exist .\src\drivers\damned\4\car-dirt.xml copy .\src\drivers\damned\4\car-dirt.xml .\runtimed\drivers\damned\4\car-dirt.xml
if exist .\src\drivers\damned\4\torcs.rgb copy .\src\drivers\damned\4\torcs.rgb .\runtimed\drivers\damned\4\torcs.rgb
if exist .\src\drivers\damned\4\logo.rgb copy .\src\drivers\damned\4\logo.rgb .\runtimed\drivers\damned\4\logo.rgb

if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtimed
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtimed\drivers\damned\5
if exist .\src\drivers\damned\5\car.xml copy .\src\drivers\damned\5\car.xml .\runtimed\drivers\damned\5\car.xml
if exist .\src\drivers\damned\5\car-dirt.xml copy .\src\drivers\damned\5\car-dirt.xml .\runtimed\drivers\damned\5\car-dirt.xml
if exist .\src\drivers\damned\5\acura-nsx-sz.rgb copy .\src\drivers\damned\5\acura-nsx-sz.rgb .\runtimed\drivers\damned\5\acura-nsx-sz.rgb
if exist .\src\drivers\damned\5\logo.rgb copy .\src\drivers\damned\5\logo.rgb .\runtimed\drivers\damned\5\logo.rgb

if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtimed
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtimed\drivers\damned\6
if exist .\src\drivers\damned\6\car.xml copy .\src\drivers\damned\6\car.xml .\runtimed\drivers\damned\6\car.xml
if exist .\src\drivers\damned\6\car-dirt.xml copy .\src\drivers\damned\6\car-dirt.xml .\runtimed\drivers\damned\6\car-dirt.xml
if exist .\src\drivers\damned\6\logo.rgb copy .\src\drivers\damned\6\logo.rgb .\runtimed\drivers\damned\6\logo.rgb

if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtimed
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtimed\drivers\damned\7
if exist .\src\drivers\damned\7\porsche-gt1.rgb copy .\src\drivers\damned\7\porsche-gt1.rgb .\runtimed\drivers\damned\7\porsche-gt1.rgb
if exist .\src\drivers\damned\7\logo.rgb copy .\src\drivers\damned\7\logo.rgb .\runtimed\drivers\damned\7\logo.rgb
if exist .\src\drivers\damned\7\car.xml copy .\src\drivers\damned\7\car.xml .\runtimed\drivers\damned\7\car.xml
if exist .\src\drivers\damned\7\car-dirt.xml copy .\src\drivers\damned\7\car-dirt.xml .\runtimed\drivers\damned\7\car-dirt.xml

if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtimed
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtimed\drivers\damned\8
if exist .\src\drivers\damned\8\car.xml copy .\src\drivers\damned\8\car.xml .\runtimed\drivers\damned\8\car.xml
if exist .\src\drivers\damned\8\logo.rgb copy .\src\drivers\damned\8\logo.rgb .\runtimed\drivers\damned\8\logo.rgb
if exist .\src\drivers\damned\8\mclaren-f1.rgb copy .\src\drivers\damned\8\mclaren-f1.rgb .\runtimed\drivers\damned\8\mclaren-f1.rgb

if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtimed
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtimed\drivers\damned\9
if exist .\src\drivers\damned\9\logo.rgb copy .\src\drivers\damned\9\logo.rgb .\runtimed\drivers\damned\9\logo.rgb
if exist .\src\drivers\damned\9\car.xml copy .\src\drivers\damned\9\car.xml .\runtimed\drivers\damned\9\car.xml
if exist .\src\drivers\damned\9\360-modena.rgb copy .\src\drivers\damned\9\360-modena.rgb .\runtimed\drivers\damned\9\360-modena.rgb

if exist .\src\drivers\damned\*.* call .\create_dir .\runtimed
if exist .\src\drivers\damned\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\damned\*.* call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\damned.xml copy .\src\drivers\damned\damned.xml .\runtimed\drivers\damned\damned.xml
if exist .\src\drivers\damned\car1.xml copy .\src\drivers\damned\car1.xml .\runtimed\drivers\damned\car1.xml

if exist .\src\drivers\human\tracks\b-speedway\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\b-speedway\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\b-speedway\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\b-speedway\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\b-speedway\*.* call .\create_dir .\runtimed\drivers\human\tracks\b-speedway
if exist .\src\drivers\human\tracks\b-speedway\car-porsche-gt1.xml copy .\src\drivers\human\tracks\b-speedway\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\b-speedway\car-porsche-gt1.xml

if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-1\*.* call .\create_dir .\runtimed\drivers\human\tracks\dirt-1
if exist .\src\drivers\human\tracks\dirt-1\car-pw-206wrc.xml copy .\src\drivers\human\tracks\dirt-1\car-pw-206wrc.xml .\runtimed\drivers\human\tracks\dirt-1\car-pw-206wrc.xml
if exist .\src\drivers\human\tracks\dirt-1\car-torcs.xml copy .\src\drivers\human\tracks\dirt-1\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-1\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtimed\drivers\human\tracks\dirt-2
if exist .\src\drivers\human\tracks\dirt-2\car-pw-206wrc.xml copy .\src\drivers\human\tracks\dirt-2\car-pw-206wrc.xml .\runtimed\drivers\human\tracks\dirt-2\car-pw-206wrc.xml
if exist .\src\drivers\human\tracks\dirt-2\car-torcs.xml copy .\src\drivers\human\tracks\dirt-2\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-2\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-3\*.* call .\create_dir .\runtimed\drivers\human\tracks\dirt-3
if exist .\src\drivers\human\tracks\dirt-3\car-torcs.xml copy .\src\drivers\human\tracks\dirt-3\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-3\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-4\*.* call .\create_dir .\runtimed\drivers\human\tracks\dirt-4
if exist .\src\drivers\human\tracks\dirt-4\car-torcs.xml copy .\src\drivers\human\tracks\dirt-4\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-4\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-5\*.* call .\create_dir .\runtimed\drivers\human\tracks\dirt-5
if exist .\src\drivers\human\tracks\dirt-5\car-torcs.xml copy .\src\drivers\human\tracks\dirt-5\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-5\car-torcs.xml

if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-6\*.* call .\create_dir .\runtimed\drivers\human\tracks\dirt-6
if exist .\src\drivers\human\tracks\dirt-6\car-porsche-gt3rs.xml copy .\src\drivers\human\tracks\dirt-6\car-porsche-gt3rs.xml .\runtimed\drivers\human\tracks\dirt-6\car-porsche-gt3rs.xml
if exist .\src\drivers\human\tracks\dirt-6\car-torcs.xml copy .\src\drivers\human\tracks\dirt-6\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-6\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-1\*.* call .\create_dir .\runtimed\drivers\human\tracks\e-track-1
if exist .\src\drivers\human\tracks\e-track-1\car-torcs.xml copy .\src\drivers\human\tracks\e-track-1\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-1\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-2\*.* call .\create_dir .\runtimed\drivers\human\tracks\e-track-2
if exist .\src\drivers\human\tracks\e-track-2\car-pw-206wrc.xml copy .\src\drivers\human\tracks\e-track-2\car-pw-206wrc.xml .\runtimed\drivers\human\tracks\e-track-2\car-pw-206wrc.xml
if exist .\src\drivers\human\tracks\e-track-2\car-torcs.xml copy .\src\drivers\human\tracks\e-track-2\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-2\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-3\*.* call .\create_dir .\runtimed\drivers\human\tracks\e-track-3
if exist .\src\drivers\human\tracks\e-track-3\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-3\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\e-track-3\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-3\car-torcs.xml copy .\src\drivers\human\tracks\e-track-3\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-3\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-4\*.* call .\create_dir .\runtimed\drivers\human\tracks\e-track-4
if exist .\src\drivers\human\tracks\e-track-4\car-360-modena.xml copy .\src\drivers\human\tracks\e-track-4\car-360-modena.xml .\runtimed\drivers\human\tracks\e-track-4\car-360-modena.xml
if exist .\src\drivers\human\tracks\e-track-4\car-mclaren-f1.xml copy .\src\drivers\human\tracks\e-track-4\car-mclaren-f1.xml .\runtimed\drivers\human\tracks\e-track-4\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\e-track-4\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-4\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\e-track-4\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml copy .\src\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml .\runtimed\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml
if exist .\src\drivers\human\tracks\e-track-4\car-torcs.xml copy .\src\drivers\human\tracks\e-track-4\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-4\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-5\*.* call .\create_dir .\runtimed\drivers\human\tracks\e-track-5
if exist .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml copy .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml .\runtimed\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml
if exist .\src\drivers\human\tracks\e-track-5\car-torcs.xml copy .\src\drivers\human\tracks\e-track-5\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-5\car-torcs.xml

if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\e-track-6\*.* call .\create_dir .\runtimed\drivers\human\tracks\e-track-6
if exist .\src\drivers\human\tracks\e-track-6\car-mclaren-f1.xml copy .\src\drivers\human\tracks\e-track-6\car-mclaren-f1.xml .\runtimed\drivers\human\tracks\e-track-6\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\e-track-6\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-6\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\e-track-6\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-6\car-torcs.xml copy .\src\drivers\human\tracks\e-track-6\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-6\car-torcs.xml

if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\g-track-2\*.* call .\create_dir .\runtimed\drivers\human\tracks\g-track-2
if exist .\src\drivers\human\tracks\g-track-2\car-360-modena.xml copy .\src\drivers\human\tracks\g-track-2\car-360-modena.xml .\runtimed\drivers\human\tracks\g-track-2\car-360-modena.xml
if exist .\src\drivers\human\tracks\g-track-2\car-mclaren-f1.xml copy .\src\drivers\human\tracks\g-track-2\car-mclaren-f1.xml .\runtimed\drivers\human\tracks\g-track-2\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\g-track-2\car-porsche-gt1.xml copy .\src\drivers\human\tracks\g-track-2\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\g-track-2\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml copy .\src\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml .\runtimed\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml
if exist .\src\drivers\human\tracks\g-track-2\car-torcs.xml copy .\src\drivers\human\tracks\g-track-2\car-torcs.xml .\runtimed\drivers\human\tracks\g-track-2\car-torcs.xml

if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\g-track-3\*.* call .\create_dir .\runtimed\drivers\human\tracks\g-track-3
if exist .\src\drivers\human\tracks\g-track-3\car-pw-206wrc.xml copy .\src\drivers\human\tracks\g-track-3\car-pw-206wrc.xml .\runtimed\drivers\human\tracks\g-track-3\car-pw-206wrc.xml

if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\mixed-1\*.* call .\create_dir .\runtimed\drivers\human\tracks\mixed-1
if exist .\src\drivers\human\tracks\mixed-1\car-torcs.xml copy .\src\drivers\human\tracks\mixed-1\car-torcs.xml .\runtimed\drivers\human\tracks\mixed-1\car-torcs.xml

if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\mixed-2\*.* call .\create_dir .\runtimed\drivers\human\tracks\mixed-2
if exist .\src\drivers\human\tracks\mixed-2\car-torcs.xml copy .\src\drivers\human\tracks\mixed-2\car-torcs.xml .\runtimed\drivers\human\tracks\mixed-2\car-torcs.xml

if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\spring\*.* call .\create_dir .\runtimed\drivers\human\tracks\spring

if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtimed\drivers\human\tracks
if exist .\src\drivers\human\tracks\wheel-1\*.* call .\create_dir .\runtimed\drivers\human\tracks\wheel-1
if exist .\src\drivers\human\tracks\wheel-1\car-mclaren-f1.xml copy .\src\drivers\human\tracks\wheel-1\car-mclaren-f1.xml .\runtimed\drivers\human\tracks\wheel-1\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\wheel-1\car-porsche-gt1.xml copy .\src\drivers\human\tracks\wheel-1\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\wheel-1\car-porsche-gt1.xml

if exist .\src\drivers\human\*.* call .\create_dir .\runtimed
if exist .\src\drivers\human\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\human\*.* call .\create_dir .\runtimed\drivers\human
if exist .\src\drivers\human\car-155-DTM.xml copy .\src\drivers\human\car-155-DTM.xml .\runtimed\drivers\human\car-155-DTM.xml
if exist .\src\drivers\human\car-360-modena.xml copy .\src\drivers\human\car-360-modena.xml .\runtimed\drivers\human\car-360-modena.xml
if exist .\src\drivers\human\car-acura-nsx-sz.xml copy .\src\drivers\human\car-acura-nsx-sz.xml .\runtimed\drivers\human\car-acura-nsx-sz.xml
if exist .\src\drivers\human\car-alpha-156-rk.xml copy .\src\drivers\human\car-alpha-156-rk.xml .\runtimed\drivers\human\car-alpha-156-rk.xml
if exist .\src\drivers\human\car-buggy.xml copy .\src\drivers\human\car-buggy.xml .\runtimed\drivers\human\car-buggy.xml
if exist .\src\drivers\human\car-cg-gt-rwd.xml copy .\src\drivers\human\car-cg-gt-rwd.xml .\runtimed\drivers\human\car-cg-gt-rwd.xml
if exist .\src\drivers\human\car-cg-nascar-fwd.xml copy .\src\drivers\human\car-cg-nascar-fwd.xml .\runtimed\drivers\human\car-cg-nascar-fwd.xml
if exist .\src\drivers\human\car-cg-nascar-rwd.xml copy .\src\drivers\human\car-cg-nascar-rwd.xml .\runtimed\drivers\human\car-cg-nascar-rwd.xml
if exist .\src\drivers\human\car-clkdtm.xml copy .\src\drivers\human\car-clkdtm.xml .\runtimed\drivers\human\car-clkdtm.xml
if exist .\src\drivers\human\car-corvette.xml copy .\src\drivers\human\car-corvette.xml .\runtimed\drivers\human\car-corvette.xml
if exist .\src\drivers\human\car-fs-02h2.xml copy .\src\drivers\human\car-fs-02h2.xml .\runtimed\drivers\human\car-fs-02h2.xml
if exist .\src\drivers\human\car-lotus-gt1.xml copy .\src\drivers\human\car-lotus-gt1.xml .\runtimed\drivers\human\car-lotus-gt1.xml
if exist .\src\drivers\human\car-mclaren-f1.xml copy .\src\drivers\human\car-mclaren-f1.xml .\runtimed\drivers\human\car-mclaren-f1.xml
if exist .\src\drivers\human\car-p406.xml copy .\src\drivers\human\car-p406.xml .\runtimed\drivers\human\car-p406.xml
if exist .\src\drivers\human\car-porsche-gt1.xml copy .\src\drivers\human\car-porsche-gt1.xml .\runtimed\drivers\human\car-porsche-gt1.xml
if exist .\src\drivers\human\car-porsche-gt3rs.xml copy .\src\drivers\human\car-porsche-gt3rs.xml .\runtimed\drivers\human\car-porsche-gt3rs.xml
if exist .\src\drivers\human\car-pw-206wrc.xml copy .\src\drivers\human\car-pw-206wrc.xml .\runtimed\drivers\human\car-pw-206wrc.xml
if exist .\src\drivers\human\car-pw-evovwrc-k.xml copy .\src\drivers\human\car-pw-evovwrc-k.xml .\runtimed\drivers\human\car-pw-evovwrc-k.xml
if exist .\src\drivers\human\car-pw-evovwrc.xml copy .\src\drivers\human\car-pw-evovwrc.xml .\runtimed\drivers\human\car-pw-evovwrc.xml
if exist .\src\drivers\human\car-torcs.xml copy .\src\drivers\human\car-torcs.xml .\runtimed\drivers\human\car-torcs.xml
if exist .\src\drivers\human\car-viper-gts-r.xml copy .\src\drivers\human\car-viper-gts-r.xml .\runtimed\drivers\human\car-viper-gts-r.xml
if exist .\src\drivers\human\car-vm-x2.xml copy .\src\drivers\human\car-vm-x2.xml .\runtimed\drivers\human\car-vm-x2.xml
if exist .\src\drivers\human\car-vm-x4.xml copy .\src\drivers\human\car-vm-x4.xml .\runtimed\drivers\human\car-vm-x4.xml
if exist .\src\drivers\human\car.xml copy .\src\drivers\human\car.xml .\runtimed\drivers\human\car.xml
if exist .\src\drivers\human\human.xml copy .\src\drivers\human\human.xml .\runtimed\drivers\human\human.xml
if exist .\src\drivers\human\preferences.xml copy .\src\drivers\human\preferences.xml .\runtimed\drivers\human\preferences.xml
if exist .\src\drivers\human\logo.rgb copy .\src\drivers\human\logo.rgb .\runtimed\drivers\human\logo.rgb
if exist .\src\drivers\human\mclaren-f1.rgb copy .\src\drivers\human\mclaren-f1.rgb .\runtimed\drivers\human\mclaren-f1.rgb

if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\1
if exist .\src\drivers\inferno\1\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\1\tracksdata
if exist .\src\drivers\inferno\1\tracksdata\aalborg.xml copy .\src\drivers\inferno\1\tracksdata\aalborg.xml .\runtimed\drivers\inferno\1\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\1\tracksdata\alpine-1.xml copy .\src\drivers\inferno\1\tracksdata\alpine-1.xml .\runtimed\drivers\inferno\1\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\1\tracksdata\a-speedway.xml copy .\src\drivers\inferno\1\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\1\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\b-speedway.xml copy .\src\drivers\inferno\1\tracksdata\b-speedway.xml .\runtimed\drivers\inferno\1\tracksdata\b-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\1\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno\1\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\1\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\1\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno\1\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\car_d-speedway.xml copy .\src\drivers\inferno\1\tracksdata\car_d-speedway.xml .\runtimed\drivers\inferno\1\tracksdata\car_d-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\car_eroad.xml copy .\src\drivers\inferno\1\tracksdata\car_eroad.xml .\runtimed\drivers\inferno\1\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno\1\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno\1\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno\1\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno\1\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno\1\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\1\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\1\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno\1\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\1\tracksdata\car_g-speedway.xml copy .\src\drivers\inferno\1\tracksdata\car_g-speedway.xml .\runtimed\drivers\inferno\1\tracksdata\car_g-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\1\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno\1\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\1\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno\1\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\car_michigan.xml copy .\src\drivers\inferno\1\tracksdata\car_michigan.xml .\runtimed\drivers\inferno\1\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\1\tracksdata\car_s2.xml copy .\src\drivers\inferno\1\tracksdata\car_s2.xml .\runtimed\drivers\inferno\1\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\1\tracksdata\car_test-1.xml copy .\src\drivers\inferno\1\tracksdata\car_test-1.xml .\runtimed\drivers\inferno\1\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\1\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\1\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno\1\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\1\tracksdata\city-1.xml copy .\src\drivers\inferno\1\tracksdata\city-1.xml .\runtimed\drivers\inferno\1\tracksdata\city-1.xml
if exist .\src\drivers\inferno\1\tracksdata\c-speedway.xml copy .\src\drivers\inferno\1\tracksdata\c-speedway.xml .\runtimed\drivers\inferno\1\tracksdata\c-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\d-speedway.xml copy .\src\drivers\inferno\1\tracksdata\d-speedway.xml .\runtimed\drivers\inferno\1\tracksdata\d-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\eroad.xml copy .\src\drivers\inferno\1\tracksdata\eroad.xml .\runtimed\drivers\inferno\1\tracksdata\eroad.xml
if exist .\src\drivers\inferno\1\tracksdata\e-speedway.xml copy .\src\drivers\inferno\1\tracksdata\e-speedway.xml .\runtimed\drivers\inferno\1\tracksdata\e-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-1.xml copy .\src\drivers\inferno\1\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\1\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-2.xml copy .\src\drivers\inferno\1\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\1\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-3.xml copy .\src\drivers\inferno\1\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\1\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-4.xml copy .\src\drivers\inferno\1\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\1\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-5.xml copy .\src\drivers\inferno\1\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\1\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\1\tracksdata\e-track-6.xml copy .\src\drivers\inferno\1\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\1\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\1\tracksdata\f-speedway.xml copy .\src\drivers\inferno\1\tracksdata\f-speedway.xml .\runtimed\drivers\inferno\1\tracksdata\f-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\g-speedway.xml copy .\src\drivers\inferno\1\tracksdata\g-speedway.xml .\runtimed\drivers\inferno\1\tracksdata\g-speedway.xml
if exist .\src\drivers\inferno\1\tracksdata\g-track-1.xml copy .\src\drivers\inferno\1\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\1\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\1\tracksdata\g-track-2.xml copy .\src\drivers\inferno\1\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\1\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\1\tracksdata\michigan.xml copy .\src\drivers\inferno\1\tracksdata\michigan.xml .\runtimed\drivers\inferno\1\tracksdata\michigan.xml
if exist .\src\drivers\inferno\1\tracksdata\s2.xml copy .\src\drivers\inferno\1\tracksdata\s2.xml .\runtimed\drivers\inferno\1\tracksdata\s2.xml
if exist .\src\drivers\inferno\1\tracksdata\wheel-1.xml copy .\src\drivers\inferno\1\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\1\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtimed\drivers\inferno\1
if exist .\src\drivers\inferno\1\defaultcar.xml copy .\src\drivers\inferno\1\defaultcar.xml .\runtimed\drivers\inferno\1\defaultcar.xml
if exist .\src\drivers\inferno\1\default.xml copy .\src\drivers\inferno\1\default.xml .\runtimed\drivers\inferno\1\default.xml
if exist .\src\drivers\inferno\1\logo.rgb copy .\src\drivers\inferno\1\logo.rgb .\runtimed\drivers\inferno\1\logo.rgb
if exist .\src\drivers\inferno\1\Makefile copy .\src\drivers\inferno\1\Makefile .\runtimed\drivers\inferno\1\Makefile
if exist .\src\drivers\inferno\1\mclaren-f1.rgb copy .\src\drivers\inferno\1\mclaren-f1.rgb .\runtimed\drivers\inferno\1\mclaren-f1.rgb

if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\10
if exist .\src\drivers\inferno\10\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\10\tracksdata
if exist .\src\drivers\inferno\10\tracksdata\aalborg.xml copy .\src\drivers\inferno\10\tracksdata\aalborg.xml .\runtimed\drivers\inferno\10\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\10\tracksdata\a-speedway.xml copy .\src\drivers\inferno\10\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\10\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\10\tracksdata\b-speedway.xml copy .\src\drivers\inferno\10\tracksdata\b-speedway.xml .\runtimed\drivers\inferno\10\tracksdata\b-speedway.xml
if exist .\src\drivers\inferno\10\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\10\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno\10\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\10\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno\10\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\10\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\10\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno\10\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\10\tracksdata\car_g-speedway.xml copy .\src\drivers\inferno\10\tracksdata\car_g-speedway.xml .\runtimed\drivers\inferno\10\tracksdata\car_g-speedway.xml
if exist .\src\drivers\inferno\10\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\10\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno\10\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\10\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\10\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno\10\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\c-speedway.xml copy .\src\drivers\inferno\10\tracksdata\c-speedway.xml .\runtimed\drivers\inferno\10\tracksdata\c-speedway.xml
if exist .\src\drivers\inferno\10\tracksdata\d-speedway.xml copy .\src\drivers\inferno\10\tracksdata\d-speedway.xml .\runtimed\drivers\inferno\10\tracksdata\d-speedway.xml
if exist .\src\drivers\inferno\10\tracksdata\eroad.xml copy .\src\drivers\inferno\10\tracksdata\eroad.xml .\runtimed\drivers\inferno\10\tracksdata\eroad.xml
if exist .\src\drivers\inferno\10\tracksdata\e-speedway.xml copy .\src\drivers\inferno\10\tracksdata\e-speedway.xml .\runtimed\drivers\inferno\10\tracksdata\e-speedway.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-1.xml copy .\src\drivers\inferno\10\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\10\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-2.xml copy .\src\drivers\inferno\10\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\10\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-3.xml copy .\src\drivers\inferno\10\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\10\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-4.xml copy .\src\drivers\inferno\10\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\10\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-5.xml copy .\src\drivers\inferno\10\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\10\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\10\tracksdata\e-track-6.xml copy .\src\drivers\inferno\10\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\10\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\10\tracksdata\f-speedway.xml copy .\src\drivers\inferno\10\tracksdata\f-speedway.xml .\runtimed\drivers\inferno\10\tracksdata\f-speedway.xml
if exist .\src\drivers\inferno\10\tracksdata\g-speedway.xml copy .\src\drivers\inferno\10\tracksdata\g-speedway.xml .\runtimed\drivers\inferno\10\tracksdata\g-speedway.xml
if exist .\src\drivers\inferno\10\tracksdata\g-track-1.xml copy .\src\drivers\inferno\10\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\10\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\10\tracksdata\g-track-2.xml copy .\src\drivers\inferno\10\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\10\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\10\tracksdata\michigan.xml copy .\src\drivers\inferno\10\tracksdata\michigan.xml .\runtimed\drivers\inferno\10\tracksdata\michigan.xml
if exist .\src\drivers\inferno\10\tracksdata\wheel-1.xml copy .\src\drivers\inferno\10\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\10\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtimed\drivers\inferno\10
if exist .\src\drivers\inferno\10\defaultcar.xml copy .\src\drivers\inferno\10\defaultcar.xml .\runtimed\drivers\inferno\10\defaultcar.xml
if exist .\src\drivers\inferno\10\default.xml copy .\src\drivers\inferno\10\default.xml .\runtimed\drivers\inferno\10\default.xml
if exist .\src\drivers\inferno\10\logo.rgb copy .\src\drivers\inferno\10\logo.rgb .\runtimed\drivers\inferno\10\logo.rgb
if exist .\src\drivers\inferno\10\Makefile copy .\src\drivers\inferno\10\Makefile .\runtimed\drivers\inferno\10\Makefile
if exist .\src\drivers\inferno\10\vm-x4.rgb copy .\src\drivers\inferno\10\vm-x4.rgb .\runtimed\drivers\inferno\10\vm-x4.rgb

if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\2
if exist .\src\drivers\inferno\2\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\2\tracksdata
if exist .\src\drivers\inferno\2\tracksdata\aalborg.xml copy .\src\drivers\inferno\2\tracksdata\aalborg.xml .\runtimed\drivers\inferno\2\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\2\tracksdata\a-speedway.xml copy .\src\drivers\inferno\2\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\2\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\b-speedway.xml copy .\src\drivers\inferno\2\tracksdata\b-speedway.xml .\runtimed\drivers\inferno\2\tracksdata\b-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\2\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno\2\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\2\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\2\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno\2\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\car_d-speedway.xml copy .\src\drivers\inferno\2\tracksdata\car_d-speedway.xml .\runtimed\drivers\inferno\2\tracksdata\car_d-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\car_eroad.xml copy .\src\drivers\inferno\2\tracksdata\car_eroad.xml .\runtimed\drivers\inferno\2\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno\2\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno\2\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno\2\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno\2\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno\2\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\2\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\2\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno\2\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\2\tracksdata\car_g-speedway.xml copy .\src\drivers\inferno\2\tracksdata\car_g-speedway.xml .\runtimed\drivers\inferno\2\tracksdata\car_g-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\2\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno\2\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\2\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno\2\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\car_michigan.xml copy .\src\drivers\inferno\2\tracksdata\car_michigan.xml .\runtimed\drivers\inferno\2\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\2\tracksdata\car_s2.xml copy .\src\drivers\inferno\2\tracksdata\car_s2.xml .\runtimed\drivers\inferno\2\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\2\tracksdata\car_test-1.xml copy .\src\drivers\inferno\2\tracksdata\car_test-1.xml .\runtimed\drivers\inferno\2\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\2\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\2\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno\2\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\2\tracksdata\c-speedway.xml copy .\src\drivers\inferno\2\tracksdata\c-speedway.xml .\runtimed\drivers\inferno\2\tracksdata\c-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\d-speedway.xml copy .\src\drivers\inferno\2\tracksdata\d-speedway.xml .\runtimed\drivers\inferno\2\tracksdata\d-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\eroad.xml copy .\src\drivers\inferno\2\tracksdata\eroad.xml .\runtimed\drivers\inferno\2\tracksdata\eroad.xml
if exist .\src\drivers\inferno\2\tracksdata\e-speedway.xml copy .\src\drivers\inferno\2\tracksdata\e-speedway.xml .\runtimed\drivers\inferno\2\tracksdata\e-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-1.xml copy .\src\drivers\inferno\2\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\2\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-2.xml copy .\src\drivers\inferno\2\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\2\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-3.xml copy .\src\drivers\inferno\2\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\2\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-4.xml copy .\src\drivers\inferno\2\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\2\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-5.xml copy .\src\drivers\inferno\2\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\2\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\2\tracksdata\e-track-6.xml copy .\src\drivers\inferno\2\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\2\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\2\tracksdata\f-speedway.xml copy .\src\drivers\inferno\2\tracksdata\f-speedway.xml .\runtimed\drivers\inferno\2\tracksdata\f-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\g-speedway.xml copy .\src\drivers\inferno\2\tracksdata\g-speedway.xml .\runtimed\drivers\inferno\2\tracksdata\g-speedway.xml
if exist .\src\drivers\inferno\2\tracksdata\g-track-1.xml copy .\src\drivers\inferno\2\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\2\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\2\tracksdata\g-track-2.xml copy .\src\drivers\inferno\2\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\2\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\2\tracksdata\michigan.xml copy .\src\drivers\inferno\2\tracksdata\michigan.xml .\runtimed\drivers\inferno\2\tracksdata\michigan.xml
if exist .\src\drivers\inferno\2\tracksdata\s2.xml copy .\src\drivers\inferno\2\tracksdata\s2.xml .\runtimed\drivers\inferno\2\tracksdata\s2.xml
if exist .\src\drivers\inferno\2\tracksdata\wheel-1.xml copy .\src\drivers\inferno\2\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\2\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtimed\drivers\inferno\2
if exist .\src\drivers\inferno\2\360-modena.rgb copy .\src\drivers\inferno\2\360-modena.rgb .\runtimed\drivers\inferno\2\360-modena.rgb
if exist .\src\drivers\inferno\2\360-modena.xcf copy .\src\drivers\inferno\2\360-modena.xcf .\runtimed\drivers\inferno\2\360-modena.xcf
if exist .\src\drivers\inferno\2\defaultcar.xml copy .\src\drivers\inferno\2\defaultcar.xml .\runtimed\drivers\inferno\2\defaultcar.xml
if exist .\src\drivers\inferno\2\default.xml copy .\src\drivers\inferno\2\default.xml .\runtimed\drivers\inferno\2\default.xml
if exist .\src\drivers\inferno\2\logo.rgb copy .\src\drivers\inferno\2\logo.rgb .\runtimed\drivers\inferno\2\logo.rgb
if exist .\src\drivers\inferno\2\Makefile copy .\src\drivers\inferno\2\Makefile .\runtimed\drivers\inferno\2\Makefile

if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\3
if exist .\src\drivers\inferno\3\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\3\tracksdata
if exist .\src\drivers\inferno\3\tracksdata\aalborg.xml copy .\src\drivers\inferno\3\tracksdata\aalborg.xml .\runtimed\drivers\inferno\3\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\3\tracksdata\alpine-1.xml copy .\src\drivers\inferno\3\tracksdata\alpine-1.xml .\runtimed\drivers\inferno\3\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\3\tracksdata\a-speedway.xml copy .\src\drivers\inferno\3\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\b-speedway.xml copy .\src\drivers\inferno\3\tracksdata\b-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\b-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\3\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno\3\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\3\tracksdata\car_alpine-1.xml copy .\src\drivers\inferno\3\tracksdata\car_alpine-1.xml .\runtimed\drivers\inferno\3\tracksdata\car_alpine-1.xml
if exist .\src\drivers\inferno\3\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\3\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_b-speedway.xml copy .\src\drivers\inferno\3\tracksdata\car_b-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\car_b-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_c-speedway.xml copy .\src\drivers\inferno\3\tracksdata\car_c-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\car_c-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_d-speedway.xml copy .\src\drivers\inferno\3\tracksdata\car_d-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\car_d-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_eroad.xml copy .\src\drivers\inferno\3\tracksdata\car_eroad.xml .\runtimed\drivers\inferno\3\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-speedway.xml copy .\src\drivers\inferno\3\tracksdata\car_e-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\car_e-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno\3\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno\3\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno\3\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno\3\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno\3\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\3\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\3\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno\3\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\3\tracksdata\car_f-speedway.xml copy .\src\drivers\inferno\3\tracksdata\car_f-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\car_f-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_g-speedway.xml copy .\src\drivers\inferno\3\tracksdata\car_g-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\car_g-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\3\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno\3\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\3\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno\3\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\car_h-speedway.xml copy .\src\drivers\inferno\3\tracksdata\car_h-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\car_h-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\car_michigan.xml copy .\src\drivers\inferno\3\tracksdata\car_michigan.xml .\runtimed\drivers\inferno\3\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\3\tracksdata\car_spring.xml copy .\src\drivers\inferno\3\tracksdata\car_spring.xml .\runtimed\drivers\inferno\3\tracksdata\car_spring.xml
if exist .\src\drivers\inferno\3\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\3\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno\3\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\3\tracksdata\c-speedway.xml copy .\src\drivers\inferno\3\tracksdata\c-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\c-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\d-speedway.xml copy .\src\drivers\inferno\3\tracksdata\d-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\d-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\eroad.xml copy .\src\drivers\inferno\3\tracksdata\eroad.xml .\runtimed\drivers\inferno\3\tracksdata\eroad.xml
if exist .\src\drivers\inferno\3\tracksdata\e-speedway.xml copy .\src\drivers\inferno\3\tracksdata\e-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\e-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-1.xml copy .\src\drivers\inferno\3\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\3\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-2.xml copy .\src\drivers\inferno\3\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\3\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-3.xml copy .\src\drivers\inferno\3\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\3\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-4.xml copy .\src\drivers\inferno\3\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\3\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-5.xml copy .\src\drivers\inferno\3\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\3\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\3\tracksdata\e-track-6.xml copy .\src\drivers\inferno\3\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\3\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\3\tracksdata\f-speedway.xml copy .\src\drivers\inferno\3\tracksdata\f-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\f-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\g-speedway.xml copy .\src\drivers\inferno\3\tracksdata\g-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\g-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\g-track-1.xml copy .\src\drivers\inferno\3\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\3\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\3\tracksdata\g-track-2.xml copy .\src\drivers\inferno\3\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\3\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\3\tracksdata\h-speedway.xml copy .\src\drivers\inferno\3\tracksdata\h-speedway.xml .\runtimed\drivers\inferno\3\tracksdata\h-speedway.xml
if exist .\src\drivers\inferno\3\tracksdata\michigan.xml copy .\src\drivers\inferno\3\tracksdata\michigan.xml .\runtimed\drivers\inferno\3\tracksdata\michigan.xml
if exist .\src\drivers\inferno\3\tracksdata\spring.xml copy .\src\drivers\inferno\3\tracksdata\spring.xml .\runtimed\drivers\inferno\3\tracksdata\spring.xml
if exist .\src\drivers\inferno\3\tracksdata\wheel-1.xml copy .\src\drivers\inferno\3\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\3\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtimed\drivers\inferno\3
if exist .\src\drivers\inferno\3\defaultcar.xml copy .\src\drivers\inferno\3\defaultcar.xml .\runtimed\drivers\inferno\3\defaultcar.xml
if exist .\src\drivers\inferno\3\default.xml copy .\src\drivers\inferno\3\default.xml .\runtimed\drivers\inferno\3\default.xml
if exist .\src\drivers\inferno\3\logo.rgb copy .\src\drivers\inferno\3\logo.rgb .\runtimed\drivers\inferno\3\logo.rgb
if exist .\src\drivers\inferno\3\Makefile copy .\src\drivers\inferno\3\Makefile .\runtimed\drivers\inferno\3\Makefile
if exist .\src\drivers\inferno\3\porsche-gt1.rgb copy .\src\drivers\inferno\3\porsche-gt1.rgb .\runtimed\drivers\inferno\3\porsche-gt1.rgb

if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\4
if exist .\src\drivers\inferno\4\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\4\tracksdata
if exist .\src\drivers\inferno\4\tracksdata\aalborg.xml copy .\src\drivers\inferno\4\tracksdata\aalborg.xml .\runtimed\drivers\inferno\4\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\4\tracksdata\alpine-1.xml copy .\src\drivers\inferno\4\tracksdata\alpine-1.xml .\runtimed\drivers\inferno\4\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\4\tracksdata\a-speedway.xml copy .\src\drivers\inferno\4\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\4\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\b-speedway.xml copy .\src\drivers\inferno\4\tracksdata\b-speedway.xml .\runtimed\drivers\inferno\4\tracksdata\b-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\4\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno\4\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\4\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\4\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno\4\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\car_eroad.xml copy .\src\drivers\inferno\4\tracksdata\car_eroad.xml .\runtimed\drivers\inferno\4\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno\4\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno\4\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno\4\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno\4\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno\4\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\4\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\4\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno\4\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\4\tracksdata\car_g-speedway.xml copy .\src\drivers\inferno\4\tracksdata\car_g-speedway.xml .\runtimed\drivers\inferno\4\tracksdata\car_g-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\4\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno\4\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\4\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno\4\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\car_g-track-3.xml copy .\src\drivers\inferno\4\tracksdata\car_g-track-3.xml .\runtimed\drivers\inferno\4\tracksdata\car_g-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\car_michigan.xml copy .\src\drivers\inferno\4\tracksdata\car_michigan.xml .\runtimed\drivers\inferno\4\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\4\tracksdata\car_test-1.xml copy .\src\drivers\inferno\4\tracksdata\car_test-1.xml .\runtimed\drivers\inferno\4\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\4\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\4\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno\4\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\4\tracksdata\c-speedway.xml copy .\src\drivers\inferno\4\tracksdata\c-speedway.xml .\runtimed\drivers\inferno\4\tracksdata\c-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\dirt-2.xml copy .\src\drivers\inferno\4\tracksdata\dirt-2.xml .\runtimed\drivers\inferno\4\tracksdata\dirt-2.xml
if exist .\src\drivers\inferno\4\tracksdata\d-speedway.xml copy .\src\drivers\inferno\4\tracksdata\d-speedway.xml .\runtimed\drivers\inferno\4\tracksdata\d-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\eroad.xml copy .\src\drivers\inferno\4\tracksdata\eroad.xml .\runtimed\drivers\inferno\4\tracksdata\eroad.xml
if exist .\src\drivers\inferno\4\tracksdata\e-speedway.xml copy .\src\drivers\inferno\4\tracksdata\e-speedway.xml .\runtimed\drivers\inferno\4\tracksdata\e-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-1.xml copy .\src\drivers\inferno\4\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\4\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-2.xml copy .\src\drivers\inferno\4\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\4\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-3.xml copy .\src\drivers\inferno\4\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\4\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-4.xml copy .\src\drivers\inferno\4\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\4\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-5.xml copy .\src\drivers\inferno\4\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\4\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\4\tracksdata\e-track-6.xml copy .\src\drivers\inferno\4\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\4\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\4\tracksdata\f-speedway.xml copy .\src\drivers\inferno\4\tracksdata\f-speedway.xml .\runtimed\drivers\inferno\4\tracksdata\f-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\g-speedway.xml copy .\src\drivers\inferno\4\tracksdata\g-speedway.xml .\runtimed\drivers\inferno\4\tracksdata\g-speedway.xml
if exist .\src\drivers\inferno\4\tracksdata\g-track-1.xml copy .\src\drivers\inferno\4\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\4\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\4\tracksdata\g-track-2.xml copy .\src\drivers\inferno\4\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\4\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\4\tracksdata\g-track-3.xml copy .\src\drivers\inferno\4\tracksdata\g-track-3.xml .\runtimed\drivers\inferno\4\tracksdata\g-track-3.xml
if exist .\src\drivers\inferno\4\tracksdata\michigan.xml copy .\src\drivers\inferno\4\tracksdata\michigan.xml .\runtimed\drivers\inferno\4\tracksdata\michigan.xml
if exist .\src\drivers\inferno\4\tracksdata\wheel-1.xml copy .\src\drivers\inferno\4\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\4\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtimed\drivers\inferno\4
if exist .\src\drivers\inferno\4\clkdtm.rgb copy .\src\drivers\inferno\4\clkdtm.rgb .\runtimed\drivers\inferno\4\clkdtm.rgb
if exist .\src\drivers\inferno\4\defaultcar.xml copy .\src\drivers\inferno\4\defaultcar.xml .\runtimed\drivers\inferno\4\defaultcar.xml
if exist .\src\drivers\inferno\4\default.xml copy .\src\drivers\inferno\4\default.xml .\runtimed\drivers\inferno\4\default.xml
if exist .\src\drivers\inferno\4\logo.rgb copy .\src\drivers\inferno\4\logo.rgb .\runtimed\drivers\inferno\4\logo.rgb
if exist .\src\drivers\inferno\4\Makefile copy .\src\drivers\inferno\4\Makefile .\runtimed\drivers\inferno\4\Makefile

if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\5
if exist .\src\drivers\inferno\5\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\5\tracksdata
if exist .\src\drivers\inferno\5\tracksdata\aalborg.xml copy .\src\drivers\inferno\5\tracksdata\aalborg.xml .\runtimed\drivers\inferno\5\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\5\tracksdata\a-speedway.xml copy .\src\drivers\inferno\5\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\5\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\5\tracksdata\b-speedway.xml copy .\src\drivers\inferno\5\tracksdata\b-speedway.xml .\runtimed\drivers\inferno\5\tracksdata\b-speedway.xml
if exist .\src\drivers\inferno\5\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\5\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno\5\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\5\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno\5\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\5\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\5\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno\5\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\5\tracksdata\car_g-speedway.xml copy .\src\drivers\inferno\5\tracksdata\car_g-speedway.xml .\runtimed\drivers\inferno\5\tracksdata\car_g-speedway.xml
if exist .\src\drivers\inferno\5\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\5\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno\5\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\5\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\5\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno\5\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\c-speedway.xml copy .\src\drivers\inferno\5\tracksdata\c-speedway.xml .\runtimed\drivers\inferno\5\tracksdata\c-speedway.xml
if exist .\src\drivers\inferno\5\tracksdata\d-speedway.xml copy .\src\drivers\inferno\5\tracksdata\d-speedway.xml .\runtimed\drivers\inferno\5\tracksdata\d-speedway.xml
if exist .\src\drivers\inferno\5\tracksdata\eroad.xml copy .\src\drivers\inferno\5\tracksdata\eroad.xml .\runtimed\drivers\inferno\5\tracksdata\eroad.xml
if exist .\src\drivers\inferno\5\tracksdata\e-speedway.xml copy .\src\drivers\inferno\5\tracksdata\e-speedway.xml .\runtimed\drivers\inferno\5\tracksdata\e-speedway.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-1.xml copy .\src\drivers\inferno\5\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\5\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-2.xml copy .\src\drivers\inferno\5\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\5\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-3.xml copy .\src\drivers\inferno\5\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\5\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-4.xml copy .\src\drivers\inferno\5\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\5\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-5.xml copy .\src\drivers\inferno\5\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\5\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\5\tracksdata\e-track-6.xml copy .\src\drivers\inferno\5\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\5\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\5\tracksdata\f-speedway.xml copy .\src\drivers\inferno\5\tracksdata\f-speedway.xml .\runtimed\drivers\inferno\5\tracksdata\f-speedway.xml
if exist .\src\drivers\inferno\5\tracksdata\g-speedway.xml copy .\src\drivers\inferno\5\tracksdata\g-speedway.xml .\runtimed\drivers\inferno\5\tracksdata\g-speedway.xml
if exist .\src\drivers\inferno\5\tracksdata\g-track-1.xml copy .\src\drivers\inferno\5\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\5\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\5\tracksdata\g-track-2.xml copy .\src\drivers\inferno\5\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\5\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\5\tracksdata\michigan.xml copy .\src\drivers\inferno\5\tracksdata\michigan.xml .\runtimed\drivers\inferno\5\tracksdata\michigan.xml
if exist .\src\drivers\inferno\5\tracksdata\wheel-1.xml copy .\src\drivers\inferno\5\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\5\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtimed\drivers\inferno\5
if exist .\src\drivers\inferno\5\defaultcar.xml copy .\src\drivers\inferno\5\defaultcar.xml .\runtimed\drivers\inferno\5\defaultcar.xml
if exist .\src\drivers\inferno\5\default.xml copy .\src\drivers\inferno\5\default.xml .\runtimed\drivers\inferno\5\default.xml
if exist .\src\drivers\inferno\5\gt40.rgb copy .\src\drivers\inferno\5\gt40.rgb .\runtimed\drivers\inferno\5\gt40.rgb
if exist .\src\drivers\inferno\5\logo.rgb copy .\src\drivers\inferno\5\logo.rgb .\runtimed\drivers\inferno\5\logo.rgb
if exist .\src\drivers\inferno\5\Makefile copy .\src\drivers\inferno\5\Makefile .\runtimed\drivers\inferno\5\Makefile

if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\6
if exist .\src\drivers\inferno\6\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\6\tracksdata
if exist .\src\drivers\inferno\6\tracksdata\aalborg.xml copy .\src\drivers\inferno\6\tracksdata\aalborg.xml .\runtimed\drivers\inferno\6\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\6\tracksdata\a-speedway.xml copy .\src\drivers\inferno\6\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\b-speedway.xml copy .\src\drivers\inferno\6\tracksdata\b-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\b-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\car_b-speedway.xml copy .\src\drivers\inferno\6\tracksdata\car_b-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\car_b-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\car_c-speedway.xml copy .\src\drivers\inferno\6\tracksdata\car_c-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\car_c-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\car_d-speedway.xml copy .\src\drivers\inferno\6\tracksdata\car_d-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\car_d-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\car_e-speedway.xml copy .\src\drivers\inferno\6\tracksdata\car_e-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\car_e-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\6\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno\6\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\6\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno\6\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\6\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\6\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno\6\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\6\tracksdata\car_f-speedway.xml copy .\src\drivers\inferno\6\tracksdata\car_f-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\car_f-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\car_g-speedway.xml copy .\src\drivers\inferno\6\tracksdata\car_g-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\car_g-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\6\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno\6\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\6\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\6\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno\6\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\car_g-track-3.xml copy .\src\drivers\inferno\6\tracksdata\car_g-track-3.xml .\runtimed\drivers\inferno\6\tracksdata\car_g-track-3.xml
if exist .\src\drivers\inferno\6\tracksdata\car_michigan.xml copy .\src\drivers\inferno\6\tracksdata\car_michigan.xml .\runtimed\drivers\inferno\6\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\6\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\6\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno\6\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\6\tracksdata\c-speedway.xml copy .\src\drivers\inferno\6\tracksdata\c-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\c-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\d-speedway.xml copy .\src\drivers\inferno\6\tracksdata\d-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\d-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\eroad.xml copy .\src\drivers\inferno\6\tracksdata\eroad.xml .\runtimed\drivers\inferno\6\tracksdata\eroad.xml
if exist .\src\drivers\inferno\6\tracksdata\e-speedway.xml copy .\src\drivers\inferno\6\tracksdata\e-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\e-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-1.xml copy .\src\drivers\inferno\6\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\6\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-2.xml copy .\src\drivers\inferno\6\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\6\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-3.xml copy .\src\drivers\inferno\6\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\6\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-4.xml copy .\src\drivers\inferno\6\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\6\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-5.xml copy .\src\drivers\inferno\6\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\6\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\6\tracksdata\e-track-6.xml copy .\src\drivers\inferno\6\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\6\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\6\tracksdata\f-speedway.xml copy .\src\drivers\inferno\6\tracksdata\f-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\f-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\g-speedway.xml copy .\src\drivers\inferno\6\tracksdata\g-speedway.xml .\runtimed\drivers\inferno\6\tracksdata\g-speedway.xml
if exist .\src\drivers\inferno\6\tracksdata\g-track-1.xml copy .\src\drivers\inferno\6\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\6\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\6\tracksdata\g-track-2.xml copy .\src\drivers\inferno\6\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\6\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\6\tracksdata\g-track-3.xml copy .\src\drivers\inferno\6\tracksdata\g-track-3.xml .\runtimed\drivers\inferno\6\tracksdata\g-track-3.xml
if exist .\src\drivers\inferno\6\tracksdata\michigan.xml copy .\src\drivers\inferno\6\tracksdata\michigan.xml .\runtimed\drivers\inferno\6\tracksdata\michigan.xml
if exist .\src\drivers\inferno\6\tracksdata\wheel-1.xml copy .\src\drivers\inferno\6\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\6\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtimed\drivers\inferno\6
if exist .\src\drivers\inferno\6\defaultcar.xml copy .\src\drivers\inferno\6\defaultcar.xml .\runtimed\drivers\inferno\6\defaultcar.xml
if exist .\src\drivers\inferno\6\default.xml copy .\src\drivers\inferno\6\default.xml .\runtimed\drivers\inferno\6\default.xml
if exist .\src\drivers\inferno\6\logo.rgb copy .\src\drivers\inferno\6\logo.rgb .\runtimed\drivers\inferno\6\logo.rgb
if exist .\src\drivers\inferno\6\Makefile copy .\src\drivers\inferno\6\Makefile .\runtimed\drivers\inferno\6\Makefile
if exist .\src\drivers\inferno\6\porsche-gt3rs.rgb copy .\src\drivers\inferno\6\porsche-gt3rs.rgb .\runtimed\drivers\inferno\6\porsche-gt3rs.rgb

if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\7
if exist .\src\drivers\inferno\7\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\7\tracksdata
if exist .\src\drivers\inferno\7\tracksdata\aalborg.xml copy .\src\drivers\inferno\7\tracksdata\aalborg.xml .\runtimed\drivers\inferno\7\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\7\tracksdata\alpine-1.xml copy .\src\drivers\inferno\7\tracksdata\alpine-1.xml .\runtimed\drivers\inferno\7\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\7\tracksdata\a-speedway.xml copy .\src\drivers\inferno\7\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\7\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\b-speedway.xml copy .\src\drivers\inferno\7\tracksdata\b-speedway.xml .\runtimed\drivers\inferno\7\tracksdata\b-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\7\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno\7\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\7\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\7\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno\7\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\car_d-speedway.xml copy .\src\drivers\inferno\7\tracksdata\car_d-speedway.xml .\runtimed\drivers\inferno\7\tracksdata\car_d-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\car_eroad.xml copy .\src\drivers\inferno\7\tracksdata\car_eroad.xml .\runtimed\drivers\inferno\7\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno\7\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno\7\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno\7\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno\7\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno\7\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\7\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\7\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno\7\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\7\tracksdata\car_g-speedway.xml copy .\src\drivers\inferno\7\tracksdata\car_g-speedway.xml .\runtimed\drivers\inferno\7\tracksdata\car_g-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\7\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno\7\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\7\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno\7\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\car_michigan.xml copy .\src\drivers\inferno\7\tracksdata\car_michigan.xml .\runtimed\drivers\inferno\7\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\7\tracksdata\car_s2.xml copy .\src\drivers\inferno\7\tracksdata\car_s2.xml .\runtimed\drivers\inferno\7\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\7\tracksdata\car_test-1.xml copy .\src\drivers\inferno\7\tracksdata\car_test-1.xml .\runtimed\drivers\inferno\7\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\7\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\7\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno\7\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\7\tracksdata\city-1.xml copy .\src\drivers\inferno\7\tracksdata\city-1.xml .\runtimed\drivers\inferno\7\tracksdata\city-1.xml
if exist .\src\drivers\inferno\7\tracksdata\c-speedway.xml copy .\src\drivers\inferno\7\tracksdata\c-speedway.xml .\runtimed\drivers\inferno\7\tracksdata\c-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\d-speedway.xml copy .\src\drivers\inferno\7\tracksdata\d-speedway.xml .\runtimed\drivers\inferno\7\tracksdata\d-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\eroad.xml copy .\src\drivers\inferno\7\tracksdata\eroad.xml .\runtimed\drivers\inferno\7\tracksdata\eroad.xml
if exist .\src\drivers\inferno\7\tracksdata\e-speedway.xml copy .\src\drivers\inferno\7\tracksdata\e-speedway.xml .\runtimed\drivers\inferno\7\tracksdata\e-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-1.xml copy .\src\drivers\inferno\7\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\7\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-2.xml copy .\src\drivers\inferno\7\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\7\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-3.xml copy .\src\drivers\inferno\7\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\7\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-4.xml copy .\src\drivers\inferno\7\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\7\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-5.xml copy .\src\drivers\inferno\7\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\7\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\7\tracksdata\e-track-6.xml copy .\src\drivers\inferno\7\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\7\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\7\tracksdata\f-speedway.xml copy .\src\drivers\inferno\7\tracksdata\f-speedway.xml .\runtimed\drivers\inferno\7\tracksdata\f-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\g-speedway.xml copy .\src\drivers\inferno\7\tracksdata\g-speedway.xml .\runtimed\drivers\inferno\7\tracksdata\g-speedway.xml
if exist .\src\drivers\inferno\7\tracksdata\g-track-1.xml copy .\src\drivers\inferno\7\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\7\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\7\tracksdata\g-track-2.xml copy .\src\drivers\inferno\7\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\7\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\7\tracksdata\michigan.xml copy .\src\drivers\inferno\7\tracksdata\michigan.xml .\runtimed\drivers\inferno\7\tracksdata\michigan.xml
if exist .\src\drivers\inferno\7\tracksdata\s2.xml copy .\src\drivers\inferno\7\tracksdata\s2.xml .\runtimed\drivers\inferno\7\tracksdata\s2.xml
if exist .\src\drivers\inferno\7\tracksdata\wheel-1.xml copy .\src\drivers\inferno\7\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\7\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtimed\drivers\inferno\7
if exist .\src\drivers\inferno\7\defaultcar.xml copy .\src\drivers\inferno\7\defaultcar.xml .\runtimed\drivers\inferno\7\defaultcar.xml
if exist .\src\drivers\inferno\7\default.xml copy .\src\drivers\inferno\7\default.xml .\runtimed\drivers\inferno\7\default.xml
if exist .\src\drivers\inferno\7\logo.rgb copy .\src\drivers\inferno\7\logo.rgb .\runtimed\drivers\inferno\7\logo.rgb
if exist .\src\drivers\inferno\7\lotus-gt1.rgb copy .\src\drivers\inferno\7\lotus-gt1.rgb .\runtimed\drivers\inferno\7\lotus-gt1.rgb
if exist .\src\drivers\inferno\7\Makefile copy .\src\drivers\inferno\7\Makefile .\runtimed\drivers\inferno\7\Makefile

if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\8
if exist .\src\drivers\inferno\8\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\8\tracksdata
if exist .\src\drivers\inferno\8\tracksdata\aalborg.xml copy .\src\drivers\inferno\8\tracksdata\aalborg.xml .\runtimed\drivers\inferno\8\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\8\tracksdata\alpine-1.xml copy .\src\drivers\inferno\8\tracksdata\alpine-1.xml .\runtimed\drivers\inferno\8\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\8\tracksdata\a-speedway.xml copy .\src\drivers\inferno\8\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\8\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\8\tracksdata\b-speedway.xml copy .\src\drivers\inferno\8\tracksdata\b-speedway.xml .\runtimed\drivers\inferno\8\tracksdata\b-speedway.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-1.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-1.xml .\runtimed\drivers\inferno\8\tracksdata\car_dirt-1.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-2.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-2.xml .\runtimed\drivers\inferno\8\tracksdata\car_dirt-2.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-3.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-3.xml .\runtimed\drivers\inferno\8\tracksdata\car_dirt-3.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-4.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-4.xml .\runtimed\drivers\inferno\8\tracksdata\car_dirt-4.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-5.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-5.xml .\runtimed\drivers\inferno\8\tracksdata\car_dirt-5.xml
if exist .\src\drivers\inferno\8\tracksdata\car_dirt-6.xml copy .\src\drivers\inferno\8\tracksdata\car_dirt-6.xml .\runtimed\drivers\inferno\8\tracksdata\car_dirt-6.xml
if exist .\src\drivers\inferno\8\tracksdata\car_g-track-3.xml copy .\src\drivers\inferno\8\tracksdata\car_g-track-3.xml .\runtimed\drivers\inferno\8\tracksdata\car_g-track-3.xml
if exist .\src\drivers\inferno\8\tracksdata\car_mixed-1.xml copy .\src\drivers\inferno\8\tracksdata\car_mixed-1.xml .\runtimed\drivers\inferno\8\tracksdata\car_mixed-1.xml
if exist .\src\drivers\inferno\8\tracksdata\car_mixed-2.xml copy .\src\drivers\inferno\8\tracksdata\car_mixed-2.xml .\runtimed\drivers\inferno\8\tracksdata\car_mixed-2.xml
if exist .\src\drivers\inferno\8\tracksdata\c-speedway.xml copy .\src\drivers\inferno\8\tracksdata\c-speedway.xml .\runtimed\drivers\inferno\8\tracksdata\c-speedway.xml
if exist .\src\drivers\inferno\8\tracksdata\d-speedway.xml copy .\src\drivers\inferno\8\tracksdata\d-speedway.xml .\runtimed\drivers\inferno\8\tracksdata\d-speedway.xml
if exist .\src\drivers\inferno\8\tracksdata\eroad.xml copy .\src\drivers\inferno\8\tracksdata\eroad.xml .\runtimed\drivers\inferno\8\tracksdata\eroad.xml
if exist .\src\drivers\inferno\8\tracksdata\e-speedway.xml copy .\src\drivers\inferno\8\tracksdata\e-speedway.xml .\runtimed\drivers\inferno\8\tracksdata\e-speedway.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-1.xml copy .\src\drivers\inferno\8\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\8\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-2.xml copy .\src\drivers\inferno\8\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\8\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-3.xml copy .\src\drivers\inferno\8\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\8\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-4.xml copy .\src\drivers\inferno\8\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\8\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-5.xml copy .\src\drivers\inferno\8\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\8\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\8\tracksdata\e-track-6.xml copy .\src\drivers\inferno\8\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\8\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\8\tracksdata\f-speedway.xml copy .\src\drivers\inferno\8\tracksdata\f-speedway.xml .\runtimed\drivers\inferno\8\tracksdata\f-speedway.xml
if exist .\src\drivers\inferno\8\tracksdata\g-speedway.xml copy .\src\drivers\inferno\8\tracksdata\g-speedway.xml .\runtimed\drivers\inferno\8\tracksdata\g-speedway.xml
if exist .\src\drivers\inferno\8\tracksdata\g-track-1.xml copy .\src\drivers\inferno\8\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\8\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\8\tracksdata\g-track-2.xml copy .\src\drivers\inferno\8\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\8\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\8\tracksdata\g-track-3.xml copy .\src\drivers\inferno\8\tracksdata\g-track-3.xml .\runtimed\drivers\inferno\8\tracksdata\g-track-3.xml
if exist .\src\drivers\inferno\8\tracksdata\michigan.xml copy .\src\drivers\inferno\8\tracksdata\michigan.xml .\runtimed\drivers\inferno\8\tracksdata\michigan.xml
if exist .\src\drivers\inferno\8\tracksdata\spring.xml copy .\src\drivers\inferno\8\tracksdata\spring.xml .\runtimed\drivers\inferno\8\tracksdata\spring.xml
if exist .\src\drivers\inferno\8\tracksdata\wheel-1.xml copy .\src\drivers\inferno\8\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\8\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtimed\drivers\inferno\8
if exist .\src\drivers\inferno\8\defaultcar.xml copy .\src\drivers\inferno\8\defaultcar.xml .\runtimed\drivers\inferno\8\defaultcar.xml
if exist .\src\drivers\inferno\8\default.xml copy .\src\drivers\inferno\8\default.xml .\runtimed\drivers\inferno\8\default.xml
if exist .\src\drivers\inferno\8\logo.rgb copy .\src\drivers\inferno\8\logo.rgb .\runtimed\drivers\inferno\8\logo.rgb
if exist .\src\drivers\inferno\8\Makefile copy .\src\drivers\inferno\8\Makefile .\runtimed\drivers\inferno\8\Makefile
if exist .\src\drivers\inferno\8\p406.rgb copy .\src\drivers\inferno\8\p406.rgb .\runtimed\drivers\inferno\8\p406.rgb

if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\9
if exist .\src\drivers\inferno\9\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno\9\tracksdata
if exist .\src\drivers\inferno\9\tracksdata\aalborg.xml copy .\src\drivers\inferno\9\tracksdata\aalborg.xml .\runtimed\drivers\inferno\9\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\9\tracksdata\alpine-1.xml copy .\src\drivers\inferno\9\tracksdata\alpine-1.xml .\runtimed\drivers\inferno\9\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\9\tracksdata\a-speedway.xml copy .\src\drivers\inferno\9\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\9\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\b-speedway.xml copy .\src\drivers\inferno\9\tracksdata\b-speedway.xml .\runtimed\drivers\inferno\9\tracksdata\b-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\9\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno\9\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\9\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\9\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno\9\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\car_d-speedway.xml copy .\src\drivers\inferno\9\tracksdata\car_d-speedway.xml .\runtimed\drivers\inferno\9\tracksdata\car_d-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\car_eroad.xml copy .\src\drivers\inferno\9\tracksdata\car_eroad.xml .\runtimed\drivers\inferno\9\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno\9\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno\9\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno\9\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno\9\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno\9\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\9\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\9\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno\9\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\9\tracksdata\car_g-speedway.xml copy .\src\drivers\inferno\9\tracksdata\car_g-speedway.xml .\runtimed\drivers\inferno\9\tracksdata\car_g-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\9\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno\9\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\9\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno\9\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\car_michigan.xml copy .\src\drivers\inferno\9\tracksdata\car_michigan.xml .\runtimed\drivers\inferno\9\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\9\tracksdata\car_s2.xml copy .\src\drivers\inferno\9\tracksdata\car_s2.xml .\runtimed\drivers\inferno\9\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\9\tracksdata\car_test-1.xml copy .\src\drivers\inferno\9\tracksdata\car_test-1.xml .\runtimed\drivers\inferno\9\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\9\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\9\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno\9\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\9\tracksdata\city-1.xml copy .\src\drivers\inferno\9\tracksdata\city-1.xml .\runtimed\drivers\inferno\9\tracksdata\city-1.xml
if exist .\src\drivers\inferno\9\tracksdata\c-speedway.xml copy .\src\drivers\inferno\9\tracksdata\c-speedway.xml .\runtimed\drivers\inferno\9\tracksdata\c-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\d-speedway.xml copy .\src\drivers\inferno\9\tracksdata\d-speedway.xml .\runtimed\drivers\inferno\9\tracksdata\d-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\eroad.xml copy .\src\drivers\inferno\9\tracksdata\eroad.xml .\runtimed\drivers\inferno\9\tracksdata\eroad.xml
if exist .\src\drivers\inferno\9\tracksdata\e-speedway.xml copy .\src\drivers\inferno\9\tracksdata\e-speedway.xml .\runtimed\drivers\inferno\9\tracksdata\e-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-1.xml copy .\src\drivers\inferno\9\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\9\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-2.xml copy .\src\drivers\inferno\9\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\9\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-3.xml copy .\src\drivers\inferno\9\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\9\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-4.xml copy .\src\drivers\inferno\9\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\9\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-5.xml copy .\src\drivers\inferno\9\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\9\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\9\tracksdata\e-track-6.xml copy .\src\drivers\inferno\9\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\9\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\9\tracksdata\f-speedway.xml copy .\src\drivers\inferno\9\tracksdata\f-speedway.xml .\runtimed\drivers\inferno\9\tracksdata\f-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\g-speedway.xml copy .\src\drivers\inferno\9\tracksdata\g-speedway.xml .\runtimed\drivers\inferno\9\tracksdata\g-speedway.xml
if exist .\src\drivers\inferno\9\tracksdata\g-track-1.xml copy .\src\drivers\inferno\9\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\9\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\9\tracksdata\g-track-2.xml copy .\src\drivers\inferno\9\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\9\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\9\tracksdata\michigan.xml copy .\src\drivers\inferno\9\tracksdata\michigan.xml .\runtimed\drivers\inferno\9\tracksdata\michigan.xml
if exist .\src\drivers\inferno\9\tracksdata\s2.xml copy .\src\drivers\inferno\9\tracksdata\s2.xml .\runtimed\drivers\inferno\9\tracksdata\s2.xml
if exist .\src\drivers\inferno\9\tracksdata\wheel-1.xml copy .\src\drivers\inferno\9\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\9\tracksdata\wheel-1.xml

if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtimed\drivers\inferno\9
if exist .\src\drivers\inferno\9\defaultcar.xml copy .\src\drivers\inferno\9\defaultcar.xml .\runtimed\drivers\inferno\9\defaultcar.xml
if exist .\src\drivers\inferno\9\default.xml copy .\src\drivers\inferno\9\default.xml .\runtimed\drivers\inferno\9\default.xml
if exist .\src\drivers\inferno\9\logo.rgb copy .\src\drivers\inferno\9\logo.rgb .\runtimed\drivers\inferno\9\logo.rgb
if exist .\src\drivers\inferno\9\Makefile copy .\src\drivers\inferno\9\Makefile .\runtimed\drivers\inferno\9\Makefile
if exist .\src\drivers\inferno\9\vm-x2.rgb copy .\src\drivers\inferno\9\vm-x2.rgb .\runtimed\drivers\inferno\9\vm-x2.rgb

if exist .\src\drivers\inferno\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno\*.* call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\inferno.xml copy .\src\drivers\inferno\inferno.xml .\runtimed\drivers\inferno\inferno.xml
if exist .\src\drivers\inferno\car1.xml copy .\src\drivers\inferno\car1.xml .\runtimed\drivers\inferno\car1.xml
if exist .\src\drivers\inferno\logo.rgb copy .\src\drivers\inferno\logo.rgb .\runtimed\drivers\inferno\logo.rgb
if exist .\src\drivers\inferno\mclaren-f1.rgb copy .\src\drivers\inferno\mclaren-f1.rgb .\runtimed\drivers\inferno\mclaren-f1.rgb

if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtimed\drivers\inferno2\1
if exist .\src\drivers\inferno2\1\defaultcar.xml copy .\src\drivers\inferno2\1\defaultcar.xml .\runtimed\drivers\inferno2\1\defaultcar.xml
if exist .\src\drivers\inferno2\1\default.xml copy .\src\drivers\inferno2\1\default.xml .\runtimed\drivers\inferno2\1\default.xml
if exist .\src\drivers\inferno2\1\Makefile copy .\src\drivers\inferno2\1\Makefile .\runtimed\drivers\inferno2\1\Makefile

if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtimed\drivers\inferno2\10
if exist .\src\drivers\inferno2\10\defaultcar.xml copy .\src\drivers\inferno2\10\defaultcar.xml .\runtimed\drivers\inferno2\10\defaultcar.xml
if exist .\src\drivers\inferno2\10\default.xml copy .\src\drivers\inferno2\10\default.xml .\runtimed\drivers\inferno2\10\default.xml
if exist .\src\drivers\inferno2\10\Makefile copy .\src\drivers\inferno2\10\Makefile .\runtimed\drivers\inferno2\10\Makefile

if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtimed\drivers\inferno2\2
if exist .\src\drivers\inferno2\2\defaultcar.xml copy .\src\drivers\inferno2\2\defaultcar.xml .\runtimed\drivers\inferno2\2\defaultcar.xml
if exist .\src\drivers\inferno2\2\default.xml copy .\src\drivers\inferno2\2\default.xml .\runtimed\drivers\inferno2\2\default.xml
if exist .\src\drivers\inferno2\2\Makefile copy .\src\drivers\inferno2\2\Makefile .\runtimed\drivers\inferno2\2\Makefile

if exist .\src\drivers\inferno2\3\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\3\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\3\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\3\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno2\3
if exist .\src\drivers\inferno2\3\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno2\3\tracksdata
if exist .\src\drivers\inferno2\3\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno2\3\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno2\3\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno2\3\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno2\3\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno2\3\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno2\3\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno2\3\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno2\3\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno2\3\tracksdata\car_g-track-3.xml copy .\src\drivers\inferno2\3\tracksdata\car_g-track-3.xml .\runtimed\drivers\inferno2\3\tracksdata\car_g-track-3.xml
if exist .\src\drivers\inferno2\3\tracksdata\e-track-2.xml copy .\src\drivers\inferno2\3\tracksdata\e-track-2.xml .\runtimed\drivers\inferno2\3\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno2\3\tracksdata\e-track-6.xml copy .\src\drivers\inferno2\3\tracksdata\e-track-6.xml .\runtimed\drivers\inferno2\3\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno2\3\tracksdata\g-track-2.xml copy .\src\drivers\inferno2\3\tracksdata\g-track-2.xml .\runtimed\drivers\inferno2\3\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno2\3\tracksdata\g-track-3.xml copy .\src\drivers\inferno2\3\tracksdata\g-track-3.xml .\runtimed\drivers\inferno2\3\tracksdata\g-track-3.xml

if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtimed\drivers\inferno2\3
if exist .\src\drivers\inferno2\3\defaultcar.xml copy .\src\drivers\inferno2\3\defaultcar.xml .\runtimed\drivers\inferno2\3\defaultcar.xml
if exist .\src\drivers\inferno2\3\default.xml copy .\src\drivers\inferno2\3\default.xml .\runtimed\drivers\inferno2\3\default.xml
if exist .\src\drivers\inferno2\3\Makefile copy .\src\drivers\inferno2\3\Makefile .\runtimed\drivers\inferno2\3\Makefile

if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtimed\drivers\inferno2\4
if exist .\src\drivers\inferno2\4\defaultcar.xml copy .\src\drivers\inferno2\4\defaultcar.xml .\runtimed\drivers\inferno2\4\defaultcar.xml
if exist .\src\drivers\inferno2\4\default.xml copy .\src\drivers\inferno2\4\default.xml .\runtimed\drivers\inferno2\4\default.xml
if exist .\src\drivers\inferno2\4\Makefile copy .\src\drivers\inferno2\4\Makefile .\runtimed\drivers\inferno2\4\Makefile

if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtimed\drivers\inferno2\5
if exist .\src\drivers\inferno2\5\defaultcar.xml copy .\src\drivers\inferno2\5\defaultcar.xml .\runtimed\drivers\inferno2\5\defaultcar.xml
if exist .\src\drivers\inferno2\5\default.xml copy .\src\drivers\inferno2\5\default.xml .\runtimed\drivers\inferno2\5\default.xml
if exist .\src\drivers\inferno2\5\Makefile copy .\src\drivers\inferno2\5\Makefile .\runtimed\drivers\inferno2\5\Makefile

if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtimed\drivers\inferno2\6
if exist .\src\drivers\inferno2\6\defaultcar.xml copy .\src\drivers\inferno2\6\defaultcar.xml .\runtimed\drivers\inferno2\6\defaultcar.xml
if exist .\src\drivers\inferno2\6\default.xml copy .\src\drivers\inferno2\6\default.xml .\runtimed\drivers\inferno2\6\default.xml
if exist .\src\drivers\inferno2\6\Makefile copy .\src\drivers\inferno2\6\Makefile .\runtimed\drivers\inferno2\6\Makefile

if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtimed\drivers\inferno2\7
if exist .\src\drivers\inferno2\7\defaultcar.xml copy .\src\drivers\inferno2\7\defaultcar.xml .\runtimed\drivers\inferno2\7\defaultcar.xml
if exist .\src\drivers\inferno2\7\default.xml copy .\src\drivers\inferno2\7\default.xml .\runtimed\drivers\inferno2\7\default.xml
if exist .\src\drivers\inferno2\7\Makefile copy .\src\drivers\inferno2\7\Makefile .\runtimed\drivers\inferno2\7\Makefile

if exist .\src\drivers\inferno2\8\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\8\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\8\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\8\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno2\8
if exist .\src\drivers\inferno2\8\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno2\8\tracksdata
if exist .\src\drivers\inferno2\8\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno2\8\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno2\8\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno2\8\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno2\8\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno2\8\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno2\8\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno2\8\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno2\8\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno2\8\tracksdata\car_g-track-3.xml copy .\src\drivers\inferno2\8\tracksdata\car_g-track-3.xml .\runtimed\drivers\inferno2\8\tracksdata\car_g-track-3.xml
if exist .\src\drivers\inferno2\8\tracksdata\e-track-2.xml copy .\src\drivers\inferno2\8\tracksdata\e-track-2.xml .\runtimed\drivers\inferno2\8\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno2\8\tracksdata\e-track-6.xml copy .\src\drivers\inferno2\8\tracksdata\e-track-6.xml .\runtimed\drivers\inferno2\8\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno2\8\tracksdata\g-track-2.xml copy .\src\drivers\inferno2\8\tracksdata\g-track-2.xml .\runtimed\drivers\inferno2\8\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno2\8\tracksdata\g-track-3.xml copy .\src\drivers\inferno2\8\tracksdata\g-track-3.xml .\runtimed\drivers\inferno2\8\tracksdata\g-track-3.xml

if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtimed\drivers\inferno2\8
if exist .\src\drivers\inferno2\8\defaultcar.xml copy .\src\drivers\inferno2\8\defaultcar.xml .\runtimed\drivers\inferno2\8\defaultcar.xml
if exist .\src\drivers\inferno2\8\default.xml copy .\src\drivers\inferno2\8\default.xml .\runtimed\drivers\inferno2\8\default.xml
if exist .\src\drivers\inferno2\8\Makefile copy .\src\drivers\inferno2\8\Makefile .\runtimed\drivers\inferno2\8\Makefile

if exist .\src\drivers\inferno2\9\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\9\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\9\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\9\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno2\9
if exist .\src\drivers\inferno2\9\tracksdata\*.* call .\create_dir .\runtimed\drivers\inferno2\9\tracksdata
if exist .\src\drivers\inferno2\9\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno2\9\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno2\9\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno2\9\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno2\9\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno2\9\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno2\9\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno2\9\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno2\9\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno2\9\tracksdata\e-track-4.xml copy .\src\drivers\inferno2\9\tracksdata\e-track-4.xml .\runtimed\drivers\inferno2\9\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno2\9\tracksdata\e-track-6.xml copy .\src\drivers\inferno2\9\tracksdata\e-track-6.xml .\runtimed\drivers\inferno2\9\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno2\9\tracksdata\g-track-2.xml copy .\src\drivers\inferno2\9\tracksdata\g-track-2.xml .\runtimed\drivers\inferno2\9\tracksdata\g-track-2.xml

if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtimed\drivers\inferno2\9
if exist .\src\drivers\inferno2\9\defaultcar.xml copy .\src\drivers\inferno2\9\defaultcar.xml .\runtimed\drivers\inferno2\9\defaultcar.xml
if exist .\src\drivers\inferno2\9\default.xml copy .\src\drivers\inferno2\9\default.xml .\runtimed\drivers\inferno2\9\default.xml
if exist .\src\drivers\inferno2\9\Makefile copy .\src\drivers\inferno2\9\Makefile .\runtimed\drivers\inferno2\9\Makefile

if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\inferno2.xml copy .\src\drivers\inferno2\inferno2.xml .\runtimed\drivers\inferno2\inferno2.xml
if exist .\src\drivers\inferno2\logo.rgb copy .\src\drivers\inferno2\logo.rgb .\runtimed\drivers\inferno2\logo.rgb

if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtimed
if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtimed\drivers\K1999
if exist .\src\drivers\K1999\1\*.* call .\create_dir .\runtimed\drivers\K1999\1
if exist .\src\drivers\K1999\1\buggy.rgb copy .\src\drivers\K1999\1\buggy.rgb .\runtimed\drivers\K1999\1\buggy.rgb
if exist .\src\drivers\K1999\1\settings.xml copy .\src\drivers\K1999\1\settings.xml .\runtimed\drivers\K1999\1\settings.xml

if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtimed
if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtimed\drivers\K1999
if exist .\src\drivers\K1999\2\*.* call .\create_dir .\runtimed\drivers\K1999\2
if exist .\src\drivers\K1999\2\cg-nascar-rwd.rgb copy .\src\drivers\K1999\2\cg-nascar-rwd.rgb .\runtimed\drivers\K1999\2\cg-nascar-rwd.rgb
if exist .\src\drivers\K1999\2\settings.xml copy .\src\drivers\K1999\2\settings.xml .\runtimed\drivers\K1999\2\settings.xml

if exist .\src\drivers\K1999\*.* call .\create_dir .\runtimed
if exist .\src\drivers\K1999\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\K1999\*.* call .\create_dir .\runtimed\drivers\K1999
if exist .\src\drivers\K1999\K1999.xml copy .\src\drivers\K1999\K1999.xml .\runtimed\drivers\K1999\K1999.xml
if exist .\src\drivers\K1999\logo.rgb copy .\src\drivers\K1999\logo.rgb .\runtimed\drivers\K1999\logo.rgb

if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtimed\drivers\lliaw
if exist .\src\drivers\lliaw\tracksdata\*.* call .\create_dir .\runtimed\drivers\lliaw\tracksdata
if exist .\src\drivers\lliaw\tracksdata\car_e-track-3.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-3.xml .\runtimed\drivers\lliaw\tracksdata\car_e-track-3.xml
if exist .\src\drivers\lliaw\tracksdata\car_e-track-4.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-4.xml .\runtimed\drivers\lliaw\tracksdata\car_e-track-4.xml
if exist .\src\drivers\lliaw\tracksdata\car_e-track-6.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-6.xml .\runtimed\drivers\lliaw\tracksdata\car_e-track-6.xml
if exist .\src\drivers\lliaw\tracksdata\car_eroad.xml copy .\src\drivers\lliaw\tracksdata\car_eroad.xml .\runtimed\drivers\lliaw\tracksdata\car_eroad.xml
if exist .\src\drivers\lliaw\tracksdata\car_g-track-3.xml copy .\src\drivers\lliaw\tracksdata\car_g-track-3.xml .\runtimed\drivers\lliaw\tracksdata\car_g-track-3.xml

if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtimed
if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtimed\drivers\lliaw
if exist .\src\drivers\lliaw\lliaw.xml copy .\src\drivers\lliaw\lliaw.xml .\runtimed\drivers\lliaw\lliaw.xml
if exist .\src\drivers\lliaw\car.xml copy .\src\drivers\lliaw\car.xml .\runtimed\drivers\lliaw\car.xml
if exist .\src\drivers\lliaw\viper-gts-r.rgb copy .\src\drivers\lliaw\viper-gts-r.rgb .\runtimed\drivers\lliaw\viper-gts-r.rgb
if exist .\src\drivers\lliaw\logo.rgb copy .\src\drivers\lliaw\logo.rgb .\runtimed\drivers\lliaw\logo.rgb

if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtimed
if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtimed\drivers\sparkle
if exist .\src\drivers\sparkle\0\*.* call .\create_dir .\runtimed\drivers\sparkle\0
if exist .\src\drivers\sparkle\0\baja-bug.rgb copy .\src\drivers\sparkle\0\baja-bug.rgb .\runtimed\drivers\sparkle\0\baja-bug.rgb
if exist .\src\drivers\sparkle\0\default.xml copy .\src\drivers\sparkle\0\default.xml .\runtimed\drivers\sparkle\0\default.xml

if exist .\src\drivers\sparkle\*.* call .\create_dir .\runtimed
if exist .\src\drivers\sparkle\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\sparkle\*.* call .\create_dir .\runtimed\drivers\sparkle
if exist .\src\drivers\sparkle\sparkle.xml copy .\src\drivers\sparkle\sparkle.xml .\runtimed\drivers\sparkle\sparkle.xml
if exist .\src\drivers\sparkle\logo.rgb copy .\src\drivers\sparkle\logo.rgb .\runtimed\drivers\sparkle\logo.rgb

if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtimed\drivers\tanhoj
if exist .\src\drivers\tanhoj\tracksdata\*.* call .\create_dir .\runtimed\drivers\tanhoj\tracksdata
if exist .\src\drivers\tanhoj\tracksdata\aalborg.xml copy .\src\drivers\tanhoj\tracksdata\aalborg.xml .\runtimed\drivers\tanhoj\tracksdata\aalborg.xml
if exist .\src\drivers\tanhoj\tracksdata\a-speedway.xml copy .\src\drivers\tanhoj\tracksdata\a-speedway.xml .\runtimed\drivers\tanhoj\tracksdata\a-speedway.xml
if exist .\src\drivers\tanhoj\tracksdata\car_aalborg.xml copy .\src\drivers\tanhoj\tracksdata\car_aalborg.xml .\runtimed\drivers\tanhoj\tracksdata\car_aalborg.xml
if exist .\src\drivers\tanhoj\tracksdata\car_a-speedway.xml copy .\src\drivers\tanhoj\tracksdata\car_a-speedway.xml .\runtimed\drivers\tanhoj\tracksdata\car_a-speedway.xml
if exist .\src\drivers\tanhoj\tracksdata\car_eroad.xml copy .\src\drivers\tanhoj\tracksdata\car_eroad.xml .\runtimed\drivers\tanhoj\tracksdata\car_eroad.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-1.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-1.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-2.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-2.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-2.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-3.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-3.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-4.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-4.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-4.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-5.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-5.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-5.xml
if exist .\src\drivers\tanhoj\tracksdata\car_e-track-6.xml copy .\src\drivers\tanhoj\tracksdata\car_e-track-6.xml .\runtimed\drivers\tanhoj\tracksdata\car_e-track-6.xml
if exist .\src\drivers\tanhoj\tracksdata\car_g-track-1.xml copy .\src\drivers\tanhoj\tracksdata\car_g-track-1.xml .\runtimed\drivers\tanhoj\tracksdata\car_g-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\car_g-track-3.xml copy .\src\drivers\tanhoj\tracksdata\car_g-track-3.xml .\runtimed\drivers\tanhoj\tracksdata\car_g-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\car_michigan.xml copy .\src\drivers\tanhoj\tracksdata\car_michigan.xml .\runtimed\drivers\tanhoj\tracksdata\car_michigan.xml
if exist .\src\drivers\tanhoj\tracksdata\car_s2.xml copy .\src\drivers\tanhoj\tracksdata\car_s2.xml .\runtimed\drivers\tanhoj\tracksdata\car_s2.xml
if exist .\src\drivers\tanhoj\tracksdata\car_test-1.xml copy .\src\drivers\tanhoj\tracksdata\car_test-1.xml .\runtimed\drivers\tanhoj\tracksdata\car_test-1.xml
if exist .\src\drivers\tanhoj\tracksdata\car_wheel-1.xml copy .\src\drivers\tanhoj\tracksdata\car_wheel-1.xml .\runtimed\drivers\tanhoj\tracksdata\car_wheel-1.xml
if exist .\src\drivers\tanhoj\tracksdata\city-1.xml copy .\src\drivers\tanhoj\tracksdata\city-1.xml .\runtimed\drivers\tanhoj\tracksdata\city-1.xml
if exist .\src\drivers\tanhoj\tracksdata\dirt-2.xml copy .\src\drivers\tanhoj\tracksdata\dirt-2.xml .\runtimed\drivers\tanhoj\tracksdata\dirt-2.xml
if exist .\src\drivers\tanhoj\tracksdata\eroad.xml copy .\src\drivers\tanhoj\tracksdata\eroad.xml .\runtimed\drivers\tanhoj\tracksdata\eroad.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-1.xml copy .\src\drivers\tanhoj\tracksdata\e-track-1.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-2.xml copy .\src\drivers\tanhoj\tracksdata\e-track-2.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-2.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-3.xml copy .\src\drivers\tanhoj\tracksdata\e-track-3.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-4.xml copy .\src\drivers\tanhoj\tracksdata\e-track-4.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-4.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-5.xml copy .\src\drivers\tanhoj\tracksdata\e-track-5.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-5.xml
if exist .\src\drivers\tanhoj\tracksdata\e-track-6.xml copy .\src\drivers\tanhoj\tracksdata\e-track-6.xml .\runtimed\drivers\tanhoj\tracksdata\e-track-6.xml
if exist .\src\drivers\tanhoj\tracksdata\g-track-1.xml copy .\src\drivers\tanhoj\tracksdata\g-track-1.xml .\runtimed\drivers\tanhoj\tracksdata\g-track-1.xml
if exist .\src\drivers\tanhoj\tracksdata\g-track-3.xml copy .\src\drivers\tanhoj\tracksdata\g-track-3.xml .\runtimed\drivers\tanhoj\tracksdata\g-track-3.xml
if exist .\src\drivers\tanhoj\tracksdata\michigan.xml copy .\src\drivers\tanhoj\tracksdata\michigan.xml .\runtimed\drivers\tanhoj\tracksdata\michigan.xml
if exist .\src\drivers\tanhoj\tracksdata\s2.xml copy .\src\drivers\tanhoj\tracksdata\s2.xml .\runtimed\drivers\tanhoj\tracksdata\s2.xml
if exist .\src\drivers\tanhoj\tracksdata\wheel-1.xml copy .\src\drivers\tanhoj\tracksdata\wheel-1.xml .\runtimed\drivers\tanhoj\tracksdata\wheel-1.xml

if exist .\src\drivers\tanhoj\*.* call .\create_dir .\runtimed
if exist .\src\drivers\tanhoj\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\tanhoj\*.* call .\create_dir .\runtimed\drivers\tanhoj
if exist .\src\drivers\tanhoj\tanhoj.xml copy .\src\drivers\tanhoj\tanhoj.xml .\runtimed\drivers\tanhoj\tanhoj.xml
if exist .\src\drivers\tanhoj\car1.xml copy .\src\drivers\tanhoj\car1.xml .\runtimed\drivers\tanhoj\car1.xml
if exist .\src\drivers\tanhoj\logo.rgb copy .\src\drivers\tanhoj\logo.rgb .\runtimed\drivers\tanhoj\logo.rgb
if exist .\src\drivers\tanhoj\cg-nascar-rwd.rgb copy .\src\drivers\tanhoj\cg-nascar-rwd.rgb .\runtimed\drivers\tanhoj\cg-nascar-rwd.rgb

if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtimed
if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtimed\drivers\tita
if exist .\src\drivers\tita\tracksdata\*.* call .\create_dir .\runtimed\drivers\tita\tracksdata
if exist .\src\drivers\tita\tracksdata\aalborg.xml copy .\src\drivers\tita\tracksdata\aalborg.xml .\runtimed\drivers\tita\tracksdata\aalborg.xml
if exist .\src\drivers\tita\tracksdata\a-speedway.xml copy .\src\drivers\tita\tracksdata\a-speedway.xml .\runtimed\drivers\tita\tracksdata\a-speedway.xml
if exist .\src\drivers\tita\tracksdata\car_aalborg.xml copy .\src\drivers\tita\tracksdata\car_aalborg.xml .\runtimed\drivers\tita\tracksdata\car_aalborg.xml
if exist .\src\drivers\tita\tracksdata\car_a-speedway.xml copy .\src\drivers\tita\tracksdata\car_a-speedway.xml .\runtimed\drivers\tita\tracksdata\car_a-speedway.xml
if exist .\src\drivers\tita\tracksdata\car_eroad.xml copy .\src\drivers\tita\tracksdata\car_eroad.xml .\runtimed\drivers\tita\tracksdata\car_eroad.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-1.xml copy .\src\drivers\tita\tracksdata\car_e-track-1.xml .\runtimed\drivers\tita\tracksdata\car_e-track-1.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-2.xml copy .\src\drivers\tita\tracksdata\car_e-track-2.xml .\runtimed\drivers\tita\tracksdata\car_e-track-2.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-3.xml copy .\src\drivers\tita\tracksdata\car_e-track-3.xml .\runtimed\drivers\tita\tracksdata\car_e-track-3.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-4.xml copy .\src\drivers\tita\tracksdata\car_e-track-4.xml .\runtimed\drivers\tita\tracksdata\car_e-track-4.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-5.xml copy .\src\drivers\tita\tracksdata\car_e-track-5.xml .\runtimed\drivers\tita\tracksdata\car_e-track-5.xml
if exist .\src\drivers\tita\tracksdata\car_e-track-6.xml copy .\src\drivers\tita\tracksdata\car_e-track-6.xml .\runtimed\drivers\tita\tracksdata\car_e-track-6.xml
if exist .\src\drivers\tita\tracksdata\car_g-track-1.xml copy .\src\drivers\tita\tracksdata\car_g-track-1.xml .\runtimed\drivers\tita\tracksdata\car_g-track-1.xml
if exist .\src\drivers\tita\tracksdata\car_g-track-3.xml copy .\src\drivers\tita\tracksdata\car_g-track-3.xml .\runtimed\drivers\tita\tracksdata\car_g-track-3.xml
if exist .\src\drivers\tita\tracksdata\car_michigan.xml copy .\src\drivers\tita\tracksdata\car_michigan.xml .\runtimed\drivers\tita\tracksdata\car_michigan.xml
if exist .\src\drivers\tita\tracksdata\car_s2.xml copy .\src\drivers\tita\tracksdata\car_s2.xml .\runtimed\drivers\tita\tracksdata\car_s2.xml
if exist .\src\drivers\tita\tracksdata\car_test-1.xml copy .\src\drivers\tita\tracksdata\car_test-1.xml .\runtimed\drivers\tita\tracksdata\car_test-1.xml
if exist .\src\drivers\tita\tracksdata\car_wheel-1.xml copy .\src\drivers\tita\tracksdata\car_wheel-1.xml .\runtimed\drivers\tita\tracksdata\car_wheel-1.xml
if exist .\src\drivers\tita\tracksdata\city-1.xml copy .\src\drivers\tita\tracksdata\city-1.xml .\runtimed\drivers\tita\tracksdata\city-1.xml
if exist .\src\drivers\tita\tracksdata\eroad.xml copy .\src\drivers\tita\tracksdata\eroad.xml .\runtimed\drivers\tita\tracksdata\eroad.xml
if exist .\src\drivers\tita\tracksdata\e-track-1.xml copy .\src\drivers\tita\tracksdata\e-track-1.xml .\runtimed\drivers\tita\tracksdata\e-track-1.xml
if exist .\src\drivers\tita\tracksdata\e-track-2.xml copy .\src\drivers\tita\tracksdata\e-track-2.xml .\runtimed\drivers\tita\tracksdata\e-track-2.xml
if exist .\src\drivers\tita\tracksdata\e-track-3.xml copy .\src\drivers\tita\tracksdata\e-track-3.xml .\runtimed\drivers\tita\tracksdata\e-track-3.xml
if exist .\src\drivers\tita\tracksdata\e-track-4.xml copy .\src\drivers\tita\tracksdata\e-track-4.xml .\runtimed\drivers\tita\tracksdata\e-track-4.xml
if exist .\src\drivers\tita\tracksdata\e-track-5.xml copy .\src\drivers\tita\tracksdata\e-track-5.xml .\runtimed\drivers\tita\tracksdata\e-track-5.xml
if exist .\src\drivers\tita\tracksdata\e-track-6.xml copy .\src\drivers\tita\tracksdata\e-track-6.xml .\runtimed\drivers\tita\tracksdata\e-track-6.xml
if exist .\src\drivers\tita\tracksdata\g-track-1.xml copy .\src\drivers\tita\tracksdata\g-track-1.xml .\runtimed\drivers\tita\tracksdata\g-track-1.xml
if exist .\src\drivers\tita\tracksdata\g-track-3.xml copy .\src\drivers\tita\tracksdata\g-track-3.xml .\runtimed\drivers\tita\tracksdata\g-track-3.xml
if exist .\src\drivers\tita\tracksdata\michigan.xml copy .\src\drivers\tita\tracksdata\michigan.xml .\runtimed\drivers\tita\tracksdata\michigan.xml
if exist .\src\drivers\tita\tracksdata\s2.xml copy .\src\drivers\tita\tracksdata\s2.xml .\runtimed\drivers\tita\tracksdata\s2.xml
if exist .\src\drivers\tita\tracksdata\wheel-1.xml copy .\src\drivers\tita\tracksdata\wheel-1.xml .\runtimed\drivers\tita\tracksdata\wheel-1.xml

if exist .\src\drivers\tita\*.* call .\create_dir .\runtimed
if exist .\src\drivers\tita\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\tita\*.* call .\create_dir .\runtimed\drivers\tita
if exist .\src\drivers\tita\tita.xml copy .\src\drivers\tita\tita.xml .\runtimed\drivers\tita\tita.xml
if exist .\src\drivers\tita\car.xml copy .\src\drivers\tita\car.xml .\runtimed\drivers\tita\car.xml
if exist .\src\drivers\tita\logo.rgb copy .\src\drivers\tita\logo.rgb .\runtimed\drivers\tita\logo.rgb
if exist .\src\drivers\tita\lotus-gt1.rgb copy .\src\drivers\tita\lotus-gt1.rgb .\runtimed\drivers\tita\lotus-gt1.rgb



if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\0
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\0\practice
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\0\race
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\0\qualifying

if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\1
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\1\practice
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\1\race
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\1\qualifying

if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\2
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\2\practice
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\2\race
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\2\qualifying

if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\3
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\3\practice
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\3\race
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\3\qualifying

if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\4
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\4\practice
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\4\race
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\4\qualifying

if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\5
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\5\practice
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\5\race
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\5\qualifying

if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\6
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\6\practice
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\6\race
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\6\qualifying

if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\7
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\7\practice
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\7\race
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\7\qualifying

if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\8
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\8\practice
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\8\race
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\8\qualifying

if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\9
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\9\practice
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\9\race
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtimed\drivers\olethros\9\qualifying

if exist .\src\drivers\olethros\0\default.xml copy .\src\drivers\olethros\0\default.xml .\runtimed\drivers\olethros\0\default.xml
if exist .\src\drivers\olethros\0\practice\aalborg.xml copy .\src\drivers\olethros\0\practice\aalborg.xml .\runtimed\drivers\olethros\0\practice\aalborg.xml
if exist .\src\drivers\olethros\0\practice\alpine-1.xml copy .\src\drivers\olethros\0\practice\alpine-1.xml .\runtimed\drivers\olethros\0\practice\alpine-1.xml
if exist .\src\drivers\olethros\0\practice\dirt-2.xml copy .\src\drivers\olethros\0\practice\dirt-2.xml .\runtimed\drivers\olethros\0\practice\dirt-2.xml
if exist .\src\drivers\olethros\0\practice\dirt-3.xml copy .\src\drivers\olethros\0\practice\dirt-3.xml .\runtimed\drivers\olethros\0\practice\dirt-3.xml
if exist .\src\drivers\olethros\0\practice\e-track-2.xml copy .\src\drivers\olethros\0\practice\e-track-2.xml .\runtimed\drivers\olethros\0\practice\e-track-2.xml
if exist .\src\drivers\olethros\0\practice\g-track-3.xml copy .\src\drivers\olethros\0\practice\g-track-3.xml .\runtimed\drivers\olethros\0\practice\g-track-3.xml
if exist .\src\drivers\olethros\0\practice\michigan.xml copy .\src\drivers\olethros\0\practice\michigan.xml .\runtimed\drivers\olethros\0\practice\michigan.xml
if exist .\src\drivers\olethros\0\practice\mixed-1.xml copy .\src\drivers\olethros\0\practice\mixed-1.xml .\runtimed\drivers\olethros\0\practice\mixed-1.xml
if exist .\src\drivers\olethros\0\practice\mixed-2.xml copy .\src\drivers\olethros\0\practice\mixed-2.xml .\runtimed\drivers\olethros\0\practice\mixed-2.xml
if exist .\src\drivers\olethros\0\practice\wheel-1.xml copy .\src\drivers\olethros\0\practice\wheel-1.xml .\runtimed\drivers\olethros\0\practice\wheel-1.xml
if exist .\src\drivers\olethros\0\qualifying\aalborg.xml copy .\src\drivers\olethros\0\qualifying\aalborg.xml .\runtimed\drivers\olethros\0\qualifying\aalborg.xml
if exist .\src\drivers\olethros\0\qualifying\alpine-1.xml copy .\src\drivers\olethros\0\qualifying\alpine-1.xml .\runtimed\drivers\olethros\0\qualifying\alpine-1.xml
if exist .\src\drivers\olethros\0\qualifying\dirt-2.xml copy .\src\drivers\olethros\0\qualifying\dirt-2.xml .\runtimed\drivers\olethros\0\qualifying\dirt-2.xml
if exist .\src\drivers\olethros\0\qualifying\dirt-3.xml copy .\src\drivers\olethros\0\qualifying\dirt-3.xml .\runtimed\drivers\olethros\0\qualifying\dirt-3.xml
if exist .\src\drivers\olethros\0\qualifying\e-track-2.xml copy .\src\drivers\olethros\0\qualifying\e-track-2.xml .\runtimed\drivers\olethros\0\qualifying\e-track-2.xml
if exist .\src\drivers\olethros\0\qualifying\g-track-3.xml copy .\src\drivers\olethros\0\qualifying\g-track-3.xml .\runtimed\drivers\olethros\0\qualifying\g-track-3.xml
if exist .\src\drivers\olethros\0\qualifying\mixed-1.xml copy .\src\drivers\olethros\0\qualifying\mixed-1.xml .\runtimed\drivers\olethros\0\qualifying\mixed-1.xml
if exist .\src\drivers\olethros\0\qualifying\mixed-2.xml copy .\src\drivers\olethros\0\qualifying\mixed-2.xml .\runtimed\drivers\olethros\0\qualifying\mixed-2.xml
if exist .\src\drivers\olethros\0\race\aalborg.xml copy .\src\drivers\olethros\0\race\aalborg.xml .\runtimed\drivers\olethros\0\race\aalborg.xml
if exist .\src\drivers\olethros\0\race\alpine-1.xml copy .\src\drivers\olethros\0\race\alpine-1.xml .\runtimed\drivers\olethros\0\race\alpine-1.xml
if exist .\src\drivers\olethros\0\race\dirt-2.xml copy .\src\drivers\olethros\0\race\dirt-2.xml .\runtimed\drivers\olethros\0\race\dirt-2.xml
if exist .\src\drivers\olethros\0\race\dirt-3.xml copy .\src\drivers\olethros\0\race\dirt-3.xml .\runtimed\drivers\olethros\0\race\dirt-3.xml
if exist .\src\drivers\olethros\0\race\e-track-2.xml copy .\src\drivers\olethros\0\race\e-track-2.xml .\runtimed\drivers\olethros\0\race\e-track-2.xml
if exist .\src\drivers\olethros\0\race\g-track-3.xml copy .\src\drivers\olethros\0\race\g-track-3.xml .\runtimed\drivers\olethros\0\race\g-track-3.xml
if exist .\src\drivers\olethros\0\race\mixed-1.xml copy .\src\drivers\olethros\0\race\mixed-1.xml .\runtimed\drivers\olethros\0\race\mixed-1.xml
if exist .\src\drivers\olethros\0\race\mixed-2.xml copy .\src\drivers\olethros\0\race\mixed-2.xml .\runtimed\drivers\olethros\0\race\mixed-2.xml
if exist .\src\drivers\olethros\0\race\wheel-1.xml copy .\src\drivers\olethros\0\race\wheel-1.xml .\runtimed\drivers\olethros\0\race\wheel-1.xml
if exist .\src\drivers\olethros\1\cg-nascar-rwd.rgb copy .\src\drivers\olethros\1\cg-nascar-rwd.rgb .\runtimed\drivers\olethros\1\cg-nascar-rwd.rgb
if exist .\src\drivers\olethros\1\default.xml copy .\src\drivers\olethros\1\default.xml .\runtimed\drivers\olethros\1\default.xml
if exist .\src\drivers\olethros\1\practice\g-track-3.xml copy .\src\drivers\olethros\1\practice\g-track-3.xml .\runtimed\drivers\olethros\1\practice\g-track-3.xml
if exist .\src\drivers\olethros\1\practice\michigan.xml copy .\src\drivers\olethros\1\practice\michigan.xml .\runtimed\drivers\olethros\1\practice\michigan.xml
if exist .\src\drivers\olethros\1\practice\wheel-1.xml copy .\src\drivers\olethros\1\practice\wheel-1.xml .\runtimed\drivers\olethros\1\practice\wheel-1.xml
if exist .\src\drivers\olethros\1\qualifying\g-track-3.xml copy .\src\drivers\olethros\1\qualifying\g-track-3.xml .\runtimed\drivers\olethros\1\qualifying\g-track-3.xml
if exist .\src\drivers\olethros\1\qualifying\wheel-1.xml copy .\src\drivers\olethros\1\qualifying\wheel-1.xml .\runtimed\drivers\olethros\1\qualifying\wheel-1.xml
if exist .\src\drivers\olethros\1\race\g-track-3.xml copy .\src\drivers\olethros\1\race\g-track-3.xml .\runtimed\drivers\olethros\1\race\g-track-3.xml
if exist .\src\drivers\olethros\1\race\wheel-1.xml copy .\src\drivers\olethros\1\race\wheel-1.xml .\runtimed\drivers\olethros\1\race\wheel-1.xml
if exist .\src\drivers\olethros\2\default.xml copy .\src\drivers\olethros\2\default.xml .\runtimed\drivers\olethros\2\default.xml
if exist .\src\drivers\olethros\2\porsche-gt1.rgb copy .\src\drivers\olethros\2\porsche-gt1.rgb .\runtimed\drivers\olethros\2\porsche-gt1.rgb
if exist .\src\drivers\olethros\2\practice\e-track-3.xml copy .\src\drivers\olethros\2\practice\e-track-3.xml .\runtimed\drivers\olethros\2\practice\e-track-3.xml
if exist .\src\drivers\olethros\2\practice\e-track-4.xml copy .\src\drivers\olethros\2\practice\e-track-4.xml .\runtimed\drivers\olethros\2\practice\e-track-4.xml
if exist .\src\drivers\olethros\2\qualifying\e-track-3.xml copy .\src\drivers\olethros\2\qualifying\e-track-3.xml .\runtimed\drivers\olethros\2\qualifying\e-track-3.xml
if exist .\src\drivers\olethros\2\qualifying\e-track-4.xml copy .\src\drivers\olethros\2\qualifying\e-track-4.xml .\runtimed\drivers\olethros\2\qualifying\e-track-4.xml
if exist .\src\drivers\olethros\2\race\e-track-3.xml copy .\src\drivers\olethros\2\race\e-track-3.xml .\runtimed\drivers\olethros\2\race\e-track-3.xml
if exist .\src\drivers\olethros\2\race\e-track-4.xml copy .\src\drivers\olethros\2\race\e-track-4.xml .\runtimed\drivers\olethros\2\race\e-track-4.xml
if exist .\src\drivers\olethros\3\155-DTM.rgb copy .\src\drivers\olethros\3\155-DTM.rgb .\runtimed\drivers\olethros\3\155-DTM.rgb
if exist .\src\drivers\olethros\3\default.xml copy .\src\drivers\olethros\3\default.xml .\runtimed\drivers\olethros\3\default.xml
if exist .\src\drivers\olethros\4\default.xml copy .\src\drivers\olethros\4\default.xml .\runtimed\drivers\olethros\4\default.xml
if exist .\src\drivers\olethros\4\mclaren-f1.rgb copy .\src\drivers\olethros\4\mclaren-f1.rgb .\runtimed\drivers\olethros\4\mclaren-f1.rgb
if exist .\src\drivers\olethros\4\practice\e-track-3.xml copy .\src\drivers\olethros\4\practice\e-track-3.xml .\runtimed\drivers\olethros\4\practice\e-track-3.xml
if exist .\src\drivers\olethros\4\practice\e-track-4.xml copy .\src\drivers\olethros\4\practice\e-track-4.xml .\runtimed\drivers\olethros\4\practice\e-track-4.xml
if exist .\src\drivers\olethros\4\qualifying\e-track-3.xml copy .\src\drivers\olethros\4\qualifying\e-track-3.xml .\runtimed\drivers\olethros\4\qualifying\e-track-3.xml
if exist .\src\drivers\olethros\4\qualifying\e-track-4.xml copy .\src\drivers\olethros\4\qualifying\e-track-4.xml .\runtimed\drivers\olethros\4\qualifying\e-track-4.xml
if exist .\src\drivers\olethros\4\race\e-track-3.xml copy .\src\drivers\olethros\4\race\e-track-3.xml .\runtimed\drivers\olethros\4\race\e-track-3.xml
if exist .\src\drivers\olethros\4\race\e-track-4.xml copy .\src\drivers\olethros\4\race\e-track-4.xml .\runtimed\drivers\olethros\4\race\e-track-4.xml
if exist .\src\drivers\olethros\5\default.xml copy .\src\drivers\olethros\5\default.xml .\runtimed\drivers\olethros\5\default.xml
if exist .\src\drivers\olethros\5\porsche-gt3rs.rgb copy .\src\drivers\olethros\5\porsche-gt3rs.rgb .\runtimed\drivers\olethros\5\porsche-gt3rs.rgb
if exist .\src\drivers\olethros\6\clkdtm.rgb copy .\src\drivers\olethros\6\clkdtm.rgb .\runtimed\drivers\olethros\6\clkdtm.rgb
if exist .\src\drivers\olethros\6\default.xml copy .\src\drivers\olethros\6\default.xml .\runtimed\drivers\olethros\6\default.xml
if exist .\src\drivers\olethros\7\360-modena.rgb copy .\src\drivers\olethros\7\360-modena.rgb .\runtimed\drivers\olethros\7\360-modena.rgb
if exist .\src\drivers\olethros\7\default.xml copy .\src\drivers\olethros\7\default.xml .\runtimed\drivers\olethros\7\default.xml
if exist .\src\drivers\olethros\7\practice\b-speedway.xml copy .\src\drivers\olethros\7\practice\b-speedway.xml .\runtimed\drivers\olethros\7\practice\b-speedway.xml
if exist .\src\drivers\olethros\7\practice\e-track-1.xml copy .\src\drivers\olethros\7\practice\e-track-1.xml .\runtimed\drivers\olethros\7\practice\e-track-1.xml
if exist .\src\drivers\olethros\7\practice\e-track-3.xml copy .\src\drivers\olethros\7\practice\e-track-3.xml .\runtimed\drivers\olethros\7\practice\e-track-3.xml
if exist .\src\drivers\olethros\7\practice\eroad.xml copy .\src\drivers\olethros\7\practice\eroad.xml .\runtimed\drivers\olethros\7\practice\eroad.xml
if exist .\src\drivers\olethros\7\practice\g-track-2.xml copy .\src\drivers\olethros\7\practice\g-track-2.xml .\runtimed\drivers\olethros\7\practice\g-track-2.xml
if exist .\src\drivers\olethros\7\practice\michigan.xml copy .\src\drivers\olethros\7\practice\michigan.xml .\runtimed\drivers\olethros\7\practice\michigan.xml
if exist .\src\drivers\olethros\7\qualifying\b-speedway.xml copy .\src\drivers\olethros\7\qualifying\b-speedway.xml .\runtimed\drivers\olethros\7\qualifying\b-speedway.xml
if exist .\src\drivers\olethros\7\qualifying\e-track-1.xml copy .\src\drivers\olethros\7\qualifying\e-track-1.xml .\runtimed\drivers\olethros\7\qualifying\e-track-1.xml
if exist .\src\drivers\olethros\7\qualifying\e-track-3.xml copy .\src\drivers\olethros\7\qualifying\e-track-3.xml .\runtimed\drivers\olethros\7\qualifying\e-track-3.xml
if exist .\src\drivers\olethros\7\qualifying\eroad.xml copy .\src\drivers\olethros\7\qualifying\eroad.xml .\runtimed\drivers\olethros\7\qualifying\eroad.xml
if exist .\src\drivers\olethros\7\qualifying\g-track-2.xml copy .\src\drivers\olethros\7\qualifying\g-track-2.xml .\runtimed\drivers\olethros\7\qualifying\g-track-2.xml
if exist .\src\drivers\olethros\7\qualifying\michigan.xml copy .\src\drivers\olethros\7\qualifying\michigan.xml .\runtimed\drivers\olethros\7\qualifying\michigan.xml
if exist .\src\drivers\olethros\7\race\b-speedway.xml copy .\src\drivers\olethros\7\race\b-speedway.xml .\runtimed\drivers\olethros\7\race\b-speedway.xml
if exist .\src\drivers\olethros\7\race\e-track-1.xml copy .\src\drivers\olethros\7\race\e-track-1.xml .\runtimed\drivers\olethros\7\race\e-track-1.xml
if exist .\src\drivers\olethros\7\race\e-track-3.xml copy .\src\drivers\olethros\7\race\e-track-3.xml .\runtimed\drivers\olethros\7\race\e-track-3.xml
if exist .\src\drivers\olethros\7\race\eroad.xml copy .\src\drivers\olethros\7\race\eroad.xml .\runtimed\drivers\olethros\7\race\eroad.xml
if exist .\src\drivers\olethros\7\race\g-track-2.xml copy .\src\drivers\olethros\7\race\g-track-2.xml .\runtimed\drivers\olethros\7\race\g-track-2.xml
if exist .\src\drivers\olethros\7\race\michigan.xml copy .\src\drivers\olethros\7\race\michigan.xml .\runtimed\drivers\olethros\7\race\michigan.xml
if exist .\src\drivers\olethros\8\default.xml copy .\src\drivers\olethros\8\default.xml .\runtimed\drivers\olethros\8\default.xml
if exist .\src\drivers\olethros\8\xj-220.rgb copy .\src\drivers\olethros\8\xj-220.rgb .\runtimed\drivers\olethros\8\xj-220.rgb
if exist .\src\drivers\olethros\9\default.xml copy .\src\drivers\olethros\9\default.xml .\runtimed\drivers\olethros\9\default.xml
if exist .\src\drivers\olethros\9\practice\michigan.xml copy .\src\drivers\olethros\9\practice\michigan.xml .\runtimed\drivers\olethros\9\practice\michigan.xml
if exist .\src\drivers\olethros\9\qualifying\michigan.xml copy .\src\drivers\olethros\9\qualifying\michigan.xml .\runtimed\drivers\olethros\9\qualifying\michigan.xml
if exist .\src\drivers\olethros\9\race\michigan.xml copy .\src\drivers\olethros\9\race\michigan.xml .\runtimed\drivers\olethros\9\race\michigan.xml
if exist .\src\drivers\olethros\logo.rgb copy .\src\drivers\olethros\logo.rgb .\runtimed\drivers\olethros\logo.rgb
if exist .\src\drivers\olethros\olethros.xml copy .\src\drivers\olethros\olethros.xml .\runtimed\drivers\olethros\olethros.xml



if exist .\src\libs\raceengineclient\*.* call .\create_dir .\runtimed
if exist .\src\libs\raceengineclient\*.* call .\create_dir .\runtimed\config
if exist .\src\libs\raceengineclient\raceengine.xml copy .\src\libs\raceengineclient\raceengine.xml .\runtimed\config\raceengine.xml
if exist .\src\libs\raceengineclient\style.xsl copy .\src\libs\raceengineclient\style.xsl .\runtimed\config\style.xsl

if exist .\src\libs\tgf\*.* call .\create_dir .\runtimed
if exist .\src\libs\tgf\*.* call .\create_dir .\runtimed\config
if exist .\src\libs\tgf\params.dtd copy .\src\libs\tgf\params.dtd .\runtimed\config\params.dtd

if exist .\src\libs\tgfclient\*.* call .\create_dir .\runtimed
if exist .\src\libs\tgfclient\*.* call .\create_dir .\runtimed\config
if exist .\src\libs\tgfclient\screen.xml copy .\src\libs\tgfclient\screen.xml .\runtimed\config\screen.xml

if exist .\src\modules\graphic\ssggraph\*.* call .\create_dir .\runtimed
if exist .\src\modules\graphic\ssggraph\*.* call .\create_dir .\runtimed\config
if exist .\src\modules\graphic\ssggraph\graph.xml copy .\src\modules\graphic\ssggraph\graph.xml .\runtimed\config\graph.xml
if exist .\src\modules\graphic\ssggraph\sound.xml copy .\src\modules\graphic\ssggraph\sound.xml .\runtimed\config\sound.xml

if exist .\src\modules\telemetry\*.* call .\create_dir .\runtimed
if exist .\src\modules\telemetry\*.* call .\create_dir .\runtimed\telemetry
if exist .\src\modules\telemetry\telemetry.sh copy .\src\modules\telemetry\telemetry.sh .\runtimed\telemetry\telemetry.sh

if exist .\src\raceman\*.* call .\create_dir .\runtimed
if exist .\src\raceman\*.* call .\create_dir .\runtimed\config
if exist .\src\raceman\*.* call .\create_dir .\runtimed\config\raceman
if exist .\src\raceman\champ.xml copy .\src\raceman\champ.xml .\runtimed\config\raceman\champ.xml
if exist .\src\raceman\dtmrace.xml copy .\src\raceman\dtmrace.xml .\runtimed\config\raceman\dtmrace.xml
if exist .\src\raceman\endrace.xml copy .\src\raceman\endrace.xml .\runtimed\config\raceman\endrace.xml
if exist .\src\raceman\ncrace.xml copy .\src\raceman\ncrace.xml .\runtimed\config\raceman\ncrace.xml
if exist .\src\raceman\practice.xml copy .\src\raceman\practice.xml .\runtimed\config\raceman\practice.xml
if exist .\src\raceman\quickrace.xml copy .\src\raceman\quickrace.xml .\runtimed\config\raceman\quickrace.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\results
call .\create_dir .\runtimed\results\champ

call .\create_dir .\runtimed
call .\create_dir .\runtimed\results
call .\create_dir .\runtimed\results\dtmrace

call .\create_dir .\runtimed
call .\create_dir .\runtimed\results
call .\create_dir .\runtimed\results\endrace

call .\create_dir .\runtimed
call .\create_dir .\runtimed\results
call .\create_dir .\runtimed\results\ncrace

call .\create_dir .\runtimed
call .\create_dir .\runtimed\results
call .\create_dir .\runtimed\results\practice

call .\create_dir .\runtimed
call .\create_dir .\runtimed\results
call .\create_dir .\runtimed\results\quickrace

if exist .\*.* call .\create_dir .\runtimed
if exist .\*.* call .\create_dir .\runtimed\.
if exist .\setup_linux.sh copy .\setup_linux.sh .\runtimed\.\setup_linux.sh

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw3

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\billy

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\bt

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\cylos1

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\cylos2

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno2

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\K1999

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\lliaw

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\sparkle

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tanhoj

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tita

call .\create_dir .\runtimed
call .\create_dir .\runtimed\.

call .\create_dir .\runtimed
call .\create_dir .\runtimed\.

call .\create_dir .\runtimed
call .\create_dir .\runtimed\.

call .\create_dir .\runtimed
call .\create_dir .\runtimed\.

call .\create_dir .\runtimed
call .\create_dir .\runtimed\.

call .\create_dir .\runtimed
call .\create_dir .\runtimed\.

call .\create_dir .\runtimed
call .\create_dir .\runtimed\.

call .\create_dir .\runtimed
call .\create_dir .\runtimed\.

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\graphic

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\simu

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\simu

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\telemetry

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\track
