#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct team {
    string name;
    int points;
};



// GetData receives a line of string and convert it into 2 variables type <team>, then these two variables will be added to the teams[][2] array
void GetData(string line, int r, team t[][2]) {
	// declaring the variables needed for this function
	int start = 0;	//the starting location where the program read each character of the string
	int end = 5;	//where the program stop reading the string, I started with 5 because the first 5 characters of the string belong to the name of the winning team.
	int part = 0;   //each string contains 4 data: name of winning team, their points, name of losing team, their points
	string name1;
	string name2;
	string num1;
	string num2;

	while (part <4) {
		// part starts with zero, the function is reading the name of winning team
		while (end < line.length()) {
			//if the charater is not a digit, the string for name1 is not ended
			if (!isdigit(line[end])) {
				end++;
			}
			else {	//if the character is a digit, this means it's time for the next part of the string
				if (part == 0) {	//if part==0, this part of the string is for name1
					name1 = line.substr(start, end-1);	//name1 = the characters from 0 to the one right before the digit
					start = end;	//the start is for part 1, the winning team's points
					end++;
					part++;
				}
				else if (part == 1) {	//part==1, this part is for num1, the winning team's points
					part++;
					if (isdigit(line[end])) {	//some teams have points with 2 digits, some have points with 1 digit
						num1 = line.substr(start, 2);
						end+=2;
						start = end;
						}
					else {
						num1 = line.substr(start, 1);
						end++;
						start = end+1;}
				}
				else if (part == 2) {	//the name of the losing team
					part++;
					name2 = line.substr(start, end-start-1);
					start = end;
					part++;
				}
				else {	//points of losing team
					if (isdigit(line[end])) {
						num2 = line.substr(start,2);
						end++;
						}
					else {
						num2 = line.substr(start,1);
						end++;
					part++;
				}
			}
		}
	}
	}
	//adding data to teams[][2] array
	t[r][0].name = name1;
	t[r][0].points = stoi(num1);
	t[r][1].name = name2;
	t[r][1].points = stoi(num2);
}

