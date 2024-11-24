#include "observer.h"

#include <assert.h>

void Observer_Init(Observer* obs)
{
	assert(obs != NULL);

	LinkedList_Init(&obs->Subscriptions);
}

ObserverSubscription* Observer_Subscribe(Observer* obs, ObserverSubscription* sub, const size_t topic, const Observer_NotifyHandler notify_handler)
{
	assert(obs != NULL);

	if (!notify_handler || !sub)
		return NULL;

	sub->TopicID = topic;
	sub->Handler = notify_handler;

	return LinkedList_AddEnd(&obs->Subscriptions, sub);
}

ObserverSubscription* Observer_Unsubscribe(Observer* obs, ObserverSubscription* sub)
{
	assert(obs != NULL);

	return LinkedList_Remove(&obs->Subscriptions, sub);
}

bool Observer_HasSubscription(const Observer* obs, const ObserverSubscription* sub)
{
	assert(obs != NULL);

	ObserverSubscription* obsSub = LinkedList_First(&obs->Subscriptions);
	if (!obsSub || !sub)
		return false;

	do {
		if (sub == obsSub)
			return true;

		obsSub = LinkedList_Next(obsSub);
	} while (obsSub != LinkedList_First(&obs->Subscriptions));

	return false;
}

void Observer_Publish(const Observer* obs, const size_t topic, const void* data)
{
	assert(obs != NULL);

	ObserverSubscription* sub = LinkedList_First(&obs->Subscriptions);
	if (!sub)
		return;

	do {
		if (topic == sub->TopicID)
			sub->Handler(data);

		sub = LinkedList_Next(sub);
	} while (sub != LinkedList_First(&obs->Subscriptions));
}
