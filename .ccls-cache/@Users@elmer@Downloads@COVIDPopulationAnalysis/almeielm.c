/**
 * @author Elmer Almeida
 * @date July 27 2021
 *
 * This file handles the implementation of helper functions that generate the
 * population dataset. In addition, delete by record, and read from file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

/**
 * Generate a random number that represents a regions name.
 *
 * @return region number
 */
int generateRegion() {
  // get random number for region
  return rand() % (REGION_RANGE + 1) + REGION_OFFSET;
}

/**
 * Generate a random number that represents a town's name
 *
 * @return town number
 */
int generateTown() {
  // get random number for the town
  return rand() % (TOWN_RANGE + 1) + TOWN_OFFSET;
}

/**
 * Generate a random number that represents a defined race (0 - 4)
 *
 * @return a number representing a race
 */
int generateRace() {
  // get random number for the race
  return rand() % (RACE_RANGE + 1) + RACE_OFFSET;
}

/**
 * Generate a random number to represent a household size between 1 and 20
 *
 * @return household size
 */
int generateHouseholdSize() {
  // get random number for the household size
  return rand() % (HOUSEHOLD_SIZE_RANGE) + HOUSEHOLD_SIZE_OFFSET;
}

/**
 * Generate a random number of senior citizens living in a given household
 *
 * @param household_size
 * @return
 */
int generateSeniors(int household_size) {
  // get a random number for the number of seniors (aged above 50) in the
  // household
  return rand() % household_size + HOUSEHOLD_SIZE_OFFSET;
}

/**
 * Provide the number of people living in the household that are not senior
 * citizens.
 *
 * @param household_size
 * @param seniors
 * @return number of adults
 */
int numberOfAdults(int household_size, int seniors) {
  // get the number of adults (under 50) in the household
  return household_size - seniors;
}

/**
 * Generate a random number of adults (not seniors [over 50]) that have chronic
 * diseases.
 *
 * @param adults
 * @return number of adults who have chronic diseases
 */
int generateAdultsWithChronicDiseases(int adults) {
  // get a random number for adults with chronic diseases in the household. if
  // adults is 0, return 0
  return (adults > 0) ? rand() % adults + HOUSEHOLD_SIZE_OFFSET : 0;
}

/**
 * Generate a random number of people tested for covid based on the number of
 * people living in the household.
 *
 * @param household_size
 * @return number of people tested for covid
 */
int generateTested(int household_size) {
  // get a random number for the number of people tested in the household
  return rand() % household_size + HOUSEHOLD_SIZE_OFFSET;
}

/**
 * Generate a random number of adults tested positive for COVID-19 that is
 * between the number of adults that exists and the number of people tested for
 * covid.
 *
 * @param adults
 * @param tested
 * @return random number of adults tested positive
 */
int generateAdultsTestedPositive(int adults, int tested) {
  int adultsTestedPositive = 0;
  // get a random number for the adults tested positive in the household
  if (adults) {
    // limit on adults
    if (adults < tested)
      adultsTestedPositive = rand() % adults + 1;
    // limit on tested
    else
      adultsTestedPositive = rand() % tested + 1;
  }
  return adultsTestedPositive;
}

/**
 * Generate a household item
 *
 * @return a household item
 */
household generateHousehold() {
  // create new household item -- use the aforementioned methods to create a new
  // household item
  household item;
  item.region = generateRegion();
  item.town = generateTown();
  item.race = generateRace();
  item.size = generateHouseholdSize();
  item.seniors = generateSeniors(item.size);
  item.tested = generateTested(item.size);

  int adults = numberOfAdults(item.size, item.seniors);

  item.adultsWithChronicDiseases = generateAdultsWithChronicDiseases(adults);
  item.adultsTestedPositive = generateAdultsTestedPositive(adults, item.tested);

  // return the newly created household item
  return item;
}

