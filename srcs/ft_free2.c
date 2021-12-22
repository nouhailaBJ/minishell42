/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:47:54 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/09/17 15:56:56 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_data(void)
{
	if (g_data.cmd)
	{
		free_list(g_data.cmd);
		g_data.cmd = NULL;
	}
}

void	ft_free(char *line)
{
	free(line);
	line = NULL;
}

char	**free_table(char **tabl, int j)
{
	while (j--)
		free(tabl[j]);
	free(tabl);
	tabl = NULL;
	return (NULL);
}

int	free_key(char *key, int ex)
{
	free(key);
	return (ex);
}
