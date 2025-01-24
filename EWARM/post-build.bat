set NAME=%1
set PROJPATH=%2\
set EXEPATH=%3\
set TOOLKITPATH=%4

for /f "tokens=1-4 delims=/ " %%i in ("%date%") do (
     set dow=%%i
     set month=%%j
     set day=%%k
     set year=%%l
)
set datestr=%dow%/%month%/%day%

for /f "delims== tokens=1,2" %%G in (%PROJPATH%buildconfig.cfg) do set %%G=%%H

set BUILD_DATE=%datestr:~0,4%%datestr:~5,2%%datestr:~8,2%
set BUILD_NAME=%NAME:~0,5%
set OUT=%EXEPATH%%1.out

call %PROJPATH%messagebox.bat
set RELEASE=%rel%
echo %RELEASE%

set HEX=%EXEPATH%%-DPROJECT_HW_DEF%_V%-DMAJORVER%.%-DMIDVER%.%-DMINORVER%.%-DINTVER%_%BUILD_DATE%.hex
set BIN=%EXEPATH%%-DPROJECT_HW_DEF%_V%-DMAJORVER%.%-DMIDVER%.%-DMINORVER%.%-DINTVER%_%BUILD_DATE%.bin

:: generate additional output: hex
%TOOLKITPATH%\ielftool.exe --ihex --verbose %OUT% %HEX%

:: generate additional output: binary
%TOOLKITPATH%\ielftool.exe --bin --verbose %OUT% %BIN%

:: del %EXEPATH%%NAME%.bin

