/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 20:47:03 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 07:31:33 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/types.h>

# include "./ft_printf/ft_printf.h"

# define FD_MAX 256
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

// ft_free
void		ft_free_strs(char **strs);

// ft_is
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
bool		ft_isnumber(char *str);
int			ft_isprint(int c);
bool		ft_isspace(int c);

// ft_mem
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *buf, int ch, size_t n);

// ft_num
long		ft_numlen(long num, long base);
long		ft_unumlen(size_t num, long base);

// ft_printf
int			ft_printf(const char *format, ...);
int			ft_dprintf(int fd, const char *format, ...);

// ft_put
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_base_fd(long num, char *base, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putnstr_fd(char *s, size_t n, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putunbr_base_fd(size_t num, char *base, int fd);

// ft_str
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
bool		ft_strcmp(char *s1, char *s2);
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

// ft_x
void		*ft_xcalloc(size_t count, size_t size);
char		**ft_xsplit(char const *s, char c);
char	    *ft_xstrdup_to_c(const char *s1, char c);
char		*ft_xstrdup(const char *s1);
char		*ft_xstrjoin_with_free(char *s1, bool b1, char *s2, bool b2);
char		*ft_xstrjoin(char const *s1, char const *s2);
char		*ft_xstrndup(const char *s1, size_t n);

// ft_xstd
void	    *ft_xmalloc(size_t size);
int			ft_xopen(const char *path, int oflag);
ssize_t		ft_xread(int fd, void *buf, size_t n);

// get_next_line
char		*get_next_line(int fd);
char	    *xget_next_line(int fd);

#endif
