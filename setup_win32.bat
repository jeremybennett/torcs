@echo off
echo Checking directories ...


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

call .\create_dir .\export
call .\create_dir .\export\include
copy .\src\libs\txml\xml.h .\export\include\xml.h
copy .\src\libs\txml\xmlparse.h .\export\include\xmlparse.h

call .\create_dir .\export
call .\create_dir .\export\include
copy .\src\libs\tgf\tgf.h .\export\include\tgf.h
copy .\src\libs\tgf\os.h .\export\include\os.h

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

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\free\free.xml .\runtime\categories\free.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\offroad-r-a\offroad-r-a.xml .\runtime\categories\offroad-r-a.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\torcs-f-a\torcs-f-a.xml .\runtime\categories\torcs-f-a.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\torcs-f-b\torcs-f-b.xml .\runtime\categories\torcs-f-b.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\torcs-r-a\torcs-r-a.xml .\runtime\categories\torcs-r-a.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\torcs-r-b\torcs-r-b.xml .\runtime\categories\torcs-r-b.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\torcs-r-c\torcs-r-c.xml .\runtime\categories\torcs-r-c.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\acura-nsx-sz
copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz.xml .\runtime\cars\acura-nsx-sz\acura-nsx-sz.xml
copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz.ac .\runtime\cars\acura-nsx-sz\acura-nsx-sz.ac
copy .\data\cars\models\acura-nsx-sz\tex-wheel.rgb .\runtime\cars\acura-nsx-sz\tex-wheel.rgb
copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz.rgb .\runtime\cars\acura-nsx-sz\acura-nsx-sz.rgb
copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz-base.ac .\runtime\cars\acura-nsx-sz\acura-nsx-sz-base.ac
copy .\data\cars\models\acura-nsx-sz\texmapper.xml .\runtime\cars\acura-nsx-sz\texmapper.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\buggy
copy .\data\cars\models\buggy\buggy.xml .\runtime\cars\buggy\buggy.xml
copy .\data\cars\models\buggy\buggy.ac .\runtime\cars\buggy\buggy.ac
copy .\data\cars\models\buggy\buggy.rgb .\runtime\cars\buggy\buggy.rgb
copy .\data\cars\models\buggy\tex-wheel.rgb .\runtime\cars\buggy\tex-wheel.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\cg-nascar-fwd
copy .\data\cars\models\cg-nascar-fwd\cg-nascar-fwd.xml .\runtime\cars\cg-nascar-fwd\cg-nascar-fwd.xml
copy .\data\cars\models\cg-nascar-fwd\cg-nascar-fwd.ac .\runtime\cars\cg-nascar-fwd\cg-nascar-fwd.ac
copy .\data\cars\models\cg-nascar-fwd\cg-nascar-fwd.rgb .\runtime\cars\cg-nascar-fwd\cg-nascar-fwd.rgb
copy .\data\cars\models\cg-nascar-fwd\tex-wheel.rgb .\runtime\cars\cg-nascar-fwd\tex-wheel.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\cg-nascar-rwd
copy .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.xml .\runtime\cars\cg-nascar-rwd\cg-nascar-rwd.xml
copy .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.ac .\runtime\cars\cg-nascar-rwd\cg-nascar-rwd.ac
copy .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.rgb .\runtime\cars\cg-nascar-rwd\cg-nascar-rwd.rgb
copy .\data\cars\models\cg-nascar-rwd\tex-wheel.rgb .\runtime\cars\cg-nascar-rwd\tex-wheel.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\lotus-gt1
copy .\data\cars\models\lotus-gt1\lotus-gt1.xml .\runtime\cars\lotus-gt1\lotus-gt1.xml
copy .\data\cars\models\lotus-gt1\lotus-gt1.ac .\runtime\cars\lotus-gt1\lotus-gt1.ac
copy .\data\cars\models\lotus-gt1\lotus-gt1-base.ac .\runtime\cars\lotus-gt1\lotus-gt1-base.ac
copy .\data\cars\models\lotus-gt1\texmapper.xml .\runtime\cars\lotus-gt1\texmapper.xml
copy .\data\cars\models\lotus-gt1\tex-wheel.rgb .\runtime\cars\lotus-gt1\tex-wheel.rgb
copy .\data\cars\models\lotus-gt1\lotus-gt1.rgb .\runtime\cars\lotus-gt1\lotus-gt1.rgb
copy .\data\cars\models\lotus-gt1\lotus-gt1-512.rgb .\runtime\cars\lotus-gt1\lotus-gt1-512.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\mclaren-f1
copy .\data\cars\models\mclaren-f1\mclaren-f1.xml .\runtime\cars\mclaren-f1\mclaren-f1.xml
copy .\data\cars\models\mclaren-f1\mclaren-f1.ac .\runtime\cars\mclaren-f1\mclaren-f1.ac
copy .\data\cars\models\mclaren-f1\mclaren-f1-base.ac .\runtime\cars\mclaren-f1\mclaren-f1-base.ac
copy .\data\cars\models\mclaren-f1\texmapper.xml .\runtime\cars\mclaren-f1\texmapper.xml
copy .\data\cars\models\mclaren-f1\tex-wheel.rgb .\runtime\cars\mclaren-f1\tex-wheel.rgb
copy .\data\cars\models\mclaren-f1\mclaren-f1.rgb .\runtime\cars\mclaren-f1\mclaren-f1.rgb
copy .\data\cars\models\mclaren-f1\mclaren-f1-512.rgb .\runtime\cars\mclaren-f1\mclaren-f1-512.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\p406
copy .\data\cars\models\p406\p406.xml .\runtime\cars\p406\p406.xml
copy .\data\cars\models\p406\texmapper.xml .\runtime\cars\p406\texmapper.xml
copy .\data\cars\models\p406\p406.ac .\runtime\cars\p406\p406.ac
copy .\data\cars\models\p406\p406-base.ac .\runtime\cars\p406\p406-base.ac
copy .\data\cars\models\p406\p406-512.rgb .\runtime\cars\p406\p406-512.rgb
copy .\data\cars\models\p406\p406.rgb .\runtime\cars\p406\p406.rgb
copy .\data\cars\models\p406\tex-wheel.rgb .\runtime\cars\p406\tex-wheel.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\torcs
copy .\data\cars\models\torcs\torcs.xml .\runtime\cars\torcs\torcs.xml
copy .\data\cars\models\torcs\torcs.ac .\runtime\cars\torcs\torcs.ac
copy .\data\cars\models\torcs\torcs.rgb .\runtime\cars\torcs\torcs.rgb
copy .\data\cars\models\torcs\tex-wheel.rgb .\runtime\cars\torcs\tex-wheel.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\viper-gts-r
copy .\data\cars\models\viper-gts-r\viper-gts-r.xml .\runtime\cars\viper-gts-r\viper-gts-r.xml
copy .\data\cars\models\viper-gts-r\tex-wheel.rgb .\runtime\cars\viper-gts-r\tex-wheel.rgb
copy .\data\cars\models\viper-gts-r\viper-gts-r.rgb .\runtime\cars\viper-gts-r\viper-gts-r.rgb
copy .\data\cars\models\viper-gts-r\viper-gts-r.ac .\runtime\cars\viper-gts-r\viper-gts-r.ac
copy .\data\cars\models\viper-gts-r\viper-gts-r-512.rgb .\runtime\cars\viper-gts-r\viper-gts-r-512.rgb
copy .\data\cars\models\viper-gts-r\viper-gts-r-base.ac .\runtime\cars\viper-gts-r\viper-gts-r-base.ac
copy .\data\cars\models\viper-gts-r\texmapper.xml .\runtime\cars\viper-gts-r\texmapper.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\fonts
copy .\data\data\fonts\b5.glf .\runtime\data\fonts\b5.glf
copy .\data\data\fonts\b6.glf .\runtime\data\fonts\b6.glf
copy .\data\data\fonts\b7.glf .\runtime\data\fonts\b7.glf
copy .\data\data\fonts\digital.glf .\runtime\data\fonts\digital.glf
copy .\data\data\fonts\fragile.glf .\runtime\data\fonts\fragile.glf
copy .\data\data\fonts\Makefile .\runtime\data\fonts\Makefile

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\img
copy .\data\data\img\arrow-down.png .\runtime\data\img\arrow-down.png
copy .\data\data\img\arrow-down-pushed.png .\runtime\data\img\arrow-down-pushed.png
copy .\data\data\img\arrow-left.png .\runtime\data\img\arrow-left.png
copy .\data\data\img\arrow-left-pushed.png .\runtime\data\img\arrow-left-pushed.png
copy .\data\data\img\arrow-right.png .\runtime\data\img\arrow-right.png
copy .\data\data\img\arrow-right-pushed.png .\runtime\data\img\arrow-right-pushed.png
copy .\data\data\img\arrow-up.png .\runtime\data\img\arrow-up.png
copy .\data\data\img\arrow-up-pushed.png .\runtime\data\img\arrow-up-pushed.png
copy .\data\data\img\env.png .\runtime\data\img\env.png
copy .\data\data\img\ruler.png .\runtime\data\img\ruler.png
copy .\data\data\img\ruler-pushed.png .\runtime\data\img\ruler-pushed.png
copy .\data\data\img\splash-free1.png .\runtime\data\img\splash-free1.png
copy .\data\data\img\splash-free2.png .\runtime\data\img\splash-free2.png
copy .\data\data\img\splash-free3.png .\runtime\data\img\splash-free3.png
copy .\data\data\img\splash-free4.png .\runtime\data\img\splash-free4.png
copy .\data\data\img\splash-free5.png .\runtime\data\img\splash-free5.png
copy .\data\data\img\splash-free7.png .\runtime\data\img\splash-free7.png
copy .\data\data\img\splash-free.png .\runtime\data\img\splash-free.png
copy .\data\data\img\splash-graphic.png .\runtime\data\img\splash-graphic.png
copy .\data\data\img\splash-joycal.png .\runtime\data\img\splash-joycal.png
copy .\data\data\img\splash-joyconf.png .\runtime\data\img\splash-joyconf.png
copy .\data\data\img\splash-main.png .\runtime\data\img\splash-main.png
copy .\data\data\img\splash-options.png .\runtime\data\img\splash-options.png
copy .\data\data\img\splash.png .\runtime\data\img\splash.png
copy .\data\data\img\splash-practice.png .\runtime\data\img\splash-practice.png
copy .\data\data\img\splash-prsess.png .\runtime\data\img\splash-prsess.png
copy .\data\data\img\splash-qrdrv.png .\runtime\data\img\splash-qrdrv.png
copy .\data\data\img\splash-qrloading.png .\runtime\data\img\splash-qrloading.png
copy .\data\data\img\splash-qr.png .\runtime\data\img\splash-qr.png
copy .\data\data\img\splash-qrtrk.png .\runtime\data\img\splash-qrtrk.png
copy .\data\data\img\splash-quit.png .\runtime\data\img\splash-quit.png
copy .\data\data\img\splash-result.png .\runtime\data\img\splash-result.png

