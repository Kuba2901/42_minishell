#include <minishell.h>
#include <assert.h>
#define TEST_CASES 6

int	main(void)
{
	const char *inputs[TEST_CASES] = {
		// Correct
		"echo hello > test.txt",
		"ls -al",
		"export ARG=hello",
		"  pwd  ",
		"cat test.txt | less",
		"cd ios && rm Podfile.lock",
		"export ARG==MAMMA",
	};
	size_t values[TEST_CASES] = {
		4, 2, 4, 1, 4, 5
	};
	for (size_t i = 0; i < TEST_CASES; i++)
	{
		size_t val = ft_count_tokens(inputs[i]);
		printf("Input: %s, Expected: %zu, Got: %zu\n", inputs[i], values[i], val);
		// assert(val == values[i]);
	}
    return (0);
}
