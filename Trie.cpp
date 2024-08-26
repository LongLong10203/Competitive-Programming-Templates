#include <bits/stdc++.h>
using namespace std;

class Trie {
    struct TrieNode {
        int prefixCount;
        unordered_map<char, TrieNode*> children;
        TrieNode() : prefixCount(0) {}
    };

private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
            current->prefixCount++;
        }
    }

    int count(const string& prefix) const {
        TrieNode* current = root;
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return 0;
            }
            current = current->children[ch];
        }
        return current->prefixCount;
    }
};

int main() {
    
}