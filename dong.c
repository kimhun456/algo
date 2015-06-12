#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** sets;         /* list of sets read from input file */
int max_number;         /* maximum number of the elements */
int rows;           /* the number of sets */
int check[751];
int min;

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
    
int check_function() {
    int i;
    for(i=1;i<=max_number;i++){
        if(check[i] == 0)
            return 1;
    }
    return 0;
}
void DFS(int index, int count){
    int n,i,j;
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
    DFS(index+1, count+1);

    // 이 인덱스에 있는 값을 선택하지 않는다면 카운트 값을 다시 내려주고 선택하지 않음
    for(i=1;i<=sets[index][0];i++){
        n = sets[index][i];
        check[n] -- ;
    }
    DFS(index+1,count);
}
int main(){
    FILE* f = NULL;
    clock_t t1,t2;
    int i,j;
    int current[300];
    
    t1 = clock();
    
    f = stdin;
    
    read_file(f);       /* read file to extract set data into variable "sets"*/

    min = 100000;
    
    for(i=1;i<=max_number;i++)
        check[i] = 0;
    
    DFS(0,0);

    t2 = clock();
    
    printf("%d\n",min);

    printf("Time : %.3fs\n",(double)(t2 - t1)/CLOCKS_PER_SEC);

    return 0;
}

