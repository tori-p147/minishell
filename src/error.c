/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:27:11 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/09 13:16:01 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_error(char *cmd_name, char *arg, int status)
{
	if (status == SYNTAX_ERROR)
		printf("minishell: %s: %s: syntax error\n", cmd_name, arg);
}
