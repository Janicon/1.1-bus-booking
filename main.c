/*
	Description			: This is a program that tracks bus booking transactions. Booked seats will retain until
							program is closed.
	Programmed by		: Jan Ambro P. Canicon | CS-STS X22
	Last modified		: December 7, 2019
	Version				: 1.2.2		Fixed a bug where a character entered in request for booked seats
										(in printTransactBookSeats) would function
				12-05-19  1.2.1		Code clean-up and additional comments
									Fixed bug where termination would loop back to some functions.
				12-03-19  1.2.0		Added a portion for testing in main where values in structs can be changed
									Bug fixes in booking page
				12-02-19  1.1.1		Cleaned up code-Renamed variables and functions, added comments
				11-30-19  1.1.0		Added additional choices to directory.
									Cleaned up loops.
				11-27-19  1.0.0		Finished program.
									Finished data saving/transferring for booking and summary page. 
				11-26-19  0.4.0		Created array struct array to share variables across functions.
									Created framework for booking and summary page.
				11-19-19  0.3.1		Bug fixes: Loops in booking redone.
				11-17-19  0.3.0		Restructured the program—moved loops to functions instead of main function.
				11-12-19  0.2.0		Created structure of trip details, incorporated struct and array to functions.
				11-05-19  0.1.1		Linked print functions together with loops and conditionals.
				10-10-19  0.1.0		Created basic functions to print displays		
	[Acknowledgements	: Borrowed libraries:
							stdio.h, stdlib.h, conio.h
						  References:
						  	http://www.cplusplus.com/reference/cstdio/
						  	http://www.dev-hq.net/c++/
						  	https://fresh2refresh.com/c-programming/c-array/
						  	https://www.javatpoint.com/array-of-structures-in-c
						  	https://www.programiz.com/c-programming
						  	https://www.programmingsimplified.com/c/conio.h/getch
							https://stackoverflow.com/
							https://www.tutorialspoint.com/c_standard_library/index.htm	
	]
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*	@param bus[i].seats.nTransactions represents the number of transactions made for a bus line, as well as
	keeping count of which array element to use for booking seats	*/
#define ITERATION bus[i].seats.nTransactions

/*		-----This marks the start of structure definitions-----		*/
struct seating
{
	int nCapacity;
	int nSpace;
	int nBooked[52];
	int nTransactions;
};

struct busDetails
{
	int nCode;
	struct seating seats;
	float fPrice;
	char cStationD[15];
	char cStationA[15];
	char cTimeD[10];
	char cTimeA[10];
};
/*		-----This marks the end of structure definitions-----		*/

/*		-----This marks the start of function prototype declarations-----
		---Section 1 of function prototype declarations [Print functions]---		*/
void printMenuSelect(struct busDetails bus[]);
void printDepartSelect (struct busDetails bus[]);
void printArriveSelect (struct busDetails bus[], int nDepStation);
void printRouteDetails(struct busDetails bus[], int nDepStation, struct busDetails bus1, struct busDetails bus2);
void printTransactBookCode(struct busDetails bus[]);
void printTransactBookSeats(struct busDetails bus[], int nCode, struct busDetails busN);
void printTransactSummary(struct busDetails bus[]);
void printTransactPricing(struct busDetails bus);
void printErrorMessage();
void printTermination(struct busDetails bus[]);
	
/*		---Section 2 of function prototype declarations [Process functions]---		*/
int getSpace(int i, struct seating seats[]);
void transferInput(struct busDetails bus[], int nBookedSeats, struct busDetails busN);
void saveBooking(struct busDetails bus[]);
int checkSpaceLeft(struct busDetails bus[]);
/*		-----This marks the end of the function prototype declarations-----		*/



