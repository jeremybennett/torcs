@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

if not exist .\src\interfaces goto src_interfaces
call .\create_dir .\export
call .\create_dir .\export\include
if exist .\src\interfaces\graphic.h copy .\src\interfaces\graphic.h .\export\include\graphic.h
if exist .\src\interfaces\raceman.h copy .\src\interfaces\raceman.h .\export\include\raceman.h
if exist .\src\interfaces\robot.h copy .\src\interfaces\robot.h .\export\include\robot.h
if exist .\src\interfaces\simu.h copy .\src\interfaces\simu.h .\export\include\simu.h
if exist .\src\interfaces\track.h copy .\src\interfaces\track.h .\export\include\track.h
if exist .\src\interfaces\car.h copy .\src\interfaces\car.h .\export\include\car.h
if exist .\src\interfaces\ttypes.h copy .\src\interfaces\ttypes.h .\export\include\ttypes.h
if exist .\src\interfaces\telemetry.h copy .\src\interfaces\telemetry.h .\export\include\telemetry.h
if exist .\src\interfaces\practicectrl.h copy .\src\interfaces\practicectrl.h .\export\include\practicectrl.h
if exist .\src\interfaces\playerpref.h copy .\src\interfaces\playerpref.h .\export\include\playerpref.h
if exist .\src\interfaces\js.h copy .\src\interfaces\js.h .\export\include\js.h
:src_interfaces

if not exist .\src\libs\txml goto src_libs_txml
call .\create_dir .\export
call .\create_dir .\export\include
if exist .\src\libs\txml\xml.h copy .\src\libs\txml\xml.h .\export\include\xml.h
if exist .\src\libs\txml\xmlparse.h copy .\src\libs\txml\xmlparse.h .\export\include\xmlparse.h
:src_libs_txml

if not exist .\src\libs\tgf goto src_libs_tgf
call .\create_dir .\export
call .\create_dir .\export\include
if exist .\src\libs\tgf\tgf.h copy .\src\libs\tgf\tgf.h .\export\include\tgf.h
if exist .\src\libs\tgf\os.h copy .\src\libs\tgf\os.h .\export\include\os.h
if exist .\src\libs\tgf\queue.h copy .\src\libs\tgf\queue.h .\export\include\queue.h
:src_libs_tgf

if not exist .\src\libs\torcs goto src_libs_torcs
call .\create_dir .\export
call .\create_dir .\export\include
if exist .\src\libs\torcs\torcs.h copy .\src\libs\torcs\torcs.h .\export\include\torcs.h
:src_libs_torcs

if not exist .\src\libs\racemantools goto src_libs_racemantools
call .\create_dir .\export
call .\create_dir .\export\include
if exist .\src\libs\racemantools\racemantools.h copy .\src\libs\racemantools\racemantools.h .\export\include\racemantools.h
:src_libs_racemantools

if not exist .\src\libs\robottools goto src_libs_robottools
call .\create_dir .\export
call .\create_dir .\export\include
if exist .\src\libs\robottools\robottools.h copy .\src\libs\robottools\robottools.h .\export\include\robottools.h
:src_libs_robottools

if not exist .\src\libs\raceengine goto src_libs_raceengine
call .\create_dir .\export
call .\create_dir .\export\include
if exist .\src\libs\raceengine\singleplayer.h copy .\src\libs\raceengine\singleplayer.h .\export\include\singleplayer.h
:src_libs_raceengine

if not exist .\src\linux goto src_linux
call .\create_dir .\export
call .\create_dir .\export\include
if exist .\src\windows\osspec.h copy .\src\windows\osspec.h .\export\include\osspec.h
:src_linux

if not exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D goto src_modules_simu_simuv2_SOLID_2.0_include_3D
call .\create_dir .\export
call .\create_dir .\export\include
call .\create_dir .\export\include\3D
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Basic.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Basic.h .\export\include\3D\Basic.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Matrix.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Matrix.h .\export\include\3D\Matrix.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Point.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Point.h .\export\include\3D\Point.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Quaternion.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Quaternion.h .\export\include\3D\Quaternion.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Tuple3.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Tuple3.h .\export\include\3D\Tuple3.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Tuple4.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Tuple4.h .\export\include\3D\Tuple4.h
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Vector.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Vector.h .\export\include\3D\Vector.h
:src_modules_simu_simuv2_SOLID_2.0_include_3D

if not exist .\src\modules\simu\simuv2\SOLID-2.0\include\SOLID goto src_modules_simu_simuv2_SOLID_2.0_include_SOLID
call .\create_dir .\export
call .\create_dir .\export\include
call .\create_dir .\export\include\SOLID
if exist .\src\modules\simu\simuv2\SOLID-2.0\include\SOLID\solid.h copy .\src\modules\simu\simuv2\SOLID-2.0\include\SOLID\solid.h .\export\include\SOLID\solid.h
:src_modules_simu_simuv2_SOLID_2.0_include_SOLID

if not exist .\src\drivers\berniw\1 goto src_drivers_berniw_1
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\1
if exist .\src\drivers\berniw\1\cg-nascar-rwd.rgb copy .\src\drivers\berniw\1\cg-nascar-rwd.rgb .\runtimed\drivers\berniw\1\cg-nascar-rwd.rgb
if exist .\src\drivers\berniw\1\aalborg.xml copy .\src\drivers\berniw\1\aalborg.xml .\runtimed\drivers\berniw\1\aalborg.xml
if exist .\src\drivers\berniw\1\alpine-1.xml copy .\src\drivers\berniw\1\alpine-1.xml .\runtimed\drivers\berniw\1\alpine-1.xml
if exist .\src\drivers\berniw\1\a-speedway.xml copy .\src\drivers\berniw\1\a-speedway.xml .\runtimed\drivers\berniw\1\a-speedway.xml
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
if exist .\src\drivers\berniw\1\michigan.xml copy .\src\drivers\berniw\1\michigan.xml .\runtimed\drivers\berniw\1\michigan.xml
if exist .\src\drivers\berniw\1\mixed-1.xml copy .\src\drivers\berniw\1\mixed-1.xml .\runtimed\drivers\berniw\1\mixed-1.xml
if exist .\src\drivers\berniw\1\mixed-2.xml copy .\src\drivers\berniw\1\mixed-2.xml .\runtimed\drivers\berniw\1\mixed-2.xml
if exist .\src\drivers\berniw\1\wheel-1.xml copy .\src\drivers\berniw\1\wheel-1.xml .\runtimed\drivers\berniw\1\wheel-1.xml
:src_drivers_berniw_1

if not exist .\src\drivers\berniw\10 goto src_drivers_berniw_10
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\10
if exist .\src\drivers\berniw\10\buggy.rgb copy .\src\drivers\berniw\10\buggy.rgb .\runtimed\drivers\berniw\10\buggy.rgb
if exist .\src\drivers\berniw\10\aalborg.xml copy .\src\drivers\berniw\10\aalborg.xml .\runtimed\drivers\berniw\10\aalborg.xml
if exist .\src\drivers\berniw\10\alpine-1.xml copy .\src\drivers\berniw\10\alpine-1.xml .\runtimed\drivers\berniw\10\alpine-1.xml
if exist .\src\drivers\berniw\10\a-speedway.xml copy .\src\drivers\berniw\10\a-speedway.xml .\runtimed\drivers\berniw\10\a-speedway.xml
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
if exist .\src\drivers\berniw\10\michigan.xml copy .\src\drivers\berniw\10\michigan.xml .\runtimed\drivers\berniw\10\michigan.xml
if exist .\src\drivers\berniw\10\mixed-1.xml copy .\src\drivers\berniw\10\mixed-1.xml .\runtimed\drivers\berniw\10\mixed-1.xml
if exist .\src\drivers\berniw\10\mixed-2.xml copy .\src\drivers\berniw\10\mixed-2.xml .\runtimed\drivers\berniw\10\mixed-2.xml
if exist .\src\drivers\berniw\10\wheel-1.xml copy .\src\drivers\berniw\10\wheel-1.xml .\runtimed\drivers\berniw\10\wheel-1.xml
:src_drivers_berniw_10

if not exist .\src\drivers\berniw\2 goto src_drivers_berniw_2
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\2
if exist .\src\drivers\berniw\2\cg-nascar-rwd.rgb copy .\src\drivers\berniw\2\cg-nascar-rwd.rgb .\runtimed\drivers\berniw\2\cg-nascar-rwd.rgb
if exist .\src\drivers\berniw\2\aalborg.xml copy .\src\drivers\berniw\2\aalborg.xml .\runtimed\drivers\berniw\2\aalborg.xml
if exist .\src\drivers\berniw\2\alpine-1.xml copy .\src\drivers\berniw\2\alpine-1.xml .\runtimed\drivers\berniw\2\alpine-1.xml
if exist .\src\drivers\berniw\2\a-speedway.xml copy .\src\drivers\berniw\2\a-speedway.xml .\runtimed\drivers\berniw\2\a-speedway.xml
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
if exist .\src\drivers\berniw\2\michigan.xml copy .\src\drivers\berniw\2\michigan.xml .\runtimed\drivers\berniw\2\michigan.xml
if exist .\src\drivers\berniw\2\mixed-1.xml copy .\src\drivers\berniw\2\mixed-1.xml .\runtimed\drivers\berniw\2\mixed-1.xml
if exist .\src\drivers\berniw\2\mixed-2.xml copy .\src\drivers\berniw\2\mixed-2.xml .\runtimed\drivers\berniw\2\mixed-2.xml
if exist .\src\drivers\berniw\2\wheel-1.xml copy .\src\drivers\berniw\2\wheel-1.xml .\runtimed\drivers\berniw\2\wheel-1.xml
:src_drivers_berniw_2

if not exist .\src\drivers\berniw\3 goto src_drivers_berniw_3
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\3
if exist .\src\drivers\berniw\3\porsche-gt1.rgb copy .\src\drivers\berniw\3\porsche-gt1.rgb .\runtimed\drivers\berniw\3\porsche-gt1.rgb
if exist .\src\drivers\berniw\3\aalborg.xml copy .\src\drivers\berniw\3\aalborg.xml .\runtimed\drivers\berniw\3\aalborg.xml
if exist .\src\drivers\berniw\3\alpine-1.xml copy .\src\drivers\berniw\3\alpine-1.xml .\runtimed\drivers\berniw\3\alpine-1.xml
if exist .\src\drivers\berniw\3\a-speedway.xml copy .\src\drivers\berniw\3\a-speedway.xml .\runtimed\drivers\berniw\3\a-speedway.xml
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
if exist .\src\drivers\berniw\3\michigan.xml copy .\src\drivers\berniw\3\michigan.xml .\runtimed\drivers\berniw\3\michigan.xml
if exist .\src\drivers\berniw\3\mixed-1.xml copy .\src\drivers\berniw\3\mixed-1.xml .\runtimed\drivers\berniw\3\mixed-1.xml
if exist .\src\drivers\berniw\3\mixed-2.xml copy .\src\drivers\berniw\3\mixed-2.xml .\runtimed\drivers\berniw\3\mixed-2.xml
if exist .\src\drivers\berniw\3\wheel-1.xml copy .\src\drivers\berniw\3\wheel-1.xml .\runtimed\drivers\berniw\3\wheel-1.xml
:src_drivers_berniw_3

