#include <stdio.h>
 
int main(void) {
	int x, y;
	char op;
 
	printf("***************** \n");	
	printf("A----Add \n");
	printf("S----Subtract \n");
	printf("M----Multiply \n");
	printf("D----Divide \n");
	printf("Q----Quit \n");
	printf("***************** \n");
 
	printf("연산을 선택하세요 : ");		
 
	do	
        {
		scanf_s("%c", &op);
        
		if (op == 'A') {
			printf("두수를 공백으로 분리하여 입력하세요 : ");
			scanf_s("%d %d", &x, &y);	
			printf("연산의 값은 %d입니다. \n", x + y);
 
			printf("연산을 선택하세요 : ");
		}
        
		if (op == 'S') {
			printf("두수를 공백으로 분리하여 입력하세요 : ");
			scanf_s("%d %d", &x, &y);	
			printf("연산의 값은 %d입니다. \n", x - y);			
 
			printf("연산을 선택하세요 : ");
		}
        
		if (op == 'M')	{
			printf("두수를 공백으로 분리하여 입력하세요 : ");	
			scanf_s("%d %d", &x, &y);	
			printf("연산의 값은 %d입니다. \n", x * y);	
 
			printf("연산을 선택하세요 : ");
		}
        
		if (op == 'D') {
			printf("두수를 공백으로 분리하여 입력하세요 : ");
			scanf_s("%d %d", &x, &y);									
			printf("연산의 값은 %d입니다. \n", x / y);
 
			printf("연산을 선택하세요 : ");
		}
        
		if (op == 'Q')	
			break;
	} while (1);
 
	return 0;
}
