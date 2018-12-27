@echo off
call javac MakeEven.java GenConvexHull.java GenCircle.java || exit

set test=0
setlocal enabledelayedexpansion

for %%a in (*.t) do (
    call :nextTest "type %%a"
)
call :nextTest "call java GenCircle 5 123"
call :nextTest "call java GenCircle 10 123"
call :nextTest "call java GenCircle 10 1123"
call :nextTest "call java GenCircle 6 123"
call :nextTest "call java GenConvexHull 500000 1000000000"
call :nextTest "call java GenConvexHull 800000 1000000000"
call :nextTest "call java GenCircle 500000 1000000000 1"
call :nextTest "call java GenCircle 600000 1000000000 2"
call :nextTest "call java GenCircle 800000 1000000000"
call :nextTest "call java GenCircle 1300000 1000000000 1"
call :nextTest "call java GenCircle 1200000 1000000000"
call :nextTest "call java GenCircle 1500000 1000000000"
call :nextTest "call java GenCircle 6000000 500000000 | call java MakeEven"

call :nextTest "call java GenCircle 11 1233 1"
call :nextTest "call java GenCircle 12 1123 2"
call :nextTest "call java GenConvexHull 6 123 2"
call :nextTest "call java GenConvexHull 11 123 | call java MakeEven"
call :nextTest "call java GenConvexHull 12 1123"

for /l %%i in (0,1,19) do (
    set /a z=%%i*50+123
    call :nextTest "call java GenCircle !z! 1000000 %%i"
)

exit /b

:nextTest 
    set /a test = test + 1
    set /a test1 = test / 10
    set /a test2 = test %% 10
    echo Writing test %test%
    %~1 > %test1%%test2%
exit /b
