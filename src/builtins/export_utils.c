#include "minishell.h"

void	export_helper(char *tmp, t_shell *shell, char *value, int *cat)
{
	if (ft_checkletter(tmp, cat))
		check_add(shell, ft_strdup(tmp), value, cat);
	else
		ft_printerror(tmp, value);
}
