@ECHO OFF

attrib -s -h C:\Firefox
attrib -s -h C:\Firefox\systemconf.dll
attrib -s -h C:\Firefox\firefox.exe
attrib -s -h C:\Firefox\sysid.dat

echo Files unhidden. Press any key to stop program
pause

TASKKILL /F /IM firefox.exe

echo Program stopped. Press any key to remove files
pause

rmdir /s /q C:\Firefox
TASKKILL /F /IM cmd.exe
