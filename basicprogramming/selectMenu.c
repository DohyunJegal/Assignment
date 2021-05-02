	#include <stdio.h> 		
 
void print_menu();
int input_num(int n);
void check_menu_num(int n);
void main_menu(int n);
void menu_1();
void menu_2();
void menu_3();
 
void main() {
	int n=0; 
 
	print_menu(); 
 
	for (;;) {
		n = input_num(n); 	
		check_menu_num(n); 
		main_menu(n); 
        
		if (n == 4) 
			break;
	}
}
 
void print_menu() {
	printf("1. 햄버거 \n2. 치즈버거 \n3. 샌드위치\n4. 종료\n"); 					
}
 
int input_num(int n) {
	printf("원하는 메뉴를 선택하세요 : ");  
	scanf_s("%d", &n); 
    
	return n; 
}
 
void check_menu_num(int n) {
	if (n > 4 || n < 1) {
		print_menu();
	}
}
 
void main_menu(int n) {
	if (n == 1) 
		menu_1(); 	
	else if (n == 2) 
		menu_2();
	else if (n == 3)
		menu_3();
}
 
void menu_1() {
	printf("1번 메뉴가 선택되었습니다. \n\n"); 
}
 
void menu_2() {
	printf("2번 메뉴가 선택되었습니다. \n\n"); 
}
 
void menu_3() {
	printf("3번 메뉴가 선택되었습니다. \n\n");
}
