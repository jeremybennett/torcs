@echo off
echo Checking directories ...

call .\create_dir .\export
call .\create_dir .\export\lib
call .\create_dir .\export\libd

if exist .\src\interfaces\*.* call .\create_dir .\export
if exist .\src\interfaces\*.* call .\create_dir .\export\include
if exist .\src\interfaces\car.h copy .\src\interfaces\car.h .\export\include\car.h
if exist .\src\interfaces\graphic.h copy .\src\interfaces\graphic.h .\export\include\graphic.h
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
if exist .\src\libs\confscreens\simuconfig.h copy .\src\libs\confscreens\simuconfig.h .\export\include\simuconfig.h
if exist .\src\libs\confscreens\soundconfig.h copy .\src\libs\confscreens\soundconfig.h .\export\include\soundconfig.h
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

if exist .\src\libs\portability\*.* call .\create_dir .\export
if exist .\src\libs\portability\*.* call .\create_dir .\export\include
if exist .\src\libs\portability\portability.h copy .\src\libs\portability\portability.h .\export\include\portability.h

if exist .\src\libs\math\*.* call .\create_dir .\export
if exist .\src\libs\math\*.* call .\create_dir .\export\include
if exist .\src\libs\math\*.* call .\create_dir .\export\include\tmath
if exist .\src\libs\math\linalg_t.h copy .\src\libs\math\linalg_t.h .\export\include\tmath\linalg_t.h
if exist .\src\libs\math\v2_t.h copy .\src\libs\math\v2_t.h .\export\include\tmath\v2_t.h
if exist .\src\libs\math\v3_t.h copy .\src\libs\math\v3_t.h .\export\include\tmath\v3_t.h
if exist .\src\libs\math\v4_t.h copy .\src\libs\math\v4_t.h .\export\include\tmath\v4_t.h
if exist .\src\libs\math\straight2_t.h copy .\src\libs\math\straight2_t.h .\export\include\tmath\straight2_t.h

if exist .\src\libs\musicplayer\*.* call .\create_dir .\export
if exist .\src\libs\musicplayer\*.* call .\create_dir .\export\include
if exist .\src\libs\musicplayer\*.* call .\create_dir .\export\include\musicplayer
if exist .\src\libs\musicplayer\musicplayer.h copy .\src\libs\musicplayer\musicplayer.h .\export\include\musicplayer\musicplayer.h
if exist .\src\libs\musicplayer\SoundStream.h copy .\src\libs\musicplayer\SoundStream.h .\export\include\musicplayer\SoundStream.h
if exist .\src\libs\musicplayer\OggSoundStream.h copy .\src\libs\musicplayer\OggSoundStream.h .\export\include\musicplayer\OggSoundStream.h
if exist .\src\libs\musicplayer\OpenALMusicPlayer.h copy .\src\libs\musicplayer\OpenALMusicPlayer.h .\export\include\musicplayer\OpenALMusicPlayer.h

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

if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers\berniw\1
if exist .\src\drivers\berniw\1\car1-stock1.rgb copy .\src\drivers\berniw\1\car1-stock1.rgb .\runtime\drivers\berniw\1\car1-stock1.rgb
if exist .\src\drivers\berniw\1\default.xml copy .\src\drivers\berniw\1\default.xml .\runtime\drivers\berniw\1\default.xml

if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers\berniw\10
if exist .\src\drivers\berniw\10\car1-trb3.rgb copy .\src\drivers\berniw\10\car1-trb3.rgb .\runtime\drivers\berniw\10\car1-trb3.rgb
if exist .\src\drivers\berniw\10\default.xml copy .\src\drivers\berniw\10\default.xml .\runtime\drivers\berniw\10\default.xml

if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers\berniw\2
if exist .\src\drivers\berniw\2\car1-stock1.rgb copy .\src\drivers\berniw\2\car1-stock1.rgb .\runtime\drivers\berniw\2\car1-stock1.rgb
if exist .\src\drivers\berniw\2\default.xml copy .\src\drivers\berniw\2\default.xml .\runtime\drivers\berniw\2\default.xml

if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers\berniw\3
if exist .\src\drivers\berniw\3\car1-trb1.rgb copy .\src\drivers\berniw\3\car1-trb1.rgb .\runtime\drivers\berniw\3\car1-trb1.rgb
if exist .\src\drivers\berniw\3\default.xml copy .\src\drivers\berniw\3\default.xml .\runtime\drivers\berniw\3\default.xml

if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers\berniw\4
if exist .\src\drivers\berniw\4\car2-trb1.rgb copy .\src\drivers\berniw\4\car2-trb1.rgb .\runtime\drivers\berniw\4\car2-trb1.rgb
if exist .\src\drivers\berniw\4\default.xml copy .\src\drivers\berniw\4\default.xml .\runtime\drivers\berniw\4\default.xml

if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers\berniw\5
if exist .\src\drivers\berniw\5\car3-trb1.rgb copy .\src\drivers\berniw\5\car3-trb1.rgb .\runtime\drivers\berniw\5\car3-trb1.rgb
if exist .\src\drivers\berniw\5\default.xml copy .\src\drivers\berniw\5\default.xml .\runtime\drivers\berniw\5\default.xml

if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers\berniw\6
if exist .\src\drivers\berniw\6\car4-trb1.rgb copy .\src\drivers\berniw\6\car4-trb1.rgb .\runtime\drivers\berniw\6\car4-trb1.rgb
if exist .\src\drivers\berniw\6\default.xml copy .\src\drivers\berniw\6\default.xml .\runtime\drivers\berniw\6\default.xml

if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers\berniw\7
if exist .\src\drivers\berniw\7\car5-trb1.rgb copy .\src\drivers\berniw\7\car5-trb1.rgb .\runtime\drivers\berniw\7\car5-trb1.rgb
if exist .\src\drivers\berniw\7\default.xml copy .\src\drivers\berniw\7\default.xml .\runtime\drivers\berniw\7\default.xml

if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers\berniw\8
if exist .\src\drivers\berniw\8\car6-trb1.rgb copy .\src\drivers\berniw\8\car6-trb1.rgb .\runtime\drivers\berniw\8\car6-trb1.rgb
if exist .\src\drivers\berniw\8\default.xml copy .\src\drivers\berniw\8\default.xml .\runtime\drivers\berniw\8\default.xml

if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers\berniw\9
if exist .\src\drivers\berniw\9\car7-trb1.rgb copy .\src\drivers\berniw\9\car7-trb1.rgb .\runtime\drivers\berniw\9\car7-trb1.rgb
if exist .\src\drivers\berniw\9\default.xml copy .\src\drivers\berniw\9\default.xml .\runtime\drivers\berniw\9\default.xml

if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\berniw.xml copy .\src\drivers\berniw\berniw.xml .\runtime\drivers\berniw\berniw.xml
if exist .\src\drivers\berniw\logo.rgb copy .\src\drivers\berniw\logo.rgb .\runtime\drivers\berniw\logo.rgb

if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers\berniw2\1
if exist .\src\drivers\berniw2\1\default.xml copy .\src\drivers\berniw2\1\default.xml .\runtime\drivers\berniw2\1\default.xml

if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers\berniw2\10
if exist .\src\drivers\berniw2\10\car1-trb3.rgb copy .\src\drivers\berniw2\10\car1-trb3.rgb .\runtime\drivers\berniw2\10\car1-trb3.rgb
if exist .\src\drivers\berniw2\10\default.xml copy .\src\drivers\berniw2\10\default.xml .\runtime\drivers\berniw2\10\default.xml

if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers\berniw2\2
if exist .\src\drivers\berniw2\2\default.xml copy .\src\drivers\berniw2\2\default.xml .\runtime\drivers\berniw2\2\default.xml

if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers\berniw2\3
if exist .\src\drivers\berniw2\3\default.xml copy .\src\drivers\berniw2\3\default.xml .\runtime\drivers\berniw2\3\default.xml

if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers\berniw2\4
if exist .\src\drivers\berniw2\4\default.xml copy .\src\drivers\berniw2\4\default.xml .\runtime\drivers\berniw2\4\default.xml

if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers\berniw2\5
if exist .\src\drivers\berniw2\5\default.xml copy .\src\drivers\berniw2\5\default.xml .\runtime\drivers\berniw2\5\default.xml

if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers\berniw2\6
if exist .\src\drivers\berniw2\6\default.xml copy .\src\drivers\berniw2\6\default.xml .\runtime\drivers\berniw2\6\default.xml

if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers\berniw2\7
if exist .\src\drivers\berniw2\7\car5-trb1.rgb copy .\src\drivers\berniw2\7\car5-trb1.rgb .\runtime\drivers\berniw2\7\car5-trb1.rgb
if exist .\src\drivers\berniw2\7\default.xml copy .\src\drivers\berniw2\7\default.xml .\runtime\drivers\berniw2\7\default.xml

if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers\berniw2\8
if exist .\src\drivers\berniw2\8\car4-trb1.rgb copy .\src\drivers\berniw2\8\car4-trb1.rgb .\runtime\drivers\berniw2\8\car4-trb1.rgb
if exist .\src\drivers\berniw2\8\default.xml copy .\src\drivers\berniw2\8\default.xml .\runtime\drivers\berniw2\8\default.xml

if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers\berniw2\9
if exist .\src\drivers\berniw2\9\car7-trb1.rgb copy .\src\drivers\berniw2\9\car7-trb1.rgb .\runtime\drivers\berniw2\9\car7-trb1.rgb
if exist .\src\drivers\berniw2\9\default.xml copy .\src\drivers\berniw2\9\default.xml .\runtime\drivers\berniw2\9\default.xml

if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\berniw2.xml copy .\src\drivers\berniw2\berniw2.xml .\runtime\drivers\berniw2\berniw2.xml
if exist .\src\drivers\berniw2\logo.rgb copy .\src\drivers\berniw2\logo.rgb .\runtime\drivers\berniw2\logo.rgb

if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtime\drivers\berniw3\1
if exist .\src\drivers\berniw3\1\default.xml copy .\src\drivers\berniw3\1\default.xml .\runtime\drivers\berniw3\1\default.xml

if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtime\drivers\berniw3\10
if exist .\src\drivers\berniw3\10\default.xml copy .\src\drivers\berniw3\10\default.xml .\runtime\drivers\berniw3\10\default.xml

if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtime\drivers\berniw3\2
if exist .\src\drivers\berniw3\2\default.xml copy .\src\drivers\berniw3\2\default.xml .\runtime\drivers\berniw3\2\default.xml

if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtime\drivers\berniw3\3
if exist .\src\drivers\berniw3\3\default.xml copy .\src\drivers\berniw3\3\default.xml .\runtime\drivers\berniw3\3\default.xml

if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtime\drivers\berniw3\4
if exist .\src\drivers\berniw3\4\default.xml copy .\src\drivers\berniw3\4\default.xml .\runtime\drivers\berniw3\4\default.xml

if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtime\drivers\berniw3\5
if exist .\src\drivers\berniw3\5\default.xml copy .\src\drivers\berniw3\5\default.xml .\runtime\drivers\berniw3\5\default.xml

if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtime\drivers\berniw3\6
if exist .\src\drivers\berniw3\6\default.xml copy .\src\drivers\berniw3\6\default.xml .\runtime\drivers\berniw3\6\default.xml

if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtime\drivers\berniw3\7
if exist .\src\drivers\berniw3\7\default.xml copy .\src\drivers\berniw3\7\default.xml .\runtime\drivers\berniw3\7\default.xml