/*		-----This marks the start of the program-----		*/
int main()
{
	/*---Initialization of structs---*/
	/*This is the structure that contains seat details*/
	struct seating seats[12] = 
	{
	/*---Struct manipulation (for testing) - change letters to manipulate values inside the struct---
		Example: {a, b, c, d}
			a:	Maxmimum capacity
			b:	Seats left (Manipulation not recommended)
			c:	Individual transaction records - Change as an array {x, y, z, ...}
			d:	Booking count - Must be set equal to the number of elements in c	*/
			
		{52, 0, {0}, 0}, //1102
		{50, 0, {0}, 0}, //1103
		{52, 0, {0}, 0}, //2102
		{50, 0, {0}, 0}, //2103
		
		{52, 0, {0}, 0}, //1201
		{46, 0, {0}, 0}, //1203
		{52, 0, {0}, 0}, //2201
		{46, 0, {0}, 0}, //2203
		
		{50, 0, {0}, 0}, //1301
		{46, 0, {0}, 0}, //1302
		{50, 0, {0}, 0}, //2301
		{46, 0, {0}, 0}  //2302
	};
	
	/*This is the structure that contains bus line details
		Contents: bus code, structure of seat details, ticket price,
		departure station, arrival station time of departure, time of arrival*/
	struct busDetails bus[12] =
	{
		{1102, seats[0], 25.00, "San Pedro", "Santa Rosa", "6:00 AM", "6:25 AM"},
		{1103, seats[1], 30.00, "San Pedro", "Calamba", "6:00 AM", "6:40 AM"},
		{2102, seats[2], 25.00, "San Pedro", "Santa Rosa", "6:00 PM", "6:25 PM"},
		{2103, seats[3], 30.00, "San Pedro", "Calamba", "6:00 PM", "6:40 PM"},
		
		{1201, seats[4], 25.00, "Santa Rosa", "San Pedro", "6:30AM", "7:00 AM"},
		{1203, seats[5], 25.00, "Santa Rosa", "Calamba", "6:00 AM", "6:25 AM"},
		{2201, seats[6], 25.00, "Santa Rosa", "San Pedro", "6:30PM", "7:00 PM"},
		{2203, seats[7], 25.00, "Santa Rosa", "Calamba", "6:00 PM", "6:25 PM"},
		
		{1301, seats[8], 30.00, "Calamba", "San Pedro", "6:45 AM", "7:30 AM"},
		{1302, seats[9], 25.00, "Calamba", "Santa Rosa", "6:30 AM", "7:00 AM"},
		{2301, seats[10], 30.00, "Calamba", "San Pedro", "6:45 PM", "7:30 PM"},
		{2302, seats[11], 25.00, "Calamba", "Santa Rosa", "6:30 PM", "7:00 PM"}
	};	
	
	/*---Declaration of variables---*/
	int i;
	
	/*---Execution of program---*/
	/*This loop goes through every element in bus[] and sets the respective seats left based on the
		number of seats booked (Default set to 0)*/
	for(i = 0; i < 12; i++)
	{
		bus[i].seats.nSpace = getSpace(i, seats);
	}
	
	printMenuSelect(bus);
}
/*		-----This marks the end of the program-----		*/



/*		-----This marks the start of function definitions-----		*/
/*		---Section 1 of function definitions[Print functions]---		*/

/*	This function prints the opening screen of the booking app
	Pre-condition: Number of available seats in any bus is greater than 0
	@param bus[] is an array of structures to allow all structure data to be passed when switching functions
*/
void printMenuSelect(struct busDetails bus[])
{
	char cInput;
	
	/*If there are seats left in any bus line, the opening page loop is started*/
	if(checkSpaceLeft(bus) > 0)	
		do
		{
			system("cls");
			printf("[R]eset app\n");
			printf("[X]Terminate app\n\n");
			printf("----- OnTime APP -----\n\n");
			printf("What do you want to do?\n");
			printf("	[D]isplay schedule\n");
			printf("	[B]ook seats\n\n");
			printf("	[E]xit\n\n\n");
			printf("Choice: ");
			scanf("%c", &cInput);
			fflush(stdin);
			
			switch(cInput)
			{
				case 'd':
				case 'D': printDepartSelect(bus); break;
				case 'b':
				case 'B': printTransactBookCode(bus); break;
				case 'e':
				case 'E': printTransactSummary(bus); break;
				case 'r': 
				case 'R': main(); break;
				case 'x':
				case 'X': break;
				default: printErrorMessage();
			}
		}while(cInput != 'x' && cInput != 'X');
		
	printTermination(bus);
}

