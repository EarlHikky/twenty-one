#include <stdio.h>

int get_arr_length(unsigned int *arr_length);
int input(int *arr, unsigned int arr_length);
void output(int *arr, unsigned int arr_length);

int main() {
    unsigned int arr_length;
    int arr[NMAX];

    if (get_arr_length(&arr_length)) return 1;

    if (input(arr, arr_length)) {
        printf("n/a");
        return 1;
    }

	return 0;
}

int get_arr_length(unsigned int *arr_length) {
    if (scanf("%u", arr_length) != 1 || 
        *arr_length > NMAX || 
        getchar() != '\n') {

        printf("n/a");
        return 1;
    }
    return 0;
}


int input(int *arr, unsigned int arr_length) {
    unsigned int count = 0;

    while (1) {
        scanf("%d", arr++);
        count++;
        char c = getchar();
        if (c == '\n') {
            if (count != arr_length)
                return 1;
            else
                return 0;
        } else if (c != ' ') {
            return 1;
		} else if (count == arr_length && c == ' ') {
			return 1;
		}			
    }
    return 0;
}

void output(int *arr, unsigned int arr_length) {
    for (unsigned int i = 0; i < arr_length; i++) {
        if (i != arr_length - 1)
            printf("%d ", arr[i]);
        else
            printf("%d", arr[i]);
    }
}