/**
 * @author Elmer Almeida
 * @date July 27 2021
 *
 * This file handles the implementation of linked list associated methods
 * defined in linkedlist.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

/**
 * Method to create a first node of the linked list
 *
 * @param num to add to the node of the linked list first element
 * @return the first linked list node created
 */
Node *makeNode(household item) {
  Node *ptr = malloc(sizeof(*ptr)); // allocate memory
  ptr->item = item;                 // add the household item to the linked list
  ptr->next = NULL;                 // make sure its the head of the list
  return ptr;
}

/**
 * Method to add a node to the front of the linked list.
 *
 * @param top node reference of the linked list
 * @param num value to add to the node
 */
void addNode(NodePtr *head, household item) {
  NodePtr ptr =
      malloc(sizeof(*ptr)); // allocate space for the new linked list node
  ptr->item = item;    // add the new household information to the linked list
  ptr->next = (*head); // the new node will be the new head, ensure the
                       // connection to the previous head
  (*head) = ptr;       // new node to head
}

/**
 * Print linked list values
 *
 * @param the first node of the linked list to traverse through
 */
void printLinkedList(Node *head) {
  Node *ptr = head;
  int ctr = 0; // keep track of how many records
  printHouseholdItemHeader();
  // iterate through entire linked list
  while (ptr != NULL) {
    printHouseholdItem(++ctr, ptr->item);
    ptr = ptr->next; // next item
  }
  // print format
  printHouseholdItemSeparator();
  printHouseholdItemFooter();
  printHouseholdItemSeparator();

  // display number of records
  printf("Number of records: %d.\n", ctr);
  puts("");
}

/**
 * Print linked list by provided region
 *
 * @param head
 * @param region
 */
void printLinkedListByRegion(Node *head, int region) {
  Node *ptr = head;
  int ctr = 0;
  printHouseholdItemHeader();
  // iterate through entire linked list
  while (ptr != NULL) {
    // check if the region matches
    if (ptr->item.region == region)
      printHouseholdItem(
          ++ctr, ptr->item); // only print out the matching household item
    ptr = ptr->next;
  }
  printHouseholdItemSeparator();
  printf("Number of records: %d\n", ctr);
  puts("");
}

/**
 * Print linked list by provided town
 *
 * @param head
 * @param town
 */
void printLinkedListByTown(Node *head, int region, int town) {
  Node *ptr = head;
  int ctr = 0; // keep track of number of records
  printHouseholdItemHeader();
  while (ptr != NULL) {
    // check to find the matching town (with region)
    if (ptr->item.region == region && ptr->item.town == town)
      printHouseholdItem(++ctr, ptr->item);
    ptr = ptr->next; // iterate over to the next node
  }
  printHouseholdItemSeparator();
  printf("Number of records: %d\n", ctr);
  puts("");
}

/**
 * Print link list data by provided race
 *
 * @param head
 * @param race
 */
void printLinkedListByRace(Node *head, int race) {
  Node *ptr = head;
  int ctr = 0;
  printHouseholdItemHeader();
  // iterate through the linked list
  while (ptr != NULL) {
    // check to see if the rece matches
    if (ptr->item.race == race)
      printHouseholdItem(++ctr, ptr->item); // only print the matched results
    ptr = ptr->next;                        // move onto the next node
  }
  printHouseholdItemSeparator();
  printf("Number of records: %d\n", ctr);
  puts("");
}

/**
 * Display the number of adults tested positive in a specified region with the
 * minimum tested positive as a filter
 *
 * @param head
 * @param region
 * @param minTestedPositive
 */
void printLinkedListByRegionWithMinTestedPositive(Node *head, int region,
                                                  int minTestedPositive) {
  Node *ptr = head;
  int ctr = 0; // keep track of all the records
  printHouseholdItemHeader();
  // iterate through entire linked list
  while (ptr != NULL) {
    // check for matching region with minimum test positives amongst adults (not
    // seniors)
    if (ptr->item.region == region &&
        ptr->item.adultsTestedPositive >= minTestedPositive)
      printHouseholdItem(++ctr,
                         ptr->item); // only print out the matching results
    ptr = ptr->next;                 // go to next node
  }
  printHouseholdItemSeparator();
  printf("Number of records: %d\n", ctr);
  puts("");
}

/**
 * Calculate the number of positive tested cases based on region
 *
 * @param head
 * @param region structure
 */
void rankPositiveTestedBasedOnRegion(Node *head, rank_cases *region) {
  Node *ptr = head;
  int peelPositiveCases = 0, yorkPositiveCases = 0, durhamPositiveCases = 0;

  // go through entire linked list
  while (ptr != NULL) {
    // Peel (0) York (1) Durham (2) - check the value of region
    switch (ptr->item.region) {
    case 0:
      // Peel - add to peel sum
      peelPositiveCases += ptr->item.adultsTestedPositive;
      break;
    case 1:
      // York - add to york sum
      yorkPositiveCases += ptr->item.adultsTestedPositive;
      break;
    case 2:
      // Durham - add to durham sum
      durhamPositiveCases += ptr->item.adultsTestedPositive;
      break;
    default:
      break;
    }
    ptr = ptr->next; // go to next node
  }
  // Peel -- add the name and cases to a structure for further manipulation
  region[0].name = "Peel";
  region[0].cases = peelPositiveCases;

  // York -- add the name and cases to a structure for further manipulation
  region[1].name = "York";
  region[1].cases = yorkPositiveCases;

  // Durham -- add the name and cases to a structure for further manipulation
  region[2].name = "Durham";
  region[2].cases = durhamPositiveCases;
}

