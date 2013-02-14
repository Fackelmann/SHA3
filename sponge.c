#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "round.h"
#include "sponge.h"

uint8_t *sponge(uint8_t* M,int32_t size){
  /*Padding*/
  if((size%72)!=0){//r=72 bytes
    M=padding(M,&size);
  }
  /*Initialization*/
  int64_t **S=(int64_t **)calloc(5,sizeof(int64_t*));
  for(int64_t i = 0; i < 5; i++) S[i] = (int64_t *)calloc(5,sizeof(int64_t));
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
  *(nM+i)=0x80;
  i++;
  while(i<(newS-1)){
    *(nM+i)=0x00;
    i++;
  }
  *(nM+i)=0x01;
  i++;
  *S=i;
  return nM;
}
