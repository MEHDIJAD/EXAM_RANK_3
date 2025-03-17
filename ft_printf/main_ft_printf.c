#include <stdio.h>

int ft_printf(const char *format, ...);

int main(void)
{
    ft_printf("%s\n", "toto");
    printf("%s\n", "toto");
    ft_printf("Magic %s is %d", "number", 42);
    printf("Magic %s is %d", "number", 42);
    ft_printf("Hexadecimal for %d is %x\n", 42, 42);
    printf("Hexadecimal for %d is %x\n", 42, 42);


}