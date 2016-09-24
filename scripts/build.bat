@rem FILE: build.bat
@rem AUTHOR: C. Smith
@rem DESC: Build the project
@echo off
setlocal

set self=%~nx0

@rem Skip function prototypes
goto main

@rem FUNCTIONS

:main
mkdir %BUILD_DIR%
pushd %BUILD_DIR%

set PATH=%PATH:C:\Program Files\Git\usr\bin;=%
set PATH=%PATH:C:\Program Files (x86)\Git\usr\bin;=%

echo Generate CMake files
cmake -G "%CMAKE_GENERATOR%" .. || goto error

echo Building Project
cmake --build . || goto error

echo Packaging Project
cpack -G "ZIP" . || goto error

:success
endlocal
echo Build successful
goto :EOF

:error
echo %self% failed with error #%errorlevel%
exit /b %errorlevel%
