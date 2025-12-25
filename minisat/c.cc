#include "minisat/simp/SimpSolver.h"

using namespace Minisat;

struct minisat_solver: public SimpSolver {};

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
    s->use_rcheck = false;
    s->use_elim = false;
    s->use_asymm = false;
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

void minisat_clear_all_decision(struct minisat_solver *s)
{
    s->clearAllDecision();
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

bool minisat_has_conflict_lit(struct minisat_solver *s, minisat_lit lit)
{
    return s->conflict.has(toLit(lit));
}

bool minisat_solve(struct minisat_solver *s, int len, const minisat_lit *ps)
{
    return s->Solver::solveLimited(len, ps) == l_True;
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

void minisat_release_act(struct minisat_solver *s)
{
    s->release_temorary();
}

void minisat_set_act(struct minisat_solver *s)
{
    Var act = s->newVar(fromC[minisat_l_True], false);
    s->temporary_act = act << 1 | 1;
}

minisat_lit minisat_get_act(struct minisat_solver *s)
{
    return s->temporary_act;
}

double minisat_var_activity(struct minisat_solver *s, minisat_var v)
{
    return s->activity[v];
}

void minisat_set_frozen(struct minisat_solver *s, minisat_var v, bool b)
{
    s->setFrozen(v, b);
}

bool minisat_simp_cube(struct minisat_solver *s, int len, const minisat_lit *ps)
{
    return s->SimpSolver::addCube(len, ps);
}

bool minisat_clean_subsumption(struct minisat_solver *s)
{
    return s->clean_subsumption();
}

}
