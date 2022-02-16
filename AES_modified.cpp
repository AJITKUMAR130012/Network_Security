
#include <iostream>  
#include <bitset>  
#include <string>  
using namespace std;   


  
//AES-128 requires 10 rounds of encryption  
const int total_round = 10; 
 //key_size_in_word Represents the number of word s that are input keys  
 
const int key_size_in_word = 4;  


  // substitution box
bitset<8> substitution_box[16][16] = {  
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},  
    {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},  
    {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},  
    {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},  
    {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},  
    {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},  
    {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},  
    {0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},  
    {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},  
    {0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},  
    {0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},  
    {0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},  
    {0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},  
    {0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},  
    {0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},  
    {0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}  
};  

// inverse substitution box
bitset<8> inverse_substitution_box[16][16] = {  
    {0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB},  
    {0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB},  
    {0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E},  
    {0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25},  
    {0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92},  
    {0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84},  
    {0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06},  
    {0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B},  
    {0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73},  
    {0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E},  
    {0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B},  
    {0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4},  
    {0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F},  
    {0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF},  
    {0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61},  
    {0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D}  
};  


//  matrix round constant  which is used in key_expansion
bitset<32> Round_constant[10] = {0x02000000, 0x03000000, 0x05000000, 0x06000000, 0x70000000,   
                 0x80000000, 0x90000000, 0x10000000, 0x5b000000, 0x56000000};  
  

// function to convert four_byte to one_word
bitset<32> converter_word(bitset<8>& k1,bitset<8>& k2, bitset<8>& k3, bitset<8>& k4)  
{ 
     // taking a variable that store intially zero in hex
    bitset<32> ans(0x00000000);
    // temporory variable  
    bitset<32> mal;  
    // converting bitset to unsigned long
    mal = k1.to_ulong();  
    // left shift by 24
    mal <<= 24;  
    // or with temporory variable
    ans |= mal;  
    // converting bitset to unsigned long
    mal = k2.to_ulong();   
     //left shift by 16
   mal <<= 16; 
   // or with temporory varible 
    ans |= mal; 
    // converting bitset to unsigned lon
    mal = k3.to_ulong(); 
    //left shift by 8
    mal <<= 8;  
    // or with temporory varible
   ans |= mal;  
   //// converting bitset to unsigned lon
    mal = k4.to_ulong(); 
    //or with temporory varible
    ans |= mal;  
    // returning after converting into word
    return ans;  
}  


  


// function used to to left shift by one

bitset<32> left_shift_by_one(bitset<32>& read_word)  
{  
    //storing the bitset by left shift eight
    bitset<32> above = read_word << 8; 
    // storing the bitset by rightshift by 24 
    bitset<32> below= read_word >> 24;  
    // performing or operation and then return the result
    return above | below;  
}  

  

// transformation by s_box for every byte in word

bitset<32> substitution_fun_word(bitset<32> read_word)  
{  
    // a declaration of temporory bitset type variable
    bitset<32> mal;  
    //iterating over substitution box to susbstitution perform
    for(int w=0; w<32; w+=8)  
    {  
        // calculation of row for substitution
        int row = read_word[w+7]*8 + read_word[w+6]*4 + read_word[w+5]*2 + read_word[w+4];  
        // calculation of column for substitution
        int column = read_word[w+3]*8 + read_word[w+2]*4 + read_word[w+1]*2 + read_word[w];  
        // performing the substitution
        bitset<8> val = substitution_box[row][column]; 

        for(int m=0; m<8; ++m)  
            mal[w+m] = val[m];  
    }  
    // returning the result
    return mal;  
}  

  
// function used to expand the key

void fun_expansion_key(bitset<8> key[4*key_size_in_word], bitset<32>w[4*(total_round+1)])  
{  
    // a variable declaration of type bitset
    bitset<32> mal; 
    // declaration and initialization of varible 
    int lol= 0;  
   
// starting four is input key as s 
    while(lol < key_size_in_word)   
    {  
        // calling to converter_word function
        w[lol] = converter_word(key[4*lol], key[4*lol+1], key[4*lol+2], key[4*lol+3]);  
        //increament the varible
        ++lol;  
    }  
  // storing the key size in lol variable
    lol= key_size_in_word;  
    // iteration
    while(lol < 4*(total_round+1))  
    {  
        
        //Record the previous word 
        mal = w[lol-1];  
        //cheking position is divisible by key size or not
        if(lol % key_size_in_word == 0)  
        {
        // if true the abolve condition the store into w[]
            w[lol] = w[lol-key_size_in_word] ^ substitution_fun_word(left_shift_by_one(mal)) ^ Round_constant[lol/key_size_in_word-1];  
        }
        else 
        {
        // if above condition is false then store into w[]
            w[lol] = w[lol-key_size_in_word] ^ mal;  
        }
        ++lol;  
    }  
}  

   
//implementing AES
// definition of substitution byte function

