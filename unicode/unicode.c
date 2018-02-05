#include <stdio.h>
#include <string.h>
#include<stdlib.h>

// reverse string
char *strrev(char *str){
    int i = strlen(str) - 1, j = 0;
    char ch;
    while (i > j){
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;j++;
    }
    return str;
}

// decimal to hex converter
char* dec2hex(int num){
    int rem = 0,i=0;
    char hex[3];
    while(num > 0 && i >=0){
        rem = num%16;
        hex[i] = rem<10 ? (char)rem+48 : (char)rem+55;
        num/=16;
        i++;
    }
    hex[i]='\0';
    return strrev(hex);
}

// This function will take decimal equivalent of input utf-16 hex string and convert it into utf-8 hex string
void utf_16_to_utf_8(int num){

    // if the given input is one byte representation
    if(num >= 0 && num <= 127){
        long int utf_8_byte = 0b00000000 | num;  // byte one template(byte start with 0) OR with binary number
        printf("utf-8 encoded string :");
        printf("%s",dec2hex(utf_8_byte));
    }
    // if the given input is two byte representation
    else if(num >= 128 && num <= 2047){

        long int byte_two = num & 0b111111;      //last six bits
        long int byte_one = (num >> 6) & 0b11111; //will right shift to 6 and get last 4 digits

        long int utf_8_byte_one = 0b11000000 | byte_one; // byte one template(byte start with 110) OR with byte one (last six bits)
        long int utf_8_byte_two = 0b10000000 | byte_two; // byte two template(byte start with 10) OR with byte two (remaining bits)

        printf("utf-8 encoded string :");
        printf("%s",dec2hex(utf_8_byte_one));
        printf("%s",dec2hex(utf_8_byte_two));
    }
    else
        printf("invalid hex string passed");
}


void main(){
    const char hex_input[3];
    printf("Enter any utf-16 string:");
    scanf("%s",&hex_input);
    long int input_data = strtol(hex_input, 0, 16);
    utf_16_to_utf_8(input_data);
}
