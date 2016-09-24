@rem FILE: install-dependencies.bat
@rem AUTHOR: C. Smith
@rem DESC: Install build/test dependencies (sfml, boost, cpputest)
@echo off
setlocal

@rem Don't run if already installed
if exist %cd%\dependencies\sfml if exist %cd%\dependencies\boost if exist %cd%\dependencies\cpputest goto success

set self=%~nx0

set sfml_version=2.3.2
set boost_version=1.60.0
set cpputest_version=3.8

@rem Skip function prototypes
goto main

@rem FUNCTIONS

@rem Download dependency
:download_dep
setlocal
set output_file=%~1
set url=%~2
echo curl -sSL -o%output_file% %url%
curl -sSL -o%output_file% %url%
if not exist %output_file% (
  echo Failed
  exit /b 1
  )

echo Success
exit /b 0

@rem Install SFML
:install_sfml
setlocal

unzip -q sfml.zip -d %cd%\dependencies\
ren %cd%\dependencies\SFML-%sfml_version% sfml
del sfml.zip

exit /b 0

@rem Install Boost
:install_boost
setlocal

pushd C:\Libraries\boost_%boost_version:.=_%

echo Bootstrap Boost
call bootstrap.bat mingw
if %errorlevel% neq 0 (
  echo Failed
  exit /b %errorlevel
  )

echo Success
echo Build and Install

b2 --with-system --with-filesystem --prefix=%proj_dir%\dependencies\boost variant=release toolset=gcc link=static install
if %errorlevel% neq 0 (
  echo Failed
  exit /b %errorlevel
  )

echo Success

popd

exit /b 0



:install_cpputest
setlocal

echo Extracting CppUTest
unzip -q cpputest.zip -d .
del cpputest.zip
echo Success

pushd cpputest-%cpputest_version%\cpputest_build
set PATH=%PATH:C:\Program Files\Git\usr\bin;=%
set PATH=%PATH:C:\Program Files (x86)\Git\usr\bin;=%

echo Building CppUTest
@rem generate
cmake -G "%CMAKE_GENERATOR%" -DCMAKE_INSTALL_PREFIX=%proj_dir%\dependencies\cpputest -DTESTS=OFF ..
if %errorlevel% neq 0 (
  echo Failed to Generate CMake files
  exit /b %errorlevel%
  )

@rem build & install
cmake --build . --target install
if %errorlevel% neq 0 (
  echo Failed to build/install CppUTest
  exit /b %errorlevel%
  )

echo Success

popd

rd /s /q cpputest-%cpputest_version%

exit /b 0

@rem Download everything
:download_all


setlocal
set sfml_url=http://www.sfml-dev.org/files/SFML-%sfml_version%-windows-gcc-4.9.2-mingw-%bits%-bit.zip
set cpputest_url=https://github.com/cpputest/cpputest/releases/download/v%cpputest_version%/cpputest-%cpputest_version%.zip


echo Downloading SFML from %sfml_url%
call :download_dep sfml.zip %sfml_url%
if %errorlevel% neq 0 exit /b %errorlevel%

echo Downloading CppUTest from %cpputest_url%
call :download_dep cpputest.zip %cpputest_url%
if %errorlevel% neq 0 exit /b %errorlevel%

exit /b 0

@rem Install everything
:install_all
setlocal
set proj_dir=%cd%

echo Installing SFML
call :install_sfml
if %errorlevel% neq 0 (
  echo Failed
  exit /b %errorlevel%
  )

echo Success

echo Installing Boost
echo %PATH%
call :install_boost
if %errorlevel% neq 0 (
  exit /b %errorlevel%
  )

echo Installing CppUTest
call :install_cpputest
if %errorlevel% neq 0 (
  exit /b %errorlevel%
  )

exit /b 0

:main
call :download_all || goto error
call :install_all || goto error

:success
endlocal
set SFML_ROOT=%cd%\dependencies\sfml
set BOOST_ROOT=%cd%\dependencies\boost
set CppUTest_PATH=%cd%\dependencies\cpputest
goto :EOF

:error
echo %self% failed with error #%errorlevel%
exit /b %errorlevel%
