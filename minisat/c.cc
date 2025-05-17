#include "minisat/simp/SimpSolver.h"

using namespace Minisat;

struct minisat_solver: public SimpSolver {
    vec<Lit> lits;
};

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

bool minisat_eliminate(struct minisat_solver *s, bool turn_off_elim)
{
    return s->eliminate(turn_off_elim);
}

void minisat_freeze_var(struct minisat_solver *s, minisat_var v, bool b)
{
    s->setFrozen(v, b);
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
    s->lits.growTo(len);
    s->lits.setsz(len);
    Lit *lits = (Lit *) s->lits;
    for (int i = 0; i < len; ++i)
        lits[i].x = *ps++;
    return s->addClause_(s->lits);
}

}
