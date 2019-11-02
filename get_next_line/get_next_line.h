/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/26 17:06:58 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/02 22:40:45 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int get_next_line(int fd, char **line);
int get_slash(char *buf);
//int count_words(char **buf);
//char	*ft_strcpy(char **line, char **buf);
int ft_strlen(char *s);
char *ft_strjoin(char *s1, char *s2);
char *out_slash(char *save);
char *ft_strdup(char *src);

#endif
