#include<stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include <ctype.h>

int count(char *p,char c);
void ToLower(char x[], int n);

int count(char *p,char c)
{
    int i,x;
    
    i=0;
    x=0;
    while(*(p+i)!='\0'){
        if (*(p+i)==c)x++;
        i++;
    }
    
    return x;
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
    FILE *fp1;
    char *word;
    char row[16];
    char ans[16];
    int i,j=0,len=0;
    int s=0;

    if(argc==1){
        
        printf("文字を入力してください\n");
        exit(1);
    }
    else{
        if (argc==2) {
            word= argv[1];
        }

        else if(argc==3){
            word=(char*)malloc(strlen(argv[1])+ strlen(argv[2]) + 1 );
            strcat(word,argv[1]);
            strcat(word,argv[2]);
        }
        else{
            printf("エラー\n");
            exit(1);

        }
    }
    int n = strlen(word);
    ToLower(word,n);/*大文字を小文字に変換*/
    
    if((fp1 = fopen( "words.txt" , "r" ))== NULL ) {
        perror("エラーが発生しました");
        return EXIT_FAILURE;
    }

    while( fgets( row , sizeof( row ) , fp1 ) != NULL ) {
        s=0;

        row[strlen(row) - 1] = '\0';/*nullを消す*/

        for( i=0;i<strlen(row);i++ ){
            
            if(count(word, row[i])==0){
                s=1;    /*入力した文字に辞書の単語の文字が含まれているかの判定*/
                break;
            }
        }
        if(strcmp(row,word)==0){    /*入力した文字と同じであるかの判定*/
            s=1;
        }
        
        for( i=0;i<n;i++)
        {
            if(s == 1){
                break;
            }

            if(count(row, word[i])>count(word, word[i])){   /*入力した文字の個数よりも多い場合*/
                s = 1;
                break;
            }
        }
      
        if(s==0&&strlen(row)>len){
                for( i=0;i<strlen(row);i++ ) {
                    ans[i] = row[i];
                }
                ans[strlen(row)] = '\0';
                len=strlen(row);
            
        }
    }
    printf("%s\n", ans);
    fclose( fp1 );
    return EXIT_SUCCESS;
}
