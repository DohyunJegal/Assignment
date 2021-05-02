#include <stdio.h>
 
int main(void) {
	char beep = '\a';
 
	printf("%c", beep);
	printf("(경보음) 화재가 발생하였습니다.\n");	
	printf("%c", beep);	
 
	return 0;
}
