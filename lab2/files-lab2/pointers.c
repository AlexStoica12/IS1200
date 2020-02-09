/*    
   pointers.c 
   By Leonardo Filippeschi.
   Last modified: 2020-02-09
   This file in in the public domain.

 */

#include <stdlib.h>
#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int list1[20];
int list2[20];
int count = 0;

void copycodes(char* text1, int* list1){
  for(int i=0; *(i+text1)!=0; i++){
    *(i+list1) = *(i+text1);
    count++;
  }    
}

void work(){
  copycodes(text1, list1);
  copycodes(text2, list2);  
}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

  void endian_proof(const char* c){
    printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
	   (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
  }

  int main(void){
    work();

    printf("\nlist1: ");
    printlist(list1);
    printf("\nlist2: ");
    printlist(list2);
    printf("\nCount = %d\n", count);

    endian_proof((char*) &count);
  }
