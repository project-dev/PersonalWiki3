SET OLDPATH=%PATH%
SET PATH=%COMMON%\zuz;%OLDPATH%

cd %ROOTDIR%\release

SET PWIKIVER=1.0

ZIP -q9 PersonalWiki3_%PWIKIVER%.zip PersonalWiki3\*.*

SET TARGETDIR=Attach
call _pwiki_pack.bat

SET TARGETDIR=Date
call _pwiki_pack.bat

SET TARGETDIR=FixPlan
call _pwiki_pack.bat

SET TARGETDIR=Img
call _pwiki_pack.bat

SET TARGETDIR=Img\Face
call _pwiki_pack.bat

SET TARGETDIR=Plugins
call _pwiki_pack.bat

SET TARGETDIR=ToDo
call _pwiki_pack.bat

SET TARGETDIR=CSS
call _pwiki_pack.bat

SET TARGETDIR=SpDay
call _pwiki_pack.bat

SET TARGETDIR=Wiki
call _pwiki_pack.bat

SET TARGETDIR=Wiki\FrontPage
call _pwiki_pack.bat

SET TARGETDIR=Wiki\ヘルプ
call _pwiki_pack.bat

SET TARGETDIR=Wiki\ヘルプ\サポートとライセンス
call _pwiki_pack.bat

SET TARGETDIR=Wiki\ヘルプ\ルール
call _pwiki_pack.bat

SET TARGETDIR=Wiki\ヘルプ\暗号化について
call _pwiki_pack.bat

SET TARGETDIR=Wiki\ヘルプ\機能説明
call _pwiki_pack.bat

SET TARGETDIR=Wiki\ヘルプ\PersonalWikiの設定
call _pwiki_pack.bat

SET TARGETDIR=Wiki\ヘルプ\定期データの設定
call _pwiki_pack.bat

SET TARGETDIR=Wiki\ヘルプ\更新履歴
call _pwiki_pack.bat

SET TARGETDIR=Wiki\ヘルプ\他のスタンドアローンWiki
call _pwiki_pack.bat

SET TARGETDIR=Wiki\ヘルプ\免責
call _pwiki_pack.bat

cd %ROOTDIR%\release\plugins

SET PLGVER=1.0.0beta2
SET TARGETNAME=BinderPlugin
call ..\_plg_pack.bat

SET PLGVER=1.0.0test
SET TARGETNAME=DrawerPlugin
call ..\_plg_pack.bat

SET PLGVER=1.0.0beta2
SET TARGETNAME=RSSPlugin
call ..\_plg_pack.bat

move /Y *.zip ..\