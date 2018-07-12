/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 09:48:02 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 13:07:56 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_select.h"

static t_key	ft_key_arrow_rl(t_select *select, unsigned int k)
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

static t_key	ft_key_arrow_ud(t_select *select, unsigned int k)
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

static t_key	ft_key_manage(t_select *select, unsigned int k)
{
	int			i;
	int			j;
	t_state		*state;

	i = 0;
	j = -1;
	if (k == 127)
	{
		if (--(select->live) == 0)
			return (KESC);
		state = select->lst->state;
		select->lst = ft_select_get_lst((const char **)select->lst,
				select->live + 1, select->id);
		while (++j < (select->live + 1))
			if (select->id != j)
				select->lst->state[i++] = state[j];
		select->map = ft_select_get_map(select);
		while (select->id >= select->live)
			ft_key_arrow_rl(select, 68);
		return (KDEL);
	}
	select->lst->state[select->id] =
		(select->lst->state[select->id] == CLEAR) ? SELECTED : CLEAR;
	ft_key_arrow_rl(select, 67);
	return (KSPACE);
}

t_key			ft_key_return(t_select *select)
{
	int			i;
	int			k;

	i = -1;
	k = 0;
	while (select->lst->lst[++i])
	{
		if (select->lst->state[i] == SELECTED)
		{
			if (k != 0)
				ft_putchar_fd(' ', 1);
			k = 1;
			ft_putstr_fd(select->lst->lst[i], 1);
		}
	}
	return (KESC);
}

t_key			ft_key_get(char buff[3], t_select *select)
{
	t_key		key;

	key = KNONE;
	if (buff[0] == 27 && buff[1] == 91 && (buff[2] == 65 || buff[2] == 66))
		key = ft_key_arrow_ud(select, (unsigned int)buff[2]);
	else if ((buff[0] == 27 && buff[1] == 91 && (buff[2] == 67 || buff[2] ==
					68)) || (buff[0] == 9 && buff[1] == 0 && buff[2] == 0))
		key = ft_key_arrow_rl(select, (unsigned int)buff[2]);
	else if ((buff[0] == 127 || buff[0] == 32) && buff[1] == 0 && buff[2] == 0)
		key = ft_key_manage(select, (unsigned int)buff[0]);
	else if (buff[0] == 13 && buff[1] == 0 && buff[2] == 0)
		key = KENT;
	else if (buff[1] == 0 && buff[2] == 0 && (buff[0] == 27 || buff[0] == 4))
		key = KESC;
	else if (buff[1] == 0 && buff[2] == 0 && ((buff[0] > 96 && buff[0] < 122)
			|| (buff[0] > 64 && buff[0] < 91)))
		key = ft_key_update_id_auto(select, (unsigned int)buff[0],
				select->lst->lst);
	return (key);
}
