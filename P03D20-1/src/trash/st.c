#include < stdio.h >   // Для printf
#include < string.h >  // Для strtok
int main(void) {
    // Массив со строкой для поиска
    char str[24] =” test1 / test2 / test3 / test4”;
    // Набор символов, которые должны входить в искомый сегмент
    char sep[10] =”/”;
    // Переменная, в которую будут заноситься начальные адреса частей
    // строки str
    char *istr;

    printf(“Исходная строка : % s\n“, str);
    printf(“Результат разбиения :\n“);
    // Выделение первой части строки
    istr = strtok(str, sep);

    // Выделение последующих частей
    while (istr != NULL) {
        // Вывод очередной выделенной части
        printf(“% s\n”, istr);
        // Выделение очередной части строки
        istr = strtok(NULL, sep);
    }

    return 0;
}