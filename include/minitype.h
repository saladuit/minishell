#ifndef MINITYPE_H
# define MINITYPE_H

# include <stdbool.h>

bool	is_delimiter(int c);
bool	is_redir(int c);
bool	is_metachar(int c);
bool	is_quote(int c);
bool	is_double_quote(int c);
bool	is_double_quoted(char *str);
bool	is_single_quote(int c);
bool	is_single_quoted(char *str);
bool	is_expand(int c);

#endif
