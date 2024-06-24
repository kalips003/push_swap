#include "push_swap.h"

static char *smallest_str(int nb, ...);
static void lets_r(char *c1, char *c2);
static char *lets_rr(char *s1, char *s2);
static void lets_rrr(t_algo *a, t_entry *one, t_entry *two, int bit);
int algo_aa(t_algo *a);
int algo_bb(t_algo *a);
int algo_ab(t_algo *a);
int algo_ba(t_algo *a);
int assign_str(t_stacks *s, t_entry *num);

static char *smallest_str(int nb, ...)
{
    va_list	args;
    int small;
    int size;
    char *smallest;
    char *string;

    smallest = NULL;
    small = INT_MAX;
    va_start(args, nb);
    while (--nb >= 0)
    {
        string = va_arg(args, char *);
        size = len(string);
        if (size && (size < small))
        {
            if (smallest)
                free(smallest);
            small = size;
            smallest = string;
        }
        else
            free(string);
    }
    va_end(args);
    return (smallest);
}

static void lets_r(char *c1, char *c2)
{
    if ((*c1 == '2' && *c2 == '3') || (*c1 == '3' && *c2 == '2'))
    {
        *c1 = '4';
        *c2 = '4';
    }
    else if ((*c1 == '5' && *c2 == '6') || (*c1 == '6' && *c2 == '5'))
    {
        *c1 = '7';
        *c2 = '7';
    }
    else if ((*c1 == '8' && *c2 == '9') || (*c1 == '9' && *c2 == '8'))
    {
        *c1 = ':';
        *c2 = ':';
    }
}

static char *lets_rr(char *s1, char *s2)
{
    int len1;
    int len2;
    int i;

    len1 = len(s1);
    len2 = len(s2);
    i = -1;
    while (++i < len1 && i < len2)
        lets_r(&s1[i], &s2[i]);
    if (!s1[i])
    {
        free(s1);
        return (s2);
    }
    else
    {
        free(s2);
        return (s1);
    }
}

/*
'2' (ASCII value 50): 00110010
'3' (ASCII value 51): 00110011
'4' (ASCII value 52): 00110100

'5' (ASCII value 53): 00110101
'6' (ASCII value 54): 00110110
'7' (ASCII value 55): 00110111

'8' (ASCII value 56): 00111000
'9' (ASCII value 57): 00111001
':' (ASCII value 58): 00111010
*/


//  bit 0b10 = one on -1
//  bit 0b00 = one on 0
//  bit 0b01 = one on -1
static void lets_rrr(t_algo *a, t_entry *one, t_entry *two, int bit)
{
    a->str1 = lets_rr(str("%.*c", one->dist_p + ((bit & 2) >> 1), '5' + (one->pile_c == 'B')), str("%.*c", two->dist_p + (bit & 1), '5' + (two->pile_c == 'B')));
    a->str2 = lets_rr(str("%.*c", one->dist_n - ((bit & 2) >> 1), '8' + (one->pile_c == 'B')), str("%.*c", two->dist_n - (bit & 1), '8' + (two->pile_c == 'B')));
    a->str3 = fjoin(2, 0b11, str("%.*c", one->dist_p + ((bit & 2) >> 1), '5' + (one->pile_c == 'B')), str("%.*c", two->dist_n - (bit & 1), '8' + (two->pile_c == 'B')));
    a->str4 = fjoin(2, 0b11, str("%.*c", one->dist_n - ((bit & 2) >> 1), '8' + (one->pile_c == 'B')), str("%.*c", two->dist_p + (bit & 1), '5' + (two->pile_c == 'B')));
    a->str1 = smallest_str(4, a->str1, a->str2, a->str3, a->str4);
}

