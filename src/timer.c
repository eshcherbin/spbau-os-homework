#include "timer.h"
#include "ioport.h"
#include "utils.h"
#include "interrupt.h"

void start_timer()
{
    mask_devices_master(BIT(0));

    out8(TIMER_COMMAND_PORT, (2 << 1) | BIT(4) | BIT(5));
    out8(TIMER_DATA_PORT, 0xff);
    out8(TIMER_DATA_PORT, 0xff);

    unmask_devices_master(BIT(0));
}
