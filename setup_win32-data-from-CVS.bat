@echo off


if exist .\data\cars\categories\free\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\free\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\free\free.xml copy .\data\cars\categories\free\free.xml .\runtime\categories\free.xml

if exist .\data\cars\categories\Historic\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\Historic\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\Historic\Historic.xml copy .\data\cars\categories\Historic\Historic.xml .\runtime\categories\Historic.xml

if exist .\data\cars\categories\Nascar\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\Nascar\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\Nascar\Nascar.xml copy .\data\cars\categories\Nascar\Nascar.xml .\runtime\categories\Nascar.xml

if exist .\data\cars\categories\Offroad-4WD-GrA\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\Offroad-4WD-GrA\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\Offroad-4WD-GrA\Offroad-4WD-GrA.xml copy .\data\cars\categories\Offroad-4WD-GrA\Offroad-4WD-GrA.xml .\runtime\categories\Offroad-4WD-GrA.xml

if exist .\data\cars\categories\Offroad-RWD-GrA\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\Offroad-RWD-GrA\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\Offroad-RWD-GrA\Offroad-RWD-GrA.xml copy .\data\cars\categories\Offroad-RWD-GrA\Offroad-RWD-GrA.xml .\runtime\categories\Offroad-RWD-GrA.xml

if exist .\data\cars\categories\Track-4WD-GrB\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\Track-4WD-GrB\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\Track-4WD-GrB\Track-4WD-GrB.xml copy .\data\cars\categories\Track-4WD-GrB\Track-4WD-GrB.xml .\runtime\categories\Track-4WD-GrB.xml

if exist .\data\cars\categories\Track-FWD-GrA\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\Track-FWD-GrA\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\Track-FWD-GrA\Track-FWD-GrA.xml copy .\data\cars\categories\Track-FWD-GrA\Track-FWD-GrA.xml .\runtime\categories\Track-FWD-GrA.xml

if exist .\data\cars\categories\Track-FWD-GrB\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\Track-FWD-GrB\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\Track-FWD-GrB\Track-FWD-GrB.xml copy .\data\cars\categories\Track-FWD-GrB\Track-FWD-GrB.xml .\runtime\categories\Track-FWD-GrB.xml

if exist .\data\cars\categories\Track-RWD-GrA\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\Track-RWD-GrA\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\Track-RWD-GrA\Track-RWD-GrA.xml copy .\data\cars\categories\Track-RWD-GrA\Track-RWD-GrA.xml .\runtime\categories\Track-RWD-GrA.xml

if exist .\data\cars\categories\Track-RWD-GrB\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\Track-RWD-GrB\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\Track-RWD-GrB\Track-RWD-GrB.xml copy .\data\cars\categories\Track-RWD-GrB\Track-RWD-GrB.xml .\runtime\categories\Track-RWD-GrB.xml

if exist .\data\cars\categories\Track-RWD-GrC\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\Track-RWD-GrC\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\Track-RWD-GrC\Track-RWD-GrC.xml copy .\data\cars\categories\Track-RWD-GrC\Track-RWD-GrC.xml .\runtime\categories\Track-RWD-GrC.xml

if exist .\data\cars\categories\F1\*.* call .\create_dir .\runtime
if exist .\data\cars\categories\F1\*.* call .\create_dir .\runtime\categories
if exist .\data\cars\categories\F1\F1.xml copy .\data\cars\categories\F1\F1.xml .\runtime\categories\F1.xml

if exist .\data\cars\models\155-DTM\*.* call .\create_dir .\runtime
if exist .\data\cars\models\155-DTM\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\155-DTM\*.* call .\create_dir .\runtime\cars\155-DTM
if exist .\data\cars\models\155-DTM\155-DTM.xml copy .\data\cars\models\155-DTM\155-DTM.xml .\runtime\cars\155-DTM\155-DTM.xml
if exist .\data\cars\models\155-DTM\155-DTM.rgb copy .\data\cars\models\155-DTM\155-DTM.rgb .\runtime\cars\155-DTM\155-DTM.rgb
if exist .\data\cars\models\155-DTM\tex-wheel.rgb copy .\data\cars\models\155-DTM\tex-wheel.rgb .\runtime\cars\155-DTM\tex-wheel.rgb
if exist .\data\cars\models\155-DTM\shadow.rgb copy .\data\cars\models\155-DTM\shadow.rgb .\runtime\cars\155-DTM\shadow.rgb
if exist .\data\cars\models\155-DTM\155-DTM.acc copy .\data\cars\models\155-DTM\155-DTM.acc .\runtime\cars\155-DTM\155-DTM.acc
if exist .\data\cars\models\155-DTM\155-DTM-lod1.acc copy .\data\cars\models\155-DTM\155-DTM-lod1.acc .\runtime\cars\155-DTM\155-DTM-lod1.acc
if exist .\data\cars\models\155-DTM\155-DTM-lod2.acc copy .\data\cars\models\155-DTM\155-DTM-lod2.acc .\runtime\cars\155-DTM\155-DTM-lod2.acc
if exist .\data\cars\models\155-DTM\readme.txt copy .\data\cars\models\155-DTM\readme.txt .\runtime\cars\155-DTM\readme.txt

if exist .\data\cars\models\360-modena\*.* call .\create_dir .\runtime
if exist .\data\cars\models\360-modena\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\360-modena\*.* call .\create_dir .\runtime\cars\360-modena
if exist .\data\cars\models\360-modena\360-modena.xml copy .\data\cars\models\360-modena\360-modena.xml .\runtime\cars\360-modena\360-modena.xml
if exist .\data\cars\models\360-modena\360-modena.rgb copy .\data\cars\models\360-modena\360-modena.rgb .\runtime\cars\360-modena\360-modena.rgb
if exist .\data\cars\models\360-modena\tex-wheel.rgb copy .\data\cars\models\360-modena\tex-wheel.rgb .\runtime\cars\360-modena\tex-wheel.rgb
if exist .\data\cars\models\360-modena\shadow.rgb copy .\data\cars\models\360-modena\shadow.rgb .\runtime\cars\360-modena\shadow.rgb
if exist .\data\cars\models\360-modena\360-modena.acc copy .\data\cars\models\360-modena\360-modena.acc .\runtime\cars\360-modena\360-modena.acc
if exist .\data\cars\models\360-modena\360-modena-lod1.acc copy .\data\cars\models\360-modena\360-modena-lod1.acc .\runtime\cars\360-modena\360-modena-lod1.acc
if exist .\data\cars\models\360-modena\360-modena-lod2.acc copy .\data\cars\models\360-modena\360-modena-lod2.acc .\runtime\cars\360-modena\360-modena-lod2.acc
if exist .\data\cars\models\360-modena\360-modena-lod3.acc copy .\data\cars\models\360-modena\360-modena-lod3.acc .\runtime\cars\360-modena\360-modena-lod3.acc
if exist .\data\cars\models\360-modena\readme.txt copy .\data\cars\models\360-modena\readme.txt .\runtime\cars\360-modena\readme.txt

if exist .\data\cars\models\acura-nsx-sz\*.* call .\create_dir .\runtime
if exist .\data\cars\models\acura-nsx-sz\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\acura-nsx-sz\*.* call .\create_dir .\runtime\cars\acura-nsx-sz
if exist .\data\cars\models\acura-nsx-sz\acura-nsx-sz.xml copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz.xml .\runtime\cars\acura-nsx-sz\acura-nsx-sz.xml
if exist .\data\cars\models\acura-nsx-sz\acura-nsx-sz.rgb copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz.rgb .\runtime\cars\acura-nsx-sz\acura-nsx-sz.rgb
if exist .\data\cars\models\acura-nsx-sz\tex-wheel.rgb copy .\data\cars\models\acura-nsx-sz\tex-wheel.rgb .\runtime\cars\acura-nsx-sz\tex-wheel.rgb
if exist .\data\cars\models\acura-nsx-sz\shadow.rgb copy .\data\cars\models\acura-nsx-sz\shadow.rgb .\runtime\cars\acura-nsx-sz\shadow.rgb
if exist .\data\cars\models\acura-nsx-sz\acura-nsx-sz.acc copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz.acc .\runtime\cars\acura-nsx-sz\acura-nsx-sz.acc
if exist .\data\cars\models\acura-nsx-sz\acura-nsx-sz-lod1.acc copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz-lod1.acc .\runtime\cars\acura-nsx-sz\acura-nsx-sz-lod1.acc
if exist .\data\cars\models\acura-nsx-sz\acura-nsx-sz-lod2.acc copy .\data\cars\models\acura-nsx-sz\acura-nsx-sz-lod2.acc .\runtime\cars\acura-nsx-sz\acura-nsx-sz-lod2.acc
if exist .\data\cars\models\acura-nsx-sz\readme.txt copy .\data\cars\models\acura-nsx-sz\readme.txt .\runtime\cars\acura-nsx-sz\readme.txt

if exist .\data\cars\models\baja-bug\*.* call .\create_dir .\runtime
if exist .\data\cars\models\baja-bug\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\baja-bug\*.* call .\create_dir .\runtime\cars\baja-bug
if exist .\data\cars\models\baja-bug\baja-bug.xml copy .\data\cars\models\baja-bug\baja-bug.xml .\runtime\cars\baja-bug\baja-bug.xml
if exist .\data\cars\models\baja-bug\baja-bug.rgb copy .\data\cars\models\baja-bug\baja-bug.rgb .\runtime\cars\baja-bug\baja-bug.rgb
if exist .\data\cars\models\baja-bug\tex-wheel.rgb copy .\data\cars\models\baja-bug\tex-wheel.rgb .\runtime\cars\baja-bug\tex-wheel.rgb
if exist .\data\cars\models\baja-bug\shadow.rgb copy .\data\cars\models\baja-bug\shadow.rgb .\runtime\cars\baja-bug\shadow.rgb
if exist .\data\cars\models\baja-bug\baja-bug.acc copy .\data\cars\models\baja-bug\baja-bug.acc .\runtime\cars\baja-bug\baja-bug.acc
if exist .\data\cars\models\baja-bug\baja-bug-lod1.acc copy .\data\cars\models\baja-bug\baja-bug-lod1.acc .\runtime\cars\baja-bug\baja-bug-lod1.acc
if exist .\data\cars\models\baja-bug\baja-bug-lod2.acc copy .\data\cars\models\baja-bug\baja-bug-lod2.acc .\runtime\cars\baja-bug\baja-bug-lod2.acc
if exist .\data\cars\models\baja-bug\readme.txt copy .\data\cars\models\baja-bug\readme.txt .\runtime\cars\baja-bug\readme.txt

if exist .\data\cars\models\buggy\*.* call .\create_dir .\runtime
if exist .\data\cars\models\buggy\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\buggy\*.* call .\create_dir .\runtime\cars\buggy
if exist .\data\cars\models\buggy\buggy.xml copy .\data\cars\models\buggy\buggy.xml .\runtime\cars\buggy\buggy.xml
if exist .\data\cars\models\buggy\buggy.rgb copy .\data\cars\models\buggy\buggy.rgb .\runtime\cars\buggy\buggy.rgb
if exist .\data\cars\models\buggy\tex-wheel.rgb copy .\data\cars\models\buggy\tex-wheel.rgb .\runtime\cars\buggy\tex-wheel.rgb
if exist .\data\cars\models\buggy\shadow.rgb copy .\data\cars\models\buggy\shadow.rgb .\runtime\cars\buggy\shadow.rgb
if exist .\data\cars\models\buggy\buggy.acc copy .\data\cars\models\buggy\buggy.acc .\runtime\cars\buggy\buggy.acc
if exist .\data\cars\models\buggy\buggy-lod1.acc copy .\data\cars\models\buggy\buggy-lod1.acc .\runtime\cars\buggy\buggy-lod1.acc
if exist .\data\cars\models\buggy\buggy-lod2.acc copy .\data\cars\models\buggy\buggy-lod2.acc .\runtime\cars\buggy\buggy-lod2.acc
if exist .\data\cars\models\buggy\readme.txt copy .\data\cars\models\buggy\readme.txt .\runtime\cars\buggy\readme.txt

if exist .\data\cars\models\cg-nascar-rwd\*.* call .\create_dir .\runtime
if exist .\data\cars\models\cg-nascar-rwd\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\cg-nascar-rwd\*.* call .\create_dir .\runtime\cars\cg-nascar-rwd
if exist .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.xml copy .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.xml .\runtime\cars\cg-nascar-rwd\cg-nascar-rwd.xml
if exist .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.rgb copy .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.rgb .\runtime\cars\cg-nascar-rwd\cg-nascar-rwd.rgb
if exist .\data\cars\models\cg-nascar-rwd\tex-wheel.rgb copy .\data\cars\models\cg-nascar-rwd\tex-wheel.rgb .\runtime\cars\cg-nascar-rwd\tex-wheel.rgb
if exist .\data\cars\models\cg-nascar-rwd\shadow.rgb copy .\data\cars\models\cg-nascar-rwd\shadow.rgb .\runtime\cars\cg-nascar-rwd\shadow.rgb
if exist .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.acc copy .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd.acc .\runtime\cars\cg-nascar-rwd\cg-nascar-rwd.acc
if exist .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd-lod1.acc copy .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd-lod1.acc .\runtime\cars\cg-nascar-rwd\cg-nascar-rwd-lod1.acc
if exist .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd-lod2.acc copy .\data\cars\models\cg-nascar-rwd\cg-nascar-rwd-lod2.acc .\runtime\cars\cg-nascar-rwd\cg-nascar-rwd-lod2.acc
if exist .\data\cars\models\cg-nascar-rwd\readme.txt copy .\data\cars\models\cg-nascar-rwd\readme.txt .\runtime\cars\cg-nascar-rwd\readme.txt

if exist .\data\cars\models\clkdtm\*.* call .\create_dir .\runtime
if exist .\data\cars\models\clkdtm\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\clkdtm\*.* call .\create_dir .\runtime\cars\clkdtm
if exist .\data\cars\models\clkdtm\clkdtm.xml copy .\data\cars\models\clkdtm\clkdtm.xml .\runtime\cars\clkdtm\clkdtm.xml
if exist .\data\cars\models\clkdtm\clkdtm.rgb copy .\data\cars\models\clkdtm\clkdtm.rgb .\runtime\cars\clkdtm\clkdtm.rgb
if exist .\data\cars\models\clkdtm\shadow.rgb copy .\data\cars\models\clkdtm\shadow.rgb .\runtime\cars\clkdtm\shadow.rgb
if exist .\data\cars\models\clkdtm\tex-wheel.rgb copy .\data\cars\models\clkdtm\tex-wheel.rgb .\runtime\cars\clkdtm\tex-wheel.rgb
if exist .\data\cars\models\clkdtm\clkdtm.acc copy .\data\cars\models\clkdtm\clkdtm.acc .\runtime\cars\clkdtm\clkdtm.acc
if exist .\data\cars\models\clkdtm\clkdtm-lod1.acc copy .\data\cars\models\clkdtm\clkdtm-lod1.acc .\runtime\cars\clkdtm\clkdtm-lod1.acc
if exist .\data\cars\models\clkdtm\clkdtm-lod2.acc copy .\data\cars\models\clkdtm\clkdtm-lod2.acc .\runtime\cars\clkdtm\clkdtm-lod2.acc
rem if exist .\data\cars\models\clkdtm\clkdtm-src.acc copy .\data\cars\models\clkdtm\clkdtm-src.acc .\runtime\cars\clkdtm\clkdtm-src.acc
if exist .\data\cars\models\clkdtm\readme.txt copy .\data\cars\models\clkdtm\readme.txt .\runtime\cars\clkdtm\readme.txt

if exist .\data\cars\models\sc-f1\*.* call .\create_dir .\runtime
if exist .\data\cars\models\sc-f1\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\sc-f1\*.* call .\create_dir .\runtime\cars\sc-f1
if exist .\data\cars\models\sc-f1\sc-f1.xml copy .\data\cars\models\sc-f1\sc-f1.xml .\runtime\cars\sc-f1\sc-f1.xml
if exist .\data\cars\models\sc-f1\sc-f1.rgb copy .\data\cars\models\sc-f1\sc-f1.rgb .\runtime\cars\sc-f1\sc-f1.rgb
if exist .\data\cars\models\sc-f1\shadow.rgb copy .\data\cars\models\sc-f1\shadow.rgb .\runtime\cars\sc-f1\shadow.rgb
if exist .\data\cars\models\sc-f1\tex-wheel.rgb copy .\data\cars\models\sc-f1\tex-wheel.rgb .\runtime\cars\sc-f1\tex-wheel.rgb
if exist .\data\cars\models\sc-f1\sc-f1.acc copy .\data\cars\models\sc-f1\sc-f1.acc .\runtime\cars\sc-f1\sc-f1.acc
if exist .\data\cars\models\sc-f1\readme.txt copy .\data\cars\models\sc-f1\readme.txt .\runtime\cars\sc-f1\readme.txt


if exist .\data\cars\models\fs-02h2\*.* call .\create_dir .\runtime
if exist .\data\cars\models\fs-02h2\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\fs-02h2\*.* call .\create_dir .\runtime\cars\fs-02h2
if exist .\data\cars\models\fs-02h2\fs-02h2.xml copy .\data\cars\models\fs-02h2\fs-02h2.xml .\runtime\cars\fs-02h2\fs-02h2.xml
if exist .\data\cars\models\fs-02h2\fs-02h2.rgb copy .\data\cars\models\fs-02h2\fs-02h2.rgb .\runtime\cars\fs-02h2\fs-02h2.rgb
if exist .\data\cars\models\fs-02h2\shadow.rgb copy .\data\cars\models\fs-02h2\shadow.rgb .\runtime\cars\fs-02h2\shadow.rgb
if exist .\data\cars\models\fs-02h2\tex-wheel.rgb copy .\data\cars\models\fs-02h2\tex-wheel.rgb .\runtime\cars\fs-02h2\tex-wheel.rgb
if exist .\data\cars\models\fs-02h2\fs-02h2.acc copy .\data\cars\models\fs-02h2\fs-02h2.acc .\runtime\cars\fs-02h2\fs-02h2.acc
if exist .\data\cars\models\fs-02h2\fs-02h2-lod1.acc copy .\data\cars\models\fs-02h2\fs-02h2-lod1.acc .\runtime\cars\fs-02h2\fs-02h2-lod1.acc
if exist .\data\cars\models\fs-02h2\fs-02h2-lod2.acc copy .\data\cars\models\fs-02h2\fs-02h2-lod2.acc .\runtime\cars\fs-02h2\fs-02h2-lod2.acc
if exist .\data\cars\models\fs-02h2\fs-02h2-lod3.acc copy .\data\cars\models\fs-02h2\fs-02h2-lod3.acc .\runtime\cars\fs-02h2\fs-02h2-lod3.acc
if exist .\data\cars\models\fs-02h2\fs-02h2-lod4.acc copy .\data\cars\models\fs-02h2\fs-02h2-lod4.acc .\runtime\cars\fs-02h2\fs-02h2-lod4.acc

if exist .\data\cars\models\fs-ansxtarga\*.* call .\create_dir .\runtime
if exist .\data\cars\models\fs-ansxtarga\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\fs-ansxtarga\*.* call .\create_dir .\runtime\cars\fs-ansxtarga
if exist .\data\cars\models\fs-ansxtarga\fs-ansxtarga.xml copy .\data\cars\models\fs-ansxtarga\fs-ansxtarga.xml .\runtime\cars\fs-ansxtarga\fs-ansxtarga.xml
if exist .\data\cars\models\fs-ansxtarga\fs-ansxtarga.rgb copy .\data\cars\models\fs-ansxtarga\fs-ansxtarga.rgb .\runtime\cars\fs-ansxtarga\fs-ansxtarga.rgb
if exist .\data\cars\models\fs-ansxtarga\shadow.rgb copy .\data\cars\models\fs-ansxtarga\shadow.rgb .\runtime\cars\fs-ansxtarga\shadow.rgb
if exist .\data\cars\models\fs-ansxtarga\tex-wheel.rgb copy .\data\cars\models\fs-ansxtarga\tex-wheel.rgb .\runtime\cars\fs-ansxtarga\tex-wheel.rgb
if exist .\data\cars\models\fs-ansxtarga\fs-ansxtarga.acc copy .\data\cars\models\fs-ansxtarga\fs-ansxtarga.acc .\runtime\cars\fs-ansxtarga\fs-ansxtarga.acc

if exist .\data\cars\models\gt40\*.* call .\create_dir .\runtime
if exist .\data\cars\models\gt40\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\gt40\*.* call .\create_dir .\runtime\cars\gt40
if exist .\data\cars\models\gt40\gt40.xml copy .\data\cars\models\gt40\gt40.xml .\runtime\cars\gt40\gt40.xml
if exist .\data\cars\models\gt40\gt40.rgb copy .\data\cars\models\gt40\gt40.rgb .\runtime\cars\gt40\gt40.rgb
if exist .\data\cars\models\gt40\tex-wheel.rgb copy .\data\cars\models\gt40\tex-wheel.rgb .\runtime\cars\gt40\tex-wheel.rgb
if exist .\data\cars\models\gt40\shadow.rgb copy .\data\cars\models\gt40\shadow.rgb .\runtime\cars\gt40\shadow.rgb
if exist .\data\cars\models\gt40\gt40.acc copy .\data\cars\models\gt40\gt40.acc .\runtime\cars\gt40\gt40.acc
if exist .\data\cars\models\gt40\gt40-lod1.acc copy .\data\cars\models\gt40\gt40-lod1.acc .\runtime\cars\gt40\gt40-lod1.acc
if exist .\data\cars\models\gt40\gt40-lod2.acc copy .\data\cars\models\gt40\gt40-lod2.acc .\runtime\cars\gt40\gt40-lod2.acc
if exist .\data\cars\models\gt40\gt40-lod3.acc copy .\data\cars\models\gt40\gt40-lod3.acc .\runtime\cars\gt40\gt40-lod3.acc
if exist .\data\cars\models\gt40\gt40-lod4.acc copy .\data\cars\models\gt40\gt40-lod4.acc .\runtime\cars\gt40\gt40-lod4.acc
if exist .\data\cars\models\gt40\gt40-src.acc copy .\data\cars\models\gt40\gt40-src.acc .\runtime\cars\gt40\gt40-src.acc
if exist .\data\cars\models\gt40\readme.txt copy .\data\cars\models\gt40\readme.txt .\runtime\cars\gt40\readme.txt

if exist .\data\cars\models\kc-2000gt\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-2000gt\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-2000gt\*.* call .\create_dir .\runtime\cars\kc-2000gt
rem if exist .\data\cars\models\kc-2000gt\2000gt.ac copy .\data\cars\models\kc-2000gt\2000gt.ac .\runtime\cars\kc-2000gt\2000gt.ac
rem if exist .\data\cars\models\kc-2000gt\car00.tga copy .\data\cars\models\kc-2000gt\car00.tga .\runtime\cars\kc-2000gt\car00.tga
rem if exist .\data\cars\models\kc-2000gt\carp.txt copy .\data\cars\models\kc-2000gt\carp.txt .\runtime\cars\kc-2000gt\carp.txt
rem if exist .\data\cars\models\kc-2000gt\kc-2000gt.ac copy .\data\cars\models\kc-2000gt\kc-2000gt.ac .\runtime\cars\kc-2000gt\kc-2000gt.ac
if exist .\data\cars\models\kc-2000gt\kc-2000gt.acc copy .\data\cars\models\kc-2000gt\kc-2000gt.acc .\runtime\cars\kc-2000gt\kc-2000gt.acc
rem if exist .\data\cars\models\kc-2000gt\kc-2000gt-lod1.ac copy .\data\cars\models\kc-2000gt\kc-2000gt-lod1.ac .\runtime\cars\kc-2000gt\kc-2000gt-lod1.ac
if exist .\data\cars\models\kc-2000gt\kc-2000gt-lod1.acc copy .\data\cars\models\kc-2000gt\kc-2000gt-lod1.acc .\runtime\cars\kc-2000gt\kc-2000gt-lod1.acc
rem if exist .\data\cars\models\kc-2000gt\kc-2000gt-lod2.ac copy .\data\cars\models\kc-2000gt\kc-2000gt-lod2.ac .\runtime\cars\kc-2000gt\kc-2000gt-lod2.ac
if exist .\data\cars\models\kc-2000gt\kc-2000gt-lod2.acc copy .\data\cars\models\kc-2000gt\kc-2000gt-lod2.acc .\runtime\cars\kc-2000gt\kc-2000gt-lod2.acc
rem if exist .\data\cars\models\kc-2000gt\kc-2000gt-lod3.ac copy .\data\cars\models\kc-2000gt\kc-2000gt-lod3.ac .\runtime\cars\kc-2000gt\kc-2000gt-lod3.ac
if exist .\data\cars\models\kc-2000gt\kc-2000gt-lod3.acc copy .\data\cars\models\kc-2000gt\kc-2000gt-lod3.acc .\runtime\cars\kc-2000gt\kc-2000gt-lod3.acc
if exist .\data\cars\models\kc-2000gt\kc-2000gt.rgb copy .\data\cars\models\kc-2000gt\kc-2000gt.rgb .\runtime\cars\kc-2000gt\kc-2000gt.rgb
rem if exist .\data\cars\models\kc-2000gt\kc-2000gt.xcf copy .\data\cars\models\kc-2000gt\kc-2000gt.xcf .\runtime\cars\kc-2000gt\kc-2000gt.xcf
if exist .\data\cars\models\kc-2000gt\kc-2000gt.xml copy .\data\cars\models\kc-2000gt\kc-2000gt.xml .\runtime\cars\kc-2000gt\kc-2000gt.xml
rem if exist .\data\cars\models\kc-2000gt\Makefile copy .\data\cars\models\kc-2000gt\Makefile .\runtime\cars\kc-2000gt\Makefile
if exist .\data\cars\models\kc-2000gt\readme.txt copy .\data\cars\models\kc-2000gt\readme.txt .\runtime\cars\kc-2000gt\readme.txt
if exist .\data\cars\models\kc-2000gt\shadow.rgb copy .\data\cars\models\kc-2000gt\shadow.rgb .\runtime\cars\kc-2000gt\shadow.rgb
if exist .\data\cars\models\kc-2000gt\tex-wheel.rgb copy .\data\cars\models\kc-2000gt\tex-wheel.rgb .\runtime\cars\kc-2000gt\tex-wheel.rgb

if exist .\data\cars\models\kc-5300gt\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-5300gt\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-5300gt\*.* call .\create_dir .\runtime\cars\kc-5300gt
rem if exist .\data\cars\models\kc-5300gt\5300gt.ac copy .\data\cars\models\kc-5300gt\5300gt.ac .\runtime\cars\kc-5300gt\5300gt.ac
rem if exist .\data\cars\models\kc-5300gt\car00.tga copy .\data\cars\models\kc-5300gt\car00.tga .\runtime\cars\kc-5300gt\car00.tga
rem if exist .\data\cars\models\kc-5300gt\carp.txt copy .\data\cars\models\kc-5300gt\carp.txt .\runtime\cars\kc-5300gt\carp.txt
rem if exist .\data\cars\models\kc-5300gt\kc-5300gt.ac copy .\data\cars\models\kc-5300gt\kc-5300gt.ac .\runtime\cars\kc-5300gt\kc-5300gt.ac
if exist .\data\cars\models\kc-5300gt\kc-5300gt.acc copy .\data\cars\models\kc-5300gt\kc-5300gt.acc .\runtime\cars\kc-5300gt\kc-5300gt.acc
rem if exist .\data\cars\models\kc-5300gt\kc-5300gt-lod1.ac copy .\data\cars\models\kc-5300gt\kc-5300gt-lod1.ac .\runtime\cars\kc-5300gt\kc-5300gt-lod1.ac
if exist .\data\cars\models\kc-5300gt\kc-5300gt-lod1.acc copy .\data\cars\models\kc-5300gt\kc-5300gt-lod1.acc .\runtime\cars\kc-5300gt\kc-5300gt-lod1.acc
rem if exist .\data\cars\models\kc-5300gt\kc-5300gt-lod2.ac copy .\data\cars\models\kc-5300gt\kc-5300gt-lod2.ac .\runtime\cars\kc-5300gt\kc-5300gt-lod2.ac
if exist .\data\cars\models\kc-5300gt\kc-5300gt-lod2.acc copy .\data\cars\models\kc-5300gt\kc-5300gt-lod2.acc .\runtime\cars\kc-5300gt\kc-5300gt-lod2.acc
rem if exist .\data\cars\models\kc-5300gt\kc-5300gt-lod3.ac copy .\data\cars\models\kc-5300gt\kc-5300gt-lod3.ac .\runtime\cars\kc-5300gt\kc-5300gt-lod3.ac
if exist .\data\cars\models\kc-5300gt\kc-5300gt-lod3.acc copy .\data\cars\models\kc-5300gt\kc-5300gt-lod3.acc .\runtime\cars\kc-5300gt\kc-5300gt-lod3.acc
if exist .\data\cars\models\kc-5300gt\kc-5300gt.rgb copy .\data\cars\models\kc-5300gt\kc-5300gt.rgb .\runtime\cars\kc-5300gt\kc-5300gt.rgb
rem if exist .\data\cars\models\kc-5300gt\kc-5300gt.xcf copy .\data\cars\models\kc-5300gt\kc-5300gt.xcf .\runtime\cars\kc-5300gt\kc-5300gt.xcf
if exist .\data\cars\models\kc-5300gt\kc-5300gt.xml copy .\data\cars\models\kc-5300gt\kc-5300gt.xml .\runtime\cars\kc-5300gt\kc-5300gt.xml
if exist .\data\cars\models\kc-5300gt\kmh1.rgb copy .\data\cars\models\kc-5300gt\kmh1.rgb .\runtime\cars\kc-5300gt\kmh1.rgb
rem if exist .\data\cars\models\kc-5300gt\Makefile copy .\data\cars\models\kc-5300gt\Makefile .\runtime\cars\kc-5300gt\Makefile
if exist .\data\cars\models\kc-5300gt\readme.txt copy .\data\cars\models\kc-5300gt\readme.txt .\runtime\cars\kc-5300gt\readme.txt
if exist .\data\cars\models\kc-5300gt\rpm1.rgb copy .\data\cars\models\kc-5300gt\rpm1.rgb .\runtime\cars\kc-5300gt\rpm1.rgb
if exist .\data\cars\models\kc-5300gt\shadow.rgb copy .\data\cars\models\kc-5300gt\shadow.rgb .\runtime\cars\kc-5300gt\shadow.rgb
if exist .\data\cars\models\kc-5300gt\tex-wheel.rgb copy .\data\cars\models\kc-5300gt\tex-wheel.rgb .\runtime\cars\kc-5300gt\tex-wheel.rgb

if exist .\data\cars\models\kc-a110\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-a110\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-a110\*.* call .\create_dir .\runtime\cars\kc-a110
rem if exist .\data\cars\models\kc-a110\a110.ac copy .\data\cars\models\kc-a110\a110.ac .\runtime\cars\kc-a110\a110.ac
rem if exist .\data\cars\models\kc-a110\alpine.ac copy .\data\cars\models\kc-a110\alpine.ac .\runtime\cars\kc-a110\alpine.ac
rem if exist .\data\cars\models\kc-a110\car00.tga copy .\data\cars\models\kc-a110\car00.tga .\runtime\cars\kc-a110\car00.tga
rem if exist .\data\cars\models\kc-a110\carp.txt copy .\data\cars\models\kc-a110\carp.txt .\runtime\cars\kc-a110\carp.txt
rem if exist .\data\cars\models\kc-a110\infos.txt copy .\data\cars\models\kc-a110\infos.txt .\runtime\cars\kc-a110\infos.txt
rem if exist .\data\cars\models\kc-a110\kc-a110.ac copy .\data\cars\models\kc-a110\kc-a110.ac .\runtime\cars\kc-a110\kc-a110.ac
if exist .\data\cars\models\kc-a110\kc-a110.acc copy .\data\cars\models\kc-a110\kc-a110.acc .\runtime\cars\kc-a110\kc-a110.acc
rem if exist .\data\cars\models\kc-a110\kc-a110-lod1.ac copy .\data\cars\models\kc-a110\kc-a110-lod1.ac .\runtime\cars\kc-a110\kc-a110-lod1.ac
if exist .\data\cars\models\kc-a110\kc-a110-lod1.acc copy .\data\cars\models\kc-a110\kc-a110-lod1.acc .\runtime\cars\kc-a110\kc-a110-lod1.acc
rem if exist .\data\cars\models\kc-a110\kc-a110-lod2.ac copy .\data\cars\models\kc-a110\kc-a110-lod2.ac .\runtime\cars\kc-a110\kc-a110-lod2.ac
if exist .\data\cars\models\kc-a110\kc-a110-lod2.acc copy .\data\cars\models\kc-a110\kc-a110-lod2.acc .\runtime\cars\kc-a110\kc-a110-lod2.acc
rem if exist .\data\cars\models\kc-a110\kc-a110-lod3.ac copy .\data\cars\models\kc-a110\kc-a110-lod3.ac .\runtime\cars\kc-a110\kc-a110-lod3.ac
if exist .\data\cars\models\kc-a110\kc-a110-lod3.acc copy .\data\cars\models\kc-a110\kc-a110-lod3.acc .\runtime\cars\kc-a110\kc-a110-lod3.acc
if exist .\data\cars\models\kc-a110\kc-a110.rgb copy .\data\cars\models\kc-a110\kc-a110.rgb .\runtime\cars\kc-a110\kc-a110.rgb
rem if exist .\data\cars\models\kc-a110\kc-a110.xcf copy .\data\cars\models\kc-a110\kc-a110.xcf .\runtime\cars\kc-a110\kc-a110.xcf
if exist .\data\cars\models\kc-a110\kc-a110.xml copy .\data\cars\models\kc-a110\kc-a110.xml .\runtime\cars\kc-a110\kc-a110.xml
rem if exist .\data\cars\models\kc-a110\Makefile copy .\data\cars\models\kc-a110\Makefile .\runtime\cars\kc-a110\Makefile
if exist .\data\cars\models\kc-a110\readme.txt copy .\data\cars\models\kc-a110\readme.txt .\runtime\cars\kc-a110\readme.txt
if exist .\data\cars\models\kc-a110\shadow.rgb copy .\data\cars\models\kc-a110\shadow.rgb .\runtime\cars\kc-a110\shadow.rgb
if exist .\data\cars\models\kc-a110\tex-wheel.rgb copy .\data\cars\models\kc-a110\tex-wheel.rgb .\runtime\cars\kc-a110\tex-wheel.rgb

