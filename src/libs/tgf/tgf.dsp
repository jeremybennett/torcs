# Microsoft Developer Studio Project File - Name="tgf" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=tgf - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tgf.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tgf.mak" CFG="tgf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tgf - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "tgf - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tgf - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TGF_EXPORTS" /YX /FD /c
# ADD CPP /nologo /G5 /W4 /GX /O2 /Ob2 /I "../../../export/include" /I "../../windows/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TGF_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 libpng.lib txml.lib sg.lib ul.lib /nologo /dll /machine:I386 /nodefaultlib:"LIBCD" /libpath:"../../../export/lib" /libpath:"../../windows/lib"
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
TargetDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetDir)\*.dll ..\..\..\runtime	copy $(TargetDir)\*.lib ..\..\..\export\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "tgf - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TGF_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /G5 /W4 /Gm /Gi /GX /ZI /Od /I "../../../export/include" /I "../../windows/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TGF_EXPORTS" /D "DEBUG" /FR /YX /FD /GZ /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libpng.lib sg.lib ul.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"../../../export/libd" /libpath:"../../windows/lib"
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
WkspDir=.
TargetDir=.\Debug
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetDir)\*.dll $(WkspDir)\runtimed	copy $(TargetDir)\*.lib $(WkspDir)\export\libd
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "tgf - Win32 Release"
# Name "tgf - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\directory.cpp
# End Source File
# Begin Source File

SOURCE=..\racemantools\driverselect.cpp
# End Source File
# Begin Source File

SOURCE=.\gui.cpp
# End Source File
# Begin Source File

SOURCE=.\guibutton.cpp
# End Source File
# Begin Source File

SOURCE=.\guiedit.cpp
# End Source File
# Begin Source File

SOURCE=.\guifont.cpp
# End Source File
# Begin Source File

SOURCE=.\guihelp.cpp
# End Source File
# Begin Source File

SOURCE=.\guilabel.cpp
# End Source File
# Begin Source File

SOURCE=.\guimenu.cpp
# End Source File
# Begin Source File

SOURCE=.\guiobject.cpp
# End Source File
# Begin Source File

SOURCE=.\guiscrollbar.cpp
# End Source File
# Begin Source File

SOURCE=.\guiscrollist.cpp
# End Source File
# Begin Source File

SOURCE=.\img.cpp
# End Source File
# Begin Source File

SOURCE=.\memory.cpp
# End Source File
# Begin Source File

SOURCE=.\module.cpp
# End Source File
# Begin Source File

SOURCE=.\os.cpp
# End Source File
# Begin Source File

SOURCE=.\params.cpp
# End Source File
# Begin Source File

SOURCE=..\racemantools\pitmenu.cpp
# End Source File
# Begin Source File

SOURCE=.\ringlist.cpp
# End Source File
# Begin Source File

SOURCE=..\robottools\rttelem.cpp
# End Source File
# Begin Source File

SOURCE=..\robottools\rttrack.cpp
# End Source File
# Begin Source File

SOURCE=.\screen.cpp
# End Source File
# Begin Source File

SOURCE=.\tgf.cpp
# End Source File
# Begin Source File

SOURCE=.\tgf.def
# End Source File
# Begin Source File

SOURCE=.\trace.cpp
# End Source File
# Begin Source File

SOURCE=..\racemantools\trackselect.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\gui.h
# End Source File
# Begin Source File

SOURCE=.\guifont.h
# End Source File
# Begin Source File

SOURCE=.\guimenu.h
# End Source File
# Begin Source File

SOURCE=.\os.h
# End Source File
# Begin Source File

SOURCE=.\params.h
# End Source File
# Begin Source File

SOURCE=..\racemantools\racemantools.h
# End Source File
# Begin Source File

SOURCE=..\robottools\robottools.h
# End Source File
# Begin Source File

SOURCE=.\tgf.h
# End Source File
# End Group
# End Target
# End Project