if not exist .\src\drivers\berniw\4 goto src_drivers_berniw_4
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\4
if exist .\src\drivers\berniw\4\viper-gts-r.rgb copy .\src\drivers\berniw\4\viper-gts-r.rgb .\runtimed\drivers\berniw\4\viper-gts-r.rgb
if exist .\src\drivers\berniw\4\aalborg.xml copy .\src\drivers\berniw\4\aalborg.xml .\runtimed\drivers\berniw\4\aalborg.xml
if exist .\src\drivers\berniw\4\alpine-1.xml copy .\src\drivers\berniw\4\alpine-1.xml .\runtimed\drivers\berniw\4\alpine-1.xml
if exist .\src\drivers\berniw\4\a-speedway.xml copy .\src\drivers\berniw\4\a-speedway.xml .\runtimed\drivers\berniw\4\a-speedway.xml
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
if exist .\src\drivers\berniw\4\michigan.xml copy .\src\drivers\berniw\4\michigan.xml .\runtimed\drivers\berniw\4\michigan.xml
if exist .\src\drivers\berniw\4\mixed-1.xml copy .\src\drivers\berniw\4\mixed-1.xml .\runtimed\drivers\berniw\4\mixed-1.xml
if exist .\src\drivers\berniw\4\mixed-2.xml copy .\src\drivers\berniw\4\mixed-2.xml .\runtimed\drivers\berniw\4\mixed-2.xml
if exist .\src\drivers\berniw\4\wheel-1.xml copy .\src\drivers\berniw\4\wheel-1.xml .\runtimed\drivers\berniw\4\wheel-1.xml
:src_drivers_berniw_4

if not exist .\src\drivers\berniw\5 goto src_drivers_berniw_5
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\5
if exist .\src\drivers\berniw\5\gt40.rgb copy .\src\drivers\berniw\5\gt40.rgb .\runtimed\drivers\berniw\5\gt40.rgb
if exist .\src\drivers\berniw\5\aalborg.xml copy .\src\drivers\berniw\5\aalborg.xml .\runtimed\drivers\berniw\5\aalborg.xml
if exist .\src\drivers\berniw\5\alpine-1.xml copy .\src\drivers\berniw\5\alpine-1.xml .\runtimed\drivers\berniw\5\alpine-1.xml
if exist .\src\drivers\berniw\5\a-speedway.xml copy .\src\drivers\berniw\5\a-speedway.xml .\runtimed\drivers\berniw\5\a-speedway.xml
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
if exist .\src\drivers\berniw\5\michigan.xml copy .\src\drivers\berniw\5\michigan.xml .\runtimed\drivers\berniw\5\michigan.xml
if exist .\src\drivers\berniw\5\mixed-1.xml copy .\src\drivers\berniw\5\mixed-1.xml .\runtimed\drivers\berniw\5\mixed-1.xml
if exist .\src\drivers\berniw\5\mixed-2.xml copy .\src\drivers\berniw\5\mixed-2.xml .\runtimed\drivers\berniw\5\mixed-2.xml
if exist .\src\drivers\berniw\5\wheel-1.xml copy .\src\drivers\berniw\5\wheel-1.xml .\runtimed\drivers\berniw\5\wheel-1.xml
:src_drivers_berniw_5

if not exist .\src\drivers\berniw\6 goto src_drivers_berniw_6
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\6
if exist .\src\drivers\berniw\6\155-DTM.rgb copy .\src\drivers\berniw\6\155-DTM.rgb .\runtimed\drivers\berniw\6\155-DTM.rgb
if exist .\src\drivers\berniw\6\aalborg.xml copy .\src\drivers\berniw\6\aalborg.xml .\runtimed\drivers\berniw\6\aalborg.xml
if exist .\src\drivers\berniw\6\alpine-1.xml copy .\src\drivers\berniw\6\alpine-1.xml .\runtimed\drivers\berniw\6\alpine-1.xml
if exist .\src\drivers\berniw\6\a-speedway.xml copy .\src\drivers\berniw\6\a-speedway.xml .\runtimed\drivers\berniw\6\a-speedway.xml
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
if exist .\src\drivers\berniw\6\michigan.xml copy .\src\drivers\berniw\6\michigan.xml .\runtimed\drivers\berniw\6\michigan.xml
if exist .\src\drivers\berniw\6\mixed-1.xml copy .\src\drivers\berniw\6\mixed-1.xml .\runtimed\drivers\berniw\6\mixed-1.xml
if exist .\src\drivers\berniw\6\mixed-2.xml copy .\src\drivers\berniw\6\mixed-2.xml .\runtimed\drivers\berniw\6\mixed-2.xml
if exist .\src\drivers\berniw\6\wheel-1.xml copy .\src\drivers\berniw\6\wheel-1.xml .\runtimed\drivers\berniw\6\wheel-1.xml
:src_drivers_berniw_6

if not exist .\src\drivers\berniw\7 goto src_drivers_berniw_7
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\7
if exist .\src\drivers\berniw\7\lotus-gt1.rgb copy .\src\drivers\berniw\7\lotus-gt1.rgb .\runtimed\drivers\berniw\7\lotus-gt1.rgb
if exist .\src\drivers\berniw\7\aalborg.xml copy .\src\drivers\berniw\7\aalborg.xml .\runtimed\drivers\berniw\7\aalborg.xml
if exist .\src\drivers\berniw\7\alpine-1.xml copy .\src\drivers\berniw\7\alpine-1.xml .\runtimed\drivers\berniw\7\alpine-1.xml
if exist .\src\drivers\berniw\7\a-speedway.xml copy .\src\drivers\berniw\7\a-speedway.xml .\runtimed\drivers\berniw\7\a-speedway.xml
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
if exist .\src\drivers\berniw\7\michigan.xml copy .\src\drivers\berniw\7\michigan.xml .\runtimed\drivers\berniw\7\michigan.xml
if exist .\src\drivers\berniw\7\mixed-1.xml copy .\src\drivers\berniw\7\mixed-1.xml .\runtimed\drivers\berniw\7\mixed-1.xml
if exist .\src\drivers\berniw\7\mixed-2.xml copy .\src\drivers\berniw\7\mixed-2.xml .\runtimed\drivers\berniw\7\mixed-2.xml
if exist .\src\drivers\berniw\7\wheel-1.xml copy .\src\drivers\berniw\7\wheel-1.xml .\runtimed\drivers\berniw\7\wheel-1.xml
:src_drivers_berniw_7

if not exist .\src\drivers\berniw\8 goto src_drivers_berniw_8
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\8
if exist .\src\drivers\berniw\8\baja-bug.rgb copy .\src\drivers\berniw\8\baja-bug.rgb .\runtimed\drivers\berniw\8\baja-bug.rgb
if exist .\src\drivers\berniw\8\aalborg.xml copy .\src\drivers\berniw\8\aalborg.xml .\runtimed\drivers\berniw\8\aalborg.xml
if exist .\src\drivers\berniw\8\alpine-1.xml copy .\src\drivers\berniw\8\alpine-1.xml .\runtimed\drivers\berniw\8\alpine-1.xml
if exist .\src\drivers\berniw\8\a-speedway.xml copy .\src\drivers\berniw\8\a-speedway.xml .\runtimed\drivers\berniw\8\a-speedway.xml
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
if exist .\src\drivers\berniw\8\michigan.xml copy .\src\drivers\berniw\8\michigan.xml .\runtimed\drivers\berniw\8\michigan.xml
if exist .\src\drivers\berniw\8\mixed-1.xml copy .\src\drivers\berniw\8\mixed-1.xml .\runtimed\drivers\berniw\8\mixed-1.xml
if exist .\src\drivers\berniw\8\mixed-2.xml copy .\src\drivers\berniw\8\mixed-2.xml .\runtimed\drivers\berniw\8\mixed-2.xml
if exist .\src\drivers\berniw\8\wheel-1.xml copy .\src\drivers\berniw\8\wheel-1.xml .\runtimed\drivers\berniw\8\wheel-1.xml
:src_drivers_berniw_8

if not exist .\src\drivers\berniw\9 goto src_drivers_berniw_9
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\9
if exist .\src\drivers\berniw\9\mclaren-f1.rgb copy .\src\drivers\berniw\9\mclaren-f1.rgb .\runtimed\drivers\berniw\9\mclaren-f1.rgb
if exist .\src\drivers\berniw\9\aalborg.xml copy .\src\drivers\berniw\9\aalborg.xml .\runtimed\drivers\berniw\9\aalborg.xml
if exist .\src\drivers\berniw\9\alpine-1.xml copy .\src\drivers\berniw\9\alpine-1.xml .\runtimed\drivers\berniw\9\alpine-1.xml
if exist .\src\drivers\berniw\9\a-speedway.xml copy .\src\drivers\berniw\9\a-speedway.xml .\runtimed\drivers\berniw\9\a-speedway.xml
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
if exist .\src\drivers\berniw\9\michigan.xml copy .\src\drivers\berniw\9\michigan.xml .\runtimed\drivers\berniw\9\michigan.xml
if exist .\src\drivers\berniw\9\mixed-1.xml copy .\src\drivers\berniw\9\mixed-1.xml .\runtimed\drivers\berniw\9\mixed-1.xml
if exist .\src\drivers\berniw\9\mixed-2.xml copy .\src\drivers\berniw\9\mixed-2.xml .\runtimed\drivers\berniw\9\mixed-2.xml
if exist .\src\drivers\berniw\9\wheel-1.xml copy .\src\drivers\berniw\9\wheel-1.xml .\runtimed\drivers\berniw\9\wheel-1.xml
:src_drivers_berniw_9

if not exist .\src\drivers\berniw goto src_drivers_berniw
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
if exist .\src\drivers\berniw\berniw.xml copy .\src\drivers\berniw\berniw.xml .\runtimed\drivers\berniw\berniw.xml
if exist .\src\drivers\berniw\logo.rgb copy .\src\drivers\berniw\logo.rgb .\runtimed\drivers\berniw\logo.rgb
if exist .\src\drivers\berniw\parameter.dat copy .\src\drivers\berniw\parameter.dat .\runtimed\drivers\berniw\parameter.dat
if exist .\src\drivers\berniw\intsinsqr.dat copy .\src\drivers\berniw\intsinsqr.dat .\runtimed\drivers\berniw\intsinsqr.dat
if exist .\src\drivers\berniw\intcossqr.dat copy .\src\drivers\berniw\intcossqr.dat .\runtimed\drivers\berniw\intcossqr.dat
:src_drivers_berniw

if not exist .\src\drivers\berniw2\1 goto src_drivers_berniw2_1
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2
call .\create_dir .\runtimed\drivers\berniw2\1
if exist .\src\drivers\berniw2\1\aalborg.xml copy .\src\drivers\berniw2\1\aalborg.xml .\runtimed\drivers\berniw2\1\aalborg.xml
if exist .\src\drivers\berniw2\1\alpine-1.xml copy .\src\drivers\berniw2\1\alpine-1.xml .\runtimed\drivers\berniw2\1\alpine-1.xml
if exist .\src\drivers\berniw2\1\a-speedway.xml copy .\src\drivers\berniw2\1\a-speedway.xml .\runtimed\drivers\berniw2\1\a-speedway.xml
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
if exist .\src\drivers\berniw2\1\michigan.xml copy .\src\drivers\berniw2\1\michigan.xml .\runtimed\drivers\berniw2\1\michigan.xml
if exist .\src\drivers\berniw2\1\mixed-1.xml copy .\src\drivers\berniw2\1\mixed-1.xml .\runtimed\drivers\berniw2\1\mixed-1.xml
if exist .\src\drivers\berniw2\1\mixed-2.xml copy .\src\drivers\berniw2\1\mixed-2.xml .\runtimed\drivers\berniw2\1\mixed-2.xml
if exist .\src\drivers\berniw2\1\wheel-1.xml copy .\src\drivers\berniw2\1\wheel-1.xml .\runtimed\drivers\berniw2\1\wheel-1.xml
:src_drivers_berniw2_1

