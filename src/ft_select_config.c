/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_select.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/04 01:12:02 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 13:07:59 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_select.h"

void				ft_select_delete(t_select **select)
{
	int				i;

	i = -1;
	while ((*select)->lst->lst[++i])
		ft_strdel(&(*select)->lst->lst[i]);
	free((*select)->lst);
	free(*select);
}

void				ft_select_save(t_select **select, int stat)
{
	static t_select	*save;

	if (stat == 0)
		save = *select;
	else
		*select = save;
}

t_lstsel			*ft_select_get_lst(const char *argv[], int argc,
		int idtarget)
{
	t_lstsel		*new;
	int				i;
	int				k;
	t_stat			stat;

	i = -1;
	k = 0;
	if ((argc > 4095) || (!(new = (t_lstsel *)malloc(sizeof(t_lstsel)))))
		return (NULL);
	while (argv[++i])
		if (i != idtarget)
		{
			new->lst[k] = ft_strdup(argv[i]);
			if (lstat(new->lst[k], &stat) > -1)
			{
				((stat.st_mode & S_IXUSR) || (stat.st_mode & S_IXGRP) ||
					(stat.st_mode & S_IXOTH)) ? new->ftype[k] = ISEXEC : 0;
				(S_ISDIR(stat.st_mode)) ? new->ftype[k] = ISDIR : 0;
			}
			(new->ftype[k] != ISDIR && new->ftype[k] != ISEXEC) ?
				new->ftype[k] = ISREG : 0;
			new->state[k++] = CLEAR;
		}
	new->lst[k] = NULL;
	return (new);
}

t_select			*ft_select_new(int argc, const char *argv[])
{
	t_select		*select;

	if (!(select = (t_select *)malloc(sizeof(t_select))))
		return (NULL);
	select->fd = 0;
	select->id = 0;
	select->live = argc - 1;
	if (argc < 2 || !(select->lst = ft_select_get_lst(argv, argc, 0)))
		return (NULL);
	select->map = ft_select_get_map(select);
	return (select);
}
