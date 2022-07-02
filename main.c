/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:00:48 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 21:54:28 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_syntax(char *str)
{
	t_token	*tok;
	t_node	*node;
	int		sts;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		tok = lexer(str);
		node = parser(tok);
		exit(0);
	}
	wait(&sts);
	return (sts != 0);
}

void	run_command(char *str)
{
	t_token	*tok;
	t_node	*node;

	tok = lexer(str);
	node = parser(tok);
	free_lexer(tok);
	expander_set_heredoc(node);
	signal_exec();
	exec(node);
	free_parser(node);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	int		pid;
	int		sts;
	t_node	*tmp;

	rl_outstream = stderr;
	g_shell = create_shell(envp);
	if (argc == 2 && ft_strcmp(argv[1], "test") == 0)
		g_shell->is_test = true;
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
		if (check_syntax(str))
		{
			free(str);
			g_shell->sts = 258;
			continue ;
		}
		run_command(str);
		free(str);
	}
	ft_putstr_fd("exit\n", 2);
	exit(g_shell->sts);
}
