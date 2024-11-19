#ifndef ENVIRONEMENT_H
# define ENVIRONEMENT_H

#include <libft.h>
#include <stdlib.h>
#include <utils.h>
# define ENV_INSERTED 1
# define ENV_UPDATED 2
# define ENV_NOT_FOUND 3
# define ENV_ERROR -1

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

t_env_list	*env_list_initialize(void);
void		env_list_insert_node(t_env_list *list, t_env_node *node);
t_env_node	*env_list_read_node(t_env_list *list, char *key);
void		env_list_delete_node(t_env_list *list, char *key);
t_env_node	*env_node_initialize(const char *entry);
char		*env_node_read(t_env_node *node);
void		env_node_update(t_env_node *node, t_env_node *redundant);
void		env_list_print(t_env_list *list);
char		*env_node_trim_double_quotes(const char *str);
t_env_list	*env_list_init_populated(const char **envp);
void		env_list_delete(t_env_list *list);
void		env_node_delete(t_env_node	*node);
int			env_node_comp(t_env_node *n1, char *key);
void		env_list_insert(t_env_list *list, const char *entry);

#endif