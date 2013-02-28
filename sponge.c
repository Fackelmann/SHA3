#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "round.h"
#include "sponge.h"
#include "keccak_f.h"

uint8_t *sponge(uint8_t* M,int32_t size){
  int32_t r=72;
  int32_t w=8;
  printf("Padding\n");
  /*Padding*/
  if((size%r)!=0){//r=72 bytes
    M=padding(M,&size);
  }
  //  printf("size= %d\n",size);
  uint64_t *nM;
  /*  for(int32_t i=0; i<size;i=i+sizeof(uint64_t)){
    swap((char *)(M+i),sizeof(uint64_t));
    }*/
  nM=(uint64_t *)M;
  printf("%"PRId64"\n",*nM);
  printf("Initialization\n");
  /*Initialization*/
  uint64_t **S=(uint64_t **)calloc(5,sizeof(uint64_t*));
  for(uint64_t i = 0; i < 5; i++) S[i] = (uint64_t *)calloc(5,sizeof(uint64_t));

  printf("Absorbing\n");
  /*Absorbing Phase*/
  for(int32_t i=0;i<size/r;i++){//Each block has 72 bytes
    for(int32_t y=0;y<5;y++){
      for(int32_t x=0;x<5;x++){
	if((x+5*y)<(r/w)){
	  S[x][y]=S[x][y] ^ *(nM+i*9+x+5*y);
	  //	  S=keccak_f(S);
	}
      }
    }
    S=keccak_f(S);
  }
  printf("Squeezing\n");
  /*Squeezing phase*/
  int32_t b=0;
  uint64_t *Z=(uint64_t *)calloc(8,sizeof(uint64_t));
  while(b<8){
  for(int32_t y=0;y<5;y++){
    for(int32_t x=0;x<5;x++){
      if((x+5*y)<(r/w)){
	*(Z+b)^=S[x][y];
	b++;
      }
    }
  }
 }

  /*  for(int32_t i=0; i<64;i=i+sizeof(uint64_t)){
    swap((char *)(Z+i),sizeof(uint64_t));
    }*/

  /*  uint64_t *Z=(uint64_t *)calloc(8,sizeof(uint64_t));
  for(int32_t i=0;i<9;i++){
    *(Z+i)=*(S+i);
    S=keccak_f(S);
    }*/
  /*  for(int32_t x=0;x<5;x++){
      for(int32_t y=0;y<5;y++){
      if((x+5*y)<(r/w)){
      *Z^=S[x][y];

      }
      }
      }*/

  return (uint8_t *) Z;
}

uint8_t *padding(uint8_t* M, int32_t* S){
  int32_t i=*S;
  int32_t newS=(*S+72-(*S%72));;
  uint8_t *nM;
  nM=malloc(*S+(72-(*S%72)));
  /*Copy string*/
  for(int32_t j=0;j<*S;j++){
    *(nM+j)=*(M+j);
  }
  //  *(nM+i)=0x80;
  *(nM+i)=0x01;
  i++;
  while(i<(newS-1)){
    *(nM+i)=0x00;
    i++;
  }
  //  *(nM+i)=0x01;
  *(nM+i)=0x80;
  i++;
  *S=i;
  return nM;
}

/*
  void swap(char *p, int len)

  *p is a pointer to an memory space
  and points to the first byte of our "thing"
  len is the length of our "thing" we want to swap
  
  our number is represented by [0][1][2][3]...
  Where each [#] represents a byte

  For 4 bytes 
  byte swapping means taking
  [0][1][2][3] and turning it into
  [3][2][1][0]

  2 bytes
  [0][1] => [1][0]

*/

void
swap(char *p, int len) {
  int i;
  char tmp;
  for(i = 0; i < len/2; i++) {
    tmp = p[len-i-1];
    p[len-i-1] = p[i];
    p[i] = tmp;
  }
}
