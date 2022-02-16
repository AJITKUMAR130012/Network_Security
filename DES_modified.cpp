// include the library
#include <iostream>
#include <string>
#include<math.h>
using namespace std;


// function performing circular left shift by two
string shift_left_twice(string key_value){ 
    // variable it store the shifted left by one string result
    string shifted_string=""; 
    // Two time shift operation perform
    for(int a = 0; a < 2; a++){ 
         // iteration over the string
        for(int b = 1; b < 28; b++){ 
            //ith element is stoed in (i-1)th position
            shifted_string += key_value[b]; 
        } 
        // at last append the element at position zero in key_value
        shifted_string += key_value[0]; 
        // shifted string store back into key_value to perform left shift 
        key_value=shifted_string; 
        //making shifted string to empty
       shifted_string =""; 
    } 
    // returning the shifted string that is above stored back to key_value
    return key_value; 
}

// function for left circular shift
string shift_left_byone(string key_value){ 
    // variable it store the shifted left by one string result
    string shifted_string=""; 
    // iteration over the string 
        for(int a = 1; a < 28; a++){ 
            //ith element is stoed in (i-1)th position
           shifted_string += key_value[a]; 
        } 
        // at last append the element at position zero in key_value
        shifted_string += key_value[0];
        //returning the shifted_string   
    return shifted_string; 
} 



// string array to store 16 keys
string keys_round[16];

void key_generator(string key){
    // The Pc1 table to compress the key from 64 to 56
    int pc_1[56] = {
    56,48,40,32,24,16,8, 
    0,57,49,41,33,25,17, 
    9,1,58,50,42,34,26, 
    18,10,2,59,51,443,35,         
    62,54,46,38,30,22,14, 
    6,61,53,45,37,29,21, 
    13,5,60,52,44,36,28, 
    20,12,4,27,19,11,3 
    };
    // The PC2 table to compress the key size from 56 to 48
    int pc_2[48] = { 
    13,16,10,23,0,4, 
    2,27,14,5,20,9, 
    22,18,11,3,25,7, 
    15,6,26,19,12,1, 
    40,51,30,36,46,54, 
    29,39,50,44,32,47, 
    43,48,38,55,33,52, 
    45,41,49,35,28,31 
    }; 
    // variable to store permute string
    string permutation_string_key =""; 
    // iteration over the pc1 table
    for(int a = 0; a < 56; a++){ 
        // Convert the key from 64 to 56 bit by compression
        permutation_string_key+= key[pc_1[a]]; 
    } 
    // Dividing the result into two equal halves
    // left and right is used to strore the substring
    string left_message= permutation_string_key.substr(0, 28); 
    string right_message= permutation_string_key.substr(28, 28); 
    // Generating all the sixteen keys
    for(int b=0; b<16; b++){ 
       
//shift the key value by one in round 3,8,11,15
        if(b == 2 || b == 7 || b==10 || b==14 ){
            // calling to shift_left_byone function for left string
            left_message= shift_left_byone(left_message); 
             // calling to shift_left_byone function for right string
            right_message=shift_left_byone(right_message);
        } 
        
//shift the ket vlue by two for round except 3,8,11,15
        else{
            // calling to shift_left_twice function for left string
            left_message= shift_left_twice(left_message); 
            // calling to shift_left_twice function for right string
            right_message= shift_left_twice(right_message);
        }
    // combinning the left and right string
    string combined_key = left_message + right_message;
    // variable use to store key generated at particular phase
    string round_key = ""; 


// transpose the key bits byusing PC2
    for(int c = 0; c < 48; c++){ 
        //after transpose storing into round_key variable
        round_key += combined_key[pc_2[c]]; 
    }  
    keys_round[b] = round_key;

    } 

}




// valriable store the original message
string plane_text;

// function converting decimal to binary

