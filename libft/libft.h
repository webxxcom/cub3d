/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:23:22 by phutran           #+#    #+#             */
/*   Updated: 2025/05/19 11:23:22 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define TRUE 1

# define LOWERCASE 0
# define UPPERCASE 1

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// Char

int			ft_isalpha(int ch);
int			ft_isdigit(int ch);
int			ft_isalnum(int ch);
int			ft_isascii(int ch);
int			ft_isprint(int ch);

// Convert

int			ft_toupper(int ch);
int			ft_tolower(int ch);
int			ft_atoi(const char *str);
char		*ft_itoa(int num);

// String

size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
int			ft_strncmp(const char *lhs, const char *rhs, size_t count);
const char	*ft_strnstr(const char *str, const char *substr, size_t count);
char		*ft_strchr(const char *str, int ch);
char		*ft_strrchr(const char *str, int ch);
char		*ft_strdup(const char *str1);
char		*ft_substr(const char *str, unsigned int pos, size_t count);
char		*ft_strjoin(const char *str1, const char *str2);
char		*ft_strtrim(const char *str1, const char *set);
char		*ft_strmapi(const char *str, char (*f)(unsigned int, char));
char		**ft_split(const char *str, char ch); // Improve
void		ft_striteri(char *str, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char ch, int fd);
void		ft_putstr_fd(char *str, int fd);
void		ft_putendl_fd(char *str, int fd);
void		ft_putnbr_fd(int num, int fd);

// Memory

int			ft_memcmp(const void *lhs, const void *rhs, size_t count);
const void	*ft_memchr(const void *ptr, int ch, size_t count);
void		*ft_memset(void *dest, int ch, size_t count);
void		*ft_bzero(void *dest, size_t count);
void		*ft_memcpy(void *dest, const void *src, size_t count);
void		*ft_memmove(void *dest, const void *src, size_t count);
void		*ft_calloc(size_t num, size_t size);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);

void		ft_free_matrix(char **matrix); // Extended - OK

// List

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			ft_lstsize(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lst_free(t_list *list);
void		ft_lst_remove_if(t_list **lst, void *data_ref, int (*cmp)(void *, void *),
				void (*del)(void *));

// Print

int			ft_printf(const char *format, ...); // Improve
int			ft_print_ch(int ch); // Improve
int			ft_print_str(const char *str); // Improve
int			ft_print_ptr(void *ptr); // Improve
int			ft_print_int(int num); // Improve
int			ft_print_uint(unsigned int num); // Improve
int			ft_print_hex(unsigned long num, int letter_case); // Improve

// Read

char		*ft_get_next_line(int fd); // Improve

#endif