@echo on
IF "%PLATFORM%" == "x86" (GOTO WIN32) ELSE (GOTO WIN64)

:WIN32
SET BITS=32
SET MINGW_URL=https://sourceforge.net/projects/mingw-w64/files/Toolchains%%20targetting%%20Win32/Personal%%20Builds/mingw-builds/4.9.2/threads-posix/dwarf/i686-4.9.2-release-posix-dwarf-rt_v4-rev2.7z/download
GOTO AFTER

:WIN64
SET BITS=64
SET MINGW_URL=https://sourceforge.net/projects/mingw-w64/files/Toolchains%%20targetting%%20Win64/Personal%%20Builds/mingw-builds/4.9.2/threads-posix/seh/x86_64-4.9.2-release-posix-seh-rt_v4-rev2.7z/download
GOTO AFTER

:AFTER
IF EXIST C:\toolchain\mingw GOTO SKIP_MINGW
curl -sSL -omingw.7z %MINGW_URL%
7z x -oC:\toolchain\ mingw.7z
REN C:\toolchain\mingw%BITS% mingw
DEL mingw.7z

:SKIP_MINGW
SET PATH=C:\toolchain\mingw\bin;%PATH%
RD /s /q C:\MinGW

SET PROJ_DIR=%cd%

IF EXIST dependencies\SFML-%SFML_VERSION% GOTO SKIP_SFML
curl -sSL -o sfml.zip http://www.sfml-dev.org/files/SFML-%SFML_VERSION%-%SFML_COMPILER%-%BITS%-bit.zip
unzip -q sfml.zip -d %PROJ_DIR%\dependencies\
DEL sfml.zip

:SKIP_SFML
SET SFML_ROOT=%PROJ_DIR%\dependencies\SFML-%SFML_VERSION%

SET BOOST_ROOT=C:\Libraries\boost_%BOOST_VERSION:.=_%
DIR %BOOST_ROOT%\libs

IF EXIST dependencies\CppUTest-%CPPUTEST_VERSION% GOTO SKIP_CppUTest
curl -sSL -o cpputest.zip https://github.com/cpputest/cpputest/releases/download/v%CPPUTEST_VERSION%/cpputest-%CPPUTEST_VERSION%.zip
unzip -q cpputest.zip -d .
DEL cpputest.zip
CD .\cpputest-%CPPUTEST_VERSION%\cpputest_build
SET OLD_PATH=%PATH%
SET PATH=%PATH:C:\Program Files\Git\usr\bin;=%
SET PATH=%PATH:C:\Program Files (x86)\Git\usr\bin;=%
cmake -G "%GENERATOR%" -DCMAKE_INSTALL_PREFIX=%PROJ_DIR%\dependencies\CppUTest-%CPPUTEST_VERSION% -DTESTS=OFF ..
SET PATH=%OLD_PATH%
cmake --build . --target install
CD ..\..\
RD /s /q cpputest-%CPPUTEST_VERSION%
CD %PROJ_DIR%

:SKIP_CppUTest
SET CppUTest_PATH=%PROJ_DIR%\dependencies\CppUTest-%CPPUTEST_VERSION%
@echo off
