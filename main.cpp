#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <cstdlib>
#include "Function.h"
#include "ListStructure.h"

using namespace std;

int main() {
	char startCommands[5] = "????";
	char endCommands[5] = "****";

	char a;
	int i = 0;
	int j = 0;

	bool commandsFlag = 0;
	bool readSelectors = 1;

	bool firstPart = 1;
	bool secondPart = 0;
	bool thirdPart = 0;

	bool getBlankspace = 0;
	bool AttributeDuplicate = 0;
	int DuplicateAttCounter = 0;

	char* buffer = new char[BUFFERSIZE];
	clearBuffer(buffer);
	char* line1 = new char [BUFFERSIZE];
	char* line2 = new char [BUFFERSIZE];
	char commandtype=' ';

	Block_list* head = new Block_list();
	Block_list* current = head;

	while (a = getchar()) {
		if (commandsFlag == 0) {
			if (j >= T) {
				j = 0;
				head->AddBlock(head);
				current = current->next;
			}
			else if (readSelectors == 1) {
				ParseSelectors(a, &getBlankspace, &readSelectors, &commandsFlag, buffer, startCommands, &i, &j, current);
			}
			else if (readSelectors == 0) {
				ParseAttributes(a,&j,&readSelectors,&i,&getBlankspace,buffer,current,&DuplicateAttCounter,&AttributeDuplicate);
			}
		}
		else if (commandsFlag == 1) {
			ParseCommands(a, &i, &getBlankspace, &commandsFlag, buffer,
				endCommands, line1, line2, &firstPart, &secondPart, &thirdPart, &commandtype, head);
		}
		if (int(a) == EOF) {
			exit(0);
		}
	}
	Block_list* tempblock = head;
	Block_list* tempblock_next = nullptr;
	while (tempblock != nullptr) {
		tempblock_next = tempblock->next;
		delete tempblock;
		tempblock = tempblock_next;
	}
	delete[] buffer;
	delete[] line1;
	delete[] line2;
}