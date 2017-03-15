/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/asm.h"

int main(int argc, char *argv[])
{
	char buf[256], line[256];
	int addMem[sizeRAM];
	FILE *input, *output;
	int value, addr, lineCnt = 1;
	int err;

	if (argc != 3) {
		exit(1);
	}
	if (testArgv(argv) != 0) {
		exit(1);
	}
	if ((output = fopen(argv[1], "wb")) == NULL) {
		exit(1);
	}
	if ((input = fopen(argv[2], "rb")) == NULL) {
		exit(1);
	}
	
	memset(addMem, 0, sizeRAM * sizeof(int));
	while (fgets(line, 256, input)) {
		strcpy(buf, line);
		err = parsingLine(buf, &addr, &value);
		if (err == 0) {
              addMem[addr] = value;
		}
		else if (err < 0) {
			err = 1;
		}
		lineCnt++;
	}
	if (err == 0) {
		fwrite(addMem,  sizeof(int) * sizeRAM, 1, output);
	}
	fclose(input);
	fclose(output);
	return 0;
}
