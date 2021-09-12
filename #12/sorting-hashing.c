#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
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
			initialize(&array);	// �迭 �ʱ�ȭ 
			break;
		case 'q': case 'Q':
			freeArray(array);	// �迭 �Ҵ� ���� 
			break;
		case 's': case 'S':
			selectionSort(array);	// �迭 �������� 
			break;
		case 'i': case 'I':
			insertionSort(array);	// �迭 �������� 
			break;
		case 'b': case 'B':
			bubbleSort(array);	// �迭 �������� 
			break;
		case 'l': case 'L':
			shellSort(array);	// �迭 ������ 
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);	// �迭 ������ 
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);	// �ؽ����̺��� �̿��� �迭 �ؽ� 
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);	// �ؽ����̺��� ���� �Է°� �˻� 
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

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)	// �迭�� ������� �ʴٸ� �Ҵ����� 
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {	// �迭�� ��������� �����޼��� ��� 
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

	for (i = 0; i < MAX_ARRAY_SIZE; i++)	// �ּҰ��� �� ���� ������ ����Ʈ���� �ݺ� 
	{
		minindex = i;
		min = a[i];	// a[i] ���� �ּҰ����� ���� 
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])	// �ּҰ����� ���� ���� �����ϴ� ��� 
			{
				min = a[j];	// �ּҰ��� ���� ������ ��ü 
				minindex = j;
			}
		}
		a[minindex] = a[i];
		a[i] = min;	// ã�� �ּҰ��� �� ������ ��ü 
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
		while (a[j-1] > t && j > 0)	// �迭�� ���� ���� �� �����ٴ� Ŭ �� ����, j�� 0�� �� �� ���� �ݺ� 
		{
			a[j] = a[j-1];
			j--;	// �迭�� ��ü������ ���������� ��ĭ�� �̵�  
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
			if (a[j-1] > a[j])	// �����Ϸ��� �迭���� ���� �迭�� ū ��� 
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;	// �迭 ��ȣ ��ȯ 
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

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)	// ��ü �迭 ũ���� ������ h�� �ΰ� h�� 1�� �� ������ h �� ������ �����ϸ� �ݺ� 
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)	// h��ŭ ������ �ΰ� �ݺ� 
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)	// �迭�� ���� h��ŭ�� �� �迭 �����ٴ� Ŭ �� ����, k�� h-1���� ���� �� ���� �ݺ� 
				{
					a[k] = a[k-h];
					k -= h;	// �ش� �迭�� h��ŭ ���������� �̵� 
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
		v = a[n-1];	// �迭�� �߰��� �ǹ� ���ڵ�� ���� 
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);	// �ǹ����� ���� Ű ã�� 
			while(a[--j] > v);	// �ǹ����� ū Ű ã�� 

			if (i >= j) break;
			t = a[i];	// Ű�� ���� ��ȯ 
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];	// �ǹ��� i�� ��ġ ��ȯ 
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);	// �������� ��ȯ������ ��� 
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;	// %�����ڸ� �̿��� �ؽ��ڵ带 ��ȯ 
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
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

	if(ht[index] == key)	// �ؽ����̺��� �ε������� �Է°��� ������ ��ȯ 
		return index;

	while(ht[++index] != key)	// �ε����� ������Ų �ؽ����̺��� ���� �Է°��� ���� �� ���� �ݺ� 
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



