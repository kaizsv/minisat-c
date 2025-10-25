#ifndef _MINISAT_C_BINDING_
#define _MINISAT_C_BINDING_

#include <stdbool.h>
#include <stdint.h>

#define minisat_var int
#define minisat_lit int

#define minisat_lbool uint8_t
#define minisat_l_False 0
#define minisat_l_True  1
#define minisat_l_Undef 2

struct minisat_solver* minisat_new();
void minisat_delete(struct minisat_solver *);
bool minisat_okay(struct minisat_solver *);

void minisat_setDecisionVar(struct minisat_solver *, minisat_var, bool);
void minisat_clear_all_decision(struct minisat_solver *);
minisat_var minisat_new_var(struct minisat_solver *, minisat_lbool, bool);
bool minisat_add_clause(struct minisat_solver *, int, const minisat_lit *);
bool minisat_add_clause1(struct minisat_solver *, int);
bool minisat_add_clause2(struct minisat_solver *, int, int);
bool minisat_add_clause3(struct minisat_solver *, int, int, int);
void minisat_release_act(struct minisat_solver *);
void minisat_set_act(struct minisat_solver *);
minisat_lit minisat_get_act(struct minisat_solver *);
bool minisat_solve(struct minisat_solver *, int, const minisat_lit *);

minisat_lbool minisat_modelValue_Var(struct minisat_solver *, minisat_var);
minisat_lit minisat_conflict_nthLit(struct minisat_solver *, int);
int minisat_conflict_len(struct minisat_solver *);

int minisat_nr_occ(struct minisat_solver *, minisat_lit);
void minisat_set_frozen(struct minisat_solver *, minisat_var, bool);
bool minisat_simp_cube(struct minisat_solver *, int, const minisat_lit *);
bool minisat_clean_subsumption(struct minisat_solver *);

#endif
