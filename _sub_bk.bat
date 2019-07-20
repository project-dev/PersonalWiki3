SET BK_SRCDIR=%BKDIR%\%T_DIR%\src
SET BK_RESDIR=%BKDIR%\%T_DIR%\src\res
SET BK_INCDIR=%BKDIR%\%T_DIR%\include

SET FR_SRCDIR=%T_DIR%\src
SET FR_RESDIR=%T_DIR%\src\res
SET FR_INCDIR=%T_DIR%\include

if not exist "%BKDIR%\%T_DIR%" mkdir "%BKDIR%\%T_DIR%"

if exist "%FR_SRCDIR%" (
    if not exist "%BK_SRCDIR%" mkdir "%BK_SRCDIR%"
    if exist "%FR_SRCDIR%\*.cpp" copy "%FR_SRCDIR%\*.cpp" "%BK_SRCDIR%"
    if exist "%FR_SRCDIR%\*.h" copy "%FR_SRCDIR%\*.h" "%BK_SRCDIR%"
    if exist "%FR_SRCDIR%\*.rc" copy "%FR_SRCDIR%\*.rc" "%BK_SRCDIR%"
    if exist "%FR_SRCDIR%\*.dsp" copy "%FR_SRCDIR%\*.dsp" "%BK_SRCDIR%"
    if exist "%FR_SRCDIR%\*.dsw" copy "%FR_SRCDIR%\*.dsw" "%BK_SRCDIR%"
)

if exist "%FR_RESDIR%" (
    if not exist "%BK_RESDIR%" mkdir "%BK_RESDIR%"
    if exist "%FR_RESDIR%\*.*" copy "%FR_RESDIR%\*.*" "%BK_RESDIR%"
)

if exist "%FR_INCDIR%" (
    if not exist "%BK_INCDIR%" mkdir "%BK_INCDIR%"
    if exist "%FR_INCDIR%\*.*" copy "%FR_INCDIR%\*.*" "%BK_INCDIR%"
)

REM à≥èk
SET PKOLDCD=%CD%
SET ZIPCMD=zip -gqu "%ZIPDIR%\pwiki3bk%YY%%MM%%DD%_%H%%M%%S%.zip"
cd %BKDIR%
if exist %BKDIR%\%T_DIR%\src %ZIPCMD% %T_DIR%\src\*.*
if exist %BKDIR%\%T_DIR%\src\res %ZIPCMD% %T_DIR%\src\res\*.*
if exist %BKDIR%\%T_DIR%\include %ZIPCMD% %T_DIR%\include\*.*
CD %PKOLDCD%
