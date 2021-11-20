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

double winnersaverage(team winners_scores[99][2], int rows)
{
    double total = 0;
    double counter = 0;
    
    for(int i = 0; i < rows; i++)
    {
        total = total + winners_scores[i][0].points;
        counter++;
        
    }
    
    double average;
    average = total / counter;
    return average;

}

double losersaverage(team losers_scores[99][2], int rows)
{
    double total = 0;
    double counter = 0;
    
    for(int i = 0; i < rows; i++)
    {
        total = total + losers_scores[i][1].points;
        counter++;
        
    }
    
    double average;
    average = total / counter;
    return average;
}

double maxscore(team team[99][2], int rows)
{
    int max = 0;
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(team[i][j].points > max)
            {
                max = team[i][j].points;
            }
        }
    }
    
    return max;

}

double minscore(team team[99][2], int rows)
{
    int min = 10000000000000;
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(team[i][j].points < min)
            {
                min = team[i][j].points;
            }
        }
    }
    
    return min;

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

    double result = winnersaverage(teams, rows);
    double result2 = losersaverage(teams, rows);
    double result3 = maxscore(teams, rows);
    double result4 = minscore(teams, rows);
    
    
    cout << "First Super Bowl Winner: " << teams[0][0].name << ", Score: " << teams[0][0].points << endl;
    cout << "Most recent Super Bowl Winner: " << teams[0][rows].name << ", Score: " << teams[0][rows].points << endl;
    cout << "Maximum score of any super bowl team: " << result3 << endl;
    cout << "Minimum score of any super bowl team: " << result4 << endl;
    cout << "Average winning score from Super Bowl teams: " << result << endl;
    cout << "Average losing score from Super Bowl teams: " << result2 << endl;


}
