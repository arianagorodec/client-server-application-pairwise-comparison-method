#include "Class.h"


template <class T>
list<T> Delete_All(const char* file_name);

int Menu_For_Admin(SOCKET c_sock) {
	USER USER;
	EXPERT ex;
	int id = USER.Login("Admin",c_sock);
	char buf[100];
	itoa(id, buf, 10);
	send(c_sock, buf, 100, 0);
	if (id != 0) {
		for (;;) {
			recv(c_sock, buf, sizeof(buf), NULL);
			int k = atoi(buf);
			switch (k) {
			case 0: ex.Add_Expert(c_sock); break;
			case 1: Menu_Edition_Expert(c_sock); break;
			case 2: Menu_Delete_Data(c_sock); break;
			case 3: ex.Output(c_sock); break;
			case 4: ex.Add_Name_Aims(c_sock); break;
			case 5: ex.Delete_Name_Aims(c_sock); break;
			case 6: Menu_Control_User(c_sock); break;
			case 7: Best_result(c_sock); break;
			case 8: All_result(c_sock); break;
			case 9: return 0;
			}
		}
	}
	else return 0;
}
int Menu_For_User(SOCKET c_sock) {
	USER user;
	EXPERT expert;
	int id = user.Login("User", c_sock);

	list<EXPERT> list_ex;
	list_ex = Creat_list("Expert", list_ex);
	
	for (EXPERT ex : list_ex) {
		if (strcmp(ex.Get_lastname(), user.Get_lastname()) == 0) {
			if (strcmp(ex.Get_firstname(), user.Get_firstname()) == 0) {
				if (strcmp(ex.Get_fathername(), user.Get_fathername()) == 0) {
					expert = ex;
					break;
				}
			}


		}
	}
	char buf[100], kd[4];
	itoa(id, buf, 10);
	send(c_sock, buf, 100, 0);
	if (id != 0) {
		for (;;) {
			recv(c_sock, buf, sizeof(buf), NULL);
			int k = atoi(buf);
			switch (k) {
			case 0: expert.Set_values(c_sock); break;
			case 1: expert.Edit_value(c_sock); break;
			case 2: Best_result(c_sock); break;
			case 3: My_result(c_sock, expert); break;
			case 4: expert.Print(c_sock); break;
			case 5: return 0;
			}
		}
	}
	else return 0;
}

int Menu_Edition_Expert(SOCKET c_sock) {
	EXPERT ex;
	int id;
	ex.Output(c_sock);
	char buf[100], kd[4];
	recv(c_sock, buf, sizeof(buf), NULL);
	int code = atoi(buf);
	id=ex.Check_Expert(code);

	itoa(id, buf, 10);
	send(c_sock, buf, 100, 0);
	if (id == 0) {
		return 0;
	}
	for (;;) {
		recv(c_sock, buf, sizeof(buf), NULL);
		int k = atoi(buf);
		switch (k) {
		case 0: ex.Edit(c_sock, "lastname", code); break;
		case 1: ex.Edit(c_sock, "firstname", code); break;
		case 2: ex.Edit(c_sock, "otchestvo", code);break;
		case 3: ex.Edit(c_sock, "post",code); break;
		case 4: return 0;
		}
	}
}
int Menu_Control_User(SOCKET c_sock) {
	USER user;
	char buf[100];
	for (;;) {
		recv(c_sock, buf, sizeof(buf), NULL);
		int k = atoi(buf);
		switch (k) {
		case 0: user.Output(c_sock);break;
		case 1: user.Edit(c_sock,"login"); break;
		case 2: user.Edit(c_sock,"password");break;
		case 3: Menu_Delete_User(c_sock);  break;
		case 4: return 0;
		}
	}
}
int Menu_Delete_User(SOCKET c_sock) {
	char buf[100];
	for (;;) {
		recv(c_sock, buf, sizeof(buf), NULL);
		int k = atoi(buf);
		switch (k) {
		case 0: Delete_All<USER>("User"); break;
		case 1: {USER user; user.Delete_user(c_sock); break; }
		case 2: return 0;
		}
	}
}
int Menu_Delete_Data(SOCKET c_sock) {
	char buf[100];
	for (;;) {
		recv(c_sock, buf, sizeof(buf), NULL);
		int k = atoi(buf);
		switch (k) {
		case 0: Delete_All<EXPERT>("Expert"); break;
		case 1: {EXPERT ex; ex.Delete_expert(c_sock); }break;
		case 2: return 0;
		}
	}
}

template <class T>
list<T> Delete_All(const char* file_name) {
	list<T> l;
	Creat_list(file_name, l);
	auto it = l.begin();
	while (it != l.end()) {
		l.erase(it);
		it++;
	}

	fstream fp;
	fp.open(file_name, fstream::out);
	fp.close();

	return l;
}