/**
 * @author Elmer Almeida
 * @date July 27 2021
 *
 * This file handles the definitions of linked list associated methods
 */

#ifndef ELMERALMEIDAASSIGN3_LINKEDLIST_H
#define ELMERALMEIDAASSIGN3_LINKEDLIST_H

#include "almeielm.h"

/*
 * Linked list administration
 */
Node *makeNode(household item);
void addNode(NodePtr *head, household item);
void deleteLinkedListItem(NodePtr *head, int region, int town, int race);

/*
 * Printing options on the linked list
 */
void printLinkedList(Node *head);
void printLinkedListByRegion(Node *head, int region);
void printLinkedListByTown(Node *head, int region, int town);
void printLinkedListByRace(Node *head, int race);
void printLinkedListByRegionWithMinTestedPositive(Node *head, int region, int minTestedPositive);

/*
 * Rank options by region and town
 */
void rankPositiveTestedBasedOnRegion(Node *head, rank_cases *region);
void rankPositiveTestedBasedOnTown(Node *head, rank_cases *town);

/*
 * Write linked list data to a user defined file
 */
void storeDataToFile(Node *head);

#endif
