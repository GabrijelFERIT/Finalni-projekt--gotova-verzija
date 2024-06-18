#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "func.h"
#include <ctype.h>

extern result;
////////////////primarno datoteka za funkcije koje imaju za cilj generiranje nasumiènih brojeva, kao i bartanje sa upisom i ispisom podataka\\\\\\\\\\\\\\\\\\\\//



//////////////////////////////Funkcija namjenjena za provjeru postojanja datoeke\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
int check_file_existence() {

	FILE* fp = NULL;
	fp = fopen("List_of_residents.txt", "r");
	if (fp == NULL) {
		return 0;
	}
	else
		fclose(fp);
		return 1;

}


                      //////////////////////////////Manja funkcija namjenjena stvaranju pokazivaèa na datoteku\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///
FILE* fp_new() {
	FILE* fp_new = NULL;
	if (check_file_existence() == 0) {
		fp_new = fopen("List_of_residents.txt", "w+");
	}
	else {
		fp_new = fopen("List_of_residents.txt", "r+");
	}
	if (fp_new == NULL) {
		exit(EXIT_FAILURE);
		printf("\nCouldn' t create a new file: %d", errno);
	}

	return fp_new;
}



////////////////////////////////////////////////////Funkcija za provjeru postoji li sadržaj u veæ kreiranoj datoteci\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
int check_file_contet(const char* file_name) {
	int file_exists = check_file_existence(file_name);

	if (file_exists == 0) {
		return 0; 
	}
	else if (file_exists == 1) {
		FILE* fp = fopen(file_name, "r");

		if (fp == NULL) {
			return 0; 
		}

		int temp_var;
		int fscan_result = fscanf(fp, "%d", &temp_var);
		fclose(fp);

		if (fscan_result == EOF) {
			return 0; 
		}
		else {
			return 1; 
		}
	}
	return 0; 
}



///////////////////////////////////////////////////////////Funkcija za dinamèko zauzimanje memorije strukture\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

RESIDENT* temp(void) {

	RESIDENT* temp_res = NULL;
	temp_res = (RESIDENT*)calloc(1, sizeof(RESIDENT));
	(temp_res)->date_of_birth = (DOB*)calloc(1, sizeof(DOB));
	if (temp_res == NULL || (temp_res)->date_of_birth == NULL) {
		exit(EXIT_FAILURE);
		printf("\nProblem while taking up dynamic array, for residents: %d", errno);
	}
	temp_res->name = (char*)calloc(20, sizeof(char));
	if (temp_res->name == NULL) {
		exit(EXIT_FAILURE);
		printf("\nError while allocating dyn mem for name: %d", errno);
	}
	temp_res->last_name = (char*)calloc(20, sizeof(char));
	if (temp_res->last_name == NULL) {
		exit(EXIT_FAILURE);
		printf("\nError while allocating dyn mem for last name: %d", errno);
	}

	

	return temp_res;
}

///////////////////////////////////////////////////Generator nasumiènih brojeva\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

long long int rand_num_gen() {

	long long int ll = 110000000000; 
	long long int ul = 900000000000; 

	
	long long int number = ll + rand() % (ul - ll + 1);

	return number;
}


