@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

call .\create_dir .\export
call .\create_dir .\export\include
copy .\src\interfaces\graphic.h .\export\include\graphic.h
copy .\src\interfaces\raceman.h .\export\include\raceman.h
copy .\src\interfaces\robot.h .\export\include\robot.h
copy .\src\interfaces\simu.h .\export\include\simu.h
copy .\src\interfaces\track.h .\export\include\track.h
copy .\src\interfaces\car.h .\export\include\car.h
copy .\src\interfaces\ttypes.h .\export\include\ttypes.h
copy .\src\interfaces\telemetry.h .\export\include\telemetry.h
copy .\src\interfaces\practicectrl.h .\export\include\practicectrl.h
copy .\src\interfaces\playerpref.h .\export\include\playerpref.h
copy .\src\interfaces\js.h .\export\include\js.h

call .\create_dir .\export
call .\create_dir .\export\include
copy .\src\libs\txml\xml.h .\export\include\xml.h
copy .\src\libs\txml\xmlparse.h .\export\include\xmlparse.h

call .\create_dir .\export
call .\create_dir .\export\include
copy .\src\libs\tgf\tgf.h .\export\include\tgf.h
copy .\src\libs\tgf\os.h .\export\include\os.h
copy .\src\libs\tgf\queue.h .\export\include\queue.h

call .\create_dir .\export
call .\create_dir .\export\include
copy .\src\libs\torcs\torcs.h .\export\include\torcs.h

call .\create_dir .\export
call .\create_dir .\export\include
copy .\src\libs\racemantools\racemantools.h .\export\include\racemantools.h

call .\create_dir .\export
call .\create_dir .\export\include
copy .\src\libs\robottools\robottools.h .\export\include\robottools.h

call .\create_dir .\export
call .\create_dir .\export\include
copy .\src\windows\osspec.h .\export\include\osspec.h

call .\create_dir .\export
call .\create_dir .\export\include
call .\create_dir .\export\include\3D
copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Basic.h .\export\include\3D\Basic.h
copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Matrix.h .\export\include\3D\Matrix.h
copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Point.h .\export\include\3D\Point.h
copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Quaternion.h .\export\include\3D\Quaternion.h
copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Tuple3.h .\export\include\3D\Tuple3.h
copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Tuple4.h .\export\include\3D\Tuple4.h
copy .\src\modules\simu\simuv2\SOLID-2.0\include\3D\Vector.h .\export\include\3D\Vector.h