if exist .\data\cars\models\kc-alfatz2\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-alfatz2\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-alfatz2\*.* call .\create_dir .\runtime\cars\kc-alfatz2
rem if exist .\data\cars\models\kc-alfatz2\alfatz2.ac copy .\data\cars\models\kc-alfatz2\alfatz2.ac .\runtime\cars\kc-alfatz2\alfatz2.ac
rem if exist .\data\cars\models\kc-alfatz2\car00.tga copy .\data\cars\models\kc-alfatz2\car00.tga .\runtime\cars\kc-alfatz2\car00.tga
rem if exist .\data\cars\models\kc-alfatz2\carp.txt copy .\data\cars\models\kc-alfatz2\carp.txt .\runtime\cars\kc-alfatz2\carp.txt
rem if exist .\data\cars\models\kc-alfatz2\kc-alfatz2.ac copy .\data\cars\models\kc-alfatz2\kc-alfatz2.ac .\runtime\cars\kc-alfatz2\kc-alfatz2.ac
if exist .\data\cars\models\kc-alfatz2\kc-alfatz2.acc copy .\data\cars\models\kc-alfatz2\kc-alfatz2.acc .\runtime\cars\kc-alfatz2\kc-alfatz2.acc
rem if exist .\data\cars\models\kc-alfatz2\kc-alfatz2-lod1.ac copy .\data\cars\models\kc-alfatz2\kc-alfatz2-lod1.ac .\runtime\cars\kc-alfatz2\kc-alfatz2-lod1.ac
if exist .\data\cars\models\kc-alfatz2\kc-alfatz2-lod1.acc copy .\data\cars\models\kc-alfatz2\kc-alfatz2-lod1.acc .\runtime\cars\kc-alfatz2\kc-alfatz2-lod1.acc
rem if exist .\data\cars\models\kc-alfatz2\kc-alfatz2-lod2.ac copy .\data\cars\models\kc-alfatz2\kc-alfatz2-lod2.ac .\runtime\cars\kc-alfatz2\kc-alfatz2-lod2.ac
if exist .\data\cars\models\kc-alfatz2\kc-alfatz2-lod2.acc copy .\data\cars\models\kc-alfatz2\kc-alfatz2-lod2.acc .\runtime\cars\kc-alfatz2\kc-alfatz2-lod2.acc
rem if exist .\data\cars\models\kc-alfatz2\kc-alfatz2-lod3.ac copy .\data\cars\models\kc-alfatz2\kc-alfatz2-lod3.ac .\runtime\cars\kc-alfatz2\kc-alfatz2-lod3.ac
if exist .\data\cars\models\kc-alfatz2\kc-alfatz2-lod3.acc copy .\data\cars\models\kc-alfatz2\kc-alfatz2-lod3.acc .\runtime\cars\kc-alfatz2\kc-alfatz2-lod3.acc
if exist .\data\cars\models\kc-alfatz2\kc-alfatz2.rgb copy .\data\cars\models\kc-alfatz2\kc-alfatz2.rgb .\runtime\cars\kc-alfatz2\kc-alfatz2.rgb
rem if exist .\data\cars\models\kc-alfatz2\kc-alfatz2.xcf copy .\data\cars\models\kc-alfatz2\kc-alfatz2.xcf .\runtime\cars\kc-alfatz2\kc-alfatz2.xcf
if exist .\data\cars\models\kc-alfatz2\kc-alfatz2.xml copy .\data\cars\models\kc-alfatz2\kc-alfatz2.xml .\runtime\cars\kc-alfatz2\kc-alfatz2.xml
if exist .\data\cars\models\kc-alfatz2\kmh1.rgb copy .\data\cars\models\kc-alfatz2\kmh1.rgb .\runtime\cars\kc-alfatz2\kmh1.rgb
rem if exist .\data\cars\models\kc-alfatz2\Makefile copy .\data\cars\models\kc-alfatz2\Makefile .\runtime\cars\kc-alfatz2\Makefile
if exist .\data\cars\models\kc-alfatz2\readme.txt copy .\data\cars\models\kc-alfatz2\readme.txt .\runtime\cars\kc-alfatz2\readme.txt
if exist .\data\cars\models\kc-alfatz2\rpm1.rgb copy .\data\cars\models\kc-alfatz2\rpm1.rgb .\runtime\cars\kc-alfatz2\rpm1.rgb
if exist .\data\cars\models\kc-alfatz2\shadow.rgb copy .\data\cars\models\kc-alfatz2\shadow.rgb .\runtime\cars\kc-alfatz2\shadow.rgb
if exist .\data\cars\models\kc-alfatz2\tex-wheel.rgb copy .\data\cars\models\kc-alfatz2\tex-wheel.rgb .\runtime\cars\kc-alfatz2\tex-wheel.rgb

if exist .\data\cars\models\kc-bigh\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-bigh\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-bigh\*.* call .\create_dir .\runtime\cars\kc-bigh
rem if exist .\data\cars\models\kc-bigh\bigh.ac copy .\data\cars\models\kc-bigh\bigh.ac .\runtime\cars\kc-bigh\bigh.ac
rem if exist .\data\cars\models\kc-bigh\car00.tga copy .\data\cars\models\kc-bigh\car00.tga .\runtime\cars\kc-bigh\car00.tga
rem if exist .\data\cars\models\kc-bigh\carp.txt copy .\data\cars\models\kc-bigh\carp.txt .\runtime\cars\kc-bigh\carp.txt
rem if exist .\data\cars\models\kc-bigh\kc-bigh.ac copy .\data\cars\models\kc-bigh\kc-bigh.ac .\runtime\cars\kc-bigh\kc-bigh.ac
if exist .\data\cars\models\kc-bigh\kc-bigh.acc copy .\data\cars\models\kc-bigh\kc-bigh.acc .\runtime\cars\kc-bigh\kc-bigh.acc
rem if exist .\data\cars\models\kc-bigh\kc-bigh-lod1.ac copy .\data\cars\models\kc-bigh\kc-bigh-lod1.ac .\runtime\cars\kc-bigh\kc-bigh-lod1.ac
if exist .\data\cars\models\kc-bigh\kc-bigh-lod1.acc copy .\data\cars\models\kc-bigh\kc-bigh-lod1.acc .\runtime\cars\kc-bigh\kc-bigh-lod1.acc
rem if exist .\data\cars\models\kc-bigh\kc-bigh-lod2.ac copy .\data\cars\models\kc-bigh\kc-bigh-lod2.ac .\runtime\cars\kc-bigh\kc-bigh-lod2.ac
if exist .\data\cars\models\kc-bigh\kc-bigh-lod2.acc copy .\data\cars\models\kc-bigh\kc-bigh-lod2.acc .\runtime\cars\kc-bigh\kc-bigh-lod2.acc
rem if exist .\data\cars\models\kc-bigh\kc-bigh-lod3.ac copy .\data\cars\models\kc-bigh\kc-bigh-lod3.ac .\runtime\cars\kc-bigh\kc-bigh-lod3.ac
if exist .\data\cars\models\kc-bigh\kc-bigh-lod3.acc copy .\data\cars\models\kc-bigh\kc-bigh-lod3.acc .\runtime\cars\kc-bigh\kc-bigh-lod3.acc
if exist .\data\cars\models\kc-bigh\kc-bigh.rgb copy .\data\cars\models\kc-bigh\kc-bigh.rgb .\runtime\cars\kc-bigh\kc-bigh.rgb
rem if exist .\data\cars\models\kc-bigh\kc-bigh.xcf copy .\data\cars\models\kc-bigh\kc-bigh.xcf .\runtime\cars\kc-bigh\kc-bigh.xcf
if exist .\data\cars\models\kc-bigh\kc-bigh.xml copy .\data\cars\models\kc-bigh\kc-bigh.xml .\runtime\cars\kc-bigh\kc-bigh.xml
rem if exist .\data\cars\models\kc-bigh\Makefile copy .\data\cars\models\kc-bigh\Makefile .\runtime\cars\kc-bigh\Makefile
if exist .\data\cars\models\kc-bigh\readme.txt copy .\data\cars\models\kc-bigh\readme.txt .\runtime\cars\kc-bigh\readme.txt
if exist .\data\cars\models\kc-bigh\shadow.rgb copy .\data\cars\models\kc-bigh\shadow.rgb .\runtime\cars\kc-bigh\shadow.rgb
if exist .\data\cars\models\kc-bigh\tex-wheel.rgb copy .\data\cars\models\kc-bigh\tex-wheel.rgb .\runtime\cars\kc-bigh\tex-wheel.rgb

if exist .\data\cars\models\kc-bmw507\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-bmw507\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-bmw507\*.* call .\create_dir .\runtime\cars\kc-bmw507
rem if exist .\data\cars\models\kc-bmw507\bmw507.ac copy .\data\cars\models\kc-bmw507\bmw507.ac .\runtime\cars\kc-bmw507\bmw507.ac
rem if exist .\data\cars\models\kc-bmw507\car00.tga copy .\data\cars\models\kc-bmw507\car00.tga .\runtime\cars\kc-bmw507\car00.tga
rem if exist .\data\cars\models\kc-bmw507\carp.txt copy .\data\cars\models\kc-bmw507\carp.txt .\runtime\cars\kc-bmw507\carp.txt
rem if exist .\data\cars\models\kc-bmw507\kc-bmw507.ac copy .\data\cars\models\kc-bmw507\kc-bmw507.ac .\runtime\cars\kc-bmw507\kc-bmw507.ac
if exist .\data\cars\models\kc-bmw507\kc-bmw507.acc copy .\data\cars\models\kc-bmw507\kc-bmw507.acc .\runtime\cars\kc-bmw507\kc-bmw507.acc
rem if exist .\data\cars\models\kc-bmw507\kc-bmw507-lod1.ac copy .\data\cars\models\kc-bmw507\kc-bmw507-lod1.ac .\runtime\cars\kc-bmw507\kc-bmw507-lod1.ac
if exist .\data\cars\models\kc-bmw507\kc-bmw507-lod1.acc copy .\data\cars\models\kc-bmw507\kc-bmw507-lod1.acc .\runtime\cars\kc-bmw507\kc-bmw507-lod1.acc
rem if exist .\data\cars\models\kc-bmw507\kc-bmw507-lod2.ac copy .\data\cars\models\kc-bmw507\kc-bmw507-lod2.ac .\runtime\cars\kc-bmw507\kc-bmw507-lod2.ac
if exist .\data\cars\models\kc-bmw507\kc-bmw507-lod2.acc copy .\data\cars\models\kc-bmw507\kc-bmw507-lod2.acc .\runtime\cars\kc-bmw507\kc-bmw507-lod2.acc
rem if exist .\data\cars\models\kc-bmw507\kc-bmw507-lod3.ac copy .\data\cars\models\kc-bmw507\kc-bmw507-lod3.ac .\runtime\cars\kc-bmw507\kc-bmw507-lod3.ac
if exist .\data\cars\models\kc-bmw507\kc-bmw507-lod3.acc copy .\data\cars\models\kc-bmw507\kc-bmw507-lod3.acc .\runtime\cars\kc-bmw507\kc-bmw507-lod3.acc
rem if exist .\data\cars\models\kc-bmw507\kc-bmw507-lod4.ac copy .\data\cars\models\kc-bmw507\kc-bmw507-lod4.ac .\runtime\cars\kc-bmw507\kc-bmw507-lod4.ac
if exist .\data\cars\models\kc-bmw507\kc-bmw507-lod4.acc copy .\data\cars\models\kc-bmw507\kc-bmw507-lod4.acc .\runtime\cars\kc-bmw507\kc-bmw507-lod4.acc
if exist .\data\cars\models\kc-bmw507\kc-bmw507.rgb copy .\data\cars\models\kc-bmw507\kc-bmw507.rgb .\runtime\cars\kc-bmw507\kc-bmw507.rgb
if exist .\data\cars\models\kc-bmw507\kc-bmw507.xml copy .\data\cars\models\kc-bmw507\kc-bmw507.xml .\runtime\cars\kc-bmw507\kc-bmw507.xml
rem if exist .\data\cars\models\kc-bmw507\Makefile copy .\data\cars\models\kc-bmw507\Makefile .\runtime\cars\kc-bmw507\Makefile
if exist .\data\cars\models\kc-bmw507\readme.txt copy .\data\cars\models\kc-bmw507\readme.txt .\runtime\cars\kc-bmw507\readme.txt
if exist .\data\cars\models\kc-bmw507\shadow.rgb copy .\data\cars\models\kc-bmw507\shadow.rgb .\runtime\cars\kc-bmw507\shadow.rgb
if exist .\data\cars\models\kc-bmw507\tex-wheel.rgb copy .\data\cars\models\kc-bmw507\tex-wheel.rgb .\runtime\cars\kc-bmw507\tex-wheel.rgb

if exist .\data\cars\models\kc-cobra\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-cobra\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-cobra\*.* call .\create_dir .\runtime\cars\kc-cobra
rem if exist .\data\cars\models\kc-cobra\carp.txt copy .\data\cars\models\kc-cobra\carp.txt .\runtime\cars\kc-cobra\carp.txt
rem if exist .\data\cars\models\kc-cobra\cobra2.ac copy .\data\cars\models\kc-cobra\cobra2.ac .\runtime\cars\kc-cobra\cobra2.ac
rem if exist .\data\cars\models\kc-cobra\kc-cobra.ac copy .\data\cars\models\kc-cobra\kc-cobra.ac .\runtime\cars\kc-cobra\kc-cobra.ac
if exist .\data\cars\models\kc-cobra\kc-cobra.acc copy .\data\cars\models\kc-cobra\kc-cobra.acc .\runtime\cars\kc-cobra\kc-cobra.acc
rem if exist .\data\cars\models\kc-cobra\kc-cobra-lod1.ac copy .\data\cars\models\kc-cobra\kc-cobra-lod1.ac .\runtime\cars\kc-cobra\kc-cobra-lod1.ac
if exist .\data\cars\models\kc-cobra\kc-cobra-lod1.acc copy .\data\cars\models\kc-cobra\kc-cobra-lod1.acc .\runtime\cars\kc-cobra\kc-cobra-lod1.acc
rem if exist .\data\cars\models\kc-cobra\kc-cobra-lod2.ac copy .\data\cars\models\kc-cobra\kc-cobra-lod2.ac .\runtime\cars\kc-cobra\kc-cobra-lod2.ac
if exist .\data\cars\models\kc-cobra\kc-cobra-lod2.acc copy .\data\cars\models\kc-cobra\kc-cobra-lod2.acc .\runtime\cars\kc-cobra\kc-cobra-lod2.acc
rem if exist .\data\cars\models\kc-cobra\kc-cobra-lod3.ac copy .\data\cars\models\kc-cobra\kc-cobra-lod3.ac .\runtime\cars\kc-cobra\kc-cobra-lod3.ac
if exist .\data\cars\models\kc-cobra\kc-cobra-lod3.acc copy .\data\cars\models\kc-cobra\kc-cobra-lod3.acc .\runtime\cars\kc-cobra\kc-cobra-lod3.acc
if exist .\data\cars\models\kc-cobra\kc-cobra.rgb copy .\data\cars\models\kc-cobra\kc-cobra.rgb .\runtime\cars\kc-cobra\kc-cobra.rgb
rem if exist .\data\cars\models\kc-cobra\kc-cobra.xcf copy .\data\cars\models\kc-cobra\kc-cobra.xcf .\runtime\cars\kc-cobra\kc-cobra.xcf
if exist .\data\cars\models\kc-cobra\kc-cobra.xml copy .\data\cars\models\kc-cobra\kc-cobra.xml .\runtime\cars\kc-cobra\kc-cobra.xml
rem if exist .\data\cars\models\kc-cobra\Makefile copy .\data\cars\models\kc-cobra\Makefile .\runtime\cars\kc-cobra\Makefile
if exist .\data\cars\models\kc-cobra\readme.txt copy .\data\cars\models\kc-cobra\readme.txt .\runtime\cars\kc-cobra\readme.txt
if exist .\data\cars\models\kc-cobra\shadow.rgb copy .\data\cars\models\kc-cobra\shadow.rgb .\runtime\cars\kc-cobra\shadow.rgb
if exist .\data\cars\models\kc-cobra\tex-wheel.rgb copy .\data\cars\models\kc-cobra\tex-wheel.rgb .\runtime\cars\kc-cobra\tex-wheel.rgb

if exist .\data\cars\models\kc-coda\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-coda\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-coda\*.* call .\create_dir .\runtime\cars\kc-coda
rem if exist .\data\cars\models\kc-coda\car00.tga copy .\data\cars\models\kc-coda\car00.tga .\runtime\cars\kc-coda\car00.tga
rem if exist .\data\cars\models\kc-coda\carp.txt copy .\data\cars\models\kc-coda\carp.txt .\runtime\cars\kc-coda\carp.txt
rem if exist .\data\cars\models\kc-coda\coda.ac copy .\data\cars\models\kc-coda\coda.ac .\runtime\cars\kc-coda\coda.ac
rem if exist .\data\cars\models\kc-coda\kc-coda.ac copy .\data\cars\models\kc-coda\kc-coda.ac .\runtime\cars\kc-coda\kc-coda.ac
if exist .\data\cars\models\kc-coda\kc-coda.acc copy .\data\cars\models\kc-coda\kc-coda.acc .\runtime\cars\kc-coda\kc-coda.acc
rem if exist .\data\cars\models\kc-coda\kc-coda-lod1.ac copy .\data\cars\models\kc-coda\kc-coda-lod1.ac .\runtime\cars\kc-coda\kc-coda-lod1.ac
if exist .\data\cars\models\kc-coda\kc-coda-lod1.acc copy .\data\cars\models\kc-coda\kc-coda-lod1.acc .\runtime\cars\kc-coda\kc-coda-lod1.acc
rem if exist .\data\cars\models\kc-coda\kc-coda-lod2.ac copy .\data\cars\models\kc-coda\kc-coda-lod2.ac .\runtime\cars\kc-coda\kc-coda-lod2.ac
if exist .\data\cars\models\kc-coda\kc-coda-lod2.acc copy .\data\cars\models\kc-coda\kc-coda-lod2.acc .\runtime\cars\kc-coda\kc-coda-lod2.acc
rem if exist .\data\cars\models\kc-coda\kc-coda-lod3.ac copy .\data\cars\models\kc-coda\kc-coda-lod3.ac .\runtime\cars\kc-coda\kc-coda-lod3.ac
if exist .\data\cars\models\kc-coda\kc-coda-lod3.acc copy .\data\cars\models\kc-coda\kc-coda-lod3.acc .\runtime\cars\kc-coda\kc-coda-lod3.acc
if exist .\data\cars\models\kc-coda\kc-coda.rgb copy .\data\cars\models\kc-coda\kc-coda.rgb .\runtime\cars\kc-coda\kc-coda.rgb
rem if exist .\data\cars\models\kc-coda\kc-coda.xcf copy .\data\cars\models\kc-coda\kc-coda.xcf .\runtime\cars\kc-coda\kc-coda.xcf
if exist .\data\cars\models\kc-coda\kc-coda.xml copy .\data\cars\models\kc-coda\kc-coda.xml .\runtime\cars\kc-coda\kc-coda.xml
rem if exist .\data\cars\models\kc-coda\Makefile copy .\data\cars\models\kc-coda\Makefile .\runtime\cars\kc-coda\Makefile
if exist .\data\cars\models\kc-coda\readme.txt copy .\data\cars\models\kc-coda\readme.txt .\runtime\cars\kc-coda\readme.txt
if exist .\data\cars\models\kc-coda\shadow.rgb copy .\data\cars\models\kc-coda\shadow.rgb .\runtime\cars\kc-coda\shadow.rgb
if exist .\data\cars\models\kc-coda\tex-wheel.rgb copy .\data\cars\models\kc-coda\tex-wheel.rgb .\runtime\cars\kc-coda\tex-wheel.rgb

if exist .\data\cars\models\kc-conrero\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-conrero\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-conrero\*.* call .\create_dir .\runtime\cars\kc-conrero
rem if exist .\data\cars\models\kc-conrero\car00.tga copy .\data\cars\models\kc-conrero\car00.tga .\runtime\cars\kc-conrero\car00.tga
rem if exist .\data\cars\models\kc-conrero\carp.txt copy .\data\cars\models\kc-conrero\carp.txt .\runtime\cars\kc-conrero\carp.txt
rem if exist .\data\cars\models\kc-conrero\conrero.ac copy .\data\cars\models\kc-conrero\conrero.ac .\runtime\cars\kc-conrero\conrero.ac
rem if exist .\data\cars\models\kc-conrero\kc-conrero.ac copy .\data\cars\models\kc-conrero\kc-conrero.ac .\runtime\cars\kc-conrero\kc-conrero.ac
if exist .\data\cars\models\kc-conrero\kc-conrero.acc copy .\data\cars\models\kc-conrero\kc-conrero.acc .\runtime\cars\kc-conrero\kc-conrero.acc
rem if exist .\data\cars\models\kc-conrero\kc-conrero-lod1.ac copy .\data\cars\models\kc-conrero\kc-conrero-lod1.ac .\runtime\cars\kc-conrero\kc-conrero-lod1.ac
if exist .\data\cars\models\kc-conrero\kc-conrero-lod1.acc copy .\data\cars\models\kc-conrero\kc-conrero-lod1.acc .\runtime\cars\kc-conrero\kc-conrero-lod1.acc
rem if exist .\data\cars\models\kc-conrero\kc-conrero-lod2.ac copy .\data\cars\models\kc-conrero\kc-conrero-lod2.ac .\runtime\cars\kc-conrero\kc-conrero-lod2.ac
if exist .\data\cars\models\kc-conrero\kc-conrero-lod2.acc copy .\data\cars\models\kc-conrero\kc-conrero-lod2.acc .\runtime\cars\kc-conrero\kc-conrero-lod2.acc
rem if exist .\data\cars\models\kc-conrero\kc-conrero-lod3.ac copy .\data\cars\models\kc-conrero\kc-conrero-lod3.ac .\runtime\cars\kc-conrero\kc-conrero-lod3.ac
if exist .\data\cars\models\kc-conrero\kc-conrero-lod3.acc copy .\data\cars\models\kc-conrero\kc-conrero-lod3.acc .\runtime\cars\kc-conrero\kc-conrero-lod3.acc
if exist .\data\cars\models\kc-conrero\kc-conrero.rgb copy .\data\cars\models\kc-conrero\kc-conrero.rgb .\runtime\cars\kc-conrero\kc-conrero.rgb
rem if exist .\data\cars\models\kc-conrero\kc-conrero.xcf copy .\data\cars\models\kc-conrero\kc-conrero.xcf .\runtime\cars\kc-conrero\kc-conrero.xcf
if exist .\data\cars\models\kc-conrero\kc-conrero.xml copy .\data\cars\models\kc-conrero\kc-conrero.xml .\runtime\cars\kc-conrero\kc-conrero.xml
if exist .\data\cars\models\kc-conrero\kmh1.rgb copy .\data\cars\models\kc-conrero\kmh1.rgb .\runtime\cars\kc-conrero\kmh1.rgb
rem if exist .\data\cars\models\kc-conrero\Makefile copy .\data\cars\models\kc-conrero\Makefile .\runtime\cars\kc-conrero\Makefile
if exist .\data\cars\models\kc-conrero\readme.txt copy .\data\cars\models\kc-conrero\readme.txt .\runtime\cars\kc-conrero\readme.txt
if exist .\data\cars\models\kc-conrero\rpm1.rgb copy .\data\cars\models\kc-conrero\rpm1.rgb .\runtime\cars\kc-conrero\rpm1.rgb
if exist .\data\cars\models\kc-conrero\shadow.rgb copy .\data\cars\models\kc-conrero\shadow.rgb .\runtime\cars\kc-conrero\shadow.rgb
if exist .\data\cars\models\kc-conrero\tex-wheel.rgb copy .\data\cars\models\kc-conrero\tex-wheel.rgb .\runtime\cars\kc-conrero\tex-wheel.rgb

if exist .\data\cars\models\kc-corvette-ttop\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-corvette-ttop\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-corvette-ttop\*.* call .\create_dir .\runtime\cars\kc-corvette-ttop
rem if exist .\data\cars\models\kc-corvette-ttop\car00.tga copy .\data\cars\models\kc-corvette-ttop\car00.tga .\runtime\cars\kc-corvette-ttop\car00.tga
rem if exist .\data\cars\models\kc-corvette-ttop\carp.txt copy .\data\cars\models\kc-corvette-ttop\carp.txt .\runtime\cars\kc-corvette-ttop\carp.txt
rem if exist .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop.ac copy .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop.ac .\runtime\cars\kc-corvette-ttop\kc-corvette-ttop.ac
if exist .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop.acc copy .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop.acc .\runtime\cars\kc-corvette-ttop\kc-corvette-ttop.acc
rem if exist .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod1.ac copy .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod1.ac .\runtime\cars\kc-corvette-ttop\kc-corvette-ttop-lod1.ac
if exist .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod1.acc copy .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod1.acc .\runtime\cars\kc-corvette-ttop\kc-corvette-ttop-lod1.acc
rem if exist .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod2.ac copy .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod2.ac .\runtime\cars\kc-corvette-ttop\kc-corvette-ttop-lod2.ac
if exist .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod2.acc copy .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod2.acc .\runtime\cars\kc-corvette-ttop\kc-corvette-ttop-lod2.acc
rem if exist .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod3.ac copy .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod3.ac .\runtime\cars\kc-corvette-ttop\kc-corvette-ttop-lod3.ac
if exist .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod3.acc copy .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop-lod3.acc .\runtime\cars\kc-corvette-ttop\kc-corvette-ttop-lod3.acc
if exist .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop.rgb copy .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop.rgb .\runtime\cars\kc-corvette-ttop\kc-corvette-ttop.rgb
rem if exist .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop.xcf copy .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop.xcf .\runtime\cars\kc-corvette-ttop\kc-corvette-ttop.xcf
if exist .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop.xml copy .\data\cars\models\kc-corvette-ttop\kc-corvette-ttop.xml .\runtime\cars\kc-corvette-ttop\kc-corvette-ttop.xml
if exist .\data\cars\models\kc-corvette-ttop\kmh1.rgb copy .\data\cars\models\kc-corvette-ttop\kmh1.rgb .\runtime\cars\kc-corvette-ttop\kmh1.rgb
rem if exist .\data\cars\models\kc-corvette-ttop\Makefile copy .\data\cars\models\kc-corvette-ttop\Makefile .\runtime\cars\kc-corvette-ttop\Makefile
if exist .\data\cars\models\kc-corvette-ttop\readme.txt copy .\data\cars\models\kc-corvette-ttop\readme.txt .\runtime\cars\kc-corvette-ttop\readme.txt
if exist .\data\cars\models\kc-corvette-ttop\rpm1.rgb copy .\data\cars\models\kc-corvette-ttop\rpm1.rgb .\runtime\cars\kc-corvette-ttop\rpm1.rgb
rem if exist .\data\cars\models\kc-corvette-ttop\sepcs.txt copy .\data\cars\models\kc-corvette-ttop\sepcs.txt .\runtime\cars\kc-corvette-ttop\sepcs.txt
if exist .\data\cars\models\kc-corvette-ttop\shadow.rgb copy .\data\cars\models\kc-corvette-ttop\shadow.rgb .\runtime\cars\kc-corvette-ttop\shadow.rgb
if exist .\data\cars\models\kc-corvette-ttop\tex-wheel.rgb copy .\data\cars\models\kc-corvette-ttop\tex-wheel.rgb .\runtime\cars\kc-corvette-ttop\tex-wheel.rgb

if exist .\data\cars\models\kc-daytona\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-daytona\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-daytona\*.* call .\create_dir .\runtime\cars\kc-daytona
rem if exist .\data\cars\models\kc-daytona\car00.tga copy .\data\cars\models\kc-daytona\car00.tga .\runtime\cars\kc-daytona\car00.tga
rem if exist .\data\cars\models\kc-daytona\carp.txt copy .\data\cars\models\kc-daytona\carp.txt .\runtime\cars\kc-daytona\carp.txt
rem if exist .\data\cars\models\kc-daytona\daytona.ac copy .\data\cars\models\kc-daytona\daytona.ac .\runtime\cars\kc-daytona\daytona.ac
rem if exist .\data\cars\models\kc-daytona\kc-daytona.ac copy .\data\cars\models\kc-daytona\kc-daytona.ac .\runtime\cars\kc-daytona\kc-daytona.ac
if exist .\data\cars\models\kc-daytona\kc-daytona.acc copy .\data\cars\models\kc-daytona\kc-daytona.acc .\runtime\cars\kc-daytona\kc-daytona.acc
rem if exist .\data\cars\models\kc-daytona\kc-daytona-lod1.ac copy .\data\cars\models\kc-daytona\kc-daytona-lod1.ac .\runtime\cars\kc-daytona\kc-daytona-lod1.ac
if exist .\data\cars\models\kc-daytona\kc-daytona-lod1.acc copy .\data\cars\models\kc-daytona\kc-daytona-lod1.acc .\runtime\cars\kc-daytona\kc-daytona-lod1.acc
rem if exist .\data\cars\models\kc-daytona\kc-daytona-lod2.ac copy .\data\cars\models\kc-daytona\kc-daytona-lod2.ac .\runtime\cars\kc-daytona\kc-daytona-lod2.ac
if exist .\data\cars\models\kc-daytona\kc-daytona-lod2.acc copy .\data\cars\models\kc-daytona\kc-daytona-lod2.acc .\runtime\cars\kc-daytona\kc-daytona-lod2.acc
rem if exist .\data\cars\models\kc-daytona\kc-daytona-lod3.ac copy .\data\cars\models\kc-daytona\kc-daytona-lod3.ac .\runtime\cars\kc-daytona\kc-daytona-lod3.ac
if exist .\data\cars\models\kc-daytona\kc-daytona-lod3.acc copy .\data\cars\models\kc-daytona\kc-daytona-lod3.acc .\runtime\cars\kc-daytona\kc-daytona-lod3.acc
if exist .\data\cars\models\kc-daytona\kc-daytona.rgb copy .\data\cars\models\kc-daytona\kc-daytona.rgb .\runtime\cars\kc-daytona\kc-daytona.rgb
rem if exist .\data\cars\models\kc-daytona\kc-daytona.xcf copy .\data\cars\models\kc-daytona\kc-daytona.xcf .\runtime\cars\kc-daytona\kc-daytona.xcf
if exist .\data\cars\models\kc-daytona\kc-daytona.xml copy .\data\cars\models\kc-daytona\kc-daytona.xml .\runtime\cars\kc-daytona\kc-daytona.xml
if exist .\data\cars\models\kc-daytona\kmh1.rgb copy .\data\cars\models\kc-daytona\kmh1.rgb .\runtime\cars\kc-daytona\kmh1.rgb
rem if exist .\data\cars\models\kc-daytona\Makefile copy .\data\cars\models\kc-daytona\Makefile .\runtime\cars\kc-daytona\Makefile
if exist .\data\cars\models\kc-daytona\readme.txt copy .\data\cars\models\kc-daytona\readme.txt .\runtime\cars\kc-daytona\readme.txt
if exist .\data\cars\models\kc-daytona\rpm1.rgb copy .\data\cars\models\kc-daytona\rpm1.rgb .\runtime\cars\kc-daytona\rpm1.rgb
if exist .\data\cars\models\kc-daytona\shadow.rgb copy .\data\cars\models\kc-daytona\shadow.rgb .\runtime\cars\kc-daytona\shadow.rgb
if exist .\data\cars\models\kc-daytona\tex-wheel.rgb copy .\data\cars\models\kc-daytona\tex-wheel.rgb .\runtime\cars\kc-daytona\tex-wheel.rgb

if exist .\data\cars\models\kc-db4z\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-db4z\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-db4z\*.* call .\create_dir .\runtime\cars\kc-db4z
rem if exist .\data\cars\models\kc-db4z\car00.tga copy .\data\cars\models\kc-db4z\car00.tga .\runtime\cars\kc-db4z\car00.tga
rem if exist .\data\cars\models\kc-db4z\carp.txt copy .\data\cars\models\kc-db4z\carp.txt .\runtime\cars\kc-db4z\carp.txt
rem if exist .\data\cars\models\kc-db4z\kc-db4z.ac copy .\data\cars\models\kc-db4z\kc-db4z.ac .\runtime\cars\kc-db4z\kc-db4z.ac
if exist .\data\cars\models\kc-db4z\kc-db4z.acc copy .\data\cars\models\kc-db4z\kc-db4z.acc .\runtime\cars\kc-db4z\kc-db4z.acc
rem if exist .\data\cars\models\kc-db4z\kc-db4z-lod1.ac copy .\data\cars\models\kc-db4z\kc-db4z-lod1.ac .\runtime\cars\kc-db4z\kc-db4z-lod1.ac
if exist .\data\cars\models\kc-db4z\kc-db4z-lod1.acc copy .\data\cars\models\kc-db4z\kc-db4z-lod1.acc .\runtime\cars\kc-db4z\kc-db4z-lod1.acc
rem if exist .\data\cars\models\kc-db4z\kc-db4z-lod2.ac copy .\data\cars\models\kc-db4z\kc-db4z-lod2.ac .\runtime\cars\kc-db4z\kc-db4z-lod2.ac
if exist .\data\cars\models\kc-db4z\kc-db4z-lod2.acc copy .\data\cars\models\kc-db4z\kc-db4z-lod2.acc .\runtime\cars\kc-db4z\kc-db4z-lod2.acc
rem if exist .\data\cars\models\kc-db4z\kc-db4z-lod3.ac copy .\data\cars\models\kc-db4z\kc-db4z-lod3.ac .\runtime\cars\kc-db4z\kc-db4z-lod3.ac
if exist .\data\cars\models\kc-db4z\kc-db4z-lod3.acc copy .\data\cars\models\kc-db4z\kc-db4z-lod3.acc .\runtime\cars\kc-db4z\kc-db4z-lod3.acc
if exist .\data\cars\models\kc-db4z\kc-db4z.rgb copy .\data\cars\models\kc-db4z\kc-db4z.rgb .\runtime\cars\kc-db4z\kc-db4z.rgb
rem if exist .\data\cars\models\kc-db4z\kc-db4z.xcf copy .\data\cars\models\kc-db4z\kc-db4z.xcf .\runtime\cars\kc-db4z\kc-db4z.xcf
if exist .\data\cars\models\kc-db4z\kc-db4z.xml copy .\data\cars\models\kc-db4z\kc-db4z.xml .\runtime\cars\kc-db4z\kc-db4z.xml
rem if exist .\data\cars\models\kc-db4z\Makefile copy .\data\cars\models\kc-db4z\Makefile .\runtime\cars\kc-db4z\Makefile
if exist .\data\cars\models\kc-db4z\readme.txt copy .\data\cars\models\kc-db4z\readme.txt .\runtime\cars\kc-db4z\readme.txt
if exist .\data\cars\models\kc-db4z\shadow.rgb copy .\data\cars\models\kc-db4z\shadow.rgb .\runtime\cars\kc-db4z\shadow.rgb
if exist .\data\cars\models\kc-db4z\tex-wheel.rgb copy .\data\cars\models\kc-db4z\tex-wheel.rgb .\runtime\cars\kc-db4z\tex-wheel.rgb

if exist .\data\cars\models\kc-dbs\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-dbs\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-dbs\*.* call .\create_dir .\runtime\cars\kc-dbs
rem if exist .\data\cars\models\kc-dbs\car00.tga copy .\data\cars\models\kc-dbs\car00.tga .\runtime\cars\kc-dbs\car00.tga
rem if exist .\data\cars\models\kc-dbs\carp.txt copy .\data\cars\models\kc-dbs\carp.txt .\runtime\cars\kc-dbs\carp.txt
rem if exist .\data\cars\models\kc-dbs\dbs.ac copy .\data\cars\models\kc-dbs\dbs.ac .\runtime\cars\kc-dbs\dbs.ac
rem if exist .\data\cars\models\kc-dbs\kc-dbs.ac copy .\data\cars\models\kc-dbs\kc-dbs.ac .\runtime\cars\kc-dbs\kc-dbs.ac
if exist .\data\cars\models\kc-dbs\kc-dbs.acc copy .\data\cars\models\kc-dbs\kc-dbs.acc .\runtime\cars\kc-dbs\kc-dbs.acc
rem if exist .\data\cars\models\kc-dbs\kc-dbs-lod1.ac copy .\data\cars\models\kc-dbs\kc-dbs-lod1.ac .\runtime\cars\kc-dbs\kc-dbs-lod1.ac
if exist .\data\cars\models\kc-dbs\kc-dbs-lod1.acc copy .\data\cars\models\kc-dbs\kc-dbs-lod1.acc .\runtime\cars\kc-dbs\kc-dbs-lod1.acc
rem if exist .\data\cars\models\kc-dbs\kc-dbs-lod2.ac copy .\data\cars\models\kc-dbs\kc-dbs-lod2.ac .\runtime\cars\kc-dbs\kc-dbs-lod2.ac
if exist .\data\cars\models\kc-dbs\kc-dbs-lod2.acc copy .\data\cars\models\kc-dbs\kc-dbs-lod2.acc .\runtime\cars\kc-dbs\kc-dbs-lod2.acc
if exist .\data\cars\models\kc-dbs\kc-dbs.rgb copy .\data\cars\models\kc-dbs\kc-dbs.rgb .\runtime\cars\kc-dbs\kc-dbs.rgb
rem if exist .\data\cars\models\kc-dbs\kc-dbs.xcf copy .\data\cars\models\kc-dbs\kc-dbs.xcf .\runtime\cars\kc-dbs\kc-dbs.xcf
if exist .\data\cars\models\kc-dbs\kc-dbs.xml copy .\data\cars\models\kc-dbs\kc-dbs.xml .\runtime\cars\kc-dbs\kc-dbs.xml
rem if exist .\data\cars\models\kc-dbs\Makefile copy .\data\cars\models\kc-dbs\Makefile .\runtime\cars\kc-dbs\Makefile
if exist .\data\cars\models\kc-dbs\readme.txt copy .\data\cars\models\kc-dbs\readme.txt .\runtime\cars\kc-dbs\readme.txt
if exist .\data\cars\models\kc-dbs\shadow.rgb copy .\data\cars\models\kc-dbs\shadow.rgb .\runtime\cars\kc-dbs\shadow.rgb
if exist .\data\cars\models\kc-dbs\tex-wheel.rgb copy .\data\cars\models\kc-dbs\tex-wheel.rgb .\runtime\cars\kc-dbs\tex-wheel.rgb

