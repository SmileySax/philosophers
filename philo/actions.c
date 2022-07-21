/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:54:57 by keaton            #+#    #+#             */
/*   Updated: 2022/07/21 22:29:17 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_report(const char *words, t_pinfo *pinfo)
{
	struct timeval	t;
	int				delta;

	pthread_mutex_lock(&(pinfo->dead->deadlock));
	if (!pinfo->dead->flag)
	{
		pthread_mutex_unlock(&(pinfo->dead->deadlock));
		gettimeofday(&t, 0);
		delta = (t.tv_sec - pinfo->start_time.tv_sec) * 1000
			+ (t.tv_usec - pinfo->start_time.tv_usec) / 1000;
		pthread_mutex_lock(&(pinfo->dead->report));
		printf("%dms %d %s\n", delta, pinfo->ph_nbr, words);
		pthread_mutex_unlock(&(pinfo->dead->report));
	}
	else
		pthread_mutex_unlock(&(pinfo->dead->deadlock));
}

void	ft_eat_odd(t_pinfo *pinfo)
{
	struct timeval	t;

	pthread_mutex_lock(pinfo->left_f);
	ft_report("has taken left fork", pinfo);
	pthread_mutex_lock(pinfo->right_f);
	ft_report("has taken right fork", pinfo);
	ft_report("is eating", pinfo);
	gettimeofday(&t, 0);
	pthread_mutex_lock(&(pinfo->mt_lock));
	pinfo->last_meal.tv_sec = t.tv_sec;
	pinfo->last_meal.tv_usec = t.tv_usec;
	pinfo->meals++;
	pthread_mutex_unlock(&(pinfo->mt_lock));
	if (pinfo->info[1] < pinfo->info[2])
		ft_usleep(pinfo->info[1] * 1000);
	else
		ft_usleep(pinfo->info[2] * 1000);
	pthread_mutex_unlock(pinfo->right_f);
	ft_report("returned right fork", pinfo);
	pthread_mutex_unlock(pinfo->left_f);
	ft_report("returned left fork", pinfo);
}

void	ft_eat_even(t_pinfo *pinfo)
{
	struct timeval	t;

	pthread_mutex_lock(pinfo->right_f);
	ft_report("has taken right fork", pinfo);
	pthread_mutex_lock(pinfo->left_f);
	ft_report("has taken left fork", pinfo);
	ft_report("is eating", pinfo);
	gettimeofday(&t, 0);
	pthread_mutex_lock(&(pinfo->mt_lock));
	pinfo->last_meal.tv_sec = t.tv_sec;
	pinfo->last_meal.tv_usec = t.tv_usec;
	pinfo->meals++;
	pthread_mutex_unlock(&(pinfo->mt_lock));
	if (pinfo->info[1] < pinfo->info[2])
		ft_usleep(pinfo->info[1] * 1000);
	else
		ft_usleep(pinfo->info[2] * 1000);
	pthread_mutex_unlock(pinfo->left_f);
	ft_report("returned left fork", pinfo);
	pthread_mutex_unlock(pinfo->right_f);
	ft_report("returned right fork", pinfo);
}

void	ft_lets_eat(t_pinfo	*pinfo, pthread_mutex_t **spoons)
{
	int				i;
	int				d;
	void			*ret;

	ft_init_times(pinfo);
	i = -1;
	while (++i < pinfo->info[0])
		pthread_create(&(pinfo[i].id), 0, *ft_philo, pinfo + i);
	ft_philo_died(pinfo);
	d = -1;
	if (pinfo->info[0] == 1)
	{
		pthread_detach(pinfo[0].id);
		ft_usleep(pinfo->info[1] + 3000);
	}
	else
		while (++d < pinfo->info[0])
			pthread_join(pinfo[d].id, &ret);
	ft_destroy_spoons(spoons, pinfo);
	ft_free_idp(pinfo->info, pinfo->dead, &pinfo);
}
