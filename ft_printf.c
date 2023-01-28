/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:05:59 by amejia            #+#    #+#             */
/*   Updated: 2023/01/28 23:54:03 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}


void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}


void	ft_putnbr_fd(int nb, int fd)
{
	char	c;

	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-nb, fd);
	}
	else if (nb < 10)
	{
		c = '0' + nb;
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
}

void ft_putfloat_fd(float nbr, int pres,int fd)
{
    float remainder;

    if (nbr < 0)
    {
        write(fd,"-",1);
        nbr = -nbr;
    }
    ft_putnbr_fd((long)nbr,fd);
    remainder = nbr - (long)nbr;
    write(fd,".",1);
    while(pres-- > 0)
        remainder*=10;
    ft_putnbr_fd((long)remainder,fd);      
}

size_t	ft_strlen(const char *s)
{
	unsigned int	counter;

	counter = 0;
	while (*(s + counter) != '\0')
	{
		counter++;
	}
	return (counter);
}


size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	unsigned int	counter;
	unsigned int	size_src;

	size_src = ft_strlen(src);
	counter = 0;
	while (counter < size && counter <= size_src)
	{
		if (counter < size - 1 && counter < size_src)
			*dest = *src;
		else
			*dest = '\0';
		if (counter < size - 1)
			dest++;
		if (counter < size_src - 1)
			src++;
		counter++;
	}
	return (size_src);
}


char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	char	*to_return;

	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	to_return = (char *)malloc((len + 1) * sizeof(char));
	if (to_return == 0)
		return (0);
	if (len == 0)
		ft_strlcpy(to_return, "", 1);
	else
		ft_strlcpy(to_return, (char *)(s + start), len + 1);
	return (to_return);
}


static int	pseudolog10(int n)
{
	if (n == -2147483648)
		return (11);
	if (n < 0)
		return (1 + pseudolog10(-n));
	if (n <= 9)
		return (1);
	return (1 + pseudolog10(n / 10));
}

static int	pseudologbase(long long n, long base)
{
	if(base < 2)
		return(-1);
	if (n < 0)
		return (1 + pseudologbase(-n, base));
	if (n < base)
		return (1);
	return (1 + pseudologbase(n / base, base));
}

void tag_i(va_list va_ptr, int *nchar)
{
	int j;

	j=va_arg(va_ptr, int);
	ft_putnbr_fd(j, 1);
	*nchar += pseudolog10(*nchar);
}

void tag_s(va_list va_ptr, int *nchar)
{
	char * j;
	
	j=va_arg(va_ptr,char *);
	if (j == 0)
	{
		ft_putstr_fd("(null)",1);
		*nchar += 6;
		return ;
	}
	ft_putstr_fd(j,1);
	*nchar += ft_strlen(j);
}

void tag_p(va_list va_ptr, int *nchar)
{
	void *j;

	j=va_arg(va_ptr, void *);
	write(1,"0x",2);
	ft_putnbr_base_fd((unsigned long long)j, "0123456789abcdef", 1);
	*nchar += pseudologbase((unsigned long long)j,16)+2;
}

static char	*tag_process(char *tag_pos,va_list va_ptr, int *nchar)
{
	char tag;
//    identify_tag();
	tag_pos++;
	tag = *(tag_pos);
	if (tag == 'i' || tag == 'd')
		tag_i(va_ptr,nchar);
	if (tag == 'c')
	{
		ft_putchar_fd(va_arg(va_ptr, int),1);
		(*nchar)++;
	}
	if (tag == 's')
		tag_s(va_ptr,nchar);
	if (tag == '%')
	{
		write(1,"%",1);
		(*nchar)++;
	}
	if (tag == 'p')
		tag_p(va_ptr,nchar);
	if (tag == 'f')
		ft_putfloat_fd(va_arg(va_ptr, double),2,1);
	if (tag == 'x')
	{
		write(1,"0x",2);
		ft_putnbr_base_fd(va_arg(va_ptr, unsigned long),"0123456789abcdef",1);
	}
	if (tag == 'X')
	{
		write(1,"0X",2);
		ft_putnbr_base_fd(va_arg(va_ptr, unsigned long),"0123456789ABCDEF",1);
	}
	return (tag_pos++, tag_pos);        
}

static void process_string(char *str, va_list va_ptr, int *nchar)
{
	char *tag_pos;
	char *temp;
	
	tag_pos=ft_strchr(str,'%');
	
	if (tag_pos != 0)
		{
		temp = ft_substr(str,0,(unsigned int)(tag_pos - str));
		*nchar+=(unsigned int)(tag_pos - str);
		}
	else
	{
		temp = ft_substr(str,0,ft_strlen(str));
		*nchar+=ft_strlen(str);
	}
	ft_putstr_fd(temp,1);
	free(temp);
	if(tag_pos != 0)
	{
		tag_pos=tag_process(tag_pos, va_ptr, nchar);
		process_string(tag_pos, va_ptr,nchar);
	}
}

int ft_printf(const char *string, ...)
{   
	int nchar;
	va_list va_ptr;
	
	nchar = 0;
	va_start(va_ptr,string);
	process_string((char *)string, va_ptr ,&nchar);
	return (nchar);
}



