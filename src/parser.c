#include <stddef.h>
#include "gc_libft.h"
#include "datastructures.h"
#include "minishell.h"

t_darray	*tokenize(char *cmd, t_gc *gc)
{
	t_darray	*tokens;
	size_t		i;
	size_t		j;

	tokens = init_darray(gc);
	i = 0;
	j = 0;
	while (cmd[i + j])
	{
		if (cmd[i + j] == '|')	
		{
			tokens->push(tokens, gc_strtrim(gc_substr(cmd, i, j, gc), " ", gc), gc);
			tokens->push(tokens, "|", gc);
			i += j + 1;
			j = -1;
		}
		j++;
	}
	tokens->push(tokens, gc_strtrim(gc_substr(cmd, i, j, gc), " ", gc), gc);
	return (tokens);
}

t_parser	*init_parser(t_gc *gc)
{
	t_parser	*parser;

	parser = gc_malloc(sizeof(t_gc *) ,gc);
	parser->tokenize = tokenize;
	return (parser);
}
