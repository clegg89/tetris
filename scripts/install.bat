@ECHO ON
IF "%PLATFORM%" == "x86" (GOTO WIN32) ELSE (GOTO WIN64)

:WIN32
choco install mingw --version=%MINGW_VERSION% -forcex86
SET BITS=32
GOTO AFTER

:WIN64
choco install mingw --version=%MINGW_VERSION%
SET BITS=64
GOTO AFTER

:AFTER
SET PATH=C:\tools\mingw%BITS%\bin;%PATH%
@REM DIR C:\tools\mingw%BITS%\bin
@REM RD /s C:\MinGW

curl -sSL -o sfml.zip http://www.sfml-dev.org/files/SFML-%SFML_VERSION%-%SFML_COMPILER%-%BITS%-bit.zip
unzip -q sfml.zip -d C:\
DEL sfml.zip
SET SFML_ROOT=C:\SFML-%SFML_VERSION%

curl -sSL -o cpputest.zip https://github.com/cpputest/cpputest/releases/download/v%CPPUTEST_VERSION%/cpputest-%CPPUTEST_VERSION%.zip
unzip -q cpputest.zip -d .
DEL cpputest.zip
CD .\cpputest-%CPPUTEST_VERSION%\cpputest_build
SET OLD_PATH=%PATH%
SET PATH=%PATH:C:\Program Files\Git\usr\bin;=%
SET PATH=%PATH:C:\Program Files (x86)\Git\usr\bin;=%
cmake -G "%GENERATOR%" -DCMAKE_INSTALL_PREFIX=C:\CppUTest-%CPPUTEST_VERSION% -DTESTS=OFF ..
SET PATH=%OLD_PATH%
cmake --build . --target install
CD ..\..\
RD /s cpputest-%CPPUTEST_VERSION%
SET CppUTest_PATH=C:\CppUTest-%CPPUTEST_VERSION%

@ECHO OFF
