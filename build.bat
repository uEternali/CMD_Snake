@echo off
set /p =^>^>^> <nul
call:colorecho "Make sure that the MinGw and the Cmake have been installed" 06 1
echo Press ANY KEY to start
pause >nul
call:colorecho "Check the version of MinGW" 06 1
mingw32-g++ --version
if not %errorlevel% == 0 (
    set /p =^>^>^> <nul
    call:colorecho "mingw32-g++ hasn't been installed or not in PATH" 04 1
    exit
)
cmake --version
if not %errorlevel% == 0 (
    set /p =^>^>^> <nul
    call:colorecho "Cmake hasn't been installed or not in PATH" 04 1
    exit
)
set /p =^>^>^> <nul
call:colorecho "Snake is going to be built······" 02 1
mkdir build
cd build
cmake -S .. -B . -G "MinGW Makefiles"
mingw32-make
copy Snake.exe .. > nul
cd..
rmdir /s /q build
set /p =^>^>^> <nul
call:colorecho "Snake has been built successfully" 02 1
echo Press ANY KEY to exit
pause >nul
goto END
:: ---------------------------------------------------------------------
:colorecho
rem text color endl?
set /p=" " <nul >%1
findstr /a:%2 . %1*
if %3 == 1 (echo.)
del /q %1
goto:eof

:END