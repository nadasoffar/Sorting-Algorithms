#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct
{
    int heapSize;
    int *array;
}MaxHeap;

void Swap(int *a,int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void printArray(int *A,int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d, ",A[i]);
    }
}
float RunningTime(clock_t start,clock_t end){
    double runningTime = ((double)end) / CLOCKS_PER_SEC;
    return runningTime;
}
void insertionSort(int *array, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = array[i];
        j = i;
        while (j > 0 && array[j-1] > key)
        {
            array[j] = array[j-1];
            j = j - 1;
        }
        array[j] = key;
    }
}
int partition (int *arr, int start, int end)
{
    int pivot,j,i = start-1;
    pivot=arr[end];
    for (int j=start;j<=end-1;j++)
    {
        if (arr[j]<pivot)
        {
            i++;   
            Swap(&arr[i],&arr[j]);
        }
    }
    Swap(&arr[i+1],&arr[end]);
    return (i+1);
}
void quickSort(int *arr,int start,int end)
{
    if (start<end)
    {
        int pindex;
        pindex = partition(arr,start,end);
        quickSort(arr, start, pindex- 1);  
        quickSort(arr, pindex + 1,end); 
    }
}
void selectionsort(int a[],int n){
    int j,i,min;
    for(j=0; j<n;j++){
              min=j;
        for(i=j+1;i<n;i++){
            if(a[i]<a[min]){
                min=i;
                 }
        }
    Swap(&a[min],&a[j]);
    }
}
void merge(int a[],int l,int mid ,int r){
int i, j, z = l, c = 0, b = 0, l1= mid -l+1, r1=r-mid;
int larray[l1],rarray[r1];
for(i=0;i<l1;i++){
        larray[i]=a[l+i];
}
for(j=0;j<r1;j++){
        rarray[j]=a[mid+1+j];
}
z = l;
while(c < l1 && b <r1){
    if(larray[c]<=rarray[b]){
        a[z]=larray[c];
        c++;
    }
    else{
    a[z]=rarray[b];
        b++;
      }
  z++;
}
while(c<l1){
  a[z]=larray[c];
        c++;
        z++;
}
while(b<r1){
  a[z]=rarray[b];
        b++;
        z++;
}
}
void mergeSort(int *a,int l,int r){
int mid;
if(l<r){
    mid=l+(r-l)/2;
    mergeSort(a,l,mid);
    mergeSort(a,mid+1,r);
    merge(a,l,mid,r);
    }
}
void MaxHeapify(MaxHeap *heap,int i){
    int left = 2*i+1;
    int right = 2*i+2;
    int largest = i;
    if (left<heap->heapSize && heap->array[left]>heap->array[largest])
    {
        largest = left;
    }
    if (right<heap->heapSize && heap->array[right]>heap->array[largest])
    {
        largest = right;
    }
    if (largest!=i)
    {
        Swap(&heap->array[i],&heap->array[largest]);
        MaxHeapify(heap,largest);
    }
}

MaxHeap* BuildMaxHeap(int *A,int n){
    MaxHeap *heap = malloc(sizeof(MaxHeap));
    heap->heapSize = n;
    heap->array = A;
    for (int i = (heap->heapSize - 1)/2; i >= 0; i--)
    {
        MaxHeapify(heap,i);
    }
    return heap;
}

void HeapSort(int *A,int n){
    MaxHeap *heap = BuildMaxHeap(A,n);
    for (int i = n; i > 1; i--)
    {
        Swap(&heap->array[0],&heap->array[heap->heapSize -1]);
        heap->heapSize--;
        MaxHeapify(heap,0);
    }
}

void BubbleSort(int A[],int n){
    int i,j,flag;
    for(i=0;i<n-1;i++){
        flag=0;
        for(j=0;j<n-i-1;j++){
            if (A[j]>A[j+1])
            {
                Swap(&A[j],&A[j+1]);
                flag=1;
            }
        }
        if (flag==0)
        {
            break;
        }
    }
}

