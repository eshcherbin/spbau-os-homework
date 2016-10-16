#include "io.h"
#include "serial.h"
#include <limits.h>
#include <stdint.h>

#define PRINT_DEC \
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
                    putc(stack[i]);

#define PRINT_HEX \
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
                    putc(stack[i]);

#define SNPUTC(c) \
                if (curn + 1 < n) \
                { \
                    s[curn++] = c; \
                } 

#define SNPRINT_DEC \
                if (item == 0) \
                    SNPUTC('0'); \
                len = 0; \
                while (item) \
                { \
                    stack[len++] = '0' + item % 10; \
                    item /= 10; \
                } \
                for (int i = len - 1; i >= 0; i--) \
                    SNPUTC(stack[i]);

#define SNPRINT_OCT \
                SNPUTC('0'); \
                if (item == 0) \
                    SNPUTC('0'); \
                len = 0; \
                while (item) \
                { \
                    stack[len++] = '0' + item % 8; \
                    item /= 8; \
                } \
                for (int i = len - 1; i >= 0; i--) \
                    SNPUTC(stack[i]); \

#define SNPRINT_HEX \
                SNPUTC('0'); \
                SNPUTC('x'); \
                if (item == 0) \
                    SNPUTC('0'); \
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
                    SNPUTC(stack[i]);

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
            else 
            {
                int64_t item_;
                uint64_t item;
                char tp;

                if (format[1] == 'h')
                {
                    if (format[2] != 'h')
                    {
                        item_ = va_arg(arg, int);
                        tp = format[2];
                        format += 3;
                    }
                    else
                    {
                        if (!format[3])
                            return -1;
                        item_ = va_arg(arg, int);
                        tp = format[3];
                        format += 4;
                    }
                    if (item_ < 0)
                    {
                        putc('-');
                        item_ = -item_;
                    }
                    item = item_;
                    if (tp == 'd' || tp == 'i' || tp == 'u')
                    {
                        PRINT_DEC
                    }
                    else if (tp == 'o')
                    {
                        PRINT_OCT
                    }
                    else
                    {
                        PRINT_HEX
                    }
                }
                else if (format[1] == 'l')
                {
                    if (format[2] != 'l')
                    {
                        tp = format[2];
                        if (tp == 'd' || tp == 'i')
                        {
                            item_ = va_arg(arg, long);
                            if (item_ == LLONG_MIN)
                            {
                                puts("-9223372036854775808");
                            }
                            else
                            {
                                if (item_ < 0)
                                {
                                    putc('-');
                                    item_ = -item_;
                                }
                                item = item_;
                                if (tp == 'd' || tp == 'i' || tp == 'u')
                                {
                                    PRINT_DEC
                                }
                            }
                        }
                        else
                        {
                            item = va_arg(arg, long);
                            if (tp == 'd' || tp == 'i' || tp == 'u')
                            {
                                PRINT_DEC
                            }
                            else if (tp == 'o')
                            {
                                PRINT_OCT
                            }
                            else
                            {
                                PRINT_HEX
                            }
                        }
                        format += 3;
                    }
                    else
                    {
                        if (!format[3])
                            return -1;
                        tp = format[3];
                        if (tp == 'd' || tp == 'i')
                        {
                            item_ = va_arg(arg, long long);
                            if (item_ == LLONG_MIN)
                            {
                                puts("-9223372036854775808");
                            }
                            else
                            {
                                if (item_ < 0)
                                {
                                    putc('-');
                                    item_ = -item_;
                                }
                                item = item_;
                                if (tp == 'd' || tp == 'i' || tp == 'u')
                                {
                                    PRINT_DEC
                                }
                            }
                        }
                        else
                        {
                            item = va_arg(arg, long long);
                            if (tp == 'd' || tp == 'i' || tp == 'u')
                            {
                                PRINT_DEC
                            }
                            else if (tp == 'o')
                            {
                                PRINT_OCT
                            }
                            else
                            {
                                PRINT_HEX
                            }
                        }
                        format += 4;
                    }
                }
                else
                {
                    item_ = va_arg(arg, int);
                    tp = format[1];
                    if (item_ < 0)
                    {
                        putc('-');
                        item_ = -item_;
                    }
                    item = item_;
                    if (tp == 'd' || tp == 'i' || tp == 'u')
                    {
                        PRINT_DEC
                    }
                    else if (tp == 'o')
                    {
                        PRINT_OCT
                    }
                    else
                    {
                        PRINT_HEX
                    }
                    format += 2;
                }
                result++;
            }
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

