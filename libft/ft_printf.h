/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:56:49 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/22 15:10:11 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# include <wchar.h>
# include <locale.h>

# define BUFF_PSIZE 255

typedef struct	s_flags
{
	int8_t		*flags;
	int			min_width;
	int8_t		period;
	int			prec;
	char		conv;
	char		type;
	int8_t		inexist;
}				t_flags;

int				ft_printf(const char *format, ...);

void			init_flags(t_flags *tflags);

int				get_flags(const char *str, va_list list, t_flags *tflags);

int				check_flags(char c, t_flags *tflags);

int				check_width(char c, t_flags *tflags, va_list list);

int				check_conv(char c, t_flags *tflags);

int				check_type(char c, t_flags *tflags);

int				check_inexisant(char c, t_flags *tflags);

int				missdirection(va_list list, t_flags *tflags);

int				signed_decimal(va_list list, t_flags *tflags);

int				unsigned_char(va_list list, t_flags *tflags);

int				print_widechar(int32_t c);

int				unsigned_string(va_list list, t_flags *tflags);

int				ft_pprint_base(uintmax_t n, const char *base);

int				left_space_padding(t_flags *tflags, int size);

int				left_zero_sign(t_flags *tflags, intmax_t nbr, int size);

int				right_space_padding(t_flags *tflags, int size);

int				unsigned_int (va_list list, t_flags *tflags);

int				uright_space_padding(t_flags *tflags, int size);

int				uleft_zero_sign(t_flags *tflags, int size, uintmax_t nbr);

int				uleft_space_padding(t_flags *tflags, int size);

int				buffin(char c);

void			flush_buff(char **buff);

int				wstring(t_flags *tflags, wchar_t *str);

int				cstring(t_flags *tflags, char *str);

int				get_normed(t_flags *tf, va_list lst, char **str, wchar_t **wst);

#endif
