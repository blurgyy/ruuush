@echo off
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (set bits=64) else (set bits=32)
%~dp0run%bits% %*
