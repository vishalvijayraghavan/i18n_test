/*
Run :
    gcc -o unicode unicode.c -lm
    ./unicode
    input utf-16 hex string > eg A2
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



/* Binary to hex decimal converter */
void binary_to_hex(char bin[]){

	int i,j,temp;
	char hexString[5],utf_8_string[5];

	/* Extract first byte and find binary hex value of it */
	for(i=0; bin[i]!='\0'; i+=4){

			for(j=0;j<4;j++){
				hexString[j] = bin[i+j];
			}
			hexString[5] = '\0';

			temp = atoi(hexString);
			switch(temp){

					case 0:
							strcat(utf_8_string, "0");
							break;
					case 1:
							strcat(utf_8_string, "1");
							break;
					case 10:
							strcat(utf_8_string, "2");
							break;
					case 11:
							strcat(utf_8_string, "3");
							break;
					case 100:
							strcat(utf_8_string, "4");
							break;
					case 101:
							strcat(utf_8_string, "5");
							break;
					case 110:
							strcat(utf_8_string, "6");
							break;
					case 111:
							strcat(utf_8_string, "7");
							break;
					case 1000:
							strcat(utf_8_string, "8");
							break;
					case 1001:
							strcat(utf_8_string, "9");
							break;
					case 1010:
							strcat(utf_8_string, "A");
							break;
					case 1011:
							strcat(utf_8_string, "B");
							break;
					case 1100:
							strcat(utf_8_string, "C");
							break;
					case 1101:
							strcat(utf_8_string, "D");
							break;
					case 1110:
							strcat(utf_8_string, "E");
							break;
					case 1111:
							strcat(utf_8_string, "F");
							break;
					default:
							printf("Invalid binary input.");
			}
	}

	strcat(utf_8_string,"\0");
	printf("utf-8 encoded string : %s\n",utf_8_string);
}

/* hex to binary converter */
void hex_to_binary(char *hex,char *bin){
	int i = 0;
	/* Extract first digit and find binary of each hex digit */
	for(i=0; hex[i]!='\0'; i++)
	{
			switch(hex[i])
			{
					case '0':
							strcat(bin, "0000");
							break;
					case '1':
							strcat(bin, "0001");
							break;
					case '2':
							strcat(bin, "0010");
							break;
					case '3':
							strcat(bin, "0011");
							break;
					case '4':
							strcat(bin, "0100");
							break;
					case '5':
							strcat(bin, "0101");
							break;
					case '6':
							strcat(bin, "0110");
							break;
					case '7':
							strcat(bin, "0111");
							break;
					case '8':
							strcat(bin, "1000");
							break;
					case '9':
							strcat(bin, "1001");
							break;
					case 'a':
					case 'A':
							strcat(bin, "1010");
							break;
					case 'b':
					case 'B':
							strcat(bin, "1011");
							break;
					case 'c':
					case 'C':
							strcat(bin, "1100");
							break;
					case 'd':
					case 'D':
							strcat(bin, "1101");
							break;
					case 'e':
					case 'E':
							strcat(bin, "1110");
							break;
					case 'f':
					case 'F':
							strcat(bin, "1111");
							break;
					default:
							printf("Invalid hexadecimal input.");
			}
			strcat(bin,"\0");
	}
}


/* binary to decimal converter */
void bin_to_decimal(char *bin,int *dec){
	int binary =  atoi(bin); ;
	int i = 0, s = 0;
	/*
	for (int i = 0; bin[i] != '\0'; ++i){
        	binary = binary*10 + bin[i] - '0';
        }
        */

	while(binary){
		s = s+pow(2,i)*(binary%10);
		binary = binary/10;
		i++;
	}
	*dec = s;
	printf("%d\n",s);
}


/* utf-8 substitution method */
void subst(char *bin,char *byte_array){
	int i=strlen(byte_array)-1,j=strlen(bin)-1;
	while(i >= 0){
		if(byte_array[i] == '-' && j >= 0){
			byte_array[i] = bin[j];
			j--;
		}
		else if(byte_array[i] == '-' && j < 0){
			byte_array[i] = '0';
		}
		i--;
	}
}

/* utf-8 formatter method */
void form_utf8(char *bin,int no_of_bytes){

	if(no_of_bytes == 1){
			/* pattern for one byte utf-8 string */
			char byte_array[9] = {'0','-','-','-','-','-','-','-','\0'};
			subst(bin,byte_array);
			printf("%s\n",byte_array);
			binary_to_hex(byte_array);
	}
	else if(no_of_bytes == 2){
			/* pattern for two byte utf-8 string */
			char byte_array[17] = {'1','1','0','-','-','-','-','-','1','0','-','-','-','-','-','-','\0'};
			subst(bin,byte_array);
			printf("%s\n",byte_array);
			binary_to_hex(byte_array);
	}
	else{
			printf("invalid no of bytes");
	}
}

int main()
{
    char hex[17],bin[65];
		int dec=0;
    /* Input hexadecimal number from user */
    printf("Enter any utf-16 string: ");
    scanf("%s",&hex);
		hex_to_binary(hex, bin);
		bin_to_decimal(bin,&dec);

		if(dec >= 0 && dec <= 127){
				form_utf8(bin,1);
		}else if(dec >= 128 && dec <=2047){
				form_utf8(bin,2);
		}else{
			printf("invalid value passed");
		}
    return 0;
}
