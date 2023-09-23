#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define BUFFERSIZE 128
#define T 8
class Attribute_list {
public:
	char *name=nullptr;
	char *value=nullptr;
	Attribute_list* next = nullptr;
	Attribute_list* prev = nullptr;
};

class Selector_list {
public:
	char *name=nullptr;
	Selector_list* next = nullptr;
	Selector_list* prev = nullptr;
};

class Section {
public:
	Selector_list* selectors = nullptr;
	Selector_list* selectors_tail = nullptr;
	Attribute_list* attributes = nullptr;
	Attribute_list* attributes_tail = nullptr;

	void AddSelector(char new_name[]);

	void AddAttribute(char new_name[]);

	void DeleteNode(Attribute_list* deletedAtt);

	~Section();
};

class Block_list {
public:
	Section* section=nullptr;
	Block_list* next = nullptr;
	Block_list* prev = nullptr;

	Block_list();
	~Block_list();

	void AddBlock(Block_list* head);
};