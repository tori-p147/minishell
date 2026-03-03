/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:18:19 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/28 16:15:07 by vmatsuda         ###   ########.fr       */
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

static int	process_line(t_tokenizer_ctx *ctx)
{
	t_cmds	*cmds;

	ctx->tokens = tokenize(ctx);
	if (!ctx->tokens)
		return (0);
	if (!validate_tokens(ctx->tokens))
	{
		ctx->shell->status = SYNTAX_ERROR;
		return (0);
	}
	cmds = parse_cmd(ctx);
	if (!cmds)
		return (0);
	set_cmd_type(cmds);
	ctx->shell->status = execute(cmds, ctx);
	free_cmd(cmds);
	return (1);
}

// tokenize後にsyntax error出力してた場合の処理の追加
void	read_input(t_tokenizer_ctx *ctx)
{
	const char	*prompt;

	prompt = "Zzz> ";
	while (1)
	{
		ctx->line = readline(prompt);
		if (!ctx->line)
			break ;
		if (ft_strlen(ctx->line) == 0)
		{
			free(ctx->line);
			continue ;
		}
		add_history(ctx->line);
		if (!process_line(ctx))
			ctx->shell->status = SYNTAX_ERROR;
		free_input(ctx);
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
		env_entry = ft_split(env[i], '=');
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