int vsnprintf (char *s, size_t n, const char *format, va_list arg)
{
    static char stack[30];
    static int len;
    static const char int64min[] = "-9223372036854775808";

    if (n <= 0)
        return -1;
    size_t curn = 0;
    
    int result = 0;
    while (*format)
    {
        if (*format == '%')
        {
            if (!format[1])
                return -1;
            if (format[1] == '%')
            {
                SNPUTC('%');
                format += 2;
            }
            else if (format[1] == 'c')
            {
                char item = (char) va_arg(arg, int);
                SNPUTC(item);
                format += 2;
            }
            else if (format[1] == 's')
            {
                const char *item = va_arg(arg, const char*);
                while (*item)
                {
                    SNPUTC(*item);
                    item++;
                }
                format += 2;
            }
            else 
            {
                int64_t item_;
                uint64_t item;
                char tp;

                if (format[1] == 'h')
                {
                    if (format[2] != 'h')
                    {
                        item_ = va_arg(arg, int);
                        tp = format[2];
                        format += 3;
                    }
                    else
                    {
                        if (!format[3])
                            return -1;
                        item_ = va_arg(arg, int);
                        tp = format[2];
                        format += 4;
                    }
                    if (item_ < 0)
                    {
                        SNPUTC('-');
                        item_ = -item_;
                    }
                    item = item_;
                    if (tp == 'd' || tp == 'i' || tp == 'u')
                    {
                        SNPRINT_DEC
                    }
                    else if (tp == 'o')
                    {
                        SNPRINT_OCT
                    }
                    else
                    {
                        SNPRINT_HEX
                    }
                }
                else if (format[1] == 'l')
                {
                    if (format[2] != 'l')
                    {
                        tp = format[2];
                        if (tp == 'd' || tp == 'i')
                        {
                            item_ = va_arg(arg, long);
                            if (item_ == LLONG_MIN)
                            {
                                const char *tmp = int64min;
                                while (*tmp)
                                {
                                    SNPUTC(*tmp);
                                    tmp++;
                                }
                            }
                            else
                            {
                                if (item_ < 0)
                                {
                                    SNPUTC('-');
                                    item_ = -item_;
                                }
                                item = item_;
                                if (tp == 'd' || tp == 'i' || tp == 'u')
                                {
                                    SNPRINT_DEC
                                }
                            }
                        }
                        else
                        {
                            item = va_arg(arg, long);
                            if (tp == 'd' || tp == 'i' || tp == 'u')
                            {
                                SNPRINT_DEC
                            }
                            else if (tp == 'o')
                            {
                                SNPRINT_OCT
                            }
                            else
                            {
                                SNPRINT_HEX
                            }
                        }
                        format += 3;
                    }
                    else
                    {
                        if (!format[3])
                            return -1;
                        tp = format[3];
                        if (tp == 'd' || tp == 'i')
                        {
                            item_ = va_arg(arg, long long);
                            if (item_ == LLONG_MIN)
                            {
                                const char *tmp = int64min;
                                while (*tmp)
                                {
                                    SNPUTC(*tmp);
                                    tmp++;
                                }
                            }
                            else
                            {
                                if (item_ < 0)
                                {
                                    SNPUTC('-');
                                    item_ = -item_;
                                }
                                item = item_;
                                if (tp == 'd' || tp == 'i' || tp == 'u')
                                {
                                    SNPRINT_DEC
                                }
                            }
                        }
                        else
                        {
                            item = va_arg(arg, long long);
                            if (tp == 'd' || tp == 'i' || tp == 'u')
                            {
                                SNPRINT_DEC
                            }
                            else if (tp == 'o')
                            {
                                SNPRINT_OCT
                            }
                            else
                            {
                                SNPRINT_HEX
                            }
                        }
                        format += 4;
                    }
                }
                else
                {
                    item_ = va_arg(arg, int);
                    tp = format[1];
                    if (item_ < 0)
                    {
                        SNPUTC('-');
                        item_ = -item_;
                    }
                    item = item_;
                    if (tp == 'd' || tp == 'i' || tp == 'u')
                    {
                        SNPRINT_DEC
                    }
                    else if (tp == 'o')
                    {
                        SNPRINT_OCT
                    }
                    else
                    {
                        SNPRINT_HEX
                    }
                    format += 2;
                }
                result++;
            }
        }
        else
        {
            SNPUTC(*format);
            format++;
        }
    }

    s[curn] = 0;
    return result;
}

int snprintf (char *s, size_t n, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int result = vsnprintf(s, n, format, args);
    va_end(args);
    return result;
}
