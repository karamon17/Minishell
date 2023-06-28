/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:25:12 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/28 14:25:14 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_helper(char *tmp, t_shell *shell, char *value, int *cat)
{
	if (ft_checkletter(tmp, cat))
		check_add(shell, ft_strdup(tmp), value, cat);
	else
		ft_printerror(tmp, value);
}
