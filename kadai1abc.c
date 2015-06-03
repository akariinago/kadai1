#include<stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include <ctype.h>

void QSort(char x[ ], int left, int right);
void Swap(char x[ ], int i, int j);
void ToLower(char x[], int n);

/* クイックソートを行う */
void QSort(char x[ ], int left, int right)
{
    int i, j;
    int pivot;
    
    i = left;
    j = right;
    
    pivot = x[(left + right) / 2];
    
    while (1) {
        
        while (x[i] < pivot)
            i++;
        while (pivot < x[j])
            j--;
        if (i >= j)
            break;
        
        Swap(x, i, j);
        i++;
        j--;
    }
    
    if (left < i - 1)
        QSort(x, left, i - 1);
    if (j + 1 <  right)
        QSort(x, j + 1, right);
}

/* 配列の要素を交換する */
void Swap(char x[ ], int i, int j)
{
    int temp;
    
    temp = x[i];
    x[i] = x[j];
    x[j] = temp;
}



void ToLower(char x[ ], int n)
{
    int i;
    
    for( i=0; i<n; i++ ){
        x[i] = tolower( x[i] );
    }
}

int main(int argc, char *argv[])
{
    FILE * fp;
    char *word;
    char row[24];
    char high[24];
    int i;
    
    if(argc==1){
        
        printf("引数を入力してください\n");
        exit(1);
    }
    if (argc==2) {
        word= argv[1];
    }

    if(argc==3){
        word=(char*)malloc(strlen(argv[1])+ strlen(argv[2]) + 1 );
        strcat(word,argv[1]);
        strcat(word,argv[2]);
    }

    int n = strlen(word);
    ToLower(word,n);
    QSort(word, 0, n - 1);
    
    
    if((fp = fopen( "words.txt" , "r" ))== NULL ) {
        perror("エラーが発生しました");
        return EXIT_FAILURE;
    }
    
    while( fgets( row , sizeof( row ) , fp ) != NULL ) {
        for( i=0;i<strlen( row );i++ ) {
            high[i] = row[i];
        }
        row[strlen(row) - 1] = '\0';/*nullを消す*/
        
        QSort(row, 0, strlen(row) - 1);

        if(strcmp(row, word)==0){/*一致していたら*/
            high[strlen(row)] = '\0';
            printf("%s\n", high);
            break;
        }
    }
    fclose( fp );
    
    return EXIT_SUCCESS;
}