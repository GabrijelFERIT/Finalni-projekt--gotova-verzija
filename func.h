#pragma once

#include "mem.h"
//Datotteka namjenjena za upisivanje, ispisivanje sadržaja te popunjavanje polja, generiranje nasumièno generiranih brojeva, itd.


void main_terminal();

void terminate_program();

int selection(char* const file_name);

short search_func(char* file_name);

void editing_del_info(void);

void sorting_func(char* file_name);

int compareByName(const void* a, const void* b);

int compareByLastName(const void* a, const void* b);

int compareByID(const void* a, const void* b);