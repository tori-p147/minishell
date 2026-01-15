/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_service.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:32:00 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/15 18:29:24 by vmatsuda         ###   ########.fr       */
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
		env_set(ctx->shell, cmd->argv[i++]);
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

int	builtin_pwd(t_tokenizer_ctx *ctx)
{
	char	*cur_dir_path;
	char	**env_entry;

	env_entry = malloc(sizeof(char *) * 3);
	if (!env_entry)
		free_ctx(ctx, EXIT_FAILURE);
	cur_dir_path = getcwd(NULL, 0);
	if (!cur_dir_path)
		return (FAIL);
	env_entry[0] = ft_strdup("PWD");
	env_entry[1] = ft_strdup(cur_dir_path);
	env_entry[2] = NULL;
	add_env(ctx->shell, env_entry);
	printf("%s\n", cur_dir_path);
	free_array(env_entry);
	free(cur_dir_path);
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
	is_n = ft_strlen(cmd->argv[1]) == 2 && !(ft_strncmp(cmd->argv[1], "-n", 2));
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
