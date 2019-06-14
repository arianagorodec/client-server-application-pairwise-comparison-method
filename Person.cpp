#pragma once
#include "Class.h"

PERSON::PERSON() {
}
PERSON::~PERSON() {

}
PERSON::PERSON(const PERSON&name) {
	strcpy(lastname, name.lastname);
	strcpy(firstname, name.firstname);
	strcpy(fathername, name.fathername);
}

char* PERSON::Set_firstname(char* str) {
	strcpy(firstname, str);
	return str;
}
char* PERSON::Set_lastname(char* str) {
	strcpy(lastname, str);
	return str;
}
char* PERSON::Set_fathername(char* str) {
	strcpy(fathername, str);
	return str;
}

char* PERSON::Get_firstname() {
	return firstname;
}

char* PERSON::Get_lastname() {
	return lastname;
}

char* PERSON::Get_fathername() {
	return fathername;
}