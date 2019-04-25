/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 13:15:03 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/13 17:26:43 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdint.h>
# include <stdlib.h>
# include "get_next_line.h"

# include "colors.h"

# define ABS(x) ((x) < 0 ? -(x) : (x))
# define SIGN(x) ((x) < 0 ? (-1) : (1))
# define US unsigned int
# define LLI long long int
# define ULLI unsigned long long int
# undef tab

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

size_t				ft_strlen(const char *s);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strdup(const char *s1);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_firstOf(const char *bytes, const char *oneOf, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_strsplit_max(char const *s, char c, int max);
char				*ft_itoa(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr(int n);
void				ft_putendl(char const *s);
void				ft_putstr(char const *s);
void				ft_putchar(char c);
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstnew_noalloc(void *c, size_t c_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstfree(t_list **alst);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstfind(t_list *lst, void *content,\
					int (*cmp)(void *c1, void *c2));
void				ft_lstadd_end(t_list **lst, t_list *new);
void				ft_lstadd_after(t_list *elem, t_list *new);
void				ft_lstadd_before(t_list **alst, t_list *old, t_list *new);
t_list				*ft_lstbefore(t_list *lst, t_list *elem);
void				ft_lstdelin(t_list **alst, t_list *elem,\
					void (*del)(void*, size_t));
void				ft_lstdelin_memdel(t_list **alst, t_list *elem);
size_t				ft_lstsize(t_list *lst);
void				ft_lstsort(t_list **alst, int (*cmp)(void *c1, void *c2));
void				ft_lstadd_sorted(t_list **alst, t_list *elem,\
					int (*cmp)(void *c1, void *c2));
void				ft_lstadd_sorted_o(t_list **al, t_list *elem, void *opt,\
					int (*cmp)(void *c1, void *c2, void *opt));
t_list				*ft_lstsplit(char const *s, char c);
int					max_of(int n, int *tab);
int					min_of(int n, int *tab);
size_t				ft_lstmaxsize(t_list *lst);
size_t				ft_strsplit_size(char **split);
void				ft_deltab(void *ad, size_t size);
int					get_next_line(int const fd, char **line);
char				*ft_itoa_base(intmax_t value, int base);
char				*ft_uitoa_base(uintmax_t u_value, int base, int up);
void				ft_strlower(char *str);
void				ft_strupper(char *str);
int					ft_isupper(int c);
int					ft_islower(int c);
int					significant_bit(void *p, size_t size);
void				ft_putwchar_fd(unsigned int c, int fd, char **result);
void				ft_putwstr_fd(unsigned int *str, int fd, char **result);
void				ft_putwstr_size_fd(US *str, int fd, int size, char **r);
char				*ft_ftoa(double d, int precision);
int					ft_printf_fd(int fd, const char *restrict format, ...);
int					ft_printf(const char *restrict format, ...);
long long int		ft_atol(const char *str);
int					ft_isin(int n, int *tab, int size);
void				ft_sorttab(int *tab, int size, int sens);
void				ft_sorttab_double(int *tab, int *tab2, int size, int sens);
int					ft_readstr(char *str);
int					ft_random(int min, int max);
int					ft_isint(char *s_int, int *result);
char				**ft_explode(char const *s, char *delimiter);
char				*ft_replace(char *str, char *to_delete, char *to_put);
char				*ft_implode(char **split, char *inter);
char				**ft_create_tab(int length);
char				**ft_inc_tab(char **data, int size);
void				ft_freetab(char **data);
void				ft_realloc_tab(char ***data, size_t size);
size_t				ft_tab_size(char **data);
void				ft_print_rep(int c, size_t repeat);
char				*ft_strtrim_w(const char *s);
char				**ft_strdup_tab(char **data);
char				*ft_implode_tab(char **data, int start, size_t len);
int					ft_index_fmatch(char *str, char chr);
int					ft_index_lmatch(char *str, char chr);
int					ft_index_nmatch(char *str, char chr, int n);
char				*ft_cut_cur_word(char *str, int index);
char				*ft_del_cur_word(char *str, int index, int i);
char				**ft_split_index(char *str, int index);
void				ft_trace(const char *mess, const char *s);
void				ft_nbrtrace(const char *mess, int i);
char				*ft_replace_in_str(char *s, char *r, char *by, int recurse);
char				*ft_str_renew(char **old, char *new);
unsigned long int	ft_hexa(const char *str);
int					ft_index(const char *s, int c);

pid_t				my_fork(void);

#endif