/**
 * Create a specified household with a set of custom (specified) parameters
 *
 * @param region
 * @param town
 * @param race
 * @param size
 * @param seniors
 * @param adultsWithChronicDiseases
 * @param tested
 * @param testedPositive
 * @return a new custom household item
 */
household createHousehold(int region, int town, int race, int size, int seniors,
                          int adultsWithChronicDiseases, int tested,
                          int testedPositive) {
  // manually create a household item based on the specified paramters
  household item;
  item.region = region;
  item.town = town;
  item.race = race;
  item.size = size;
  item.seniors = seniors;
  item.adultsWithChronicDiseases = adultsWithChronicDiseases;
  item.tested = tested;
  item.adultsTestedPositive = testedPositive;
  // return the manually newly created household item
  return item;
}

/**
 * Print the header that showcases what data is in the columns -- this should be
 * called before the loop that goes into printing each household item.
 */
void printHouseholdItemHeader() {
  // header formatting
  printf("---------------------------------------------------------------------"
         "-----------------------------------------------\n");
  printf("%5s\t%7s\t%16s\t%20s\t%20s\t%15s\t%15s\n", "S.no", "Size",
         "Total Tested", "Total Tested Positive", "Race", "Region", "Town");
  printf("---------------------------------------------------------------------"
         "-----------------------------------------------\n");
}

/**
 * Print the household item in its detail entirely
 *
 * @param household item
 */
void printHouseholdItem(int ctr, household item) {
  // print all the household data points in a specified format matching the
  // aforementioned header
  printf("%5d\t%7d\t%16d\t%20d\t%20s\t%15s\t%15s\n", ctr, item.size,
         item.tested, item.adultsTestedPositive, displayRace(item.race),
         displayRegion(item.region), displayTown(item.region, item.town));
}

/**
 * Separator to ensure proper and clean output of data to the console
 */
void printHouseholdItemSeparator() {
  // separator for visual pleasing
  printf("---------------------------------------------------------------------"
         "-----------------------------------------------\n");
}

/**
 * Print a message after the records of the linked list has been displayed
 */
void printHouseholdItemFooter() {
  // disclaimer i guess
  printf("---------------------- This program analyzes and stores information "
         "related to COVID-19 cases ----------------------\n");
  printf("----------------------------- and its impact on various races, "
         "regions and towns of GTA ----------------------------\n");
}

/**
 * Display the race name based on the race number assigned to it.
 *
 * @param race number assigned
 * @return race name
 */
char *displayRace(int race) {
  char *raceName;
  // return the name of the race based on the assigned integer
  switch (race) {
  // African American (0) Asian (1) Caucasian (2) Indigenous (3) Other (4)
  case 0:
    raceName = "African American";
    break;
  case 1:
    raceName = "Asian";
    break;
  case 2:
    raceName = "Caucasian";
    break;
  case 3:
    raceName = "Indigenous";
    break;
  case 4:
    raceName = "Other";
    break;
  default:
    raceName = "Not Specified";
    break;
  }
  // return the race name
  return raceName;
}

/**
 * Display the region name based on the integer value assigned to the region
 *
 * @param region
 * @return the name of the region
 */
char *displayRegion(int region) {
  char *regionName;
  // get the region name based on the integer specified
  switch (region) {
  // Peel (0) York (1) Durham (2)
  case 0:
    regionName = "Peel";
    break;
  case 1:
    regionName = "York";
    break;
  case 2:
    regionName = "Durham";
    break;
  default:
    regionName = "Not Specified";
    break;
  }
  // return the reigon name
  return regionName;
}

/**
 * Get the name of the town based on the region and the town number
 *
 * @param region
 * @param town
 * @return the town's name
 */
