/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:45:19 by keaton            #+#    #+#             */
/*   Updated: 2022/07/21 17:46:04 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_close_sems(t_pinfo *pinfo)
{
	if (pinfo->sem_fork != (sem_t *)-1)
		sem_close(pinfo->sem_fork);
	if (pinfo->sem_possible != (sem_t *)-1)
		sem_close(pinfo->sem_possible);
	if (pinfo->sem_report != (sem_t *)-1)
		sem_close(pinfo->sem_report);
	pthread_mutex_destroy(&(pinfo->lock_full));
	pthread_mutex_destroy(&(pinfo->lock_mt));
	sem_unlink("fork");
	sem_unlink("possible");
	sem_unlink("report");
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