if exist .\data\cars\models\kc-dino\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-dino\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-dino\*.* call .\create_dir .\runtime\cars\kc-dino
rem if exist .\data\cars\models\kc-dino\carp.txt copy .\data\cars\models\kc-dino\carp.txt .\runtime\cars\kc-dino\carp.txt
rem if exist .\data\cars\models\kc-dino\dino.ac copy .\data\cars\models\kc-dino\dino.ac .\runtime\cars\kc-dino\dino.ac
rem if exist .\data\cars\models\kc-dino\kc-dino.ac copy .\data\cars\models\kc-dino\kc-dino.ac .\runtime\cars\kc-dino\kc-dino.ac
if exist .\data\cars\models\kc-dino\kc-dino.acc copy .\data\cars\models\kc-dino\kc-dino.acc .\runtime\cars\kc-dino\kc-dino.acc
rem if exist .\data\cars\models\kc-dino\kc-dino-lod1.ac copy .\data\cars\models\kc-dino\kc-dino-lod1.ac .\runtime\cars\kc-dino\kc-dino-lod1.ac
if exist .\data\cars\models\kc-dino\kc-dino-lod1.acc copy .\data\cars\models\kc-dino\kc-dino-lod1.acc .\runtime\cars\kc-dino\kc-dino-lod1.acc
rem if exist .\data\cars\models\kc-dino\kc-dino-lod2.ac copy .\data\cars\models\kc-dino\kc-dino-lod2.ac .\runtime\cars\kc-dino\kc-dino-lod2.ac
if exist .\data\cars\models\kc-dino\kc-dino-lod2.acc copy .\data\cars\models\kc-dino\kc-dino-lod2.acc .\runtime\cars\kc-dino\kc-dino-lod2.acc
if exist .\data\cars\models\kc-dino\kc-dino.rgb copy .\data\cars\models\kc-dino\kc-dino.rgb .\runtime\cars\kc-dino\kc-dino.rgb
rem if exist .\data\cars\models\kc-dino\kc-dino.xcf copy .\data\cars\models\kc-dino\kc-dino.xcf .\runtime\cars\kc-dino\kc-dino.xcf
if exist .\data\cars\models\kc-dino\kc-dino.xml copy .\data\cars\models\kc-dino\kc-dino.xml .\runtime\cars\kc-dino\kc-dino.xml
if exist .\data\cars\models\kc-dino\kmh1.rgb copy .\data\cars\models\kc-dino\kmh1.rgb .\runtime\cars\kc-dino\kmh1.rgb
rem if exist .\data\cars\models\kc-dino\Makefile copy .\data\cars\models\kc-dino\Makefile .\runtime\cars\kc-dino\Makefile
if exist .\data\cars\models\kc-dino\readme.txt copy .\data\cars\models\kc-dino\readme.txt .\runtime\cars\kc-dino\readme.txt
if exist .\data\cars\models\kc-dino\rpm1.rgb copy .\data\cars\models\kc-dino\rpm1.rgb .\runtime\cars\kc-dino\rpm1.rgb
if exist .\data\cars\models\kc-dino\shadow.rgb copy .\data\cars\models\kc-dino\shadow.rgb .\runtime\cars\kc-dino\shadow.rgb
if exist .\data\cars\models\kc-dino\tex-wheel.rgb copy .\data\cars\models\kc-dino\tex-wheel.rgb .\runtime\cars\kc-dino\tex-wheel.rgb

if exist .\data\cars\models\kc-ghibli\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-ghibli\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-ghibli\*.* call .\create_dir .\runtime\cars\kc-ghibli
rem if exist .\data\cars\models\kc-ghibli\car00.tga copy .\data\cars\models\kc-ghibli\car00.tga .\runtime\cars\kc-ghibli\car00.tga
rem if exist .\data\cars\models\kc-ghibli\carp.txt copy .\data\cars\models\kc-ghibli\carp.txt .\runtime\cars\kc-ghibli\carp.txt
rem if exist .\data\cars\models\kc-ghibli\ghibli.ac copy .\data\cars\models\kc-ghibli\ghibli.ac .\runtime\cars\kc-ghibli\ghibli.ac
rem if exist .\data\cars\models\kc-ghibli\kc-ghibli.ac copy .\data\cars\models\kc-ghibli\kc-ghibli.ac .\runtime\cars\kc-ghibli\kc-ghibli.ac
if exist .\data\cars\models\kc-ghibli\kc-ghibli.acc copy .\data\cars\models\kc-ghibli\kc-ghibli.acc .\runtime\cars\kc-ghibli\kc-ghibli.acc
rem if exist .\data\cars\models\kc-ghibli\kc-ghibli-lod1.ac copy .\data\cars\models\kc-ghibli\kc-ghibli-lod1.ac .\runtime\cars\kc-ghibli\kc-ghibli-lod1.ac
if exist .\data\cars\models\kc-ghibli\kc-ghibli-lod1.acc copy .\data\cars\models\kc-ghibli\kc-ghibli-lod1.acc .\runtime\cars\kc-ghibli\kc-ghibli-lod1.acc
rem if exist .\data\cars\models\kc-ghibli\kc-ghibli-lod2.ac copy .\data\cars\models\kc-ghibli\kc-ghibli-lod2.ac .\runtime\cars\kc-ghibli\kc-ghibli-lod2.ac
if exist .\data\cars\models\kc-ghibli\kc-ghibli-lod2.acc copy .\data\cars\models\kc-ghibli\kc-ghibli-lod2.acc .\runtime\cars\kc-ghibli\kc-ghibli-lod2.acc
rem if exist .\data\cars\models\kc-ghibli\kc-ghibli-lod3.ac copy .\data\cars\models\kc-ghibli\kc-ghibli-lod3.ac .\runtime\cars\kc-ghibli\kc-ghibli-lod3.ac
if exist .\data\cars\models\kc-ghibli\kc-ghibli-lod3.acc copy .\data\cars\models\kc-ghibli\kc-ghibli-lod3.acc .\runtime\cars\kc-ghibli\kc-ghibli-lod3.acc
if exist .\data\cars\models\kc-ghibli\kc-ghibli.rgb copy .\data\cars\models\kc-ghibli\kc-ghibli.rgb .\runtime\cars\kc-ghibli\kc-ghibli.rgb
rem if exist .\data\cars\models\kc-ghibli\kc-ghibli.xcf copy .\data\cars\models\kc-ghibli\kc-ghibli.xcf .\runtime\cars\kc-ghibli\kc-ghibli.xcf
if exist .\data\cars\models\kc-ghibli\kc-ghibli.xml copy .\data\cars\models\kc-ghibli\kc-ghibli.xml .\runtime\cars\kc-ghibli\kc-ghibli.xml
rem if exist .\data\cars\models\kc-ghibli\Makefile copy .\data\cars\models\kc-ghibli\Makefile .\runtime\cars\kc-ghibli\Makefile
if exist .\data\cars\models\kc-ghibli\readme.txt copy .\data\cars\models\kc-ghibli\readme.txt .\runtime\cars\kc-ghibli\readme.txt
if exist .\data\cars\models\kc-ghibli\shadow.rgb copy .\data\cars\models\kc-ghibli\shadow.rgb .\runtime\cars\kc-ghibli\shadow.rgb
if exist .\data\cars\models\kc-ghibli\tex-wheel.rgb copy .\data\cars\models\kc-ghibli\tex-wheel.rgb .\runtime\cars\kc-ghibli\tex-wheel.rgb

if exist .\data\cars\models\kc-giulietta\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-giulietta\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-giulietta\*.* call .\create_dir .\runtime\cars\kc-giulietta
rem if exist .\data\cars\models\kc-giulietta\car00.tga copy .\data\cars\models\kc-giulietta\car00.tga .\runtime\cars\kc-giulietta\car00.tga
rem if exist .\data\cars\models\kc-giulietta\carp.txt copy .\data\cars\models\kc-giulietta\carp.txt .\runtime\cars\kc-giulietta\carp.txt
rem if exist .\data\cars\models\kc-giulietta\giul.ac copy .\data\cars\models\kc-giulietta\giul.ac .\runtime\cars\kc-giulietta\giul.ac
rem if exist .\data\cars\models\kc-giulietta\kc-giulietta.ac copy .\data\cars\models\kc-giulietta\kc-giulietta.ac .\runtime\cars\kc-giulietta\kc-giulietta.ac
if exist .\data\cars\models\kc-giulietta\kc-giulietta.acc copy .\data\cars\models\kc-giulietta\kc-giulietta.acc .\runtime\cars\kc-giulietta\kc-giulietta.acc
rem if exist .\data\cars\models\kc-giulietta\kc-giulietta-lod1.ac copy .\data\cars\models\kc-giulietta\kc-giulietta-lod1.ac .\runtime\cars\kc-giulietta\kc-giulietta-lod1.ac
if exist .\data\cars\models\kc-giulietta\kc-giulietta-lod1.acc copy .\data\cars\models\kc-giulietta\kc-giulietta-lod1.acc .\runtime\cars\kc-giulietta\kc-giulietta-lod1.acc
rem if exist .\data\cars\models\kc-giulietta\kc-giulietta-lod2.ac copy .\data\cars\models\kc-giulietta\kc-giulietta-lod2.ac .\runtime\cars\kc-giulietta\kc-giulietta-lod2.ac
if exist .\data\cars\models\kc-giulietta\kc-giulietta-lod2.acc copy .\data\cars\models\kc-giulietta\kc-giulietta-lod2.acc .\runtime\cars\kc-giulietta\kc-giulietta-lod2.acc
rem if exist .\data\cars\models\kc-giulietta\kc-giulietta-lod3.ac copy .\data\cars\models\kc-giulietta\kc-giulietta-lod3.ac .\runtime\cars\kc-giulietta\kc-giulietta-lod3.ac
if exist .\data\cars\models\kc-giulietta\kc-giulietta-lod3.acc copy .\data\cars\models\kc-giulietta\kc-giulietta-lod3.acc .\runtime\cars\kc-giulietta\kc-giulietta-lod3.acc
rem if exist .\data\cars\models\kc-giulietta\kc-giulietta-lod4.ac copy .\data\cars\models\kc-giulietta\kc-giulietta-lod4.ac .\runtime\cars\kc-giulietta\kc-giulietta-lod4.ac
if exist .\data\cars\models\kc-giulietta\kc-giulietta-lod4.acc copy .\data\cars\models\kc-giulietta\kc-giulietta-lod4.acc .\runtime\cars\kc-giulietta\kc-giulietta-lod4.acc
if exist .\data\cars\models\kc-giulietta\kc-giulietta.rgb copy .\data\cars\models\kc-giulietta\kc-giulietta.rgb .\runtime\cars\kc-giulietta\kc-giulietta.rgb
if exist .\data\cars\models\kc-giulietta\kc-giulietta.xml copy .\data\cars\models\kc-giulietta\kc-giulietta.xml .\runtime\cars\kc-giulietta\kc-giulietta.xml
rem if exist .\data\cars\models\kc-giulietta\Makefile copy .\data\cars\models\kc-giulietta\Makefile .\runtime\cars\kc-giulietta\Makefile
if exist .\data\cars\models\kc-giulietta\readme.txt copy .\data\cars\models\kc-giulietta\readme.txt .\runtime\cars\kc-giulietta\readme.txt
if exist .\data\cars\models\kc-giulietta\shadow.rgb copy .\data\cars\models\kc-giulietta\shadow.rgb .\runtime\cars\kc-giulietta\shadow.rgb
if exist .\data\cars\models\kc-giulietta\tex-wheel.rgb copy .\data\cars\models\kc-giulietta\tex-wheel.rgb .\runtime\cars\kc-giulietta\tex-wheel.rgb

if exist .\data\cars\models\kc-grifo\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-grifo\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-grifo\*.* call .\create_dir .\runtime\cars\kc-grifo
rem if exist .\data\cars\models\kc-grifo\car00.rgb copy .\data\cars\models\kc-grifo\car00.rgb .\runtime\cars\kc-grifo\car00.rgb
rem if exist .\data\cars\models\kc-grifo\car00.tga copy .\data\cars\models\kc-grifo\car00.tga .\runtime\cars\kc-grifo\car00.tga
rem if exist .\data\cars\models\kc-grifo\carp.txt copy .\data\cars\models\kc-grifo\carp.txt .\runtime\cars\kc-grifo\carp.txt
rem if exist .\data\cars\models\kc-grifo\grifo.ac copy .\data\cars\models\kc-grifo\grifo.ac .\runtime\cars\kc-grifo\grifo.ac
rem if exist .\data\cars\models\kc-grifo\kc-grifo.ac copy .\data\cars\models\kc-grifo\kc-grifo.ac .\runtime\cars\kc-grifo\kc-grifo.ac
if exist .\data\cars\models\kc-grifo\kc-grifo.acc copy .\data\cars\models\kc-grifo\kc-grifo.acc .\runtime\cars\kc-grifo\kc-grifo.acc
rem if exist .\data\cars\models\kc-grifo\kc-grifo-lod1.ac copy .\data\cars\models\kc-grifo\kc-grifo-lod1.ac .\runtime\cars\kc-grifo\kc-grifo-lod1.ac
if exist .\data\cars\models\kc-grifo\kc-grifo-lod1.acc copy .\data\cars\models\kc-grifo\kc-grifo-lod1.acc .\runtime\cars\kc-grifo\kc-grifo-lod1.acc
rem if exist .\data\cars\models\kc-grifo\kc-grifo-lod2.ac copy .\data\cars\models\kc-grifo\kc-grifo-lod2.ac .\runtime\cars\kc-grifo\kc-grifo-lod2.ac
if exist .\data\cars\models\kc-grifo\kc-grifo-lod2.acc copy .\data\cars\models\kc-grifo\kc-grifo-lod2.acc .\runtime\cars\kc-grifo\kc-grifo-lod2.acc
rem if exist .\data\cars\models\kc-grifo\kc-grifo-lod3.ac copy .\data\cars\models\kc-grifo\kc-grifo-lod3.ac .\runtime\cars\kc-grifo\kc-grifo-lod3.ac
if exist .\data\cars\models\kc-grifo\kc-grifo-lod3.acc copy .\data\cars\models\kc-grifo\kc-grifo-lod3.acc .\runtime\cars\kc-grifo\kc-grifo-lod3.acc
rem if exist .\data\cars\models\kc-grifo\kc-grifo-lod4.ac copy .\data\cars\models\kc-grifo\kc-grifo-lod4.ac .\runtime\cars\kc-grifo\kc-grifo-lod4.ac
if exist .\data\cars\models\kc-grifo\kc-grifo-lod4.acc copy .\data\cars\models\kc-grifo\kc-grifo-lod4.acc .\runtime\cars\kc-grifo\kc-grifo-lod4.acc
if exist .\data\cars\models\kc-grifo\kc-grifo.rgb copy .\data\cars\models\kc-grifo\kc-grifo.rgb .\runtime\cars\kc-grifo\kc-grifo.rgb
if exist .\data\cars\models\kc-grifo\kc-grifo.xml copy .\data\cars\models\kc-grifo\kc-grifo.xml .\runtime\cars\kc-grifo\kc-grifo.xml
if exist .\data\cars\models\kc-grifo\kmh1.rgb copy .\data\cars\models\kc-grifo\kmh1.rgb .\runtime\cars\kc-grifo\kmh1.rgb
rem if exist .\data\cars\models\kc-grifo\Makefile copy .\data\cars\models\kc-grifo\Makefile .\runtime\cars\kc-grifo\Makefile
if exist .\data\cars\models\kc-grifo\readme.txt copy .\data\cars\models\kc-grifo\readme.txt .\runtime\cars\kc-grifo\readme.txt
if exist .\data\cars\models\kc-grifo\rpm1.rgb copy .\data\cars\models\kc-grifo\rpm1.rgb .\runtime\cars\kc-grifo\rpm1.rgb
if exist .\data\cars\models\kc-grifo\shadow.rgb copy .\data\cars\models\kc-grifo\shadow.rgb .\runtime\cars\kc-grifo\shadow.rgb
if exist .\data\cars\models\kc-grifo\tex-wheel.rgb copy .\data\cars\models\kc-grifo\tex-wheel.rgb .\runtime\cars\kc-grifo\tex-wheel.rgb

if exist .\data\cars\models\kc-gt40\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-gt40\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-gt40\*.* call .\create_dir .\runtime\cars\kc-gt40
rem if exist .\data\cars\models\kc-gt40\car00.tga copy .\data\cars\models\kc-gt40\car00.tga .\runtime\cars\kc-gt40\car00.tga
rem if exist .\data\cars\models\kc-gt40\carp.txt copy .\data\cars\models\kc-gt40\carp.txt .\runtime\cars\kc-gt40\carp.txt
rem if exist .\data\cars\models\kc-gt40\gt40.ac copy .\data\cars\models\kc-gt40\gt40.ac .\runtime\cars\kc-gt40\gt40.ac
if exist .\data\cars\models\kc-gt40\gt40.acc copy .\data\cars\models\kc-gt40\gt40.acc .\runtime\cars\kc-gt40\gt40.acc
rem if exist .\data\cars\models\kc-gt40\kc-gt40-2.ac copy .\data\cars\models\kc-gt40\kc-gt40-2.ac .\runtime\cars\kc-gt40\kc-gt40-2.ac
rem if exist .\data\cars\models\kc-gt40\kc-gt40.ac copy .\data\cars\models\kc-gt40\kc-gt40.ac .\runtime\cars\kc-gt40\kc-gt40.ac
if exist .\data\cars\models\kc-gt40\kc-gt40.acc copy .\data\cars\models\kc-gt40\kc-gt40.acc .\runtime\cars\kc-gt40\kc-gt40.acc
rem if exist .\data\cars\models\kc-gt40\kc-gt40-lod1.ac copy .\data\cars\models\kc-gt40\kc-gt40-lod1.ac .\runtime\cars\kc-gt40\kc-gt40-lod1.ac
if exist .\data\cars\models\kc-gt40\kc-gt40-lod1.acc copy .\data\cars\models\kc-gt40\kc-gt40-lod1.acc .\runtime\cars\kc-gt40\kc-gt40-lod1.acc
rem if exist .\data\cars\models\kc-gt40\kc-gt40-lod2.ac copy .\data\cars\models\kc-gt40\kc-gt40-lod2.ac .\runtime\cars\kc-gt40\kc-gt40-lod2.ac
if exist .\data\cars\models\kc-gt40\kc-gt40-lod2.acc copy .\data\cars\models\kc-gt40\kc-gt40-lod2.acc .\runtime\cars\kc-gt40\kc-gt40-lod2.acc
rem if exist .\data\cars\models\kc-gt40\kc-gt40-lod3.ac copy .\data\cars\models\kc-gt40\kc-gt40-lod3.ac .\runtime\cars\kc-gt40\kc-gt40-lod3.ac
if exist .\data\cars\models\kc-gt40\kc-gt40-lod3.acc copy .\data\cars\models\kc-gt40\kc-gt40-lod3.acc .\runtime\cars\kc-gt40\kc-gt40-lod3.acc
if exist .\data\cars\models\kc-gt40\kc-gt40.rgb copy .\data\cars\models\kc-gt40\kc-gt40.rgb .\runtime\cars\kc-gt40\kc-gt40.rgb
rem if exist .\data\cars\models\kc-gt40\kc-gt40.xcf copy .\data\cars\models\kc-gt40\kc-gt40.xcf .\runtime\cars\kc-gt40\kc-gt40.xcf
if exist .\data\cars\models\kc-gt40\kc-gt40.xml copy .\data\cars\models\kc-gt40\kc-gt40.xml .\runtime\cars\kc-gt40\kc-gt40.xml
if exist .\data\cars\models\kc-gt40\kmh1.rgb copy .\data\cars\models\kc-gt40\kmh1.rgb .\runtime\cars\kc-gt40\kmh1.rgb
rem if exist .\data\cars\models\kc-gt40\Makefile copy .\data\cars\models\kc-gt40\Makefile .\runtime\cars\kc-gt40\Makefile
if exist .\data\cars\models\kc-gt40\readme.txt copy .\data\cars\models\kc-gt40\readme.txt .\runtime\cars\kc-gt40\readme.txt
if exist .\data\cars\models\kc-gt40\rpm1.rgb copy .\data\cars\models\kc-gt40\rpm1.rgb .\runtime\cars\kc-gt40\rpm1.rgb
if exist .\data\cars\models\kc-gt40\shadow.rgb copy .\data\cars\models\kc-gt40\shadow.rgb .\runtime\cars\kc-gt40\shadow.rgb
if exist .\data\cars\models\kc-gt40\tex-wheel.rgb copy .\data\cars\models\kc-gt40\tex-wheel.rgb .\runtime\cars\kc-gt40\tex-wheel.rgb

if exist .\data\cars\models\kc-gto\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-gto\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-gto\*.* call .\create_dir .\runtime\cars\kc-gto
rem if exist .\data\cars\models\kc-gto\car00.rgb copy .\data\cars\models\kc-gto\car00.rgb .\runtime\cars\kc-gto\car00.rgb
rem if exist .\data\cars\models\kc-gto\carp.txt copy .\data\cars\models\kc-gto\carp.txt .\runtime\cars\kc-gto\carp.txt
rem if exist .\data\cars\models\kc-gto\gto.ac copy .\data\cars\models\kc-gto\gto.ac .\runtime\cars\kc-gto\gto.ac
rem if exist .\data\cars\models\kc-gto\kc-gto.ac copy .\data\cars\models\kc-gto\kc-gto.ac .\runtime\cars\kc-gto\kc-gto.ac
if exist .\data\cars\models\kc-gto\kc-gto.acc copy .\data\cars\models\kc-gto\kc-gto.acc .\runtime\cars\kc-gto\kc-gto.acc
rem if exist .\data\cars\models\kc-gto\kc-gto-lod1.ac copy .\data\cars\models\kc-gto\kc-gto-lod1.ac .\runtime\cars\kc-gto\kc-gto-lod1.ac
if exist .\data\cars\models\kc-gto\kc-gto-lod1.acc copy .\data\cars\models\kc-gto\kc-gto-lod1.acc .\runtime\cars\kc-gto\kc-gto-lod1.acc
rem if exist .\data\cars\models\kc-gto\kc-gto-lod2.ac copy .\data\cars\models\kc-gto\kc-gto-lod2.ac .\runtime\cars\kc-gto\kc-gto-lod2.ac
if exist .\data\cars\models\kc-gto\kc-gto-lod2.acc copy .\data\cars\models\kc-gto\kc-gto-lod2.acc .\runtime\cars\kc-gto\kc-gto-lod2.acc
rem if exist .\data\cars\models\kc-gto\kc-gto-lod3.ac copy .\data\cars\models\kc-gto\kc-gto-lod3.ac .\runtime\cars\kc-gto\kc-gto-lod3.ac
if exist .\data\cars\models\kc-gto\kc-gto-lod3.acc copy .\data\cars\models\kc-gto\kc-gto-lod3.acc .\runtime\cars\kc-gto\kc-gto-lod3.acc
rem if exist .\data\cars\models\kc-gto\kc-gto-lod4.ac copy .\data\cars\models\kc-gto\kc-gto-lod4.ac .\runtime\cars\kc-gto\kc-gto-lod4.ac
if exist .\data\cars\models\kc-gto\kc-gto-lod4.acc copy .\data\cars\models\kc-gto\kc-gto-lod4.acc .\runtime\cars\kc-gto\kc-gto-lod4.acc
if exist .\data\cars\models\kc-gto\kc-gto.rgb copy .\data\cars\models\kc-gto\kc-gto.rgb .\runtime\cars\kc-gto\kc-gto.rgb
rem if exist .\data\cars\models\kc-gto\kc-gto.xcf copy .\data\cars\models\kc-gto\kc-gto.xcf .\runtime\cars\kc-gto\kc-gto.xcf
if exist .\data\cars\models\kc-gto\kc-gto.xml copy .\data\cars\models\kc-gto\kc-gto.xml .\runtime\cars\kc-gto\kc-gto.xml
if exist .\data\cars\models\kc-gto\kmh1.rgb copy .\data\cars\models\kc-gto\kmh1.rgb .\runtime\cars\kc-gto\kmh1.rgb
rem if exist .\data\cars\models\kc-gto\Makefile copy .\data\cars\models\kc-gto\Makefile .\runtime\cars\kc-gto\Makefile
if exist .\data\cars\models\kc-gto\readme.txt copy .\data\cars\models\kc-gto\readme.txt .\runtime\cars\kc-gto\readme.txt
if exist .\data\cars\models\kc-gto\rpm1.rgb copy .\data\cars\models\kc-gto\rpm1.rgb .\runtime\cars\kc-gto\rpm1.rgb
if exist .\data\cars\models\kc-gto\shadow.rgb copy .\data\cars\models\kc-gto\shadow.rgb .\runtime\cars\kc-gto\shadow.rgb
if exist .\data\cars\models\kc-gto\tex-wheel.rgb copy .\data\cars\models\kc-gto\tex-wheel.rgb .\runtime\cars\kc-gto\tex-wheel.rgb

if exist .\data\cars\models\kc-gullwing\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-gullwing\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-gullwing\*.* call .\create_dir .\runtime\cars\kc-gullwing
rem if exist .\data\cars\models\kc-gullwing\accc copy .\data\cars\models\kc-gullwing\accc .\runtime\cars\kc-gullwing\accc
rem if exist .\data\cars\models\kc-gullwing\car00.tga copy .\data\cars\models\kc-gullwing\car00.tga .\runtime\cars\kc-gullwing\car00.tga
rem if exist .\data\cars\models\kc-gullwing\carp.txt copy .\data\cars\models\kc-gullwing\carp.txt .\runtime\cars\kc-gullwing\carp.txt
rem if exist .\data\cars\models\kc-gullwing\dash00.tga copy .\data\cars\models\kc-gullwing\dash00.tga .\runtime\cars\kc-gullwing\dash00.tga
rem if exist .\data\cars\models\kc-gullwing\gullwing.ac copy .\data\cars\models\kc-gullwing\gullwing.ac .\runtime\cars\kc-gullwing\gullwing.ac
rem if exist .\data\cars\models\kc-gullwing\kc-gullwing.ac copy .\data\cars\models\kc-gullwing\kc-gullwing.ac .\runtime\cars\kc-gullwing\kc-gullwing.ac
if exist .\data\cars\models\kc-gullwing\kc-gullwing.acc copy .\data\cars\models\kc-gullwing\kc-gullwing.acc .\runtime\cars\kc-gullwing\kc-gullwing.acc
rem if exist .\data\cars\models\kc-gullwing\kc-gullwing-lod1.ac copy .\data\cars\models\kc-gullwing\kc-gullwing-lod1.ac .\runtime\cars\kc-gullwing\kc-gullwing-lod1.ac
if exist .\data\cars\models\kc-gullwing\kc-gullwing-lod1.acc copy .\data\cars\models\kc-gullwing\kc-gullwing-lod1.acc .\runtime\cars\kc-gullwing\kc-gullwing-lod1.acc
rem if exist .\data\cars\models\kc-gullwing\kc-gullwing-lod2.ac copy .\data\cars\models\kc-gullwing\kc-gullwing-lod2.ac .\runtime\cars\kc-gullwing\kc-gullwing-lod2.ac
if exist .\data\cars\models\kc-gullwing\kc-gullwing-lod2.acc copy .\data\cars\models\kc-gullwing\kc-gullwing-lod2.acc .\runtime\cars\kc-gullwing\kc-gullwing-lod2.acc
rem if exist .\data\cars\models\kc-gullwing\kc-gullwing-lod3.ac copy .\data\cars\models\kc-gullwing\kc-gullwing-lod3.ac .\runtime\cars\kc-gullwing\kc-gullwing-lod3.ac
if exist .\data\cars\models\kc-gullwing\kc-gullwing-lod3.acc copy .\data\cars\models\kc-gullwing\kc-gullwing-lod3.acc .\runtime\cars\kc-gullwing\kc-gullwing-lod3.acc
rem if exist .\data\cars\models\kc-gullwing\kc-gullwing-lod4.ac copy .\data\cars\models\kc-gullwing\kc-gullwing-lod4.ac .\runtime\cars\kc-gullwing\kc-gullwing-lod4.ac
if exist .\data\cars\models\kc-gullwing\kc-gullwing-lod4.acc copy .\data\cars\models\kc-gullwing\kc-gullwing-lod4.acc .\runtime\cars\kc-gullwing\kc-gullwing-lod4.acc
if exist .\data\cars\models\kc-gullwing\kc-gullwing.rgb copy .\data\cars\models\kc-gullwing\kc-gullwing.rgb .\runtime\cars\kc-gullwing\kc-gullwing.rgb
if exist .\data\cars\models\kc-gullwing\kc-gullwing.xml copy .\data\cars\models\kc-gullwing\kc-gullwing.xml .\runtime\cars\kc-gullwing\kc-gullwing.xml
rem if exist .\data\cars\models\kc-gullwing\Makefile copy .\data\cars\models\kc-gullwing\Makefile .\runtime\cars\kc-gullwing\Makefile
if exist .\data\cars\models\kc-gullwing\readme.txt copy .\data\cars\models\kc-gullwing\readme.txt .\runtime\cars\kc-gullwing\readme.txt
if exist .\data\cars\models\kc-gullwing\shadow.rgb copy .\data\cars\models\kc-gullwing\shadow.rgb .\runtime\cars\kc-gullwing\shadow.rgb
if exist .\data\cars\models\kc-gullwing\tex-wheel.rgb copy .\data\cars\models\kc-gullwing\tex-wheel.rgb .\runtime\cars\kc-gullwing\tex-wheel.rgb

if exist .\data\cars\models\kc-lightweight\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-lightweight\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-lightweight\*.* call .\create_dir .\runtime\cars\kc-lightweight
rem if exist .\data\cars\models\kc-lightweight\kc-lightweight.ac copy .\data\cars\models\kc-lightweight\kc-lightweight.ac .\runtime\cars\kc-lightweight\kc-lightweight.ac
if exist .\data\cars\models\kc-lightweight\kc-lightweight.acc copy .\data\cars\models\kc-lightweight\kc-lightweight.acc .\runtime\cars\kc-lightweight\kc-lightweight.acc
rem if exist .\data\cars\models\kc-lightweight\kc-lightweight-lod1.ac copy .\data\cars\models\kc-lightweight\kc-lightweight-lod1.ac .\runtime\cars\kc-lightweight\kc-lightweight-lod1.ac
if exist .\data\cars\models\kc-lightweight\kc-lightweight-lod1.acc copy .\data\cars\models\kc-lightweight\kc-lightweight-lod1.acc .\runtime\cars\kc-lightweight\kc-lightweight-lod1.acc
rem if exist .\data\cars\models\kc-lightweight\kc-lightweight-lod2.ac copy .\data\cars\models\kc-lightweight\kc-lightweight-lod2.ac .\runtime\cars\kc-lightweight\kc-lightweight-lod2.ac
if exist .\data\cars\models\kc-lightweight\kc-lightweight-lod2.acc copy .\data\cars\models\kc-lightweight\kc-lightweight-lod2.acc .\runtime\cars\kc-lightweight\kc-lightweight-lod2.acc
rem if exist .\data\cars\models\kc-lightweight\kc-lightweight-lod3.ac copy .\data\cars\models\kc-lightweight\kc-lightweight-lod3.ac .\runtime\cars\kc-lightweight\kc-lightweight-lod3.ac
if exist .\data\cars\models\kc-lightweight\kc-lightweight-lod3.acc copy .\data\cars\models\kc-lightweight\kc-lightweight-lod3.acc .\runtime\cars\kc-lightweight\kc-lightweight-lod3.acc
rem if exist .\data\cars\models\kc-lightweight\kc-lightweight-lod4.ac copy .\data\cars\models\kc-lightweight\kc-lightweight-lod4.ac .\runtime\cars\kc-lightweight\kc-lightweight-lod4.ac
if exist .\data\cars\models\kc-lightweight\kc-lightweight-lod4.acc copy .\data\cars\models\kc-lightweight\kc-lightweight-lod4.acc .\runtime\cars\kc-lightweight\kc-lightweight-lod4.acc
rem if exist .\data\cars\models\kc-lightweight\kc-lightweight.png copy .\data\cars\models\kc-lightweight\kc-lightweight.png .\runtime\cars\kc-lightweight\kc-lightweight.png
if exist .\data\cars\models\kc-lightweight\kc-lightweight.rgb copy .\data\cars\models\kc-lightweight\kc-lightweight.rgb .\runtime\cars\kc-lightweight\kc-lightweight.rgb
if exist .\data\cars\models\kc-lightweight\kc-lightweight.xml copy .\data\cars\models\kc-lightweight\kc-lightweight.xml .\runtime\cars\kc-lightweight\kc-lightweight.xml
rem if exist .\data\cars\models\kc-lightweight\Makefile copy .\data\cars\models\kc-lightweight\Makefile .\runtime\cars\kc-lightweight\Makefile
if exist .\data\cars\models\kc-lightweight\readme.txt copy .\data\cars\models\kc-lightweight\readme.txt .\runtime\cars\kc-lightweight\readme.txt
if exist .\data\cars\models\kc-lightweight\shadow.rgb copy .\data\cars\models\kc-lightweight\shadow.rgb .\runtime\cars\kc-lightweight\shadow.rgb
if exist .\data\cars\models\kc-lightweight\tex-wheel.rgb copy .\data\cars\models\kc-lightweight\tex-wheel.rgb .\runtime\cars\kc-lightweight\tex-wheel.rgb

