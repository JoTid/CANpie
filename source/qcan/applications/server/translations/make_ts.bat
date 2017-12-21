@ECHO OFF
TITLE Execute Qt's Linguist tool chain lupdate
ECHO Create XML based translations files in the *.ts format 
ECHO from translatable messages in C++ and Java source code.
ECHO Make sure system paths are set to:
ECHO QT\Qt5.9.1\5.9.1\mingw53_32\bin 
ECHO QT\Qt5.9.1\Tools\mingw530_32\bin
ECHO.
ECHO.
ECHO.
lupdate.exe -verbose ..\server.pro
ECHO.
ECHO.
ECHO.
PAUSE
EXIT