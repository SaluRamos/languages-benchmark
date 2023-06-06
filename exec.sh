clear
rm -r build
rm -r dist
pyinstaller main.py
cp data.txt dist/main/data.txt
./dist/main/main
javac Main.java
java Main
g++ main.cpp -o main
./main