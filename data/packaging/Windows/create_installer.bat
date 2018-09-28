@echo off

copy ..\..\..\COPYING meta\license.txt /y
xcopy ..\..\..\bin application\data /h /e /i /y

binarycreator -c config.xml -p . AdvancedMetronomeInstaller
