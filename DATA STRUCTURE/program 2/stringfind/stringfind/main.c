#include<stdio.h>
#include<stdlib.h>
#include<string.h>




int nfind(char *string , char *pat);

int main()
{
    int result;
    char *pat = "aab" , *string ="ababbaabaa";
    
    printf("   pat = %s\n", pat);
    printf("string = %s\n", string);
    
    result = nfind(string, pat);
    
    if(result != -1){
        printf("\n find pattern \"%s\" at position %d \n", pat,result);
    }
    else{
        printf("\npattern \"%s\" not find\n", pat);
    }
    return 0;
    
    
    
    
    
}



int nfind(char *string , char *pat)
{
    int i, j=0, start =0;                     ///why adding   =0
    long lasts = strlen(string)-1;           ///why can not use int initialize
    long lastp = strlen(pat)-1;              ///same
    long endmatch = lastp;
    
    //endmatch(對比字串的最後一個)。startch(哪裡開始比)
    for(i=0; endmatch<=lasts; endmatch++,start++){
        //ＥＸ如果第三個有對到才從第1個比看有沒有都配對到
        if(string[endmatch]==pat[lastp])
            //i(長)j(短)是用來計算是不是有對比到資料 start(回傳從第幾比對到)
            for( j =0,i=start; j<lastp && string[i]== pat[j]; i++,j++);
        //代表有對成功
        if( j == lastp)
            return start;
    }
    return -1;
}
