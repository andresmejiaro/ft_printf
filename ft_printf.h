/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:06:52 by amejia            #+#    #+#             */
/*   Updated: 2023/01/28 23:58:32 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int     ft_printf(const char *, ...);
void	ft_putnbr_base_fd(long long nbr, char *base, int fd);
void    ft_putfloat_fd(float nbr, int pres,int fd);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int nb, int fd);
void ft_putfloat_fd(float nbr, int pres,int fd);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, unsigned int len);

#endif