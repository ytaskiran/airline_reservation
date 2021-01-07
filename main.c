#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int passwordCheck();

int main() {
    int choice, check;
    system("clear");

    printf( "\n\n**********************************************************************************\n" \
            "**********************************************************************************\n" \
            "**********\t\t\t\t\t\t\t\t**********\n" \ 
            "**********\tWELCOME TO THE PISMANIYE AIRLINE RESERVATION SYSTEM\t********** \n" \
            "**********\t\t\t\t\t\t\t\t**********\n" \ 
            "**********************************************************************************\n" \
            "**********************************************************************************\n" \
            "\n\n\t1- Admin Menu\n" \
            "\t2- Passenger Menu\n\n\n ");

    printf("Select your menu: ");
    scanf("%d", &choice);

    if (choice == 1){
        check = passwordCheck();
        printf("%d\n", check);
    }

    else if (choice == 2){
        printf("2\n");
    }

    else {
        printf("Please enter a valid value\n");
    }

    return 0;

}

int passwordCheck()
{
    char real_pw[20] = "admin123";
    char input_pw[20];
    int check;

    printf("\nPassword: ");
    scanf("%s", &input_pw);

    printf("Input password: %s\n", input_pw);
    printf("Real password: %s\n", real_pw); 

    check = strcmp(input_pw, real_pw);

    return check;
}









