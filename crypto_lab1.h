// crypto_lab1.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <array>

std::string monoalphabetic_sub_encrypt(const std::string &data);
std::string caesar_encrypt(const std::string &data, const int &shift);
std::string vigenere_decrypt(const std::string &data, const std::string &key);
std::string vigenere_encrypt(const std::string &data, const std::string &key);
std::string enigma_encrypt(const std::string &data, const int &rotl_num, const int &rotm_num,const int &rotr_num, const std::string &rotor_settings);
std::string monoalphabetic_sub_decrypt(const std::string &data);
