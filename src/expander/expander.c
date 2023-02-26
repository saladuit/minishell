#include <minishell.h>

void    skip_until_quote_or_dollar(char *arg, size_t *i)
{
    while (arg[*i] && !is_dollar(arg[*i]) && !is_quote(arg[*i]))
        (*i)++;
}

char *expand_single_quote(char *arg)
{
    size_t len = ft_strlen(arg) - 2;
    char *expanded = ft_substr(arg, 1, len);
    return expanded;
}

char *combine_expanded_strings(t_list *stack)
{
    char *result;
    char *tmp;

    tmp = NULL;
    result = ft_calloc(1, 1);
    while (stack)
    {
        tmp = ft_strjoin(result, stack->content);
        free(result);
        result = tmp;
        stack = stack->next;
    }
    return (result);
}

t_list *copy_until_quote_or_dollar(char *arg, size_t *i)
{
    char *expansion;
    t_list *node;

    skip_until_quote_or_dollar(arg, i);
    expansion = ft_substr(arg, 0, *i);
    if (!expansion)
        return (NULL);
    node = ft_lstnew(expansion);
    return (node);
}

// Return the error code or the environment variable
char *expand_dollar(char *arg, t_exitstatus *status)
{
    char *expansion;

    if (*(++arg) == '\0')
        return (ft_strdup("$"));
    if (*arg == '?')
        return (ft_itoa(*status));
    expansion = getenv(arg);
    if (expansion == NULL) 
        return (ft_strdup(""));
    return (ft_strdup(expansion));
}

t_list *expand_dollar_node(char *arg, size_t *i, t_exitstatus *status)
{
    t_list *node;
    char *expansion;

    expansion = expand_dollar(arg,status);
    if (!expansion)
        return (NULL);
    (*i)++;
    skip_until_quote_or_dollar(arg, i);
    node = ft_lstnew(expansion);
    return (node);
}

char *expand_token(char *arg, t_exitstatus *status)
{
    t_list *stack;
    t_list *node;
    char *new_arg;
    size_t i;

    (void)status;
    i = 0;
    stack = NULL;
    node = NULL;
    while (arg[i])
    {
        if (is_dollar(arg[i]))
            node = expand_dollar_node(arg, &i, status);
        else if (is_single_quote(arg[i]))
            node = expand_single_quote_node(arg, &i);
        else
            node = copy_until_quote_or_dollar(arg, &i);
        if (node == NULL)
        {
            ft_lstclear(&stack, free);
            return (NULL);
        }
        ft_lstadd_back(&stack, node);
    }
    new_arg = combine_expanded_strings(stack);
    ft_lstclear(&stack, free);
    return (new_arg);
}

bool are_quotes_closed(const char *str)
{
    bool in_single_quote;
    bool in_double_quote;
    
    in_single_quote = false;
    in_double_quote = false;
    while (*str != '\0')
    {
        if (is_single_quote(*str)) 
            in_single_quote = !in_single_quote;
        else if (is_double_quote(*str)) 
            in_double_quote = !in_double_quote;
        str++;
    }
    
    return (!in_single_quote && !in_double_quote);
}

//this will be moved to parser
void expand_tokens(t_list **arg, t_exitstatus *status)
{
    t_list *curr;
    char *arg_str;
    char *arg_expanded;

    curr = *arg;
    while (curr)
    {
        arg_str = (char *)curr->content;
        if (are_quotes_closed(arg_str))
        {
            arg_expanded = expand_token(arg_str, status);
            free(arg_str);
            curr->content = arg_expanded;
        }
        curr = curr->next;
    }
}
