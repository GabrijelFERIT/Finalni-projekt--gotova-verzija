#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "func.h"
#include "mem.h"
#include <stdlib.h>
#include <string.h>

int result;

//Datoteka za definiranje glavnih funkcija


//Glavni terminal
void main_terminal() {

	system("cls");
	printf("\t\t\t==========================\n");
	printf("\t\t\tOdaberite jednu od opcija:\n");
	printf("\t\t\t1. Enter a new resident\n");
	printf("\t\t\t2. See the list of residents\n");
	printf("\t\t\t3. Delete file\n");
	printf("\t\t\t4. Exit program\n");
	printf("\t\t\t5. Edit/delete residents info\n");
	printf("\t\t\t6. Sorting\n");
	printf("\t\t\t==========================\n");

}


//Glavni izbornik
int selection(char* const file_name) {


	int selected;
	int rp_mn = 1;

	enum option {
		WRITE_MEM = 1,
		PRINT_OUT = 2,
		DELETE_FILE = 3,
		EXIT_PROGRAM = 4,
		EDIT_DELETE_MEM = 5,
		SORTING = 6
	};

	while (rp_mn == 1) {

		main_terminal();



		do {
			printf("\t\t\t");
			result = scanf("%d", &selected);
			while (getchar() != '\n');
			if (result == 0 || selected < 1 || selected > 6) {
				system("cls");
				printf("\t\t\tYour selection is invalid\n");
			}
		} while (result == 0 || selected < 1 || selected > 6);


		switch (selected) {
		case WRITE_MEM:
				system("cls");
				FILE* fp = fp_new();
				if (fp == NULL) {
					exit(EXIT_FAILURE);
				}
				new_resident(fp);
				fclose(fp);
			break;

		case PRINT_OUT:
			if (check_file_existence() == 0 || check_file_contet(file_name) == 0) {
				system("cls");
				printf("\nDatoteka ne psotoji ili nema sadrzaja ,molimo Vas, prvo kreirajte datoteku ili upisite sadrzaj da bi ste nastavili sa upisivanjem\n\n");
				break;
			}
			else {

				print_members_select();

			}


		break;

		case DELETE_FILE:
			delete_file(file_name);
			break;

		case EXIT_PROGRAM:
			terminate_program();
			break;
			
		case EDIT_DELETE_MEM:
			editing_del_info();
			break;

		case SORTING:

			sorting_func(file_name);

			break;

		default:
			return selected;
			break;
		}
	}
}

//Funkcija za izlaženje iz programa
void terminate_program() {
	exit(EXIT_SUCCESS);
}


//Baza programa za ispisivanje odakle se pozivaju funkcije koje isto i odrade
void print_members_select(void){

	short result;
	short selection;

	printf("\nEnter 1 for all members or 2 for a specific member\n");
	do {
		result = scanf("%hd", &selection);
		while (getchar() != '\n');
		if (selection < 1 || selection > 2 || result == 0) {
			system("cls");
			printf("\nValue isn' t valida, please try again\n");
		}
	} while (selection < 1 || selection > 2 || result == 0);

	enum option {
		ALL_MEM = 1,
		ONE_MEM = 2
	 };

	switch(selection) {
	case ALL_MEM:
		print_all();
		break;

	case ONE_MEM:
		print_one();
		break;
	default:
		break;

	}

}


//Funkcija za brisanje datoteke
void delete_file(char* file_name) {

	char select;
	int f = 0;
	while (f == 0) {

		printf("\nAre you sure you want to delete the file?\n press 1 for yes and 2 for no ");

		short option;
		short result;
		do {
			result = scanf("%hd", &option);
			while (getchar() != '\n');
			if (result == 0 || option < 1 || option > 2) {
				system("cls");
				printf("\nInvalid value");
			}
		} while (result == 0 || option < 1 || option > 2);

		if (option == 1) {
			remove(file_name);
			printf("\nFile has been deleted");
			f = 1;
		}
		else {
			printf("\nPress y to return\n");
		
			do {
				scanf(" %c", &select);

				if (select != 'y' || select != 'Y') {
					printf("\nAction unavalibale try again\n");
				}
			} while (select != 'y' && select != 'Y');
			if (select == 'y' || 'Y') {
				system("cls");
				return;
			}
		}
	}
	
}

//Funkcije koje zajedno tvore širi blok algoritma za sortiranje
int compareByName(const void* a, const void* b) {
	RESIDENT* resA = *(RESIDENT**)a;
	RESIDENT* resB = *(RESIDENT**)b;
	return strcmp(resA->name, resB->name);
}