call .\create_dir .\runtime
call .\create_dir .\runtime\menu
copy .\data\data\menu\entry.xml .\runtime\menu\entry.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\objects
copy .\data\data\objects\stand-inter.ac .\runtime\data\objects\stand-inter.ac
copy .\data\data\objects\stand-main.ac .\runtime\data\objects\stand-main.ac
copy .\data\data\objects\stand-wall.ac .\runtime\data\objects\stand-wall.ac
copy .\data\data\objects\tree1.ac .\runtime\data\objects\tree1.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\sound
copy .\data\data\sound\crash1.wav .\runtime\data\sound\crash1.wav
copy .\data\data\sound\crash2.wav .\runtime\data\sound\crash2.wav
copy .\data\data\sound\crash3.wav .\runtime\data\sound\crash3.wav
copy .\data\data\sound\crash4.wav .\runtime\data\sound\crash4.wav
copy .\data\data\sound\crash5.wav .\runtime\data\sound\crash5.wav
copy .\data\data\sound\crash6.wav .\runtime\data\sound\crash6.wav
copy .\data\data\sound\engine-1.wav .\runtime\data\sound\engine-1.wav
copy .\data\data\sound\skid.wav .\runtime\data\sound\skid.wav

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\textures
copy .\data\data\textures\background.png .\runtime\data\textures\background.png
copy .\data\data\textures\logo.png .\runtime\data\textures\logo.png
copy .\data\data\textures\pylon1.png .\runtime\data\textures\pylon1.png
copy .\data\data\textures\pylon2.png .\runtime\data\textures\pylon2.png
copy .\data\data\textures\pylon3.png .\runtime\data\textures\pylon3.png
copy .\data\data\textures\tr-asphalt-both.png .\runtime\data\textures\tr-asphalt-both.png
copy .\data\data\textures\tr-asphalt-left.png .\runtime\data\textures\tr-asphalt-left.png
copy .\data\data\textures\tr-asphalt-l.png .\runtime\data\textures\tr-asphalt-l.png
copy .\data\data\textures\tr-asphalt.png .\runtime\data\textures\tr-asphalt.png
copy .\data\data\textures\tr-asphalt-p.png .\runtime\data\textures\tr-asphalt-p.png
copy .\data\data\textures\tr-asphalt-right.png .\runtime\data\textures\tr-asphalt-right.png
copy .\data\data\textures\tr-barrier.png .\runtime\data\textures\tr-barrier.png
copy .\data\data\textures\tr-concrete.png .\runtime\data\textures\tr-concrete.png
copy .\data\data\textures\tr-dirtb.png .\runtime\data\textures\tr-dirtb.png
copy .\data\data\textures\tr-dirt.png .\runtime\data\textures\tr-dirt.png
copy .\data\data\textures\tr-grass.png .\runtime\data\textures\tr-grass.png
copy .\data\data\textures\tr-sand.png .\runtime\data\textures\tr-sand.png
copy .\data\data\textures\concrete2.rgb .\runtime\data\textures\concrete2.rgb
copy .\data\data\textures\concrete.rgb .\runtime\data\textures\concrete.rgb
copy .\data\data\textures\env.rgb .\runtime\data\textures\env.rgb
copy .\data\data\textures\logo.rgb .\runtime\data\textures\logo.rgb
copy .\data\data\textures\pit-left.rgb .\runtime\data\textures\pit-left.rgb
copy .\data\data\textures\pit-right.rgb .\runtime\data\textures\pit-right.rgb
copy .\data\data\textures\pylon1.rgb .\runtime\data\textures\pylon1.rgb
copy .\data\data\textures\pylon2.rgb .\runtime\data\textures\pylon2.rgb
copy .\data\data\textures\pylon3.rgb .\runtime\data\textures\pylon3.rgb
copy .\data\data\textures\rim1.rgb .\runtime\data\textures\rim1.rgb
copy .\data\data\textures\rim2.rgb .\runtime\data\textures\rim2.rgb
copy .\data\data\textures\tr-asphalt-both_nmm.rgb .\runtime\data\textures\tr-asphalt-both_nmm.rgb
copy .\data\data\textures\tr-asphalt-both.rgb .\runtime\data\textures\tr-asphalt-both.rgb
copy .\data\data\textures\tr-asphalt-left_nmm.rgb .\runtime\data\textures\tr-asphalt-left_nmm.rgb
copy .\data\data\textures\tr-asphalt-left.rgb .\runtime\data\textures\tr-asphalt-left.rgb
copy .\data\data\textures\tr-asphalt-l_nmm.rgb .\runtime\data\textures\tr-asphalt-l_nmm.rgb
copy .\data\data\textures\tr-asphalt-l.rgb .\runtime\data\textures\tr-asphalt-l.rgb
copy .\data\data\textures\tr-asphalt_nmm.rgb .\runtime\data\textures\tr-asphalt_nmm.rgb
copy .\data\data\textures\tr-asphalt-p_nmm.rgb .\runtime\data\textures\tr-asphalt-p_nmm.rgb
copy .\data\data\textures\tr-asphalt-p.rgb .\runtime\data\textures\tr-asphalt-p.rgb
copy .\data\data\textures\tr-asphalt.rgb .\runtime\data\textures\tr-asphalt.rgb
copy .\data\data\textures\tr-asphalt-right_nmm.rgb .\runtime\data\textures\tr-asphalt-right_nmm.rgb
copy .\data\data\textures\tr-asphalt-right.rgb .\runtime\data\textures\tr-asphalt-right.rgb
copy .\data\data\textures\tr-barrier.rgb .\runtime\data\textures\tr-barrier.rgb
copy .\data\data\textures\tr-concrete_nmm.rgb .\runtime\data\textures\tr-concrete_nmm.rgb
copy .\data\data\textures\tr-concrete.rgb .\runtime\data\textures\tr-concrete.rgb
copy .\data\data\textures\tr-dirtb.rgb .\runtime\data\textures\tr-dirtb.rgb
copy .\data\data\textures\tr-dirt.rgb .\runtime\data\textures\tr-dirt.rgb
copy .\data\data\textures\tree1.rgb .\runtime\data\textures\tree1.rgb
copy .\data\data\textures\tr-grass2.rgb .\runtime\data\textures\tr-grass2.rgb
copy .\data\data\textures\tr-grass.rgb .\runtime\data\textures\tr-grass.rgb
copy .\data\data\textures\tr-sand2.rgb .\runtime\data\textures\tr-sand2.rgb
copy .\data\data\textures\tr-sand.rgb .\runtime\data\textures\tr-sand.rgb
copy .\data\data\textures\tr-water.rgb .\runtime\data\textures\tr-water.rgb
copy .\data\data\textures\turn100L.rgb .\runtime\data\textures\turn100L.rgb
copy .\data\data\textures\turn100R.rgb .\runtime\data\textures\turn100R.rgb
copy .\data\data\textures\turn150L.rgb .\runtime\data\textures\turn150L.rgb
copy .\data\data\textures\turn150R.rgb .\runtime\data\textures\turn150R.rgb
copy .\data\data\textures\turn200L.rgb .\runtime\data\textures\turn200L.rgb
copy .\data\data\textures\turn200R.rgb .\runtime\data\textures\turn200R.rgb
copy .\data\data\textures\turn300L.rgb .\runtime\data\textures\turn300L.rgb
copy .\data\data\textures\turn300R.rgb .\runtime\data\textures\turn300R.rgb
copy .\data\data\textures\turn50L.rgb .\runtime\data\textures\turn50L.rgb
copy .\data\data\textures\turn50R.rgb .\runtime\data\textures\turn50R.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\tracks
copy .\data\data\tracks\surfaces.xml .\runtime\data\tracks\surfaces.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\aalborg
copy .\data\tracks\aalborg\aalborg.xml .\runtime\tracks\aalborg\aalborg.xml
copy .\data\tracks\aalborg\aalborg.ac .\runtime\tracks\aalborg\aalborg.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\a-speedway
copy .\data\tracks\a-speedway\a-speedway.xml .\runtime\tracks\a-speedway\a-speedway.xml
copy .\data\tracks\a-speedway\background.png .\runtime\tracks\a-speedway\background.png
copy .\data\tracks\a-speedway\a-speedway.ac .\runtime\tracks\a-speedway\a-speedway.ac
copy .\data\tracks\a-speedway\a-speedway-relief.ac .\runtime\tracks\a-speedway\a-speedway-relief.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-1
copy .\data\tracks\dirt-1\dirt-1.xml .\runtime\tracks\dirt-1\dirt-1.xml
copy .\data\tracks\dirt-1\background.png .\runtime\tracks\dirt-1\background.png
copy .\data\tracks\dirt-1\dirt-1.ac .\runtime\tracks\dirt-1\dirt-1.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-2
copy .\data\tracks\dirt-2\dirt-2.xml .\runtime\tracks\dirt-2\dirt-2.xml
copy .\data\tracks\dirt-2\background.png .\runtime\tracks\dirt-2\background.png
copy .\data\tracks\dirt-2\dirt-2.ac .\runtime\tracks\dirt-2\dirt-2.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-3
copy .\data\tracks\dirt-3\dirt-3.xml .\runtime\tracks\dirt-3\dirt-3.xml
copy .\data\tracks\dirt-3\background.png .\runtime\tracks\dirt-3\background.png
copy .\data\tracks\dirt-3\background2.png .\runtime\tracks\dirt-3\background2.png
copy .\data\tracks\dirt-3\dirt-3.ac .\runtime\tracks\dirt-3\dirt-3.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-4
copy .\data\tracks\dirt-4\dirt-4.xml .\runtime\tracks\dirt-4\dirt-4.xml
copy .\data\tracks\dirt-4\background.png .\runtime\tracks\dirt-4\background.png
copy .\data\tracks\dirt-4\dirt-4.ac .\runtime\tracks\dirt-4\dirt-4.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-5
copy .\data\tracks\dirt-5\dirt-5.xml .\runtime\tracks\dirt-5\dirt-5.xml
copy .\data\tracks\dirt-5\background.png .\runtime\tracks\dirt-5\background.png
copy .\data\tracks\dirt-5\dirt-5.ac .\runtime\tracks\dirt-5\dirt-5.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-6
copy .\data\tracks\dirt-6\dirt-6.xml .\runtime\tracks\dirt-6\dirt-6.xml
copy .\data\tracks\dirt-6\background.png .\runtime\tracks\dirt-6\background.png
copy .\data\tracks\dirt-6\dirt-6.ac .\runtime\tracks\dirt-6\dirt-6.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\eroad
copy .\data\tracks\eroad\eroad.xml .\runtime\tracks\eroad\eroad.xml
copy .\data\tracks\eroad\background.png .\runtime\tracks\eroad\background.png
copy .\data\tracks\eroad\eroad.ac .\runtime\tracks\eroad\eroad.ac
copy .\data\tracks\eroad\eroad-relief.ac .\runtime\tracks\eroad\eroad-relief.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-1
copy .\data\tracks\e-track-1\e-track-1.xml .\runtime\tracks\e-track-1\e-track-1.xml
copy .\data\tracks\e-track-1\background.png .\runtime\tracks\e-track-1\background.png
copy .\data\tracks\e-track-1\e-track-1.ac .\runtime\tracks\e-track-1\e-track-1.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-2
copy .\data\tracks\e-track-2\e-track-2.xml .\runtime\tracks\e-track-2\e-track-2.xml
copy .\data\tracks\e-track-2\background.png .\runtime\tracks\e-track-2\background.png
copy .\data\tracks\e-track-2\e-track-2.ac .\runtime\tracks\e-track-2\e-track-2.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-3
copy .\data\tracks\e-track-3\e-track-3.xml .\runtime\tracks\e-track-3\e-track-3.xml
copy .\data\tracks\e-track-3\background.png .\runtime\tracks\e-track-3\background.png
copy .\data\tracks\e-track-3\env.rgb .\runtime\tracks\e-track-3\env.rgb
copy .\data\tracks\e-track-3\e-track-3.ac .\runtime\tracks\e-track-3\e-track-3.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-4
copy .\data\tracks\e-track-4\e-track-4.xml .\runtime\tracks\e-track-4\e-track-4.xml
copy .\data\tracks\e-track-4\background.png .\runtime\tracks\e-track-4\background.png
copy .\data\tracks\e-track-4\e-track-4.ac .\runtime\tracks\e-track-4\e-track-4.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-5
copy .\data\tracks\e-track-5\e-track-5.xml .\runtime\tracks\e-track-5\e-track-5.xml
copy .\data\tracks\e-track-5\background.png .\runtime\tracks\e-track-5\background.png
copy .\data\tracks\e-track-5\e-track-5.ac .\runtime\tracks\e-track-5\e-track-5.ac
copy .\data\tracks\e-track-5\e-track-5-relief.ac .\runtime\tracks\e-track-5\e-track-5-relief.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-6
copy .\data\tracks\e-track-6\e-track-6.xml .\runtime\tracks\e-track-6\e-track-6.xml
copy .\data\tracks\e-track-6\background.png .\runtime\tracks\e-track-6\background.png
copy .\data\tracks\e-track-6\e-track-6.ac .\runtime\tracks\e-track-6\e-track-6.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\g-track-1
copy .\data\tracks\g-track-1\g-track-1.xml .\runtime\tracks\g-track-1\g-track-1.xml
copy .\data\tracks\g-track-1\g-track-1.ac .\runtime\tracks\g-track-1\g-track-1.ac
copy .\data\tracks\g-track-1\background.png .\runtime\tracks\g-track-1\background.png
copy .\data\tracks\g-track-1\alltree2.rgb .\runtime\tracks\g-track-1\alltree2.rgb
copy .\data\tracks\g-track-1\alltree.rgb .\runtime\tracks\g-track-1\alltree.rgb
copy .\data\tracks\g-track-1\asphalt2.rgb .\runtime\tracks\g-track-1\asphalt2.rgb
copy .\data\tracks\g-track-1\asphalt3.rgb .\runtime\tracks\g-track-1\asphalt3.rgb
copy .\data\tracks\g-track-1\env.rgb .\runtime\tracks\g-track-1\env.rgb
copy .\data\tracks\g-track-1\grassg1.rgb .\runtime\tracks\g-track-1\grassg1.rgb
copy .\data\tracks\g-track-1\grassg2.rgb .\runtime\tracks\g-track-1\grassg2.rgb
copy .\data\tracks\g-track-1\grassg3.rgb .\runtime\tracks\g-track-1\grassg3.rgb
copy .\data\tracks\g-track-1\rock2.rgb .\runtime\tracks\g-track-1\rock2.rgb
copy .\data\tracks\g-track-1\rock3.rgb .\runtime\tracks\g-track-1\rock3.rgb
copy .\data\tracks\g-track-1\texte1.rgb .\runtime\tracks\g-track-1\texte1.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\michigan
copy .\data\tracks\michigan\michigan.xml .\runtime\tracks\michigan\michigan.xml
copy .\data\tracks\michigan\background.png .\runtime\tracks\michigan\background.png
copy .\data\tracks\michigan\michigan.ac .\runtime\tracks\michigan\michigan.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\mixed-1
copy .\data\tracks\mixed-1\mixed-1.xml .\runtime\tracks\mixed-1\mixed-1.xml
copy .\data\tracks\mixed-1\mixed-1.ac .\runtime\tracks\mixed-1\mixed-1.ac
copy .\data\tracks\mixed-1\background.png .\runtime\tracks\mixed-1\background.png
copy .\data\tracks\mixed-1\env1.png .\runtime\tracks\mixed-1\env1.png

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\mixed-2
copy .\data\tracks\mixed-2\mixed-2.xml .\runtime\tracks\mixed-2\mixed-2.xml
copy .\data\tracks\mixed-2\background.png .\runtime\tracks\mixed-2\background.png
copy .\data\tracks\mixed-2\env.rgb .\runtime\tracks\mixed-2\env.rgb
copy .\data\tracks\mixed-2\mixed-2.ac .\runtime\tracks\mixed-2\mixed-2.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\cylos1
call .\create_dir .\runtime\drivers\cylos1\tracksdata
copy .\src\drivers\cylos1\tracksdata\car_e-track-3.xml .\runtime\drivers\cylos1\tracksdata\car_e-track-3.xml
copy .\src\drivers\cylos1\tracksdata\car_lemans.xml .\runtime\drivers\cylos1\tracksdata\car_lemans.xml
copy .\src\drivers\cylos1\tracksdata\car_test-1.xml .\runtime\drivers\cylos1\tracksdata\car_test-1.xml
copy .\src\drivers\cylos1\tracksdata\lemans.xml .\runtime\drivers\cylos1\tracksdata\lemans.xml
copy .\src\drivers\cylos1\tracksdata\michigan.xml .\runtime\drivers\cylos1\tracksdata\michigan.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\cylos1
copy .\src\drivers\cylos1\cylos1.xml .\runtime\drivers\cylos1\cylos1.xml
copy .\src\drivers\cylos1\car1.xml .\runtime\drivers\cylos1\car1.xml
copy .\src\drivers\cylos1\cg-nascar-rwd.rgb .\runtime\drivers\cylos1\cg-nascar-rwd.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\1
copy .\src\drivers\damned\1\car.xml .\runtime\drivers\damned\1\car.xml
copy .\src\drivers\damned\1\buggy.rgb .\runtime\drivers\damned\1\buggy.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\10
copy .\src\drivers\damned\10\car.xml .\runtime\drivers\damned\10\car.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\2
copy .\src\drivers\damned\2\car.xml .\runtime\drivers\damned\2\car.xml
copy .\src\drivers\damned\2\buggy.rgb .\runtime\drivers\damned\2\buggy.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\3
copy .\src\drivers\damned\3\p406.rgb .\runtime\drivers\damned\3\p406.rgb
copy .\src\drivers\damned\3\car.xml .\runtime\drivers\damned\3\car.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\4
copy .\src\drivers\damned\4\p406.rgb .\runtime\drivers\damned\4\p406.rgb
copy .\src\drivers\damned\4\car.xml .\runtime\drivers\damned\4\car.xml
copy .\src\drivers\damned\4\torcs.rgb .\runtime\drivers\damned\4\torcs.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\5
copy .\src\drivers\damned\5\car.xml .\runtime\drivers\damned\5\car.xml
copy .\src\drivers\damned\5\acura-nsx-sz.rgb .\runtime\drivers\damned\5\acura-nsx-sz.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\6
copy .\src\drivers\damned\6\acura-nsx-sz.rgb .\runtime\drivers\damned\6\acura-nsx-sz.rgb
copy .\src\drivers\damned\6\car.xml .\runtime\drivers\damned\6\car.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\7
copy .\src\drivers\damned\7\viper-gts-r.rgb .\runtime\drivers\damned\7\viper-gts-r.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\8
copy .\src\drivers\damned\8\car.xml .\runtime\drivers\damned\8\car.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
copy .\src\drivers\damned\damned.xml .\runtime\drivers\damned\damned.xml
copy .\src\drivers\damned\car1.xml .\runtime\drivers\damned\car1.xml
copy .\src\drivers\damned\logo.rgb .\runtime\drivers\damned\logo.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\cg-gt-rwd
copy .\src\drivers\human\cg-gt-rwd\skin.png .\runtime\drivers\human\cg-gt-rwd\skin.png
copy .\src\drivers\human\cg-gt-rwd\skin.rgb .\runtime\drivers\human\cg-gt-rwd\skin.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-1
copy .\src\drivers\human\tracks\dirt-1\car-torcs.xml .\runtime\drivers\human\tracks\dirt-1\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-2
copy .\src\drivers\human\tracks\dirt-2\car-torcs.xml .\runtime\drivers\human\tracks\dirt-2\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-3
copy .\src\drivers\human\tracks\dirt-3\car-torcs.xml .\runtime\drivers\human\tracks\dirt-3\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-4
copy .\src\drivers\human\tracks\dirt-4\car-torcs.xml .\runtime\drivers\human\tracks\dirt-4\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-5
copy .\src\drivers\human\tracks\dirt-5\car-torcs.xml .\runtime\drivers\human\tracks\dirt-5\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-6
copy .\src\drivers\human\tracks\dirt-6\car-torcs.xml .\runtime\drivers\human\tracks\dirt-6\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-1
copy .\src\drivers\human\tracks\e-track-1\car-torcs.xml .\runtime\drivers\human\tracks\e-track-1\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-2
copy .\src\drivers\human\tracks\e-track-2\car-torcs.xml .\runtime\drivers\human\tracks\e-track-2\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-3
copy .\src\drivers\human\tracks\e-track-3\car-torcs.xml .\runtime\drivers\human\tracks\e-track-3\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-4
copy .\src\drivers\human\tracks\e-track-4\car-torcs.xml .\runtime\drivers\human\tracks\e-track-4\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-5
copy .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml .\runtime\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml
copy .\src\drivers\human\tracks\e-track-5\car-torcs.xml .\runtime\drivers\human\tracks\e-track-5\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-6
copy .\src\drivers\human\tracks\e-track-6\car-torcs.xml .\runtime\drivers\human\tracks\e-track-6\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\mixed-1
copy .\src\drivers\human\tracks\mixed-1\car-torcs.xml .\runtime\drivers\human\tracks\mixed-1\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\mixed-2
copy .\src\drivers\human\tracks\mixed-2\car-torcs.xml .\runtime\drivers\human\tracks\mixed-2\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
copy .\src\drivers\human\car-buggy.xml .\runtime\drivers\human\car-buggy.xml
copy .\src\drivers\human\car-cg-gt-rwd.xml .\runtime\drivers\human\car-cg-gt-rwd.xml
copy .\src\drivers\human\car-cg-nascar-fwd.xml .\runtime\drivers\human\car-cg-nascar-fwd.xml
copy .\src\drivers\human\car-cg-nascar-rwd.xml .\runtime\drivers\human\car-cg-nascar-rwd.xml
copy .\src\drivers\human\car-lotus-gt1.xml .\runtime\drivers\human\car-lotus-gt1.xml
copy .\src\drivers\human\car-mclaren-f1.xml .\runtime\drivers\human\car-mclaren-f1.xml
copy .\src\drivers\human\car-p406.xml .\runtime\drivers\human\car-p406.xml
copy .\src\drivers\human\car-torcs.xml .\runtime\drivers\human\car-torcs.xml
copy .\src\drivers\human\car-viper-gts-r.xml .\runtime\drivers\human\car-viper-gts-r.xml
copy .\src\drivers\human\human.xml .\runtime\drivers\human\human.xml
copy .\src\drivers\human\preferences.xml .\runtime\drivers\human\preferences.xml
copy .\src\drivers\human\logo.rgb .\runtime\drivers\human\logo.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\K1999
copy .\src\drivers\K1999\K1999.xml .\runtime\drivers\K1999\K1999.xml
copy .\src\drivers\K1999\settings.xml .\runtime\drivers\K1999\settings.xml
copy .\src\drivers\K1999\logo.rgb .\runtime\drivers\K1999\logo.rgb
copy .\src\drivers\K1999\cg-nascar-rwd.rgb .\runtime\drivers\K1999\cg-nascar-rwd.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\lliaw
call .\create_dir .\runtime\drivers\lliaw\tracksdata
copy .\src\drivers\lliaw\tracksdata\car_e-track-3.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-3.xml
copy .\src\drivers\lliaw\tracksdata\car_e-track-4.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-4.xml
copy .\src\drivers\lliaw\tracksdata\car_e-track-6.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-6.xml
copy .\src\drivers\lliaw\tracksdata\car_eroad.xml .\runtime\drivers\lliaw\tracksdata\car_eroad.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\lliaw
copy .\src\drivers\lliaw\lliaw.xml .\runtime\drivers\lliaw\lliaw.xml
copy .\src\drivers\lliaw\car.xml .\runtime\drivers\lliaw\car.xml
copy .\src\drivers\lliaw\viper-gts-r.rgb .\runtime\drivers\lliaw\viper-gts-r.rgb
copy .\src\drivers\lliaw\logo.rgb .\runtime\drivers\lliaw\logo.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tanhoj
call .\create_dir .\runtime\drivers\tanhoj\tracksdata
copy .\src\drivers\tanhoj\tracksdata\aalborg.xml .\runtime\drivers\tanhoj\tracksdata\aalborg.xml
copy .\src\drivers\tanhoj\tracksdata\car_aalborg.xml .\runtime\drivers\tanhoj\tracksdata\car_aalborg.xml
copy .\src\drivers\tanhoj\tracksdata\car_eroad.xml .\runtime\drivers\tanhoj\tracksdata\car_eroad.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-1.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-2.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-2.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-3.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-3.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-4.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-4.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-5.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-5.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-6.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-6.xml
copy .\src\drivers\tanhoj\tracksdata\car_g-track-1.xml .\runtime\drivers\tanhoj\tracksdata\car_g-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_s2.xml .\runtime\drivers\tanhoj\tracksdata\car_s2.xml
copy .\src\drivers\tanhoj\tracksdata\car_test-1.xml .\runtime\drivers\tanhoj\tracksdata\car_test-1.xml
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

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tanhoj
copy .\src\drivers\tanhoj\tanhoj.xml .\runtime\drivers\tanhoj\tanhoj.xml
copy .\src\drivers\tanhoj\car1.xml .\runtime\drivers\tanhoj\car1.xml
copy .\src\drivers\tanhoj\logo.rgb .\runtime\drivers\tanhoj\logo.rgb
copy .\src\drivers\tanhoj\cg-nascar-rwd.rgb .\runtime\drivers\tanhoj\cg-nascar-rwd.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tita
copy .\src\drivers\tita\tita.xml .\runtime\drivers\tita\tita.xml
copy .\src\drivers\tita\car.xml .\runtime\drivers\tita\car.xml
copy .\src\drivers\tita\logo.rgb .\runtime\drivers\tita\logo.rgb
copy .\src\drivers\tita\lotus-gt1.rgb .\runtime\drivers\tita\lotus-gt1.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tutorial1
copy .\src\drivers\tutorial1\tutorial1.xml .\runtime\drivers\tutorial1\tutorial1.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tutorial2
copy .\src\drivers\tutorial2\tutorial2.xml .\runtime\drivers\tutorial2\tutorial2.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\config
copy .\src\libs\tgf\screen.xml .\runtime\config\screen.xml
copy .\src\libs\tgf\params.dtd .\runtime\config\params.dtd

