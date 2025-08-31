#include <iostream>
#include <string>
using namespace std;

void getKeyMatrix(const string& key, int keyMatrix[3][3]) {
    int k = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            keyMatrix[i][j] = toupper(key[k++]) - 'A';
}

void encrypt(int cipherMatrix[3][1], int keyMatrix[3][3], int messageVector[3][1]) {
    for (int i = 0; i < 3; i++) {
        cipherMatrix[i][0] = 0;
        for (int j = 0; j < 3; j++)
            cipherMatrix[i][0] += keyMatrix[i][j] * messageVector[j][0];
        cipherMatrix[i][0] %= 26;
    }
}

void HillCipher(const string& message, const string& key) {
    int keyMatrix[3][3];
    getKeyMatrix(key, keyMatrix);

    int messageVector[3][1];
    for (int i = 0; i < 3; i++)
        messageVector[i][0] = toupper(message[i]) - 'A';

    int cipherMatrix[3][1];
    encrypt(cipherMatrix, keyMatrix, messageVector);

    string CipherText = "";
    for (int i = 0; i < 3; i++)
        CipherText += (char)(cipherMatrix[i][0] + 'A');

    cout << "Ciphertext: " << CipherText << endl;
}

int main() {
    string message, key;

    cout << "Enter the message (3 letters): ";
    cin >> message;
    if (message.length() != 3) {
        cout << "Message must have exactly 3 letters." << endl;
        return 1;
    }

    cout << "Enter the key (9 letters): ";
    cin >> key;
    if (key.length() != 9) {
        cout << "Key must have exactly 9 letters." << endl;
        return 1;
    }

    HillCipher(message, key);
    return 0;
}
