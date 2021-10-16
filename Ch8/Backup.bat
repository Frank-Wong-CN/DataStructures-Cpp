@echo off
setlocal enabledelayedexpansion
call set7z

set dt=
for /f %%a in ('wmic os get LocalDateTime ^| findstr ^[0-9]') do ( set dt=%%a )
set date=!dt:~0,8!
set time=!dt:~8,6!

set filename=Backup-%date%%time%

if not "%1" == "" (
	set filename=!filename!-%1
)

set allfiles=

for /f "tokens=* usebackq" %%a in (`dir /b`) do (
	if not "%%a" == "Backup" (
		if not "%%a" == "Build" (
			echo %%a
			set allfiles="%~dp0%%a" !allfiles!
		)
	)
)

7z a "%~dp0Backup\!filename!.7z" !allfiles!
echo Backup complete.
