/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:54:52 by keaton            #+#    #+#             */
/*   Updated: 2022/07/22 13:29:23 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_spoons(pthread_mutex_t **spoons, t_pinfo *pinfo)
{
	int	i;

	i = 0;
	while (i < pinfo->info[0])
		pthread_mutex_destroy((*spoons) + i++);
	i = 0;
	while (i < pinfo->info[0])
		pthread_mutex_destroy(&(pinfo[i++].mt_lock));
	free(*spoons);
	pthread_mutex_destroy(&(pinfo->dead->deadlock));
}

t_pinfo	*ft_free_idp(int *i, t_dead *d, t_pinfo **p)
{
	if (i)
		free(i);
	if (d)
		free(d);
	if (*p)
	{
		free(*p);
		*p = NULL;
	}
	return (NULL);
}
