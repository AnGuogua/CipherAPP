#pragma once
#include<string>
#include<random>
#include<vector>
#include<bitset>
#include<algorithm>
//Crypto++ headfiles
#include <sha.h>
#include <sha3.h>
#include <md5.h>
#include <md4.h>
#include <blake2.h>
#include <hex.h>
#include <base64.h>

#include<QString>

enum hash_type
{
	SHA3_224, SHA3_256, SHA3_384, SHA3_512, SHA2_224, SHA2_256, SHA2_384, SHA2_512, SHA1, MD5, MD4, BLAKE2
};
QString mcharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.+-*;:`~!@#$%^&/|[]{}()<>";
int mblocksize = 8;
QString characters = mcharacters;
int blocksize = mblocksize;
bool autocopy = true;
hash_type ht = SHA3_256;
bool english = true;
bool skipBase64 = false; 
bool setting_start = false;