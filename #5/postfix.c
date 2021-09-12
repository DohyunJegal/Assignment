#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10 // 스택의 최대 크기 정의 
#define MAX_EXPRESSION_SIZE 20 // 입력받을 수 있는 연산의 최대 크기 

typedef enum{
	lparen = 0, 
	rparen = 9, 
	times = 7, 
	divide = 6, 
	plus = 5,   
	minus = 4,   
	operand = 1
} precedence; // 연산자의 우선순위를 정하는 열거형 

char infixExp[MAX_EXPRESSION_SIZE];   	
char postfixExp[MAX_EXPRESSION_SIZE]; // 중위표기식과 후위표기식을 저장할 전역변수 
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];	// 후위표기식과 값의 계산에 사용되는 스택을 저장할 전역변수 

int postfixStackTop = -1;  
int evalStackTop = -1;	// 후위표기식과 값의 계산 스택의 top을 표현할 전역변수 

int evalResult = 0;	  // 후위표기식의 값을 저장할 전역변수 

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
			getInfix(); // 중위표기식을 입력받는 함수 
			break;
		case 'p': case 'P':
			toPostfix(); // 입력받은 중위표기식을 후위표기식으로 변환하는 함수 
			break;
		case 'e': case 'E':
			evaluation(); // 변환한 후위표기식의 값을 계산하는 함수 
			break;
		case 'd': case 'D':
			debug(); // 중위표기식과 변환한 후위표기식, 계산 값을 모두 표시하는 함수 
			break;
		case 'r': case 'R':
			reset(); // 초기화 
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");  // 이외의 값이 입력되면 오류메세지 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); // q 입력 전 까지 메뉴 반복 출력

	return 1;
}

void postfixPush(char x){
    postfixStack[++postfixStackTop] = x; // X를 후위표기식의 스택 top을 증가시킨 값의 스택에 저장 
}

char postfixPop(){
    char x;
    if(postfixStackTop == -1) // 스택의 top 값이 초기 상태, 즉 스택이 비어있다면 '\0' 반환 
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; // x에 스택의 top이 위치한 스택의 값을 저장 후 top 감소 
    }
    return x;
}

void evalPush(int x){
    evalStack[++evalStackTop] = x; // x를 후위표기식 계산 스택의 top값을 증가시킨 후  top이 위치한 계산 스택에 저장 
}

int evalPop(){
    if(evalStackTop == -1) // 스택의 top 값이 초기 상태, 즉 스택이 비어있다면 -1 반환 
        return -1;
    else
        return evalStack[evalStackTop--]; // 스택의 top이 위치한 스택의 값을 반환 후 top 감소 
}

void getInfix(){
    printf("Type the expression >>> ");
    scanf("%s",infixExp); // 중위표기식을 infixExp에 저장 
}

precedence getToken(char symbol){
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand; // 입력받은 문자가 어떤 연산자인지 알기 쉽도록 사전 정의한 열거형 값으로 리턴 
	}
}

precedence getPriority(char x){
	return getToken(x); // x를 getToken으로 전달하여 우선순위를 알 수 있다. 
}

void charCat(char* c){
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1); // c의 문자열을 후위표기식 문자열에 1글자만 복사 
}

void toPostfix(){
	char *exp = infixExp; // 중위표기식의 주소를 exp에 담음 
	char x,y; // 중위표기식의 문자를 담을 x 변수와 임시변수 y 생성 

	while(*exp != '\0'){ // 중위표기식의 끝에 도달시까지 반복 
		x = *exp; 
		
		if(getPriority(x) == 1) // x가 피연산자인 경우 
			charCat(&x); // x의 값을 후위표기식 문자열에 복사 
		else if(getPriority(x) == 9){ // x가 ')' 괄호인 경우 
			while(postfixStack[postfixStackTop] != '('){ // '('를 만날 때 까지 반복 
				y = postfixPop(); // 만난 연산자를 y에 저장 후 pop 
				charCat(&y); // y의 값을 후위표기식 문자열에 복사 
			}
			postfixPop(); // 후위표기식에 사용하지 않는 ')' 괄호 pop 
		}
		else if(getPriority(x) == 0){ // x가 '(' 괄호인 경우 
				postfixPush(x++); // '(' 괄호를 push
		}
		else{
			while(getPriority(postfixStack[postfixStackTop]) >= getPriority(x)){ // 중위표기식의 연산자의 우선순위가 후위표기식 스택보다 낮을때 까지 반복 
				y = postfixPop();
				charCat(&y);
			}
			postfixPush(x); // 연산자를 push
		}
		
	exp++; // exp를 증가시켜 다음 글자로 이동 
	}
	
	while(postfixStackTop > -1){ // 후위표기식의 전부분 반복 
		y = postfixPop();
		charCat(&y);
	}
}

void debug(){
	int i;
	
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); 
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult); // 중위표기식, 후위표기식, 계산 값 출력 

	printf("postfixStack : ");
	for(i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); // 후위표기식의 스택에 저장된 연산자 출력 

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
	evalResult = 0; // 중위표기식과 후위표기식을 모두 '\0'으로 초기화하고 스택의 top 값, 계산 값 초기화 
}

void evaluation(){
	char *exp=postfixExp; // 후위표기식의 주소를 exp에 담음 
	char x; // 중위표기식의 문자를 담을 x 변수
	int a,b; // 피연산자를 담을 변수 
	
	while(*exp != '\0'){
		x = *exp;
			
		if(getPriority(x) == 1) 
			evalPush(x-48); // 피연산자의 ASCII코드에서 48을 빼 숫자가 저장되게 함 
		else{
			a = evalPop(); // 현재 스택 top이 위치한 값을 a에 저장 
			b = evalPop(); // 이후 스택 top이 위치한 값을 b에 저장
			
			switch(getPriority(x)){  
				case 5: 
					evalPush(b+a);
					break;
				case 4: 
					evalPush(b-a);// 연산자에 따라 b와 a를 계산하여 push
					break;
				case 7: 
					evalPush(b*a); // 스택에 먼저 저장된 경우 순서가 뒤로 가므로 b-a꼴로 계산 
					break;
				case 6: 
					evalPush(b/a);  
					break;
			}
		}
		exp++; // exp를 증가시켜 다음 글자로 이동 
	}
	evalResult = evalPop(); // 스택의 top이 위치한 스택의 값을 evalResult에 저장
}

