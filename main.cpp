
#include <cstddef>
#include <openssl/crypto.h>
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstring>

struct data{
    size_t size;
    unsigned char *text;
    data(size_t s, unsigned char *t) {
        size = s;
        text = t;
    }


};


unsigned char * sha256( char msg_in[]){
    EVP_MD_CTX * ctx;
    EVP_MD * md;

    unsigned len;

    ctx = EVP_MD_CTX_new();

    md = EVP_MD_fetch(NULL, "SHA256", NULL);
    
    EVP_DigestInit_ex(ctx, md, NULL);
    EVP_DigestUpdate(ctx, msg_in,strlen(msg_in));
    
    auto msg_out = new unsigned char[EVP_MD_get_size(md)];

    EVP_DigestFinal_ex(ctx, msg_out, &len);
    EVP_MD_free(md);
    EVP_MD_CTX_free(ctx);
    return msg_out;    
}



data AES128_ENC(char msg_in[], char key[], size_t len){
    auto msg_out = new unsigned char[1062144];
    EVP_CIPHER_CTX * ctx;
    ctx = EVP_CIPHER_CTX_new();
    int outlen =0;
    int tmplen =0;
    auto hkey = sha256(key);
    unsigned char iv[16];
    std::memcpy(iv, hkey, 16); 
    
    EVP_EncryptInit_ex2(ctx, EVP_aes_128_cbc(), hkey, iv, nullptr);
    EVP_EncryptUpdate(ctx, msg_out, &outlen, reinterpret_cast<unsigned char *>(msg_in), len);
    EVP_EncryptFinal_ex(ctx, msg_out + outlen, &tmplen);
    EVP_CIPHER_CTX_free(ctx);
    data data_enc(outlen, msg_out);
    return data_enc;
}

data AES128_DEC(char msg_in[], char key[], size_t len){
    auto msg_out = new unsigned char[1062144];
    EVP_CIPHER_CTX * ctx;
    ctx = EVP_CIPHER_CTX_new();
    int outlen =0;
    int tmplen = 0;
    auto hkey = sha256(key);
    unsigned char iv[16];
    std::memcpy(iv, hkey, 16); 
    
    EVP_DecryptInit_ex2(ctx, EVP_aes_128_cbc(), hkey, iv, nullptr);
    EVP_DecryptUpdate(ctx, msg_out, &outlen, reinterpret_cast<unsigned char *>(msg_in),len);
    EVP_DecryptFinal_ex(ctx, msg_out+outlen, &tmplen);
    EVP_CIPHER_CTX_free(ctx);
    data data_enc(outlen, msg_out);
    return data_enc;
}

data file_read(char * file_name){
    std::ifstream file(file_name);
    file.seekg(0, std::ios::end); 
    auto tmp = file.tellg();
    auto datafile = new char[tmp];
    file.clear(); 
    file.seekg(0); 
    file.read(datafile, tmp);
    file.close();
    data readed_file(tmp, reinterpret_cast<unsigned char*>(datafile));
    return readed_file;    
}

void file_write(char * file_name, data d){
    std::fstream data_file;
    data_file.open(file_name,std::fstream::out); 

    data_file.write(reinterpret_cast<char *>(d.text),d.size);    
    data_file.close();
    
}

int main(){
    std::string choos = "1";
    char key[] = "12323132132";
    char data_in[] = "test.txt";
    
    std::cout << "encrypt(en) or decrypt(de): ";
    std::cin >> choos;
    std::cout << "file to " << choos << "crypt: ";
    std::cin >> data_in;
    std::cout << "key to " << choos <<"crypt: ";
    std::cin >> key;
    


    if(choos == "de"){       
        auto tmp_d = file_read(data_in);
        auto tmp_dec = AES128_DEC(reinterpret_cast<char *>(tmp_d.text), key, tmp_d.size);
        file_write(data_in, tmp_dec);
    }

    else if(choos == "en"){
        auto tmp_d = file_read(data_in);
        auto tmp_enc = AES128_ENC(reinterpret_cast<char *>(tmp_d.text), key, tmp_d.size);
        file_write(data_in, tmp_enc);
    }
    std::cout << "done\n";
    return 0;
}