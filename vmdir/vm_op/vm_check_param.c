int vm_check_param(int ocp, unsigned int n_op)
{
    int i;

    i = 0;
    if (ocp & 1 == 1 || (ocp >> 1) & 1 == 1)
        return (i);
    ocp >>= 2;
    while (i < 3 && ocp > 0)
    {
        if (i >= op_tab[n_op].nb_p)
            return (0);
        tocp = (ocp >> (2 * i + 1)) & 3
        if (tocp == 1 && ((op_tab[n_op].type_param[i]) & T_REG) == 0)
            return (0);
        else if (tocp == 2 && ((op_tab[n_op].type_param[i]) & T_DIR) == 0)
            return (0);
        else if (tocp == 3 && ((op_tab[n_op].type_param[i]) & T_IND) == 0)
            return (0);
        else if (tocp == 0)
            return (0);
    }
    return(i == op_tab[n_op].nb_p)
}