int main(){
    int arraySize,i=0;
    float heapTimeArray[5],bubbleTimeArray[5],quickTimeArray[5],insertionTimeArray[5],selectionTimeArray[5],mergeTimeArray[5];
    int arraySizes[5] = {10,100,1000,10000,100000};
    clock_t start,end;
    for (int i = 0; i < 5; i++)
    {
        arraySize = arraySizes[i];
        int A[arraySize],H[arraySize],Is[arraySize],Q[arraySize],S[arraySize],Me[arraySize];
        printf("Array Size: %d\n",arraySize);
        srand(time(0));
        for(int j = 0; j<arraySize; j++){
        A[j] = rand() % 101;
        H[j] = Me[j] = Is[j] = Q[j] = S[j] = A[j];
        }  
        /* printf("Array before Bubble Sort: ");
        printArray(A,arraySize); */
        start = clock();
        BubbleSort(A,arraySize);
        end = clock() - start;
        /* printf("Array after Bubble Sort: ");
        printArray(A,arraySize); */
        double bubbleTime = RunningTime(start,end); 
        /* printf("Array before Heap Sort: ");
        printArray(H,arraySize); */
        start = clock();
        HeapSort(H,arraySize);
        end = clock() - start;
        /* printf("Array after Heap Sort: ");
        printArray(H,arraySize); */
        double heapTime = RunningTime(start,end);
        /* printf("Array before Quick Sort: ");
        printArray(Q,arraySize); */
        start = clock();
        quickSort(Q,Q[0],Q[arraySize-1]);
        end = clock() - start;
        /* printf("Array after Quick Sort: ");
        printArray(Q,arraySize); */
        double quickTime = RunningTime(start,end);
        /* printf("Array before Insertion Sort: ");
        printArray(Is,arraySize); */
        start = clock();
        insertionSort(Is,arraySize);
        end = clock() - start;
        /* printf("Array after Insertion Sort: ");
        printArray(Is,arraySize); */
        double insertionTime = RunningTime(start,end);
        /* printf("Array before Merge Sort: ");
        printArray(Me,arraySize); */
        start = clock();
        mergeSort(Me,0,arraySize-1);
        end = clock() - start;
        /* printf("Array after Merge Sort: ");
        printArray(Me,arraySize); */
        double mergeTime = RunningTime(start,end);
        /* printf("Array before Selection Sort: ");
        printArray(S,arraySize); */
        start = clock();
        selectionsort(S,arraySize);
        end = clock() - start;
        /* printf("Array after Selection Sort: ");
        printArray(S,arraySize); */
        double selectionTime = RunningTime(start,end);
        heapTimeArray[i] = heapTime*1000;
        bubbleTimeArray[i] = bubbleTime*1000;
        quickTimeArray[i] = quickTime*1000;
        insertionTimeArray[i] = insertionTime*1000;
        mergeTimeArray[i] = mergeTime*1000;
        selectionTimeArray[i] = selectionTime*1000;
        printf("Running times for array size = %d :\n",arraySizes[i]);
        printf("Bubble Sort running time = %f milliseconds. \n",bubbleTime*1000);
        printf("Heap Sort running time = %f milliseconds. \n",heapTime*1000);
        printf("Quick Sort running time = %f milliseconds. \n",quickTime*1000);
        printf("Insertion Sort running time = %f milliseconds. \n",insertionTime*1000);
        printf("Merge Sort running time = %f milliseconds. \n",mergeTime*1000);
        printf("Selection Sort running time = %f milliseconds. \n",selectionTime*1000);
        printf("---------------------------------------------------------\n");
    }
    FILE * fp = fopen("mydata.csv", "w");
    fprintf(fp, "Array Size, Bubble Sort, Insertion Sort, Selection Sort, Merge Sort, Quick sort, Heap Sort\n");
    for (int i = 0; i < 5; i++)
    {
        fprintf(fp, "%d, ", arraySizes[i]);
        fprintf(fp, "%f, ", bubbleTimeArray[i]);
        fprintf(fp, "%f, ", insertionTimeArray[i]);
        fprintf(fp, "%f, ", selectionTimeArray[i]);
        fprintf(fp, "%f, ", mergeTimeArray[i]);
        fprintf(fp, "%f, ", quickTimeArray[i]);
        fprintf(fp, "%f, ", heapTimeArray[i]);
        fprintf(fp,"\n");
    }
    fclose(fp);

    return 0;
}