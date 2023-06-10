#include <stdio.h>
#include <math.h>

int main() {
    int n, ct = 0;
    double num, S, P = 1;
    printf("Enter n:\n");
    scanf("%d", &n);

    if (n <= 0) {
        printf("The program cannot be executed\n");
        printf("n = %d", n);
    } else {
        for (int i = 1; i <= n; i++) {
            num = i * i + 1;
            S = 0;
            for (int j = 1; j <= i; j++) {
                S += j + sin(j);
                ct += 6; // <=|++|sin()|+|+=|jmp
            }
            P *= num/S;
            ct += 10; // <=|++|*|+|=|=0|j=1|/|*=|jmp
        }
        ct++; // i=1
        printf("Result: %.7lf\n", P);
        printf("Operations: %d", ct);
    }

    return 0;
}
