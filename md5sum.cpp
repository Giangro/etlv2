/*
 * File:   md5sum.cpp
 * Author: Alex
 *
 * Created on 28 novembre 2015, 15.44
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include "md5sum.h"

void md5hash(const char* str, char *md5sum) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char*) str, strlen(str), (unsigned char*) &digest);
    for (int i = 0; i < 16; i++)
        sprintf(md5sum+(i * 2), "%02x", (unsigned int) digest[i]);
}
