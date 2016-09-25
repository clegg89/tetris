@rem FILE: install-common.bat
@rem AUTHOR: C. Smith
@rem DESC: Common setup for install scripts
@echo off
setlocal

set self=%~nx0

@rem Skip function prototypes
goto main

@rem FUNCTIONS

:main

:success
endlocal
if "%PLATFORM%" == "x86" (set bits=32) else (set bits=64)
goto :EOF

:error
echo %self% failed with error #%errorlevel%
exit /b %errorlevel%
