/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:18:19 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/19 20:02:39 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	init_ctx(t_tokenizer_ctx *ctx, t_shell_ctx *sh_ctx)
{
	ctx->shell = sh_ctx;
	ctx->tokens = NULL;
	ctx->token = NULL;
	ctx->state = NORMAL;
	ctx->line_len = 0;
	ctx->line = NULL;
	ctx->c = 0;
}

void	read_input(t_tokenizer_ctx *ctx)
{
	const char	*prompt = "Zzz> ";
	t_cmd		*cmd;

	ctx->line = readline(prompt);
	while ((ctx->line != NULL))
	{
		if (ft_strlen(ctx->line) > 0)
		{
			add_history(ctx->line);
			ctx->tokens = tokenize(ctx);
			cmd = parse_cmd(ctx, cmd);
			printf("cmd OK\n");
			if (!cmd)
			{
				free_input(ctx);
				ctx->line = readline(prompt);
				continue ;
			}
			ctx->shell->status = execute(cmd, ctx);
			free_cmd(cmd);
			free_input(ctx);
		}
		ctx->line = readline(prompt);
	}
}

void	print_envs(t_shell_ctx *sh_ctx)
{
	t_env	*curr;

	curr = sh_ctx->env;
	while (curr)
	{
		printf("added key: %s val: %s next %p\n", curr->key, curr->value,
			curr->next);
		curr = curr->next;
	}
}

void	set_env_list(t_shell_ctx *sh_ctx, char **env)
{
	size_t	i;
	char	**env_entry;

	i = 0;
	sh_ctx->status = 0;
	env_entry = NULL;
	sh_ctx->env = NULL;
	while (env[i])
	{
		// printf("env: %s\n", env[i]);
		env_entry = ft_split(env[i], '=');
		// printf("entry k: %s val: %s\n", env_entry[0], env_entry[1]);
		set_env(sh_ctx, env_entry);
		free_array(env_entry);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell_ctx		sh_ctx;
	t_tokenizer_ctx	ctx;

	(void)argc;
	(void)argv;
	setup_signals_shell();
	set_env_list(&sh_ctx, env);
	init_ctx(&ctx, &sh_ctx);
	read_input(&ctx);
	rl_clear_history();
	free_ctx(&ctx, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
