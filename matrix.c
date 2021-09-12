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
    char command; // �޴� �Է°� 
    printf("[----- [Jegal Dohyun]  [2018038018] -----]\n");

    int row, col;
    srand(time(NULL)); // �ߺ��� ���� ���� ���� 

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    
    int** matrix_a = create_matrix(row, col); 
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row); // 2���� �迭 a, b, a_t ���� 

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) // �迭 ���� ������ ã�� ��ó�� �˻� 
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
            	fill_data(matrix_b, row, col); // �迭 a,b�� ���� ������ �Ҵ� 
            	break;
            	
        	case 'p': case 'P':
            	printf("Print matrix\n");
            	printf("matrix_a\n");
            	print_matrix(matrix_a, row, col);
            	printf("matrix_b\n");
            	print_matrix(matrix_b, row, col); // �迭 a,b�� ���� ��� 
            	break;
            	
        	case 'a': case 'A':
        	    printf("Add two matrices\n");
            	addition_matrix(matrix_a, matrix_b, row, col); // �� �迭�� ���� ��� 
            	break;
            	
        	case 's': case 'S':
           		printf("Subtract two matrices \n");
            	subtraction_matrix(matrix_a, matrix_b, row, col); // �� �迭�� ���� ��� 
            	break;
            	
        	case 't': case 'T':
            	printf("Transpose matrix_a \n");
            	printf("matrix_a_t\n");
            	transpose_matrix(matrix_a, matrix_a_t, col, row); // �迭 a�� ��ġ��� a_t�� ��� 
            	print_matrix(matrix_a_t, col, row);
            	break;
            	
        	case 'm': case 'M':
            	printf("Multiply matrix_a with transposed matrix_a \n");
            	transpose_matrix(matrix_a, matrix_a_t, col, row);
            	multiply_matrix(matrix_a, matrix_a_t, row, col); // �迭 a�� a_t�� ���� ��� 
            	break;
            	
        	case 'q': case 'Q':
            	printf("Free all matrices..\n");
            	free_matrix(matrix_a_t, col, row);
            	free_matrix(matrix_a, row, col);
            	free_matrix(matrix_b, row, col); // free�� ���� �޸� �Ҵ� ���� 
            	break;
            	
        	default:
            	printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // �̿��� ���� ������ �����޼��� ��� 
            	break;
        }
    } while(command != 'q' && command != 'Q'); // ���� �޴� �Է� �� ���� �ݺ� 
    
    return 1;
}

int** create_matrix(int row, int col){
	int **x, i;
	
	if(row <= 0 || col <=0) {
		printf("Check the sizes of row and col!\n");  // �迭 ���� ������ ã�� ��ó�� �˻� 
		return NULL;
	}
	
	x = (int **)malloc(sizeof(int*)*row); // malloc() �Լ��� ���� �ּҸ� ��� int�� �迭�� row ��ŭ ����  
	for(i=0; i<row; i++)
		x[i] = (int *)malloc(sizeof(int)*col); // malloc() �Լ��� ���� ������ �迭 x�� ���� ��� int�� �迭�� col ��ŭ ���� 
	
	if(x == NULL) {
		printf("Check the sizes of row and col!\n"); // �迭 ���� ������ ã�� ��ó�� �˻� 
		return NULL;
	}
	
	return x;
}

void print_matrix(int** matrix, int row, int col){
	int i,j;
	
	for(i=0; i<row; i++){
		for(j=0; j<col; j++)
			printf("%d\t",matrix[i][j]); // ���� for���� ���� �迭�� ��� ���� �������� ���� ��� 
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
        free(matrix[i]); // free()�Լ��� ���� ���� ��� int�� �迭�� �Ҵ� ���� 
    }
    free(matrix); // ���� �ּҸ� ��� int�� �迭�� �Ҵ� ���� 
    
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
			matrix[i][j] = rand()%20; // �迭�� 0~19�� �������� ���� 
	}
	
	if(matrix == NULL) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	return 1;
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col){
	int **matrix_sum = create_matrix(row, col); // �迭�� ���� �����ϱ� ���� �迭 ���� 
	int i,j;
	
	if(row <= 0 || col <=0) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	for(i=0; i<row; i++){
		for(j=0; j<col; j++) 
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; // �迭 a, b�� ���� �迭 sum�� ���� 
	}
	print_matrix(matrix_sum, row, col);
	
	if(matrix_sum == NULL) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	free_matrix(matrix_sum, row, col); // �޸� ���� ������ ���� �Ҵ� ���� 
	
	return 1;
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col){
	int **matrix_sub = create_matrix(row, col); // �迭�� ���� �����ϱ� ���� �迭 ����
	int i,j;
	
	if(row <= 0 || col <=0) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	for(i=0; i<row; i++){
		for(j=0; j<col; j++) 
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; // �迭 a, b�� ���� �迭 sub�� ���� 
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
		for(j=0; j<row; j++)  // �迭 a�� ��ġ����̹Ƿ� �迭 a_t�� ũ��� col x row�� �ȴ�. 
			matrix_t[i][j] = matrix[j][i]; // ��ġ����� �� ����  
	}
	
	if(matrix_t == NULL) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	return 1;
}

int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col){
	int **matrix_axt = create_matrix(row, row); // �迭 a�� a_t�� ���� �����ϱ� ���� �迭 ����, �迭�� ũ��� (�迭 a�� �� ũ�� row) x (�迭 a_t�� �� ũ�� row) 
	int i,j,k, result;
	
	if(row <= 0 || col <=0) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	
	for(i=0; i<row; i++){
        for(j=0; j<row; j++){
        	result = 0; // result�� 0���� �ʱ�ȭ 
        	
            for(k=0; k<col; k++) // k�� ���� �迭 a�� ���� �迭 a_t�� �� ��ġ�� ����
                result += matrix_a[i][k] * matrix_t[k][j]; // ���� ����� result�� ���� 
                
            matrix_axt[i][j] = result; // result�� ���� �迭 atx�� ���� 
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

