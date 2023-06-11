@REM realiza o teste em todas as linguagens
cls
javac java/Main.java
g++ c++/main.cpp -o c++/main -lssl -lcrypto
cd python
python build.py build
cd ..
python python/main.py
cd java
java Main
cd ..
cd c++
main.exe