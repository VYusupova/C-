/*Задача на работу со строками 
   на вход подается строка ее надо отформатировать так что бы
   не было пробелов вначале и конце строки
   между словами по одному пробелу  */
   /* 3 вариант с ипользованием конструкции     scanf("%ms", &str);*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    char * str = NULL;
        printf("<");
    scanf("%ms", &str);
    if (str != NULL) printf("%s", str);
    while(1){
        if (str == NULL) break;
        printf(" %s", str);
        free(str);
        scanf("%ms", &str);
    }
        free(str);
        printf(">");
}