if exist .\data\cars\models\kc-mangusta\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-mangusta\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-mangusta\*.* call .\create_dir .\runtime\cars\kc-mangusta
rem if exist .\data\cars\models\kc-mangusta\carp.txt copy .\data\cars\models\kc-mangusta\carp.txt .\runtime\cars\kc-mangusta\carp.txt
rem if exist .\data\cars\models\kc-mangusta\kc-mangusta.ac copy .\data\cars\models\kc-mangusta\kc-mangusta.ac .\runtime\cars\kc-mangusta\kc-mangusta.ac
if exist .\data\cars\models\kc-mangusta\kc-mangusta.acc copy .\data\cars\models\kc-mangusta\kc-mangusta.acc .\runtime\cars\kc-mangusta\kc-mangusta.acc
rem if exist .\data\cars\models\kc-mangusta\kc-mangusta-lod1.ac copy .\data\cars\models\kc-mangusta\kc-mangusta-lod1.ac .\runtime\cars\kc-mangusta\kc-mangusta-lod1.ac
if exist .\data\cars\models\kc-mangusta\kc-mangusta-lod1.acc copy .\data\cars\models\kc-mangusta\kc-mangusta-lod1.acc .\runtime\cars\kc-mangusta\kc-mangusta-lod1.acc
rem if exist .\data\cars\models\kc-mangusta\kc-mangusta-lod2.ac copy .\data\cars\models\kc-mangusta\kc-mangusta-lod2.ac .\runtime\cars\kc-mangusta\kc-mangusta-lod2.ac
if exist .\data\cars\models\kc-mangusta\kc-mangusta-lod2.acc copy .\data\cars\models\kc-mangusta\kc-mangusta-lod2.acc .\runtime\cars\kc-mangusta\kc-mangusta-lod2.acc
rem if exist .\data\cars\models\kc-mangusta\kc-mangusta-lod3.ac copy .\data\cars\models\kc-mangusta\kc-mangusta-lod3.ac .\runtime\cars\kc-mangusta\kc-mangusta-lod3.ac
if exist .\data\cars\models\kc-mangusta\kc-mangusta-lod3.acc copy .\data\cars\models\kc-mangusta\kc-mangusta-lod3.acc .\runtime\cars\kc-mangusta\kc-mangusta-lod3.acc
if exist .\data\cars\models\kc-mangusta\kc-mangusta.rgb copy .\data\cars\models\kc-mangusta\kc-mangusta.rgb .\runtime\cars\kc-mangusta\kc-mangusta.rgb
if exist .\data\cars\models\kc-mangusta\kc-mangusta.xml copy .\data\cars\models\kc-mangusta\kc-mangusta.xml .\runtime\cars\kc-mangusta\kc-mangusta.xml
rem if exist .\data\cars\models\kc-mangusta\Makefile copy .\data\cars\models\kc-mangusta\Makefile .\runtime\cars\kc-mangusta\Makefile
rem if exist .\data\cars\models\kc-mangusta\mangusta.ac copy .\data\cars\models\kc-mangusta\mangusta.ac .\runtime\cars\kc-mangusta\mangusta.ac
if exist .\data\cars\models\kc-mangusta\readme.txt copy .\data\cars\models\kc-mangusta\readme.txt .\runtime\cars\kc-mangusta\readme.txt
if exist .\data\cars\models\kc-mangusta\shadow.rgb copy .\data\cars\models\kc-mangusta\shadow.rgb .\runtime\cars\kc-mangusta\shadow.rgb
if exist .\data\cars\models\kc-mangusta\tex-wheel.rgb copy .\data\cars\models\kc-mangusta\tex-wheel.rgb .\runtime\cars\kc-mangusta\tex-wheel.rgb

if exist .\data\cars\models\kc-mclaren\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-mclaren\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-mclaren\*.* call .\create_dir .\runtime\cars\kc-mclaren
rem if exist .\data\cars\models\kc-mclaren\carp.txt copy .\data\cars\models\kc-mclaren\carp.txt .\runtime\cars\kc-mclaren\carp.txt
rem if exist .\data\cars\models\kc-mclaren\kc-mclaren.ac copy .\data\cars\models\kc-mclaren\kc-mclaren.ac .\runtime\cars\kc-mclaren\kc-mclaren.ac
if exist .\data\cars\models\kc-mclaren\kc-mclaren.acc copy .\data\cars\models\kc-mclaren\kc-mclaren.acc .\runtime\cars\kc-mclaren\kc-mclaren.acc
rem if exist .\data\cars\models\kc-mclaren\kc-mclaren-lod1.ac copy .\data\cars\models\kc-mclaren\kc-mclaren-lod1.ac .\runtime\cars\kc-mclaren\kc-mclaren-lod1.ac
if exist .\data\cars\models\kc-mclaren\kc-mclaren-lod1.acc copy .\data\cars\models\kc-mclaren\kc-mclaren-lod1.acc .\runtime\cars\kc-mclaren\kc-mclaren-lod1.acc
rem if exist .\data\cars\models\kc-mclaren\kc-mclaren-lod2.ac copy .\data\cars\models\kc-mclaren\kc-mclaren-lod2.ac .\runtime\cars\kc-mclaren\kc-mclaren-lod2.ac
if exist .\data\cars\models\kc-mclaren\kc-mclaren-lod2.acc copy .\data\cars\models\kc-mclaren\kc-mclaren-lod2.acc .\runtime\cars\kc-mclaren\kc-mclaren-lod2.acc
rem if exist .\data\cars\models\kc-mclaren\kc-mclaren-lod3.ac copy .\data\cars\models\kc-mclaren\kc-mclaren-lod3.ac .\runtime\cars\kc-mclaren\kc-mclaren-lod3.ac
if exist .\data\cars\models\kc-mclaren\kc-mclaren-lod3.acc copy .\data\cars\models\kc-mclaren\kc-mclaren-lod3.acc .\runtime\cars\kc-mclaren\kc-mclaren-lod3.acc
rem if exist .\data\cars\models\kc-mclaren\kc-mclaren-lod4.ac copy .\data\cars\models\kc-mclaren\kc-mclaren-lod4.ac .\runtime\cars\kc-mclaren\kc-mclaren-lod4.ac
if exist .\data\cars\models\kc-mclaren\kc-mclaren-lod4.acc copy .\data\cars\models\kc-mclaren\kc-mclaren-lod4.acc .\runtime\cars\kc-mclaren\kc-mclaren-lod4.acc
if exist .\data\cars\models\kc-mclaren\kc-mclaren.rgb copy .\data\cars\models\kc-mclaren\kc-mclaren.rgb .\runtime\cars\kc-mclaren\kc-mclaren.rgb
if exist .\data\cars\models\kc-mclaren\kc-mclaren.xml copy .\data\cars\models\kc-mclaren\kc-mclaren.xml .\runtime\cars\kc-mclaren\kc-mclaren.xml
rem if exist .\data\cars\models\kc-mclaren\Makefile copy .\data\cars\models\kc-mclaren\Makefile .\runtime\cars\kc-mclaren\Makefile
rem if exist .\data\cars\models\kc-mclaren\mclaren.ac copy .\data\cars\models\kc-mclaren\mclaren.ac .\runtime\cars\kc-mclaren\mclaren.ac
if exist .\data\cars\models\kc-mclaren\readme.txt copy .\data\cars\models\kc-mclaren\readme.txt .\runtime\cars\kc-mclaren\readme.txt
if exist .\data\cars\models\kc-mclaren\shadow.rgb copy .\data\cars\models\kc-mclaren\shadow.rgb .\runtime\cars\kc-mclaren\shadow.rgb
if exist .\data\cars\models\kc-mclaren\tex-wheel.rgb copy .\data\cars\models\kc-mclaren\tex-wheel.rgb .\runtime\cars\kc-mclaren\tex-wheel.rgb

if exist .\data\cars\models\kc-mga\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-mga\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-mga\*.* call .\create_dir .\runtime\cars\kc-mga
rem if exist .\data\cars\models\kc-mga\carp.txt copy .\data\cars\models\kc-mga\carp.txt .\runtime\cars\kc-mga\carp.txt
rem if exist .\data\cars\models\kc-mga\kc-mga.ac copy .\data\cars\models\kc-mga\kc-mga.ac .\runtime\cars\kc-mga\kc-mga.ac
if exist .\data\cars\models\kc-mga\kc-mga.acc copy .\data\cars\models\kc-mga\kc-mga.acc .\runtime\cars\kc-mga\kc-mga.acc
rem if exist .\data\cars\models\kc-mga\kc-mga-lod1.ac copy .\data\cars\models\kc-mga\kc-mga-lod1.ac .\runtime\cars\kc-mga\kc-mga-lod1.ac
if exist .\data\cars\models\kc-mga\kc-mga-lod1.acc copy .\data\cars\models\kc-mga\kc-mga-lod1.acc .\runtime\cars\kc-mga\kc-mga-lod1.acc
rem if exist .\data\cars\models\kc-mga\kc-mga-lod2.ac copy .\data\cars\models\kc-mga\kc-mga-lod2.ac .\runtime\cars\kc-mga\kc-mga-lod2.ac
if exist .\data\cars\models\kc-mga\kc-mga-lod2.acc copy .\data\cars\models\kc-mga\kc-mga-lod2.acc .\runtime\cars\kc-mga\kc-mga-lod2.acc
rem if exist .\data\cars\models\kc-mga\kc-mga-lod3.ac copy .\data\cars\models\kc-mga\kc-mga-lod3.ac .\runtime\cars\kc-mga\kc-mga-lod3.ac
if exist .\data\cars\models\kc-mga\kc-mga-lod3.acc copy .\data\cars\models\kc-mga\kc-mga-lod3.acc .\runtime\cars\kc-mga\kc-mga-lod3.acc
rem if exist .\data\cars\models\kc-mga\kc-mga-lod4.ac copy .\data\cars\models\kc-mga\kc-mga-lod4.ac .\runtime\cars\kc-mga\kc-mga-lod4.ac
if exist .\data\cars\models\kc-mga\kc-mga-lod4.acc copy .\data\cars\models\kc-mga\kc-mga-lod4.acc .\runtime\cars\kc-mga\kc-mga-lod4.acc
if exist .\data\cars\models\kc-mga\kc-mga.rgb copy .\data\cars\models\kc-mga\kc-mga.rgb .\runtime\cars\kc-mga\kc-mga.rgb
rem if exist .\data\cars\models\kc-mga\kc-mga.xcf copy .\data\cars\models\kc-mga\kc-mga.xcf .\runtime\cars\kc-mga\kc-mga.xcf
if exist .\data\cars\models\kc-mga\kc-mga.xml copy .\data\cars\models\kc-mga\kc-mga.xml .\runtime\cars\kc-mga\kc-mga.xml
rem if exist .\data\cars\models\kc-mga\Makefile copy .\data\cars\models\kc-mga\Makefile .\runtime\cars\kc-mga\Makefile
rem if exist .\data\cars\models\kc-mga\mga.ac copy .\data\cars\models\kc-mga\mga.ac .\runtime\cars\kc-mga\mga.ac
if exist .\data\cars\models\kc-mga\readme.txt copy .\data\cars\models\kc-mga\readme.txt .\runtime\cars\kc-mga\readme.txt
if exist .\data\cars\models\kc-mga\shadow.rgb copy .\data\cars\models\kc-mga\shadow.rgb .\runtime\cars\kc-mga\shadow.rgb
if exist .\data\cars\models\kc-mga\tex-wheel.rgb copy .\data\cars\models\kc-mga\tex-wheel.rgb .\runtime\cars\kc-mga\tex-wheel.rgb

if exist .\data\cars\models\kc-mgb\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-mgb\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-mgb\*.* call .\create_dir .\runtime\cars\kc-mgb
rem if exist .\data\cars\models\kc-mgb\car00.tga copy .\data\cars\models\kc-mgb\car00.tga .\runtime\cars\kc-mgb\car00.tga
rem if exist .\data\cars\models\kc-mgb\carp.txt copy .\data\cars\models\kc-mgb\carp.txt .\runtime\cars\kc-mgb\carp.txt
rem if exist .\data\cars\models\kc-mgb\kc-mgb.ac copy .\data\cars\models\kc-mgb\kc-mgb.ac .\runtime\cars\kc-mgb\kc-mgb.ac
if exist .\data\cars\models\kc-mgb\kc-mgb.acc copy .\data\cars\models\kc-mgb\kc-mgb.acc .\runtime\cars\kc-mgb\kc-mgb.acc
rem if exist .\data\cars\models\kc-mgb\kc-mgb-lod1.ac copy .\data\cars\models\kc-mgb\kc-mgb-lod1.ac .\runtime\cars\kc-mgb\kc-mgb-lod1.ac
if exist .\data\cars\models\kc-mgb\kc-mgb-lod1.acc copy .\data\cars\models\kc-mgb\kc-mgb-lod1.acc .\runtime\cars\kc-mgb\kc-mgb-lod1.acc
rem if exist .\data\cars\models\kc-mgb\kc-mgb-lod2.ac copy .\data\cars\models\kc-mgb\kc-mgb-lod2.ac .\runtime\cars\kc-mgb\kc-mgb-lod2.ac
if exist .\data\cars\models\kc-mgb\kc-mgb-lod2.acc copy .\data\cars\models\kc-mgb\kc-mgb-lod2.acc .\runtime\cars\kc-mgb\kc-mgb-lod2.acc
rem if exist .\data\cars\models\kc-mgb\kc-mgb-lod3.ac copy .\data\cars\models\kc-mgb\kc-mgb-lod3.ac .\runtime\cars\kc-mgb\kc-mgb-lod3.ac
if exist .\data\cars\models\kc-mgb\kc-mgb-lod3.acc copy .\data\cars\models\kc-mgb\kc-mgb-lod3.acc .\runtime\cars\kc-mgb\kc-mgb-lod3.acc
rem if exist .\data\cars\models\kc-mgb\kc-mgb-lod4.ac copy .\data\cars\models\kc-mgb\kc-mgb-lod4.ac .\runtime\cars\kc-mgb\kc-mgb-lod4.ac
if exist .\data\cars\models\kc-mgb\kc-mgb-lod4.acc copy .\data\cars\models\kc-mgb\kc-mgb-lod4.acc .\runtime\cars\kc-mgb\kc-mgb-lod4.acc
if exist .\data\cars\models\kc-mgb\kc-mgb.rgb copy .\data\cars\models\kc-mgb\kc-mgb.rgb .\runtime\cars\kc-mgb\kc-mgb.rgb
rem if exist .\data\cars\models\kc-mgb\kc-mgb.xcf copy .\data\cars\models\kc-mgb\kc-mgb.xcf .\runtime\cars\kc-mgb\kc-mgb.xcf
if exist .\data\cars\models\kc-mgb\kc-mgb.xml copy .\data\cars\models\kc-mgb\kc-mgb.xml .\runtime\cars\kc-mgb\kc-mgb.xml
rem if exist .\data\cars\models\kc-mgb\Makefile copy .\data\cars\models\kc-mgb\Makefile .\runtime\cars\kc-mgb\Makefile
rem if exist .\data\cars\models\kc-mgb\mgb.ac copy .\data\cars\models\kc-mgb\mgb.ac .\runtime\cars\kc-mgb\mgb.ac
if exist .\data\cars\models\kc-mgb\readme.txt copy .\data\cars\models\kc-mgb\readme.txt .\runtime\cars\kc-mgb\readme.txt
if exist .\data\cars\models\kc-mgb\shadow.rgb copy .\data\cars\models\kc-mgb\shadow.rgb .\runtime\cars\kc-mgb\shadow.rgb
if exist .\data\cars\models\kc-mgb\tex-wheel.rgb copy .\data\cars\models\kc-mgb\tex-wheel.rgb .\runtime\cars\kc-mgb\tex-wheel.rgb

if exist .\data\cars\models\kc-p4\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-p4\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-p4\*.* call .\create_dir .\runtime\cars\kc-p4
rem if exist .\data\cars\models\kc-p4\car00.tga copy .\data\cars\models\kc-p4\car00.tga .\runtime\cars\kc-p4\car00.tga
rem if exist .\data\cars\models\kc-p4\carp.txt copy .\data\cars\models\kc-p4\carp.txt .\runtime\cars\kc-p4\carp.txt
rem if exist .\data\cars\models\kc-p4\kc-p4.ac copy .\data\cars\models\kc-p4\kc-p4.ac .\runtime\cars\kc-p4\kc-p4.ac
if exist .\data\cars\models\kc-p4\kc-p4.acc copy .\data\cars\models\kc-p4\kc-p4.acc .\runtime\cars\kc-p4\kc-p4.acc
rem if exist .\data\cars\models\kc-p4\kc-p4-lod1.ac copy .\data\cars\models\kc-p4\kc-p4-lod1.ac .\runtime\cars\kc-p4\kc-p4-lod1.ac
if exist .\data\cars\models\kc-p4\kc-p4-lod1.acc copy .\data\cars\models\kc-p4\kc-p4-lod1.acc .\runtime\cars\kc-p4\kc-p4-lod1.acc
rem if exist .\data\cars\models\kc-p4\kc-p4-lod2.ac copy .\data\cars\models\kc-p4\kc-p4-lod2.ac .\runtime\cars\kc-p4\kc-p4-lod2.ac
if exist .\data\cars\models\kc-p4\kc-p4-lod2.acc copy .\data\cars\models\kc-p4\kc-p4-lod2.acc .\runtime\cars\kc-p4\kc-p4-lod2.acc
rem if exist .\data\cars\models\kc-p4\kc-p4-lod3.ac copy .\data\cars\models\kc-p4\kc-p4-lod3.ac .\runtime\cars\kc-p4\kc-p4-lod3.ac
if exist .\data\cars\models\kc-p4\kc-p4-lod3.acc copy .\data\cars\models\kc-p4\kc-p4-lod3.acc .\runtime\cars\kc-p4\kc-p4-lod3.acc
if exist .\data\cars\models\kc-p4\kc-p4.rgb copy .\data\cars\models\kc-p4\kc-p4.rgb .\runtime\cars\kc-p4\kc-p4.rgb
rem if exist .\data\cars\models\kc-p4\kc-p4.xcf copy .\data\cars\models\kc-p4\kc-p4.xcf .\runtime\cars\kc-p4\kc-p4.xcf
if exist .\data\cars\models\kc-p4\kc-p4.xml copy .\data\cars\models\kc-p4\kc-p4.xml .\runtime\cars\kc-p4\kc-p4.xml
rem if exist .\data\cars\models\kc-p4\Makefile copy .\data\cars\models\kc-p4\Makefile .\runtime\cars\kc-p4\Makefile
rem if exist .\data\cars\models\kc-p4\p4.ac copy .\data\cars\models\kc-p4\p4.ac .\runtime\cars\kc-p4\p4.ac
if exist .\data\cars\models\kc-p4\readme.txt copy .\data\cars\models\kc-p4\readme.txt .\runtime\cars\kc-p4\readme.txt
if exist .\data\cars\models\kc-p4\shadow.rgb copy .\data\cars\models\kc-p4\shadow.rgb .\runtime\cars\kc-p4\shadow.rgb
if exist .\data\cars\models\kc-p4\tex-wheel.rgb copy .\data\cars\models\kc-p4\tex-wheel.rgb .\runtime\cars\kc-p4\tex-wheel.rgb

if exist .\data\cars\models\kc-p400s\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-p400s\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-p400s\*.* call .\create_dir .\runtime\cars\kc-p400s
rem if exist .\data\cars\models\kc-p400s\carp.txt copy .\data\cars\models\kc-p400s\carp.txt .\runtime\cars\kc-p400s\carp.txt
rem if exist .\data\cars\models\kc-p400s\kc-p400s.ac copy .\data\cars\models\kc-p400s\kc-p400s.ac .\runtime\cars\kc-p400s\kc-p400s.ac
if exist .\data\cars\models\kc-p400s\kc-p400s.acc copy .\data\cars\models\kc-p400s\kc-p400s.acc .\runtime\cars\kc-p400s\kc-p400s.acc
rem if exist .\data\cars\models\kc-p400s\kc-p400s-lod1.ac copy .\data\cars\models\kc-p400s\kc-p400s-lod1.ac .\runtime\cars\kc-p400s\kc-p400s-lod1.ac
if exist .\data\cars\models\kc-p400s\kc-p400s-lod1.acc copy .\data\cars\models\kc-p400s\kc-p400s-lod1.acc .\runtime\cars\kc-p400s\kc-p400s-lod1.acc
rem if exist .\data\cars\models\kc-p400s\kc-p400s-lod2.ac copy .\data\cars\models\kc-p400s\kc-p400s-lod2.ac .\runtime\cars\kc-p400s\kc-p400s-lod2.ac
if exist .\data\cars\models\kc-p400s\kc-p400s-lod2.acc copy .\data\cars\models\kc-p400s\kc-p400s-lod2.acc .\runtime\cars\kc-p400s\kc-p400s-lod2.acc
rem if exist .\data\cars\models\kc-p400s\kc-p400s-lod3.ac copy .\data\cars\models\kc-p400s\kc-p400s-lod3.ac .\runtime\cars\kc-p400s\kc-p400s-lod3.ac
if exist .\data\cars\models\kc-p400s\kc-p400s-lod3.acc copy .\data\cars\models\kc-p400s\kc-p400s-lod3.acc .\runtime\cars\kc-p400s\kc-p400s-lod3.acc
rem if exist .\data\cars\models\kc-p400s\kc-p400s-lod4.ac copy .\data\cars\models\kc-p400s\kc-p400s-lod4.ac .\runtime\cars\kc-p400s\kc-p400s-lod4.ac
if exist .\data\cars\models\kc-p400s\kc-p400s-lod4.acc copy .\data\cars\models\kc-p400s\kc-p400s-lod4.acc .\runtime\cars\kc-p400s\kc-p400s-lod4.acc
if exist .\data\cars\models\kc-p400s\kc-p400s.rgb copy .\data\cars\models\kc-p400s\kc-p400s.rgb .\runtime\cars\kc-p400s\kc-p400s.rgb
if exist .\data\cars\models\kc-p400s\kc-p400s.xml copy .\data\cars\models\kc-p400s\kc-p400s.xml .\runtime\cars\kc-p400s\kc-p400s.xml
rem if exist .\data\cars\models\kc-p400s\Makefile copy .\data\cars\models\kc-p400s\Makefile .\runtime\cars\kc-p400s\Makefile
rem if exist .\data\cars\models\kc-p400s\p400s.ac copy .\data\cars\models\kc-p400s\p400s.ac .\runtime\cars\kc-p400s\p400s.ac
if exist .\data\cars\models\kc-p400s\readme.txt copy .\data\cars\models\kc-p400s\readme.txt .\runtime\cars\kc-p400s\readme.txt
if exist .\data\cars\models\kc-p400s\shadow.rgb copy .\data\cars\models\kc-p400s\shadow.rgb .\runtime\cars\kc-p400s\shadow.rgb
if exist .\data\cars\models\kc-p400s\tex-wheel.rgb copy .\data\cars\models\kc-p400s\tex-wheel.rgb .\runtime\cars\kc-p400s\tex-wheel.rgb

if exist .\data\cars\models\kc-stratos\*.* call .\create_dir .\runtime
if exist .\data\cars\models\kc-stratos\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\kc-stratos\*.* call .\create_dir .\runtime\cars\kc-stratos
rem if exist .\data\cars\models\kc-stratos\carp.txt copy .\data\cars\models\kc-stratos\carp.txt .\runtime\cars\kc-stratos\carp.txt
rem if exist .\data\cars\models\kc-stratos\kc-stratos.ac copy .\data\cars\models\kc-stratos\kc-stratos.ac .\runtime\cars\kc-stratos\kc-stratos.ac
if exist .\data\cars\models\kc-stratos\kc-stratos.acc copy .\data\cars\models\kc-stratos\kc-stratos.acc .\runtime\cars\kc-stratos\kc-stratos.acc
rem if exist .\data\cars\models\kc-stratos\kc-stratos-lod1.ac copy .\data\cars\models\kc-stratos\kc-stratos-lod1.ac .\runtime\cars\kc-stratos\kc-stratos-lod1.ac
if exist .\data\cars\models\kc-stratos\kc-stratos-lod1.acc copy .\data\cars\models\kc-stratos\kc-stratos-lod1.acc .\runtime\cars\kc-stratos\kc-stratos-lod1.acc
rem if exist .\data\cars\models\kc-stratos\kc-stratos-lod2.ac copy .\data\cars\models\kc-stratos\kc-stratos-lod2.ac .\runtime\cars\kc-stratos\kc-stratos-lod2.ac
if exist .\data\cars\models\kc-stratos\kc-stratos-lod2.acc copy .\data\cars\models\kc-stratos\kc-stratos-lod2.acc .\runtime\cars\kc-stratos\kc-stratos-lod2.acc
rem if exist .\data\cars\models\kc-stratos\kc-stratos-lod3.ac copy .\data\cars\models\kc-stratos\kc-stratos-lod3.ac .\runtime\cars\kc-stratos\kc-stratos-lod3.ac
if exist .\data\cars\models\kc-stratos\kc-stratos-lod3.acc copy .\data\cars\models\kc-stratos\kc-stratos-lod3.acc .\runtime\cars\kc-stratos\kc-stratos-lod3.acc
rem if exist .\data\cars\models\kc-stratos\kc-stratos-lod4.ac copy .\data\cars\models\kc-stratos\kc-stratos-lod4.ac .\runtime\cars\kc-stratos\kc-stratos-lod4.ac
if exist .\data\cars\models\kc-stratos\kc-stratos-lod4.acc copy .\data\cars\models\kc-stratos\kc-stratos-lod4.acc .\runtime\cars\kc-stratos\kc-stratos-lod4.acc
if exist .\data\cars\models\kc-stratos\kc-stratos.rgb copy .\data\cars\models\kc-stratos\kc-stratos.rgb .\runtime\cars\kc-stratos\kc-stratos.rgb
rem if exist .\data\cars\models\kc-stratos\kc-stratos.xcf copy .\data\cars\models\kc-stratos\kc-stratos.xcf .\runtime\cars\kc-stratos\kc-stratos.xcf
if exist .\data\cars\models\kc-stratos\kc-stratos.xml copy .\data\cars\models\kc-stratos\kc-stratos.xml .\runtime\cars\kc-stratos\kc-stratos.xml
rem if exist .\data\cars\models\kc-stratos\Makefile copy .\data\cars\models\kc-stratos\Makefile .\runtime\cars\kc-stratos\Makefile
if exist .\data\cars\models\kc-stratos\readme.txt copy .\data\cars\models\kc-stratos\readme.txt .\runtime\cars\kc-stratos\readme.txt
if exist .\data\cars\models\kc-stratos\shadow.rgb copy .\data\cars\models\kc-stratos\shadow.rgb .\runtime\cars\kc-stratos\shadow.rgb
rem if exist .\data\cars\models\kc-stratos\stratos.ac copy .\data\cars\models\kc-stratos\stratos.ac .\runtime\cars\kc-stratos\stratos.ac
if exist .\data\cars\models\kc-stratos\tex-wheel.rgb copy .\data\cars\models\kc-stratos\tex-wheel.rgb .\runtime\cars\kc-stratos\tex-wheel.rgb

if exist .\data\cars\models\lotus-gt1\*.* call .\create_dir .\runtime
if exist .\data\cars\models\lotus-gt1\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\lotus-gt1\*.* call .\create_dir .\runtime\cars\lotus-gt1
if exist .\data\cars\models\lotus-gt1\lotus-gt1.xml copy .\data\cars\models\lotus-gt1\lotus-gt1.xml .\runtime\cars\lotus-gt1\lotus-gt1.xml
if exist .\data\cars\models\lotus-gt1\lotus-gt1.rgb copy .\data\cars\models\lotus-gt1\lotus-gt1.rgb .\runtime\cars\lotus-gt1\lotus-gt1.rgb
if exist .\data\cars\models\lotus-gt1\tex-wheel.rgb copy .\data\cars\models\lotus-gt1\tex-wheel.rgb .\runtime\cars\lotus-gt1\tex-wheel.rgb
if exist .\data\cars\models\lotus-gt1\shadow.rgb copy .\data\cars\models\lotus-gt1\shadow.rgb .\runtime\cars\lotus-gt1\shadow.rgb
if exist .\data\cars\models\lotus-gt1\lotus-gt1.acc copy .\data\cars\models\lotus-gt1\lotus-gt1.acc .\runtime\cars\lotus-gt1\lotus-gt1.acc
if exist .\data\cars\models\lotus-gt1\lotus-gt1-lod1.acc copy .\data\cars\models\lotus-gt1\lotus-gt1-lod1.acc .\runtime\cars\lotus-gt1\lotus-gt1-lod1.acc
if exist .\data\cars\models\lotus-gt1\lotus-gt1-lod2.acc copy .\data\cars\models\lotus-gt1\lotus-gt1-lod2.acc .\runtime\cars\lotus-gt1\lotus-gt1-lod2.acc
rem if exist .\data\cars\models\lotus-gt1\lotus-gt1-src.acc copy .\data\cars\models\lotus-gt1\lotus-gt1-src.acc .\runtime\cars\lotus-gt1\lotus-gt1-src.acc
if exist .\data\cars\models\lotus-gt1\readme.txt copy .\data\cars\models\lotus-gt1\readme.txt .\runtime\cars\lotus-gt1\readme.txt

if exist .\data\cars\models\mclaren-f1\*.* call .\create_dir .\runtime
if exist .\data\cars\models\mclaren-f1\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\mclaren-f1\*.* call .\create_dir .\runtime\cars\mclaren-f1
if exist .\data\cars\models\mclaren-f1\mclaren-f1.xml copy .\data\cars\models\mclaren-f1\mclaren-f1.xml .\runtime\cars\mclaren-f1\mclaren-f1.xml
if exist .\data\cars\models\mclaren-f1\mclaren-f1.rgb copy .\data\cars\models\mclaren-f1\mclaren-f1.rgb .\runtime\cars\mclaren-f1\mclaren-f1.rgb
if exist .\data\cars\models\mclaren-f1\tex-wheel.rgb copy .\data\cars\models\mclaren-f1\tex-wheel.rgb .\runtime\cars\mclaren-f1\tex-wheel.rgb
if exist .\data\cars\models\mclaren-f1\shadow.rgb copy .\data\cars\models\mclaren-f1\shadow.rgb .\runtime\cars\mclaren-f1\shadow.rgb
if exist .\data\cars\models\mclaren-f1\mclaren-f1.acc copy .\data\cars\models\mclaren-f1\mclaren-f1.acc .\runtime\cars\mclaren-f1\mclaren-f1.acc
if exist .\data\cars\models\mclaren-f1\mclaren-f1-lod1.acc copy .\data\cars\models\mclaren-f1\mclaren-f1-lod1.acc .\runtime\cars\mclaren-f1\mclaren-f1-lod1.acc
if exist .\data\cars\models\mclaren-f1\mclaren-f1-lod2.acc copy .\data\cars\models\mclaren-f1\mclaren-f1-lod2.acc .\runtime\cars\mclaren-f1\mclaren-f1-lod2.acc
if exist .\data\cars\models\mclaren-f1\readme.txt copy .\data\cars\models\mclaren-f1\readme.txt .\runtime\cars\mclaren-f1\readme.txt

if exist .\data\cars\models\p406\*.* call .\create_dir .\runtime
if exist .\data\cars\models\p406\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\p406\*.* call .\create_dir .\runtime\cars\p406
if exist .\data\cars\models\p406\p406.xml copy .\data\cars\models\p406\p406.xml .\runtime\cars\p406\p406.xml
rem if exist .\data\cars\models\p406\texmapper.xml copy .\data\cars\models\p406\texmapper.xml .\runtime\cars\p406\texmapper.xml
if exist .\data\cars\models\p406\p406.acc copy .\data\cars\models\p406\p406.acc .\runtime\cars\p406\p406.acc
if exist .\data\cars\models\p406\p406-lod1.acc copy .\data\cars\models\p406\p406-lod1.acc .\runtime\cars\p406\p406-lod1.acc
if exist .\data\cars\models\p406\p406-lod2.acc copy .\data\cars\models\p406\p406-lod2.acc .\runtime\cars\p406\p406-lod2.acc
if exist .\data\cars\models\p406\p406-lod3.acc copy .\data\cars\models\p406\p406-lod3.acc .\runtime\cars\p406\p406-lod3.acc
if exist .\data\cars\models\p406\p406-lod4.acc copy .\data\cars\models\p406\p406-lod4.acc .\runtime\cars\p406\p406-lod4.acc
if exist .\data\cars\models\p406\p406-lod5.acc copy .\data\cars\models\p406\p406-lod5.acc .\runtime\cars\p406\p406-lod5.acc
if exist .\data\cars\models\p406\p406-lod6.acc copy .\data\cars\models\p406\p406-lod6.acc .\runtime\cars\p406\p406-lod6.acc
if exist .\data\cars\models\p406\p406-lod7.acc copy .\data\cars\models\p406\p406-lod7.acc .\runtime\cars\p406\p406-lod7.acc
rem if exist .\data\cars\models\p406\kmh1.rgb copy .\data\cars\models\p406\kmh1.rgb .\runtime\cars\p406\kmh1.rgb
rem if exist .\data\cars\models\p406\p406-1024.rgb copy .\data\cars\models\p406\p406-1024.rgb .\runtime\cars\p406\p406-1024.rgb
rem if exist .\data\cars\models\p406\p406-512.rgb copy .\data\cars\models\p406\p406-512.rgb .\runtime\cars\p406\p406-512.rgb
if exist .\data\cars\models\p406\p406.rgb copy .\data\cars\models\p406\p406.rgb .\runtime\cars\p406\p406.rgb
rem if exist .\data\cars\models\p406\rpm1.rgb copy .\data\cars\models\p406\rpm1.rgb .\runtime\cars\p406\rpm1.rgb
if exist .\data\cars\models\p406\shadow.rgb copy .\data\cars\models\p406\shadow.rgb .\runtime\cars\p406\shadow.rgb
if exist .\data\cars\models\p406\tex-wheel.rgb copy .\data\cars\models\p406\tex-wheel.rgb .\runtime\cars\p406\tex-wheel.rgb
if exist .\data\cars\models\p406\readme.txt copy .\data\cars\models\p406\readme.txt .\runtime\cars\p406\readme.txt

if exist .\data\cars\models\porsche-gt1\*.* call .\create_dir .\runtime
if exist .\data\cars\models\porsche-gt1\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\porsche-gt1\*.* call .\create_dir .\runtime\cars\porsche-gt1
if exist .\data\cars\models\porsche-gt1\porsche-gt1.xml copy .\data\cars\models\porsche-gt1\porsche-gt1.xml .\runtime\cars\porsche-gt1\porsche-gt1.xml
if exist .\data\cars\models\porsche-gt1\porsche-gt1.rgb copy .\data\cars\models\porsche-gt1\porsche-gt1.rgb .\runtime\cars\porsche-gt1\porsche-gt1.rgb
if exist .\data\cars\models\porsche-gt1\tex-wheel.rgb copy .\data\cars\models\porsche-gt1\tex-wheel.rgb .\runtime\cars\porsche-gt1\tex-wheel.rgb
if exist .\data\cars\models\porsche-gt1\shadow.rgb copy .\data\cars\models\porsche-gt1\shadow.rgb .\runtime\cars\porsche-gt1\shadow.rgb
if exist .\data\cars\models\porsche-gt1\porsche-gt1.acc copy .\data\cars\models\porsche-gt1\porsche-gt1.acc .\runtime\cars\porsche-gt1\porsche-gt1.acc
if exist .\data\cars\models\porsche-gt1\porsche-gt1-lod1.acc copy .\data\cars\models\porsche-gt1\porsche-gt1-lod1.acc .\runtime\cars\porsche-gt1\porsche-gt1-lod1.acc
if exist .\data\cars\models\porsche-gt1\porsche-gt1-lod2.acc copy .\data\cars\models\porsche-gt1\porsche-gt1-lod2.acc .\runtime\cars\porsche-gt1\porsche-gt1-lod2.acc
if exist .\data\cars\models\porsche-gt1\porsche-gt1-lod3.acc copy .\data\cars\models\porsche-gt1\porsche-gt1-lod3.acc .\runtime\cars\porsche-gt1\porsche-gt1-lod3.acc
if exist .\data\cars\models\porsche-gt1\porsche-gt1-lod4.acc copy .\data\cars\models\porsche-gt1\porsche-gt1-lod4.acc .\runtime\cars\porsche-gt1\porsche-gt1-lod4.acc
if exist .\data\cars\models\porsche-gt1\readme.txt copy .\data\cars\models\porsche-gt1\readme.txt .\runtime\cars\porsche-gt1\readme.txt

