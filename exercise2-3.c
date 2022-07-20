#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/* write the function htoi(s) which converts a string of hexadecimal digits
(including an optional 0x or 0X) into its equivalent integer value. The 
allowable digits are 0 through 9, a through f, and A through F. */

#define a 10
#define b 11
#define c 12
#define d 13
#define e 14
#define f 15

#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15


#define MAX_HEX_LENGTH 10000
// Converts a string representing a hexidecimal number to an integer number
int convert_to_decimal(char hex[], int hex_length); 

// COnverts s to an integer
int atoi(char s);

int main()
{  
   int hex_length = 0;
   int i = 0;
   char hex[MAX_HEX_LENGTH];
   char hex_digit;
   
   // Read new digit and store in array
   while ((hex_digit = getchar()) != EOF)
   {
      hex[i] = hex_digit;

      ++hex_length;
      ++i;
   }


   printf("%d\n", convert_to_decimal(hex, hex_length));
   return 0;
}

int atoi(char s)
{
   return s - '0';
}

int convert_to_decimal(char hex[], int hex_length)
{
   int i;
   long int integer_value = 0;
   int local_hex_length = hex_length - 1;

   // Some hexadecimal numbers are prefixed by "0x" or "0X" in order to 
   // signify a hex number. We first ask if our hex number contains such a 
   // sequence so that we may ignore the prefix in calculating the decimal
   // representation
   if ((hex[0] == '0') && ((hex[1] == 'x') || (hex[1] == 'X')))
   {
      i = 2;
      local_hex_length -= 2;
   }
   else
      i = 0;

   // We want to use the hex_length to multiply the individual digits by the 
   // corresponding power of 16
   for (;i < hex_length; i++)
   {
      double power = pow(16, local_hex_length);
      if ((hex[i] == 'a') || (hex[i] == 'A'))
      {
         integer_value += power*A;
      }
      else if ((hex[i] == 'b') || (hex[i] == 'B'))
      {
         integer_value += power*B;

      }
      else if ((hex[i] == 'c') || (hex[i] == 'C'))
      {
         integer_value += power*C;

      }
      else if ((hex[i] == 'd') || (hex[i] == 'D'))
      {
         integer_value += power*D;

      }
      else if ((hex[i] == 'e') || (hex[i] == 'E'))
      {
         integer_value += power*E;
      }
      else if ((hex[i] == 'f') || (hex[i] == 'F'))
      {
         integer_value += power*F;
      }
      else
      {
         char s  = hex[i];
         printf("%f\n", power* (atoi(hex[i])));
         integer_value += power* (atoi(s));
      }

      printf("%d\n", local_hex_length);
      //printf("%f\n", pow(16, local_hex_length)* (atoi(hex[i])));
      local_hex_length--;
   }

   return integer_value;
}