/**
 * Calculate the positive tested cases based on town
 *
 * @param head
 * @param town structure
 */
void rankPositiveTestedBasedOnTown(Node *head, rank_cases *town) {
  Node *ptr = head;

  // keep track of cases by city
  int bramptonCases = 0, mississaugaCases = 0, mapleCases = 0, vaughanCases = 0,
      whitbyCases = 0, oshawaCases = 0;

  // go through entire linked list
  while (ptr != NULL) {
    switch (ptr->item.region) {
    case 0:
      // Peel
      switch (ptr->item.town) {
      case 0:
        // Brampton - add cases to the overall for the respective city
        bramptonCases += ptr->item.adultsTestedPositive;
        break;
      case 1:
        // Mississauga - add cases to the overall for the respective city
        mississaugaCases += ptr->item.adultsTestedPositive;
        break;
      default:
        break;
      }
      break;
    case 1:
      // York
      switch (ptr->item.town) {
      case 0:
        // Maple - add cases to the overall for the respective city
        mapleCases += ptr->item.adultsTestedPositive;
        break;
      case 1:
        // Vaughan - add cases to the overall for the respective city
        vaughanCases += ptr->item.adultsTestedPositive;
        break;
      default:
        break;
      }
      break;
    case 2:
      // Durham
      switch (ptr->item.town) {
      case 0:
        // Whitby - add cases to the overall for the respective city
        whitbyCases += ptr->item.adultsTestedPositive;
        break;
      case 1:
        // Oshawa - add cases to the overall for the respective city
        oshawaCases += ptr->item.adultsTestedPositive;
        break;
      default:
        break;
      }
      break;
    default:
      break;
    }
    ptr = ptr->next; // go to next node
  }

  // all all town data to a structure for further manipulation (sorting based on
  // cases)
  town[0].name = "Brampton";
  town[0].cases = bramptonCases;

  town[1].name = "Mississauga";
  town[1].cases = mississaugaCases;

  town[2].name = "Maple";
  town[2].cases = mapleCases;

  town[3].name = "Vaughan";
  town[3].cases = vaughanCases;

  town[4].name = "Whitby";
  town[4].cases = whitbyCases;

  town[5].name = "Oshawa";
  town[5].cases = oshawaCases;
}

/**
 * Delete linked list items based on user specified arguments
 *
 * @param region
 * @param town
 * @param race
 */
void deleteLinkedListItem(NodePtr *head, int region, int town, int race) {
  // go through entire linked list
  while (*head != NULL) {
    // check if the node matches up with the region, town and race
    if ((*head)->item.region == region && (*head)->item.town == town &&
        (*head)->item.race == race) {
      // temp node to store the head
      Node *tmp = *head;
      // move head to the next node
      *head = (*head)->next;
      // free the memory of the previous head
      free(tmp);
    } else {
      // move onto next node
      head = &(*head)->next;
    }
  }
}

/**
 * Write linked list data to file
 *
 * @param file
 */
void storeDataToFile(Node *head) {
  Node *ptr = head;
  char fileName[25]; // user input for file name
  FILE *file;        // file pointer
  int ctr = 0;       // number of records being written to the file

  // clean out buffer
  while (getchar() != '\n')
    ;

  // Get filename from user
  printf("Enter the file name with extension, for example, households.txt\n");
  printf("Filename: ");
  fgets(fileName, sizeof(fileName),
        stdin); // get the file name from stdin (user input)
  fileName[strcspn(fileName, "\n")] =
      0; // remove the new line character from the filename

  // open the new file with "w" permission. this will ensure that the file will
  // be overwritten if already exists, and if doesn't exist, create it.
  file = fopen(fileName, "w");

  // check if the file has been created
  if (file == NULL) {
    printf("Unable to create/write to file.\n");
    return;
  }

  // add a header to the file corresponding with the data meant to view in that
  // column
  fprintf(file, "%5s\t%7s\t%16s\t%20s\t%20s\t%10s\t%15s\n", "S.no", "Size",
          "Total Tested", "Total Tested Positive", "Race", "Region", "Town");

  // loop through linked list and add each line to the file
  while (ptr != NULL) {
    // output data to the file
    fprintf(file, "%5d\t%7d\t%16d\t%20d\t%20s\t%10s\t%15s\n", ++ctr,
            ptr->item.size, ptr->item.tested, ptr->item.adultsTestedPositive,
            displayRace(ptr->item.race), displayRegion(ptr->item.region),
            displayTown(ptr->item.region, ptr->item.town));
    ptr = ptr->next; // go to the next node in the linked list
  }

  // display stats to the console
  printf("%d records have been written to the file: %s\n\n", ctr, fileName);

  // close file
  fclose(file);
}
