void getCharInBinary(int *result,int c);
void getEncodedBinary(int *code, char *output);
char binaryToHexa(int x1, int x2, int x3, int x4);

/*
*   Get any char transformed in binary by their value in %d.
*   Declaring an array without loop is quicker.
*   Ratio speed : 1.7
*/

/***************************************************************

This method might be quicker to convert char to binary

// const char *byte_to_binary(int x)
// {
//     static char b[9];
//     b[0] = '\0';
//
//     int z;
//     for (z = 128; z > 0; z >>= 1)
//     {
//         strcat(b, ((x & z) == z) ? "1" : "0");
//     }
//
//     return b;
// }

***************************************************************/

void getCharInBinary(int *result, int c){
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
    result[4] = 0;
    result[5] = 0;
    result[6] = 0;
    result[7] = 0;
    if(c >= 128){
        result[0] = 1;
        c -= 128;
    }
    if(c >= 64){
        result[1] = 1;
        c -= 64;
    }
    if(c >= 32){
        result[2] = 1;
        c -= 32;
    }
    if(c >= 16){
        result[3] = 1;
        c -= 16;
    }
    if(c >= 8){
        result[4] = 1;
        c -= 8;
    }
    if(c >= 4){
        result[5] = 1;
        c -= 4;
    }
    if(c >= 2){
        result[6] = 1;
        c -= 2;
    }
    if(c >= 1){
        result[7] = 1;
        c -= 1;
    }
}

/*
*   Get any binary number transformed in HexaDecimal.
*/

void getEncodedBinary(int *code, char *output){
    int matrice[4][8]={{1,0,0,0,1,1,1,0},{0,1,0,0,1,1,1,1},{0,0,1,0,0,1,1,1},{0,0,0,1,0,0,1,0}};

    /* MATRICE
    *
    *   1000 | 1110 [0][0-7]
    *   0100 | 1111 [1][0-7]
    *   0010 | 0111 [2][0-7]
    *   0001 | 0010 [3][0-7]
    *
    */

    // A VERIFIER !!!!


    char encoded[16];
    int i,j;
    int h=0;
    int k =0;
    int result;
    for(h=0;h<8;h=h+4){
        for(i=0;i<8;i++){
            result = 0;
            for(j=0;j<4;j++){
                result += code[j+h] * matrice[j][i];
            }
            if(result %2 == 0){
                result = 0;
            }else{
                result = 1;
            }
            encoded[k]=result;
            k++;
        }
    }


    output[0] = binaryToHexa(encoded[0],encoded[1],encoded[2],encoded[3]); // This declaration is quicker than doing a loop. Ratio speed : 1.7
    output[1] = binaryToHexa(encoded[4],encoded[5],encoded[6],encoded[7]);
    output[2] = binaryToHexa(encoded[8],encoded[9],encoded[10],encoded[11]);
    output[3] = binaryToHexa(encoded[12],encoded[13],encoded[14],encoded[15]);
}


/*
*   Return a char in HexaDecimal depending on the sequence in binary.
*   Switch quicker but not possible. If/else if is quicker than just doing some if.
*   Ratio speed : 1.3
*/
char binaryToHexa(int x1, int x2, int x3, int x4){
    if(x1 == 0 && x2 == 0 && x3 == 0 && x4 == 0)
        return '0';
    else if(x1 == 0 && x2 == 0 && x3 == 0 && x4 == 1)
        return '1';
    else if(x1 == 0 && x2 == 0 && x3 == 1 && x4 == 0)
        return '2';
    else if(x1 == 0 && x2 == 0 && x3 == 1 && x4 == 1)
        return '3';
    else if(x1 == 0 && x2 == 1 && x3 == 0 && x4 == 0)
        return '4';
    else if(x1 == 0 && x2 == 1 && x3 == 0 && x4 == 1)
        return '5';
    else if(x1 == 0 && x2 == 1 && x3 == 1 && x4 == 0)
        return '6';
    else if(x1 == 0 && x2 == 1 && x3 == 1 && x4 == 1)
        return '7';
    else if(x1 == 1 && x2 == 0 && x3 == 0 && x4 == 0)
        return '8';
    else if(x1 == 1 && x2 == 0 && x3 == 0 && x4 == 1)
        return '9';
    else if(x1 == 1 && x2 == 0 && x3 == 1 && x4 == 0)
        return 'A';
    else if(x1 == 1 && x2 == 0 && x3 == 1 && x4 == 1)
        return 'B';
    else if(x1 == 1 && x2 == 1 && x3 == 0 && x4 == 0)
        return 'C';
    else if(x1 == 1 && x2 == 1 && x3 == 0 && x4 == 1)
        return 'D';
    else if(x1 == 1 && x2 == 1 && x3 == 1 && x4 == 0)
        return 'E';
    else if(x1 == 1 && x2 == 1 && x3 == 1 && x4 == 1)
        return 'F';
    return 0;
}
