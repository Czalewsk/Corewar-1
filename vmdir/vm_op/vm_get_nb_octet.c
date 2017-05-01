#include "vm_op.h"

int     vm_get_nb_octet(int *nb_octet, int ocp, int nop);
{
    int noct;
    int i;
    int tocp;

    i = 0;
    noct = 0;
    if (!(ocp & 1 == 1 || (ocp >> 1) & 1 == 1))
    {
        while (i < op_tab[nop].nb_p)
        {
            tocp = (ocp >> (2 * i + 1)) & 3
            if (tocp == 1)
                nb_octet[i] == T_REG;
            else if (tocp == 2)
                nb_octet[i] = op_tab[i].index ? T_IND : T_DIR;
            else if (tocp == 3)
                nb_octet[i] = 2;
            noct += nb_octet[i];
            i++;
        }
    }
    return (noct + 2);
}
