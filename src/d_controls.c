#include "push_swap.h"

int		function_cmd_string(t_stacks *stacks, char *instructions, char sw2);
void	function_cmd(t_stacks *stacks, int i, char sw2);

///////////////////////////////////////////////////////////////////////////////]
//	#	takes in "0123456789a11", and do it, instructions can be NULL
//  if sw2: print instructions beeing executed
int	function_cmd_string(t_stacks *stacks, char *instructions, char sw2)
{
	int i = -1;
	int b;

	if (!instructions)
		return (0);
	while (instructions[++i])
	{
		b = wii_wrapper(instructions[i]);
		if (b >= 0)
			function_cmd(stacks, b, sw2);
	}
	return (len(instructions));
}

///////////////////////////////////////////////////////////////////////////////]
//	#	COMMANDS FUNCTION
//  sw2: 0 = execute; 1 = execute and print
void	function_cmd(t_stacks *stacks, int i, char sw2)
{
	f_cmd	function_cmd[11];

	function_cmd[0] = pb;
	function_cmd[1] = pa;
	function_cmd[2] = sa;
	function_cmd[3] = sb;
	function_cmd[4] = ss;
	function_cmd[5] = ra;
	function_cmd[6] = rb;
	function_cmd[7] = rr;
	function_cmd[8] = rra;
	function_cmd[9] = rrb;
	function_cmd[10] = rrr;
	function_cmd[i](stacks, sw2);
}
