#include "gc_libft.h"
#include "minishell.h"

t_lexer	*init_lexer(t_gc *gc)
{
	t_lexer	*lexer;

	lexer = gc_malloc(sizeof(t_gc *) ,gc);
	return (lexer);
}
