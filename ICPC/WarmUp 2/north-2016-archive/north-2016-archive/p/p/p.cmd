@echo off
if exist %~dp0setenv.cmd call %~dp0setenv.cmd
%~dp0..\python\python -b -B -E -s %~dp0p.py %*
