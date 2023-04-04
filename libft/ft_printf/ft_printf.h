/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:12:35 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/14 18:12:37 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

typedef struct s_flags{
	int	pad;
	int	meno;
	int	punto;
	int	numsign;
	int	spazio;
	int	piu;
	int	npad[2];
}	t_flags;

int		unnbrlen(unsigned long n, unsigned int base);
int		nbrlen(long n, int base, int spc);
int		ft_max(int n1, int n2);
void	ft_reset(t_flags *flags);
int		get_flags(const char *str, char *set, t_flags *flags);
void	ft_putchar(char c);
int		ft_putstr(char *s, int bypass);
void	ft_putpad(int npad, int pad);
void	ft_putnbrbase(long n, int base, int uc, t_flags flags);
void	ft_putunnbrbase(unsigned long n, unsigned int bs, int uc, t_flags fags);
int		ft_printf(const char *str, ...);
int		manage_almost_flag(int *i, int result);
int		manage_real_flags(int *i, int result, const char *str, va_list arg_ptr);
int		manage_no_flag(int *i, int result, const char *str);
int		manage_char_flag(int result, t_flags flags, va_list arg_ptr);
int		manage_string_flag(int len, int result, char *strvar, t_flags flags);
int		manage_nostring_flag(int result, t_flags flags);
int		manage_nbr_flag(int result, t_flags flags, va_list arg_ptr);
int		manage_uns_flag(int result, t_flags flags, va_list arg_ptr);
int		manage_hex_flag(int result, char flag, t_flags flags, va_list arg_ptr);
int		manage_imptr_flag(int result, long n, t_flags flags);
int		manage_ptr_flag(int result, t_flags flags, va_list arg_ptr);
int		manage_more_flags(int result, char flag, t_flags flags, va_list ap);
int		manage_flags(int i, const char *str, t_flags *flags);
void	managenbr(long n, int base, int spc, t_flags flags);
char	*ptrtostr(long ptr, int i, int tmp, t_flags flags);
int		ptrtostr1(int *len, char **str, t_flags *flags);
int		ptrtostr2(int *len, int *i, char *str, t_flags flags);

#endif
