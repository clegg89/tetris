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
curl -sSL -o%output_file% %url% || exit /b %errorlevel%
exit /b 0

@rem Install SFML
:install_sfml
setlocal

unzip -q sfml.zip -d %cd%\dependencies\ || exit /b %errorlevel%
ren %cd%\dependencies\SFML-%sfml_version% sfml
del sfml.zip

exit /b 0

@rem Install Boost
:install_boost
setlocal

pushd C:\Libraries\boot_%boost_version:.=_%

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

@rem Install CppUTest
:install_cpputest
setlocal

echo Extracting CppUTest
unzip -q cpputest.zip -d . || exit /b %errorlevel%
del cpputest.zip
echo Success

pushd cpputest-%cpputest_version%\cpputest_build
SET PATH=%PATH:C:\Program Files\Git\usr\bin;=%
SET PATH=%PATH:C:\Program Files (x86)\Git\usr\bin;=%

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

echo Downloading SFML
call :download_dep sfml.zip http://www.sfml-dev.org/files/SFML-%sfml_version%-windows-gcc-4.9.2-mingw-%bits%-bit.zip || exit /b %errorlevel%
echo Success

echo Downloading CppUTest
call :download_dep cpputest.zip https://github.com/cpputest/cpputest/releases/download/v%cpputest_version%/cpputest-%cpputest_version%.zip || exit /b %errorlevel%
echo Success

exit /b 0

@rem Install everything
:install_all
setlocal
set proj_dir=%cd%

echo Installing SFML
call :install_sfml || exit /b %errorlevel%
echo Success
echo Installing Boost
call :install_boost || exit /b %errorlevel%
echo Installing CppUTest
call :install_cpputest || exit /b %errorlevel%

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
