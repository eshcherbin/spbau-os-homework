#include "io.h"
#include "serial.h"
#include <limits.h>

#define PRINT_DEC \
                if (item < 0) \
                { \
                    putc('-'); \
                    item = -item; \
                } \
                if (item == 0) \
                    putc('0'); \
                len = 0; \
                while (item) \
                { \
                    stack[len++] = '0' + item % 10; \
                    item /= 10; \
                } \
                for (int i = len - 1; i >= 0; i--) \
                    putc(stack[i]); \

#define PRINT_OCT \
                if (item < 0) \
                { \
                    putc('-'); \
                    item = -item; \
                } \
                putc('0'); \
                if (item == 0) \
                    putc('0'); \
                len = 0; \
                while (item) \
                { \
                    stack[len++] = '0' + item % 8; \
                    item /= 8; \
                } \
                for (int i = len - 1; i >= 0; i--) \
                    putc(stack[i]); \

#define PRINT_HEX \
                if (item < 0) \
                { \
                    putc('-'); \
                    item = -item; \
                } \
                putc('0'); \
                putc('x'); \
                if (item == 0) \
                    putc('0'); \
                len = 0; \
                while (item) \
                { \
                    if (item % 16 < 10) \
                        stack[len++] = '0' + item % 16; \
                    else \
                        stack[len++] = 'a' + item % 16 - 10; \
                    item /= 16; \
                } \
                for (int i = len - 1; i >= 0; i--) \
                    putc(stack[i]); \

int vprintf(const char *format, va_list arg)
{
    static char stack[30];
    static int len;

    int result = 0;
    while (*format)
    {
        if (*format == '%')
        {
            if (!format[1])
                return -1;
            if (format[1] == '%')
            {
                putc('%');
                format += 2;
            }
            else if (format[1] == 'c')
            {
                char item = (char) va_arg(arg, int);
                putc(item);
                format += 2;
            }
            else if (format[1] == 's')
            {
                const char *item = va_arg(arg, const char*);
                puts(item);
                format += 2;
            }
            else if (format[1] == 'h')
            {
                if (!format[2] || format[2] != 'h')
                {
                    if (format[2] == 'd' || format[2] == 'i')
                    {
                        short item = va_arg(arg, int);
                        if (item == SHRT_MIN)
                            puts("-32768");
                        else
                        {
                            PRINT_DEC
                        }
                    }
                    else
                    {
                        unsigned short item = va_arg(arg, unsigned int);
                        if (format[2] == 'u')
                        {
                            PRINT_DEC
                        }
                        else if (format[2] == 'o')
                        {
                            PRINT_OCT
                        }
                        else if (format[2] == 'x')
                        {
                            PRINT_HEX
                        }
                        else
                            return -1;
                    }
                    format += 3;
                }
                else
                {
                    if (!format[3])
                        return -1;
                    if (format[3] == 'd' || format[3] == 'i')
                    {
                        char item = va_arg(arg, int);
                        if (item == CHAR_MIN)
                            puts("-128");
                        else
                        {
                            PRINT_DEC
                        }
                    }
                    else
                    {
                        unsigned char item = va_arg(arg, unsigned int);
                        if (format[3] == 'u')
                        {
                            PRINT_DEC
                        }
                        else if (format[3] == 'o')
                        {
                            PRINT_OCT
                        }
                        else if (format[3] == 'x')
                        {
                            PRINT_HEX
                        }
                        else
                            return -1;
                    }
                    format += 4;
                }
            }
            else if (format[1] == 'l')
            {
                if (!format[2] || format[2] != 'l')
                {
                    if (format[2] == 'd' || format[2] == 'i')
                    {
                        long item = va_arg(arg, long);
                        if (item == LONG_MIN)
                            puts("-9223372036854775808");
                        else
                        {
                            PRINT_DEC
                        }
                    }
                    else
                    {
                        unsigned long item = va_arg(arg, unsigned long);
                        if (format[2] == 'u')
                        {
                            PRINT_DEC
                        }
                        else if (format[2] == 'o')
                        {
                            PRINT_OCT
                        }
                        else if (format[2] == 'x')
                        {
                            PRINT_HEX
                        }
                        else
                            return -1;
                    }
                    format += 3;
                }
                else
                {
                    if (!format[3])
                        return -1;
                    if (format[3] == 'd' || format[3] == 'i')
                    {
                        long long item = va_arg(arg, long long);
                        if (item == LLONG_MIN)
                            puts("-9223372036854775808");
                        else
                        {
                            PRINT_DEC
                        }
                    }
                    else
                    {
                        unsigned long long item = va_arg(arg, unsigned long long);
                        if (format[3] == 'u')
                        {
                            PRINT_DEC
                        }
                        else if (format[3] == 'o')
                        {
                            PRINT_OCT
                        }
                        else if (format[3] == 'x')
                        {
                            PRINT_HEX
                        }
                        else
                            return -1;
                    }
                    format += 4;
                }
            }
            else
            {
                if (format[1] == 'd' || format[1] == 'i')
                {
                    int item = va_arg(arg, int);
                    if (item == INT_MIN)
                        puts("-2147483648");
                    else
                    {
                        PRINT_DEC
                    }
                }
                else
                {
                    unsigned int item = va_arg(arg, unsigned int);
                    if (format[1] == 'u')
                    {
                        PRINT_DEC
                    }
                    else if (format[1] == 'o')
                    {
                        PRINT_OCT
                    }
                    else if (format[1] == 'x')
                    {
                        PRINT_HEX
                    }
                    else
                        return -1;
                }
                format += 2;
            }
            result++;
        }
        else
        {
            putc(*format);
            format++;
        }
    }

    return result;
}

int printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int result = vprintf(format, args);
    va_end(args);
    return result;
}

/*int vsnprintf (char *s, size_t n, const char *format, va_list arg)
{

}

int snprintf (char *s, size_t n, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int result = vprintf(format, args);
    va_end(args);
    return result;
}*/
