#include "crypt.hpp"
#include "fs.hpp"
#include <iostream>

int main(){
    std::string choose;
    char key[1024];
    char data_in[] = "test.txt";
    
    std::cout << "encrypt(en) or decrypt(de): ";
    std::cin >> choose;
    std::cout << "file to " << choose << "crypt: ";
    std::cin >> data_in;
    std::cout << "key to " << choose <<"crypt: ";
    std::cin >> key;
    
    if(choose == "de"){       
        auto tmp_d = file_read(data_in);
        auto tmp_dec = AES128_DEC(reinterpret_cast<char *>(tmp_d.text), key, tmp_d.size);
        file_write(data_in, tmp_dec);
    } else if(choose == "en"){
        auto tmp_d = file_read(data_in);
        auto tmp_enc = AES128_ENC(reinterpret_cast<char *>(tmp_d.text), key, tmp_d.size);
        file_write(data_in, tmp_enc);
    }
    
    return 0;
}
