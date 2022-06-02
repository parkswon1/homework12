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
	printf("[----- [SeokWonPark] [2017018003] -----]");
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
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
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

int initialize(int** a) //함수 값을 랜덤으로 배정해주는 함수 정렬된 배열을 랜덤화할때도 사용된다.
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

int freeArray(int *a)//프로그램이 다 끝났을때 동적할당을 해제해주는 함수
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a) //배열안에 어떤 값이 들어있는지 알려주는 함수
{
	if (a == NULL) {
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


int selectionSort(int *a) //선택 정렬 가장 작은 데이터를 찾아 가장 앞의 데이터와 교환해나간다.
{
	int min; //작은값을 저장할 변수
	int minindex; //작은값의 주소를 저장할 변수
	int i, j; //for문을 돌리기위한 i,j

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//원래 배열에 어떤값이 있는지 출력해주는 함수

	for (i = 0; i < MAX_ARRAY_SIZE; i++)//가장 작은 값을 앞으로 옮긴다음 그 옮긴 수 다음부터 비교해감
	{
		minindex = i; //i를 가장 작은 값의 주소로 두고
		min = a[i];//a[i]를 작은값에다가 저장
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)//j를 증가시키면서 //(j=i+1)인 이유는 가장 i까지는 정렬이 되어있기 때문
		{
			if (min > a[j])//min값이 a[j]값보다 클경우
			{
				min = a[j]; //min값에 a[j]값을 넣어준다
				minindex = j; //가장 작은수 주소를 j로 해준다
			}
		}
		a[minindex] = a[i];//비교되서 더큰수인 a[i]를 빈칸이될 a[minindex]에 넣어준다.
		a[i] = min; //원래 a[i]가 있던곳에 비교해서 가장 작은수를 넣어준다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a) //정렬된 앞부분으로 원소를 옮기는 방법
{
	int i, j, t; 

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)//정렬되지 않은 배열값을 i개의 정렬된 리스트에 넣어서 i+1인 정렬된 배열을 만들어가는 과정
	{
		t = a[i]; //t에 a[i]값을 넣어주고
		j = i; //j에 i값을 넣어준다
		while (a[j-1] > t && j > 0)//a[j]를 앞으로 이동시킬 것이다 자신보다 작은수가 나오기 전까지
		{
			a[j] = a[j-1];//앞으로 이동하며 값 교환
			j--;//인덱스 감소
		}
		a[j] = t;//a[i]값을 변화한 a[j]에 넣어준다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)//주변 데이터중 가장 큰 데이터를 뒤로 보내는것
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)//i값을 증가시키면서
	{
		for (j = 1; j < MAX_ARRAY_SIZE+1; j++) //j값을 증가시키면서
		//원래코드에서 j를 0부터 실행시켜버렸기때문에 j[-1]값을 가져와이상한 값을 가져왔고
		//정렬이후에 가장 뒷값이 튀는 오류가 발생해서 해결했다.(보고서 첨수)
		{
			if (a[j-1] > a[j])//j번째에 있는 값이 그 앞값보다 작다면
			{
				t = a[j-1]; //t에 앞값 저장
				a[j-1] = a[j]; //j번재 값을 앞으로 이동
				a[j] = t; //앞값을 뒤로이동
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)//insertionSort의 단점을 보완하기위해 만듬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //배열사이즈를 (현재 13)를 반으로 나눈 h=6이고그다음은 3 이런식으로 2로 나누변서 반복
	{
		for (i = 0; i < h; i++)//i를 h가되기 전까지 증가시키면서
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//h만큼 떨어진 값이랑 비교하기위해
			{
				v = a[j]; //v에 j번째 값을 넣어주고
				k = j; //k에 j값을 넣어준다
				while (k > h-1 && a[k-h] > v)//shell을 초기화지않고 shell에서 h만큼 앞에있는 값보다 j번재 값이 작으면
				{
					a[k] = a[k-h];//서로 위치를 바꿔준다
					k -= h;
				}//어느정도 정렬이되면서 h가 작아지다가 1이되면 삽입정렬이되서 정렬을 완료한다
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)//기준 값을 중심으로 왼쪽과 오른쪽 부분집합으로 분할해서 정렬
{
	int v, t;//피봇과 탬프
	int i, j;//인덱스 값들

	if (n > 1) //n이 1보다 클때 이때 n은 MAXARRAY값인 10이 들어온다
	{
		v = a[n-1];//피봇은 배열의 가장 마지막에있는것
		i = -1;//i는 -1
		j = n - 1;//j는 배열의 가장 마지막

		while(1)//break문이 나올때까지 반복
		{
			while(a[++i] < v);//부분집합의 왼쪽의 인댁스를 증가시키면서 피봇보다는 작을떄동안
			while(a[--j] > v);//부분집합의 오른쪽의 인댁스를 감소시키면서 피봇보다는 클동안

			if (i >= j) break; //i랑j가 같아지거나 i가 j를 초과할때까지 반복하라는뜻
			t = a[i];//t에 a[i]를 넣어주고
			a[i] = a[j];//a[i]랑 a[j]를 교환하고
			a[j] = t;//a[j]에 a[i]에 원래있던 값을 넣어준다.
		}
		t = a[i];//피봇을 넣어주고교환을 해줌
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);//i를 피봇으로 sort
		quickSort(a+i+1, n-i-1);//i를 중심으로 오른족 왼쪽을 나누면서 정렬
	}


	return 0;
}

int hashCode(int key) { //인덱스값이 초과되지 않게 나머지를 계산해주는 함수
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)//문자열을 빠르게 찾을수 있도록 변환하는 것
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
		hashtable[i] = -1;//해시 테이블을 -1로 초기화시킴

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1; //변수들 지정후 -1로 초기화
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];//배열의 값을 받아오고
		hashcode = hashCode(key); //값을 인덱스화함
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)//hashtable의 hashcode번째가 비었다면 그곳에 바로 key값을 넣어준다.
		{
			hashtable[hashcode] = key;//값넣어주기
		} else 	{

			index = hashcode;//hashcode를 index에 넣고

			while(hashtable[index] != -1) //인덱스가 비었을떄까지 index를 증가시키면서 찾는다.
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;//빈곳을 찾았으면 값을 넣어준다.
		}
	}

	return 0;
}

int search(int *ht, int key)//정렬된 값 찾기
{
	int index = hashCode(key);//index에 찾아올 key값 넣어준고

	if(ht[index] == key)//인덱스가 key값이면 바로 출력하면되고
		return index;

	while(ht[++index] != key)//아닐경우에 index를 증가시키면서 찾는다
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;//찾은 인덱스 반환
}



