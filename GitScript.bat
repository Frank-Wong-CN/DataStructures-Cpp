@echo off
setlocal enabledelayedexpansion
title Git Operation
set Op=%1
set Arg=%2
:: Up - git commit -a -m %Arg% & git push
:: Down - git pull & git checkout main
:: Log - git log --oneline
:: Cred - git config --global --unset credential.helper & git config --global credential.helper store

::echo Op: !Op!
::echo Arg: !Arg!

2>nul call :Option_!Op!
if errorlevel 1 call :Option_Default

exit /b

:Option_Up
if "!Arg!" == "" (
	echo Usage: GitScript Up ^<Commit Messages^>
	exit /b
)

echo Will execute: git commit -a -m !Arg!, git push
echo Press any key to continue, or press Ctrl-C to quit.
pause>nul

echo.
echo Commiting...
git commit -a -m !Arg!
echo.
echo Pushing...
git push

goto End

:Option_Down
echo Will execute: git pull, git checkout main
echo Press any key to continue, or press Ctrl-C to quit.
pause>nul

echo.
echo Pulling...
git pull
echo.
echo Checking out...
git checkout main

goto End

:Option_Log
git log --oneline
exit /b

:Option_Cred
echo Will execute: git config --global --unset credential.helper, git --global config credential.helper store
echo Press any key to continue, or press Ctrl-C to quit.
pause>nul

git config --global --unset credential.helper
git config --global credential.helper store

goto End

:Option_Default
echo Usage: GitScript ^<Option^> [Optional Argument]
echo Available options:
echo 	Up	Commit and push to remote, require optional argument: commit message
echo 	Down	Pull and checkout main branch
echo 	Log	Check git one-line log
echo 	Cred	Remove and update credential in next operation
exit /b

:End
echo.
echo Command completed.