call .\create_dir .\runtime
call .\create_dir .\runtime\config
call .\create_dir .\runtime\config\practice
copy .\src\modules\raceman\practice\practice\practice.xml .\runtime\config\practice\practice.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\config
call .\create_dir .\runtime\config\quickrace
copy .\src\modules\raceman\quickrace\qrace.xml .\runtime\config\quickrace\qrace.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\telemetry
copy .\src\modules\telemetry\telemetry.sh .\runtime\telemetry\telemetry.sh

call .\create_dir .\runtime
call .\create_dir .\runtime\tools
call .\create_dir .\runtime\tools\trackgen
copy .\src\tools\trackgen\trackgen.xml .\runtime\tools\trackgen\trackgen.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\free\free.xml .\runtime\categories\free.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\offroad-r-a\offroad-r-a.xml .\runtime\categories\offroad-r-a.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\torcs-f-a\torcs-f-a.xml .\runtime\categories\torcs-f-a.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\torcs-f-b\torcs-f-b.xml .\runtime\categories\torcs-f-b.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\torcs-r-a\torcs-r-a.xml .\runtime\categories\torcs-r-a.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\torcs-r-b\torcs-r-b.xml .\runtime\categories\torcs-r-b.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\categories
copy .\data\cars\categories\torcs-r-c\torcs-r-c.xml .\runtime\categories\torcs-r-c.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\acura-nsx-sz
copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz.xml .\runtime\cars\acura-nsx-sz\acura-nsx-sz.xml
copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz.ac .\runtime\cars\acura-nsx-sz\acura-nsx-sz.ac
copy .\data\cars\models\acura-nsx-sz\tex-wheel.rgb .\runtime\cars\acura-nsx-sz\tex-wheel.rgb
copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz.rgb .\runtime\cars\acura-nsx-sz\acura-nsx-sz.rgb
copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz-base.ac .\runtime\cars\acura-nsx-sz\acura-nsx-sz-base.ac
copy .\data\cars\models\acura-nsx-sz\texmapper.xml .\runtime\cars\acura-nsx-sz\texmapper.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\buggy
copy .\data\cars\models\buggy\buggy.xml .\runtime\cars\buggy\buggy.xml
copy .\data\cars\models\buggy\buggy.ac .\runtime\cars\buggy\buggy.ac
copy .\data\cars\models\buggy\buggy.rgb .\runtime\cars\buggy\buggy.rgb
copy .\data\cars\models\buggy\tex-wheel.rgb .\runtime\cars\buggy\tex-wheel.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\cg-nascar-fwd
copy .\data\cars\models\cg-nascar-fwd\cg-nascar-fwd.xml .\runtime\cars\cg-nascar-fwd\cg-nascar-fwd.xml
copy .\data\cars\models\cg-nascar-fwd\cg-nascar-fwd.ac .\runtime\cars\cg-nascar-fwd\cg-nascar-fwd.ac
copy .\data\cars\models\cg-nascar-fwd\cg-nascar-fwd.rgb .\runtime\cars\cg-nascar-fwd\cg-nascar-fwd.rgb
copy .\data\cars\models\cg-nascar-fwd\tex-wheel.rgb .\runtime\cars\cg-nascar-fwd\tex-wheel.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\cg-nascar-rwd
copy .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.xml .\runtime\cars\cg-nascar-rwd\cg-nascar-rwd.xml
copy .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.ac .\runtime\cars\cg-nascar-rwd\cg-nascar-rwd.ac
copy .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.rgb .\runtime\cars\cg-nascar-rwd\cg-nascar-rwd.rgb
copy .\data\cars\models\cg-nascar-rwd\tex-wheel.rgb .\runtime\cars\cg-nascar-rwd\tex-wheel.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\lotus-gt1
copy .\data\cars\models\lotus-gt1\lotus-gt1.xml .\runtime\cars\lotus-gt1\lotus-gt1.xml
copy .\data\cars\models\lotus-gt1\lotus-gt1.ac .\runtime\cars\lotus-gt1\lotus-gt1.ac
copy .\data\cars\models\lotus-gt1\lotus-gt1-base.ac .\runtime\cars\lotus-gt1\lotus-gt1-base.ac
copy .\data\cars\models\lotus-gt1\texmapper.xml .\runtime\cars\lotus-gt1\texmapper.xml
copy .\data\cars\models\lotus-gt1\tex-wheel.rgb .\runtime\cars\lotus-gt1\tex-wheel.rgb
copy .\data\cars\models\lotus-gt1\lotus-gt1.rgb .\runtime\cars\lotus-gt1\lotus-gt1.rgb
copy .\data\cars\models\lotus-gt1\lotus-gt1-512.rgb .\runtime\cars\lotus-gt1\lotus-gt1-512.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\mclaren-f1
copy .\data\cars\models\mclaren-f1\mclaren-f1.xml .\runtime\cars\mclaren-f1\mclaren-f1.xml
copy .\data\cars\models\mclaren-f1\mclaren-f1.ac .\runtime\cars\mclaren-f1\mclaren-f1.ac
copy .\data\cars\models\mclaren-f1\mclaren-f1-base.ac .\runtime\cars\mclaren-f1\mclaren-f1-base.ac
copy .\data\cars\models\mclaren-f1\texmapper.xml .\runtime\cars\mclaren-f1\texmapper.xml
copy .\data\cars\models\mclaren-f1\tex-wheel.rgb .\runtime\cars\mclaren-f1\tex-wheel.rgb
copy .\data\cars\models\mclaren-f1\mclaren-f1.rgb .\runtime\cars\mclaren-f1\mclaren-f1.rgb
copy .\data\cars\models\mclaren-f1\mclaren-f1-512.rgb .\runtime\cars\mclaren-f1\mclaren-f1-512.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\p406
copy .\data\cars\models\p406\p406.xml .\runtime\cars\p406\p406.xml
copy .\data\cars\models\p406\texmapper.xml .\runtime\cars\p406\texmapper.xml
copy .\data\cars\models\p406\p406.ac .\runtime\cars\p406\p406.ac
copy .\data\cars\models\p406\p406-base.ac .\runtime\cars\p406\p406-base.ac
copy .\data\cars\models\p406\p406-512.rgb .\runtime\cars\p406\p406-512.rgb
copy .\data\cars\models\p406\p406.rgb .\runtime\cars\p406\p406.rgb
copy .\data\cars\models\p406\tex-wheel.rgb .\runtime\cars\p406\tex-wheel.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\torcs
copy .\data\cars\models\torcs\torcs.xml .\runtime\cars\torcs\torcs.xml
copy .\data\cars\models\torcs\torcs.ac .\runtime\cars\torcs\torcs.ac
copy .\data\cars\models\torcs\torcs.rgb .\runtime\cars\torcs\torcs.rgb
copy .\data\cars\models\torcs\tex-wheel.rgb .\runtime\cars\torcs\tex-wheel.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\cars
call .\create_dir .\runtime\cars\viper-gts-r
copy .\data\cars\models\viper-gts-r\viper-gts-r.xml .\runtime\cars\viper-gts-r\viper-gts-r.xml
copy .\data\cars\models\viper-gts-r\tex-wheel.rgb .\runtime\cars\viper-gts-r\tex-wheel.rgb
copy .\data\cars\models\viper-gts-r\viper-gts-r.rgb .\runtime\cars\viper-gts-r\viper-gts-r.rgb
copy .\data\cars\models\viper-gts-r\viper-gts-r.ac .\runtime\cars\viper-gts-r\viper-gts-r.ac
copy .\data\cars\models\viper-gts-r\viper-gts-r-512.rgb .\runtime\cars\viper-gts-r\viper-gts-r-512.rgb
copy .\data\cars\models\viper-gts-r\viper-gts-r-base.ac .\runtime\cars\viper-gts-r\viper-gts-r-base.ac
copy .\data\cars\models\viper-gts-r\texmapper.xml .\runtime\cars\viper-gts-r\texmapper.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\fonts
copy .\data\data\fonts\b5.glf .\runtime\data\fonts\b5.glf
copy .\data\data\fonts\b6.glf .\runtime\data\fonts\b6.glf
copy .\data\data\fonts\b7.glf .\runtime\data\fonts\b7.glf
copy .\data\data\fonts\digital.glf .\runtime\data\fonts\digital.glf
copy .\data\data\fonts\fragile.glf .\runtime\data\fonts\fragile.glf
copy .\data\data\fonts\Makefile .\runtime\data\fonts\Makefile

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\img
copy .\data\data\img\arrow-down.png .\runtime\data\img\arrow-down.png
copy .\data\data\img\arrow-down-pushed.png .\runtime\data\img\arrow-down-pushed.png
copy .\data\data\img\arrow-left.png .\runtime\data\img\arrow-left.png
copy .\data\data\img\arrow-left-pushed.png .\runtime\data\img\arrow-left-pushed.png
copy .\data\data\img\arrow-right.png .\runtime\data\img\arrow-right.png
copy .\data\data\img\arrow-right-pushed.png .\runtime\data\img\arrow-right-pushed.png
copy .\data\data\img\arrow-up.png .\runtime\data\img\arrow-up.png
copy .\data\data\img\arrow-up-pushed.png .\runtime\data\img\arrow-up-pushed.png
copy .\data\data\img\env.png .\runtime\data\img\env.png
copy .\data\data\img\ruler.png .\runtime\data\img\ruler.png
copy .\data\data\img\ruler-pushed.png .\runtime\data\img\ruler-pushed.png
copy .\data\data\img\splash-free1.png .\runtime\data\img\splash-free1.png
copy .\data\data\img\splash-free2.png .\runtime\data\img\splash-free2.png
copy .\data\data\img\splash-free3.png .\runtime\data\img\splash-free3.png
copy .\data\data\img\splash-free4.png .\runtime\data\img\splash-free4.png
copy .\data\data\img\splash-free5.png .\runtime\data\img\splash-free5.png
copy .\data\data\img\splash-free7.png .\runtime\data\img\splash-free7.png
copy .\data\data\img\splash-free.png .\runtime\data\img\splash-free.png
copy .\data\data\img\splash-graphic.png .\runtime\data\img\splash-graphic.png
copy .\data\data\img\splash-joycal.png .\runtime\data\img\splash-joycal.png
copy .\data\data\img\splash-joyconf.png .\runtime\data\img\splash-joyconf.png
copy .\data\data\img\splash-main.png .\runtime\data\img\splash-main.png
copy .\data\data\img\splash-options.png .\runtime\data\img\splash-options.png
copy .\data\data\img\splash.png .\runtime\data\img\splash.png
copy .\data\data\img\splash-practice.png .\runtime\data\img\splash-practice.png
copy .\data\data\img\splash-prsess.png .\runtime\data\img\splash-prsess.png
copy .\data\data\img\splash-qrdrv.png .\runtime\data\img\splash-qrdrv.png
copy .\data\data\img\splash-qrloading.png .\runtime\data\img\splash-qrloading.png
copy .\data\data\img\splash-qr.png .\runtime\data\img\splash-qr.png
copy .\data\data\img\splash-qrtrk.png .\runtime\data\img\splash-qrtrk.png
copy .\data\data\img\splash-quit.png .\runtime\data\img\splash-quit.png
copy .\data\data\img\splash-result.png .\runtime\data\img\splash-result.png

