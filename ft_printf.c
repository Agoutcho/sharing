#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

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
    char temp; 
    
    temp = (char)c;
    write(1, &temp, 1);
    *r += 1;
}

static void ft_putstr(void *c, int * r)
{
    char * temp; 
    
    temp = (char *)c;
    while (*temp)
    {
        write(1, temp, 1);
        *r += 1;
        temp++;
    }
}

void ft_puthexa_up(void * n, int * r)
{
    char * hexa;
    int number;

    number = (int)n;
    hexa = "0123456789ABCDEF";
    if (number < 0)
    {
        number = -number;
        ft_putchar((void *)'-', r);
    }
    if (number > 15)
        ft_puthexa_up((void *)(number / 16), r);
    ft_putchar((void *)hexa[number % 16], r); 
}

void ft_puthexa_low(void * n, int * r)
{
    char * hexa;
    int number;

    number = (int)n;
    hexa = "0123456789abcdef";
    if (number < 0)
    {
        number = -number;
        ft_putchar((void *)'-', r);
    }
    if (number > 15)
        ft_puthexa_low((void *)(number / 16), r);
    ft_putchar((void *)hexa[number % 16], r); 
}

void ft_putnbr(void * n, int * r)
{
    char * decimal;
    int number;

    number = (int)n;
    decimal = "0123456789";
    if (number < 0)
    {
        number = -number;
        ft_putchar((void *)'-', r);
    }
    if (number > 9)
        ft_putnbr((void *)(number / 10), r);
    ft_putchar((void *)decimal[number % 10], r); 
}

void ft_putnbr_u(void * n, int * r)
{
    char * decimal;
    unsigned int number;

    number = (unsigned int)n;
    decimal = "0123456789";
    if (number > 9)
        ft_putnbr_u((void *)(number / 10), r);
    ft_putchar((void *)decimal[number % 10], r); 
}

void ft_putadr(void * p, int * r)
{
    unsigned long nb;
    char * hexa;

    nb = (unsigned long)p;
    hexa = "0123456789abcdef";
    if (nb > 15)
        ft_putadr((void *)(nb / 16), r);
    ft_putchar((void *)hexa[nb % 16], r); 
}

static void ft_print_it(const char s, va_list p, int * r)
{
    void (*f[9])(void *, int *) = {ft_putadr, ft_putchar, ft_putnbr, ft_putstr, 
                   ft_puthexa_up, ft_putnbr_u, NULL, 
                    ft_putnbr, ft_puthexa_low};
    //void (*ft_tab[10])(void *, int *) = {NULL, ft_putchar, NULL, NULL, 
    //                ft_puthexa_up, NULL, NULL, 
    //                NULL, ft_puthexa_low, NULL};
    if (s == '%')
    {
        ft_putchar((void *)'%', r);
        return ;
    }
    else if (s == 'p')
        ft_putstr((void *)"0x", r);
    void * pap;
    pap = va_arg(p, void *);
    f[s % 14](pap, r);
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
    int u = 9;
    //ft_printf("c : %c \nx : %x \nX : %X",'T', 95, 95);
    printf   ("printf    %%p : %p\n", &u);
    ft_printf("ft_printf %%p : %p\n",&u);
    printf   ("printf    %%c : %c\n", 'z');
    ft_printf("ft_printf %%c : %c\n", 'z');
    printf   ("printf    %%d : %d\n", 745);
    ft_printf("ft_printf %%d : %d\n", 745);
    printf   ("printf    %%s : %s\n","MDR lol 2 ptdr");
    ft_printf("ft_printf %%s : %s\n","MDR lol 2 ptdr");
    printf   ("printf    %%X : %X\n", 967);
    ft_printf("ft_printf %%X : %X\n", 967);
    printf   ("printf    %%u : %u\n", -12);
    ft_printf("ft_printf %%u : %u\n", -12);
    printf   ("printf    %%i : %i\n", -12);
    ft_printf("ft_printf %%i : %i\n", -12);
    printf   ("printf    %%x : %x\n", 967);
    ft_printf("ft_printf %%x : %x\n", 967);


    //ft_printf("ft_printf %%p : %p\n",&u);
    //ft_printf("ceci est un test avec : %c et %y\n\n",'1');
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
