#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int mainMenu();
int passwordCheck();
void adminpanel();
void addflight();

struct Flight{ 
char airline[50];
char flight_code[50];
char departure_airport[50];
char destination_airport[50];
char time_of_departure[50];
char time_of_arrival[50];
char passenger_capacity[50];
};

int main() {
    int choice, check;
    choice = mainMenu();

    if (choice == 1){
        int count = 0;
        do { 
            check = passwordCheck();
            if (check == 0){
				printf("Password is correct\n");
				adminpanel();
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
	FILE *checkpas;
    char real_pw[20] ;
    char input_pw[20];
    int check;
    
	checkpas = fopen("adminpassword.txt","r");
	printf("%s",checkpas);
	fgets(real_pw,50,checkpas);
    printf("\nPassword: ");
    scanf("%s", &input_pw);
    check = strcmp(input_pw, real_pw);
    return check;
}
void changepass(){
	FILE *password ;
	password = fopen("adminpassword.txt","a+");
	char oldpassword[50], newpassword[50],newpassword2[50], inputpassword[50];
	fgets(oldpassword,50,password);
	fclose(password);
	printf("Enter Old Password:");
	scanf("%s",&inputpassword);
	if(strcmp(inputpassword, oldpassword) == 0 ){
		printf("Correct! Enter New Password:");
		scanf("%s",newpassword);
		printf("Enter New Password:");
		scanf("%s",newpassword2);
		if (strcmp(newpassword,newpassword2)){
			password = fopen("adminpassword.txt","w");
			fputs(newpassword,password);
			fclose(password);
			printf("Password Changed Successfully");
			main();}
		else{
			printf("Different passwords have been entered");
			main();}
		}
	else {
		printf("Wrong Password");
		main();
	}
}

void addflight(){
	char airline[50],flight_code[50],departure_ap[50],destination_ap[50],departure_time[50],arrival_time[50],capacity[50];
	printf("Enter the information to add a new flight: ");
	printf("\nAirline: ");
	scanf("%s",airline);
	printf("\nFlight Code: ");
	scanf("%s",flight_code);
	printf("\nDeparture Airport: ");
	scanf("%s",departure_ap);
	printf("\nDestination Airport: ");
	scanf("%s",destination_ap);
	printf("\nTime of Departure: ");
	scanf("%s",departure_time);
	printf("\nTime of Arrival: ");
	scanf("%s",arrival_time);
	printf("\nPassenger Capacity: ");
	scanf("%s",capacity);
	struct Flight newflight;
	strcpy(newflight.airline, airline);
	strcpy(newflight.flight_code, flight_code);
	strcpy(newflight.departure_airport, departure_ap);
	strcpy(newflight.destination_airport, destination_ap);
	strcpy(newflight.time_of_departure, departure_time);
	strcpy(newflight.time_of_arrival, arrival_time);
	strcpy(newflight.passenger_capacity, capacity);
	FILE *addfile;
	addfile = fopen("flights.txt","a+");
	fwrite(&newflight, sizeof(struct Flight),1, addfile);		
	fclose(addfile);
	printf("New Flight Successfully Added");
	main();
}

void listflight(){
		FILE *reading;
		struct Flight d2;
		reading = fopen("flights.txt","r");
		int i= 0;
		while (fread(&d2,sizeof(struct Flight),1,reading)){
		printf("Number: %d\nairline: %s\nflight_code: %s\ndeparture_airport: %s\ndestination airport: %s\nDeparture Time: %s\nArrival Time: %s\nPassenger Capacity: %s\n-------------------------------------\n",i,d2.airline,d2.flight_code,d2.departure_airport,d2.destination_airport,d2.time_of_departure,d2.time_of_arrival,d2.passenger_capacity);
		i++;
		fclose(reading);
	}	
}
void adminpanel(){
	        int choice;
            printf("Welcome to Admin Panel\n");
            printf("1- Add/Edit/Delete Flights\n");
            printf("2- List available flights\n");
            printf("3- List current bookings\n");
            printf("4- Change admin password\n");
            printf("Select an Option:\n");
            scanf("%d",&choice);
			if (choice == 1){
				printf("Sadece add flight eklendi:");
				addflight();}
            else if (choice == 2)
            	listflight();
            else if (choice == 3)
            	printf("3- Not implemented");
            else if (choice == 4)
            	printf("4- Not implemented");
            else {
            	printf("invalid option");
			}
}