call .\create_dir .\runtime
call .\create_dir .\runtime\menu
copy .\data\data\menu\entry.xml .\runtime\menu\entry.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\objects
copy .\data\data\objects\stand-inter.ac .\runtime\data\objects\stand-inter.ac
copy .\data\data\objects\stand-main.ac .\runtime\data\objects\stand-main.ac
copy .\data\data\objects\stand-wall.ac .\runtime\data\objects\stand-wall.ac
copy .\data\data\objects\tree1.ac .\runtime\data\objects\tree1.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\sound
copy .\data\data\sound\crash1.wav .\runtime\data\sound\crash1.wav
copy .\data\data\sound\crash2.wav .\runtime\data\sound\crash2.wav
copy .\data\data\sound\crash3.wav .\runtime\data\sound\crash3.wav
copy .\data\data\sound\crash4.wav .\runtime\data\sound\crash4.wav
copy .\data\data\sound\crash5.wav .\runtime\data\sound\crash5.wav
copy .\data\data\sound\crash6.wav .\runtime\data\sound\crash6.wav
copy .\data\data\sound\engine-1.wav .\runtime\data\sound\engine-1.wav
copy .\data\data\sound\skid.wav .\runtime\data\sound\skid.wav

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\textures
copy .\data\data\textures\background.png .\runtime\data\textures\background.png
copy .\data\data\textures\logo.png .\runtime\data\textures\logo.png
copy .\data\data\textures\pylon1.png .\runtime\data\textures\pylon1.png
copy .\data\data\textures\pylon2.png .\runtime\data\textures\pylon2.png
copy .\data\data\textures\pylon3.png .\runtime\data\textures\pylon3.png
copy .\data\data\textures\tr-asphalt-both.png .\runtime\data\textures\tr-asphalt-both.png
copy .\data\data\textures\tr-asphalt-left.png .\runtime\data\textures\tr-asphalt-left.png
copy .\data\data\textures\tr-asphalt-l.png .\runtime\data\textures\tr-asphalt-l.png
copy .\data\data\textures\tr-asphalt.png .\runtime\data\textures\tr-asphalt.png
copy .\data\data\textures\tr-asphalt-p.png .\runtime\data\textures\tr-asphalt-p.png
copy .\data\data\textures\tr-asphalt-right.png .\runtime\data\textures\tr-asphalt-right.png
copy .\data\data\textures\tr-barrier.png .\runtime\data\textures\tr-barrier.png
copy .\data\data\textures\tr-concrete.png .\runtime\data\textures\tr-concrete.png
copy .\data\data\textures\tr-dirtb.png .\runtime\data\textures\tr-dirtb.png
copy .\data\data\textures\tr-dirt.png .\runtime\data\textures\tr-dirt.png
copy .\data\data\textures\tr-grass.png .\runtime\data\textures\tr-grass.png
copy .\data\data\textures\tr-sand.png .\runtime\data\textures\tr-sand.png
copy .\data\data\textures\concrete2.rgb .\runtime\data\textures\concrete2.rgb
copy .\data\data\textures\concrete.rgb .\runtime\data\textures\concrete.rgb
copy .\data\data\textures\env.rgb .\runtime\data\textures\env.rgb
copy .\data\data\textures\logo.rgb .\runtime\data\textures\logo.rgb
copy .\data\data\textures\pit-left.rgb .\runtime\data\textures\pit-left.rgb
copy .\data\data\textures\pit-right.rgb .\runtime\data\textures\pit-right.rgb
copy .\data\data\textures\pylon1.rgb .\runtime\data\textures\pylon1.rgb
copy .\data\data\textures\pylon2.rgb .\runtime\data\textures\pylon2.rgb
copy .\data\data\textures\pylon3.rgb .\runtime\data\textures\pylon3.rgb
copy .\data\data\textures\rim1.rgb .\runtime\data\textures\rim1.rgb
copy .\data\data\textures\rim2.rgb .\runtime\data\textures\rim2.rgb
copy .\data\data\textures\tr-asphalt-both_nmm.rgb .\runtime\data\textures\tr-asphalt-both_nmm.rgb
copy .\data\data\textures\tr-asphalt-both.rgb .\runtime\data\textures\tr-asphalt-both.rgb
copy .\data\data\textures\tr-asphalt-left_nmm.rgb .\runtime\data\textures\tr-asphalt-left_nmm.rgb
copy .\data\data\textures\tr-asphalt-left.rgb .\runtime\data\textures\tr-asphalt-left.rgb
copy .\data\data\textures\tr-asphalt-l_nmm.rgb .\runtime\data\textures\tr-asphalt-l_nmm.rgb
copy .\data\data\textures\tr-asphalt-l.rgb .\runtime\data\textures\tr-asphalt-l.rgb
copy .\data\data\textures\tr-asphalt_nmm.rgb .\runtime\data\textures\tr-asphalt_nmm.rgb
copy .\data\data\textures\tr-asphalt-p_nmm.rgb .\runtime\data\textures\tr-asphalt-p_nmm.rgb
copy .\data\data\textures\tr-asphalt-p.rgb .\runtime\data\textures\tr-asphalt-p.rgb
copy .\data\data\textures\tr-asphalt.rgb .\runtime\data\textures\tr-asphalt.rgb
copy .\data\data\textures\tr-asphalt-right_nmm.rgb .\runtime\data\textures\tr-asphalt-right_nmm.rgb
copy .\data\data\textures\tr-asphalt-right.rgb .\runtime\data\textures\tr-asphalt-right.rgb
copy .\data\data\textures\tr-barrier.rgb .\runtime\data\textures\tr-barrier.rgb
copy .\data\data\textures\tr-concrete_nmm.rgb .\runtime\data\textures\tr-concrete_nmm.rgb
copy .\data\data\textures\tr-concrete.rgb .\runtime\data\textures\tr-concrete.rgb
copy .\data\data\textures\tr-dirtb.rgb .\runtime\data\textures\tr-dirtb.rgb
copy .\data\data\textures\tr-dirt.rgb .\runtime\data\textures\tr-dirt.rgb
copy .\data\data\textures\tree1.rgb .\runtime\data\textures\tree1.rgb
copy .\data\data\textures\tr-grass2.rgb .\runtime\data\textures\tr-grass2.rgb
copy .\data\data\textures\tr-grass.rgb .\runtime\data\textures\tr-grass.rgb
copy .\data\data\textures\tr-sand2.rgb .\runtime\data\textures\tr-sand2.rgb
copy .\data\data\textures\tr-sand.rgb .\runtime\data\textures\tr-sand.rgb
copy .\data\data\textures\tr-water.rgb .\runtime\data\textures\tr-water.rgb
copy .\data\data\textures\turn100L.rgb .\runtime\data\textures\turn100L.rgb
copy .\data\data\textures\turn100R.rgb .\runtime\data\textures\turn100R.rgb
copy .\data\data\textures\turn150L.rgb .\runtime\data\textures\turn150L.rgb
copy .\data\data\textures\turn150R.rgb .\runtime\data\textures\turn150R.rgb
copy .\data\data\textures\turn200L.rgb .\runtime\data\textures\turn200L.rgb
copy .\data\data\textures\turn200R.rgb .\runtime\data\textures\turn200R.rgb
copy .\data\data\textures\turn300L.rgb .\runtime\data\textures\turn300L.rgb
copy .\data\data\textures\turn300R.rgb .\runtime\data\textures\turn300R.rgb
copy .\data\data\textures\turn50L.rgb .\runtime\data\textures\turn50L.rgb
copy .\data\data\textures\turn50R.rgb .\runtime\data\textures\turn50R.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\data
call .\create_dir .\runtime\data\tracks
copy .\data\data\tracks\surfaces.xml .\runtime\data\tracks\surfaces.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\aalborg
copy .\data\tracks\aalborg\aalborg.xml .\runtime\tracks\aalborg\aalborg.xml
copy .\data\tracks\aalborg\aalborg.ac .\runtime\tracks\aalborg\aalborg.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\a-speedway
copy .\data\tracks\a-speedway\a-speedway.xml .\runtime\tracks\a-speedway\a-speedway.xml
copy .\data\tracks\a-speedway\background.png .\runtime\tracks\a-speedway\background.png
copy .\data\tracks\a-speedway\a-speedway.ac .\runtime\tracks\a-speedway\a-speedway.ac
copy .\data\tracks\a-speedway\a-speedway-relief.ac .\runtime\tracks\a-speedway\a-speedway-relief.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-1
copy .\data\tracks\dirt-1\dirt-1.xml .\runtime\tracks\dirt-1\dirt-1.xml
copy .\data\tracks\dirt-1\background.png .\runtime\tracks\dirt-1\background.png
copy .\data\tracks\dirt-1\dirt-1.ac .\runtime\tracks\dirt-1\dirt-1.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-2
copy .\data\tracks\dirt-2\dirt-2.xml .\runtime\tracks\dirt-2\dirt-2.xml
copy .\data\tracks\dirt-2\background.png .\runtime\tracks\dirt-2\background.png
copy .\data\tracks\dirt-2\dirt-2.ac .\runtime\tracks\dirt-2\dirt-2.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-3
copy .\data\tracks\dirt-3\dirt-3.xml .\runtime\tracks\dirt-3\dirt-3.xml
copy .\data\tracks\dirt-3\background.png .\runtime\tracks\dirt-3\background.png
copy .\data\tracks\dirt-3\background2.png .\runtime\tracks\dirt-3\background2.png
copy .\data\tracks\dirt-3\dirt-3.ac .\runtime\tracks\dirt-3\dirt-3.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-4
copy .\data\tracks\dirt-4\dirt-4.xml .\runtime\tracks\dirt-4\dirt-4.xml
copy .\data\tracks\dirt-4\background.png .\runtime\tracks\dirt-4\background.png
copy .\data\tracks\dirt-4\dirt-4.ac .\runtime\tracks\dirt-4\dirt-4.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-5
copy .\data\tracks\dirt-5\dirt-5.xml .\runtime\tracks\dirt-5\dirt-5.xml
copy .\data\tracks\dirt-5\background.png .\runtime\tracks\dirt-5\background.png
copy .\data\tracks\dirt-5\dirt-5.ac .\runtime\tracks\dirt-5\dirt-5.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\dirt-6
copy .\data\tracks\dirt-6\dirt-6.xml .\runtime\tracks\dirt-6\dirt-6.xml
copy .\data\tracks\dirt-6\background.png .\runtime\tracks\dirt-6\background.png
copy .\data\tracks\dirt-6\dirt-6.ac .\runtime\tracks\dirt-6\dirt-6.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\eroad
copy .\data\tracks\eroad\eroad.xml .\runtime\tracks\eroad\eroad.xml
copy .\data\tracks\eroad\background.png .\runtime\tracks\eroad\background.png
copy .\data\tracks\eroad\eroad.ac .\runtime\tracks\eroad\eroad.ac
copy .\data\tracks\eroad\eroad-relief.ac .\runtime\tracks\eroad\eroad-relief.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-1
copy .\data\tracks\e-track-1\e-track-1.xml .\runtime\tracks\e-track-1\e-track-1.xml
copy .\data\tracks\e-track-1\background.png .\runtime\tracks\e-track-1\background.png
copy .\data\tracks\e-track-1\e-track-1.ac .\runtime\tracks\e-track-1\e-track-1.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-2
copy .\data\tracks\e-track-2\e-track-2.xml .\runtime\tracks\e-track-2\e-track-2.xml
copy .\data\tracks\e-track-2\background.png .\runtime\tracks\e-track-2\background.png
copy .\data\tracks\e-track-2\e-track-2.ac .\runtime\tracks\e-track-2\e-track-2.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-3
copy .\data\tracks\e-track-3\e-track-3.xml .\runtime\tracks\e-track-3\e-track-3.xml
copy .\data\tracks\e-track-3\background.png .\runtime\tracks\e-track-3\background.png
copy .\data\tracks\e-track-3\env.rgb .\runtime\tracks\e-track-3\env.rgb
copy .\data\tracks\e-track-3\e-track-3.ac .\runtime\tracks\e-track-3\e-track-3.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-4
copy .\data\tracks\e-track-4\e-track-4.xml .\runtime\tracks\e-track-4\e-track-4.xml
copy .\data\tracks\e-track-4\background.png .\runtime\tracks\e-track-4\background.png
copy .\data\tracks\e-track-4\e-track-4.ac .\runtime\tracks\e-track-4\e-track-4.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-5
copy .\data\tracks\e-track-5\e-track-5.xml .\runtime\tracks\e-track-5\e-track-5.xml
copy .\data\tracks\e-track-5\background.png .\runtime\tracks\e-track-5\background.png
copy .\data\tracks\e-track-5\e-track-5.ac .\runtime\tracks\e-track-5\e-track-5.ac
copy .\data\tracks\e-track-5\e-track-5-relief.ac .\runtime\tracks\e-track-5\e-track-5-relief.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\e-track-6
copy .\data\tracks\e-track-6\e-track-6.xml .\runtime\tracks\e-track-6\e-track-6.xml
copy .\data\tracks\e-track-6\background.png .\runtime\tracks\e-track-6\background.png
copy .\data\tracks\e-track-6\e-track-6.ac .\runtime\tracks\e-track-6\e-track-6.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\g-track-1
copy .\data\tracks\g-track-1\g-track-1.xml .\runtime\tracks\g-track-1\g-track-1.xml
copy .\data\tracks\g-track-1\g-track-1.ac .\runtime\tracks\g-track-1\g-track-1.ac
copy .\data\tracks\g-track-1\background.png .\runtime\tracks\g-track-1\background.png
copy .\data\tracks\g-track-1\alltree2.rgb .\runtime\tracks\g-track-1\alltree2.rgb
copy .\data\tracks\g-track-1\alltree.rgb .\runtime\tracks\g-track-1\alltree.rgb
copy .\data\tracks\g-track-1\asphalt2.rgb .\runtime\tracks\g-track-1\asphalt2.rgb
copy .\data\tracks\g-track-1\asphalt3.rgb .\runtime\tracks\g-track-1\asphalt3.rgb
copy .\data\tracks\g-track-1\env.rgb .\runtime\tracks\g-track-1\env.rgb
copy .\data\tracks\g-track-1\grassg1.rgb .\runtime\tracks\g-track-1\grassg1.rgb
copy .\data\tracks\g-track-1\grassg2.rgb .\runtime\tracks\g-track-1\grassg2.rgb
copy .\data\tracks\g-track-1\grassg3.rgb .\runtime\tracks\g-track-1\grassg3.rgb
copy .\data\tracks\g-track-1\rock2.rgb .\runtime\tracks\g-track-1\rock2.rgb
copy .\data\tracks\g-track-1\rock3.rgb .\runtime\tracks\g-track-1\rock3.rgb
copy .\data\tracks\g-track-1\texte1.rgb .\runtime\tracks\g-track-1\texte1.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\michigan
copy .\data\tracks\michigan\michigan.xml .\runtime\tracks\michigan\michigan.xml
copy .\data\tracks\michigan\background.png .\runtime\tracks\michigan\background.png
copy .\data\tracks\michigan\michigan.ac .\runtime\tracks\michigan\michigan.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\mixed-1
copy .\data\tracks\mixed-1\mixed-1.xml .\runtime\tracks\mixed-1\mixed-1.xml
copy .\data\tracks\mixed-1\mixed-1.ac .\runtime\tracks\mixed-1\mixed-1.ac
copy .\data\tracks\mixed-1\background.png .\runtime\tracks\mixed-1\background.png
copy .\data\tracks\mixed-1\env1.png .\runtime\tracks\mixed-1\env1.png

