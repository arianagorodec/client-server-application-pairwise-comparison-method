#pragma once
#include "Class.h"

USER::USER() :PERSON() {
}

USER::USER(const USER&user, const PERSON &name) : PERSON(name) {
	strcpy(login, user.login);
	strcpy(password, user.password);
}

char* USER::Get_login() {
	return this->login;
}
char* USER::Set_login(char* login) {
	strcpy(this->login, login);
	return login;
}


char* USER::Get_password() {
	Deencrypt(this->password);
	return this->password;
}
char* USER::Set_password(char* password) {
	Encrypt(password);
	strcpy(this->password, password);
	return this->password;
}

char* USER::Set_firstname(char* s) {
	strcpy(firstname, s);
	return firstname;
}
char*  USER::Set_lastname(char* s) {
	strcpy(lastname, s);
	return lastname;
}
char* USER::Set_fathername(char* s) {
	strcpy(fathername, s);
	return fathername;
}

void USER::Add_user(SOCKET c_sock) {
	USER newuser;
	list<USER> list_user;
	list<EXPERT> list_ex;
	list_user = Creat_list("User", list_user);
	list_ex = Creat_list("Expert", list_ex);
	int stringf = 0, sw = 0;
	char string[100];
	while (sw != 3) {
		recv(c_sock, string, sizeof(string), 0);
		newuser.Set_lastname(string);
		recv(c_sock, string, sizeof(string), 0);
		newuser.Set_firstname(string);
		recv(c_sock, string, sizeof(string), 0);
		newuser.Set_fathername(string);
		for (EXPERT ex : list_ex) {
			stringf = 0;
			if (strcmp(ex.Get_lastname(), newuser.Get_lastname()) == 0) {
				if (strcmp(ex.Get_firstname(), newuser.Get_firstname()) == 0) {
					if (strcmp(ex.Get_fathername(), newuser.Get_fathername()) == 0) {
						stringf++;
						break;
					}
				}
			}
		}
		if (stringf == 0) {
			itoa(stringf, string, 10);
			send(c_sock, string, 100, 0);
			sw++;
		}
		else {
			itoa(stringf, string, 10);
			send(c_sock, string, 100, 0);
			sw = 3;
		}
	}

	stringf = 0;
	while (1) {
		recv(c_sock, string, sizeof(string), 0);
		newuser.Set_login(string);
		for (USER user : list_user) {
			stringf = 0;
			if (strcmp(user.login, newuser.login) == 0) {
				stringf++;
				send(c_sock, string, 100, 0);
				break;
			}
		}
		if (stringf == 0) {
			break;
		}
	}
	itoa(stringf, string, 10);
	send(c_sock, string, 100, 0);// string in client
	recv(c_sock, string, sizeof(string), 0);//get password;
	newuser.Set_password(string);
	fstream fp = Open_File("User");
	fp << newuser.lastname;
	fp << " ";
	fp << newuser.firstname;
	fp << " ";
	fp << newuser.fathername;
	fp << " ";
	fp << newuser.login;
	fp << " ";
	fp << newuser.password;
	fp << "\n";
	fp.close();
}

void USER::From_File(fstream &fp) {
	fp >> lastname;
	fp >> firstname;
	fp >> fathername;
	fp >> login;
	fp >> password;
}


ostream &operator<<(ostream &stream, USER u) {
	stream << u.lastname<<" "<< u.firstname<<" "<< u.fathername<<" "<< u.login<<" "<< u.password<<"\n";
	return stream;
}

void USER::User_output(list<USER> list_user) {
	USER us;
	int n = 1;
	list_user = Creat_list("User", list_user);
	if (!list_user.empty()) {
		for (USER user : list_user) {
			user.Print(n);
			n++;
		}
	}
}

int USER::Login(const char* name, SOCKET c_sock) {
	USER user;
	int i = 0;
	recv(c_sock, user.login, sizeof(user.login), NULL);
	recv(c_sock, user.password, sizeof(user.password), NULL);
	strcpy(user.password, user.Encrypt(user.password));
	list<USER> list_user;
	list_user = Creat_list(name, list_user);
	int id = user.Check_User(list_user, name);
	if (id == 0) {
		return 0;
	}
	else {
		strcpy(lastname ,user.lastname);
		strcpy(firstname, user.firstname);
		strcpy(fathername, user.fathername);
		return id;
	}
}

int USER::Check_User(list<USER> list_user, const char* name) {
	int id = 0;
	if (strcmp(name, "Admin") == 0) {
		if (list_user.size() == 0) {
			return 0;
		}
		else {
			for (USER user : list_user) {
				if ((strcmp(login, user.login) == 0) && (strcmp(password, user.password) == 0))
				{
					id = 1;
					break;
				}
			}
		}
		return id;
	}
	else {
		list<EXPERT> list_ex;
		list_ex= Creat_list("Expert", list_ex);
		if (list_user.size() == 0) {
			return 0;
		}
		else {
			for (USER user : list_user) {
				if ((strcmp(login, user.login) == 0) && (strcmp(password, user.password) == 0))
				{
					for (EXPERT ex : list_ex) {
						if ((strcmp(user.lastname, ex.Get_lastname()) == 0))
						{
							if ((strcmp(user.firstname, ex.Get_firstname()) == 0))
							{
								if ((strcmp(user.fathername, ex.Get_fathername()) == 0))
								{
									strcpy(lastname, user.lastname);
									strcpy(firstname, user.firstname);
									strcpy(fathername, user.fathername);
									id++;
									break;
								}
							}
						}
					}
				}
			}
			return id;
		}
	}
}