void substitution_byte_function(bitset<8> matrix[4*4])  
{  
   // taking a variable to iterate over susbstitution box 
int w=0;
     while(w<16)
{  
    // calculation of row
        int row = matrix[w][7]*8 + matrix[w][6]*4 + matrix[w][5]*2 + matrix[w][4]; 
        // calculation of column 
        int col = matrix[w][3]*8 + matrix[w][2]*4 + matrix[w][1]*2 + matrix[w][0];  
        //string into matrix according to row and column
        matrix[w] = substitution_box[row][col]; 
        //increament 
        w++;
    }  
}  
  
// definition of shifting left row function

void shifting_left_row_function(bitset<8> matrix[4*4])  
{  
// left shift by one of second row
    bitset<8> mal = matrix[4]; 
    // performing left shift operation 
    for(int w=0; w<3; ++w)  
        matrix[w+4] = matrix[w+5];  
    matrix[7] = mal;  
    
// move two places of third line of circle
    for(int w=0; w<2; ++w)  
    {  
        // taking a temp varible and store the element at position w+8
        mal = matrix[w+8]; 
        //w+8 position occupied by w+10 
        matrix[w+8] = matrix[w+10]; 
        // w+10 position is filled by temp variable for shifting operation 
        matrix[w+10] = mal;  
    }  
   // move three places of third line of circle 
    mal = matrix[15];  
    for(int u=3; u>0; --u)  
    // storing u+11 element to u+12
        matrix[u+12] = matrix[u+11];  
        //stroing temporory varible to at position 12
    matrix[12] = mal;  
}  
  

//  multiplication on finite field
bitset<8> multiplication_by_gf(bitset<8> mal1, bitset<8> mal2) { 
    // declaration of varible of type bitset  
    bitset<8> pppp = 0;  
    // again declaration of temprory variable of type bitset
    bitset<8> set_bit;  
    //performing the multiplication operation
    for (int counter = 0; counter < 8; counter++) { 
        // checking condition 
        if ((mal2 & bitset<8>(1)) != 0) { 
            // xor operation  
            pppp ^= mal1;  
        }  
        set_bit = (bitset<8>) (mal1 & bitset<8>(0x80));  
        //left shift by one
        mal1 <<= 1;  
        // checking condition
        if (set_bit != 0) {
            //performing x-or operation
            /* y^8 + y^4 + y^3 + y + 1 */   
            mal1 ^= 0x1b;      
        }  
        //right shift by one
        mal2 >>= 1;  
    }  
    // returning the result
    return pppp;  
}  
  
// definition of mix_column function to perform mix_column operation
void mix_column_function(bitset<8> matrix[4*4])  
{  
    // declaration of array of size 4 of type bitset
    bitset<8> array[4];  
    //iteration
    for(int a=0; a<4; ++a)  
    {  
        // internal iteration
        for(int b=0; b<4; ++b)  
        // storing into array temp
            array[b] = matrix[a+b*4];  
        // performing the relavant operation to perform mix_coumn function
        matrix[a] = multiplication_by_gf(0x02, array[0]) ^ multiplication_by_gf(0x03, array[1]) ^ array[2] ^ array[3];  
        // stroing at a+4 position
        matrix[a+4] = array[0] ^ multiplication_by_gf(0x02, array[1]) ^ multiplication_by_gf(0x03, array[2]) ^ array[3];  
        // stroing at a+8 position
        matrix[a+8] = array[0] ^ array[1] ^ multiplication_by_gf(0x02, array[2]) ^ multiplication_by_gf(0x03, array[3]); 
        // storing at a+12 position 
        matrix[a+12] = multiplication_by_gf(0x03, array[0]) ^ array[1] ^ array[2] ^ multiplication_by_gf(0x02, array[3]);  
    }  
}  
  
