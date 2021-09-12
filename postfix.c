#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10 // ������ �ִ� ũ�� ���� 
#define MAX_EXPRESSION_SIZE 20 // �Է¹��� �� �ִ� ������ �ִ� ũ�� 

typedef enum{
	lparen = 0, 
	rparen = 9, 
	times = 7, 
	divide = 6, 
	plus = 5,   
	minus = 4,   
	operand = 1
} precedence; // �������� �켱������ ���ϴ� ������ 

char infixExp[MAX_EXPRESSION_SIZE];   	
char postfixExp[MAX_EXPRESSION_SIZE]; // ����ǥ��İ� ����ǥ����� ������ �������� 
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];	// ����ǥ��İ� ���� ��꿡 ���Ǵ� ������ ������ �������� 

int postfixStackTop = -1;  
int evalStackTop = -1;	// ����ǥ��İ� ���� ��� ������ top�� ǥ���� �������� 

int evalResult = 0;	  // ����ǥ����� ���� ������ �������� 

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main(){
	char command;

	printf("[----- [Jegal Dohyun] [2018038018] -----]\n\n");
	
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix(); // ����ǥ����� �Է¹޴� �Լ� 
			break;
		case 'p': case 'P':
			toPostfix(); // �Է¹��� ����ǥ����� ����ǥ������� ��ȯ�ϴ� �Լ� 
			break;
		case 'e': case 'E':
			evaluation(); // ��ȯ�� ����ǥ����� ���� ����ϴ� �Լ� 
			break;
		case 'd': case 'D':
			debug(); // ����ǥ��İ� ��ȯ�� ����ǥ���, ��� ���� ��� ǥ���ϴ� �Լ� 
			break;
		case 'r': case 'R':
			reset(); // �ʱ�ȭ 
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");  // �̿��� ���� �ԷµǸ� �����޼��� ���
			break;
		}

	}while(command != 'q' && command != 'Q'); // q �Է� �� ���� �޴� �ݺ� ���

	return 1;
}

void postfixPush(char x){
    postfixStack[++postfixStackTop] = x; // X�� ����ǥ����� ���� top�� ������Ų ���� ���ÿ� ���� 
}

char postfixPop(){
    char x;
    if(postfixStackTop == -1) // ������ top ���� �ʱ� ����, �� ������ ����ִٸ� '\0' ��ȯ 
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; // x�� ������ top�� ��ġ�� ������ ���� ���� �� top ���� 
    }
    return x;
}

void evalPush(int x){
    evalStack[++evalStackTop] = x; // x�� ����ǥ��� ��� ������ top���� ������Ų ��  top�� ��ġ�� ��� ���ÿ� ���� 
}

int evalPop(){
    if(evalStackTop == -1) // ������ top ���� �ʱ� ����, �� ������ ����ִٸ� -1 ��ȯ 
        return -1;
    else
        return evalStack[evalStackTop--]; // ������ top�� ��ġ�� ������ ���� ��ȯ �� top ���� 
}

void getInfix(){
    printf("Type the expression >>> ");
    scanf("%s",infixExp); // ����ǥ����� infixExp�� ���� 
}

precedence getToken(char symbol){
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand; // �Է¹��� ���ڰ� � ���������� �˱� ������ ���� ������ ������ ������ ���� 
	}
}

precedence getPriority(char x){
	return getToken(x); // x�� getToken���� �����Ͽ� �켱������ �� �� �ִ�. 
}

void charCat(char* c){
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1); // c�� ���ڿ��� ����ǥ��� ���ڿ��� 1���ڸ� ���� 
}

void toPostfix(){
	char *exp = infixExp; // ����ǥ����� �ּҸ� exp�� ���� 
	char x,y; // ����ǥ����� ���ڸ� ���� x ������ �ӽú��� y ���� 

	while(*exp != '\0'){ // ����ǥ����� ���� ���޽ñ��� �ݺ� 
		x = *exp; 
		
		if(getPriority(x) == 1) // x�� �ǿ������� ��� 
			charCat(&x); // x�� ���� ����ǥ��� ���ڿ��� ���� 
		else if(getPriority(x) == 9){ // x�� ')' ��ȣ�� ��� 
			while(postfixStack[postfixStackTop] != '('){ // '('�� ���� �� ���� �ݺ� 
				y = postfixPop(); // ���� �����ڸ� y�� ���� �� pop 
				charCat(&y); // y�� ���� ����ǥ��� ���ڿ��� ���� 
			}
			postfixPop(); // ����ǥ��Ŀ� ������� �ʴ� ')' ��ȣ pop 
		}
		else if(getPriority(x) == 0){ // x�� '(' ��ȣ�� ��� 
				postfixPush(x++); // '(' ��ȣ�� push
		}
		else{
			while(getPriority(postfixStack[postfixStackTop]) >= getPriority(x)){ // ����ǥ����� �������� �켱������ ����ǥ��� ���ú��� ������ ���� �ݺ� 
				y = postfixPop();
				charCat(&y);
			}
			postfixPush(x); // �����ڸ� push
		}
		
	exp++; // exp�� �������� ���� ���ڷ� �̵� 
	}
	
	while(postfixStackTop > -1){ // ����ǥ����� ���κ� �ݺ� 
		y = postfixPop();
		charCat(&y);
	}
}

void debug(){
	int i;
	
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); 
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult); // ����ǥ���, ����ǥ���, ��� �� ��� 

	printf("postfixStack : ");
	for(i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); // ����ǥ����� ���ÿ� ����� ������ ��� 

	printf("\n");

}

void reset(){
	int i;
	
	infixExp[0] = '\0';
	postfixExp[0] = '\0'; 

	for(i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0; // ����ǥ��İ� ����ǥ����� ��� '\0'���� �ʱ�ȭ�ϰ� ������ top ��, ��� �� �ʱ�ȭ 
}

void evaluation(){
	char *exp=postfixExp; // ����ǥ����� �ּҸ� exp�� ���� 
	char x; // ����ǥ����� ���ڸ� ���� x ����
	int a,b; // �ǿ����ڸ� ���� ���� 
	
	while(*exp != '\0'){
		x = *exp;
			
		if(getPriority(x) == 1) 
			evalPush(x-48); // �ǿ������� ASCII�ڵ忡�� 48�� �� ���ڰ� ����ǰ� �� 
		else{
			a = evalPop(); // ���� ���� top�� ��ġ�� ���� a�� ���� 
			b = evalPop(); // ���� ���� top�� ��ġ�� ���� b�� ����
			
			switch(getPriority(x)){  
				case 5: 
					evalPush(b+a);
					break;
				case 4: 
					evalPush(b-a);// �����ڿ� ���� b�� a�� ����Ͽ� push
					break;
				case 7: 
					evalPush(b*a); // ���ÿ� ���� ����� ��� ������ �ڷ� ���Ƿ� b-a�÷� ��� 
					break;
				case 6: 
					evalPush(b/a);  
					break;
			}
		}
		exp++; // exp�� �������� ���� ���ڷ� �̵� 
	}
	evalResult = evalPop(); // ������ top�� ��ġ�� ������ ���� evalResult�� ����
}

