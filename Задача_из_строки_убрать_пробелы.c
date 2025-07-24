/*Задача на работу со строками 
   на вход подается строка ее надо отформатировать так что бы
   не было пробелов вначале и конце строки
   между словами по одному пробелму  */
   
#include <stdio.h>

void print_str(char * str) {
    int i = 0;
    char space = ' ';
    // посчитаем длину строки
    while (str[i] != '\0') {
        i++;
    }
    //  выделим память под новую строку
    char * out = malloc(i);
    i = 0;
    int j = 0;
    // пропустим начальные пробелы
    while (str[i] == space) {
        i++;
    }
    while (str[i] != '\0') {
        if (str[i] == '\n') break;
        if (space == str[i] && str[i - 1] == space) {}
        else {
            out[j] = str[i];
            j++;
        }
        i++;
    }
    if (out[j - 1] == space) out[j - 1] = '\0';
    printf("%s", out);
    if (out) free(out);
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