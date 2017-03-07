#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <vector>

int times[] = {107,47,102,64,50,100,28,91,27,5,22,114,23,42,13,3,93,8,92,79,53,83,63,7,15,66,105,57,14,65,58,113,112,1,62,103,120,72,111,51,9,36,119,99,30,20,25,84,16,116,98,18,37,108,10,80,101,35,75,39,109,17,38,117,60,46,85,31,41,12,29,26,74,77,21,4,70,61,88,44,49,94,122,2,97,73,69,71,86,45,96,104,89,68,40,6,87,115,54,123,125,90,32,118,52,11,33,106,95,76,19,82,56,121,55,34,24,43,124,81,48,110,78,67,59};
int numHorses;

class Horse {
	public:
		int horseNumber;
		int timer;
		std::vector<Horse*> fasterThan;
		std::vector<Horse*> slowerThan;
};

void race(Horse* seg[], int len);
void printHorses(Horse* horseList[], int len);

int main () {
	numHorses = sizeof(times)/sizeof(*times);
	Horse horses[numHorses];
	Horse* horseList[numHorses];
	for (int i = 0; i < numHorses; i++) {
		horses[i].horseNumber = i;
		horses[i].timer = times[i];
		horseList[i] = &horses[i];
	}

	Horse* raceHorses[5] = {horseList[0], horseList[1], horseList[2], horseList[3], horseList[4]};
	printHorses(raceHorses, 5);
	race(raceHorses, 5);
	printHorses(raceHorses, 5);
	return 0;
}

void race(Horse* seg[], int len) {
	bool swappedAny;
	do {
		swappedAny = false;
		for(int i = 0; i < len-1; i++) {
			if (seg[i+1]->timer < seg[i]->timer) {
				swappedAny = true;
				Horse* tempHorse = seg[i];
				seg[i] = seg[i+1];
				seg[i+1] = tempHorse;
				seg[i+1]->fasterThan.push_back(seg[i]);
				seg[i]->slowerThan.push_back(seg[i+1]);
			} else if (seg[i]->timer < seg[i+1]->timer) {
				seg[i]->fasterThan.push_back(seg[i+1]);
				seg[i+1]->slowerThan.push_back(seg[i]);
			}
		}
	} while(swappedAny);
}

void printHorses(Horse* horseList[], int len) {
	for(int i = 0; i < len; i++) {
		printf("%d ", horseList[i]->timer);
	}
	printf("\n");
}