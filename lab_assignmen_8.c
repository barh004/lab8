#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

typedef struct tree_node {
    int data;
    struct tree_node *left_child;
    struct tree_node *right_child;
}tree_node;

void swap(int *xp,int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;

}


void heapify(int arr[], int n, int x){
    int largest = x;

    int left = 2 * x + 1;

    int right= 2 * x + 2;

    if(left < n && arr[left] > arr[largest]){
        largest = left;
    
    } 

    if(right< n && arr[right] > arr[largest]){
        largest = right;
    }

    if(largest != x){
        swap(&arr[x], &arr[largest]);

        heapify(arr, n, largest);

    }

}

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
    for(int x = n / 2 - 1; x >=0; x--){
        heapify(arr, n, x);
    }

    for(int x = n - 1; x >= 0; x--){
        swap(&arr[0], &arr[x]);

        heapify(arr, x, 0);
    }

}

void merge(int pData[], int l, int m, int r)
{
    int a = 0;
    int b = 0;
    int c = l;

    int num = m - l + 1;
    int num2 = r - m;

    int *L = (int *) malloc(num * sizeof(int));
    int *R = (int *) malloc(num2 * sizeof(int));

    extraMemoryAllocated= (num * sizeof(int)) + (num2 * sizeof(int));

    for (a = 0; a < num; a++)
        L[a] = pData[l + a];
    for (b = 0; b < num2; b++)
    {
        R[b] = pData[m + 1+ b];
    }

    a = 0;
    b = 0;
    
    while(a < num && b < num2)
    {
        if (L[a] <= R[b])
        {
            pData[c] = L[a];
            a++;
        }
        else
        {
            pData[c] = R[b];
            b++;
        }
        c++;
    }

    while( a < num)
    {
        pData[c] = L[a];
        a++;
        c++;
    }
    while( b < num2)
    {
        pData[c] = R[b];
        b++;
        c++;
    }


    free(L);
    free(R);

}
// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
     if( l < r)
    {
        int m = (l + r) / 2;

        mergeSort(pData, l, m);
        mergeSort(pData, m +1, r);

        merge(pData, l, m, r);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
        if(i>= dataSz){
            printf("\n\n");
            return;
        }
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
