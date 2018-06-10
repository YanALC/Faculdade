#include"ciclo.h"

ciclo::ciclo(uint ifn, uint id, uint ex, uint wb)
{
        IF.reserve(ifn);
        ID.reserve(id);
        EX.reserve(ex);
        WB.reserve(wb);
        IF.assign(ifn,-1);
        ID.assign(id,-1);
        EX.assign(ex,-1);
        WB.assign(wb,-1);
}
