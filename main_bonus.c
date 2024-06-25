#include "push_swap.h"

////////////////////////////////////////////////////////////
int main(int ac, char **av)
{
	t_stacks	stacks;

	if (ac < 2)
		return (put(MSG_NONUM), 0);
	ini_stacks(ac, av, &stacks);
	print_header(&stacks, 0b111, 0);
	tester(&stacks);
	if (!final_test(&stacks))
		end(&stacks, MSG_KO, 0);
	end(&stacks, MSG_OK, 0);
	return (0);
}
////////////////////////////////////////////////////////////
