/*Задача про телефонный справочние Exam_01_05 Уровень 4
Напиши телефонный справочник который выводить 
данные о контактах построчно храняться в текстовом файле, путь до которго задается на потоке ввода
stdin(относительно корневой директории) и заканчивается символом новой строки \n*/

#include <stdio.h>

#include <string.h>

int end_str(char c) {
    return (c == '\n' || c == '\0') ? 1 : 0;
}

int print_str(char * str) {
    int i = 0;
    while (!end_str(str[i])) i++;
    int len = i;
    char * name = calloc(len, sizeof(char));
    char * number = NULL;

    int j = 0;
    for (i = 0; str[i] != ':'; i++, j++) {
        if (end_str(str[i])) break;
        else name[i] = str[i];
    }
    if (!end_str(str[i])) {
        number =  calloc(len, sizeof(char));
        number[0] = '+';
        number[1] = '7';
        number[2] = '(';
        j = 3;
        while (str[i] != '-') {
            if (end_str(str[i])) break;
            i++;
        }
        for (i++; str[i] != '-'; i++, j++) {
            if (end_str(str[i])) break;
            number[j] = str[i];
        }
        number[j] = ')';
        for (i++, j++; !end_str(str[i]); i++, j++) {
            
            number[j] = str[i];
        }
    }

    if (name) {
        if (number != NULL) {
            printf("%s%s", name, number);
            free(name);
        }
        free(number);
    }
}

int main() {
    char * str = NULL;
    size_t len = 0;
    ssize_t read = 0;
     printf("<");
     if (read = getline( & str, & len, stdin) != -1) print_str(str);
    while (read = getline( & str, & len, stdin) != -1) {
        printf("\n");
        print_str(str) ;
        
    }
    printf(">");

}