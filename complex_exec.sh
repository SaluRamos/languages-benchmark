clear
rm -r build
rm -r dist
pyinstaller main.py
cp data.txt dist/main/data.txt
# python3 setup_cxfreeze.py build
clear
./dist/main/main
javac Main.java
java Main
g++ main.cpp -o main
./main
rm main
rm Main.class
rm main.spec