int compareByLastName(const void* a, const void* b) {
	RESIDENT* resA = *(RESIDENT**)a;
	RESIDENT* resB = *(RESIDENT**)b;
	return strcmp(resA->last_name, resB->last_name);
}

int compareByID(const void* a, const void* b) {
	RESIDENT* resA = *(RESIDENT**)a;
	RESIDENT* resB = *(RESIDENT**)b;

	// Usporedbda ID-ova
	if (resA->ID < resB->ID) return -1;
	if (resA->ID > resB->ID) return 1;
	return 0; 
}

void sorting_func(char* file_name) {

	int f = 0;

	while (f == 0) {
		FILE* fp = fopen(file_name, "r");
		if (fp == NULL) {
			perror("Failed to open file");
			exit(EXIT_FAILURE);
		}

		int num_res;
		fscanf(fp, "%d", &num_res);
		//Dinamièko zauzimanje
		RESIDENT** arr_of_res = (RESIDENT**)calloc(num_res, sizeof(RESIDENT*));
		if (arr_of_res == NULL) {
			perror("Failed to allocate memory");
			exit(EXIT_FAILURE);
		}

		// Èitanje podataka
		for (int i = 0; i < num_res; i++) {
			arr_of_res[i] = temp(); 
			fseek(fp, sizeof(short) + i * sizeof(RESIDENT), SEEK_SET); 
			fscanf(fp, "%19s %19s %lld %c %hd %d %hd %hd %hd",
				arr_of_res[i]->name,
				arr_of_res[i]->last_name,
				&arr_of_res[i]->ID,
				&arr_of_res[i]->geneder,
				&arr_of_res[i]->age,
				&arr_of_res[i]->income,
				&arr_of_res[i]->date_of_birth->day,
				&arr_of_res[i]->date_of_birth->month,
				&arr_of_res[i]->date_of_birth->year);
		}

		fclose(fp); // Zatvranje filea

		enum sorting_option {
			NAME = 1,
			LAST_NAME = 2,
			ID = 3
		};

		int sorting_option;

		system("cls");

		printf("\nEnter how you would like to sort the residents info:\n1. By name\n2. By last name\n3. By ID\n");

		int result;
		do {
			result = scanf("%d", &sorting_option);
			while (getchar() != '\n'); // Clear input buffer
			if (result == 0 || sorting_option < 1 || sorting_option > 3) {
				printf("\nInvalid value. Please enter 1, 2, or 3: ");
			}
		} while (result == 0 || sorting_option < 1 || sorting_option > 3);

		switch (sorting_option) {
		case NAME:
			qsort(arr_of_res, num_res, sizeof(RESIDENT*), compareByName);
			break;
		case LAST_NAME:
			qsort(arr_of_res, num_res, sizeof(RESIDENT*), compareByLastName);
			break;
		case ID:
			qsort(arr_of_res, num_res, sizeof(RESIDENT*), compareByID);
			break;
		default:
			f = 1; // Napusti petlju
			break;
		}

		// De-facto brisanje staron ne sortiranog filea
		fp = fopen(file_name, "w");
		if (fp == NULL) {
			perror("Failed to open file for writing");
			exit(EXIT_FAILURE);
		}

		// Ponovno zapisivanje svih sortiranih podataka
		fprintf(fp, "%d\n", num_res); 
		for (int i = 0; i < num_res; i++) {
			fseek(fp, sizeof(short) + i * sizeof(RESIDENT), SEEK_SET);
			fprintf(fp, "%s %s %lld %c %hd %d %hd %hd %hd\n",
				arr_of_res[i]->name,
				arr_of_res[i]->last_name,
				arr_of_res[i]->ID,
				arr_of_res[i]->geneder,
				arr_of_res[i]->age,
				arr_of_res[i]->income,
				arr_of_res[i]->date_of_birth->day,
				arr_of_res[i]->date_of_birth->month,
				arr_of_res[i]->date_of_birth->year);
		}
		// Oslobaðanje memorije i zatvarnje datoteke
		fclose(fp); 

		
		for (int i = 0; i < num_res; i++) {
			free(arr_of_res[i]);
		}
		free(arr_of_res);


		printf("\nDo you want to finish sorting? Type 'Y' for yes and 'N' for no: ");
		char choice;
		scanf(" %c", &choice);

		if (choice == 'Y' || choice == 'y') {
			f = 1; // Izaði iz petlje
		}
		else {
			f = 0; // Nastavi sortiranje
		}
	}
}