/*	This function lets the user select a departure station
	Pre-condition: Char 'D' or 'd' is input in printMenuSelect
	@param bus[] is an array of structures to allow all structure data to be passed when switching functions
*/	
void printDepartSelect (struct busDetails bus[])
{
	int nInput;
	
	/*Prints the departure station selection page and indefinitely loops it until another function is called*/
	do
	{
	system("cls");
	printf("----- DISPLAY SCHEDULE -----\n");
	printf("Pick departure station\n");
	printf("	[1] San Pedro\n");
	printf("	[2] Santa Rosa\n");
	printf("	[3] Calamba\n\n");
	printf("	[7] Menu\n");
	printf("	[8] Book Seats\n");
	printf("	[9] Go Back\n");
	printf("	[0] Exit\n\n");
	printf("Choice: ");
	scanf("%d", &nInput);
	fflush(stdin);
	
		switch(nInput)
		{
			case 1: 
			case 2: 
			case 3: printArriveSelect(bus, nInput); break;
			case 7: printMenuSelect(bus); break;
			case 8: printTransactBookCode(bus); break;
			case 9: printMenuSelect(bus); break;
			case 0: printTransactSummary(bus); break;
			default: printErrorMessage(bus);
		}
	}while(1);
}

/*	This function lets the user select an arrival station
	Pre-condition:Integer inclusive of 1 and 3 is input in printDepartSelect
	@param bus[] is an array of structures to allow structure data to be passed when switching functions
	@param cDepStation retains the data for the choice of departure station
*/
void printArriveSelect (struct busDetails bus[], int nDepStation)
{
	int nInput;
	
	/*Prints the arrival station selection page and indefinitely loops it until another function is called*/			
	do
	{
		system("cls");
		printf("----- DISPLAY SCHEDULE -----\n");
		printf("Pick arrival station\n");
	
		/*Prints departure stations except for the one chosen as the departure station*/	
		if(nDepStation != 1)
			printf("	[1] San Pedro\n");
		if(nDepStation != 2)
			printf("	[2] Santa Rosa\n");	
		if(nDepStation != 3)
			printf("	[3] Calamba\n");

		printf("\n");
		printf("	[7] Menu\n");
		printf("	[8] Book Seats\n");
		printf("	[9] Go Back\n");
		printf("	[0] Exit\n\n");
		printf("Choice: ");
		scanf("%d", &nInput);
		fflush(stdin);
		
		/*Multiple switch cases depending on which departure station was selected*/
		if(nDepStation == 1)
		{
			switch(nInput)
			{
				case 2: printRouteDetails(bus, nDepStation, bus[0], bus[2]); break;
				case 3: printRouteDetails(bus, nDepStation, bus[1], bus[3]); break;
				case 7: printMenuSelect(bus); break;
				case 8: printTransactBookCode(bus); break;
				case 9: printDepartSelect(bus); break;
				case 0: printTransactSummary(bus); break;
				default: printErrorMessage();
			}
		}
		
		if(nDepStation == 2)
		{
			switch(nInput)
			{
				case 1: printRouteDetails(bus, nDepStation, bus[4], bus[6]); break;
				case 3: printRouteDetails(bus, nDepStation, bus[5], bus[7]); break;
				case 7: printMenuSelect(bus); break;
				case 8: printTransactBookCode(bus); break;
				case 9: printDepartSelect(bus); break;
				case 0: printTransactSummary(bus); break;
				default: printErrorMessage();
			}
		}
		
		if(nDepStation == 3)
		{
			switch(nInput)
			{
				case 1: printRouteDetails(bus, nDepStation, bus[8], bus[10]); break;
				case 2: printRouteDetails(bus, nDepStation, bus[9], bus[11]); break;
				case 7: printMenuSelect(bus); break;
				case 8: printTransactBookCode(bus); break;
				case 9: printDepartSelect(bus); break;
				case 0: printTransactSummary(bus); break;
				default: printErrorMessage();
			}
		}		
	}while(1);	
}

