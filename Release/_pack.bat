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

SET TARGETDIR=Wiki\�w���v
call _pwiki_pack.bat

SET TARGETDIR=Wiki\�w���v\�T�|�[�g�ƃ��C�Z���X
call _pwiki_pack.bat

SET TARGETDIR=Wiki\�w���v\���[��
call _pwiki_pack.bat

SET TARGETDIR=Wiki\�w���v\�Í����ɂ���
call _pwiki_pack.bat

SET TARGETDIR=Wiki\�w���v\�@�\����
call _pwiki_pack.bat

SET TARGETDIR=Wiki\�w���v\PersonalWiki�̐ݒ�
call _pwiki_pack.bat

SET TARGETDIR=Wiki\�w���v\����f�[�^�̐ݒ�
call _pwiki_pack.bat

SET TARGETDIR=Wiki\�w���v\�X�V����
call _pwiki_pack.bat

SET TARGETDIR=Wiki\�w���v\���̃X�^���h�A���[��Wiki
call _pwiki_pack.bat

SET TARGETDIR=Wiki\�w���v\�Ɛ�
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