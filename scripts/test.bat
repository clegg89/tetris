@rem FILE: test.bat
@rem AUTHOR: C. Smith
@rem DESC: Run tests
@echo off
setlocal

set self=%~nx0

@rem Skip function prototypes
goto main

@rem FUNCTIONS

:main
echo Running tests
pushd %BUILD_DIR%
ctest -V . || goto error
popd

:success
endlocal
echo Tests successful
goto :EOF

:error
echo %self% failed with error #%errorlevel%
exit /b %errorlevel%