/*	This function prints the details of a bus line from some departure station to another arrival station
	Pre-condition: Two different integers, inclusive of 1 and 3, are input in printDepartSelect and printArriveSelect
	@param bus[] is an array of structures to allow all structure data to be passed when switching functions
	@param cDepStation retains the data for the choice of departure station
	@param bus1 contains the first bus line's data in a structure
	@param bus2 contains the second bus line's data in a structure
*/
void printRouteDetails (struct busDetails bus[], int nDepStation, struct busDetails bus1, struct busDetails bus2)
{
	int nInput;
	
	/*Prints the bus details page and indefinitely loops it until another function is called*/
	do
	{	
	system("cls");
	printf("----- DISPLAY SCHEDULE -----\n\n");
	printf("Departure Station:	%s\n", bus1.cStationD);
	printf("Arrival Station:	%s\n\n", bus1.cStationA);
	printf("-----------------------------------------------\n");
	printf("CODE	ETD	ETA	Seats Left	Price\n");
	printf("-----------------------------------------------\n");
	printf("%d	%s	%s	   %d		%.2f\n", bus1.nCode, bus1.cTimeD, bus1.cTimeA, bus1.seats.nSpace, bus1.fPrice);
	printf("%d	%s	%s	   %d		%.2f\n", bus2.nCode, bus2.cTimeD, bus2.cTimeA, bus2.seats.nSpace, bus2.fPrice);
	printf("-----------------------------------------------\n\n");
	
	printf("	[7] Menu\n");
	printf("	[8] Book Seats\n");
	printf("	[9] Go Back\n");
	printf("	[0] Exit\n\n");
	printf("Choice: ");
	scanf("%d", &nInput);
	fflush(stdin);
	
		switch(nInput)
		{
			case 7: printMenuSelect(bus); break;
			case 8: printTransactBookCode(bus); break;
			case 9: printArriveSelect(bus, nDepStation); break;
			case 0: printTransactSummary(bus); break;
			default: printErrorMessage();
		}
	}while(1);	
}

/*	This function prints the first part of the booking page where the program requests for a bus code
	Pre-condition: nCode matches a member in the structure bus[]
	@param bus[] is an array of structures to allow all structure data to be passed when switching functions
*/
void printTransactBookCode(struct busDetails bus[])
{
	int nCode, i;
	
	/*Prints the first part of the booking page where the program asks for the bus code to book seats in
		Loops until 0 is entered, wherein it will return to the opening screen*/
	do
	{	
		system("cls");
		printf("----- BOOK SEATS -----\n");
		printf("Book through Bus Code\n\n");
		
		printf("Enter [0] to cancel\n");
		printf("Bus Code: ");
		scanf("%d", &nCode);
		fflush(stdin);
		
		/*This loop checks if the given bus code matches a bus code initialized in an element of bus[].
			If there is a matching code, it switches to another function*/
		for(i = 0; i < 12; i++)
			if(nCode == bus[i].nCode)
				{
					/*Calls a function that prints the details of the bus if there are available seats, otherwise 
						prints that the selected bus line is fully booked before asking for a bus code again*/
					if(bus[i].seats.nSpace > 0)
						printTransactBookSeats(bus, nCode, bus[i]);
					else
					{
						printf("\nThis bus line is fully booked.\n");
						printf("Press any key to continue...");
						getch();
						printTransactBookCode(bus);
					}
				}
		
		if(nCode != 0)
			printErrorMessage();
	}while(nCode != 0);
	
	printMenuSelect(bus);	
}		

