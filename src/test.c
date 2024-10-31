#include <minishell.h>
#include <assert.h>
#define TEST_CASES 7

int	main(void)
{
	const char *inputs[TEST_CASES] = {
		// Correct
		"echo hello > test.txt",
		"ls -al",
		"export ARG=hello",
		"cd ios; pod install",
		"cat test.txt | less",
		"cd ios && rm Podfile.lock; pod install",
		"export ARG==MAMMA",
	};
	printf("Running tests for ft_count_tokens\n");
	// size_t count_tokens_values[TEST_CASES] = {
	// 	4, 2, 4, 1, 4, 5
	// };
	// for (size_t i = 0; i < TEST_CASES; i++)
	// {
	// 	size_t val = ft_count_tokens(inputs[i]);
	// 	printf("Input: %s, Expected: %zu, Got: %zu\n", inputs[i], count_tokens_values[i], val);
	// 	// assert(val == values[i]);
	// }
	printf("Running tests for ft_count_sentences\n");
	size_t count_sentences_values[TEST_CASES] = {
		1, 1, 1, 2, 1, 3, 1
	};
	for (size_t i = 0; i < TEST_CASES; i++)
	{
		size_t val = ft_count_sentences((char *)inputs[i]);
		printf("Input: %s, Expected: %zu, Got: %zu\n", inputs[i], count_sentences_values[i], val);
		// assert(val == values[i]);
	}
    return (0);
}
