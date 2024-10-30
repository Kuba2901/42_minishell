#include <minishell.h>
#include <assert.h>

int	main(void)
{
	const char *inputs[] = {
		"echo hello > test.txt",
		"ls -al",
		"export ARG=hello"
	};
	size_t values[] = {
		4, 2, 4
	};
	for (size_t i = 0; i < 3; i++)
	{
		size_t val = ft_count_tokens(inputs[i]);
		printf("Input: %s, Expected: %zu, Got: %zu\n", inputs[i], values[i], val);
		// assert(val == values[i]);
	}
    return (0);
}
