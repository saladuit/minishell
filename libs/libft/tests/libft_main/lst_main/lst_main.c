#include "../libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int test_lstnew(void)
{
    t_list *start;
    char *p = "Smart people look at the right tree";

    start = ft_lstnew(p);
    puts((char*)(start->content));
    return (0);
}

int test_lstadd_front(void)
{
    t_list *start;
    t_list *new;
    char *p1 = "becuase smart people look at the right tree";
    char *p2 = "Nature is growing and glowing, ";

    start = ft_lstnew(p1);
    new = ft_lstnew(p2);
    ft_lstadd_front(&start, new);
    puts((char*)(start->content));
    puts((char*)(start->next->content));
    return (0);
}

int test_lstadd_back(void)
{
    t_list *start;
    t_list *new;

    char *p1 = "becuase smart people look at the right tree";
    char *p2 = "Nature is growing and glowing, ";
    char *p3 = "that is rocking in the wind";

    start = ft_lstnew(p1);
    new = ft_lstnew(p2);
    ft_lstadd_front(&start, new);
    new = ft_lstnew(p3);
    ft_lstadd_back(&start, new);
    puts((char*)(start->content));
    puts((char*)(start->next->content));
    puts((char*)(start->next->next->content));
    return (0);
}

int test_lstsize(void)
{
    t_list *start;
    t_list *new;

    char *p1 = "becuase smart people look at the right tree";
    char *p2 = "Nature is growing and glowing, ";
    char *p3 = "that is rocking in the wind";

    start = ft_lstnew(p1);
    new = ft_lstnew(p2);
    ft_lstadd_front(&start, new);
    new = ft_lstnew(p3);
    ft_lstadd_back(&start, new);
    puts((char*)(start->content));
    puts((char*)(start->next->content));
    puts((char*)(start->next->next->content));
    printf("size: %d\n", ft_lstsize(start));
    return (0);
}

int test_lstlast(void)
{
    t_list *start;
    t_list *new;

    char *p1 = "becuase smart people look at the right tree";
    char *p2 = "Nature is growing and glowing, ";
    char *p3 = "that is rocking in the wind";

    start = ft_lstnew(p1);
    new = ft_lstnew(p2);
    ft_lstadd_front(&start, new);
    new = ft_lstnew(p3);
    ft_lstadd_back(&start, new);
    puts((char*)(ft_lstlast(start)->content));
    return (0);
}

int test_lstdelone(void)
{
    char    *c;
    t_list  *start;

    c = strdup("1234567890");
    start = ft_lstnew(c);
    printf("%s\n", (char*)(start->content));
    ft_lstdelone(start, &free);
    printf("%s\n", (char*)(start->content));
}

int test_lstclear(void)
{
    t_list      *start;
    t_list      *new;
    char *one;
    char *two;
    char *three;

    one = strdup("1234567890");
    two = strdup("asdfghjkl");
    three = strdup("qwertyuiop");
    start = ft_lstnew(one);
    new = ft_lstnew(two);
    ft_lstadd_back(&start, new);
    new = ft_lstnew(three);
    ft_lstadd_back(&start, new);
    printf("%s\n", (char*)start->content);
    printf("%s\n", (char*)start->next->content);
    printf("%s\n", (char*)start->next->next->content);
    ft_lstclear(&start, &free);
    printf("%p\n", start);
    return (0);
}

void    convert_str_to_upper(void *s)
{
    int     i;
    char    *str;
    str = s;    
    i = 0;
    while (str[i] != 0)
    {
        str[i] = toupper(str[i]);
        i++;
    }
}
int test_lstiter(void)
{
    t_list      *start;
    t_list      *new;
    char *one;
    char *two;
    char *three;
    one = strdup("1234567890");
    two = strdup("asdfghjkl");
    three = strdup("qwertyuiop");
    start = ft_lstnew(one);
    new = ft_lstnew(two);
    ft_lstadd_back(&start, new);
    new = ft_lstnew(three);
    ft_lstadd_back(&start, new);
    printf("%s\n", (char*)start->content);
    printf("%s\n", (char*)start->next->content);
    printf("%s\n", (char*)start->next->next->content);
    ft_lstiter(start, &convert_str_to_upper);
    printf("%s\n", (char*)start->content);
    printf("%s\n", (char*)start->next->content);
    printf("%s\n", (char*)start->next->next->content);
    return (0);
}
