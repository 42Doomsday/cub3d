/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:57:14 by clouden           #+#    #+#             */
/*   Updated: 2026/02/12 18:20:59 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

struct s_float
{
	int				sign;
	int				lnum;
	int				rnum;
	double			deci;
	long long		zero;
};

// chars
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

// convs
double		ft_atof(const char *str);
int			ft_atoi(const char*str);
__int128_t	ft_atol(const char *str);
char		*ft_itoa(int n);

// get_next_line
char		*get_next_line(int fd);

// io
int			ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
int			ft_puthex_fd(unsigned long long n, int fd, char mode);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
int			ft_putunbr_fd(unsigned int n, int fd);

// lists
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);

// logic

// math
int			ft_power(int base, int exp);

// memory
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_realloc(void *ptr, size_t size);
void		ft_strarr_free(char ***arr);

// strings
char		**ft_split(char const *s, char c);
char		**ft_strarr_join(char **arr1, char **arr2);
int			ft_strarr_len(char **arr);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_n(char **str_segs);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif
