#include "minisat/simp/SimpSolver.h"

using namespace Minisat;

struct minisat_solver: public SimpSolver {
    vec<Lit> clause;
    vec<Lit> assumps;
};

extern "C" {

#include "c.h"

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

minisat_var minisat_new_var(struct minisat_solver *s)
{
    return s->newVar();
}

bool minisat_eliminate(struct minisat_solver *s, bool turn_off_elim)
{
    return s->eliminate(turn_off_elim);
}

void minisat_freeze_var(struct minisat_solver *s, minisat_var v, bool b)
{
    s->setFrozen(v, b);
}

static inline minisat_lbool toC(lbool a)
{
    return a == l_True  ? minisat_l_True
         : a == l_False ? minisat_l_False
         : minisat_l_Undef;
}

minisat_lbool minisat_modelValue_Var(struct minisat_solver *s, minisat_var v)
{
    return toC(s->modelValue(v));
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
    s->assumps.clear();
    for (int i = 0; i < len; ++i)
        s->assumps.push(toLit(*ps++));
    return s->solveLimited(s->assumps) == l_True;
}

bool minisat_add_clause(struct minisat_solver *s, int len, const minisat_lit *ps)
{
    s->clause.clear();
    for (int i = 0; i < len; ++i)
        s->clause.push(toLit(*ps++));
    return s->addClause_(s->clause);
}

}
