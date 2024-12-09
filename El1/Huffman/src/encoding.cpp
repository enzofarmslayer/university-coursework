/*
 * Developers: kevma271, enzcu445
 */

#include "encoding.h"
#include "bitstream.h"
#include <queue>


/**
 * @brief buildFrequencyTable reads all characters
 * from the given file and
 * maps them to a number indicating frequency.
 *
 * @param input - the file to read from
 * @return freqTable - every letter mapped to frequency
 */
map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;

    int charFromFile;
    bool fileNotEmpty = true;

    while (fileNotEmpty) {
        charFromFile = input.get();

        // Check if we've read entire file
        if (input.fail()) {
            freqTable[PSEUDO_EOF] = 1;
            fileNotEmpty = false;
        }

        // If char hasn't been read before
        else if (freqTable.count(charFromFile) == 0) {
            freqTable[charFromFile] = 1;
        }

        // Otherwise the char has been read before
        else {
            freqTable[charFromFile] += 1;
        }
    }

    return freqTable;
}


/**
 * @brief buildEncodingTree takes all letters and
 * their respective frequency and makes a huffman
 * tree of them.
 *
 * @param freqTable frequency table
 * @return pointer to root
 */
HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    priority_queue<HuffmanNode*> encodingTree;

    // Initalize relevant variables to avoid abundancy
    HuffmanNode* newNode;
    HuffmanNode* leftChild;
    HuffmanNode* rightChild;
    HuffmanNode* combinedNode;

    int newCount;

    // Create nodes for all chars
    for (auto it = freqTable.begin(); it != freqTable.end(); ++it) {
        newNode = new HuffmanNode(it->first, it->second, nullptr, nullptr);
        encodingTree.push(newNode);
    }

    // Combine two lowest nodes and create a tree
    while (encodingTree.size() > 1) {
        leftChild = encodingTree.top();
        encodingTree.pop();

        rightChild = encodingTree.top();
        encodingTree.pop();

        newCount = leftChild->count+rightChild->count;

        combinedNode = new HuffmanNode(NOT_A_CHAR, newCount, leftChild, rightChild);
        encodingTree.push(combinedNode);
    }
    //cout << encodingTree.top();

    return encodingTree.top();
}


/**
 * @brief buildEncodingMap
 * @param encodingTree
 * @return
 */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;



    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
