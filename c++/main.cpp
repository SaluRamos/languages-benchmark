

#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <chrono>
#include <string>
#include <openssl/md5.h>

using namespace std;
using namespace std::chrono;

std::string md5(const std::string& input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((const unsigned char*)input.c_str(), input.length(), digest);
    char md5String[33];
    for (int i = 0; i < 16; ++i)
        sprintf(&md5String[i * 2], "%02x", (unsigned int)digest[i]);
    return std::string(md5String);
}

int fib(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

void testGeometry(double vector3_1[3], double vector3_2[3], double radius1, double radius2, double radius3) {
    double distance = std::sqrt(std::pow(vector3_2[0] - vector3_1[0], 2) + std::pow(vector3_2[1] - vector3_1[1], 2) + std::pow(vector3_2[2] - vector3_1[2], 2));
    double distance_between_centers = std::sqrt(std::pow(vector3_2[0] - vector3_1[0], 2) + std::pow(vector3_2[1] - vector3_1[1], 2) + std::pow(vector3_2[2] - vector3_1[2], 2));
    double sphere_volume = (4.0 / 3.0) * 3.1415 * std::pow(radius3, 3);
}

std::string loadData() {
    std::ifstream file;
    file.open("../data.txt", std::fstream::in | std::fstream::binary);
    std::string data;

    if (file.is_open()) {
        while ( !file.eof() ) {
            file >> data;
        }
        file.close();
    }

    return data;
}

int main() {
    high_resolution_clock::time_point startFib = high_resolution_clock::now();
    int resultFib = fib(34);
    high_resolution_clock::time_point finishFib = high_resolution_clock::now();
    std::cout << "result fib = " << resultFib << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 10.0);
    double vector3_1[3] = { dis(gen), dis(gen), dis(gen) };
    double vector3_2[3] = { dis(gen), dis(gen), dis(gen) };
    double radius1 = dis(gen);
    double radius2 = dis(gen);
    double radius3 = dis(gen);
    high_resolution_clock::time_point startGeometry = high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++) {
        testGeometry(vector3_1, vector3_2, radius1, radius2, radius3);
    }
    high_resolution_clock::time_point finishGeometry = high_resolution_clock::now();

    high_resolution_clock::time_point startData = high_resolution_clock::now();
    std::string resultData = loadData();
    high_resolution_clock::time_point finishData = high_resolution_clock::now();
    std::cout << "data hash = " << md5(resultData) << std::endl;

    duration<double, milli> timeElapsedFib = finishFib - startFib;
    duration<double, milli> timeElapsedGeometry = finishGeometry - startGeometry;
    duration<double, milli> timeElapsedData = finishData - startData;
    std::cout << "C++:" << std::endl;
    std::cout << "teste fib: " << static_cast<long>(timeElapsedFib.count()) << " ms" << std::endl;
    std::cout << "teste geometry: " << static_cast<long>(timeElapsedGeometry.count()) << " ms" << std::endl;
    std::cout << "teste data: " << static_cast<long>(timeElapsedData.count()) << " ms" << std::endl;

    return 0;
}
