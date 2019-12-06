#include "subscriber.h"

TSubscriber systick_subscribers[MAX_SUBSCRIBERS];

unsigned int NUM_SUBSCRIBERS = 0;

void Notify_SysTick(void)
{
  unsigned int index;
  for (index = 0; index < NUM_SUBSCRIBERS; ++index)
  {
    systick_subscribers[index].current++;
  }
}

SubscriberID RegisterSubscriber(void)
{
  if (NUM_SUBSCRIBERS >= MAX_SUBSCRIBERS)
  {
    return BAD_SUBSCRIBER;
  }
  return NUM_SUBSCRIBERS++;
}

void ServiceSubscriber(SubscriberID id)
{
    if (id < 0 || id >= MAX_SUBSCRIBERS) return;
    
    TSubscriber * thisSubscriber = &systick_subscribers[id];
    if(thisSubscriber->current >= thisSubscriber->threshold)
    {
      thisSubscriber->callback();
      thisSubscriber->current = 0;
    }
}

HSubscriber GetSubscriber(SubscriberID id)
{
  if (id < 0 || id >= MAX_SUBSCRIBERS) return 0;
  return &systick_subscribers[id];
}