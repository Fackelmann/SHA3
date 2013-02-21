#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "round.h"
#include "sponge.h"

int main(){
  printf("Hola\n");
  char *message="abc";
  printf("Adios\n");
  int32_t size=(int32_t *)strlen(message);;
  int32_t *psize=&size;
  //  message=(uint8_t *)message;
  uint8_t *newmessage;
  newmessage=sponge((uint8_t *)message,*psize);
  printf("%d\n",*psize);
  for(int32_t i=0;i<64;i++){
    printf("%d %X\n",i,*(newmessage+i));
  }
  return 0;
}
