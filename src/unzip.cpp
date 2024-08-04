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
    string zipped_text;
    string unzipped_text;

    try {
        zipped_text = get_text(input_filename);
        unordered_map<string, char> huffmanCode;

        load_hash(hash_filename, huffmanCode);
        unzipped_text = decode(huffmanCode, zipped_text);
        write_text(output_filename, unzipped_text);
    } catch (...) {
        cout << "empty input file" << endl;
    }

	return 0;
}