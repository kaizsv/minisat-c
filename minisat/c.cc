#include "minisat/core/Solver.h"

using namespace Minisat;

struct minisat_solver: public Solver {};

extern "C" {

#include "c.h"

static const lbool fromC[3] = { l_False, l_True, l_Undef, };
static const minisat_lbool toC[3] = {
    minisat_l_True,
    minisat_l_False,
    minisat_l_Undef,
};

struct minisat_solver* minisat_new()
{
    struct minisat_solver *s = new minisat_solver();
    s->budgetOff();
    return s;
}

void minisat_delete(struct minisat_solver *s)
{
    delete s;
}

bool minisat_okay(struct minisat_solver *s)
{
    return s->okay();
}

void minisat_setDecisionVar(struct minisat_solver *s, minisat_var v, bool b)
{
    s->setDecisionVar(v, b);
}

minisat_var minisat_new_var(struct minisat_solver *s,
                            minisat_lbool b, bool undc)
{
    return s->newVar(fromC[b], undc);
}

minisat_lbool minisat_modelValue_Var(struct minisat_solver *s, minisat_var v)
{
    return toC[toInt(s->modelValue(v))];
}

minisat_lit minisat_conflict_nthLit(struct minisat_solver *s, int i)
{
    return toInt(s->conflict[i]);
}

int minisat_conflict_len(struct minisat_solver *s)
{
    return s->conflict.size();
}

bool minisat_solve(struct minisat_solver *s, int len, const minisat_lit *ps)
{
    return s->solveLimited(len, ps) == l_True;
}

bool minisat_add_clause(struct minisat_solver *s, int len, const minisat_lit *ps)
{
    return s->add_clause(len, ps);
}

bool minisat_add_clause1(struct minisat_solver *s, int l1)
{
    return s->add_clause(l1);
}

bool minisat_add_clause2(struct minisat_solver *s, int l1, int l2)
{
    return s->add_clause(l1, l2);
}

bool minisat_add_clause3(struct minisat_solver *s, int l1, int l2, int l3)
{
    return s->add_clause(l1, l2, l3);
}

}
