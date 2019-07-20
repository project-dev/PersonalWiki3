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

REM �K�v�ȃt�H���_�̍쐬
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

echo �Y�t�t�@�C�����ۑ�����܂�>%TODIR%\Attach\readme.txt
echo �X�^�C���V�[�g�����Ă�������>%TODIR%\CSS\readme.txt
echo �X�P�W���[���f�[�^���ۑ�����܂�>%TODIR%\Date\readme.txt
echo ����f�[�^���ۑ�����܂�>%TODIR%\FixPlan\readme.txt
echo �v���O�C���̊i�[��ł�>%TODIR%\plugins\readme.txt
echo �L�O�����ۑ�����܂�>%TODIR%\SpDay\readme.txt
echo ToDo���ۑ�����܂�>%TODIR%\ToDo\readme.txt


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

SET PAGE=�w���v
SET TOPATH=
call _wikicp.bat

SET PAGE=�w���v\�T�|�[�g�ƃ��C�Z���X
SET TOPATH=�w���v
call _wikicp.bat

SET PAGE=�w���v\���[��
SET TOPATH=�w���v
call _wikicp.bat

SET PAGE=�w���v\�Í����ɂ���
SET TOPATH=�w���v
call _wikicp.bat

SET PAGE=�w���v\�@�\����
SET TOPATH=�w���v
call _wikicp.bat

SET PAGE=�w���v\�X�V����
SET TOPATH=�w���v
call _wikicp.bat

SET PAGE=�w���v\���̃X�^���h�A���[��Wiki
SET TOPATH=�w���v
call _wikicp.bat

SET PAGE=�w���v\�Ɛ�
SET TOPATH=�w���v
call _wikicp.bat

SET PAGE=�w���v\�@�\����\PersonalWiki�̐ݒ�
SET TOPATH=�w���v\�@�\����
call _wikicp.bat

SET PAGE=�w���v\�@�\����\����f�[�^�̐ݒ�
SET TOPATH=�w���v\�@�\����
call _wikicp.bat

REM -------------------------------------------------------
REM �v���O�C���̃R�s�[
REM -------------------------------------------------------
ECHO �v���O�C���̃R�s�[

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
