/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_key_move.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 06:02:55 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 06:05:47 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_select.h"

t_key		ft_key_arrow_rl(t_select *select, unsigned int k)
{
	if (k == 67 || k == 0)
		if (++(select->id) >= select->live)
			select->id = 0;
	if (k == 68)
		if (--(select->id) == -1)
			select->id = select->live - 1;
	if (k == 69)
		if (--(select->id) == -1)
			if ((select->id = select->map.nb_col) >= select->live)
				select->id = select->live - 1;
	return ((k == 67 || k == 0) ? KRIGHT : KLEFT);
}

t_key		ft_key_arrow_ud(t_select *select, unsigned int k)
{
	if (k == 65)
	{
		if ((select->id -= select->map.nb_col) < 0)
		{
			select->id += select->map.nb_col;
			ft_key_arrow_rl(select, 69);
			while ((select->id + select->map.nb_col) <= select->live - 1)
				select->id += select->map.nb_col;
		}
	}
	if (k == 66)
	{
		if ((select->id += select->map.nb_col) >= select->live)
		{
			select->id -= select->map.nb_col;
			while ((select->id - select->map.nb_col) > -1)
				select->id -= select->map.nb_col;
			ft_key_arrow_rl(select, 67);
		}
	}
	return ((k == 65) ? KUP : KDOWN);
}
