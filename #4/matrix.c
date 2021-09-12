#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main(){
    char command; // 메뉴 입력값 
    printf("[----- [Jegal Dohyun]  [2018038018] -----]\n");

    int row, col;
    srand(time(NULL)); // 중복이 없는 난수 생성 

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    
    int** matrix_a = create_matrix(row, col); 
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row); // 2차원 배열 a, b, a_t 생성 

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) // 배열 값의 오류를 찾는 전처리 검사 
		return -1;

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");
        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        	case 'z': case 'Z':
            	printf("Matrix Initialized\n");
           		fill_data(matrix_a, row, col);
            	fill_data(matrix_b, row, col); // 배열 a,b의 값을 난수로 할당 
            	break;
            	
        	case 'p': case 'P':
            	printf("Print matrix\n");
            	printf("matrix_a\n");
            	print_matrix(matrix_a, row, col);
            	printf("matrix_b\n");
            	print_matrix(matrix_b, row, col); // 배열 a,b의 값을 출력 
            	break;
            	
        	case 'a': case 'A':
        	    printf("Add two matrices\n");
            	addition_matrix(matrix_a, matrix_b, row, col); // 두 배열의 합을 출력 
            	break;
            	
        	case 's': case 'S':
           		printf("Subtract two matrices \n");
            	subtraction_matrix(matrix_a, matrix_b, row, col); // 두 배열의 차를 출력 
            	break;
            	
        	case 't': case 'T':
            	printf("Transpose matrix_a \n");
            	printf("matrix_a_t\n");
            	transpose_matrix(matrix_a, matrix_a_t, col, row); // 배열 a의 전치행렬 a_t를 계산 
            	print_matrix(matrix_a_t, col, row);
            	break;
            	
        	case 'm': case 'M':
            	printf("Multiply matrix_a with transposed matrix_a \n");
            	transpose_matrix(matrix_a, matrix_a_t, col, row);
            	multiply_matrix(matrix_a, matrix_a_t, row, col); // 배열 a와 a_t의 곱을 출력 
            	break;
            	
        	case 'q': case 'Q':
            	printf("Free all matrices..\n");
            	free_matrix(matrix_a_t, col, row);
            	free_matrix(matrix_a, row, col);
            	free_matrix(matrix_b, row, col); // free를 통해 메모리 할당 해제 
            	break;
            	
        	default:
            	printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 이외의 값이 나오면 오류메세지 출력 
            	break;
        }
    } while(command != 'q' && command != 'Q'); // 종료 메뉴 입력 전 까지 반복 
    
    return 1;
}

int** create_matrix(int row, int col){
	int **x, i;
	
	if(row <= 0 || col <=0) {
		printf("Check the sizes of row and col!\n");  // 배열 값의 오류를 찾는 전처리 검사 
		return NULL;
	}
	
	x = (int **)malloc(sizeof(int*)*row); // malloc() 함수를 통해 주소를 담는 int형 배열을 row 만큼 생성  
	for(i=0; i<row; i++)
		x[i] = (int *)malloc(sizeof(int)*col); // malloc() 함수를 통해 생성한 배열 x에 값을 담는 int형 배열을 col 만큼 생성 
	
	if(x == NULL) {
		printf("Check the sizes of row and col!\n"); // 배열 값의 오류를 찾는 후처리 검사 
		return NULL;
	}
	
	return x;
}

void print_matrix(int** matrix, int row, int col){
	int i,j;
	
	for(i=0; i<row; i++){
		for(j=0; j<col; j++)
			printf("%d\t",matrix[i][j]); // 이중 for문을 통해 배열의 행과 열을 증가시켜 값을 출력 
	printf("\n");
	}
}


int free_matrix(int** matrix, int row, int col){
	int i;
	
	if(row <= 0 || col <=0) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	for(i=0; i<row; i++){
        free(matrix[i]); // free()함수를 통해 값을 담는 int형 배열을 할당 해제 
    }
    free(matrix); // 이후 주소를 담는 int형 배열을 할당 해제 
    
    if(matrix == NULL) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	return 1;
}

int fill_data(int** matrix, int row, int col){
	int i,j;
	
	if(row <= 0 || col <=0) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	for(i=0; i<row; i++){
		for(j=0; j<col; j++) 
			matrix[i][j] = rand()%20; // 배열에 0~19의 난수값을 대입 
	}
	
	if(matrix == NULL) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	return 1;
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col){
	int **matrix_sum = create_matrix(row, col); // 배열의 합을 저장하기 위한 배열 생성 
	int i,j;
	
	if(row <= 0 || col <=0) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	for(i=0; i<row; i++){
		for(j=0; j<col; j++) 
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; // 배열 a, b의 합을 배열 sum에 저장 
	}
	print_matrix(matrix_sum, row, col);
	
	if(matrix_sum == NULL) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	free_matrix(matrix_sum, row, col); // 메모리 누수 방지를 위해 할당 해제 
	
	return 1;
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col){
	int **matrix_sub = create_matrix(row, col); // 배열의 차를 저장하기 위한 배열 생성
	int i,j;
	
	if(row <= 0 || col <=0) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	for(i=0; i<row; i++){
		for(j=0; j<col; j++) 
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; // 배열 a, b의 차를 배열 sub에 저장 
	}
	print_matrix(matrix_sub, row, col);
	
	if(matrix_sub == NULL) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	free_matrix(matrix_sub, row, col);
	
	return 1;
}

int transpose_matrix(int** matrix, int** matrix_t, int col, int row){
	int i,j;
	
	if(row <= 0 || col <=0) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	for(i=0; i<col; i++){ 
		for(j=0; j<row; j++)  // 배열 a의 전치행렬이므로 배열 a_t의 크기는 col x row가 된다. 
			matrix_t[i][j] = matrix[j][i]; // 전치행렬의 값 대입  
	}
	
	if(matrix_t == NULL) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	return 1;
}

int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col){
	int **matrix_axt = create_matrix(row, row); // 배열 a와 a_t의 곱을 저장하기 위한 배열 생성, 배열의 크기는 (배열 a의 행 크기 row) x (배열 a_t의 열 크기 row) 
	int i,j,k, result;
	
	if(row <= 0 || col <=0) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	for(i=0; i<row; i++){
        for(j=0; j<row; j++){
        	result = 0; // result를 0으로 초기화 
        	
            for(k=0; k<col; k++) // k를 통해 배열 a의 열과 배열 a_t의 행 위치를 증가
                result += matrix_a[i][k] * matrix_t[k][j]; // 곱의 결과를 result에 저장 
                
            matrix_axt[i][j] = result; // result의 값을 배열 atx에 저장 
    	}
	}
    	
    print_matrix(matrix_axt, row, row);
	
	if(matrix_axt == NULL) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	free_matrix(matrix_axt, row, row); 
	
	return 1;
}

