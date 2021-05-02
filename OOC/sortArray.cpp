#include <iostream>
#define MAX_DATA 5 
using namespace std;
 
void PrintMenu();

template <typename T>
void sortArray(T array[], int size){
	int i,j,min;
	T temp;
	
    for (i=0; i<size-1; i++){
    	min = i;
        for (j=i+1; j<size; j++){
            if (array[j] < array[min])
				min = j;
        }
		temp = array[min];
        array[min] = array[i];
        array[i] = temp;
    }
	 
	cout << "정렬 결과 : ";
	for(i=0; i<size; i++)
		cout << array[i] << " ";
	cout << "\n";
}

int main(void){
	int menu_input, break_num, i;
	int int_array[MAX_DATA];
	float float_array[MAX_DATA];
		
	for(;;){
		do{
			PrintMenu();
			cin >> menu_input;
		} while (menu_input!=1 && menu_input!=2 && menu_input!=3);
	
		switch(menu_input){
			case 1:
				cout << MAX_DATA << "개의 정수를 입력하세요 : ";
				for(i=0; i<MAX_DATA; i++)
					cin >> int_array[i];
				sortArray(int_array, MAX_DATA);
				break;
			case 2:
				cout << MAX_DATA << "개의 실수를 입력하세요 : ";
				for(i=0; i<MAX_DATA; i++)
					cin >> float_array[i];
				sortArray(float_array, MAX_DATA);
				break;
			case 3:
				break_num = 1;
				break;
		}
		
	if (break_num == 1)
		break;
	}
}

void PrintMenu(){
	cout << "\n1. 정수 정렬\n"; 
	cout << "2. 실수 정렬\n";
	cout << "3. 프로그램 종료\n\n";
	cout <<"메뉴 선택 : ";
}
