/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:18:19 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/27 18:29:14 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	init_ctx(t_tokenizer_ctx *ctx)
{
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

	ctx->line = readline(prompt);
	while ((ctx->line != NULL))
	{
		if (ft_strlen(ctx->line) > 0)
		{
			add_history(ctx->line);
			ctx->tokens = parse(ctx);
			// status = execute(ctx->tokens);
			free(ctx->tokens);
			ctx->tokens = NULL;
		}
		free(ctx->line);
		ctx->line = readline(prompt);
	}
}

int	main(void)
{
	t_tokenizer_ctx	ctx;

	setup_signals_shell();
	init_ctx(&ctx);
	read_input(&ctx);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