if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtime\drivers\berniw3\8
if exist .\src\drivers\berniw3\8\default.xml copy .\src\drivers\berniw3\8\default.xml .\runtime\drivers\berniw3\8\default.xml

if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtime\drivers\berniw3\9
if exist .\src\drivers\berniw3\9\default.xml copy .\src\drivers\berniw3\9\default.xml .\runtime\drivers\berniw3\9\default.xml

if exist .\src\drivers\berniw3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\berniw3.xml copy .\src\drivers\berniw3\berniw3.xml .\runtime\drivers\berniw3\berniw3.xml
if exist .\src\drivers\berniw3\logo.rgb copy .\src\drivers\berniw3\logo.rgb .\runtime\drivers\berniw3\logo.rgb

if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtime\drivers\bt\0
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtime\drivers\bt\0\practice

if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtime\drivers\bt\0
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtime\drivers\bt\0\qualifying

if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtime\drivers\bt\0
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtime\drivers\bt\0\race

if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtime\drivers\bt\0
if exist .\src\drivers\bt\0\default.xml copy .\src\drivers\bt\0\default.xml .\runtime\drivers\bt\0\default.xml
if exist .\src\drivers\bt\0\car1-stock1.rgb copy .\src\drivers\bt\0\car1-stock1.rgb .\runtime\drivers\bt\0\car1-stock1.rgb

if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtime\drivers\bt\1
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtime\drivers\bt\1\practice

if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtime\drivers\bt\1
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtime\drivers\bt\1\qualifying

if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtime\drivers\bt\1
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtime\drivers\bt\1\race

if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtime\drivers\bt\1
if exist .\src\drivers\bt\1\default.xml copy .\src\drivers\bt\1\default.xml .\runtime\drivers\bt\1\default.xml
if exist .\src\drivers\bt\1\car1-stock1.rgb copy .\src\drivers\bt\1\car1-stock1.rgb .\runtime\drivers\bt\1\car1-stock1.rgb

if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtime\drivers\bt\2
if exist .\src\drivers\bt\2\car1-trb1.rgb copy .\src\drivers\bt\2\car1-trb1.rgb .\runtime\drivers\bt\2\car1-trb1.rgb
if exist .\src\drivers\bt\2\default.xml copy .\src\drivers\bt\2\default.xml .\runtime\drivers\bt\2\default.xml

if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtime\drivers\bt\3
if exist .\src\drivers\bt\3\car2-trb1.rgb copy .\src\drivers\bt\3\car2-trb1.rgb .\runtime\drivers\bt\3\car2-trb1.rgb
if exist .\src\drivers\bt\3\default.xml copy .\src\drivers\bt\3\default.xml .\runtime\drivers\bt\3\default.xml

if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtime\drivers\bt\4
if exist .\src\drivers\bt\4\car3-trb1.rgb copy .\src\drivers\bt\4\car3-trb1.rgb .\runtime\drivers\bt\4\car3-trb1.rgb
if exist .\src\drivers\bt\4\default.xml copy .\src\drivers\bt\4\default.xml .\runtime\drivers\bt\4\default.xml

if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtime\drivers\bt\5
if exist .\src\drivers\bt\5\car4-trb1.rgb copy .\src\drivers\bt\5\car4-trb1.rgb .\runtime\drivers\bt\5\car4-trb1.rgb
if exist .\src\drivers\bt\5\default.xml copy .\src\drivers\bt\5\default.xml .\runtime\drivers\bt\5\default.xml

if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtime\drivers\bt\6
if exist .\src\drivers\bt\6\car5-trb1.rgb copy .\src\drivers\bt\6\car5-trb1.rgb .\runtime\drivers\bt\6\car5-trb1.rgb
if exist .\src\drivers\bt\6\default.xml copy .\src\drivers\bt\6\default.xml .\runtime\drivers\bt\6\default.xml

if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtime\drivers\bt\7
if exist .\src\drivers\bt\7\car6-trb1.rgb copy .\src\drivers\bt\7\car6-trb1.rgb .\runtime\drivers\bt\7\car6-trb1.rgb
if exist .\src\drivers\bt\7\default.xml copy .\src\drivers\bt\7\default.xml .\runtime\drivers\bt\7\default.xml

if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtime\drivers\bt\8
if exist .\src\drivers\bt\8\car7-trb1.rgb copy .\src\drivers\bt\8\car7-trb1.rgb .\runtime\drivers\bt\8\car7-trb1.rgb
if exist .\src\drivers\bt\8\default.xml copy .\src\drivers\bt\8\default.xml .\runtime\drivers\bt\8\default.xml

if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtime\drivers\bt\9
if exist .\src\drivers\bt\9\default.xml copy .\src\drivers\bt\9\default.xml .\runtime\drivers\bt\9\default.xml

if exist .\src\drivers\bt\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\bt.xml copy .\src\drivers\bt\bt.xml .\runtime\drivers\bt\bt.xml
if exist .\src\drivers\bt\logo.rgb copy .\src\drivers\bt\logo.rgb .\runtime\drivers\bt\logo.rgb

if exist .\src\drivers\damned\0\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\0\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\0\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\0\*.* call .\create_dir .\runtime\drivers\damned\0
if exist .\src\drivers\damned\0\default.xml copy .\src\drivers\damned\0\default.xml .\runtime\drivers\damned\0\default.xml

if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers\damned\1
if exist .\src\drivers\damned\1\default.xml copy .\src\drivers\damned\1\default.xml .\runtime\drivers\damned\1\default.xml

if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers\damned\2
if exist .\src\drivers\damned\2\default.xml copy .\src\drivers\damned\2\default.xml .\runtime\drivers\damned\2\default.xml

if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers\damned\3
if exist .\src\drivers\damned\3\default.xml copy .\src\drivers\damned\3\default.xml .\runtime\drivers\damned\3\default.xml

if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers\damned\4
if exist .\src\drivers\damned\4\default.xml copy .\src\drivers\damned\4\default.xml .\runtime\drivers\damned\4\default.xml

if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers\damned\5
if exist .\src\drivers\damned\5\default.xml copy .\src\drivers\damned\5\default.xml .\runtime\drivers\damned\5\default.xml

if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers\damned\6
if exist .\src\drivers\damned\6\car5-trb1.rgb copy .\src\drivers\damned\6\car5-trb1.rgb .\runtime\drivers\damned\6\car5-trb1.rgb
if exist .\src\drivers\damned\6\default.xml copy .\src\drivers\damned\6\default.xml .\runtime\drivers\damned\6\default.xml

if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers\damned\7
if exist .\src\drivers\damned\7\car6-trb1.rgb copy .\src\drivers\damned\7\car6-trb1.rgb .\runtime\drivers\damned\7\car6-trb1.rgb
if exist .\src\drivers\damned\7\default.xml copy .\src\drivers\damned\7\default.xml .\runtime\drivers\damned\7\default.xml

if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers\damned\8
if exist .\src\drivers\damned\8\car7-trb1.rgb copy .\src\drivers\damned\8\car7-trb1.rgb .\runtime\drivers\damned\8\car7-trb1.rgb
if exist .\src\drivers\damned\8\default.xml copy .\src\drivers\damned\8\default.xml .\runtime\drivers\damned\8\default.xml

if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers\damned\9
if exist .\src\drivers\damned\9\car1-trb3.rgb copy .\src\drivers\damned\9\car1-trb3.rgb .\runtime\drivers\damned\9\car1-trb3.rgb
if exist .\src\drivers\damned\9\default.xml copy .\src\drivers\damned\9\default.xml .\runtime\drivers\damned\9\default.xml

if exist .\src\drivers\damned\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\damned.xml copy .\src\drivers\damned\damned.xml .\runtime\drivers\damned\damned.xml
if exist .\src\drivers\damned\logo.rgb copy .\src\drivers\damned\logo.rgb .\runtime\drivers\damned\logo.rgb

if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-2
if exist .\src\drivers\human\tracks\dirt-2\car-pw-206wrc.xml copy .\src\drivers\human\tracks\dirt-2\car-pw-206wrc.xml .\runtime\drivers\human\tracks\dirt-2\car-pw-206wrc.xml

if exist .\src\drivers\human\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\car.xml copy .\src\drivers\human\car.xml .\runtime\drivers\human\car.xml
if exist .\src\drivers\human\human.xml copy .\src\drivers\human\human.xml .\runtime\drivers\human\human.xml
if exist .\src\drivers\human\preferences.xml copy .\src\drivers\human\preferences.xml .\runtime\drivers\human\preferences.xml
if exist .\src\drivers\human\logo.rgb copy .\src\drivers\human\logo.rgb .\runtime\drivers\human\logo.rgb

if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers\inferno\1
if exist .\src\drivers\inferno\1\default.xml copy .\src\drivers\inferno\1\default.xml .\runtime\drivers\inferno\1\default.xml

if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers\inferno\10
if exist .\src\drivers\inferno\10\car1-trb3.rgb copy .\src\drivers\inferno\10\car1-trb3.rgb .\runtime\drivers\inferno\10\car1-trb3.rgb
if exist .\src\drivers\inferno\10\default.xml copy .\src\drivers\inferno\10\default.xml .\runtime\drivers\inferno\10\default.xml

if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers\inferno\2
if exist .\src\drivers\inferno\2\p406.rgb copy .\src\drivers\inferno\2\p406.rgb .\runtime\drivers\inferno\2\p406.rgb
if exist .\src\drivers\inferno\2\default.xml copy .\src\drivers\inferno\2\default.xml .\runtime\drivers\inferno\2\default.xml

if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers\inferno\3
if exist .\src\drivers\inferno\3\car1-trb1.rgb copy .\src\drivers\inferno\3\car1-trb1.rgb .\runtime\drivers\inferno\3\car1-trb1.rgb
if exist .\src\drivers\inferno\3\default.xml copy .\src\drivers\inferno\3\default.xml .\runtime\drivers\inferno\3\default.xml

if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers\inferno\4
if exist .\src\drivers\inferno\4\car2-trb1.rgb copy .\src\drivers\inferno\4\car2-trb1.rgb .\runtime\drivers\inferno\4\car2-trb1.rgb
if exist .\src\drivers\inferno\4\default.xml copy .\src\drivers\inferno\4\default.xml .\runtime\drivers\inferno\4\default.xml

if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers\inferno\5
if exist .\src\drivers\inferno\5\car3-trb1.rgb copy .\src\drivers\inferno\5\car3-trb1.rgb .\runtime\drivers\inferno\5\car3-trb1.rgb
if exist .\src\drivers\inferno\5\default.xml copy .\src\drivers\inferno\5\default.xml .\runtime\drivers\inferno\5\default.xml

if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers\inferno\6
if exist .\src\drivers\inferno\6\car4-trb1.rgb copy .\src\drivers\inferno\6\car4-trb1.rgb .\runtime\drivers\inferno\6\car4-trb1.rgb
if exist .\src\drivers\inferno\6\default.xml copy .\src\drivers\inferno\6\default.xml .\runtime\drivers\inferno\6\default.xml

if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers\inferno\7
if exist .\src\drivers\inferno\7\car5-trb1.rgb copy .\src\drivers\inferno\7\car5-trb1.rgb .\runtime\drivers\inferno\7\car5-trb1.rgb
if exist .\src\drivers\inferno\7\default.xml copy .\src\drivers\inferno\7\default.xml .\runtime\drivers\inferno\7\default.xml

if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers\inferno\8
if exist .\src\drivers\inferno\8\car6-trb1.rgb copy .\src\drivers\inferno\8\car6-trb1.rgb .\runtime\drivers\inferno\8\car6-trb1.rgb
if exist .\src\drivers\inferno\8\default.xml copy .\src\drivers\inferno\8\default.xml .\runtime\drivers\inferno\8\default.xml

