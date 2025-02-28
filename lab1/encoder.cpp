#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

const string base64_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

string base64_encode(ifstream &file) {
    unsigned char buffer[3];
    string encoded_data = "";

    while (file.read(reinterpret_cast<char*>(buffer), 3)) {
        unsigned int value = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];

        encoded_data += base64_alphabet[(value >> 18) & 0b111111];
        encoded_data += base64_alphabet[(value >> 12) & 0b111111];
        encoded_data += base64_alphabet[(value >> 6) & 0b111111];
        encoded_data += base64_alphabet[value & 0b111111];
    }

    size_t remaining = file.gcount();
    if (remaining > 0) {
        buffer[1] = buffer[2] = 0;

        unsigned int value = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];

        encoded_data += base64_alphabet[(value >> 18) & 0b111111];
        encoded_data += base64_alphabet[(value >> 12) & 0b111111];

        if (remaining == 2) {
            encoded_data += base64_alphabet[(value >> 6) & 0b111111];
            encoded_data += "=";
        } else {
            encoded_data += "==";
        }
    }

    return encoded_data;
}

int main() {
    ifstream file("urlCache.bin", ios::binary);
    
    string encoded_data = base64_encode(file);
    file.close();

    ofstream afile("oded.txt", ios_base::out);
	if (afile.is_open()) {
		const size_t line_length = 76;
        for (size_t i = 0; i < encoded_data.size(); i += line_length) {
            afile << encoded_data.substr(i, line_length) << "\n";
        }
		afile.close();
	}
 
	cin.get();

    return 0;
}
