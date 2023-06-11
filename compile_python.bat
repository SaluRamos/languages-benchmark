cls
cd python
pyinstaller --hidden-import FileDialog main.py
cd dist
cd main
main.exe
cd ..
cd ..
del main.spec