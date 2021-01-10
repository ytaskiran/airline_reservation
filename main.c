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

int mainMenu(); // Main welcome -> -Admin menu -Passenger Menu -Quit
void adminPanel(); // Admin Menu ->  -Add/Edit/Delete flights -List available flights -List current bookings -Change admin password 
void passwordCheck(); // Password control
void addFlight(); // Add flight 
void deleteflight(); // Delete an existing flight 
void editFlight(); // Edit an existing flight feature 
void listflight(int opt); // Listing flights
void listBookings(); // Listing ticket&booking informations
void changePass(); // Change admin password
void passengerMenu(); // Passenger Menu -> -Book a flight -Cancel a booking -List booked flights
void bookFlight(); // Core function for booking a flight
void filterFlights(char departure[50], char destination[50]); // Filters flights according to the departure and destination location information
int checkSeats(char flightnum[6]); // Checks available seats of a flight
const char * assignBookingID(); // Assigns a booking ID 
void cancelBooking(); // Cancels existing booking
void deleteTicket(char bookingid[6]); // Subsidiary function for cancelBooking()
void listBookedFlights(); // Lists booked flights for a passenger 
void checkTicket(char name[30],char id_num[30]); // Subsidiary function of listBookedFlights(). Checks database for ticket information
void displayFlightInfo(const char* flight_num); // Subsidiary function for displaying detailed information about flight for a given ticket.

struct Flight{  // Struct data initialization for flight database
char airline[50];
char flight_code[50];
char departure_airport[50];
char destination_airport[50];
char time_of_departure[50];
char time_of_arrival[50];
char passenger_capacity[50];
};

struct Ticket{ // Struct data initialization for ticket database
char bookingID[10];
char flight_num[10];
char name[50];
char id[20];
int seat_num;
};


#if defined(_WIN32) // Terminal clear command function for windows
	void clear(){
		system("cls");
	}
#elif defined(__linux__) // Terminal clear command function for linux
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
		main();
	}
	else if (choice == 2){
	    passengerMenu();
		main();
	}
	else if (choice == 3){
		clear();
		exit(1);
	}
	else{ 
	    printf("Please enter a valid value\n");
		main();
	}
    return 0;
}

int mainMenu() 
{   /*
	Entrance display. Takes input from
	user to go to the desired menu.
	Returns choice to main.
	*/
    int choice;
    clear();
    printf( "\n\n**********************************************************************************\n");
    printf( "**********************************************************************************\n");
    printf( "**********\t\t\t\t\t\t\t\t**********\n");
    printf( "**********\tWELCOME TO THE PISMANIYE AIRLINE RESERVATION SYSTEM\t********** \n");
    printf( "**********\t\t\t\t\t\t\t\t**********\n");
    printf( "**********************************************************************************\n");
    printf( "**********************************************************************************\n");
    printf( "\n\n\t1- Admin Panel\n");
    printf( "\t2- Passenger Menu\n ");
	printf("\t3- Quit\n\n\n ");
    printf("Select your menu: ");
    scanf("%d", &choice);

    return choice;
}

void passwordCheck()
{	/*
	Checks the password taken is true or not
	based on the password determined before 
	*/
	FILE *checkpas;
    char real_pw[20]; // true password
    char input_pw[20]; // password taken from the user
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
                    exit(1); // If the password is given wrong 5 times, the system kicks the user out of the system
                }
                else { 
                    printf("Password is not correct, please try again.\n\n");
                }
            }} while (true);  
}

void adminPanel(){
	/*
	Admin Menu Center
	*/		
	int admin_choice, inp;

    clear();

    printf("\n   Welcome to Admin Panel\n\n");
    printf("1- Add a new flight\n");
	printf("2- Edit a flight\n");
    printf("3- Delete an existing flight\n");
    printf("4- List available flights\n");
    printf("5- List current bookings\n");
    printf("6- Change admin password\n\n");
	printf("9- Return to Main Menu \n\n\n");
    printf("Select an Option: ");
    scanf("%d",&inp);

	admin_choice = inp; // this step which seems unnecessary, helps the program to prevent string inputs.

	if (admin_choice == 1){
		addFlight();
	}
    else if (admin_choice == 2){
        editFlight();
	}
    else if (admin_choice == 3){
		deleteflight();
		main();
	}	
    else if (admin_choice == 4){
    	listflight(1);
	}
	else if (admin_choice == 5){
    	listBookings();
	}
	else if (admin_choice == 6){
       	changePass();
	}
	else if (admin_choice == 9){
    	main();
	}				
    else {
       	printf("Invalid option");
	}
}

