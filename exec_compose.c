/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_compose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:50:32 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/15 12:08:34 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	exec_compose_cleanup(char **paths, char *exec)
{
	int	j;

	j = 0;
	if (exec != 0)
		free(exec);
	while (paths[j])
		free(paths[j++]);
	free(paths);
}

char	*check_and_return_exec(char *exec, t_utils *utils)
{
	struct stat	path_stat;

	if (access(exec, F_OK) != 0)
	{
		utils->last_exit_status = 127;
		return (my_perror("minishell", exec), free(exec), (char *)0);
	}
	if (stat(exec, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		utils->last_exit_status = 126;
		return (write(2, "minishell: ", 11), write(2, exec, ft_strlen(exec)), \
				write(2, " is a directory\n", 16), free(exec), (char *)0);
	}
	if (access(exec, X_OK) != 0)
	{
		utils->last_exit_status = 126;
		return (my_perror("minishell", exec), free(exec), (char *)0);
	}
	return (exec);
}

char	*exec_compose2(char *exec, char **paths, t_utils *utils)
{
	int		i;
	char	*temp;
	char	*result;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i++], "/");
		if (temp == 0)
			return (exec_compose_cleanup(paths, exec), (char *)0);
		result = ft_strjoin(temp, exec);
		free(temp);
		if (result == 0)
			return (exec_compose_cleanup(paths, exec), (char *)0);
		if (access(result, F_OK) == 0)
			return (exec_compose_cleanup(paths, exec), \
					check_and_return_exec(result, utils));
		free(result);
	}
	utils->last_exit_status = 127;
	return (write(2, "minishell: ", 11), write(2, exec, ft_strlen(exec)), \
			write(2, " command not found\n", 19), free(exec), \
			exec_compose_cleanup(paths, 0), (char *)0);
}

void	print_error_if_needed(t_utils *utils)
{
	int	i;

	i = 0;
	space_processor(&i, utils->i_string);
	if (utils->i_string[i] == '"' || utils->i_string[i] == '\'')
	{
		write(2, "minishell: : command not found\n", 31);
		utils->last_exit_status = 1;
	}
	else
		utils->last_exit_status = 0;
}

char	*exec_compose(char *argv0, t_utils *utils)
{
	int		i;
	char	**paths;
	char	*exec;
	char	**env;

	if (argv0[0] == 0)
		return (print_error_if_needed(utils), (char *)0);
	i = 0;
	env = utils->env;
	exec = (char *)malloc(sizeof(char) * (ft_strlen(argv0) + 1));
	if (exec == 0)
		return (0);
	ft_strlcpy(exec, argv0, ft_strlen(argv0) + 1);
	if (is_builtin(exec))
		return (exec);
	if (ft_strchr(exec, (int) '/'))
		return (check_and_return_exec(exec, utils));
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i] == 0)
		return (check_and_return_exec(exec, utils));
	paths = ft_split(&(env[i][5]), ':');
	if (paths == 0)
		return (free (exec), (char *)0);
	return (exec_compose2(exec, paths, utils));
}
