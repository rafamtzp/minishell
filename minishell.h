



// command table struct

typedef struct s_cmdtable
{
	char *command;
	
	struct s_cmdtable *next;
} t_cmdtable;