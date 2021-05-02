#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
using namespace std;

typedef struct {
	string SubName;
	int Hakjum;
	string Grade;
	float GPA;
}Subject;

typedef struct {
	string StdName;
	int Hakbun;
	Subject *Sub;
	int SubNum;
	float AveGPA;
}Student;

void PrintMenu();
void inputData(Student *, int);
void CalcGPA(Subject&);
float CalcAveGPA(Subject *, int);
void PrintOneData(const Student&, int);
void PrintAllData(const Student*, int);
Student* StdSearch(Student *, int);
inline void InputValue(string &str);
inline void InputValue(int &i);
void PrintAllStdList(const Student *, int);
Subject* SubSearch(const Student &);
void ModifyStdInfo(Student *, int);

int main(void) {
	int num, i, j, StudentNum;
	bool break_num = false;
	Student* SearchStd;

	cout << "학생 수를 입력하세요 : ";
	InputValue(StudentNum);
	Student *std = new Student[StudentNum];

	for (;;) {
		do {
			PrintMenu();
			InputValue(num);
		} while (num != 1 && num != 2 && num != 3 && num != 4 && num != 5 && num != 6);

		switch (num) {
		case 1:
			inputData(std, StudentNum);

			for (i = 0; i<StudentNum; i++) {
				for (j = 0; j<std[i].SubNum; j++) {
					CalcGPA(std[i].Sub[j]);
				}

				std[i].AveGPA = CalcAveGPA(std[i].Sub, std[i].SubNum);
			}
			break;

		case 2:
			PrintAllData(std, StudentNum);
			break;

		case 3:
			SearchStd = StdSearch(std, StudentNum);
			if (SearchStd != NULL)
				PrintOneData(*SearchStd, SearchStd->SubNum);
			else
				cout << "\n학생을 찾을 수 없습니다. \n\n";
			break;

		case 4:
			PrintAllStdList(std, StudentNum);
			break;

		case 5:
			ModifyStdInfo(std, StudentNum);
			break;

		case 6:
			break_num = true;
			break;
		}

		if (break_num == true)
			break;
	}

	delete[] std;
}

void PrintMenu() {
	cout << "\n===== 메뉴 ===== \n";
	cout << "1. 학생 성적 입력 \n";
	cout << "2. 전체 학생 성적 보기 \n";
	cout << "3. 학생 이름 검색 \n";
	cout << "4. 전체 학생 목록 보기\n";
	cout << "5. 학생 정보 수정 \n";
	cout << "6. 프로그램 종료 \n\n";
	cout << "원하시는 기능을 입력하세요 : ";
}

void inputData(Student *A, int x) {
	int i, j;

	for (i = 0; i<x; i++) {
		cout << "\n*" << i + 1 << "번 째 학생의 이름과 학번을 입력하세요. \n";
		cout << "이름 : ";
		InputValue(A->StdName);
		cout << "학번 : ";
		InputValue(A->Hakbun);

		cout << "\n과목 수를 입력하세요 : ";
		InputValue(A->SubNum);
		Subject *Sub = new Subject[A->SubNum];
		A->Sub = Sub;

		cout << "\n * 수강한 과목 " << A->SubNum << "개와 각 교과목명, 과목학점, 과목등급을 입력하세요. \n";
		for (j = 0; j<A->SubNum; j++) {
			cout << "교과목명 : ";
			InputValue(Sub[j].SubName);
			cout << "과목학점 : ";
			InputValue(Sub[j].Hakjum);
			cout << "과목등급 (A+ ~ F) : ";
			InputValue(Sub[j].Grade);
			cout << "\n";
		}
		A++;
	}
}

void CalcGPA(Subject& Sub) {
	float score = 0.0;

	if (Sub.Grade == "A+")
		score = 4.5;
	else if (Sub.Grade == "A" || Sub.Grade == "A0")
		score = 4.0;
	else if (Sub.Grade == "B+")
		score = 3.5;
	else if (Sub.Grade == "B" || Sub.Grade == "B0")
		score = 3.0;
	else if (Sub.Grade == "C+")
		score = 2.5;
	else if (Sub.Grade == "C" || Sub.Grade == "C0")
		score = 2.0;
	else if (Sub.Grade == "D+")
		score = 1.5;
	else if (Sub.Grade == "D" || Sub.Grade == "D0")
		score = 1.0;
	else
		score = 0.0;

	Sub.GPA = (float)Sub.Hakjum * score;
}

