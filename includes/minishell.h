/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:51:52 by surpetro          #+#    #+#             */
/*   Updated: 2024/10/11 15:52:02 by surpetro         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define STRING 0
# define PIPE 1 // |
# define OUTPUT_REDIRECTION 2 // >
# define INPUT_REDIRECTION 3 // <
# define APPEND_OUTPUT_REDIRECTION 4 // >>
# define HERE_DOCUMENT 5 // <<


typedef struct s_duplicate_env
{
	char					*key;
	char					*value;
	struct s_duplicate_env	*next;
} t_duplicate_env;


typedef struct s_shell
{
	char			**str;
	t_duplicate_env	*duplicate_env;
} t_shell;

typedef struct utils_s3
{
	//Suren part
	char **env;
	struct s_shell *shell;

	//Aram part
	int		new_word;
	int		in_block;
	char	*i_string;
	char	*hd_eof;
	int		hd_mode;
	
} utils_t;


/* ------------------------ functions ------------------------ */
void	pwd(utils_t *utils);
void	ft_execve(t_shell *shell, char **env);
void	ctrl_d(char *str, utils_t *utils);
char	*dollar(char *str, utils_t *utils);
int		cd(char *str, utils_t *utils);
void	echo(char **argv, utils_t *utils);
void	env_print(utils_t *utils);

/* ------------------------ functions_utils ------------------------ */
void	duplicate_env(t_shell *shell, char **env);
void	changes_old_env(t_duplicate_env **env, char *cwd);
void	changes_env(t_duplicate_env **env, char *cwd);
int		access_directory(char *s);
char	*home(t_duplicate_env *env);
int		check_directory(char *s);
void	export_f(utils_t *utils);
char	*ft_strndup(char *s1);
char	*ft_strtrim(const char *s1, const char *set);

/* ------------------------ utils ------------------------ */
int		ft_strlen(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strstr(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

/* ------------------------ jamankavor ------------------------ */
char	**ft_split(char const *s, char c);
int		ft_strcmp_space(char *s1, char *s2);




#endif
