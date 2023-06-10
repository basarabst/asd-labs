#include <stdio.h>

int main() {
    float x = 0;

    printf("Enter x:\n");
    scanf("%f", &x);

    if (x <= 0) {
        if (x < -20) {
            if (x >= -32) {
                float y = x * x - 3;
                printf("x = %.2f, y = %.2f\n", x, y);
                printf("x belongs to the interval [-32; -20) union (10; + infinity)");
            } else {
                printf("x = %.2f\n", x);
                printf("x does not belong to the given intervals");
            }
        } else {
            printf("x = %.2f\n", x);
            printf("x does not belong to the given intervals");
        }
    } else if (x <= 5) {
        float y = x * x * x - 5 * x * x;
        printf("x = %.2f, y = %.2f\n", x, y);
        printf("x belongs to the interval (0; 5]");
    } else if (x > 10) {
        float y = x * x - 3;
        printf("x = %.2f, y = %.2f\n", x, y);
        printf("x belongs to the interval [-32; -20) union (10; + infinity)");
    } else {
        printf("x = %.2f\n", x);
        printf("x does not belong to the given intervals");
    }

    return 0;
    }