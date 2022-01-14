#include <stdio.h>
#include <stdarg.h>


static int ft_is_ok(char c)
{
    if (c == 'c' || c == 's' || c == 'p' || c == 'd' || 
        c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%')
        return (1);
    else 
        return (0);
}

static void ft_putchar(void *c, int * r)
{
    char temp = (char)c;
    write(1, &temp, 1);
    *r += 1;
}

static void ft_print_it(const char s, va_list p, int * r)
{
    //void * (f)(void *, int *)[10] = {ft_putadr, ft_putchar, ft_putnbr, ft_putstr, 
    //                ft_nbr_hexa, ft_putnbr_u, NULL, 
    //                ft_putnbr, ft_nbr_HEXA, ft_percent};
    void (*ft_tab[10])(void *, int *) = {NULL, ft_putchar, NULL, NULL, 
                    NULL, NULL, NULL, 
                    NULL, NULL, NULL};
    //printf("s : %c\ns %% 14 : %d", s, s % 14);
    void * pap;
    pap = va_arg(p, void *);
    ft_tab[s % 14](pap, r);
}

int ft_printf(const char * s, ...)
{
    int result;
    va_list ptr;
    
    va_start(ptr, s);
    result = 0;
    while (*s)
    {
        if (!(*s == '%'))
            ft_putchar((void *)*(s), &result);
        else if (*s++ == '%' && ft_is_ok(*s--))
            ft_print_it(*++s, ptr, &result);
        s++;
    }
    va_end(ptr);
    return (result);
}

int main()
{
    ft_printf("ceci est un test avec : %c et %\n\n",'T');
    ft_printf("ceci est un test avec : %c et %y\n\n",'1');
}

/*
void test2(va_list p)
{
    printf("///test 2\\\\\\\n");
    int d = va_arg(p, int);
    printf("d : %d\n", d);
    return ;
}

void test(int a, ...)
{
    printf("///test 1\\\\\\\n");
    va_list ptr;
    va_start(ptr, a);
    printf("1er appel : \n");
    test2(ptr);
    printf("2e appel : \n");
    test2(ptr);
    printf("3e appel : \n");
    test2(ptr);
}




//c : 1 
//s : 3 
//p : 0 
//d : 2 
//i : 7 
//u : 5 
//x : 8 
//X : 4 
//% : 9 

*/