call .\create_dir .\runtime
call .\create_dir .\runtime\tracks
call .\create_dir .\runtime\tracks\mixed-2
copy .\data\tracks\mixed-2\mixed-2.xml .\runtime\tracks\mixed-2\mixed-2.xml
copy .\data\tracks\mixed-2\background.png .\runtime\tracks\mixed-2\background.png
copy .\data\tracks\mixed-2\env.rgb .\runtime\tracks\mixed-2\env.rgb
copy .\data\tracks\mixed-2\mixed-2.ac .\runtime\tracks\mixed-2\mixed-2.ac

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\cylos1
call .\create_dir .\runtime\drivers\cylos1\tracksdata
copy .\src\drivers\cylos1\tracksdata\car_e-track-3.xml .\runtime\drivers\cylos1\tracksdata\car_e-track-3.xml
copy .\src\drivers\cylos1\tracksdata\car_lemans.xml .\runtime\drivers\cylos1\tracksdata\car_lemans.xml
copy .\src\drivers\cylos1\tracksdata\car_test-1.xml .\runtime\drivers\cylos1\tracksdata\car_test-1.xml
copy .\src\drivers\cylos1\tracksdata\lemans.xml .\runtime\drivers\cylos1\tracksdata\lemans.xml
copy .\src\drivers\cylos1\tracksdata\michigan.xml .\runtime\drivers\cylos1\tracksdata\michigan.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\cylos1
copy .\src\drivers\cylos1\cylos1.xml .\runtime\drivers\cylos1\cylos1.xml
copy .\src\drivers\cylos1\car1.xml .\runtime\drivers\cylos1\car1.xml
copy .\src\drivers\cylos1\cg-nascar-rwd.rgb .\runtime\drivers\cylos1\cg-nascar-rwd.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\1
copy .\src\drivers\damned\1\car.xml .\runtime\drivers\damned\1\car.xml
copy .\src\drivers\damned\1\buggy.rgb .\runtime\drivers\damned\1\buggy.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\10
copy .\src\drivers\damned\10\car.xml .\runtime\drivers\damned\10\car.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\2
copy .\src\drivers\damned\2\car.xml .\runtime\drivers\damned\2\car.xml
copy .\src\drivers\damned\2\buggy.rgb .\runtime\drivers\damned\2\buggy.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\3
copy .\src\drivers\damned\3\p406.rgb .\runtime\drivers\damned\3\p406.rgb
copy .\src\drivers\damned\3\car.xml .\runtime\drivers\damned\3\car.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\4
copy .\src\drivers\damned\4\p406.rgb .\runtime\drivers\damned\4\p406.rgb
copy .\src\drivers\damned\4\car.xml .\runtime\drivers\damned\4\car.xml
copy .\src\drivers\damned\4\torcs.rgb .\runtime\drivers\damned\4\torcs.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\5
copy .\src\drivers\damned\5\car.xml .\runtime\drivers\damned\5\car.xml
copy .\src\drivers\damned\5\acura-nsx-sz.rgb .\runtime\drivers\damned\5\acura-nsx-sz.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\6
copy .\src\drivers\damned\6\acura-nsx-sz.rgb .\runtime\drivers\damned\6\acura-nsx-sz.rgb
copy .\src\drivers\damned\6\car.xml .\runtime\drivers\damned\6\car.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\7
copy .\src\drivers\damned\7\viper-gts-r.rgb .\runtime\drivers\damned\7\viper-gts-r.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
call .\create_dir .\runtime\drivers\damned\8
copy .\src\drivers\damned\8\car.xml .\runtime\drivers\damned\8\car.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\damned
copy .\src\drivers\damned\damned.xml .\runtime\drivers\damned\damned.xml
copy .\src\drivers\damned\car1.xml .\runtime\drivers\damned\car1.xml
copy .\src\drivers\damned\logo.rgb .\runtime\drivers\damned\logo.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\cg-gt-rwd
copy .\src\drivers\human\cg-gt-rwd\skin.png .\runtime\drivers\human\cg-gt-rwd\skin.png
copy .\src\drivers\human\cg-gt-rwd\skin.rgb .\runtime\drivers\human\cg-gt-rwd\skin.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-1
copy .\src\drivers\human\tracks\dirt-1\car-torcs.xml .\runtime\drivers\human\tracks\dirt-1\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-2
copy .\src\drivers\human\tracks\dirt-2\car-torcs.xml .\runtime\drivers\human\tracks\dirt-2\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-3
copy .\src\drivers\human\tracks\dirt-3\car-torcs.xml .\runtime\drivers\human\tracks\dirt-3\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-4
copy .\src\drivers\human\tracks\dirt-4\car-torcs.xml .\runtime\drivers\human\tracks\dirt-4\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-5
copy .\src\drivers\human\tracks\dirt-5\car-torcs.xml .\runtime\drivers\human\tracks\dirt-5\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\dirt-6
copy .\src\drivers\human\tracks\dirt-6\car-torcs.xml .\runtime\drivers\human\tracks\dirt-6\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-1
copy .\src\drivers\human\tracks\e-track-1\car-torcs.xml .\runtime\drivers\human\tracks\e-track-1\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-2
copy .\src\drivers\human\tracks\e-track-2\car-torcs.xml .\runtime\drivers\human\tracks\e-track-2\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-3
copy .\src\drivers\human\tracks\e-track-3\car-torcs.xml .\runtime\drivers\human\tracks\e-track-3\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-4
copy .\src\drivers\human\tracks\e-track-4\car-torcs.xml .\runtime\drivers\human\tracks\e-track-4\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-5
copy .\src\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml .\runtime\drivers\human\tracks\e-track-5\car-cg-nascar-rwd.xml
copy .\src\drivers\human\tracks\e-track-5\car-torcs.xml .\runtime\drivers\human\tracks\e-track-5\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\e-track-6
copy .\src\drivers\human\tracks\e-track-6\car-torcs.xml .\runtime\drivers\human\tracks\e-track-6\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\mixed-1
copy .\src\drivers\human\tracks\mixed-1\car-torcs.xml .\runtime\drivers\human\tracks\mixed-1\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
call .\create_dir .\runtime\drivers\human\tracks
call .\create_dir .\runtime\drivers\human\tracks\mixed-2
copy .\src\drivers\human\tracks\mixed-2\car-torcs.xml .\runtime\drivers\human\tracks\mixed-2\car-torcs.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\human
copy .\src\drivers\human\car-buggy.xml .\runtime\drivers\human\car-buggy.xml
copy .\src\drivers\human\car-cg-gt-rwd.xml .\runtime\drivers\human\car-cg-gt-rwd.xml
copy .\src\drivers\human\car-cg-nascar-fwd.xml .\runtime\drivers\human\car-cg-nascar-fwd.xml
copy .\src\drivers\human\car-cg-nascar-rwd.xml .\runtime\drivers\human\car-cg-nascar-rwd.xml
copy .\src\drivers\human\car-lotus-gt1.xml .\runtime\drivers\human\car-lotus-gt1.xml
copy .\src\drivers\human\car-mclaren-f1.xml .\runtime\drivers\human\car-mclaren-f1.xml
copy .\src\drivers\human\car-p406.xml .\runtime\drivers\human\car-p406.xml
copy .\src\drivers\human\car-torcs.xml .\runtime\drivers\human\car-torcs.xml
copy .\src\drivers\human\car-viper-gts-r.xml .\runtime\drivers\human\car-viper-gts-r.xml
copy .\src\drivers\human\human.xml .\runtime\drivers\human\human.xml
copy .\src\drivers\human\preferences.xml .\runtime\drivers\human\preferences.xml
copy .\src\drivers\human\logo.rgb .\runtime\drivers\human\logo.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\K1999
copy .\src\drivers\K1999\K1999.xml .\runtime\drivers\K1999\K1999.xml
copy .\src\drivers\K1999\settings.xml .\runtime\drivers\K1999\settings.xml
copy .\src\drivers\K1999\logo.rgb .\runtime\drivers\K1999\logo.rgb
copy .\src\drivers\K1999\cg-nascar-rwd.rgb .\runtime\drivers\K1999\cg-nascar-rwd.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\lliaw
call .\create_dir .\runtime\drivers\lliaw\tracksdata
copy .\src\drivers\lliaw\tracksdata\car_e-track-3.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-3.xml
copy .\src\drivers\lliaw\tracksdata\car_e-track-4.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-4.xml
copy .\src\drivers\lliaw\tracksdata\car_e-track-6.xml .\runtime\drivers\lliaw\tracksdata\car_e-track-6.xml
copy .\src\drivers\lliaw\tracksdata\car_eroad.xml .\runtime\drivers\lliaw\tracksdata\car_eroad.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\lliaw
copy .\src\drivers\lliaw\lliaw.xml .\runtime\drivers\lliaw\lliaw.xml
copy .\src\drivers\lliaw\car.xml .\runtime\drivers\lliaw\car.xml
copy .\src\drivers\lliaw\viper-gts-r.rgb .\runtime\drivers\lliaw\viper-gts-r.rgb
copy .\src\drivers\lliaw\logo.rgb .\runtime\drivers\lliaw\logo.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tanhoj
call .\create_dir .\runtime\drivers\tanhoj\tracksdata
copy .\src\drivers\tanhoj\tracksdata\aalborg.xml .\runtime\drivers\tanhoj\tracksdata\aalborg.xml
copy .\src\drivers\tanhoj\tracksdata\car_aalborg.xml .\runtime\drivers\tanhoj\tracksdata\car_aalborg.xml
copy .\src\drivers\tanhoj\tracksdata\car_eroad.xml .\runtime\drivers\tanhoj\tracksdata\car_eroad.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-1.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-2.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-2.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-3.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-3.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-4.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-4.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-5.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-5.xml
copy .\src\drivers\tanhoj\tracksdata\car_e-track-6.xml .\runtime\drivers\tanhoj\tracksdata\car_e-track-6.xml
copy .\src\drivers\tanhoj\tracksdata\car_g-track-1.xml .\runtime\drivers\tanhoj\tracksdata\car_g-track-1.xml
copy .\src\drivers\tanhoj\tracksdata\car_s2.xml .\runtime\drivers\tanhoj\tracksdata\car_s2.xml
copy .\src\drivers\tanhoj\tracksdata\car_test-1.xml .\runtime\drivers\tanhoj\tracksdata\car_test-1.xml
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

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tanhoj
copy .\src\drivers\tanhoj\tanhoj.xml .\runtime\drivers\tanhoj\tanhoj.xml
copy .\src\drivers\tanhoj\car1.xml .\runtime\drivers\tanhoj\car1.xml
copy .\src\drivers\tanhoj\logo.rgb .\runtime\drivers\tanhoj\logo.rgb
copy .\src\drivers\tanhoj\cg-nascar-rwd.rgb .\runtime\drivers\tanhoj\cg-nascar-rwd.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tita
copy .\src\drivers\tita\tita.xml .\runtime\drivers\tita\tita.xml
copy .\src\drivers\tita\car.xml .\runtime\drivers\tita\car.xml
copy .\src\drivers\tita\logo.rgb .\runtime\drivers\tita\logo.rgb
copy .\src\drivers\tita\lotus-gt1.rgb .\runtime\drivers\tita\lotus-gt1.rgb

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tutorial1
copy .\src\drivers\tutorial1\tutorial1.xml .\runtime\drivers\tutorial1\tutorial1.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tutorial2
copy .\src\drivers\tutorial2\tutorial2.xml .\runtime\drivers\tutorial2\tutorial2.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\config
copy .\src\libs\tgf\screen.xml .\runtime\config\screen.xml
copy .\src\libs\tgf\params.dtd .\runtime\config\params.dtd

call .\create_dir .\runtime
call .\create_dir .\runtime\config
call .\create_dir .\runtime\config\practice
copy .\src\modules\raceman\practice\practice\practice.xml .\runtime\config\practice\practice.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\config
call .\create_dir .\runtime\config\quickrace
copy .\src\modules\raceman\quickrace\qrace.xml .\runtime\config\quickrace\qrace.xml

call .\create_dir .\runtime
call .\create_dir .\runtime\telemetry
copy .\src\modules\telemetry\telemetry.sh .\runtime\telemetry\telemetry.sh

call .\create_dir .\runtime
call .\create_dir .\runtime\tools
call .\create_dir .\runtime\tools\trackgen
copy .\src\tools\trackgen\trackgen.xml .\runtime\tools\trackgen\trackgen.xml
