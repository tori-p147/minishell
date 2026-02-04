/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:39:31 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/04 19:01:05 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	*search_exists_path(char *arg0, t_tokenizer_ctx *ctx, char **path_dirs)
{
	char	*path_to_bin;
	size_t	i;

	i = -1;
	while (path_dirs[++i])
	{
		path_to_bin = ft_double_strjoin(path_dirs[i], "/", arg0);
		printf("path_to_bin = %s\n", path_to_bin);
		if (!path_to_bin)
		{
			free_array(path_dirs);
			free_ctx(ctx, EXIT_FAILURE);
		}
		if (access(path_to_bin, X_OK) == 0)
			return (path_to_bin);
		free(path_to_bin);
	}
	return (NULL);
}

char	*resolve_path(char *arg0, t_tokenizer_ctx *ctx)
{
	char	*path_to_bin;
	char	*path_env;
	char	**path_dirs;

	if (ft_strchr(arg0, '/'))
		return (arg0);
	path_env = get_value_by_key(ctx->shell->env, "PATH");
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	path_to_bin = search_exists_path(arg0, ctx, path_dirs);
	if (!path_to_bin)
	{
		free_array(path_dirs);
		return (NULL);
	}
	printf("FOUND PATH = %s\n", path_to_bin);
	free_array(path_dirs);
	return (path_to_bin);
}
