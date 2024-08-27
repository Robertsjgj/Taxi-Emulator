#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "emulator.h"

extern void display_taxis();

int choice1 = 0;

void taxi_menu() {
	do {
		printf("\nTaxi Menu\n\n");
		printf("1: Add Taxi\n");
		printf("2: Edit Taxi\n");
		printf("3: Delete Taxi\n");
		printf("4: Display Taxis\n");
		printf("5: Go Back\n");
		scanf_s("%d", &choice1);

		switch (choice1)
		{
		case 1:
			system("cls");
			//ADD TAXI
			break;
		case 2:
			system("cls");
			//UPDATE TAXI
			break;
		case 3:
			system("cls");
			//DELETE TAXI
			break;
		case 4:
			system("cls");
			display_taxis(); //DISPLAY TAXIS
			break;
		case 5:
			system("cls");
			break;
		default:
			system("cls");
			printf("\nwrong choice.Enter Again");
			break;
		}


	} while (choice1 != 5);
}