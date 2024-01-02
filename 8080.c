#include <stdio.h>
#include <stdlib.h>

int disassembler8080(unsigned char *codebuffer, int pc) {
    unsigned char *code = &codebuffer[pc]; 
    int opbytes = 1;
    printf("%04x\t", pc); // program counter's address in memory'

    switch (*code) {
	default:
	    printf("Unknown instruction: 0x%02x", *code);
	    break;
        case 0x00:
	    printf("NOP");
            break;
        case 0x01:
            printf("LXI\tB, #$0x%02x%02x", code[2], code[1]);
	    opbytes = 3;
            break;
    	case 0x02:
	    printf("STAX\tB");
	    break;
    }
    
    printf("\n");

    return opbytes;
}

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "rb");

    if (f == NULL) {
	printf("Error: %s not found.\n", argv[1]);
    	exit(1);
    }
    
    fseek(f, 0, SEEK_END); // file pointer set to the end of the file
    int fsize = ftell(f); // store file size
    printf("Size of entered file is: %ld\n", ftell(f));
    fseek(f, 0, SEEK_SET); // file pointer set back to the begining of the file
    
    unsigned char *codebuffer = malloc(fsize);
    fread(codebuffer, fsize, 1, f);

    // printf("%s there \n", codebuffer);

    fclose(f);

    int pc = 0;
    while (pc < fsize) {
	pc += disassembler8080(codebuffer, pc);
    }
    
    free(codebuffer);
    return 0;
}