///////////////////////////////////////////////////////////////////////////////////////////
// (0) pb  (1) pa  (2) sa  (3) sb  (4) ss  (5) ra  (6) rb  (7) rr  (8) rra  (9) rrb (:) rrr
int algo_aa(t_algo *a)
{
    if (a->sizeb_t > 0)
    {
        a->str1 = str("%.*c%.*c%.*c", abs(a->num->dist + 1), '5' + 3 * (a->num->dist < 0), a->num_d_tar_plus - 1, '0', min(a->sizeb_n, a->sizeb_t), '5' + 3 * (a->sizeb_n < a->sizeb_t));

        a->str2 = str("%.*c%.*c%.*c%.*c", abs(a->blk_num->dist), '5' + 3 * (a->blk_num->dist < 0), a->sizeb_n, '0' \
                    , min(a->num_d_tar_plus, a->bt_dist_bn + a->sizeb_t) - 1, '5' + 3 * (a->bt_dist_bn + a->sizeb_t < a->num_d_tar_plus), min(a->sizeb_n, a->sizeb_t), '0' + (a->sizeb_t > a->sizeb_n));

        a->str3 = str("%.*c%.*c%.*c5%.*c%.*c", abs(a->target->dist), '5' + 3 * (a->target->dist < 0), a->sizeb_t, '0' \
                    , min(a->num_d_tar_plus, a->bt_dist_bn + a->sizeb_n) - 1, '5' + 3 * (a->bt_dist_bn + a->sizeb_n > a->num_d_tar_plus) \
                    , a->sizeb_t, '1', min(a->sizeb_n, a->sizeb_t), '5' + 3 * (a->sizeb_n < a->sizeb_t));
        a->num->algo = smallest_str(3, a->str1, a->str2, a->str3);

    }
    else if (a->sizeb_t == -2)
        a->num->algo = str("%.*c2", abs(a->blk_tar->dist), '5' + 3 * (a->blk_tar->dist < 0));
    else if (a->sizeb_t < 0)
    {
        a->str1 = str("%.*c%*s", abs(a->blk_tar->dist), '5' + 3 * (a->blk_tar->dist < 0), -a->sizeb_t, "09");
        a->str2 = str("%.*c0%*s", abs(a->target->dist), '5' + 3 * (a->target->dist < 0), -a->sizeb_t - 1, "80");
        a->num->algo = smallest_str(2, a->str1, a->str2);
    }
    if (a->sizeb_n == 1 && (a->sizeb_t == 1 || a->sizeb_t < -2))
    {
        a->str1 = str("%.*c%.*c5", abs(a->target->dist + 1), '5' + 3 * (a->target->dist < 0), a->bt_dist_bn - abs(a->sizeb_t), '0');
        a->str2 = str("%.*c%.*c%.*c0", abs(a->blk_tar->dist), '5' + 3 * (a->blk_tar->dist < 0), abs(a->sizeb_t), '0', min(a->num_d_tar_plus - abs(a->sizeb_t) + 1, a->bt_dist_bn - abs(a->sizeb_t))
                , '5' + 3 * (a->num_d_tar_plus - abs(a->sizeb_t) < a->bt_dist_bn - abs(a->sizeb_t)));
        a->str3 = str("%.*c0%.*c15", abs(a->num->dist), '5' + 3 * (a->num->dist < 0) \
                , min(a->num_d_tar_plus - 1, a->bt_dist_bn - abs(a->sizeb_t) - 1) + 1\
                , '5' + 3 * (a->num_d_tar_plus - 1 > a->bt_dist_bn - abs(a->sizeb_t) - 1));
        a->num->algo = smallest_str(4, a->num->algo, a->str1, a->str2, a->str3);
    }

    // (free(a->num->algo), a->num->algo = NULL);
    return (len(a->num->algo));
}