if not exist .\src\drivers\berniw2\10 goto src_drivers_berniw2_10
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2
call .\create_dir .\runtimed\drivers\berniw2\10
if exist .\src\drivers\berniw2\10\360-modena.rgb copy .\src\drivers\berniw2\10\360-modena.rgb .\runtimed\drivers\berniw2\10\360-modena.rgb
if exist .\src\drivers\berniw2\10\aalborg.xml copy .\src\drivers\berniw2\10\aalborg.xml .\runtimed\drivers\berniw2\10\aalborg.xml
if exist .\src\drivers\berniw2\10\alpine-1.xml copy .\src\drivers\berniw2\10\alpine-1.xml .\runtimed\drivers\berniw2\10\alpine-1.xml
if exist .\src\drivers\berniw2\10\a-speedway.xml copy .\src\drivers\berniw2\10\a-speedway.xml .\runtimed\drivers\berniw2\10\a-speedway.xml
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
if exist .\src\drivers\berniw2\10\michigan.xml copy .\src\drivers\berniw2\10\michigan.xml .\runtimed\drivers\berniw2\10\michigan.xml
if exist .\src\drivers\berniw2\10\mixed-1.xml copy .\src\drivers\berniw2\10\mixed-1.xml .\runtimed\drivers\berniw2\10\mixed-1.xml
if exist .\src\drivers\berniw2\10\mixed-2.xml copy .\src\drivers\berniw2\10\mixed-2.xml .\runtimed\drivers\berniw2\10\mixed-2.xml
if exist .\src\drivers\berniw2\10\wheel-1.xml copy .\src\drivers\berniw2\10\wheel-1.xml .\runtimed\drivers\berniw2\10\wheel-1.xml
:src_drivers_berniw2_10

if not exist .\src\drivers\berniw2\2 goto src_drivers_berniw2_2
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2
call .\create_dir .\runtimed\drivers\berniw2\2
if exist .\src\drivers\berniw2\2\aalborg.xml copy .\src\drivers\berniw2\2\aalborg.xml .\runtimed\drivers\berniw2\2\aalborg.xml
if exist .\src\drivers\berniw2\2\alpine-1.xml copy .\src\drivers\berniw2\2\alpine-1.xml .\runtimed\drivers\berniw2\2\alpine-1.xml
if exist .\src\drivers\berniw2\2\a-speedway.xml copy .\src\drivers\berniw2\2\a-speedway.xml .\runtimed\drivers\berniw2\2\a-speedway.xml
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
if exist .\src\drivers\berniw2\2\michigan.xml copy .\src\drivers\berniw2\2\michigan.xml .\runtimed\drivers\berniw2\2\michigan.xml
if exist .\src\drivers\berniw2\2\mixed-1.xml copy .\src\drivers\berniw2\2\mixed-1.xml .\runtimed\drivers\berniw2\2\mixed-1.xml
if exist .\src\drivers\berniw2\2\mixed-2.xml copy .\src\drivers\berniw2\2\mixed-2.xml .\runtimed\drivers\berniw2\2\mixed-2.xml
if exist .\src\drivers\berniw2\2\wheel-1.xml copy .\src\drivers\berniw2\2\wheel-1.xml .\runtimed\drivers\berniw2\2\wheel-1.xml
:src_drivers_berniw2_2

if not exist .\src\drivers\berniw2\3 goto src_drivers_berniw2_3
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2
call .\create_dir .\runtimed\drivers\berniw2\3
if exist .\src\drivers\berniw2\3\aalborg.xml copy .\src\drivers\berniw2\3\aalborg.xml .\runtimed\drivers\berniw2\3\aalborg.xml
if exist .\src\drivers\berniw2\3\alpine-1.xml copy .\src\drivers\berniw2\3\alpine-1.xml .\runtimed\drivers\berniw2\3\alpine-1.xml
if exist .\src\drivers\berniw2\3\a-speedway.xml copy .\src\drivers\berniw2\3\a-speedway.xml .\runtimed\drivers\berniw2\3\a-speedway.xml
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
if exist .\src\drivers\berniw2\3\michigan.xml copy .\src\drivers\berniw2\3\michigan.xml .\runtimed\drivers\berniw2\3\michigan.xml
if exist .\src\drivers\berniw2\3\mixed-1.xml copy .\src\drivers\berniw2\3\mixed-1.xml .\runtimed\drivers\berniw2\3\mixed-1.xml
if exist .\src\drivers\berniw2\3\mixed-2.xml copy .\src\drivers\berniw2\3\mixed-2.xml .\runtimed\drivers\berniw2\3\mixed-2.xml
if exist .\src\drivers\berniw2\3\wheel-1.xml copy .\src\drivers\berniw2\3\wheel-1.xml .\runtimed\drivers\berniw2\3\wheel-1.xml
:src_drivers_berniw2_3

if not exist .\src\drivers\berniw2\4 goto src_drivers_berniw2_4
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2
call .\create_dir .\runtimed\drivers\berniw2\4
if exist .\src\drivers\berniw2\4\aalborg.xml copy .\src\drivers\berniw2\4\aalborg.xml .\runtimed\drivers\berniw2\4\aalborg.xml
if exist .\src\drivers\berniw2\4\alpine-1.xml copy .\src\drivers\berniw2\4\alpine-1.xml .\runtimed\drivers\berniw2\4\alpine-1.xml
if exist .\src\drivers\berniw2\4\a-speedway.xml copy .\src\drivers\berniw2\4\a-speedway.xml .\runtimed\drivers\berniw2\4\a-speedway.xml
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
if exist .\src\drivers\berniw2\4\michigan.xml copy .\src\drivers\berniw2\4\michigan.xml .\runtimed\drivers\berniw2\4\michigan.xml
if exist .\src\drivers\berniw2\4\mixed-1.xml copy .\src\drivers\berniw2\4\mixed-1.xml .\runtimed\drivers\berniw2\4\mixed-1.xml
if exist .\src\drivers\berniw2\4\mixed-2.xml copy .\src\drivers\berniw2\4\mixed-2.xml .\runtimed\drivers\berniw2\4\mixed-2.xml
if exist .\src\drivers\berniw2\4\wheel-1.xml copy .\src\drivers\berniw2\4\wheel-1.xml .\runtimed\drivers\berniw2\4\wheel-1.xml
:src_drivers_berniw2_4

if not exist .\src\drivers\berniw2\5 goto src_drivers_berniw2_5
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2
call .\create_dir .\runtimed\drivers\berniw2\5
if exist .\src\drivers\berniw2\5\aalborg.xml copy .\src\drivers\berniw2\5\aalborg.xml .\runtimed\drivers\berniw2\5\aalborg.xml
if exist .\src\drivers\berniw2\5\alpine-1.xml copy .\src\drivers\berniw2\5\alpine-1.xml .\runtimed\drivers\berniw2\5\alpine-1.xml
if exist .\src\drivers\berniw2\5\a-speedway.xml copy .\src\drivers\berniw2\5\a-speedway.xml .\runtimed\drivers\berniw2\5\a-speedway.xml
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
if exist .\src\drivers\berniw2\5\michigan.xml copy .\src\drivers\berniw2\5\michigan.xml .\runtimed\drivers\berniw2\5\michigan.xml
if exist .\src\drivers\berniw2\5\mixed-1.xml copy .\src\drivers\berniw2\5\mixed-1.xml .\runtimed\drivers\berniw2\5\mixed-1.xml
if exist .\src\drivers\berniw2\5\mixed-2.xml copy .\src\drivers\berniw2\5\mixed-2.xml .\runtimed\drivers\berniw2\5\mixed-2.xml
if exist .\src\drivers\berniw2\5\wheel-1.xml copy .\src\drivers\berniw2\5\wheel-1.xml .\runtimed\drivers\berniw2\5\wheel-1.xml
:src_drivers_berniw2_5

if not exist .\src\drivers\berniw2\6 goto src_drivers_berniw2_6
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2
call .\create_dir .\runtimed\drivers\berniw2\6
if exist .\src\drivers\berniw2\6\aalborg.xml copy .\src\drivers\berniw2\6\aalborg.xml .\runtimed\drivers\berniw2\6\aalborg.xml
if exist .\src\drivers\berniw2\6\alpine-1.xml copy .\src\drivers\berniw2\6\alpine-1.xml .\runtimed\drivers\berniw2\6\alpine-1.xml
if exist .\src\drivers\berniw2\6\a-speedway.xml copy .\src\drivers\berniw2\6\a-speedway.xml .\runtimed\drivers\berniw2\6\a-speedway.xml
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
if exist .\src\drivers\berniw2\6\michigan.xml copy .\src\drivers\berniw2\6\michigan.xml .\runtimed\drivers\berniw2\6\michigan.xml
if exist .\src\drivers\berniw2\6\mixed-1.xml copy .\src\drivers\berniw2\6\mixed-1.xml .\runtimed\drivers\berniw2\6\mixed-1.xml
if exist .\src\drivers\berniw2\6\mixed-2.xml copy .\src\drivers\berniw2\6\mixed-2.xml .\runtimed\drivers\berniw2\6\mixed-2.xml
if exist .\src\drivers\berniw2\6\wheel-1.xml copy .\src\drivers\berniw2\6\wheel-1.xml .\runtimed\drivers\berniw2\6\wheel-1.xml
:src_drivers_berniw2_6

if not exist .\src\drivers\berniw2\7 goto src_drivers_berniw2_7
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2
call .\create_dir .\runtimed\drivers\berniw2\7
if exist .\src\drivers\berniw2\7\porsche-gt3rs.rgb copy .\src\drivers\berniw2\7\porsche-gt3rs.rgb .\runtimed\drivers\berniw2\7\porsche-gt3rs.rgb
if exist .\src\drivers\berniw2\7\aalborg.xml copy .\src\drivers\berniw2\7\aalborg.xml .\runtimed\drivers\berniw2\7\aalborg.xml
if exist .\src\drivers\berniw2\7\alpine-1.xml copy .\src\drivers\berniw2\7\alpine-1.xml .\runtimed\drivers\berniw2\7\alpine-1.xml
if exist .\src\drivers\berniw2\7\a-speedway.xml copy .\src\drivers\berniw2\7\a-speedway.xml .\runtimed\drivers\berniw2\7\a-speedway.xml
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
if exist .\src\drivers\berniw2\7\michigan.xml copy .\src\drivers\berniw2\7\michigan.xml .\runtimed\drivers\berniw2\7\michigan.xml
if exist .\src\drivers\berniw2\7\mixed-1.xml copy .\src\drivers\berniw2\7\mixed-1.xml .\runtimed\drivers\berniw2\7\mixed-1.xml
if exist .\src\drivers\berniw2\7\mixed-2.xml copy .\src\drivers\berniw2\7\mixed-2.xml .\runtimed\drivers\berniw2\7\mixed-2.xml
if exist .\src\drivers\berniw2\7\wheel-1.xml copy .\src\drivers\berniw2\7\wheel-1.xml .\runtimed\drivers\berniw2\7\wheel-1.xml
:src_drivers_berniw2_7

if not exist .\src\drivers\berniw2\8 goto src_drivers_berniw2_8
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2
call .\create_dir .\runtimed\drivers\berniw2\8
if exist .\src\drivers\berniw2\8\clkdtm.rgb copy .\src\drivers\berniw2\8\clkdtm.rgb .\runtimed\drivers\berniw2\8\clkdtm.rgb
if exist .\src\drivers\berniw2\8\aalborg.xml copy .\src\drivers\berniw2\8\aalborg.xml .\runtimed\drivers\berniw2\8\aalborg.xml
if exist .\src\drivers\berniw2\8\alpine-1.xml copy .\src\drivers\berniw2\8\alpine-1.xml .\runtimed\drivers\berniw2\8\alpine-1.xml
if exist .\src\drivers\berniw2\8\a-speedway.xml copy .\src\drivers\berniw2\8\a-speedway.xml .\runtimed\drivers\berniw2\8\a-speedway.xml
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
if exist .\src\drivers\berniw2\8\michigan.xml copy .\src\drivers\berniw2\8\michigan.xml .\runtimed\drivers\berniw2\8\michigan.xml
if exist .\src\drivers\berniw2\8\mixed-1.xml copy .\src\drivers\berniw2\8\mixed-1.xml .\runtimed\drivers\berniw2\8\mixed-1.xml
if exist .\src\drivers\berniw2\8\mixed-2.xml copy .\src\drivers\berniw2\8\mixed-2.xml .\runtimed\drivers\berniw2\8\mixed-2.xml
if exist .\src\drivers\berniw2\8\wheel-1.xml copy .\src\drivers\berniw2\8\wheel-1.xml .\runtimed\drivers\berniw2\8\wheel-1.xml
:src_drivers_berniw2_8

