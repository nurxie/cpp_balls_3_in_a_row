#include<iostream>
#include<string>
#include<ctime>

using namespace std;
const int  x_define = 4;  //4   //8
const int  y_define = 3;  //3   //8
int score = 0;


string del_repeat(string line, int& curr_pos, char templ)
{
	while (curr_pos < line.size() && line[curr_pos] == templ)
	{
		line = line.replace(curr_pos, 1, "*");
		curr_pos++;
	}

	return line;
}

string check_repeat(string line)
{
	string line_new = "";
	int curr_pos = 0;
	//while (curr_pos < line.size() - 2)
	while (curr_pos + 2 < line.size())
	{
		if (line[curr_pos] == line[curr_pos + 1] && line[curr_pos] == line[curr_pos + 2])
		{
			line = del_repeat(line, curr_pos, line[curr_pos]);
			score++;
		}
		else
		{
			curr_pos++;
		}
	}

	return line;
}

void gravitation(char answer[][x_define]) {
	for (int countner_of_faling = y_define - 1; countner_of_faling > 0; countner_of_faling--) {
		for (int y = y_define; y > 0; y--) {
			for (int x = 0; x < x_define; x++) {
				if (answer[y][x] == '*') {
					bool enable = true;
					int countner = 0;
					while (enable == true) {
						if ((y - countner - 1) >= 0) {
							answer[y - countner][x] = answer[y - countner - 1][x];
							answer[y - countner - 1][x] = '*';
							countner++;
						}
						else {
							enable = false;
						}
					}
				}
			}
		}
	}
}

bool delete_string(char mass[][x_define], char mass_after_string_search[][x_define]) {
	bool buff = false;
	string buffer = "";

	//cout << "to chto vidit funkziya po strokam" << endl;
	for (int y = 0; y < y_define; y++) {
		for (int x = 0; x < x_define; x++) {
			buffer = buffer + mass[y][x];
		}
		//cout << stroka << endl;
		buffer = check_repeat(buffer);
		for (int x = 0; x < x_define; x++) {
			mass_after_string_search[y][x] = buffer[x];
		}
		if (buffer[y] == '*') {
			buff = true;
		}
		buffer.clear();
	}
	//cout << "" << endl;
	return buff;
}

bool delete_column(char mass[][x_define], char mass_after_column_search[][x_define]) { //mass_after_column_search
	string buffer = "";
	bool buff = false;

	//cout << "to chto vidit funkziya po stolbikam" << endl;
	for (int x = 0; x < x_define; x++) {
		for (int y = 0; y < y_define; y++) {
			buffer = buffer + mass[y][x];
		}
		//cout << stolbik << endl;
		buffer = check_repeat(buffer);
		for (int y = 0; y < y_define; y++) {
			mass_after_column_search[y][x] = buffer[y];
		}
		if (buffer[x] == '*') {
			buff = true;
		}
		buffer.clear();
	}
	return buff;
}

void comparison(char mass[][x_define], char mass_after_string_search[][x_define], char mass_after_column_search[][x_define]) {
	for (int x = 0; x < x_define; x++) {
		for (int y = 0; y < y_define; y++) {
			if ((mass_after_column_search[y][x] != mass_after_string_search[y][x]) || ((mass_after_string_search[y][x] == '*') && (mass_after_column_search[y][x] == '*'))) {
				mass[y][x] = '*';
			}
		}
	}
	//cout << "" << endl;
}

bool filling(char answer[][x_define]) {
	bool edit = false;
	for (int x = 0; x < x_define; x++) {
		for (int y = 0; y < y_define; y++) {
			if (answer[y][x] == '*') {
				answer[y][x] = (rand() % 8 + 1) + '0'; //ot 1 do 9  
				edit = true;
			}
		}
	}
	return edit;
}

void swap(int y1, int x1, int y2, int x2, char mass[][x_define]) {
	char buff = ' ';
	buff = mass[y1 - 1][x1 - 1];
	mass[y1 - 1][x1 - 1] = mass[y2 - 1][x2 - 1];
	mass[y2 - 1][x2 - 1] = buff;
}

bool gamecore(char mass[][x_define], char mass_after_string_search[][x_define], char mass_after_column_search[][x_define]) {
	delete_string(mass, mass_after_string_search);
	delete_column(mass, mass_after_column_search);
	comparison(mass, mass_after_string_search, mass_after_column_search);
	gravitation(mass);
	return filling(mass);
}

