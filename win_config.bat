@echo off

set masterfolder=%cd%

mkdir build
cd build
call cmake -G "Visual Studio 17 2022" -T host=x86 -A Win32 ..

cd %masterfolder%
