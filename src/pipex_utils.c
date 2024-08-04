/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:28:49 by ojacobs           #+#    #+#             */
/*   Updated: 2024/08/04 12:31:09 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	makepath(t_struct *ppx)
{
	while (ppx->s_path[ppx->i])
	{
		ppx->cmdarg = ft_strjoin(ppx->s_path[ppx->i], "/");
		if (!ppx->cmdarg)
		{
			perror("Error joining '/' to path");
			exit(EXIT_FAILURE);
		}
		ppx->full_cmd = ft_strjoin(ppx->cmdarg, ppx->s_cmd[0]);
		free(ppx->cmdarg);
		if (!ppx->full_cmd)
		{
			perror("Error joining full path for access");
			exit(EXIT_FAILURE);
		}
		if (access(ppx->full_cmd, F_OK) == 0)
		{
			ppx->cmdarg = ppx->full_cmd;
			return ;
		}
		else
			free(ppx->full_cmd);
		ppx->i++;
	}
	ppx->full_cmd = NULL;
}

void	accesspath(t_struct *ppx, char *argv)
{
	ppx->i = 0;
	if (access(argv, F_OK) == 0)
	{
		ppx->cmdarg = ft_strdup(argv);
		ppx->s_cmd = ft_split(argv, ' ');
		return ;
	}
	setcmd(ppx, argv);
	makepath(ppx);
	if (!ppx->s_path[ppx->i])
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putstr_fd(ppx->s_cmd[0], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	pidx_assist(t_struct *ppx, char **argv, char **envp)
{
	close(ppx->fd[1]);
	dup2(ppx->fd[0], STDIN_FILENO);
	dup2(ppx->outfile, STDOUT_FILENO);
	accesspath(ppx, argv[3]);
	close(ppx->fd[0]);
	close(ppx->outfile);
	execve(ppx->cmdarg, ppx->s_cmd, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	pidx(t_struct *ppx, int n, char **argv, char **envp)
{
	if (n == 0)
	{
		if (ppx->infile < 0)
		{
			free_split(ppx->s_path);
			exit(EXIT_FAILURE);
		}
		close(ppx->fd[0]);
		dup2(ppx->infile, STDIN_FILENO);
		dup2(ppx->fd[1], STDOUT_FILENO);
		accesspath(ppx, argv[2]);
		close(ppx->infile);
		close(ppx->fd[1]);
		execve(ppx->cmdarg, ppx->s_cmd, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (n == 1)
	{
		pidx_assist(ppx, argv, envp);
	}
}
