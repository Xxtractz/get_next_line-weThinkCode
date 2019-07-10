/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaloyi <mbaloyi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:51:47 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/10 14:52:03 by mbaloyi          ###   ########.fr       */
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
			{
				if (BUFF_SIZE == 1)
					return (temp);		
				return ((char *)LINE_NOT_FOUND);
			}
			temp = ft_strjoin(temp, buff);
			i = -1;
		}
		i++;
	}
    return (temp);
}

int		check(char **line, char *new, int i, t_var var){
	if(!(*line = ft_memalloc(sizeof(char) * (i + 1))))
        return (INVALID);
	*line = ft_strncpy(*line, new, i);
	return (LINE_FOUND);
}


int			get_next_line(const int fd, char **line)
{
	static t_var var; // This is struct contains "j - keeps track of values in temp", "temp - *char from the buff "
	char buff[BUFF_SIZE + 1]; // Allocation of  a fixed string to buff size 
	char *new; // stores everything from temp after finding a new line
	int i; // counter for *new  
	int s ;  // iters through var.temp
	 
    i = 0; 
    if (fd <  0 || line == NULL)
        return (INVALID);
    ft_bzero(buff, BUFF_SIZE + 1);
	if (var.j > 0)
	{
	    if (!(new = ft_memalloc(sizeof(char) * (var.j + 1))))
            return (INVALID);	
		while (var.temp[(s = ft_strlen(var.temp) - var.j)] != '\0' )
		{
			new[i] = var.temp[s];
			if (var.temp[s++] == '\n')
			{
				var.j--;
				return check(line,new,i,var);
			}
			i++;
			var.j--;
		}
        var.temp = ft_strdup(new);
	}
    if (i == 0)
	    var.temp = ft_strnew(BUFF_SIZE);;
	if ((i = read(fd, buff, BUFF_SIZE)) == 0)
		return (LINE_NOT_FOUND);
	var.temp = ft_strjoin(var.temp, buff);
    var.temp = read_line(i, fd, buff, var.temp);
	if (var.temp == (char *)LINE_NOT_FOUND)
		return (0);
	s = 0;
	if (var.temp[s])
		while (var.temp[s] != '\n')
			s++;
	s++;
	if(var.j == 0)
		*line = (char *)malloc(sizeof(char) * (s + 1));
	*line = ft_strncat(*line, var.temp, s - 1);
	var.j = ft_strlen(var.temp) - s;
	return (LINE_FOUND);
}

#include <stdio.h>
#include <fcntl.h>
 int     main(int argc, char **argv)
 {
     int     fd;
     char    *line;
     int     x = 1;
 
     //if (argc > 1)
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
