/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:33:54 by keaton            #+#    #+#             */
/*   Updated: 2022/07/21 18:00:36 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_report(const char *words, t_pinfo *pinfo, int stop)
{
	struct timeval	t;

	gettimeofday(&t, 0);
	sem_wait(pinfo->sem_report);
	printf("%d %d %s\n", t.tv_usec / 1000, pinfo->ph_nbr, words);
	if (!stop)
		sem_post(pinfo->sem_report);
}

void	ft_eat(t_pinfo *pinfo)
{
	struct timeval	t;

	sem_wait(pinfo->sem_possible);
	sem_wait(pinfo->sem_fork);
	ft_report("has taken left fork", pinfo, 0);
	sem_wait(pinfo->sem_fork);
	ft_report("has taken right fork", pinfo, 0);
	ft_report("is eating", pinfo, 0);
	gettimeofday(&t, 0);
	pthread_mutex_lock(&(pinfo->lock_mt));
	(pinfo->last_meal).tv_sec = t.tv_sec;
	(pinfo->last_meal).tv_usec = t.tv_usec;
	pinfo->meals++;
	pthread_mutex_unlock(&(pinfo->lock_mt));
	if (pinfo->info[1] < pinfo->info[2])
		ft_usleep(pinfo->info[1] * 1000);
	else
		ft_usleep(pinfo->info[2] * 1000);
	sem_post(pinfo->sem_fork);
	ft_report("returned right fork", pinfo, 0);
	sem_post(pinfo->sem_fork);
	sem_post(pinfo->sem_possible);
	ft_report("returned left fork", pinfo, 0);
}

int	ft_check_death(t_pinfo *pinfo)
{
	struct timeval	now;
	int				n;

	gettimeofday(&now, 0);
	pthread_mutex_lock(&(pinfo->lock_mt));
	n = pinfo->meals;
	if (((now.tv_sec - (pinfo->last_meal).tv_sec) * 1000
			+ (now.tv_usec - (pinfo->last_meal).tv_usec)
			/ 1000) > pinfo->info[1] && n < pinfo->info[4])
	{
		pthread_mutex_unlock(&(pinfo->lock_mt));
		return (1);
	}
	else
		pthread_mutex_unlock(&(pinfo->lock_mt));
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
		pthread_mutex_lock(&(pinfo->lock_mt));
		if (pinfo->info[4] && pinfo->meals >= pinfo->info[4])
		{
			pthread_mutex_unlock(&(pinfo->lock_mt));
			ft_report("is full", pinfo, 0);
			pthread_mutex_lock(&(pinfo->lock_full));
			pinfo->full = 1;
			pthread_mutex_unlock(&(pinfo->lock_full));
			break ;
		}
		else
			pthread_mutex_unlock(&(pinfo->lock_mt));
	}
	return (arg);
}

int	ft_sleep_n_think(t_pinfo *pinfo)
{
	pthread_mutex_lock(&(pinfo->lock_full));
	if (pinfo->full)
	{
		pthread_mutex_unlock(&(pinfo->lock_full));
		return (1);
	}
	pthread_mutex_unlock(&(pinfo->lock_full));
	ft_report("is sleeping", pinfo, 0);
	if ((pinfo->info)[1] <= (pinfo->info)[2] + (pinfo->info)[3])
		return (1);
	ft_usleep((pinfo->info)[3] * 1000);
	ft_report("is thinking", pinfo, 0);
	return (0);
}
