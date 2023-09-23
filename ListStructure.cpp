#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ListStructure.h"

void Section::AddSelector(char new_name[])
{
	Selector_list* newSelector = new Selector_list();
	newSelector->name = new char[strlen(new_name)];
	strcpy(newSelector->name, new_name);
	if (selectors == nullptr) {
		selectors = newSelector;
		selectors_tail = newSelector;
	}
	else {
		selectors_tail->next = newSelector;
		newSelector->prev = selectors_tail;
		newSelector->next = nullptr;
		selectors_tail = newSelector;
	}
}

void Section::AddAttribute(char new_name[])
{
	Attribute_list* newAtt = new Attribute_list();
	newAtt->name = new char[strlen(new_name)];
	strcpy(newAtt->name, new_name);
	if (attributes == nullptr) {
		attributes = newAtt;
		attributes_tail = newAtt;
	}
	else {
		attributes_tail->next = newAtt;
		newAtt->prev = attributes_tail;
		newAtt->next = nullptr;
		attributes_tail = newAtt;
	}
}

void Section::DeleteNode(Attribute_list* deletedAtt) {
	if (deletedAtt == attributes) {
		attributes = attributes->next;
		if (attributes != nullptr)attributes->prev = nullptr;
	}
	else if (deletedAtt == attributes_tail) {
		attributes_tail = attributes_tail->prev;
		if (attributes_tail != nullptr)attributes_tail->next = nullptr;
	}
	else {
		deletedAtt->next->prev = deletedAtt->prev;
		deletedAtt->prev->next = deletedAtt->next;
	}
	delete deletedAtt;
}

Section::~Section() {
	Selector_list* tempsel = selectors;
	Selector_list* tempsel_next = nullptr;
	while (tempsel != nullptr) {
		tempsel_next = tempsel->next;
		delete[] tempsel->name;
		delete tempsel;
		tempsel = tempsel_next;
	}
	Attribute_list* tempatt = attributes;
	Attribute_list* tempatt_next = nullptr;
	while (tempatt != nullptr) {
		tempatt_next = tempatt->next;
		delete[] tempatt->value;
		delete[] tempatt->name;
		delete tempatt;
		tempatt = tempatt_next;
	}
}

Block_list::Block_list() {
	section = new Section[T];
}

Block_list::~Block_list() {
	delete[] section;
}

void Block_list::AddBlock(Block_list* head)
{
	Block_list* newBlock = new Block_list();
	Block_list* tmp = head;
	while (tmp->next != nullptr) {
		tmp = tmp->next;
	}
	tmp->next = newBlock;
	newBlock->next = nullptr;
	newBlock->prev = tmp;
}