#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int mainMenu();
int passwordCheck();

int main() {
    int choice, check;

    choice = mainMenu();

    if (choice == 1){
        int count = 0;
        do { 
            check = passwordCheck();
            if (check == 0){
                printf("Password is correct\n");
                break;
            }
            else {
                count++;
                if (count == 5){
                    printf("\nToo many wrong attempts\n\n");
                    exit(0);
                }
                else { 
                    printf("Password is not correct, please try again.\n\n");
                }
            }} 
            while (true);
        
    }

    else if (choice == 2){
        printf("2\n");
    }

    else {
        printf("Please enter a valid value\n");
    }

    return 0;

}

int mainMenu() 
{   
    int choice;
    system("clear");

    printf( "\n\n**********************************************************************************\n");
    printf( "**********************************************************************************\n");
    printf( "**********\t\t\t\t\t\t\t\t**********\n");
    printf( "**********\tWELCOME TO THE PISMANIYE AIRLINE RESERVATION SYSTEM\t********** \n");
    printf( "**********\t\t\t\t\t\t\t\t**********\n");
    printf( "**********************************************************************************\n");
    printf( "**********************************************************************************\n");
    printf( "\n\n\t1- Admin Menu\n");
    printf( "\t2- Passenger Menu\n\n\n ");

    printf("Select your menu: ");
    scanf("%d", &choice);

    return choice;
}

int passwordCheck()
{
    char real_pw[20] = "admin123";
    char input_pw[20];
    int check;

    printf("\nPassword: ");
    scanf("%s", &input_pw);

    check = strcmp(input_pw, real_pw);

    return check;
}









