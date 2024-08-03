/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:35:26 by ojacobs           #+#    #+#             */
/*   Updated: 2024/08/03 15:18:46 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <sys/types.h>
# include <time.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <ctype.h>
# include "./libft/libft.h"

typedef struct s_struct
{
	int		i;
	int		infile;
	int		outfile;
	int		fd[2];
	int		pid[2];
	int		pipe;
	int		status;
	char	*cmd;
	char	*full_cmd;
	char	**s_cmd;
	char	**s_path;
	char	*cmdarg;
}	t_struct;

void	pipeinit(t_struct *ppx, int argc, char **argv);
void	setcmd(t_struct *ppx, char *argv);
void	setpath(t_struct *ppx, char **envp);
void	makepath(t_struct *ppx);
void	accesspath(t_struct *ppx, char *argv);
void	pidx(t_struct *ppx, int n, char **argv, char **envp);
void	freeppx(t_struct *ppx);
char	**split_argument(char *str);
char	*amendstr(char *str);
int		check_quote(char *str);

#endif