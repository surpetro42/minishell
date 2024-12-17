/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:52:25 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/11 15:57:34 by ayeganya         ###   ########.fr       */
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
# include <limits.h>
# include "libft/libft.h"
# include <sys/ioctl.h>

/***********CONSTANTS DEFINITION***********/
# define PROMPT "\001\033[38;5;43m\002minishell: \001\033[0;000m\002"
# define PRNTHS_ERROR \
	"Parenthesis error: Please make sure you are using parenthesis correctly.\n"
# define QTS_ERROR \
	"Quotes error: Please make sure you are using quotes correctly.\n"

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
	int				type;
	int				input_fd;
	int				output_fd;
	int				tmp_pipe_input_fd;
	int				next_logic_elem;
	int				exit_status;

	//for EXEC type
	char			**exec_argv;

	//for SUBSH type
	struct block_s	*subsh_block_arr;
	struct block_s	**parsh_block;

	//for list functionality
	struct block_s	*next;
	struct block_s	*prev;
	int				index;
}	t_block;

typedef struct utils_s
{
	//Suren part
	char			**env;
	struct s_shell	*shell;

	//Aram part
	//**tokenizer temp variables
	int				in_block;
	char			*i_string;
	char			*hd_eof;
	int				hd_stop;
	int				hd_mode;
	int				ok_to_cnt;
	int				last_exit_status;
	int				reading;
	tcflag_t		original_c_lflag;
	t_block			**parsh_block;

}	t_utils;

/*******GLOBAL_VARIABLE*******/
t_utils	*g_interrupt;

typedef struct file_list_s
{
	char				filename[NAME_MAX];
	struct file_list_s	*next;
}	t_file_list;

typedef struct dfs_s
{
	char	*src;
	char	*dst;
	int		i;
}	t_dfs;

char			*dollar_func(char *str, t_utils *utils);
int				cd(char *str, t_utils *utils);
void			echo(char **argv, t_utils *utils);
void			pwd(t_utils *utils);
//int		export_f(t_utils *utils);

void			extract_the_phrase(char *dst, char *src, int *index);
void			space_processor(int *index, char *str);
int				next_block_creator(t_block **block_arr, t_utils *utils);
t_block			*last_block(t_block *block_arr);
void			block_init(t_block *block);
void			restore_hidden_dollar(char *str);
int				is_not_special(char ch);
int				count_phrase_size(char *str, int i);
int				status_decoder(int status);
int				executor(t_block *block, t_utils *utils);
int				regular_subshell(t_block *block, t_utils *utils);
int				pipe_exec(t_block **block, t_utils *utils);
void			clean_argv_memory(char **argv);
int				is_builtin(char *exec);
int				run_builtin(t_block *block, t_utils *utils);
//This function cleans token's structure after the line execution
void			cleaner(t_block **block_arr, t_utils *utils);
//This function should be called before exit to clean up all resources
void			full_clean(t_block *block_arr, t_utils *utils);
int				my_exit(t_block *block, t_utils *utils);
void			block_arr_cleaner(t_block *p_block);
void			clean_all_fd(t_block *block);
int				syntax_check(t_utils *utils);
void			my_perror(char *prefix, char *suffix);
int				argv_wildcard_processor(t_block *block);
int				argv_replace(char ***p_argv, int i, t_file_list *file_list, \
		int match_nbr);
void			file_list_clean(t_file_list *file_list);
void			filename_creator(char *filename, int number);
int				h_doc_processor(int *index, t_block **p_block_arr, t_utils \
		*utils);
int				s_output_processor(int *index, t_block **p_block_arr, t_utils \
		*utils, int mode);
int				s_input_processor(int *index, t_block **p_block_arr, t_utils \
		*utils);
int				command_processor(int *index, t_block **p_block_arr, \
		t_utils *utils);
int				logical_and_processor(int *index, t_block **p_block_arr, \
		t_utils *utils);
int				logical_or_processor(int *index, t_block **p_block_arr, \
		t_utils *utils);
int				pipe_processor(int *index, t_block **p_block_arr, \
		t_utils *utils);
int				parenthesis_open(int *index, t_block ***p_p_block_arr, \
		t_utils *utils);
int				parenthesis_close(int *index, t_block ***p_p_block_arr, \
		t_utils *utils);
int				tokenizer(t_block **p_block_arr, t_utils *utils);
char			*exec_compose(char *argv0, t_utils *utils);
int				builtin_fd_chng(int *fd, t_block *block);
int				builtin_fd_revert(int *fd);
void			exit_status_processing(t_block *block, t_utils *utils);
int				regular_exec(t_block *block, t_utils *utils);
int				env_struct_revert(t_utils *utils);
int				ex_status_value(t_utils *utils, char **value);
int				find_the_value(t_utils *utils, char **value, char *key);
int				extract_key(t_dfs *dfs, char **key);
int				count_the_key_size(t_dfs *dfs);
void			extract_the_phrase_2(char *dst, char *src, int *index);
int				count_words(char *str, int i);
int				check_first_dot(char *w_str, char *fname);
char			*hd_getstring(t_utils *utils);
void			regular_exec_initial_checks_2(t_block *block, t_utils *utils);
void			close_block_fd(t_block *block);

