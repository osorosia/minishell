/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:00:48 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 20:06:12 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_token	*tok;
	t_node	*node;
	char	*str;
	int		pid;
	int		sts;
	t_node	*tmp;

	rl_outstream = stderr;
	g_shell = create_shell(envp);
	while (true)
	{
		signal_init();
		str = readline("% ");
		if (str == NULL)
			break ;
		if (is_only_space(str))
		{
			free(str);
			continue ;
		}
		add_history(str);
		{
			pid = fork();
			if (pid == 0)
			{
				tok = lexer(str);
				node = parser(tok);
				exit(0);
			}
			wait(&sts);
			if (sts != 0)
			{
				free(str);
				g_shell->sts = 258;
				continue ;
			}
		}
		tok = lexer(str);
		node = parser(tok);
		free_lexer(tok);
		expander_set_heredoc(node);
		signal_exec();
		exec(node);
		free_parser(node);
		free(str);
	}
	ft_putstr_fd("exit\n", 2);
	exit(g_shell->sts);
}