char *displayTown(int region, int town) {
  char *townName;
  // return the town name based on the region and town integer specified
  switch (region) {
  // Peel
  case 0:
    switch (town) {
    // Brampton (0) Mississauga (1)
    case 0:
      townName = "Brampton";
      break;
    case 1:
      townName = "Mississauga";
      break;
    default:
      townName = "Invalid";
      break;
    }
    break;
  // York
  case 1:
    switch (town) {
    // Maple (0) Vaughan (1)
    case 0:
      townName = "Maple";
      break;
    case 1:
      townName = "Vaughan";
      break;
    default:
      townName = "Invalid";
      break;
    }
    break;
  // Durham
  case 2:
    switch (town) {
    // Whitby (0) Oshawa (1)
    case 0:
      townName = "Whitby";
      break;
    case 1:
      townName = "Oshawa";
      break;
    default:
      townName = "Invalid";
      break;
    }
    break;
  default:
    townName = "Invalid";
    break;
  }
  return townName;
}

/**
 * Provide the user with a list of options available
 */
void displayMenu() {
  printf("Menu:\n");
  printf("1. display households of a region\n");
  printf("2. display households of a town\n");
  printf("3. display households of a race\n");
  printf("4. display households of a region with a given minimum number of "
         "people tested positive for COVID-19\n");
  printf("5. display the regions town-wise ranking of number of people tested "
         "positive for COVID-19\n");
  printf("6. add a record\n");
  printf("7. delete all records of a region, town and race triplet\n");
  printf("8. display updated data\n");
  printf("9. store data to a file\n");
  printf("10. display data from file\n");
  printf("0. to exit the program\n");
  printf("Your choice: ");
}

/**
 * Display household records by region
 */
void displayHouseholdsByRegion(Node *head) {
  int regionChoice;
  do {
    // get the region choice
    printf("Enter an integer for region: Peel (0) York (1) Durham (2)\n");
    scanf("%d", &regionChoice);
    switch (regionChoice) {
    // 3 regions built in
    case 0:
    case 1:
    case 2:
      printf("Records with region: %s.\n", displayRegion(regionChoice));
      printLinkedListByRegion(head,
                              regionChoice); // print the linked list filtered
                                             // by the region specified
      regionChoice = 9; // make sure to end this do - while outer loop
      break;
    case 9:
      printf("Exiting...\n\n");
      break;
    default:
      printf("Invalid data, Enter an integer 0 through 2 or enter 9 to go back "
             "to the main menu. Try again.\n\n");
      break;
    }
  } while (regionChoice != 9); // only when the regionChoice entered by the user
                               // is 9 does the program exit this loop
}

/**
 * Display household records by town
 */
void displayHouseholdsByTown(Node *head) {
  int regionChoice;
  int townChoice;
  do {
    // get the region from the user
    printf("Enter an integer for region: Peel (0) York (1) Durham (2)\n");
    scanf("%d", &regionChoice);

    switch (regionChoice) {
    // Peel (0) York (1) Durham (2)
    case 0:
      // get the town from the user
      printf("Enter an integer for town: Brampton (0) Mississauga (1)\n");
      scanf("%d", &townChoice);
      // peel region
      switch (townChoice) {
      case 0:
      case 1:
        // print the linked list filtered by the specified region and town
        printf("Records with town: %s.\n",
               displayTown(regionChoice, townChoice));
        printLinkedListByTown(head, regionChoice, townChoice);
        townChoice = 9;
        regionChoice = 9;
        break;
      default:
        printf("Invalid choice. Please try again later.\n\n");
        break;
      }
      break;
    case 1:
      // get the town from the user
      printf("Enter an integer for town: Maple (0) Vaughan (1)\n");
      scanf("%d", &townChoice);
      // york region
      switch (townChoice) {
      // 2 towns for every region
      case 0:
      case 1:
        // print the linked list filtered by the specified region and town
        printf("Records with town: %s.\n",
               displayTown(regionChoice, townChoice));
        printLinkedListByTown(head, regionChoice, townChoice);
        townChoice = 9;
        regionChoice = 9;
        break;
      default:
        printf("Invalid choice. Please try again later.\n\n");
        break;
      }
      break;
    case 2:
      // get the town from the user
      printf("Enter an integer for town: Whitby (0) Oshawa (1)\n");
      scanf("%d", &townChoice);
      // durham region
      switch (townChoice) {
      case 0:
      case 1:
        // print the linked list filtered by the specified region and town
        printf("Records with town: %s.\n",
               displayTown(regionChoice, townChoice));
        printLinkedListByTown(head, regionChoice, townChoice);
        townChoice = 9;
        regionChoice = 9;
        break;
      default:
        printf("Invalid choice. Please try again later.\n\n");
        break;
      }
      break;
    default:
      printf("Invalid option. Please try again later.\n\n");
      break;
    }
  } while (regionChoice != 9 ||
           townChoice != 9); // do - while until the region or town entered is 9
}

