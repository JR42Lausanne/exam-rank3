/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaiti <jlaiti@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:37:09 by jlaiti            #+#    #+#             */
/*   Updated: 2023/03/08 09:07:49 by jlaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
//include <fcntl.h>
//#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_strlen(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(char *s, char c)
{
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return (1);
		s++;
	}	
	if (*s == (char)c)
		return (1);
	return (0);
}

char	*ft_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(s1);
	return (new);
}

char	*search_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	if (!buff[0])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}	
	if (buff[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*rest_line(char	*buff)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\0')
	{
		free(buff);
		return (NULL);
	}	
	rest = malloc(sizeof(char) * (ft_strlen(buff) - i + 1));
	if (!rest)
		return (NULL);
	if (buff[i] == '\n')
		i++;
	j = 0;
	while (buff[i])
	{
		rest[j] = buff[i];
		i++;
		j++;
	}
	rest[j] = '\0';
	free(buff);
	return (rest);
}

char	*read_file(int fd, char *file)
{
   	char	reader[BUFFER_SIZE + 1];
   	int		count;

	count = 1;
	while (!ft_strchr(file, '\n') && count != 0)
	{
		count = read(fd, reader, BUFFER_SIZE);
		if (count == -1)
		{
			free(file);
			return (NULL);
		}
		reader[count] = '\0';
		file = ft_join(file, reader);
	}
	return (file);
}

char	*get_next_line(int fd)
{
	static char *buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = read_file(fd, buff);
	if (!buff)
		return (NULL);
	line = search_line(buff);
	buff = rest_line(buff);
	return (line);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;

	(void) argc;
	fd = open(argv[1], O_RDONLY);
	if (fd != -1)
	{
		line = get_next_line(fd);
		while (line)
		{
			printf("%s", line);
			line = get_next_line(fd);
		}
	}
}

