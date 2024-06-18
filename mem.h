#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


//Datoteka namjenjena za rad sa memorijom ukljuèujuæi funkcije èija je zadaæa rad sa poljima, strukturama i fileovima

int check_file_existence();

FILE* fp_new();

void new_resident(FILE* fp);

typedef struct date {

	signed short day;
	signed short month;
	signed short year;

}DOB;

typedef struct residents {

	char* name;
	char* last_name;
	short age;
	char geneder;
	long long int ID;
	DOB* date_of_birth;
	signed int income;

}RESIDENT;

RESIDENT* temp(void);

long long int rand_num_gen();

DOB* temp_res_dob();

void print_members_select(void);

void print_all(void);

void print_one(void);

void delete_file(char* file_name);

int check_file_contet(const char* file_name);