if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers\inferno\9
if exist .\src\drivers\inferno\9\car7-trb1.rgb copy .\src\drivers\inferno\9\car7-trb1.rgb .\runtime\drivers\inferno\9\car7-trb1.rgb
if exist .\src\drivers\inferno\9\default.xml copy .\src\drivers\inferno\9\default.xml .\runtime\drivers\inferno\9\default.xml

if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\inferno.xml copy .\src\drivers\inferno\inferno.xml .\runtime\drivers\inferno\inferno.xml
if exist .\src\drivers\inferno\logo.rgb copy .\src\drivers\inferno\logo.rgb .\runtime\drivers\inferno\logo.rgb

if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtime\drivers\inferno2\1
if exist .\src\drivers\inferno2\1\defaultcar.xml copy .\src\drivers\inferno2\1\defaultcar.xml .\runtime\drivers\inferno2\1\defaultcar.xml
if exist .\src\drivers\inferno2\1\default.xml copy .\src\drivers\inferno2\1\default.xml .\runtime\drivers\inferno2\1\default.xml
if exist .\src\drivers\inferno2\1\Makefile copy .\src\drivers\inferno2\1\Makefile .\runtime\drivers\inferno2\1\Makefile

if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtime\drivers\inferno2\10
if exist .\src\drivers\inferno2\10\defaultcar.xml copy .\src\drivers\inferno2\10\defaultcar.xml .\runtime\drivers\inferno2\10\defaultcar.xml
if exist .\src\drivers\inferno2\10\default.xml copy .\src\drivers\inferno2\10\default.xml .\runtime\drivers\inferno2\10\default.xml
if exist .\src\drivers\inferno2\10\Makefile copy .\src\drivers\inferno2\10\Makefile .\runtime\drivers\inferno2\10\Makefile

if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtime\drivers\inferno2\2
if exist .\src\drivers\inferno2\2\defaultcar.xml copy .\src\drivers\inferno2\2\defaultcar.xml .\runtime\drivers\inferno2\2\defaultcar.xml
if exist .\src\drivers\inferno2\2\default.xml copy .\src\drivers\inferno2\2\default.xml .\runtime\drivers\inferno2\2\default.xml
if exist .\src\drivers\inferno2\2\Makefile copy .\src\drivers\inferno2\2\Makefile .\runtime\drivers\inferno2\2\Makefile

if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtime\drivers\inferno2\3
if exist .\src\drivers\inferno2\3\defaultcar.xml copy .\src\drivers\inferno2\3\defaultcar.xml .\runtime\drivers\inferno2\3\defaultcar.xml
if exist .\src\drivers\inferno2\3\default.xml copy .\src\drivers\inferno2\3\default.xml .\runtime\drivers\inferno2\3\default.xml
if exist .\src\drivers\inferno2\3\Makefile copy .\src\drivers\inferno2\3\Makefile .\runtime\drivers\inferno2\3\Makefile

if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtime\drivers\inferno2\4
if exist .\src\drivers\inferno2\4\defaultcar.xml copy .\src\drivers\inferno2\4\defaultcar.xml .\runtime\drivers\inferno2\4\defaultcar.xml
if exist .\src\drivers\inferno2\4\default.xml copy .\src\drivers\inferno2\4\default.xml .\runtime\drivers\inferno2\4\default.xml
if exist .\src\drivers\inferno2\4\Makefile copy .\src\drivers\inferno2\4\Makefile .\runtime\drivers\inferno2\4\Makefile

if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtime\drivers\inferno2\5
if exist .\src\drivers\inferno2\5\defaultcar.xml copy .\src\drivers\inferno2\5\defaultcar.xml .\runtime\drivers\inferno2\5\defaultcar.xml
if exist .\src\drivers\inferno2\5\default.xml copy .\src\drivers\inferno2\5\default.xml .\runtime\drivers\inferno2\5\default.xml
if exist .\src\drivers\inferno2\5\Makefile copy .\src\drivers\inferno2\5\Makefile .\runtime\drivers\inferno2\5\Makefile

if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtime\drivers\inferno2\6
if exist .\src\drivers\inferno2\6\defaultcar.xml copy .\src\drivers\inferno2\6\defaultcar.xml .\runtime\drivers\inferno2\6\defaultcar.xml
if exist .\src\drivers\inferno2\6\default.xml copy .\src\drivers\inferno2\6\default.xml .\runtime\drivers\inferno2\6\default.xml
if exist .\src\drivers\inferno2\6\Makefile copy .\src\drivers\inferno2\6\Makefile .\runtime\drivers\inferno2\6\Makefile

if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtime\drivers\inferno2\7
if exist .\src\drivers\inferno2\7\defaultcar.xml copy .\src\drivers\inferno2\7\defaultcar.xml .\runtime\drivers\inferno2\7\defaultcar.xml
if exist .\src\drivers\inferno2\7\default.xml copy .\src\drivers\inferno2\7\default.xml .\runtime\drivers\inferno2\7\default.xml
if exist .\src\drivers\inferno2\7\Makefile copy .\src\drivers\inferno2\7\Makefile .\runtime\drivers\inferno2\7\Makefile

if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtime\drivers\inferno2\8
if exist .\src\drivers\inferno2\8\defaultcar.xml copy .\src\drivers\inferno2\8\defaultcar.xml .\runtime\drivers\inferno2\8\defaultcar.xml
if exist .\src\drivers\inferno2\8\default.xml copy .\src\drivers\inferno2\8\default.xml .\runtime\drivers\inferno2\8\default.xml
if exist .\src\drivers\inferno2\8\Makefile copy .\src\drivers\inferno2\8\Makefile .\runtime\drivers\inferno2\8\Makefile

if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtime\drivers\inferno2\9
if exist .\src\drivers\inferno2\9\defaultcar.xml copy .\src\drivers\inferno2\9\defaultcar.xml .\runtime\drivers\inferno2\9\defaultcar.xml
if exist .\src\drivers\inferno2\9\default.xml copy .\src\drivers\inferno2\9\default.xml .\runtime\drivers\inferno2\9\default.xml
if exist .\src\drivers\inferno2\9\Makefile copy .\src\drivers\inferno2\9\Makefile .\runtime\drivers\inferno2\9\Makefile

if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\inferno2.xml copy .\src\drivers\inferno2\inferno2.xml .\runtime\drivers\inferno2\inferno2.xml
if exist .\src\drivers\inferno2\logo.rgb copy .\src\drivers\inferno2\logo.rgb .\runtime\drivers\inferno2\logo.rgb

if exist .\src\drivers\lliaw\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\1\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\1\*.* call .\create_dir .\runtime\drivers\lliaw\1
if exist .\src\drivers\lliaw\1\default.xml copy .\src\drivers\lliaw\1\default.xml .\runtime\drivers\lliaw\1\default.xml

if exist .\src\drivers\lliaw\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\10\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\10\*.* call .\create_dir .\runtime\drivers\lliaw\10
if exist .\src\drivers\lliaw\10\default.xml copy .\src\drivers\lliaw\10\default.xml .\runtime\drivers\lliaw\10\default.xml

if exist .\src\drivers\lliaw\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\2\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\2\*.* call .\create_dir .\runtime\drivers\lliaw\2
if exist .\src\drivers\lliaw\2\default.xml copy .\src\drivers\lliaw\2\default.xml .\runtime\drivers\lliaw\2\default.xml

if exist .\src\drivers\lliaw\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\3\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\3\*.* call .\create_dir .\runtime\drivers\lliaw\3
if exist .\src\drivers\lliaw\3\car1-trb1.rgb copy .\src\drivers\lliaw\3\car1-trb1.rgb .\runtime\drivers\lliaw\3\car1-trb1.rgb
if exist .\src\drivers\lliaw\3\default.xml copy .\src\drivers\lliaw\3\default.xml .\runtime\drivers\lliaw\3\default.xml

if exist .\src\drivers\lliaw\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\4\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\4\*.* call .\create_dir .\runtime\drivers\lliaw\4
if exist .\src\drivers\lliaw\4\car2-trb1.rgb copy .\src\drivers\lliaw\4\car2-trb1.rgb .\runtime\drivers\lliaw\4\car2-trb1.rgb
if exist .\src\drivers\lliaw\4\default.xml copy .\src\drivers\lliaw\4\default.xml .\runtime\drivers\lliaw\4\default.xml

if exist .\src\drivers\lliaw\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\5\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\5\*.* call .\create_dir .\runtime\drivers\lliaw\5
if exist .\src\drivers\lliaw\5\car3-trb1.rgb copy .\src\drivers\lliaw\5\car3-trb1.rgb .\runtime\drivers\lliaw\5\car3-trb1.rgb
if exist .\src\drivers\lliaw\5\default.xml copy .\src\drivers\lliaw\5\default.xml .\runtime\drivers\lliaw\5\default.xml

if exist .\src\drivers\lliaw\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\6\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\6\*.* call .\create_dir .\runtime\drivers\lliaw\6
if exist .\src\drivers\lliaw\6\car4-trb1.rgb copy .\src\drivers\lliaw\6\car4-trb1.rgb .\runtime\drivers\lliaw\6\car4-trb1.rgb
if exist .\src\drivers\lliaw\6\default.xml copy .\src\drivers\lliaw\6\default.xml .\runtime\drivers\lliaw\6\default.xml

if exist .\src\drivers\lliaw\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\7\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\7\*.* call .\create_dir .\runtime\drivers\lliaw\7
if exist .\src\drivers\lliaw\7\car5-trb1.rgb copy .\src\drivers\lliaw\7\car5-trb1.rgb .\runtime\drivers\lliaw\7\car5-trb1.rgb
if exist .\src\drivers\lliaw\7\default.xml copy .\src\drivers\lliaw\7\default.xml .\runtime\drivers\lliaw\7\default.xml

if exist .\src\drivers\lliaw\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\8\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\8\*.* call .\create_dir .\runtime\drivers\lliaw\8
if exist .\src\drivers\lliaw\8\car6-trb1.rgb copy .\src\drivers\lliaw\8\car6-trb1.rgb .\runtime\drivers\lliaw\8\car6-trb1.rgb
if exist .\src\drivers\lliaw\8\default.xml copy .\src\drivers\lliaw\8\default.xml .\runtime\drivers\lliaw\8\default.xml

if exist .\src\drivers\lliaw\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\9\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\9\*.* call .\create_dir .\runtime\drivers\lliaw\9
if exist .\src\drivers\lliaw\9\car7-trb1.rgb copy .\src\drivers\lliaw\9\car7-trb1.rgb .\runtime\drivers\lliaw\9\car7-trb1.rgb
if exist .\src\drivers\lliaw\9\default.xml copy .\src\drivers\lliaw\9\default.xml .\runtime\drivers\lliaw\9\default.xml

if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\lliaw.xml copy .\src\drivers\lliaw\lliaw.xml .\runtime\drivers\lliaw\lliaw.xml
if exist .\src\drivers\lliaw\logo.rgb copy .\src\drivers\lliaw\logo.rgb .\runtime\drivers\lliaw\logo.rgb

if exist .\src\drivers\olethros\0\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\0\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\0\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\0\*.* call .\create_dir .\runtime\drivers\olethros\0
if exist .\src\drivers\olethros\0\default.xml copy .\src\drivers\olethros\0\default.xml .\runtime\drivers\olethros\0\default.xml