if exist .\data\cars\models\porsche-gt3rs\*.* call .\create_dir .\runtime
if exist .\data\cars\models\porsche-gt3rs\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\porsche-gt3rs\*.* call .\create_dir .\runtime\cars\porsche-gt3rs
if exist .\data\cars\models\porsche-gt3rs\porsche-gt3rs.xml copy .\data\cars\models\porsche-gt3rs\porsche-gt3rs.xml .\runtime\cars\porsche-gt3rs\porsche-gt3rs.xml
if exist .\data\cars\models\porsche-gt3rs\porsche-gt3rs.rgb copy .\data\cars\models\porsche-gt3rs\porsche-gt3rs.rgb .\runtime\cars\porsche-gt3rs\porsche-gt3rs.rgb
if exist .\data\cars\models\porsche-gt3rs\tex-wheel.rgb copy .\data\cars\models\porsche-gt3rs\tex-wheel.rgb .\runtime\cars\porsche-gt3rs\tex-wheel.rgb
if exist .\data\cars\models\porsche-gt3rs\shadow.rgb copy .\data\cars\models\porsche-gt3rs\shadow.rgb .\runtime\cars\porsche-gt3rs\shadow.rgb
if exist .\data\cars\models\porsche-gt3rs\porsche-gt3rs.acc copy .\data\cars\models\porsche-gt3rs\porsche-gt3rs.acc .\runtime\cars\porsche-gt3rs\porsche-gt3rs.acc
if exist .\data\cars\models\porsche-gt3rs\porsche-gt3rs-lod1.acc copy .\data\cars\models\porsche-gt3rs\porsche-gt3rs-lod1.acc .\runtime\cars\porsche-gt3rs\porsche-gt3rs-lod1.acc
if exist .\data\cars\models\porsche-gt3rs\porsche-gt3rs-lod2.acc copy .\data\cars\models\porsche-gt3rs\porsche-gt3rs-lod2.acc .\runtime\cars\porsche-gt3rs\porsche-gt3rs-lod2.acc
if exist .\data\cars\models\porsche-gt3rs\porsche-gt3rs-lod3.acc copy .\data\cars\models\porsche-gt3rs\porsche-gt3rs-lod3.acc .\runtime\cars\porsche-gt3rs\porsche-gt3rs-lod3.acc
if exist .\data\cars\models\porsche-gt3rs\readme.txt copy .\data\cars\models\porsche-gt3rs\readme.txt .\runtime\cars\porsche-gt3rs\readme.txt

if exist .\data\cars\models\pw-206wrc\*.* call .\create_dir .\runtime
if exist .\data\cars\models\pw-206wrc\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\pw-206wrc\*.* call .\create_dir .\runtime\cars\pw-206wrc
if exist .\data\cars\models\pw-206wrc\pw-206wrc.xml copy .\data\cars\models\pw-206wrc\pw-206wrc.xml .\runtime\cars\pw-206wrc\pw-206wrc.xml
if exist .\data\cars\models\pw-206wrc\pw-206wrc.rgb copy .\data\cars\models\pw-206wrc\pw-206wrc.rgb .\runtime\cars\pw-206wrc\pw-206wrc.rgb
if exist .\data\cars\models\pw-206wrc\shadow.rgb copy .\data\cars\models\pw-206wrc\shadow.rgb .\runtime\cars\pw-206wrc\shadow.rgb
if exist .\data\cars\models\pw-206wrc\tex-wheel.rgb copy .\data\cars\models\pw-206wrc\tex-wheel.rgb .\runtime\cars\pw-206wrc\tex-wheel.rgb
if exist .\data\cars\models\pw-206wrc\pw-206wrc.acc copy .\data\cars\models\pw-206wrc\pw-206wrc.acc .\runtime\cars\pw-206wrc\pw-206wrc.acc
if exist .\data\cars\models\pw-206wrc\pw-206wrc-lod1.acc copy .\data\cars\models\pw-206wrc\pw-206wrc-lod1.acc .\runtime\cars\pw-206wrc\pw-206wrc-lod1.acc
if exist .\data\cars\models\pw-206wrc\pw-206wrc-lod2.acc copy .\data\cars\models\pw-206wrc\pw-206wrc-lod2.acc .\runtime\cars\pw-206wrc\pw-206wrc-lod2.acc
if exist .\data\cars\models\pw-206wrc\readme.txt copy .\data\cars\models\pw-206wrc\readme.txt .\runtime\cars\pw-206wrc\readme.txt

if exist .\data\cars\models\pw-306wrc\*.* call .\create_dir .\runtime
if exist .\data\cars\models\pw-306wrc\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\pw-306wrc\*.* call .\create_dir .\runtime\cars\pw-306wrc
if exist .\data\cars\models\pw-306wrc\pw-306wrc.xml copy .\data\cars\models\pw-306wrc\pw-306wrc.xml .\runtime\cars\pw-306wrc\pw-306wrc.xml
if exist .\data\cars\models\pw-306wrc\pw-306wrc.rgb copy .\data\cars\models\pw-306wrc\pw-306wrc.rgb .\runtime\cars\pw-306wrc\pw-306wrc.rgb
if exist .\data\cars\models\pw-306wrc\shadow.rgb copy .\data\cars\models\pw-306wrc\shadow.rgb .\runtime\cars\pw-306wrc\shadow.rgb
if exist .\data\cars\models\pw-306wrc\tex-wheel.rgb copy .\data\cars\models\pw-306wrc\tex-wheel.rgb .\runtime\cars\pw-306wrc\tex-wheel.rgb
if exist .\data\cars\models\pw-306wrc\pw-306wrc.acc copy .\data\cars\models\pw-306wrc\pw-306wrc.acc .\runtime\cars\pw-306wrc\pw-306wrc.acc
if exist .\data\cars\models\pw-306wrc\pw-306wrc-lod1.acc copy .\data\cars\models\pw-306wrc\pw-306wrc-lod1.acc .\runtime\cars\pw-306wrc\pw-306wrc-lod1.acc
if exist .\data\cars\models\pw-306wrc\pw-306wrc-lod2.acc copy .\data\cars\models\pw-306wrc\pw-306wrc-lod2.acc .\runtime\cars\pw-306wrc\pw-306wrc-lod2.acc
rem if exist .\data\cars\models\pw-306wrc\carp.txt copy .\data\cars\models\pw-306wrc\carp.txt .\runtime\cars\pw-306wrc\carp.txt
if exist .\data\cars\models\pw-306wrc\readme.txt copy .\data\cars\models\pw-306wrc\readme.txt .\runtime\cars\pw-306wrc\readme.txt

if exist .\data\cars\models\pw-corollawrc\*.* call .\create_dir .\runtime
if exist .\data\cars\models\pw-corollawrc\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\pw-corollawrc\*.* call .\create_dir .\runtime\cars\pw-corollawrc
if exist .\data\cars\models\pw-corollawrc\pw-corollawrc.xml copy .\data\cars\models\pw-corollawrc\pw-corollawrc.xml .\runtime\cars\pw-corollawrc\pw-corollawrc.xml
if exist .\data\cars\models\pw-corollawrc\pw-corollawrc.rgb copy .\data\cars\models\pw-corollawrc\pw-corollawrc.rgb .\runtime\cars\pw-corollawrc\pw-corollawrc.rgb
if exist .\data\cars\models\pw-corollawrc\shadow.rgb copy .\data\cars\models\pw-corollawrc\shadow.rgb .\runtime\cars\pw-corollawrc\shadow.rgb
if exist .\data\cars\models\pw-corollawrc\tex-wheel.rgb copy .\data\cars\models\pw-corollawrc\tex-wheel.rgb .\runtime\cars\pw-corollawrc\tex-wheel.rgb
if exist .\data\cars\models\pw-corollawrc\pw-corollawrc.acc copy .\data\cars\models\pw-corollawrc\pw-corollawrc.acc .\runtime\cars\pw-corollawrc\pw-corollawrc.acc
if exist .\data\cars\models\pw-corollawrc\pw-corollawrc-lod1.acc copy .\data\cars\models\pw-corollawrc\pw-corollawrc-lod1.acc .\runtime\cars\pw-corollawrc\pw-corollawrc-lod1.acc
if exist .\data\cars\models\pw-corollawrc\pw-corollawrc-lod2.acc copy .\data\cars\models\pw-corollawrc\pw-corollawrc-lod2.acc .\runtime\cars\pw-corollawrc\pw-corollawrc-lod2.acc
rem if exist .\data\cars\models\pw-corollawrc\carp.txt copy .\data\cars\models\pw-corollawrc\carp.txt .\runtime\cars\pw-corollawrc\carp.txt
if exist .\data\cars\models\pw-corollawrc\readme.txt copy .\data\cars\models\pw-corollawrc\readme.txt .\runtime\cars\pw-corollawrc\readme.txt

if exist .\data\cars\models\pw-evoviwrc\*.* call .\create_dir .\runtime
if exist .\data\cars\models\pw-evoviwrc\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\pw-evoviwrc\*.* call .\create_dir .\runtime\cars\pw-evoviwrc
if exist .\data\cars\models\pw-evoviwrc\pw-evoviwrc.xml copy .\data\cars\models\pw-evoviwrc\pw-evoviwrc.xml .\runtime\cars\pw-evoviwrc\pw-evoviwrc.xml
if exist .\data\cars\models\pw-evoviwrc\pw-evoviwrc.rgb copy .\data\cars\models\pw-evoviwrc\pw-evoviwrc.rgb .\runtime\cars\pw-evoviwrc\pw-evoviwrc.rgb
if exist .\data\cars\models\pw-evoviwrc\shadow.rgb copy .\data\cars\models\pw-evoviwrc\shadow.rgb .\runtime\cars\pw-evoviwrc\shadow.rgb
if exist .\data\cars\models\pw-evoviwrc\tex-wheel.rgb copy .\data\cars\models\pw-evoviwrc\tex-wheel.rgb .\runtime\cars\pw-evoviwrc\tex-wheel.rgb
if exist .\data\cars\models\pw-evoviwrc\pw-evoviwrc.acc copy .\data\cars\models\pw-evoviwrc\pw-evoviwrc.acc .\runtime\cars\pw-evoviwrc\pw-evoviwrc.acc
if exist .\data\cars\models\pw-evoviwrc\pw-evoviwrc-lod1.acc copy .\data\cars\models\pw-evoviwrc\pw-evoviwrc-lod1.acc .\runtime\cars\pw-evoviwrc\pw-evoviwrc-lod1.acc
if exist .\data\cars\models\pw-evoviwrc\pw-evoviwrc-lod2.acc copy .\data\cars\models\pw-evoviwrc\pw-evoviwrc-lod2.acc .\runtime\cars\pw-evoviwrc\pw-evoviwrc-lod2.acc
if exist .\data\cars\models\pw-evoviwrc\readme.txt copy .\data\cars\models\pw-evoviwrc\readme.txt .\runtime\cars\pw-evoviwrc\readme.txt

if exist .\data\cars\models\pw-evovwrc\*.* call .\create_dir .\runtime
if exist .\data\cars\models\pw-evovwrc\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\pw-evovwrc\*.* call .\create_dir .\runtime\cars\pw-evovwrc
if exist .\data\cars\models\pw-evovwrc\pw-evovwrc.xml copy .\data\cars\models\pw-evovwrc\pw-evovwrc.xml .\runtime\cars\pw-evovwrc\pw-evovwrc.xml
if exist .\data\cars\models\pw-evovwrc\pw-evovwrc.rgb copy .\data\cars\models\pw-evovwrc\pw-evovwrc.rgb .\runtime\cars\pw-evovwrc\pw-evovwrc.rgb
if exist .\data\cars\models\pw-evovwrc\shadow.rgb copy .\data\cars\models\pw-evovwrc\shadow.rgb .\runtime\cars\pw-evovwrc\shadow.rgb
if exist .\data\cars\models\pw-evovwrc\tex-wheel.rgb copy .\data\cars\models\pw-evovwrc\tex-wheel.rgb .\runtime\cars\pw-evovwrc\tex-wheel.rgb
if exist .\data\cars\models\pw-evovwrc\pw-evovwrc.acc copy .\data\cars\models\pw-evovwrc\pw-evovwrc.acc .\runtime\cars\pw-evovwrc\pw-evovwrc.acc
if exist .\data\cars\models\pw-evovwrc\pw-evovwrc-lod1.acc copy .\data\cars\models\pw-evovwrc\pw-evovwrc-lod1.acc .\runtime\cars\pw-evovwrc\pw-evovwrc-lod1.acc
if exist .\data\cars\models\pw-evovwrc\pw-evovwrc-lod2.acc copy .\data\cars\models\pw-evovwrc\pw-evovwrc-lod2.acc .\runtime\cars\pw-evovwrc\pw-evovwrc-lod2.acc
rem if exist .\data\cars\models\pw-evovwrc\carp.txt copy .\data\cars\models\pw-evovwrc\carp.txt .\runtime\cars\pw-evovwrc\carp.txt
if exist .\data\cars\models\pw-evovwrc\readme.txt copy .\data\cars\models\pw-evovwrc\readme.txt .\runtime\cars\pw-evovwrc\readme.txt

if exist .\data\cars\models\pw-evovwrc-k\*.* call .\create_dir .\runtime
if exist .\data\cars\models\pw-evovwrc-k\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\pw-evovwrc-k\*.* call .\create_dir .\runtime\cars\pw-evovwrc-k
if exist .\data\cars\models\pw-evovwrc-k\pw-evovwrc-k.xml copy .\data\cars\models\pw-evovwrc-k\pw-evovwrc-k.xml .\runtime\cars\pw-evovwrc-k\pw-evovwrc-k.xml
if exist .\data\cars\models\pw-evovwrc-k\pw-evovwrc-k.rgb copy .\data\cars\models\pw-evovwrc-k\pw-evovwrc-k.rgb .\runtime\cars\pw-evovwrc-k\pw-evovwrc-k.rgb
if exist .\data\cars\models\pw-evovwrc-k\shadow.rgb copy .\data\cars\models\pw-evovwrc-k\shadow.rgb .\runtime\cars\pw-evovwrc-k\shadow.rgb
if exist .\data\cars\models\pw-evovwrc-k\tex-wheel.rgb copy .\data\cars\models\pw-evovwrc-k\tex-wheel.rgb .\runtime\cars\pw-evovwrc-k\tex-wheel.rgb
if exist .\data\cars\models\pw-evovwrc-k\pw-evovwrc-k.acc copy .\data\cars\models\pw-evovwrc-k\pw-evovwrc-k.acc .\runtime\cars\pw-evovwrc-k\pw-evovwrc-k.acc
if exist .\data\cars\models\pw-evovwrc-k\pw-evovwrc-k-lod1.acc copy .\data\cars\models\pw-evovwrc-k\pw-evovwrc-k-lod1.acc .\runtime\cars\pw-evovwrc-k\pw-evovwrc-k-lod1.acc
if exist .\data\cars\models\pw-evovwrc-k\pw-evovwrc-k-lod2.acc copy .\data\cars\models\pw-evovwrc-k\pw-evovwrc-k-lod2.acc .\runtime\cars\pw-evovwrc-k\pw-evovwrc-k-lod2.acc
rem if exist .\data\cars\models\pw-evovwrc-k\carp.txt copy .\data\cars\models\pw-evovwrc-k\carp.txt .\runtime\cars\pw-evovwrc-k\carp.txt
if exist .\data\cars\models\pw-evovwrc-k\readme.txt copy .\data\cars\models\pw-evovwrc-k\readme.txt .\runtime\cars\pw-evovwrc-k\readme.txt

if exist .\data\cars\models\pw-focuswrc\*.* call .\create_dir .\runtime
if exist .\data\cars\models\pw-focuswrc\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\pw-focuswrc\*.* call .\create_dir .\runtime\cars\pw-focuswrc
if exist .\data\cars\models\pw-focuswrc\pw-focuswrc.xml copy .\data\cars\models\pw-focuswrc\pw-focuswrc.xml .\runtime\cars\pw-focuswrc\pw-focuswrc.xml
if exist .\data\cars\models\pw-focuswrc\pw-focuswrc.rgb copy .\data\cars\models\pw-focuswrc\pw-focuswrc.rgb .\runtime\cars\pw-focuswrc\pw-focuswrc.rgb
if exist .\data\cars\models\pw-focuswrc\shadow.rgb copy .\data\cars\models\pw-focuswrc\shadow.rgb .\runtime\cars\pw-focuswrc\shadow.rgb
if exist .\data\cars\models\pw-focuswrc\tex-wheel.rgb copy .\data\cars\models\pw-focuswrc\tex-wheel.rgb .\runtime\cars\pw-focuswrc\tex-wheel.rgb
if exist .\data\cars\models\pw-focuswrc\pw-focuswrc.acc copy .\data\cars\models\pw-focuswrc\pw-focuswrc.acc .\runtime\cars\pw-focuswrc\pw-focuswrc.acc
if exist .\data\cars\models\pw-focuswrc\pw-focuswrc-lod1.acc copy .\data\cars\models\pw-focuswrc\pw-focuswrc-lod1.acc .\runtime\cars\pw-focuswrc\pw-focuswrc-lod1.acc
if exist .\data\cars\models\pw-focuswrc\pw-focuswrc-lod2.acc copy .\data\cars\models\pw-focuswrc\pw-focuswrc-lod2.acc .\runtime\cars\pw-focuswrc\pw-focuswrc-lod2.acc
rem if exist .\data\cars\models\pw-focuswrc\carp.txt copy .\data\cars\models\pw-focuswrc\carp.txt .\runtime\cars\pw-focuswrc\carp.txt
if exist .\data\cars\models\pw-focuswrc\readme.txt copy .\data\cars\models\pw-focuswrc\readme.txt .\runtime\cars\pw-focuswrc\readme.txt

if exist .\data\cars\models\pw-imprezawrc\*.* call .\create_dir .\runtime
if exist .\data\cars\models\pw-imprezawrc\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\pw-imprezawrc\*.* call .\create_dir .\runtime\cars\pw-imprezawrc
if exist .\data\cars\models\pw-imprezawrc\pw-imprezawrc.xml copy .\data\cars\models\pw-imprezawrc\pw-imprezawrc.xml .\runtime\cars\pw-imprezawrc\pw-imprezawrc.xml
if exist .\data\cars\models\pw-imprezawrc\pw-imprezawrc.rgb copy .\data\cars\models\pw-imprezawrc\pw-imprezawrc.rgb .\runtime\cars\pw-imprezawrc\pw-imprezawrc.rgb
if exist .\data\cars\models\pw-imprezawrc\shadow.rgb copy .\data\cars\models\pw-imprezawrc\shadow.rgb .\runtime\cars\pw-imprezawrc\shadow.rgb
if exist .\data\cars\models\pw-imprezawrc\tex-wheel.rgb copy .\data\cars\models\pw-imprezawrc\tex-wheel.rgb .\runtime\cars\pw-imprezawrc\tex-wheel.rgb
if exist .\data\cars\models\pw-imprezawrc\pw-imprezawrc.acc copy .\data\cars\models\pw-imprezawrc\pw-imprezawrc.acc .\runtime\cars\pw-imprezawrc\pw-imprezawrc.acc
if exist .\data\cars\models\pw-imprezawrc\pw-imprezawrc-lod1.acc copy .\data\cars\models\pw-imprezawrc\pw-imprezawrc-lod1.acc .\runtime\cars\pw-imprezawrc\pw-imprezawrc-lod1.acc
if exist .\data\cars\models\pw-imprezawrc\pw-imprezawrc-lod2.acc copy .\data\cars\models\pw-imprezawrc\pw-imprezawrc-lod2.acc .\runtime\cars\pw-imprezawrc\pw-imprezawrc-lod2.acc
rem if exist .\data\cars\models\pw-imprezawrc\carp.txt copy .\data\cars\models\pw-imprezawrc\carp.txt .\runtime\cars\pw-imprezawrc\carp.txt
if exist .\data\cars\models\pw-imprezawrc\readme.txt copy .\data\cars\models\pw-imprezawrc\readme.txt .\runtime\cars\pw-imprezawrc\readme.txt

if exist .\data\cars\models\viper-gts-r\*.* call .\create_dir .\runtime
if exist .\data\cars\models\viper-gts-r\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\viper-gts-r\*.* call .\create_dir .\runtime\cars\viper-gts-r
if exist .\data\cars\models\viper-gts-r\viper-gts-r.xml copy .\data\cars\models\viper-gts-r\viper-gts-r.xml .\runtime\cars\viper-gts-r\viper-gts-r.xml
if exist .\data\cars\models\viper-gts-r\viper-gts-r.rgb copy .\data\cars\models\viper-gts-r\viper-gts-r.rgb .\runtime\cars\viper-gts-r\viper-gts-r.rgb
if exist .\data\cars\models\viper-gts-r\tex-wheel.rgb copy .\data\cars\models\viper-gts-r\tex-wheel.rgb .\runtime\cars\viper-gts-r\tex-wheel.rgb
if exist .\data\cars\models\viper-gts-r\shadow.rgb copy .\data\cars\models\viper-gts-r\shadow.rgb .\runtime\cars\viper-gts-r\shadow.rgb
if exist .\data\cars\models\viper-gts-r\viper-gts-r.acc copy .\data\cars\models\viper-gts-r\viper-gts-r.acc .\runtime\cars\viper-gts-r\viper-gts-r.acc
if exist .\data\cars\models\viper-gts-r\viper-gts-r-lod1.acc copy .\data\cars\models\viper-gts-r\viper-gts-r-lod1.acc .\runtime\cars\viper-gts-r\viper-gts-r-lod1.acc
if exist .\data\cars\models\viper-gts-r\viper-gts-r-lod2.acc copy .\data\cars\models\viper-gts-r\viper-gts-r-lod2.acc .\runtime\cars\viper-gts-r\viper-gts-r-lod2.acc
if exist .\data\cars\models\viper-gts-r\readme.txt copy .\data\cars\models\viper-gts-r\readme.txt .\runtime\cars\viper-gts-r\readme.txt

if exist .\data\cars\models\vm-x2\*.* call .\create_dir .\runtime
if exist .\data\cars\models\vm-x2\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\vm-x2\*.* call .\create_dir .\runtime\cars\vm-x2
if exist .\data\cars\models\vm-x2\readme.txt copy .\data\cars\models\vm-x2\readme.txt .\runtime\cars\vm-x2\readme.txt
rem if exist .\data\cars\models\vm-x2\texmapper.xml copy .\data\cars\models\vm-x2\texmapper.xml .\runtime\cars\vm-x2\texmapper.xml
if exist .\data\cars\models\vm-x2\vm-x2.xml copy .\data\cars\models\vm-x2\vm-x2.xml .\runtime\cars\vm-x2\vm-x2.xml
if exist .\data\cars\models\vm-x2\vm-x2.acc copy .\data\cars\models\vm-x2\vm-x2.acc .\runtime\cars\vm-x2\vm-x2.acc
if exist .\data\cars\models\vm-x2\vm-x2-lod1.acc copy .\data\cars\models\vm-x2\vm-x2-lod1.acc .\runtime\cars\vm-x2\vm-x2-lod1.acc
if exist .\data\cars\models\vm-x2\vm-x2-lod2.acc copy .\data\cars\models\vm-x2\vm-x2-lod2.acc .\runtime\cars\vm-x2\vm-x2-lod2.acc
if exist .\data\cars\models\vm-x2\vm-x2-lod3.acc copy .\data\cars\models\vm-x2\vm-x2-lod3.acc .\runtime\cars\vm-x2\vm-x2-lod3.acc
if exist .\data\cars\models\vm-x2\vm-x2-lod4.acc copy .\data\cars\models\vm-x2\vm-x2-lod4.acc .\runtime\cars\vm-x2\vm-x2-lod4.acc
if exist .\data\cars\models\vm-x2\shadow.rgb copy .\data\cars\models\vm-x2\shadow.rgb .\runtime\cars\vm-x2\shadow.rgb
if exist .\data\cars\models\vm-x2\tex-wheel.rgb copy .\data\cars\models\vm-x2\tex-wheel.rgb .\runtime\cars\vm-x2\tex-wheel.rgb
if exist .\data\cars\models\vm-x2\vm-x2.rgb copy .\data\cars\models\vm-x2\vm-x2.rgb .\runtime\cars\vm-x2\vm-x2.rgb

if exist .\data\cars\models\vm-x4\*.* call .\create_dir .\runtime
if exist .\data\cars\models\vm-x4\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\vm-x4\*.* call .\create_dir .\runtime\cars\vm-x4
if exist .\data\cars\models\vm-x4\readme.txt copy .\data\cars\models\vm-x4\readme.txt .\runtime\cars\vm-x4\readme.txt
rem if exist .\data\cars\models\vm-x4\texmapper.xml copy .\data\cars\models\vm-x4\texmapper.xml .\runtime\cars\vm-x4\texmapper.xml
if exist .\data\cars\models\vm-x4\vm-x4.xml copy .\data\cars\models\vm-x4\vm-x4.xml .\runtime\cars\vm-x4\vm-x4.xml
if exist .\data\cars\models\vm-x4\shadow.rgb copy .\data\cars\models\vm-x4\shadow.rgb .\runtime\cars\vm-x4\shadow.rgb
if exist .\data\cars\models\vm-x4\tex-wheel.rgb copy .\data\cars\models\vm-x4\tex-wheel.rgb .\runtime\cars\vm-x4\tex-wheel.rgb
if exist .\data\cars\models\vm-x4\vm-x4.rgb copy .\data\cars\models\vm-x4\vm-x4.rgb .\runtime\cars\vm-x4\vm-x4.rgb
if exist .\data\cars\models\vm-x4\vm-x4.acc copy .\data\cars\models\vm-x4\vm-x4.acc .\runtime\cars\vm-x4\vm-x4.acc
if exist .\data\cars\models\vm-x4\vm-x4-lod1.acc copy .\data\cars\models\vm-x4\vm-x4-lod1.acc .\runtime\cars\vm-x4\vm-x4-lod1.acc
if exist .\data\cars\models\vm-x4\vm-x4-lod2.acc copy .\data\cars\models\vm-x4\vm-x4-lod2.acc .\runtime\cars\vm-x4\vm-x4-lod2.acc
if exist .\data\cars\models\vm-x4\vm-x4-lod3.acc copy .\data\cars\models\vm-x4\vm-x4-lod3.acc .\runtime\cars\vm-x4\vm-x4-lod3.acc
if exist .\data\cars\models\vm-x4\vm-x4-lod4.acc copy .\data\cars\models\vm-x4\vm-x4-lod4.acc .\runtime\cars\vm-x4\vm-x4-lod4.acc

if exist .\data\cars\models\xj-220\*.* call .\create_dir .\runtime
if exist .\data\cars\models\xj-220\*.* call .\create_dir .\runtime\cars
if exist .\data\cars\models\xj-220\*.* call .\create_dir .\runtime\cars\xj-220
if exist .\data\cars\models\xj-220\xj-220.xml copy .\data\cars\models\xj-220\xj-220.xml .\runtime\cars\xj-220\xj-220.xml
if exist .\data\cars\models\xj-220\xj-220.rgb copy .\data\cars\models\xj-220\xj-220.rgb .\runtime\cars\xj-220\xj-220.rgb
if exist .\data\cars\models\xj-220\tex-wheel.rgb copy .\data\cars\models\xj-220\tex-wheel.rgb .\runtime\cars\xj-220\tex-wheel.rgb
if exist .\data\cars\models\xj-220\shadow.rgb copy .\data\cars\models\xj-220\shadow.rgb .\runtime\cars\xj-220\shadow.rgb
if exist .\data\cars\models\xj-220\xj-220.acc copy .\data\cars\models\xj-220\xj-220.acc .\runtime\cars\xj-220\xj-220.acc
if exist .\data\cars\models\xj-220\xj-220-lod1.acc copy .\data\cars\models\xj-220\xj-220-lod1.acc .\runtime\cars\xj-220\xj-220-lod1.acc
if exist .\data\cars\models\xj-220\xj-220-lod2.acc copy .\data\cars\models\xj-220\xj-220-lod2.acc .\runtime\cars\xj-220\xj-220-lod2.acc
if exist .\data\cars\models\xj-220\readme.txt copy .\data\cars\models\xj-220\readme.txt .\runtime\cars\xj-220\readme.txt

if exist .\data\data\fonts\*.* call .\create_dir .\runtime
if exist .\data\data\fonts\*.* call .\create_dir .\runtime\data
if exist .\data\data\fonts\*.* call .\create_dir .\runtime\data\fonts
if exist .\data\data\fonts\b5.glf copy .\data\data\fonts\b5.glf .\runtime\data\fonts\b5.glf
if exist .\data\data\fonts\b6.glf copy .\data\data\fonts\b6.glf .\runtime\data\fonts\b6.glf
if exist .\data\data\fonts\b7.glf copy .\data\data\fonts\b7.glf .\runtime\data\fonts\b7.glf
if exist .\data\data\fonts\digital.glf copy .\data\data\fonts\digital.glf .\runtime\data\fonts\digital.glf
if exist .\data\data\fonts\fragile.glf copy .\data\data\fonts\fragile.glf .\runtime\data\fonts\fragile.glf

if exist .\data\data\img\*.* call .\create_dir .\runtime
if exist .\data\data\img\*.* call .\create_dir .\runtime\data
if exist .\data\data\img\*.* call .\create_dir .\runtime\data\img
if exist .\data\data\img\arrow-down.png copy .\data\data\img\arrow-down.png .\runtime\data\img\arrow-down.png
if exist .\data\data\img\arrow-down-pushed.png copy .\data\data\img\arrow-down-pushed.png .\runtime\data\img\arrow-down-pushed.png
if exist .\data\data\img\arrow-left.png copy .\data\data\img\arrow-left.png .\runtime\data\img\arrow-left.png
if exist .\data\data\img\arrow-left-pushed.png copy .\data\data\img\arrow-left-pushed.png .\runtime\data\img\arrow-left-pushed.png
if exist .\data\data\img\arrow-right.png copy .\data\data\img\arrow-right.png .\runtime\data\img\arrow-right.png
if exist .\data\data\img\arrow-right-pushed.png copy .\data\data\img\arrow-right-pushed.png .\runtime\data\img\arrow-right-pushed.png
if exist .\data\data\img\arrow-up.png copy .\data\data\img\arrow-up.png .\runtime\data\img\arrow-up.png
if exist .\data\data\img\arrow-up-pushed.png copy .\data\data\img\arrow-up-pushed.png .\runtime\data\img\arrow-up-pushed.png
if exist .\data\data\img\ruler.png copy .\data\data\img\ruler.png .\runtime\data\img\ruler.png
if exist .\data\data\img\ruler-pushed.png copy .\data\data\img\ruler-pushed.png .\runtime\data\img\ruler-pushed.png
if exist .\data\data\img\splash-ctrlconf.png copy .\data\data\img\splash-ctrlconf.png .\runtime\data\img\splash-ctrlconf.png
if exist .\data\data\img\splash-dtm.png copy .\data\data\img\splash-dtm.png .\runtime\data\img\splash-dtm.png
if exist .\data\data\img\splash-dtmstart.png copy .\data\data\img\splash-dtmstart.png .\runtime\data\img\splash-dtmstart.png
if exist .\data\data\img\splash-filesel.png copy .\data\data\img\splash-filesel.png .\runtime\data\img\splash-filesel.png
if exist .\data\data\img\splash-graphconf.png copy .\data\data\img\splash-graphconf.png .\runtime\data\img\splash-graphconf.png
if exist .\data\data\img\splash-graphic.png copy .\data\data\img\splash-graphic.png .\runtime\data\img\splash-graphic.png
if exist .\data\data\img\splash-joycal.png copy .\data\data\img\splash-joycal.png .\runtime\data\img\splash-joycal.png
if exist .\data\data\img\splash-joyconf.png copy .\data\data\img\splash-joyconf.png .\runtime\data\img\splash-joyconf.png
if exist .\data\data\img\splash-keyconf.png copy .\data\data\img\splash-keyconf.png .\runtime\data\img\splash-keyconf.png
if exist .\data\data\img\splash-main.png copy .\data\data\img\splash-main.png .\runtime\data\img\splash-main.png
if exist .\data\data\img\splash-mousecal.png copy .\data\data\img\splash-mousecal.png .\runtime\data\img\splash-mousecal.png
if exist .\data\data\img\splash-mouseconf.png copy .\data\data\img\splash-mouseconf.png .\runtime\data\img\splash-mouseconf.png
if exist .\data\data\img\splash-options.png copy .\data\data\img\splash-options.png .\runtime\data\img\splash-options.png
if exist .\data\data\img\splash.png copy .\data\data\img\splash.png .\runtime\data\img\splash.png
if exist .\data\data\img\splash-practice.png copy .\data\data\img\splash-practice.png .\runtime\data\img\splash-practice.png
if exist .\data\data\img\splash-prsess.png copy .\data\data\img\splash-prsess.png .\runtime\data\img\splash-prsess.png
if exist .\data\data\img\splash-qrdrv.png copy .\data\data\img\splash-qrdrv.png .\runtime\data\img\splash-qrdrv.png
if exist .\data\data\img\splash-qrloading.png copy .\data\data\img\splash-qrloading.png .\runtime\data\img\splash-qrloading.png
if exist .\data\data\img\splash-qr.png copy .\data\data\img\splash-qr.png .\runtime\data\img\splash-qr.png
if exist .\data\data\img\splash-qrtrk.png copy .\data\data\img\splash-qrtrk.png .\runtime\data\img\splash-qrtrk.png
if exist .\data\data\img\splash-quit.png copy .\data\data\img\splash-quit.png .\runtime\data\img\splash-quit.png
if exist .\data\data\img\splash-raceopt.png copy .\data\data\img\splash-raceopt.png .\runtime\data\img\splash-raceopt.png
if exist .\data\data\img\splash-result.png copy .\data\data\img\splash-result.png .\runtime\data\img\splash-result.png
if exist .\data\data\img\splash-run-practice.png copy .\data\data\img\splash-run-practice.png .\runtime\data\img\splash-run-practice.png
if exist .\data\data\img\splash-single-player.png copy .\data\data\img\splash-single-player.png .\runtime\data\img\splash-single-player.png
if exist .\data\data\img\splash-simucfg.png copy .\data\data\img\splash-simucfg.png .\runtime\data\img\splash-simucfg.png

if exist .\data\data\menu\*.* call .\create_dir .\runtime
if exist .\data\data\menu\*.* call .\create_dir .\runtime\menu
if exist .\data\data\menu\entry.xml copy .\data\data\menu\entry.xml .\runtime\menu\entry.xml

if exist .\data\data\objects\*.* call .\create_dir .\runtime
if exist .\data\data\objects\*.* call .\create_dir .\runtime\data
if exist .\data\data\objects\*.* call .\create_dir .\runtime\data\objects
if exist .\data\data\objects\ad1.ac copy .\data\data\objects\ad1.ac .\runtime\data\objects\ad1.ac
if exist .\data\data\objects\bridge.ac copy .\data\data\objects\bridge.ac .\runtime\data\objects\bridge.ac
if exist .\data\data\objects\bridge-arch.ac copy .\data\data\objects\bridge-arch.ac .\runtime\data\objects\bridge-arch.ac
if exist .\data\data\objects\building1.ac copy .\data\data\objects\building1.ac .\runtime\data\objects\building1.ac
if exist .\data\data\objects\building2.ac copy .\data\data\objects\building2.ac .\runtime\data\objects\building2.ac
if exist .\data\data\objects\forest1.ac copy .\data\data\objects\forest1.ac .\runtime\data\objects\forest1.ac
if exist .\data\data\objects\forest2.ac copy .\data\data\objects\forest2.ac .\runtime\data\objects\forest2.ac
if exist .\data\data\objects\forest3.ac copy .\data\data\objects\forest3.ac .\runtime\data\objects\forest3.ac
if exist .\data\data\objects\needle.ac copy .\data\data\objects\needle.ac .\runtime\data\objects\needle.ac
if exist .\data\data\objects\stadium1.ac copy .\data\data\objects\stadium1.ac .\runtime\data\objects\stadium1.ac
if exist .\data\data\objects\stand-inter.ac copy .\data\data\objects\stand-inter.ac .\runtime\data\objects\stand-inter.ac
if exist .\data\data\objects\stand-main.ac copy .\data\data\objects\stand-main.ac .\runtime\data\objects\stand-main.ac
if exist .\data\data\objects\stand-wall.ac copy .\data\data\objects\stand-wall.ac .\runtime\data\objects\stand-wall.ac
if exist .\data\data\objects\tree10.ac copy .\data\data\objects\tree10.ac .\runtime\data\objects\tree10.ac
if exist .\data\data\objects\tree11.ac copy .\data\data\objects\tree11.ac .\runtime\data\objects\tree11.ac
if exist .\data\data\objects\tree12.ac copy .\data\data\objects\tree12.ac .\runtime\data\objects\tree12.ac
if exist .\data\data\objects\tree13.ac copy .\data\data\objects\tree13.ac .\runtime\data\objects\tree13.ac
if exist .\data\data\objects\tree14.ac copy .\data\data\objects\tree14.ac .\runtime\data\objects\tree14.ac
if exist .\data\data\objects\tree15.ac copy .\data\data\objects\tree15.ac .\runtime\data\objects\tree15.ac
if exist .\data\data\objects\tree16.ac copy .\data\data\objects\tree16.ac .\runtime\data\objects\tree16.ac
if exist .\data\data\objects\tree17.ac copy .\data\data\objects\tree17.ac .\runtime\data\objects\tree17.ac
if exist .\data\data\objects\tree1.ac copy .\data\data\objects\tree1.ac .\runtime\data\objects\tree1.ac
if exist .\data\data\objects\tree2.ac copy .\data\data\objects\tree2.ac .\runtime\data\objects\tree2.ac
if exist .\data\data\objects\tree3.ac copy .\data\data\objects\tree3.ac .\runtime\data\objects\tree3.ac
if exist .\data\data\objects\tree4.ac copy .\data\data\objects\tree4.ac .\runtime\data\objects\tree4.ac
if exist .\data\data\objects\tree5.ac copy .\data\data\objects\tree5.ac .\runtime\data\objects\tree5.ac
if exist .\data\data\objects\tree6.ac copy .\data\data\objects\tree6.ac .\runtime\data\objects\tree6.ac
if exist .\data\data\objects\tree7.ac copy .\data\data\objects\tree7.ac .\runtime\data\objects\tree7.ac
if exist .\data\data\objects\tree8.ac copy .\data\data\objects\tree8.ac .\runtime\data\objects\tree8.ac
if exist .\data\data\objects\tree9.ac copy .\data\data\objects\tree9.ac .\runtime\data\objects\tree9.ac
if exist .\data\data\objects\treeg1.ac copy .\data\data\objects\treeg1.ac .\runtime\data\objects\treeg1.ac

