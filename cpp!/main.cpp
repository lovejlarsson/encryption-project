#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "helper.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Användning: " << argv[0] << " <nyckel> <inputfil> <outputfil>\n";
        return 1;
    }

    std::string key = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Kunde inte öppna inputfilen.\n";
        return 1;
    }

    std::ostringstream buffer;
    std::string word;
    int index = 0;

    while (std::getline(inFile, word)) {
        if (word.empty()) {
            std::cout << "Tom rad, hoppar över.\n";
            continue;
        }

        auto startTid = std::chrono::high_resolution_clock::now();

        for (int j = 0; j < 1000; ++j) {
            std::string encrypted = xorEncryptDecrypt(word, key);
            std::string decrypted = xorEncryptDecrypt(encrypted, key);
        }

        auto slutTid = std::chrono::high_resolution_clock::now();
        auto tid = std::chrono::duration<double, std::nano>(slutTid - startTid).count();
        auto genomTid = tid / 1000.0;  // mikrosekunder

        buffer << index << "," << std::fixed << std::setprecision(3) << genomTid << "\n";
        ++index;
    }

    // Skriv hela bufferten till fil i ett svep
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Kunde inte öppna outputfilen.\n";
        return 1;
    }

    outFile << buffer.str();
    outFile.close();

    std::cout << "Kryptering/avkryptering klar. Resultat sparat i: " << outputFile << "\n";
    return 0;
}


/**
 * För att kompilera: 
 * g++ main.cpp helper.cpp -o xorcrypt.exe
 * 
 * För att köra: 
 * .\xorcrypt.exe kodord input.txt output.csv
 * 
 * 
 * kört alla med kodordet kodord 
 */