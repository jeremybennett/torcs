@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

call .\create_dir ./export
call .\create_dir ./export/include
copy /home/torcs/sb3/torcs/torcs/src/interfaces/graphic.h /home/torcs/sb3/torcs/torcs/export/include/graphic.h
copy /home/torcs/sb3/torcs/torcs/src/interfaces/raceman.h /home/torcs/sb3/torcs/torcs/export/include/raceman.h
copy /home/torcs/sb3/torcs/torcs/src/interfaces/robot.h /home/torcs/sb3/torcs/torcs/export/include/robot.h
copy /home/torcs/sb3/torcs/torcs/src/interfaces/simu.h /home/torcs/sb3/torcs/torcs/export/include/simu.h
copy /home/torcs/sb3/torcs/torcs/src/interfaces/track.h /home/torcs/sb3/torcs/torcs/export/include/track.h
copy /home/torcs/sb3/torcs/torcs/src/interfaces/car.h /home/torcs/sb3/torcs/torcs/export/include/car.h
copy /home/torcs/sb3/torcs/torcs/src/interfaces/ttypes.h /home/torcs/sb3/torcs/torcs/export/include/ttypes.h
copy /home/torcs/sb3/torcs/torcs/src/interfaces/telemetry.h /home/torcs/sb3/torcs/torcs/export/include/telemetry.h
copy /home/torcs/sb3/torcs/torcs/src/interfaces/practicectrl.h /home/torcs/sb3/torcs/torcs/export/include/practicectrl.h
copy /home/torcs/sb3/torcs/torcs/src/interfaces/playerpref.h /home/torcs/sb3/torcs/torcs/export/include/playerpref.h
copy /home/torcs/sb3/torcs/torcs/src/interfaces/js.h /home/torcs/sb3/torcs/torcs/export/include/js.h

call .\create_dir ./export
call .\create_dir ./export/include
copy /home/torcs/sb3/torcs/torcs/src/libs/txml/xml.h /home/torcs/sb3/torcs/torcs/export/include/xml.h
copy /home/torcs/sb3/torcs/torcs/src/libs/txml/xmlparse.h /home/torcs/sb3/torcs/torcs/export/include/xmlparse.h

call .\create_dir ./export
call .\create_dir ./export/include
copy /home/torcs/sb3/torcs/torcs/src/libs/tgf/tgf.h /home/torcs/sb3/torcs/torcs/export/include/tgf.h
copy /home/torcs/sb3/torcs/torcs/src/libs/tgf/os.h /home/torcs/sb3/torcs/torcs/export/include/os.h
copy /home/torcs/sb3/torcs/torcs/src/libs/tgf/queue.h /home/torcs/sb3/torcs/torcs/export/include/queue.h

call .\create_dir ./export
call .\create_dir ./export/include
copy /home/torcs/sb3/torcs/torcs/src/libs/torcs/torcs.h /home/torcs/sb3/torcs/torcs/export/include/torcs.h

call .\create_dir ./export
call .\create_dir ./export/include
copy /home/torcs/sb3/torcs/torcs/src/libs/racemantools/racemantools.h /home/torcs/sb3/torcs/torcs/export/include/racemantools.h

call .\create_dir ./export
call .\create_dir ./export/include
copy /home/torcs/sb3/torcs/torcs/src/libs/robottools/robottools.h /home/torcs/sb3/torcs/torcs/export/include/robottools.h

call .\create_dir ./export
call .\create_dir ./export/include
copy /home/torcs/sb3/torcs/torcs/src/linux/osspec.h /home/torcs/sb3/torcs/torcs/export/include/osspec.h

call .\create_dir ./export
call .\create_dir ./export/include
call .\create_dir ./export/include/3D
copy /home/torcs/sb3/torcs/torcs/src/modules/simu/simuv2/SOLID-2.0/include/3D/Basic.h /home/torcs/sb3/torcs/torcs/export/include/3D/Basic.h
copy /home/torcs/sb3/torcs/torcs/src/modules/simu/simuv2/SOLID-2.0/include/3D/Matrix.h /home/torcs/sb3/torcs/torcs/export/include/3D/Matrix.h
copy /home/torcs/sb3/torcs/torcs/src/modules/simu/simuv2/SOLID-2.0/include/3D/Point.h /home/torcs/sb3/torcs/torcs/export/include/3D/Point.h
copy /home/torcs/sb3/torcs/torcs/src/modules/simu/simuv2/SOLID-2.0/include/3D/Quaternion.h /home/torcs/sb3/torcs/torcs/export/include/3D/Quaternion.h
copy /home/torcs/sb3/torcs/torcs/src/modules/simu/simuv2/SOLID-2.0/include/3D/Tuple3.h /home/torcs/sb3/torcs/torcs/export/include/3D/Tuple3.h
copy /home/torcs/sb3/torcs/torcs/src/modules/simu/simuv2/SOLID-2.0/include/3D/Tuple4.h /home/torcs/sb3/torcs/torcs/export/include/3D/Tuple4.h
copy /home/torcs/sb3/torcs/torcs/src/modules/simu/simuv2/SOLID-2.0/include/3D/Vector.h /home/torcs/sb3/torcs/torcs/export/include/3D/Vector.h

call .\create_dir ./export
call .\create_dir ./export/include
call .\create_dir ./export/include/SOLID
copy /home/torcs/sb3/torcs/torcs/src/modules/simu/simuv2/SOLID-2.0/include/SOLID/solid.h /home/torcs/sb3/torcs/torcs/export/include/SOLID/solid.h
