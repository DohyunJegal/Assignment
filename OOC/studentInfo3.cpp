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

void PrintMenu();
void inputData(Student *, int *);
void CalcGPA(Subject&);
float CalcAveGPA(Subject *);
void PrintOneData(const Student&);
void PrintAllData(const Student*, int);
Student* StdSearch(Student *, int);
inline void InputValue(char *str);
inline void InputValue(int &i);
void PrintAllStdList(const Student *, int);
void Modify(Student *) ;

int main(void){
	int num, i, j, StudentNum;
	bool break_num = false;
	Student std[2];
	Student* SearchStd;
		
	for(;;){
		do{
			PrintMenu();
			InputValue(num);
		} while (num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=6);
	
		switch(num){
			case 1:
				StudentNum = 0;
				
				inputData(&std[0], &StudentNum);
				inputData(&std[1], &StudentNum);
				
				for(i=0; i<StudentNum; i++){
					for(j=0; j<3; j++){
						CalcGPA(std[i].Sub[j]);
					}
					
					std[i].AveGPA = CalcAveGPA(std[i].Sub);
				}
				break;
				
			case 2:
				PrintAllData(std, StudentNum);
				break;
				
			case 3:
				SearchStd = StdSearch(std, StudentNum);
				if (SearchStd != NULL) 
					PrintOneData(*SearchStd);
				else
					cout << "\n학생을 찾을 수 없습니다. \n\n";
				break;
			
			case 4:
				PrintAllStdList(std, StudentNum);
				break;
			case 5:	
				SearchStd = StdSearch(std, StudentNum);
				if (SearchStd != NULL) 
					Modify(SearchStd);
				else
					cout << "\n학생을 찾을 수 없습니다. \n\n";
				break;
			case 6:
				break_num = true;
				break;
		}
		
	if (break_num == true)
		break;
	}
}

void PrintMenu(){
	cout << "\n===== 메뉴 ===== \n"; 
	cout << "1. 학생 성적 입력 \n";
	cout << "2. 전체 학생 성적 보기 \n";
	cout << "3. 학생 이름 검색 \n";
	cout << "4. 전체 학생 목록 보기\n";
	cout << "5. 학생 정보 수정 \n";
	cout << "6. 프로그램 종료 \n\n";
	cout << "원하시는 기능을 입력하세요 : ";
}

void inputData (Student *A, int *x){
	int i;
	(*x)++;
	
	cout << "\n*" << *x <<"번 째 학생의 이름과 학번을 입력하세요. \n";
	cout << "이름 : ";
	InputValue(A->StdName);
	cout << "학번 : ";
	InputValue(A->Hakbun);
	cout << "\n";
	
	cout << "\n * 수강한 과목 3개와 각 교과목명, 과목학점, 과목등급을 입력하세요. \n";
	for(i=0; i<3; i++){
		cout << "교과목명 : ";
		InputValue(A->Sub[i].SubName);
		cout << "과목학점 : ";
		InputValue(A->Sub[i].Hakjum);
		cout << "과목등급 (A+ ~ F) : ";
		InputValue(A->Sub[i].Grade);
		cout << "\n";
	}
}

void CalcGPA(Subject& Sub){
	float score;
	
	if (strcmp(Sub.Grade, "A+") == 0)
		score = 4.5;
	else if (strcmp(Sub.Grade, "A") == 0 || strcmp(Sub.Grade, "A0") == 0)
		score = 4.0;
	else if (strcmp(Sub.Grade, "B+") == 0)
		score = 3.5;
	else if (strcmp(Sub.Grade, "B") == 0 || strcmp(Sub.Grade, "B0") == 0)
		score = 3.0;
	else if (strcmp(Sub.Grade, "C+") == 0)
		score = 2.5;
	else if (strcmp(Sub.Grade, "C") == 0 || strcmp(Sub.Grade, "C0") == 0)
		score = 2.0;
	else if (strcmp(Sub.Grade, "D+") == 0)
		score = 1.5;
	else if (strcmp(Sub.Grade, "D") == 0 || strcmp(Sub.Grade, "D0") == 0)
		score = 1.0;
	else
		score = 0;
		
	Sub.GPA = (float)Sub.Hakjum * score;
}

float CalcAveGPA(Subject *Sub){
	int i;
	float addGPA=0;
	
	for(i=0; i<3; i++){
		addGPA += Sub[i].GPA;
	}
	
	return addGPA/3.0;
}

void PrintOneData(const Student& rSt){
	int i;
	
	cout.precision(2);
	cout << fixed;

	cout.width(10);
	cout <<"\n이름 : " << rSt.StdName;
	cout.width(10);	
	cout <<"학번 : " << rSt.Hakbun << "\n";
	
	cout << "================================================\n";
	cout << "과목명    과목학점    과목등급    과목평점\n";
	cout << "================================================\n";
	
	for(i=0;i<3;i++){
		cout.width(10);	
		cout << rSt.Sub[i].SubName << "\t" << rSt.Sub[i].Hakjum << "\t" <<  rSt.Sub[i].Grade << "\t" <<  rSt.Sub[i].GPA << "\n";
	}
	cout << "================================================\n";
	cout << "\t\t\t\t 평균평점 : " << rSt.AveGPA << "\n\n";
}

void PrintAllData(const Student* pSt, int x){
	cout << "\n\t 전체 학생 성적 보기 \n";
	cout << "================================================";

	for(int i=0; i<x; i++){
		PrintOneData(*pSt);
		pSt++;
	}
}

Student* StdSearch(Student *pSt, int x){
	int i;
	char searchName[30]; 
	
	cout << "\n검색 할 학생 이름 : ";
	InputValue(searchName);
	
	for(i=0; i<x; i++){
		if (strcmp(searchName, pSt[i].StdName) == 0)
			return &pSt[i];
	}
	
	return NULL;
}

inline void InputValue(char *str){
	cin >> str;
}

inline void InputValue(int &i){
	cin >> i;
}

void PrintAllStdList(const Student *pSt, int StdNum=2){
	int i;
	cout << "\n================================================\n";
	cout << "\t학번\t이름\n";
	cout << "================================================\n";
	for(i=0; i<StdNum; i++){
		cout.width(10);	
		cout << pSt[i].Hakbun << "\t" <<pSt[i].StdName << "\n";
	}
	cout << "================================================\n";
}

void Modify(Student *pSt){
	cout << "\n(" << pSt->StdName << ", "<< pSt->Hakbun << ") 의 정보를 수정하세요\n";
	cout << "이름 : "; InputValue(pSt->StdName);
	cout << "학번 : "; InputValue(pSt->Hakbun);
	cout << "정보가 수정되었습니다. \n";
}
