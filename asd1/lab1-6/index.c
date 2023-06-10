#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main() {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Pos;
    int i, j, sum;
    int rows = 24;
    int columns = 80;
    int pause = 5;

    SetConsoleTextAttribute(hout, FOREGROUND_GREEN);

    for (sum = rows+columns-2; sum >= 0; sum--) {

        if (sum % 2 == 0) {
            for (j = columns-1; j >= 0; j--) {
                for (i = 0; i <= rows - 1; i++) {
                    if (sum == i + j) {
                        Pos.X = j;
                        Pos.Y = i;
                        SetConsoleCursorPosition(hout, Pos);
                        printf("@");
                        Sleep(pause);
                    }
                }
            }
        } else {
            for (i = rows-1; i >= 0; i--) {
                for (j = 0; j <= columns-1; j++) {
                    if (sum == i+j) {
                        Pos.X = sum-i;
                        Pos.Y = i;
                        SetConsoleCursorPosition(hout, Pos);
                        printf("@");
                        Sleep(pause);
                    }
                }
            }
        }
    }
    getch();
    return 0;
}