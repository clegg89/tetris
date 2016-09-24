MKDIR build
CD build
SET OLD_PATH=%PATH%
SET PATH=%PATH:C:\Program Files\Git\usr\bin;=%
SET PATH=%PATH:C:\Program Files (x86)\Git\usr\bin;=%
cmake -G "%GENERATOR%" ..
SET PATH=%OLD_PATH%
cmake --build .
cpack -G "ZIP" .
