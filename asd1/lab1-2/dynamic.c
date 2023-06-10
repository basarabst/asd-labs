#include <stdio.h>
#include <math.h>

int main() {
    int n, ct = 0;
    double num, S = 0, P = 1;
    printf("Enter n:\n");
    scanf("%d", &n);

    if (n <= 0) {
        printf("The program cannot be executed\n");
        printf("n = %d", n);
    } else {
        for (int i = 1; i <= n; i++) {
            num = i * i + 1;
            S += i + sin(i);
            P *= num / S;
            ct += 11; // <=|++|*|+|=|sin()|+|+=|/|*=|jmp
        }
        ct++; // i=1
        printf("Result: %.7lf\n", P);
        printf("Operations: %d", ct);
    }

    return 0;
}