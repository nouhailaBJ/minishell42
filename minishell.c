/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:38:43 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/09/19 17:40:48 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		if (g_data.fork == 0)
			rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		if (g_data.fork > 0)
		{
			g_data.fork = 0;
			printf("Quit: 3\n");
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	ctrl_d(void)
{
	ft_putstr_fd("exit\n", 2);
	g_data.done = 1;
	free(g_data.line);
	clear_mem();
	clear_data();
	exit(g_data.n_exit);
}

void	ft_parse(void)
{
	char	*status;

	add_history(g_data.line);
	if (*g_data.line && is_error(g_data.line, '|', -1) != -1
		&& is_error(g_data.line, ';', -1) != -1
		&& not_comp_quote(g_data.line) != -1
		&& is_redir_error(g_data.line) != -1)
	{
		stock_command(&g_data.cmd, g_data.line);
		ft_excute();
	}
}

void	ft_minishell(void)
{
	while (1)
	{
		g_data.line = readline("minishell$ ");
		if (!g_data.line)
			ctrl_d();
		else if (*g_data.line)
			ft_parse();
		free(g_data.line);
		g_data.fork = 0;
		clear_mem();
		clear_data();
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_data.done = 0;
	g_data.ctrl_c = 0;
	g_data.fork = 0;
	init_envp(envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	ft_minishell();
	return (0);
}
