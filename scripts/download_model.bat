@echo off
title Model Puller

echo.

REM Create models folder if it doesn't exist
if not exist "models" mkdir "models"

REM Check for the correct file name
if not exist "models\model.safetensors" (

    REM Bright Yellow
    echo [93mFetching GPT-2 SafeTensor from Hugging Face repository[0m
    echo.

    curl -L -X GET "https://huggingface.co/openai-community/gpt2/resolve/main/model.safetensors" -o "models\model.safetensors"

) else (

    echo.

    REM Bright Green
    echo [92mmodel.safetensors already there in models directory.[0m
)

echo.

REM Bright Cyan
echo [96mDone![0m

echo.
pause