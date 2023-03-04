#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H
#include <string>

class hash_functions
{
//to hold binary
protected:
    typedef unsigned char register_8; //8 bit
    typedef unsigned int register_32; //32 bit
    typedef unsigned long long register_64; //64 bit

    const static register_32 hash_keys[]; //hold 64 sets of 32 bits
    static const unsigned int BLOCK_SIZE_of_256 = (512/8);
public:
    void stateregister(); //init 8 registers in hexadecimal; (% of the square root of the first 8 prime #s) * 2^32
    void adjust_digest(const unsigned char *text, unsigned int text_len); //text_length starts 1 rest 0 for last 64 bits
    void digest_final(unsigned char *digest);
    static const unsigned int PADD_SIZE = ( 256 / 8); //must pad entire message so 448 bits store message, adn last 64 store message length

protected:
    void compress(const unsigned char *message, unsigned int block_nb);
    unsigned int s_r_totlen; //total length of state register
    unsigned int s_r_len; //current length of state register
    unsigned char s_r_block[2*BLOCK_SIZE_of_256]; //
    register_32 s_r[8]; //
};

std::string sha256(std::string input);

#define R_SHFT(x, n)    (x >> n)  //Right shift function
#define R_ROTATE(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n))) //Right rotate function
#define L_ROTATE(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n))) //Left rotate function
#define CHOICE_OF(x, y, z)  ((x & y) ^ (~x & z)) //function to find choice of
#define MAJORITY_OF(x, y, z) ((x & y) ^ (x & z) ^ (y & z)) //function to find majority of
#define SHAF_1(x) (R_ROTATE(x,  2) ^ R_ROTATE(x, 13) ^ R_ROTATE(x, 22)) //sigma rotation function
#define SHAF_2(x) (R_ROTATE(x,  6) ^ R_ROTATE(x, 11) ^ R_ROTATE(x, 25)) //sigma rotation function
#define SHAF_3(x) (R_ROTATE(x,  7) ^ R_ROTATE(x, 18) ^ R_SHFT(x,  3)) //sigma0 rotation
#define SHAF_4(x) (R_ROTATE(x, 17) ^ R_ROTATE(x, 19) ^ R_SHFT(x, 10)) //sigma1 rotation

#define SHAF_UNPACK32(x, str)                 \
{                                             \
    *((str) + 3) = (register_8) ((x)      );       \
    *((str) + 2) = (register_8) ((x) >>  8);       \
    *((str) + 1) = (register_8) ((x) >> 16);       \
    *((str) + 0) = (register_8) ((x) >> 24);       \
}
#define SHAF_PACK32(str, x)                   \
{                                             \
    *(x) =   ((register_32) *((str) + 3)      )    \
           | ((register_32) *((str) + 2) <<  8)    \
           | ((register_32) *((str) + 1) << 16)    \
           | ((register_32) *((str) + 0) << 24);   \
}
#endif