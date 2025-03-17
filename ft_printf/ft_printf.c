#include <unistd.h>
#include <stdarg.h>

int ft_printchar(int c)
{
    return (write(1, &c, 1));  
}

int ft_printstr(char *str)
{
    int count;

    count = 0;
    if (str == NULL)
        count += ft_printstr("(null)");
    else if (str)
    {
        while (*str)
        {
            ft_printchar(*str++);
            count++;
        }
    }
    return (count);
}
int ft_printdigit(long number, int base, char *base_symbols)
{
    unsigned long n;
    int           count;
    count = 0;
    if (number < 0 && base == 10)
    {
        count += ft_printchar('-');
        n = -number;
    }
    else
    {
        n = (unsigned long)number;
    }
    if (n >= (unsigned long)base)
    {
        count += ft_printdigit((n / base), base, base_symbols);
    }
    count += ft_printchar(base_symbols[n % base]);
    return (count);
}

int ft_print_format(char f_sp, va_list ap)
{
    int count;

    count = 0;
    if (f_sp == 'c')
        count += ft_printchar(va_arg(ap, int));
    else if (f_sp == 's')
        count += ft_printstr(va_arg(ap, char *));
    else if (f_sp == 'd')
        count += ft_printdigit(va_arg(ap, int),10, "0123456789");
    else if (f_sp == 'x')
        count += ft_printdigit(va_arg(ap, int),16, "0123456789abcdef");

    return (count);
}

int ft_printf(const char *format, ...)
{
    va_list ap;
    int count;

    if(write(1, 0, 0) == -1)
        return (-1);
    count = 0;
    va_start(ap, format);
    while (*format)
    {
        if (*format == '%')
            count += ft_print_format(*(++format), ap);
        else
            count += write(1, format, 1);
        format++;
    }
    va_end(ap);
    return (count);
}