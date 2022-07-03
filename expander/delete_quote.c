/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:15:04 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 15:52:53 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*_delete_quote_in_str(char *str)
{
	char	*new;
	bool	single_quote;
	bool	double_quote;
	long	i;

	new = ft_xstrdup("");
	single_quote = false;
	double_quote = false;
	i = 0;
	while (str[i])
	{
		if (!single_quote && !double_quote && str[i] == '"')
			double_quote = true;
		else if (!single_quote && !double_quote && str[i] == '\'')
			single_quote = true;
		else if (double_quote && str[i] == '"')
			double_quote = false;
		else if (single_quote && str[i] == '\'')
			single_quote = false;
		else
			new = ft_str_add_char(new, str[i]);
		i++;
	}
	free(str);
	return (new);
}

void	_delete_quote_in_redir(t_redir *redir)
{
	if (redir == NULL)
		return ;
	redir->str = _delete_quote_in_str(redir->str);
	_delete_quote_in_redir(redir->next);
}

void	_delete_quote_in_word(t_word *word)
{
	if (word == NULL)
		return ;
	if (!word->dont_expand)
		word->str = _delete_quote_in_str(word->str);
	_delete_quote_in_word(word->next);
}

void	delete_quote(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == ND_STMT)
		return ;
	if (node->kind == ND_CMD)
	{
		_delete_quote_in_word(node->cmd->word);
		_delete_quote_in_redir(node->cmd->redir_in);
		_delete_quote_in_redir(node->cmd->redir_out);
	}
	else
	{
		delete_quote(node->lhs);
		delete_quote(node->rhs);
	}
}

void	delete_quote_in_heredoc(t_redir *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == RD_HEREDOC)
		redir->str = _delete_quote_in_str(redir->str);
	delete_quote_in_heredoc(redir->next);
}
