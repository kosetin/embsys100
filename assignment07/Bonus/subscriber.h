#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__

#define HSubscriber TSubscriber*
#define BAD_SUBSCRIBER -1

typedef int SubscriberID;

enum { MAX_SUBSCRIBERS = 5 };

typedef struct Subscriber
{
  unsigned int current;
  unsigned int threshold;
  void (*callback)(void);
} TSubscriber;

void Notify_SysTick(void);
SubscriberID RegisterSubscriber(void);
HSubscriber GetSubscriber(SubscriberID id);
void ServiceSubscriber(SubscriberID id);

#endif