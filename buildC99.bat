@echo off
if exist %~dp0\\build\\*.exe del %~dp0\\build\\*.exe
gcc main.cpp -o %~dp0build\\main.exe -O2 -Wall -std=c99 -Wno-missing-braces -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
cmd /c if exist %~dp0build\\main.exe %~dp0build\\main.exe