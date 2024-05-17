#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 101

/* insert string t into string s at position i */
void strnins(char *s, char *t, int i);

int main() {
    
    // C 字串寫法(第一個會是\n)
   char s[MAX_SIZE] = "amobile", t[MAX_SIZE] = "uto";
   printf("s = %s\n", s);
   printf("t = %s\n", t);

   strnins(s, t, 1);
   printf("strnins(s, t,1) = ");
   printf("%s\n", s);

   return 0;
}

/* insert string t into string s at position i */
void strnins(char *s, char *t, int i) {
   char string[MAX_SIZE];
   char *temp = string;

   if (i < 0 || i > strlen(s)) {
       fprintf(stderr, "Position is out of bounds \n");
       exit(1);
   }
   if (!strlen(s)) strcpy(s, t);
   else if (strlen(t)) {
       
       //不加星號是因為要放記憶體位置
       strncpy(temp, s, i);
       //\n,a
       printf("temp= %s\n", temp);                                                  ///Why output will print numbers 'TEMP'
       strcat(temp,t);
       //\n,a,u,t,o
       printf("temp= %s\n", temp);
       strcat(temp, (s + i));
       //\n,a,u,t,o,m,o,b,i,l,e
       printf("temp= %s\n", temp);
       strcpy(s, temp);
       printf("%s\n", s);
   }
}

