cls
cd python
python build.py build
pyinstaller --hidden-import FileDialog main.py
cd dist
cd main
main.exe
cd ..
cd ..
del main.spec