float CalcAveGPA(Subject *Sub, int SubNum) {
	int i;
	float addGPA = 0;

	for (i = 0; i<SubNum; i++) {
		addGPA += Sub[i].GPA;
	}

	return addGPA / (float)SubNum;
}

void PrintOneData(const Student& rSt, int SubNum) {
	int i;

	cout.precision(2);
	cout << fixed;

	cout.width(10);
	cout << "\n이름 : " << rSt.StdName;
	cout.width(10);
	cout << "학번 : " << rSt.Hakbun << "\n";

	cout << "================================================\n";
	cout << "과목명    과목학점    과목등급    과목평점\n";
	cout << "================================================\n";

	for (i = 0; i<SubNum; i++) {
		cout.width(10);
		cout << rSt.Sub[i].SubName << "\t" << rSt.Sub[i].Hakjum << "\t" << rSt.Sub[i].Grade << "\t" << rSt.Sub[i].GPA << "\n";
	}
	cout << "================================================\n";
	cout << "\t\t\t\t 평균평점 : " << rSt.AveGPA << "\n\n";
}

void PrintAllData(const Student* pSt, int x) {
	cout << "\n\t 전체 학생 성적 보기 \n";
	cout << "================================================";

	for (int i = 0; i<x; i++) {
		PrintOneData(*pSt, pSt->SubNum);
		pSt++;
	}
}

Student* StdSearch(Student *pSt, int x) {
	int i;
	string searchName;

	cout << "\n검색 할 학생 이름 : ";
	InputValue(searchName);

	for (i = 0; i<x; i++) {
		if (searchName == pSt[i].StdName)
			return &pSt[i];
	}

	return NULL;
}

inline void InputValue(string &str) {
	getline(cin, str);
}

inline void InputValue(int &i) {
	cin >> i;
	cin.ignore();
}

void PrintAllStdList(const Student *pSt, int StdNum = 2) {
	int i;
	cout << "\n================================================\n";
	cout << "\t학번\t이름\n";
	cout << "================================================\n";
	for (i = 0; i<StdNum; i++) {
		cout.width(10);
		cout << pSt[i].Hakbun << "\t" << pSt[i].StdName << "\n";
	}
	cout << "================================================\n";
}

Subject* SubSearch(const Student &pSt) {
	string Type;
	int i;

	cout << "\n검색 할 과목 이름 : ";
	getline(cin, Type);

	for (i = 0; i < pSt.SubNum; i++) {
		if (Type == pSt.Sub[i].SubName) {
			return &pSt.Sub[i];
		}
	}

	cout << "과목이 존재하지 않습니다. \n";
	return NULL;
}

void ModifyStdInfo(Student *pSt, int StdNum) {
	Student *SearchStd = StdSearch(pSt, StdNum);
	string Type;
	int i;

	if (SearchStd != NULL) {

		while (1) {
			cout << "수정(학생정보/과목정보) : ";
			InputValue(Type);

			if (Type == "학생정보") {
				cout << "\n(" << pSt->StdName << ", " << pSt->Hakbun << ") 의 정보를 수정하세요\n";
				cout << "\n이름 : "; InputValue(pSt->StdName);
				cout << "학번 : "; InputValue(pSt->Hakbun);
				cout << "정보가 수정되었습니다. \n";
				break;
			}
			else if (Type == "과목정보") {
				Subject* SearchSub = SubSearch(SearchStd[0]);

				if (SearchSub != NULL) {
					cout << "\n(" << SearchSub->SubName << ", " << SearchSub->Hakjum << ", " << SearchSub->Grade << ") 의 정보를 수정하세요\n";
					cout << "교과목명 : "; InputValue(SearchSub->SubName);
					cout << "과목학점 : "; InputValue(SearchSub->Hakjum);
					cout << "과목등급 (A+ ~ F) : "; InputValue(SearchSub->Grade);

					for (i = 0; i<SearchStd->SubNum; i++) {
						CalcGPA(SearchStd->Sub[i]);
					}

					SearchStd->AveGPA = CalcAveGPA(SearchStd->Sub, SearchStd->SubNum);
				}

				break;
			}
		}
	}
	else
		cout << "\n학생을 찾을 수 없습니다. \n\n";
}
