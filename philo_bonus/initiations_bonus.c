/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiations_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:27:36 by keaton            #+#    #+#             */
/*   Updated: 2022/07/22 00:15:29 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_info(int *info, int flag)
{
	int	i;

	if (flag)
	{
		printf("err: ./philo n_phs t_die t_eat t_sleep [n_times_eat]\n");
		printf("err: integer n_phs >= 0\n");
		printf("err: integer t_die >= 0\n");
		printf("err: integer t_eat >= 0\n");
		printf("err: integer t_sleep >= 0\n");
		printf("err: integer n_times_eat >= 0\n");
		return (0);
	}
	i = 0;
	while (i < 5)
		if (info[i++] < 0)
			return (ft_check_info(info, 1));
	return (1);
}

void	ft_init_mt(t_pinfo *pinfo)
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
			ft_itoa(i, name);
			sem_unlink(name);
			pinfo->sem_mt[i] = sem_open(name, O_CREAT, 0666, 1);
			free(name);
			if (pinfo->sem_mt[i] == (sem_t *)-1)
			{
				i--;
				continue ;
			}
		}
	}
}

int	**ft_fill_info(char **argv, int **info)
{
	int	i;

	(*info) = (int *)malloc(5 * sizeof(int));
	if (!*info)
		return (NULL);
	i = 0;
	while (argv[++i])
	{
		(*info)[i - 1] = ft_atoi(argv[i]);
		if (i == 5 && (*info)[i - 1] == 0)
		{
			ft_usleep(100);
			free(*info);
			return (NULL);
		}
	}
	if (i == 5)
		(*info)[4] = 0;
	if (!ft_check_info(*info, 0))
	{
		free(*info);
		return (NULL);
	}
	return (info);
}

void	ft_pinfo_init(t_pinfo *pinfo, int *info)
{
	sem_unlink("fork");
	sem_unlink("possible");
	sem_unlink("report");
	sem_unlink("full");
	pinfo->info = info;
	pinfo->sem_fork = sem_open("fork", O_CREAT, 0666, info[0]);
	pinfo->sem_possible = sem_open("possible", O_CREAT, 0666, info[0] / 2);
	pinfo->sem_report = sem_open("report", O_CREAT, 0666, 1);
	pinfo->sem_full = sem_open("full", O_CREAT, 0666, 1);
	pinfo->sem_mt = (sem_t **)malloc(info[0] * sizeof(sem_t *));
	ft_init_mt(pinfo);
	pinfo->meals = 0;
	pinfo->full = 0;
	pinfo->ph_nbr = -1;
	if ((pinfo->sem_fork == (sem_t *)-1 || pinfo->sem_possible == (sem_t *)-1
			|| pinfo->sem_report == (sem_t *)-1 || pinfo->sem_mt == NULL
			|| pinfo->sem_full == (sem_t *)-1) && ft_close_sems(pinfo))
		ft_pinfo_init(pinfo, info);
}

t_pinfo	ft_init_values(t_pinfo *pinfo, char **argv)
{
	int		*info;

	info = NULL;
	pinfo->info = NULL;
	if (!ft_fill_info(argv, &info))
		return (*pinfo);
	pinfo->pid = (int *)malloc(info[0] * sizeof(int));
	if (!pinfo->pid)
	{
		ft_free_ip(info, pinfo);
		return (*pinfo);
	}
	ft_pinfo_init(pinfo, info);
	return (*pinfo);
}
