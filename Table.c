#include "Table.h"

Table* bulidTable()
{
	Table* table = (Table*)malloc(sizeof(Table));//dummy
	Table* runner = table, * prev;
	int i;
	for (i = 0; i < 5; i++) {
		//Build philosopher
		runner->next = (Table*)malloc(sizeof(Table));
		prev = runner;
		runner = runner->next;
		runner->isPhilosopher = 1;
		runner->id = i + 1;
		runner->prev = prev;
		//Build Spoon
		runner->next = (Table*)malloc(sizeof(Table));
		prev = runner;
		runner = runner->next;
		runner->id = 0;
		runner->isPhilosopher = 0;
		runner->prev = prev;
	}
	//ignore the first dummy node
	runner->next = table->next;
	table->next->prev = runner;
	free(table);
	return runner->next;//Does not matter which node is returned
}
void destructTable(Table* table)
{
	Table* runner = table->next, * deleted;
	while (runner != table)
	{
		deleted = runner;
		runner = runner->next;
		free(deleted);
	}
	free(table);
}
void printTable(Table* table)
{
	Table* runner = table->next;
	if (table->isPhilosopher)
		printf("Philosopher %d <-> ", table->id);
	else
		printf("Stick <-> ");
	while (runner != table)
	{
		if (runner->isPhilosopher)
			printf("Philosopher %d <-> ", runner->id);
		else
			printf("Stick <-> ");
		runner = runner->next;
	}
	printf("\n\n");
}