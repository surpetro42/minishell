/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:52:25 by ayeganya          #+#    #+#             */
/*   Updated: 2024/11/24 21:22:45 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

/***********HEADER INCLUDES***********/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <termios.h>
# include <term.h>
# include "libft/libft.h"
//# include "builtins_minishel/includes/minishell.h"


/***********CONSTANTS DEFINITION***********/
# define PROMPT "\033[38;5;43mminishell: \033[0;000m"
# define PRNTHS_ERROR "Parenthesis error: Please make sure you are using parenthesis correctly.\n"
# define QTS_ERROR "Quotes error: Please make sure you are using quotes correctly.\n"
//# define MAX_ERROR_LNGT 500

/*******BLOCK TYPES*******/
# define EXEC 1
# define SUBSH 2

/*******LOGICAL ELEMENTS*******/
# define AND_AND	1
# define OR_OR		2
# define MY_PIPE 	3

/***********STRUCTURES***********/
typedef struct block_s
{
	int	type;
	int	input_fd;
	int	output_fd;
	int output_mode;
	int	next_logic_elem;
	int exit_status;

	//for EXEC type
	char	**exec_argv;

	//for SUBSH type
	struct block_s	*subsh_block_arr;
	//struct block_s	*parsh_block_arr;
	struct block_s	**parsh_block;


	//for PIPE type
	//char	**exec_arr;

	//for list functionality
	struct block_s	*next;
	struct block_s	*prev;
	int				index;
} block_t;

/*typedef struct token_s
{
	char
}*/

typedef struct utils_s
{
	//Suren part
	char **env;
	struct s_shell *shell;

	//Aram part
	//**tokenizer temp variables
	int		new_word;
	int		in_block;
	char	*i_string;
	char	*hd_eof;
	int		hd_mode;
	int		ok_to_cnt;
	int		last_exit_status;
	block_t	**parsh_block;
	
} utils_t;


char	*dollar_func(char *str, utils_t *utils);
int		cd(char *str, utils_t *utils);
void	echo(char **argv, utils_t *utils);
void	pwd(utils_t *utils);
//int		export_f(utils_t *utils);

void	extract_the_phrase(char *dst, char *src, int *index);
int		space_processor(int *index, char *str);
int		next_block_creator(block_t **block_arr, utils_t *utils);
block_t	*last_block(block_t *block_arr);
void	block_init(block_t *block);
void	restore_hidden_dollar(char *str);
int		is_not_special(char ch);
int		count_phrase_size(char *str, int i);
int		status_decoder(int status);
int 	executor(block_t *block, utils_t *utils);
//This function cleans token's structure after the line execution
void	cleaner(block_t **block_arr, utils_t *utils);

//This function should be called before exit to clean up all resources
void	full_clean(block_t *block_arr, utils_t *utils);

# define STRING 0
# define PIPE 1 // |
# define OUTPUT_REDIRECTION 2 // >
# define INPUT_REDIRECTION 3 // <
# define APPEND_OUTPUT_REDIRECTION 4 // >>
# define HERE_DOCUMENT 5 // <<

typedef struct s_export
{
	char					*key;
	char					*value;
	int						type;
	struct s_export	*next;
} t_export;

typedef struct s_duplicate_env
{
	char					*key;
	char					*value;
	int						type;
	struct s_duplicate_env	*next;
} t_duplicate_env;

typedef struct s_var_export
{
	t_duplicate_env	*new_node;
	int				findel;
	int				len_equally;
	char			*buff_key;
	char			*buff_vlaue;

} t_var_export;

typedef struct s_var_dollar
{
	char	*s1_before;
	char	*s2_key;
	char	*s3_after;
	char	*res_line_key;
	char	*res_1;
	char	*buff;
	
} t_var_dollar;

typedef struct s_shell

{
	char			**str;
	t_duplicate_env	*duplicate_env;
	t_export		*input_export;
	t_var_export	*var;
} t_shell;

/* ------------------------ functions ------------------------ */
void	pwd(utils_t *utils);
void	ft_execve(t_shell *shell, char **env);
void	ctrl_d(char *str, utils_t *utils);
char	*dollar(char *str, utils_t *utils);
int		cd(char *str, utils_t *utils);
void	echo(char **argv, utils_t *utils);
void	env_print(utils_t *utils);
void	export_f(utils_t *utils, char **str);
void	unset_f(utils_t *utils, char **str);

/* ------------------------ functions_utils ------------------------ */
void			duplicate_env(t_shell *shell, char **env);
void			changes_old_env(t_duplicate_env **env, char *cwd);
void			changes_env(t_duplicate_env **env, char *cwd);
int				access_directory(char *s);
char			*home(t_duplicate_env *env);
int				check_directory(char *s);
char			*ft_strtrim(const char *s1, const char *set);
int				find(char *s);
char			**ft_split_export(char const *s, char c);
char			**ft_split(char const *s, char c);
char			*old_environment(t_duplicate_env *env);


//			dollar
				//utils_dollar_0
char			*ft_strndup(char *s1);
int				dollar_validation(char *s);
char			*completion_status(char *str, int last_exit_status);
				//utils_dollar_1
char			*before_dollar(char *str);
char			*key(char *str);
char			*after(char *str);

				//utils_dollar_2
char			*variable(char *str);
char			*remains(char *key);
int				valid_remains_line(char *str);

//			export
int				validation_equal_variable(char *s);
int				validation_symble_variable(char *s);
int				find_equal(char *s);
int				find_before_equal(char *s);
int				checking_existence_variable(t_duplicate_env *env, char *buff_key, char *buff_vlaue);
void			print_export_list(utils_t *utils);
void			add_enviorment(t_shell *shell);
int				ft_env_elem_size(t_export *begin_list);
t_export		*ft_env_elem_at(t_export *begin_list, unsigned int nbr);
t_export		*ft_merge_sorted_list(t_export *left, t_export *right, int (*cmp)());
t_export		*merge_sort(t_export *begin_list, int (*cmp)());
void			ft_env_elem_sort(t_export **begin_list, int (*cmp)());
t_duplicate_env	*create_new_node(char *key, char *value, int type);
int				process_string(char *str, t_var_export *var);
void			add_to_list(t_duplicate_env **env,
	t_duplicate_env **last, t_duplicate_env *node);
void			handle_logic(t_var_export *var, t_duplicate_env **env,
	t_duplicate_env **last);
void			arr_string_element(char *str, t_duplicate_env **env,
	t_duplicate_env **last);




	
/* ------------------------ free_builtins ------------------------ */
// void			free_dollar(t_var_dollar var);


#endif
