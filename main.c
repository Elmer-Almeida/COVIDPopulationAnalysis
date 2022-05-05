/**
 * @author Elmer Almeida
 * @date July 27 2021
 *
 * This file handles program lifecycle.
 *
 * The main objective of the program will be to generate population data, and
 * store it in a linked list. The ability to store data into a file and read
 * from a file will also be available.
 */

#include <stdio.h>

#include "almeielm.h"
#include "linkedlist.h"

#define HOUSEHOLD_LIMIT 100

int main() {
  int userChoice;                           // user choice for menu
  household itemHead = generateHousehold(); // create first household item
  Node *head = makeNode(itemHead); // add the first created household to the
                                   // head of the linked list

  // add randomized data to the linked list
  for (int household_ctr = 1; household_ctr < HOUSEHOLD_LIMIT;
       household_ctr++) {
    // generate a new household with randomized data
    household item = generateHousehold();
    // add the new randomized data household to the linked list
    addNode(&head, item);
  }

  // print linked list data
  printLinkedList(head);

  do {
    // display menu for user choice
    displayMenu();

    // get user input
    scanf("%d", &userChoice);

    switch (userChoice) {
    case 0:
      break;
    case 1:
      // display households by a region
      displayHouseholdsByRegion(head);
      break;
    case 2:
      // display households of a town
      displayHouseholdsByTown(head);
      break;
    case 3:
      // display households of a race
      displayHouseholdsByRace(head);
      break;
    case 4:
      // display households of a region with a given minimum number of people
      // tested positive for COVID-19
      displayByRegionMinTestedPositive(head);
      break;
    case 5:
      // display the regions town-wise ranking of number of people tested
      // positive for COVID-19
      printf("\nTested Positive for COVID-19 cases:\n");
      displayRegionAndTownRankingTestedPositive(head);
      break;
    case 6:
      // add a record
      head = addRecord(head);
      break;
    case 7:
      // delete all records of a region, town and race triplet
      head = deleteByRegionTownRace(head);
      printLinkedList(head);
      break;
    case 8:
      // display updated data
      printLinkedList(head);
      break;
    case 9:
      // store data to a file
      storeDataToFile(head);
      break;
    case 10:
      // display data fromm a file
      readDataFromFile();
      break;
    default:
      printf("Please enter a valid option.\n\n");
      break;
    }
  } while (userChoice); // keep looping until the user enters '0'

  // goodbye
  if (!userChoice)
    printf("\nGoodbye! Have a nice day.\n");
}
