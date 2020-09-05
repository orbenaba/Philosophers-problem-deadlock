#include "Table.h"


//declarations
int pickSticks(Table* t);
int putDownSticks(Table* disconnected, Table* table);
DWORD WINAPI eat(LPVOID lpParameter);
void closeHandles(HANDLE* handles, int len);


CRITICAL_SECTION locker;


int main()
{
	int i;
	InitializeCriticalSection(&locker);
	Table* table = bulidTable();//build the table for the diner - guest
	printf("The diner table before someone starts to eat:\n");
	printTable(table);
	HANDLE handles[5];
	for (i = 0; i < 5; i++) {
		handles[i] = CreateThread(NULL, NULL, eat, table, NULL, NULL);
		table = table->next->next;
	}
	WaitForMultipleObjects(5, handles, TRUE, 10000);//Wait for all the five theards at the most - 10 seconds
	DeleteCriticalSection(&locker);
	printf("The diner table after everyone are satisfied:\n");
	closeHandles(handles, 5);
	printTable(table);
	destructTable(table);//free resources
	return 0;
}





DWORD WINAPI eat(LPVOID lpParameter)
{
	Table* disconnected = (Table*)lpParameter;
	printf("Philopher %d gets in the dinner room\n", disconnected->id);
	Table* table = disconnected->next->next;
	EnterCriticalSection(&locker);
	//The philospher waits to both sticks to be available,
	//this line will cause deadlock in case we don't use CRITICAL_SECTION
	while (disconnected->next == NULL || disconnected->prev == NULL);
	pickSticks(disconnected);//Only one philosopher can picks up two sticks
	printf("Philosopher %d picks up the sticks and starts to eat\n",disconnected->id);
	putDownSticks(disconnected, table);
	printf("Philosopher %d is satisfied and puts down the sticks\n\n",disconnected->id);
	LeaveCriticalSection(&locker);
	return 0;
}


//The philosopher picks two sticks -> critcal section
int pickSticks(Table* t)
{
	if (t->next == NULL || t->prev == NULL)
		return 0;
	t->prev->next = NULL;
	t->next->prev = NULL;
	t->next = t->prev = NULL;//Critical line
	return 1;
}


int putDownSticks(Table* disconnected, Table* table) 
{
	Table* runner = table;
	while (runner->prev != NULL)
		runner = runner->prev;
	//connect the right spoon back to the table
	runner->prev = disconnected;
	disconnected->next = runner;
	while (runner->next != NULL)
		runner = runner->next;
	//connect the left spoon back to the table
	runner->next = disconnected;
	disconnected->prev = runner;
	return 1;
}

void closeHandles(HANDLE* handles, int len)
{
	int i;
	for (i = 0; i < len; i++)
		CloseHandle(handles[i]);
}