// definition of adding key function
void adding_round_key_function(bitset<8> matrix[4*4], bitset<32>kate[4])  
{  
    // iteration
    for(int a=0; a<4; ++a)  
    {  
        // perform the right shift then store in kate1
        bitset<32> kate1 = kate[a] >> 24;  
        //perform the left shift followed by right shift then store in kate2
        bitset<32> kate2 = (kate[a] << 8) >> 24; 
         //perform the left shift followed by right shift then store in kate3
        bitset<32> kate3 = (kate[a] << 16) >> 24;  
        //perform the left shift followed by right shift then store in kate3
        bitset<32> kate4 = (kate[a] << 24) >> 24;  
          // performing the x-or then store at position a
        matrix[a] = matrix[a] ^ bitset<8>(kate1.to_ulong()); 
        // performing the x-or then store at position a+4
        matrix[a+4] = matrix[a+4] ^ bitset<8>(kate2.to_ulong());  
        // performing the x-or then store at position a+8
        matrix[a+8] = matrix[a+8] ^ bitset<8>(kate3.to_ulong()); 
        // performing the x-or then store at position a+12 
        matrix[a+12] = matrix[a+12] ^ bitset<8>(kate4.to_ulong());  
    }  
}  
  
// definition of inverse substitution function
void inverse_substitution_function(bitset<8> matrix[4*4])  
{  
    // iteration
    for(int a=0; a<16; ++a)  
    {  // calculation of row
        int row = matrix[a][7]*8 + matrix[a][6]*4 + matrix[a][5]*2 + matrix[a][4];  
        //calculation of column
        int column = matrix[a][3]*8 + matrix[a][2]*4 + matrix[a][1]*2 + matrix[a][0];  
        // storing into matrix after calculation of row and column
        matrix[a] = inverse_substitution_box[row][column];  
    }  
}  
  
// definition of inverse_shift row function
void inverse_shift_row_function(bitset<8> matrix[4*4])  
{  
    //The second line circle moves one bit to the right  
    bitset<8> mal = matrix[7];  
    // iteration
    for(int a=3; a>0; --a)  
    {
        // element at position a=3 is store at a+4
        matrix[a+4] = matrix[a+3];  
    }

    matrix[4] = mal;  
    //The third line circle moves two to the right 
    //iteration 
    for(int a=0; a<2; ++a)  
    {  
        // storing element of position a+8
        mal = matrix[a+8];  
        // storing a+10 element to a+8
       matrix[a+8] = matrix[a+10]; 
       // storing back to a+10 from temporory variable 
        matrix[a+10] = mal;  
    }  
    //Fourth line circle moves three to the right  

    mal = matrix[12];  
    // iteration
    for(int a=0; a<3; ++a)  
    // stroring element at a+13 to a+12
        matrix[a+12] = matrix[a+13]; 
        // storing at last frm temprory varible 
    matrix[15] = mal;  
}  
  // definition of mix_column while decryption
void mix_column_inverse(bitset<8> matrix[4*4])  
{  
    // a temporory variable of type bitset
   bitset<8> arr[4];  
   // iteration
    for(int a=0; a<4; ++a)  
    {  
        // internal iteration
        for(int b=0; b<4; ++b)  
        // mix column_operation
            arr[b] =matrix[a+b*4];  
         // storing at position a
        matrix[a] = multiplication_by_gf(0x0e, arr[0]) ^ multiplication_by_gf(0x0b, arr[1]) ^ multiplication_by_gf(0x0d, arr[2]) ^ multiplication_by_gf(0x09, arr[3]); 
         // storing at position a+4
        matrix[a+4] = multiplication_by_gf(0x09, arr[0]) ^ multiplication_by_gf(0x0e, arr[1]) ^ multiplication_by_gf(0x0b, arr[2]) ^ multiplication_by_gf(0x0d, arr[3]);
        // storing at position a+8  
        matrix[a+8] = multiplication_by_gf(0x0d, arr[0]) ^ multiplication_by_gf(0x09, arr[1]) ^ multiplication_by_gf(0x0e, arr[2]) ^ multiplication_by_gf(0x0b, arr[3]); 
        // storing at position a+12 
        matrix[a+12] = multiplication_by_gf(0x0b, arr[0]) ^ multiplication_by_gf(0x0d, arr[1]) ^ multiplication_by_gf(0x09, arr[2]) ^ multiplication_by_gf(0x0e, arr[3]);  
    }  
}  