if exist .\data\data\sound\*.* call .\create_dir .\runtime
if exist .\data\data\sound\*.* call .\create_dir .\runtime\data
if exist .\data\data\sound\*.* call .\create_dir .\runtime\data\sound
if exist .\data\data\sound\axle.wav copy .\data\data\sound\axle.wav .\runtime\data\sound\axle.wav
if exist .\data\data\sound\boom.wav copy .\data\data\sound\boom.wav .\runtime\data\sound\boom.wav
if exist .\data\data\sound\bottom_crash.wav copy .\data\data\sound\bottom_crash.wav .\runtime\data\sound\bottom_crash.wav
if exist .\data\data\sound\corolla1400hi2.wav copy .\data\data\sound\corolla1400hi2.wav .\runtime\data\sound\corolla1400hi2.wav
if exist .\data\data\sound\corolla1400hi.wav copy .\data\data\sound\corolla1400hi.wav .\runtime\data\sound\corolla1400hi.wav
if exist .\data\data\sound\corolla1400.wav copy .\data\data\sound\corolla1400.wav .\runtime\data\sound\corolla1400.wav
if exist .\data\data\sound\corolla1.wav copy .\data\data\sound\corolla1.wav .\runtime\data\sound\corolla1.wav
if exist .\data\data\sound\corolla_l.wav copy .\data\data\sound\corolla_l.wav .\runtime\data\sound\corolla_l.wav
if exist .\data\data\sound\crash1.wav copy .\data\data\sound\crash1.wav .\runtime\data\sound\crash1.wav
if exist .\data\data\sound\crash2.wav copy .\data\data\sound\crash2.wav .\runtime\data\sound\crash2.wav
if exist .\data\data\sound\crash3.wav copy .\data\data\sound\crash3.wav .\runtime\data\sound\crash3.wav
if exist .\data\data\sound\crash4.wav copy .\data\data\sound\crash4.wav .\runtime\data\sound\crash4.wav
if exist .\data\data\sound\crash5.wav copy .\data\data\sound\crash5.wav .\runtime\data\sound\crash5.wav
if exist .\data\data\sound\crash6.wav copy .\data\data\sound\crash6.wav .\runtime\data\sound\crash6.wav
if exist .\data\data\sound\engine-10.wav copy .\data\data\sound\engine-10.wav .\runtime\data\sound\engine-10.wav
if exist .\data\data\sound\engine-11.wav copy .\data\data\sound\engine-11.wav .\runtime\data\sound\engine-11.wav
if exist .\data\data\sound\engine-12.wav copy .\data\data\sound\engine-12.wav .\runtime\data\sound\engine-12.wav
if exist .\data\data\sound\engine-1.wav copy .\data\data\sound\engine-1.wav .\runtime\data\sound\engine-1.wav
if exist .\data\data\sound\engine-2t.wav copy .\data\data\sound\engine-2t.wav .\runtime\data\sound\engine-2t.wav
if exist .\data\data\sound\engine-2.wav copy .\data\data\sound\engine-2.wav .\runtime\data\sound\engine-2.wav
if exist .\data\data\sound\engine-3.wav copy .\data\data\sound\engine-3.wav .\runtime\data\sound\engine-3.wav
if exist .\data\data\sound\engine-4.wav copy .\data\data\sound\engine-4.wav .\runtime\data\sound\engine-4.wav
if exist .\data\data\sound\engine-5.wav copy .\data\data\sound\engine-5.wav .\runtime\data\sound\engine-5.wav
if exist .\data\data\sound\engine-7.wav copy .\data\data\sound\engine-7.wav .\runtime\data\sound\engine-7.wav
if exist .\data\data\sound\engine-8.wav copy .\data\data\sound\engine-8.wav .\runtime\data\sound\engine-8.wav
if exist .\data\data\sound\engine-9.wav copy .\data\data\sound\engine-9.wav .\runtime\data\sound\engine-9.wav
if exist .\data\data\sound\engine-torcs.wav copy .\data\data\sound\engine-torcs.wav .\runtime\data\sound\engine-torcs.wav
if exist .\data\data\sound\ferrarif355.wav copy .\data\data\sound\ferrarif355.wav .\runtime\data\sound\ferrarif355.wav
if exist .\data\data\sound\ferrarif50.wav copy .\data\data\sound\ferrarif50.wav .\runtime\data\sound\ferrarif50.wav
if exist .\data\data\sound\lamborghinidiablo_lp.wav copy .\data\data\sound\lamborghinidiablo_lp.wav .\runtime\data\sound\lamborghinidiablo_lp.wav
if exist .\data\data\sound\lamborghinidiablo.wav copy .\data\data\sound\lamborghinidiablo.wav .\runtime\data\sound\lamborghinidiablo.wav
if exist .\data\data\sound\locked.wav copy .\data\data\sound\locked.wav .\runtime\data\sound\locked.wav
if exist .\data\data\sound\mclarenf1.wav copy .\data\data\sound\mclarenf1.wav .\runtime\data\sound\mclarenf1.wav
if exist .\data\data\sound\out_of_road-3.wav copy .\data\data\sound\out_of_road-3.wav .\runtime\data\sound\out_of_road-3.wav
if exist .\data\data\sound\out_of_road.wav copy .\data\data\sound\out_of_road.wav .\runtime\data\sound\out_of_road.wav
if exist .\data\data\sound\road-ride.wav copy .\data\data\sound\road-ride.wav .\runtime\data\sound\road-ride.wav
if exist .\data\data\sound\skid_metal.wav copy .\data\data\sound\skid_metal.wav .\runtime\data\sound\skid_metal.wav
if exist .\data\data\sound\skid_tyres.wav copy .\data\data\sound\skid_tyres.wav .\runtime\data\sound\skid_tyres.wav
if exist .\data\data\sound\skid.wav copy .\data\data\sound\skid.wav .\runtime\data\sound\skid.wav
if exist .\data\data\sound\test.wav copy .\data\data\sound\test.wav .\runtime\data\sound\test.wav
if exist .\data\data\sound\ford1b.wav copy .\data\data\sound\ford1b.wav .\runtime\data\sound\ford1b.wav
if exist .\data\data\sound\gear_change1.wav copy .\data\data\sound\gear_change1.wav .\runtime\data\sound\gear_change1.wav
if exist .\data\data\sound\backfire.wav copy .\data\data\sound\backfire.wav .\runtime\data\sound\backfire.wav
if exist .\data\data\sound\backfire_loop.wav copy .\data\data\sound\backfire_loop.wav .\runtime\data\sound\backfire_loop.wav
if exist .\data\data\sound\viper2.wav copy .\data\data\sound\viper2.wav .\runtime\data\sound\viper2.wav
if exist .\data\data\sound\ford2c.wav copy .\data\data\sound\ford2c.wav .\runtime\data\sound\ford2c.wav
if exist .\data\data\sound\206_engine.wav copy .\data\data\sound\206_engine.wav .\runtime\data\sound\206_engine.wav
if exist .\data\data\sound\evo7_engine_f.wav copy .\data\data\sound\evo7_engine_f.wav .\runtime\data\sound\evo7_engine_f.wav
if exist .\data\data\sound\evo7_engine.wav copy .\data\data\sound\evo7_engine.wav .\runtime\data\sound\evo7_engine.wav
if exist .\data\data\sound\impreza2002_engine.wav copy .\data\data\sound\impreza2002_engine.wav .\runtime\data\sound\impreza2002_engine.wav
if exist .\data\data\sound\porsche_engine.wav copy .\data\data\sound\porsche_engine.wav .\runtime\data\sound\porsche_engine.wav



if exist .\data\data\textures\*.* call .\create_dir .\runtime
if exist .\data\data\textures\*.* call .\create_dir .\runtime\data
if exist .\data\data\textures\*.* call .\create_dir .\runtime\data\textures
if exist .\data\data\textures\background.png copy .\data\data\textures\background.png .\runtime\data\textures\background.png
if exist .\data\data\textures\bushes_side.png copy .\data\data\textures\bushes_side.png .\runtime\data\textures\bushes_side.png
if exist .\data\data\textures\cut_red_earth_side.png copy .\data\data\textures\cut_red_earth_side.png .\runtime\data\textures\cut_red_earth_side.png
if exist .\data\data\textures\earth_and_grass.png copy .\data\data\textures\earth_and_grass.png .\runtime\data\textures\earth_and_grass.png
if exist .\data\data\textures\env.png copy .\data\data\textures\env.png .\runtime\data\textures\env.png
if exist .\data\data\textures\envshadow.png copy .\data\data\textures\envshadow.png .\runtime\data\textures\envshadow.png
if exist .\data\data\textures\fields_small.png copy .\data\data\textures\fields_small.png .\runtime\data\textures\fields_small.png
if exist .\data\data\textures\forest_far_above.png copy .\data\data\textures\forest_far_above.png .\runtime\data\textures\forest_far_above.png
if exist .\data\data\textures\grey_rock_side.png copy .\data\data\textures\grey_rock_side.png .\runtime\data\textures\grey_rock_side.png
if exist .\data\data\textures\red_dirt.png copy .\data\data\textures\red_dirt.png .\runtime\data\textures\red_dirt.png
if exist .\data\data\textures\red_earth.png copy .\data\data\textures\red_earth.png .\runtime\data\textures\red_earth.png
if exist .\data\data\textures\red_rock_side.png copy .\data\data\textures\red_rock_side.png .\runtime\data\textures\red_rock_side.png
if exist .\data\data\textures\road_concrete_boundary.png copy .\data\data\textures\road_concrete_boundary.png .\runtime\data\textures\road_concrete_boundary.png
if exist .\data\data\textures\road_earth_boundary.png copy .\data\data\textures\road_earth_boundary.png .\runtime\data\textures\road_earth_boundary.png
if exist .\data\data\textures\road_gravel_boundary.png copy .\data\data\textures\road_gravel_boundary.png .\runtime\data\textures\road_gravel_boundary.png
if exist .\data\data\textures\rusted_barrier.png copy .\data\data\textures\rusted_barrier.png .\runtime\data\textures\rusted_barrier.png
if exist .\data\data\textures\yellow_rock_side.png copy .\data\data\textures\yellow_rock_side.png .\runtime\data\textures\yellow_rock_side.png
if exist .\data\data\textures\ancient-concrete1.rgb copy .\data\data\textures\ancient-concrete1.rgb .\runtime\data\textures\ancient-concrete1.rgb
if exist .\data\data\textures\ancient-concrete-bump.rgb copy .\data\data\textures\ancient-concrete-bump.rgb .\runtime\data\textures\ancient-concrete-bump.rgb
if exist .\data\data\textures\back-sign.rgb copy .\data\data\textures\back-sign.rgb .\runtime\data\textures\back-sign.rgb
if exist .\data\data\textures\basalt1_2.rgb copy .\data\data\textures\basalt1_2.rgb .\runtime\data\textures\basalt1_2.rgb
if exist .\data\data\textures\basalt1.rgb copy .\data\data\textures\basalt1.rgb .\runtime\data\textures\basalt1.rgb
if exist .\data\data\textures\basalt2_2b.rgb copy .\data\data\textures\basalt2_2b.rgb .\runtime\data\textures\basalt2_2b.rgb
if exist .\data\data\textures\basalt2_2.rgb copy .\data\data\textures\basalt2_2.rgb .\runtime\data\textures\basalt2_2.rgb
if exist .\data\data\textures\basalt2.rgb copy .\data\data\textures\basalt2.rgb .\runtime\data\textures\basalt2.rgb
if exist .\data\data\textures\breaklight1.rgb copy .\data\data\textures\breaklight1.rgb .\runtime\data\textures\breaklight1.rgb
if exist .\data\data\textures\breaklight2.rgb copy .\data\data\textures\breaklight2.rgb .\runtime\data\textures\breaklight2.rgb
if exist .\data\data\textures\building1.rgb copy .\data\data\textures\building1.rgb .\runtime\data\textures\building1.rgb
if exist .\data\data\textures\building2.rgb copy .\data\data\textures\building2.rgb .\runtime\data\textures\building2.rgb
if exist .\data\data\textures\bump-2.rgb copy .\data\data\textures\bump-2.rgb .\runtime\data\textures\bump-2.rgb
if exist .\data\data\textures\bump-3.rgb copy .\data\data\textures\bump-3.rgb .\runtime\data\textures\bump-3.rgb
if exist .\data\data\textures\bump-4.rgb copy .\data\data\textures\bump-4.rgb .\runtime\data\textures\bump-4.rgb
if exist .\data\data\textures\bump-5.rgb copy .\data\data\textures\bump-5.rgb .\runtime\data\textures\bump-5.rgb
if exist .\data\data\textures\bump-6.rgb copy .\data\data\textures\bump-6.rgb .\runtime\data\textures\bump-6.rgb
if exist .\data\data\textures\bump-7.rgb copy .\data\data\textures\bump-7.rgb .\runtime\data\textures\bump-7.rgb
if exist .\data\data\textures\bump-8.rgb copy .\data\data\textures\bump-8.rgb .\runtime\data\textures\bump-8.rgb
if exist .\data\data\textures\bump-9.rgb copy .\data\data\textures\bump-9.rgb .\runtime\data\textures\bump-9.rgb
if exist .\data\data\textures\bump-as.rgb copy .\data\data\textures\bump-as.rgb .\runtime\data\textures\bump-as.rgb
if exist .\data\data\textures\bump-finegrain.rgb copy .\data\data\textures\bump-finegrain.rgb .\runtime\data\textures\bump-finegrain.rgb
if exist .\data\data\textures\bump-sand.rgb copy .\data\data\textures\bump-sand.rgb .\runtime\data\textures\bump-sand.rgb
if exist .\data\data\textures\concrete2.rgb copy .\data\data\textures\concrete2.rgb .\runtime\data\textures\concrete2.rgb
if exist .\data\data\textures\concrete.rgb copy .\data\data\textures\concrete.rgb .\runtime\data\textures\concrete.rgb
if exist .\data\data\textures\counter-bg-10.rgb copy .\data\data\textures\counter-bg-10.rgb .\runtime\data\textures\counter-bg-10.rgb
if exist .\data\data\textures\counter-bg2.rgb copy .\data\data\textures\counter-bg2.rgb .\runtime\data\textures\counter-bg2.rgb
if exist .\data\data\textures\counter-bg.rgb copy .\data\data\textures\counter-bg.rgb .\runtime\data\textures\counter-bg.rgb
if exist .\data\data\textures\counter-bg-rpm.rgb copy .\data\data\textures\counter-bg-rpm.rgb .\runtime\data\textures\counter-bg-rpm.rgb
if exist .\data\data\textures\counter.rgb copy .\data\data\textures\counter.rgb .\runtime\data\textures\counter.rgb
if exist .\data\data\textures\fire0.rgb copy .\data\data\textures\fire0.rgb .\runtime\data\textures\fire0.rgb
if exist .\data\data\textures\fire1.rgb copy .\data\data\textures\fire1.rgb .\runtime\data\textures\fire1.rgb
if exist .\data\data\textures\forest1.rgb copy .\data\data\textures\forest1.rgb .\runtime\data\textures\forest1.rgb
if exist .\data\data\textures\forest1-r.rgb copy .\data\data\textures\forest1-r.rgb .\runtime\data\textures\forest1-r.rgb
if exist .\data\data\textures\forest2.rgb copy .\data\data\textures\forest2.rgb .\runtime\data\textures\forest2.rgb
if exist .\data\data\textures\forest3.rgb copy .\data\data\textures\forest3.rgb .\runtime\data\textures\forest3.rgb
if exist .\data\data\textures\frontlight1.rgb copy .\data\data\textures\frontlight1.rgb .\runtime\data\textures\frontlight1.rgb
if exist .\data\data\textures\frontlight2.rgb copy .\data\data\textures\frontlight2.rgb .\runtime\data\textures\frontlight2.rgb
if exist .\data\data\textures\grassg1.rgb copy .\data\data\textures\grassg1.rgb .\runtime\data\textures\grassg1.rgb
if exist .\data\data\textures\grassg2.rgb copy .\data\data\textures\grassg2.rgb .\runtime\data\textures\grassg2.rgb
if exist .\data\data\textures\grassg3.rgb copy .\data\data\textures\grassg3.rgb .\runtime\data\textures\grassg3.rgb
if exist .\data\data\textures\grey-tracks.rgb copy .\data\data\textures\grey-tracks.rgb .\runtime\data\textures\grey-tracks.rgb
if exist .\data\data\textures\hard-dirt1.rgb copy .\data\data\textures\hard-dirt1.rgb .\runtime\data\textures\hard-dirt1.rgb
if exist .\data\data\textures\hard-dirt1-side.rgb copy .\data\data\textures\hard-dirt1-side.rgb .\runtime\data\textures\hard-dirt1-side.rgb
if exist .\data\data\textures\hard-dirt.rgb copy .\data\data\textures\hard-dirt.rgb .\runtime\data\textures\hard-dirt.rgb
if exist .\data\data\textures\logo.rgb copy .\data\data\textures\logo.rgb .\runtime\data\textures\logo.rgb
if exist .\data\data\textures\mud-gravel1.rgb copy .\data\data\textures\mud-gravel1.rgb .\runtime\data\textures\mud-gravel1.rgb
if exist .\data\data\textures\mud-gravel-side.rgb copy .\data\data\textures\mud-gravel-side.rgb .\runtime\data\textures\mud-gravel-side.rgb
if exist .\data\data\textures\mud-hard-dirt.rgb copy .\data\data\textures\mud-hard-dirt.rgb .\runtime\data\textures\mud-hard-dirt.rgb
if exist .\data\data\textures\mud-river.rgb copy .\data\data\textures\mud-river.rgb .\runtime\data\textures\mud-river.rgb
if exist .\data\data\textures\panel-empty.rgb copy .\data\data\textures\panel-empty.rgb .\runtime\data\textures\panel-empty.rgb
if exist .\data\data\textures\people1.rgb copy .\data\data\textures\people1.rgb .\runtime\data\textures\people1.rgb
if exist .\data\data\textures\pit-left.rgb copy .\data\data\textures\pit-left.rgb .\runtime\data\textures\pit-left.rgb
if exist .\data\data\textures\pit-right.rgb copy .\data\data\textures\pit-right.rgb .\runtime\data\textures\pit-right.rgb
if exist .\data\data\textures\poutre3.rgb copy .\data\data\textures\poutre3.rgb .\runtime\data\textures\poutre3.rgb
if exist .\data\data\textures\pylon1.rgb copy .\data\data\textures\pylon1.rgb .\runtime\data\textures\pylon1.rgb
if exist .\data\data\textures\pylon2.rgb copy .\data\data\textures\pylon2.rgb .\runtime\data\textures\pylon2.rgb
if exist .\data\data\textures\pylon3.rgb copy .\data\data\textures\pylon3.rgb .\runtime\data\textures\pylon3.rgb
if exist .\data\data\textures\rearlight1.rgb copy .\data\data\textures\rearlight1.rgb .\runtime\data\textures\rearlight1.rgb
if exist .\data\data\textures\rearlight2.rgb copy .\data\data\textures\rearlight2.rgb .\runtime\data\textures\rearlight2.rgb
if exist .\data\data\textures\red-light-off.rgb copy .\data\data\textures\red-light-off.rgb .\runtime\data\textures\red-light-off.rgb
if exist .\data\data\textures\red-light-on.rgb copy .\data\data\textures\red-light-on.rgb .\runtime\data\textures\red-light-on.rgb
if exist .\data\data\textures\rock2.rgb copy .\data\data\textures\rock2.rgb .\runtime\data\textures\rock2.rgb
if exist .\data\data\textures\rock3.rgb copy .\data\data\textures\rock3.rgb .\runtime\data\textures\rock3.rgb
if exist .\data\data\textures\rpm5500.rgb copy .\data\data\textures\rpm5500.rgb .\runtime\data\textures\rpm5500.rgb
if exist .\data\data\textures\rpm7000.rgb copy .\data\data\textures\rpm7000.rgb .\runtime\data\textures\rpm7000.rgb
if exist .\data\data\textures\rpm8000.rgb copy .\data\data\textures\rpm8000.rgb .\runtime\data\textures\rpm8000.rgb
if exist .\data\data\textures\rpm8500.rgb copy .\data\data\textures\rpm8500.rgb .\runtime\data\textures\rpm8500.rgb
if exist .\data\data\textures\rpm20000.rgb copy .\data\data\textures\rpm20000.rgb .\runtime\data\textures\rpm20000.rgb
if exist .\data\data\textures\smoke.rgb copy .\data\data\textures\smoke.rgb .\runtime\data\textures\smoke.rgb
if exist .\data\data\textures\speed240.rgb copy .\data\data\textures\speed240.rgb .\runtime\data\textures\speed240.rgb
if exist .\data\data\textures\speed300.rgb copy .\data\data\textures\speed300.rgb .\runtime\data\textures\speed300.rgb
if exist .\data\data\textures\speed360.rgb copy .\data\data\textures\speed360.rgb .\runtime\data\textures\speed360.rgb
if exist .\data\data\textures\torcs-ad1.rgb copy .\data\data\textures\torcs-ad1.rgb .\runtime\data\textures\torcs-ad1.rgb
if exist .\data\data\textures\torcsad1.rgb copy .\data\data\textures\torcsad1.rgb .\runtime\data\textures\torcsad1.rgb
if exist .\data\data\textures\torcsad2.rgb copy .\data\data\textures\torcsad2.rgb .\runtime\data\textures\torcsad2.rgb
if exist .\data\data\textures\trans-mud-hard-dirt.rgb copy .\data\data\textures\trans-mud-hard-dirt.rgb .\runtime\data\textures\trans-mud-hard-dirt.rgb
if exist .\data\data\textures\tr-asphalt-both_nmm.rgb copy .\data\data\textures\tr-asphalt-both_nmm.rgb .\runtime\data\textures\tr-asphalt-both_nmm.rgb
if exist .\data\data\textures\tr-asphalt-both.rgb copy .\data\data\textures\tr-asphalt-both.rgb .\runtime\data\textures\tr-asphalt-both.rgb
if exist .\data\data\textures\tr-asphalt-grass-l.rgb copy .\data\data\textures\tr-asphalt-grass-l.rgb .\runtime\data\textures\tr-asphalt-grass-l.rgb
if exist .\data\data\textures\tr-asphalt-grass-r.rgb copy .\data\data\textures\tr-asphalt-grass-r.rgb .\runtime\data\textures\tr-asphalt-grass-r.rgb
if exist .\data\data\textures\tr-asphalt-left_nmm.rgb copy .\data\data\textures\tr-asphalt-left_nmm.rgb .\runtime\data\textures\tr-asphalt-left_nmm.rgb
if exist .\data\data\textures\tr-asphalt-left.rgb copy .\data\data\textures\tr-asphalt-left.rgb .\runtime\data\textures\tr-asphalt-left.rgb
if exist .\data\data\textures\tr-asphalt-l_nmm.rgb copy .\data\data\textures\tr-asphalt-l_nmm.rgb .\runtime\data\textures\tr-asphalt-l_nmm.rgb
if exist .\data\data\textures\tr-asphalt-l.rgb copy .\data\data\textures\tr-asphalt-l.rgb .\runtime\data\textures\tr-asphalt-l.rgb
if exist .\data\data\textures\tr-asphalt_nmm.rgb copy .\data\data\textures\tr-asphalt_nmm.rgb .\runtime\data\textures\tr-asphalt_nmm.rgb
if exist .\data\data\textures\tr-asphalt-p_nmm.rgb copy .\data\data\textures\tr-asphalt-p_nmm.rgb .\runtime\data\textures\tr-asphalt-p_nmm.rgb
if exist .\data\data\textures\tr-asphalt-p.rgb copy .\data\data\textures\tr-asphalt-p.rgb .\runtime\data\textures\tr-asphalt-p.rgb
if exist .\data\data\textures\tr-asphalt.rgb copy .\data\data\textures\tr-asphalt.rgb .\runtime\data\textures\tr-asphalt.rgb
if exist .\data\data\textures\tr-asphalt-right_nmm.rgb copy .\data\data\textures\tr-asphalt-right_nmm.rgb .\runtime\data\textures\tr-asphalt-right_nmm.rgb
if exist .\data\data\textures\tr-asphalt-right.rgb copy .\data\data\textures\tr-asphalt-right.rgb .\runtime\data\textures\tr-asphalt-right.rgb
if exist .\data\data\textures\tr-asphalt-road1.rgb copy .\data\data\textures\tr-asphalt-road1.rgb .\runtime\data\textures\tr-asphalt-road1.rgb
if exist .\data\data\textures\tr-asphalt-sand.rgb copy .\data\data\textures\tr-asphalt-sand.rgb .\runtime\data\textures\tr-asphalt-sand.rgb
if exist .\data\data\textures\tr-bar-gr.rgb copy .\data\data\textures\tr-bar-gr.rgb .\runtime\data\textures\tr-bar-gr.rgb
if exist .\data\data\textures\tr-bar-gr_n.rgb copy .\data\data\textures\tr-bar-gr_n.rgb .\runtime\data\textures\tr-bar-gr_n.rgb
if exist .\data\data\textures\tr-bar.rgb copy .\data\data\textures\tr-bar.rgb .\runtime\data\textures\tr-bar.rgb
if exist .\data\data\textures\tr-barrier.rgb copy .\data\data\textures\tr-barrier.rgb .\runtime\data\textures\tr-barrier.rgb
if exist .\data\data\textures\tr-bar-turn1.rgb copy .\data\data\textures\tr-bar-turn1.rgb .\runtime\data\textures\tr-bar-turn1.rgb
if exist .\data\data\textures\tr-b-asphalt-grass6-l1.rgb copy .\data\data\textures\tr-b-asphalt-grass6-l1.rgb .\runtime\data\textures\tr-b-asphalt-grass6-l1.rgb
if exist .\data\data\textures\tr-b-asphalt-grass6.rgb copy .\data\data\textures\tr-b-asphalt-grass6.rgb .\runtime\data\textures\tr-b-asphalt-grass6.rgb
if exist .\data\data\textures\tr-b-asphalt-grass7-l1.rgb copy .\data\data\textures\tr-b-asphalt-grass7-l1.rgb .\runtime\data\textures\tr-b-asphalt-grass7-l1.rgb
if exist .\data\data\textures\tr-b-asphalt-grass7.rgb copy .\data\data\textures\tr-b-asphalt-grass7.rgb .\runtime\data\textures\tr-b-asphalt-grass7.rgb
if exist .\data\data\textures\tr-b-asphalt-gravel-l1.rgb copy .\data\data\textures\tr-b-asphalt-gravel-l1.rgb .\runtime\data\textures\tr-b-asphalt-gravel-l1.rgb
if exist .\data\data\textures\tr-b-asphalt-gravel.rgb copy .\data\data\textures\tr-b-asphalt-gravel.rgb .\runtime\data\textures\tr-b-asphalt-gravel.rgb
if exist .\data\data\textures\tr-b-asphalt-l1p.rgb copy .\data\data\textures\tr-b-asphalt-l1p.rgb .\runtime\data\textures\tr-b-asphalt-l1p.rgb
if exist .\data\data\textures\tr-b-asphalt-l1.rgb copy .\data\data\textures\tr-b-asphalt-l1.rgb .\runtime\data\textures\tr-b-asphalt-l1.rgb
if exist .\data\data\textures\tr-b-asphalt.rgb copy .\data\data\textures\tr-b-asphalt.rgb .\runtime\data\textures\tr-b-asphalt.rgb
if exist .\data\data\textures\tr-b-asphalt-sand3-l1.rgb copy .\data\data\textures\tr-b-asphalt-sand3-l1.rgb .\runtime\data\textures\tr-b-asphalt-sand3-l1.rgb
if exist .\data\data\textures\tr-b-asphalt-sand3.rgb copy .\data\data\textures\tr-b-asphalt-sand3.rgb .\runtime\data\textures\tr-b-asphalt-sand3.rgb
if exist .\data\data\textures\tr-b-concrete4-concrete-l1p.rgb copy .\data\data\textures\tr-b-concrete4-concrete-l1p.rgb .\runtime\data\textures\tr-b-concrete4-concrete-l1p.rgb
if exist .\data\data\textures\tr-b-concrete4-concrete-l1.rgb copy .\data\data\textures\tr-b-concrete4-concrete-l1.rgb .\runtime\data\textures\tr-b-concrete4-concrete-l1.rgb
if exist .\data\data\textures\tr-b-road1-grass6-l2.rgb copy .\data\data\textures\tr-b-road1-grass6-l2.rgb .\runtime\data\textures\tr-b-road1-grass6-l2.rgb
if exist .\data\data\textures\tr-b-road1-grass6.rgb copy .\data\data\textures\tr-b-road1-grass6.rgb .\runtime\data\textures\tr-b-road1-grass6.rgb
if exist .\data\data\textures\tr-b-road1-gravel-l2.rgb copy .\data\data\textures\tr-b-road1-gravel-l2.rgb .\runtime\data\textures\tr-b-road1-gravel-l2.rgb
if exist .\data\data\textures\tr-b-road1-l2p.rgb copy .\data\data\textures\tr-b-road1-l2p.rgb .\runtime\data\textures\tr-b-road1-l2p.rgb
if exist .\data\data\textures\tr-b-road1-l2.rgb copy .\data\data\textures\tr-b-road1-l2.rgb .\runtime\data\textures\tr-b-road1-l2.rgb
if exist .\data\data\textures\tr-b-road1-sand3-l2.rgb copy .\data\data\textures\tr-b-road1-sand3-l2.rgb .\runtime\data\textures\tr-b-road1-sand3-l2.rgb
if exist .\data\data\textures\tr-b-road1-sand3.rgb copy .\data\data\textures\tr-b-road1-sand3.rgb .\runtime\data\textures\tr-b-road1-sand3.rgb
if exist .\data\data\textures\tr-concrete4.rgb copy .\data\data\textures\tr-concrete4.rgb .\runtime\data\textures\tr-concrete4.rgb
if exist .\data\data\textures\tr-concrete_nmm.rgb copy .\data\data\textures\tr-concrete_nmm.rgb .\runtime\data\textures\tr-concrete_nmm.rgb
if exist .\data\data\textures\tr-concrete-pit.rgb copy .\data\data\textures\tr-concrete-pit.rgb .\runtime\data\textures\tr-concrete-pit.rgb
if exist .\data\data\textures\tr-concrete.rgb copy .\data\data\textures\tr-concrete.rgb .\runtime\data\textures\tr-concrete.rgb
if exist .\data\data\textures\tr-curb-l.rgb copy .\data\data\textures\tr-curb-l.rgb .\runtime\data\textures\tr-curb-l.rgb
if exist .\data\data\textures\tr-curb-r.rgb copy .\data\data\textures\tr-curb-r.rgb .\runtime\data\textures\tr-curb-r.rgb
if exist .\data\data\textures\tr-dirtb.rgb copy .\data\data\textures\tr-dirtb.rgb .\runtime\data\textures\tr-dirtb.rgb
if exist .\data\data\textures\tr-dirt.rgb copy .\data\data\textures\tr-dirt.rgb .\runtime\data\textures\tr-dirt.rgb
if exist .\data\data\textures\tree10.rgb copy .\data\data\textures\tree10.rgb .\runtime\data\textures\tree10.rgb
if exist .\data\data\textures\tree11.rgb copy .\data\data\textures\tree11.rgb .\runtime\data\textures\tree11.rgb
if exist .\data\data\textures\tree12.rgb copy .\data\data\textures\tree12.rgb .\runtime\data\textures\tree12.rgb
if exist .\data\data\textures\tree13.rgb copy .\data\data\textures\tree13.rgb .\runtime\data\textures\tree13.rgb
if exist .\data\data\textures\tree14.rgb copy .\data\data\textures\tree14.rgb .\runtime\data\textures\tree14.rgb
if exist .\data\data\textures\tree15.rgb copy .\data\data\textures\tree15.rgb .\runtime\data\textures\tree15.rgb
if exist .\data\data\textures\tree16.rgb copy .\data\data\textures\tree16.rgb .\runtime\data\textures\tree16.rgb
if exist .\data\data\textures\tree17.rgb copy .\data\data\textures\tree17.rgb .\runtime\data\textures\tree17.rgb
if exist .\data\data\textures\tree18.rgb copy .\data\data\textures\tree18.rgb .\runtime\data\textures\tree18.rgb
if exist .\data\data\textures\tree19.rgb copy .\data\data\textures\tree19.rgb .\runtime\data\textures\tree19.rgb
if exist .\data\data\textures\tree1.rgb copy .\data\data\textures\tree1.rgb .\runtime\data\textures\tree1.rgb
if exist .\data\data\textures\tree20.rgb copy .\data\data\textures\tree20.rgb .\runtime\data\textures\tree20.rgb
if exist .\data\data\textures\tree2.rgb copy .\data\data\textures\tree2.rgb .\runtime\data\textures\tree2.rgb
if exist .\data\data\textures\tree3.rgb copy .\data\data\textures\tree3.rgb .\runtime\data\textures\tree3.rgb
if exist .\data\data\textures\tree4.rgb copy .\data\data\textures\tree4.rgb .\runtime\data\textures\tree4.rgb
if exist .\data\data\textures\tree5.rgb copy .\data\data\textures\tree5.rgb .\runtime\data\textures\tree5.rgb
if exist .\data\data\textures\tree7.rgb copy .\data\data\textures\tree7.rgb .\runtime\data\textures\tree7.rgb
if exist .\data\data\textures\tree8.rgb copy .\data\data\textures\tree8.rgb .\runtime\data\textures\tree8.rgb
if exist .\data\data\textures\tree9.rgb copy .\data\data\textures\tree9.rgb .\runtime\data\textures\tree9.rgb
if exist .\data\data\textures\treebui1.rgb copy .\data\data\textures\treebui1.rgb .\runtime\data\textures\treebui1.rgb
if exist .\data\data\textures\treebui2.rgb copy .\data\data\textures\treebui2.rgb .\runtime\data\textures\treebui2.rgb
if exist .\data\data\textures\treeg1.rgb copy .\data\data\textures\treeg1.rgb .\runtime\data\textures\treeg1.rgb
if exist .\data\data\textures\tr-fake-road-2.rgb copy .\data\data\textures\tr-fake-road-2.rgb .\runtime\data\textures\tr-fake-road-2.rgb
if exist .\data\data\textures\tr-fake-road-borders.rgb copy .\data\data\textures\tr-fake-road-borders.rgb .\runtime\data\textures\tr-fake-road-borders.rgb
if exist .\data\data\textures\tr-fake-road-lines.rgb copy .\data\data\textures\tr-fake-road-lines.rgb .\runtime\data\textures\tr-fake-road-lines.rgb
if exist .\data\data\textures\tr-fake-road.rgb copy .\data\data\textures\tr-fake-road.rgb .\runtime\data\textures\tr-fake-road.rgb
if exist .\data\data\textures\tr-grass2.rgb copy .\data\data\textures\tr-grass2.rgb .\runtime\data\textures\tr-grass2.rgb
if exist .\data\data\textures\tr-grass3.rgb copy .\data\data\textures\tr-grass3.rgb .\runtime\data\textures\tr-grass3.rgb
if exist .\data\data\textures\tr-grass4.rgb copy .\data\data\textures\tr-grass4.rgb .\runtime\data\textures\tr-grass4.rgb
if exist .\data\data\textures\tr-grass5.rgb copy .\data\data\textures\tr-grass5.rgb .\runtime\data\textures\tr-grass5.rgb
if exist .\data\data\textures\tr-grass6.rgb copy .\data\data\textures\tr-grass6.rgb .\runtime\data\textures\tr-grass6.rgb
if exist .\data\data\textures\tr-grass7.rgb copy .\data\data\textures\tr-grass7.rgb .\runtime\data\textures\tr-grass7.rgb
if exist .\data\data\textures\tr-grass.rgb copy .\data\data\textures\tr-grass.rgb .\runtime\data\textures\tr-grass.rgb
if exist .\data\data\textures\tr-gravel.rgb copy .\data\data\textures\tr-gravel.rgb .\runtime\data\textures\tr-gravel.rgb
if exist .\data\data\textures\tr-road1-asphalt.rgb copy .\data\data\textures\tr-road1-asphalt.rgb .\runtime\data\textures\tr-road1-asphalt.rgb
if exist .\data\data\textures\tr-road1-pit.rgb copy .\data\data\textures\tr-road1-pit.rgb .\runtime\data\textures\tr-road1-pit.rgb
if exist .\data\data\textures\tr-road1.rgb copy .\data\data\textures\tr-road1.rgb .\runtime\data\textures\tr-road1.rgb
if exist .\data\data\textures\tr-sand2.rgb copy .\data\data\textures\tr-sand2.rgb .\runtime\data\textures\tr-sand2.rgb
if exist .\data\data\textures\tr-sand3.rgb copy .\data\data\textures\tr-sand3.rgb .\runtime\data\textures\tr-sand3.rgb
if exist .\data\data\textures\tr-sand.rgb copy .\data\data\textures\tr-sand.rgb .\runtime\data\textures\tr-sand.rgb
if exist .\data\data\textures\tr-snow.rgb copy .\data\data\textures\tr-snow.rgb .\runtime\data\textures\tr-snow.rgb
if exist .\data\data\textures\tr-stone-wall2.rgb copy .\data\data\textures\tr-stone-wall2.rgb .\runtime\data\textures\tr-stone-wall2.rgb
if exist .\data\data\textures\tr-stone-wall.rgb copy .\data\data\textures\tr-stone-wall.rgb .\runtime\data\textures\tr-stone-wall.rgb
if exist .\data\data\textures\tr-tirewall.rgb copy .\data\data\textures\tr-tirewall.rgb .\runtime\data\textures\tr-tirewall.rgb
if exist .\data\data\textures\tr-wall_nmm.rgb copy .\data\data\textures\tr-wall_nmm.rgb .\runtime\data\textures\tr-wall_nmm.rgb
if exist .\data\data\textures\tr-wall.rgb copy .\data\data\textures\tr-wall.rgb .\runtime\data\textures\tr-wall.rgb
if exist .\data\data\textures\tr-water.rgb copy .\data\data\textures\tr-water.rgb .\runtime\data\textures\tr-water.rgb
if exist .\data\data\textures\turn100L.rgb copy .\data\data\textures\turn100L.rgb .\runtime\data\textures\turn100L.rgb
if exist .\data\data\textures\turn100R.rgb copy .\data\data\textures\turn100R.rgb .\runtime\data\textures\turn100R.rgb
if exist .\data\data\textures\turn150L.rgb copy .\data\data\textures\turn150L.rgb .\runtime\data\textures\turn150L.rgb
if exist .\data\data\textures\turn150R.rgb copy .\data\data\textures\turn150R.rgb .\runtime\data\textures\turn150R.rgb
if exist .\data\data\textures\turn200L.rgb copy .\data\data\textures\turn200L.rgb .\runtime\data\textures\turn200L.rgb
if exist .\data\data\textures\turn200R.rgb copy .\data\data\textures\turn200R.rgb .\runtime\data\textures\turn200R.rgb
if exist .\data\data\textures\turn300L.rgb copy .\data\data\textures\turn300L.rgb .\runtime\data\textures\turn300L.rgb
if exist .\data\data\textures\turn300R.rgb copy .\data\data\textures\turn300R.rgb .\runtime\data\textures\turn300R.rgb
if exist .\data\data\textures\turn50L.rgb copy .\data\data\textures\turn50L.rgb .\runtime\data\textures\turn50L.rgb
if exist .\data\data\textures\turn50R.rgb copy .\data\data\textures\turn50R.rgb .\runtime\data\textures\turn50R.rgb