if not exist .\src\drivers\berniw2\9 goto src_drivers_berniw2_9
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2
call .\create_dir .\runtimed\drivers\berniw2\9
if exist .\src\drivers\berniw2\9\mclaren-f1.rgb copy .\src\drivers\berniw2\9\mclaren-f1.rgb .\runtimed\drivers\berniw2\9\mclaren-f1.rgb
if exist .\src\drivers\berniw2\9\aalborg.xml copy .\src\drivers\berniw2\9\aalborg.xml .\runtimed\drivers\berniw2\9\aalborg.xml
if exist .\src\drivers\berniw2\9\alpine-1.xml copy .\src\drivers\berniw2\9\alpine-1.xml .\runtimed\drivers\berniw2\9\alpine-1.xml
if exist .\src\drivers\berniw2\9\a-speedway.xml copy .\src\drivers\berniw2\9\a-speedway.xml .\runtimed\drivers\berniw2\9\a-speedway.xml
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
if exist .\src\drivers\berniw2\9\michigan.xml copy .\src\drivers\berniw2\9\michigan.xml .\runtimed\drivers\berniw2\9\michigan.xml
if exist .\src\drivers\berniw2\9\mixed-1.xml copy .\src\drivers\berniw2\9\mixed-1.xml .\runtimed\drivers\berniw2\9\mixed-1.xml
if exist .\src\drivers\berniw2\9\mixed-2.xml copy .\src\drivers\berniw2\9\mixed-2.xml .\runtimed\drivers\berniw2\9\mixed-2.xml
if exist .\src\drivers\berniw2\9\wheel-1.xml copy .\src\drivers\berniw2\9\wheel-1.xml .\runtimed\drivers\berniw2\9\wheel-1.xml
:src_drivers_berniw2_9

if not exist .\src\drivers\berniw2 goto src_drivers_berniw2
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2
if exist .\src\drivers\berniw2\berniw2.xml copy .\src\drivers\berniw2\berniw2.xml .\runtimed\drivers\berniw2\berniw2.xml
if exist .\src\drivers\berniw2\logo.rgb copy .\src\drivers\berniw2\logo.rgb .\runtimed\drivers\berniw2\logo.rgb
if exist .\src\drivers\berniw2\parameter.dat copy .\src\drivers\berniw2\parameter.dat .\runtimed\drivers\berniw2\parameter.dat
if exist .\src\drivers\berniw2\intsinsqr.dat copy .\src\drivers\berniw2\intsinsqr.dat .\runtimed\drivers\berniw2\intsinsqr.dat
if exist .\src\drivers\berniw2\intcossqr.dat copy .\src\drivers\berniw2\intcossqr.dat .\runtimed\drivers\berniw2\intcossqr.dat
:src_drivers_berniw2

if not exist .\src\drivers\cylos1\tracksdata goto src_drivers_cylos1_tracksdata
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\cylos1
call .\create_dir .\runtimed\drivers\cylos1\tracksdata
if exist .\src\drivers\cylos1\tracksdata\car_e-track-3.xml copy .\src\drivers\cylos1\tracksdata\car_e-track-3.xml .\runtimed\drivers\cylos1\tracksdata\car_e-track-3.xml
if exist .\src\drivers\cylos1\tracksdata\car_lemans.xml copy .\src\drivers\cylos1\tracksdata\car_lemans.xml .\runtimed\drivers\cylos1\tracksdata\car_lemans.xml
if exist .\src\drivers\cylos1\tracksdata\car_test-1.xml copy .\src\drivers\cylos1\tracksdata\car_test-1.xml .\runtimed\drivers\cylos1\tracksdata\car_test-1.xml
if exist .\src\drivers\cylos1\tracksdata\lemans.xml copy .\src\drivers\cylos1\tracksdata\lemans.xml .\runtimed\drivers\cylos1\tracksdata\lemans.xml
if exist .\src\drivers\cylos1\tracksdata\michigan.xml copy .\src\drivers\cylos1\tracksdata\michigan.xml .\runtimed\drivers\cylos1\tracksdata\michigan.xml
:src_drivers_cylos1_tracksdata

if not exist .\src\drivers\cylos1 goto src_drivers_cylos1
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\cylos1
if exist .\src\drivers\cylos1\cylos1.xml copy .\src\drivers\cylos1\cylos1.xml .\runtimed\drivers\cylos1\cylos1.xml
if exist .\src\drivers\cylos1\car1.xml copy .\src\drivers\cylos1\car1.xml .\runtimed\drivers\cylos1\car1.xml
if exist .\src\drivers\cylos1\cg-nascar-rwd.rgb copy .\src\drivers\cylos1\cg-nascar-rwd.rgb .\runtimed\drivers\cylos1\cg-nascar-rwd.rgb
if exist .\src\drivers\cylos1\logo.rgb copy .\src\drivers\cylos1\logo.rgb .\runtimed\drivers\cylos1\logo.rgb
:src_drivers_cylos1

if not exist .\src\drivers\damned\1 goto src_drivers_damned_1
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\1
if exist .\src\drivers\damned\1\car.xml copy .\src\drivers\damned\1\car.xml .\runtimed\drivers\damned\1\car.xml
if exist .\src\drivers\damned\1\car-dirt.xml copy .\src\drivers\damned\1\car-dirt.xml .\runtimed\drivers\damned\1\car-dirt.xml
if exist .\src\drivers\damned\1\buggy.rgb copy .\src\drivers\damned\1\buggy.rgb .\runtimed\drivers\damned\1\buggy.rgb
if exist .\src\drivers\damned\1\logo.rgb copy .\src\drivers\damned\1\logo.rgb .\runtimed\drivers\damned\1\logo.rgb
:src_drivers_damned_1

if not exist .\src\drivers\damned\10 goto src_drivers_damned_10
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\10
if exist .\src\drivers\damned\10\car.xml copy .\src\drivers\damned\10\car.xml .\runtimed\drivers\damned\10\car.xml
if exist .\src\drivers\damned\10\logo.rgb copy .\src\drivers\damned\10\logo.rgb .\runtimed\drivers\damned\10\logo.rgb
if exist .\src\drivers\damned\10\155-DTM.rgb copy .\src\drivers\damned\10\155-DTM.rgb .\runtimed\drivers\damned\10\155-DTM.rgb
:src_drivers_damned_10

if not exist .\src\drivers\damned\2 goto src_drivers_damned_2
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\2
if exist .\src\drivers\damned\2\car.xml copy .\src\drivers\damned\2\car.xml .\runtimed\drivers\damned\2\car.xml
if exist .\src\drivers\damned\2\car-dirt.xml copy .\src\drivers\damned\2\car-dirt.xml .\runtimed\drivers\damned\2\car-dirt.xml
if exist .\src\drivers\damned\2\buggy.rgb copy .\src\drivers\damned\2\buggy.rgb .\runtimed\drivers\damned\2\buggy.rgb
if exist .\src\drivers\damned\2\logo.rgb copy .\src\drivers\damned\2\logo.rgb .\runtimed\drivers\damned\2\logo.rgb
:src_drivers_damned_2

if not exist .\src\drivers\damned\3 goto src_drivers_damned_3
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\3
if exist .\src\drivers\damned\3\p406.rgb copy .\src\drivers\damned\3\p406.rgb .\runtimed\drivers\damned\3\p406.rgb
if exist .\src\drivers\damned\3\car.xml copy .\src\drivers\damned\3\car.xml .\runtimed\drivers\damned\3\car.xml
if exist .\src\drivers\damned\3\car-dirt.xml copy .\src\drivers\damned\3\car-dirt.xml .\runtimed\drivers\damned\3\car-dirt.xml
if exist .\src\drivers\damned\3\logo.rgb copy .\src\drivers\damned\3\logo.rgb .\runtimed\drivers\damned\3\logo.rgb
:src_drivers_damned_3

if not exist .\src\drivers\damned\4 goto src_drivers_damned_4
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\4
if exist .\src\drivers\damned\4\p406.rgb copy .\src\drivers\damned\4\p406.rgb .\runtimed\drivers\damned\4\p406.rgb
if exist .\src\drivers\damned\4\car.xml copy .\src\drivers\damned\4\car.xml .\runtimed\drivers\damned\4\car.xml
if exist .\src\drivers\damned\4\car-dirt.xml copy .\src\drivers\damned\4\car-dirt.xml .\runtimed\drivers\damned\4\car-dirt.xml
if exist .\src\drivers\damned\4\torcs.rgb copy .\src\drivers\damned\4\torcs.rgb .\runtimed\drivers\damned\4\torcs.rgb
if exist .\src\drivers\damned\4\logo.rgb copy .\src\drivers\damned\4\logo.rgb .\runtimed\drivers\damned\4\logo.rgb
:src_drivers_damned_4

if not exist .\src\drivers\damned\5 goto src_drivers_damned_5
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\5
if exist .\src\drivers\damned\5\car.xml copy .\src\drivers\damned\5\car.xml .\runtimed\drivers\damned\5\car.xml
if exist .\src\drivers\damned\5\car-dirt.xml copy .\src\drivers\damned\5\car-dirt.xml .\runtimed\drivers\damned\5\car-dirt.xml
if exist .\src\drivers\damned\5\acura-nsx-sz.rgb copy .\src\drivers\damned\5\acura-nsx-sz.rgb .\runtimed\drivers\damned\5\acura-nsx-sz.rgb
if exist .\src\drivers\damned\5\logo.rgb copy .\src\drivers\damned\5\logo.rgb .\runtimed\drivers\damned\5\logo.rgb
:src_drivers_damned_5

if not exist .\src\drivers\damned\6 goto src_drivers_damned_6
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\6
if exist .\src\drivers\damned\6\car.xml copy .\src\drivers\damned\6\car.xml .\runtimed\drivers\damned\6\car.xml
if exist .\src\drivers\damned\6\car-dirt.xml copy .\src\drivers\damned\6\car-dirt.xml .\runtimed\drivers\damned\6\car-dirt.xml
if exist .\src\drivers\damned\6\logo.rgb copy .\src\drivers\damned\6\logo.rgb .\runtimed\drivers\damned\6\logo.rgb
:src_drivers_damned_6

if not exist .\src\drivers\damned\7 goto src_drivers_damned_7
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\7
if exist .\src\drivers\damned\7\porsche-gt1.rgb copy .\src\drivers\damned\7\porsche-gt1.rgb .\runtimed\drivers\damned\7\porsche-gt1.rgb
if exist .\src\drivers\damned\7\logo.rgb copy .\src\drivers\damned\7\logo.rgb .\runtimed\drivers\damned\7\logo.rgb
if exist .\src\drivers\damned\7\car.xml copy .\src\drivers\damned\7\car.xml .\runtimed\drivers\damned\7\car.xml
:src_drivers_damned_7

if not exist .\src\drivers\damned\8 goto src_drivers_damned_8
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\8
if exist .\src\drivers\damned\8\car.xml copy .\src\drivers\damned\8\car.xml .\runtimed\drivers\damned\8\car.xml
if exist .\src\drivers\damned\8\logo.rgb copy .\src\drivers\damned\8\logo.rgb .\runtimed\drivers\damned\8\logo.rgb
if exist .\src\drivers\damned\8\mclaren-f1.rgb copy .\src\drivers\damned\8\mclaren-f1.rgb .\runtimed\drivers\damned\8\mclaren-f1.rgb
:src_drivers_damned_8

