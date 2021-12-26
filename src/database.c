#include "database.h"

// #include "fnv.h"
// #define HASH_FUNC FNV_Hash

#include "sdbm.h"
#define HASH_FUNC SDBM_Hash

#include <string.h>

void Database_Init(Database* database) { LinkedList_Init(&database->Subscriptions); }

void Database_Subscribe(Database* database, Subscription* subscription, char* topic, char* name, NotifyCallback callback)
{
	if (subscription)
	{
		LinkedList_LinkTail(&database->Subscriptions, subscription);
		subscription->Name	   = name ? HASH_FUNC(name, strlen(name)) : 0;
		subscription->Topic	   = HASH_FUNC(topic, strlen(topic));
		subscription->Callback = callback;
	}
}

Subscription* Database_FindSubscription(Database* database, char* name)
{
	Subscription* sub	  = (Subscription*)database->Subscriptions.Head;
	uint32_t	  subName = name ? HASH_FUNC(name, strlen(name)) : 0;
	if (sub == NULL)
		return NULL;
	do {
		if (sub->Name == subName)
			return sub;

		sub = (Subscription*)sub->List.Next;
	} while (sub != (Subscription*)database->Subscriptions.Head);

	// Subscription could not be found
	return NULL;
}

void Database_Unsubscribe(Database* database, Subscription* subscription) { LinkedList_UnlinkNode(&database->Subscriptions, &subscription->List); }

void Database_Notify(Database* database, char* topic, void* data)
{
	Subscription* sub		= (Subscription*)database->Subscriptions.Head;
	uint32_t	  topicName = HASH_FUNC(topic, strlen(topic));
	if (sub == NULL)
		return;
	do {
		if (sub->Topic == topicName)
			sub->Callback(data);

		sub = (Subscription*)sub->List.Next;
	} while (sub != (Subscription*)database->Subscriptions.Head);
}
