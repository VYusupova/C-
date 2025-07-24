/*Задача на работу со строками 
   на вход подается строка ее надо отформатировать так что бы
   не было пробелов вначале и конце строки
   между словами по одному пробелму  */
   
#include <stdio.h>
#include <string.h>

void print_str(char * str) {
    char *word = strtok(str," ");
    if( word != NULL){
        printf("%s", word);
        word = strtok(NULL, " ");
        do{
            printf(" %s", word);
            word = strtok(NULL," ");
        }while(word != NULL);
    }
    if (word) free(word);
}

int main() {
    char * str = NULL;
    size_t len = 0;
    ssize_t read = getline( & str, & len, stdin);
    if (read != -1) {
        //printf("%s",str);
        printf("<");
        print_str(str);
        printf(">");
    }
    else {
        printf("Error");
    }

}