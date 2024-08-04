#include "huffman.h"

// A Tree node
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

// Function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};

// traverse the Huffman Tree and store Huffman Codes
// in a map.
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// Builds Huffman Tree and decode given input text
Node* buildHuffmanTree(string text, unordered_map<char, string>& huffmanCode)
{
	// count frequency of appearance of each character
	// and store it in a map
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of
	// Huffman tree;
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root stores pointer to root of Huffman Tree
	Node* root = pq.top();

	// traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
	encode(root, "", huffmanCode);

	/*
	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair: huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}
	*/
    return root;
}

string zip(string text, unordered_map<char, string>& huffmanCode) {
	string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}

    return str;
}

void write_text(string filename, string& text) {
    ofstream out;
    out.open(filename);
    if (out.is_open())
    {
        out << text;
    }
    out.close(); 
}

string get_text(string filename) {
    string text = "";
    ifstream in(filename);
    if (in.is_open())
    {
        string line;
        while (getline(in, line))
        {
            text.append(line);
        }
    }
    in.close();
    return text;
}

string decode(unordered_map<string, char>& huffmanCode, string& text) {
    string str;
    int it = 0;
    while (it < text.size() - 1) {
        int size = 1;
        string enc = "";
        while (!huffmanCode[enc]) {
            enc = text.substr(it, size);
            size++;
			if (it + size > text.size()) break;
        }
        it += size - 1;
        str.push_back(huffmanCode[enc]);
    }
    return str;
}

void store_hash(string filename, unordered_map<char, string>& huffmanCode)
{
    ofstream out;
    out.open(filename);
    if (out.is_open())
    {
        for (auto& pair:huffmanCode) {
            out << pair.first << ':' << pair.second << '\n';
        }
    }
    out.close(); 
}

void load_hash(string filename, unordered_map<string, char>& huffmanCode)
{
    ifstream in;
    string line;
    in.open(filename);
    if (in.is_open())
    {
        while (getline(in, line))
        {
            if (line.empty()) {
                continue;
            }
            stringstream ss(line);
            string c;
            string code;
            getline(ss, c, ':');
			getline(ss, code, ':');
            huffmanCode[code] = c[0];
        }
    }
    in.close(); 
}