/* filename: structs.c
 * demonstrate structures, unions and bit fields in C 
 */

/* sample output:
  1 bit :(5)   1
  2 bits:(4)   0
  2 bits:(7)   3
  
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int SIZE = 5;

/* define a struct type without using keyword typedef */
struct test {
    int i;
    int j;
};
 
int main()
{
  /* declare a variable of that type - note use of struct keyword */
  struct test my_test;

  /* you must use the 'struct' keyword in all cases */
  struct test * t;

  /* define a struct type and declare a variable of that type */
  struct {
     char fname[20];
     char lname[20];
     int age;
  } person; 

  person.age = 20;


  /* you can define a struct type using keyword typedef */
  typedef struct {
      char str[80];
  } Str80;


  /* a variable declared of the structure type does not need 'struct' */
  Str80 oneString;
  Str80 * arrStr80s[SIZE];   

  printf("Size of a type Str80: %d\n", sizeof(Str80));
  printf("Size of a variable onString : %d\n", sizeof(oneString));
  
  arrStr80s[0] = (Str80 *)malloc (sizeof(Str80));   
  arrStr80s[1] = (Str80 *)malloc (sizeof(Str80));   

  
  /* structures may be nested and self-referential via pointers */
  typedef struct {
     char name[30];
     int ID;  
     struct {               /*  Nested structure */ 
          int day;
          int month;
          int year;
     } birth_date;
  
  } Employee;

  Employee jon, sue;    // this creates two variables of employee type
  Employee sam;
  
  sam.ID = 7347;
  jon.birth_date.day = 15;
  sue.ID = 7734;
 
  Employee * eptr = malloc(sizeof(Employee)); 
  eptr->ID = 9999;
  eptr->birth_date.day = 30;
  strcpy(eptr->name,"sam spade");
 
  /* example of structures using named and unnamed bit fields, which allow 
     data to be densely packed into storage */
  struct Bits { 
    unsigned int a:1;   // bit field of size 1 bit
    unsigned int :0 ;   // unnamed bit field of size 0 forces c to be aligned 
    unsigned int c:2;   // named bit field of size 2
    unsigned int b:1;   // named bit field of size 1 
  } bits;
 
  /* do some funky coercions- gcc will give you a warning but you can ignore */ 
  bits.a =5;   // assigns 'a' the least significant bit of 101
  bits.c =4;   // assigns 'c' the least 2 significant bits of 100
  
  printf("1 bits.a:(5)   %d \n", bits.a);
  printf("2 bits.c:(4)   %d \n", bits.c);

  bits.c =7;   // assigns 'c' the least 2 significant bits of 111
  printf("2 bits.c:(7)   %d \n", bits.c);

  bits.b =1;   // flip b bit 
  printf("bits.a %d & bits.b %d is %d \n", bits.a, bits.b, bits.a & bits.b);
  bits.b = bits.b << 1;   // left shift b bit 
  printf("bits.a %d & bits.b %d is %d \n", bits.a, bits.b, bits.a & bits.b);
  printf("bits.a %d | bits.b %d is %d \n", bits.a, bits.b, bits.a | bits.b);
  printf("bits.a %d ^ bits.b %d is %d \n", bits.a, bits.b, bits.a ^ bits.b);
  bits.b = 1;  
  printf("bits.a %d ^ bits.b %d is %d \n", bits.a, bits.b, bits.a ^ bits.b);
  return 0;
}
  
