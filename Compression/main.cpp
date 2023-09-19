#include "huffman.h"

int main(){
    std::cout << "\n[ Demonstration for various compression methods implemented in C++ ]\n";
    std::string text;
    std::cout << "\nEnter string to compress: ";
    std::cin >> std::ws;
    std::getline(std::cin, text);

    huffmanEncodingDemonstration(text);
    
    return 0;
}