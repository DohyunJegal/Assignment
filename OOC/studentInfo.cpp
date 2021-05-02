#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;


typedef struct{
	char SubName[30];
	int Hakjum; 
	char Grade[10];
	float GPA;
}Subject;

typedef struct{
	char StdName[30];
	int Hakbun; 
	Subject Sub[3]; 
	float AveGPA; 
}Student;

int input_num(int);
int input_data(Student *, int *);
int output_data (Student *);
float cal_GPA (int, char *);

int main(void){
	int num, order=1;
	bool break_num = false;
	Student infoA, infoB;
	
	for(;;){
		do
			num = input_num(num);
		while (num!=1 && num!=2 && num!=3);
	
		switch(num){
			case 1:
				input_data(&infoA, &order);
				input_data(&infoB, &order);
				
				break;
			case 2:
				output_data(&infoA);
				output_data(&infoB);
				
				break;
			case 3:
				break_num = true;
				break;
		}
		
	if (break_num == true)
		break;
	}
}

int input_num (int x){
	cout << "===== 메뉴 ===== \n"; 
	cout << "1. 학생 성적 입력 \n";
	cout << "2. 전체 학생 성적 보기 \n";
	cout << "3. 프로그램 종료 \n\n";
	cout << "원하시는 기능을 입력하세요 : ";
	
	cin >> x;
	
	return x;
}

int input_data (Student *A, int *x){
	int i;
	float addGPA=0;
	
	cout << "\n*" << *x <<"번 째 학생의 이름과 학번을 입력하세요. \n";
	cout << "이름 : ";
	cin >> A->StdName;
	cout << "학번 : ";
	cin >> A->Hakbun;
	cout << "\n";
	
	cout << "\n * 수강한 과목 3개와 각 교과목명, 과목학점, 과목등급을 입력하세요. \n";
	for(i=0; i<3; i++){
		cout << "교과목명 : ";
		cin >> A->Sub[i].SubName;
		cout << "과목학점 : ";
		cin >> A->Sub[i].Hakjum;
		cout << "과목등급 (A+ ~ F) : ";
		cin >> A->Sub[i].Grade;
		cout << "\n";
		
		A->Sub[i].GPA = cal_GPA(A->Sub[i].Hakjum, A->Sub[i].Grade);
		addGPA += A->Sub[i].GPA;
	}
	
	A->AveGPA = addGPA/3.0;
	
	(*x)++;
	return 0;
}

int output_data (Student *A){
	int i;
	
	cout.precision(2);
	cout << fixed;

	cout.width(10);
	cout <<"이름 : " << A->StdName;
	cout.width(10);	
	cout <<"학번 : " << A->Hakbun << "\n";
	
	cout << "================================================\n";
	cout << "과목명    과목학점    과목등급    과목평점\n";
	cout << "================================================\n";
	
	for(i=0;i<3;i++){
	cout.width(10);	
	cout << A->Sub[i].SubName << "\t" << A->Sub[i].Hakjum << "\t" <<  A->Sub[i].Grade << "\t" <<  A->Sub[i].GPA << "\n";
	}
	cout << "================================================\n";
	cout << "\t\t\t\t 평균평점 : " << A->AveGPA << "\n\n";
	
	return 0;
}

float cal_GPA (int x, char *y){
	float score;
	
	if (strcmp(y, "A+") == 0)
		score = 4.5;
	else if (strcmp(y, "A") == 0 || strcmp(y, "A0") == 0)
		score = 4.0;
	else if (strcmp(y, "B+") == 0)
		score = 3.5;
	else if (strcmp(y, "B") == 0 || strcmp(y, "B0") == 0)
		score = 3.0;
	else if (strcmp(y, "C+") == 0)
		score = 2.5;
	else if (strcmp(y, "C") == 0 || strcmp(y, "C0") == 0)
		score = 2.0;
	else if (strcmp(y, "D+") == 0)
		score = 1.5;
	else if (strcmp(y, "D") == 0 || strcmp(y, "D0") == 0)
		score = 1.0;
	else
		score = 0;
	
	return score*x;
}
