#include<bits/stdc++.h>
using namespace std;

//Sbox
const unsigned char GIFT_S[16] = { 1,10, 4,12, 6,15, 3, 9, 2,13,11, 7, 5, 0, 8,14};
const unsigned char GIFT_S_inv[16] = {13, 0, 8, 6, 2,12, 4,11,14, 7, 1,10, 3, 9,15, 5};


//bit permutation
const unsigned char GIFT_P[]={

  0, 17, 34, 51, 48,  1, 18, 35, 32, 49,  2, 19, 16, 33, 50,  3, 4, 21, 38, 55, 52,  5, 22, 39, 36, 53,  6, 23, 20, 37, 54,  7,
  8, 25, 42, 59, 56,  9, 26, 43, 40, 57, 10, 27, 24, 41, 58, 11, 12, 29, 46, 63, 60, 13, 30, 47, 44, 61, 14, 31, 28, 45, 62, 15
};

const unsigned char GIFT_P_inv[]={

  0,  5, 10, 15, 16, 21, 26, 31, 32, 37, 42, 47, 48, 53, 58, 63, 12,  1,  6, 11, 28, 17, 22, 27, 44, 33, 38, 43, 60, 49, 54, 59,
  8, 13,  2,  7, 24, 29, 18, 23, 40, 45, 34, 39, 56, 61, 50, 55, 4,  9, 14,  3, 20, 25, 30, 19, 36, 41, 46, 35, 52, 57, 62, 51
};


// round constants
const unsigned char GIFT_RC[62] = {
    0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3E, 0x3D, 0x3B, 0x37, 0x2F,
    0x1E, 0x3C, 0x39, 0x33, 0x27, 0x0E, 0x1D, 0x3A, 0x35, 0x2B,
    0x16, 0x2C, 0x18, 0x30, 0x21, 0x02, 0x05, 0x0B, 0x17, 0x2E,
    0x1C, 0x38, 0x31, 0x23, 0x06, 0x0D, 0x1B, 0x36, 0x2D, 0x1A,
    0x34, 0x29, 0x12, 0x24, 0x08, 0x11, 0x22, 0x04, 0x09, 0x13,
    0x26, 0x0c, 0x19, 0x32, 0x25, 0x0a, 0x15, 0x2a, 0x14, 0x28,
    0x10, 0x20
};


