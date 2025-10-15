#include "minishell.h"
char *getvarname(char *new_var)
{
	char *varname;
	char *ptr;

	varname = ft_strdup(new_var); // remember to free!
	ptr = varname;
	while (ptr != '=')
		ptr++;
	*ptr = '\0';
	return (varname);
}

t_envar *envlst_new(t_envar **envars, char *new_var)
{
	t_envar	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->varname = getvarname(new_var);
	new->value = ft_strchr(new_var, '=') + 1;
	//IDK if this is a good way to allocate these
	new->next = NULL;
	return (new);
}

void envlst_add_back(t_envar **envars, t_envar *new)
{
	t_envar	*ptr;

	if (ptr == 0 || new == 0)
		return ;
	ptr = *envars;
	if (*envars == 0)
	{
		*envars = new;
		return ;
	}
	while (ptr->next != 0)
		ptr = ptr->next;
	ptr->next = new;
}