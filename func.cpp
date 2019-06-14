#include "Class.h"

double* Methods(SOCKET c_sock, int number_aims) {
	list<EXPERT> expert;
	expert = Creat_list("Expert", expert);

	double* end_values = new double[number_aims];
	int size = expert.size();

	int* empty_expert = new int[size];
	char str[100];
	double sum = 0;

	double** all_values = new double*[size];
	for (int i = 0; i < size; i++) {
		all_values[i] = new double[number_aims];
	}

	if (number_aims) {
		int column = 0;
		int k = 0;
		int num = 0;

		for (EXPERT ex : expert) {

			double newvalues;
			double values = 0;
			double sum = 0;
			char ch[10];

			itoa(ex.Get_code(), ch, 10);
			char name[100] = "Value_Aim";
			strcat(name, ch);

			fstream file = Open_File(name);
			file.seekg(0, ios::end);
			int file_size = file.tellg();
			if (file_size == 0) {
				size--;
				empty_expert[k] = num;
				k++;
				file.close();
			}

			else {
				file.seekg(0, ios::beg);
				for (int j = 0; j < number_aims; j++) {
					values = 0;
					for (int i = 0; i < number_aims; i++) {
						file >> newvalues;
						if (!file.eof()) {
							values = values + newvalues;
						}
						else {
							int num = 1;
							send(c_sock, "4", 100, 0);
							send(c_sock, "Нет значений", 100, 0);
							break;
						}
					}
					all_values[column][j] = values;
				}
				file.close();

				for (int i = 0; i < number_aims; i++) {
					sum = sum + all_values[column][i];
				}
				for (int i = 0; i < number_aims; i++) {
					all_values[column][i] = all_values[column][i] / sum;
				}
				column++;
			}
			num++;
		}

		double multiplier;
		for (int j = 0; j < number_aims; j++) {
			end_values[j] = 0;
			int i = 0;
			for (EXPERT ex : expert) {
				int cnt = 0;
				for (int m = 0; m < f; m++) {
					if (empty_expert[m] == i) {
						cnt = 1;
					}
				}
				if (cnt == 0) {
					if (ex.Get_code_post() == 1)
						multiplier = 0.5;
					else if (ex.Get_code_post() == 2)
						multiplier = 0.3;
					else if (ex.Get_code_post() == 3)
						multiplier = 0.2;
					end_values[j] += (all_values[i][j] * multiplier);
				}
				i++;
			}
		}

		double end_sum = 0;
		for (int j = 0; j < number_aims; j++) {
			end_sum += end_values[j];
		}
		for (int j = 0; j < number_aims; j++) {
			end_values[j] /= end_sum;
		}
		return end_values;
	}

}

void Best_result(SOCKET c_sock) {

	int number_aims = 0;
	string name_aim;
	vector<string> name_aims;
	char str[100];

	fstream file2 = Open_File("Name_Aim");
	file2.seekg(0, ios::end);
	int file_size = file2.tellg();
	if (file_size != 0) {
		file2.seekg(0, ios::beg);
		file2 >> number_aims;
		file2.clear();
		file2.ignore(100, '\n');
		for (int i = 0; i < number_aims; i++) {
			getline(file2, name_aim, '\n');
			name_aims.push_back(name_aim);
		}
		file2.close();

		itoa(number_aims, str, 10);
		send(c_sock, str, 100, 0);

		double* end_values = new double[number_aims];
		end_values = Methods(c_sock, number_aims);
		double best_result = end_values[0];
		int number_best_result = 0;
		for (int i = 1; i < number_aims; i++) {
			if (end_values[i] > best_result) {
				best_result = end_values[i];
				number_best_result = i;
			}
		}
		char* res;
		send(c_sock, "1", 100, 0);
		string str = to_string(best_result);
		send(c_sock, name_aims[number_best_result].c_str(), 100, 0);
		send(c_sock, str.c_str(), 100, 0);
	}
	else
		send(c_sock, "0", 100, 0);
}

