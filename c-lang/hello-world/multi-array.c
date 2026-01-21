// https://www.learn-c.org/en/Multidimensional_Arrays
#include <stdio.h>

int main() {

    int grades[][5] = {
        {80, 70, 65, 89, 90},
        {85, 80, 80, 82, 87}
    };

    int i, j, len = 5;
    for (i = 0; i < 2; i++) {
        double average = 0;
        for (j = 0; j < len; j++) {
            average += grades[i][j];
        }
        printf("%f\n", average / 5);
    }



    return 0;
}