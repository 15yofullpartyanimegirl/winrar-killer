#include "huffman.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 4) {
        cout << "invalid input" << endl;
        return 0;
    }

    string input_filename = argv[1];
    string output_filename = argv[2];
    string hash_filename = argv[3];
    string text;
    string zipped_text;
    
    try {
        text = get_text(input_filename);
        unordered_map<char, string> huffmanCode;
        Node* root = buildHuffmanTree(text, huffmanCode);

        zipped_text = zip(text, huffmanCode);
        write_text(output_filename, zipped_text);

        store_hash(hash_filename, huffmanCode);
    } catch (...) {
        cout << "empty input file" << endl;
    }
    
	return 0;
}