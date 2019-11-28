/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:29:36 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/27 19:11:40 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** -------- HEADERS --------
*/

# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <wchar.h>

/*
** -------- TYPEDEFS --------
*/

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

/*
** -------- STRING FUNCTIONS --------
*/

int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_is_whitespace(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *restrict s1, const char *restrict s2);
char				*ft_strdup(const char *src);
char				*ft_strncat(char *restrict s1, const char *restrict s2,\
								size_t n);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,\
								size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				*ft_strnew(size_t size);
char				*ft_strrev(char *str);
char				**ft_strsplit(char const *s, char c);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_strlcat(char *restrict dst, const char *restrict src,\
								size_t dstsize);
size_t				ft_strlen(const char *str);
size_t				ft_strlcat(char *restrict dst, const char *restrict src,\
								size_t dstsize);
size_t				ft_strlen(const char *str);

/*
** -------- WRITE FUNCTIONS --------
*/

void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int nb);
void				ft_putnbr_fd(int nb, int fd);

/*
** -------- MEMORY FUNCTIONS --------
*/

void				ft_bzero(void *s, size_t n);
void				ft_memdel(void **ap);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memalloc(size_t size);
void				*ft_memdup(void const *content, size_t content_size);

/*
** -------- LIST FUNCTIONS --------
*/

void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstpushback(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** -------- CONVERSION FUNCTIONS --------
*/

int					ft_atoi(const char *str);
char				*ft_itoa(long long n);
char				*ft_itoa_base(uint64_t nb, int base);

/*
** -------- ADDITIONAL FUNCTIONS --------
*/

int					ft_count_digits(uint64_t n, int base);
char				*ft_putchar_w(wint_t c);
char				*ft_putstr_w(wchar_t *str);
char				*ft_strupper(char *str);
void				ft_print_hex(uint64_t n);
void				ft_print_bits(uint64_t bits, int len);
size_t				ft_leading_char_count(char const *s, int (*f)(int));
size_t				ft_trailing_char_count(char const *s, int (*f)(int));
size_t				ft_strchr_len(const char *s, int c);
int64_t				ft_pow(int64_t nb, int power);

#endif