//******************************************************//DODAVANJE STANOVNIKA\\******************************************************\\//
void new_resident(FILE* fp) {

	static int cuurent_population = 0;
	int status = 0;


	
	fseek(fp, 0, SEEK_SET);
	if (fscanf(fp, "%d", &cuurent_population) != 1) {
		cuurent_population = 0;
	}

	
	short flag = 0;

	while (flag == 0) {

		RESIDENT* temp_res = temp();
		
	
		

		printf("\t\t\tEnter %d. member of the town, ID will be assigned automatically:\nName: ", cuurent_population + 1);

		fseek(fp, cuurent_population * sizeof(RESIDENT), SEEK_SET);


		scanf("%19s", (temp_res)->name);
		(temp_res)->name[0] = toupper((temp_res)->name[0]);
		for (int i = 1; i != '\n'; i++) {
			temp_res->name[i] = tolower(temp_res->name[i]);
		}

		
		printf("\nEnter last name: ");
		scanf("%19s", (temp_res)->last_name);
		(temp_res)->last_name[0] = toupper((temp_res)->last_name[0]);
		for (int i = 1; i != '\n'; i++) {
			temp_res->last_name[i] = tolower(temp_res->last_name[i]);
		}
		
		printf("\nEnter age: ");
		do{
			
			result = scanf("%hd", &(temp_res)->age);
			while (getchar() != '\n');

			if (result == 0 || (temp_res)->age < 0 || (temp_res)->age > 130) {
				system("cls");
				printf("\nAge isn' t possible, please enter your age again: ");
			}
		} while (result == 0 || (temp_res)->age < 0 || (temp_res)->age > 130);
		
		(temp_res)->ID = rand_num_gen();


		printf("\nEnter gender (m for male or f for female)\n");
		do {
			scanf(" %c", &(temp_res)->geneder);

			if ((temp_res->geneder != 'M' && temp_res->geneder != 'm') && (temp_res->geneder != 'F' && temp_res->geneder != 'f')) {
				system("cls");
				printf("\nGnder undefined\n");
			}
		
		} while ((temp_res->geneder != 'M' && temp_res->geneder != 'm') && (temp_res->geneder != 'F' && temp_res->geneder != 'f'));
		


		printf("\nEnter income: ");
		do {
			result = scanf("%d", &(temp_res)->income);
			while (getchar() != '\n');
			if (result == 0 || (temp_res)->income < 0 || (temp_res)->income > 1000000000) {
				system("cls");
				printf("\nIncome isn' t possoble please try entering gain\n");
			}
		} while (result == 0 ||(temp_res)->income < 0 || (temp_res)->income > 1000000000);
		
		printf("\nEnter birth month: ");
		do {
			result = scanf("%hd", &(temp_res)->date_of_birth->month);
			while (getchar() != '\n');
			if (result == 0 || (temp_res)->date_of_birth->month < 1 || (temp_res)->date_of_birth->month > 12) {
				system("cls");
				printf("Such month doesn' t exist, please try again: ");
			}
		} while (result == 0 ||(temp_res)->date_of_birth->month < 1 || (temp_res)->date_of_birth->month > 12);
		
		printf("\nEnter birth year: ");
		do {
			result = scanf("%hd", &(temp_res)->date_of_birth->year);
			while (getchar() != '\n');
			if (result == 0 || (temp_res)->date_of_birth->year < 1910 || (temp_res)->date_of_birth->year > 2024) {
				system("cls");
				printf("\nBirth year isn' t possible, please choose a number bewteen 1910 & 2024: ");
			}
		} while (result == 0 || (temp_res)->date_of_birth->year < 1910 || (temp_res)->date_of_birth->year > 2024);
		



		int max_days;
		switch ((temp_res)->date_of_birth->month) {
		case 2:
			if ((temp_res)->date_of_birth->year % 4 == 0 && ((temp_res)->date_of_birth->year % 100 != 0 || (temp_res)->date_of_birth->year % 400 == 0)) {
				max_days = 29; // Prestupna godina
			}
			else {
				max_days = 28; // Nije prestupna godina
			}
			break;
		case 4: case 6: case 9: case 11:
			max_days = 30;
			break;
		default:
			max_days = 31;
		}

		printf("\nEnter day of birth: ");
		do {
			result = scanf("%hd", &(temp_res)->date_of_birth->day);
			while (getchar() != '\n');
			if (result == 0 || (temp_res)->date_of_birth->day < 1 || (temp_res)->date_of_birth->day > max_days) {
				printf("\nInvalid day. Please enter a day between 1 and %d: ", max_days);
			}
		} while (result == 0 || (temp_res)->date_of_birth->day < 1 || (temp_res)->date_of_birth->day > max_days);
		
			
		//Zapisivanje svih korisnièkih podytaka\\//
         fprintf(fp, "\n%s %s %lld %c %hd %d %hd %hd %hd",
			 temp_res->name,
			 temp_res->last_name,
			 temp_res->ID,
			 temp_res->geneder,
			 temp_res->age,
			 temp_res->income,
			 temp_res->date_of_birth->day,
			 temp_res->date_of_birth->month,
			 temp_res->date_of_birth->year);
		////////////////////////////////////////

		cuurent_population++;
		rewind(fp);
		fprintf(fp, "%d", cuurent_population);
		

		printf("\t\t\tDo you want to finish entry of residents, type Y for yes and N for no\n\t\t\t");
		char choice;
		
		

		do {
			
			scanf("%c", &choice);
			if (choice == 'Y' || choice == 'y') {
				flag = 1;
				system("cls");
				
			}
			else if(choice == 'N' || choice == 'n') {
				flag = 0;
				system("cls");
			}
			else {
				system("cls");
				printf("\nThat isn' t an option please try again\n");
			}
		} while ((choice != 'Y' && choice != 'y') && (choice != 'N' && choice != 'n'));
		//Oslobaðanje i zatvarnje filea
		free(temp_res->name);
		free(temp_res->last_name);
		free(temp_res->date_of_birth);
		free(temp_res);
		

	}

	
	fclose(fp);
}


                         //******************************************************//ISPIS STANOVNIKA\\******************************************************\\//



