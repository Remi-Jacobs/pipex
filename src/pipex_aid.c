/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 00:32:53 by ojacobs           #+#    #+#             */
/*   Updated: 2024/08/04 12:30:26 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

static	size_t	slashsize(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			k++;
		i++;
	}
	return (i - k);
}

char	*amendstr(char *str)
{
	char	*newstr;
	int		i;
	int		k;

	i = 0;
	k = 0;
	newstr = (char *)malloc(sizeof(char) * (slashsize(str) + 1));
	if (!newstr)
		return (NULL);
	while (str[i])
	{
		while (str[i] == '\\' && str[i + 1] != '\0')
			i++;
		newstr[k] = str[i];
		i++;
		k++;
	}
	newstr[k] = '\0';
	return (newstr);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	freeppx(t_struct *ppx)
{
	if (ppx->s_path)
		free_split(ppx->s_path);
	if (ppx->s_cmd)
		free_split(ppx->s_cmd);
	if (ppx->cmd)
		free(ppx->cmd);
	if (ppx->cmdarg && ppx->cmdarg != ppx->full_cmd)
		free(ppx->cmdarg);
	if (ppx->full_cmd)
		free(ppx->full_cmd);
}
