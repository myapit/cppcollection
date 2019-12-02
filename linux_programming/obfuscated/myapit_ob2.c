#include <stdio.h>
#include <stdlib.h>

//compression algo rithim 
void comp_algo(__int128_t s, int i){
    int c= (((s & ((__int128_t)0x1FULL << i * 5)) >> i * 5 ) + 65);
    printf("%c",c);
}

int main() {
    for(int i=0;i<17;i++) {
        comp_algo(0x79481E6BBCC01223 + ((__int128_t)0x1222DC << 64), i);
    }
}