/**
 * Display household records by race
 */
void displayHouseholdsByRace(Node *head) {
  int raceChoice;
  do {
    // get the race from the user
    printf("Enter an integer for race: African American (0) Asian (1) "
           "Caucasian (2) Indigenous (3) Other (4)\n");
    scanf("%d", &raceChoice);
    // 0 - 4 acceptable race inputs
    switch (raceChoice) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      // print the linked list filtered by the race
      printLinkedListByRace(head, raceChoice);
      raceChoice = 9;
      break;
    default:
      printf("Invalid entry. Please choose between 0 through 4 or 9 to exit. "
             "Try again.\n");
      break;
    }
  } while (raceChoice != 9); // exit when the race entered is 9
}

/**
 * Display the households by region with a specified minimum of adults tested
 * positive.
 *
 * @param head of the linked list
 */
void displayByRegionMinTestedPositive(Node *head) {
  int regionChoice;
  int minTestedPositive;
  do {
    // get the region from the user
    printf("Enter an integer for region: Peel (0) York (1) Durham (2)\n");
    scanf("%d", &regionChoice);
    switch (regionChoice) {
    case 0:
    case 1:
    case 2:
      printf("Enter minimum number of people tested positive\n");
      scanf(
          "%d",
          &minTestedPositive); // get the minimum adults positive from the user
      printLinkedListByRegionWithMinTestedPositive(
          head, regionChoice,
          minTestedPositive); // print the linked list filtered by the region
                              // and minimum tested positive
      regionChoice = 9;       // ensure that the do - while loop exists
      break;
    default:
      printf("Invalid choice. Enter 0 through 2 or 9 to exit. Try again.\n");
      break;
    }
  } while (regionChoice != 9); // loop until region entered is 9
}

/**
 * Display the region and town ranking based on adults tested positive
 *
 * @param head
 */
void displayRegionAndTownRankingTestedPositive(Node *head) {
  // Regions
  struct rank_cases region[NUM_REGIONS];
  struct rank_cases town[NUM_TOWNS];

  // regions
  printf("Region-wise Ranking:\n");
  rankPositiveTestedBasedOnRegion(head, region); // get the region case data
  sortCaseRanking(region, NUM_REGIONS);          // sort the region cases
  printCaseRanking(region, NUM_REGIONS);         // print the region cases

  // towns
  printf("Town-wise Ranking:\n");
  rankPositiveTestedBasedOnTown(head, town); // get the town case data
  sortCaseRanking(town, NUM_TOWNS);          // sort the town cases
  printCaseRanking(town, NUM_TOWNS);         // print the town cases

  puts("");
}

/**
 * Sort the regions structure by cases in descending order.
 *
 * @param item structure | region or town
 */
void sortCaseRanking(rank_cases *item, int count) {
  int i, j;
  rank_cases temp_item; // cases structure
  // go through the specified number of times (regions 3, towns 6)
  for (i = 0; i < count; i++) {
    for (j = i + 1; j < count; j++) { // start the next loop at the next element
      if (item[i].cases < item[j].cases) {
        temp_item = item[i]; // temp storage for the item that has to be swapped
        item[i] = item[j];   // swap the elements
        item[j] = temp_item; // move the temp stored item to the correct place
      }
    }
  }
}

/**
 * Print the cases to the console
 *
 * @param item | region or town structure
 */
