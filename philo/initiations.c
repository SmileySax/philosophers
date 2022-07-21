/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:55:03 by keaton            #+#    #+#             */
/*   Updated: 2022/07/21 21:27:34 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_dead	**ft_fill_dead(t_dead **dead)
{
	(*dead) = (t_dead *)malloc(sizeof(t_dead));
	if (!(*dead))
		return (NULL);
	pthread_mutex_init(&((*dead)->deadlock), 0);
	pthread_mutex_init(&((*dead)->report), 0);
	(*dead)->flag = 0;
	return (dead);
}

void	ft_init_times(t_pinfo *pinfo)
{
	int	i;
	int	n_of_philos;

	i = 0;
	n_of_philos = pinfo->info[0];
	while (i < n_of_philos)
	{
		gettimeofday(&(pinfo[i].last_meal), 0);
		gettimeofday(&(pinfo[i++].start_time), 0);
	}
}

void	ft_pinfo_init(t_pinfo *pinfo, int n, int *info, t_dead *dead)
{
	pinfo->dead = dead;
	pinfo->id = 0;
	pinfo->info = info;
	pinfo->left_f = NULL;
	pinfo->right_f = NULL;
	pinfo->ph_nbr = n + 1;
	pinfo->meals = 0;
}

pthread_mutex_t	**ft_init_spoons(pthread_mutex_t **spoons, t_pinfo **pinfo)
{
	int	i;

	i = 0;
	*spoons = (pthread_mutex_t *)malloc((*pinfo)->info[0]
			* sizeof(pthread_mutex_t));
	if (!*spoons)
		return (NULL);
	pthread_mutex_init(&((*spoons)[i]), 0);
	while (i < (*pinfo)->info[0] - 1)
	{
		(*pinfo)[i].right_f = (*spoons) + i;
		pthread_mutex_init(&((*spoons)[i + 1]), 0);
		(*pinfo)[i].left_f = (*spoons) + i + 1;
		pthread_mutex_init(&((*pinfo)[i].mt_lock), 0);
		i++;
	}
	pthread_mutex_init(&((*pinfo)[i].mt_lock), 0);
	(*pinfo)[i].right_f = (*spoons) + (i % (*pinfo)[i].info[0]);
	(*pinfo)[i].left_f = (*spoons);
	return (spoons);
}

t_pinfo	*ft_init_values(t_pinfo **pinfo, pthread_mutex_t **spoons, char **argv)
{
	int		*info;
	int		i;
	t_dead	*dead;

	info = NULL;
	dead = NULL;
	if (!ft_fill_info(argv, &info))
		return (NULL);
	if (!ft_fill_dead(&dead))
		return (ft_free_idp(info, dead, pinfo));
	*pinfo = (t_pinfo *)malloc(info[0] * sizeof(t_pinfo));
	if (!*pinfo)
		return (ft_free_idp(info, dead, pinfo));
	i = -1;
	while (++i < info[0])
		ft_pinfo_init(&((*pinfo)[i]), i, info, dead);
	if (!ft_init_spoons(spoons, pinfo))
		return (ft_free_idp(info, dead, pinfo));
	return (*pinfo);
}
