/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:48:09 by ojacobs           #+#    #+#             */
/*   Updated: 2024/08/04 12:36:10 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	closeppx(t_struct *ppx)
{
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	if (ppx->infile > -1)
		close(ppx->infile);
	close(ppx->outfile);
}

void	initialize(t_struct *ppx, int argc, char **argv, char **envp)
{
	*ppx = (t_struct){0};
	pipeinit(ppx, argc, argv);
	setpath(ppx, envp);
}

void	fork_processes(t_struct *ppx, char **argv, char **envp)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		ppx->pid[i] = fork();
		if (ppx->pid[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (ppx->pid[i] == 0)
			pidx(ppx, i, argv, envp);
	}
}

void	wait_for_processes(t_struct *ppx)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		waitpid(ppx->pid[i], &ppx->status, 0);
		if (WIFEXITED(ppx->status) && WEXITSTATUS(ppx->status) != 0)
		{
			freeppx(ppx);
			exit(WEXITSTATUS(ppx->status));
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	ppx;

	initialize(&ppx, argc, argv, envp);
	fork_processes(&ppx, argv, envp);
	closeppx(&ppx);
	wait_for_processes(&ppx);
	freeppx(&ppx);
	return (0);
}