void printCaseRanking(rank_cases *region, int count) {
  int i;
  // loop through the specified number of times and print the cases
  for (i = 0; i < count; i++) {
    printf("%15s : %5d\n", region[i].name, region[i].cases);
  }
}

/**
 * Get region input from the user
 *
 * @return the region choice from the user
 */
int getRegionInput() {
  int regionChoice;
  do {
    // get the region input from the user
    printf("Enter an integer for region: Peel (0) York (1) Durham (2)\n");
    printf("Region: ");
    scanf("%d", &regionChoice);
    // check if valid input
    if (regionChoice < 0 || regionChoice > 2)
      printf("Invalid input. Try again.\n");
  } while (regionChoice < 0 ||
           regionChoice > 2); // keep looping if invalid expectation
  return regionChoice;        // return region entered
}

/**
 * Get the town input from the user depending on the region previously chosen by
 * the user
 *
 * @param region
 * @return the town choice
 */
int getTownInput(int region) {
  int townChoice;
  do {
    // prompt the user for the correct town based on a pre-entered region
    if (region == 0)
      printf("Enter an integer for town: Brampton (0) Mississauga (1)\n");
    else if (region == 1)
      printf("Enter an integer for town: Maple (0) Vaughan (1)\n");
    else if (region == 2)
      printf("Enter an integer for town: Whitby (0) Oshawa (1)\n");
    printf("Town: ");
    // get the town from the user
    scanf("%d", &townChoice);
    // display invalid message if the town entered is invalid
    if (townChoice < 0 || townChoice > 1)
      printf("Invalid input. Try again.\n");
  } while (townChoice < 0 ||
           townChoice > 1); // loop until the town entered is valid
  return townChoice;        // return the town entered
}

/**
 * Get the race choice from the user
 *
 * @return user's input for race
 */
int getRaceInput() {
  int raceInput;
  do {
    // get the race input from the user
    printf("Enter an integer for race: African American (0) Asian (1) "
           "Caucasian (2) Indigenous (3) Other (4)\n");
    printf("Race: ");
    scanf("%d", &raceInput);
  } while (raceInput < 0 ||
           raceInput >
               4); // keep looping until the correct (0 - 4) race is entered
  return raceInput;
}

/**
 * Get household information such as the household size, the number of seniors
 * living in the household and the number of adults (under 50) with chronic
 * diseases living in the household.
 *
 * @param householdSize
 * @param householdSeniors
 * @param householdAdultsWithChronicDiseases
 */
void getHouseholdInformationInput(int *householdSize, int *householdSeniors,
                                  int *householdAdultsWithChronicDiseases) {
  int validInput = 0;
  int size, seniors, adultsWithChronicDiseases;
  do {
    // get the household size, seniors, and adults with chronic diseases from
    // the user
    printf("Please enter\n1 - Total number of people in the household,\n2 - "
           "People over the age of 50,\n3 - People under the age of 50 with "
           "chronic diseases separated by space/tab and make sure all of these "
           "are valid integers\n");
    scanf("%d %d %d", &size, &seniors, &adultsWithChronicDiseases);
    // check to see if the household size is less than the seniors entered, or
    // if the household size if less than the adults with chronic diseases
    // entered or check to see if the seniors + adults with chronic diseases are
    // greater than the household size entered
    if ((seniors + adultsWithChronicDiseases) > size || size < seniors ||
        size < adultsWithChronicDiseases)
      printf("Total people in the household can't be less than the people over "
             "50 or people under 50 with chronic diseases or even their sum. "
             "Kindly re-enter the data.\n");
    // check if the household size is 0 or lower
    else if (size <= 0)
      printf("The household size cannot be zero. Try again.\n");
    // everything is fine
    else
      validInput = 1;
  } while (!validInput); // keep looping until determine a valid input for all 3
                         // (household size, seniors and adults with chronic
                         // diseases)

  // will always be valid input if program reaches here -- pointer so multiple
  // data can be changed
  *householdSize = size;
  *householdSeniors = seniors;
  *householdAdultsWithChronicDiseases = adultsWithChronicDiseases;
}

