@echo off
:: Batch script to build and execute the project, including optional Python visualization

:: Initialize variables
set PYTHON=python
set VISUALIZE=1

:: Check if Python is available
where %PYTHON% >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    set PYTHON=python3
    where %PYTHON% >nul 2>&1
    if %ERRORLEVEL% NEQ 0 (
        echo Python environment could not be found for visualization
        set VISUALIZE=0
    )
)

:: Navigate to the parent directory's 'code' folder
set DIR=%~dp0
cd /d "%DIR%\..\code"

:: Run CMake to configure and build the project
cmake CMakeLists.txt
cmake --build . --config Release

:: Execute the project with parameters
.\elastic_deformation.exe 100 100000

:: If visualization is enabled, install Python dependencies and run the visualizer
if %VISUALIZE%==1 (
    %PYTHON% -m pip install -r requirements.txt
    %PYTHON% visualizer.py true
)
