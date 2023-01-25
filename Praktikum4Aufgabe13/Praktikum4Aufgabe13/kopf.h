#ifndef KOPF_H
#define KOPF_H

#endif // KOPF_H

#include<iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

struct Entry;
bool vergleichscore(const Entry &a, const Entry &b);
void addscore(string name, int score);
void Highscoreanzeigen();
