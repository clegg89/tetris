IF "%PLATFORM%" == "x86" (GOTO WIN32) ELSE (GOTO WIN64)

:WIN32
SET BITS=32
SET GENERATOR=Visual Studio 14 2015
GOTO AFTER

:WIN64
SET BITS=64
SET GENERATOR=Visual Studio 14 2015 Win64
GOTO AFTER

:AFTER
curl -sSL -o sfml.zip http://www.sfml-dev.org/files/SFML-%SFML_VERSION%-windows-vc14-%BITS%-bit.zip
UNZIP -q sfml.zip -d C:\
DEL sfml.zip
SET SFML_ROOT=C:\SFML-%SFML_VERSION%
