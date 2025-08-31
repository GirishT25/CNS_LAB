#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Prepare the plaintext: remove spaces, convert to lowercase, replace 'j' with 'i', handle double letters, make even length
string prepareText(string text) {
    text.erase(remove(text.begin(), text.end(), ' '), text.end());
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    replace(text.begin(), text.end(), 'j', 'i');
    string result;
    for (size_t i = 0; i < text.length(); i++) {
        result += text[i];
        if (i + 1 < text.length() && text[i] == text[i + 1])
            result += 'x';
    }
    if (result.length() % 2 != 0)
        result += 'x';
    return result;
}

// Generate the 5x5 Playfair matrix using the key
void generateMatrix(string key, char matrix[5][5]) {
    string used = "";
    key += "abcdefghijklmnopqrstuvwxyz";
    for (char &c : key) {
        if (c == 'j') continue;
        if (used.find(c) == string::npos) used += c;
    }
    int k = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matrix[i][j] = used[k++];
}

// Find the row and column of a character in the matrix
void findPosition(char matrix[5][5], char c, int &row, int &col) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
}

// Encrypt the plaintext using Playfair cipher
string playfairEncrypt(const string &text, const string &key) {
    char matrix[5][5];
    generateMatrix(key, matrix);

    string preparedText = prepareText(text);
    string cipher;
    cipher.reserve(preparedText.size()); // reserve space to avoid repeated reallocations

    // Create a lookup for character positions to avoid repeated searches
    unordered_map<char, pair<int,int>> pos;
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            pos[matrix[r][c]] = {r, c};
        }
    }

    for (size_t i = 0; i < preparedText.length(); i += 2) {
        auto [r1, c1] = pos[preparedText[i]];
        auto [r2, c2] = pos[preparedText[i + 1]];

        if (r1 == r2) { // same row
            cipher += matrix[r1][(c1 + 1) % 5];
            cipher += matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) { // same column
            cipher += matrix[(r1 + 1) % 5][c1];
            cipher += matrix[(r2 + 1) % 5][c2];
        } else { // rectangle
            cipher += matrix[r1][c2];
            cipher += matrix[r2][c1];
        }
    }

    return cipher;
}
int main() {
    string key = "ldrp";
    string plaintext = "responsive";
    string encrypted = playfairEncrypt(plaintext, key);
    cout << "Encrypted text: " << encrypted << endl;
    return 0;
}