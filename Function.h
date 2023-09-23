#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "ListStructure.h"
void countSections(Block_list* start);

void countSelectors(int i, Block_list* start);

void countAttributes(int i, Block_list* start);

void coutSelector(int i, int j, Block_list* start);

void coutAttribute(int i, char* att, Block_list* start);

void countAttributeByName(char* arr, Block_list* start);

void countSelectorByName(char* arr, Block_list* start);

void coutAttFromSelector(char* line1, char* line2, Block_list* start);

void DeleteSection(int i, Block_list* start);

void DeleteAttribute(int i, char* att, Block_list* start);

void executeCommand(char* commandType, char* line1, char* line2, Block_list* start);

void cutBlankspaces(char* arr, int* end);

void clearBuffer(char* arr);

void isAttDuplicate(Block_list* current, int* DuplicateAttCounter, int* j, char* buffer, bool* AttributeDuplicate);

void FindDuplicateAddValue(Block_list* current, char* buffer, int j, int DuplicateAttCounter);

void ParseCommands(char a, int* i, bool* getBlankspace, bool* commandsFlag, char buffer[],
	char endCommands[], char line1[], char line2[], bool* firstPart, bool* secondPart, bool* thirdPart, char* commandtype, Block_list* head);

void ParseSelectors(char a, bool* getBlankspace, bool* readSelectors, bool* commandsFlag, char buffer[], char startCommands[], int* i, int* j, Block_list* current);

void ParseAttributes(char a, int* j, bool* readSelectors, int* i, bool* getBlankspace, char* buffer, Block_list* current, int* DuplicateAttCounter, bool* AttributeDuplicate);

void AddAttValue(Attribute_list* temp, char* buffer);