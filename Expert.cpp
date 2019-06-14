#pragma once
#include "Class.h"



EXPERT::~EXPERT() {}
EXPERT::EXPERT(const EXPERT &Expert, const PERSON &name) : PERSON(name) {
	code = Expert.code;
	code_post = Expert.code_post;
	count_aims = Expert.count_aims;
	name_aims = Expert.name_aims;
	for (int i = 0; i < count_aims; i++) {
		for (int j = i; j < count_aims; j++) {
			values[i][j] = Expert.values[i][j];
		}
	}
}

void EXPERT::Set_code(int k) {
	code = k;
}
void EXPERT::Set_code_post(int k) {
	code_post=k;
}
void EXPERT::Set_values(SOCKET c_sock) {
	char ch[3], str[100];
	itoa(code, ch, 10);
	char name[100] = "Value_Aim";
	strcat(name, ch);

	name_aims.clear();
	string name_aim;

	fstream fp2 = Open_File("Name_Aim");
	fp2 >> count_aims;
	fp2.clear();
	fp2.ignore(100, '\n');
	for (int i = 0; i < count_aims; i++) {
		getline(fp2, name_aim, '\n');
		name_aims.push_back(name_aim);
	}
	fp2.close();

	itoa(count_aims, str, 10);
	send(c_sock, str, 100, 0);

	if (count_aims != 0) {
		fstream fp1;
		fp1.open(name, fstream::out);
		fp1.close();

		for (int i = 0; i < count_aims; i++) {
			for (int j = i; j < count_aims; j++) {
				if (i == j) {
					values[i][j] = 0;
				}
				else {
					send(c_sock, name_aims[i].c_str(), 100, 0);
					send(c_sock, name_aims[j].c_str(), 100, 0);
					recv(c_sock, str, sizeof(str), 0);
					values[i][j] = atoi(str);
					if (values[i][j] == 1) {
						values[j][i] = 0;
					}
					else if (values[i][j] == 0) {
						values[j][i] = 1;
					}
					else {
						values[j][i] = 2;
					}
				}
			}
		}

		fstream fp = Open_File(name);
		for (int i = 0; i < count_aims; i++) {
			for (int j = 0; j < count_aims; j++) {
				fp << values[i][j] << " ";
			}
		}
		fp.close();
	}
}

void EXPERT::Edit_value(SOCKET c_sock) {
	char ch[3], str[100];
	itoa(code, ch, 10);
	char name[100] = "Value_Aim";
	strcat(name, ch);

	name_aims.clear();
	string name_aim;

	fstream fp2 = Open_File("Name_Aim");
	fp2 >> count_aims;
	fp2.clear();
	fp2.ignore(100, '\n');
	for (int i = 0; i < count_aims; i++) {
		getline(fp2, name_aim, '\n');
		name_aims.push_back(name_aim);
	}
	fp2.close();

	itoa(count_aims, str, 10);
	send(c_sock, str, 100, 0);

	if (count_aims != 0) {

		fstream fp2 = Open_File(name);
		fp2.seekg(0, ios::end);
		int file_size = fp2.tellg();
		if (file_size == 0){
			send(c_sock, "Файл пуст", 100,0);
			fp2.close();
		}
		else {
			fp2.seekg(0, ios::beg);
			for (int i = 0; i < count_aims; i++) {
				for (int j = 0; j < count_aims; j++) {
					fp2 >> values[i][j];
					itoa(values[i][j], str, 10);
					send(c_sock, str, 100, 0);
				}
			}
			fp2.close();

			for (int i = 0; i < count_aims; i++) {
				for (int j = i; j < count_aims; j++) {
					if (i == j)
						values[i][j] = 0;
					else {
						send(c_sock, name_aims[i].c_str(), 100, 0);
						send(c_sock, name_aims[j].c_str(), 100, 0);
						recv(c_sock, str, sizeof(str), 0);
						values[i][j] = atoi(str);
						if (values[i][j] == 1) {
							values[j][i] = 0;
						}
						else if (values[i][j] == 0) {
							values[j][i] = 1;
						}
						else
							values[j][i] = 2;
					}

				}
			}

			fstream fp1;
			fp1.open(name, fstream::out);
			fp1.close();

			fstream fp = Open_File(name);
			for (int i = 0; i < count_aims; i++) {
				for (int j = 0; j < count_aims; j++) {
					fp << values[i][j] << " ";
				}
			}
			fp.close();
		}
	}
}

