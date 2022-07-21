/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:54:47 by keaton            #+#    #+#             */
/*   Updated: 2022/06/29 15:39:30 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death(t_pinfo *pinfo, int i, int *n)
{
	struct timeval	now;
	pthread_mutex_t	*lock;

	lock = &(pinfo->dead->deadlock);
	gettimeofday(&now, 0);
	pthread_mutex_lock(&(pinfo[i].mt_lock));
	*n = pinfo[i].meals;
	if (((now.tv_sec - pinfo[i].last_meal.tv_sec) * 1000
			+ (now.tv_usec - pinfo[i].last_meal.tv_usec) / 1000)
		> pinfo[i].info[1] && *n != pinfo[i].info[4])
	{
		pthread_mutex_unlock(&(pinfo[i].mt_lock));
		ft_report("died", pinfo + i);
		pthread_mutex_lock(lock);
		pinfo->dead->flag = 1;
		pthread_mutex_unlock(lock);
		return (1);
	}
	pthread_mutex_unlock(&(pinfo[i].mt_lock));
	return (0);
}

int	ft_philo_died(t_pinfo *pinfo)
{
	int	i;
	int	count;
	int	n;

	i = 0;
	while (i++ >= 0)
	{
		if (i == pinfo->info[0])
			i = 0;
		if (ft_check_death(pinfo, i, &n))
			return (1);
		if (n == pinfo[i].info[4])
			count++;
		else
			count = 0;
		if (count == pinfo->info[0])
			return (0);
	}
	return (0);
}

int	ft_check_smbd_died(t_pinfo *philo, int full)
{
	pthread_mutex_lock(&(philo->dead->deadlock));
	if (philo->dead->flag)
	{
		pthread_mutex_unlock(&(philo->dead->deadlock));
		return (1);
	}
	pthread_mutex_unlock(&(philo->dead->deadlock));
	if (full)
	{
		pthread_mutex_lock(&(philo->mt_lock));
		if (philo->meals == philo->info[4])
		{
			pthread_mutex_unlock(&(philo->mt_lock));
			ft_report("is full", philo);
			return (1);
		}
		pthread_mutex_unlock(&(philo->mt_lock));
	}
	return (0);
}

void	*ft_philo(void *pinfo)
{
	t_pinfo	*philo;

	philo = (t_pinfo *)pinfo;
	if (philo->ph_nbr % 2 != 0 && philo->info[2] < philo->info[1])
		ft_usleep(philo->info[2] * 1000 + 1000 * philo->info[0] / 5);
	else if (philo->ph_nbr % 2 != 0 && philo->info[2] >= philo->info[1])
		ft_usleep(philo->info[1] * 1000 + 1000 * philo->info[0] / 5);
	ft_report("is ready", philo);
	while (1)
	{
		if (philo->ph_nbr % 2 == 0)
			ft_eat_even(philo);
		else
			ft_eat_odd(philo);
		if (ft_check_smbd_died(philo, 1))
			break ;
		ft_report("is sleeping", philo);
		if (philo->info[1] <= philo->info[2] + philo->info[3])
			break ;
		ft_usleep(philo->info[3] * 1000);
		ft_report("is thinking", philo);
		if (ft_check_smbd_died(philo, 0))
			break ;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_pinfo			*pinfo;
	pthread_mutex_t	*spoons;

	if (argc < 5 || argc > 6)
	{
		printf("err: ./philo n_phs t_die t_eat t_sleep [n_times_eat]");
		ft_usleep(100);
		return (1);
	}
	pinfo = NULL;
	if (!ft_init_values(&pinfo, &spoons, argv))
		return (1);
	ft_lets_eat(pinfo, &spoons);
	return (0);
}
