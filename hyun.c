#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** sets;         /* list of sets read from input file */
int max_number;         /* maximum number of the elements */
int rows;           /* the number of sets */
int check[751];
int min;
int length;
void read_file(FILE* f){
    int i,j;
    char buf[1024];
    char* pbuf;
    int value;


    fscanf(f,"%d\n",&max_number); /* first line contains the maximum number */
    fscanf(f,"%d\n",&rows);   /* second line contains the number of sets */

    /* dynamic allocation************ */
    sets = (int**)malloc(sizeof(int*)*rows);
    for(i=0;i<rows;++i)
    sets[i] = (int*)malloc(sizeof(int)*(max_number+1));
    /* ****************************** */

    for(i=0;i<rows;++i){
    if(fgets(buf,1024,f) == NULL)
        break;

    pbuf = buf;
    j=1;
    while(*pbuf !='\n' && pbuf != NULL){
        if(*pbuf == ' '){
        pbuf++;
        continue;
        }
        value = strtol(pbuf,&pbuf,10);
        sets[i][j++] = value;
    }
    sets[i][0] = j-1;       /* the number of elements is stored at the first element in the array. */
    }
}
    
void quick_sort(int **arr, int left, int right)
{
        int i, j;
        int *temp;
        int pivot = arr[left][0];
        if(left < right)
        {
               i = left;
               j = right+1; //do while문경우 --연산먼저하므로 index를 1초과한값으로 시작
               while( i <= j)
               {
                       do
                       i++;
                       while(arr[i][0] > pivot); //오름차순을 원할경우 >를 <로
                       do
                       j--;
                       while(arr[j][0] < pivot); //오름차순을 원할경우 <를 >로
                       if(i<j) // 엇갈리지않으면 두 요소를 스왑
                       {
                              temp = arr[i];
                              arr[i] = arr[j];
                              arr[j] = temp;
                       }
                       else //찾은 두소요가 겹치거나 엇갈리면 한바퀴 끝
                             break;
               }
               // j위치 요소를 기준이 되었던 pivot 과 Swap
               temp = arr[j];
               arr[j] = arr[left];
               arr[left] = temp;
               //Swap ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
               quick_sort(arr, left, j-1); // 가운데가 된 pivot을 중심으로 왼쪽 영역 재귀
               quick_sort(arr, j+1, right);// 가운데가 된 pivot을 중심으로 오른쪽 영역 재귀
        }
}

int greedy_current(int* current){
    int max=0;
    int max_i;
    int i,j,n,count;

    for(i=1; i<=rows; i++){
        count = 0;
        // 선택하지 않은 부분
        if(current[i]){

            for(j=1;j<=sets[i][0];++j){
                // 이미 선택된 부분이라면 
                if(check[j] ==0){
                    count++;
                }
            }
            if(max < count){
                max = count;
                max_i = i;
            }

        }
    }

    return max_i;
}

int check_function() {
    int i;
    for(i=1;i<=max_number;i++){
        if(check[i] == 0)
            return 1;
    }
    return 0;
}
void DFS(int index, int count, int* current){
    int n,i,j;
    int next_index;
    next_index = greedy_current(current);
    //카운트한 값이 현재 최소값보다 크다면 조사할 필요가 없다. 
    if(count >= min)
        return;

    if(index >= rows){
        if(check_function() == 0 && min > count){
            min = count;
        }
        return;
    }

    // 이 인덱스에 있는 값을 선택한다면 카운트 값을 늘려주고 선택 
    for(i=1;i<=sets[index][0];i++){
        n = sets[index][i];
        check[n] ++ ;
    }
    current[index]=0;
    DFS(next_index, count+1,current);

    // 이 인덱스에 있는 값을 선택하지 않는다면 카운트 값을 다시 내려주고 선택하지 않음
    for(i=1;i<=sets[index][0];i++){
        n = sets[index][i];
        check[n] -- ;
    }
    current[index]=1;
    DFS(next_index,count,current);
}







int main(){
    FILE* f = NULL;
    clock_t t1,t2;
    int i,j;
    int *current;
    
    t1 = clock();
    
    f = stdin;
    
    read_file(f);       /* read file to extract set data into variable "sets"*/

    min = 100000;
    
    for(i=1;i<=max_number;i++)
        check[i] = 0;

    // current 배열을 초기화 시킨다. 
    current = (int*)malloc(sizeof(int)*rows+1);
    for(i=1; i<= rows; i++){
        current[i]=1;
        printf("%d " , current[i]);
    }

    //받아온 값으로 sets를 정렬시킨다. 더많은 원소가 있을 수 록 앞에 있게 된다. 
    //quick_sort(sets,0,rows-1); 

    DFS(0,0,current);

    printf("%d\n",min);

    return 0;
}

