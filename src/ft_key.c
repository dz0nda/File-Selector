/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_key.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 04:56:15 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 04:56:19 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_select.h"

static t_key	ft_key_update_id_auto(t_select *select, unsigned int k,
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

static t_key	ft_key_delete(t_select *select)
{
	int			i;
	int			j;

	i = select->id;
	j = -1;
	if (--(select->live) == 0)
		return (KESC);
	while (select->lst->lst[++i])
	{
		ft_strdel(&select->lst->lst[i - 1]);
		select->lst->lst[i - 1] = ft_strdup(select->lst->lst[i]);
		select->lst->ftype[i - 1] = select->lst->ftype[i];
		select->lst->state[i - 1] = select->lst->state[i];
	}
	select->map = ft_select_get_map(select);
	while (select->id >= select->live)
		ft_key_arrow_rl(select, 68);
	return (KDEL);
}

static t_key	ft_key_space(t_select *select)
{
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
				ft_putchar_fd(' ', STDOUT_FILENO);
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
	else if (buff[0] == 127 && buff[1] == 0 && buff[2] == 0)
		key = ft_key_delete(select);
	else if (buff[0] == 32 && buff[1] == 0 && buff[2] == 0)
		key = ft_key_space(select);
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
