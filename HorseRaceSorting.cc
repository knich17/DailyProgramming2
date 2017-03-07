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

		//find first horce to race
		for (int j = 0; j < numHorses; j++) {
			if(horseList[j]->simpleAntiUsefulness() < numHorses-1 && 
				(raceHorses[0] == NULL || horseList[j]->simpleAntiUsefulness() < raceHorses[0]->simpleAntiUsefulness())) {
				raceHorses[0] = horseList[j];
			}
		}

		//find remaining horces to race
		for (int i = 1; i < 5; i++) { //for the final 4 horses
			int usefulness= 0;
			for (int j = 0; j < numHorses; j++) {	//for every horse
				int tempUsefulness= 0;
				bool inArray = false;
				for(int k = 0; k < i; k++) {	//for every horse already selected to race
					if (raceHorses[k] == horseList[j]) {
						inArray = true;
						break;
						
					} else if (raceHorses[k] != NULL) {
						if (raceHorses[k]->fasterThan.empty() || std::find(raceHorses[k]->fasterThan.begin(), raceHorses[k]->fasterThan.end(), horseList[j]) == raceHorses[k]->fasterThan.end()) 
							tempUsefulness++;
						if (raceHorses[k]->slowerThan.empty() || std::find(raceHorses[k]->slowerThan.begin(), raceHorses[k]->slowerThan.end(), horseList[j]) == raceHorses[k]->slowerThan.end()) 
							tempUsefulness++;
					}
				}
				if(!inArray && tempUsefulness > 0 &&
					(raceHorses[i] == NULL || tempUsefulness > usefulness)) {
					usefulness = tempUsefulness;
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

		//printf("\n");
		printHorses(raceHorses, length);
		// for (int i = 0; i < 5; i++) {
		// 	printf("i=%d, timer=%d\n fasterThan:", i, raceHorses[i]->timer);
		// 	for(Horse* h : raceHorses[i]->fasterThan) {
		// 		printf(" %d", h->timer);
		// 	}
		// 	printf("\nSlowerThan:");
		// 	for(Horse* h : raceHorses[i]->slowerThan) {
		// 		printf(" %d", h->timer);
		// 	}
		// 	printf("\n\n");
		// }
		race(raceHorses, length);
		//printHorses(raceHorses, length);

		// extend analysis, doesn't actually improve anything
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
			}

		}
	} while(swappedAny);

	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			if (j == i) continue;
			if (i < j) {
				if (seg[i]->fasterThan.empty() || std::find(seg[i]->fasterThan.begin(), seg[i]->fasterThan.end(), seg[j]) == seg[i]->fasterThan.end())
				seg[i]->fasterThan.push_back(seg[j]);
				if (seg[j]->slowerThan.empty() || std::find(seg[j]->slowerThan.begin(), seg[j]->slowerThan.end(), seg[i]) == seg[j]->slowerThan.end())
				seg[j]->slowerThan.push_back(seg[i]);
			} else {
				if (seg[j]->fasterThan.empty() || std::find(seg[j]->fasterThan.begin(), seg[j]->fasterThan.end(), seg[i]) == seg[j]->fasterThan.end())
				seg[j]->fasterThan.push_back(seg[i]);
				if (seg[i]->slowerThan.empty() || std::find(seg[i]->slowerThan.begin(), seg[i]->slowerThan.end(), seg[j]) == seg[i]->slowerThan.end())
				seg[i]->slowerThan.push_back(seg[j]);
			}
		}
	}
}

void printHorses(Horse* horseList[], int len) {
	for(int i = 0; i < len; i++) {
		if (horseList[i] != NULL)
			printf("%d ", horseList[i]->timer);
	}
	printf("\n");
}