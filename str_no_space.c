/*Задача на работу со строками 
   на вход подается строка ее надо отформатировать так что бы
   не было пробелов вначале и конце строки
   между словами по одному пробелу  */
   
#include <stdio.h>
#include <stdlib.h>

static void print_str(const char * str) {
    int i = 0;
    char space = ' ';
    // посчитаем длину строки
    while (str[i] != '\0') {
        if (str[i] == '\n') break;
        i++;
    }
    //  выделим память под новую строку

    char * out = NULL;
    if (i > 0) out = malloc(i*sizeof(char));
    if (out == NULL) return;
    i = 0;
    int j = 0;
    // пропустим начальные пробелы
    while (str[i] == space) {
        i++;
    }
    while (str[i] != '\0' )  {
        if (str[i] == '\n') break;
        if (space == str[i] && str[i - 1] == space) {}
        else {
            out[j] = str[i];
            j++; 
        }
       i++;
    }
    if (out[j - 1] == space) out[j - 1] = '\0';    
    if (out != NULL) {printf("%s", out);free(out);}
}

int main() {
    char * str = NULL;
    size_t len = 0;
    size_t read = getline( & str, & len, stdin);
    if (read != (unsigned long int)-1) {
        if (str != NULL) {
        	//printf("%s",str);
        	printf("<");
       	print_str(str);
        	printf(">");
        	free(str);
        }
    }
    else {
        printf("Error");
    }

}
