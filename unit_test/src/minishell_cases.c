// #include <stdio.h>
// #include <unit_test.h>
//
// void redirect_stdfds(void)
// {
//     cr_redirect_stdin();
//     cr_redirect_stdout();
// }
// char *cr_strdup(const char *str)
// {
//     char *ptr = cr_malloc(strlen(str) + 1);
//     if (ptr)
//         strcpy(ptr, str);
//     return ptr;
// }
// int32_t	minishell_loop(t_minishell *sheldon);
//
// Test(minishell_loop, test_ls_exit) 
// {
//     t_minishell sheldon;
//
// 	ft_bzero(&sheldon, sizeof(t_minishell));
// 	sheldon.command_line = ft_strdup("ls");
//     minishell_loop(&sheldon);
// }
