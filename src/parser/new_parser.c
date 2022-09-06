#include "minishell.h"

int ms_parser(t_token *tokens, t_cmdlst **cmds)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp && !g_global.data->err)
	{
		if (!tmp->prev && is_delim(tmp))
			return (EXIT_FAILURE);
		if (is_delim(tmp) && (tmp->next && is_delim(tmp->next)))
			return (EXIT_FAILURE);
		if (!is_delim(tmp))
			add_cmdlst(cmds, create_cmdlst(WORD, create_cmd(&tmp)));
		else
		{
			add_cmdlst(cmds, create_cmdlst(tmp->type, NULL));
			tmp = tmp->next;
		}
	}
	display_cmds();
	// gerer les erreurs type ( && = erreur, ) && = pas erreur 
	// set head
	// create a list of commands based on the parser
	// if no parsing errors are detected
	// return cmds
	// else
	// return error
	// clean the tokens
	return (EXIT_SUCCESS);
}
