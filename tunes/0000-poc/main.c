#include <stdio.h>

int main(int t){
  for(;t < 80000;t++)
    putchar(((t<<1)^((t<<1)+(t>>7)&t>>12))|t>>(4-(1^7&(t>>19)))|t>>7);
  return 0;
}