if not exist .\src\drivers\damned\9 goto src_drivers_damned_9
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\9
if exist .\src\drivers\damned\9\logo.rgb copy .\src\drivers\damned\9\logo.rgb .\runtimed\drivers\damned\9\logo.rgb
if exist .\src\drivers\damned\9\car.xml copy .\src\drivers\damned\9\car.xml .\runtimed\drivers\damned\9\car.xml
if exist .\src\drivers\damned\9\360-modena.rgb copy .\src\drivers\damned\9\360-modena.rgb .\runtimed\drivers\damned\9\360-modena.rgb
:src_drivers_damned_9

if not exist .\src\drivers\damned goto src_drivers_damned
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
if exist .\src\drivers\damned\damned.xml copy .\src\drivers\damned\damned.xml .\runtimed\drivers\damned\damned.xml
if exist .\src\drivers\damned\car1.xml copy .\src\drivers\damned\car1.xml .\runtimed\drivers\damned\car1.xml
:src_drivers_damned

if not exist .\src\drivers\human\tracks\dirt-1 goto src_drivers_human_tracks_dirt_1
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-1
if exist .\src\drivers\human\tracks\dirt-1\car-torcs.xml copy .\src\drivers\human\tracks\dirt-1\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-1\car-torcs.xml
:src_drivers_human_tracks_dirt_1

if not exist .\src\drivers\human\tracks\dirt-2 goto src_drivers_human_tracks_dirt_2
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-2
if exist .\src\drivers\human\tracks\dirt-2\car-torcs.xml copy .\src\drivers\human\tracks\dirt-2\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-2\car-torcs.xml
:src_drivers_human_tracks_dirt_2

if not exist .\src\drivers\human\tracks\dirt-3 goto src_drivers_human_tracks_dirt_3
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-3
if exist .\src\drivers\human\tracks\dirt-3\car-torcs.xml copy .\src\drivers\human\tracks\dirt-3\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-3\car-torcs.xml
:src_drivers_human_tracks_dirt_3

if not exist .\src\drivers\human\tracks\dirt-4 goto src_drivers_human_tracks_dirt_4
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-4
if exist .\src\drivers\human\tracks\dirt-4\car-torcs.xml copy .\src\drivers\human\tracks\dirt-4\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-4\car-torcs.xml
:src_drivers_human_tracks_dirt_4

if not exist .\src\drivers\human\tracks\dirt-5 goto src_drivers_human_tracks_dirt_5
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-5
if exist .\src\drivers\human\tracks\dirt-5\car-torcs.xml copy .\src\drivers\human\tracks\dirt-5\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-5\car-torcs.xml
:src_drivers_human_tracks_dirt_5

if not exist .\src\drivers\human\tracks\dirt-6 goto src_drivers_human_tracks_dirt_6
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-6
if exist .\src\drivers\human\tracks\dirt-6\car-torcs.xml copy .\src\drivers\human\tracks\dirt-6\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-6\car-torcs.xml
:src_drivers_human_tracks_dirt_6

if not exist .\src\drivers\human\tracks\e-track-1 goto src_drivers_human_tracks_e_track_1
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-1
if exist .\src\drivers\human\tracks\e-track-1\car-torcs.xml copy .\src\drivers\human\tracks\e-track-1\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-1\car-torcs.xml
:src_drivers_human_tracks_e_track_1

if not exist .\src\drivers\human\tracks\e-track-2 goto src_drivers_human_tracks_e_track_2
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-2
if exist .\src\drivers\human\tracks\e-track-2\car-206W10.xml copy .\src\drivers\human\tracks\e-track-2\car-206W10.xml .\runtimed\drivers\human\tracks\e-track-2\car-206W10.xml
if exist .\src\drivers\human\tracks\e-track-2\car-torcs.xml copy .\src\drivers\human\tracks\e-track-2\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-2\car-torcs.xml
:src_drivers_human_tracks_e_track_2

if not exist .\src\drivers\human\tracks\e-track-3 goto src_drivers_human_tracks_e_track_3
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-3
if exist .\src\drivers\human\tracks\e-track-3\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-3\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\e-track-3\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-3\car-torcs.xml copy .\src\drivers\human\tracks\e-track-3\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-3\car-torcs.xml
:src_drivers_human_tracks_e_track_3

if not exist .\src\drivers\human\tracks\e-track-4 goto src_drivers_human_tracks_e_track_4
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-4
if exist .\src\drivers\human\tracks\e-track-4\car-360-modena.xml copy .\src\drivers\human\tracks\e-track-4\car-360-modena.xml .\runtimed\drivers\human\tracks\e-track-4\car-360-modena.xml
if exist .\src\drivers\human\tracks\e-track-4\car-mclaren-f1.xml copy .\src\drivers\human\tracks\e-track-4\car-mclaren-f1.xml .\runtimed\drivers\human\tracks\e-track-4\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\e-track-4\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-4\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\e-track-4\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml copy .\src\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml .\runtimed\drivers\human\tracks\e-track-4\car-porsche-gt3rs.xml
if exist .\src\drivers\human\tracks\e-track-4\car-torcs.xml copy .\src\drivers\human\tracks\e-track-4\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-4\car-torcs.xml
:src_drivers_human_tracks_e_track_4

if not exist .\src\drivers\human\tracks\e-track-5 goto src_drivers_human_tracks_e_track_5
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-5
if exist .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml copy .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml .\runtimed\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml
if exist .\src\drivers\human\tracks\e-track-5\car-torcs.xml copy .\src\drivers\human\tracks\e-track-5\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-5\car-torcs.xml
:src_drivers_human_tracks_e_track_5

if not exist .\src\drivers\human\tracks\e-track-6 goto src_drivers_human_tracks_e_track_6
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-6
if exist .\src\drivers\human\tracks\e-track-6\car-porsche-gt1.xml copy .\src\drivers\human\tracks\e-track-6\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\e-track-6\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\e-track-6\car-torcs.xml copy .\src\drivers\human\tracks\e-track-6\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-6\car-torcs.xml
:src_drivers_human_tracks_e_track_6

if not exist .\src\drivers\human\tracks\g-track-2 goto src_drivers_human_tracks_g_track_2
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\g-track-2
if exist .\src\drivers\human\tracks\g-track-2\car-360-modena.xml copy .\src\drivers\human\tracks\g-track-2\car-360-modena.xml .\runtimed\drivers\human\tracks\g-track-2\car-360-modena.xml
if exist .\src\drivers\human\tracks\g-track-2\car-mclaren-f1.xml copy .\src\drivers\human\tracks\g-track-2\car-mclaren-f1.xml .\runtimed\drivers\human\tracks\g-track-2\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\g-track-2\car-porsche-gt1.xml copy .\src\drivers\human\tracks\g-track-2\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\g-track-2\car-porsche-gt1.xml
if exist .\src\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml copy .\src\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml .\runtimed\drivers\human\tracks\g-track-2\car-porsche-gt3rs.xml
if exist .\src\drivers\human\tracks\g-track-2\car-torcs.xml copy .\src\drivers\human\tracks\g-track-2\car-torcs.xml .\runtimed\drivers\human\tracks\g-track-2\car-torcs.xml
:src_drivers_human_tracks_g_track_2

if not exist .\src\drivers\human\tracks\mixed-1 goto src_drivers_human_tracks_mixed_1
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\mixed-1
if exist .\src\drivers\human\tracks\mixed-1\car-torcs.xml copy .\src\drivers\human\tracks\mixed-1\car-torcs.xml .\runtimed\drivers\human\tracks\mixed-1\car-torcs.xml
:src_drivers_human_tracks_mixed_1

if not exist .\src\drivers\human\tracks\mixed-2 goto src_drivers_human_tracks_mixed_2
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\mixed-2
if exist .\src\drivers\human\tracks\mixed-2\car-torcs.xml copy .\src\drivers\human\tracks\mixed-2\car-torcs.xml .\runtimed\drivers\human\tracks\mixed-2\car-torcs.xml
:src_drivers_human_tracks_mixed_2

if not exist .\src\drivers\human\tracks\wheel-1 goto src_drivers_human_tracks_wheel_1
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\wheel-1
if exist .\src\drivers\human\tracks\wheel-1\car-mclaren-f1.xml copy .\src\drivers\human\tracks\wheel-1\car-mclaren-f1.xml .\runtimed\drivers\human\tracks\wheel-1\car-mclaren-f1.xml
if exist .\src\drivers\human\tracks\wheel-1\car-porsche-gt1.xml copy .\src\drivers\human\tracks\wheel-1\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\wheel-1\car-porsche-gt1.xml
:src_drivers_human_tracks_wheel_1

if not exist .\src\drivers\human goto src_drivers_human
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
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
if exist .\src\drivers\human\car-lotus-gt1.xml copy .\src\drivers\human\car-lotus-gt1.xml .\runtimed\drivers\human\car-lotus-gt1.xml
if exist .\src\drivers\human\car-mclaren-f1.xml copy .\src\drivers\human\car-mclaren-f1.xml .\runtimed\drivers\human\car-mclaren-f1.xml
if exist .\src\drivers\human\car-p406.xml copy .\src\drivers\human\car-p406.xml .\runtimed\drivers\human\car-p406.xml
if exist .\src\drivers\human\car-porsche-gt1.xml copy .\src\drivers\human\car-porsche-gt1.xml .\runtimed\drivers\human\car-porsche-gt1.xml
if exist .\src\drivers\human\car-porsche-gt3rs.xml copy .\src\drivers\human\car-porsche-gt3rs.xml .\runtimed\drivers\human\car-porsche-gt3rs.xml
if exist .\src\drivers\human\car-torcs.xml copy .\src\drivers\human\car-torcs.xml .\runtimed\drivers\human\car-torcs.xml
if exist .\src\drivers\human\car-viper-gts-r.xml copy .\src\drivers\human\car-viper-gts-r.xml .\runtimed\drivers\human\car-viper-gts-r.xml
if exist .\src\drivers\human\human.xml copy .\src\drivers\human\human.xml .\runtimed\drivers\human\human.xml
if exist .\src\drivers\human\preferences.xml copy .\src\drivers\human\preferences.xml .\runtimed\drivers\human\preferences.xml
if exist .\src\drivers\human\logo.rgb copy .\src\drivers\human\logo.rgb .\runtimed\drivers\human\logo.rgb
if exist .\src\drivers\human\mclaren-f1.rgb copy .\src\drivers\human\mclaren-f1.rgb .\runtimed\drivers\human\mclaren-f1.rgb
:src_drivers_human