if exist .\src\drivers\olethros\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\1\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\1\*.* call .\create_dir .\runtime\drivers\olethros\1
if exist .\src\drivers\olethros\1\default.xml copy .\src\drivers\olethros\1\default.xml .\runtime\drivers\olethros\1\default.xml

if exist .\src\drivers\olethros\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\2\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\2\*.* call .\create_dir .\runtime\drivers\olethros\2
if exist .\src\drivers\olethros\2\car1-trb1.rgb copy .\src\drivers\olethros\2\car1-trb1.rgb .\runtime\drivers\olethros\2\car1-trb1.rgb
if exist .\src\drivers\olethros\2\default.xml copy .\src\drivers\olethros\2\default.xml .\runtime\drivers\olethros\2\default.xml

if exist .\src\drivers\olethros\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\3\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\3\*.* call .\create_dir .\runtime\drivers\olethros\3
if exist .\src\drivers\olethros\3\car2-trb1.rgb copy .\src\drivers\olethros\3\car2-trb1.rgb .\runtime\drivers\olethros\3\car2-trb1.rgb
if exist .\src\drivers\olethros\3\default.xml copy .\src\drivers\olethros\3\default.xml .\runtime\drivers\olethros\3\default.xml

if exist .\src\drivers\olethros\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\4\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\4\*.* call .\create_dir .\runtime\drivers\olethros\4
if exist .\src\drivers\olethros\4\car3-trb1.rgb copy .\src\drivers\olethros\4\car3-trb1.rgb .\runtime\drivers\olethros\4\car3-trb1.rgb
if exist .\src\drivers\olethros\4\default.xml copy .\src\drivers\olethros\4\default.xml .\runtime\drivers\olethros\4\default.xml

if exist .\src\drivers\olethros\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\5\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\5\*.* call .\create_dir .\runtime\drivers\olethros\5
if exist .\src\drivers\olethros\5\car4-trb1.rgb copy .\src\drivers\olethros\5\car4-trb1.rgb .\runtime\drivers\olethros\5\car4-trb1.rgb
if exist .\src\drivers\olethros\5\default.xml copy .\src\drivers\olethros\5\default.xml .\runtime\drivers\olethros\5\default.xml

if exist .\src\drivers\olethros\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\6\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\6\*.* call .\create_dir .\runtime\drivers\olethros\6
if exist .\src\drivers\olethros\6\car5-trb1.rgb copy .\src\drivers\olethros\6\car5-trb1.rgb .\runtime\drivers\olethros\6\car5-trb1.rgb
if exist .\src\drivers\olethros\6\default.xml copy .\src\drivers\olethros\6\default.xml .\runtime\drivers\olethros\6\default.xml

if exist .\src\drivers\olethros\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\7\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\7\*.* call .\create_dir .\runtime\drivers\olethros\7
if exist .\src\drivers\olethros\7\car6-trb1.rgb copy .\src\drivers\olethros\7\car6-trb1.rgb .\runtime\drivers\olethros\7\car6-trb1.rgb
if exist .\src\drivers\olethros\7\default.xml copy .\src\drivers\olethros\7\default.xml .\runtime\drivers\olethros\7\default.xml

if exist .\src\drivers\olethros\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\8\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\8\*.* call .\create_dir .\runtime\drivers\olethros\8
if exist .\src\drivers\olethros\8\car7-trb1.rgb copy .\src\drivers\olethros\8\car7-trb1.rgb .\runtime\drivers\olethros\8\car7-trb1.rgb
if exist .\src\drivers\olethros\8\default.xml copy .\src\drivers\olethros\8\default.xml .\runtime\drivers\olethros\8\default.xml

if exist .\src\drivers\olethros\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\9\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\9\*.* call .\create_dir .\runtime\drivers\olethros\9
if exist .\src\drivers\olethros\9\default.xml copy .\src\drivers\olethros\9\default.xml .\runtime\drivers\olethros\9\default.xml
if exist .\src\drivers\olethros\9\car1-trb3.rgb copy .\src\drivers\olethros\9\car1-trb3.rgb .\runtime\drivers\olethros\9\car1-trb3.rgb

if exist .\src\drivers\olethros\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\olethros.xml copy .\src\drivers\olethros\olethros.xml .\runtime\drivers\olethros\olethros.xml
if exist .\src\drivers\olethros\logo.rgb copy .\src\drivers\olethros\logo.rgb .\runtime\drivers\olethros\logo.rgb

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

if exist .\src\drivers\tita\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\1\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\1\*.* call .\create_dir .\runtime\drivers\tita\1
if exist .\src\drivers\tita\1\default.xml copy .\src\drivers\tita\1\default.xml .\runtime\drivers\tita\1\default.xml

if exist .\src\drivers\tita\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\10\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\10\*.* call .\create_dir .\runtime\drivers\tita\10
if exist .\src\drivers\tita\10\default.xml copy .\src\drivers\tita\10\default.xml .\runtime\drivers\tita\10\default.xml

if exist .\src\drivers\tita\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\2\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\2\*.* call .\create_dir .\runtime\drivers\tita\2
if exist .\src\drivers\tita\2\default.xml copy .\src\drivers\tita\2\default.xml .\runtime\drivers\tita\2\default.xml

if exist .\src\drivers\tita\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\3\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\3\*.* call .\create_dir .\runtime\drivers\tita\3
if exist .\src\drivers\tita\3\car1-trb1.rgb copy .\src\drivers\tita\3\car1-trb1.rgb .\runtime\drivers\tita\3\car1-trb1.rgb
if exist .\src\drivers\tita\3\default.xml copy .\src\drivers\tita\3\default.xml .\runtime\drivers\tita\3\default.xml

if exist .\src\drivers\tita\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\4\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\4\*.* call .\create_dir .\runtime\drivers\tita\4
if exist .\src\drivers\tita\4\car2-trb1.rgb copy .\src\drivers\tita\4\car2-trb1.rgb .\runtime\drivers\tita\4\car2-trb1.rgb
if exist .\src\drivers\tita\4\default.xml copy .\src\drivers\tita\4\default.xml .\runtime\drivers\tita\4\default.xml

if exist .\src\drivers\tita\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\5\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\5\*.* call .\create_dir .\runtime\drivers\tita\5
if exist .\src\drivers\tita\5\car3-trb1.rgb copy .\src\drivers\tita\5\car3-trb1.rgb .\runtime\drivers\tita\5\car3-trb1.rgb
if exist .\src\drivers\tita\5\default.xml copy .\src\drivers\tita\5\default.xml .\runtime\drivers\tita\5\default.xml

if exist .\src\drivers\tita\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\6\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\6\*.* call .\create_dir .\runtime\drivers\tita\6
if exist .\src\drivers\tita\6\car4-trb1.rgb copy .\src\drivers\tita\6\car4-trb1.rgb .\runtime\drivers\tita\6\car4-trb1.rgb
if exist .\src\drivers\tita\6\default.xml copy .\src\drivers\tita\6\default.xml .\runtime\drivers\tita\6\default.xml

if exist .\src\drivers\tita\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\7\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\7\*.* call .\create_dir .\runtime\drivers\tita\7
if exist .\src\drivers\tita\7\car5-trb1.rgb copy .\src\drivers\tita\7\car5-trb1.rgb .\runtime\drivers\tita\7\car5-trb1.rgb
if exist .\src\drivers\tita\7\default.xml copy .\src\drivers\tita\7\default.xml .\runtime\drivers\tita\7\default.xml

if exist .\src\drivers\tita\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\8\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\8\*.* call .\create_dir .\runtime\drivers\tita\8
if exist .\src\drivers\tita\8\car6-trb1.rgb copy .\src\drivers\tita\8\car6-trb1.rgb .\runtime\drivers\tita\8\car6-trb1.rgb
if exist .\src\drivers\tita\8\default.xml copy .\src\drivers\tita\8\default.xml .\runtime\drivers\tita\8\default.xml

if exist .\src\drivers\tita\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\9\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\9\*.* call .\create_dir .\runtime\drivers\tita\9
if exist .\src\drivers\tita\9\car7-trb1.rgb copy .\src\drivers\tita\9\car7-trb1.rgb .\runtime\drivers\tita\9\car7-trb1.rgb
if exist .\src\drivers\tita\9\default.xml copy .\src\drivers\tita\9\default.xml .\runtime\drivers\tita\9\default.xml

if exist .\src\drivers\tita\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\tita.xml copy .\src\drivers\tita\tita.xml .\runtime\drivers\tita\tita.xml
if exist .\src\drivers\tita\logo.rgb copy .\src\drivers\tita\logo.rgb .\runtime\drivers\tita\logo.rgb

if exist .\src\libs\raceengineclient\*.* call .\create_dir .\runtime
if exist .\src\libs\raceengineclient\*.* call .\create_dir .\runtime\config
if exist .\src\libs\raceengineclient\raceengine.xml copy .\src\libs\raceengineclient\raceengine.xml .\runtime\config\raceengine.xml
if exist .\src\libs\raceengineclient\style.xsl copy .\src\libs\raceengineclient\style.xsl .\runtime\config\style.xsl

if exist .\src\libs\tgf\*.* call .\create_dir .\runtime
if exist .\src\libs\tgf\*.* call .\create_dir .\runtime\config
if exist .\src\libs\tgf\params.dtd copy .\src\libs\tgf\params.dtd .\runtime\config\params.dtd

if exist .\src\libs\tgfclient\*.* call .\create_dir .\runtime
if exist .\src\libs\tgfclient\*.* call .\create_dir .\runtime\config
if exist .\src\libs\tgfclient\screen.xml copy .\src\libs\tgfclient\screen.xml .\runtime\config\screen.xml

if exist .\src\modules\graphic\ssggraph\*.* call .\create_dir .\runtime
if exist .\src\modules\graphic\ssggraph\*.* call .\create_dir .\runtime\config
if exist .\src\modules\graphic\ssggraph\graph.xml copy .\src\modules\graphic\ssggraph\graph.xml .\runtime\config\graph.xml
if exist .\src\modules\graphic\ssggraph\sound.xml copy .\src\modules\graphic\ssggraph\sound.xml .\runtime\config\sound.xml

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

if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\1\*.* call .\create_dir .\runtime\drivers\berniw\1
if exist .\src\drivers\berniw\1\car1-stock1.rgb copy .\src\drivers\berniw\1\car1-stock1.rgb .\runtime\drivers\berniw\1\car1-stock1.rgb
if exist .\src\drivers\berniw\1\default.xml copy .\src\drivers\berniw\1\default.xml .\runtime\drivers\berniw\1\default.xml

if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\10\*.* call .\create_dir .\runtime\drivers\berniw\10
if exist .\src\drivers\berniw\10\car1-trb3.rgb copy .\src\drivers\berniw\10\car1-trb3.rgb .\runtime\drivers\berniw\10\car1-trb3.rgb
if exist .\src\drivers\berniw\10\default.xml copy .\src\drivers\berniw\10\default.xml .\runtime\drivers\berniw\10\default.xml

if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\2\*.* call .\create_dir .\runtime\drivers\berniw\2
if exist .\src\drivers\berniw\2\car1-stock1.rgb copy .\src\drivers\berniw\2\car1-stock1.rgb .\runtime\drivers\berniw\2\car1-stock1.rgb
if exist .\src\drivers\berniw\2\default.xml copy .\src\drivers\berniw\2\default.xml .\runtime\drivers\berniw\2\default.xml

if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\3\*.* call .\create_dir .\runtime\drivers\berniw\3
if exist .\src\drivers\berniw\3\car1-trb1.rgb copy .\src\drivers\berniw\3\car1-trb1.rgb .\runtime\drivers\berniw\3\car1-trb1.rgb
if exist .\src\drivers\berniw\3\default.xml copy .\src\drivers\berniw\3\default.xml .\runtime\drivers\berniw\3\default.xml

