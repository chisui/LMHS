#ifndef maxsat_solver_h
#define maxsat_solver_h

#include "ProblemInstance.h"
#include "Util.h"
#include "GlobalConfig.h"
#include "ISATSolver.h"

#include <vector>
#include <unordered_map>
#include <iosfwd>

class Solver {
 public:
  Solver(ProblemInstance& instance);
  ~Solver();

  void findDisjointCores(std::vector<std::vector<int> >& disjointCores);
  bool getCore(std::vector<int>& hs, std::vector<int>& core);
  bool getCores(std::vector<int>& hs, std::vector<std::vector<int>>& cores);
  void setAssumptions(std::vector<int>& hs);
  void findGreedyHittingSet(std::vector<int>& hs);

  void solve(std::ostream & out);
  void printStats();
  void printBounds(double lb, double ub);
  void printSolution(std::ostream & out);
  double findSolution(std::vector<int>& out_solution);

  void updateUB();

  double solveAsMIP(std::vector<int>& out_solution);
  double solveMaxHS(std::vector<int>& out_solution);

  void presolve();
  bool hardClausesSatisfiable();
  void reset();
  void processCore(std::vector<int>& core);

  // variables for timing
  clock_t startTime, endTime,
      totalTime, solveTime, disjointStart, disjointTime;

  std::vector<unsigned> coreSizes;
  std::unordered_map<int, unsigned> coreClauseCounts;
  std::vector<std::pair<double, int>> sortedWeights;

  GlobalConfig &cfg;
  ProblemInstance &instance;
  bool newInstance;

  // statistics
  unsigned nSolutions;
  unsigned nLabelCores;
  unsigned nNonoptCores, nEquivConstraints, nDisjointCores;

  double relaxLB;
  double LB;
  double UB;

  std::vector<int> UB_solution;

  std::vector<std::vector<int> > cores;

  std::vector<int> opt_model;
  double           opt_weight;

  ISATSolver* sat_solver;
  IMIPSolver* mip_solver;
};

#endif