if not exist .\src\drivers\inferno\tracksdata goto src_drivers_inferno_tracksdata
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno
call .\create_dir .\runtimed\drivers\inferno\tracksdata
if exist .\src\drivers\inferno\tracksdata\aalborg.xml copy .\src\drivers\inferno\tracksdata\aalborg.xml .\runtimed\drivers\inferno\tracksdata\aalborg.xml
if exist .\src\drivers\inferno\tracksdata\alpine-1.xml copy .\src\drivers\inferno\tracksdata\alpine-1.xml .\runtimed\drivers\inferno\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno\tracksdata\a-speedway.xml copy .\src\drivers\inferno\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno\tracksdata\car_aalborg.xml copy .\src\drivers\inferno\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno\tracksdata\car_eroad.xml copy .\src\drivers\inferno\tracksdata\car_eroad.xml .\runtimed\drivers\inferno\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno\tracksdata\car_michigan.xml copy .\src\drivers\inferno\tracksdata\car_michigan.xml .\runtimed\drivers\inferno\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno\tracksdata\car_s2.xml copy .\src\drivers\inferno\tracksdata\car_s2.xml .\runtimed\drivers\inferno\tracksdata\car_s2.xml
if exist .\src\drivers\inferno\tracksdata\car_test-1.xml copy .\src\drivers\inferno\tracksdata\car_test-1.xml .\runtimed\drivers\inferno\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno\tracksdata\city-1.xml copy .\src\drivers\inferno\tracksdata\city-1.xml .\runtimed\drivers\inferno\tracksdata\city-1.xml
if exist .\src\drivers\inferno\tracksdata\eroad.xml copy .\src\drivers\inferno\tracksdata\eroad.xml .\runtimed\drivers\inferno\tracksdata\eroad.xml
if exist .\src\drivers\inferno\tracksdata\e-track-1.xml copy .\src\drivers\inferno\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno\tracksdata\e-track-2.xml copy .\src\drivers\inferno\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno\tracksdata\e-track-3.xml copy .\src\drivers\inferno\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno\tracksdata\e-track-4.xml copy .\src\drivers\inferno\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno\tracksdata\e-track-5.xml copy .\src\drivers\inferno\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno\tracksdata\e-track-6.xml copy .\src\drivers\inferno\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno\tracksdata\g-track-1.xml copy .\src\drivers\inferno\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno\tracksdata\g-track-2.xml copy .\src\drivers\inferno\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno\tracksdata\michigan.xml copy .\src\drivers\inferno\tracksdata\michigan.xml .\runtimed\drivers\inferno\tracksdata\michigan.xml
if exist .\src\drivers\inferno\tracksdata\s2.xml copy .\src\drivers\inferno\tracksdata\s2.xml .\runtimed\drivers\inferno\tracksdata\s2.xml
if exist .\src\drivers\inferno\tracksdata\wheel-1.xml copy .\src\drivers\inferno\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\tracksdata\wheel-1.xml
:src_drivers_inferno_tracksdata

if not exist .\src\drivers\inferno goto src_drivers_inferno
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno
if exist .\src\drivers\inferno\inferno.xml copy .\src\drivers\inferno\inferno.xml .\runtimed\drivers\inferno\inferno.xml
if exist .\src\drivers\inferno\car1.xml copy .\src\drivers\inferno\car1.xml .\runtimed\drivers\inferno\car1.xml
if exist .\src\drivers\inferno\logo.rgb copy .\src\drivers\inferno\logo.rgb .\runtimed\drivers\inferno\logo.rgb
if exist .\src\drivers\inferno\mclaren-f1.rgb copy .\src\drivers\inferno\mclaren-f1.rgb .\runtimed\drivers\inferno\mclaren-f1.rgb
:src_drivers_inferno

if not exist .\src\drivers\inferno2\tracksdata goto src_drivers_inferno2_tracksdata
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno2
call .\create_dir .\runtimed\drivers\inferno2\tracksdata
if exist .\src\drivers\inferno2\tracksdata\aalborg.xml copy .\src\drivers\inferno2\tracksdata\aalborg.xml .\runtimed\drivers\inferno2\tracksdata\aalborg.xml
if exist .\src\drivers\inferno2\tracksdata\a-speedway.xml copy .\src\drivers\inferno2\tracksdata\a-speedway.xml .\runtimed\drivers\inferno2\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno2\tracksdata\car_aalborg.xml copy .\src\drivers\inferno2\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno2\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno2\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno2\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno2\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno2\tracksdata\car_eroad.xml copy .\src\drivers\inferno2\tracksdata\car_eroad.xml .\runtimed\drivers\inferno2\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno2\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno2\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno2\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno2\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno2\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno2\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno2\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno2\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno2\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno2\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno2\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno2\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno2\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno2\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno2\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno2\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno2\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno2\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno2\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno2\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno2\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno2\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno2\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno2\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno2\tracksdata\car_michigan.xml copy .\src\drivers\inferno2\tracksdata\car_michigan.xml .\runtimed\drivers\inferno2\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno2\tracksdata\car_s2.xml copy .\src\drivers\inferno2\tracksdata\car_s2.xml .\runtimed\drivers\inferno2\tracksdata\car_s2.xml
if exist .\src\drivers\inferno2\tracksdata\car_test-1.xml copy .\src\drivers\inferno2\tracksdata\car_test-1.xml .\runtimed\drivers\inferno2\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno2\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno2\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno2\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno2\tracksdata\eroad.xml copy .\src\drivers\inferno2\tracksdata\eroad.xml .\runtimed\drivers\inferno2\tracksdata\eroad.xml
if exist .\src\drivers\inferno2\tracksdata\e-track-1.xml copy .\src\drivers\inferno2\tracksdata\e-track-1.xml .\runtimed\drivers\inferno2\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno2\tracksdata\e-track-2.xml copy .\src\drivers\inferno2\tracksdata\e-track-2.xml .\runtimed\drivers\inferno2\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno2\tracksdata\e-track-3.xml copy .\src\drivers\inferno2\tracksdata\e-track-3.xml .\runtimed\drivers\inferno2\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno2\tracksdata\e-track-4.xml copy .\src\drivers\inferno2\tracksdata\e-track-4.xml .\runtimed\drivers\inferno2\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno2\tracksdata\e-track-5.xml copy .\src\drivers\inferno2\tracksdata\e-track-5.xml .\runtimed\drivers\inferno2\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno2\tracksdata\e-track-6.xml copy .\src\drivers\inferno2\tracksdata\e-track-6.xml .\runtimed\drivers\inferno2\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno2\tracksdata\g-track-1.xml copy .\src\drivers\inferno2\tracksdata\g-track-1.xml .\runtimed\drivers\inferno2\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno2\tracksdata\g-track-2.xml copy .\src\drivers\inferno2\tracksdata\g-track-2.xml .\runtimed\drivers\inferno2\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno2\tracksdata\michigan.xml copy .\src\drivers\inferno2\tracksdata\michigan.xml .\runtimed\drivers\inferno2\tracksdata\michigan.xml
if exist .\src\drivers\inferno2\tracksdata\s2.xml copy .\src\drivers\inferno2\tracksdata\s2.xml .\runtimed\drivers\inferno2\tracksdata\s2.xml
if exist .\src\drivers\inferno2\tracksdata\wheel-1.xml copy .\src\drivers\inferno2\tracksdata\wheel-1.xml .\runtimed\drivers\inferno2\tracksdata\wheel-1.xml
:src_drivers_inferno2_tracksdata

if not exist .\src\drivers\inferno2 goto src_drivers_inferno2
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno2
if exist .\src\drivers\inferno2\inferno2.xml copy .\src\drivers\inferno2\inferno2.xml .\runtimed\drivers\inferno2\inferno2.xml
if exist .\src\drivers\inferno2\car1.xml copy .\src\drivers\inferno2\car1.xml .\runtimed\drivers\inferno2\car1.xml
if exist .\src\drivers\inferno2\logo.rgb copy .\src\drivers\inferno2\logo.rgb .\runtimed\drivers\inferno2\logo.rgb
if exist .\src\drivers\inferno2\360-modena.rgb copy .\src\drivers\inferno2\360-modena.rgb .\runtimed\drivers\inferno2\360-modena.rgb
:src_drivers_inferno2

if not exist .\src\drivers\inferno3\tracksdata goto src_drivers_inferno3_tracksdata
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno3
call .\create_dir .\runtimed\drivers\inferno3\tracksdata
if exist .\src\drivers\inferno3\tracksdata\aalborg.xml copy .\src\drivers\inferno3\tracksdata\aalborg.xml .\runtimed\drivers\inferno3\tracksdata\aalborg.xml
if exist .\src\drivers\inferno3\tracksdata\alpine-1.xml copy .\src\drivers\inferno3\tracksdata\alpine-1.xml .\runtimed\drivers\inferno3\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno3\tracksdata\a-speedway.xml copy .\src\drivers\inferno3\tracksdata\a-speedway.xml .\runtimed\drivers\inferno3\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno3\tracksdata\car_aalborg.xml copy .\src\drivers\inferno3\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno3\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno3\tracksdata\car_alpine-1.xml copy .\src\drivers\inferno3\tracksdata\car_alpine-1.xml .\runtimed\drivers\inferno3\tracksdata\car_alpine-1.xml
if exist .\src\drivers\inferno3\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno3\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno3\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno3\tracksdata\car_eroad.xml copy .\src\drivers\inferno3\tracksdata\car_eroad.xml .\runtimed\drivers\inferno3\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno3\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno3\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno3\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno3\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno3\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno3\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno3\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno3\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno3\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno3\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno3\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno3\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno3\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno3\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno3\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno3\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno3\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno3\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno3\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno3\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno3\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno3\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno3\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno3\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno3\tracksdata\car_michigan.xml copy .\src\drivers\inferno3\tracksdata\car_michigan.xml .\runtimed\drivers\inferno3\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno3\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno3\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno3\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno3\tracksdata\eroad.xml copy .\src\drivers\inferno3\tracksdata\eroad.xml .\runtimed\drivers\inferno3\tracksdata\eroad.xml
if exist .\src\drivers\inferno3\tracksdata\e-track-1.xml copy .\src\drivers\inferno3\tracksdata\e-track-1.xml .\runtimed\drivers\inferno3\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno3\tracksdata\e-track-2.xml copy .\src\drivers\inferno3\tracksdata\e-track-2.xml .\runtimed\drivers\inferno3\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno3\tracksdata\e-track-3.xml copy .\src\drivers\inferno3\tracksdata\e-track-3.xml .\runtimed\drivers\inferno3\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno3\tracksdata\e-track-4.xml copy .\src\drivers\inferno3\tracksdata\e-track-4.xml .\runtimed\drivers\inferno3\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno3\tracksdata\e-track-5.xml copy .\src\drivers\inferno3\tracksdata\e-track-5.xml .\runtimed\drivers\inferno3\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno3\tracksdata\e-track-6.xml copy .\src\drivers\inferno3\tracksdata\e-track-6.xml .\runtimed\drivers\inferno3\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno3\tracksdata\g-track-1.xml copy .\src\drivers\inferno3\tracksdata\g-track-1.xml .\runtimed\drivers\inferno3\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno3\tracksdata\g-track-2.xml copy .\src\drivers\inferno3\tracksdata\g-track-2.xml .\runtimed\drivers\inferno3\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno3\tracksdata\michigan.xml copy .\src\drivers\inferno3\tracksdata\michigan.xml .\runtimed\drivers\inferno3\tracksdata\michigan.xml
if exist .\src\drivers\inferno3\tracksdata\wheel-1.xml copy .\src\drivers\inferno3\tracksdata\wheel-1.xml .\runtimed\drivers\inferno3\tracksdata\wheel-1.xml
:src_drivers_inferno3_tracksdata

if not exist .\src\drivers\inferno3 goto src_drivers_inferno3
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno3
if exist .\src\drivers\inferno3\inferno3.xml copy .\src\drivers\inferno3\inferno3.xml .\runtimed\drivers\inferno3\inferno3.xml
if exist .\src\drivers\inferno3\car1.xml copy .\src\drivers\inferno3\car1.xml .\runtimed\drivers\inferno3\car1.xml
if exist .\src\drivers\inferno3\logo.rgb copy .\src\drivers\inferno3\logo.rgb .\runtimed\drivers\inferno3\logo.rgb
if exist .\src\drivers\inferno3\porsche-gt1.rgb copy .\src\drivers\inferno3\porsche-gt1.rgb .\runtimed\drivers\inferno3\porsche-gt1.rgb
:src_drivers_inferno3

