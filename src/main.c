/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:18:19 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/21 20:30:09 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

void read_input(void)
{
	char *in_line;
	char **args;
	// int status;
	
	while ((in_line = readline("Zzz> ")) != NULL)
	{
		if (ft_strlen(in_line) > 0)
		{
			add_history(in_line);
			args = parse(in_line);
			// status = execute(args);
			free(args);
		}
		free(in_line);
	}
}

int main(void)
{
	setup_signals_shell();
	read_input();
	rl_clear_history();
	return (EXIT_SUCCESS);
}
