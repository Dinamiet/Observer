#ifndef _OBSERVER_H_
#define _OBSERVER_H_

/** \file
 * Observer
 *
 * General subscribe-notify design pattern
 */

#include "linkedlist.h"

#include <stdbool.h>

/**
 * Function template which will be used to notify subscribers of information on their topic
 * \param data The data which was published
 */
typedef void (*Observer_Notify)(const void* data);

/**
 * Subscription information storage
 */
typedef struct _ObserverSubscription_
{
	Node            Node;    /* Storage for housekeeping of all subscriptions */
	size_t          TopicID; /* Topic for which the subscription is waiting */
	Observer_Notify Notify;  /* Notification channel */
} ObserverSubscription;

/**
 * Observer information storage
 */
typedef struct _Observer_
{
	LinkedList Subscriptions; /* List of all active subscriptions */
} Observer;

/**
 * Observer initialization
 * \param obs Observer to initialize
 */
void Observer_Init(Observer* obs);

/**
 * Subscribe to a specific topic on the observer
 * \param obs Observer to which the subscription will be registered
 * \param sub Subscription storage where relative subscription information will be stored
 * \param topic The topic of interest
 * \param notify The notification function when data becomes available on topic
 * \return Newly added subscription (same as sub) if successful, NULL otherwise
 */
ObserverSubscription* Observer_Subscribe(Observer* obs, ObserverSubscription* sub, const size_t topic, const Observer_Notify notify);

/**
 * Unsubscribe or remove subscription from observer list
 * \param obs Observer from which the subscription will be removed
 * \param sub The subscription to remove
 * \return Removed subscription (same as sub) if successful, NULL otherwise
 */
ObserverSubscription* Observer_Unsubscribe(Observer* obs, ObserverSubscription* sub);

/**
 * Check if the subscription is registered with the observer
 * \param obs Observer to check subscription registration against
 * \param sub Subscription to search for in observer
 * \return True when subscription is registered with observer, False otherwise
 */
bool Observer_HasSubscription(const Observer* obs, const ObserverSubscription* sub);

/**
 * Publish data to a specific topic. All active subscription for the topic will be notified with the data
 * \param obs The observer to which the topic will be published
 * \param topic The topic to which data is published
 * \param data The data to notify subscribers about
 */
void Observer_Publish(const Observer* obs, const size_t topic, const void* data);

#endif
