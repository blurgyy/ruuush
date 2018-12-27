@echo off
    call :suite %1
exit /b

:directory
    if exist "%1p.suite" (
        call :suite %1 || exit /b 1
    ) else if exist "%1p.test" (
        call :test %1 || exit /b 1
    ) else (
        echo TEST %1 FAILED: No '%1p.test' or '%1p.suite' found
        exit /b 1
    )
exit /b 0

:test
    pushd %1
    echo Running test "%1"
    set command=
    set result=
    for /f "tokens=1,2* delims==" %%a in (p.test) do set "%%a=%%b"
    call %~dp0p %command%
    set out=
    if exist t.out for /f "tokens=1* delims=~" %%a in (t.out) do set "out=%%a"
    if not ["%out%"] == ["%result%"] (
        echo.TEST %1 FAILED
        echo.Expected: %result%
        echo.Found:    %out%
        exit /b 1
    )
    echo TEST "%1" OK
    popd
exit /b 0

:suite
    echo Running suite "%1"
    echo %CD%
    for /d %%a in ("%1*") do (call :directory %%a\ || exit /b 1)
    echo SUITE "%1" OK
exit /b 0
