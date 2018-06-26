/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isspace.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:10:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 20:15:30 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

int					ft_isspace(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch == 32 || ch == 11 || ch == 12 || ch == 13 || ch == 9 ||
		ch == 10)
		return (1);
	return (0);
}