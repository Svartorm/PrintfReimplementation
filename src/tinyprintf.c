#include "tinyprintf.h"

#include <stdarg.h>
#include <stdio.h>

void swap(char *uwu, char *owo)
{
    char qwq = *uwu;
    *uwu = *owo;
    *owo = qwq;
}

void str_revert(char str[])
{
    int len = 0;
    while (str[len] != 0)
        len++;

    int uwu = 0;
    int owo = len - 1;

    for (int i = 0; i < len / 2; i++)
    {
        swap(&str[uwu], &str[owo]);
        uwu++;
        owo--;
    }
}

char *my_itoa_base(int value, char *s, const char *base)
{
    if (value == 0)
    {
        *s = *base;
        *(s + 1) = 0;
        return s;
    }

    int len = 0;
    while (*(base + len) != 0)
        len++;

    int i = 0;
    int flag = 0;

    if (value < 0)
    {
        value *= -1;
        flag = 1;
    }

    while (value > 0)
    {
        *(s + i) = base[value % len];
        value /= len;
        i++;
    }

    if (flag == 1)
    {
        *(s + i) = '-';
        i++;
    }

    *(s + i) = 0;
    str_revert(s);

    return s;
}

char *my_itoa_base_u(unsigned value, char *s, const char *base)
{
    if (value == 0)
    {
        *s = *base;
        *(s + 1) = 0;
        return s;
    }

    int len = 0;
    while (*(base + len) != 0)
        len++;

    int i = 0;

    while (value > 0)
    {
        *(s + i) = base[value % len];
        value /= len;
        i++;
    }

    *(s + i) = 0;
    str_revert(s);

    return s;
}

int handle_deci(int i, int arg)
{
    char num[300];
    return handle_str(i, my_itoa_base(arg, num, "0123456789"));
}

int handle_unsign(int i, unsigned arg)
{
    char num[300];
    return handle_str(i, my_itoa_base_u(arg, num, "0123456789"));
}

int handle_str(int i, char *arg)
{
    if (arg == NULL)
        arg = "(null)";

    int u = 0;
    for (; arg[u] != 0; u++)
        putchar(arg[u]);

    return i + 1;
}

int handle_octal(int i, int arg)
{
    char num[300];
    return handle_str(i, my_itoa_base(arg, num, "01234567"));
}

int handle_hexa(int i, int arg)
{
    char num[300];
    return handle_str(i, my_itoa_base_u(arg, num, "0123456789abcdef"));
}

int tinyprintf(const char *format, ...)
{
    va_list args;

    if (format == NULL)
        return 0;

    va_start(args, format);

    // We run through our input string
    int i = 0;
    for (; format[i] != 0; i++)
    {
        if (format[i] == '%') // Directive
        {
            if (format[i + 1] == 0)
                return i;

            // Handle directive
            switch (format[i + 1])
            {
            case 'd':
                i = handle_deci(i, va_arg(args, int));
                continue;

            case 'u':
                i = handle_unsign(i, va_arg(args, unsigned));
                continue;

            case 's':
                i = handle_str(i, va_arg(args, char *));
                continue;

            case 'o':
                i = handle_octal(i, va_arg(args, int));
                continue;

            case 'x':
                i = handle_hexa(i, va_arg(args, int));
                continue;

            case 'c':
            /* FALLTHROUGH */
            case '%':
                putchar(format[i + 1] == '%' ? '%' : va_arg(args, int));
                i++;
                continue;

            default:
                putchar(format[i++]);
                putchar(format[i]);
                continue;
            }
        }

        // Print c
        putchar(format[i]);
    }

    va_end(args);

    return i - 1; // This function return the number of characters printed, -1
                  // if an error occurs
}

/*
int main(void)
{
    tinyprintf("Hello World!\n");
    //tinyprintf("%s [%d] %s", "Hello", 42, "world!\n");
    //tinyprintf("%s [%x] %s", "Hello", 42, "world!\n");
    tinyprintf("%%s\n", "in your head");
    //tinyprintf("Good morning ACU! %t Tinyprintf is cool\n", 12);
    //tinyprintf("%c%c is %s... %d too.\n", '4', '2', "the answer", '*');
    return 0;
}
*/
