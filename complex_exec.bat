cls
del /s /q /f "build" & rmdir /s /q "build"
del /s /q /f "dist" & rmdir /s /q "dist"
@REM pyinstaller.exe main.py
@REM python setup_cxfreeze.py build
copy data.txt "dist/main/data.txt"
cls
dist\main\main.exe
javac Main.java
java Main
g++ main.cpp -o main
main
del main
del Main.class
del main.spec