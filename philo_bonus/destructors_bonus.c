/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:45:19 by keaton            #+#    #+#             */
/*   Updated: 2022/07/22 00:15:17 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_mt(t_pinfo *pinfo)
{
	char	*name;
	int		i;

	i = -1;
	if (pinfo->sem_mt)
	{
		while (++i < pinfo->info[0])
		{
			name = (char *)malloc(ft_deccount(i) + 3);
			if (!name)
			{
				i--;
				continue ;
			}
			ft_itoa(i, name + 2);
			if (pinfo->sem_mt[i] != (sem_t *)-1)
				sem_close(pinfo->sem_mt[i]);
			sem_unlink(name);
			free(name);
		}
		free(pinfo->sem_mt);
	}
}

int	ft_close_sems(t_pinfo *pinfo)
{
	if (pinfo->sem_fork != (sem_t *)-1)
		sem_close(pinfo->sem_fork);
	if (pinfo->sem_possible != (sem_t *)-1)
		sem_close(pinfo->sem_possible);
	if (pinfo->sem_report != (sem_t *)-1)
		sem_close(pinfo->sem_report);
	if (pinfo->sem_full != (sem_t *)-1)
		sem_close(pinfo->sem_full);
	ft_close_mt(pinfo);
	sem_unlink("fork");
	sem_unlink("possible");
	sem_unlink("report");
	sem_unlink("full");
	sem_unlink("mt");
	return (1);
}

int	ft_free_ip(int *i, t_pinfo *p)
{
	if (i)
		free(i);
	if (p->pid)
	{
		free(p->pid);
		p->pid = NULL;
	}
	return (0);
}

void	ft_kill_n_finish(t_pinfo *pinfo, int i)
{
	int				d;
	int				err;

	d = -1;
	while (++d < (pinfo->info)[0])
	{
		wait(&err);
		if (err)
		{
			while (i >= 1)
				kill((pinfo->pid)[--i], SIGKILL);
			break ;
		}
	}
	ft_close_sems(pinfo);
	ft_free_ip(pinfo->info, pinfo);
}
