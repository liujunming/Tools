#include <stdio.h>

asm (".pushsection .text, \"ax\" \n"
     ".globl bin_entry \n"
     "bin_entry: \n"
     ".incbin \"./hello.bin\" \n"
     ".popsection"
);

extern void bin_entry(void);
int main(int argc, char *argv[])
{
	bin_entry();
	return 0;
}