void encrypt(unsigned char* input, unsigned char* masterkey, int rounds){
cout<<"Encryption >>>>>"<<endl;
    unsigned char key[32];
    for (int i=0; i<32;i++){
        key[i] = masterkey[i];
    }

    cout<<"input = ";
    for (int i=0; i<16; i++){
        cout<<hex<<(int)input[15-i]<<dec;
        if(i%2==1) cout<<" ";
    }
    cout<<endl<<"key = ";
    for (int i=0; i<32;i++){
        cout<<hex<<(int)key[31-i]<<dec;
        if(i%2==1) cout<<" ";
    }
    cout<<endl<<endl;



unsigned char bits[64], perm_bits[64];
unsigned char key_bits[128];
unsigned char temp_key[32];
for (int r=0; r<rounds; r++){

    for (int i=0; i<16; i++){
        input[i] = GIFT_S[input[i]];
    }

        cout<<setw(2)<<r<<": after SubCells: ";
        for (int i=0; i<16; i++){
            cout<<hex<<(int)input[15-i]<<dec;
            if(i%2==1) cout<<" ";
        }
        cout<<endl;
    

    for (int i=0; i<16; i++){
        for (int j=0; j<4; j++){
            bits[4*i+j] = (input[i] >> j) & 0x1;
        }
    }
    
    for (int i=0; i<64; i++){
        perm_bits[GIFT_P[i]] = bits[i];
    }
    
    for (int i=0; i<16; i++){
        input[i]=0;
        for (int j=0; j<4; j++){
             input[i] ^= perm_bits[4*i+j] << j;
        }
    }

    
        cout<<setw(2)<<r<<": after PermBits: ";
        for (int i=0; i<16; i++){
            cout<<hex<<(int)input[15-i]<<dec;
            if(i%2==1) cout<<" ";
        }
        cout<<endl;
    


    
    for (int i=0; i<16; i++){
        for (int j=0; j<4; j++){
            bits[4*i+j] = (input[i] >> j) & 0x1;
        }
    }
    
    for (int i=0; i<32; i++){
        for (int j=0; j<4; j++){
            key_bits[4*i+j] = (key[i] >> j) & 0x1;
        }
    }

    
    int kbc=0;  
    for (int i=0; i<16; i++){
        bits[4*i] ^= key_bits[kbc];
        bits[4*i+1] ^= key_bits[kbc+16];
        kbc++;
    }

    
    bits[3] ^= GIFT_RC[r] & 0x1;
    bits[7] ^= (GIFT_RC[r]>>1) & 0x1;
    bits[11] ^= (GIFT_RC[r]>>2) & 0x1;
    bits[15] ^= (GIFT_RC[r]>>3) & 0x1;
    bits[19] ^= (GIFT_RC[r]>>4) & 0x1;
    bits[23] ^= (GIFT_RC[r]>>5) & 0x1;
    bits[63] ^= 1;

    for (int i=0; i<16; i++){
        input[i]=0;
        for (int j=0; j<4; j++){
             input[i] ^= bits[4*i+j] << j;
        }
    }

    
        cout<<setw(2)<<r<<": after AddRoundKeys: ";
        for (int i=0; i<16; i++){
            cout<<hex<<(int)input[15-i]<<dec;
            if(i%2==1) cout<<" ";
        }
        cout<<endl;
    

    
    for(int i=0; i<32; i++){
        temp_key[i] = key[(i+8)%32];
    }
    for(int i=0; i<24; i++) key[i] = temp_key[i];
    //k0>>12
    key[24] = temp_key[27];
    key[25] = temp_key[24];
    key[26] = temp_key[25];
    key[27] = temp_key[26];
    //k1>>2
    key[28] = ((temp_key[28]&0xc)>>2) ^ ((temp_key[29]&0x3)<<2);
    key[29] = ((temp_key[29]&0xc)>>2) ^ ((temp_key[30]&0x3)<<2);
    key[30] = ((temp_key[30]&0xc)>>2) ^ ((temp_key[31]&0x3)<<2);
    key[31] = ((temp_key[31]&0xc)>>2) ^ ((temp_key[28]&0x3)<<2);

    
        cout<<setw(2)<<r<<": updated Key: ";
        for (int i=0; i<32; i++){
            cout<<hex<<(int)key[31-i]<<dec;
            if(i%2==1) cout<<" ";
        }
        cout<<endl<<endl;
    
}

    
        cout<<"input = ";
        for (int i=0; i<16; i++){
            cout<<hex<<(int)input[15-i]<<dec;
            if(i%2==1) cout<<" ";
        }
        cout<<endl<<"key = ";
        for (int i=0; i<32;i++){
            cout<<hex<<(int)key[31-i]<<dec;
            if(i%2==1) cout<<" ";
        }
        cout<<endl<<endl;
    
return;
}