/*	This function prints the second part of the booking page where the program requests for seats to book and for
		booking confirmation
	Pre-condition: nSeats is a non-negative integer
	@param bus[] is an array of structures to allow structure data to be passed when switching functions
	@param nCode retains the bus code requested in the first booking page
	@param busN is the structure corresponding to the bus code in nCode
*/
void printTransactBookSeats(struct busDetails bus[], int nCode, struct busDetails busN)
{
	int nInput;
	int nSeats = -1;
	
	/*Prints details of a bus line depending on the code given as input in the first booking page and indefinitely
		loops it until another function is called*/
	do
	{		
		printf("\n-----------------------------------\n");
		printf("BUS DETAILS:\n", busN.nCode);
		printf("-----------------------------------\n");
		printf("Departure Station:	%s\n", busN.cStationD);
		printf("Arrival Station:	%s\n", busN.cStationA);
		printf("ETD:			%s\n", busN.cTimeD);
		printf("ETA:			%s\n", busN.cTimeA);
		printf("Seats Left:		%d\n", busN.seats.nSpace);
		printf("Price:			%.2f\n", busN.fPrice);
		printf("-----------------------------------\n\n");

		if(busN.seats.nBooked[busN.seats.nTransactions] > 0)
		{
			printf("You have previously booked %d seats in bus line %d.\n", busN.seats.nBooked[busN.seats.nTransactions], busN.nCode);
			printf("Booking will renew the number of seats you have booked.\n\n");
		}
		printf("Number of seats: ");
		scanf("%d", &nSeats);
		fflush(stdin);
		
		/*Proceeds to ask for confirmation if the number of requested seats is not greater than the number of
			available seats*/
		if(nSeats >= 0 && nSeats <= busN.seats.nSpace)
		{
			if(nSeats == 0)
				printf("\nNo seats booked.\n\n");
			else
			{
				printf("\nYou have booked %d seats in Bus %d.\n", nSeats, nCode);
				printf("Total price is P%.2f.\n\n", nSeats * busN.fPrice);
			}
			printf("	[1] Confirm\n");
			printf("	[2] Book again\n");
			printf("	[3] Cancel book\n\n");
			printf("	[9] Go Back\n");
			printf("	[0] Exit\n\n");
			
			printf("Choice: ");
			scanf("%d", &nInput);
			fflush(stdin);
			
			switch(nInput)
			{
				case 1: {
						transferInput(bus, nSeats, busN);
						printMenuSelect(bus);
						} break;
				case 2: {
						transferInput(bus, nSeats, busN);
						printTransactBookCode(bus);
						} break;
				case 3: printTransactBookCode(bus); break;
				case 9: printMenuSelect(bus); break;
				case 0: {
						transferInput(bus, nSeats, busN);
						printTransactSummary(bus);
						} break;
				default:
				{
					printErrorMessage();
					printTransactBookCode(bus);
				};
			}
		}
		
		else
		{
			printErrorMessage();
			printTransactBookCode(bus);
		}
	}while(1);
				
}

/*	This function prints the summary of all confirmed transactions
	Pre-condition: bus[i].seats.nBooked[ITERATION] and fPrice are non-negative values
	@param bus[] is an array of structures to allow structure data to be passed when switching functions
*/	
void printTransactSummary(struct busDetails bus[])
{	
	int i, nTotalSeats = 0;
	float fTotalPrice = 0;
	
	system("cls");
	printf("----- BOOKING SUMMARY -----\n\n");
	
	/*This loop checks every element of bus[] if seats were booked during the current transaction
		(Defined at the start as ITERATION)*/
	for(i = 0; i < 12; i++)
	{
		/*If seats were booked, the details of the transaction is printed, and the total seats booked and price
			are added up*/
		if(bus[i].seats.nBooked[ITERATION] > 0)
		{
			printTransactPricing(bus[i]);
			nTotalSeats += bus[i].seats.nBooked[ITERATION];
			fTotalPrice += bus[i].seats.nBooked[ITERATION] * bus[i].fPrice;
		}
	}	
	
	/*Prints total seats booked and price if there are seats booked, otherwise prints a message stating full capacity*/
	if(nTotalSeats > 0)
	{
		printf("-----------------------------------\n\n");	
		printf("\nTotal Seats Booked:	%d\n", nTotalSeats);
		printf("Total Price:		%.2f\n\n\n", fTotalPrice);
	}
	else
		printf("No seats booked.\n\n\n");
	printf("Press any key to continue...");
	getch();
	saveBooking(bus);
	printMenuSelect(bus);
}

/*	This function prints the details of a booked bus line
	Pre-condition: bus.seats.nBooked[bus.seats.nTransactions] and fPrice are non-negative values
	@param bus is the structure requested
*/
void printTransactPricing(struct busDetails bus)
{
	printf("-----------------------------------\n");	
	printf("BUS CODE %d\n", bus.nCode);
	printf("-----------------------------------\n");
	printf("Departure Station:	%s\n", bus.cStationD);
	printf("Arrival Station:	%s\n", bus.cStationA);
	printf("ETD:			%s\n", bus.cTimeD);
	printf("ETA:			%s\n", bus.cTimeA);	
	printf("Seats Booked:		%d\n", bus.seats.nBooked[bus.seats.nTransactions]);
	printf("Total Price:		%.2f\n", bus.seats.nBooked[bus.seats.nTransactions] * bus.fPrice);

}

