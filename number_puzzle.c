#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

#define WIDTH 100
#define HEIGHT 25

int level, rows, columns, digit = 1, elements;
int arr[100][100];
int check_arr[100][100];
int arr1d[100];
int selected_val;
int count = 0;
int swap;
int x, y, k, i, j, temp;
char ch;
char selected_ch;
int m, n, check_element = 1, check_count;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void input()
{
    printf("\033[?25l");
    gotoxy(56, 15);
    printf("Enter the Level : ");
    printf("\033[32m");
    scanf("%d", &level);
    printf("\033[0m");
}

void generate()
{
    elements = level * level;
    rows = level;
    columns = level;
    m = rows / 2;
    n = columns / 2;
    for (i = 0; i < elements; i++)
    {
        arr1d[i] = digit;
        digit = digit + 1;
    }
    srand(time(NULL));
    for (i = (elements - 1); i > 0; i--)
    {
        j = rand() % (i + 1);
        temp = arr1d[i];
        arr1d[i] = arr1d[j];
        arr1d[j] = temp;
    }
    k = 0;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            arr[i][j] = arr1d[k];
            k++;
        }
    }
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            check_arr[i][j] = check_element;
            check_element = check_element + 1;
        }
    }
}

void display()
{
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            if (i == m && j == n)
            {
                printf("\033[34m");
                printf("%d \t", arr[i][j]);
                printf("\033[0m");
                continue;
            }
            printf("%d \t", arr[i][j]);
        }
        printf("\n");
        gotoxy(x, y + i + 1);
    }
}

void selected_display()
{
    gotoxy(56, 23);
    printf("\033[31m");
    printf("%d \t", selected_val);
    printf("\033[0m");
}

void display_level()
{
    gotoxy(52, 1);
    printf("\033[36m");
    printf("LEVEL : %d", level);
    printf("\033[0m");
}

void check()
{
    check_count = 0;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            if (arr[i][j] == check_arr[i][j])
            {
                check_count = check_count + 1;
            }
        }
    }

    if (check_count == elements)
    {
        system("cls");
        printf("\033[?25l");
        gotoxy(56, 15);
        printf("\033[31m");
        printf("NICE\n");
        printf("\033[0m");
        if (kbhit())
        {
            ch = getch();
            if (ch == 27)
            {
                system("cls");
                exit(0);
            }
            else
            {
                system("cls");
                level = level + 1;
                generate();
                system("cls");
                printf("\033[?25l");
                gotoxy(x, y);
                display();
                display_level();
            }
        }
    }
}

int main()
{
    x = WIDTH / 2 - 2;
    y = HEIGHT / 2 - 1;
    input();
    generate();
    system("cls");
    printf("\033[?25l");
    gotoxy(x, y);
    display();
    display_level();
    while (1)
    {
        ch = getch();
        if (ch == 119)
        {
            system("cls");
            printf("\033[?25l");
            if (m == 0)
            {
                m = m + 1;
            }
            m = m - 1;
            gotoxy(x, y);
            display();
            display_level();
        }
        if (ch == 97)
        {
            system("cls");
            printf("\033[?25l");
            if (n == 0)
            {
                n = n + 1;
            }
            n = n - 1;
            gotoxy(x, y);
            display();
            display_level();
        }
        if (ch == 115)
        {
            system("cls");
            printf("\033[?25l");
            if (m == (rows - 1))
            {
                m = m - 1;
            }
            m = m + 1;
            gotoxy(x, y);
            display();
            display_level();
        }
        if (ch == 100)
        {
            system("cls");
            printf("\033[?25l");
            if (n == (columns - 1))
            {
                n = n - 1;
            }
            n = n + 1;
            gotoxy(x, y);
            display();
            display_level();
        }
        if (ch == 32)
        {
            system("cls");
            selected_val = arr[m][n];
            selected_display();
            gotoxy(x, y);
            display();
            display_level();
            selected_ch = getch();
            if (selected_ch == 119)
            {
                if (m == 0)
                {
                    system("cls");
                    gotoxy(x, y);
                    display();
                    display_level();
                }
                else
                {
                    swap = arr[m - 1][n];
                    arr[m][n] = arr[m - 1][n];
                    arr[m - 1][n] = selected_val;
                    system("cls");
                    gotoxy(x, y);
                    display();
                    display_level();
                    check();
                }
            }
            if (selected_ch == 97)
            {
                if (n == 0)
                {
                    system("cls");
                    gotoxy(x, y);
                    display();
                    display_level();
                }
                else
                {
                    swap = arr[m][n - 1];
                    arr[m][n] = arr[m][n - 1];
                    arr[m][n - 1] = selected_val;
                    system("cls");
                    gotoxy(x, y);
                    display();
                    display_level();
                    check();
                }
            }
            if (selected_ch == 115)
            {
                if (m == (rows - 1))
                {
                    system("cls");
                    gotoxy(x, y);
                    display();
                    display_level();
                }
                else
                {
                    swap = arr[m + 1][n];
                    arr[m][n] = arr[m + 1][n];
                    arr[m + 1][n] = selected_val;
                    system("cls");
                    gotoxy(x, y);
                    display();
                    display_level();
                    check();
                }
            }
            if (selected_ch == 100)
            {
                if (n == (columns - 1))
                {
                    system("cls");
                    gotoxy(x, y);
                    display();
                    display_level();
                }
                else
                {
                    swap = arr[m][n + 1];
                    arr[m][n] = arr[m][n + 1];
                    arr[m][n + 1] = selected_val;
                    system("cls");
                    gotoxy(x, y);
                    display();
                    display_level();
                    check();
                }
            }
        }
        if (ch == 27)
        {
            system("cls");
            exit(0);
        }
    }
}