if not exist .\src\drivers\inferno4\tracksdata goto src_drivers_inferno4_tracksdata
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno4
call .\create_dir .\runtimed\drivers\inferno4\tracksdata
if exist .\src\drivers\inferno4\tracksdata\aalborg.xml copy .\src\drivers\inferno4\tracksdata\aalborg.xml .\runtimed\drivers\inferno4\tracksdata\aalborg.xml
if exist .\src\drivers\inferno4\tracksdata\alpine-1.xml copy .\src\drivers\inferno4\tracksdata\alpine-1.xml .\runtimed\drivers\inferno4\tracksdata\alpine-1.xml
if exist .\src\drivers\inferno4\tracksdata\a-speedway.xml copy .\src\drivers\inferno4\tracksdata\a-speedway.xml .\runtimed\drivers\inferno4\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno4\tracksdata\car_aalborg.xml copy .\src\drivers\inferno4\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno4\tracksdata\car_aalborg.xml
if exist .\src\drivers\inferno4\tracksdata\car_a-speedway.xml copy .\src\drivers\inferno4\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno4\tracksdata\car_a-speedway.xml
if exist .\src\drivers\inferno4\tracksdata\car_eroad.xml copy .\src\drivers\inferno4\tracksdata\car_eroad.xml .\runtimed\drivers\inferno4\tracksdata\car_eroad.xml
if exist .\src\drivers\inferno4\tracksdata\car_e-track-1.xml copy .\src\drivers\inferno4\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno4\tracksdata\car_e-track-1.xml
if exist .\src\drivers\inferno4\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno4\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno4\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno4\tracksdata\car_e-track-3.xml copy .\src\drivers\inferno4\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno4\tracksdata\car_e-track-3.xml
if exist .\src\drivers\inferno4\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno4\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno4\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno4\tracksdata\car_e-track-5.xml copy .\src\drivers\inferno4\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno4\tracksdata\car_e-track-5.xml
if exist .\src\drivers\inferno4\tracksdata\car_e-track-6.xml copy .\src\drivers\inferno4\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno4\tracksdata\car_e-track-6.xml
if exist .\src\drivers\inferno4\tracksdata\car_g-track-1.xml copy .\src\drivers\inferno4\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno4\tracksdata\car_g-track-1.xml
if exist .\src\drivers\inferno4\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno4\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno4\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno4\tracksdata\car_michigan.xml copy .\src\drivers\inferno4\tracksdata\car_michigan.xml .\runtimed\drivers\inferno4\tracksdata\car_michigan.xml
if exist .\src\drivers\inferno4\tracksdata\car_test-1.xml copy .\src\drivers\inferno4\tracksdata\car_test-1.xml .\runtimed\drivers\inferno4\tracksdata\car_test-1.xml
if exist .\src\drivers\inferno4\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno4\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno4\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno4\tracksdata\dirt-2.xml copy .\src\drivers\inferno4\tracksdata\dirt-2.xml .\runtimed\drivers\inferno4\tracksdata\dirt-2.xml
if exist .\src\drivers\inferno4\tracksdata\eroad.xml copy .\src\drivers\inferno4\tracksdata\eroad.xml .\runtimed\drivers\inferno4\tracksdata\eroad.xml
if exist .\src\drivers\inferno4\tracksdata\e-track-1.xml copy .\src\drivers\inferno4\tracksdata\e-track-1.xml .\runtimed\drivers\inferno4\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno4\tracksdata\e-track-2.xml copy .\src\drivers\inferno4\tracksdata\e-track-2.xml .\runtimed\drivers\inferno4\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno4\tracksdata\e-track-3.xml copy .\src\drivers\inferno4\tracksdata\e-track-3.xml .\runtimed\drivers\inferno4\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno4\tracksdata\e-track-4.xml copy .\src\drivers\inferno4\tracksdata\e-track-4.xml .\runtimed\drivers\inferno4\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno4\tracksdata\e-track-5.xml copy .\src\drivers\inferno4\tracksdata\e-track-5.xml .\runtimed\drivers\inferno4\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno4\tracksdata\e-track-6.xml copy .\src\drivers\inferno4\tracksdata\e-track-6.xml .\runtimed\drivers\inferno4\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno4\tracksdata\g-track-1.xml copy .\src\drivers\inferno4\tracksdata\g-track-1.xml .\runtimed\drivers\inferno4\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno4\tracksdata\g-track-2.xml copy .\src\drivers\inferno4\tracksdata\g-track-2.xml .\runtimed\drivers\inferno4\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno4\tracksdata\michigan.xml copy .\src\drivers\inferno4\tracksdata\michigan.xml .\runtimed\drivers\inferno4\tracksdata\michigan.xml
if exist .\src\drivers\inferno4\tracksdata\wheel-1.xml copy .\src\drivers\inferno4\tracksdata\wheel-1.xml .\runtimed\drivers\inferno4\tracksdata\wheel-1.xml
:src_drivers_inferno4_tracksdata

if not exist .\src\drivers\inferno4 goto src_drivers_inferno4
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno4
if exist .\src\drivers\inferno4\inferno4.xml copy .\src\drivers\inferno4\inferno4.xml .\runtimed\drivers\inferno4\inferno4.xml
if exist .\src\drivers\inferno4\car1.xml copy .\src\drivers\inferno4\car1.xml .\runtimed\drivers\inferno4\car1.xml
if exist .\src\drivers\inferno4\logo.rgb copy .\src\drivers\inferno4\logo.rgb .\runtimed\drivers\inferno4\logo.rgb
if exist .\src\drivers\inferno4\xj-220.rgb copy .\src\drivers\inferno4\xj-220.rgb .\runtimed\drivers\inferno4\xj-220.rgb
if exist .\src\drivers\inferno4\clkdtm.rgb copy .\src\drivers\inferno4\clkdtm.rgb .\runtimed\drivers\inferno4\clkdtm.rgb
:src_drivers_inferno4

if not exist .\src\drivers\inferno5\tracksdata goto src_drivers_inferno5_tracksdata
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno5
call .\create_dir .\runtimed\drivers\inferno5\tracksdata
if exist .\src\drivers\inferno5\tracksdata\aalborg.xml copy .\src\drivers\inferno5\tracksdata\aalborg.xml .\runtimed\drivers\inferno5\tracksdata\aalborg.xml
if exist .\src\drivers\inferno5\tracksdata\a-speedway.xml copy .\src\drivers\inferno5\tracksdata\a-speedway.xml .\runtimed\drivers\inferno5\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno5\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno5\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno5\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno5\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno5\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno5\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno5\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno5\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno5\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno5\tracksdata\eroad.xml copy .\src\drivers\inferno5\tracksdata\eroad.xml .\runtimed\drivers\inferno5\tracksdata\eroad.xml
if exist .\src\drivers\inferno5\tracksdata\e-track-1.xml copy .\src\drivers\inferno5\tracksdata\e-track-1.xml .\runtimed\drivers\inferno5\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno5\tracksdata\e-track-2.xml copy .\src\drivers\inferno5\tracksdata\e-track-2.xml .\runtimed\drivers\inferno5\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno5\tracksdata\e-track-3.xml copy .\src\drivers\inferno5\tracksdata\e-track-3.xml .\runtimed\drivers\inferno5\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno5\tracksdata\e-track-4.xml copy .\src\drivers\inferno5\tracksdata\e-track-4.xml .\runtimed\drivers\inferno5\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno5\tracksdata\e-track-5.xml copy .\src\drivers\inferno5\tracksdata\e-track-5.xml .\runtimed\drivers\inferno5\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno5\tracksdata\e-track-6.xml copy .\src\drivers\inferno5\tracksdata\e-track-6.xml .\runtimed\drivers\inferno5\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno5\tracksdata\g-track-1.xml copy .\src\drivers\inferno5\tracksdata\g-track-1.xml .\runtimed\drivers\inferno5\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno5\tracksdata\g-track-2.xml copy .\src\drivers\inferno5\tracksdata\g-track-2.xml .\runtimed\drivers\inferno5\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno5\tracksdata\michigan.xml copy .\src\drivers\inferno5\tracksdata\michigan.xml .\runtimed\drivers\inferno5\tracksdata\michigan.xml
if exist .\src\drivers\inferno5\tracksdata\wheel-1.xml copy .\src\drivers\inferno5\tracksdata\wheel-1.xml .\runtimed\drivers\inferno5\tracksdata\wheel-1.xml
:src_drivers_inferno5_tracksdata

if not exist .\src\drivers\inferno5 goto src_drivers_inferno5
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno5
if exist .\src\drivers\inferno5\inferno5.xml copy .\src\drivers\inferno5\inferno5.xml .\runtimed\drivers\inferno5\inferno5.xml
if exist .\src\drivers\inferno5\car1.xml copy .\src\drivers\inferno5\car1.xml .\runtimed\drivers\inferno5\car1.xml
if exist .\src\drivers\inferno5\logo.rgb copy .\src\drivers\inferno5\logo.rgb .\runtimed\drivers\inferno5\logo.rgb
if exist .\src\drivers\inferno5\gt40.rgb copy .\src\drivers\inferno5\gt40.rgb .\runtimed\drivers\inferno5\gt40.rgb
:src_drivers_inferno5

if not exist .\src\drivers\inferno6\tracksdata goto src_drivers_inferno6_tracksdata
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno6
call .\create_dir .\runtimed\drivers\inferno6\tracksdata
if exist .\src\drivers\inferno6\tracksdata\aalborg.xml copy .\src\drivers\inferno6\tracksdata\aalborg.xml .\runtimed\drivers\inferno6\tracksdata\aalborg.xml
if exist .\src\drivers\inferno6\tracksdata\a-speedway.xml copy .\src\drivers\inferno6\tracksdata\a-speedway.xml .\runtimed\drivers\inferno6\tracksdata\a-speedway.xml
if exist .\src\drivers\inferno6\tracksdata\car_e-track-2.xml copy .\src\drivers\inferno6\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno6\tracksdata\car_e-track-2.xml
if exist .\src\drivers\inferno6\tracksdata\car_e-track-4.xml copy .\src\drivers\inferno6\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno6\tracksdata\car_e-track-4.xml
if exist .\src\drivers\inferno6\tracksdata\car_g-track-2.xml copy .\src\drivers\inferno6\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno6\tracksdata\car_g-track-2.xml
if exist .\src\drivers\inferno6\tracksdata\car_wheel-1.xml copy .\src\drivers\inferno6\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno6\tracksdata\car_wheel-1.xml
if exist .\src\drivers\inferno6\tracksdata\eroad.xml copy .\src\drivers\inferno6\tracksdata\eroad.xml .\runtimed\drivers\inferno6\tracksdata\eroad.xml
if exist .\src\drivers\inferno6\tracksdata\e-track-1.xml copy .\src\drivers\inferno6\tracksdata\e-track-1.xml .\runtimed\drivers\inferno6\tracksdata\e-track-1.xml
if exist .\src\drivers\inferno6\tracksdata\e-track-2.xml copy .\src\drivers\inferno6\tracksdata\e-track-2.xml .\runtimed\drivers\inferno6\tracksdata\e-track-2.xml
if exist .\src\drivers\inferno6\tracksdata\e-track-3.xml copy .\src\drivers\inferno6\tracksdata\e-track-3.xml .\runtimed\drivers\inferno6\tracksdata\e-track-3.xml
if exist .\src\drivers\inferno6\tracksdata\e-track-4.xml copy .\src\drivers\inferno6\tracksdata\e-track-4.xml .\runtimed\drivers\inferno6\tracksdata\e-track-4.xml
if exist .\src\drivers\inferno6\tracksdata\e-track-5.xml copy .\src\drivers\inferno6\tracksdata\e-track-5.xml .\runtimed\drivers\inferno6\tracksdata\e-track-5.xml
if exist .\src\drivers\inferno6\tracksdata\e-track-6.xml copy .\src\drivers\inferno6\tracksdata\e-track-6.xml .\runtimed\drivers\inferno6\tracksdata\e-track-6.xml
if exist .\src\drivers\inferno6\tracksdata\g-track-1.xml copy .\src\drivers\inferno6\tracksdata\g-track-1.xml .\runtimed\drivers\inferno6\tracksdata\g-track-1.xml
if exist .\src\drivers\inferno6\tracksdata\g-track-2.xml copy .\src\drivers\inferno6\tracksdata\g-track-2.xml .\runtimed\drivers\inferno6\tracksdata\g-track-2.xml
if exist .\src\drivers\inferno6\tracksdata\michigan.xml copy .\src\drivers\inferno6\tracksdata\michigan.xml .\runtimed\drivers\inferno6\tracksdata\michigan.xml
if exist .\src\drivers\inferno6\tracksdata\wheel-1.xml copy .\src\drivers\inferno6\tracksdata\wheel-1.xml .\runtimed\drivers\inferno6\tracksdata\wheel-1.xml
:src_drivers_inferno6_tracksdata

