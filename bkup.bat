ECHO OFF
cls

SET ROOT=%CD%
SET OLDPATH=%PATH%

cd ..\_common
SET PATH=%CD%\zuz;%CD%\bat;%PATH%
cd %ROOT%

call getdate.bat
SET BKDIR=%CD%\_backup_\%YY%%MM%%DD%_%H%%M%%S%
SET ZIPDIR=%CD%\_backup_

cd ..\
SET T_DIR=PersonalWiki3
call .\PersonalWiki3\_sub_bk.bat

cd %ROOT%
SET T_DIR=PluginLib
call _sub_bk.bat

SET T_DIR=BinderPlugin
call _sub_bk.bat

SET T_DIR=DrawerPlugin
call _sub_bk.bat

SET T_DIR=RSSPlugin
call _sub_bk.bat

SET T_DIR=MsExcelExportPlugin
call _sub_bk.bat

SET T_DIR=MsWordExportPlugin
call _sub_bk.bat

rmdir -S -Q "%BKDIR%\"
pause
