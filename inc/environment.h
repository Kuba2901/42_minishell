#ifndef ENVIRONEMENT_H
# define ENVIRONEMENT_H

#include <libft.h>
#include <stdlib.h>
#include <utils.h>

typedef struct  s_env_node
{
    char                *key;
    char                *value;
    struct s_env_node   *next;
    struct s_env_node   *prev;
}   t_env_node;

typedef struct s_env_list
{
    t_env_node  *head;
    t_env_node  *tail;
}   t_env_list;

t_env_list	*create_env_list(const char **envp);
void		free_env_list(t_env_list *list);
void		print_env_list(t_env_list *list);
void		insert_env_node(const char *entry, t_env_list *list);
void		delete_env_node(t_env_list *list, char *key);

#endif