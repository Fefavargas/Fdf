/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:06:52 by fvargas           #+#    #+#             */
/*   Updated: 2024/11/25 16:20:46 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_empty(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	return (0);
}

int	count_words(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_empty(s[i]))
			i++;
		if (s[i] && !is_empty(s[i]))
			count++;
		while (s[i] && !is_empty(s[i]))
			i++;
	}
	return (count);
}
