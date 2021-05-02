#include <iostream>
using namespace std;

int main(){
	int M[3][3]={{1,2,3},
				 {4,5,6},
				 {7,8,9}};

	int (*ptr)[3]; int *p; int **pt;
	
	ptr = M;
	
	cout << **ptr << **M << "\n";
	cout << **(ptr+1) << **(M+1) << "\n";
	cout << **(ptr+1) << *ptr[1] << **(M+1) << *M[1] << "\n";
	cout << **(ptr+1) << **(M+1) << *M[1] << M[1][0] << "\n";

	p = M[0];

	cout << *p << *M[0] << **M << "\n";
	cout << *(p+1) << *(M[0]+1) << *(*M+1) << "\n";
	cout << *(p+1) << *(M[0]+1) << *(*M+1) << "\n";
	
	pt = &p;

	cout << **pt << *p << "\n";
	cout << **pt << *p << "\n"; 
}
