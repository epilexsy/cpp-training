#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

class FreqKeyValuePair {
public:
    char letter;
    int frequency;

    FreqKeyValuePair(char letter_, int freq) : letter(letter_), frequency(freq) {}
};

class TreeNode {
public:
    char letter;
    int value;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;

    TreeNode(char c=0, int val=0) : letter(c), value(val), left(nullptr), right(nullptr) {}
};

class HuffmanEncoder {
public:
    std::unique_ptr<TreeNode> root;
    std::vector<std::unique_ptr<FreqKeyValuePair>> frequencyArray;
    std::vector<std::unique_ptr<TreeNode>> nodeBuffer;
    std::map<char, std::vector<bool>> encodingTable;

    HuffmanEncoder() : root(nullptr) {}

    void sortFrequencyArray(const int ascending = 0){
        if(!ascending) {
            std::sort(frequencyArray.begin(), frequencyArray.end(), [](const auto& a, const auto& b){
                return a->frequency > b->frequency;
            });
        }
        else {
            std::sort(frequencyArray.begin(), frequencyArray.end(), [](const auto& a, const auto& b){
                return a->frequency < b->frequency;
            });
        }
    }

    void sortNodeBuffer(const int ascending = 0){
        if(!ascending) {
            std::sort(nodeBuffer.begin(), nodeBuffer.end(), [](const auto& a, const auto& b){
                return a->value > b->value;
            });
        }
        else {
            std::sort(nodeBuffer.begin(), nodeBuffer.end(), [](const auto& a, const auto& b){
                return a->value < b->value;
            });
        }

    }

    void updateFrequencyArray(std::string text){
        int char_found = 0;
        for (char c : text) {
            char_found = 0;
            for (const auto& freq : frequencyArray) {
                if (freq->letter == c){
                    freq->frequency += 1;
                    char_found = 1;
                    break;
                }
            }
            if(!char_found){
                frequencyArray.push_back(std::make_unique<FreqKeyValuePair>(c, 1));
            }
        }
        sortFrequencyArray();
    }


    void fillNodeBuffer(){
        for (const auto& freq : frequencyArray){
            nodeBuffer.push_back(std::make_unique<TreeNode>(freq->letter, freq->frequency));
        }
    }

    void createTree(std::string text){
        updateFrequencyArray(text);
        fillNodeBuffer();
        while(nodeBuffer.size() > 1){
            std::unique_ptr<TreeNode> newNode = std::make_unique<TreeNode>();

            newNode->right = std::move(nodeBuffer.back());
            nodeBuffer.pop_back();
            
            newNode->left = std::move(nodeBuffer.back());
            nodeBuffer.pop_back();
            
            newNode->value = newNode->left->value + newNode->right->value;
            nodeBuffer.push_back(std::move(newNode));

            sortNodeBuffer();
        }
        root = std::move(nodeBuffer.back());
        nodeBuffer.pop_back();

        encodingTable = buildEncodingTable(root);
    }

    std::map<char, std::vector<bool>> buildEncodingTable(std::unique_ptr<TreeNode>& current, std::vector<bool> encodedLetter = std::vector<bool>()){
        std::map<char, std::vector<bool>> encodingTable_;
        
        if (current->letter) {
            encodingTable_[current->letter] = encodedLetter;
        }
        else {
            std::vector<bool> leftEncoded = encodedLetter;
            leftEncoded.push_back(false);            
            
            for (const auto& pair : buildEncodingTable(current->left, leftEncoded)){
                encodingTable_.insert(pair);
            }
        
            std::vector<bool> rightEncoded = encodedLetter;
            rightEncoded.push_back(true);
            for (const auto& pair : buildEncodingTable(current->right, rightEncoded)) {
                encodingTable_.insert(pair);
            }
        }
        return encodingTable_;
    }

    void reset(){
        root.reset();
        frequencyArray.clear();
    }

    std::vector<bool> encode(std::string text){
        createTree(text);
        std::vector<bool> encodedBytes;
        for (char c : text) {
            encodedBytes.insert(encodedBytes.end(), encodingTable[c].begin(), encodingTable[c].end());
        }
        displayEncodingTable();
        reset();
        return encodedBytes;
    }

    void displayFrequencyArray(const char c = 0){
        if (!frequencyArray.size()){
            std::cout << "Empty" << "\n";
        }
        if (c){
            for (const auto& freq : frequencyArray) {
                if (freq->letter == c){
                    std::cout << "'" << c << "': " << freq->frequency << "\n";
                    return;
                }
            }
            std::cout << "Character '" << c <<"' not found in frequency array." << "\n";
        }
        else {
            int i = 1;
            std::cout << "{";
            for (const auto& freq : frequencyArray) {
                std::cout << "'" << freq->letter << "': " << freq->frequency << ((++i > frequencyArray.size()) ? "": ", ");
            }
            std::cout << "}\n";
        }
    }
    
    void displayEncodingTable(){
        for (auto pair : encodingTable) {
            std::cout << pair.first << ": ";
            for (bool value : pair.second) {
                std::cout << (value) ? "1" : "0";
            }
            std::cout << "\n";
        }
    }
    
};

void huffmanEncodingDemonstration(std::string text){
    std::vector<bool> encodedBytes;
    std::unique_ptr<HuffmanEncoder> huffmanEncoder = std::make_unique<HuffmanEncoder>();

    std::cout << "\nHuffman Encoding\n";
    std::cout << "---------------------------\n";
    encodedBytes = huffmanEncoder->encode(text);

    std::cout << "Bits in input string: " << text.length() * 8 << "\n";
    std::cout << "Bits in encoded string: " << encodedBytes.size() << "\n";
    std::cout << "Compression rate: " << 100*(((double)encodedBytes.size() / (text.length()*8))) << "%\n";

    std::cout << std::endl;
}
