#include "ipasir.h"
#include "ipasir_max.h"
#include "Solver.h"
#include "ProblemInstance.h"
#include <vector>
#include <complex>
#include <cassert>

using std::vector;
using namespace std;

#define UNUSED(x) (void)(x)

struct LMHSSolver {
    ~LMHSSolver()
    {
        delete solver;
        delete instance;
    }

    LMHSSolver()
    {
        instance = new ProblemInstance;
        solver = new Solver(*instance);
        solution_weight = -1;
    }

    Solver* solver;
    ProblemInstance* instance;
    vector<int> clause;
    vector<int> assumptions;
    vector<int> solution;
    double solution_weight;
};

// define SAT solver name
#if defined(SAT_MINISAT)
  #define SAT_SOLVER "minisat"
#elif defined(SAT_LINGELING)
  #define SAT_SOLVER "lingeling"
#endif

// define MIP solver name
#if defined(MIP_CPLEX)
  #define MIP_SOLVER "CPLEX"
#elif defined(MIP_SCIP)
  #define MIP_SOLVER "SCIPr"
#elif defined(MIP_GUROBI)
  #define MIP_SOLVER "Gurobi"
#endif

// define version
#if defined(GITHASH)
  #define VERSION GITHASH
#elif defined(GITDATE)
  #define VERSION GITDATE
#else
  #define VERSION "???"
#endif

#define SIGNATURE "LMHS(SAT:" SAT_SOLVER " MIP:" MIP_SOLVER " VERSION:" VERSION ")"

extern "C" {

    const char * ipasir_signature () { return (const char *)SIGNATURE; }

    void * ipasir_init () {
        LMHSSolver *s = new LMHSSolver;
        return (void*)s;
    }

    void * get_problem_instance (void * solver) {
        LMHSSolver* s = (LMHSSolver*)solver;
        ProblemInstance* realInstance = s->instance;
        return static_cast<void*>(realInstance);
    }

    void ipasir_release (void * solver) {
        LMHSSolver* s = (LMHSSolver*)solver;
        delete s;
    }

    void ipasir_add (void * solver, int lit_or_zero) {
        LMHSSolver* s = (LMHSSolver*)solver;

        if (lit_or_zero == 0) {
            s->solver->instance.addHardClause(s->clause);
            s->clause.clear();
        } else {
            int var = std::abs(lit_or_zero);
            while (var >= s->solver->sat_solver->nVars()) {
                s->solver->sat_solver->newVar();
            }
            s->instance->max_var = max(s->instance->max_var, var);
            s->clause.push_back(lit_or_zero);
        }
    }

    void ipasir_add_soft (void * solver, double weight) {
        LMHSSolver* s = (LMHSSolver*)solver;

        s->solver->instance.addSoftClause(s->clause, weight);
        s->clause.clear();
    }

    void ipasir_assume (void * solver, int lit) {
        UNUSED(solver);
        UNUSED(lit);
        // not supported
    }

    int ipasir_solve (void * solver) {
        LMHSSolver* s = (LMHSSolver*)solver;

        s->solution.clear();
        s->solution_weight=-1;
        if (s->solver->hardClausesSatisfiable()) {
            s->solution_weight = s->solver->solveMaxHS(s->solution);
        }
        return s->solution.size() != 0 || s->solution_weight > 0
            ? 10
            : 20;
    }

    int ipasir_val (void * solver, int lit) {
        LMHSSolver* s = (LMHSSolver*)solver;
        return s->solution[abs(lit)-1];
    }

    double ipasir_weight (void * solver) {
        LMHSSolver* s = (LMHSSolver*)solver;
        return s->solution_weight;
    }

    int ipasir_failed (void * solver, int lit) {
        // TODO
        return 0;
    }

    void ipasir_set_terminate (void * solver, void * state, int (*terminate)(void * state)) {
        UNUSED(solver);
        UNUSED(state);
        UNUSED(terminate);
        //this is complicated.
    }

    void ipasir_set_learn (void * solver, void * state, int max_length, void (*learn)(void * state, int * clause)) {
        UNUSED(solver);
        UNUSED(state);
        UNUSED(max_length);
        UNUSED(learn);
        //this is complicated
    }

}