bool findcomdinations(char mass[][x_define]) {
	char duplicate[y_define][x_define];
	char mass_after_string_search[y_define][x_define];
	char mass_after_column_search[y_define][x_define];
	bool boolbuffstring = false;
	bool boolbuffcolumn = false;
	for (int x = 0; x < x_define; x++) {
		for (int y = 0; y < y_define; y++) {
			duplicate[y][x] = mass[y][x];
		}
	}
	for (int x = 1; x <= x_define; x++) {
		for (int y = 1; y <= y_define; y++) {
			if (y + 1 <= y_define) {
				swap(y, x, y + 1, x, duplicate);
				boolbuffstring = delete_string(duplicate, mass_after_string_search);
				boolbuffcolumn = delete_column(duplicate, mass_after_column_search);
			}
			if (boolbuffstring == true || boolbuffcolumn == true) {
				return true;
			}
			else {
				if (y + 1 <= y_define)
					swap(y + 1, x, y, x, duplicate);
			}
		}
	}
	for (int y = 1; y <= y_define; y++) {
		for (int x = 1; x <= x_define; x++) {
			if (x + 1 <= x_define) {
				swap(y, x, y, x + 1, duplicate);
				boolbuffstring = delete_string(duplicate, mass_after_string_search);
				boolbuffcolumn = delete_column(duplicate, mass_after_column_search);
			}
			if (boolbuffstring == true || boolbuffcolumn == true) {
				return true;
			}
			else {
				if (x + 1 <= x_define)
					swap(y, x + 1, y, x, duplicate);
			}
		}
	}
	return false;
}

bool magicshake(char mass[][x_define]) {
	int end = (rand() % 99 + 1);
	while (1) {
		int x1 = (rand() % (x_define - 1) + 1); //ot 1 do x_def
		int y1 = (rand() % (y_define - 1) + 1); //ot 1 do y_def
		int x2 = (rand() % (x_define - 1) + 1); //ot 1 do x_def
		int y2 = (rand() % (y_define - 1) + 1); //ot 1 do y_def
		swap(y1, x1, y2, x2, mass);
		end--;
		if (end == 0) {
			break;
		}
	}
	return 1;
}

bool end_of_the_game() {
	char answer;
	cout << "YOU LOSE!" << endl << "SCORE: " << score << endl;
	cout << "DO YOU WANT TO START THE GAME?" << endl << "YES - y    NO - n (press any key)" << endl;
	cin >> answer;

	if (answer == 'y')
	{
		return 1;
	}
	else {
		return 0;
	}
}

void cout_mass(char mass[][x_define]) {
	string buffer = "";
	for (int y = 0; y < y_define; y++) {
		for (int x = 0; x < x_define; x++) {
			buffer = buffer + mass[y][x];
		}
		cout << buffer << endl;
		buffer.clear();
	}
}

int main(int argc, char* argv[])
{
	cout << "============================================" << endl;
	char mass[y_define][x_define] = { {'*', '*', '*', '*'},
										{'*', '*', '*', '*'},
										{'*', '*', '*', '*'} };
	char mass_after_string_search[y_define][x_define];
	char mass_after_column_search[y_define][x_define];
	string buffer = "";
	srand(time(0)); // generate random time of work the pc
	int y1, x1, y2, x2;
	filling(mass);
	bool i = false;
	do {
		i = gamecore(mass, mass_after_string_search, mass_after_column_search);
	} while (i);
	if (!findcomdinations(mass)) {
		int countner = 0;
		do {
			magicshake(mass);
			do {
				if (!gamecore(mass, mass_after_string_search, mass_after_column_search)) break;
			} while (1);
			countner++;
			if (countner == 100) {
				if (end_of_the_game())
				{
					score = 0;
				}
				else {
					return 0;
				}
			}
		} while (!findcomdinations(mass));
	}
	cout_mass(mass);
	while (1) {
		cout << endl;
		cout << score << ":Score" << endl;
		cout << "it was not automatically possible to remove the balls, please enter the coordinates for the swap 1 -  y x   2 -  y x" << endl;
		cout << "1 - ";
		cin >> y1 >> x1;
		cout << "2 - ";
		cin >> y2 >> x2;

		if ((y1 > 0 && y1 <= y_define && x1 > 0 && x1 <= x_define && y2 > 0 && y2 <= y_define && x2 > 0 && x2 <= x_define) && (x1 == x2 || y1 == y2)) {
			if (abs(y1 - y2) <= 1 && abs(x1 - x2) <= 1) {
				swap(y1, x1, y2, x2, mass);
			}
			else {
				if (end_of_the_game())
				{
					score = 0;
				}
				else {
					return 0;
				}
			}
		}
		else {
			if (end_of_the_game())
			{
				score = 0;
			}
			else {
				return 0;
			}
		}
		if (!gamecore(mass, mass_after_string_search, mass_after_column_search)) {
			swap(y2, x2, y1, x1, mass); score--;
		}
		if (!findcomdinations(mass)) {
			int countner = 0;
			do {
				magicshake(mass);
				do {
					if (!gamecore(mass, mass_after_string_search, mass_after_column_search)) break;
				} while (1);
				countner++;
				if (countner == 100) {
					if (end_of_the_game())
					{
						score = 0;
						break;
					}
					else {
						return 0;
					}
				}
			} while (!findcomdinations(mass));
		}
		cout_mass(mass);
	}
	return 0;
}