void changePass(){
	/*
	Function for changing admin password
	and save it to the database
	*/
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
			printf("Directing to Main Menu");
			sleep(2);
			main();
		}
		else{
			printf("Different passwords have been entered\n");
			printf("Directing to Main Menu...");
			sleep(2);
			main();
		}
		}
	else {
		printf("Wrong Password\n");
		printf("Directing to Main Menu...");
		sleep(2);
		main();
	}
}

void addFlight(){
	/*
	Add new flight and save it 
	to the database from admin panel
	*/
	char airline[50],flight_code[50],departure_ap[50],destination_ap[50],departure_time[50],arrival_time[50],capacity[50];

	clear();

	printf("\nEnter the informations to add a new flight\n\n\n");
	printf("Airline: ");
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

void listflight(int opt){
	/*
	Lists existing flights in the database
	*/
	FILE *reading;
	struct Flight d2;
	reading = fopen("flights.txt","r");
	int i=1;
	while (fread(&d2,sizeof(struct Flight),1,reading)){
		printf("\nFlight %d\nAirline: %s\nFlight Code: %s\nDeparture Airport: %s\nDestination Airport: %s\nDeparture Time: %s\nArrival Time: %s\nPassenger Capacity: %s\n-------------------------------------\n",i,d2.airline,d2.flight_code,d2.departure_airport,d2.destination_airport,d2.time_of_departure,d2.time_of_arrival,d2.passenger_capacity);
		i++;
	}
	int dummy;

	if (opt == 1){
		do{
			printf("Press 0 to continue Main Menu\n");
			printf("Press 1 to continue Admin Panel\nChoice: ");

			scanf(" %d",&dummy);

			if (dummy == 0)
				main();

			else if (dummy == 1)
				adminPanel();

			else
				printf("\n\nInvalid Option\nPlease Try Again\n\n");

		}while ((dummy != 9) && (dummy != 8 ));
	}
}

void editFlight(){
	/*
	Edit a flight feature from admin panel
	*/
	int edchoice,found = 0;
	char newfeature[50], edflightchoice[50];
	clear();

	printf("----Edit Flight Screen----\n");
	listflight(0);
	printf("Enter Flight Code to select an flight:\n");
	scanf("%s", edflightchoice);

	clear();

	printf("Flight Code: %s selected\n",edflightchoice);
	printf("0- Return to Admin Panel\n");
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
				editFlight();
			}			
			fwrite(&edit,sizeof(struct Flight),1,tempfile);
			printf("Changes Saved\n");
	}
		else 
			fwrite(&edit,sizeof(struct Flight),1,tempfile);
	}
	if (found == 0){
		printf("No flight found");
		editFlight();
}
	fclose(f_edit);
	fclose(tempfile);

	remove("flights.txt");
	rename("temp.txt","flights.txt");
	printf("Directing to Admin Panel...");

	sleep(2); 
	adminPanel();
}
void deleteflight(){
	/*
	Delete a flight from database
	*/
	char deletecode[50], yesno;
	int found = 0;

	listflight(0);

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
	printf("Directing to Admin Panel...");
	sleep(3); 
	adminPanel();
	}

	else if (yesno == 'n'){
		printf("\nDirecting to Admin Panel...");
		sleep(3); 
		adminPanel();
	}
	else {
		printf("\nInvalid Option\n");
		printf("Directing to Admin Panel...");
		sleep(3); 
		adminPanel();
	}
}

