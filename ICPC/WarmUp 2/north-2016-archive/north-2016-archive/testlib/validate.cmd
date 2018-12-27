@echo off
if exist "%~dp0validate4j.build" rmdir /s /q "%~dp0validate4j.build"
mkdir "%~dp0validate4j.build"
call javac -d "%~dp0validate4j.build" %~dp0validate4j/ru/ifmo/validate/*.java
jar -cf validate4j.jar -C "%~dp0validate4j.build" .
rmdir /s /q "%~dp0validate4j.build"