// function use to covert binary to decimal value
int convertBinaryToDecimal(string binary)
{
    //variable use to strore decimal value
    int decimal = 0;
    // counter variable
    int counter = 0;
    // size store then length of binary string
    int size = binary.length();
    // iterating over the binary string
    for(int i = size-1; i >= 0; i--)
    {
        //checking the bit of binary string
        if(binary[i] == '1'){
            // if it is one then decimal value increase by (2^counter)
            decimal += pow(2, counter);
        }
        //increasing the value of counter
    counter++;
    }
    // returning decimal value
    return decimal;
}

string convertDecimalToBinary(int decimal)
{
    // variable use to store the binary result
    string binary;
    // looping over decimal value untill it becoe zero
    while(decimal != 0) {
        // remainder after dividing by two store in head of binary_string
        binary = (decimal % 2 == 0 ? "0" : "1") + binary; 
        // half the decimal value
        decimal = decimal/2;
    }
    //increasing the binary string length if its length is less than four by appending zero in front
    while(binary.length() < 4){
        // appending zero in front
        binary = "0" + binary;
    }
    // returning binary string
    return binary;
}





// Function to compute xor between two strings
string Xor(string a, string b){ 
    // variable use to store result
    string result = ""; 
    // size store the length of b string
    int size = b.size();
    //iterating over both string
    for(int i = 0; i < size; i++){
        // if both are not equal then result store the value 1(x-or properties) 
        // converting char to int
         int t=a[i]-48;
         // converting char to int
        int u=b[i]-48;
        // x-or operation by modulo two properties
        int rem=(t+u)%2;
        // converting int to string then push_back into the result
        result+=to_string(rem);
    } 
    // returning the result
    return result; 
} 


// function DES , implementation of DES algorithm
string DES_fun(){ 
  
    // inverse_permutation table
    int inverse_permutation_table[64]= { 
         39,7,47,15,55,23,63,31, 
    38,6,46,14,54,22,62,30, 
    37,5,45,13,53,21,61,29, 
    36,4,44,12,52,20,60,28, 
    35,3,43,11,51,19,59,27, 
    34,2,42,10,50,18,58,26, 
    33,1,41,9,49,17,57,25, 
    32,0,40,8,48,16,56,24 
    };
    // initial permutation table will be use to for initial permutation
 int initial_permutation_table[64] = { 
    57,49,41,33,25,17,9,1, 
    59,51,43,35,27,19,11,3, 
    61,53,45,37,29,21,13,5, 
    63,55,47,39,31,23,15,7, 
    56,48,40,32,24,16,8,0, 
    58,50,42,34,26,18,10,2, 
    60,52,44,36,28,20,12,4, 
    62,54,46,38,30,22,14,6 
    }; 
// expansion table is use to increase right string from thirty two to fourty eight bit 
    int expansion_table[48] = { 
    31,0,1,2,3,4,3,4, 
    5,6,7,8,7,8,9,10, 
    11,12,12,12,13,14,15,16, 
    15,16,17,18,19,20,19,20, 
    21,22,23,24,23,24,25,26, 
    27,28,27,28,29,30,31,0 
    }; 
 

//substition box will be used for substitution
   int substition_boxes[8][4][16]=  
    {{ 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
        13,14,1,3,0,2,5,4,8,7,6,9,10,11,12,15 
       
    }, 
    { 
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
    }, 
    { 
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
    }, 
    { 
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
    }, 
    { 
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
    }, 
    { 
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
    }, 
    { 
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
    }, 
    { 
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
    }};
    //  permutation table to perform permutation intermediate
    int permutation_tab[32] = { 
    15,6,19,20,28,11,27,16, 
    0,14,22,25,4,17,30,11, 
    1,7,23,13,31,26,2,8,
    18,12,29,5,21,10,3,24 
    }; 
   // variable use to store initial permutation result
    string first_permutation_string = "";
    // iterating over the initial_permutation_table 
    for(int i = 0; i < 64; i++){ 
        //after performing the permutation , storing variable
       first_permutation_string += plane_text[initial_permutation_table[i]]; 
    }  
    // Divide the string into two part
    //left variable store the left 32 bit string
    string left = first_permutation_string.substr(0, 32); 
    //right variable store the right 32 bit string
    string right = first_permutation_string.substr(32, 32);
    
//Encryption done at 16 times
    for(int a=0; a<16; a++) {
        // variable store the expended right string 
        string right_expanded_string = ""; 
        
//half right expansion of plane text to perform x-or between key and right string
        for(int a = 0; a < 48; a++) { 
            right_expanded_string+= right[expansion_table[a]]; 
    }; 
     // x-or between expended_right string and key
        string xored_res = Xor(keys_round[a],right_expanded_string);  
        // variable use to store final result 
        string final_res = ""; 
       

// dividing the result into eight parts and here passed substitution box and
 //size is reduce to four bit from six bit
        for(int a=0;a<8; a++){ 
            // Finding row and column indices to lookup the
            // substituition box
            // calculation of row to use substitution box
            string row1= xored_res.substr(a*6,1) + xored_res.substr(a*6 + 5,1);
            //converting the row from binary string to decimal
            int row = convertBinaryToDecimal(row1);
            // calculation of column to use in substitution box
            string col1 = xored_res.substr(a*6 + 1,1) + xored_res.substr(a*6 + 2,1) + xored_res.substr(a*6 + 3,1) + xored_res.substr(a*6 + 4,1);;
            //converting the binary value from binary to decimal
            int col = convertBinaryToDecimal(col1);
            //substitution occur
            int val = substition_boxes[a][row][col];
            // substitution box return the decimal value so coverting into binary
            // calling the decimaltobinary converter function
           final_res += convertDecimalToBinary(val);  
        } 
        // Another permutation is applied
        // variable to store the permute string
        string first_permutation_string2 =""; 
        // iterating over the permutation_tab
        for(int a = 0; a< 32; a++){ 
            //performing permutation for each element
            first_permutation_string2 += final_res[permutation_tab[a]]; 
        }
        //  The result is xored with the left half
        xored_res = Xor(first_permutation_string2, left);
        left = xored_res; 

          //Swap of left and right string
        if(a < 15){ 
            swap(left,right);

        } 
    } 

// adding the left and right string
    string merge_text = left + right; 
    // variable use to store cipher text  
    string ciphertext_string =""; 

//performing inverse permutation 
    for(int w = 0; w< 64; w++){ 
       
        ciphertext_string+= merge_text[inverse_permutation_table[w]]; 
    }

//returning cipher_text
    return ciphertext_string; 
}

