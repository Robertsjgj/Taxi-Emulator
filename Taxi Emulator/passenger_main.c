#include"emulator.h"

int passenger_control() {

	int choice;


	printf("To make use of this software do either of the following\n");

	while(1)
	{
		/*
			when you chose the option to initialize record
			- you're creating a new binary file if it does not already exist
			- if file already exist, then you're just deleting it's content and overwriting it with
			  a new entry
		*/
		printf("\n1: Initialize record\n");
		printf("2: view a particular passenger record\n");
		printf("3: display all passenger record\n");
		printf("4: add new passenger\n");
		printf("5: update a particular passenger record\n");
		printf("6: To quit\n");
		printf("choice -> ");
		scanf_s("%d", &choice);

		switch (choice) 
		{
		case 1:
			system("cls");
			init_passenger();
			printf("\n Initializing successful!!!\n\n");
			break;

		case 2:
			system("cls");
			view_pass_record();
			break;

		case 3:
			system("cls");
			disp_all_pass_record();
			break;

		case 4:
			system("cls");
			add_new_passenger();
			break;

		case 5:
			system("cls");
			update_pass_record();

		case 6:
			break;

		default:
			printf("Entry is Invalid: Please TRY AGAIN! \n\n");
		}
		
		if (choice == 6) {
			break;
		}
	}

	return;
}