///////////////////////////////////////////////////////////////////////////////////////////
// (0) pb  (1) pa  (2) sa  (3) sb  (4) ss  (5) ra  (6) rb  (7) rr  (8) rra  (9) rrb (:) rrr
int algo_bb(t_algo *a)
{
    if (a->sizeb_t > 0)
    {
        a->str1 = str("%.*c%.*c%.*c", abs(a->target->dist + 1), '6' + 3 * (a->target->dist < 0), a->num_d_tar_plus - 1, '1', min(a->sizeb_n, abs(a->sizeb_t)), '6' + 3 * (a->sizeb_n > a->sizeb_t));

        a->str2 = str("%.*c%.*c%.*c%.*c", abs(a->blk_tar->dist), '6' + 3 * (a->blk_tar->dist < 0), abs(a->sizeb_t), '1' 
                    , min(a->num_d_tar_plus, a->bt_dist_bn + a->sizeb_n) - 1, '6' + 3 * (a->bt_dist_bn + a->sizeb_n < a->num_d_tar_plus), min(a->sizeb_n, abs(a->sizeb_t)), '0' + (a->sizeb_t > a->sizeb_n));

        a->str3 = str("%.*c%.*c%.*c6%.*c%.*c", abs(a->num->dist), '6' + 3 * (a->num->dist < 0), a->sizeb_n, '1' \
                    , min(a->num_d_tar_plus, a->bt_dist_bn + abs(a->sizeb_t)) - 1, '6' + 3 * (a->bt_dist_bn + abs(a->sizeb_t) > a->num_d_tar_plus) \
                    , a->sizeb_n, '0', min(a->sizeb_n, abs(a->sizeb_t)), '6' + 3 * (a->sizeb_n > a->sizeb_t));
        a->num->algo = smallest_str(3, a->str1, a->str2, a->str3);
    }
    else if (a->sizeb_t == -2)
        a->num->algo = str("%.*c3", abs(a->target->dist), '6' + 3 * (a->target->dist < 0));
    else if (a->sizeb_t < 0)
    {
        a->str1 = str("%.*c%*s", abs(a->target->dist), '5' + 3 * (a->target->dist < 0), -a->sizeb_t, "18");
        a->str2 = str("%.*c1%*s", abs(a->blk_tar->dist), '5' + 3 * (a->blk_tar->dist < 0), -a->sizeb_t - 1, "91");
        a->num->algo = smallest_str(2, a->str1, a->str2);
    }
    if (a->sizeb_n == 1 && (a->sizeb_t == 1 || a->sizeb_t < -2))
    {
        a->str1 = str("%.*c%.*c6", abs(a->num->dist + 1), '6' + 3 * (a->num->dist < 0), a->bt_dist_bn - abs(a->sizeb_t), '1');
        // a->num->algo = str("%.*c%.*c%.*c1", abs(a->target->dist), '6' + 3 * (a->target->dist < 0), abs(a->sizeb_t), '1', min(a->num_d_tar_plus - abs(a->sizeb_t) + 1, a->bt_dist_bn - abs(a->sizeb_t))
        //         , '6' + 3 * (a->num_d_tar_plus - abs(a->sizeb_t) < a->bt_dist_bn - abs(a->sizeb_t)));
        // a->str3 = str("%.*c0%.*c15", abs(a->num->dist), '5' + 3 * (a->num->dist < 0) 
        //         , min(a->num_d_tar_plus - 1, a->bt_dist_bn - abs(a->sizeb_t) - 1) + 1
        //         , '5' + 3 * (a->num_d_tar_plus - 1 > a->bt_dist_bn - abs(a->sizeb_t) - 1));
        a->num->algo = smallest_str(2, a->num->algo, a->str1);
    }


    // (free(a->num->algo), a->num->algo = NULL);
    return (len(a->num->algo));
}

///////////////////////////////////////////////////////////////////////////////////////////
// (0) pb  (1) pa  (2) sa  (3) sb  (4) ss  (5) ra  (6) rb  (7) rr  (8) rra  (9) rrb (:) rrr
int algo_ab(t_algo *a)
//        OK!
{
    if (a->sizeb_t > 0)
    {
        lets_rrr(a, a->num, a->blk_tar, 0b10);
        a->num->algo = fjoin(2, 0b11, a->str1, str("%.*c%.*c", a->sizeb_t, '1', min(a->sizeb_n, a->sizeb_t), '5' + 3 * (a->sizeb_t > a->sizeb_n)));
        lets_rrr(a, a->blk_num, a->target, 0b01);
        a->str1 = fjoin(2, 0b11, a->str1, str("%.*c%.*c", a->sizeb_n, '0', min(a->sizeb_n, a->sizeb_t), '6' + 3 * (a->sizeb_t < a->sizeb_n)));
        a->num->algo = smallest_str(2, a->str1, a->num->algo);
    }
    else if (a->sizeb_t == -2)
    {
        lets_rrr(a, a->num, a->target, 0b10);
        a->num->algo = fjoin(2, 0b11, a->str1, str("112%.*c", min(a->sizeb_n, -a->sizeb_t), '5' + 3 * (-a->sizeb_t < a->sizeb_n)));
    }
    else if (a->sizeb_t < 0)
    {
        lets_rrr(a, a->num, a->target, 0b10);
        a->num->algo = fjoin(2, 0b11, a->str1, str("%*s", -a->sizeb_t, "15"));
        lets_rrr(a, a->num, a->blk_tar, 0b10);
        a->str1 = fjoin(2, 0b11, a->str1, str("%*s%.*c", -a->sizeb_t, "91", min(a->sizeb_n, -a->sizeb_t), '5' + 3 * (-a->sizeb_t > a->sizeb_n)));
    }
    if (a->sizeb_n == 1 && (a->sizeb_t == 1 || a->sizeb_t < -2))
    {
        lets_rrr(a, a->num, a->target, 0b00);
        a->num->algo = smallest_str(2, a->num->algo, fjoin(2, 0b11, a->str1, str("0")));
    }

    // (free(a->num->algo), a->num->algo = NULL);
    return (len(a->num->algo));
}

