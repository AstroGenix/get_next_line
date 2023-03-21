/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:22:24 by dberehov          #+#    #+#             */
/*   Updated: 2022/12/06 09:22:25 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

//C Libraries
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <strings.h>
# include <limits.h>

//Buffer size definition
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

//Main function
char		*get_next_line(int fd);
//Auxiliary functions
size_t		ft_strlen(const char *str);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
void		*ft_calloc(size_t nmemb, size_t size);
#endif