/**
 * Get the number of people tested and the number of people tested positive in
 * the household from the user
 *
 * @param householdTested
 * @param householdTestedPositive
 */
int getHouseholdCovidInformationInput(int householdSize, int *householdTested,
                                      int *householdTestedPositive) {
  int validInput = 0, tested, testedPositive;
  char continueInput;
  do {
    // get the tested and tested positive in the household from the user
    printf("Enter total number of people in the household who were tested for "
           "COVID-19 and those who were tested positive separated by space or "
           "tab.\n");
    scanf("%d %d", &tested, &testedPositive);
    // check to see if the tested are greater than the household size or if the
    // tested positive is greater than the tested
    if (tested > householdSize || testedPositive > tested) {
      printf("Total people in the household cannot be less than the total "
             "members tested for COVID-19\nSimilarly total tested can't be "
             "less than the total tested positive\nEnter 'Y' if you want to "
             "re-enter/correct household members or\nEnter 'F' if you want to "
             "re-enter only COVID-19 test figures\n");
      // flush input stream
      while (getchar() != '\n')
        ;
      scanf("%c", &continueInput);
      if (continueInput == 'Y') {
        // go back to correct household numbers
        return 0;
      } else if (continueInput == 'F') {
        continue; // continue the program -- will ensure that tested and
                  // positive tested match the conditions set
      }
      // everything is fine
    } else {
      validInput = 1;
    }
  } while (!validInput); // loop until valid input is determined
  // add the data to the pointers
  *householdTested = tested;
  *householdTestedPositive = testedPositive;
  return 1;
}

/**
 * Get all the details to add a record
 *
 * @param head
 * @return new head node of the linked list
 */
Node *addRecord(Node *head) {
  int size, seniors, adultsWithChronicDiseases;
  int response, tested, testedPositive;

  // get the region, town and race  from the user
  int region = getRegionInput();
  int town = getTownInput(region);
  int race = getRaceInput();

  do {
    // get the household information
    getHouseholdInformationInput(&size, &seniors, &adultsWithChronicDiseases);
    // get the household covid information -- if response if 0, household
    // information needs to be updated, if anything else (99.9% sure 1), will
    // continue
    response =
        getHouseholdCovidInformationInput(size, &tested, &testedPositive);
  } while (response == 0);

  // create new household record
  household item =
      createHousehold(region, town, race, size, seniors,
                      adultsWithChronicDiseases, tested, testedPositive);
  // add the record
  addNode(&head, item);
  // print new household item
  printHouseholdItemHeader();
  printHouseholdItem(1, item);
  printHouseholdItemSeparator();

  // return the head of the linked list after the added item
  return head;
}

/**
 * Delete by user specified region town and race combined
 */
Node *deleteByRegionTownRace(Node *head) {
  // get the region, town and race from the user
  int region = getRegionInput();
  int town = getTownInput(region);
  int race = getRaceInput();

  // send the request to delete the household record based on the region, town
  // and race
  deleteLinkedListItem(&head, region, town, race);

  // return the new head of the linkedlist with the deleted items
  return head;
}

/**
 * Read data from file
 */
void readDataFromFile() {
  FILE *file;
  char fileName[25];    // file name to get from the user
  char singleLine[255]; // single line to read from the file

  // flush input stream
  while (getchar() != '\n')
    ;

  // get the filename to read from the user
  printf("Enter the file name with extension, for example, households.txt\n");
  printf("Filename: ");
  fgets(fileName, sizeof(fileName), stdin);
  fileName[strcspn(fileName, "\n")] =
      0; // remove the new line character from the filename

  // open the file in read mode
  file = fopen(fileName, "r");

  // loop until not end of file
  while (!feof(file)) {
    // get the file line and add it to the singleLine
    fgets(singleLine, sizeof(singleLine), file);
    printf("%s", singleLine); // output the single line
  }

  // close file
  fclose(file);
}
