#include "serial.h"
#include "ioport.h"
#include "utils.h"

void init_serial_port(void)
{
    /* set speed */
    out8(SERIAL_PORT(3), BIT(7));
    out8(SERIAL_PORT(0), 1);
    out8(SERIAL_PORT(1), 0);

    /* set other settings */
    out8(SERIAL_PORT(3), BIT(0) | BIT(1));

    /* set polling */
    out8(SERIAL_PORT(1), 0);
}

void putc(char c)
{
    out8(SERIAL_PORT(0), c);
    while (!(in8(SERIAL_PORT(5)) & BIT(5)));
}

// unlike standart puts this implementation 
// doesn't put a newline character in the end
void puts(const char *s)
{
    while (*s)
    {
        putc(*s);
        s++;
    }
}
