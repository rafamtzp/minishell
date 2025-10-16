#include "minishell.h"

t_envar	*findmin(t_envar **s, t_envar *prevmin)
{
	t_envar	*candidate;
	t_envar	*ptr;

	ptr = *s;
	candidate = NULL;
	while (ptr != NULL)
	{
		if ((prevmin == NULL || ptr->ascii_sum > prevmin->ascii_sum)
			&& (candidate == NULL || ptr->ascii_sum < candidate->ascii_sum))
			candidate = ptr;
		ptr = ptr->next;
	}
	if (candidate == NULL)
		return (findmin(s, NULL));
	return (candidate);
}

/* could be helpful........
t_envar	*findmax(t_envar **s, t_envar *prevmax)
{
	t_envar	*candidate;
	t_envar	*ptr;

	ptr = *s;
	candidate = NULL;
	while (ptr != NULL)
	{
		if ((prevmax == NULL || ptr->ascii_sum < prevmax->ascii_sum) && (candidate == NULL
				|| ptr->ascii_sum > candidate->ascii_sum))
			candidate = ptr;
		ptr = ptr->next;
	}
	if (candidate == NULL)
		return (findmax(s, NULL));
	return (candidate);
}
*/

static void	set_empty_indices(t_envar **s)
{
	t_envar	*ptr;

	if (*s == NULL || s == NULL)
		return ;
	ptr = *s;
	while (ptr != NULL)
	{
		ptr->ascii_index = -1;
		ptr = ptr->next;
	}
	return ;
}

static void set_ascii_sums(t_envar **s)
{
	t_envar *ptr;
	int i;
	int sum;

	// assuming all vars are properly sent
	if (*s == NULL || s == NULL)
		return ;
	ptr = *s;
	while (ptr != NULL)
	{
		i = 0;
		sum = 0;
		while (ptr->varname[i] != '\0')
			sum += ptr->varname[i++];
		ptr = ptr->next;
	}
}

static int	indices_set(t_envar **s)
{
	t_envar	*ptr;

	ptr = *s;
	if (ptr == NULL)
		return (1);
	while (ptr != NULL)
	{
		if (ptr->ascii_index == -1)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

void	set_ascii_indices(t_envar **s)
{
	t_envar	*ptr;
	t_envar	*min;
	int		i;

	ptr = *s;
	if (ptr == NULL)
		return ;
	set_empty_indices(s);
	min = findmin(s, NULL);
	i = 0;
	while (indices_set(s) != 1)
	{
		if (ptr == min)
		{
			ptr->ascii_index = i++;
			min = findmin(s, min);
			ptr = *s;
		}
		else if (ptr == NULL)
			ptr = *s;
		else
			ptr = ptr->next;
	}
	return ;
}



