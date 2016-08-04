rmdir /S /Q CMakeFiles
del CMakeCache.txt
del cmake_install.cmake
del Makefile

rmdir /S /Q Core\CMakeFiles
del Core\cmake_install.cmake
del Core\Makefile

rmdir /S /Q Client\CMakeFiles
del Client\cmake_install.cmake
del Client\Makefile

rmdir /S /Q Server\CMakeFiles
del Server\cmake_install.cmake
del Server\Makefile
