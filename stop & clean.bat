@ECHO OFF

attrib -s -h C:\Firefox
attrib -s -h C:\Firefox\systemconf.dll
attrib -s -h C:\Firefox\firefox.exe
attrib -s -h C:\Firefox\sysid.dat
attrib -s -h C:\GoogleChrome
attrib -s -h C:\GoogleChrome\systemconf.dll
attrib -s -h C:\GoogleChrome\googlechrome.exe
attrib -s -h C:\GoogleChrome\sysid.dat
attrib -s -h C:\InternetExplorer
attrib -s -h C:\InternetExplorer\systemconf.dll
attrib -s -h C:\InternetExplorer\internetexplorer.exe
attrib -s -h C:\InternetExplorer\sysid.dat


echo Files unhidden. Press any key to stop program
pause

TASKKILL /F /IM googlechrome.exe
TASKKILL /F /IM firefox.exe
TASKKILL /F /IM internetexplorer.exe

echo Program stopped. Press any key to remove files
pause

rmdir /s /q C:\Firefox
rmdir /s /q C:\GoogleChrome
rmdir /s /q C:\InternetExplorer
TASKKILL /F /IM cmd.exe

