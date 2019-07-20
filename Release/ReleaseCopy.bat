echo off
cls
cd ..\
SET FROMDIR=%CD%\bin\release
SET TODIR=%CD%\release\PersonalWiki3
SET ROOTDIR=%CD%

cd ..\_common
SET COMMON=%CD%
cd %ROOTDIR%

RMDIR /S /Q %TODIR%

REM 必要なフォルダの作成
mkdir %TODIR%
mkdir %TODIR%\Attach
mkdir %TODIR%\CSS
mkdir %TODIR%\Date
mkdir %TODIR%\FixPlan
mkdir %TODIR%\Img
mkdir %TODIR%\Img\Face
mkdir %TODIR%\plugins
mkdir %TODIR%\SpDay
mkdir %TODIR%\ToDo
mkdir %TODIR%\Wiki

echo 添付ファイルが保存されます>%TODIR%\Attach\readme.txt
echo スタイルシートを入れてください>%TODIR%\CSS\readme.txt
echo スケジュールデータが保存されます>%TODIR%\Date\readme.txt
echo 定期データが保存されます>%TODIR%\FixPlan\readme.txt
echo プラグインの格納先です>%TODIR%\plugins\readme.txt
echo 記念日が保存されます>%TODIR%\SpDay\readme.txt
echo ToDoが保存されます>%TODIR%\ToDo\readme.txt


copy %FROMDIR%\PersonalWiki3.exe %TODIR%
copy %FROMDIR%\dev*.dll %TODIR%
rem copy %FROMDIR%\category.txt %TODIR%
copy %FROMDIR%\mime.dat %TODIR%
copy %FROMDIR%\readme.txt %TODIR%

copy %FROMDIR%\CSS\*.css %TODIR%\CSS

copy %FROMDIR%\Img\Face\*.png %TODIR%\Img\Face

copy %FROMDIR%\SpDay\*.spd %TODIR%\SpDay

cd Release

SET PAGE=FrontPage
SET TOPATH=
call _wikicp.bat

SET PAGE=ヘルプ
SET TOPATH=
call _wikicp.bat

SET PAGE=ヘルプ\サポートとライセンス
SET TOPATH=ヘルプ
call _wikicp.bat

SET PAGE=ヘルプ\ルール
SET TOPATH=ヘルプ
call _wikicp.bat

SET PAGE=ヘルプ\暗号化について
SET TOPATH=ヘルプ
call _wikicp.bat

SET PAGE=ヘルプ\機能説明
SET TOPATH=ヘルプ
call _wikicp.bat

SET PAGE=ヘルプ\更新履歴
SET TOPATH=ヘルプ
call _wikicp.bat

SET PAGE=ヘルプ\他のスタンドアローンWiki
SET TOPATH=ヘルプ
call _wikicp.bat

SET PAGE=ヘルプ\免責
SET TOPATH=ヘルプ
call _wikicp.bat

SET PAGE=ヘルプ\機能説明\PersonalWikiの設定
SET TOPATH=ヘルプ\機能説明
call _wikicp.bat

SET PAGE=ヘルプ\機能説明\定期データの設定
SET TOPATH=ヘルプ\機能説明
call _wikicp.bat

REM -------------------------------------------------------
REM プラグインのコピー
REM -------------------------------------------------------
ECHO プラグインのコピー

CD %ROOTDIR%
SET FROMDIR=%CD%\bin\release\plugins
SET TODIR=%CD%\release\plugins

RMDIR /S /Q %TODIR%

mkdir %TODIR%

cd release

SET PLGNAME=RSSPlugin
call _plugincp.bat

SET PLGNAME=BinderPlugin
call _plugincp.bat
copy %ROOTDIR%\bin\release\BREGEXP.DLL %TODIR%\BinderPlugin\PersonalWiki3

SET PLGNAME=DrawerPlugin
call _plugincp.bat
copy %ROOTDIR%\bin\release\gdiplus.dll %TODIR%\DrawerPlugin\PersonalWiki3

call _pack.bat

pause
