/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:24:10 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/12 17:32:55 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cdprint_error(char *cmd)
{
	g_error_status = 1;
	if (errno == 13)
		printf("Minishell : cd: %s: Permission denied\n", cmd);
	else
		printf("Minishell : cd: %s: Not a directory\n", cmd);
}
