#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "linkedlist.h"

typedef void (*Observer_Notify)(const void*);

typedef struct _ObserverSubscription_
{
	Node            Node;
	size_t          TopicID;
	Observer_Notify Notify;
} ObserverSubscription;

typedef struct _Observer_
{
	LinkedList Subscriptions;
} Observer;

void                  Observer_Init(Observer* obs);
ObserverSubscription* Observer_Subscribe(Observer* obs, ObserverSubscription* sub, const size_t topic, const Observer_Notify notify);
ObserverSubscription* Observer_Unsubscribe(Observer* obs, ObserverSubscription* sub);
bool                  Observer_HasSubscription(const Observer* obs, const ObserverSubscription* sub);
void                  Observer_Publish(const Observer* obs, const size_t topic, const void* data);

#endif