void EXPERT::Output_Name_Aims(SOCKET c_sock) {

	name_aims.clear();
	string name_aim;

	fstream fp2 = Open_File("Name_Aim");
	fp2 >> count_aims;
	char string[100];
	itoa(count_aims, string, 10);
	send(c_sock, string, 100, 0);
	fp2.clear();
	fp2.ignore(100, '\n');
	for (int i = 0; i < count_aims; i++) {
		getline(fp2, name_aim, '\n');
		send(c_sock, name_aim.c_str(), 100, 0);
	}
	fp2.close();

}

void EXPERT::Output_aims_and_values(SOCKET c_sock) {
		char ch[3], str[100];
		itoa(code, ch, 10);
		char name[100] = "Value_Aim";
		strcat(name, ch);

		name_aims.clear();
		string name_aim;

		fstream fp2 = Open_File("Name_Aim");
		fp2 >> count_aims;
		fp2.clear();
		fp2.ignore(100, '\n');
		for (int i = 0; i < count_aims; i++) {
			getline(fp2, name_aim, '\n');
			name_aims.push_back(name_aim);
		}
		fp2.close();

		itoa(count_aims, str, 10);
		send(c_sock, str, 100, 0);
		
		int k = 0;
		int l = 0;

		if (count_aims != 0) {
			fstream fp = Open_File(name);
			fp.seekg(0, ios::end);
			int file_size = fp.tellg();
			if (file_size == 0) {
				l++;
				fp.close();
			}
			if (count_aims == l) {
				send(c_sock, "-", 100, 0);
				send(c_sock, "Значения в файл не введены", 100, 0);
			}

			else {
				for (int i = 0; i < count_aims; i++) {
					if (k == 1)
						break;
					for (int j = 0; j < count_aims; j++) {
						if (i != j) {
							fp >> values[i][j];
							send(c_sock, name_aims[i].c_str(), 100, 0);
							send(c_sock, name_aims[j].c_str(), 100, 0);
							itoa(values[i][j], str, 10);
							send(c_sock, str, 100, 0);
						}
					}
				}
			}
			fp.close();
			if (count_aims == l) {
				send(c_sock, "-", 100, 0);
				send(c_sock, "Значения в файл не введены", 100, 0);
			}
		}
}


void EXPERT::Set_name_aims(SOCKET c_sock) {
	char str[256];
	recv(c_sock, str, sizeof(str), 0);
	string obj(str);
	name_aims.push_back(obj);
	count_aims++;
}

void EXPERT::Edit_lastname(SOCKET c_sock) {
	char lastname[100];
	recv(c_sock, lastname, sizeof(lastname), 0);
	PERSON::Set_lastname(lastname);
}

void EXPERT::Edit_firstname(SOCKET c_sock) {
	char firstname[100];
	recv(c_sock, firstname, sizeof(firstname), 0);
	Set_firstname(firstname);
}

void EXPERT::Edit_fathername(SOCKET c_sock) {
	char fathername[100];
	recv(c_sock, fathername, sizeof(fathername), 0);
	Set_fathername(fathername);
}

void EXPERT::Edit_post(SOCKET c_sock) {
	char post[100];
	recv(c_sock, post, sizeof(post), 0);
	int code_post = atoi(post);
	Set_code_post(code_post);
}



int EXPERT::Get_code() {
	return code;
}
int EXPERT::Get_code_post() {
	return code_post;
}

void EXPERT::Add_Expert(SOCKET c_sock) {
	EXPERT newex;
	list<EXPERT> list_ex;
	char string[100];
	list_ex = Creat_list("Expert", list_ex);
	int count=list_ex.size();
	count++;
	newex.Set_code(count);
	recv(c_sock, string, sizeof(string), 0);
	newex.Set_lastname(string);
	recv(c_sock, string, sizeof(string), 0);
	newex.Set_firstname(string);
	recv(c_sock, string, sizeof(string), 0);
	newex.Set_fathername(string);
	recv(c_sock, string, sizeof(string), 0);
	int k = atoi(string);
	newex.Set_code_post(k);

	fstream fp = Open_File("Expert");
	fp << newex;
	fp.close();
}

