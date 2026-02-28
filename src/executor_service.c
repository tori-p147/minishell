/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_service.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:32:00 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/28 15:20:15 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int	builtin_export(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	size_t	i;

	if (!is_export_valid(cmd))
		return (FAIL);
	i = 1;
	while (cmd->argv[i])
		add_or_update_env(ctx->shell, cmd->argv[i++]);
	return (SUCCESS);
}

int	builtin_unset(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	size_t	i;

	i = 1;
	while (cmd->argv[i])
		env_unset(ctx->shell, cmd->argv[i++]);
	return (SUCCESS);
}

int	builtin_exit(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	size_t	i;

	if (!cmd->argv[1])
	{
		printf("exit\n");
		free_ctx(ctx, SUCCESS);
		return (SUCCESS);
	}
	else
	{
		i = -1;
		while (++i < ft_strlen(cmd->argv[1]))
		{
			if (!ft_isdigit((int)cmd->argv[1][i]))
			{
				print_error(cmd->argv[0], cmd->argv[1], SYNTAX_ERROR);
				free_ctx(ctx, SYNTAX_ERROR);
				return (SYNTAX_ERROR);
			}
		}
	}
	printf("exit\n");
	free_ctx(ctx, ft_atoi(cmd->argv[1]));
	return (ft_atoi(cmd->argv[1]));
}

int	builtin_echo(t_cmd *cmd)
{
	size_t	i;
	bool	is_n;

	is_n = false;
	i = 0;
	is_n = !(ft_strcmp(cmd->argv[1], "-n"));
	if (is_n)
		i = 1;
	while (cmd->argv[++i])
	{
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write(1, " ", 1);
	}
	if (!(is_n))
		write(1, "\n", 1);
	return (SUCCESS);
}

int	builtin_env(t_tokenizer_ctx *ctx)
{
	size_t	i;
	t_env	*curr;

	i = -1;
	curr = ctx->shell->env;
	while (curr)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	return (0);
}