//WorstTeam loop through teams[][2] array, make a vector of teams that never win, find the largest number of lost, and print out the teams' names and number of loses
void WorstTeam(team t[][2], int row) {
	vector<string> neverWin;
	int n=1;			//length of the neverWin vector
	bool win = false;
	// loop through the each row of teams array
	for (int i=0; i<row; i++) {
		for (int j=0; j<row; j++) {				//checking if the losing team's name ever appear in the winning team, if their name ever shown in the winning team column, bool win = true
			if (t[j][0].name == t[i][1].name) {
				win = true;
			}
		}
		if (!win) {				//if the losing team's never won, their name is added to the neverWin vector
			neverWin.push_back(t[i][1].name);
			n++;
			win = false;
		} 
		else {win = false;}
	}

	// this part loops through neverWin vector and counts for how many time a name of the team appears in the vector, which is also the number of their loses
	vector<int> NumberofLoses;		//the number of loses of each team
	for (int i=0; i<n; i++) {
		int loses = 0;
		for (int j=0; j<n; j++) {
			if (neverWin[i]==neverWin[j]) {loses++;}
		}
		NumberofLoses.push_back(loses);
		loses = 0;
	}

	//finding the largest number of times a neverWin team lost
	int mostloses = 0;
	for (int i=0; i<n; i++) {
		if (mostloses < NumberofLoses[i]) {mostloses = NumberofLoses[i];};
	}

	//neverWin vector is a list with repeated names, this part loop through neverWin vector, find the teams that have the most loses and their locations in neverWin vector. Their locations are stored in locations vector declared below.
	vector<int> locations;
	int locationsLength = 0;
	bool repeated = false;		//if the name is never repeated in neverWin vector, bool repeated is set to false
	for (int i=0; i<n; i++) {
		if (NumberofLoses[i] >= mostloses) {
			if (!repeated) {		//if name is never repeated, their location is added to locations vector
				locations.push_back(i);
				locationsLength++;}
			if (neverWin[i] == neverWin[locations[locationsLength-1]]) {		//checking if the current row has the same name with the last one
				repeated = true;
				}
			else {repeated = false;}
		}
	}
	cout << "The team(s) that have never won but lost the most super bowls are: <";
	for (int i=0; i<locationsLength; i++) {
		cout << neverWin[locations[i]] << "> <";
	}
	cout << "> they lost " << mostloses << " times." << endl;
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
    int min = 1000;
    
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

//This function calculates the team(s) that won the most times in a row, how many times they won, and prints that information out to the console
void MostInRow(team teams[][2], int row)
{
	//initializing variables needed for the function
	vector<string> BestTeams;
	int bestInRow = 0;
	int currentWins = 1;
	
	//looping throuh the teams.name array. This compares the current team and next team to see if they won multiple times
	for(int i = 0; i < row; i++)
	{
		//if a team won multiple times, it increments the counter
		if(teams[i + 1][0].name == teams[i][0].name)
		{
			currentWins++;
		}
		//if the streak was broken, the counter resets to 1
		else
		{
			currentWins = 1;
		}
		//before the loop ends, if the counter is at it's highest, it will set a variable to save the highest value the counter got to
		if(currentWins > bestInRow)
		{
			bestInRow = currentWins;
		}
	}
	
	//counter is reset so another loop can be started
	currentWins = 1;
	
	//now that the program knows the highest wins in a row for any team, another loop is needed to check every team that won that many times in a row
	for(int i = 0; i < row; i++)
	{
		if(teams[i + 1][0].name == teams[i][0].name)
		{
			currentWins++;
		}
		else
		{
			currentWins = 1;
		}
		//this adds the name of the team(s) that have the highest number of wins in a row to a vector
		if ((currentWins == bestInRow) && (teams[i + 1][0].name == teams[i][0].name))
		{
			BestTeams.push_back(teams[i][0].name);
		}
	}
	
	//printing out the information
	cout << "The team(s) that have won the most amount of times in a row are: ";
	for (int i = 0; i < BestTeams.size(); i++)
	{
		//this condition just checks for duplicate values
		if (BestTeams[i] != BestTeams[i+1])
		{
			cout << "<" << BestTeams[i] << "> ";
		}
	}
	cout << "they won " << bestInRow << " times in a row." << endl;
}


//This function calculates the team(s) that lost the most times in a row, how many times they lost, and prints that information out to the console
void LostInRow(team teams[][2], int row)
{
	//initializing variables needed for the function
	vector<string> WorstTeams;
	int worstInRow = 0;
	int currentLosses = 1;
	
	//looping throuh the teams.name array. This compares the current team and next team to see if they lost multiple times
	for(int i = 0; i < row; i++)
	{
		//if a team lost multiple times, it increments the counter
		if(teams[i + 1][1].name == teams[i][1].name)
		{
			currentLosses++;
		}
		//if the streak was broken, the counter resets to 1
		else
		{
			currentLosses = 1;
		}
		//before the loop ends, if the counter is at it's highest, it will set a variable to save the highest value the counter got to
		if(currentLosses > worstInRow)
		{
			worstInRow = currentLosses;
		}
	}
	
	//counter is reset for a new loop
	currentLosses = 1;
	
	//now that the program knows the highest losses in a row for any team, another loop is needed to check every team that lost that many times in a row
	for(int i = 0; i < row; i++)
	{
		if(teams[i + 1][1].name == teams[i][1].name)
		{
			currentLosses++;
		}
		else
		{
			currentLosses = 1;
		}
		//this adds the name of the team(s) that have the losses number of wins in a row to a vector
		if ((currentLosses == worstInRow) && (teams[i + 1][1].name == teams[i][1].name))
		{
			WorstTeams.push_back(teams[i][1].name);
		}
	}
	
	//printing out the information
	cout << "The team(s) that have lost the most times in a row are: ";
	for (int i = 0; i < WorstTeams.size(); i++)
	{
		//this condition just checks for duplicate values
		if (WorstTeams[i] != WorstTeams[i+1])
		{
			cout << "<" << WorstTeams[i] << "> ";
		}
	}
	cout << "they lost " << worstInRow << " times in a row.";
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
			GetData(tp, rows, teams);
			rows++;
	}
	newfile.close(); //close the file object.
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
    WorstTeam(teams, rows); 
	MostInRow(teams, rows);
    LostInRow(teams, rows);

}
