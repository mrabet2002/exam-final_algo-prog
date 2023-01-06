#include <stdio.h>
#include <stdlib.h>

#ifndef GUSS_H

#define GUSS_H

//**************************************************************************//
//************************ Structures de donnees ***************************//
//**************************************************************************//
typedef struct vecteur_t
{
    double *data;
    int N;
} vecteur_t;

typedef struct matrice_t
{
    double **data;
    int N;
} matrice_t;

typedef struct system_t
{
    matrice_t A;
    vecteur_t x;
    vecteur_t y;
    int N;
} system_t;
//*******************************************************************************//
//************************* Declaration des fonctions ***************************//
//*******************************************************************************//
vecteur_t create_vect(int n);
matrice_t create_mat(int n);
system_t create_sys(int n);
system_t scan_sys();
void print_sys(system_t sys);
void swap(double *a, double *b);
int swap_line(system_t *sys, int line_index);
system_t triangularize_sys(system_t sys);
int is_cramer(system_t sys);
int solve_sys(system_t *sys);

#endif