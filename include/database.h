#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "linkedlist.h"

#include <stddef.h>
#include <stdint.h>

typedef void (*NotifyCallback)(void*);

typedef struct
{
	Node		   List;
	uint32_t	   Name;
	uint32_t	   Topic;
	NotifyCallback Callback;
} Subscription;

typedef struct
{
	LinkedList Subscriptions;
} Database;

void		  Database_Init(Database* database);
void		  Database_Subscribe(Database* database, Subscription* subscription, char* topic, char* name, NotifyCallback callback);
Subscription* Database_FindSubscription(Database* database, char* name);
void		  Database_Unsubscribe(Database* database, Subscription* subscription);
void		  Database_Notify(Database* database, char* topic, void* data);

#endif
