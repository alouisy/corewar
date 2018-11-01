#include "asm.h"

/*t_op absolu */

t_op    g_op_tab[16] =
{

    {"aff", 1, {T_REG}, 16, 1, 0},
    {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 1, 1},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 1, 0},
    {"st", 2, {T_REG, T_IND | T_REG}, 3, 1, 0},
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 0},
    {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 1, 1},
    {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 1, 0},
    {"live", 1, {T_DIR}, 1, 0, 0},
    {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 1, 0},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 1, 0},
    {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 1, 1},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 1, 0},
    {"fork", 1, {T_DIR}, 12, 0, 1},
    {"add", 3, {T_REG, T_REG, T_REG}, 4, 1, 0},
    {"lfork", 1, {T_DIR}, 15, 0, 1},
    {"zjmp", 1, {T_DIR}, 9, 0, 1}
};

/*
t_op logique
t_op    g_op_tab[9][3] =
{

    {"aff", 1, {T_REG}, 16, 1, 0}
    {"zjmp", 1, {T_DIR}, 9, 0, 1}
    {0, 0, {0}, 0, 0, 0, 0},

    {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 1, 1},
    {0, 0, {0}, 0, 0, 0, 0},
    {0, 0, {0}, 0, 0, 0, 0},

    {0, 0, {0}, 0, 0, 0, 0},
    {0, 0, {0}, 0, 0, 0, 0},
    {0, 0, {0}, 0, 0, 0, 0},

    {"add", 3, {T_REG, T_REG, T_REG}, 4, 1, 0}
    {0, 0, {0}, 0, 0, 0, 0},
    {0, 0, {0}, 0, 0, 0, 0},
    
    {"lfork", 1, {T_DIR}, 15, 0, 1}
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 0},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 1, 0},


    {"st", 2, {T_REG, T_IND | T_REG}, 3, 1, 0},
    {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 1, 1},
    {0, 0, {0}, 0, 0, 0, 0},


	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 1, 0},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 1, 1},
    {0, 0, {0}, 0, 0, 0, 0},

    {"live", 1, {T_DIR}, 1, 0, 0},
    {0, 0, {0}, 0, 0, 0, 0},
    {0, 0, {0}, 0, 0, 0, 0},

    {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 1, 0},
    {0, 0, {0}, 0, 0, 0, 0},
    {0, 0, {0}, 0, 0, 0, 0},

    {"fork", 1, {T_DIR}, 12, 0, 1},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 1, 0},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 1, 0}
};*/
