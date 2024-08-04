#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <sstream> 
#include <fstream>

using namespace std;

struct Node;

Node* getNode(char ch, int freq, Node* left, Node* right);

struct comp;

void encode(Node* root, string str, unordered_map<char, string> &huffmanCode);

Node* buildHuffmanTree(string text, unordered_map<char, string>& huffmanCode);

string zip(string text, unordered_map<char, string>& huffmanCode);

void write_text(string filename, string& text);

string get_text(string filename);

string decode(unordered_map<string, char>& huffmanCode, string& text);

void store_hash(string filename, unordered_map<char, string>& huffmanCode);

void load_hash(string filename, unordered_map<string, char>& huffmanCode);