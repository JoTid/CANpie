@ECHO OFF
TITLE Execute Qt's Linguist tool chain lrelease
ECHO Convert XML based translations files in *.ts format 
ECHO into the 'compiled' *.qm format used by QTranslator objects.
ECHO Make sure system paths are set to:
ECHO QT\Qt5.9.1\5.9.1\mingw53_32\bin 
ECHO QT\Qt5.9.1\Tools\mingw530_32\bin
ECHO.
ECHO.
ECHO.
lrelease.exe -verbose ..\server.pro
ECHO.
ECHO.
ECHO.
PAUSE
EXIT