void EXPERT::Add_Name_Aims(SOCKET c_sock) {
	Output_Name_Aims(c_sock);
	name_aims.clear();
	string name;

	fstream fp2 = Open_File("Name_Aim");
	fp2 >> count_aims;
	fp2.clear();
	fp2.ignore(100, '\n');
	for (int i = 0; i < count_aims; i++) {

		getline(fp2, name, '\n');
		name_aims.push_back(name);
	}
	fp2.close();

	Set_name_aims(c_sock);

	fstream fp1;
	fp1.open("Name_Aim", fstream::out);
	fp1.close();

	fstream fp = Open_File("Name_Aim");
	fp << count_aims << "\n";
	for (int i = 0; i < count_aims; i++) {
		fp << name_aims[i] << "\n";
	}
	fp.close();

	list<EXPERT> list_expert;
	list_expert = Creat_list("Expert", list_expert);

	char ch[10];
	for (EXPERT ex : list_expert) {
		itoa(ex.Get_code(), ch, 10);
		char name[100] = "Value_Aim";
		strcat(name, ch);

		fstream fp;
		fp.open(name, fstream::out);
		fp.close();
	}
}

void EXPERT::Delete_Name_Aims(SOCKET c_sock) {
	Output_Name_Aims(c_sock);
	string name;
	char name1[256];
	int k = 0, stringf = 0;
	recv(c_sock, name1, sizeof(name1), 0);
	name_aims.clear();
	fstream fp2 = Open_File("Name_Aim");
	fp2 >> count_aims;
	fp2.clear();
	fp2.ignore(100, '\n');
	for (int i = 0; i < count_aims; i++) {
		getline(fp2, name, '\n');
		name_aims.push_back(name);
	}
	int num=0;
	auto it = name_aims.begin();
	for ( string str : name_aims) {
		if (str==((string)name1)) {
			name_aims.erase(it);
			count_aims--;
			stringf++;
			break;
		}
		it++;
		num++;
	}
	itoa(stringf, name1, 10);
	send(c_sock, name1, 100, 0);

	if (stringf != 0){
		fstream fp1;
		fp1.open("Name_Aim", fstream::out);
		fp1.close();
		fstream fp = Open_File("Name_Aim");
		fp << count_aims << "\n";
		for (int i = 0; i < count_aims; i++) {
			fp << name_aims[i] << "\n";
		}
		fp.close();
	}

	list<EXPERT> list_expert;
	list_expert = Creat_list("Expert", list_expert);
	int count_ex = list_expert.size();
	count_aims++;

	int** values_for_expert = new int*[count_aims];
	for (int i = 0; i < count_aims; i++) {
		values_for_expert[i] = new int[count_aims];
	}

	char ch[10];
	int* broke_expert = new int[count_ex];
	int t = 0, f = 0;
	k = 0;
	for (EXPERT ex : list_expert) {

		double newvalues;
		double values = 0;
		double sum = 0;


		itoa(ex.Get_code(), ch, 10);
		char name[100] = "Value_Aim";
		strcat(name, ch);

		fstream fp = Open_File(name);
		fp.seekg(0, ios::end);
		int file_size = fp.tellg();

		if (file_size != 0) {
			fp.seekg(0, ios::beg);
			for (int j = 0; j < count_aims; j++) {
				for (int i = 0; i < count_aims; i++) {
					fp >> values_for_expert[j][i];
					if (fp.eof()) {
						break;
					}
				}
			}
		}

		fp.close();
		fstream fp1;
		fp1.open(name, fstream::out);
	
		if (file_size != 0) {
			for (int i = 0; i < count_aims; i++) {
				for (int j = 0; j < count_aims; j++) {
					if (j != num) {
						fp1 << values_for_expert[i][j]<<" ";
					}
				}
			}
		}
		fp1.close();
	}
}

void EXPERT::Delete_expert(SOCKET c_sock) {
	char string[100];
	int k = 0, stringf = 0;
	Output(c_sock);
	recv(c_sock, string, sizeof(string), 0); //получение результата
	int code = atoi(string);
	list<EXPERT> list_expert;
	list_expert = Creat_list("Expert", list_expert);
	list<EXPERT>::iterator it = list_expert.begin();
	for (EXPERT ex : list_expert) {
		if (code==ex.code) {
			list_expert = Delete(list_expert, k);
			stringf++;
			break;
		}
		k++;
	}
	itoa(stringf, string, 10);
	send(c_sock, string, 100, 0);
	if (stringf != 0) {
		fstream fp1;
		fp1.open("Expert", fstream::out);
		fp1.close();
		fstream fp = Open_File("Expert");
		for (EXPERT ex : list_expert) {
			fp << ex;
		}
		fp.close();
	}
}