if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\4\*.* call .\create_dir .\runtime\drivers\berniw\4
if exist .\src\drivers\berniw\4\car2-trb1.rgb copy .\src\drivers\berniw\4\car2-trb1.rgb .\runtime\drivers\berniw\4\car2-trb1.rgb
if exist .\src\drivers\berniw\4\default.xml copy .\src\drivers\berniw\4\default.xml .\runtime\drivers\berniw\4\default.xml

if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\5\*.* call .\create_dir .\runtime\drivers\berniw\5
if exist .\src\drivers\berniw\5\car3-trb1.rgb copy .\src\drivers\berniw\5\car3-trb1.rgb .\runtime\drivers\berniw\5\car3-trb1.rgb
if exist .\src\drivers\berniw\5\default.xml copy .\src\drivers\berniw\5\default.xml .\runtime\drivers\berniw\5\default.xml

if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\6\*.* call .\create_dir .\runtime\drivers\berniw\6
if exist .\src\drivers\berniw\6\car4-trb1.rgb copy .\src\drivers\berniw\6\car4-trb1.rgb .\runtime\drivers\berniw\6\car4-trb1.rgb
if exist .\src\drivers\berniw\6\default.xml copy .\src\drivers\berniw\6\default.xml .\runtime\drivers\berniw\6\default.xml

if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\7\*.* call .\create_dir .\runtime\drivers\berniw\7
if exist .\src\drivers\berniw\7\car5-trb1.rgb copy .\src\drivers\berniw\7\car5-trb1.rgb .\runtime\drivers\berniw\7\car5-trb1.rgb
if exist .\src\drivers\berniw\7\default.xml copy .\src\drivers\berniw\7\default.xml .\runtime\drivers\berniw\7\default.xml

if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\8\*.* call .\create_dir .\runtime\drivers\berniw\8
if exist .\src\drivers\berniw\8\car6-trb1.rgb copy .\src\drivers\berniw\8\car6-trb1.rgb .\runtime\drivers\berniw\8\car6-trb1.rgb
if exist .\src\drivers\berniw\8\default.xml copy .\src\drivers\berniw\8\default.xml .\runtime\drivers\berniw\8\default.xml

if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\9\*.* call .\create_dir .\runtime\drivers\berniw\9
if exist .\src\drivers\berniw\9\car7-trb1.rgb copy .\src\drivers\berniw\9\car7-trb1.rgb .\runtime\drivers\berniw\9\car7-trb1.rgb
if exist .\src\drivers\berniw\9\default.xml copy .\src\drivers\berniw\9\default.xml .\runtime\drivers\berniw\9\default.xml

if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw\*.* call .\create_dir .\runtime\drivers\berniw
if exist .\src\drivers\berniw\berniw.xml copy .\src\drivers\berniw\berniw.xml .\runtime\drivers\berniw\berniw.xml
if exist .\src\drivers\berniw\logo.rgb copy .\src\drivers\berniw\logo.rgb .\runtime\drivers\berniw\logo.rgb

if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\1\*.* call .\create_dir .\runtime\drivers\berniw2\1
if exist .\src\drivers\berniw2\1\default.xml copy .\src\drivers\berniw2\1\default.xml .\runtime\drivers\berniw2\1\default.xml

if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\10\*.* call .\create_dir .\runtime\drivers\berniw2\10
if exist .\src\drivers\berniw2\10\car1-trb3.rgb copy .\src\drivers\berniw2\10\car1-trb3.rgb .\runtime\drivers\berniw2\10\car1-trb3.rgb
if exist .\src\drivers\berniw2\10\default.xml copy .\src\drivers\berniw2\10\default.xml .\runtime\drivers\berniw2\10\default.xml

if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\2\*.* call .\create_dir .\runtime\drivers\berniw2\2
if exist .\src\drivers\berniw2\2\default.xml copy .\src\drivers\berniw2\2\default.xml .\runtime\drivers\berniw2\2\default.xml

if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\3\*.* call .\create_dir .\runtime\drivers\berniw2\3
if exist .\src\drivers\berniw2\3\default.xml copy .\src\drivers\berniw2\3\default.xml .\runtime\drivers\berniw2\3\default.xml

if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\4\*.* call .\create_dir .\runtime\drivers\berniw2\4
if exist .\src\drivers\berniw2\4\default.xml copy .\src\drivers\berniw2\4\default.xml .\runtime\drivers\berniw2\4\default.xml

if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\5\*.* call .\create_dir .\runtime\drivers\berniw2\5
if exist .\src\drivers\berniw2\5\default.xml copy .\src\drivers\berniw2\5\default.xml .\runtime\drivers\berniw2\5\default.xml

if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\6\*.* call .\create_dir .\runtime\drivers\berniw2\6
if exist .\src\drivers\berniw2\6\default.xml copy .\src\drivers\berniw2\6\default.xml .\runtime\drivers\berniw2\6\default.xml

if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\7\*.* call .\create_dir .\runtime\drivers\berniw2\7
if exist .\src\drivers\berniw2\7\car5-trb1.rgb copy .\src\drivers\berniw2\7\car5-trb1.rgb .\runtime\drivers\berniw2\7\car5-trb1.rgb
if exist .\src\drivers\berniw2\7\default.xml copy .\src\drivers\berniw2\7\default.xml .\runtime\drivers\berniw2\7\default.xml

if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\8\*.* call .\create_dir .\runtime\drivers\berniw2\8
if exist .\src\drivers\berniw2\8\car4-trb1.rgb copy .\src\drivers\berniw2\8\car4-trb1.rgb .\runtime\drivers\berniw2\8\car4-trb1.rgb
if exist .\src\drivers\berniw2\8\default.xml copy .\src\drivers\berniw2\8\default.xml .\runtime\drivers\berniw2\8\default.xml

if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\9\*.* call .\create_dir .\runtime\drivers\berniw2\9
if exist .\src\drivers\berniw2\9\car7-trb1.rgb copy .\src\drivers\berniw2\9\car7-trb1.rgb .\runtime\drivers\berniw2\9\car7-trb1.rgb
if exist .\src\drivers\berniw2\9\default.xml copy .\src\drivers\berniw2\9\default.xml .\runtime\drivers\berniw2\9\default.xml

if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw2\*.* call .\create_dir .\runtime\drivers\berniw2
if exist .\src\drivers\berniw2\berniw2.xml copy .\src\drivers\berniw2\berniw2.xml .\runtime\drivers\berniw2\berniw2.xml
if exist .\src\drivers\berniw2\logo.rgb copy .\src\drivers\berniw2\logo.rgb .\runtime\drivers\berniw2\logo.rgb

if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\1\*.* call .\create_dir .\runtime\drivers\berniw3\1
if exist .\src\drivers\berniw3\1\default.xml copy .\src\drivers\berniw3\1\default.xml .\runtime\drivers\berniw3\1\default.xml

if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\10\*.* call .\create_dir .\runtime\drivers\berniw3\10
if exist .\src\drivers\berniw3\10\default.xml copy .\src\drivers\berniw3\10\default.xml .\runtime\drivers\berniw3\10\default.xml

if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\2\*.* call .\create_dir .\runtime\drivers\berniw3\2
if exist .\src\drivers\berniw3\2\default.xml copy .\src\drivers\berniw3\2\default.xml .\runtime\drivers\berniw3\2\default.xml

if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\3\*.* call .\create_dir .\runtime\drivers\berniw3\3
if exist .\src\drivers\berniw3\3\default.xml copy .\src\drivers\berniw3\3\default.xml .\runtime\drivers\berniw3\3\default.xml

if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\4\*.* call .\create_dir .\runtime\drivers\berniw3\4
if exist .\src\drivers\berniw3\4\default.xml copy .\src\drivers\berniw3\4\default.xml .\runtime\drivers\berniw3\4\default.xml

if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\5\*.* call .\create_dir .\runtime\drivers\berniw3\5
if exist .\src\drivers\berniw3\5\default.xml copy .\src\drivers\berniw3\5\default.xml .\runtime\drivers\berniw3\5\default.xml

if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\6\*.* call .\create_dir .\runtime\drivers\berniw3\6
if exist .\src\drivers\berniw3\6\default.xml copy .\src\drivers\berniw3\6\default.xml .\runtime\drivers\berniw3\6\default.xml

if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\7\*.* call .\create_dir .\runtime\drivers\berniw3\7
if exist .\src\drivers\berniw3\7\default.xml copy .\src\drivers\berniw3\7\default.xml .\runtime\drivers\berniw3\7\default.xml

if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\8\*.* call .\create_dir .\runtime\drivers\berniw3\8
if exist .\src\drivers\berniw3\8\default.xml copy .\src\drivers\berniw3\8\default.xml .\runtime\drivers\berniw3\8\default.xml

if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\9\*.* call .\create_dir .\runtime\drivers\berniw3\9
if exist .\src\drivers\berniw3\9\default.xml copy .\src\drivers\berniw3\9\default.xml .\runtime\drivers\berniw3\9\default.xml

if exist .\src\drivers\berniw3\*.* call .\create_dir .\runtime
if exist .\src\drivers\berniw3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\berniw3\*.* call .\create_dir .\runtime\drivers\berniw3
if exist .\src\drivers\berniw3\berniw3.xml copy .\src\drivers\berniw3\berniw3.xml .\runtime\drivers\berniw3\berniw3.xml
if exist .\src\drivers\berniw3\logo.rgb copy .\src\drivers\berniw3\logo.rgb .\runtime\drivers\berniw3\logo.rgb

if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtime\drivers\bt\0
if exist .\src\drivers\bt\0\practice\*.* call .\create_dir .\runtime\drivers\bt\0\practice

if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtime\drivers\bt\0
if exist .\src\drivers\bt\0\qualifying\*.* call .\create_dir .\runtime\drivers\bt\0\qualifying

if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtime\drivers\bt\0
if exist .\src\drivers\bt\0\race\*.* call .\create_dir .\runtime\drivers\bt\0\race

if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\0\*.* call .\create_dir .\runtime\drivers\bt\0
if exist .\src\drivers\bt\0\default.xml copy .\src\drivers\bt\0\default.xml .\runtime\drivers\bt\0\default.xml
if exist .\src\drivers\bt\0\car1-stock1.rgb copy .\src\drivers\bt\0\car1-stock1.rgb .\runtime\drivers\bt\0\car1-stock1.rgb

if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtime\drivers\bt\1
if exist .\src\drivers\bt\1\practice\*.* call .\create_dir .\runtime\drivers\bt\1\practice

if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtime\drivers\bt\1
if exist .\src\drivers\bt\1\qualifying\*.* call .\create_dir .\runtime\drivers\bt\1\qualifying

if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtime\drivers\bt\1
if exist .\src\drivers\bt\1\race\*.* call .\create_dir .\runtime\drivers\bt\1\race

if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\1\*.* call .\create_dir .\runtime\drivers\bt\1
if exist .\src\drivers\bt\1\default.xml copy .\src\drivers\bt\1\default.xml .\runtime\drivers\bt\1\default.xml
if exist .\src\drivers\bt\1\car1-stock1.rgb copy .\src\drivers\bt\1\car1-stock1.rgb .\runtime\drivers\bt\1\car1-stock1.rgb

