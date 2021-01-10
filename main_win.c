#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> 


int mainMenu();
void adminPanel();
void passwordCheck();
void addflight();
void deleteflight();
void editflight();
void listflight();
void passengerMenu();
void bookFlight();
void delay(); 

struct Flight{ 
char airline[50];
char flight_code[50];
char departure_airport[50];
char destination_airport[50];
char time_of_departure[50];
char time_of_arrival[50];
char passenger_capacity[50];
};

#if defined(_WIN32)
	void clear(){
		system("cls");
	}
#elif defined(__linux__)
	void clear(){
		system("clear");
	}
#endif


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
    clear();
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
            printf("Select an Option: ");
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
				printf("Press any key to continue");
				getch();
				adminPanel();
			}
			else if (admin_choice == 5){
            	printf("Under Development");
			}
			else if (admin_choice == 6){
            	changepass();
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

		if (strcmp(newpassword,newpassword2) == 0){
			password = fopen("adminpassword.txt","w");
			fputs(newpassword,password);
			fclose(password);
			printf("Password Changed Successfully\n");
			printf("Directing to main menu");
			delay(2);
			main();}
		else{
			printf("Different passwords have been entered\n");
			printf("Directing to main menu...");
			delay(2);
			main();}
		}
	else {
		printf("Wrong Password\n");
		printf("Directing to main menu...");
		delay(2);
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
}

void editflight(){
	int edchoice,found = 0;
	char newfeature[50], edflightchoice[50];
	printf("----Edit Flight Screen----\n");
	listflight();
	printf("Enter Flight Code to select an flight:\n");
	scanf("%s",&edflightchoice);
	clear();
	printf("Flight Code: %s selected\n",edflightchoice);
	printf("0- Return to Admin Menu\n");
	printf("-----------------------\n");
	printf("1- Airline\n");
	printf("2- Flight Code\n");
	printf("3- Departure Airport\n");
	printf("4- Destination Airport\n");
	printf("5-Departure Time\n");
	printf("6-Arrival Time\n");
	printf("7-Passenger Capacity\n");
	printf("-----------------------\n");
	printf("Enter the feature you want to edit: ");
	scanf("%d",&edchoice);
	if (edchoice == 0)
		adminPanel();
	printf("\nEnter new version of the feature: ");
	scanf("%s",&newfeature);
	FILE *f_edit, *tempfile;
	struct Flight edit;
	f_edit = fopen("flights.txt","a+");
	tempfile = fopen("temp.txt","w");
	while (fread(&edit,sizeof(struct Flight),1,f_edit)){
		if (strcmp(edit.flight_code,edflightchoice) == 0){
			found = 1;
			if (edchoice == 1)
				strcpy(edit.airline, newfeature);
			else if (edchoice == 2)
				strcpy(edit.flight_code, newfeature);
			else if (edchoice == 3)
				strcpy(edit.departure_airport, newfeature);
			else if (edchoice == 4)
				strcpy(edit.destination_airport, newfeature);
			else if (edchoice == 5)
				strcpy(edit.time_of_departure, newfeature);
			else if (edchoice == 6)
				strcpy(edit.time_of_arrival, newfeature);
			else if (edchoice == 7) 
				strcpy(edit.passenger_capacity, newfeature);
			else{
				printf("Invalid option");
				printf("Please Try Again");
				editflight();}			
			fwrite(&edit,sizeof(struct Flight),1,tempfile);
			printf("Changes Saved\n");
	}
		else 
			fwrite(&edit,sizeof(struct Flight),1,tempfile);
	}
	if (found == 0){
		printf("No flight found");
		editflight();
}
	fclose(f_edit);
	fclose(tempfile);
	remove("flights.txt");
	rename("temp.txt","flights.txt");
	printf("Directing to admin panel...");
	delay(2); 
	adminPanel();
}
void deleteflight(){
	char deletecode[50], yesno;
	int found = 0;

	printf("Flight code of the record you want to delete: ");
	scanf("%s",&deletecode);

	struct Flight del;
	FILE *filedelete, *tempfile;
	filedelete = fopen("flights.txt","r");
	tempfile = fopen("temp.txt","w");
	printf("Flight code %s will be deleted\n",deletecode);
	printf("Are you sure?(y/n): ");
	
	scanf(" %c",&yesno);
	if (yesno == 'y')
	{
		
	printf("\nDeletion is in progress\n");
	
	while (fread(&del,sizeof(struct Flight),1,filedelete)){
		if (strcmp(del.flight_code,deletecode) == 0){
			found = 1;
			printf("Flight Code: %s deleted...\n",&deletecode);}
		else 
			fwrite(&del,sizeof(struct Flight),1,tempfile);
	}
	if (found == 0)
		printf("No flight found with this code\n");

	fclose(filedelete);
	fclose(tempfile);
	remove("flights.txt");
	rename("temp.txt","flights.txt");
	printf("Directing to admin panel...");
	delay(3); 
	adminPanel();}
	else if (yesno == 'n'){
		printf("Answered No\n");
		printf("Directing to admin panel...");
		delay(3); 
		adminPanel();
	}
	else {
		printf("Invalid Option\n");
		printf("Directing to admin panel...");
		delay(3); 
		adminPanel();
	}
}
void listcurrentbookings(){
	printf("Not implemented");
	}

void passengerMenu() 
{	
	int passenger_choice, inp;

	clear();

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

	clear();

	printf("\n Please provide departure and destination airport information\n\n");
	printf("Departure: ");
	scanf("%s", departure);
	printf("\nDestination: ");
	scanf("%s", destination);
	printf("%s \n", departure);
	printf("%s",destination);
}

void delay(int number_of_seconds) // İneternetten aldım. Biraz değiştirelim.
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 
} 


