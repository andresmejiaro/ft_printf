#include <stdio.h>

#include "ft_putnbrbasepiscina.c"
#include "ft_printf.c"





int main(void)
{   
    int o=33333699;

    char k='w';
    char str[]="berry";
    float f=12.3;

    printf("hello %i como %c m %p un float %f \n", o,k,str,f);
    ft_printf("hello %i como %c m %p un float %f \n", o,k,str,f);
    printf("P%pP",(void *)str);
    ft_printf("P%pP",(void *)str);
    ft_printf("%p", (void *)-14523);
    return 0;
}








