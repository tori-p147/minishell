/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:27:11 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/19 19:56:30 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_error(char *cmd_name, char *arg, int status)
{
	if (status == SYNTAX_ERROR)
		printf("minishell: %s: %s: syntax error\n", cmd_name, arg);
}