/*	This function prints an error message and waits for user input before clearing
	Pre-condition: Invalid input is given in a function
*/
void printErrorMessage()
{
	printf("\nInvalid input. Press any key to re-input...");
	getch();
}

/*	This function prints the termination message of the program
	Pre-condition: All values of nBooked in seats[] are 0 OR 'x' or 'X' is given as input
		in printMenuSelect
	@param bus[] is an array of structures to allow structure data to be passed when switching functions
*/
void printTermination(struct busDetails bus[])
{	
	char cInput;
	
	system("cls");
	/*Prints a message that depends if there are no more seats or the program is terminated*/
	if(checkSpaceLeft(bus) == 0)
		printf("All seats booked.\n");
	else
		printf("Program terminated.\n");
	printf("Thank you for using our booking app!\n");
	printf("----------------------------------------\n");
	printf("Press [Spacebar] to reset app or press any key to exit...\n");
	if(getch() == ' ')
		main();
	else
		exit(0);
}



/*		---Section 2 of function definitions [Process functions]---		*/
/*	This function gets the number of seats left in a bus line
	Pre-condition: nBusID is a valid element of seats[], nTranscations is equal to the number
		of elements in nBooked[]
	@param nBusID dictates which array element to use for seats[]
	@param seats[] is an array of structures that store the capacity data of a bus line
	@return returns the total amount of seats available
*/
int getSpace(int nBusID, struct seating seats[])
{
	int i, nSum = 0;
	
	/*This loop adds the number of booked seats based on the number of transactions made*/
	for(i = 0; i < seats[nBusID].nTransactions; i++)
		nSum += seats[nBusID].nBooked[i];
	
	return seats[nBusID].nCapacity - nSum;
}

/*	This function changes the number of seats left in a bus line based on the user's input
	Pre-condition: nBookedSeats is a non-negative value, nCode in busN matches a member nCode from bus[]
	@param bus[] is an array of structures to allow structure data to be passed when switching functions
	@param nBookedSeats is the number of seats the program user gave as input
	@param busN is the structure to be manipulated
*/
void transferInput(struct busDetails bus[], int nBookedSeats, struct busDetails busN)
{
	int i, nHolder;
	
	/*This loop checks the bus code given in the first booking page matches a code in bus[]
		If it does, the respective array element number is assigned to a holder variable*/
	for(i = 0; i < 12; i++)
	{
		if(busN.nCode == bus[i].nCode)
			nHolder = i;
	}
	
	/*Moves the value from the holder variable to i, which represents the array element of bus[]*/
	i = nHolder;
	
	/*Moves the value from user input to the main structure of seats
		(nBookedSeats moved to corresponding array element (Represented by ITERATION) in .nBooked),
		then reduces the number of total seats available*/
	bus[i].seats.nSpace += bus[i].seats.nBooked[ITERATION];
	bus[i].seats.nBooked[ITERATION] = nBookedSeats;
	bus[i].seats.nSpace -= nBookedSeats;	
}

/*	This function counts the iterations of booking transactions done
	Pre-condition: nBooked is a non-negative value
	@param bus[] is an array of structures to allow structure data to be passed when switching functions
*/
void saveBooking(struct busDetails bus[])
{
	int i;
	
	/*This program loops through all the elements of bus[]*/
	for(i = 0; i < 12; i++)
		/*If there are seats booked in the current transaction(ITERATION), the number of transactions done is
			increased*/
		if(bus[i].seats.nBooked[ITERATION] > 0)
			bus[i].seats.nTransactions++;
}

/*	This function gets the total seats left across all bus lines
	Pre-condition: nSpace is a non-negative value
	@param bus[] is an array of structures to allow structure data to be passed when switching functions
*/
int checkSpaceLeft(struct busDetails bus[])
{
	int i, nSum = 0;
	
	/*This loop goes through all the elements of bus[] and adds up all the available seats*/
	for(i = 0; i < 12; i++)
		nSum += bus[i].seats.nSpace;
		
	return nSum;
}
/*		-----This marks the end of function definitions-----		*/
