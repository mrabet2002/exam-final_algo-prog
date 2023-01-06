#include <stdio.h>
#include "gauss.h"

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
