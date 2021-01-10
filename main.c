#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> 

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int mainMenu();
void adminPanel();
void passwordCheck();
void addflight();
void deleteflight();
void editflight();
void listflight();
void changepass();
void passengerMenu();
void bookFlight();
void filterFlights(char departure[50], char destination[50]);
int checkSeats(char flightnum[6]);
const char * assignBookingID();
void cancelBooking();
void deleteTicket(char bookingid[6]);
void listBookedFlights();
const char *checkTicket(char name[30],char id_num[30]);
void displayFlightInfo(const char* flight_num);

struct Flight{ 
char airline[50];
char flight_code[50];
char departure_airport[50];
char destination_airport[50];
char time_of_departure[50];
char time_of_arrival[50];
char passenger_capacity[50];
};

struct Ticket{ 
char bookingID[10];
char flight_num[10];
char name[50];
char id[20];
int seat_num;
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
    else if (choice == 2)
        passengerMenu();
    
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
    char real_pw[20];
    char input_pw[20];
    int check;
    
	checkpas = fopen("adminpassword.txt","r");
	fgets(real_pw,50,checkpas);

    int count = 0;
        do { 
            printf("\nPassword: ");
            scanf("%s", input_pw);
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

            clear();

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
			}
			else if (admin_choice == 5){
            	a_listbookings();
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
	scanf("%s", inputpassword);

	if(strcmp(inputpassword, oldpassword) == 0 ){
		printf("Correct! Enter New Password:");
		scanf("%s", newpassword);
		printf("Enter New Password:");
		scanf("%s", newpassword2);

		if (strcmp(newpassword,newpassword2) == 0){
			password = fopen("adminpassword.txt","w");
			fputs(newpassword,password);
			fclose(password);
			printf("Password Changed Successfully\n");
			printf("Directing to main menu");
			sleep(2);
			main();}
		else{
			printf("Different passwords have been entered\n");
			printf("Directing to main menu...");
			sleep(2);
			main();}
		}
	else {
		printf("Wrong Password\n");
		printf("Directing to main menu...");
		sleep(2);
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
		int dummy;
		do{
			printf("Press 9 to continue main menu\n");
			printf("Press 8 to continue admin panel\nChoice: ");
			
			scanf(" %d",&dummy);
			
			if (dummy == 9)
				main();
			
			else if (dummy == 8)
				adminPanel();
			
			else
				printf("Invalid Option\nPlease Try Again\n");
				
		}while ((dummy != 9) && (dummy != 8 ));
}

void editflight(){
	int edchoice,found = 0;
	char newfeature[50], edflightchoice[50];
	printf("----Edit Flight Screen----\n");
	listflight();
	printf("Enter Flight Code to select an flight:\n");
	scanf("%s", edflightchoice);
	clear();
	printf("Flight Code: %s selected\n",edflightchoice);
	printf("0- Return to Admin Menu\n");
	printf("-----------------------\n");
	printf("1- Airline\n");
	printf("2- Flight Code\n");
	printf("3- Departure Airport\n");
	printf("4- Destination Airport\n");
	printf("5- Departure Time\n");
	printf("6- Arrival Time\n");
	printf("7- Passenger Capacity\n");
	printf("-----------------------\n");
	printf("Enter the feature you want to edit: ");
	scanf("%d",&edchoice);
	if (edchoice == 0)
		adminPanel();
	printf("\nEnter new version of the feature: ");
	scanf("%s", newfeature);
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
	sleep(2); 
	adminPanel();
}
void deleteflight(){
	char deletecode[50], yesno;
	int found = 0;

	printf("Flight code of the record you want to delete: ");
	scanf("%s", deletecode);

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
			printf("Flight Code: %s deleted...\n", deletecode);}
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
	sleep(3); 
	adminPanel();}
	else if (yesno == 'n'){
		printf("Answered No\n");
		printf("Directing to admin panel...");
		sleep(3); 
		adminPanel();
	}
	else {
		printf("Invalid Option\n");
		printf("Directing to admin panel...");
		sleep(3); 
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
		cancelBooking();
	}
	else if (passenger_choice == 3) {
		listBookedFlights();
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
	char flightnum[6];
	char name[20], id[20];
	int selectedSeat, bookingID;

	clear();

	printf("\n Please provide departure and destination airport information\n\n");
	printf("Departure: ");
	scanf("%s", departure);
	printf("\nDestination: ");
	scanf("%s", destination);

    filterFlights(departure, destination);

	while (true) {
		int select, flag;

		printf("\n1- Continue");
		printf("\n9- Return to main menu\t");
		scanf("%d", &select);

		if (select == 1){
			printf("\nSelect flight - Enter the flight number: ");
			scanf("%s", flightnum);
			flag = checkSeats(flightnum);

			if (flag == 1){
				break;
			}
			else if (flag == 0){
				printf("\nThis flight is full, consider another option\n");
			}
		}
		else if (select == 9){
			passengerMenu();
		}
		else {
			printf("\nInvalid option");
		}
	}
	printf("\n\nPlease select a seat: ");
	scanf("%d", &selectedSeat);

	printf("\n\nYour name: ");
	scanf("%s", name);
	printf("\nYour ID number: ");
	scanf("%s", id);
	
	const char* bookingid = assignBookingID();
	printf("\n Your booking id is: %s", bookingid);	
	
	struct Ticket newticket;
	strcpy(newticket.bookingID, bookingid);
	strcpy(newticket.flight_num, flightnum);
	strcpy(newticket.name, name);
	strcpy(newticket.id, id);
	newticket.seat_num = selectedSeat;

	FILE *addfile;
	addfile = fopen("tickets.txt","a+");
	fwrite(&newticket, sizeof(struct Flight),1, addfile);		
	fclose(addfile);

	printf("\n\nYour booking is successful \n");
	sleep(2);
	passengerMenu();
}

void filterFlights(char departure[50], char destination[50])
{
	int found = 0;
	
	struct Flight filter;
	FILE *filefilter;
	filefilter = fopen("flights.txt","r");

    printf("\n\n\tFlight Code\t\tDeparture\t\tDestination\t\tDeparture Time\t\t Arrival Time\n");
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

int checkSeats(char flightnum[6])
{	
	clear();

	int CAPACITY;
	struct Flight cap;
	FILE *fileseatcap;
	fileseatcap = fopen("flights.txt", "r");

	while (fread(&cap, sizeof(struct Flight), 1, fileseatcap)){
		if (strcmp(cap.flight_code, flightnum) == 0){
			CAPACITY = atoi(cap.passenger_capacity);
		}
	}
	int count = 0;
	int seats_taken[CAPACITY+1];
	int available_seats[CAPACITY+1];

	struct Ticket check;
	FILE *filecheck;
	filecheck = fopen("tickets.txt","r");

	while (fread(&check, sizeof(struct Ticket), 1, filecheck)){
		if (strcmp(check.flight_num, flightnum) == 0){
			seats_taken[count] = check.seat_num;
			count++;
		}}
	if (count == CAPACITY){
		printf("seats are full");
		return 0;
	}
	
	fclose(filecheck);
	int SIZE = sizeof seats_taken / sizeof *seats_taken;
	int found, i=0, seat=1, j=0;

	for (seat=1; seat<=CAPACITY; seat++){
		found = 0;
		for (j=0; j<SIZE; j++){
			if (seat == seats_taken[j]){
				found = 1;
			}
		}
		if (found == 0){
			available_seats[i] = seat;
			i++;
		}
	}
	CAPACITY = CAPACITY - count + 1;
	printf("\nAvailable seats: ");
	int itr=0;
	for (itr=0; itr<CAPACITY; itr++){
		printf("%d  ", available_seats[itr]);
	}
	return 1;
}

const char * assignBookingID()
{
	static char bookingid[6];
	int idint;
	FILE *fileassign, *filenewid;
	fileassign = fopen("bookingid.txt", "r");

	fscanf(fileassign, "%s", bookingid);
	idint = atoi(bookingid);
	idint++;
	sprintf(bookingid, "%d", idint);
	filenewid = fopen("bookingid.txt", "w");
	fprintf(filenewid, "%s", bookingid);

	fclose(fileassign);
	fclose(filenewid);

	return bookingid;
}

void cancelBooking()
{
	static char bookingid[6];

	clear();
	printf("\nYour booking id: ");
	scanf("%s", bookingid);

	deleteTicket(bookingid);
}

void deleteTicket(char bookingid[6])
{
	int found = 0;
	char yesno;

	struct Ticket del;
	FILE *filedel, *tempfile;
	filedel = fopen("tickets.txt", "r");
	tempfile = fopen("temp.txt","w");

	while (fread(&del, sizeof(struct Ticket), 1, filedel)){
		if (strcmp(del.bookingID, bookingid) == 0){
			found = 1;
			printf("Your booking will be canceled\n");
			printf("Are you sure?(y/n): ");
			scanf(" %c", &yesno);

			if (yesno == 'y') {
				printf("\n\nYour booking is canceled");
			}
		}
		else 
			fwrite(&del, sizeof(struct Ticket), 1, tempfile);
	}
	if (found == 0)
		printf("\n\nNo ticket found with this booking id\n");

	fclose(filedel);
	fclose(tempfile);

	remove("tickets.txt");
	rename("temp.txt","tickets.txt");
	sleep(3);
	passengerMenu();
}

void listBookedFlights()
{
	static char name[30], id_num[30];
	int detailed;

	clear();
	printf("\nYour name: ");
	scanf("%s", name);
	printf("\nYour ID: ");
	scanf("%s", id_num);

	const char* flight_num = checkTicket(name, id_num);
	sleep(5);
	
	printf("\n\nPress '1' for more detailed flight information or '0' to return to main menu: ");
	scanf("%d", &detailed);

	if (detailed == 1){
		displayFlightInfo(flight_num);
	}
	else if (detailed == 0)
		main();



}

const char * checkTicket(char name[30], char id_num[30])
{
	int found = 0;
	static char flight_num[20];

	struct Ticket filter;
	FILE *filefilter;
	filefilter = fopen("tickets.txt","r");

    printf("\n\n\tBooking ID\t\tFlight Number\t\tName\t\tID\t\tSeat Number\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");

	while (fread(&filter,sizeof(struct Ticket),1,filefilter)){
		if (strcmp(filter.name, name) == 0 && strcmp(filter.id, id_num) == 0){
			found = 1;
			flight_num[20] = filter.flight_num;
			printf("\t%s\t\t\t%s\t\t%s\t\t\t%s\t\t%s\n", filter.bookingID, filter.flight_num, filter.name, filter.id, filter.seat_num);
		}	
	}
    printf("\n\n\n");
	if (found == 0)
		printf("\nNo flight found\n\n");

	fclose(filefilter);

	return flight_num;
}

void displayFlightInfo(const char* flight_num)
{
	struct Flight info;
	FILE *fileinfo;
	fileinfo = fopen("flights.txt","r");

	while (fread(&info,sizeof(struct Flight),1,fileinfo)){
		if (strcmp(info.flight_code,flight_num) == 0) {
			printf("\nAirline: %s\nFlight Code: %s\nDeparture Airport: %s\nDestination Airport: %s\nDeparture Time: %s\nArrival Time: %s\nPassenger Capacity: %s\n-------------------------------------\n",info.airline,info.flight_code,info.departure_airport,info.destination_airport,info.time_of_departure,info.time_of_arrival,info.passenger_capacity);
        }	
	}
}

void a_listbookings(){
	FILE *listbookings;
	listbookings = fopen("booking","r");
	struct Ticket listticket;
	printf("Bookings");
	printf("| Booking ID  | Flight Number | Passenger Name | Passenger ID | Seat Number |");
	printf("---------------");
	while (fread(&listticket,sizeof(struct Ticket),1,listbookings)){
		printf("| %s | %s | %s | %s | %d |");
	}
	fclose(listbookings);
}
