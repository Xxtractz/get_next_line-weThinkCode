/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:51:47 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/09 10:31:31 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char      *read_line(int f, int fd, char *buff, char *temp)
{
    int i;
    
	i = 0;
	while (f > 0)
	{
		if (buff[i] == '\n'){
			break;

		}
		else if (i == BUFF_SIZE)
		{
			f = read(fd, buff, BUFF_SIZE);
			if (f == 0)
				return ((char *)LINE_NOT_FOUND);
			temp = ft_strjoin(temp, buff);
			i = -1;
		}
		i++;
	}
    return (temp);
}

static char			*check_static(t_var var, char *new, char *line)
{
	int s;
	int i;

	s = 0;
	i = 0;
	new = ft_memalloc(sizeof(char) * (var.j + 1));
	if (!new)
		return ((char *)INVALID);
	s = ft_strlen(var.temp) - var.j;
    //w = var.j;
	while (var.temp[s] != '\0')
	{
		new[i] = var.temp[s];
		if (var.temp[s] == '\n')
		{
			if (!(line = ft_memalloc(sizeof(char) * (i + 1))))
 				return ((char *)INVALID);
			line = ft_strncpy(line, new, i);
			var.j--;
			return ((char *)LINE_FOUND);
		}
		s++;
		var.j--;
		i++;
	}
	var.temp = ft_strdup(new);
	return (var.temp);
}

int					get_next_line(const int fd, char **line)
{
	static t_var var;
	char buff[BUFF_SIZE + 1];
	char *new;
	int i;
 	int f = 0;
	int s = 0;
    int w = 0;
    i = 0;

    if (fd <  0 || line == NULL)
        return (INVALID);
    ft_bzero(buff, BUFF_SIZE + 1);
	if (var.j > 0)
	{
		w = var.j;
/*		new = ft_memalloc(sizeof(char) * (var.j + 1));
	    if (!new)
            return (INVALID);
		s = ft_strlen(var.temp) - var.j;
		f = s;
        w = var.j;
		while (var.temp[s] != '\0')
		{
			new[i] = var.temp[s];
			if (var.temp[s] == '\n')
			{
				if(!(*line = ft_memalloc(sizeof(char) * (i + 1))))
                    return (INVALID);
				*line = ft_strncpy(*line, new, i);
				var.j--;
				return (LINE_FOUND);
			}
			s++;
			var.j--;
			i++;
		}
		//s = f;
        var.temp = ft_strdup(new);*/
	if((var.temp = check_static(var, new, *line)) == (char *)LINE_FOUND)//function call
		return (1);

	}//first read after this loop
    if (w == 0)
	    var.temp = ft_strnew(BUFF_SIZE);
	f = read(fd, buff, BUFF_SIZE);
	if (f == 0)
		return (LINE_NOT_FOUND);
	var.temp = ft_strjoin(var.temp, buff);
    if (!(var.temp = read_line(f, fd, buff, var.temp)))//function call
		return (0);
	s = 0;
	if (var.temp[s])
	{
		while (var.temp[s] != '\n')
			s++;
	}
	s++;
	if(var.j == 0)
		*line = (char *)malloc(sizeof(char) * (s + 1));
	*line = ft_strncat(*line, var.temp, s - 1);
	var.j = ft_strlen(var.temp) - s;
	return (1);
}

#include <stdio.h>
#include <fcntl.h>
/*int main()
{
	char *txt;
	int i;
	int x = 1;
	int j = 0;
	
	i = open("file.txt", O_RDONLY);
	while (j < 12)
	{
		x = get_next_line(i, &txt);
        printf("%s\n", txt);
        j++;
	}
   // free(txt);
	return (0);
}*/
int     main(int argc, char **argv)
{
	int     fd;
	char    *line;
	int     x = 1;
 
     if (argc > 1)
     {
     	fd = open(argv[1], O_RDONLY);
     	while (x == 1)
     	{
        	 x = get_next_line(fd, &line);
        	printf("%s\n", line);
     	}
     	close(fd);
     }
     return (0);
 }
