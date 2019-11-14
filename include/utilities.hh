#ifndef UTILITIES_HH
# define UTILITIES_HH
#include <vector>
#include <cmath>
#include "types.hh"
#include "cuddObj.hh"

using namespace std;

extern "C++" {
  inline int log_2(int x) {
    if(x==1)
      return 1;
    else
      return (int)ceil(log2(x));
  }
  BDD Exists(Cudd *bddmgr, BDDvector* v, BDD x);
  ADD ADDExists(Cudd * bddmgr, ADDvector v, ADD x);
  BDD check_EX (BDD next, bdd_parameters *para);
  BDD check_EF (BDD p, bdd_parameters *para);
  BDD check_EG (BDD p, bdd_parameters *para);
  BDD check_EU(BDD p, BDD q, bdd_parameters *para);
  BDD check_AU(BDD p, BDD q, bdd_parameters *para);
  BDD check_nK (BDD next, BDD RK, bdd_parameters *para);
  BDD check_nO (BDD next, string name, bdd_parameters *para);
  BDD check_GK (BDD next, string name, bdd_parameters *para);
  BDD check_DK (BDD next, string name, bdd_parameters *para);
  BDD check_GCK (BDD next, string name, bdd_parameters *para);
  BDD check_ATLX(BDD next, string grpname, bdd_parameters *para);
  BDD check_ATLG(BDD p, string grpname, bdd_parameters *para);
  BDD check_ATLU(BDD q1, BDD q2, string grpname, bdd_parameters *para);  

  BDD get_Future(BDD p, bdd_parameters * para);
  BDD get_Past(BDD p, bdd_parameters * para);
  BDD get_non_unique(BDD p, string name, bdd_parameters * para);
  BDD get_K2_states(BDD * state, string name, string name1, bdd_parameters * para);
  BDD check_SC(BDD p, string name, string name1, bdd_parameters *para);  
  BDD check_Fu(BDD p, string name, string name1, bdd_parameters *para);  
  BDD check_Vi(BDD p, string name, string name1, bdd_parameters *para);  
  
  // IJCAI 2011
  void get_shared_vars(string name1, string name2, vector<basictype *> *shared);
  BDD build_shared_equivalence(vector<basictype *> *shared, bdd_parameters * para);
  BDD get_SC_states(BDD p, string name1, string name2, bdd_parameters *para);
  BDD get_SC_states_fair(BDD p, string name1, string name2, bdd_parameters *para, BDD fair_reach);
  BDD get_Fu_states(BDD p, string name1, string name2, bdd_parameters *para);
  BDD get_eq_states(BDD * state, string name1, string name2, vector<basictype *> *shared, bdd_parameters * para);
  BDD get_Fu_states_fair(BDD p, string name1, string name2, bdd_parameters *para, BDD fair_reach);

  // AAMAS 2013
  void get_all_shared_vars(set<string> *allshared);
  BDD get_new_accessible_states(BDD *state, string name1, string name2, bdd_parameters *para);
  BDD build_accessible_equivalence(string name1, string name2, vector<basictype *> *shared, bdd_parameters * para);
  BDD get_accessible_preimage(BDD X, BDD Z, bdd_parameters *para);
  BDD get_accessible_image(BDD X, BDD Z, bdd_parameters *para);
  BDD get_WCC_states(BDD p, BDD q, string name1, string name2, bdd_parameters *para);
  BDD get_SCC_states(BDD p, BDD q, string name1, string name2, bdd_parameters *para);
  BDD get_FUW_states(BDD p, BDD q, string name1, string name2, bdd_parameters *para);
  BDD get_FUS_states(BDD p, BDD q, string name1, string name2, bdd_parameters *para);
  BDD get_FUS_states_new(BDD p, BDD q, string name1, string name2, bdd_parameters *para);
  BDD get_CAS_states_new(BDD p, BDD q, string name1, string name2, bdd_parameters *para);
  BDD get_RES_states_new(BDD p, BDD q, string name1, string name2, bdd_parameters *para);
  BDD get_DES_states_new(BDD p, BDD q, string name1, string name2, string name3, bdd_parameters *para);
  BDD get_ASS_states_new(BDD p, BDD q, string name1, string name2, string name3,  bdd_parameters *para);
  BDD get_TR_states(BDD p, BDD q, string name1, string name2, bdd_parameters *para);
  BDD get_TP_states(BDD p, BDD q, string name1, string name2, int op, int int_bound,  bdd_parameters *para);
  BDD get_TC_states(BDD p, BDD q, string name1, string name2, int op, int int_bound,  bdd_parameters *para);

  BDD check_EG_fair (BDD p, bdd_parameters *para);
  BDD check_EF_fair (BDD p, BDD fair_reach, bdd_parameters *para);
  BDD check_EX_fair (BDD p, BDD fair_reach, bdd_parameters *para);
  BDD check_EU_fair(BDD p, BDD q, BDD fair_reach, bdd_parameters *para);
  BDD check_nO_fair (BDD next, string name, BDD fair_reach, bdd_parameters *para);
  BDD check_GK_fair (BDD next, string name, BDD fair_reach, bdd_parameters *para);
  BDD check_DK_fair (BDD next, string name, BDD fair_reach, bdd_parameters *para);
  BDD check_GCK_fair (BDD next, string name, BDD fair_reach, bdd_parameters *para);
  BDD check_ATLX_fair(BDD next, string grpname, BDD fair_reach, bdd_parameters *para);
  BDD check_ATLG_fair(BDD p, string grpname, bdd_parameters *para);
  BDD check_ATLU_fair(BDD q1, BDD q2, string grpname, BDD fair_reach, bdd_parameters *para);  

  BDD get_K_states(BDD aset1, BDD *state, string name, bdd_parameters *para);
  BDD get_nK_states(BDD *state, string name, bdd_parameters *para);
  BDD get_nK_states_fair(BDD *state, string name, BDD fair_reach, bdd_parameters *para);
  BDD get_GK_states(BDD aset1, BDD *state, string name, bdd_parameters *para);
  BDD get_DK_states(BDD aset1, BDD *state, string name, bdd_parameters *para);

  DdNode * addApplyLT(DdManager* mgr, DdNode ** n1, DdNode ** n2);
  DdNode * addApplyLE(DdManager* mgr, DdNode ** n1, DdNode ** n2);
  DdNode * addApplyGT(DdManager* mgr, DdNode ** n1, DdNode ** n2);
  DdNode * addApplyGE(DdManager* mgr, DdNode ** n1, DdNode ** n2);
  DdNode * addApplyEQ(DdManager* mgr, DdNode ** n1, DdNode ** n2);
  DdNode * addApplyNEQ(DdManager* mgr, DdNode ** n1, DdNode ** n2);

  ADD addLT(Cudd * bddmgr, ADD a1, ADD a2);
  ADD addLE(Cudd * bddmgr, ADD a1, ADD a2);
  ADD addGT(Cudd * bddmgr, ADD a1, ADD a2);
  ADD addGE(Cudd * bddmgr, ADD a1, ADD a2);
  ADD addEQ(Cudd * bddmgr, ADD a1, ADD a2);
  ADD addNEQ(Cudd * bddmgr, ADD a1, ADD a2);
 
  // Calculate X * RT with local transition relations
  BDD timesTrans(BDD *from, BDD *to, BDDvector *vRT);

  // Remove actions from X * RT
  BDD timesRT(BDD *state, Cudd *bddmgr, BDDvector *vRT, BDDvector *a);

  int search_string_table(string *s);
  int search_variable_table(variable *v);
  int search_logic_expression_table(bool_expression *le);
  int search_logic_expression_table1(bool_expression *le);
}

extern map < string, int > options;
extern map<string, basic_agent *> *is_agents;
extern vector<basic_agent *> *agents;
extern map<string, bool_expression *> *is_evaluation;
extern bool_expression *is_istates;
extern map<string, set<string> > *is_groups;
extern vector<modal_formula> *is_formulae;
extern vector<fairness_expression *> *is_fairness;
extern int obsvars_bdd_length;
extern int envars_bdd_length;
extern BDD fair_reach;
extern vector< vector<int> * > *countex; // For counterexamples
extern map<int, BDD *> *idbdd;
extern int scount;
extern vector < vector <transition *> *> *cextr;
extern vector<string *> *string_table;
extern vector<variable *> *variable_table;
extern vector<bool_expression *> *logic_expression_table;
extern vector<bool_expression *> *logic_expression_table1;
extern void print_state(BDD state, BDDvector v);
extern void print_states(BDD states, BDDvector v, Cudd* bddmgr);
extern void print_action(BDD state, BDDvector a);
extern string state_to_str(BDD state, BDDvector v);
extern set<string> all_shared_var_names;

#endif // ! UTILITIES_HH
