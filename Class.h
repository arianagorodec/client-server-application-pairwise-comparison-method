#pragma once
#include "includes.h"

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <iterator>

using namespace std;

int Menu_For_Admin(SOCKET c_sock);
int Menu_For_User(SOCKET c_sock);
int Menu_Control_User(SOCKET c_sock);
int Menu_Delete_User(SOCKET c_sock);
int Menu_Delete_Data(SOCKET c_sock);
int Menu_Edition_Expert(SOCKET c_sock);

double* Methods(SOCKET c_sock, int count_aims);
void All_result(SOCKET c_sock);
void Best_result(SOCKET c_sock);

class PERSON {

protected:
	char lastname[100];//фамилия
	char firstname[100];//имя
	char fathername[100];//отчество
public:
	PERSON(); // конструктор
	~PERSON(); //деструктор
	PERSON(const PERSON&name); //конструктор копирования
	char* Set_firstname(char* str);
	char* Set_lastname(char* str);
	char* Set_fathername(char* str);
	char* Get_firstname();
	char* Get_lastname();
	char* Get_fathername();
};


class USER : public PERSON {
	friend fstream Open_File(const char* name);
	template <typename T>
	friend list<T> Creat_list(const char* file_name,list<USER> l);
	template <class T>
	friend list<T> Delete(list<T> l, int k);
private:
	char login[256];
	char password[256];
public:
	USER(); // конструктор
	USER(const USER &user, const PERSON &name);  //конструктор копирования
	char* Get_login();
	char* Set_login(char* login);
	char* Get_password();
	char* Set_password(char* password);
	char* Set_firstname(char* s);
	char* Set_lastname(char* s);
	char* Set_fathername(char* s);
	void From_File(fstream& fp);
	char* Encrypt(char* password);//шифрование
	char* Deencrypt(char* password);//дешифрование
	void Find_user();
	void Edit_login(SOCKET);
	void Edit_password(SOCKET);
	void Print(SOCKET c_sock);
	int Check_User(list<USER> list_user, const char* name);
	void Delete_user(SOCKET c_sock);
	static void Add_user(SOCKET);
	static void User_output(list<USER> L);
	int Login(const char* name, SOCKET c_sock);
	static void Edit(SOCKET c_soket,const char* field);
	static void Output(SOCKET c_sock);
	friend ostream &operator<<(ostream &stream, USER u);
};


class EXPERT : public PERSON {
	friend fstream Open_File(const char* name);
	template <typename T>
	friend list<T> Creat_list(const char* file_name, list<T> l);
	template <class T>
	friend list<T> Delete(list<T> l, int k);
protected:
	int code;
	int code_post;
	int count_aims;
	vector<string> name_aims;
	int values[100][100];

public:
	EXPERT() :code(0), code_post(0), count_aims(0), PERSON() {}; // конструктор
	~EXPERT(); //деструктор
	EXPERT(const EXPERT &Expert, const PERSON &name); //конструктор копирования
	int Get_code();
	int Get_code_post();
	void Edit(SOCKET,const char* field, int code);
	void Set_code(int k);
	void Set_code_post(int k);
	void Set_name_aims(SOCKET);
	void Set_values(SOCKET);
	void Output_aims_and_values(SOCKET c_sock);
	void Output_one(SOCKET c_sock);
	void Edit_lastname(SOCKET c_sock);
	void Edit_firstname(SOCKET c_sock);
	void Edit_fathername(SOCKET c_sock);
	void Edit_post(SOCKET c_sock);
	void Edit_value(SOCKET c_sock);
	void Add_Expert(SOCKET c_sock);
	void Add_Name_Aims(SOCKET c_sock);
	void Delete_Name_Aims(SOCKET c_sock);
	void Output_Name_Aims(SOCKET c_sock);
	void Delete_expert(SOCKET c_sock);
	void Value_From_File(int c);
	void Name_aim_From_file();
	void Print(SOCKET c_sock);
	void Output(SOCKET c_sock);
	int Check_Expert(int code);
	void From_File(fstream &fp);
	friend ostream &operator<<(ostream &stream, EXPERT ex);
};

void My_result(SOCKET c_sock, EXPERT ex);
