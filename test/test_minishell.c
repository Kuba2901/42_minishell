#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <minishell.h>

void test_example() {
    CU_ASSERT(1 + 1 == 2);
}

void	test_ft_count_sentences() {
	const char *inputs[7] = {
		"echo hello > test.txt",
		"ls -al",
		"export ARG=hello",
		"cd ios; pod install",
		"cat test.txt | less",
		"cd ios && rm Podfile.lock; pod install",
		"export ARG==MAMMA",
	};
	size_t count_sentences_values[7] = {
		1, 1, 1, 2, 1, 3, 1
	};
	for (size_t i = 0; i < 7; i++)
	{
		size_t val = ft_count_sentences((char *)inputs[i]);
		CU_ASSERT_EQUAL(val, count_sentences_values[i]);
	}
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Minishell Test Suite", 0, 0);
    CU_add_test(suite, "FT_COUNT_SENTENCES", test_ft_count_sentences);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}