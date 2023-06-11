@REM faz build do salubenchmark, compila o software e protege com obfuscação
cls
cd python
python build.py build
pyinstaller --hidden-import FileDialog main.py
pyarmor gen --pack dist/main/main.exe main.py
cd dist
cd main
main.exe