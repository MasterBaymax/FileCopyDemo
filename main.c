/* fread/fwrite example: read an entire file and copy the file into the another file */
#include <stdio.h>
#include <stdlib.h>
#define N 2048

int main()
{
    FILE *pFile1, *pFile2;
    char *buffer;
    long lSize; // current vallue of the position of file
    size_t result;

    pFile1 = fopen("flowerRGB.bmp", "rb");
    pFile2 = fopen("copy.bmp", "wb");
    if(pFile1==NULL || pFile2==NULL) {fputs("File error", stderr); exit(1);}

    // obtain file size (size = width * height)
    fseek(pFile1, 0L, SEEK_END);
    lSize = ftell(pFile1); //current position assign to lSize
    rewind(pFile1); //return start position

    //allocate memory to contain the whole file:
    buffer = (char *)malloc(sizeof(char)*lSize);
    if(buffer == NULL) {fputs("Memory error", stderr); exit(2);}

    //copy the file into the buffer:
    result = fread(buffer, 1, lSize, pFile1);
    if(result != lSize) {fputs("Reading error",stderr);exit(3);}

    //copy the file into the pFile2:
    result = fwrite(buffer, 1, lSize, pFile2);
    if(result != lSize) {fputs("Writing error",stderr);exit(4);}

    /* the whole file is now loaded in the pFile2. */

    //terminate
    fclose(pFile1);
    fclose(pFile2);
    free(buffer);
    return 0;
}

