/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_innit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:28:40 by ojacobs           #+#    #+#             */
/*   Updated: 2024/08/03 15:19:12 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	pipeinit(t_struct *ppx, int argc, char **argv)
{
	if (argc == 5)
	{
		ppx->outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
		ppx->infile = open(argv[1], O_RDONLY);
		if (ppx->infile == -1)
		{
			perror("Error");
		}
		if (ppx->outfile == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		if (pipe(ppx->fd) == -1)
		{
			perror("Error opening pipe");
			exit(1);
		}
	}
	else
	{
		ft_putstr_fd("Invalid number of arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	setcmd(t_struct *ppx, char *argv)
{
	ppx->cmd = ft_strdup(argv);
	if (!ppx->cmd)
	{
		perror("Error with ft_strdup");
		exit(EXIT_FAILURE);
	}
	if (check_quote(argv) > 0)
		ppx->s_cmd = split_argument(argv);
	else
		ppx->s_cmd = ft_split(argv, ' ');
	if (!ppx->s_cmd)
	{
		perror("Error splitting s_cmd");
		exit(EXIT_FAILURE);
	}
}

void	setpath(t_struct *ppx, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] && ft_strncmp(envp[i], "PATH=", 5) == 0)
	{
		ppx->s_path = ft_split(&envp[i][5], ':');
		if (!ppx->s_path)
		{
			perror("Error splitting envp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		perror("Could not find PATH");
		exit(EXIT_FAILURE);
	}
}
