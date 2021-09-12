#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	printf("[----- [Jegal Dohyun] [2018038018] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);	// 배열 초기화 
			break;
		case 'q': case 'Q':
			freeArray(array);	// 배열 할당 해제 
			break;
		case 's': case 'S':
			selectionSort(array);	// 배열 선택정렬 
			break;
		case 'i': case 'I':
			insertionSort(array);	// 배열 삽입정렬 
			break;
		case 'b': case 'B':
			bubbleSort(array);	// 배열 버블정렬 
			break;
		case 'l': case 'L':
			shellSort(array);	// 배열 셸정렬 
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);	// 배열 퀵정렬 
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);	// 해시테이블을 이용한 배열 해싱 
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);	// 해시테이블을 통한 입력값 검색 
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)	// 배열이 비어있지 않다면 할당해제 
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {	// 배열이 비어있으면 오류메세지 출력 
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); 
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)	// 최소값을 둔 앞을 제외한 리스트에서 반복 
	{
		minindex = i;
		min = a[i];	// a[i] 값을 최소값으로 설정 
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])	// 최소값보다 작은 값이 존재하는 경우 
			{
				min = a[j];	// 최소값을 작은 값으로 교체 
				minindex = j;
			}
		}
		a[minindex] = a[i];
		a[i] = min;	// 찾은 최소값을 맨 앞으로 교체 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)	// 배열의 값이 이전 열 값보다는 클 때 까지, j가 0이 될 때 까지 반복 
		{
			a[j] = a[j-1];
			j--;	// 배열을 전체적으로 오른쪽으로 한칸씩 이동  
		}
		a[j] = t 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])	// 정렬하려는 배열보다 이전 배열이 큰 경우 
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;	// 배열 상호 교환 
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)	// 전체 배열 크기의 절반인 h를 두고 h가 1이 될 때까지 h 값 반으로 감소하며 반복 
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)	// h만큼 간격을 두고 반복 
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)	// 배열의 값이 h만큼의 전 배열 값보다는 클 때 까지, k가 h-1보다 작을 때 까지 반복 
				{
					a[k] = a[k-h];
					k -= h;	// 해당 배열을 h만큼 오른쪽으로 이동 
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];	// 배열의 중간을 피벗 레코드로 선택 
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);	// 피벗보다 작은 키 찾기 
			while(a[--j] > v);	// 피벗보다 큰 키 찾기 

			if (i >= j) break;
			t = a[i];	// 키를 서로 교환 
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];	// 피벗과 i의 위치 교환 
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);	// 퀵정렬을 순환적으로 사용 
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;	// %연산자를 이용해 해시코드를 반환 
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)	// 해시테이블의 인덱스값이 입력값과 같으면 반환 
		return index;

	while(ht[++index] != key)	// 인덱스를 증가시킨 해시테이블의 값이 입력값이 같을 때 까지 반복 
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}