if not exist .\src\drivers\inferno6 goto src_drivers_inferno6
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno6
if exist .\src\drivers\inferno6\inferno6.xml copy .\src\drivers\inferno6\inferno6.xml .\runtimed\drivers\inferno6\inferno6.xml
if exist .\src\drivers\inferno6\car1.xml copy .\src\drivers\inferno6\car1.xml .\runtimed\drivers\inferno6\car1.xml
if exist .\src\drivers\inferno6\logo.rgb copy .\src\drivers\inferno6\logo.rgb .\runtimed\drivers\inferno6\logo.rgb
if exist .\src\drivers\inferno6\porsche-gt3rs.rgb copy .\src\drivers\inferno6\porsche-gt3rs.rgb .\runtimed\drivers\inferno6\porsche-gt3rs.rgb
:src_drivers_inferno6

if not exist .\src\drivers\K1999\1 goto src_drivers_K1999_1
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\K1999
call .\create_dir .\runtimed\drivers\K1999\1
if exist .\src\drivers\K1999\1\buggy.rgb copy .\src\drivers\K1999\1\buggy.rgb .\runtimed\drivers\K1999\1\buggy.rgb
if exist .\src\drivers\K1999\1\settings.xml copy .\src\drivers\K1999\1\settings.xml .\runtimed\drivers\K1999\1\settings.xml
:src_drivers_K1999_1

if not exist .\src\drivers\K1999\2 goto src_drivers_K1999_2
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\K1999
call .\create_dir .\runtimed\drivers\K1999\2
if exist .\src\drivers\K1999\2\cg-nascar-rwd.rgb copy .\src\drivers\K1999\2\cg-nascar-rwd.rgb .\runtimed\drivers\K1999\2\cg-nascar-rwd.rgb
if exist .\src\drivers\K1999\2\settings.xml copy .\src\drivers\K1999\2\settings.xml .\runtimed\drivers\K1999\2\settings.xml
:src_drivers_K1999_2

if not exist .\src\drivers\K1999 goto src_drivers_K1999
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\K1999
if exist .\src\drivers\K1999\K1999.xml copy .\src\drivers\K1999\K1999.xml .\runtimed\drivers\K1999\K1999.xml
if exist .\src\drivers\K1999\logo.rgb copy .\src\drivers\K1999\logo.rgb .\runtimed\drivers\K1999\logo.rgb
:src_drivers_K1999

if not exist .\src\drivers\lliaw\tracksdata goto src_drivers_lliaw_tracksdata
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\lliaw
call .\create_dir .\runtimed\drivers\lliaw\tracksdata
if exist .\src\drivers\lliaw\tracksdata\car_e-track-3.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-3.xml .\runtimed\drivers\lliaw\tracksdata\car_e-track-3.xml
if exist .\src\drivers\lliaw\tracksdata\car_e-track-4.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-4.xml .\runtimed\drivers\lliaw\tracksdata\car_e-track-4.xml
if exist .\src\drivers\lliaw\tracksdata\car_e-track-6.xml copy .\src\drivers\lliaw\tracksdata\car_e-track-6.xml .\runtimed\drivers\lliaw\tracksdata\car_e-track-6.xml
if exist .\src\drivers\lliaw\tracksdata\car_eroad.xml copy .\src\drivers\lliaw\tracksdata\car_eroad.xml .\runtimed\drivers\lliaw\tracksdata\car_eroad.xml
:src_drivers_lliaw_tracksdata

if not exist .\src\drivers\lliaw goto src_drivers_lliaw
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\lliaw
if exist .\src\drivers\lliaw\lliaw.xml copy .\src\drivers\lliaw\lliaw.xml .\runtimed\drivers\lliaw\lliaw.xml
if exist .\src\drivers\lliaw\car.xml copy .\src\drivers\lliaw\car.xml .\runtimed\drivers\lliaw\car.xml
if exist .\src\drivers\lliaw\viper-gts-r.rgb copy .\src\drivers\lliaw\viper-gts-r.rgb .\runtimed\drivers\lliaw\viper-gts-r.rgb
if exist .\src\drivers\lliaw\logo.rgb copy .\src\drivers\lliaw\logo.rgb .\runtimed\drivers\lliaw\logo.rgb
:src_drivers_lliaw

if not exist .\src\drivers\tanhoj\tracksdata goto src_drivers_tanhoj_tracksdata
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tanhoj
call .\create_dir .\runtimed\drivers\tanhoj\tracksdata
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
if exist .\src\drivers\tanhoj\tracksdata\michigan.xml copy .\src\drivers\tanhoj\tracksdata\michigan.xml .\runtimed\drivers\tanhoj\tracksdata\michigan.xml
if exist .\src\drivers\tanhoj\tracksdata\s2.xml copy .\src\drivers\tanhoj\tracksdata\s2.xml .\runtimed\drivers\tanhoj\tracksdata\s2.xml
if exist .\src\drivers\tanhoj\tracksdata\wheel-1.xml copy .\src\drivers\tanhoj\tracksdata\wheel-1.xml .\runtimed\drivers\tanhoj\tracksdata\wheel-1.xml
:src_drivers_tanhoj_tracksdata

if not exist .\src\drivers\tanhoj goto src_drivers_tanhoj
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tanhoj
if exist .\src\drivers\tanhoj\tanhoj.xml copy .\src\drivers\tanhoj\tanhoj.xml .\runtimed\drivers\tanhoj\tanhoj.xml
if exist .\src\drivers\tanhoj\car1.xml copy .\src\drivers\tanhoj\car1.xml .\runtimed\drivers\tanhoj\car1.xml
if exist .\src\drivers\tanhoj\logo.rgb copy .\src\drivers\tanhoj\logo.rgb .\runtimed\drivers\tanhoj\logo.rgb
if exist .\src\drivers\tanhoj\cg-nascar-rwd.rgb copy .\src\drivers\tanhoj\cg-nascar-rwd.rgb .\runtimed\drivers\tanhoj\cg-nascar-rwd.rgb
:src_drivers_tanhoj

if not exist .\src\drivers\tita\tracksdata goto src_drivers_tita_tracksdata
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tita
call .\create_dir .\runtimed\drivers\tita\tracksdata
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
if exist .\src\drivers\tita\tracksdata\michigan.xml copy .\src\drivers\tita\tracksdata\michigan.xml .\runtimed\drivers\tita\tracksdata\michigan.xml
if exist .\src\drivers\tita\tracksdata\s2.xml copy .\src\drivers\tita\tracksdata\s2.xml .\runtimed\drivers\tita\tracksdata\s2.xml
if exist .\src\drivers\tita\tracksdata\wheel-1.xml copy .\src\drivers\tita\tracksdata\wheel-1.xml .\runtimed\drivers\tita\tracksdata\wheel-1.xml
:src_drivers_tita_tracksdata

if not exist .\src\drivers\tita goto src_drivers_tita
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tita
if exist .\src\drivers\tita\tita.xml copy .\src\drivers\tita\tita.xml .\runtimed\drivers\tita\tita.xml
if exist .\src\drivers\tita\car.xml copy .\src\drivers\tita\car.xml .\runtimed\drivers\tita\car.xml
if exist .\src\drivers\tita\logo.rgb copy .\src\drivers\tita\logo.rgb .\runtimed\drivers\tita\logo.rgb
if exist .\src\drivers\tita\lotus-gt1.rgb copy .\src\drivers\tita\lotus-gt1.rgb .\runtimed\drivers\tita\lotus-gt1.rgb
:src_drivers_tita

if not exist .\src\drivers\tutor goto src_drivers_tutor
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tutor
if exist .\src\drivers\tutor\tutor.xml copy .\src\drivers\tutor\tutor.xml .\runtimed\drivers\tutor\tutor.xml
if exist .\src\drivers\tutor\360-modena.rgb copy .\src\drivers\tutor\360-modena.rgb .\runtimed\drivers\tutor\360-modena.rgb
if exist .\src\drivers\tutor\logo.rgb copy .\src\drivers\tutor\logo.rgb .\runtimed\drivers\tutor\logo.rgb
:src_drivers_tutor

if not exist .\src\drivers\tutorial1 goto src_drivers_tutorial1
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tutorial1
if exist .\src\drivers\tutorial1\tutorial1.xml copy .\src\drivers\tutorial1\tutorial1.xml .\runtimed\drivers\tutorial1\tutorial1.xml
:src_drivers_tutorial1

if not exist .\src\drivers\tutorial2 goto src_drivers_tutorial2
call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tutorial2
if exist .\src\drivers\tutorial2\tutorial2.xml copy .\src\drivers\tutorial2\tutorial2.xml .\runtimed\drivers\tutorial2\tutorial2.xml
:src_drivers_tutorial2

if not exist .\src\libs\tgf goto src_libs_tgf
call .\create_dir .\runtimed
call .\create_dir .\runtimed\config
if exist .\src\libs\tgf\screen.xml copy .\src\libs\tgf\screen.xml .\runtimed\config\screen.xml
if exist .\src\libs\tgf\params.dtd copy .\src\libs\tgf\params.dtd .\runtimed\config\params.dtd
:src_libs_tgf

if not exist .\src\modules\graphic\ssggraph goto src_modules_graphic_ssggraph
call .\create_dir .\runtimed
call .\create_dir .\runtimed\config
if exist .\src\modules\graphic\ssggraph\graph.xml copy .\src\modules\graphic\ssggraph\graph.xml .\runtimed\config\graph.xml
:src_modules_graphic_ssggraph

if not exist .\src\modules\raceman\practice\practice goto src_modules_raceman_practice_practice
call .\create_dir .\runtimed
call .\create_dir .\runtimed\config
call .\create_dir .\runtimed\config\practice
if exist .\src\modules\raceman\practice\practice\practice.xml copy .\src\modules\raceman\practice\practice\practice.xml .\runtimed\config\practice\practice.xml
:src_modules_raceman_practice_practice

if not exist .\src\modules\raceman\quickrace goto src_modules_raceman_quickrace
call .\create_dir .\runtimed
call .\create_dir .\runtimed\config
call .\create_dir .\runtimed\config\quickrace
if exist .\src\modules\raceman\quickrace\qrace.xml copy .\src\modules\raceman\quickrace\qrace.xml .\runtimed\config\quickrace\qrace.xml
:src_modules_raceman_quickrace

if not exist .\src\modules\raceman\simplerace goto src_modules_raceman_simplerace
call .\create_dir .\runtimed
call .\create_dir .\runtimed\config
call .\create_dir .\runtimed\config\simplerace
if exist .\src\modules\raceman\simplerace\simplerace.xml copy .\src\modules\raceman\simplerace\simplerace.xml .\runtimed\config\simplerace\simplerace.xml
:src_modules_raceman_simplerace

if not exist .\src\modules\telemetry goto src_modules_telemetry
call .\create_dir .\runtimed
call .\create_dir .\runtimed\telemetry
if exist .\src\modules\telemetry\telemetry.sh copy .\src\modules\telemetry\telemetry.sh .\runtimed\telemetry\telemetry.sh
:src_modules_telemetry

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw2

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\cylos1

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
call .\create_dir .\runtimed\drivers\inferno3

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno4

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno5

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno6

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\K1999

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\lliaw

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tanhoj

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tita

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tutor

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tutorial1

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tutorial2

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
call .\create_dir .\runtimed\modules\raceman
call .\create_dir .\runtimed\modules\raceman\practice
call .\create_dir .\runtimed\modules\raceman\practice\control

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\raceman

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\raceman

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\raceman

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\simu

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\telemetry

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\track
