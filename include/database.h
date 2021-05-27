#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "bufferedlist.h"

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
	BufferedList Subscriptions;
} Database;

void		  Database_Init(Database* database, Subscription* buffer, uint32_t number);
Subscription* Database_Subscribe(Database* database, char* topic, char* name, NotifyCallback callback);
Subscription* Database_FindSubscription(Database* database, char* name);
void		  Database_Unsubscribe(Database* database, Subscription* subscription);
void		  Database_Notify(Database* database, char* topic, void* data);

#endif
