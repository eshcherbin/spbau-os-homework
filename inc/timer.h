#ifndef __TIMER_H__
#define __TIMER_H__

#define TIMER_FREQ 1193182

#define TIMER_COMMAND_PORT 0x43
#define TIMER_DATA_PORT 0x40

void start_timer(void);

#endif
