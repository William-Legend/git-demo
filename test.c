#include <stdio.h>
#include <stdlib.h>

typedef struct Date
{
    int Day;
    int Month;
    int Year;
}DATE, *PDATE;






int isLeapyear(int year)
{

    // if ((year % 4 ==0 && year %100 != 0)  ||  year % 400 == 0)
    // {
    //     return 1;
    // }
    // else
    // {
    //     return 0;
    // }
    //简洁写法：
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}


int getDaysInMonth(int month, int year)
{
    int Days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 2 && isLeapyear(year) == 1)
    {
        return 29;
    }
    else
    {
        return Days[month-1];
    }
}

int getDayOfWeek(int d,int m,int y)
{
     if (m < 3)
    {
        m += 12;
        y -= 1;
    }
    int k = y % 100;//年份后两位
    int j = y / 100;//世纪数
    int f = d + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j;
    return f % 7; 
}


const char *getDayName(int dayOfWeek)
{
    const char *days[] = {
        "Saturday", "Sunday", "Monday", "Tuesday",
        "Wednesday", "Thursday", "Friday"};
    return days[dayOfWeek];
}


void printMonthCalendar(int month, int year)
{
    const char *months[]= {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    printf("\n  ===== %s %d =====\n", months[month - 1], year);
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    int startDay = (getDayOfWeek(1, month, year) + 6) % 7; 
    int days = getDaysInMonth(month, year);

    int i;
    for (i = 0; i < startDay; i++)
        printf("     "); // 打印空白

    for (int d = 1; d <= days; d++)
    {
        printf("%5d", d);
        if (++i % 7 == 0)
            printf("\n");
    }
    printf("\n");

}


void printFullYearCalendar(int year)
{
    for (int i = 0; i < 12; i++)
    {
        printMonthCalendar(i+1,  year);
    }
    

    
}


void saveCalendarToFile(int month,int year)
{
    FILE *fp;
    char filename[50];
    snprintf(filename,sizeof(filename), "calendar_%02d_%d.txt", month, year);

    if ((fp=fopen(filename,"w"))== NULL)
    {
        perror("文件打开失败");
        exit(EXIT_FAILURE);
    }


     const char *months[]= {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    fprintf(fp, "Calendar for %02d/%d\n", month, year);
    fprintf(fp, "Sun Mon Tue Wed Thu Fri Sat\n");

    int startDay = (getDayOfWeek(1, month, year) + 6) % 7; 
    int days = getDaysInMonth(month, year);

    int i;
    for (i = 0; i < startDay; i++)
        fprintf(fp,"    "); // 打印空白

    for (int d = 1; d <= days; d++)
    {
        fprintf(fp,"%4d", d);
        if (++i % 7 == 0)
            fprintf(fp,"\n");
    }
    fprintf(fp,"\n");


    fclose(fp);
    printf("Calendar saved to %s \n", filename);

}



void saveFullYearCalendarToFile(int year)
{  
    FILE *fp;
    char filename[50];
    snprintf(filename,sizeof(filename), "calendar_%d.txt", year);
    if ((fp=fopen(filename,"w"))== NULL)
    {
        perror("文件打开失败");
        exit(EXIT_FAILURE);
    }

    const char *months[]= {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };


    for (int month = 1; month <= 12; month++)
    {
    
    fprintf(fp, "Calendar for %02d/%d\n", month, year);
    fprintf(fp, "Sun Mon Tue Wed Thu Fri Sat\n");

    int startDay = (getDayOfWeek(1, month, year) + 6) % 7; 
    int days = getDaysInMonth(month, year);

    int i;
    for (i = 0; i < startDay; i++)
        fprintf(fp,"    "); // 打印空白

    for (int d = 1; d <= days; d++)
    {
        fprintf(fp,"%4d", d);
        if (++i % 7 == 0)
            fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
    }


    fclose(fp);
    printf("Calendar saved to %s \n", filename);
    
 
}

int main(void) {
    int choice;
    while (1) {
        printf("\n==== Simple Calendar App ====\n");
        printf("1. Check Leap Year\n");
        printf("2. Get Day of a Date\n");
        printf("3. Print Monthly Calendar\n");
        printf("4. Print Full Year Calendar\n");
        printf("5. Export Monthly Calendar to File\n");
        printf("6. Export Full Year Calendar to File\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: 
            {
                int year;
                printf("Enter year: ");
                scanf("%d", &year);
                if (isLeapyear(year))
                    printf("%d is leap year!\n", year);
                else
                    printf("%d is not leap year!\n", year);
                break;
            }
            case 2: 
            {
                DATE date;
                printf("Please enter the day(DD MM YYYY):");
                scanf("%d %d %d", &date.Day, &date.Month, &date.Year);
                int n = getDayOfWeek(date.Day, date.Month, date.Year);
                printf("The day is %s\n", getDayName(n));
                break;
            }
            case 3: 
            {
                DATE date;
                printf("Please enter the month and the year(MM YYYY):");
                scanf("%d %d", &date.Month, &date.Year);
                printMonthCalendar(date.Month, date.Year);
                break;
            }
            case 4: 
            {
                int year;
                printf("Please enter the year:");
                scanf("%d", &year);
                printFullYearCalendar(year);
                break;
            }
            case 5: 
            {
                DATE date;
                printf("Please enter the month and the year(MM YYYY):");
                scanf("%d %d", &date.Month, &date.Year);
                saveCalendarToFile(date.Month, date.Year);
                break;
            }
            case 6: 
            {
                int year;
                printf("Please enter the year:");
                scanf("%d", &year);
                saveFullYearCalendarToFile(year);
                break;
            }
            case 7:
                printf("Goodbye!!\n");
                return 0;  // 直接退出程序
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}