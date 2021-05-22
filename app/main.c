#include "database.h"

#include <stdio.h>

#define SUB_BUFFER_SIZE	   5
#define RESULT_BUFFER_SIZE 20

uint32_t counter = 0;

uint32_t resultBuffer[RESULT_BUFFER_SIZE] = {0};
uint32_t testVector[RESULT_BUFFER_SIZE]	  = {0x1, 0x1, 0x65, 0x2, 0x66, 0x4, 0x68, 0x8, 0x6C, 0x2718};

void Call1(void* data)
{
	uint32_t value			= *(uint32_t*)data;
	resultBuffer[counter++] = value;
	printf("Call1: %d\n", value);
}

void Call2(void* data)
{
	uint32_t value			= *(uint32_t*)data;
	resultBuffer[counter++] = value + 100;
	printf("Call2: %d\n", value);
}

void Call3(void* data)
{
	uint32_t value			= *(uint32_t*)data;
	resultBuffer[counter++] = value + 10000;
	printf("Call3: %d\n", value);
}

int main()
{
	Database	 db;
	Subscription subBuffer[SUB_BUFFER_SIZE];

	Database_Init(&db, subBuffer, SUB_BUFFER_SIZE);
	Subscription* sub = Database_Subscribe(&db, "Topic1", "Sub1", Call1);
	if (sub == NULL)
		return 1;

	uint32_t callValue = 1;
	Database_Notify(&db, "Topic1", (void*)&callValue);

	sub = Database_Subscribe(&db, "Topic1", "Sub2", Call2);
	if (sub == NULL)
		return 2;

	Database_Notify(&db, "Topic1", (void*)&callValue);

	sub = Database_Subscribe(&db, "Topic2", "Sub3", Call3);
	if (sub == NULL)
		return 3;

	sub = Database_Subscribe(&db, "Topic3", "Sub4", Call1);
	if (sub == NULL)
		return 4;

	sub = Database_Subscribe(&db, "Topic3", "Sub5", Call2);
	if (sub == NULL)
		return 5;

	sub = Database_Subscribe(&db, "Topic4", "Sub6", Call3);
	if (sub != NULL)
		return 6;

	callValue = 2;
	Database_Notify(&db, "Topic1", (void*)&callValue);
	Database_Notify(&db, "Topic4", (void*)&callValue);
	callValue = 4;
	Database_Notify(&db, "Topic3", (void*)&callValue);

	sub = Database_FindSubscription(&db, "Sub6");
	if (sub != NULL)
		return 7;

	sub = Database_FindSubscription(&db, "Sub3");
	if (sub == NULL)
		return 8;

	Database_Unsubscribe(&db, sub);
	Database_Notify(&db, "Topic2", (void*)&callValue);

	callValue = 8;
	sub		  = Database_Subscribe(&db, "Topic1", "Sub6", Call3);
	Database_Notify(&db, "Topic1", (void*)&callValue);

	for (size_t i = 0; i < counter; i++)
	{
		if (testVector[i] != resultBuffer[i])
			return RESULT_BUFFER_SIZE + i;
	}

	return 0;
}
