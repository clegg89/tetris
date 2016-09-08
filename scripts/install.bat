IF "%PLATFORM%" == "x86" (GOTO WIN32) ELSE (GOTO WIN64)

:WIN32
SET BITS=32
SET GENERATOR=Visual Studio 14 2015
SET SFML_COMPILER=windows-vc14
GOTO AFTER

:WIN64
SET BITS=64
SET GENERATOR=Visual Studio 14 2015 Win64
SET SFML_COMPILER=windows-vc14
GOTO AFTER

:AFTER
curl -sSL -o sfml.zip http://www.sfml-dev.org/files/SFML-%SFML_VERSION%-%SFML_COMPILER%-%BITS%-bit.zip
unzip -q sfml.zip -d C:\
DEL sfml.zip
SET SFML_ROOT=C:\SFML-%SFML_VERSION%

curl -sSL -o cpputest.zip http://github.com/cpputest/cpputest/releases/download/%CPPUTEST_VERSION%/cpputest-%CPPUTEST_VERSION%.zip
unzip -q cpputest.zip -d .
DEL cpputest.zip
CD .\cpputest-%CPPUTEST_VERSION%\cpputest_build
@REM Should specify install location
cmake -G %GENERATOR% -DCMAKE_INSTALL_PREFIX=C:\CppUTest-%CPPUTEST_VERSION% -DTESTS=OFF ..
cmake --build . --target install
CD ..\..\
RD cpputest-%CPPUTEST_VERSION%
SET CppUTest_PATH=C:\CppUTest-%CPPUTEST_VERSION%
