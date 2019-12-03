#include "subscriber.h"

enum { MAX_SUBSCRIBERS = 10 };

TSubscriber systick_subscribers[MAX_SUBSCRIBERS];

unsigned int NUM_SUBSCRIBERS = 0;

void Notify_SysTick(void)
{
  unsigned int index;
  for (index = 0; index < NUM_SUBSCRIBERS; ++index)
  {
    TSubscriber * thisSubscriber = &systick_subscribers[index];
    if(thisSubscriber->current++ >= thisSubscriber->threshold)
    {
      thisSubscriber->callback();
      thisSubscriber->current = 0;
    }
  }
}

TSubscriber * Register_Subscriber_SysTick(void)
{
  if (NUM_SUBSCRIBERS > MAX_SUBSCRIBERS-1)
  {
    return 0;
  }
  return &systick_subscribers[NUM_SUBSCRIBERS++];
}