void All_result(SOCKET c_sock) {

	int number_aims = 0;
	string name_aim;
	vector<string> name_aims;
	char str[100];

	fstream file2 = Open_File("Name_Aim");
	file2 >> number_aims;
	file2.clear();
	file2.ignore(100, '\n');
	for (int i = 0; i < number_aims; i++) {
		getline(file2, name_aim, '\n');
		name_aims.push_back(name_aim);
	}
	file2.close();

	itoa(number_aims, str, 10);
	send(c_sock, str, 100, 0);

	double* end_values = new double[number_aims];
	end_values = Methods(c_sock, number_aims);
	for (int i = 0; i < number_aims; i++) {
			string str = to_string(end_values[i]);
			send(c_sock, name_aims[i].c_str(), 100, 0);
	}

	list<EXPERT> expert;
	expert = Creat_list("Expert", expert);
	int count_ex = expert.size();
	itoa(count_ex, str, 10);
	send(c_sock, str, 100, 0);
	char ch[10];
	int* empty_expert = new int[count_ex];
	int t = 0, f = 0, k = 0,l=0;

	for (EXPERT ex : expert) {

		double newvalues;
		double values = 0;
		double sum = 0;

		itoa(ex.Get_code(), ch, 10);
		char name[100] = "Value_Aim";
		strcat(name, ch);
		fstream file = Open_File(name);
		file.seekg(0, ios::end);
		int file_size = file.tellg();
		if (file_size == 0) {
			empty_expert[f] = k;
			f++;
			l++;
			send(c_sock, "1", 100, 0);
			file.close();
		}

		else {
			send(c_sock, "0", 100, 0);
			itoa(ex.Get_code(), str, 10);
			send(c_sock, str, 100, 0);
			file.seekg(0, ios::beg);
			for (int j = 0; j < number_aims; j++) {
				for (int i = 0; i < number_aims; i++) {
					file >> newvalues;
					if (!file.eof()) {
						itoa(newvalues, str, 10);
						send(c_sock, str, 100, 0);
					}
				}
			}
		}
		file.close();
	}
	if (l != count_ex) {
		for (int i = 0; i < number_aims; i++) {
			string str = to_string(end_values[i]);
			send(c_sock, name_aims[i].c_str(), 100, 0);
			send(c_sock, str.c_str(), 100, 0);
		}
	}
}

void My_result(SOCKET c_sock, EXPERT ex) {

	int number_aims = 0;
	string name_aim;
	vector<string> name_aims;
	char str[100];

	fstream file2 = Open_File("Name_Aim");
	file2 >> number_aims;
	file2.clear();
	file2.ignore(100, '\n');
	for (int i = 0; i < number_aims; i++) {
		getline(file2, name_aim, '\n');
		name_aims.push_back(name_aim);
	}
	file2.close();

	itoa(number_aims, str, 10);
	send(c_sock, str, 100, 0);

	double* end_values = new double[number_aims];
	for (int i = 0; i < number_aims; i++) {
		send(c_sock, name_aims[i].c_str(), 100, 0);
	}

	int newvalues;
	char ch[10];

	itoa(ex.Get_code(), ch, 10);
	char name[100] = "Value_Aim";
	strcat(name, ch);

	fstream file = Open_File(name);
	file.seekg(0, ios::end);
	int file_size = file.tellg();

	if (file_size == 0) {
		send(c_sock, "1", 100, 0);
		file.close();
	}

	else {
		send(c_sock, "0", 100, 0);
		itoa(ex.Get_code(), str, 10);
		send(c_sock, str, 100, 0);
		file.seekg(0, ios::beg);
		for (int j = 0; j < number_aims; j++) {
			for (int i = 0; i < number_aims; i++) {
				file >> newvalues;
				if (!file.eof()) {
					itoa(newvalues, str, 10);
					send(c_sock, str, 100, 0);
				}
				else {
					int k = 1;
					send(c_sock, "4", 100, 0);
					send(c_sock, "Значения не заданы", 100, 0);
					break;
				}
			}
		}
		file.close();
	}
}