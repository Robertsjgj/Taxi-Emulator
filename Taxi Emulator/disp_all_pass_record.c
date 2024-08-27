#include"emulator.h"

int disp_all_pass_record() {

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


	rec_num = 1;

	while (rec_num < header_pass_rec.first_id && fread(&passeng_rec, sizeof(PASSENGER), 1, pfd)) {

		printf("\npassenger ID: %-6u Request time: %-8u Orig street: %-8u Orig avenue: %u\n",
			passeng_rec.pid, passeng_rec.time_req, passeng_rec.origin.street, passeng_rec.origin.avenue);
		printf("passenger ID: %-6u orig puc: %-12u dest street: %-8u dest avenue: %u\n",
			passeng_rec.pid, passeng_rec.pick_up_corner, passeng_rec.destination.street, passeng_rec.destination.avenue);
		printf("passenger ID: %-6u drop-of-corner: %-6u passenger state: %u\n\n\n",
			passeng_rec.pid, passeng_rec.drop_off_corner, passeng_rec.pass_state);

	}

	fclose(pfd); //close binary file
	return 0;
}

