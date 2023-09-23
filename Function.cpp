#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Function.h"
#include "ListStructure.h"

using namespace std;

void countSections(Block_list* start) {
	Block_list* tmp = start;
	int counter = 0;
	while (tmp != nullptr) {
		for (int i = 0; i < T; i++) {
			if (tmp->section[i].attributes != nullptr)counter++;
		}
		tmp = tmp->next;
	}
	cout << "? == " << counter << endl;
}

void countSelectors(int i, Block_list* start) {
	int selcounter = 0;
	int scounter = 0;
	Block_list* tmp_block = start;
	Selector_list* tmp_selector = nullptr;
	Selector_list* tmp_selector2 = nullptr;
	while (tmp_block != nullptr) {
		for (int t = 0; t < T; t++) {
			if (tmp_block->section[t].attributes != nullptr)scounter++;
			if (scounter == i) {
				tmp_selector = tmp_block->section[t].selectors;
				tmp_selector2 = tmp_block->section[t].selectors;
				break;
			}
		}
		if (scounter == i)break;
		tmp_block = tmp_block->next;
	}
	while (tmp_selector != nullptr) {
		if(tmp_selector->name[0]!='\0')selcounter++;
		tmp_selector = tmp_selector->next;
	}
	if (tmp_selector2 != nullptr)cout << i << ",S,? == " << selcounter << endl;
}

void countAttributes(int i, Block_list* start) {
	int scounter = 0;
	int attcounter = 0;
	Block_list* tmp_block = start;
	Attribute_list* tmp_att = nullptr;
	while (tmp_block != nullptr) {
		for (int t = 0; t < T; t++) {
			if (tmp_block->section[t].attributes != nullptr)scounter++;
			if (scounter == i) {
				tmp_att = tmp_block->section[t].attributes;
				break;
			}
		}
		if (scounter == i)break;
		tmp_block = tmp_block->next;
	}
	while (tmp_att != nullptr) {
		attcounter++;
		tmp_att = tmp_att->next;
	}
	if (attcounter != 0)cout << i << ",A,? == " << attcounter << endl;//moze byc bug
}

void coutSelector(int i, int j, Block_list* start) {
	Block_list* tmp_block = start;
	Selector_list* tmp_selector = nullptr;
	int scount = 0;
	int selcount = 0;

	while (tmp_block != nullptr) {
		for (int t = 0; t < T; t++) {
			if (tmp_block->section[t].attributes != nullptr)scount++;
			if (scount == i) {
				tmp_selector = tmp_block->section[t].selectors;
				break;
			}
		}
		if (scount == i)break;
		tmp_block = tmp_block->next;
	}
	if (tmp_selector != nullptr) {
		while (tmp_selector != nullptr) {
			if (selcount == j - 1) {
				if(tmp_selector->name[0]!=NULL)cout << i << ",S," << j << " == " << tmp_selector->name << endl;
				break;
			}
			selcount++;
			tmp_selector = tmp_selector->next;
		}
	}
	else return;
}

void coutAttribute(int i, char* att, Block_list* start) {
	Block_list* tmp_block = start;
	Attribute_list* tmp_att = nullptr;
	int scount = 0;
	while (tmp_block != nullptr) {
		for (int t = 0; t < T; t++) {
			if (tmp_block->section[t].attributes != nullptr)scount++;
			if (scount == i) {
				tmp_att = tmp_block->section[t].attributes;
				break;
			}
		}
		if (scount == i)break;
		tmp_block = tmp_block->next;
	}
	while (tmp_att != nullptr) {
		if (strcmp(tmp_att->name, att) == 0) {
			cout << i << ",A," << att << " == " << tmp_att->value << endl;
			break;
		}
		tmp_att = tmp_att->next;
	}
}

