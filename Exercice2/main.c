#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

vecteur_t create_vect(int n)
{
    vecteur_t v;
    v.N = n;
    v.data = (double *)malloc(v.N * sizeof(double));
    return v;
}
matrice_t create_mat(int n)
{
    matrice_t m;
    int i;
    m.N = n;
    m.data = (double **)malloc(m.N * sizeof(double *));
    for (i = 0; i < m.N; i++)
        m.data[i] = (double *)malloc(m.N * sizeof(double));
    return m;
}
system_t create_sys(int n)
{
    system_t sys;
    sys.A = create_mat(n);
    sys.x = create_vect(n);
    sys.y = create_vect(n);
    sys.N = n;
    return sys;
}
system_t scan_sys()
{
    system_t sys;
    int n, i, j;
    printf("Donnez la taille du system : ");
    scanf("%d", &n);
    sys = create_sys(n);
    printf("Donnez les coefficients aij et les seconds membres bi : \n");
    for (i = 0; i < sys.N; i++)
    {
        for (j = 0; j < sys.N; j++)
        {
            printf("A%d%d = ", i + 1, j + 1);
            scanf("%lf", &sys.A.data[i][j]);
        }
        printf("b%d = ", i + 1);
        scanf("%lf", &sys.y.data[i]);
    }
    return sys;
}
/**
 * J'ajoute cette fonction pour afficher les systemes
 * Dans le but de tester le programme
 */
void print_sys(system_t sys)
{
    int i, j;
    for (i = 0; i < sys.N; i++)
    {
        for (j = 0; j < sys.N; j++)
        {
            printf("%.2fX%d", sys.A.data[i][j], j + 1);
            if (j < sys.N - 1)
                printf(" + ");
        }
        printf(" = %.2f\n", sys.y.data[i]);
    }
}
/**
 * Cette fonction permet de permuter deux doubles
 * Utiliser dans la fonction swap_line
 */
void swap(double *a, double *b)
{
    *a += *b;
    *b = *a - *b;
    *a -= *b;
}
/**
 * Cette fonction permet de permuter une ligne avec une autre
 * si le pivot est nul
 */
int swap_line(system_t *sys, int line_index)
{
    int i, j;
    for (i = 0; i < sys->N - 1; i++)
    {
        if ((i != line_index) && (sys->A.data[i][line_index] != 0))
        {
            for (j = 0; j < sys->N; j++)
                swap(&sys->A.data[line_index][j], &sys->A.data[i][j]);
            swap(&sys->y.data[line_index], &sys->y.data[i]);
            return 1;
        }
    }
    return 0;
}
system_t triangularize_sys(system_t sys)
{
    int i, j, k, pivot_is_valid = 1;
    double pivot;
    system_t tri_sys = sys;
    for (i = 0; i < tri_sys.N; i++)
    {
        if (tri_sys.A.data[i][i] == 0)
            swap_line(&tri_sys, i);
        if (pivot_is_valid)
        {
            for (j = i + 1; j < tri_sys.N; j++)
            {
                pivot = tri_sys.A.data[j][i] / tri_sys.A.data[i][i];
                for (k = i; k < tri_sys.N; k++)
                {
                    tri_sys.A.data[j][k] = tri_sys.A.data[j][k] - pivot * tri_sys.A.data[i][k];
                }
                tri_sys.y.data[j] = tri_sys.y.data[j] - pivot * tri_sys.y.data[i];
            }
        }
        else
        {
            printf("le systeme n'est pas regulier!\n");
            return sys;
        }
    }
    return tri_sys;
}
int is_cramer(system_t sys)
{
    for (int i = 0; i < sys.N; i++)
        if (sys.A.data[i][i] == 0)
            return 0;
    return 1;
}
int solve_sys(system_t *sys)
{
    int i, j;
    double sum = 0;
    system_t tri_sys = triangularize_sys(*sys);
    if (is_cramer(tri_sys))
    {
        for (i = sys->N - 1; i >= 0; i--)
        {
            for (j = i + 1; j < sys->N; j++)
                sum += sys->A.data[i][j] * sys->x.data[j];
            sys->x.data[i] = (sys->y.data[i] - sum) / sys->A.data[i][i];
            sum = 0;
        }
        return 1;
    }
    else
    {
        printf("Le systeme admet une infinite ou n'admet pas de solution!\n");
        return 0;
    }
}
//*****************************************************************************//
//*********************************** Main ************************************//
//*****************************************************************************//
int main(int argc, char const *argv[])
{
    system_t sys = scan_sys();
    int i;

    //******************** Pour le test *********************//
    // system_t sys = create_sys(4);
    // sys.A.data[0][0] = 0;
    // sys.A.data[0][1] = 1;
    // sys.A.data[0][2] = 0;
    // sys.A.data[0][3] = 3;
    // sys.y.data[0] = 4;

    // sys.A.data[1][0] = 2;
    // sys.A.data[1][1] = 1;
    // sys.A.data[1][2] = -1;
    // sys.A.data[1][3] = 1;
    // sys.y.data[1] = 1;

    // sys.A.data[2][0] = 3;
    // sys.A.data[2][1] = -1;
    // sys.A.data[2][2] = -1;
    // sys.A.data[2][3] = 2;
    // sys.y.data[2] = -3;

    // sys.A.data[3][0] = -1;
    // sys.A.data[3][1] = 2;
    // sys.A.data[3][2] = 3;
    // sys.A.data[3][3] = -1;
    // sys.y.data[3] = 4;

    // print_sys(triangularize_sys(sys));
    //******************** Pour le test *********************//

    print_sys(sys);
    if (solve_sys(&sys))
    {
        printf("Le systeme admet une solution unique : (");
        for (i = 0; i < sys.N; i++)
            printf("%.2f,", sys.x.data[i]);
        printf("\b)\n");
    }

    return 0;
}
