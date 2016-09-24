@rem FILE: install-toolchain.bat
@rem AUTHOR: C. Smith
@rem DESC: Install the toolchain for appveyor builds
@echo off
setlocal

@rem Don't run if already installed
if exist %toolchain_path%\%toolchain% goto success

set self=%~nx0

@rem Skip function prototypes
goto main

@rem FUNCTIONS



:setup_env

if "%PLATFORM%" == "x86" (
  set mingw_url=https://sourceforge.net/projects/mingw-w64/files/Toolchains%%20targetting%%20Win32/Personal%%20Builds/mingw-builds/4.9.2/threads-posix/dwarf/i686-4.9.2-release-posix-dwarf-rt_v4-rev2.7z/download
  ) else (
  set mingw_url=https://sourceforge.net/projects/mingw-w64/files/Toolchains%%20targetting%%20Win64/Personal%%20Builds/mingw-builds/4.9.2/threads-posix/seh/x86_64-4.9.2-release-posix-seh-rt_v4-rev2.7z/download
  )

exit /b 0


:download_mingw

echo Downloading MinGW
curl -sSL -o%toolchain%.7z %mingw_url%
if not exist %toolchain%.7z (
  echo Failed
  exit /b 1
  )

echo Success

exit /b 0


:install_mingw

echo Extracting MinGW
7z x -o%toolchain_path% %toolchain%.7z
if not exist %toolchain_path%\%toolchain%%bits% (
  echo Failed
  exit /b 1
  )

ren %toolchain_path%\%toolchain%%bits% %toolchain%
del %toolchain%.7z
echo Success

exit /b 0

:main
call :setup_env || goto error
call :download_mingw || goto error
call :install_mingw || goto error

:success
endlocal
set PATH=%toolchain_path%\%toolchain%;%PATH%
rd /s /q C:\MinGW
goto :EOF


:error
echo %self% failed with error #%errorlevel%
exit /b %errorlevel%

