#include <iostream>
#include <fstream> //
#include <sstream> //
#include <cstdio>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <unistd.h> //

using namespace std;

struct Entry
{
    string name;
    int score;
};

vector<Entry> highscore;

bool vergleichscore(const Entry &a, const Entry &b)
{
    return a.score > b.score;
}
void addscore(string name, int score)
{
    Entry neuscore;
    neuscore.name = name;
    neuscore.score = score;
    // read current highscores from the file
    ifstream myfile("C:/Users/Studierende/Documents/C++ Projects/pg1_Praktikum4/Praktikum4Aufgabe13/Praktikum4Aufgabe13/highscore.txt");
    if (myfile.is_open())
    {
        string line;
        while (getline(myfile, line))
        {
            istringstream iss(line);
            string name;
            int score;
            iss >> name >> score;
            Entry entry;
            entry.name = name;
            entry.score = score;
            highscore.push_back(entry);
        }
        myfile.close();
    }
    else
    {
        cout << " Unable to open file " << endl;
    }
    // add new score
    highscore.push_back(neuscore);
    // sort highscores
    sort(highscore.begin(),highscore.end(),vergleichscore);
    // write sorted highscores to the file
    ofstream myoutfile("C:/Users/Studierende/Documents/C++ Projects/pg1_Praktikum4/Praktikum4Aufgabe13/Praktikum4Aufgabe13/highscore.txt",ios::out);
    if(myoutfile.is_open())
    {
            for (int i=0; i<highscore.size();i++)
            {
                myoutfile << highscore.at(i).name << " " << highscore.at(i).score << endl;
            }
            myoutfile.close();
    }
    else
    {
        cout << " Unable to open file " << endl;
    }
    /*Entry neuscore;
    neuscore.name = name;
    neuscore.score = score;
    highscore.push_back(neuscore);
    sort(highscore.begin(),highscore.end(),vergleichscore);
    ofstream myfile("C:/Users/Studierende/Documents/C++ Projects/pg1_Praktikum4/Praktikum4Aufgabe13/Praktikum4Aufgabe13/highscore.txt",ios::app);
    if(myfile.is_open())
    {
            for (int i=0; i<highscore.size();i++)
            {
                myfile << highscore.at(i).name << " " << highscore.at(i).score << endl;
            }
            myfile.close();
    }
    else
    {
        cout << " Unable to open file " << endl;
    }*/
}

void Highscoreanzeigen()
{
    for (int i=0; i<highscore.size();i++)
    {
        cout << "(" << (i+1) << ") " << highscore.at(i).name << " mit " << highscore.at(i).score << " Punkten" << endl;
    }

    string name;
    int score;
    ifstream myfile(("C:/Users/Studierende/Documents/C++ Projects/pg1_Praktikum4/Praktikum4Aufgabe13/Praktikum4Aufgabe13/highscore.txt"));
    if(myfile.is_open())
    {
        while(getline(myfile,name))
        {
            cout << name << endl;
        }
    }
    myfile.close();

}
/*void savehighscore(){
    ofstream myfile;
    myfile.open ("highscore.txt");
    for (size_t i=0; i<highscore.size();i++)
    {
        myfile << highscore.at(i).name << " " << highscore.at(i).score << endl;
    }
    myfile.close();
}*/

/*void loadhighscore(){
    string name;
    int score;
    ifstream myfile;
    myfile.open ("highscore.txt");
    while (myfile >> name >> score)
    {
        addscore(name, score);
    }
    myfile.close();
}*/

