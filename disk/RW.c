#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 4096;
const int FILE_SIZE = 2000000;
const int OFFSET = 4096;

void readBlock(FILE* disk, int blockNum, char* buffer){
        disk = fopen("vdisk", "w+b");
        fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
        fread(buffer, BLOCK_SIZE, 1, disk);
        fclose(disk);
}

void writeBlock(FILE* disk, int blockNum, char* data){
        disk = fopen("vdisk", "w+b");
        fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
        fwrite(data, BLOCK_SIZE, 1, disk); // will overwrite 
        fclose(disk);  
}

void CreateDisk(){
    remove("vdisk");
    FILE *fp = fopen("vdisk", "w");
    fseek(fp, FILE_SIZE -1 , SEEK_SET);
    fputc('\0', fp);
    fclose(fp);
}

int main(int argc, char* argv[]) {
    printf("attempting");
    CreateDisk();
    FILE* disk = fopen("vdisk", "wb"); // Open the file to be written to in binary mode
    writeBlock(disk, 2, "Hello world!");
    fclose(disk);
    printf("disk created");
    printf("blach blach");

    disk = fopen("vdisk", "w+b"); 
    char* buffer = malloc(sizeof(char) * BLOCK_SIZE * 3);
    readBlock(disk, 2, buffer);
    //printf("%s", buffer);
    for (int i = 0; i < BLOCK_SIZE; i++){
        printf("%2x ", buffer[i]);
    }
    fclose(disk);
    return 0;
}