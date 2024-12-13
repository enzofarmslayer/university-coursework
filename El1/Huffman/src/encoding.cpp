/*
 * Code for reading a text file and coverting it to huffman. Can be used later to write the
 * same huffman file and convert it back to a normal text file.
 *
 * Developers: kevma271, enzcu445
 */

#include "encoding.h"
#include "bitstream.h"
#include <queue>
#include <stack>


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
HuffmanNode* buildEncodingTree(const std::map<int, int>& freqTable) {
    priority_queue<HuffmanNode> encodingTree;

    // Dynamically create nodes for all characters
    for (auto it = freqTable.begin(); it != freqTable.end(); ++it) {
        encodingTree.push(HuffmanNode(it->first, it->second, nullptr, nullptr));
    }

    // Combine two lowest nodes and create the tree
    while (encodingTree.size() > 1) {
        HuffmanNode leftChild = encodingTree.top();
        encodingTree.pop();

        HuffmanNode rightChild = encodingTree.top();
        encodingTree.pop();

        encodingTree.push(HuffmanNode(NOT_A_CHAR,
            leftChild.count + rightChild.count,
            new HuffmanNode(leftChild),
            new HuffmanNode(rightChild)
            ));
    }

    // Get the final top node (root of the tree)
    HuffmanNode* root = new HuffmanNode(encodingTree.top());
    return root;
}


/**
 * @brief buildEncodingMap map each character with a "01" sequence string
 * @param encodingTree
 * @return the map
 */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;

    if (encodingTree == nullptr) {
        return encodingMap;
    }

    stack<pair<HuffmanNode*, string>> nodeStack;

    nodeStack.push({encodingTree, ""});

    while (!nodeStack.empty()) {
        pair<HuffmanNode*, string> current = nodeStack.top();
        nodeStack.pop();
        HuffmanNode* node = current.first;
        string code = current.second;

        if (node->character != NOT_A_CHAR) {
            encodingMap[node->character] = code;
        }

        if (node->zero != nullptr) {
            nodeStack.push({node->zero, code + "0"});
        }

        if (node->one != nullptr) {
            nodeStack.push({node->one, code + "1"});
        }
    }

    return encodingMap;
}


/**
 * @brief encodeData makes characters into binary representations
 *        that are not ASCI, but considers frequency instead
 * @param input
 * @param encodingMap
 * @param output
 */
void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    char character;

    // Read from file
    while (input.get(character)) {

        string encodedBits = encodingMap.at(character);

        for (char bit : encodedBits) {
            if (bit == '1') {
                output.writeBit(1);
            } else {
                output.writeBit(0);
            }
        }
    }

    string EofBits = encodingMap.at(PSEUDO_EOF);
    for (char bit : EofBits) {
        if (bit == '1') {
            output.writeBit(1);
        } else {
            output.writeBit(0);
        }
    }
}


/**
 * @brief decodeData read the huffman converted file and decode it
 * @param input
 * @param encodingTree
 * @param output
 */
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
        HuffmanNode* current = encodingTree;

        //current->character == PSEUDO_EOF
        while (true) {
            int bit = input.readBit();

            if (bit == 0) {
                current = current->zero;
            }
            else if (bit == 1) {
                current = current->one;
            }

            if (current->zero == nullptr && current->one == nullptr) {
                if (current->character == PSEUDO_EOF) {
                    break;
                }

                output.put(current->character);
                current = encodingTree;
            }
        }
}


/**
 * @brief mapToString takes in a map and turns it
 *        into a string.
 * @param freqTable the map we will convert
 * @return the map in string format
 */
template <typename T>
string mapToString(const map<T, T>& freqTable) {
    string stringifiedMap;
    stringifiedMap.append("{");

    for (auto it = freqTable.begin(); it != freqTable.end(); ++it) {
        // Append each digit of the key (it->first) as a separate character
        for (char ch : to_string(it->first)) {
            stringifiedMap.append(1, ch);  // Append one character
        }

        stringifiedMap.append(":");

        // Append each digit of the value (it->second) as a separate character
        for (char ch : to_string(it->second)) {
            stringifiedMap.append(1, ch);  // Append one character
        }

        // Add a comma if it's not the last element
        if (next(it) != freqTable.end()) {
            stringifiedMap.append(",");
            stringifiedMap.append(" ");
        }
    }
    stringifiedMap.append("}");

    return stringifiedMap;
}


/**
 * @brief compress Reads a file and writes to another
 *        with a header and characters converted
 *        with huffman structure
 * @param input file to read from
 * @param output convertred file
 */
void compress(istream& input, obitstream& output) {
    const map<int, int> freqTable = buildFrequencyTable(input);

    // Serialize the frequency table
    string freqTableString = mapToString(freqTable);
    for (char c : freqTableString) {
        output.put(c);
    }

    HuffmanNode* root = buildEncodingTree(freqTable);

    map<int, string> encodingMap = buildEncodingMap(root);

    input.clear();
    input.seekg(0);

    encodeData(input, encodingMap, output);

    freeTree(root);
}



/**
 * @brief fromStringToMap convert the stringified header to a map again
 * @param input
 * @return
 */
map<int, int> fromStringToMap(const string& freqString) {
    map<int, int> freqTable;
    string currAsci;
    string currFreq;
    bool asci;

    for (auto it = freqString.begin(); it != freqString.end(); ++it) {
        if (*it == '{' || *it == ' ') {
            asci = true;
            continue;
        }

        if (*it == ',') {
            freqTable[stoi(currAsci)] = stoi(currFreq);
            currAsci.clear();
            currFreq.clear();
            continue;
        }

        if (*it == ':' || *it == '}') {
            asci = false;
            continue;
        }

        if (asci) {
            currAsci += *it;
        }
        else {
            currFreq += *it;
        }
    }
    freqTable[PSEUDO_EOF] = 1;
    return freqTable;
}


/**
 * @brief decompress calls relevant methods to decompress a huf file
 * @param input
 * @param output
 */
void decompress(ibitstream& input, ostream& output) {
    string freqString;
    string readByte;

    while (true) {
        readByte = input.get();
        if (readByte == "}") {  // Stop if the terminating character is reached
            freqString += readByte;
            break;
        }
        freqString += readByte;
    }

    const map<int, int> freqTable = fromStringToMap(freqString);

    HuffmanNode* root = buildEncodingTree(freqTable);

    decodeData(input, root, output);

    freeTree(root);
}


/**
 * @brief freeTree free all allocated memoery by the huffman tree
 * @param node
 */
void freeTree(HuffmanNode* node) {
    if (node == nullptr) {
        return;
    }

    freeTree(node->zero);


    freeTree(node->one);


    delete node;
}
