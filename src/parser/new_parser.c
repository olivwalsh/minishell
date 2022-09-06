#include "minishell.h"

int ms_parser(t_token *tokens, t_cmdlst **cmds)
{
	t_token	*tmp;
	t_cmd	*cmd;

	tmp = tokens;
	while (tmp && !g_global.data->err)
	{
		cmd = NULL;
		if (!tmp->prev && is_delimiter(tmp))
			return (EXIT_FAILURE);
		if (is_delimiter(tmp) && (tmp->next && is_delimiter(tmp->next)))
			return (EXIT_FAILURE);
		if (tmp->type == WORD)
			cmd = create_cmd(tmp);
		add_cmdlst(cmds, create_cmdlst(tmp->type, cmd));
		tmp = tmp->next;
	}
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
