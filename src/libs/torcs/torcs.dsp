# Microsoft Developer Studio Project File - Name="torcs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=torcs - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "torcs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "torcs.mak" CFG="torcs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "torcs - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "torcs - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "torcs - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TORCS_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../../../export/include" /I "../../interfaces" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TORCS_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib tgf.lib /nologo /dll /machine:I386 /libpath:"../../../export/lib"
# Begin Custom Build
InputPath=.\Release\torcs.dll
SOURCE="$(InputPath)"

"..\..\..\export\include\torcs.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy torcs.h ..\..\..\export\include

# End Custom Build
# Begin Special Build Tool
TargetDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetDir)\*.dll ..\..\..\runtime	copy $(TargetDir)\*.lib ..\..\..\export\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "torcs - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TORCS_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W4 /WX /Gm /Gi /GX /ZI /Od /I "../../../export/include" /I "../../interfaces" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TORCS_EXPORTS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib tgf.lib /nologo /dll /debug /machine:I386 /out:"Debug/torcsd.dll" /pdbtype:sept /libpath:"../../../export/lib"
# Begin Custom Build
InputPath=.\Debug\torcsd.dll
SOURCE="$(InputPath)"

"..\..\..\export\include\torcs.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy torcs.h ..\..\..\export\include

# End Custom Build
# Begin Special Build Tool
TargetDir=.\Debug
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetDir)\*.dll ..\..\..\runtimed	copy $(TargetDir)\*.lib ..\..\..\export\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "torcs - Win32 Release"
# Name "torcs - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\driverconfig.cpp
# End Source File
# Begin Source File

SOURCE=.\entry.cpp
# End Source File
# Begin Source File

SOURCE=.\exitmenu.cpp
# End Source File
# Begin Source File

SOURCE=.\graphconfig.cpp
# End Source File
# Begin Source File

SOURCE=.\mainmenu.cpp
# End Source File
# Begin Source File

SOURCE=.\optionmenu.cpp
# End Source File
# Begin Source File

SOURCE=.\raceman.cpp
# End Source File
# Begin Source File

SOURCE=.\splash.cpp
# End Source File
# Begin Source File

SOURCE=.\torcs.def
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\driverconfig.h
# End Source File
# Begin Source File

SOURCE=.\exitmenu.h
# End Source File
# Begin Source File

SOURCE=.\mainmenu.h
# End Source File
# Begin Source File

SOURCE=.\optionmenu.h
# End Source File
# Begin Source File

SOURCE=.\raceman.h
# End Source File
# Begin Source File

SOURCE=.\splash.h
# End Source File
# Begin Source File

SOURCE=.\torcs.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
