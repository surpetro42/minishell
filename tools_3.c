/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 12:54:44 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/15 12:55:04 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	my_perror(char *prefix, char *suffix)
{
	char	*error_message;

	error_message = strerror(errno);
	if (prefix)
		write(2, prefix, ft_strlen(prefix));
	write(2, ": ", 2);
	write(2, error_message, ft_strlen(error_message));
	write(2, " ", 1);
	if (suffix)
		write(2, suffix, ft_strlen(suffix));
	write(2, "\n", 1);
}

int	is_not_special(char ch)
{
	if (ch != ' ' && ch != '(' && ch != ')' && \
			ch != '<' && ch != '>' && ch != '|' && ch != '&')
		return (1);
	else
		return (0);
}

int	count_words(char *str, int i)
{
	int		result;
	char	temp;

	result = 1;
	while ((str[i] && is_not_special(str[i])) || str[i] == ' ')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			temp = str[i++];
			while (str[i] && str[i] != temp)
				i++;
		}
		else
			if (str[i] == ' ' && is_not_special(str[i + 1]))
				result++;
		i++;
	}
	return (result);
}

int	check_first_dot(char *w_str, char *fname)
{
	if (fname[0] == '.' && w_str[0] != '.')
		return (0);
	else
		return (1);
}

char	*hd_getstring(t_utils *utils)
{
	struct termios	termios_p;
	char			*result;

	tcgetattr(STDIN_FILENO, &termios_p);
	utils->original_c_lflag = termios_p.c_lflag;
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	utils->reading = 2;
	result = readline(">");
	utils->reading = 0;
	termios_p.c_lflag = utils->original_c_lflag;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	return (result);
}
