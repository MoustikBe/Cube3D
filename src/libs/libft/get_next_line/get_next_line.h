/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:19:41 by misaac-c          #+#    #+#             */
/*   Updated: 2025/02/12 12:14:57 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
// --- Declaration des bibliotheque --- // 
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
// ------------------------------------ // 
// -- PARTIE BUFFER -- //
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
// ------------------- //
// -- Strucutre de la liste chainer -- //
typedef struct s_list_gnl
{
	char			*content;
	struct s_list_gnl	*next;
}					t_list_gnl;
// ----------------------------------- //
// - Fonction - //
t_list_gnl	*mk_clean(t_list_gnl **lst);
void		add_to_lst(t_list_gnl **lst, char *buff, int readed, int count);
void		count_for_line(t_list_gnl *lst, char **line);
void		read_store(int fd, t_list_gnl **lst);
void		free_all(t_list_gnl *lst);
void		reset_lst(t_list_gnl **lst, int count, int count_2, t_list_gnl *clean);
void		define_line(t_list_gnl *lst, char **line);
char		*get_next_line(int fd);
char		*so_free(t_list_gnl **lst);
int			found_a_count(t_list_gnl *lst, const char *str, int flag, int count);
// ------------ //
#endif
