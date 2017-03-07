#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <vector>
#include <algorithm>

int times[] = {107,47,102,64,50,100,28,91,27,5,22,114,23,42,13,3,93,8,92,79,53,83,63,7,15,66,105,57,14,65,58,113,112,1,62,103,120,72,111,51,9,36,119,99,30,20,25,84,16,116,98,18,37,108,10,80,101,35,75,39,109,17,38,117,60,46,85,31,41,12,29,26,74,77,21,4,70,61,88,44,49,94,122,2,97,73,69,71,86,45,96,104,89,68,40,6,87,115,54,123,125,90,32,118,52,11,33,106,95,76,19,82,56,121,55,34,24,43,124,81,48,110,78,67,59};
int numHorses;

class Horse {
	public:
		int horseNumber;
		int timer;
		std::vector<Horse*> fasterThan;
		std::vector<Horse*> slowerThan;
		int simpleAntiUsefulness() {return fasterThan.size()+slowerThan.size();}
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

	int numRaces = 0;
	while(true){
		//reset
		Horse* raceHorses[5] = {NULL, NULL, NULL, NULL, NULL};

		//find horces to race (simply by looking at how much is still unknown to each horse individually, needs to be changed to look at how much is unknown/can be gained for any set of horses)
		for(int i = 0; i < 5; i++) {
			for (int j = 0; j < numHorses; j++) {
				bool inArray = false;
				for(int k = 0; k < i; k++) {
					if (raceHorses[k] == horseList[j]) {
						inArray = true;
						break;
					}
				}

				if(!inArray&& horseList[j]->simpleAntiUsefulness() < numHorses-1 && 
					(raceHorses[i] == NULL || horseList[j]->simpleAntiUsefulness() < raceHorses[i]->simpleAntiUsefulness())) {
					raceHorses[i] = horseList[j];
				}
			}
		}

		//calc num of race horses
		int length = 5;
		for (int i = 0; i < 5;i++) {
			if (raceHorses[i] == NULL) length--;
		}
		//end if no horses to race
		if (length == 0) break;

		//race horses
		printHorses(raceHorses, length);
		race(raceHorses, length);
		printHorses(raceHorses, length);

		//extend analysis, doesn't actually improve anything
		// for(int j = 0; j < numHorses; j++) {
		// 	bool wasRaced = false;
		// 	for(int i = 0; i < 5; i++) {
		// 		if(horseList[j] == raceHorses[i]) wasRaced = true;
		// 	}
		// 	if(wasRaced) continue;

		// 	for(int i = 0; i < 5; i++) {
		// 		if(std::find(horseList[j]->fasterThan.begin(), horseList[j]->fasterThan.end(), raceHorses[i]) != horseList[j]->fasterThan.end()) {
		// 			for(Horse* slowerHorse : horseList[j]->fasterThan) {
		// 				if (std::find(horseList[j]->fasterThan.begin(), horseList[j]->fasterThan.end(), slowerHorse) == horseList[j]->fasterThan.end()) {
		// 					horseList[j]->fasterThan.push_back(slowerHorse);
		// 				}
		// 			}
		// 		} else if (std::find(horseList[j]->slowerThan.begin(), horseList[j]->slowerThan.end(), raceHorses[i]) != horseList[j]->slowerThan.end()) {
		// 			for(Horse* fasterHorse : horseList[j]->slowerThan) {
		// 				if(std::find(horseList[j]->slowerThan.begin(), horseList[j]->slowerThan.end(), fasterHorse) == horseList[j]->slowerThan.end()) {
		// 					horseList[j]->slowerThan.push_back(fasterHorse);
		// 				}
		// 			}
		// 		}
		// 	}
		// }

		numRaces++;
	}
	printf("Number of races = %d\n [", numRaces);

	int min = 0;
	for(int i = 0; i < numHorses; i++) {
		int max = 999;
		int index;
		for(int j = 0; j < numHorses; j++) {
			if (horseList[j]->slowerThan.size() < max && horseList[j]->slowerThan.size() > min) {
				max = horseList[j]->slowerThan.size();
				index = j;
			}
		}
		min = max;
		printf(i==0? "%d" : ", %d", horseList[index]->slowerThan.size());
	}
	printf("]\n");
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
		if (horseList[i] != NULL)
			printf("%d ", horseList[i]->timer);
	}
	printf("\n");
}