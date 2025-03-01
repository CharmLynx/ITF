#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const string base64_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

vector<unsigned char> base64_decode(const string &encoded_data) {
    vector<unsigned char> decoded_data;
    int val = 0, bits = -8;
    for (const char &c : encoded_data) {
        if (c == '=') break;
        int index = base64_alphabet.find(c);
        if (index == string::npos) continue;
        
        val = (val << 6) | index;
        bits += 6;
        if (bits >= 0) {
            decoded_data.push_back((val >> bits) & 0xFF);
            bits -= 8;
        }
    }
    return decoded_data;
}

int main() {
    ifstream afile("encoded.txt");
    ofstream file("decoded.bin", ios::binary);
    
    string encoded_data, line;
    while (getline(afile, line)) {
        encoded_data += line;
    }
    afile.close();
    
    vector<unsigned char> decoded_data = base64_decode(encoded_data);
    file.write(reinterpret_cast<const char*>(decoded_data.data()), decoded_data.size());
    file.close();
    
    return 0;
}
