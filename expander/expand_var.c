/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:17:31 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 10:27:31 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*_expand_var_in_str(char *str)
{
	char	*new;
	long	i;
	bool	double_quote;
	bool	single_quote;

	new = ft_xstrdup("");
	double_quote = false;
	single_quote = false;
	i = 0;
	while (str[i])
	{
		if (!single_quote && str[i] == '$')
		{
			i = _expand_var_at_doller_mark(str, &new, i);
			continue ;
		}
		if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		new = ft_str_add_char(new, str[i]);
		i++;
	}
	free(str);
	return (new);
}

void	_expand_var_in_redir(t_redir *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind != RD_HEREDOC)
		redir->str = _expand_var_in_str(redir->str);
	_expand_var_in_redir(redir->next);
}

void	_expand_var_in_word(t_word *word)
{
	if (word == NULL)
		return ;
	word->str = _expand_var_in_str(word->str);
	_expand_var_in_word(word->next);
}

void	expand_var(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == ND_STMT)
		return ;
	if (node->kind == ND_CMD)
	{
		_expand_var_in_word(node->cmd->word);
		_expand_var_in_redir(node->cmd->redir_in);
		_expand_var_in_redir(node->cmd->redir_out);
	}
	else
	{
		expand_var(node->lhs);
		expand_var(node->rhs);
	}
}
