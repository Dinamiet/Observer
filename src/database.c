#include "database.h"

// #include "fnv.h"
// #define HASH_FUNC FNV_Hash

#include "sdbm.h"
#define HASH_FUNC SDBM_Hash

#include <string.h>

void Database_Init(Database* database, Subscription* buffer, size_t num)
{
	BufferedList_Init(&database->Subscriptions, (Node*)buffer, sizeof(Subscription), num);
}

Subscription* Database_Subscribe(Database* database, char* topic, char* name, NotifyCallback callback)
{
	Subscription* sub = (Subscription*)BufferedList_LinkTail(&database->Subscriptions);
	if (sub)
	{
		sub->Name	  = name ? HASH_FUNC(name, strlen(name)) : 0;
		sub->Topic	  = HASH_FUNC(topic, strlen(topic));
		sub->Callback = callback;
	}

	return sub;
}

Subscription* Database_FindSubscription(Database* database, char* name)
{
	Subscription* sub	  = (Subscription*)database->Subscriptions.Used.Head;
	uint32_t	  subName = name ? HASH_FUNC(name, strlen(name)) : 0;
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
	uint32_t	  topicName = HASH_FUNC(topic, strlen(topic));
	if (sub == NULL)
		return;
	do {
		if (sub->Topic == topicName)
			sub->Callback(data);

		sub = (Subscription*)sub->List.Next;
	} while (sub != (Subscription*)database->Subscriptions.Used.Head);
}
