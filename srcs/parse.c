/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkruszyn <pkruszyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 10:45:39 by kwlodars          #+#    #+#             */
/*   Updated: 2026/08/06 11:08:43 by pkruszyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	add_num(t_ps *ps, char *str, char **split)
{
	long long	val;
	t_node		*node;

	val = 0;
	if (!is_number(str) || !ft_atoi_overflow(str, &val)
		|| duplicate(&ps->a, (int)val))
	{
		free_split(split);
		ps_error(ps);
	}
	node = node_new((int)val);
	if (!node)
	{
		free_split(split);
		ps_error(ps);
	}
	stack_add_back(&ps->a, node);
}

static void	add_arg(t_ps *ps, char *arg)
{
	char	**split;
	int		j;

	split = ft_split(arg, ' ');
	if (!split)
		ps_error(ps);
	if (!split[0])
	{
		free_split(split);
		ps_error(ps);
	}
	j = -1;
	while (split[++j])
		add_num(ps, split[j], split);
	free_split(split);
}

void	parse_args(t_ps *ps, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] == '-')
	{
		set_flag(ps, argv[i]);
		i++;
	}
	if (ps->strategy == NO_STRATEGY)
		ps->strategy = ADAPTIVE;
	while (i < argc)
	{
		add_arg(ps, argv[i]);
		i++;
	}
}
