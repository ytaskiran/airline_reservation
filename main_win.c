#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int mainMenu();
void adminPanel();
void passwordCheck();
void addflight();
void deleteflight();
void editflight();
void listflight();
void passengerMenu();
void bookFlight();
void filterFlights(char departure[50], char destination[50]);

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
    int choice;
    choice = mainMenu();

    if (choice == 1){
        passwordCheck();
        adminPanel();
    }

    else if (choice == 2){
        passengerMenu();
    }
    
    else if (choice == 3)
    	exit(1);

    else {
        printf("Please enter a valid value\n");
    }
    
    return 0;

}

int mainMenu() 
{   
    int choice;
    system("cls");

    printf( "\n\n**********************************************************************************\n");
    printf( "**********************************************************************************\n");
    printf( "**********\t\t\t\t\t\t\t\t**********\n");
    printf( "**********\tWELCOME TO THE PISMANIYE AIRLINE RESERVATION SYSTEM\t********** \n");
    printf( "**********\t\t\t\t\t\t\t\t**********\n");
    printf( "**********************************************************************************\n");
    printf( "**********************************************************************************\n");
    printf( "\n\n\t1- Admin Menu\n");
    printf( "\t2- Passenger Menu\n ");
	printf("\t3- Quit\n\n\n ");
    printf("Select your menu: ");
    scanf("%d", &choice);

    return choice;
}

void passwordCheck()
{
	FILE *checkpas;
    char real_pw[20] ;
    char input_pw[20];
    int check;
    
	checkpas = fopen("adminpassword.txt","r");
	fgets(real_pw,50,checkpas);

    int count = 0;
        do { 
            printf("\nPassword: ");
            scanf("%s", &input_pw);
            check = strcmp(input_pw, real_pw);
            if (check == 0){
				printf("Password is correct\n\n");
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
            }} while (true);  
}

void adminPanel(){
	        int admin_choice, inp;
            system("cls");
            printf("\n\tWelcome to Admin Panel\n\n");
            printf("1- Add a new flight\n");
			printf("2- Edit a flight\n");
            printf("3- Delete an existing flight\n");
            printf("4- List available flights\n");
            printf("5- List current bookings\n");
            printf("6- Change admin password\n\n");
			printf("9- Return to main menu \n\n\n");
            printf("Select an Option:");
            scanf("%d",&inp);

			admin_choice = inp;

			if (admin_choice == 1){
				addflight();
			}
            else if (admin_choice == 2){
            	editflight();
			}
            else if (admin_choice == 3){
            	listflight();
				deleteflight();
				main();
			}	
            else if (admin_choice == 4){
            	listflight();
			}
			else if (admin_choice == 5){
            	printf("Under Development");
			}
			else if (admin_choice == 6){
            	printf("Under Development");
			}
			else if (admin_choice == 9){
            	main();
			}				
            else {
            	printf("Invalid option");
			}
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
	adminPanel();
}

void listflight(){
		FILE *reading;
		struct Flight d2;
		reading = fopen("flights.txt","r");
		int i= 0;
		while (fread(&d2,sizeof(struct Flight),1,reading)){
			printf("Number: %d\nAirline: %s\nFlight Code: %s\nDeparture Airport: %s\nDestination Airport: %s\nDeparture Time: %s\nArrival Time: %s\nPassenger Capacity: %s\n-------------------------------------\n",i,d2.airline,d2.flight_code,d2.departure_airport,d2.destination_airport,d2.time_of_departure,d2.time_of_arrival,d2.passenger_capacity);
			i++;
		}
		fclose(reading);
}

void editflight(){
	printf("Not implemented");
}
void deleteflight(){
	char deletecode[50];
	int found = 0;

	printf("Flight code of the record you want to delete: ");
	scanf("%s",&deletecode);

	struct Flight del;
	FILE *filedelete, *tempfile;
	filedelete = fopen("flights.txt","r");
	tempfile = fopen("temp.txt","w");

	printf("Deletion is in progress\n");

	while (fread(&del,sizeof(struct Flight),1,filedelete)){
		if (strcmp(del.flight_code,deletecode) == 0){
			found = 1;
			printf("Flight Code: %s deleted...\n",&deletecode);}
		else 
			fwrite(&del,sizeof(struct Flight),1,tempfile);
	}
	if (found == 0)
		printf("No flight found with this code");

	fclose(filedelete);
	fclose(tempfile);
	remove("flights.txt");
	rename("temp.txt","flights.txt");
}
void listcurrentbookings(){
	printf("Not implemented");
	}

void passengerMenu() 
{	
	int passenger_choice, inp;

	system("cls");

	printf("\n\tPassenger Menu\n\n");
	printf("1- Book a flight\n");
	printf("2- Cancel a booking\n");
	printf("3- List booked flights\n");
	printf("\n9- Return to main menu\n\n");

	scanf("%d", &inp);
	passenger_choice = inp;

	if (passenger_choice == 1) {
		bookFlight();	
	}
	else if (passenger_choice == 2) {
		printf("\n\nThis section is in development2...\n");
	}
	else if (passenger_choice == 3) {
		printf("\n\nThis section is in development3...\n");
	}
	else if (passenger_choice == 9) {
		main();
	}
	else {
		printf("Please enter valid value\n");
	}
}

void bookFlight()
{	
	char departure[50], destination[50];

	system("clear");

	printf("\n Please provide departure and destination airport information\n\n");
	printf("Departure: ");
	scanf("%s", departure);
	printf("\nDestination: ");
	scanf("%s", destination);

    filterFlights(departure, destination);
}

void filterFlights(char departure[50], char destination[50])
{
	int found = 0;
	
	struct Flight filter;
	FILE *filefilter;
	filefilter = fopen("flights.txt","r");

    printf("\n\tFlight Code\t\tDeparture\t\tDestination\t\tDeparture Time\t\t Arrival Time\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");

	while (fread(&filter,sizeof(struct Flight),1,filefilter)){
		if (strcmp(filter.departure_airport,departure) == 0 && strcmp(filter.destination_airport, destination) == 0){
			found = 1;
			printf("\t%s\t\t\t%s\t\t%s\t\t\t%s\t\t%s\n", filter.flight_code, filter.departure_airport, filter.destination_airport, filter.time_of_departure, filter.time_of_arrival);
        }	
	}
    printf("\n\n\n");
	if (found == 0)
		printf("\nNo flight found\n\n");

	fclose(filefilter);
}