void print_all() {

	int num_res;

	FILE* fp = NULL;
	fp = fp_new();
	if (fp == NULL) {
		printf("\nERROR while opening file: %d", errno);
	}

	int f = 0;
	char select;

	RESIDENT* temp_res = temp();

	while (f == 0) {
		fscanf(fp, "%d", &num_res);
		printf("\n\n%d", num_res);
		system("cls");
		for (int i = 0; i < num_res; i++) {
			
			fseek(fp, sizeof(short) + i * sizeof(RESIDENT), SEEK_SET);
			
			fscanf(fp, "%19s %19s %lld %c %hd %d %hd %hd %hd",
				temp_res->name,
				temp_res->last_name,
				&temp_res->ID,
				&temp_res->geneder,
				&temp_res->age,
				&temp_res->income,
				&temp_res->date_of_birth->day,
				&temp_res->date_of_birth->month,
				&temp_res->date_of_birth->year);
			
			
			printf("\n\n%d. Name : %s,Last_name : %s, ID : %lld, Income: %d ",i + 1 , (temp_res)->name, (temp_res)->last_name, (temp_res)->ID, (temp_res)->income);

			
		}

		printf("\nDo you want to return?\nEnter y for yes\n");
		do {
			scanf("%c", &select);
			if ((select != 'y' && select != 'Y')) {
				printf("\nSelection is invalid plese try agin\n");
			}
			else if (select == 'y' || 'Y') {
				f = 1;
				system("cls");
			}
		} while ((select != 'y' && select != 'Y'));
	}
	//Zatvaranje datoteke i brisanje podataka
	free(temp_res->name);
	free(temp_res->last_name);
	free(temp_res->date_of_birth);
	free(temp_res);
	fclose(fp);
}

                    ///////////////////////////////////////////////////******ISPIS ODREÐNOG ÈLANA******\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

