/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 20:47:03 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/29 18:01:53 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/errno.h>

# define FD_MAX 256
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_abs(int num);
long		ft_abs_l(long num);
long long	ft_abs_ll(long long num);
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
bool		ft_isnumber(char *str);
int			ft_isprint(int c);
char		*ft_itoa(int n);
void		ft_lstadd_back(t_list **lst, t_list *new_lst);
void		ft_lstadd_front(t_list **lst, t_list *new_lst);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *buf, int ch, size_t n);
size_t		ft_numlen(long long num);
size_t		ft_numlen_base(long long num, int base);
size_t		ft_numlen_u(unsigned long long num);
size_t		ft_numlen_u_base(unsigned long long num, unsigned int base);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putnstr_fd(char *s, size_t n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
char		*ft_strdup_to_c(const char *s1, char c);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
size_t		ft_strlen_to_c(const char *str, const char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strndup(const char *s1, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*get_next_line(int fd);

#endif