void countAttributeByName(char* arr, Block_list* start) {
	int counter = 0;
	Block_list* tmp = start;
	while (tmp != nullptr) {
		for (int i = 0; i < T; i++) {
			Attribute_list* temp = tmp->section[i].attributes;
			while (temp != nullptr) {
				if (strcmp(arr, temp->name) == 0)counter++;
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
	cout << arr << ",A,? == " << counter << endl;
}

void countSelectorByName(char* arr, Block_list* start) {
	int counter = 0;
	Block_list* tmp = start;
	Selector_list* temp = nullptr;
	while (tmp != nullptr) {
		for (int i = 0; i < T; i++) {
			temp = tmp->section[i].selectors;
			while (temp != nullptr) {
				if (strcmp(arr, temp->name) == 0) {
					counter++;
					break;
				}
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
	cout << arr << ",S,? == " << counter << endl;
}

void coutAttFromSelector(char* line1, char* line2, Block_list* start) {
	Block_list* tmp_block = start;
	Attribute_list* tmp_att = nullptr;
	Selector_list* tmp_sel = nullptr;
	while (tmp_block->next != nullptr) {
		tmp_block = tmp_block->next;
	}
	while (tmp_block != nullptr) {
		for (int i = T - 1; i >= 0; i--) {
			tmp_att = tmp_block->section[i].attributes_tail;
			if (tmp_att != nullptr) {
				tmp_sel = tmp_block->section[i].selectors;
				while (tmp_sel != nullptr) {
					if (strcmp(tmp_sel->name, line1) == 0) {
						while (tmp_att != nullptr) {
							if (strcmp(tmp_att->name, line2) == 0) {
								cout << line1 << ",E," << line2 << " == ";
								cout << tmp_att->value << endl;
								return;
							}
							tmp_att = tmp_att->prev;
						}
					}
					tmp_sel = tmp_sel->next;
				}
			}
		}
		tmp_block = tmp_block->prev;
	}
}

void DeleteSection(int i, Block_list* start) {
	int a = 0;
	int scounter = 0;
	Block_list* temp_block = start;
	if (i > 0) {
		while (temp_block != nullptr) {
			a = 0;
			for (int j = 0; j < T; j++) {
				if (temp_block->section[j].attributes != nullptr)scounter++;
				a++;
				if (scounter == i)break;
			}
			if (scounter == i)break;
			temp_block = temp_block->next;
		}
		if (temp_block != nullptr) {
			temp_block->section[a - 1].attributes = nullptr;
			temp_block->section[a - 1].attributes_tail = nullptr;
			temp_block->section[a - 1].selectors = nullptr;
			temp_block->section[a - 1].selectors_tail = nullptr;
			cout << i << ",D,* == deleted" << endl;
		}
	}
}

void DeleteAttribute(int i, char* att, Block_list* start) {
	int scounter = 0;
	int a = 0;
	bool emptySelector = 0;
	Block_list* tmp_block = start;
	Attribute_list* tmp_att = nullptr;
	while (tmp_block != nullptr) {
		for (int t = 0; t < T; t++) {
			if (tmp_block->section[t].attributes != nullptr)scounter++;
			if (scounter == i) {
				tmp_att = tmp_block->section[t].attributes;
				a = t;
				break;
			}
		}
		if (scounter == i)break;
		else tmp_block = tmp_block->next;
	}
	if (tmp_att != nullptr) {
		while (tmp_att != NULL) {
			if (tmp_att != nullptr) {
				if (strcmp(tmp_att->name, att) == 0)break;
				tmp_att = tmp_att->next;
			}
		}
		if (tmp_att != nullptr) {
			tmp_block->section[a].DeleteNode(tmp_att);
			cout << i << ",D," << att << " == deleted" << endl;
		}
		else emptySelector = 1;

		if (tmp_att == nullptr && emptySelector==0)DeleteSection(scounter, start);
	}
}

void executeCommand(char* commandType, char* line1, char* line2, Block_list* start) {
	if (line1[0] == '?')countSections(start);
	else if (commandType[0] == 'S') {
		if (isdigit(line1[0]) && line2[0] == '?') {
			countSelectors(atoi(line1), start);
		}
		else if (isdigit(line1[0]) && isdigit(line2[0])) {
			coutSelector(atoi(line1), atoi(line2), start);
		}
		else if (line2[0] == '?') {
			countSelectorByName(line1, start);
		}
	}
	else if (commandType[0] == 'A') {
		if (isdigit(line1[0]) && line2[0] == '?') {
			countAttributes(atoi(line1), start);
		}
		else if (isdigit(line1[0])) {
			coutAttribute(atoi(line1), line2, start);
		}
		else if (line2[0] == '?') {
			countAttributeByName(line1, start);
			*commandType = NULL;
		}
	}
	else if (commandType[0] == 'E') {
		coutAttFromSelector(line1, line2, start);
	}
	else if (commandType[0] == 'D') {
		if (line2[0] == '*')DeleteSection(atoi(line1), start);
		else DeleteAttribute(atoi(line1), line2, start);
	}
}

void cutBlankspaces(char* arr, int* end) {
	while (arr[*end] <= 32) {
		(*end)--;
	}
}

void clearBuffer(char* arr) {
	for (int i = 0; i < BUFFERSIZE; i++) {
		arr[i] = NULL;
	}
}

void isAttDuplicate(Block_list* current, int *DuplicateAttCounter,int *j,char* buffer,bool *AttributeDuplicate) {
	Block_list* tmp_block = current;
	Attribute_list* tmp_att = tmp_block->section[*j].attributes;
	while (tmp_att != nullptr) {
		(*DuplicateAttCounter)++;
		if (strcmp(tmp_att->name, buffer) == 0) {
			*AttributeDuplicate = 1;
			break;
		}
		tmp_att = tmp_att->next;
	}
}

void FindDuplicateAddValue(Block_list* current, char* buffer, int j, int DuplicateAttCounter) {
		Block_list* tmp_block = current;
		Attribute_list* tmp_att = tmp_block->section[j].attributes;
		int counter = 0;
		while (tmp_att != nullptr) {
			counter++;
			if (DuplicateAttCounter == counter)break;
			tmp_att = tmp_att->next;
		}
		if (tmp_att != nullptr)AddAttValue(tmp_att, buffer);
}

void AddAttValue(Attribute_list* temp, char* buffer) {
	temp->value = new char[strlen(buffer)];
	strcpy(temp->value, buffer);
}

void ParseCommands
(char a, int* i, bool* getBlankspace, bool* commandsFlag, char buffer[],
	char endCommands[], char line1[], char line2[], bool* firstPart, bool* secondPart, bool* thirdPart, char* commandtype, Block_list* head) {
	if (a != ',' && a != '\n' && *i < BUFFERSIZE - 1) {
		if (a > ' ')*getBlankspace = 1;
		if (*getBlankspace == 1) {
			buffer[*i] = a;
			(*i)++;
		}
	}
	else if (a == '\n') {
		buffer[*i] = '\0';
		if (strcmp(buffer, endCommands) == 0) {
			*commandsFlag = 0;
			*i = 0;
		}
	}
	if (int(a) == EOF || a == ',' || a == '\n' && *i != 0) {
		*getBlankspace = 0;
		(*i)--;
		if (buffer[*i] <= 32)cutBlankspaces(buffer, i);
		buffer[(*i)+1] = '\0';
		if (*firstPart == 1) {
			strcpy(line1, buffer);
			buffer[0] = '\0';
			*firstPart = 0;
			*secondPart = 1;
			*i = 0;
		}
		else if (*secondPart == 1 && a != '\n') {
			*commandtype = buffer[0];
			*secondPart = 0;
			*thirdPart = 1;
			*i = 0;
			if (buffer[0] != 'A' && buffer[0] != 'S' && buffer[0] != 'D' && buffer[0] != 'E') {
				*firstPart = 1;
				*secondPart = 0;
			}
		}
		else if (*thirdPart == 1) {
			strcpy(line2, buffer);
			*firstPart = 1;
			*thirdPart = 0;
			*i = 0;
		}
		if (a == '\n' || int(a) == EOF && line2[0] != '?') {
			executeCommand(commandtype, line1, line2, head);
			*firstPart = 1;
			*secondPart = 0;
		}
	}
}

void ParseSelectors(char a, bool* getBlankspace, bool* readSelectors, bool* commandsFlag, char buffer[], char startCommands[], int *i, int *j, Block_list* current) {
	if (a != ',' && a != '\n' && a != '\t' && a != '{' && a != '}') {
		if (a > ' ')*getBlankspace = 1;
		if (*getBlankspace == 1) {
			buffer[*i] = a;
			(*i)++;
		}
	}
	else if (a == ',' || a == '{') {
		(*i)--;
		if (buffer[*i] <= 32)cutBlankspaces(buffer, i);
		buffer[(*i) + 1] = '\0';
		current->section[*j].AddSelector(buffer);
		*getBlankspace = 0;
		*i = 0;
	}
	if (a == '{') {
		*readSelectors = 0;
	}
	if (a == '\n') {
		buffer[*i] = '\0';
		if (strcmp(buffer, startCommands) == 0) {
			*commandsFlag = 1;
			*i = 0;
		}
	}
}

void ParseAttributes(char a, int* j,bool* readSelectors,int* i,bool* getBlankspace,char* buffer,Block_list* current, int* DuplicateAttCounter, bool* AttributeDuplicate) {
	if (a == '}') {
		(*j)++;
		*readSelectors = 1;
	}
	if (a != ':' && a != ';' && a != '\n' && a != '\t' && a != '{' && a != '}') {
		if (*i == 0 && a > 32)*getBlankspace = 1;
		if (*getBlankspace == 1) {
			buffer[*i] = a;
			(*i)++;
		}
	}
	else if (a == ':') {
		buffer[*i] = '\0';
		isAttDuplicate(current, DuplicateAttCounter, j, buffer, AttributeDuplicate);
		if (*AttributeDuplicate == 0)current->section[*j].AddAttribute(buffer);
		*getBlankspace = 0;
		*i = 0;
	}
	else if (a == ';') {
		buffer[*i] = '\0';
		if (*AttributeDuplicate == 1)FindDuplicateAddValue(current, buffer, *j, *DuplicateAttCounter);
		else AddAttValue(current->section[*j].attributes_tail, buffer);
		*getBlankspace = 0;
		*AttributeDuplicate = 0;
		*DuplicateAttCounter = 0;
		*i = 0;
	}
}