# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

set(MINGW_SYSROOT /usr/x86_64-w64-mingw32/sys-root)

# Change default install location
set(CMAKE_INSTALL_PREFIX ${MINGW_SYSROOT}/mingw)

# Set sys-root
set(CMAKE_SYSROOT ${MINGW_SYSROOT})

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment

# Root path to look for externals
set(CMAKE_FIND_ROOT_PATH ${MINGW_SYSROOT}/mingw)

# Do not look for any programs in FIND_ROOT_PATH (only use system path)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Only use includes and libraries found in FIND_ROOT_PATH
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
