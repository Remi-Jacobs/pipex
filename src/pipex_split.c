/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:56:59 by ojacobs           #+#    #+#             */
/*   Updated: 2024/08/02 23:18:21 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	*extract_quoted_substring(char **str, char quote)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;

	start = *str + 1;
	end = start;
	while (*end && (*end != quote || (*(end - 1) == '\\' && *end == quote)))
		end++;
	len = end - start;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, start, len);
	result[len] = '\0';
	*str = end + 1;
	result = amendstr(result);
	return (result);
}

static void	add_token(char ***result, int *count, int *size, char *token)
{
	char	**new_result;
	int		i;

	if (*count >= *size)
	{
		*size *= 2;
		new_result = (char **)ft_calloc(*size, sizeof(char *));
		if (!new_result)
			return ;
		i = 0;
		while (i < *count)
		{
			new_result[i] = (*result)[i];
			i++;
		}
		free(*result);
		*result = new_result;
	}
	(*result)[*count] = ft_strdup(token);
	(*count)++;
}

void	process_non_quoted(char **arg, char ***result, int *count, int *size)
{
	char	*token;

	token = *arg;
	while (**arg && **arg != ' ' && **arg != '"' && **arg != '\'')
		(*arg)++;
	if (**arg)
		**arg = '\0';
	(*arg)++;
	add_token(result, count, size, token);
}

static void	process_argument(char *arg, char ***result, int *count, int *size)
{
	char	*quoted_str;

	while (*arg)
	{
		if (*arg == ' ')
		{
			arg++;
			continue ;
		}
		if (*arg == '"' || *arg == '\'')
		{
			quoted_str = extract_quoted_substring(&arg, *arg);
			add_token(result, count, size, quoted_str);
			free(quoted_str);
		}
		else
		{
			process_non_quoted(&arg, result, count, size);
		}
	}
}

char	**split_argument(char *str)
{
	int		count;
	int		size;
	char	**result;

	count = 0;
	size = 4;
	result = (char **)ft_calloc(size, sizeof(char *));
	if (!result)
		return (NULL);
	process_argument(str, &result, &count, &size);
	result[count] = NULL;
	return (result);
}
