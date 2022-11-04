#include<stdio.h>
#include<math.h>
#include<string.h>
int main() {
	unsigned val = 0x59b997fa;
	printf("val hex is %x\n", val);
	char buf[40];
	sprintf(buf, "%.8x", val);
	puts(buf);
	char* t ;
	strncmp(buf, t, 2);
	int *s = (int*)buf;
	printf("%x\n", *s);
	s++;
	printf("%x\n", *s);
	return 0;
}
