//#include <minishell.h>
//
//static bool	is_meta_token(t_list *tokens, char *type)
//{
//	char	*token;
//	bool	meta;
//
//	meta = false;
//	while (tokens)
//	{
//		token = (char *) tokens->content;
//		if (ft_strncmp() && !meta)
//			meta = true;
//		else if (is_meta(token) && meta)
//		{
//			*type = token;
//			return (false);
//		}
//		else
//			meta = false;
//		tokens = tokens->next;
//	}
//	if (is_meta(token))
//	{
//		*type = token;
//		return (false);
//	}
//	return (true);
//}
//
//bool	validate_tokens(t_list *tokens, t_status *exit)
//{
//	char	error_msg[2];
//	char	type;
//
//	if (!is_meta_token(tokens, &type))
//	{
//		error_msg[0] = type;
//		error_msg[1] = '\0';
//		*exit = message_general_error(E_UNEXPECTED_TOKEN, error_msg);
//		return (false);
//	}
//	else
//		return (true);
//}