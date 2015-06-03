#include<stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include <ctype.h>

void QSort(char x[ ], int left, int right);
void Swap(char x[ ], int i, int j);
void ShowData(char x[ ], int n);
void ToLower(char x[], int n);

/* クイックソートを行う */
void QSort(char x[ ], int left, int right)
{
    int i, j;
    int pivot;
    
    i = left;                      /* ソートする配列の一番小さい要素の添字 */
    j = right;                     /* ソートする配列の一番大きい要素の添字 */
    
    pivot = x[(left + right) / 2]; /* 基準値を配列の中央付近にとる */
    
    while (1) {                    /* 無限ループ */
        
        while (x[i] < pivot)       /* pivot より大きい値が */
            i++;                   /* 出るまで i を増加させる */
        
        while (pivot < x[j])       /* pivot より小さい値が */
            j--;                   /*  出るまで j を減少させる */
        if (i >= j)                /* i >= j なら */
            break;                 /* 無限ループから抜ける */
        
        Swap(x, i, j);             /* x[i] と x[j]を交換 */
        i++;                       /* 次のデータ */
        j--;
    }
    //ShowData(x, 10);               /* 途中経過を表示 */
    
    if (left < i - 1)              /* 基準値の左に 2 以上要素があれば */
        QSort(x, left, i - 1);     /* 左の配列を Q ソートする */
    if (j + 1 <  right)            /* 基準値の右に 2 以上要素があれば */
        QSort(x, j + 1, right);    /* 右の配列を Q ソートする */
}

/* 配列の要素を交換する */
void Swap(char x[ ], int i, int j)
{
    int temp;
    
    temp = x[i];
    x[i] = x[j];
    x[j] = temp;
}


/* n 個のデータを表示する */
void ShowData(char x[ ], int n)
{
    int i;
    
    for (i = 0; i < n ; i++)
        printf("%c", x[i]);
    printf("\n");
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
    
    printf("ソート前:\n");
    ShowData(word, n);
    
    QSort(word, 0, n - 1);
    
    printf("ソート後:\n");
    ShowData(word, n);
    
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