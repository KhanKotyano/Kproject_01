@echo off
g++ main.cpp -o %~dp0build/main.exe -O1 -Wall -std=c++14 -Wno-missing-braces -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
cmd /c if exist %~dp0build/main.exe %~dp0build/main.exe