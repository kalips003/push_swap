#include "push_swap.h"

////////////////////////////////////////////////////////////
// final check, 0 = KO, 1 = OK
int final_test(t_stacks *s)
{
    t_entry *temp;
    int     i;

    if (s->size_b || s->size_a != s->full_size)
        return(0);
    if (s->top_a->num_index || s->top_a->above->num_index != s->full_size - 1)
        return(0);
    temp = s->top_a;
    i = -1;
    while (++i < s->full_size)
    {
        if (temp->num_index != i)
            return (0);
        temp = temp->below;
    }
    return (i);
}

// final check wrapper
void test_output(t_stacks *stacks)
{
    int grade;

    put(CLEAR"\n\t""\033[38;5;58m""FINAL TEST:"RED"\n\n( A ) -> ");
    print_stack(stacks, stacks->top_a, stacks->size_a, 0);
    put(BLUE "\n(index)> ");
    print_stack(stacks, stacks->top_a, stacks->size_a, 1);
    grade = final_test(stacks);
    if (!grade)
        exit_all(stacks, RED"\n\n>\t\t KO\n"RESET, -1, NULL);
    exit_all(stacks, GREEN"\n\n>\t\t BRAVO !\n"RESET, -1, NULL);
}

//////////////////////////////////////////////////////////////////////////////
void (*function_test[])() = {function1, function2, function3, NULL};
//////////////////////////////////////////////////////////////////////////////
//  function 1 to test [ - ]
void    function1(t_stacks *stacks, int i)
{
    t_entry *small;

    small = assign_str_all(stacks);
    if (!small)
        return ;
    if (!i)
        function_cmd_string(stacks, small->algo, 0);
    else
        put("%s\n", small->algo);
    print_header(stacks, 0b111, 1);
    put("\t(%d) %s\n", small->num_index, small->algo);
}
//  function 2 to test [ + ]
void    function2(t_stacks *stacks, int i)
{
    t_entry *temp;
    int j = i;

    give_position(stacks);
    if (i >= 0)
        temp = stacks->top_a;
    else
    {
        temp = stacks->top_b;
        j = abs(i) - 1;
    }
    while (--j >= 0)
        temp = temp->below;
    t_algo  algo;
    fill_stru_algo(stacks, &algo, temp);
    print_stru_algo(&algo);
}
// {
//     t_entry *temp;
//     t_algo  algo;

//     i = -1;
//     temp = stacks->top_a;
//     give_position(stacks);
//     while (++i < stacks->full_size)
//     {
//         if (i == stacks->size_a)
//             (temp = stacks->top_b, put("\n"));
//         fill_stru_algo(stacks, &algo, temp);
//         put("%c)%d) size_blk= %d, size_tar= %d\n", temp->pile, temp->num_index, algo.sizeb_n, algo.sizeb_t);
//         put("num_dist_target = %d\n", algo.num_dist_target);
//         temp = temp->below;
//     }
// }

//  function 3 to test [ . ]
void    function3(t_stacks *stacks)
{
    t_entry *temp;
    int i;
    t_entry *small = assign_str_all(stacks);
    print_header(stacks, 0b111, 1);
    if (small && small->algo)
        put("%s\n", small->algo);
    i = -1;
    temp = stacks->top_a;
    while (++i < stacks->full_size)
    {
        if (i == stacks->size_a)
            temp = stacks->top_b;
        put("%c) -%d- = %s\n", temp->pile, temp->num_index, temp->algo);
        temp = temp->below;
    }
}
//  function 1 to test [ - ]
// {
//     assign_str_all(stacks);
//     if (!i)
//     {
//         int j = -1;
//         t_entry *temp = stacks->top_a;
//         while (++j < stacks->size_a)
//         {
//             if (temp->algo)
//                 put("NUM=%3d;%3d; str=%s=\n", temp->num, temp->num_index, temp->algo);
//             temp = *((t_entry **)(temp) + 4);
//         }
//         j = -1;
//         temp = stacks->top_b;
//         while (++j < stacks->size_b)
//         {
//             if (temp->algo)
//                 put("NUM=%3d;%3d; str=%s=\n", temp->num, temp->num_index, temp->algo);
//             temp = *((t_entry **)(temp) + 4);
//         }
//     }
// }
// {
//     t_entry *temp;

//     i = -1;
//     temp = stacks->top_a;
//     while (++i < stacks->full_size)
//     {
//         if (i == stacks->size_a)
//             (put("\n"), temp = stacks->top_b);
//         put("NUM=%3d;%3d; str=%s=\n", temp->num, temp->num_index, temp->algo);
//         temp = temp->below;
//     }
// }

//  function 2 to test [ + ]