void print_one(void) {

	system("cls");

	int f = 0;

	while (f == 0) {

		system("cls");

		printf("\nPlease choose the parameter by which you want to search and see information on a resident");
		printf("\nType 1. To search by position, 2. by ID, or 3. by Name/Last name\n");

		int selction;
		int result;

		do {
			result = scanf("%d", &selction);
			while (getchar() != '\n');
			if (result == 0 || (selction < 1 || selction > 3)) {
				system("cls");
				printf("Number you have entered isnt an option please try again\n");
			}
		} while (result == 0 || (selction < 1 || selction > 3));

		int num_res;

		enum selct {
			SEARCH_POS_BY_NUM = 1,
			SEARCH_BY_ID = 2,
			SEARCH_BY_NAME = 3
		};
		/////////////Algoritam pretrage putem pozicije u datoteci odnosno redoslijeda unosa\\\\\\\\\\\\\\\\\\\//
		if (selction == SEARCH_POS_BY_NUM) {
			system("cls");
			printf("Enter the position of the member you want to see\n");
			FILE* fp = fp_new();
			fscanf(fp, "%d", &num_res);
			short select_res;

			RESIDENT* temp_res = temp();

			do {

				result = scanf("%hd", &select_res);
				while (getchar() != '\n')
					if (result == 0 || select_res < 1 || select_res > num_res) {
						system("cls");
						printf("Invalid number, try again\n");
					}

			} while (result == 0 || select_res < 1 || select_res > num_res);

			fseek(fp, sizeof(short) + (select_res - 1)*sizeof(RESIDENT), SEEK_SET);

			fscanf(fp, "%19s %19s %lld %c %hd %d %hd %hd %hd",
				temp_res->name,
				temp_res->last_name,
				&temp_res->ID,
				&temp_res->geneder,
				&temp_res->age,
				&temp_res->income,
				&temp_res->date_of_birth->day,
				&temp_res->date_of_birth->month,
				&temp_res->date_of_birth->year);



			printf("\n\n%d. Name : %s,Last_name : %s, ID : %lld, Income: %d, \nBorn on : %hd/%hd/%hd ",
				select_res,
				(temp_res)->name,
				(temp_res)->last_name,
				(temp_res)->ID, 
				(temp_res)->income,
				temp_res->date_of_birth->day,
				temp_res->date_of_birth->month,
				temp_res->date_of_birth->year);

			free(temp_res); //Oslobaðanje i zatvarnje filea
			fclose(fp);
		}

		/////////////////////////////////////////Pretraga po osbnom identifakatorskom broju radi baratnja podatcima u sklopu programa\\\\\\\\\\\\\\\\\\\\\\\//
		else if (selction == SEARCH_BY_ID) {

			system("cls");
			printf("Enter the ID of the member you want to see\n");
			FILE* fp = fp_new();
			fscanf(fp, "%d", &num_res);
			long long select_res;

			RESIDENT* temp_res = temp();

			do {

				result = scanf("%lld", &select_res);
				while (getchar() != '\n')
					if (result == 0 || select_res < 100000000000 || select_res > 999999999999) {
						system("cls");
						printf("Invalid number, try again\n");
					}

			} while (result == 0 || select_res < 100000000000 || select_res > 999999999999);


			short found = 0;

			for (int i = 0; i < num_res; i++) {
				fseek(fp, sizeof(short) + i * sizeof(RESIDENT), SEEK_SET);
				fscanf(fp, "%19s %19s %lld %c %hd %d %hd %hd %hd",
					temp_res->name,
					temp_res->last_name,
					&temp_res->ID,
					&temp_res->geneder,
					&temp_res->age,
					&temp_res->income,
					&temp_res->date_of_birth->day,
					&temp_res->date_of_birth->month,
					&temp_res->date_of_birth->year);

				if (temp_res->ID == select_res) {
					found = 1;

					printf("Ime: %s Prezime: %s ID: %lld Spol: %c Dob: %hd Prihodi: %d\nDatum rodjenja: %hd/%hd/%hd",
						temp_res->name,
						temp_res->last_name,
						temp_res->ID,
						temp_res->geneder,
						temp_res->age, 
						temp_res->income,
						temp_res->date_of_birth->day,
						temp_res->date_of_birth->month,
						temp_res->date_of_birth->year);

				}
			}

			if (found == 0) {
				printf("\nMember does not exist");
			}
			//Zatvaranje datoteke i brisanje podataka

			free(temp_res);
			fclose(fp);



		}///////////////////////////////////////////////////Zajednièko tijelo pretrage po imenu ili prezimenu\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
		else if (selction == SEARCH_BY_NAME) {

			enum selcted {
				NAME = 1,
				LAST_NAME = 2
			};

			short name_or_last;

			printf("\nEnter weather you want to search by name (1) or last name (2)\n");


			do {

				result = scanf("%hd", &name_or_last);
				while (getchar() != '\n')
					if (result == 0 || (name_or_last < 1 || name_or_last > 2)) {
						system("cls");
						printf("Invalid number, try again\n");
					}

			} while (result == 0 || name_or_last < 1 || name_or_last > 2);


			/////////////////////////////////////////Pretraga po imenu\\\\\\\\\\\\\\\\\\\\\\\\\//
			if (name_or_last == NAME) {
				system("cls");

				char name[20];
				printf("\nEnter the name of the desired member: ");
				scanf("%19s", name);

				FILE* fp = fp_new();
				if (fp == NULL) {
					printf("Error opening file.");
					return;
				}

				fscanf(fp, "%d", &num_res);

				RESIDENT* temp_res = temp();
				if (temp_res == NULL) {
					printf("Error allocating memory.");
					fclose(fp);
					return;
				}

				char temp_name[20];
				char temp_last_name[20];
				DOB temp_dob;

				int found_count = 0;
				RESIDENT** found_residents = NULL;

				for (int i = 0; i < num_res; i++) {
					fseek(fp, sizeof(short) + i * sizeof(RESIDENT), SEEK_SET);
					fscanf(fp, "%19s %19s %lld %c %hd %d %hd %hd %hd", temp_name, temp_last_name, &temp_res->ID, &temp_res->geneder, &temp_res->age, &temp_res->income, &temp_dob.day, &temp_dob.month, &temp_dob.year);

					if (strcmp(temp_name, name) == 0) {
						found_count++;
						found_residents = realloc(found_residents, found_count * sizeof(RESIDENT*));
						if (found_residents == NULL) {
							printf("Error reallocating memory.");
							fclose(fp);
							free(temp_res);
							return;
						}
						found_residents[found_count - 1] = malloc(sizeof(RESIDENT));
						if (found_residents[found_count - 1] == NULL) {
							printf("Error allocating memory.");
							fclose(fp);
							for (int j = 0; j < found_count - 1; j++) {
								free(found_residents[j]->name);
								free(found_residents[j]->last_name);
								free(found_residents[j]->date_of_birth);
								free(found_residents[j]);
							}
							free(found_residents);
							free(temp_res);
							return;
						}

						found_residents[found_count - 1]->name = malloc(strlen(temp_name) + 1);
						found_residents[found_count - 1]->last_name = malloc(strlen(temp_last_name) + 1);
						found_residents[found_count - 1]->date_of_birth = malloc(sizeof(DOB));
						if (found_residents[found_count - 1]->name == NULL || found_residents[found_count - 1]->last_name == NULL || found_residents[found_count - 1]->date_of_birth == NULL) {
							printf("Error allocating memory.");
							fclose(fp);
							for (int j = 0; j < found_count; j++) {
								free(found_residents[j]->name);
								free(found_residents[j]->last_name);
								free(found_residents[j]->date_of_birth);
								free(found_residents[j]);
							}
							free(found_residents);
							free(temp_res);
							return;
						}
						strcpy(found_residents[found_count - 1]->name, temp_name);
						strcpy(found_residents[found_count - 1]->last_name, temp_last_name);
						memcpy(found_residents[found_count - 1]->date_of_birth, &temp_dob, sizeof(DOB));
						found_residents[found_count - 1]->ID = temp_res->ID;
						found_residents[found_count - 1]->geneder = temp_res->geneder;
						found_residents[found_count - 1]->age = temp_res->age;
						found_residents[found_count - 1]->income = temp_res->income;
					}
				}

				if (found_count == 0) {
					printf("\nSearched member doesn't exist");
				}
				else {//Zatvaranje datoteke i brisanje podataka
					for (int i = 0; i < found_count; i++) {
						printf("\n\nSelected resident by:\nName : %s, Last_name : %s, ID : %lld, Gender: %c, Age: %hd, Income: %d, \nBorn on : %hd/%hd/%hd ", found_residents[i]->name, found_residents[i]->last_name, found_residents[i]->ID, found_residents[i]->geneder, found_residents[i]->age, found_residents[i]->income, found_residents[i]->date_of_birth->day, found_residents[i]->date_of_birth->month, found_residents[i]->date_of_birth->year);

						free(found_residents[i]->name);
						free(found_residents[i]->last_name);
						free(found_residents[i]->date_of_birth);
						free(found_residents[i]);
					}
					free(found_residents);
				}

				fclose(fp);
				free(temp_res);
			}


			///////////////////////////////////////////////////Pretraga po prezimenu\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

			else if (name_or_last == LAST_NAME) {

				system("cls");

				char last_name[20];
				printf("\nEnter the last name of the desired member: ");
				scanf("%19s", last_name);
				//Stvaranje pokazivaèa
				FILE* fp = fp_new();
				if (fp == NULL) {
					printf("Error opening file.");
					return;
				}

				fscanf(fp, "%d", &num_res);
				//Dinamièko zauzimanje
				RESIDENT* temp_res = temp();
				if (temp_res == NULL) {
					printf("Error allocating memory.");
					fclose(fp);
					return;
				}

				int found_count = 0;
				int found_pos[100];  
				RESIDENT** found_residents = NULL;

				char temp_name[20];
				char temp_last_name[20];
				DOB temp_dob;

				for (int i = 0; i < num_res; i++) {
					fseek(fp, sizeof(short) + i * sizeof(RESIDENT), SEEK_SET);
					fscanf(fp, "%19s %19s %lld %c %hd %d %hd %hd %hd", temp_name,
						temp_last_name, &temp_res->ID,
						&temp_res->geneder,
						&temp_res->age,
						&temp_res->income,
						&temp_dob.day,
						&temp_dob.month,
						&temp_dob.year);

					if (strcmp(temp_last_name, last_name) == 0) {
						found_pos[found_count] = i;
						found_count++;

						found_residents = realloc(found_residents, found_count * sizeof(RESIDENT*));
						if (found_residents == NULL) {
							printf("Error reallocating memory.");
							fclose(fp);
							free(temp_res);
							return;
						}

						found_residents[found_count - 1] = malloc(sizeof(RESIDENT));
						if (found_residents[found_count - 1] == NULL) {
							printf("Error allocating memory.");
							fclose(fp);
							for (int j = 0; j < found_count - 1; j++) {
								free(found_residents[j]->name);
								free(found_residents[j]->last_name);
								free(found_residents[j]->date_of_birth);
								free(found_residents[j]);
							}
							free(found_residents);
							free(temp_res);
							return;
						}

						found_residents[found_count - 1]->name = malloc(strlen(temp_name) + 1);
						found_residents[found_count - 1]->last_name = malloc(strlen(temp_last_name) + 1);
						found_residents[found_count - 1]->date_of_birth = malloc(sizeof(DOB));
						if (found_residents[found_count - 1]->name == NULL || found_residents[found_count - 1]->last_name == NULL || found_residents[found_count - 1]->date_of_birth == NULL) {
							printf("Error allocating memory.");
							fclose(fp);
							for (int j = 0; j < found_count; j++) {
								free(found_residents[j]->name);
								free(found_residents[j]->last_name);
								free(found_residents[j]->date_of_birth);
								free(found_residents[j]);
							}
							free(found_residents);
							free(temp_res);
							return;
						}

						strcpy(found_residents[found_count - 1]->name, temp_name);
						strcpy(found_residents[found_count - 1]->last_name, temp_last_name);
						memcpy(found_residents[found_count - 1]->date_of_birth, &temp_dob, sizeof(DOB));
						found_residents[found_count - 1]->ID = temp_res->ID;
						found_residents[found_count - 1]->geneder = temp_res->geneder;
						found_residents[found_count - 1]->age = temp_res->age;
						found_residents[found_count - 1]->income = temp_res->income;
					}
				}

				if (found_count == 0) {
					printf("\nSearched member doesn't exist");
				}
				else {
					for (int i = 0; i < found_count; i++) {
						printf("\n\nSelected resident by:\nName : %s, Last_name : %s, ID : %lld, Gender: %c, Age: %hd, Income: %d, \nBorn on : %hd/%hd/%hd ", found_residents[i]->name, found_residents[i]->last_name, found_residents[i]->ID, found_residents[i]->geneder, found_residents[i]->age, found_residents[i]->income, found_residents[i]->date_of_birth->day, found_residents[i]->date_of_birth->month, found_residents[i]->date_of_birth->year);
					}
				}
				//Zatvaranje datoteke i brisanje podataka
				for (int i = 0; i < found_count; i++) {
					free(found_residents[i]->name);
					free(found_residents[i]->last_name);
					free(found_residents[i]->date_of_birth);
					free(found_residents[i]);
				}
				free(found_residents);

				fclose(fp);
				free(temp_res);
				}

		}




		//Izlazak iz petlje, vraæanje u glavni izbornik


		printf("\n\nDo you want to continue looking up information of citezens\n");

		printf("\nType y for yes and n for no\n");

		char stay_in_loop;



		do {
			scanf(" %c", &stay_in_loop);
			if ((stay_in_loop != 'y' && stay_in_loop != 'Y') && (stay_in_loop != 'n' && stay_in_loop != 'N')) {
				system("cls");
				printf("Invalid input please try again\n");
			}
		} while ((stay_in_loop != 'y' && stay_in_loop != 'Y') && (stay_in_loop != 'n' && stay_in_loop != 'N'));


		if (stay_in_loop == 'y' || stay_in_loop == 'Y') {
			f = 0;
		}
		else if (stay_in_loop == 'n' || stay_in_loop == 'N') {
			f = 1;
		}
		else {
			f = 0;
		}




	}



}

