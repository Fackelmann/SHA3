#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "round.h"
#include "sponge.h"

int main(){
  printf("Hola\n");
  char *message="Hello, world!\n";
  printf("Adios\n");
  int32_t size=(int32_t *)strlen(message);;
  int32_t *psize=&size;
  //  message=(uint8_t *)message;
  uint8_t *newmessage;
  newmessage=padding((uint8_t *)message,psize);
  printf("%d\n",size);
  for(int32_t i=0;i<size;i++){
    printf("%d %X\n",i,*(newmessage+i));
  }

  return 0;
}