if exist .\data\data\tracks\*.* call .\create_dir .\runtime
if exist .\data\data\tracks\*.* call .\create_dir .\runtime\data
if exist .\data\data\tracks\*.* call .\create_dir .\runtime\data\tracks
if exist .\data\data\tracks\dirt.xml copy .\data\data\tracks\dirt.xml .\runtime\data\tracks\dirt.xml
if exist .\data\data\tracks\objects.xml copy .\data\data\tracks\objects.xml .\runtime\data\tracks\objects.xml
if exist .\data\data\tracks\oval.xml copy .\data\data\tracks\oval.xml .\runtime\data\tracks\oval.xml
if exist .\data\data\tracks\road.xml copy .\data\data\tracks\road.xml .\runtime\data\tracks\road.xml
if exist .\data\data\tracks\surfaces.xml copy .\data\data\tracks\surfaces.xml .\runtime\data\tracks\surfaces.xml

if exist .\data\tracks\aalborg\*.* call .\create_dir .\runtime
if exist .\data\tracks\aalborg\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\aalborg\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\aalborg\*.* call .\create_dir .\runtime\tracks\road\aalborg
if exist .\data\tracks\aalborg\aalborg.xml copy .\data\tracks\aalborg\aalborg.xml .\runtime\tracks\road\aalborg\aalborg.xml
if exist .\data\tracks\aalborg\aalborg.ac copy .\data\tracks\aalborg\aalborg.ac .\runtime\tracks\road\aalborg\aalborg.ac
if exist .\data\tracks\aalborg\aalborg.png copy .\data\tracks\aalborg\aalborg.png .\runtime\tracks\road\aalborg\aalborg.png

if exist .\data\tracks\a-speedway\*.* call .\create_dir .\runtime
if exist .\data\tracks\a-speedway\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\a-speedway\*.* call .\create_dir .\runtime\tracks\oval
if exist .\data\tracks\a-speedway\*.* call .\create_dir .\runtime\tracks\oval\a-speedway
if exist .\data\tracks\a-speedway\a-speedway.xml copy .\data\tracks\a-speedway\a-speedway.xml .\runtime\tracks\oval\a-speedway\a-speedway.xml
if exist .\data\tracks\a-speedway\background.png copy .\data\tracks\a-speedway\background.png .\runtime\tracks\oval\a-speedway\background.png
if exist .\data\tracks\a-speedway\a-speedway.ac copy .\data\tracks\a-speedway\a-speedway.ac .\runtime\tracks\oval\a-speedway\a-speedway.ac
if exist .\data\tracks\a-speedway\a-speedway.png copy .\data\tracks\a-speedway\a-speedway.png .\runtime\tracks\oval\a-speedway\a-speedway.png

if exist .\data\tracks\dirt-1\*.* call .\create_dir .\runtime
if exist .\data\tracks\dirt-1\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\dirt-1\*.* call .\create_dir .\runtime\tracks\dirt
if exist .\data\tracks\dirt-1\*.* call .\create_dir .\runtime\tracks\dirt\dirt-1
if exist .\data\tracks\dirt-1\dirt-1.xml copy .\data\tracks\dirt-1\dirt-1.xml .\runtime\tracks\dirt\dirt-1\dirt-1.xml
if exist .\data\tracks\dirt-1\background.png copy .\data\tracks\dirt-1\background.png .\runtime\tracks\dirt\dirt-1\background.png
if exist .\data\tracks\dirt-1\dirt-1.ac copy .\data\tracks\dirt-1\dirt-1.ac .\runtime\tracks\dirt\dirt-1\dirt-1.ac
if exist .\data\tracks\dirt-1\dirt-1.png copy .\data\tracks\dirt-1\dirt-1.png .\runtime\tracks\dirt\dirt-1\dirt-1.png

if exist .\data\tracks\dirt-2\*.* call .\create_dir .\runtime
if exist .\data\tracks\dirt-2\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\dirt-2\*.* call .\create_dir .\runtime\tracks\dirt
if exist .\data\tracks\dirt-2\*.* call .\create_dir .\runtime\tracks\dirt\dirt-2
if exist .\data\tracks\dirt-2\dirt-2.xml copy .\data\tracks\dirt-2\dirt-2.xml .\runtime\tracks\dirt\dirt-2\dirt-2.xml
if exist .\data\tracks\dirt-2\background.png copy .\data\tracks\dirt-2\background.png .\runtime\tracks\dirt\dirt-2\background.png
if exist .\data\tracks\dirt-2\dirt-2.ac copy .\data\tracks\dirt-2\dirt-2.ac .\runtime\tracks\dirt\dirt-2\dirt-2.ac
if exist .\data\tracks\dirt-2\dirt-2.png copy .\data\tracks\dirt-2\dirt-2.png .\runtime\tracks\dirt\dirt-2\dirt-2.png

if exist .\data\tracks\dirt-3\*.* call .\create_dir .\runtime
if exist .\data\tracks\dirt-3\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\dirt-3\*.* call .\create_dir .\runtime\tracks\dirt
if exist .\data\tracks\dirt-3\*.* call .\create_dir .\runtime\tracks\dirt\dirt-3
if exist .\data\tracks\dirt-3\dirt-3.xml copy .\data\tracks\dirt-3\dirt-3.xml .\runtime\tracks\dirt\dirt-3\dirt-3.xml
if exist .\data\tracks\dirt-3\background.png copy .\data\tracks\dirt-3\background.png .\runtime\tracks\dirt\dirt-3\background.png
if exist .\data\tracks\dirt-3\background2.png copy .\data\tracks\dirt-3\background2.png .\runtime\tracks\dirt\dirt-3\background2.png
if exist .\data\tracks\dirt-3\dirt-3.ac copy .\data\tracks\dirt-3\dirt-3.ac .\runtime\tracks\dirt\dirt-3\dirt-3.ac
if exist .\data\tracks\dirt-3\dirt-3.png copy .\data\tracks\dirt-3\dirt-3.png .\runtime\tracks\dirt\dirt-3\dirt-3.png

if exist .\data\tracks\dirt-4\*.* call .\create_dir .\runtime
if exist .\data\tracks\dirt-4\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\dirt-4\*.* call .\create_dir .\runtime\tracks\dirt
if exist .\data\tracks\dirt-4\*.* call .\create_dir .\runtime\tracks\dirt\dirt-4
if exist .\data\tracks\dirt-4\dirt-4.xml copy .\data\tracks\dirt-4\dirt-4.xml .\runtime\tracks\dirt\dirt-4\dirt-4.xml
if exist .\data\tracks\dirt-4\background.png copy .\data\tracks\dirt-4\background.png .\runtime\tracks\dirt\dirt-4\background.png
if exist .\data\tracks\dirt-4\dirt-4.ac copy .\data\tracks\dirt-4\dirt-4.ac .\runtime\tracks\dirt\dirt-4\dirt-4.ac
if exist .\data\tracks\dirt-4\dirt-4.png copy .\data\tracks\dirt-4\dirt-4.png .\runtime\tracks\dirt\dirt-4\dirt-4.png

if exist .\data\tracks\dirt-5\*.* call .\create_dir .\runtime
if exist .\data\tracks\dirt-5\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\dirt-5\*.* call .\create_dir .\runtime\tracks\dirt
if exist .\data\tracks\dirt-5\*.* call .\create_dir .\runtime\tracks\dirt\dirt-5
if exist .\data\tracks\dirt-5\dirt-5.xml copy .\data\tracks\dirt-5\dirt-5.xml .\runtime\tracks\dirt\dirt-5\dirt-5.xml
if exist .\data\tracks\dirt-5\background.png copy .\data\tracks\dirt-5\background.png .\runtime\tracks\dirt\dirt-5\background.png
if exist .\data\tracks\dirt-5\dirt-5.ac copy .\data\tracks\dirt-5\dirt-5.ac .\runtime\tracks\dirt\dirt-5\dirt-5.ac
if exist .\data\tracks\dirt-5\dirt-5.png copy .\data\tracks\dirt-5\dirt-5.png .\runtime\tracks\dirt\dirt-5\dirt-5.png

if exist .\data\tracks\dirt-6\*.* call .\create_dir .\runtime
if exist .\data\tracks\dirt-6\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\dirt-6\*.* call .\create_dir .\runtime\tracks\dirt
if exist .\data\tracks\dirt-6\*.* call .\create_dir .\runtime\tracks\dirt\dirt-6
if exist .\data\tracks\dirt-6\dirt-6.xml copy .\data\tracks\dirt-6\dirt-6.xml .\runtime\tracks\dirt\dirt-6\dirt-6.xml
if exist .\data\tracks\dirt-6\background.png copy .\data\tracks\dirt-6\background.png .\runtime\tracks\dirt\dirt-6\background.png
if exist .\data\tracks\dirt-6\dirt-6.ac copy .\data\tracks\dirt-6\dirt-6.ac .\runtime\tracks\dirt\dirt-6\dirt-6.ac
if exist .\data\tracks\dirt-6\dirt-6.png copy .\data\tracks\dirt-6\dirt-6.png .\runtime\tracks\dirt\dirt-6\dirt-6.png

if exist .\data\tracks\eroad\*.* call .\create_dir .\runtime
if exist .\data\tracks\eroad\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\eroad\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\eroad\*.* call .\create_dir .\runtime\tracks\road\eroad
if exist .\data\tracks\eroad\eroad.xml copy .\data\tracks\eroad\eroad.xml .\runtime\tracks\road\eroad\eroad.xml
if exist .\data\tracks\eroad\background.png copy .\data\tracks\eroad\background.png .\runtime\tracks\road\eroad\background.png
if exist .\data\tracks\eroad\eroad.ac copy .\data\tracks\eroad\eroad.ac .\runtime\tracks\road\eroad\eroad.ac
if exist .\data\tracks\eroad\eroad.png copy .\data\tracks\eroad\eroad.png .\runtime\tracks\road\eroad\eroad.png

if exist .\data\tracks\e-track-1\*.* call .\create_dir .\runtime
if exist .\data\tracks\e-track-1\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\e-track-1\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\e-track-1\*.* call .\create_dir .\runtime\tracks\road\e-track-1
if exist .\data\tracks\e-track-1\e-track-1.xml copy .\data\tracks\e-track-1\e-track-1.xml .\runtime\tracks\road\e-track-1\e-track-1.xml
if exist .\data\tracks\e-track-1\background.png copy .\data\tracks\e-track-1\background.png .\runtime\tracks\road\e-track-1\background.png
if exist .\data\tracks\e-track-1\e-track-1.ac copy .\data\tracks\e-track-1\e-track-1.ac .\runtime\tracks\road\e-track-1\e-track-1.ac
if exist .\data\tracks\e-track-1\e-track-1.png copy .\data\tracks\e-track-1\e-track-1.png .\runtime\tracks\road\e-track-1\e-track-1.png

if exist .\data\tracks\e-track-2\*.* call .\create_dir .\runtime
if exist .\data\tracks\e-track-2\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\e-track-2\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\e-track-2\*.* call .\create_dir .\runtime\tracks\road\e-track-2
if exist .\data\tracks\e-track-2\e-track-2.xml copy .\data\tracks\e-track-2\e-track-2.xml .\runtime\tracks\road\e-track-2\e-track-2.xml
if exist .\data\tracks\e-track-2\e-track-2.acc copy .\data\tracks\e-track-2\e-track-2.acc .\runtime\tracks\road\e-track-2\e-track-2.acc
if exist .\data\tracks\e-track-2\background.png copy .\data\tracks\e-track-2\background.png .\runtime\tracks\road\e-track-2\background.png
if exist .\data\tracks\e-track-2\e-track-2.png copy .\data\tracks\e-track-2\e-track-2.png .\runtime\tracks\road\e-track-2\e-track-2.png
if exist .\data\tracks\e-track-2\env.png copy .\data\tracks\e-track-2\env.png .\runtime\tracks\road\e-track-2\env.png
if exist .\data\tracks\e-track-2\pylon3.rgb copy .\data\tracks\e-track-2\pylon3.rgb .\runtime\tracks\road\e-track-2\pylon3.rgb

if exist .\data\tracks\e-track-3\*.* call .\create_dir .\runtime
if exist .\data\tracks\e-track-3\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\e-track-3\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\e-track-3\*.* call .\create_dir .\runtime\tracks\road\e-track-3
if exist .\data\tracks\e-track-3\e-track-3.xml copy .\data\tracks\e-track-3\e-track-3.xml .\runtime\tracks\road\e-track-3\e-track-3.xml
if exist .\data\tracks\e-track-3\background.png copy .\data\tracks\e-track-3\background.png .\runtime\tracks\road\e-track-3\background.png
if exist .\data\tracks\e-track-3\env.rgb copy .\data\tracks\e-track-3\env.rgb .\runtime\tracks\road\e-track-3\env.rgb
if exist .\data\tracks\e-track-3\e-track-3.ac copy .\data\tracks\e-track-3\e-track-3.ac .\runtime\tracks\road\e-track-3\e-track-3.ac
if exist .\data\tracks\e-track-3\e-track-3.png copy .\data\tracks\e-track-3\e-track-3.png .\runtime\tracks\road\e-track-3\e-track-3.png

if exist .\data\tracks\e-track-4\*.* call .\create_dir .\runtime
if exist .\data\tracks\e-track-4\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\e-track-4\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\e-track-4\*.* call .\create_dir .\runtime\tracks\road\e-track-4
if exist .\data\tracks\e-track-4\e-track-4.xml copy .\data\tracks\e-track-4\e-track-4.xml .\runtime\tracks\road\e-track-4\e-track-4.xml
if exist .\data\tracks\e-track-4\background.png copy .\data\tracks\e-track-4\background.png .\runtime\tracks\road\e-track-4\background.png
if exist .\data\tracks\e-track-4\e-track-4.ac copy .\data\tracks\e-track-4\e-track-4.ac .\runtime\tracks\road\e-track-4\e-track-4.ac
if exist .\data\tracks\e-track-4\e-track-4.png copy .\data\tracks\e-track-4\e-track-4.png .\runtime\tracks\road\e-track-4\e-track-4.png

if exist .\data\tracks\e-track-5\*.* call .\create_dir .\runtime
if exist .\data\tracks\e-track-5\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\e-track-5\*.* call .\create_dir .\runtime\tracks\oval
if exist .\data\tracks\e-track-5\*.* call .\create_dir .\runtime\tracks\oval\e-track-5
if exist .\data\tracks\e-track-5\e-track-5.xml copy .\data\tracks\e-track-5\e-track-5.xml .\runtime\tracks\oval\e-track-5\e-track-5.xml
if exist .\data\tracks\e-track-5\background.png copy .\data\tracks\e-track-5\background.png .\runtime\tracks\oval\e-track-5\background.png
if exist .\data\tracks\e-track-5\e-track-5.ac copy .\data\tracks\e-track-5\e-track-5.ac .\runtime\tracks\oval\e-track-5\e-track-5.ac
if exist .\data\tracks\e-track-5\e-track-5.png copy .\data\tracks\e-track-5\e-track-5.png .\runtime\tracks\oval\e-track-5\e-track-5.png

if exist .\data\tracks\e-track-6\*.* call .\create_dir .\runtime
if exist .\data\tracks\e-track-6\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\e-track-6\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\e-track-6\*.* call .\create_dir .\runtime\tracks\road\e-track-6
if exist .\data\tracks\e-track-6\background.png copy .\data\tracks\e-track-6\background.png .\runtime\tracks\road\e-track-6\background.png
rem if exist .\data\tracks\e-track-6\e-track-6-2.ac copy .\data\tracks\e-track-6\e-track-6-2.ac .\runtime\tracks\road\e-track-6\e-track-6-2.ac
rem if exist .\data\tracks\e-track-6\e-track-6.ac copy .\data\tracks\e-track-6\e-track-6.ac .\runtime\tracks\road\e-track-6\e-track-6.ac
if exist .\data\tracks\e-track-6\e-track-6.acc copy .\data\tracks\e-track-6\e-track-6.acc .\runtime\tracks\road\e-track-6\e-track-6.acc
if exist .\data\tracks\e-track-6\e-track-6.png copy .\data\tracks\e-track-6\e-track-6.png .\runtime\tracks\road\e-track-6\e-track-6.png
rem if exist .\data\tracks\e-track-6\e-track-6-relief1.ac copy .\data\tracks\e-track-6\e-track-6-relief1.ac .\runtime\tracks\road\e-track-6\e-track-6-relief1.ac
rem if exist .\data\tracks\e-track-6\e-track-6-relief.ac copy .\data\tracks\e-track-6\e-track-6-relief.ac .\runtime\tracks\road\e-track-6\e-track-6-relief.ac
if exist .\data\tracks\e-track-6\e-track-6.xml copy .\data\tracks\e-track-6\e-track-6.xml .\runtime\tracks\road\e-track-6\e-track-6.xml
rem if exist .\data\tracks\e-track-6\Makefile copy .\data\tracks\e-track-6\Makefile .\runtime\tracks\road\e-track-6\Makefile
if exist .\data\tracks\e-track-6\object-map1.png copy .\data\tracks\e-track-6\object-map1.png .\runtime\tracks\road\e-track-6\object-map1.png

if exist .\data\tracks\g-track-1\*.* call .\create_dir .\runtime
if exist .\data\tracks\g-track-1\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\g-track-1\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\g-track-1\*.* call .\create_dir .\runtime\tracks\road\g-track-1
if exist .\data\tracks\g-track-1\g-track-1.xml copy .\data\tracks\g-track-1\g-track-1.xml .\runtime\tracks\road\g-track-1\g-track-1.xml
if exist .\data\tracks\g-track-1\g-track-1.ac copy .\data\tracks\g-track-1\g-track-1.ac .\runtime\tracks\road\g-track-1\g-track-1.ac
if exist .\data\tracks\g-track-1\background.png copy .\data\tracks\g-track-1\background.png .\runtime\tracks\road\g-track-1\background.png
if exist .\data\tracks\g-track-1\g-track-1.png copy .\data\tracks\g-track-1\g-track-1.png .\runtime\tracks\road\g-track-1\g-track-1.png
if exist .\data\tracks\g-track-1\alltree2.rgb copy .\data\tracks\g-track-1\alltree2.rgb .\runtime\tracks\road\g-track-1\alltree2.rgb
if exist .\data\tracks\g-track-1\alltree.rgb copy .\data\tracks\g-track-1\alltree.rgb .\runtime\tracks\road\g-track-1\alltree.rgb
if exist .\data\tracks\g-track-1\asphalt2.rgb copy .\data\tracks\g-track-1\asphalt2.rgb .\runtime\tracks\road\g-track-1\asphalt2.rgb
if exist .\data\tracks\g-track-1\asphalt3.rgb copy .\data\tracks\g-track-1\asphalt3.rgb .\runtime\tracks\road\g-track-1\asphalt3.rgb
if exist .\data\tracks\g-track-1\env.rgb copy .\data\tracks\g-track-1\env.rgb .\runtime\tracks\road\g-track-1\env.rgb
if exist .\data\tracks\g-track-1\grassg1.rgb copy .\data\tracks\g-track-1\grassg1.rgb .\runtime\tracks\road\g-track-1\grassg1.rgb
if exist .\data\tracks\g-track-1\grassg2.rgb copy .\data\tracks\g-track-1\grassg2.rgb .\runtime\tracks\road\g-track-1\grassg2.rgb
if exist .\data\tracks\g-track-1\grassg3.rgb copy .\data\tracks\g-track-1\grassg3.rgb .\runtime\tracks\road\g-track-1\grassg3.rgb
if exist .\data\tracks\g-track-1\rock2.rgb copy .\data\tracks\g-track-1\rock2.rgb .\runtime\tracks\road\g-track-1\rock2.rgb
if exist .\data\tracks\g-track-1\rock3.rgb copy .\data\tracks\g-track-1\rock3.rgb .\runtime\tracks\road\g-track-1\rock3.rgb
if exist .\data\tracks\g-track-1\texte1.rgb copy .\data\tracks\g-track-1\texte1.rgb .\runtime\tracks\road\g-track-1\texte1.rgb

if exist .\data\tracks\michigan\*.* call .\create_dir .\runtime
if exist .\data\tracks\michigan\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\michigan\*.* call .\create_dir .\runtime\tracks\oval
if exist .\data\tracks\michigan\*.* call .\create_dir .\runtime\tracks\oval\michigan
if exist .\data\tracks\michigan\michigan.xml copy .\data\tracks\michigan\michigan.xml .\runtime\tracks\oval\michigan\michigan.xml
if exist .\data\tracks\michigan\background.png copy .\data\tracks\michigan\background.png .\runtime\tracks\oval\michigan\background.png
if exist .\data\tracks\michigan\michigan.ac copy .\data\tracks\michigan\michigan.ac .\runtime\tracks\oval\michigan\michigan.ac
if exist .\data\tracks\michigan\michigan.png copy .\data\tracks\michigan\michigan.png .\runtime\tracks\oval\michigan\michigan.png

if exist .\data\tracks\mixed-1\*.* call .\create_dir .\runtime
if exist .\data\tracks\mixed-1\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\mixed-1\*.* call .\create_dir .\runtime\tracks\dirt
if exist .\data\tracks\mixed-1\*.* call .\create_dir .\runtime\tracks\dirt\mixed-1
if exist .\data\tracks\mixed-1\background.png copy .\data\tracks\mixed-1\background.png .\runtime\tracks\dirt\mixed-1\background.png
if exist .\data\tracks\mixed-1\env1.png copy .\data\tracks\mixed-1\env1.png .\runtime\tracks\dirt\mixed-1\env1.png
rem if exist .\data\tracks\mixed-1\Makefile copy .\data\tracks\mixed-1\Makefile .\runtime\tracks\dirt\mixed-1\Makefile
rem if exist .\data\tracks\mixed-1\mixed-1.ac copy .\data\tracks\mixed-1\mixed-1.ac .\runtime\tracks\dirt\mixed-1\mixed-1.ac
if exist .\data\tracks\mixed-1\mixed-1.acc copy .\data\tracks\mixed-1\mixed-1.acc .\runtime\tracks\dirt\mixed-1\mixed-1.acc
if exist .\data\tracks\mixed-1\mixed-1.png copy .\data\tracks\mixed-1\mixed-1.png .\runtime\tracks\dirt\mixed-1\mixed-1.png
rem if exist .\data\tracks\mixed-1\mixed-1-s.ac copy .\data\tracks\mixed-1\mixed-1-s.ac .\runtime\tracks\dirt\mixed-1\mixed-1-s.ac
if exist .\data\tracks\mixed-1\mixed-1.xml copy .\data\tracks\mixed-1\mixed-1.xml .\runtime\tracks\dirt\mixed-1\mixed-1.xml
if exist .\data\tracks\mixed-1\shadow2.rgb copy .\data\tracks\mixed-1\shadow2.rgb .\runtime\tracks\dirt\mixed-1\shadow2.rgb

if exist .\data\tracks\mixed-2\*.* call .\create_dir .\runtime
if exist .\data\tracks\mixed-2\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\mixed-2\*.* call .\create_dir .\runtime\tracks\dirt
if exist .\data\tracks\mixed-2\*.* call .\create_dir .\runtime\tracks\dirt\mixed-2
if exist .\data\tracks\mixed-2\mixed-2.xml copy .\data\tracks\mixed-2\mixed-2.xml .\runtime\tracks\dirt\mixed-2\mixed-2.xml
if exist .\data\tracks\mixed-2\background.png copy .\data\tracks\mixed-2\background.png .\runtime\tracks\dirt\mixed-2\background.png
if exist .\data\tracks\mixed-2\env.rgb copy .\data\tracks\mixed-2\env.rgb .\runtime\tracks\dirt\mixed-2\env.rgb
if exist .\data\tracks\mixed-2\mixed-2.ac copy .\data\tracks\mixed-2\mixed-2.ac .\runtime\tracks\dirt\mixed-2\mixed-2.ac
if exist .\data\tracks\mixed-2\mixed-2.png copy .\data\tracks\mixed-2\mixed-2.png .\runtime\tracks\dirt\mixed-2\mixed-2.png

if exist .\data\tracks\oval\b-speedway\*.* call .\create_dir .\runtime
if exist .\data\tracks\oval\b-speedway\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\oval\b-speedway\*.* call .\create_dir .\runtime\tracks\oval
if exist .\data\tracks\oval\b-speedway\*.* call .\create_dir .\runtime\tracks\oval\b-speedway
if exist .\data\tracks\oval\b-speedway\background.png copy .\data\tracks\oval\b-speedway\background.png .\runtime\tracks\oval\b-speedway\background.png
if exist .\data\tracks\oval\b-speedway\b-speedway.ac copy .\data\tracks\oval\b-speedway\b-speedway.ac .\runtime\tracks\oval\b-speedway\b-speedway.ac
if exist .\data\tracks\oval\b-speedway\b-speedway.png copy .\data\tracks\oval\b-speedway\b-speedway.png .\runtime\tracks\oval\b-speedway\b-speedway.png
rem if exist .\data\tracks\oval\b-speedway\b-speedway-relief.ac copy .\data\tracks\oval\b-speedway\b-speedway-relief.ac .\runtime\tracks\oval\b-speedway\b-speedway-relief.ac
if exist .\data\tracks\oval\b-speedway\b-speedway.xml copy .\data\tracks\oval\b-speedway\b-speedway.xml .\runtime\tracks\oval\b-speedway\b-speedway.xml
rem if exist .\data\tracks\oval\b-speedway\Makefile copy .\data\tracks\oval\b-speedway\Makefile .\runtime\tracks\oval\b-speedway\Makefile

if exist .\data\tracks\oval\c-speedway\*.* call .\create_dir .\runtime
if exist .\data\tracks\oval\c-speedway\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\oval\c-speedway\*.* call .\create_dir .\runtime\tracks\oval
if exist .\data\tracks\oval\c-speedway\*.* call .\create_dir .\runtime\tracks\oval\c-speedway
if exist .\data\tracks\oval\c-speedway\background.png copy .\data\tracks\oval\c-speedway\background.png .\runtime\tracks\oval\c-speedway\background.png
if exist .\data\tracks\oval\c-speedway\c-speedway.ac copy .\data\tracks\oval\c-speedway\c-speedway.ac .\runtime\tracks\oval\c-speedway\c-speedway.ac
if exist .\data\tracks\oval\c-speedway\c-speedway.png copy .\data\tracks\oval\c-speedway\c-speedway.png .\runtime\tracks\oval\c-speedway\c-speedway.png
rem if exist .\data\tracks\oval\c-speedway\c-speedway-relief.ac copy .\data\tracks\oval\c-speedway\c-speedway-relief.ac .\runtime\tracks\oval\c-speedway\c-speedway-relief.ac
if exist .\data\tracks\oval\c-speedway\c-speedway.xml copy .\data\tracks\oval\c-speedway\c-speedway.xml .\runtime\tracks\oval\c-speedway\c-speedway.xml
rem if exist .\data\tracks\oval\c-speedway\Makefile copy .\data\tracks\oval\c-speedway\Makefile .\runtime\tracks\oval\c-speedway\Makefile

if exist .\data\tracks\oval\d-speedway\*.* call .\create_dir .\runtime
if exist .\data\tracks\oval\d-speedway\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\oval\d-speedway\*.* call .\create_dir .\runtime\tracks\oval
if exist .\data\tracks\oval\d-speedway\*.* call .\create_dir .\runtime\tracks\oval\d-speedway
if exist .\data\tracks\oval\d-speedway\background.png copy .\data\tracks\oval\d-speedway\background.png .\runtime\tracks\oval\d-speedway\background.png
if exist .\data\tracks\oval\d-speedway\d-speedway.ac copy .\data\tracks\oval\d-speedway\d-speedway.ac .\runtime\tracks\oval\d-speedway\d-speedway.ac
if exist .\data\tracks\oval\d-speedway\d-speedway.png copy .\data\tracks\oval\d-speedway\d-speedway.png .\runtime\tracks\oval\d-speedway\d-speedway.png
rem if exist .\data\tracks\oval\d-speedway\d-speedway-relief.ac copy .\data\tracks\oval\d-speedway\d-speedway-relief.ac .\runtime\tracks\oval\d-speedway\d-speedway-relief.ac
if exist .\data\tracks\oval\d-speedway\d-speedway.xml copy .\data\tracks\oval\d-speedway\d-speedway.xml .\runtime\tracks\oval\d-speedway\d-speedway.xml
rem if exist .\data\tracks\oval\d-speedway\Makefile copy .\data\tracks\oval\d-speedway\Makefile .\runtime\tracks\oval\d-speedway\Makefile

if exist .\data\tracks\oval\e-speedway\*.* call .\create_dir .\runtime
if exist .\data\tracks\oval\e-speedway\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\oval\e-speedway\*.* call .\create_dir .\runtime\tracks\oval
if exist .\data\tracks\oval\e-speedway\*.* call .\create_dir .\runtime\tracks\oval\e-speedway
if exist .\data\tracks\oval\e-speedway\background.png copy .\data\tracks\oval\e-speedway\background.png .\runtime\tracks\oval\e-speedway\background.png
if exist .\data\tracks\oval\e-speedway\e-speedway.ac copy .\data\tracks\oval\e-speedway\e-speedway.ac .\runtime\tracks\oval\e-speedway\e-speedway.ac
if exist .\data\tracks\oval\e-speedway\e-speedway.png copy .\data\tracks\oval\e-speedway\e-speedway.png .\runtime\tracks\oval\e-speedway\e-speedway.png
rem if exist .\data\tracks\oval\e-speedway\e-speedway-relief.ac copy .\data\tracks\oval\e-speedway\e-speedway-relief.ac .\runtime\tracks\oval\e-speedway\e-speedway-relief.ac
if exist .\data\tracks\oval\e-speedway\e-speedway.xml copy .\data\tracks\oval\e-speedway\e-speedway.xml .\runtime\tracks\oval\e-speedway\e-speedway.xml
rem if exist .\data\tracks\oval\e-speedway\Makefile copy .\data\tracks\oval\e-speedway\Makefile .\runtime\tracks\oval\e-speedway\Makefile

if exist .\data\tracks\oval\f-speedway\*.* call .\create_dir .\runtime
if exist .\data\tracks\oval\f-speedway\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\oval\f-speedway\*.* call .\create_dir .\runtime\tracks\oval
if exist .\data\tracks\oval\f-speedway\*.* call .\create_dir .\runtime\tracks\oval\f-speedway
if exist .\data\tracks\oval\f-speedway\background.png copy .\data\tracks\oval\f-speedway\background.png .\runtime\tracks\oval\f-speedway\background.png
if exist .\data\tracks\oval\f-speedway\f-speedway.ac copy .\data\tracks\oval\f-speedway\f-speedway.ac .\runtime\tracks\oval\f-speedway\f-speedway.ac
if exist .\data\tracks\oval\f-speedway\f-speedway.png copy .\data\tracks\oval\f-speedway\f-speedway.png .\runtime\tracks\oval\f-speedway\f-speedway.png
rem if exist .\data\tracks\oval\f-speedway\f-speedway-relief.ac copy .\data\tracks\oval\f-speedway\f-speedway-relief.ac .\runtime\tracks\oval\f-speedway\f-speedway-relief.ac
if exist .\data\tracks\oval\f-speedway\f-speedway.xml copy .\data\tracks\oval\f-speedway\f-speedway.xml .\runtime\tracks\oval\f-speedway\f-speedway.xml
rem if exist .\data\tracks\oval\f-speedway\Makefile copy .\data\tracks\oval\f-speedway\Makefile .\runtime\tracks\oval\f-speedway\Makefile