//**********************Zajednièko tijelo obje "funkcije"**************************++\\//


void editing_del_info(void) {

	int f = 0;

	while (f == 0) {
		FILE* fp = fp_new();

		system("cls");
		printf("\nDo you wish to change information or delete a resident?\nEnter 1 for deletion and 2 for editing\n");

		int choice;
		int result;
		int num_res;

		fscanf(fp, "%d", &num_res);

		do {
			result = scanf("%d", &choice);
			while (getchar() != '\n');
			if (result == 0 || (choice < 1 || choice > 2)) {
				system("cls");
				printf("Number you have entered isn't an option, please try again\n");
			}
		} while (result == 0 || (choice < 1 || choice > 2));



		//**********************Funkcija za brisanje**************************++\\//


		fscanf(fp, "%d", &num_res);

		if (choice == 1) {
			system("cls");
			printf("Enter the ID of the member you want to delete\n");

			long long select_res;


			do {
				result = scanf("%lld", &select_res);
				while (getchar() != '\n')
					if (result == 0 || select_res < 100000000000 || select_res > 999999999999) {
						system("cls");
						printf("Invalid number, try again\n");
					}
			} while (result == 0 || select_res < 100000000000 || select_res > 999999999999);

			//Dinamièko zauzimanje
			RESIDENT* temp_res = temp();

			RESIDENT** arr_of_res = (RESIDENT**)calloc(num_res, sizeof(RESIDENT*));
			if (arr_of_res == NULL) {
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}

			for (int i = 0; i < num_res; i++) {

				arr_of_res[i] = temp();
				fseek(fp, sizeof(short) + i * sizeof(RESIDENT), SEEK_SET);
				fscanf(fp, "%s %s %lld %c %hd %d %hd %hd %hd",
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
			fclose(fp);

			int searched_mem = 0;

			for (int i = 0; i < num_res; i++) {
				if (arr_of_res[i]->ID == select_res) {
					searched_mem = i + 1;
					break;
				}
			}

			if (searched_mem == 0) {
				printf("\nMember does not exist\n");
			}
			else {
				fseek(fp, 0, SEEK_SET);


				int j = 0;

				FILE* fp = fopen("List_of_residents.txt", "w");


				fprintf(fp, "%d\n", num_res - 1);

				for (int i = 0; i < searched_mem; i++) {
					if (i != searched_mem) {
						fseek(fp, sizeof(short) + j * sizeof(RESIDENT), SEEK_SET);
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
						j++;
					}
				}



				printf("\nMember deleted successfully\nType anything to rerutn\n");

				char main_menu;

				if (scanf("%c", &main_menu) >= 1) {
					f = 1;
				}
			}
			//Zatvaranje datoteke i brisanje podataka
			fclose(fp);
			for (int i = 0; i < num_res; i++) {
				free(arr_of_res[i]->name);
				free(arr_of_res[i]->last_name);
				free(arr_of_res[i]);
			}
			free(arr_of_res);
		}

		//**********************Funkcija za ureðivanje**************************++\\//
		else if (choice == 2) {

			FILE* fp = fp_new();

			fscanf(fp, "%d", &num_res);
			system("cls");

			printf("\nPlease enter the ID of the member you wish to change information of: ");
			long long select_res;

			RESIDENT* temp_res = temp();
			RESIDENT** arr_of_res = (RESIDENT**)calloc(num_res, sizeof(RESIDENT*));
			if (arr_of_res == NULL) {
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}

			for (int i = 0; i < num_res; i++) {
				arr_of_res[i] = temp();
			}

			int result;
			do {
				result = scanf("%lld", &select_res);
				while (getchar() != '\n');
				if (result == 0 || select_res < 100000000000 || select_res > 999999999999) {
					system("cls");
					printf("Invalid number, try again\n");
				}
			} while (result == 0 || select_res < 100000000000 || select_res > 999999999999);


			//Dinamièko zauzimanje
			short found = 0;
			for (int i = 0; i < num_res; i++) {
				fseek(fp, sizeof(short) + i * sizeof(RESIDENT), SEEK_SET);
				fscanf(fp, "%19s %19s %lld %c %hd %d %hd %hd %hd",
					temp_res->name, temp_res->last_name, &temp_res->ID, &temp_res->geneder,
					&temp_res->age, &temp_res->income,
					&temp_res->date_of_birth->day, &temp_res->date_of_birth->month,
					&temp_res->date_of_birth->year);

				if (temp_res->ID == select_res) {
					printf("\n\nSelected resident by ID:\nName : %s, Last_name : %s, ID : %lld, Income: %d, \nBorn on : %hd/%hd/%hd ",
						temp_res->name, temp_res->last_name, temp_res->ID, temp_res->income,
						temp_res->date_of_birth->day, temp_res->date_of_birth->month,
						temp_res->date_of_birth->year);
					found = i + 1;
					break;
				}
			}

			if (found == 0) {
				printf("\nMember does not exist");
			}
			else {
				short choice;
				system("cls");
				printf("\nEnter what do you want to change:\n1. For name\n2. For last name\n3.For income \n4.For Date of birth \n5. For age \nOr 6. For everything\n");

				do {
					result = scanf("%hd", &choice);
					while (getchar() != '\n');
					if (result == 0 || choice < 1 || choice > 6) {
						system("cls");
						printf("\nInvalid input please try again\n");
					}
				} while (result == 0 || choice < 1 || choice > 6);

				enum { NAME = 1, LAST_NAME, INCOME, DATE_OF_BIRTH, AGE, ALL };

				switch (choice) {
				case NAME:
					printf("\nPlease enter the new name: ");
					scanf("%19s", temp_res->name);
					break;
				case LAST_NAME:
					printf("\nPlease enter the new last name: ");
					scanf("%19s", temp_res->last_name);
					break;
				case INCOME:
					printf("\nPlease enter the new income: ");
					scanf("%d", &temp_res->income);
					break;
				case DATE_OF_BIRTH:
					printf("\nPlease enter the new birth day: ");
					scanf("%hd", &temp_res->date_of_birth->day);
					printf("\nPlease enter the new birth month: ");
					scanf("%hd", &temp_res->date_of_birth->month);
					printf("\nPlease enter the new birth year: ");
					scanf("%hd", &temp_res->date_of_birth->year);
					break;
				case AGE:
					printf("\nPlease enter the new age: ");
					scanf("%hd", &temp_res->age);
					break;
				case ALL:
					printf("\nPlease enter the new name: ");
					scanf("%19s", temp_res->name);
					printf("\nPlease enter the new last name: ");
					scanf("%19s", temp_res->last_name);
					printf("\nPlease enter the new income: ");
					scanf("%d", &temp_res->income);
					printf("\nPlease enter the new birth day: ");
					scanf("%hd", &temp_res->date_of_birth->day);
					printf("\nPlease enter the new birth month: ");
					scanf("%hd", &temp_res->date_of_birth->month);
					printf("\nPlease enter the new birth year: ");
					scanf("%hd", &temp_res->date_of_birth->year);
					printf("\nPlease enter the new age: ");
					scanf("%hd", &temp_res->age);
					break;
				}

				// Ažuriranje podataka
				fseek(fp, sizeof(short) + (found - 1) * sizeof(RESIDENT), SEEK_SET);
				fprintf(fp, "%s %s %lld %c %hd %d %hd %hd %hd\n",
					temp_res->name, temp_res->last_name, temp_res->ID, temp_res->geneder,
					temp_res->age, temp_res->income,
					temp_res->date_of_birth->day, temp_res->date_of_birth->month,
					temp_res->date_of_birth->year);
			}

			// Oslobaðanje memorije
			for (int i = 0; i < num_res; i++) {
				free(arr_of_res[i]);
			}
			free(arr_of_res);
			free(temp_res);

			char stay_in_loop;
			do {
				printf("Do you want to continue editing/deleting information? (y/n): ");
				scanf(" %c", &stay_in_loop);
				if ((stay_in_loop != 'y' && stay_in_loop != 'Y') && (stay_in_loop != 'n' && stay_in_loop != 'N')) {
					system("cls");
					printf("Invalid input. Please enter 'y' or 'n'\n");
				}
			} while ((stay_in_loop != 'y' && stay_in_loop != 'Y') && (stay_in_loop != 'n' && stay_in_loop != 'N'));

			if (stay_in_loop == 'n' || stay_in_loop == 'N') {
				f = 1; 
			}
			//Zatvaranje datoteke 
			fclose(fp); 
		}
	}
}