void EXPERT::Value_From_File(int c) {
	int v;
	char ch[100];
	itoa(c, ch, 10);
	char name[100] = "Value_Aim";
	strcat(name,ch);
	fstream fp1 = Open_File("Name_Aim");
	fp1 >> count_aims;
	fp1.close();
	fstream fp = Open_File(name);
	for (int i = 0; i < count_aims; i++) {
		for (int j = 0; j < count_aims; j++) {
			fp >> v;
			values[i][j] = v;
		}
	}
	fp.close();
}

void EXPERT::Name_aim_From_file() {
	fstream fp = Open_File("Name_Aim");
	string name;
	fp >> count_aims;
	for (int i = 0; i < count_aims; i++) {
		//fp >> name;
		getline(fp, name, '\n');
		//getline(fp, name);
		name_aims.push_back(name);
	}
	fp.close();
}

void EXPERT::From_File(fstream &fp) {
	fp >> code;
	fp >> code_post;
	fp >> lastname;
	fp >> firstname;
	fp >> fathername;
	Name_aim_From_file();
	Value_From_File(code);
}

int EXPERT::Check_Expert (int code) {
	int id = 0;
	list<EXPERT> list_Expert;
	list_Expert = Creat_list("Expert", list_Expert);
	if (list_Expert.size() == 0) {
		return 0;
	}
	else {
		for (EXPERT expert : list_Expert) {
			if (code == expert.code)
			{
				id = 1;
				break;
			}
		}
	}
	return id;
}


void EXPERT::Edit(SOCKET c_sock, const char* field,int code) {
	list<EXPERT> list_expert;
	list_expert = Creat_list("Expert", list_expert);
	list<EXPERT>::iterator it = list_expert.begin();
	int t = 0,k=1;
	char string[100];
	int stringf, stringf1; 
	for (EXPERT expert : list_expert) {
		int tr = 0;
		if (expert.Get_code()== code) {
			if (strcmp(field, "lastname") == 0) {
				list_expert.erase(it);
				recv(c_sock, string, sizeof(string), NULL);
				expert.Set_lastname(string);
				list_expert.push_back(expert);
			}
			else if (strcmp(field, "firstname") == 0) {
				list_expert.erase(it);
				recv(c_sock, string, sizeof(string), NULL);
				expert.Set_firstname(string);
				list_expert.push_back(expert);
			}
			else if (strcmp(field, "fathername") == 0) {
				list_expert.erase(it);
				recv(c_sock, string, sizeof(string), NULL);
				expert.Set_fathername(string);
				list_expert.push_back(expert);
			}
			else if (strcmp(field, "post") == 0) {
				list_expert.erase(it);
				recv(c_sock, string, sizeof(string), NULL);
				stringf = atoi(string);
				expert.Set_code_post(stringf);
				list_expert.push_back(expert);
			}
			break;
		}
		t++;
		++it;
	}

	fstream fp1;
	fp1.open("Expert", fstream::out);
	fp1.close();

	fstream fp = Open_File("Expert");
	for (EXPERT ex:list_expert) {
		fp << ex;
	}
	fp.close();
}

void EXPERT::Print(SOCKET c_sock) {
	char post[30];
	char string[100];
	if (code_post == 1)
		strcpy(post, "Первая");
	else if (code_post == 2)
		strcpy(post, "Вторая");
	else if (code_post == 3)
		strcpy(post, "Третья");
	itoa(code, string, 10);
	send(c_sock, string, 100, 0);
	send(c_sock, post, 100, 0);
	send(c_sock, lastname, 100, 0);
	send(c_sock, firstname, 100, 0);
	send(c_sock, fathername, 100, 0);
}

void EXPERT::Output(SOCKET c_sock) {
	list<EXPERT> list_expert;
	USER us;
	char string[256];
	list_expert = Creat_list("Expert", list_expert);
	int n = 1;
	int k = list_expert.size();
	itoa(k, string, 10);
	send(c_sock, string, 100, 0);
	for (EXPERT ex : list_expert) {
		ex.Print(c_sock);
	}
}


void EXPERT::Output_one(SOCKET c_sock) {
	list<EXPERT> list_expert;
	USER us;
	char string[256];
	list_expert = Creat_list("Expert", list_expert);
	int n = 1;
	int k = list_expert.size();
	itoa(k, string, 10);
	send(c_sock, string, 100, 0);
	Print(c_sock);
}

ostream &operator<<(ostream &stream, EXPERT ex) {
	stream << ex.Get_code() << " " << ex.Get_code_post() << " " << ex.Get_lastname() << " " << ex.Get_firstname() << " " << ex.Get_fathername() << "\n";
	return stream;
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