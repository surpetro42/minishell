/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:51:41 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/15 12:10:08 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

/**********************INIT_INIT***************************/

int	init_init(t_utils *utils, char **env)
{
	utils->in_block = 0;
	utils->i_string = 0;
	utils->hd_eof = 0;
	utils->hd_mode = 0;
	utils->hd_stop = 0;
	utils->i_string = 0;
	utils->parsh_block = 0;
	utils->ok_to_cnt = 1;
	utils->last_exit_status = 0;
	utils->reading = 0;
	utils->parsh_block = 0;
	utils->shell = malloc(sizeof(t_shell));
	if (!utils->shell)
		return (1);
	utils->shell->duplicate_env = NULL;
	utils->shell->input_export = NULL;
	duplicate_env(utils->shell, env);
	utils->env = 0;
	if (env_struct_revert(utils) != 0)
		return (1);
	return (0);
}

void	handle_sigint(int sig)
{
	if (g_interrupt->reading == 1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_interrupt->last_exit_status = 1;
	}
	else if (g_interrupt->reading == 2)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		g_interrupt->hd_stop = 1;
		g_interrupt->last_exit_status = 1;
	}
	else
		write(1, "\n", 1);
	sig++;
}

void	get_string(t_utils *utils)
{
	struct termios	termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);
	utils->original_c_lflag = termios_p.c_lflag;
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	utils->reading = 1;
	utils->i_string = readline(PROMPT);
	utils->reading = 0;
	termios_p.c_lflag = utils->original_c_lflag;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	if (utils->i_string == 0)
	{
		full_clean(0, utils);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(1, "exit\n", 5);
		exit (0);
	}
	if (ft_strcmp(utils->i_string, ""))
		add_history(utils->i_string);
}

int	main(int argc, char *argv[], char *env[])
{
	t_block	*block_arr;
	t_utils	utils;

	g_interrupt = &utils;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (argc > 1)
		argv[1] = 0;
	if (init_init(&utils, env) == 1)
		return (1);
	block_arr = 0;
	while (1)
	{
		get_string(&utils);
		if (syntax_check(&utils) == 0)
			if (tokenizer(&block_arr, &utils) == 0)
				executor(block_arr, &utils);
		cleaner(&block_arr, &utils);
	}
}
