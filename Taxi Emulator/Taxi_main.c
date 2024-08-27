#include"emulator.h"

int taxi_control() {

	int choice;


	printf("To make use of this software do either of the following\n");

	while (1)
	{
		/*
			when you chose the option to initialize record
			- you're creating a new binary file if it does not already exist
			- if file already exist, then you're just deleting it's content and overwriting it with
			  a new entry
		*/
		printf("0: To quit");
		printf("\n1: Initialize record\n");
		printf("2: view a particular taxi record\n");
		printf("3: To deleted a taxi record\n");
		printf("4: add new taxi to the record\n");;
		printf("5: view all taxis at end of simulation\n");
		printf("choice -> ");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 0:
			break;

		case 1:
			system("cls");
			init_taxi();
			printf("\n Initializing successful!!!\n\n");
			break;

		case 2:
			system("cls");
			view_taxi_record();
			break;

		case 3:
			system("cls");
			delete_taxi();
			break;

		case 4:
			system("cls");
			add_new_taxi();
			break;

		case 5:
			system("cls");
			display_taxis();
			break;

		default:
			printf("Entry is Invalid: Please TRY AGAIN! \n\n");

		}

		if (choice == 0) {
			break;
		}
	}
}