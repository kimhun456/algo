#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int** sets;         /* list of sets read from input file */
int max_number;         /* maximum number of the elements */
int rows;           /* the number of sets */


/* This function check if given sets cover the universe
 *
 * int* current: the array "current" holds the list of sets which are currently processed.
 * int k : the number of sets that "current" is holding
 * int min : the minimum number of sets that is found currently
 *
 * return 1 if "current" holds sets that cover the universe, 0 otherwise.
 * */
int is_solution(int *current,int k){
    int i,j;
    int length;
    int index;

    int checker[750];       /* for checking if "current" hold sets whose union covers the universe */


    /* Initialize */
    for(i=0;i<750;++i){
    checker[i] = 0;
    }
    
    //printf("TRY : ");
    for(i=0;i<k;++i){
    //printf("%d ",current[i]);
    index = current[i];
    length = sets[index][0]; /* 1st element in the "sets" contains the number of elements
                   
                       * */
    for(j=1;j<=length;++j){
        checker[sets[index][j]] = 1;
    }
    }


    for(i=1;i<=max_number;++i){
    if(checker[i] == 0){
        //printf("\n");
        return 0;
    }
    }

    //printf(" : SOLUTION\n");
    return 1;
}


void process_solution(int *current,int k,int *min){
    int i,j;
    int index;
    int length;
    
    //printf("Found the solution!!\n");
/*
    for(i=0;i<k;++i){
    index = current[i];
    length = sets[current[i]][0]; 
    for(j=1;j<=length;++j){
        printf("%d ",sets[index][j]);
    }
    printf("\n");
    }
*/
    if(k < *min)
    *min = k;
    //printf("the minimum number of sets to cover the universe: %d\n",k);

}

void construct_candidates(int *current,int k,int* c){
    int i,j;

    /* Initialize candidate set */
    for(i=0;i<rows;++i){
    c[i] = 1;
    }

    for(i=0;i<k;++i){
    c[current[i]] = 0;
    }
}


void backtrack(int *current,int k,int* min){
    int candidates[300];        /* candidate sets */
    int i,j;

    if(is_solution(current,k)){
    process_solution(current,k,min);
    }
    else{
    construct_candidates(current,k,candidates);
    for(i=0;i<rows;++i){
        if(candidates[i] == 1){
        current[k] = i;
        backtrack(current,k+1,min);
        }
    }
    }
}

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
    

int main(int argc,char* argv[]){
    FILE* f = NULL;
    clock_t t1,t2;
    int i,j;
    int current[300];
    int min;
    
    t1 = clock();

    f = stdin;
    
    read_file(f);       /* read file to extract set data into variable "sets"*/

    // printf("MAX NUM:%d\n",max_number);
    // printf("MAX ROW:%d\n",rows);
    
    /* ************************************************************** */
    /* This is test code to display sample dataset. ***************** */
    /* You should remove this part when you submit. ***************** */
 //    for(i=0;i<rows;++i){
    // for(j=1;j<=sets[i][0];++j){
    //     printf("%d ",sets[i][j]);
    // }
    // printf("\n");
 //    }
    /* *************************************************************** */
    min = rows;
    backtrack(current,0,&min);

    printf("%d\n",min);

    /* deallocate sets */
    for(i=0;i<rows;++i){
    free(sets[i]);
    }

    free(sets);
    /* *************** */
    t2 = clock();
    return 0;
}