if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\2\*.* call .\create_dir .\runtime\drivers\bt\2
if exist .\src\drivers\bt\2\car1-trb1.rgb copy .\src\drivers\bt\2\car1-trb1.rgb .\runtime\drivers\bt\2\car1-trb1.rgb
if exist .\src\drivers\bt\2\default.xml copy .\src\drivers\bt\2\default.xml .\runtime\drivers\bt\2\default.xml

if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\3\*.* call .\create_dir .\runtime\drivers\bt\3
if exist .\src\drivers\bt\3\car2-trb1.rgb copy .\src\drivers\bt\3\car2-trb1.rgb .\runtime\drivers\bt\3\car2-trb1.rgb
if exist .\src\drivers\bt\3\default.xml copy .\src\drivers\bt\3\default.xml .\runtime\drivers\bt\3\default.xml

if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\4\*.* call .\create_dir .\runtime\drivers\bt\4
if exist .\src\drivers\bt\4\car3-trb1.rgb copy .\src\drivers\bt\4\car3-trb1.rgb .\runtime\drivers\bt\4\car3-trb1.rgb
if exist .\src\drivers\bt\4\default.xml copy .\src\drivers\bt\4\default.xml .\runtime\drivers\bt\4\default.xml

if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\5\*.* call .\create_dir .\runtime\drivers\bt\5
if exist .\src\drivers\bt\5\car4-trb1.rgb copy .\src\drivers\bt\5\car4-trb1.rgb .\runtime\drivers\bt\5\car4-trb1.rgb
if exist .\src\drivers\bt\5\default.xml copy .\src\drivers\bt\5\default.xml .\runtime\drivers\bt\5\default.xml

if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\6\*.* call .\create_dir .\runtime\drivers\bt\6
if exist .\src\drivers\bt\6\car5-trb1.rgb copy .\src\drivers\bt\6\car5-trb1.rgb .\runtime\drivers\bt\6\car5-trb1.rgb
if exist .\src\drivers\bt\6\default.xml copy .\src\drivers\bt\6\default.xml .\runtime\drivers\bt\6\default.xml

if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\7\*.* call .\create_dir .\runtime\drivers\bt\7
if exist .\src\drivers\bt\7\car6-trb1.rgb copy .\src\drivers\bt\7\car6-trb1.rgb .\runtime\drivers\bt\7\car6-trb1.rgb
if exist .\src\drivers\bt\7\default.xml copy .\src\drivers\bt\7\default.xml .\runtime\drivers\bt\7\default.xml

if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\8\*.* call .\create_dir .\runtime\drivers\bt\8
if exist .\src\drivers\bt\8\car7-trb1.rgb copy .\src\drivers\bt\8\car7-trb1.rgb .\runtime\drivers\bt\8\car7-trb1.rgb
if exist .\src\drivers\bt\8\default.xml copy .\src\drivers\bt\8\default.xml .\runtime\drivers\bt\8\default.xml

if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\9\*.* call .\create_dir .\runtime\drivers\bt\9
if exist .\src\drivers\bt\9\default.xml copy .\src\drivers\bt\9\default.xml .\runtime\drivers\bt\9\default.xml

if exist .\src\drivers\bt\*.* call .\create_dir .\runtime
if exist .\src\drivers\bt\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\bt\*.* call .\create_dir .\runtime\drivers\bt
if exist .\src\drivers\bt\bt.xml copy .\src\drivers\bt\bt.xml .\runtime\drivers\bt\bt.xml
if exist .\src\drivers\bt\logo.rgb copy .\src\drivers\bt\logo.rgb .\runtime\drivers\bt\logo.rgb

if exist .\src\drivers\damned\0\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\0\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\0\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\0\*.* call .\create_dir .\runtime\drivers\damned\0
if exist .\src\drivers\damned\0\default.xml copy .\src\drivers\damned\0\default.xml .\runtime\drivers\damned\0\default.xml

if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\1\*.* call .\create_dir .\runtime\drivers\damned\1
if exist .\src\drivers\damned\1\default.xml copy .\src\drivers\damned\1\default.xml .\runtime\drivers\damned\1\default.xml

if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\2\*.* call .\create_dir .\runtime\drivers\damned\2
if exist .\src\drivers\damned\2\default.xml copy .\src\drivers\damned\2\default.xml .\runtime\drivers\damned\2\default.xml

if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\3\*.* call .\create_dir .\runtime\drivers\damned\3
if exist .\src\drivers\damned\3\default.xml copy .\src\drivers\damned\3\default.xml .\runtime\drivers\damned\3\default.xml

if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\4\*.* call .\create_dir .\runtime\drivers\damned\4
if exist .\src\drivers\damned\4\default.xml copy .\src\drivers\damned\4\default.xml .\runtime\drivers\damned\4\default.xml

if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\5\*.* call .\create_dir .\runtime\drivers\damned\5
if exist .\src\drivers\damned\5\default.xml copy .\src\drivers\damned\5\default.xml .\runtime\drivers\damned\5\default.xml

if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\6\*.* call .\create_dir .\runtime\drivers\damned\6
if exist .\src\drivers\damned\6\car5-trb1.rgb copy .\src\drivers\damned\6\car5-trb1.rgb .\runtime\drivers\damned\6\car5-trb1.rgb
if exist .\src\drivers\damned\6\default.xml copy .\src\drivers\damned\6\default.xml .\runtime\drivers\damned\6\default.xml

if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\7\*.* call .\create_dir .\runtime\drivers\damned\7
if exist .\src\drivers\damned\7\car6-trb1.rgb copy .\src\drivers\damned\7\car6-trb1.rgb .\runtime\drivers\damned\7\car6-trb1.rgb
if exist .\src\drivers\damned\7\default.xml copy .\src\drivers\damned\7\default.xml .\runtime\drivers\damned\7\default.xml

if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\8\*.* call .\create_dir .\runtime\drivers\damned\8
if exist .\src\drivers\damned\8\car7-trb1.rgb copy .\src\drivers\damned\8\car7-trb1.rgb .\runtime\drivers\damned\8\car7-trb1.rgb
if exist .\src\drivers\damned\8\default.xml copy .\src\drivers\damned\8\default.xml .\runtime\drivers\damned\8\default.xml

if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\9\*.* call .\create_dir .\runtime\drivers\damned\9
if exist .\src\drivers\damned\9\car1-trb3.rgb copy .\src\drivers\damned\9\car1-trb3.rgb .\runtime\drivers\damned\9\car1-trb3.rgb
if exist .\src\drivers\damned\9\default.xml copy .\src\drivers\damned\9\default.xml .\runtime\drivers\damned\9\default.xml

if exist .\src\drivers\damned\*.* call .\create_dir .\runtime
if exist .\src\drivers\damned\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\damned\*.* call .\create_dir .\runtime\drivers\damned
if exist .\src\drivers\damned\damned.xml copy .\src\drivers\damned\damned.xml .\runtime\drivers\damned\damned.xml
if exist .\src\drivers\damned\logo.rgb copy .\src\drivers\damned\logo.rgb .\runtime\drivers\damned\logo.rgb

if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human\tracks
if exist .\src\drivers\human\tracks\dirt-2\*.* call .\create_dir .\runtime\drivers\human\tracks\dirt-2
if exist .\src\drivers\human\tracks\dirt-2\car-pw-206wrc.xml copy .\src\drivers\human\tracks\dirt-2\car-pw-206wrc.xml .\runtime\drivers\human\tracks\dirt-2\car-pw-206wrc.xml

if exist .\src\drivers\human\*.* call .\create_dir .\runtime
if exist .\src\drivers\human\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\human\*.* call .\create_dir .\runtime\drivers\human
if exist .\src\drivers\human\car.xml copy .\src\drivers\human\car.xml .\runtime\drivers\human\car.xml
if exist .\src\drivers\human\human.xml copy .\src\drivers\human\human.xml .\runtime\drivers\human\human.xml
if exist .\src\drivers\human\preferences.xml copy .\src\drivers\human\preferences.xml .\runtime\drivers\human\preferences.xml
if exist .\src\drivers\human\logo.rgb copy .\src\drivers\human\logo.rgb .\runtime\drivers\human\logo.rgb

if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\1\*.* call .\create_dir .\runtime\drivers\inferno\1
if exist .\src\drivers\inferno\1\default.xml copy .\src\drivers\inferno\1\default.xml .\runtime\drivers\inferno\1\default.xml

if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\10\*.* call .\create_dir .\runtime\drivers\inferno\10
if exist .\src\drivers\inferno\10\car1-trb3.rgb copy .\src\drivers\inferno\10\car1-trb3.rgb .\runtime\drivers\inferno\10\car1-trb3.rgb
if exist .\src\drivers\inferno\10\default.xml copy .\src\drivers\inferno\10\default.xml .\runtime\drivers\inferno\10\default.xml

if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\2\*.* call .\create_dir .\runtime\drivers\inferno\2
if exist .\src\drivers\inferno\2\p406.rgb copy .\src\drivers\inferno\2\p406.rgb .\runtime\drivers\inferno\2\p406.rgb
if exist .\src\drivers\inferno\2\default.xml copy .\src\drivers\inferno\2\default.xml .\runtime\drivers\inferno\2\default.xml

if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\3\*.* call .\create_dir .\runtime\drivers\inferno\3
if exist .\src\drivers\inferno\3\car1-trb1.rgb copy .\src\drivers\inferno\3\car1-trb1.rgb .\runtime\drivers\inferno\3\car1-trb1.rgb
if exist .\src\drivers\inferno\3\default.xml copy .\src\drivers\inferno\3\default.xml .\runtime\drivers\inferno\3\default.xml

if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\4\*.* call .\create_dir .\runtime\drivers\inferno\4
if exist .\src\drivers\inferno\4\car2-trb1.rgb copy .\src\drivers\inferno\4\car2-trb1.rgb .\runtime\drivers\inferno\4\car2-trb1.rgb
if exist .\src\drivers\inferno\4\default.xml copy .\src\drivers\inferno\4\default.xml .\runtime\drivers\inferno\4\default.xml

if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\5\*.* call .\create_dir .\runtime\drivers\inferno\5
if exist .\src\drivers\inferno\5\car3-trb1.rgb copy .\src\drivers\inferno\5\car3-trb1.rgb .\runtime\drivers\inferno\5\car3-trb1.rgb
if exist .\src\drivers\inferno\5\default.xml copy .\src\drivers\inferno\5\default.xml .\runtime\drivers\inferno\5\default.xml

if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\6\*.* call .\create_dir .\runtime\drivers\inferno\6
if exist .\src\drivers\inferno\6\car4-trb1.rgb copy .\src\drivers\inferno\6\car4-trb1.rgb .\runtime\drivers\inferno\6\car4-trb1.rgb
if exist .\src\drivers\inferno\6\default.xml copy .\src\drivers\inferno\6\default.xml .\runtime\drivers\inferno\6\default.xml

if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\7\*.* call .\create_dir .\runtime\drivers\inferno\7
if exist .\src\drivers\inferno\7\car5-trb1.rgb copy .\src\drivers\inferno\7\car5-trb1.rgb .\runtime\drivers\inferno\7\car5-trb1.rgb
if exist .\src\drivers\inferno\7\default.xml copy .\src\drivers\inferno\7\default.xml .\runtime\drivers\inferno\7\default.xml

if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\8\*.* call .\create_dir .\runtime\drivers\inferno\8
if exist .\src\drivers\inferno\8\car6-trb1.rgb copy .\src\drivers\inferno\8\car6-trb1.rgb .\runtime\drivers\inferno\8\car6-trb1.rgb
if exist .\src\drivers\inferno\8\default.xml copy .\src\drivers\inferno\8\default.xml .\runtime\drivers\inferno\8\default.xml

