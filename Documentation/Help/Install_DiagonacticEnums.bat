@ECHO OFF
CLS

REM This is an example script to show how to use the Help Library Manager Launcher to install an MS Help
REM Viewer file.  You can use this as an example for creating a script to run from your product's installer.

REM NOTE: If not executed from within the same folder as the executable, a full path is required on the
REM executable and the HelpContentSetup.msha file.

IF "%1%"=="H2" GOTO HelpViewer2
IF "%1%"=="h2" GOTO HelpViewer2
IF "%1%"=="H21" GOTO HelpViewer21
IF "%1%"=="h21" GOTO HelpViewer21
IF "%1%"=="H22" GOTO HelpViewer22
IF "%1%"=="h22" GOTO HelpViewer22

REM Help Viewer 1.0
REM Uninstall first in case it is already there.  If not, it won't install below.  We'll ignore any error output
REM by redirecting it to NUL.
HelpLibraryManagerLauncher.exe /product "VS" /version "100" /locale en-us /uninstall /silent /vendor "Matthew S Dippel" /productName "Diagonactic Enums" /mediaBookList "Diagonactic Enums Library" > NUL

REM For Help Viewer 1.0. the setup name must be HelpContentSetup.msha so make sure we copy the setup file to that
REM name.  SHFB names it after the help file so that multiple files can be deployed to the same output older at
REM build time.
IF EXIST "DiagonacticEnums.msha" COPY /Y "DiagonacticEnums.msha" HelpContentSetup.msha

REM Install the new content.
HelpLibraryManagerLauncher.exe /product "VS" /version "100" /locale en-us /sourceMedia "%CD%\HelpContentSetup.msha"

GOTO Exit

:HelpViewer2

REM Help Viewer 2.0
REM Uninstall first in case it is already there.  If not, it won't install below.  We'll ignore any error output
REM by redirecting it to NUL.
HelpLibraryManagerLauncher.exe /viewerVersion 2.0  /locale en-us /wait 0 /operation uninstall /vendor "Matthew S Dippel" /productName "Diagonactic Enums" /bookList "Diagonactic Enums Library" > NUL

REM Install the new content.
HelpLibraryManagerLauncher.exe /viewerVersion 2.0  /locale en-us /wait 0 /operation install /sourceUri "%CD%\DiagonacticEnums.msha"

GOTO Exit

:HelpViewer21

REM Help Viewer 2.1
REM Uninstall first in case it is already there.  If not, it won't install below.  We'll ignore any error output
REM by redirecting it to NUL.
HelpLibraryManagerLauncher.exe /viewerVersion 2.1  /locale en-us /wait 0 /operation uninstall /vendor "Matthew S Dippel" /productName "Diagonactic Enums" /bookList "Diagonactic Enums Library" > NUL

REM Install the new content.
HelpLibraryManagerLauncher.exe /viewerVersion 2.1  /locale en-us /wait 0 /operation install /sourceUri "%CD%\DiagonacticEnums.msha"

GOTO Exit

:HelpViewer22

REM Help Viewer 2.2
REM Uninstall first in case it is already there.  If not, it won't install below.  We'll ignore any error output
REM by redirecting it to NUL.
HelpLibraryManagerLauncher.exe /viewerVersion 2.2  /locale en-us /wait 0 /operation uninstall /vendor "Matthew S Dippel" /productName "Diagonactic Enums" /bookList "Diagonactic Enums Library" > NUL

REM Install the new content.
HelpLibraryManagerLauncher.exe /viewerVersion 2.2  /locale en-us /wait 0 /operation install /sourceUri "%CD%\DiagonacticEnums.msha"

:Exit
