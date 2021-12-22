/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 20:34:15 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 17:00:16 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_path_helper(t_pipes *pipe, char *path, char **tbl, int i)
{
	char	*tmp;

	tmp = pipe->params[0];
	pipe->params[0] = ft_strdup(path);
	free(tmp);
	while (tbl[i])
	{
		free(tbl[i]);
		i++;
	}
	if (path)
		free(path);
	free(tbl);
	tbl = NULL;
	return (1);
}

int	search_path_free(char *path, char **all_path)
{
	free(path);
	free(all_path);
	all_path = NULL;
	return (0);
}

int	search_path(char *line, t_pipes *pipe, char *pt)
{
	char		*path;
	char		**all_path;
	struct stat	stats;
	int			i;
	char		*tmp;

	pt = change_plus_envp("PATH");
	all_path = ft_split(pt, ':');
	free(pt);
	i = 0;
	path = ft_strdup("");
	while (all_path[i])
	{
		tmp = path;
		path = join_path(all_path[i], line);
		free(tmp);
		if (stat(path, &stats) == 0)
		{
			if (stats.st_mode & X_OK)
				return (search_path_helper(pipe, path, all_path, i));
		}
		free(all_path[i]);
		i++;
	}
	return (search_path_free(path, all_path));
}
