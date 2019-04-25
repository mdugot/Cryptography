/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 12:35:34 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/08 16:41:31 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define SPEC v->specifier
# define SIGNED v->flags.forced_sign
# define BSIGNED v->flags.blank_sign
# define ZERO v->flags.zero_blank
# define PREFIX v->flags.prefix
# define RIGHT v->flags.right_blank
# define ACT_P v->active_precision
# define ACT_W v->active_width
# define C_NORMAL "\x1B[0m"
# define C_RED "\x1B[31m"
# define C_GREEN "\x1B[32m"
# define C_YELLOW "\x1B[33m"
# define C_BLUE "\x1B[34m"
# define C_MAGENTA  "\x1B[35m"
# define C_CYAN "\x1B[36m"
# define C_WHITE "\x1B[37m"
# define RESET "\033[0m"

typedef union	u_arg
{
	int			a_char;
	intmax_t	a_int;
	uintmax_t	a_uint;
	US			a_wchar;
	double		a_double;
	char		*a_str;
	US			*a_wstr;
	void		*a_ad;
}				t_arg;

typedef struct	s_printer
{
	char		*result;
	int			fd;
	va_list		*ap;
	char		*format;
	int			lenght;
}				t_printer;

typedef enum	e_subspe
{
	SS_NULL = 0, HH = 1, H = 2, L = 3, LL = 4, J = 5, Z = 6,
}				t_subspe;

typedef struct	s_flags
{
	char		right_blank;
	char		zero_blank;
	char		forced_sign;
	char		blank_sign;
	char		prefix;
}				t_flags;

typedef struct	s_value
{
	t_printer	*printer;
	char		active_width;
	char		active_precision;
	char		char_null;
	char		specifier;
	t_flags		flags;
	t_subspe	ss;
	int			width;
	int			precision;
}				t_value;

char			*ft_strf(const char *restrict format, ...);
int				ft_printf_fd(int fd, const char *restrict format, ...);
int				ft_printf(const char *restrict format, ...);
int				do_printf_fd(int fd, char *format, va_list *ap);
char			*find_next_special(char *str);
int				is_expr(char c);
int				is_flag(char c);
int				is_specifier(char c);
int				is_special(char c);
void			print_between(t_printer *p, char *end);
void			read_special(t_printer *p);
t_arg			find_type(va_list *ap, t_value *v);
void			write_value(t_value *v, t_printer *p);
void			wprint_value(t_printer *p, t_value *v, US *str);
void			print_value(t_printer *p, t_value *v, char *str);
void			print_with_width(char *str, t_value *v, t_printer *p);
void			print_str(char *str, t_value *v, int fd);
void			wprint_str(US *str, t_value *v, int fd, int size);
int				read_joker(t_printer *p, char *flag);
void			read_color(t_printer *p);
char			*one_char_str(char c);
void			printf_putchar(char c, int fd, char **to_join);
void			printf_putstr(char *str, int fd, char **to_join);
t_printer		initialize_printer(int fd, char *format, va_list *ap);

#endif
