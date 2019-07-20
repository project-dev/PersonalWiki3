mkdir "%TODIR%\%PLGNAME%"
mkdir "%TODIR%\%PLGNAME%\PersonalWiki3"
mkdir "%TODIR%\%PLGNAME%\PersonalWiki3\plugins"
copy "%FROMDIR%\%PLGNAME%.pwp" "%TODIR%\%PLGNAME%\PersonalWiki3\plugins"
SET FILEBASE=%ROOTDIR%\%PLGNAME%\%PLGNAME%
if exist "%FILEBASE%.txt" copy "%FILEBASE%.txt" "%TODIR%\%PLGNAME%\PersonalWiki3\plugins"
if exist "%FILEBASE%.pwd" (
mkdir "%TODIR%\%PLGNAME%\PersonalWiki3\wiki"
mkdir "%TODIR%\%PLGNAME%\PersonalWiki3\wiki\プラグインヘルプ"
copy "%FILEBASE%.pwd" "%TODIR%\%PLGNAME%\PersonalWiki3\wiki\プラグインヘルプ"
)
