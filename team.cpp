#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct team {
    string name;
    int points;
};


bool isNumber(char a)
{

    // if (isdigit(a) == 0) return false;
    // return true;
	return isdigit(a);
}

void getdata(string line, int c, team teams[][2]) {

	int start = 0;
	int big_count = 0;
	int end = 5;
	string name1;
	string name2;
	string num1;
	string num2;

	while (big_count <4) {
		while (end < line.length()) {
			if (!isNumber(line[end])) {
				end++;
			}
			else {
				if (big_count == 0) {
					name1 = line.substr(start, end-1);
					start = end;
					end++;
					big_count++;
				}
				else if (big_count == 1) {
					big_count++;
					if (isNumber(line[end])) {
						num1 = line.substr(start, 2);
						end+=2;
						start = end;
						}
					else {
						num1 = line.substr(start, 1);
						end++;
						start = end+1;}
				}
				else if (big_count == 2) {
					big_count++;
					name2 = line.substr(start, end-start-1);
					// end++;;
					start = end;
					big_count++;
				}
				else {
					if (isNumber(line[end])) {
						num2 = line.substr(start,2);
						end++;
						}
					else {
						num2 = line.substr(start,1);
						end++;
					big_count++;
				}
			}
		}
	}
	}
// 	return {name1, num1, name2, num2};
    // cout << name1 << ".." << num1 << ".." << name2 << ".." << num2 << ".." << endl;
	teams[c][0].name = name1;
	teams[c][0].points = stoi(num1);
	teams[c][1].name = name2;
	teams[c][1].points = stoi(num2);
}

int main(){
	team teams[99][2];
	int rows = 0;
    fstream newfile;
    newfile.open("SuperBowl.txt",ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){ //checking whether the file is open
        string tp;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            // cout << tp << "\n"; //print the data of the string
			getdata(tp, rows, teams);
			rows++;
        }
        newfile.close(); //close the file object.
    }
    for (int r=0;r<rows;r++) {
    	for (int c=0;c<2;c++) {
    		cout << teams[r][c].name << ":" << teams[r][c].points << "...";
    	}
		cout << endl;
}
}
