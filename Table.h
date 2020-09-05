#include "pci.h"

//isPhilosopher = 0 -> stick 
//iPhilosopher !=0 -> philosopher
typedef struct Table {
	byte isPhilosopher;
	int id;
	struct Table* prev, * next;
}Table;
Table* bulidTable();
void destructTable(Table* table);
void printTable(Table* table);