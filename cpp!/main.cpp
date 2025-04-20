#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
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

    //felutskrifter 
    if (!inFile) {
        std::cerr << "Kunde inte öppna inputfilen.\n";
        return 1;
    }

    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Kunde inte öppna outputfilen.\n";
        return 1;
    }

    std::string word;
    int index = 0;

    while (std::getline(inFile, word)) {

        //sker om man skickar in en input med en tom rad 
        if (word.empty()) {
            std::cout << "Tom rad, hoppar över.\n";
            continue;
        }
        //tiden sätts igång, kryptering, dekryptering och tiden stopas
        auto startTid = std::chrono::high_resolution_clock::now();
        std::string encrypted = xorEncryptDecrypt(word, key);
        std::string decrypted = xorEncryptDecrypt(encrypted, key);
        auto slutTid = std::chrono::high_resolution_clock::now();

        auto tid = std::chrono::duration<double, std::micro>(slutTid - startTid).count();

        /**std::cout << "Rad " << index << ":\n";
        std::cout << "  Original:    " << word << "\n";
        std::cout << "  Krypterat (hex): ";
        for (unsigned char c : encrypted) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
        }
        std::cout << std::dec << "\n";
        std::cout << "  Dekrypterat: " << decrypted << "\n\n";*/
        //skriver ner till fil 
        outFile << index << "," << std::fixed << std::setprecision(6) << tid << "\n";

        ++index;
    }

    outFile.close(),
    //skriver ut att det är klart 
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