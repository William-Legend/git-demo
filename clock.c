#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

int is24hour = 1;

void print_time(int blink)
{
    time_t now;
    struct tm *t;

    time(&now);
    t = localtime(&now);

    char ampm[3] = "";
    int display_hour = t->tm_hour;  

    if (!is24hour)
    {
        if (display_hour == 0)
            display_hour = 12;
        else if (display_hour > 12)
            display_hour -= 12;


        snprintf(ampm, sizeof(ampm), t->tm_hour >= 12 ? "PM" : "AM");
    }

    printf("\n\n\t\t+--------------------------+\n");
    printf("\t\t|     DIGITAL CLOCK        |\n");
    printf("\t\t+--------------------------+\n\n");

    printf("\t\t      %02d%c%02d%c%02d %s\n",
        display_hour,
        blink ? ':' : ' ',
        t->tm_min,
        blink ? ':' : ' ',
        t->tm_sec,
        is24hour ? "" : ampm
    );

    printf("\n\t[H] Toggle 12/24 Hour   [Q] Quit\n");
}

int main(void)
{
    int blink = 1;
    char ch;

    while (1)
    {
        system("cls");          
        print_time(blink);
        blink = !blink;
        Sleep(1000);            

        if (kbhit())
        {
            ch = getch();
            if (ch == 'q' || ch == 'Q')
                break;
            else if (ch == 'h' || ch == 'H')
                is24hour = !is24hour;
        }    
    }

    system("cls");
    printf("Clock closed. Goodbye!\n");

    return 0;
}