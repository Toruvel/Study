#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE * file = fopen(argv[1], "r+");
    int total = 0;
    int32_t x;
    int32_t y;
    while (fread(&x, sizeof(int32_t), 1, file) > 0)
           ++total;
    total -= 1;
    printf("total = %d\n", total);
    fseek(file, 0, SEEK_SET);
    int N = atoi(argv[2]);
    int k = total/N;
    int i;
       printf("k= %d\n", k);
    for (i = 0; i <= (total/2) ; ++i) {
        fread(&x, sizeof(int32_t), 1, file);
        if ( i%N == 0 ) {
            printf("change #%d elem = %d", i, x);
                
            long offs = (k - i/N)*N -1-i ;
            printf(" ..offset = %ld  ", offs);
            fseek(file, offs*sizeof(int32_t), SEEK_CUR);
            fread(&y, sizeof(int32_t), 1, file);
            printf("to %d\n", y);
            fseek(file, -sizeof(int32_t), SEEK_CUR);
            fwrite(&x, sizeof(int32_t), 1, file);
            fseek(file, -(offs + 2)*sizeof(int32_t), SEEK_CUR);
            fwrite(&y, sizeof(int32_t), 1, file);
        }
    }
    fclose(file);
    return 0;
}  