typedef struct s_export
{
	char					*key;
	char					*value;
	int						type;
	struct s_export			*next;
}	t_export;

typedef struct s_duplicate_env
{
	char					*key;
	char					*value;
	int						type;
	struct s_duplicate_env	*next;
}	t_duplicate_env;

typedef struct s_var_export
{
	t_duplicate_env	*new_node;
	int				findel;
	int				len_equally;
	char			*buff_key;
	char			*buff_vlaue;

}	t_var_export;

typedef struct s_var_dollar
{
	char	*s1_before;
	char	*s2_key;
	char	*s3_after;
	char	*res_line_key;
	char	*res_1;
	char	*buff;
	char	*res_buff;
	char	*line;
	char	*res_line;
	char	*res_line_remains;
	char	*open_exit_status;

}	t_var_dollar;

typedef struct s_shell
{
	char			**str;
	t_duplicate_env	*duplicate_env;
	t_export		*input_export;
	t_var_export	*var;
}	t_shell;

/* ------------------------ functions ------------------------ */
void			pwd(t_utils *utils);
void			ft_execve(t_shell *shell, char **env);
void			ctrl_d(char *str, t_utils *utils);
char			*dollar(char *str, t_utils *utils);
int				cd(char *str, t_utils *utils);
void			echo(char **argv, t_utils *utils);
void			env_print(t_utils *utils);
int				export_f(t_utils *utils, char **str);
int				unset_f(t_utils *utils, char **str);

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

//				dollar
				//utils_dollar_0
char			*ft_strndup(char *s1);
int				dollar_validation(char *s);
void			initialization(t_var_dollar *var);
int				len_remaining(char *str);
char			*remaining_after(char *str);
				//utils_dollar_1
char			*before_dollar(char *str);
char			*key(char *str);
char			*after(char *str);
				//utils_dollar_2
char			*variable(char *str);
char			*remains(char *key);
int				valid_remains_line(char *str);
int				search_for_a_negative_character(char *s);
char			*development_s3_atfer(char *str);
				//utils_dollar_3
int				key_search_env(t_duplicate_env duplicate_env, t_var_dollar \
		*var);
void			env_list_key_search(t_duplicate_env **duplicate_env, \
		t_var_dollar *var);
int				take_key(char *key, t_var_dollar *var);
				//utils_dollar_4
void			doll_key_after(t_var_dollar *var, char *str);
void			doll_before_key_after(t_var_dollar *var, char *str);
char			*share_dollar_input(t_var_dollar *var, char *str);
char			*opn_ext_sts(int last_exit_status);
				//utils_dollar_5
int				search_symbol_dollar(char *str, int l);
int				find_remains_end(char *key, int i);

//			export
void			new_nudd_list(t_var_export *var, int len_equally);
int				validation_equal_variable(char *s);
int				validation_symble_variable(char *s);
int				find_equal(char *s);
int				find_before_equal(char *s);
int				checking_existence_variable(t_duplicate_env *env, \
		char *buff_key, char *buff_vlaue, int exists);
void			print_export_list(t_utils *utils);
void			add_enviorment(t_shell *shell);
int				ft_env_elem_size(t_export *begin_list);
t_export		*ft_env_elem_at(t_export *begin_list, unsigned int nbr);
t_export		*ft_merge_sorted_list(t_export *left, t_export *right, \
		int (*cmp)());
t_export		*merge_sort(t_export *begin_list, int (*cmp)());
void			ft_env_elem_sort(t_export **begin_list, int (*cmp)());
t_duplicate_env	*create_new_node(char *key, char *value, int type);
int				process_string(char *str, t_var_export *var);
void			add_to_list(t_duplicate_env **env, \
		t_duplicate_env **last, t_duplicate_env *node);
void			handle_logic(t_var_export *var, t_duplicate_env **env, \
		t_duplicate_env **last);
int				arr_string_element(char *str, t_duplicate_env **env, \
		t_duplicate_env **last, t_var_export *var);

//			cd
int				minus_oldpwd(t_utils *utils, char *cwd, char *str);
int				tilda_oldpwd(t_duplicate_env *env, char *cwd, char *str);
int				other(t_duplicate_env *env, char *cwd, char *str, char *s);

//			exit
void			final_block_arr_cleaner(t_block *block);

/* ------------------------ free_builtins ------------------------ */

//				free_dollar
void			free_dollar(t_var_dollar var);

//				free_export
void			free_export(t_var_export var);

//				free_exp_env_list
void			free_env_list(t_duplicate_env *list);
void			free_exp_list(t_export *list);

#endif