if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\9\*.* call .\create_dir .\runtime\drivers\inferno\9
if exist .\src\drivers\inferno\9\car7-trb1.rgb copy .\src\drivers\inferno\9\car7-trb1.rgb .\runtime\drivers\inferno\9\car7-trb1.rgb
if exist .\src\drivers\inferno\9\default.xml copy .\src\drivers\inferno\9\default.xml .\runtime\drivers\inferno\9\default.xml

if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno\*.* call .\create_dir .\runtime\drivers\inferno
if exist .\src\drivers\inferno\inferno.xml copy .\src\drivers\inferno\inferno.xml .\runtime\drivers\inferno\inferno.xml
if exist .\src\drivers\inferno\logo.rgb copy .\src\drivers\inferno\logo.rgb .\runtime\drivers\inferno\logo.rgb

if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\1\*.* call .\create_dir .\runtime\drivers\inferno2\1
if exist .\src\drivers\inferno2\1\defaultcar.xml copy .\src\drivers\inferno2\1\defaultcar.xml .\runtime\drivers\inferno2\1\defaultcar.xml
if exist .\src\drivers\inferno2\1\default.xml copy .\src\drivers\inferno2\1\default.xml .\runtime\drivers\inferno2\1\default.xml
if exist .\src\drivers\inferno2\1\Makefile copy .\src\drivers\inferno2\1\Makefile .\runtime\drivers\inferno2\1\Makefile

if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\10\*.* call .\create_dir .\runtime\drivers\inferno2\10
if exist .\src\drivers\inferno2\10\defaultcar.xml copy .\src\drivers\inferno2\10\defaultcar.xml .\runtime\drivers\inferno2\10\defaultcar.xml
if exist .\src\drivers\inferno2\10\default.xml copy .\src\drivers\inferno2\10\default.xml .\runtime\drivers\inferno2\10\default.xml
if exist .\src\drivers\inferno2\10\Makefile copy .\src\drivers\inferno2\10\Makefile .\runtime\drivers\inferno2\10\Makefile

if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\2\*.* call .\create_dir .\runtime\drivers\inferno2\2
if exist .\src\drivers\inferno2\2\defaultcar.xml copy .\src\drivers\inferno2\2\defaultcar.xml .\runtime\drivers\inferno2\2\defaultcar.xml
if exist .\src\drivers\inferno2\2\default.xml copy .\src\drivers\inferno2\2\default.xml .\runtime\drivers\inferno2\2\default.xml
if exist .\src\drivers\inferno2\2\Makefile copy .\src\drivers\inferno2\2\Makefile .\runtime\drivers\inferno2\2\Makefile

if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\3\*.* call .\create_dir .\runtime\drivers\inferno2\3
if exist .\src\drivers\inferno2\3\defaultcar.xml copy .\src\drivers\inferno2\3\defaultcar.xml .\runtime\drivers\inferno2\3\defaultcar.xml
if exist .\src\drivers\inferno2\3\default.xml copy .\src\drivers\inferno2\3\default.xml .\runtime\drivers\inferno2\3\default.xml
if exist .\src\drivers\inferno2\3\Makefile copy .\src\drivers\inferno2\3\Makefile .\runtime\drivers\inferno2\3\Makefile

if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\4\*.* call .\create_dir .\runtime\drivers\inferno2\4
if exist .\src\drivers\inferno2\4\defaultcar.xml copy .\src\drivers\inferno2\4\defaultcar.xml .\runtime\drivers\inferno2\4\defaultcar.xml
if exist .\src\drivers\inferno2\4\default.xml copy .\src\drivers\inferno2\4\default.xml .\runtime\drivers\inferno2\4\default.xml
if exist .\src\drivers\inferno2\4\Makefile copy .\src\drivers\inferno2\4\Makefile .\runtime\drivers\inferno2\4\Makefile

if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\5\*.* call .\create_dir .\runtime\drivers\inferno2\5
if exist .\src\drivers\inferno2\5\defaultcar.xml copy .\src\drivers\inferno2\5\defaultcar.xml .\runtime\drivers\inferno2\5\defaultcar.xml
if exist .\src\drivers\inferno2\5\default.xml copy .\src\drivers\inferno2\5\default.xml .\runtime\drivers\inferno2\5\default.xml
if exist .\src\drivers\inferno2\5\Makefile copy .\src\drivers\inferno2\5\Makefile .\runtime\drivers\inferno2\5\Makefile

if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\6\*.* call .\create_dir .\runtime\drivers\inferno2\6
if exist .\src\drivers\inferno2\6\defaultcar.xml copy .\src\drivers\inferno2\6\defaultcar.xml .\runtime\drivers\inferno2\6\defaultcar.xml
if exist .\src\drivers\inferno2\6\default.xml copy .\src\drivers\inferno2\6\default.xml .\runtime\drivers\inferno2\6\default.xml
if exist .\src\drivers\inferno2\6\Makefile copy .\src\drivers\inferno2\6\Makefile .\runtime\drivers\inferno2\6\Makefile

if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\7\*.* call .\create_dir .\runtime\drivers\inferno2\7
if exist .\src\drivers\inferno2\7\defaultcar.xml copy .\src\drivers\inferno2\7\defaultcar.xml .\runtime\drivers\inferno2\7\defaultcar.xml
if exist .\src\drivers\inferno2\7\default.xml copy .\src\drivers\inferno2\7\default.xml .\runtime\drivers\inferno2\7\default.xml
if exist .\src\drivers\inferno2\7\Makefile copy .\src\drivers\inferno2\7\Makefile .\runtime\drivers\inferno2\7\Makefile

if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\8\*.* call .\create_dir .\runtime\drivers\inferno2\8
if exist .\src\drivers\inferno2\8\defaultcar.xml copy .\src\drivers\inferno2\8\defaultcar.xml .\runtime\drivers\inferno2\8\defaultcar.xml
if exist .\src\drivers\inferno2\8\default.xml copy .\src\drivers\inferno2\8\default.xml .\runtime\drivers\inferno2\8\default.xml
if exist .\src\drivers\inferno2\8\Makefile copy .\src\drivers\inferno2\8\Makefile .\runtime\drivers\inferno2\8\Makefile

if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\9\*.* call .\create_dir .\runtime\drivers\inferno2\9
if exist .\src\drivers\inferno2\9\defaultcar.xml copy .\src\drivers\inferno2\9\defaultcar.xml .\runtime\drivers\inferno2\9\defaultcar.xml
if exist .\src\drivers\inferno2\9\default.xml copy .\src\drivers\inferno2\9\default.xml .\runtime\drivers\inferno2\9\default.xml
if exist .\src\drivers\inferno2\9\Makefile copy .\src\drivers\inferno2\9\Makefile .\runtime\drivers\inferno2\9\Makefile

if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime
if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\inferno2\*.* call .\create_dir .\runtime\drivers\inferno2
if exist .\src\drivers\inferno2\inferno2.xml copy .\src\drivers\inferno2\inferno2.xml .\runtime\drivers\inferno2\inferno2.xml
if exist .\src\drivers\inferno2\logo.rgb copy .\src\drivers\inferno2\logo.rgb .\runtime\drivers\inferno2\logo.rgb

if exist .\src\drivers\lliaw\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\1\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\1\*.* call .\create_dir .\runtime\drivers\lliaw\1
if exist .\src\drivers\lliaw\1\default.xml copy .\src\drivers\lliaw\1\default.xml .\runtime\drivers\lliaw\1\default.xml

if exist .\src\drivers\lliaw\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\10\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\10\*.* call .\create_dir .\runtime\drivers\lliaw\10
if exist .\src\drivers\lliaw\10\default.xml copy .\src\drivers\lliaw\10\default.xml .\runtime\drivers\lliaw\10\default.xml

if exist .\src\drivers\lliaw\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\2\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\2\*.* call .\create_dir .\runtime\drivers\lliaw\2
if exist .\src\drivers\lliaw\2\default.xml copy .\src\drivers\lliaw\2\default.xml .\runtime\drivers\lliaw\2\default.xml

if exist .\src\drivers\lliaw\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\3\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\3\*.* call .\create_dir .\runtime\drivers\lliaw\3
if exist .\src\drivers\lliaw\3\car1-trb1.rgb copy .\src\drivers\lliaw\3\car1-trb1.rgb .\runtime\drivers\lliaw\3\car1-trb1.rgb
if exist .\src\drivers\lliaw\3\default.xml copy .\src\drivers\lliaw\3\default.xml .\runtime\drivers\lliaw\3\default.xml

if exist .\src\drivers\lliaw\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\4\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\4\*.* call .\create_dir .\runtime\drivers\lliaw\4
if exist .\src\drivers\lliaw\4\car2-trb1.rgb copy .\src\drivers\lliaw\4\car2-trb1.rgb .\runtime\drivers\lliaw\4\car2-trb1.rgb
if exist .\src\drivers\lliaw\4\default.xml copy .\src\drivers\lliaw\4\default.xml .\runtime\drivers\lliaw\4\default.xml

if exist .\src\drivers\lliaw\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\5\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\5\*.* call .\create_dir .\runtime\drivers\lliaw\5
if exist .\src\drivers\lliaw\5\car3-trb1.rgb copy .\src\drivers\lliaw\5\car3-trb1.rgb .\runtime\drivers\lliaw\5\car3-trb1.rgb
if exist .\src\drivers\lliaw\5\default.xml copy .\src\drivers\lliaw\5\default.xml .\runtime\drivers\lliaw\5\default.xml

if exist .\src\drivers\lliaw\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\6\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\6\*.* call .\create_dir .\runtime\drivers\lliaw\6
if exist .\src\drivers\lliaw\6\car4-trb1.rgb copy .\src\drivers\lliaw\6\car4-trb1.rgb .\runtime\drivers\lliaw\6\car4-trb1.rgb
if exist .\src\drivers\lliaw\6\default.xml copy .\src\drivers\lliaw\6\default.xml .\runtime\drivers\lliaw\6\default.xml

if exist .\src\drivers\lliaw\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\7\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\7\*.* call .\create_dir .\runtime\drivers\lliaw\7
if exist .\src\drivers\lliaw\7\car5-trb1.rgb copy .\src\drivers\lliaw\7\car5-trb1.rgb .\runtime\drivers\lliaw\7\car5-trb1.rgb
if exist .\src\drivers\lliaw\7\default.xml copy .\src\drivers\lliaw\7\default.xml .\runtime\drivers\lliaw\7\default.xml

if exist .\src\drivers\lliaw\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\8\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\8\*.* call .\create_dir .\runtime\drivers\lliaw\8
if exist .\src\drivers\lliaw\8\car6-trb1.rgb copy .\src\drivers\lliaw\8\car6-trb1.rgb .\runtime\drivers\lliaw\8\car6-trb1.rgb
if exist .\src\drivers\lliaw\8\default.xml copy .\src\drivers\lliaw\8\default.xml .\runtime\drivers\lliaw\8\default.xml

if exist .\src\drivers\lliaw\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\9\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\9\*.* call .\create_dir .\runtime\drivers\lliaw\9
if exist .\src\drivers\lliaw\9\car7-trb1.rgb copy .\src\drivers\lliaw\9\car7-trb1.rgb .\runtime\drivers\lliaw\9\car7-trb1.rgb
if exist .\src\drivers\lliaw\9\default.xml copy .\src\drivers\lliaw\9\default.xml .\runtime\drivers\lliaw\9\default.xml

