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
ctest -V . || goto error

:success
endlocal
echo Tests successful
goto :EOF

:error
echo %self% failed with error #%errorlevel%
exit /b %errorlevel%
