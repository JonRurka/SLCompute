@echo off
set GLSLC=glslc.exe
if defined VULKAN_SDK set GLSLC=%VULKAN_SDK%\Bin\glslc.exe
cd /d "%~dp0"
"%GLSLC%" utilities.comp -o bin\utilities.spv
"%GLSLC%" complex.comp -o bin\complex.spv
pause
