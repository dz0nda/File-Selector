/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select_config.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 04:56:49 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 04:56:56 by dzonda      ###    #+. /#+    ###.fr     */
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

static t_lstsel		*ft_select_get_lst(const char *argv[])
{
	int				i;
	int				k;
	t_lstsel		*lst;
	t_stat			stat;

	i = 0;
	k = -1;
	if (!(lst = (t_lstsel *)malloc(sizeof(t_lstsel))))
		return (NULL);
	while (argv[++i])
	{
		lst->lst[++k] = ft_strdup(argv[i]);
		if (lstat(lst->lst[k], &stat) > -1)
		{
			if ((stat.st_mode & S_IXUSR))
				lst->ftype[k] = ISEXEC;
			if (S_ISDIR(stat.st_mode))
				lst->ftype[k] = ISDIR;
		}
		if (lst->ftype[k] != ISDIR && lst->ftype[k] != ISEXEC)
			lst->ftype[k] = ISREG;
		lst->state[k] = CLEAR;
	}
	lst->lst[++k] = NULL;
	return (lst);
}

t_select			*ft_select_new(int argc, const char *argv[])
{
	t_select		*select;

	if (!(select = (t_select *)malloc(sizeof(t_select))))
		return (NULL);
	select->id = 0;
	select->live = argc - 1;
	if ((argc < 2 || argc > 4095) || !(select->lst = ft_select_get_lst(argv)))
	{
		free(select);
		return (NULL);
	}
	select->map = ft_select_get_map(select);
	return (select);
}
