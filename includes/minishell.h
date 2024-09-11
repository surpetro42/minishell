/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:51:52 by surpetro          #+#    #+#             */
/*   Updated: 2024/09/11 17:59:52 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

# define STRING 0
# define PIPE 1 // |
# define OUTPUT_REDIRECTION 2 // >
# define INPUT_REDIRECTION 3 // <
# define APPEND_OUTPUT_REDIRECTION 4 // >>
# define HERE_DOCUMENT 5 // <<

typedef struct s_env_list
{
	char				*key;
	int x ;
	char 				*value;
	struct s_env_list *next;
} t_env_list;


typedef struct s_arguments
{
	char 				*value;
	int 				type;
	struct s_arguments *next;
} t_arguments;

typedef struct s_shell
{
	char		*input;
	char		**str;
	char		**duplicate_env;
	t_arguments	*arguments;
	t_env_list	*env_list;
} t_shell;

/* ------------------------ functions ------------------------ */
void	ctrl_d(t_shell *utils);
void	dollar(t_shell	*shell);

/* ------------------------ utils ------------------------ */
int		ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	split_token(t_shell *shell);
int		ft_isspace(char c);
char	*ft_strdup(char *s1);
int		len_inputI(char *s);
int		len_duplicate_env(char *s);

/* ------------------------ tokenization ------------------------ */
void	token_utils(t_shell *shell);
void	tokenization(t_shell *shell);

#endif