void passengerMenu() 
{	
	/*
	Passenger Menu Entrance
	*/
	int passenger_choice, inp;

	clear();

	printf("\n   Passenger Menu\n\n");
	printf("1- Book a flight\n");
	printf("2- Cancel a booking\n");
	printf("3- List booked flights\n");
	printf("\n9- Return to Main Menu\n\n");
	printf("Select an option: ");
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
{	/*
	Booking a flight 
	*/
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

	while (true) {
		int select, flag;

		filterFlights(departure, destination); //Display the flights for desired departure and destination location

		printf("\n1- Continue");
		printf("\n9- Return to Main Menu\n\n-> ");
		scanf("%d", &select);

		if (select == 1){
			printf("\nSelect flight - Enter the flight code: ");
			scanf("%s", flightnum);
			flag = checkSeats(flightnum); // Checks available seats for corresponding flight

			if (flag == 1){
				break; // Flag 1, flight capacity is not full, break the loop and go on to next steps
			}
			else if (flag == 0){
				printf("\nThis flight is full, consider another option\n"); // Flag 0 means there is not any available seat for
			}																// corresponding flight, loop makes user to choose another option
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
	
	const char* bookingid = assignBookingID(); // Function returns a unique booking id
	printf("\nYour booking id is: %s", bookingid);	
	
	struct Ticket newticket; // Store the booking informations to database
	strcpy(newticket.bookingID, bookingid);
	strcpy(newticket.flight_num, flightnum);
	strcpy(newticket.name, name);
	strcpy(newticket.id, id);
	newticket.seat_num = selectedSeat;

	FILE *addfile;
	addfile = fopen("tickets.txt","a+");
	fwrite(&newticket, sizeof(struct Ticket),1, addfile);		
	fclose(addfile);

	printf("\n\nYour booking is successful \n");
	sleep(2);
	passengerMenu();
}

void filterFlights(char departure[50], char destination[50])
{	/*
	Filters flights that covers desired
	departure and destination points and 
	display them to user
	*/
	int found = 0;
	
	struct Flight filter;
	FILE *filefilter;
	filefilter = fopen("flights.txt","r");

    printf("\n\n\tFlight Code\t\tDeparture\t\tDestination\t\tDeparture Time\t\t Arrival Time\t\tAirline\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");

	while (fread(&filter,sizeof(struct Flight),1,filefilter)){
		if (strcmp(filter.departure_airport,departure) == 0 && strcmp(filter.destination_airport, destination) == 0){
			found = 1;
			printf("\t%s\t\t\t%s\t\t%s\t\t\t%s\t\t%s\t\t%s\n", filter.flight_code, filter.departure_airport, filter.destination_airport, filter.time_of_departure, filter.time_of_arrival, filter.airline);
        }	
	}
    printf("\n\n\n");
	if (found == 0)
		printf("\nNo flight found\n\n");

	fclose(filefilter);
}

int checkSeats(char flightnum[6])
{	/*
	Checks available seats for
	a given flight number (code)
	*/
	clear();

	int CAPACITY;
	struct Flight cap;
	FILE *fileseatcap;
	fileseatcap = fopen("flights.txt", "r");

	while (fread(&cap, sizeof(struct Flight), 1, fileseatcap)){
		if (strcmp(cap.flight_code, flightnum) == 0){
			CAPACITY = atoi(cap.passenger_capacity); //convert to int
		}
	}
	int SIZE = 0;
	int seats_taken[CAPACITY+1];
	int available_seats[CAPACITY+1];

	struct Ticket check;
	FILE *filecheck;
	filecheck = fopen("tickets.txt","r");

	while (fread(&check, sizeof(struct Ticket), 1, filecheck)){
		if (strcmp(check.flight_num, flightnum) == 0){
			seats_taken[SIZE] = check.seat_num;
			SIZE++;
		}}
	fclose(filecheck);

	if (SIZE == CAPACITY){
		printf("Seats are full\n");
		return 0;
	}

	else if (SIZE == 0){
		int x=0;
		printf("\nAvailable seats: ");
		for (x=1; x<=CAPACITY; x++){
			printf("%d ", x);
		}
		return 1;
	}
	
	
	else {
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
		printf("\nAvailable seats: ");
		int itr=0;
		for (itr=0; itr<i; itr++){
			printf("%d  ", available_seats[itr]);
		}
		return 1;
	}
}

const char * assignBookingID()
{	
	/*
	Assigns a unique booking id
	for passenger's ticket
	*/
	char bookingid[10];
	static char id[10];
	int idint;
	FILE *fileassign, *filenewid;
	fileassign = fopen("bookingid.txt", "r");

	fscanf(fileassign, "%s", bookingid);
	strcpy(id, bookingid);
	idint = atoi(bookingid);
	idint++;
	sprintf(bookingid, "%d", idint);
	filenewid = fopen("bookingid.txt", "w");
	fprintf(filenewid, "%s", bookingid);

	fclose(fileassign);
	fclose(filenewid);

	return id;
}

void cancelBooking()
{	/*
	Cancels existing ticket
	from passenger menu
	*/
	static char bookingid[6];

	clear();
	printf("\nYour booking id: ");
	scanf("%s", bookingid);

	deleteTicket(bookingid);
}

void deleteTicket(char bookingid[6])
{	/*
	Subsidiary function for cancellation
	*/
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
{	/*
	Lists booked flights for 
	a passenger given his/her 
	name and id
	*/
	static char name[30], id_num[30];
	char flightnum[20];
	int choice;

	clear();
	printf("\nYour name: ");
	scanf("%s", name);
	printf("\nYour ID: ");
	scanf("%s", id_num);

	checkTicket(name, id_num);

	while (true){
		printf("\n\nPress '1' for more detailed flight information or '0' to return to Main Menu: ");
		scanf("%d", &choice);

		if (choice == 1){
			printf("\nFlight code: ");
			scanf("%s", flightnum);
			displayFlightInfo(flightnum);
		}
		else if (choice == 0)
			break;
	}
}

void checkTicket(char name[30], char id_num[30])
{	/*
	Checks database and returns
	ticket informations
	*/
	int found = 0;
	static char flight_num[20];

	struct Ticket filter;
	FILE *filefilter;
	filefilter = fopen("tickets.txt","r");

    printf("\n\n\tBooking ID\t\tFlight Code\t\tName\t\tID\t\tSeat Number\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");

	while (fread(&filter,sizeof(struct Ticket),1,filefilter)){
		if (strcmp(filter.name, name) == 0 && strcmp(filter.id, id_num) == 0){
			found = 1;
			printf("\t%s\t\t\t%s\t\t\t%s\t\t%s\t\t%d\n", filter.bookingID, filter.flight_num, filter.name, filter.id, filter.seat_num);
		}	
	}
    printf("\n\n\n");
	if (found == 0)
		printf("\nNo flight found\n\n");

	fclose(filefilter);
}

void displayFlightInfo(const char* flight_num)
{	/*
	Display detailed flight information
	*/
	struct Flight info;
	FILE *fileinfo;
	fileinfo = fopen("flights.txt","r");

	while (fread(&info,sizeof(struct Flight),1,fileinfo)){
		if (strcmp(info.flight_code,flight_num) == 0) {
			printf("\nAirline: %s\nFlight Code: %s\nDeparture Airport: %s\nDestination Airport: %s\nDeparture Time: %s\nArrival Time: %s\nPassenger Capacity: %s\n-------------------------------------\n",info.airline,info.flight_code,info.departure_airport,info.destination_airport,info.time_of_departure,info.time_of_arrival,info.passenger_capacity);
        }	
	}
}

void listBookings(){
	char choice;

	FILE *listbookings;
	listbookings = fopen("tickets.txt","r");
	struct Ticket listticket;
	printf("|  Booking ID   |  Flight Code  |  Passenger Name  |  Passenger ID  |  Seat Number  |");
	printf("\n--------------------------------------------------------------------------------------\n");
	while (fread(&listticket,sizeof(struct Ticket),1,listbookings)){
		printf("|\t%s\t|\t%s\t|\t%s\t   |\t  %s\t    |\t   %d\t  |\n", listticket.bookingID, listticket.flight_num, listticket.name, listticket.id, listticket.seat_num);
	}
	fclose(listbookings);
	printf("\n\nPress any key to return Admin Panel -> ");
	scanf(" %c", &choice);
	passengerMenu();
}