int main(){ 
    // A 64 bit key
     string key;
    cout<<"Please enter  key(binary_form of size 64)"<<endl;
    cin>>key;
 //   cout<<"Enter plane text(binary_form of size 64)"
 //   cin>>plane_text;
  //  string key= "1010101010111011000010010001100000100111001101101100110011011101";
    // original message of 64 bit
      plane_text= "1110101010101010101010000000000001101010101010100000111111010100";
    string a_plane_text = plane_text;
    // Calling the function to generate 16 keys
    key_generator(key); 
    cout<<"Original_message: "<<plane_text<<endl; 
    // calling to DES function
    string cipher_text= DES_fun(); 
    cout<<"Incrypted_message : "<<cipher_text<<endl;
    // Reversing the keys_round array for decryption
    int n = 15;
    int m = 0;
    while(n > m)
    {
        // storing key at particular round from back to temp
        string temp = keys_round[n];
       // in last keys_round , stroing the initail key
        keys_round[n] = keys_round[m];
        //storing temp into intial key_round
        keys_round[m] = temp;
        n--;
        m++;
        // overall swapping done
    }
    // copy the cipher_text contenet to plane_text
    plane_text = cipher_text;
    // calling des function again to perform dycryption
    string decrypted_text = DES_fun();
    //printing dycripted message
    cout<<"Decrypted message:"<<decrypted_text<<endl;
    // Comapring the initial plain text with the decrypted text
    if (decrypted_text == a_plane_text){
        cout<<"Plain text encrypted and decrypted perform successfully."<<endl;
    }
    else{
        cout<<"Incryption and decryption failled"<<endl;
    }
} 