///////////////////////////////////////////////////////////////////////////////////////////
// (0) pb  (1) pa  (2) sa  (3) sb  (4) ss  (5) ra  (6) rb  (7) rr  (8) rra  (9) rrb (:) rrr
int algo_ba(t_algo *a)
//        OK!
{
    if (a->sizeb_t > 0)
    {
        lets_rrr(a, a->num, a->target, 0b00);
        a->num->algo = fjoin(2, 0b11, a->str1, str("%.*c", min(a->sizeb_n, a->sizeb_t), '1' - (a->sizeb_n > a->sizeb_t)));
    }
    else if (a->sizeb_t == -2)
    {
        lets_rrr(a, a->num, a->blk_tar, 0b00);
        a->num->algo = fjoin(2, 0b11, a->str1, str("2%.*c", min(a->sizeb_n, 2), '1' - (a->sizeb_n > 2)));
    }
    else if (a->sizeb_t < 0)
    {
        lets_rrr(a, a->num, a->target, 0b00);
        a->num->algo = fjoin(2, 0b11, a->str1, str("0%*s", -a->sizeb_t - 1, "80"));
        lets_rrr(a, a->num, a->blk_tar, 0b00);
        a->str1 = fjoin(2, 0b11, a->str1, str("%*s0%.*c", -a->sizeb_t - 1, "06", min(a->sizeb_n + 1, -a->sizeb_t - 1), '6' + 3 * (a->sizeb_n + 1 > -a->sizeb_t - 1)));
        a->num->algo = smallest_str(2, a->num->algo, a->str1);
    }
    if (a->sizeb_n == 1 && (a->sizeb_t == 1 || a->sizeb_t < -2))
    {
        lets_rrr(a, a->num, a->target, 0b01);
        a->num->algo = smallest_str(2, a->num->algo, fjoin(2, 0b11, a->str1, str("15")));
    }
    // (free(a->num->algo), a->num->algo = NULL);
    return (len(a->num->algo));
}




////////////////////////////////////////////////////////////
//  #    initialize algori struct
// (0) pb  (1) pa  (2) sa  (3) sb  (4) ss  (5) ra  (6) rb  (7) rr  (8) rra  (9) rrb (:) rrr
int assign_str(t_stacks *s, t_entry *num)
{
    t_algo a;

    fill_stru_algo(s, &a, num);
    int bit = (a.num->pile_c == 'A') << 1 | (a.target->pile_c == 'A');
    // if  (num->dist == 1 && a.sizeb_n == -1) -> 'sa'
    if (a.num_dist_target == 1 || a.num_dist_target == -1)
        return (0);
    if (help_modulo(s, num, *((t_entry **)(num) + (num->pile_c == 'A'))) == -1)
        return (0);
    if (bit == 0)// num top stack, swap !! 7-10-8-11 > 10-7-8-11
        return(algo_bb(&a));
    else if (bit == 1)
        return(algo_ba(&a));
    else if (bit == 2)
        return(algo_ab(&a));
    else
        return(algo_aa(&a));
    return (0);
}

// typedef int		(*t_func)(va_list, t_flags *);
// int (*function_tab[4])(t_algo *) = {algo_aa, algo_bb, algo_ab, algo_ba};

// int algo_tab(t_algo *a, int bit)
// {
//     int (*algo_tab[8])(t_algo *) = {
//         algo_bb,
//         algo_ba,
//         algo_ab,
//         algo_aa,
//         algo_bb_neg,
//         algo_ba_neg,
//         algo_ab_neg,
//         algo_aa_neg};

// }


//  ! un seul block restant (of size 2!) dans B > NULL string?

//  if NUm end of negative blk? [(3) 2 1 0] ..........?
