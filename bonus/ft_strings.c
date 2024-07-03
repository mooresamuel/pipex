/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:36:43 by samoore           #+#    #+#             */
/*   Updated: 2024/01/15 17:27:52 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (0);
	while (j < i)
	{
		dst[j] = s[j];
		j++;
	}
	dst[j] = 0;
	return (dst);
}

static int	s_len(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*res_p;

	if (!s1 && !s2)
		return (NULL);
	res = malloc(sizeof(char) * (s_len(s1) + s_len(s2) + 1));
	if (!res)
		return (0);
	res_p = res;
	while (s1 && *s1)
		*res++ = *s1++;
	while (s2 && *s2)
		*res++ = *s2++;
	*res = 0;
	return (res_p);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}
