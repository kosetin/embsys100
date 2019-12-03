#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__

typedef struct Subscriber
{
  unsigned int current;
  unsigned int threshold;
  void (*callback)(void);
} TSubscriber;

void Notify_SysTick(void);
TSubscriber * Register_Subscriber_SysTick(void);

#endif