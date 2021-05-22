#include "database.h"

// #include "fnv.h"
// #define HASH_FUNC FNV_Hash

#include "sdbm.h"
#define HASH_FUNC SDBM_Hash

#include <string.h>

void Database_Init(Database* database, Subscription* buffer, uint32_t number)
{
	BufferedList_Init(&database->Subscriptions, (Node*)buffer, sizeof(Subscription), number);
}

Subscription* Database_Subscribe(Database* database, char* name, char* topic, void (*callback)(void*))
{
	Subscription* sub = (Subscription*)BufferedList_LinkTail(&database->Subscriptions);
	if (sub)
	{
		sub->Name	  = HASH_FUNC((uint8_t*)name, strlen(name));
		sub->Topic	  = HASH_FUNC((uint8_t*)topic, strlen(name));
		sub->Callback = callback;
	}

	return sub;
}

Subscription* Database_FindSubscription(Database* database, char* name)
{
	Subscription* sub	  = (Subscription*)database->Subscriptions.Used.Head;
	uint32_t	  subName = HASH_FUNC((uint8_t*)name, strlen(name));
	if (sub == NULL)
		return NULL;
	do {
		if (sub->Name == subName)
			return sub;

		sub = (Subscription*)sub->List.Next;
	} while (sub != (Subscription*)database->Subscriptions.Used.Head);

	// Subscription could not be found
	return NULL;
}

void Database_Unsubscribe(Database* database, Subscription* subscription) { BufferedList_UnlinkNode(&database->Subscriptions, &subscription->List); }

void Database_Notify(Database* database, char* topic, void* data)
{
	Subscription* sub		= (Subscription*)database->Subscriptions.Used.Head;
	uint32_t	  topicName = HASH_FUNC((uint8_t*)topic, strlen(topic));
	if (sub == NULL)
		return;
	do {
		if (sub->Topic == topicName)
			sub->Callback(data);

		sub = (Subscription*)sub->List.Next;
	} while (sub != (Subscription*)database->Subscriptions.Used.Head);
}