void decrypt(unsigned char* input, unsigned char* masterkey, int rounds){
cout<<"----------"<<endl<<"decryption..."<<endl<<"----------"<<endl;
    unsigned char key[32];
    for (int i=0; i<32;i++){
        key[i] = masterkey[i];
    }
    
    cout<<"input = ";
    for (int i=0; i<16; i++){
        cout<<hex<<(int)input[15-i]<<dec;
        if(i%2==1) cout<<" ";
    }
    cout<<endl<<"key = ";
    for (int i=0; i<32;i++){
        cout<<hex<<(int)key[31-i]<<dec;
        if(i%2==1) cout<<" ";
    }
    cout<<endl<<endl;


unsigned char round_key_state[rounds][32];
unsigned char bits[64], perm_bits[64];
unsigned char key_bits[128];
unsigned char temp_key[32];
for (int r=0; r<rounds; r++){
    
    for (int i=0; i<32; i++){
        round_key_state[r][i] = key[i];
    }

    
    for(int i=0; i<32; i++){
        temp_key[i] = key[(i+8)%32];
    }
    for(int i=0; i<24; i++) key[i] = temp_key[i];
    //k0>>12
    key[24] = temp_key[27];
    key[25] = temp_key[24];
    key[26] = temp_key[25];
    key[27] = temp_key[26];
    //k1>>2
    key[28] = ((temp_key[28]&0xc)>>2) ^ ((temp_key[29]&0x3)<<2);
    key[29] = ((temp_key[29]&0xc)>>2) ^ ((temp_key[30]&0x3)<<2);
    key[30] = ((temp_key[30]&0xc)>>2) ^ ((temp_key[31]&0x3)<<2);
    key[31] = ((temp_key[31]&0xc)>>2) ^ ((temp_key[28]&0x3)<<2);
}

for (int r=rounds-1; r>=0; r--){
   
    for (int i=0; i<16; i++){
        for (int j=0; j<4; j++){
            bits[4*i+j] = (input[i] >> j) & 0x1;
        }
    }
    
    for (int i=0; i<32; i++){
        for (int j=0; j<4; j++){
            key_bits[4*i+j] = (round_key_state[r][i] >> j) & 0x1;
        }
    }

    
    int kbc=0;  
    for (int i=0; i<16; i++){
        bits[4*i] ^= key_bits[kbc];
        bits[4*i+1] ^= key_bits[kbc+16];
        kbc++;
    }

   
    bits[3] ^= GIFT_RC[r] & 0x1;
    bits[7] ^= (GIFT_RC[r]>>1) & 0x1;
    bits[11] ^= (GIFT_RC[r]>>2) & 0x1;
    bits[15] ^= (GIFT_RC[r]>>3) & 0x1;
    bits[19] ^= (GIFT_RC[r]>>4) & 0x1;
    bits[23] ^= (GIFT_RC[r]>>5) & 0x1;
    bits[63] ^= 1;

   
    for (int i=0; i<16; i++){
        input[i]=0;
        for (int j=0; j<4; j++){
             input[i] ^= bits[4*i+j] << j;
        }
    }

        cout<<setw(2)<<r<<": after inverse AddRoundKeys: ";
        for (int i=0; i<16; i++){
            cout<<hex<<(int)input[15-i]<<dec;
            if(i%2==1) cout<<" ";
        }
        cout<<endl;
    

    for (int i=0; i<16; i++){
        for (int j=0; j<4; j++){
            bits[4*i+j] = (input[i] >> j) & 0x1;
        }
    }
    
    for (int i=0; i<64; i++){
        perm_bits[GIFT_P_inv[i]] = bits[i];
    }
    
    for (int i=0; i<16; i++){
        input[i]=0;
        for (int j=0; j<4; j++){
             input[i] ^= perm_bits[4*i+j] << j;
        }
    }

    
        cout<<setw(2)<<r<<": after inverse PermBits: ";
        for (int i=0; i<16; i++){
            cout<<hex<<(int)input[15-i]<<dec;
            if(i%2==1) cout<<" ";
        }
        cout<<endl;
    


    //SubCells
    for (int i=0; i<16; i++){
        input[i] = GIFT_S_inv[input[i]];
    }

    
        cout<<setw(2)<<r<<": after inverse SubCells: ";
        for (int i=0; i<16; i++){
            cout<<hex<<(int)input[15-i]<<dec;
            if(i%2==1) cout<<" ";
        }
        cout<<endl<<endl;
    



}

    
        cout<<"input = ";
        for (int i=0; i<16; i++){
            cout<<hex<<(int)input[15-i]<<dec;
            if(i%2==1) cout<<" ";
        }
        cout<<endl<<endl;
    
return;
}



int main(){


unsigned char P[16], K[32];
for (int i=0; i<16; i++){
     P[i] = rand() &0xf;
} 
for (int i=0; i<32; i++){ 
    K[i] = rand() &0xf;
}
cout<<"Plaintext = ";
for (int i=0; i<16; i++){
    cout<<hex<<(int)P[15-i]<<dec;
    if(i%2==1) cout<<" ";
}
cout<<endl;

cout<<"masterkey = ";
    for (int i=0; i<32;i++){
        cout<<hex<<(int)K[31-i]<<dec;
        if(i%2==1) cout<<" ";
    }
cout<<endl<<endl;

encrypt(P,K,28);

cout<<"Ciphertext = ";
for (int i=0; i<16; i++){
    cout<<hex<<(int)P[15-i]<<dec;
    if(i%2==1) cout<<" ";
}
cout<<endl<<endl;

decrypt(P,K,28);

cout<<"Plaintext = ";
for (int i=0; i<16; i++){
    cout<<hex<<(int)P[15-i]<<dec;
    if(i%2==1) cout<<" ";
}
cout<<endl;

return 0;}






   

