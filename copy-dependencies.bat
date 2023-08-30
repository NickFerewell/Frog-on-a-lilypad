@echo off
chcp 1251
:parse
SET _libPath=""
IF "%~1"=="" (
	IF "%CD%\" =="%~dp0" GOTO getPromt ELSE GOTO giveExplanation
) ELSE (
	IF EXIST "%~1" (
		SET _libPath="%~1"
		GOTO copyRelease
	)
)
IF "%~1"=="-RELEASE" (
	IF EXIST "%~2" (
		SET _libPath="%~2"
		GOTO copyRelease
	) ELSE (
		echo ����� �� �������
		GOTO giveExplanation
	)
)
IF "%~1"=="-DEBUG" (
	IF EXIST "%~2" (
		SET _libPath="%~2"
		GOTO copyDebug
	) ELSE (
		echo ����� �� �������
		GOTO giveExplanation
	)
)
:endParse
GOTO end

:getPromt
SET /P _mode=��� �����? -RELEASE ��� -DEBUG: || SET _mode=-RELEASE
SET /P _libPath=������ ���� � ����� ����������(� �������): || GOTO giveExplanation
:: remove &'s and quotes from the answer (via string replace)
SET _mode=%_mode:&=%
SET _mode=%_mode:"=%
IF %_mode%==-RELEASE GOTO copyRelease
IF %_mode%==-DEBUG GOTO copyDebug
::�� ������, ���� _mode �� ������
GOTO giveExplanation


:copyRelease
cd %_libPath%\bin
for %%I in (sfml-graphics-2.dll sfml-system-2.dll sfml-window-2.dll) do copy %%I "%~dp0x64\Release"
GOTO end

:copyDebug
cd %_libPath%\bin
copy sfml-*-d-2.dll "%~dp0x64\Debug"
GOTO end

:copyAll
cd %_libPath%\bin
copy sfml-*.dll "%~dp0x64\Debug"
GOTO end

:giveExplanation
echo ���� ������� �����: -DEBUG ��� -RELEASE, � ����� ������� ���������� � �����������.
echo ��������, � ��������� ������: "copy-dependencies.bat -RELEASE "C:\libs\SFML""

:end
cd "%~dp0"
pause