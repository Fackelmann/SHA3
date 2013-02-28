#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "round.h"
#include "sponge.h"

int main(){
  //  char *message="abc";
  //  char *message="abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
  char *message="abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
  int32_t size=strlen(message);;
  int32_t *psize=&size;
  uint8_t *newmessage;
  newmessage=sponge((uint8_t *)message,*psize);
  for(int32_t i=0;i<64;i++){
    printf("%d %X\n",i,*(newmessage+i));
  }
  return 0;
}
