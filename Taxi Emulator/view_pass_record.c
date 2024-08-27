/*
	This module contains the function that is used to view a particular passenger record.
*/

#include"emulator.h"


int view_pass_record(void) {

	const char* passenger_binaryfile = "passenger_binary.bin";

	/* open the relative / binary file for reading and writing*/
	FILE* pfd = fopen(passenger_binaryfile, "r+");

	/* read the file sequentially*/
	PASSENGER passeng_rec;
	HEADER header_pass_rec;
	long rec_num;


	/* 
		- position the file pointer to the start-of-file (header) 
		- read the header record(aka zeroth record) 
		  it indicates the first available passenger id */
	fseek(pfd, 0, SEEK_SET);
	fread(&header_pass_rec, sizeof(HEADER), 1, pfd);

	/* Ask the user for Passenger ID */
	printf("\n");
	printf("Which specific passengers record would you like to view?\n");
	printf("It should be noted that passenger IDS start from (1000)\n");
	printf("Please type in ID of the passenger record you would like to view: ");
	scanf_s("%d", &rec_num);

	if (rec_num >= START) {

		/* Move through the passenger record to the position of the passenger id inputted by the user */
		// START = 1000, Because passenger id starts from 1000
		fseek(pfd, ((rec_num - START) * sizeof(PASSENGER)) + sizeof(HEADER), SEEK_SET);

		

		/* Ensuring user input is valid*/
		if ((rec_num < START) || (fread(&passeng_rec, sizeof(PASSENGER), 1, pfd) == 0)) {

			printf("\nPassenger record not found\n\n");
			return 0;
		}

		/*input must have been valid and passenger exists*/
		printf("\npassenger ID: %-6u Request time: %-8u Orig street: %-8u Orig avenue: %u\n",
			passeng_rec.pid, passeng_rec.time_req, passeng_rec.origin.street, passeng_rec.origin.avenue);
		printf("passenger ID: %-6u orig puc: %-12u dest street: %-8u dest avenue: %u\n",
			passeng_rec.pid, passeng_rec.pick_up_corner, passeng_rec.destination.street, passeng_rec.destination.avenue);
		printf("passenger ID: %-6u drop-of-corner: %-6u passanger state: %u\n\n\n",
			passeng_rec.pid, passeng_rec.drop_off_corner, passeng_rec.pass_state);

	}
	else {
		printf("\n\nInvalid entry!!!\n\n");
	}

	fclose(pfd); //close binary file
	return 0;
}

