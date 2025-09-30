 #include <bits/stdc++.h>
using namespace std;

// Function to encrypt using Rail Fence Cipher
string encryptRailFence(string text, int key) {
    if (key == 1) return text; // No change if only 1 rail

    vector<string> rail(key);
    int dir = 1, row = 0;

    for (char c : text) {
        rail[row].push_back(c);
        if (row == 0) dir = 1;
        else if (row == key - 1) dir = -1;
        row += dir;
    }

    string result;
    for (int i = 0; i < key; i++) {
        result += rail[i];
    }
    return result;
}

// Function to decrypt Rail Fence Cipher
string decryptRailFence(string cipher, int key) {
    if (key == 1) return cipher;

    vector<vector<bool>> mark(cipher.size(), vector<bool>(key, false));
    int dir = 1, row = 0;

    // Mark positions
    for (int i = 0; i < cipher.size(); i++) {
        mark[i][row] = true;
        if (row == 0) dir = 1;
        else if (row == key - 1) dir = -1;
        row += dir;
    }

    // Fill characters
    vector<vector<char>> rail(cipher.size(), vector<char>(key, '\n'));
    int idx = 0;
    for (int j = 0; j < key; j++) {
        for (int i = 0; i < cipher.size(); i++) {
            if (mark[i][j] && idx < cipher.size()) {
                rail[i][j] = cipher[idx++];
            }
        }
    }

    // Read in zigzag order
    string result;
    row = 0, dir = 1;
    for (int i = 0; i < cipher.size(); i++) {
        result.push_back(rail[i][row]);
        if (row == 0) dir = 1;
        else if (row == key - 1) dir = -1;
        row += dir;
    }
    return result;
}

int main() {
    string text;
    int key;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key (number of rails): ";
    cin >> key;

    string cipher = encryptRailFence(text, key);
    cout << "Encrypted: " << cipher << endl;

    string decrypted = decryptRailFence(cipher, key);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
