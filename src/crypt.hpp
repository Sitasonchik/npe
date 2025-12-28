#pragma once
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <cstring>
#include "data.hpp"

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
    auto *msg_out = new unsigned char[len * AES_BLOCK_SIZE];
    EVP_CIPHER_CTX * ctx;
    ctx = EVP_CIPHER_CTX_new();
    int outlen =0;
    int tmplen =0;
    auto hkey = sha256(key);
    unsigned char iv[16];
    std::memcpy(iv, hkey, 16); 
    
    EVP_EncryptInit_ex2(ctx, EVP_aes_128_cbc(), hkey, iv, nullptr);
    EVP_EncryptUpdate(ctx, msg_out, &outlen, reinterpret_cast<unsigned char *>(msg_in), len);
    EVP_EncryptFinal_ex(ctx, msg_out, &tmplen);
    EVP_CIPHER_CTX_free(ctx);
    data data_enc(outlen, msg_out);
    return data_enc;
}

data AES128_DEC(char msg_in[], char key[], size_t len){
    auto *msg_out = new unsigned char[len * AES_BLOCK_SIZE];
    EVP_CIPHER_CTX * ctx;
    ctx = EVP_CIPHER_CTX_new();
    int outlen =0;
    int tmplen = 0;
    auto hkey = sha256(key);
    unsigned char iv[16];
    std::memcpy(iv, hkey, 16); 
    
    EVP_DecryptInit_ex2(ctx, EVP_aes_128_cbc(), hkey, iv, nullptr);
    EVP_DecryptUpdate(ctx, msg_out, &outlen, reinterpret_cast<unsigned char *>(msg_in),len);
    EVP_DecryptFinal_ex(ctx, msg_out, &tmplen);
    EVP_CIPHER_CTX_free(ctx);
    data data_enc(outlen, msg_out);
    return data_enc;
}