char* USER::Encrypt(char* password) {
	int i = 0;
	char temp;
	int size = strlen(password);
	while (i < size - 2) {
		temp = password[i];
		password[i] = password[i + 2];
		password[i + 2] = temp;
		i += 3;
	}
	return password;
}

char* USER::Deencrypt(char* password) {
	int i = 0;
	char temp;
	int size = strlen(password);
	while (i < size - 2) {
		temp = password[i + 2];
		password[i + 2] = password[i];
		password[i] = temp;
		i += 3;
	}
	return password;
}

void USER::Print(SOCKET c_sock) {
	//int size = strlen(s);
	strcpy(password, Deencrypt(password));
	send(c_sock, lastname, 100, 0);
	send(c_sock, firstname, 100, 0);
	send(c_sock, fathername, 100, 0);
	send(c_sock, login, 100, 0);
	send(c_sock, password, 100, 0);
}

void USER::Output(SOCKET c_sock) {
	list<USER> list_user;
	USER us;
	char string[256];
	list_user = Creat_list("User", list_user);
	int n = 1;
	int k = list_user.size();
	itoa(k, string, 10);
	send(c_sock, string, 100, 0);
	if (k != 0) {
		for (USER user : list_user) {
			user.Print(c_sock);
		}
	}
}

void USER::Find_user() {
	list<USER> list_user;
	list_user = Creat_list("User", list_user);
	char* login_us = new char[100];
	int n = 1, stringf = 0;
	cout << "Введите логин пользователя, информацию о котором хотите найти: " << endl;
	cin >> login_us;
	for (USER user : list_user) {
		if (strcmp(user.login, login_us) == 0) {
			user.Print(n);
			n++;
			stringf++;
		}
	}
	if (stringf == 0) {
		cout << "Такого пользователя не найдено." << endl;
	}
	_getch(); _getch();
}

void USER::Edit_login(SOCKET c_sock) {
	char login[100];
	recv(c_sock, login, sizeof(login), 0);
	Set_login(login);
}

void USER::Edit_password(SOCKET c_sock) {
	char password[100];
	recv(c_sock, password, sizeof(password), 0);
	Set_password(password);
}

void USER::Edit(SOCKET c_sock, const char* field) {
	list<USER> list_user;
	list_user = Creat_list("User", list_user);
	int stringf = 0, t = 0;
	char string[100],pass[100];
	char id[100];
	Output(c_sock);
	recv(c_sock, id, sizeof(id), 0); //получение результата
	int k=0;
	for (USER user : list_user) {
		k = 0;
		if (strcmp(user.Get_login(), id) == 0) {
			k = 1;
			itoa(k, string, 10);
			send(c_sock, string, 100, 0);
			if (strcmp(field, "login") == 0) {
				list_user = Delete(list_user, t);
				user.Edit_login(c_sock);
				list_user.push_back(user);
			}
			else if (strcmp(field, "password") == 0) {
				list_user = Delete(list_user, t);
				user.Edit_password(c_sock);
				list_user.push_back(user);
			}
			stringf++;
			break;
		}
		else {
			k = 0;
			itoa(k, string, 10);
		}
		t++;
	}
	if (k == 0) {
		send(c_sock, string, 100, 0);
	}
	if (stringf != 0) {
		fstream fp1;
		fp1.open("User", fstream::out);
		fp1.close();
		fstream fp = Open_File("User");
		for (USER u : list_user) {
			fp << u;
		}
		fp.close();
	}
}


void USER::Delete_user(SOCKET c_sock) {
	char login[256];
	char string[100];
	int k = 0, stringf = 0;
	Output(c_sock);
	recv(c_sock, login, sizeof(login), 0); //получение результата
	list<USER> list_user;
	list_user = Creat_list("User", list_user);
	list<USER>::iterator it = list_user.begin();
	for (USER user : list_user) {
		if (strcmp(login, user.login) == 0) {
			list_user = Delete(list_user, k);
			stringf++;
			break;
		}
		k++;
	}
	itoa(stringf, string, 10);
	send(c_sock, string, 100, 0);
	if (stringf != 0) {
		fstream fp1;
		fp1.open("User", fstream::out);
		fp1.close();
		fstream fp = Open_File("User");
		for (USER user : list_user) {
			fp << user;
		}
		fp.close();
	}
}

fstream Open_File(const char* name) {
	fstream fp;
	fp.open(name, fstream::in | fstream::out | fstream::app);
	if (!fp) {
		printf("Ошибка открытия файла!\n");
		_getch(); _getch();
	}
	return fp;
}

template <class T>
list<T> Creat_list(const char* file_name, list<T> l) {
	fstream fp = Open_File(file_name);
	if (fp) {
		fp.seekg(0, ios::end);
		int end_size = fp.tellg();
		fp.seekg(0, ios::beg);
		int current_size = fp.tellg();
		int k = 0;
		if (end_size == current_size) {}
		else {
			if (l.empty()) {
				while (k == 0) {
					T obj;
					if ((current_size + 2) == end_size) {
						k = 1;
					}
					else {
						obj.From_File(fp);
						l.push_back(obj);
						current_size = fp.tellg();
					}
				}
			}
		}
	}
	return l;
}

template <class T>
list<T> Delete(list<T> l, int k) {
	auto it = l.begin();
	for (int t = 0; t < k; t++) {
		it++;
	}
	l.erase(it);
	return l;
}
