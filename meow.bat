@echo off
if "%1"=="ex" (
    cmake --build build --target bpast_example --parallel
) else (
    cmake --build build --parallel
)
