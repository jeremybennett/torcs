TORCS version 1.1.0 Installation Instructions
---------------------------------------------

INSTALLATION FROM BINARIES:
---------------------------

1 - unzip the TORCS-x.y.z-win32.zip

go to the TORCS-x.y.z directory newly created

2 - unzip all the other archives in this directory.
  TORCS-x.y.z-data.zip, TORCS-x.y.z-data-tracks*.zip, TORCS-x.y.z-data-cars.zip
  TORCS-x.y.z-win32-robots*.zip


INSTALLATION FROM SOURCES:
--------------------------

1 - unzip the source archives

IMPORTANT: run setup_win32.bat
----------

Open The TORCS.dsw with VC++6.0
Select the TORCS project and the w32-Release version.

Compile (33 warnings)

exit from VC++

Go to runtime

2 - unzip the data archives

click on wtorcs.exe

Et Voila !


Note:
-----
The debug version is not working at this time, you should use the release version.


VC++ setting:
-------------

View->Properties
	tab size = 8
	Indent size = 4
Tools->Options (Tab)
	tab size = 8
	Indent size = 4

