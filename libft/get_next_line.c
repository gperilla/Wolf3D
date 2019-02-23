/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 10:19:22 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/11 14:57:00 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int	check_endline(char *str, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		if (str[i] == '\0' || str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	check_str(char *str, int i, char **line)
{
	int j;

	if (str[i] == '\0')
		j = i;
	else
		j = i + 1;
	str[i] = '\0';
	if (!(*line = ft_strdup(str)))
		return (-1);
	str = ft_strcpy(str, str + j);
	if (i == j)
		str[0] = '\0';
	return (1);
}

static int	found_endl(char **str, char *buff, int i, char **line)
{
	if (!(*str = ft_strjoin_free(*str, buff, 1)))
		return (-1);
	i = check_endline(*str, ft_strlen(*str));
	return (check_str(*str, i, line));
}

static int	read_loop(int fd, char **str, char *buff, char **line)
{
	int i;

	while ((i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if ((i = check_endline(buff, i)) < 0)
			*str = ft_strjoin_free(*str, buff, 1);
		else
			return (found_endl(str, buff, i, line));
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	return (i);
}

int			get_next_line(const int fd, char **line)
{
	int			i;
	static char	*str;
	char		*buff;

	if (str == NULL)
		if (!(str = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
	if ((i = check_endline(str, ft_strlen(str))) >= 0)
		return (check_str(str, i, line));
	if (!(buff = malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	ft_bzero(buff, BUFF_SIZE + 1);
	if ((i = read_loop(fd, &str, buff, line)) > 0)
	{
		free(buff);
		return (i);
	}
	free(buff);
	if (str[0] != '\0')
		return (check_str(str, ft_strlen(str), line));
	if (i == 0)
		return (0);
	return (-1);
}
