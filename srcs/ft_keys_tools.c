/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 09:48:02 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 01:31:17 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"

t_key			ft_key_update_id_auto(t_select *select, unsigned int k,
		char *lst[])
{
	int			i;
	int			pos;

	i = -1;
	pos = -1;
	while (++pos < select->map.col_width)
	{
		while (lst[++i])
			if ((int)ft_strlen(lst[i]) > pos)
				if ((unsigned int)lst[i][pos] == k)
					if ((select->id = i) > -1)
						return (KNONE);
		i = -1;
	}
	return (KNONE);
}
