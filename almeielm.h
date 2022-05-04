/**
 * @author Elmer Almeida
 * @date July 27 2021
 *
 * This file handles the blueprint for generating the population and other methods required.
 */

#ifndef ELMERALMEIDAASSIGN3_ALMEIELM_H
#define ELMERALMEIDAASSIGN3_ALMEIELM_H

#define NUM_REGIONS 3
#define NUM_TOWNS 6

#define REGION_RANGE 2
#define REGION_OFFSET 0

#define TOWN_RANGE 1
#define TOWN_OFFSET 0

#define RACE_RANGE 4
#define RACE_OFFSET 0

#define HOUSEHOLD_SIZE_RANGE 20
#define HOUSEHOLD_SIZE_OFFSET 1

typedef struct Household {
    int region;
    int town;
    int race;
    int size;
    int seniors;
    int adultsWithChronicDiseases;
    int tested;
    int adultsTestedPositive;
} household;

typedef struct node {
    household item;
    struct node *next;
} Node, *NodePtr;

typedef struct rank_cases {
    char *name;
    int cases;
} rank_cases;

int generateRegion();
int generateTown();
int generateRace();
int generateHouseholdSize();
int generateSeniors(int household_size);
int numberOfAdults(int household_size, int seniors);
int generateAdultsWithChronicDiseases(int adults);
int generateTested(int household_size);
int generateAdultsTestedPositive(int adults, int tested);

char* displayRegion(int region);
char* displayTown(int region, int town);
char* displayRace(int race);

household generateHousehold();
household createHousehold(int region, int town, int race, int size, int seniors, int adultsWithChronicDiseases, int tested, int testedPositive);
void printHouseholdItemHeader();
void printHouseholdItem(int ctr, household household);
void printHouseholdItemSeparator();
void printHouseholdItemFooter();

void displayMenu();
void displayHouseholdsByRegion(Node *head);
void displayHouseholdsByTown(Node *head);
void displayHouseholdsByRace(Node *head);
void displayByRegionMinTestedPositive(Node *head);

void displayRegionAndTownRankingTestedPositive(Node *head);
void sortCaseRanking(rank_cases *item, int count);
void printCaseRanking(rank_cases *item, int count);

Node* addRecord(Node *head);

int getRegionInput();
int getTownInput(int region);
int getRaceInput();
void getHouseholdInformationInput(int *size, int *seniors, int *adultsWithChronicDiseases);
int getHouseholdCovidInformationInput(int size, int *tested, int *testedPositive);

Node* deleteByRegionTownRace(Node *head);

void readDataFromFile();

#endif //ELMERALMEIDAASSIGN3_ALMEIELM_H