call .\create_dir .\export
call .\create_dir .\export\include
call .\create_dir .\export\include\SOLID
copy .\src\modules\simu\simuv2\SOLID-2.0\include\SOLID\solid.h .\export\include\SOLID\solid.h

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\1
copy .\src\drivers\berniw\1\cg-nascar-rwd.rgb .\runtimed\drivers\berniw\1\cg-nascar-rwd.rgb
copy .\src\drivers\berniw\1\aalborg.xml .\runtimed\drivers\berniw\1\aalborg.xml
copy .\src\drivers\berniw\1\a-speedway.xml .\runtimed\drivers\berniw\1\a-speedway.xml
copy .\src\drivers\berniw\1\dirt-1.xml .\runtimed\drivers\berniw\1\dirt-1.xml
copy .\src\drivers\berniw\1\dirt-2.xml .\runtimed\drivers\berniw\1\dirt-2.xml
copy .\src\drivers\berniw\1\dirt-3.xml .\runtimed\drivers\berniw\1\dirt-3.xml
copy .\src\drivers\berniw\1\dirt-4.xml .\runtimed\drivers\berniw\1\dirt-4.xml
copy .\src\drivers\berniw\1\dirt-5.xml .\runtimed\drivers\berniw\1\dirt-5.xml
copy .\src\drivers\berniw\1\dirt-6.xml .\runtimed\drivers\berniw\1\dirt-6.xml
copy .\src\drivers\berniw\1\eroad.xml .\runtimed\drivers\berniw\1\eroad.xml
copy .\src\drivers\berniw\1\e-track-1.xml .\runtimed\drivers\berniw\1\e-track-1.xml
copy .\src\drivers\berniw\1\e-track-2.xml .\runtimed\drivers\berniw\1\e-track-2.xml
copy .\src\drivers\berniw\1\e-track-3.xml .\runtimed\drivers\berniw\1\e-track-3.xml
copy .\src\drivers\berniw\1\e-track-4.xml .\runtimed\drivers\berniw\1\e-track-4.xml
copy .\src\drivers\berniw\1\e-track-5.xml .\runtimed\drivers\berniw\1\e-track-5.xml
copy .\src\drivers\berniw\1\e-track-6.xml .\runtimed\drivers\berniw\1\e-track-6.xml
copy .\src\drivers\berniw\1\g-track-1.xml .\runtimed\drivers\berniw\1\g-track-1.xml
copy .\src\drivers\berniw\1\g-track-2.xml .\runtimed\drivers\berniw\1\g-track-2.xml
copy .\src\drivers\berniw\1\michigan.xml .\runtimed\drivers\berniw\1\michigan.xml
copy .\src\drivers\berniw\1\mixed-1.xml .\runtimed\drivers\berniw\1\mixed-1.xml
copy .\src\drivers\berniw\1\mixed-2.xml .\runtimed\drivers\berniw\1\mixed-2.xml
copy .\src\drivers\berniw\1\wheel-1.xml .\runtimed\drivers\berniw\1\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\10
copy .\src\drivers\berniw\10\buggy.rgb .\runtimed\drivers\berniw\10\buggy.rgb
copy .\src\drivers\berniw\10\aalborg.xml .\runtimed\drivers\berniw\10\aalborg.xml
copy .\src\drivers\berniw\10\a-speedway.xml .\runtimed\drivers\berniw\10\a-speedway.xml
copy .\src\drivers\berniw\10\dirt-1.xml .\runtimed\drivers\berniw\10\dirt-1.xml
copy .\src\drivers\berniw\10\dirt-2.xml .\runtimed\drivers\berniw\10\dirt-2.xml
copy .\src\drivers\berniw\10\dirt-3.xml .\runtimed\drivers\berniw\10\dirt-3.xml
copy .\src\drivers\berniw\10\dirt-4.xml .\runtimed\drivers\berniw\10\dirt-4.xml
copy .\src\drivers\berniw\10\dirt-5.xml .\runtimed\drivers\berniw\10\dirt-5.xml
copy .\src\drivers\berniw\10\dirt-6.xml .\runtimed\drivers\berniw\10\dirt-6.xml
copy .\src\drivers\berniw\10\eroad.xml .\runtimed\drivers\berniw\10\eroad.xml
copy .\src\drivers\berniw\10\e-track-1.xml .\runtimed\drivers\berniw\10\e-track-1.xml
copy .\src\drivers\berniw\10\e-track-2.xml .\runtimed\drivers\berniw\10\e-track-2.xml
copy .\src\drivers\berniw\10\e-track-3.xml .\runtimed\drivers\berniw\10\e-track-3.xml
copy .\src\drivers\berniw\10\e-track-4.xml .\runtimed\drivers\berniw\10\e-track-4.xml
copy .\src\drivers\berniw\10\e-track-5.xml .\runtimed\drivers\berniw\10\e-track-5.xml
copy .\src\drivers\berniw\10\e-track-6.xml .\runtimed\drivers\berniw\10\e-track-6.xml
copy .\src\drivers\berniw\10\g-track-1.xml .\runtimed\drivers\berniw\10\g-track-1.xml
copy .\src\drivers\berniw\10\michigan.xml .\runtimed\drivers\berniw\10\michigan.xml
copy .\src\drivers\berniw\10\mixed-1.xml .\runtimed\drivers\berniw\10\mixed-1.xml
copy .\src\drivers\berniw\10\mixed-2.xml .\runtimed\drivers\berniw\10\mixed-2.xml
copy .\src\drivers\berniw\10\wheel-1.xml .\runtimed\drivers\berniw\10\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\2
copy .\src\drivers\berniw\2\cg-nascar-rwd.rgb .\runtimed\drivers\berniw\2\cg-nascar-rwd.rgb
copy .\src\drivers\berniw\2\aalborg.xml .\runtimed\drivers\berniw\2\aalborg.xml
copy .\src\drivers\berniw\2\a-speedway.xml .\runtimed\drivers\berniw\2\a-speedway.xml
copy .\src\drivers\berniw\2\dirt-1.xml .\runtimed\drivers\berniw\2\dirt-1.xml
copy .\src\drivers\berniw\2\dirt-2.xml .\runtimed\drivers\berniw\2\dirt-2.xml
copy .\src\drivers\berniw\2\dirt-3.xml .\runtimed\drivers\berniw\2\dirt-3.xml
copy .\src\drivers\berniw\2\dirt-4.xml .\runtimed\drivers\berniw\2\dirt-4.xml
copy .\src\drivers\berniw\2\dirt-5.xml .\runtimed\drivers\berniw\2\dirt-5.xml
copy .\src\drivers\berniw\2\dirt-6.xml .\runtimed\drivers\berniw\2\dirt-6.xml
copy .\src\drivers\berniw\2\eroad.xml .\runtimed\drivers\berniw\2\eroad.xml
copy .\src\drivers\berniw\2\e-track-1.xml .\runtimed\drivers\berniw\2\e-track-1.xml
copy .\src\drivers\berniw\2\e-track-2.xml .\runtimed\drivers\berniw\2\e-track-2.xml
copy .\src\drivers\berniw\2\e-track-3.xml .\runtimed\drivers\berniw\2\e-track-3.xml
copy .\src\drivers\berniw\2\e-track-4.xml .\runtimed\drivers\berniw\2\e-track-4.xml
copy .\src\drivers\berniw\2\e-track-5.xml .\runtimed\drivers\berniw\2\e-track-5.xml
copy .\src\drivers\berniw\2\e-track-6.xml .\runtimed\drivers\berniw\2\e-track-6.xml
copy .\src\drivers\berniw\2\g-track-1.xml .\runtimed\drivers\berniw\2\g-track-1.xml
copy .\src\drivers\berniw\2\g-track-2.xml .\runtimed\drivers\berniw\2\g-track-2.xml
copy .\src\drivers\berniw\2\michigan.xml .\runtimed\drivers\berniw\2\michigan.xml
copy .\src\drivers\berniw\2\mixed-1.xml .\runtimed\drivers\berniw\2\mixed-1.xml
copy .\src\drivers\berniw\2\mixed-2.xml .\runtimed\drivers\berniw\2\mixed-2.xml
copy .\src\drivers\berniw\2\wheel-1.xml .\runtimed\drivers\berniw\2\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\3
copy .\src\drivers\berniw\3\porsche-gt1.rgb .\runtimed\drivers\berniw\3\porsche-gt1.rgb
copy .\src\drivers\berniw\3\aalborg.xml .\runtimed\drivers\berniw\3\aalborg.xml
copy .\src\drivers\berniw\3\a-speedway.xml .\runtimed\drivers\berniw\3\a-speedway.xml
copy .\src\drivers\berniw\3\dirt-1.xml .\runtimed\drivers\berniw\3\dirt-1.xml
copy .\src\drivers\berniw\3\dirt-2.xml .\runtimed\drivers\berniw\3\dirt-2.xml
copy .\src\drivers\berniw\3\dirt-3.xml .\runtimed\drivers\berniw\3\dirt-3.xml
copy .\src\drivers\berniw\3\dirt-4.xml .\runtimed\drivers\berniw\3\dirt-4.xml
copy .\src\drivers\berniw\3\dirt-5.xml .\runtimed\drivers\berniw\3\dirt-5.xml
copy .\src\drivers\berniw\3\dirt-6.xml .\runtimed\drivers\berniw\3\dirt-6.xml
copy .\src\drivers\berniw\3\eroad.xml .\runtimed\drivers\berniw\3\eroad.xml
copy .\src\drivers\berniw\3\e-track-1.xml .\runtimed\drivers\berniw\3\e-track-1.xml
copy .\src\drivers\berniw\3\e-track-2.xml .\runtimed\drivers\berniw\3\e-track-2.xml
copy .\src\drivers\berniw\3\e-track-3.xml .\runtimed\drivers\berniw\3\e-track-3.xml
copy .\src\drivers\berniw\3\e-track-4.xml .\runtimed\drivers\berniw\3\e-track-4.xml
copy .\src\drivers\berniw\3\e-track-5.xml .\runtimed\drivers\berniw\3\e-track-5.xml
copy .\src\drivers\berniw\3\e-track-6.xml .\runtimed\drivers\berniw\3\e-track-6.xml
copy .\src\drivers\berniw\3\g-track-1.xml .\runtimed\drivers\berniw\3\g-track-1.xml
copy .\src\drivers\berniw\3\g-track-2.xml .\runtimed\drivers\berniw\3\g-track-2.xml
copy .\src\drivers\berniw\3\michigan.xml .\runtimed\drivers\berniw\3\michigan.xml
copy .\src\drivers\berniw\3\mixed-1.xml .\runtimed\drivers\berniw\3\mixed-1.xml
copy .\src\drivers\berniw\3\mixed-2.xml .\runtimed\drivers\berniw\3\mixed-2.xml
copy .\src\drivers\berniw\3\wheel-1.xml .\runtimed\drivers\berniw\3\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\4
copy .\src\drivers\berniw\4\viper-gts-r.rgb .\runtimed\drivers\berniw\4\viper-gts-r.rgb
copy .\src\drivers\berniw\4\aalborg.xml .\runtimed\drivers\berniw\4\aalborg.xml
copy .\src\drivers\berniw\4\a-speedway.xml .\runtimed\drivers\berniw\4\a-speedway.xml
copy .\src\drivers\berniw\4\dirt-1.xml .\runtimed\drivers\berniw\4\dirt-1.xml
copy .\src\drivers\berniw\4\dirt-2.xml .\runtimed\drivers\berniw\4\dirt-2.xml
copy .\src\drivers\berniw\4\dirt-3.xml .\runtimed\drivers\berniw\4\dirt-3.xml
copy .\src\drivers\berniw\4\dirt-4.xml .\runtimed\drivers\berniw\4\dirt-4.xml
copy .\src\drivers\berniw\4\dirt-5.xml .\runtimed\drivers\berniw\4\dirt-5.xml
copy .\src\drivers\berniw\4\dirt-6.xml .\runtimed\drivers\berniw\4\dirt-6.xml
copy .\src\drivers\berniw\4\eroad.xml .\runtimed\drivers\berniw\4\eroad.xml
copy .\src\drivers\berniw\4\e-track-1.xml .\runtimed\drivers\berniw\4\e-track-1.xml
copy .\src\drivers\berniw\4\e-track-2.xml .\runtimed\drivers\berniw\4\e-track-2.xml
copy .\src\drivers\berniw\4\e-track-3.xml .\runtimed\drivers\berniw\4\e-track-3.xml
copy .\src\drivers\berniw\4\e-track-4.xml .\runtimed\drivers\berniw\4\e-track-4.xml
copy .\src\drivers\berniw\4\e-track-5.xml .\runtimed\drivers\berniw\4\e-track-5.xml
copy .\src\drivers\berniw\4\e-track-6.xml .\runtimed\drivers\berniw\4\e-track-6.xml
copy .\src\drivers\berniw\4\g-track-1.xml .\runtimed\drivers\berniw\4\g-track-1.xml
copy .\src\drivers\berniw\4\michigan.xml .\runtimed\drivers\berniw\4\michigan.xml
copy .\src\drivers\berniw\4\mixed-1.xml .\runtimed\drivers\berniw\4\mixed-1.xml
copy .\src\drivers\berniw\4\mixed-2.xml .\runtimed\drivers\berniw\4\mixed-2.xml
copy .\src\drivers\berniw\4\wheel-1.xml .\runtimed\drivers\berniw\4\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\5
copy .\src\drivers\berniw\5\cg-nascar-rwd.rgb .\runtimed\drivers\berniw\5\cg-nascar-rwd.rgb
copy .\src\drivers\berniw\5\aalborg.xml .\runtimed\drivers\berniw\5\aalborg.xml
copy .\src\drivers\berniw\5\a-speedway.xml .\runtimed\drivers\berniw\5\a-speedway.xml
copy .\src\drivers\berniw\5\dirt-1.xml .\runtimed\drivers\berniw\5\dirt-1.xml
copy .\src\drivers\berniw\5\dirt-2.xml .\runtimed\drivers\berniw\5\dirt-2.xml
copy .\src\drivers\berniw\5\dirt-3.xml .\runtimed\drivers\berniw\5\dirt-3.xml
copy .\src\drivers\berniw\5\dirt-4.xml .\runtimed\drivers\berniw\5\dirt-4.xml
copy .\src\drivers\berniw\5\dirt-5.xml .\runtimed\drivers\berniw\5\dirt-5.xml
copy .\src\drivers\berniw\5\dirt-6.xml .\runtimed\drivers\berniw\5\dirt-6.xml
copy .\src\drivers\berniw\5\eroad.xml .\runtimed\drivers\berniw\5\eroad.xml
copy .\src\drivers\berniw\5\e-track-1.xml .\runtimed\drivers\berniw\5\e-track-1.xml
copy .\src\drivers\berniw\5\e-track-2.xml .\runtimed\drivers\berniw\5\e-track-2.xml
copy .\src\drivers\berniw\5\e-track-3.xml .\runtimed\drivers\berniw\5\e-track-3.xml
copy .\src\drivers\berniw\5\e-track-4.xml .\runtimed\drivers\berniw\5\e-track-4.xml
copy .\src\drivers\berniw\5\e-track-5.xml .\runtimed\drivers\berniw\5\e-track-5.xml
copy .\src\drivers\berniw\5\e-track-6.xml .\runtimed\drivers\berniw\5\e-track-6.xml
copy .\src\drivers\berniw\5\g-track-1.xml .\runtimed\drivers\berniw\5\g-track-1.xml
copy .\src\drivers\berniw\5\g-track-2.xml .\runtimed\drivers\berniw\5\g-track-2.xml
copy .\src\drivers\berniw\5\michigan.xml .\runtimed\drivers\berniw\5\michigan.xml
copy .\src\drivers\berniw\5\mixed-1.xml .\runtimed\drivers\berniw\5\mixed-1.xml
copy .\src\drivers\berniw\5\mixed-2.xml .\runtimed\drivers\berniw\5\mixed-2.xml
copy .\src\drivers\berniw\5\wheel-1.xml .\runtimed\drivers\berniw\5\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\6
copy .\src\drivers\berniw\6\155-DTM.rgb .\runtimed\drivers\berniw\6\155-DTM.rgb
copy .\src\drivers\berniw\6\aalborg.xml .\runtimed\drivers\berniw\6\aalborg.xml
copy .\src\drivers\berniw\6\a-speedway.xml .\runtimed\drivers\berniw\6\a-speedway.xml
copy .\src\drivers\berniw\6\dirt-1.xml .\runtimed\drivers\berniw\6\dirt-1.xml
copy .\src\drivers\berniw\6\dirt-2.xml .\runtimed\drivers\berniw\6\dirt-2.xml
copy .\src\drivers\berniw\6\dirt-3.xml .\runtimed\drivers\berniw\6\dirt-3.xml
copy .\src\drivers\berniw\6\dirt-4.xml .\runtimed\drivers\berniw\6\dirt-4.xml
copy .\src\drivers\berniw\6\dirt-5.xml .\runtimed\drivers\berniw\6\dirt-5.xml
copy .\src\drivers\berniw\6\dirt-6.xml .\runtimed\drivers\berniw\6\dirt-6.xml
copy .\src\drivers\berniw\6\eroad.xml .\runtimed\drivers\berniw\6\eroad.xml
copy .\src\drivers\berniw\6\e-track-1.xml .\runtimed\drivers\berniw\6\e-track-1.xml
copy .\src\drivers\berniw\6\e-track-2.xml .\runtimed\drivers\berniw\6\e-track-2.xml
copy .\src\drivers\berniw\6\e-track-3.xml .\runtimed\drivers\berniw\6\e-track-3.xml
copy .\src\drivers\berniw\6\e-track-4.xml .\runtimed\drivers\berniw\6\e-track-4.xml
copy .\src\drivers\berniw\6\e-track-5.xml .\runtimed\drivers\berniw\6\e-track-5.xml
copy .\src\drivers\berniw\6\e-track-6.xml .\runtimed\drivers\berniw\6\e-track-6.xml
copy .\src\drivers\berniw\6\g-track-1.xml .\runtimed\drivers\berniw\6\g-track-1.xml
copy .\src\drivers\berniw\6\michigan.xml .\runtimed\drivers\berniw\6\michigan.xml
copy .\src\drivers\berniw\6\mixed-1.xml .\runtimed\drivers\berniw\6\mixed-1.xml
copy .\src\drivers\berniw\6\mixed-2.xml .\runtimed\drivers\berniw\6\mixed-2.xml
copy .\src\drivers\berniw\6\wheel-1.xml .\runtimed\drivers\berniw\6\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\7
copy .\src\drivers\berniw\7\lotus-gt1.rgb .\runtimed\drivers\berniw\7\lotus-gt1.rgb
copy .\src\drivers\berniw\7\aalborg.xml .\runtimed\drivers\berniw\7\aalborg.xml
copy .\src\drivers\berniw\7\a-speedway.xml .\runtimed\drivers\berniw\7\a-speedway.xml
copy .\src\drivers\berniw\7\dirt-1.xml .\runtimed\drivers\berniw\7\dirt-1.xml
copy .\src\drivers\berniw\7\dirt-2.xml .\runtimed\drivers\berniw\7\dirt-2.xml
copy .\src\drivers\berniw\7\dirt-3.xml .\runtimed\drivers\berniw\7\dirt-3.xml
copy .\src\drivers\berniw\7\dirt-4.xml .\runtimed\drivers\berniw\7\dirt-4.xml
copy .\src\drivers\berniw\7\dirt-5.xml .\runtimed\drivers\berniw\7\dirt-5.xml
copy .\src\drivers\berniw\7\dirt-6.xml .\runtimed\drivers\berniw\7\dirt-6.xml
copy .\src\drivers\berniw\7\eroad.xml .\runtimed\drivers\berniw\7\eroad.xml
copy .\src\drivers\berniw\7\e-track-1.xml .\runtimed\drivers\berniw\7\e-track-1.xml
copy .\src\drivers\berniw\7\e-track-2.xml .\runtimed\drivers\berniw\7\e-track-2.xml
copy .\src\drivers\berniw\7\e-track-3.xml .\runtimed\drivers\berniw\7\e-track-3.xml
copy .\src\drivers\berniw\7\e-track-4.xml .\runtimed\drivers\berniw\7\e-track-4.xml
copy .\src\drivers\berniw\7\e-track-5.xml .\runtimed\drivers\berniw\7\e-track-5.xml
copy .\src\drivers\berniw\7\e-track-6.xml .\runtimed\drivers\berniw\7\e-track-6.xml
copy .\src\drivers\berniw\7\g-track-1.xml .\runtimed\drivers\berniw\7\g-track-1.xml
copy .\src\drivers\berniw\7\g-track-2.xml .\runtimed\drivers\berniw\7\g-track-2.xml
copy .\src\drivers\berniw\7\michigan.xml .\runtimed\drivers\berniw\7\michigan.xml
copy .\src\drivers\berniw\7\mixed-1.xml .\runtimed\drivers\berniw\7\mixed-1.xml
copy .\src\drivers\berniw\7\mixed-2.xml .\runtimed\drivers\berniw\7\mixed-2.xml
copy .\src\drivers\berniw\7\wheel-1.xml .\runtimed\drivers\berniw\7\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\8
copy .\src\drivers\berniw\8\corvette.rgb .\runtimed\drivers\berniw\8\corvette.rgb
copy .\src\drivers\berniw\8\aalborg.xml .\runtimed\drivers\berniw\8\aalborg.xml
copy .\src\drivers\berniw\8\a-speedway.xml .\runtimed\drivers\berniw\8\a-speedway.xml
copy .\src\drivers\berniw\8\dirt-1.xml .\runtimed\drivers\berniw\8\dirt-1.xml
copy .\src\drivers\berniw\8\dirt-2.xml .\runtimed\drivers\berniw\8\dirt-2.xml
copy .\src\drivers\berniw\8\dirt-3.xml .\runtimed\drivers\berniw\8\dirt-3.xml
copy .\src\drivers\berniw\8\dirt-4.xml .\runtimed\drivers\berniw\8\dirt-4.xml
copy .\src\drivers\berniw\8\dirt-5.xml .\runtimed\drivers\berniw\8\dirt-5.xml
copy .\src\drivers\berniw\8\dirt-6.xml .\runtimed\drivers\berniw\8\dirt-6.xml
copy .\src\drivers\berniw\8\eroad.xml .\runtimed\drivers\berniw\8\eroad.xml
copy .\src\drivers\berniw\8\e-track-1.xml .\runtimed\drivers\berniw\8\e-track-1.xml
copy .\src\drivers\berniw\8\e-track-2.xml .\runtimed\drivers\berniw\8\e-track-2.xml
copy .\src\drivers\berniw\8\e-track-3.xml .\runtimed\drivers\berniw\8\e-track-3.xml
copy .\src\drivers\berniw\8\e-track-4.xml .\runtimed\drivers\berniw\8\e-track-4.xml
copy .\src\drivers\berniw\8\e-track-5.xml .\runtimed\drivers\berniw\8\e-track-5.xml
copy .\src\drivers\berniw\8\e-track-6.xml .\runtimed\drivers\berniw\8\e-track-6.xml
copy .\src\drivers\berniw\8\g-track-1.xml .\runtimed\drivers\berniw\8\g-track-1.xml
copy .\src\drivers\berniw\8\michigan.xml .\runtimed\drivers\berniw\8\michigan.xml
copy .\src\drivers\berniw\8\mixed-1.xml .\runtimed\drivers\berniw\8\mixed-1.xml
copy .\src\drivers\berniw\8\mixed-2.xml .\runtimed\drivers\berniw\8\mixed-2.xml
copy .\src\drivers\berniw\8\wheel-1.xml .\runtimed\drivers\berniw\8\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
call .\create_dir .\runtimed\drivers\berniw\9
copy .\src\drivers\berniw\9\mclaren-f1.rgb .\runtimed\drivers\berniw\9\mclaren-f1.rgb
copy .\src\drivers\berniw\9\aalborg.xml .\runtimed\drivers\berniw\9\aalborg.xml
copy .\src\drivers\berniw\9\a-speedway.xml .\runtimed\drivers\berniw\9\a-speedway.xml
copy .\src\drivers\berniw\9\dirt-1.xml .\runtimed\drivers\berniw\9\dirt-1.xml
copy .\src\drivers\berniw\9\dirt-2.xml .\runtimed\drivers\berniw\9\dirt-2.xml
copy .\src\drivers\berniw\9\dirt-3.xml .\runtimed\drivers\berniw\9\dirt-3.xml
copy .\src\drivers\berniw\9\dirt-4.xml .\runtimed\drivers\berniw\9\dirt-4.xml
copy .\src\drivers\berniw\9\dirt-5.xml .\runtimed\drivers\berniw\9\dirt-5.xml
copy .\src\drivers\berniw\9\dirt-6.xml .\runtimed\drivers\berniw\9\dirt-6.xml
copy .\src\drivers\berniw\9\eroad.xml .\runtimed\drivers\berniw\9\eroad.xml
copy .\src\drivers\berniw\9\e-track-1.xml .\runtimed\drivers\berniw\9\e-track-1.xml
copy .\src\drivers\berniw\9\e-track-2.xml .\runtimed\drivers\berniw\9\e-track-2.xml
copy .\src\drivers\berniw\9\e-track-3.xml .\runtimed\drivers\berniw\9\e-track-3.xml
copy .\src\drivers\berniw\9\e-track-4.xml .\runtimed\drivers\berniw\9\e-track-4.xml
copy .\src\drivers\berniw\9\e-track-5.xml .\runtimed\drivers\berniw\9\e-track-5.xml
copy .\src\drivers\berniw\9\e-track-6.xml .\runtimed\drivers\berniw\9\e-track-6.xml
copy .\src\drivers\berniw\9\g-track-1.xml .\runtimed\drivers\berniw\9\g-track-1.xml
copy .\src\drivers\berniw\9\g-track-2.xml .\runtimed\drivers\berniw\9\g-track-2.xml
copy .\src\drivers\berniw\9\michigan.xml .\runtimed\drivers\berniw\9\michigan.xml
copy .\src\drivers\berniw\9\mixed-1.xml .\runtimed\drivers\berniw\9\mixed-1.xml
copy .\src\drivers\berniw\9\mixed-2.xml .\runtimed\drivers\berniw\9\mixed-2.xml
copy .\src\drivers\berniw\9\wheel-1.xml .\runtimed\drivers\berniw\9\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw
copy .\src\drivers\berniw\berniw.xml .\runtimed\drivers\berniw\berniw.xml
copy .\src\drivers\berniw\logo.rgb .\runtimed\drivers\berniw\logo.rgb
copy .\src\drivers\berniw\parameter.dat .\runtimed\drivers\berniw\parameter.dat
copy .\src\drivers\berniw\intsinsqr.dat .\runtimed\drivers\berniw\intsinsqr.dat
copy .\src\drivers\berniw\intcossqr.dat .\runtimed\drivers\berniw\intcossqr.dat

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\berniw

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\cylos1
call .\create_dir .\runtimed\drivers\cylos1\tracksship
copy .\src\drivers\cylos1\tracksdata\car_e-track-3.xml .\runtimed\drivers\cylos1\tracksship\car_e-track-3.xml
copy .\src\drivers\cylos1\tracksdata\car_lemans.xml .\runtimed\drivers\cylos1\tracksship\car_lemans.xml
copy .\src\drivers\cylos1\tracksdata\car_test-1.xml .\runtimed\drivers\cylos1\tracksship\car_test-1.xml
copy .\src\drivers\cylos1\tracksdata\lemans.xml .\runtimed\drivers\cylos1\tracksship\lemans.xml
copy .\src\drivers\cylos1\tracksdata\michigan.xml .\runtimed\drivers\cylos1\tracksship\michigan.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\cylos1
copy .\src\drivers\cylos1\cylos1.xml .\runtimed\drivers\cylos1\cylos1.xml
copy .\src\drivers\cylos1\car1.xml .\runtimed\drivers\cylos1\car1.xml
copy .\src\drivers\cylos1\cg-nascar-rwd.rgb .\runtimed\drivers\cylos1\cg-nascar-rwd.rgb
copy .\src\drivers\cylos1\logo.rgb .\runtimed\drivers\cylos1\logo.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\cylos1

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\1
copy .\src\drivers\damned\1\car.xml .\runtimed\drivers\damned\1\car.xml
copy .\src\drivers\damned\1\car-dirt.xml .\runtimed\drivers\damned\1\car-dirt.xml
copy .\src\drivers\damned\1\buggy.rgb .\runtimed\drivers\damned\1\buggy.rgb
copy .\src\drivers\damned\1\logo.rgb .\runtimed\drivers\damned\1\logo.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\10
copy .\src\drivers\damned\10\car.xml .\runtimed\drivers\damned\10\car.xml
copy .\src\drivers\damned\10\logo.rgb .\runtimed\drivers\damned\10\logo.rgb
copy .\src\drivers\damned\10\155-DTM.rgb .\runtimed\drivers\damned\10\155-DTM.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\2
copy .\src\drivers\damned\2\car.xml .\runtimed\drivers\damned\2\car.xml
copy .\src\drivers\damned\2\car-dirt.xml .\runtimed\drivers\damned\2\car-dirt.xml
copy .\src\drivers\damned\2\buggy.rgb .\runtimed\drivers\damned\2\buggy.rgb
copy .\src\drivers\damned\2\logo.rgb .\runtimed\drivers\damned\2\logo.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\3
copy .\src\drivers\damned\3\p406.rgb .\runtimed\drivers\damned\3\p406.rgb
copy .\src\drivers\damned\3\car.xml .\runtimed\drivers\damned\3\car.xml
copy .\src\drivers\damned\3\car-dirt.xml .\runtimed\drivers\damned\3\car-dirt.xml
copy .\src\drivers\damned\3\logo.rgb .\runtimed\drivers\damned\3\logo.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\4
copy .\src\drivers\damned\4\p406.rgb .\runtimed\drivers\damned\4\p406.rgb
copy .\src\drivers\damned\4\car.xml .\runtimed\drivers\damned\4\car.xml
copy .\src\drivers\damned\4\car-dirt.xml .\runtimed\drivers\damned\4\car-dirt.xml
copy .\src\drivers\damned\4\torcs.rgb .\runtimed\drivers\damned\4\torcs.rgb
copy .\src\drivers\damned\4\logo.rgb .\runtimed\drivers\damned\4\logo.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\5
copy .\src\drivers\damned\5\car.xml .\runtimed\drivers\damned\5\car.xml
copy .\src\drivers\damned\5\car-dirt.xml .\runtimed\drivers\damned\5\car-dirt.xml
copy .\src\drivers\damned\5\acura-nsx-sz.rgb .\runtimed\drivers\damned\5\acura-nsx-sz.rgb
copy .\src\drivers\damned\5\logo.rgb .\runtimed\drivers\damned\5\logo.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\6
copy .\src\drivers\damned\6\acura-nsx-sz.rgb .\runtimed\drivers\damned\6\acura-nsx-sz.rgb
copy .\src\drivers\damned\6\car.xml .\runtimed\drivers\damned\6\car.xml
copy .\src\drivers\damned\6\logo.rgb .\runtimed\drivers\damned\6\logo.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\7
copy .\src\drivers\damned\7\porsche-gt1.rgb .\runtimed\drivers\damned\7\porsche-gt1.rgb
copy .\src\drivers\damned\7\logo.rgb .\runtimed\drivers\damned\7\logo.rgb
copy .\src\drivers\damned\7\car.xml .\runtimed\drivers\damned\7\car.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\8
copy .\src\drivers\damned\8\car.xml .\runtimed\drivers\damned\8\car.xml
copy .\src\drivers\damned\8\logo.rgb .\runtimed\drivers\damned\8\logo.rgb
copy .\src\drivers\damned\8\mclaren-f1.rgb .\runtimed\drivers\damned\8\mclaren-f1.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
call .\create_dir .\runtimed\drivers\damned\9
copy .\src\drivers\damned\9\logo.rgb .\runtimed\drivers\damned\9\logo.rgb
copy .\src\drivers\damned\9\car.xml .\runtimed\drivers\damned\9\car.xml
copy .\src\drivers\damned\9\360-modena.rgb .\runtimed\drivers\damned\9\360-modena.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned
copy .\src\drivers\damned\damned.xml .\runtimed\drivers\damned\damned.xml
copy .\src\drivers\damned\car1.xml .\runtimed\drivers\damned\car1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\damned

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-1
copy .\src\drivers\human\tracks\dirt-1\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-1\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-2
copy .\src\drivers\human\tracks\dirt-2\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-2\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-3
copy .\src\drivers\human\tracks\dirt-3\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-3\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-4
copy .\src\drivers\human\tracks\dirt-4\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-4\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-5
copy .\src\drivers\human\tracks\dirt-5\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-5\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\dirt-6
copy .\src\drivers\human\tracks\dirt-6\car-torcs.xml .\runtimed\drivers\human\tracks\dirt-6\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-1
copy .\src\drivers\human\tracks\e-track-1\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-1\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-2
copy .\src\drivers\human\tracks\e-track-2\car-206W10.xml .\runtimed\drivers\human\tracks\e-track-2\car-206W10.xml
copy .\src\drivers\human\tracks\e-track-2\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-2\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-3
copy .\src\drivers\human\tracks\e-track-3\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\e-track-3\car-porsche-gt1.xml
copy .\src\drivers\human\tracks\e-track-3\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-3\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-4
copy .\src\drivers\human\tracks\e-track-4\car-360-modena.xml .\runtimed\drivers\human\tracks\e-track-4\car-360-modena.xml
copy .\src\drivers\human\tracks\e-track-4\car-mclaren-f1.xml .\runtimed\drivers\human\tracks\e-track-4\car-mclaren-f1.xml
copy .\src\drivers\human\tracks\e-track-4\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\e-track-4\car-porsche-gt1.xml
copy .\src\drivers\human\tracks\e-track-4\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-4\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-5
copy .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml .\runtimed\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml
copy .\src\drivers\human\tracks\e-track-5\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-5\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\e-track-6
copy .\src\drivers\human\tracks\e-track-6\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\e-track-6\car-porsche-gt1.xml
copy .\src\drivers\human\tracks\e-track-6\car-torcs.xml .\runtimed\drivers\human\tracks\e-track-6\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\mixed-1
copy .\src\drivers\human\tracks\mixed-1\car-torcs.xml .\runtimed\drivers\human\tracks\mixed-1\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\mixed-2
copy .\src\drivers\human\tracks\mixed-2\car-torcs.xml .\runtimed\drivers\human\tracks\mixed-2\car-torcs.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
call .\create_dir .\runtimed\drivers\human\tracks
call .\create_dir .\runtimed\drivers\human\tracks\wheel-1
copy .\src\drivers\human\tracks\wheel-1\car-mclaren-f1.xml .\runtimed\drivers\human\tracks\wheel-1\car-mclaren-f1.xml
copy .\src\drivers\human\tracks\wheel-1\car-porsche-gt1.xml .\runtimed\drivers\human\tracks\wheel-1\car-porsche-gt1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human
copy .\src\drivers\human\car-155-DTM.xml .\runtimed\drivers\human\car-155-DTM.xml
copy .\src\drivers\human\car-360-modena.xml .\runtimed\drivers\human\car-360-modena.xml
copy .\src\drivers\human\car-acura-nsx-sz.xml .\runtimed\drivers\human\car-acura-nsx-sz.xml
copy .\src\drivers\human\car-buggy.xml .\runtimed\drivers\human\car-buggy.xml
copy .\src\drivers\human\car-cg-gt-rwd.xml .\runtimed\drivers\human\car-cg-gt-rwd.xml
copy .\src\drivers\human\car-cg-nascar-fwd.xml .\runtimed\drivers\human\car-cg-nascar-fwd.xml
copy .\src\drivers\human\car-cg-nascar-rwd.xml .\runtimed\drivers\human\car-cg-nascar-rwd.xml
copy .\src\drivers\human\car-corvette.xml .\runtimed\drivers\human\car-corvette.xml
copy .\src\drivers\human\car-lotus-gt1.xml .\runtimed\drivers\human\car-lotus-gt1.xml
copy .\src\drivers\human\car-mclaren-f1.xml .\runtimed\drivers\human\car-mclaren-f1.xml
copy .\src\drivers\human\car-p406.xml .\runtimed\drivers\human\car-p406.xml
copy .\src\drivers\human\car-porsche-gt1.xml .\runtimed\drivers\human\car-porsche-gt1.xml
copy .\src\drivers\human\car-torcs.xml .\runtimed\drivers\human\car-torcs.xml
copy .\src\drivers\human\car-viper-gts-r.xml .\runtimed\drivers\human\car-viper-gts-r.xml
copy .\src\drivers\human\human.xml .\runtimed\drivers\human\human.xml
copy .\src\drivers\human\preferences.xml .\runtimed\drivers\human\preferences.xml
copy .\src\drivers\human\logo.rgb .\runtimed\drivers\human\logo.rgb
copy .\src\drivers\human\mclaren-f1.rgb .\runtimed\drivers\human\mclaren-f1.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\human

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno
call .\create_dir .\runtimed\drivers\inferno\tracksship
copy .\src\drivers\inferno\tracksdata\aalborg.xml .\runtimed\drivers\inferno\tracksship\aalborg.xml
copy .\src\drivers\inferno\tracksdata\a-speedway.xml .\runtimed\drivers\inferno\tracksship\a-speedway.xml
copy .\src\drivers\inferno\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno\tracksship\car_aalborg.xml
copy .\src\drivers\inferno\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno\tracksship\car_a-speedway.xml
copy .\src\drivers\inferno\tracksdata\car_eroad.xml .\runtimed\drivers\inferno\tracksship\car_eroad.xml
copy .\src\drivers\inferno\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno\tracksship\car_e-track-1.xml
copy .\src\drivers\inferno\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno\tracksship\car_e-track-2.xml
copy .\src\drivers\inferno\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno\tracksship\car_e-track-3.xml
copy .\src\drivers\inferno\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno\tracksship\car_e-track-4.xml
copy .\src\drivers\inferno\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno\tracksship\car_e-track-5.xml
copy .\src\drivers\inferno\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno\tracksship\car_e-track-6.xml
copy .\src\drivers\inferno\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno\tracksship\car_g-track-1.xml
copy .\src\drivers\inferno\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno\tracksship\car_g-track-2.xml
copy .\src\drivers\inferno\tracksdata\car_michigan.xml .\runtimed\drivers\inferno\tracksship\car_michigan.xml
copy .\src\drivers\inferno\tracksdata\car_s2.xml .\runtimed\drivers\inferno\tracksship\car_s2.xml
copy .\src\drivers\inferno\tracksdata\car_test-1.xml .\runtimed\drivers\inferno\tracksship\car_test-1.xml
copy .\src\drivers\inferno\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno\tracksship\car_wheel-1.xml
copy .\src\drivers\inferno\tracksdata\city-1.xml .\runtimed\drivers\inferno\tracksship\city-1.xml
copy .\src\drivers\inferno\tracksdata\eroad.xml .\runtimed\drivers\inferno\tracksship\eroad.xml
copy .\src\drivers\inferno\tracksdata\e-track-1.xml .\runtimed\drivers\inferno\tracksship\e-track-1.xml
copy .\src\drivers\inferno\tracksdata\e-track-2.xml .\runtimed\drivers\inferno\tracksship\e-track-2.xml
copy .\src\drivers\inferno\tracksdata\e-track-3.xml .\runtimed\drivers\inferno\tracksship\e-track-3.xml
copy .\src\drivers\inferno\tracksdata\e-track-4.xml .\runtimed\drivers\inferno\tracksship\e-track-4.xml
copy .\src\drivers\inferno\tracksdata\e-track-5.xml .\runtimed\drivers\inferno\tracksship\e-track-5.xml
copy .\src\drivers\inferno\tracksdata\e-track-6.xml .\runtimed\drivers\inferno\tracksship\e-track-6.xml
copy .\src\drivers\inferno\tracksdata\g-track-1.xml .\runtimed\drivers\inferno\tracksship\g-track-1.xml
copy .\src\drivers\inferno\tracksdata\g-track-2.xml .\runtimed\drivers\inferno\tracksship\g-track-2.xml
copy .\src\drivers\inferno\tracksdata\michigan.xml .\runtimed\drivers\inferno\tracksship\michigan.xml
copy .\src\drivers\inferno\tracksdata\s2.xml .\runtimed\drivers\inferno\tracksship\s2.xml
copy .\src\drivers\inferno\tracksdata\wheel-1.xml .\runtimed\drivers\inferno\tracksship\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno
copy .\src\drivers\inferno\inferno.xml .\runtimed\drivers\inferno\inferno.xml
copy .\src\drivers\inferno\car1.xml .\runtimed\drivers\inferno\car1.xml
copy .\src\drivers\inferno\logo.rgb .\runtimed\drivers\inferno\logo.rgb
copy .\src\drivers\inferno\mclaren-f1.rgb .\runtimed\drivers\inferno\mclaren-f1.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno2
call .\create_dir .\runtimed\drivers\inferno2\tracksship
copy .\src\drivers\inferno2\tracksdata\aalborg.xml .\runtimed\drivers\inferno2\tracksship\aalborg.xml
copy .\src\drivers\inferno2\tracksdata\a-speedway.xml .\runtimed\drivers\inferno2\tracksship\a-speedway.xml
copy .\src\drivers\inferno2\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno2\tracksship\car_aalborg.xml
copy .\src\drivers\inferno2\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno2\tracksship\car_a-speedway.xml
copy .\src\drivers\inferno2\tracksdata\car_eroad.xml .\runtimed\drivers\inferno2\tracksship\car_eroad.xml
copy .\src\drivers\inferno2\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno2\tracksship\car_e-track-1.xml
copy .\src\drivers\inferno2\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno2\tracksship\car_e-track-2.xml
copy .\src\drivers\inferno2\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno2\tracksship\car_e-track-3.xml
copy .\src\drivers\inferno2\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno2\tracksship\car_e-track-4.xml
copy .\src\drivers\inferno2\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno2\tracksship\car_e-track-5.xml
copy .\src\drivers\inferno2\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno2\tracksship\car_e-track-6.xml
copy .\src\drivers\inferno2\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno2\tracksship\car_g-track-1.xml
copy .\src\drivers\inferno2\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno2\tracksship\car_g-track-2.xml
copy .\src\drivers\inferno2\tracksdata\car_michigan.xml .\runtimed\drivers\inferno2\tracksship\car_michigan.xml
copy .\src\drivers\inferno2\tracksdata\car_s2.xml .\runtimed\drivers\inferno2\tracksship\car_s2.xml
copy .\src\drivers\inferno2\tracksdata\car_test-1.xml .\runtimed\drivers\inferno2\tracksship\car_test-1.xml
copy .\src\drivers\inferno2\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno2\tracksship\car_wheel-1.xml
copy .\src\drivers\inferno2\tracksdata\eroad.xml .\runtimed\drivers\inferno2\tracksship\eroad.xml
copy .\src\drivers\inferno2\tracksdata\e-track-1.xml .\runtimed\drivers\inferno2\tracksship\e-track-1.xml
copy .\src\drivers\inferno2\tracksdata\e-track-2.xml .\runtimed\drivers\inferno2\tracksship\e-track-2.xml
copy .\src\drivers\inferno2\tracksdata\e-track-3.xml .\runtimed\drivers\inferno2\tracksship\e-track-3.xml
copy .\src\drivers\inferno2\tracksdata\e-track-4.xml .\runtimed\drivers\inferno2\tracksship\e-track-4.xml
copy .\src\drivers\inferno2\tracksdata\e-track-5.xml .\runtimed\drivers\inferno2\tracksship\e-track-5.xml
copy .\src\drivers\inferno2\tracksdata\e-track-6.xml .\runtimed\drivers\inferno2\tracksship\e-track-6.xml
copy .\src\drivers\inferno2\tracksdata\g-track-1.xml .\runtimed\drivers\inferno2\tracksship\g-track-1.xml
copy .\src\drivers\inferno2\tracksdata\g-track-2.xml .\runtimed\drivers\inferno2\tracksship\g-track-2.xml
copy .\src\drivers\inferno2\tracksdata\michigan.xml .\runtimed\drivers\inferno2\tracksship\michigan.xml
copy .\src\drivers\inferno2\tracksdata\s2.xml .\runtimed\drivers\inferno2\tracksship\s2.xml
copy .\src\drivers\inferno2\tracksdata\wheel-1.xml .\runtimed\drivers\inferno2\tracksship\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno2
copy .\src\drivers\inferno2\inferno2.xml .\runtimed\drivers\inferno2\inferno2.xml
copy .\src\drivers\inferno2\car1.xml .\runtimed\drivers\inferno2\car1.xml
copy .\src\drivers\inferno2\logo.rgb .\runtimed\drivers\inferno2\logo.rgb
copy .\src\drivers\inferno2\360-modena.rgb .\runtimed\drivers\inferno2\360-modena.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno2

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno3
call .\create_dir .\runtimed\drivers\inferno3\tracksship
copy .\src\drivers\inferno3\tracksdata\aalborg.xml .\runtimed\drivers\inferno3\tracksship\aalborg.xml
copy .\src\drivers\inferno3\tracksdata\a-speedway.xml .\runtimed\drivers\inferno3\tracksship\a-speedway.xml
copy .\src\drivers\inferno3\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno3\tracksship\car_aalborg.xml
copy .\src\drivers\inferno3\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno3\tracksship\car_a-speedway.xml
copy .\src\drivers\inferno3\tracksdata\car_eroad.xml .\runtimed\drivers\inferno3\tracksship\car_eroad.xml
copy .\src\drivers\inferno3\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno3\tracksship\car_e-track-1.xml
copy .\src\drivers\inferno3\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno3\tracksship\car_e-track-2.xml
copy .\src\drivers\inferno3\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno3\tracksship\car_e-track-3.xml
copy .\src\drivers\inferno3\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno3\tracksship\car_e-track-4.xml
copy .\src\drivers\inferno3\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno3\tracksship\car_e-track-5.xml
copy .\src\drivers\inferno3\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno3\tracksship\car_e-track-6.xml
copy .\src\drivers\inferno3\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno3\tracksship\car_g-track-1.xml
copy .\src\drivers\inferno3\tracksdata\car_g-track-2.xml .\runtimed\drivers\inferno3\tracksship\car_g-track-2.xml
copy .\src\drivers\inferno3\tracksdata\car_michigan.xml .\runtimed\drivers\inferno3\tracksship\car_michigan.xml
copy .\src\drivers\inferno3\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno3\tracksship\car_wheel-1.xml
copy .\src\drivers\inferno3\tracksdata\eroad.xml .\runtimed\drivers\inferno3\tracksship\eroad.xml
copy .\src\drivers\inferno3\tracksdata\e-track-1.xml .\runtimed\drivers\inferno3\tracksship\e-track-1.xml
copy .\src\drivers\inferno3\tracksdata\e-track-2.xml .\runtimed\drivers\inferno3\tracksship\e-track-2.xml
copy .\src\drivers\inferno3\tracksdata\e-track-3.xml .\runtimed\drivers\inferno3\tracksship\e-track-3.xml
copy .\src\drivers\inferno3\tracksdata\e-track-4.xml .\runtimed\drivers\inferno3\tracksship\e-track-4.xml
copy .\src\drivers\inferno3\tracksdata\e-track-5.xml .\runtimed\drivers\inferno3\tracksship\e-track-5.xml
copy .\src\drivers\inferno3\tracksdata\e-track-6.xml .\runtimed\drivers\inferno3\tracksship\e-track-6.xml
copy .\src\drivers\inferno3\tracksdata\g-track-1.xml .\runtimed\drivers\inferno3\tracksship\g-track-1.xml
copy .\src\drivers\inferno3\tracksdata\g-track-2.xml .\runtimed\drivers\inferno3\tracksship\g-track-2.xml
copy .\src\drivers\inferno3\tracksdata\michigan.xml .\runtimed\drivers\inferno3\tracksship\michigan.xml
copy .\src\drivers\inferno3\tracksdata\wheel-1.xml .\runtimed\drivers\inferno3\tracksship\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno3
copy .\src\drivers\inferno3\inferno3.xml .\runtimed\drivers\inferno3\inferno3.xml
copy .\src\drivers\inferno3\car1.xml .\runtimed\drivers\inferno3\car1.xml
copy .\src\drivers\inferno3\logo.rgb .\runtimed\drivers\inferno3\logo.rgb
copy .\src\drivers\inferno3\porsche-gt1.rgb .\runtimed\drivers\inferno3\porsche-gt1.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno3

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno4
call .\create_dir .\runtimed\drivers\inferno4\tracksship
copy .\src\drivers\inferno4\tracksdata\aalborg.xml .\runtimed\drivers\inferno4\tracksship\aalborg.xml
copy .\src\drivers\inferno4\tracksdata\a-speedway.xml .\runtimed\drivers\inferno4\tracksship\a-speedway.xml
copy .\src\drivers\inferno4\tracksdata\car_aalborg.xml .\runtimed\drivers\inferno4\tracksship\car_aalborg.xml
copy .\src\drivers\inferno4\tracksdata\car_a-speedway.xml .\runtimed\drivers\inferno4\tracksship\car_a-speedway.xml
copy .\src\drivers\inferno4\tracksdata\car_eroad.xml .\runtimed\drivers\inferno4\tracksship\car_eroad.xml
copy .\src\drivers\inferno4\tracksdata\car_e-track-1.xml .\runtimed\drivers\inferno4\tracksship\car_e-track-1.xml
copy .\src\drivers\inferno4\tracksdata\car_e-track-2.xml .\runtimed\drivers\inferno4\tracksship\car_e-track-2.xml
copy .\src\drivers\inferno4\tracksdata\car_e-track-3.xml .\runtimed\drivers\inferno4\tracksship\car_e-track-3.xml
copy .\src\drivers\inferno4\tracksdata\car_e-track-4.xml .\runtimed\drivers\inferno4\tracksship\car_e-track-4.xml
copy .\src\drivers\inferno4\tracksdata\car_e-track-5.xml .\runtimed\drivers\inferno4\tracksship\car_e-track-5.xml
copy .\src\drivers\inferno4\tracksdata\car_e-track-6.xml .\runtimed\drivers\inferno4\tracksship\car_e-track-6.xml
copy .\src\drivers\inferno4\tracksdata\car_g-track-1.xml .\runtimed\drivers\inferno4\tracksship\car_g-track-1.xml
copy .\src\drivers\inferno4\tracksdata\car_michigan.xml .\runtimed\drivers\inferno4\tracksship\car_michigan.xml
copy .\src\drivers\inferno4\tracksdata\car_test-1.xml .\runtimed\drivers\inferno4\tracksship\car_test-1.xml
copy .\src\drivers\inferno4\tracksdata\car_wheel-1.xml .\runtimed\drivers\inferno4\tracksship\car_wheel-1.xml
copy .\src\drivers\inferno4\tracksdata\dirt-2.xml .\runtimed\drivers\inferno4\tracksship\dirt-2.xml
copy .\src\drivers\inferno4\tracksdata\eroad.xml .\runtimed\drivers\inferno4\tracksship\eroad.xml
copy .\src\drivers\inferno4\tracksdata\e-track-1.xml .\runtimed\drivers\inferno4\tracksship\e-track-1.xml
copy .\src\drivers\inferno4\tracksdata\e-track-2.xml .\runtimed\drivers\inferno4\tracksship\e-track-2.xml
copy .\src\drivers\inferno4\tracksdata\e-track-3.xml .\runtimed\drivers\inferno4\tracksship\e-track-3.xml
copy .\src\drivers\inferno4\tracksdata\e-track-4.xml .\runtimed\drivers\inferno4\tracksship\e-track-4.xml
copy .\src\drivers\inferno4\tracksdata\e-track-5.xml .\runtimed\drivers\inferno4\tracksship\e-track-5.xml
copy .\src\drivers\inferno4\tracksdata\e-track-6.xml .\runtimed\drivers\inferno4\tracksship\e-track-6.xml
copy .\src\drivers\inferno4\tracksdata\g-track-1.xml .\runtimed\drivers\inferno4\tracksship\g-track-1.xml
copy .\src\drivers\inferno4\tracksdata\michigan.xml .\runtimed\drivers\inferno4\tracksship\michigan.xml
copy .\src\drivers\inferno4\tracksdata\wheel-1.xml .\runtimed\drivers\inferno4\tracksship\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno4
copy .\src\drivers\inferno4\inferno4.xml .\runtimed\drivers\inferno4\inferno4.xml
copy .\src\drivers\inferno4\car1.xml .\runtimed\drivers\inferno4\car1.xml
copy .\src\drivers\inferno4\logo.rgb .\runtimed\drivers\inferno4\logo.rgb
copy .\src\drivers\inferno4\xj-220.rgb .\runtimed\drivers\inferno4\xj-220.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\inferno4

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\K1999
call .\create_dir .\runtimed\drivers\K1999\1
copy .\src\drivers\K1999\1\buggy.rgb .\runtimed\drivers\K1999\1\buggy.rgb
copy .\src\drivers\K1999\1\settings.xml .\runtimed\drivers\K1999\1\settings.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\K1999
call .\create_dir .\runtimed\drivers\K1999\2
copy .\src\drivers\K1999\2\cg-nascar-rwd.rgb .\runtimed\drivers\K1999\2\cg-nascar-rwd.rgb
copy .\src\drivers\K1999\2\settings.xml .\runtimed\drivers\K1999\2\settings.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\K1999
copy .\src\drivers\K1999\K1999.xml .\runtimed\drivers\K1999\K1999.xml
copy .\src\drivers\K1999\logo.rgb .\runtimed\drivers\K1999\logo.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\K1999

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\lliaw
call .\create_dir .\runtimed\drivers\lliaw\tracksship
copy .\src\drivers\lliaw\tracksdata\car_e-track-3.xml .\runtimed\drivers\lliaw\tracksship\car_e-track-3.xml
copy .\src\drivers\lliaw\tracksdata\car_e-track-4.xml .\runtimed\drivers\lliaw\tracksship\car_e-track-4.xml
copy .\src\drivers\lliaw\tracksdata\car_e-track-6.xml .\runtimed\drivers\lliaw\tracksship\car_e-track-6.xml
copy .\src\drivers\lliaw\tracksdata\car_eroad.xml .\runtimed\drivers\lliaw\tracksship\car_eroad.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\lliaw
copy .\src\drivers\lliaw\lliaw.xml .\runtimed\drivers\lliaw\lliaw.xml
copy .\src\drivers\lliaw\car.xml .\runtimed\drivers\lliaw\car.xml
copy .\src\drivers\lliaw\viper-gts-r.rgb .\runtimed\drivers\lliaw\viper-gts-r.rgb
copy .\src\drivers\lliaw\logo.rgb .\runtimed\drivers\lliaw\logo.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\lliaw

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tanhoj
call .\create_dir .\runtimed\drivers\tanhoj\tracksship
copy .\src\drivers\tanhoj\tracksdata\aalborg.xml .\runtimed\drivers\tanhoj\tracksship\aalborg.xml
copy .\src\drivers\tanhoj\tracksdata\a-speedway.xml .\runtimed\drivers\tanhoj\tracksship\a-speedway.xml
copy .\src\drivers\tanhoj\tracksdata\car_aalborg.xml .\runtimed\drivers\tanhoj\tracksship\car_aalborg.xml
copy .\src\drivers\tanhoj\tracksdata\car_a-speedway.xml .\runtimed\drivers\tanhoj\tracksship\car_a-speedway.xml
copy .\src\drivers\tanhoj\tracksdata\car_eroad.xml .\runtimed\drivers\tanhoj\tracksship\car_eroad.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-1.xml .\runtimed\drivers\tanhoj\tracksship\car_e-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-2.xml .\runtimed\drivers\tanhoj\tracksship\car_e-track-2.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-3.xml .\runtimed\drivers\tanhoj\tracksship\car_e-track-3.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-4.xml .\runtimed\drivers\tanhoj\tracksship\car_e-track-4.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-5.xml .\runtimed\drivers\tanhoj\tracksship\car_e-track-5.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-6.xml .\runtimed\drivers\tanhoj\tracksship\car_e-track-6.xml
copy .\src\drivers\tanhoj\tracksdata\car_g-track-1.xml .\runtimed\drivers\tanhoj\tracksship\car_g-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_michigan.xml .\runtimed\drivers\tanhoj\tracksship\car_michigan.xml
copy .\src\drivers\tanhoj\tracksdata\car_s2.xml .\runtimed\drivers\tanhoj\tracksship\car_s2.xml
copy .\src\drivers\tanhoj\tracksdata\car_test-1.xml .\runtimed\drivers\tanhoj\tracksship\car_test-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_wheel-1.xml .\runtimed\drivers\tanhoj\tracksship\car_wheel-1.xml
copy .\src\drivers\tanhoj\tracksdata\city-1.xml .\runtimed\drivers\tanhoj\tracksship\city-1.xml
copy .\src\drivers\tanhoj\tracksdata\dirt-2.xml .\runtimed\drivers\tanhoj\tracksship\dirt-2.xml
copy .\src\drivers\tanhoj\tracksdata\eroad.xml .\runtimed\drivers\tanhoj\tracksship\eroad.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-1.xml .\runtimed\drivers\tanhoj\tracksship\e-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-2.xml .\runtimed\drivers\tanhoj\tracksship\e-track-2.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-3.xml .\runtimed\drivers\tanhoj\tracksship\e-track-3.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-4.xml .\runtimed\drivers\tanhoj\tracksship\e-track-4.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-5.xml .\runtimed\drivers\tanhoj\tracksship\e-track-5.xml
copy .\src\drivers\tanhoj\tracksdata\e-track-6.xml .\runtimed\drivers\tanhoj\tracksship\e-track-6.xml
copy .\src\drivers\tanhoj\tracksdata\g-track-1.xml .\runtimed\drivers\tanhoj\tracksship\g-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\michigan.xml .\runtimed\drivers\tanhoj\tracksship\michigan.xml
copy .\src\drivers\tanhoj\tracksdata\s2.xml .\runtimed\drivers\tanhoj\tracksship\s2.xml
copy .\src\drivers\tanhoj\tracksdata\wheel-1.xml .\runtimed\drivers\tanhoj\tracksship\wheel-1.xml

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

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tita
call .\create_dir .\runtimed\drivers\tita\tracksship
copy .\src\drivers\tita\tracksdata\aalborg.xml .\runtimed\drivers\tita\tracksship\aalborg.xml
copy .\src\drivers\tita\tracksdata\a-speedway.xml .\runtimed\drivers\tita\tracksship\a-speedway.xml
copy .\src\drivers\tita\tracksdata\car_aalborg.xml .\runtimed\drivers\tita\tracksship\car_aalborg.xml
copy .\src\drivers\tita\tracksdata\car_a-speedway.xml .\runtimed\drivers\tita\tracksship\car_a-speedway.xml
copy .\src\drivers\tita\tracksdata\car_eroad.xml .\runtimed\drivers\tita\tracksship\car_eroad.xml
copy .\src\drivers\tita\tracksdata\car_e-track-1.xml .\runtimed\drivers\tita\tracksship\car_e-track-1.xml
copy .\src\drivers\tita\tracksdata\car_e-track-2.xml .\runtimed\drivers\tita\tracksship\car_e-track-2.xml
copy .\src\drivers\tita\tracksdata\car_e-track-3.xml .\runtimed\drivers\tita\tracksship\car_e-track-3.xml
copy .\src\drivers\tita\tracksdata\car_e-track-4.xml .\runtimed\drivers\tita\tracksship\car_e-track-4.xml
copy .\src\drivers\tita\tracksdata\car_e-track-5.xml .\runtimed\drivers\tita\tracksship\car_e-track-5.xml
copy .\src\drivers\tita\tracksdata\car_e-track-6.xml .\runtimed\drivers\tita\tracksship\car_e-track-6.xml
copy .\src\drivers\tita\tracksdata\car_g-track-1.xml .\runtimed\drivers\tita\tracksship\car_g-track-1.xml
copy .\src\drivers\tita\tracksdata\car_michigan.xml .\runtimed\drivers\tita\tracksship\car_michigan.xml
copy .\src\drivers\tita\tracksdata\car_s2.xml .\runtimed\drivers\tita\tracksship\car_s2.xml
copy .\src\drivers\tita\tracksdata\car_test-1.xml .\runtimed\drivers\tita\tracksship\car_test-1.xml
copy .\src\drivers\tita\tracksdata\car_wheel-1.xml .\runtimed\drivers\tita\tracksship\car_wheel-1.xml
copy .\src\drivers\tita\tracksdata\city-1.xml .\runtimed\drivers\tita\tracksship\city-1.xml
copy .\src\drivers\tita\tracksdata\eroad.xml .\runtimed\drivers\tita\tracksship\eroad.xml
copy .\src\drivers\tita\tracksdata\e-track-1.xml .\runtimed\drivers\tita\tracksship\e-track-1.xml
copy .\src\drivers\tita\tracksdata\e-track-2.xml .\runtimed\drivers\tita\tracksship\e-track-2.xml
copy .\src\drivers\tita\tracksdata\e-track-3.xml .\runtimed\drivers\tita\tracksship\e-track-3.xml
copy .\src\drivers\tita\tracksdata\e-track-4.xml .\runtimed\drivers\tita\tracksship\e-track-4.xml
copy .\src\drivers\tita\tracksdata\e-track-5.xml .\runtimed\drivers\tita\tracksship\e-track-5.xml
copy .\src\drivers\tita\tracksdata\e-track-6.xml .\runtimed\drivers\tita\tracksship\e-track-6.xml
copy .\src\drivers\tita\tracksdata\g-track-1.xml .\runtimed\drivers\tita\tracksship\g-track-1.xml
copy .\src\drivers\tita\tracksdata\michigan.xml .\runtimed\drivers\tita\tracksship\michigan.xml
copy .\src\drivers\tita\tracksdata\s2.xml .\runtimed\drivers\tita\tracksship\s2.xml
copy .\src\drivers\tita\tracksdata\wheel-1.xml .\runtimed\drivers\tita\tracksship\wheel-1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tita
copy .\src\drivers\tita\tita.xml .\runtimed\drivers\tita\tita.xml
copy .\src\drivers\tita\car.xml .\runtimed\drivers\tita\car.xml
copy .\src\drivers\tita\logo.rgb .\runtimed\drivers\tita\logo.rgb
copy .\src\drivers\tita\lotus-gt1.rgb .\runtimed\drivers\tita\lotus-gt1.rgb

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tita

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tutorial1
copy .\src\drivers\tutorial1\tutorial1.xml .\runtimed\drivers\tutorial1\tutorial1.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tutorial1

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tutorial2
copy .\src\drivers\tutorial2\tutorial2.xml .\runtimed\drivers\tutorial2\tutorial2.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\drivers
call .\create_dir .\runtimed\drivers\tutorial2

call .\create_dir .\runtimed
call .\create_dir .\runtimed\.

call .\create_dir .\runtimed
call .\create_dir .\runtimed\.

call .\create_dir .\runtimed
call .\create_dir .\runtimed\config
copy .\src\libs\tgf\screen.xml .\runtimed\config\screen.xml
copy .\src\libs\tgf\params.dtd .\runtimed\config\params.dtd

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
call .\create_dir .\runtimed\config
call .\create_dir .\runtimed\config\practice
copy .\src\modules\raceman\practice\practice\practice.xml .\runtimed\config\practice\practice.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\raceman

call .\create_dir .\runtimed
call .\create_dir .\runtimed\config
call .\create_dir .\runtimed\config\quickrace
copy .\src\modules\raceman\quickrace\qrace.xml .\runtimed\config\quickrace\qrace.xml

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\raceman

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\simu

call .\create_dir .\runtimed
call .\create_dir .\runtimed\telemetry
copy .\src\modules\telemetry\telemetry.sh .\runtimed\telemetry\telemetry.sh

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\telemetry

call .\create_dir .\runtimed
call .\create_dir .\runtimed\modules
call .\create_dir .\runtimed\modules\track