if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime
if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\lliaw\*.* call .\create_dir .\runtime\drivers\lliaw
if exist .\src\drivers\lliaw\lliaw.xml copy .\src\drivers\lliaw\lliaw.xml .\runtime\drivers\lliaw\lliaw.xml
if exist .\src\drivers\lliaw\logo.rgb copy .\src\drivers\lliaw\logo.rgb .\runtime\drivers\lliaw\logo.rgb

if exist .\src\drivers\olethros\0\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\0\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\0\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\0\*.* call .\create_dir .\runtime\drivers\olethros\0
if exist .\src\drivers\olethros\0\default.xml copy .\src\drivers\olethros\0\default.xml .\runtime\drivers\olethros\0\default.xml

if exist .\src\drivers\olethros\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\1\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\1\*.* call .\create_dir .\runtime\drivers\olethros\1
if exist .\src\drivers\olethros\1\default.xml copy .\src\drivers\olethros\1\default.xml .\runtime\drivers\olethros\1\default.xml

if exist .\src\drivers\olethros\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\2\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\2\*.* call .\create_dir .\runtime\drivers\olethros\2
if exist .\src\drivers\olethros\2\car1-trb1.rgb copy .\src\drivers\olethros\2\car1-trb1.rgb .\runtime\drivers\olethros\2\car1-trb1.rgb
if exist .\src\drivers\olethros\2\default.xml copy .\src\drivers\olethros\2\default.xml .\runtime\drivers\olethros\2\default.xml

if exist .\src\drivers\olethros\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\3\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\3\*.* call .\create_dir .\runtime\drivers\olethros\3
if exist .\src\drivers\olethros\3\car2-trb1.rgb copy .\src\drivers\olethros\3\car2-trb1.rgb .\runtime\drivers\olethros\3\car2-trb1.rgb
if exist .\src\drivers\olethros\3\default.xml copy .\src\drivers\olethros\3\default.xml .\runtime\drivers\olethros\3\default.xml

if exist .\src\drivers\olethros\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\4\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\4\*.* call .\create_dir .\runtime\drivers\olethros\4
if exist .\src\drivers\olethros\4\car3-trb1.rgb copy .\src\drivers\olethros\4\car3-trb1.rgb .\runtime\drivers\olethros\4\car3-trb1.rgb
if exist .\src\drivers\olethros\4\default.xml copy .\src\drivers\olethros\4\default.xml .\runtime\drivers\olethros\4\default.xml

if exist .\src\drivers\olethros\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\5\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\5\*.* call .\create_dir .\runtime\drivers\olethros\5
if exist .\src\drivers\olethros\5\car4-trb1.rgb copy .\src\drivers\olethros\5\car4-trb1.rgb .\runtime\drivers\olethros\5\car4-trb1.rgb
if exist .\src\drivers\olethros\5\default.xml copy .\src\drivers\olethros\5\default.xml .\runtime\drivers\olethros\5\default.xml

if exist .\src\drivers\olethros\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\6\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\6\*.* call .\create_dir .\runtime\drivers\olethros\6
if exist .\src\drivers\olethros\6\car5-trb1.rgb copy .\src\drivers\olethros\6\car5-trb1.rgb .\runtime\drivers\olethros\6\car5-trb1.rgb
if exist .\src\drivers\olethros\6\default.xml copy .\src\drivers\olethros\6\default.xml .\runtime\drivers\olethros\6\default.xml

if exist .\src\drivers\olethros\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\7\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\7\*.* call .\create_dir .\runtime\drivers\olethros\7
if exist .\src\drivers\olethros\7\car6-trb1.rgb copy .\src\drivers\olethros\7\car6-trb1.rgb .\runtime\drivers\olethros\7\car6-trb1.rgb
if exist .\src\drivers\olethros\7\default.xml copy .\src\drivers\olethros\7\default.xml .\runtime\drivers\olethros\7\default.xml

if exist .\src\drivers\olethros\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\8\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\8\*.* call .\create_dir .\runtime\drivers\olethros\8
if exist .\src\drivers\olethros\8\car7-trb1.rgb copy .\src\drivers\olethros\8\car7-trb1.rgb .\runtime\drivers\olethros\8\car7-trb1.rgb
if exist .\src\drivers\olethros\8\default.xml copy .\src\drivers\olethros\8\default.xml .\runtime\drivers\olethros\8\default.xml

if exist .\src\drivers\olethros\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\9\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\9\*.* call .\create_dir .\runtime\drivers\olethros\9
if exist .\src\drivers\olethros\9\default.xml copy .\src\drivers\olethros\9\default.xml .\runtime\drivers\olethros\9\default.xml
if exist .\src\drivers\olethros\9\car1-trb3.rgb copy .\src\drivers\olethros\9\car1-trb3.rgb .\runtime\drivers\olethros\9\car1-trb3.rgb

if exist .\src\drivers\olethros\*.* call .\create_dir .\runtime
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\olethros\*.* call .\create_dir .\runtime\drivers\olethros
if exist .\src\drivers\olethros\olethros.xml copy .\src\drivers\olethros\olethros.xml .\runtime\drivers\olethros\olethros.xml
if exist .\src\drivers\olethros\logo.rgb copy .\src\drivers\olethros\logo.rgb .\runtime\drivers\olethros\logo.rgb

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

if exist .\src\drivers\tita\1\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\1\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\1\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\1\*.* call .\create_dir .\runtime\drivers\tita\1
if exist .\src\drivers\tita\1\default.xml copy .\src\drivers\tita\1\default.xml .\runtime\drivers\tita\1\default.xml

if exist .\src\drivers\tita\10\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\10\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\10\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\10\*.* call .\create_dir .\runtime\drivers\tita\10
if exist .\src\drivers\tita\10\default.xml copy .\src\drivers\tita\10\default.xml .\runtime\drivers\tita\10\default.xml

if exist .\src\drivers\tita\2\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\2\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\2\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\2\*.* call .\create_dir .\runtime\drivers\tita\2
if exist .\src\drivers\tita\2\default.xml copy .\src\drivers\tita\2\default.xml .\runtime\drivers\tita\2\default.xml

if exist .\src\drivers\tita\3\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\3\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\3\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\3\*.* call .\create_dir .\runtime\drivers\tita\3
if exist .\src\drivers\tita\3\car1-trb1.rgb copy .\src\drivers\tita\3\car1-trb1.rgb .\runtime\drivers\tita\3\car1-trb1.rgb
if exist .\src\drivers\tita\3\default.xml copy .\src\drivers\tita\3\default.xml .\runtime\drivers\tita\3\default.xml

if exist .\src\drivers\tita\4\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\4\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\4\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\4\*.* call .\create_dir .\runtime\drivers\tita\4
if exist .\src\drivers\tita\4\car2-trb1.rgb copy .\src\drivers\tita\4\car2-trb1.rgb .\runtime\drivers\tita\4\car2-trb1.rgb
if exist .\src\drivers\tita\4\default.xml copy .\src\drivers\tita\4\default.xml .\runtime\drivers\tita\4\default.xml

if exist .\src\drivers\tita\5\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\5\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\5\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\5\*.* call .\create_dir .\runtime\drivers\tita\5
if exist .\src\drivers\tita\5\car3-trb1.rgb copy .\src\drivers\tita\5\car3-trb1.rgb .\runtime\drivers\tita\5\car3-trb1.rgb
if exist .\src\drivers\tita\5\default.xml copy .\src\drivers\tita\5\default.xml .\runtime\drivers\tita\5\default.xml

if exist .\src\drivers\tita\6\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\6\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\6\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\6\*.* call .\create_dir .\runtime\drivers\tita\6
if exist .\src\drivers\tita\6\car4-trb1.rgb copy .\src\drivers\tita\6\car4-trb1.rgb .\runtime\drivers\tita\6\car4-trb1.rgb
if exist .\src\drivers\tita\6\default.xml copy .\src\drivers\tita\6\default.xml .\runtime\drivers\tita\6\default.xml

if exist .\src\drivers\tita\7\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\7\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\7\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\7\*.* call .\create_dir .\runtime\drivers\tita\7
if exist .\src\drivers\tita\7\car5-trb1.rgb copy .\src\drivers\tita\7\car5-trb1.rgb .\runtime\drivers\tita\7\car5-trb1.rgb
if exist .\src\drivers\tita\7\default.xml copy .\src\drivers\tita\7\default.xml .\runtime\drivers\tita\7\default.xml

if exist .\src\drivers\tita\8\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\8\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\8\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\8\*.* call .\create_dir .\runtime\drivers\tita\8
if exist .\src\drivers\tita\8\car6-trb1.rgb copy .\src\drivers\tita\8\car6-trb1.rgb .\runtime\drivers\tita\8\car6-trb1.rgb
if exist .\src\drivers\tita\8\default.xml copy .\src\drivers\tita\8\default.xml .\runtime\drivers\tita\8\default.xml

if exist .\src\drivers\tita\9\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\9\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\9\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\9\*.* call .\create_dir .\runtime\drivers\tita\9
if exist .\src\drivers\tita\9\car7-trb1.rgb copy .\src\drivers\tita\9\car7-trb1.rgb .\runtime\drivers\tita\9\car7-trb1.rgb
if exist .\src\drivers\tita\9\default.xml copy .\src\drivers\tita\9\default.xml .\runtime\drivers\tita\9\default.xml

if exist .\src\drivers\tita\*.* call .\create_dir .\runtime
if exist .\src\drivers\tita\*.* call .\create_dir .\runtime\drivers
if exist .\src\drivers\tita\*.* call .\create_dir .\runtime\drivers\tita
if exist .\src\drivers\tita\tita.xml copy .\src\drivers\tita\tita.xml .\runtime\drivers\tita\tita.xml
if exist .\src\drivers\tita\logo.rgb copy .\src\drivers\tita\logo.rgb .\runtime\drivers\tita\logo.rgb

if exist .\src\libs\raceengineclient\*.* call .\create_dir .\runtime
if exist .\src\libs\raceengineclient\*.* call .\create_dir .\runtime\config
if exist .\src\libs\raceengineclient\raceengine.xml copy .\src\libs\raceengineclient\raceengine.xml .\runtime\config\raceengine.xml
if exist .\src\libs\raceengineclient\style.xsl copy .\src\libs\raceengineclient\style.xsl .\runtime\config\style.xsl

if exist .\src\libs\tgf\*.* call .\create_dir .\runtime
if exist .\src\libs\tgf\*.* call .\create_dir .\runtime\config
if exist .\src\libs\tgf\params.dtd copy .\src\libs\tgf\params.dtd .\runtime\config\params.dtd

if exist .\src\libs\tgfclient\*.* call .\create_dir .\runtime
if exist .\src\libs\tgfclient\*.* call .\create_dir .\runtime\config
if exist .\src\libs\tgfclient\screen.xml copy .\src\libs\tgfclient\screen.xml .\runtime\config\screen.xml

if exist .\src\modules\graphic\ssggraph\*.* call .\create_dir .\runtime
if exist .\src\modules\graphic\ssggraph\*.* call .\create_dir .\runtime\config
if exist .\src\modules\graphic\ssggraph\graph.xml copy .\src\modules\graphic\ssggraph\graph.xml .\runtime\config\graph.xml
if exist .\src\modules\graphic\ssggraph\sound.xml copy .\src\modules\graphic\ssggraph\sound.xml .\runtime\config\sound.xml

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
call .\create_dir .\runtime\drivers\berniw

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\berniw2

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\berniw3

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\bt

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
call .\create_dir .\runtime\drivers\lliaw

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\olethros

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\sparkle

call .\create_dir .\runtime
call .\create_dir .\runtime\drivers
call .\create_dir .\runtime\drivers\tita

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