// definition of encryption function
void encryption_function(bitset<8> inct[4*4], bitset<32> toy[4*(total_round+1)])  
{  
    // temporory array of type bitset
    bitset<32> key[4]; 
    //iterartion 
    for(int i=0; i<4; ++i) 
    {
    // stroing the element of toy to temporory array 
        key[i] = toy[i];  
    }
        // calling to adding key function
    adding_round_key_function(inct, key);  
  // iteration
    for(int round=1; round<total_round; ++round)  
    {  
        //calling to substitution  byte function
       substitution_byte_function(inct);  
       //calling to leftshift function
        shifting_left_row_function(inct); 
        //calling to mix_column function 
        mix_column_function(inct);
        // iteration  
        for(int i=0; i<4; ++i)  
        //performing operation
            key[i] = toy[4*round+i];  
            // calling to adding key round function
        adding_round_key_function(inct, key);  
    }  
  // calling to substitution byte function
    substitution_byte_function(inct);  
    // calling to shifting_left_row_function
    shifting_left_row_function(inct); 
    // looping 
    for(int i=0; i<4; ++i) 
    {
    // operation
        key[i] = toy[4*total_round+i]; 
    } 
        // calling to adding round key function
    adding_round_key_function(inct, key);  
}  
  
// function of decryption function
void decryption_function_AES(bitset<8> inct[4*4], bitset<32> toy[4*(total_round+1)])  
{  
    // temporory variable
    bitset<32> key[4]; 
    // iteration  
    for(int a=0; a<4; ++a)  
    {
    // performing relevant operation
        key[a] = toy[4*total_round+a];  
    }
    // calling to adding round key function
    adding_round_key_function(inct, key);  

  // performing the total round in iverse order
    for(int round=total_round-1; round>0; --round)  
    {  
        // calling to inverse shift row function
        inverse_shift_row_function(inct); 
        // calling to inverse_substitution_function
        inverse_substitution_function(inct); 
        // iteration 
        for(int a=0; a<4; ++a)  
        {
            // storing into key
            key[a] = toy[4*round+a];  
        }
        // calling to adding_round_key_function
        adding_round_key_function(inct, key);
        // calling to   mix_column_inverse
        mix_column_inverse(inct);  
    }  
   // calling to inverse_shift_row_function
    inverse_shift_row_function(inct);
    // calling to   inverse_substitution_function
   inverse_substitution_function(inct);  
   // iteration
    for(int a=0; a<4; ++a)  
    {
        // stroring into key array
        key[a] = toy[a];  
    }
    // calling to adding_round_key_function
   adding_round_key_function(inct, key);  
}  
  
  // main function
int main()  
{  
    // plane_text
bitset<8> plain[16] = {0x31, 0x87, 0x66, 0x76,   
                    0x42, 0x54, 0x81, 0x97,  
                    0x02, 0x10, 0x95, 0x17,  
                    0xb8, 0xfd, 0xd2, 0xa4};
// key
    bitset<8> key[16] = {0x22, 0x73, 0x95, 0x86,   
                    0x25, 0xfe, 0xf2, 0xa6,   
                    0x4b, 0x77, 0xa5, 0xe8,   
                    0x19, 0x3f, 0x45, 0x37};  
  
       
   
   
  // temporory container of type bitset
    bitset<32> w[4*(total_round+1)]; 
    // calling to  fun_expansion_key
    fun_expansion_key(key, w);  
   // printing plane_text
    cout<<"Plane_Text"<<endl; 
    // a variable
    int a=0;
    // printing plane text
    while(a<16)
    {  
        // printing containt after converting into unsigned long
        cout << hex << plain[a].to_ulong() << " ";  
        // if position is divisible by 4
        if((a+1)%4 == 0)  
        {
            // printing newline
            cout << endl; 
        }
        //increament
            a++; 
    }  
    //printing new line
    cout<<endl; 
  
    //Encryption, output ciphertext  
    encryption_function(plain, w); 
    // print a text as cipherText 
    cout << "ciphertext:"<<endl; 
    //variable
    a=0; 
     // printing cipher_text
    while(a<16)
    {  
        // print element of cipher_text after converting into unsigned long
        cout << hex << plain[a].to_ulong() << " ";
        //if (a+1) is divisible by four  
        if((a+1)%4 == 0)  
        {
            // printing new line
            cout << endl;  
        }
        // increament
            a++;
    }  
    // printing new_line
    cout << endl;  
  
    //Decrypt, output plaintext  
    decryption_function_AES(plain, w); 
    // printing a text as  Decrypted plaintext:
    cout << "Decrypted plaintext:"<<endl; 
    // variable
    a=0; 
    // printing decrypted message
    while(a<16) 
    {  
        // printing eleent of decrypted message
        cout << hex << plain[a].to_ulong() << " "; 
        // checking condition(a+1) is divisible by four or not 
        if((a+1)%4 == 0)  
        {
            // if divisible by four then printing new line
            cout << endl; 
        }
        // incrementation
            a++; 
    }  
    // printing new line
    cout << endl; 
    // returning zero from main function 
    return 0;  
}  

