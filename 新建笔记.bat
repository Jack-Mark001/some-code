@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

:: ===== 配置区域（按需修改） =====
:: 笔记存放路径（修改成你想要的文件夹）
set NOTEBOOK_DIR=.\知识库\0_感
:: Typora 安装路径（根据你的实际路径修改）
set TYPORA_PATH="D:\software\soft\Typora\Typora.exe"
:: ===== 配置结束 =====

:: 生成时间戳文件名 YYYY-MM-DD.md
for /f "tokens=1-3 delims=/ " %%a in ('date /t') do (
    set year=%%a
    set month=%%b
    set day=%%c
)
:: 如果 date /t 格式是 MM/DD/YYYY，用下面这种
for /f "tokens=1-3 delims=/- " %%a in ('echo %date%') do (
    set year=%%c
    set month=%%a
    set day=%%b
)

:: 如果上面的不行，用这个万能的（基于 PowerShell）
for /f %%i in ('powershell -Command "Get-Date -Format 'yyyy-MM-dd'"') do set FILENAME=%%i

:: 确保文件夹存在
if not exist "%NOTEBOOK_DIR%" mkdir "%NOTEBOOK_DIR%"

:: 完整文件路径
set FILE_PATH=%NOTEBOOK_DIR%\%FILENAME%.md

:: 如果文件不存在则创建模板，存在则直接打开
if not exist "%FILE_PATH%" (
    echo # %FILENAME% > "%FILE_PATH%"
    echo. >> "%FILE_PATH%"
    echo ## 做了什么 >> "%FILE_PATH%"
    echo. >> "%FILE_PATH%"
    echo -  >> "%FILE_PATH%"
    echo. >> "%FILE_PATH%"
    echo ## 遇到的问题 >> "%FILE_PATH%"
    echo. >> "%FILE_PATH%"
    echo -  >> "%FILE_PATH%"
    echo. >> "%FILE_PATH%"
    echo ## 要做的事 >> "%FILE_PATH%"
    echo. >> "%FILE_PATH%"
    echo - [ ]  >> "%FILE_PATH%"
)

:: 用 Typora 打开
start "" %TYPORA_PATH% "%FILE_PATH%"
