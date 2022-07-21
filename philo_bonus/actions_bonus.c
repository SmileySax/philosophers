/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:33:54 by keaton            #+#    #+#             */
/*   Updated: 2022/07/21 23:38:04 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_report(const char *words, t_pinfo *pinfo, int stop)
{
	struct timeval	t;
	int				delta;

	gettimeofday(&t, 0);
	sem_wait(pinfo->sem_report);
	delta = (t.tv_sec - pinfo->start_time.tv_sec) * 1000
		+ (t.tv_usec - pinfo->start_time.tv_usec) / 1000;
	printf("%dms %d %s\n", delta, pinfo->ph_nbr, words);
	if (!stop)
		sem_post(pinfo->sem_report);
}

void	ft_eat(t_pinfo *pinfo)
{
	struct timeval	t;

	if ((pinfo->info)[0] > 1)
		sem_wait(pinfo->sem_possible);
	sem_wait(pinfo->sem_fork);
	ft_report("has taken left fork", pinfo, 0);
	sem_wait(pinfo->sem_fork);
	ft_report("has taken right fork", pinfo, 0);
	ft_report("is eating", pinfo, 0);
	gettimeofday(&t, 0);
	sem_wait(pinfo->sem_mt[pinfo->ph_nbr - 1]);
	(pinfo->last_meal).tv_sec = t.tv_sec;
	(pinfo->last_meal).tv_usec = t.tv_usec;
	pinfo->meals++;
	sem_post(pinfo->sem_mt[pinfo->ph_nbr - 1]);
	if (pinfo->info[1] < pinfo->info[2])
		ft_usleep(pinfo->info[1] * 1000);
	else
		ft_usleep(pinfo->info[2] * 1000);
	sem_post(pinfo->sem_fork);
	ft_report("returned right fork", pinfo, 0);
	sem_post(pinfo->sem_fork);
	if ((pinfo->info)[0] > 1)
		sem_post(pinfo->sem_possible);
	ft_report("returned left fork", pinfo, 0);
}

int	ft_check_death(t_pinfo *pinfo)
{
	struct timeval	now;
	int				n;

	gettimeofday(&now, 0);
	sem_wait(pinfo->sem_mt[pinfo->ph_nbr - 1]);
	n = pinfo->meals;
	if (((now.tv_sec - (pinfo->last_meal).tv_sec) * 1000
			+ (now.tv_usec - (pinfo->last_meal).tv_usec) / 1000)
		> pinfo->info[1] && (n < pinfo->info[4] || !(pinfo->info[4])))
	{
		sem_post(pinfo->sem_mt[pinfo->ph_nbr - 1]);
		return (1);
	}
	else
		sem_post(pinfo->sem_mt[pinfo->ph_nbr - 1]);
	return (0);
}

void	*monitoring(void *arg)
{
	t_pinfo	*pinfo;

	pinfo = (t_pinfo *)arg;
	while (1)
	{
		ft_usleep(3000);
		if (ft_check_death(pinfo) > 0)
		{
			ft_report("died", pinfo, 1);
			exit(1);
		}
		sem_wait(pinfo->sem_mt[pinfo->ph_nbr - 1]);
		if (pinfo->info[4] && pinfo->meals >= pinfo->info[4])
		{
			sem_post(pinfo->sem_mt[pinfo->ph_nbr - 1]);
			ft_report("is full", pinfo, 0);
			sem_wait(pinfo->sem_full);
			pinfo->full = 1;
			sem_post(pinfo->sem_full);
			break ;
		}
		else
			sem_post(pinfo->sem_mt[pinfo->ph_nbr - 1]);
	}
	return (arg);
}

int	ft_sleep_n_think(t_pinfo *pinfo)
{
	sem_wait(pinfo->sem_full);
	if (pinfo->full)
	{
		sem_post(pinfo->sem_full);
		return (1);
	}
	else
		sem_post(pinfo->sem_full);
	ft_report("is sleeping", pinfo, 0);
	if ((pinfo->info)[1] <= (pinfo->info)[2] + (pinfo->info)[3])
		return (1);
	ft_usleep((pinfo->info)[3] * 1000);
	ft_report("is thinking", pinfo, 0);
	return (0);
}
