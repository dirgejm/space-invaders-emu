#include <stdio.h>
#include <stdlib.h>

int disassembler8080(unsigned char *codebuffer, int pc) {
    unsigned char *opcode = &codebuffer[pc]; 
    int opbytes = 1;
    printf("%04x\t", pc); // program counter's address in memory

    switch (*opcode) {
	default:
	    	printf("Unknown instruction: 0x%02x", *opcode); break;
        case 0x00:
	    	printf("NOP"); break;
        case 0x01:
	    	printf("Full opcode variable:\t");
		for (int i = 0; i < 3; i++) {
			printf("%02x", opcode[i]);
		}
            	printf("\nLXI\tB, #$0x%02x%02x", opcode[2], opcode[1]); opbytes = 3; break;
    	case 0x02:
	    	printf("STAX\tB"); break;
    	case 0x03:
	    	printf("INX\tB"); break;
	case 0x04:
		printf("INR\tB"); break;
	case 0x05:
		printf("DCR\tB"); break;
	case 0x06:
		printf("MVI\tB, #$0x%02x", opcode[1]); opbytes = 2; break;
	case 0x07:
		printf("RLC"); break;
	case 0x08:
		printf("NOP"); break;
	case 0x09:
		printf("DAD\tB"); break;
	case 0x0a:
		printf("LDAX\tB"); break;
	case 0x0b:
		printf("DCX\tB"); break;
	case 0x0c:
		printf("INR\tC"); break;
	case 0x0d:
		printf("DCR\tC"); break;
	case 0x0e:
		printf("MVI\tC, #$0x%02x", opcode[1]); opbytes = 2; break;
	case 0x0f:
		printf("RRC"); break;  
	case 0x10:
		printf("NOP"); break;
	case 0x11:
		printf("LXI\tD, #$0x%02x%02x", opcode[2], opcode[1]); opbytes = 3; break;
	case 0x12:
		printf("STAX\tD"); break;
	case 0x13:
		printf("INX\tD"); break;
	case 0x14:
		printf("INR\tD"); break;
	case 0x15:
		printf("DCR\tD"); break;
	case 0x16:
		printf("MVI\tD, #$0x%02x", opcode[1]); opbytes = 2; break;
	case 0x17:
		printf("RAL"); break;
	case 0x18:
		printf("NOP"); break;
	case 0x19:
		printf("DAD\tD"); break;
	case 0x1a:
		printf("LDAX\tD"); break;
	case 0x1b:
		printf("DCX\tD"); break;
	case 0x1c:
		printf("INR\tE"); break;
	case 0x1d:
		printf("DCR\tE"); break;
	case 0x1e:
		printf("MVI\tE, #$0x%02x", opcode[1]); opbytes = 2; break;
	case 0x1f:
		printf("RAR"); break;
	case 0x20:
		printf("NOP"); break;
	case 0x21:
		printf("LXI\tH, #$0x%02x%02x", opcode[2], opcode[1]); opbytes = 3; break;
	case 0x22:
		printf("SHLD, #$%02x%02x", opcode[2], opcode[1]); opbytes = 3; break;
	case 0x23:
		printf("INX\tH"); break;
	case 0x24:
		printf("INR\tH"); break;
	case 0x25:
		printf("DCR\tH"); break;
	case 0x26:
		printf("MVI\tH, #$0x%02x", opcode[1]); opbytes = 2; break;
	case 0x27:
		printf("DAA"); break;
	case 0x28:
		printf("NOP"); break;
	case 0x29:
		printf("DAD\tH"); break;
	case 0x2a:
		printf("LHLD, #$%02x%02x", opcode[2], opcode[1]); opbytes = 3; break;
	case 0x2b:
		printf("DCX\tH"); break;
	case 0x2c:
		printf("INR\tL"); break;
	case 0x2d:
		printf("DCR\tL"); break;
	case 0x2e:
		printf("MVI\tL, #$0x%02x", opcode[1]); opbytes = 2; break;
	case 0x2f:
		printf("CMA"); break;
	case 0x30:
		printf("NOP"); break;
	// 31...
	
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

    fclose(f);

    int pc = 0;
    while (pc < fsize) {
	pc += disassembler8080(codebuffer, pc);
    }
    
    free(codebuffer);
    return 0;
}