if exist .\data\tracks\oval\g-speedway\*.* call .\create_dir .\runtime
if exist .\data\tracks\oval\g-speedway\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\oval\g-speedway\*.* call .\create_dir .\runtime\tracks\oval
if exist .\data\tracks\oval\g-speedway\*.* call .\create_dir .\runtime\tracks\oval\g-speedway
if exist .\data\tracks\oval\g-speedway\background.png copy .\data\tracks\oval\g-speedway\background.png .\runtime\tracks\oval\g-speedway\background.png
if exist .\data\tracks\oval\g-speedway\g-speedway.ac copy .\data\tracks\oval\g-speedway\g-speedway.ac .\runtime\tracks\oval\g-speedway\g-speedway.ac
if exist .\data\tracks\oval\g-speedway\g-speedway.png copy .\data\tracks\oval\g-speedway\g-speedway.png .\runtime\tracks\oval\g-speedway\g-speedway.png
rem if exist .\data\tracks\oval\g-speedway\g-speedway-relief.ac copy .\data\tracks\oval\g-speedway\g-speedway-relief.ac .\runtime\tracks\oval\g-speedway\g-speedway-relief.ac
if exist .\data\tracks\oval\g-speedway\g-speedway.xml copy .\data\tracks\oval\g-speedway\g-speedway.xml .\runtime\tracks\oval\g-speedway\g-speedway.xml
rem if exist .\data\tracks\oval\g-speedway\Makefile copy .\data\tracks\oval\g-speedway\Makefile .\runtime\tracks\oval\g-speedway\Makefile

if exist .\data\tracks\oval\h-speedway\*.* call .\create_dir .\runtime
if exist .\data\tracks\oval\h-speedway\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\oval\h-speedway\*.* call .\create_dir .\runtime\tracks\oval
if exist .\data\tracks\oval\h-speedway\*.* call .\create_dir .\runtime\tracks\oval\h-speedway
if exist .\data\tracks\oval\h-speedway\background.png copy .\data\tracks\oval\h-speedway\background.png .\runtime\tracks\oval\h-speedway\background.png
if exist .\data\tracks\oval\h-speedway\h-speedway.ac copy .\data\tracks\oval\h-speedway\h-speedway.ac .\runtime\tracks\oval\h-speedway\h-speedway.ac
if exist .\data\tracks\oval\h-speedway\h-speedway.png copy .\data\tracks\oval\h-speedway\h-speedway.png .\runtime\tracks\oval\h-speedway\h-speedway.png
if exist .\data\tracks\oval\h-speedway\h-speedway.xml copy .\data\tracks\oval\h-speedway\h-speedway.xml .\runtime\tracks\oval\h-speedway\h-speedway.xml
rem if exist .\data\tracks\oval\h-speedway\Makefile copy .\data\tracks\oval\h-speedway\Makefile .\runtime\tracks\oval\h-speedway\Makefile

if exist .\data\tracks\road\alpine-1\*.* call .\create_dir .\runtime
if exist .\data\tracks\road\alpine-1\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\road\alpine-1\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\road\alpine-1\*.* call .\create_dir .\runtime\tracks\road\alpine-1
if exist .\data\tracks\road\alpine-1\alpine-1.ac copy .\data\tracks\road\alpine-1\alpine-1.ac .\runtime\tracks\road\alpine-1\alpine-1.ac
if exist .\data\tracks\road\alpine-1\alpine-1.png copy .\data\tracks\road\alpine-1\alpine-1.png .\runtime\tracks\road\alpine-1\alpine-1.png
if exist .\data\tracks\road\alpine-1\alpine-1.xml copy .\data\tracks\road\alpine-1\alpine-1.xml .\runtime\tracks\road\alpine-1\alpine-1.xml
if exist .\data\tracks\road\alpine-1\arbor01.rgb copy .\data\tracks\road\alpine-1\arbor01.rgb .\runtime\tracks\road\alpine-1\arbor01.rgb
if exist .\data\tracks\road\alpine-1\asgrassr_n.rgb copy .\data\tracks\road\alpine-1\asgrassr_n.rgb .\runtime\tracks\road\alpine-1\asgrassr_n.rgb
if exist .\data\tracks\road\alpine-1\background.png copy .\data\tracks\road\alpine-1\background.png .\runtime\tracks\road\alpine-1\background.png
if exist .\data\tracks\road\alpine-1\barg3.rgb copy .\data\tracks\road\alpine-1\barg3.rgb .\runtime\tracks\road\alpine-1\barg3.rgb
if exist .\data\tracks\road\alpine-1\barrier.rgb copy .\data\tracks\road\alpine-1\barrier.rgb .\runtime\tracks\road\alpine-1\barrier.rgb
if exist .\data\tracks\road\alpine-1\cham2.rgb copy .\data\tracks\road\alpine-1\cham2.rgb .\runtime\tracks\road\alpine-1\cham2.rgb
if exist .\data\tracks\road\alpine-1\concdal.rgb copy .\data\tracks\road\alpine-1\concdal.rgb .\runtime\tracks\road\alpine-1\concdal.rgb
rem if exist .\data\tracks\road\alpine-1\elevation-map.png copy .\data\tracks\road\alpine-1\elevation-map.png .\runtime\tracks\road\alpine-1\elevation-map.png
if exist .\data\tracks\road\alpine-1\gconcrete.rgb copy .\data\tracks\road\alpine-1\gconcrete.rgb .\runtime\tracks\road\alpine-1\gconcrete.rgb
if exist .\data\tracks\road\alpine-1\ggrass3.rgb copy .\data\tracks\road\alpine-1\ggrass3.rgb .\runtime\tracks\road\alpine-1\ggrass3.rgb
if exist .\data\tracks\road\alpine-1\house.rgb copy .\data\tracks\road\alpine-1\house.rgb .\runtime\tracks\road\alpine-1\house.rgb
rem if exist .\data\tracks\road\alpine-1\Makefile copy .\data\tracks\road\alpine-1\Makefile .\runtime\tracks\road\alpine-1\Makefile
if exist .\data\tracks\road\alpine-1\mur2.rgb copy .\data\tracks\road\alpine-1\mur2.rgb .\runtime\tracks\road\alpine-1\mur2.rgb
if exist .\data\tracks\road\alpine-1\murpub.rgb copy .\data\tracks\road\alpine-1\murpub.rgb .\runtime\tracks\road\alpine-1\murpub.rgb
if exist .\data\tracks\road\alpine-1\poutre3.rgb copy .\data\tracks\road\alpine-1\poutre3.rgb .\runtime\tracks\road\alpine-1\poutre3.rgb
rem if exist .\data\tracks\road\alpine-1\relief.ac copy .\data\tracks\road\alpine-1\relief.ac .\runtime\tracks\road\alpine-1\relief.ac
if exist .\data\tracks\road\alpine-1\road1.rgb copy .\data\tracks\road\alpine-1\road1.rgb .\runtime\tracks\road\alpine-1\road1.rgb
if exist .\data\tracks\road\alpine-1\road4.rgb copy .\data\tracks\road\alpine-1\road4.rgb .\runtime\tracks\road\alpine-1\road4.rgb
if exist .\data\tracks\road\alpine-1\rockg0.rgb copy .\data\tracks\road\alpine-1\rockg0.rgb .\runtime\tracks\road\alpine-1\rockg0.rgb
if exist .\data\tracks\road\alpine-1\shadow2.rgb copy .\data\tracks\road\alpine-1\shadow2.rgb .\runtime\tracks\road\alpine-1\shadow2.rgb
if exist .\data\tracks\road\alpine-1\torcs2.rgb copy .\data\tracks\road\alpine-1\torcs2.rgb .\runtime\tracks\road\alpine-1\torcs2.rgb
if exist .\data\tracks\road\alpine-1\treeg10.rgb copy .\data\tracks\road\alpine-1\treeg10.rgb .\runtime\tracks\road\alpine-1\treeg10.rgb
if exist .\data\tracks\road\alpine-1\truck0.rgb copy .\data\tracks\road\alpine-1\truck0.rgb .\runtime\tracks\road\alpine-1\truck0.rgb
if exist .\data\tracks\road\alpine-1\truck1.rgb copy .\data\tracks\road\alpine-1\truck1.rgb .\runtime\tracks\road\alpine-1\truck1.rgb
if exist .\data\tracks\road\alpine-1\walls2.rgb copy .\data\tracks\road\alpine-1\walls2.rgb .\runtime\tracks\road\alpine-1\walls2.rgb
if exist .\data\tracks\road\alpine-1\walls.rgb copy .\data\tracks\road\alpine-1\walls.rgb .\runtime\tracks\road\alpine-1\walls.rgb

if exist .\data\tracks\road\g-track-2\*.* call .\create_dir .\runtime
if exist .\data\tracks\road\g-track-2\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\road\g-track-2\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\road\g-track-2\*.* call .\create_dir .\runtime\tracks\road\g-track-2
if exist .\data\tracks\road\g-track-2\g-track-2.xml copy .\data\tracks\road\g-track-2\g-track-2.xml .\runtime\tracks\road\g-track-2\g-track-2.xml
if exist .\data\tracks\road\g-track-2\g-track-2.acc copy .\data\tracks\road\g-track-2\g-track-2.acc .\runtime\tracks\road\g-track-2\g-track-2.acc
rem if exist .\data\tracks\road\g-track-2\g-track-2.ac copy .\data\tracks\road\g-track-2\g-track-2.ac .\runtime\tracks\road\g-track-2\g-track-2.ac
rem if exist .\data\tracks\road\g-track-2\g-track-2-relief.ac copy .\data\tracks\road\g-track-2\g-track-2-relief.ac .\runtime\tracks\road\g-track-2\g-track-2-relief.ac
if exist .\data\tracks\road\g-track-2\g-track-2.png copy .\data\tracks\road\g-track-2\g-track-2.png .\runtime\tracks\road\g-track-2\g-track-2.png
if exist .\data\tracks\road\g-track-2\background.png copy .\data\tracks\road\g-track-2\background.png .\runtime\tracks\road\g-track-2\background.png
if exist .\data\tracks\road\g-track-2\alltree2.rgb copy .\data\tracks\road\g-track-2\alltree2.rgb .\runtime\tracks\road\g-track-2\alltree2.rgb
if exist .\data\tracks\road\g-track-2\alltree.rgb copy .\data\tracks\road\g-track-2\alltree.rgb .\runtime\tracks\road\g-track-2\alltree.rgb
if exist .\data\tracks\road\g-track-2\arbor01.rgb copy .\data\tracks\road\g-track-2\arbor01.rgb .\runtime\tracks\road\g-track-2\arbor01.rgb
if exist .\data\tracks\road\g-track-2\asasphr.rgb copy .\data\tracks\road\g-track-2\asasphr.rgb .\runtime\tracks\road\g-track-2\asasphr.rgb
if exist .\data\tracks\road\g-track-2\asb2l.rgb copy .\data\tracks\road\g-track-2\asb2l.rgb .\runtime\tracks\road\g-track-2\asb2l.rgb
if exist .\data\tracks\road\g-track-2\asb2r.rgb copy .\data\tracks\road\g-track-2\asb2r.rgb .\runtime\tracks\road\g-track-2\asb2r.rgb
if exist .\data\tracks\road\g-track-2\asbl.rgb copy .\data\tracks\road\g-track-2\asbl.rgb .\runtime\tracks\road\g-track-2\asbl.rgb
if exist .\data\tracks\road\g-track-2\asconcr.rgb copy .\data\tracks\road\g-track-2\asconcr.rgb .\runtime\tracks\road\g-track-2\asconcr.rgb
if exist .\data\tracks\road\g-track-2\asgrassl.rgb copy .\data\tracks\road\g-track-2\asgrassl.rgb .\runtime\tracks\road\g-track-2\asgrassl.rgb
if exist .\data\tracks\road\g-track-2\asgrassr.rgb copy .\data\tracks\road\g-track-2\asgrassr.rgb .\runtime\tracks\road\g-track-2\asgrassr.rgb
if exist .\data\tracks\road\g-track-2\asphalt2.rgb copy .\data\tracks\road\g-track-2\asphalt2.rgb .\runtime\tracks\road\g-track-2\asphalt2.rgb
if exist .\data\tracks\road\g-track-2\asphalt3.rgb copy .\data\tracks\road\g-track-2\asphalt3.rgb .\runtime\tracks\road\g-track-2\asphalt3.rgb
if exist .\data\tracks\road\g-track-2\asphalt4.rgb copy .\data\tracks\road\g-track-2\asphalt4.rgb .\runtime\tracks\road\g-track-2\asphalt4.rgb
if exist .\data\tracks\road\g-track-2\asphalt.rgb copy .\data\tracks\road\g-track-2\asphalt.rgb .\runtime\tracks\road\g-track-2\asphalt.rgb
if exist .\data\tracks\road\g-track-2\asphaltr.rgb copy .\data\tracks\road\g-track-2\asphaltr.rgb .\runtime\tracks\road\g-track-2\asphaltr.rgb
if exist .\data\tracks\road\g-track-2\asp_nmm.rgb copy .\data\tracks\road\g-track-2\asp_nmm.rgb .\runtime\tracks\road\g-track-2\asp_nmm.rgb
if exist .\data\tracks\road\g-track-2\asp_n.rgb copy .\data\tracks\road\g-track-2\asp_n.rgb .\runtime\tracks\road\g-track-2\asp_n.rgb
if exist .\data\tracks\road\g-track-2\assandr.rgb copy .\data\tracks\road\g-track-2\assandr.rgb .\runtime\tracks\road\g-track-2\assandr.rgb
if exist .\data\tracks\road\g-track-2\astiled.rgb copy .\data\tracks\road\g-track-2\astiled.rgb .\runtime\tracks\road\g-track-2\astiled.rgb
if exist .\data\tracks\road\g-track-2\barg1_n.rgb copy .\data\tracks\road\g-track-2\barg1_n.rgb .\runtime\tracks\road\g-track-2\barg1_n.rgb
if exist .\data\tracks\road\g-track-2\barg2.rgb copy .\data\tracks\road\g-track-2\barg2.rgb .\runtime\tracks\road\g-track-2\barg2.rgb
if exist .\data\tracks\road\g-track-2\barg3.rgb copy .\data\tracks\road\g-track-2\barg3.rgb .\runtime\tracks\road\g-track-2\barg3.rgb
if exist .\data\tracks\road\g-track-2\barr1.rgb copy .\data\tracks\road\g-track-2\barr1.rgb .\runtime\tracks\road\g-track-2\barr1.rgb
if exist .\data\tracks\road\g-track-2\concdal.rgb copy .\data\tracks\road\g-track-2\concdal.rgb .\runtime\tracks\road\g-track-2\concdal.rgb
if exist .\data\tracks\road\g-track-2\env.rgb copy .\data\tracks\road\g-track-2\env.rgb .\runtime\tracks\road\g-track-2\env.rgb
if exist .\data\tracks\road\g-track-2\gconcrete.rgb copy .\data\tracks\road\g-track-2\gconcrete.rgb .\runtime\tracks\road\g-track-2\gconcrete.rgb
if exist .\data\tracks\road\g-track-2\grassg1.rgb copy .\data\tracks\road\g-track-2\grassg1.rgb .\runtime\tracks\road\g-track-2\grassg1.rgb
if exist .\data\tracks\road\g-track-2\grassg2.rgb copy .\data\tracks\road\g-track-2\grassg2.rgb .\runtime\tracks\road\g-track-2\grassg2.rgb
if exist .\data\tracks\road\g-track-2\grassg3.rgb copy .\data\tracks\road\g-track-2\grassg3.rgb .\runtime\tracks\road\g-track-2\grassg3.rgb
if exist .\data\tracks\road\g-track-2\grtiled.rgb copy .\data\tracks\road\g-track-2\grtiled.rgb .\runtime\tracks\road\g-track-2\grtiled.rgb
if exist .\data\tracks\road\g-track-2\gsand.rgb copy .\data\tracks\road\g-track-2\gsand.rgb .\runtime\tracks\road\g-track-2\gsand.rgb
if exist .\data\tracks\road\g-track-2\gsandtiled.rgb copy .\data\tracks\road\g-track-2\gsandtiled.rgb .\runtime\tracks\road\g-track-2\gsandtiled.rgb
if exist .\data\tracks\road\g-track-2\gtirewall.rgb copy .\data\tracks\road\g-track-2\gtirewall.rgb .\runtime\tracks\road\g-track-2\gtirewall.rgb
if exist .\data\tracks\road\g-track-2\gwall.rgb copy .\data\tracks\road\g-track-2\gwall.rgb .\runtime\tracks\road\g-track-2\gwall.rgb
if exist .\data\tracks\road\g-track-2\poutre3.rgb copy .\data\tracks\road\g-track-2\poutre3.rgb .\runtime\tracks\road\g-track-2\poutre3.rgb
if exist .\data\tracks\road\g-track-2\poutre4.rgb copy .\data\tracks\road\g-track-2\poutre4.rgb .\runtime\tracks\road\g-track-2\poutre4.rgb
if exist .\data\tracks\road\g-track-2\reflect.rgb copy .\data\tracks\road\g-track-2\reflect.rgb .\runtime\tracks\road\g-track-2\reflect.rgb
if exist .\data\tracks\road\g-track-2\rock2.rgb copy .\data\tracks\road\g-track-2\rock2.rgb .\runtime\tracks\road\g-track-2\rock2.rgb
if exist .\data\tracks\road\g-track-2\rock3.rgb copy .\data\tracks\road\g-track-2\rock3.rgb .\runtime\tracks\road\g-track-2\rock3.rgb
if exist .\data\tracks\road\g-track-2\rock4.rgb copy .\data\tracks\road\g-track-2\rock4.rgb .\runtime\tracks\road\g-track-2\rock4.rgb
if exist .\data\tracks\road\g-track-2\spec.rgb copy .\data\tracks\road\g-track-2\spec.rgb .\runtime\tracks\road\g-track-2\spec.rgb
if exist .\data\tracks\road\g-track-2\std.rgb copy .\data\tracks\road\g-track-2\std.rgb .\runtime\tracks\road\g-track-2\std.rgb
if exist .\data\tracks\road\g-track-2\tent.rgb copy .\data\tracks\road\g-track-2\tent.rgb .\runtime\tracks\road\g-track-2\tent.rgb
if exist .\data\tracks\road\g-track-2\texte1.rgb copy .\data\tracks\road\g-track-2\texte1.rgb .\runtime\tracks\road\g-track-2\texte1.rgb
if exist .\data\tracks\road\g-track-2\torcs0.rgb copy .\data\tracks\road\g-track-2\torcs0.rgb .\runtime\tracks\road\g-track-2\torcs0.rgb
if exist .\data\tracks\road\g-track-2\torcs1.rgb copy .\data\tracks\road\g-track-2\torcs1.rgb .\runtime\tracks\road\g-track-2\torcs1.rgb
if exist .\data\tracks\road\g-track-2\torcs2.rgb copy .\data\tracks\road\g-track-2\torcs2.rgb .\runtime\tracks\road\g-track-2\torcs2.rgb
if exist .\data\tracks\road\g-track-2\trcurbl.rgb copy .\data\tracks\road\g-track-2\trcurbl.rgb .\runtime\tracks\road\g-track-2\trcurbl.rgb
if exist .\data\tracks\road\g-track-2\trcurbr.rgb copy .\data\tracks\road\g-track-2\trcurbr.rgb .\runtime\tracks\road\g-track-2\trcurbr.rgb
if exist .\data\tracks\road\g-track-2\treecl1.rgb copy .\data\tracks\road\g-track-2\treecl1.rgb .\runtime\tracks\road\g-track-2\treecl1.rgb
if exist .\data\tracks\road\g-track-2\treewate.rgb copy .\data\tracks\road\g-track-2\treewate.rgb .\runtime\tracks\road\g-track-2\treewate.rgb

if exist .\data\tracks\road\g-track-3\*.* call .\create_dir .\runtime
if exist .\data\tracks\road\g-track-3\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\road\g-track-3\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\road\g-track-3\*.* call .\create_dir .\runtime\tracks\road\g-track-3
if exist .\data\tracks\road\g-track-3\g-track-3.xml copy .\data\tracks\road\g-track-3\g-track-3.xml .\runtime\tracks\road\g-track-3\g-track-3.xml
if exist .\data\tracks\road\g-track-3\g-track-3.acc copy .\data\tracks\road\g-track-3\g-track-3.acc .\runtime\tracks\road\g-track-3\g-track-3.acc
if exist .\data\tracks\road\g-track-3\background.png copy .\data\tracks\road\g-track-3\background.png .\runtime\tracks\road\g-track-3\background.png
if exist .\data\tracks\road\g-track-3\env.png copy .\data\tracks\road\g-track-3\env.png .\runtime\tracks\road\g-track-3\env.png
if exist .\data\tracks\road\g-track-3\envshadow.png copy .\data\tracks\road\g-track-3\envshadow.png .\runtime\tracks\road\g-track-3\envshadow.png
if exist .\data\tracks\road\g-track-3\g-track-3.png copy .\data\tracks\road\g-track-3\g-track-3.png .\runtime\tracks\road\g-track-3\g-track-3.png
if exist .\data\tracks\road\g-track-3\arbor01.rgb copy .\data\tracks\road\g-track-3\arbor01.rgb .\runtime\tracks\road\g-track-3\arbor01.rgb
if exist .\data\tracks\road\g-track-3\asasphr.rgb copy .\data\tracks\road\g-track-3\asasphr.rgb .\runtime\tracks\road\g-track-3\asasphr.rgb
if exist .\data\tracks\road\g-track-3\asb2l.rgb copy .\data\tracks\road\g-track-3\asb2l.rgb .\runtime\tracks\road\g-track-3\asb2l.rgb
if exist .\data\tracks\road\g-track-3\asconcr.rgb copy .\data\tracks\road\g-track-3\asconcr.rgb .\runtime\tracks\road\g-track-3\asconcr.rgb
if exist .\data\tracks\road\g-track-3\asgrassr_n.rgb copy .\data\tracks\road\g-track-3\asgrassr_n.rgb .\runtime\tracks\road\g-track-3\asgrassr_n.rgb
if exist .\data\tracks\road\g-track-3\asphalt4.rgb copy .\data\tracks\road\g-track-3\asphalt4.rgb .\runtime\tracks\road\g-track-3\asphalt4.rgb
if exist .\data\tracks\road\g-track-3\asp_n.rgb copy .\data\tracks\road\g-track-3\asp_n.rgb .\runtime\tracks\road\g-track-3\asp_n.rgb
if exist .\data\tracks\road\g-track-3\asp.rgb copy .\data\tracks\road\g-track-3\asp.rgb .\runtime\tracks\road\g-track-3\asp.rgb
if exist .\data\tracks\road\g-track-3\assandr.rgb copy .\data\tracks\road\g-track-3\assandr.rgb .\runtime\tracks\road\g-track-3\assandr.rgb
if exist .\data\tracks\road\g-track-3\astiled.rgb copy .\data\tracks\road\g-track-3\astiled.rgb .\runtime\tracks\road\g-track-3\astiled.rgb
if exist .\data\tracks\road\g-track-3\barg1_n.rgb copy .\data\tracks\road\g-track-3\barg1_n.rgb .\runtime\tracks\road\g-track-3\barg1_n.rgb
if exist .\data\tracks\road\g-track-3\barg2.rgb copy .\data\tracks\road\g-track-3\barg2.rgb .\runtime\tracks\road\g-track-3\barg2.rgb
if exist .\data\tracks\road\g-track-3\barg3.rgb copy .\data\tracks\road\g-track-3\barg3.rgb .\runtime\tracks\road\g-track-3\barg3.rgb
if exist .\data\tracks\road\g-track-3\barg4.rgb copy .\data\tracks\road\g-track-3\barg4.rgb .\runtime\tracks\road\g-track-3\barg4.rgb
if exist .\data\tracks\road\g-track-3\barr1.rgb copy .\data\tracks\road\g-track-3\barr1.rgb .\runtime\tracks\road\g-track-3\barr1.rgb
if exist .\data\tracks\road\g-track-3\concdal.rgb copy .\data\tracks\road\g-track-3\concdal.rgb .\runtime\tracks\road\g-track-3\concdal.rgb
if exist .\data\tracks\road\g-track-3\gconcrete.rgb copy .\data\tracks\road\g-track-3\gconcrete.rgb .\runtime\tracks\road\g-track-3\gconcrete.rgb
if exist .\data\tracks\road\g-track-3\ggrass3.rgb copy .\data\tracks\road\g-track-3\ggrass3.rgb .\runtime\tracks\road\g-track-3\ggrass3.rgb
if exist .\data\tracks\road\g-track-3\ground0.rgb copy .\data\tracks\road\g-track-3\ground0.rgb .\runtime\tracks\road\g-track-3\ground0.rgb
if exist .\data\tracks\road\g-track-3\ground1.rgb copy .\data\tracks\road\g-track-3\ground1.rgb .\runtime\tracks\road\g-track-3\ground1.rgb
if exist .\data\tracks\road\g-track-3\grtiled.rgb copy .\data\tracks\road\g-track-3\grtiled.rgb .\runtime\tracks\road\g-track-3\grtiled.rgb
if exist .\data\tracks\road\g-track-3\gsand.rgb copy .\data\tracks\road\g-track-3\gsand.rgb .\runtime\tracks\road\g-track-3\gsand.rgb
if exist .\data\tracks\road\g-track-3\gsandtiled.rgb copy .\data\tracks\road\g-track-3\gsandtiled.rgb .\runtime\tracks\road\g-track-3\gsandtiled.rgb
if exist .\data\tracks\road\g-track-3\gtirewall.rgb copy .\data\tracks\road\g-track-3\gtirewall.rgb .\runtime\tracks\road\g-track-3\gtirewall.rgb
if exist .\data\tracks\road\g-track-3\house.rgb copy .\data\tracks\road\g-track-3\house.rgb .\runtime\tracks\road\g-track-3\house.rgb
if exist .\data\tracks\road\g-track-3\mur2.rgb copy .\data\tracks\road\g-track-3\mur2.rgb .\runtime\tracks\road\g-track-3\mur2.rgb
if exist .\data\tracks\road\g-track-3\road1.rgb copy .\data\tracks\road\g-track-3\road1.rgb .\runtime\tracks\road\g-track-3\road1.rgb
if exist .\data\tracks\road\g-track-3\road2.rgb copy .\data\tracks\road\g-track-3\road2.rgb .\runtime\tracks\road\g-track-3\road2.rgb
if exist .\data\tracks\road\g-track-3\road3.rgb copy .\data\tracks\road\g-track-3\road3.rgb .\runtime\tracks\road\g-track-3\road3.rgb
if exist .\data\tracks\road\g-track-3\road4.rgb copy .\data\tracks\road\g-track-3\road4.rgb .\runtime\tracks\road\g-track-3\road4.rgb
if exist .\data\tracks\road\g-track-3\road5.rgb copy .\data\tracks\road\g-track-3\road5.rgb .\runtime\tracks\road\g-track-3\road5.rgb
if exist .\data\tracks\road\g-track-3\rockg0.rgb copy .\data\tracks\road\g-track-3\rockg0.rgb .\runtime\tracks\road\g-track-3\rockg0.rgb
if exist .\data\tracks\road\g-track-3\shadow2.rgb copy .\data\tracks\road\g-track-3\shadow2.rgb .\runtime\tracks\road\g-track-3\shadow2.rgb
if exist .\data\tracks\road\g-track-3\skid_m2.rgb copy .\data\tracks\road\g-track-3\skid_m2.rgb .\runtime\tracks\road\g-track-3\skid_m2.rgb
if exist .\data\tracks\road\g-track-3\torcs0.rgb copy .\data\tracks\road\g-track-3\torcs0.rgb .\runtime\tracks\road\g-track-3\torcs0.rgb
if exist .\data\tracks\road\g-track-3\torcs1.rgb copy .\data\tracks\road\g-track-3\torcs1.rgb .\runtime\tracks\road\g-track-3\torcs1.rgb
if exist .\data\tracks\road\g-track-3\torcs2.rgb copy .\data\tracks\road\g-track-3\torcs2.rgb .\runtime\tracks\road\g-track-3\torcs2.rgb
if exist .\data\tracks\road\g-track-3\trcurbl.rgb copy .\data\tracks\road\g-track-3\trcurbl.rgb .\runtime\tracks\road\g-track-3\trcurbl.rgb
if exist .\data\tracks\road\g-track-3\trcurbr.rgb copy .\data\tracks\road\g-track-3\trcurbr.rgb .\runtime\tracks\road\g-track-3\trcurbr.rgb
if exist .\data\tracks\road\g-track-3\treebui1.rgb copy .\data\tracks\road\g-track-3\treebui1.rgb .\runtime\tracks\road\g-track-3\treebui1.rgb
if exist .\data\tracks\road\g-track-3\treeg10.rgb copy .\data\tracks\road\g-track-3\treeg10.rgb .\runtime\tracks\road\g-track-3\treeg10.rgb
if exist .\data\tracks\road\g-track-3\truck0.rgb copy .\data\tracks\road\g-track-3\truck0.rgb .\runtime\tracks\road\g-track-3\truck0.rgb
if exist .\data\tracks\road\g-track-3\truck1.rgb copy .\data\tracks\road\g-track-3\truck1.rgb .\runtime\tracks\road\g-track-3\truck1.rgb
if exist .\data\tracks\road\g-track-3\walls2.rgb copy .\data\tracks\road\g-track-3\walls2.rgb .\runtime\tracks\road\g-track-3\walls2.rgb
if exist .\data\tracks\road\g-track-3\walls.rgb copy .\data\tracks\road\g-track-3\walls.rgb .\runtime\tracks\road\g-track-3\walls.rgb

if exist .\data\tracks\road\ole-road-1\*.* call .\create_dir .\runtime
if exist .\data\tracks\road\ole-road-1\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\road\ole-road-1\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\road\ole-road-1\*.* call .\create_dir .\runtime\tracks\road\ole-road-1
if exist .\data\tracks\road\ole-road-1\ole-road-1.xml copy .\data\tracks\road\ole-road-1\ole-road-1.xml .\runtime\tracks\road\ole-road-1\ole-road-1.xml
if exist .\data\tracks\road\ole-road-1\ole-road-1.acc copy .\data\tracks\road\ole-road-1\ole-road-1.acc .\runtime\tracks\road\ole-road-1\ole-road-1.acc
if exist .\data\tracks\road\ole-road-1\background.png copy .\data\tracks\road\ole-road-1\background.png .\runtime\tracks\road\ole-road-1\background.png
if exist .\data\tracks\road\ole-road-1\concrete-patch.png copy .\data\tracks\road\ole-road-1\concrete-patch.png .\runtime\tracks\road\ole-road-1\concrete-patch.png
if exist .\data\tracks\road\ole-road-1\cracked-asphalt.png copy .\data\tracks\road\ole-road-1\cracked-asphalt.png .\runtime\tracks\road\ole-road-1\cracked-asphalt.png
if exist .\data\tracks\road\ole-road-1\patched-asphalt-1.png copy .\data\tracks\road\ole-road-1\patched-asphalt-1.png .\runtime\tracks\road\ole-road-1\patched-asphalt-1.png
if exist .\data\tracks\road\ole-road-1\patched-asphalt-2.png copy .\data\tracks\road\ole-road-1\patched-asphalt-2.png .\runtime\tracks\road\ole-road-1\patched-asphalt-2.png
if exist .\data\tracks\road\ole-road-1\ole-concrete-side.png copy .\data\tracks\road\ole-road-1\ole-concrete-side.png .\runtime\tracks\road\ole-road-1\ole-concrete-side.png
if exist .\data\tracks\road\ole-road-1\ole-concrete-pits.png copy .\data\tracks\road\ole-road-1\ole-concrete-pits.png .\runtime\tracks\road\ole-road-1\ole-concrete-pits.png
if exist .\data\tracks\road\ole-road-1\close-bush.rgb copy .\data\tracks\road\ole-road-1\close-bush.rgb .\runtime\tracks\road\ole-road-1\close-bush.rgb
if exist .\data\tracks\road\ole-road-1\ole-road-1.png copy .\data\tracks\road\ole-road-1\ole-road-1.png .\runtime\tracks\road\ole-road-1\ole-road-1.png
if exist .\data\tracks\road\ole-road-1\shadow2.rgb copy .\data\tracks\road\ole-road-1\shadow2.rgb .\runtime\tracks\road\ole-road-1\shadow2.rgb
if exist .\data\tracks\road\ole-road-1\tr-asphalt-l_nmm.rgb copy .\data\tracks\road\ole-road-1\tr-asphalt-l_nmm.rgb .\runtime\tracks\road\ole-road-1\tr-asphalt-l_nmm.rgb


if exist .\data\tracks\road\ole-road-1\env.png copy .\data\tracks\road\g-track-3\env.png .\runtime\tracks\road\g-track-3\env.png
if exist .\data\tracks\road\ole-road-1\envshadow.png copy .\data\tracks\road\g-track-3\envshadow.png .\runtime\tracks\road\g-track-3\envshadow.png





if exist .\data\tracks\road\spring\*.* call .\create_dir .\runtime
if exist .\data\tracks\road\spring\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\road\spring\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\road\spring\*.* call .\create_dir .\runtime\tracks\road\spring
if exist .\data\tracks\road\spring\spring.xml copy .\data\tracks\road\spring\spring.xml .\runtime\tracks\road\spring\spring.xml
if exist .\data\tracks\road\spring\spring.ac copy .\data\tracks\road\spring\spring.ac .\runtime\tracks\road\spring\spring.ac
if exist .\data\tracks\road\spring\spring.png copy .\data\tracks\road\spring\spring.png .\runtime\tracks\road\spring\spring.png

if exist .\data\tracks\wheel-1\*.* call .\create_dir .\runtime
if exist .\data\tracks\wheel-1\*.* call .\create_dir .\runtime\tracks
if exist .\data\tracks\wheel-1\*.* call .\create_dir .\runtime\tracks\road
if exist .\data\tracks\wheel-1\*.* call .\create_dir .\runtime\tracks\road\wheel-1
if exist .\data\tracks\wheel-1\wheel-1.xml copy .\data\tracks\wheel-1\wheel-1.xml .\runtime\tracks\road\wheel-1\wheel-1.xml
if exist .\data\tracks\wheel-1\background.png copy .\data\tracks\wheel-1\background.png .\runtime\tracks\road\wheel-1\background.png
if exist .\data\tracks\wheel-1\env.rgb copy .\data\tracks\wheel-1\env.rgb .\runtime\tracks\road\wheel-1\env.rgb
if exist .\data\tracks\wheel-1\wheel-1.ac copy .\data\tracks\wheel-1\wheel-1.ac .\runtime\tracks\road\wheel-1\wheel-1.ac
if exist .\data\tracks\wheel-1\wheel-1.png copy .\data\tracks\wheel-1\wheel-1.png .\runtime\tracks\road\wheel-1\wheel-1.png

if exist .\*.* call .\create_dir .\runtime
if exist .\*.* call .\create_dir .\runtime\.
if exist .\CHANGELOG.html copy .\CHANGELOG.html .\runtime\.\CHANGELOG.html
if exist .\COPYING copy .\COPYING .\runtime\.\COPYING
if exist .\Ticon.png copy .\Ticon.png .\runtime\.\Ticon.png
if exist .\Ticon.ico copy .\Ticon.ico .\runtime\.\Ticon.ico
if exist .\tux.png copy .\tux.png .\runtime\.\tux.png
if exist .\logo-skinner.png copy .\logo-skinner.png .\runtime\.\logo-skinner.png
