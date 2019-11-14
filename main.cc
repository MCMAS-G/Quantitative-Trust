
/* ************************************************************************
 *            MCMAS -- Model Checker for Multi-Agent Systems
 *
 *     Copyright (C) 2007, 2008, 2009, 2010
 *     Hongyang Qu and Franco Raimondi and Alessio Lomuscio
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 **************************************************************************/

#define NAME "mcmas"
#define URL "http://www-lai.doc.ic.ac.uk/mcmas/"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>
#include <ctime>
#include "types.hh"
#include "utilities.hh"
#include "mcmas-driver.hh"
#include "cuddObj.hh"
#include <sys/timeb.h>

using namespace std;

vector< string * >*string_table;
vector< bool_expression * >*logic_expression_table;
vector< bool_expression * >*logic_expression_table1;
vector< variable * >*variable_table;
map< string, basic_agent * >*is_agents;
vector< basic_agent * >*agents;
map< string, bool_expression * >*is_evaluation;
bool_expression *is_istates = NULL;
map< string, set< string > >*is_groups;
vector< modal_formula > *is_formulae;
vector< fairness_expression * >*is_fairness;
int obsvars_bdd_length;
int envars_bdd_length;
// A map to store global options, e.g. verbosity, etc.
map< string, int >options;
string cex_prefix;    // Destination directory for counterexamples
BDD fair_reach;
vector< vector< int >*>*countex;  // For counterexamples
map< int, BDD * >*idbdd;  // Map state id -> bdd (for counterexamples again)
int scount;     // a global counter for counterexamples.
vector< vector< transition * >*>*cextr; // instead of state id, counterexample with transitions
set<string> all_shared_var_names;

bool global_consistency_check();
void exec_simulation(void *ptr);
int export_model(bdd_parameters * para, BDD *is, vector< vector< int >*> *countex, map< int, BDD * > *idbdd, vector< vector< transition * >*> *cextr);
void print_cex(bdd_parameters * para, string fname, string str_head, map< int, BDD * > *idbdd, vector< vector< transition * >*> *cextr);

void
print_help(void)
{
  cout << "Usage: " << NAME << " [OPTIONS] FILE " << endl;
  cout << "Example: " << NAME << " -v 3 -u myfile.ispl" << endl;
  cout << endl << "Options: " << endl;
  cout << "  -s \t \t Interactive execution" << endl;

  cout << endl;

  cout << "  -v Number \t verbosity level ( 1 -- 5 )" << endl;
  cout << "  -u \t \t Print BDD statistics " << endl;

  cout << endl;

  cout << "  -e Number \t Choose the way to generate reachable state space (1 -- 3, default 1)" << endl;
  cout << "  -o Number \t Choose the way to order BDD variables (1 -- 4, default 2)" << endl;
  cout << "  -g Number \t Choose the way to group BDD variables (1 -- 3, default 3)" << endl;
  cout << "  -d Number \t Choose the point to disable dynamic BDD reordering (1 -- 3, default 3)" << endl;

  cout << endl;

  cout << "  -k \t \t Check deadlock in the model" << endl;
  cout << "  -a \t \t Check arithmetic overflow in the model" << endl;

  cout << endl;

  cout << "  -c Number \t Choose the way to display counterexamples/witness executions (1 -- 3)" << endl;
  cout << "  -p Path \t Choose the path to store files for counterexamples" << endl;
  cout << "  -exportmodel \t Export model (states and transition relation) to a file in dot format" << endl;

  cout << endl;

  cout << "  -f Number \t Choose the level of generating ATL strategies (1 -- 4)"  << endl;
  cout << "  -l Number \t Choose the level of generating ATL counterexamples (1 -- 2)"  << endl;
  cout << "  -w \t \t Try to choose new states when generating ATL strategies"  << endl;

  cout << endl;

  cout << "  -n \t \t Disable comparison between an enumeration type and its strict subset"  << endl;

  cout << endl;

  cout << "  -h \t \t This screen" << endl;
}

void
print_banner(void)
{
  cout <<
    "************************************************************************"
       << endl;
  cout << "                       MCMAS v1.0.1 for Social Commitment " << endl << endl;
  cout << " This software comes with ABSOLUTELY NO WARRANTY, to the extent"
       << endl;
  cout << " permited by applicable law. " << endl << endl;
  cout << " Please check "  << URL;
  cout << " for the latest release.\n Report bugs to <mcmas@imperial.ac.uk>"
       << endl;
  cout <<
    "************************************************************************"
       << endl << endl;
}

void
print_state(BDD state, BDDvector v)
{
  for (unsigned int i = 0; i < agents->size(); i++) {
    cout << "Agent " << (*agents)[i]->get_name() << endl;
    (*agents)[i]->print_state("  ", state, v);
  }
}

void
print_states(BDD states, BDDvector v, Cudd* bddmgr)
{
  BDD tmp = states;
  BDD tmp1;
  while(tmp != bddmgr->bddZero()) {
    tmp1 = tmp.PickOneMinterm(v);
    tmp = tmp - tmp1;
    print_state(tmp1, v);
  }
}

string
state_to_str(BDD state, BDDvector v)
{
  ostringstream s;

  for (unsigned int i = 0; i < agents->size(); i++) {
    s << "  Agent " << (*agents)[i]->get_name() << "\n";
    s << (*agents)[i]->state_to_str(state, v);

  }
  return s.str();
}

bool
find_same_state(map< string, int >*statehash, string state)
{
  if (statehash != NULL) {
    map< string, int >::iterator iter = statehash->find(state);
    if (iter != statehash->end()) {
      return true;
    }
  }
  return false;
}

bool
is_valid_state(BDD state, BDDvector v)
{
  for (unsigned int i = 0; i < agents->size(); i++) {
    if (!(*agents)[i]->is_valid_state(state, v))
      return false;
  }
  return true;
}

void
print_action(BDD state, BDDvector a)
{
  for (unsigned int i = 0; i < agents->size(); i++) {
    cout << (*agents)[i]->get_name() << " : ";
    (*agents)[i]->print_action(state, a);
    if (i < agents->size() - 1)
      cout << "; ";
    else
      cout << endl;
  }
}

void
print_action_1(BDD state, BDDvector a)
{
  for (unsigned int i = 0; i < agents->size(); i++) {
    cout << (*agents)[i]->get_name() << " : ";
    (*agents)[i]->print_action(state, a);
    cout << "; ";
  }
  cout << endl;
}

bool
is_valid_action(BDD state, BDDvector a)
{
  for (unsigned int i = 0; i < agents->size(); i++) {
    if (!(*agents)[i]->is_valid_action(state, a))
      return false;
  }
  return true;
}

BDD
append_variable_BDDs(Cudd * bddmgr, BDDvector * v, BDD a)
{
  for (unsigned int j = 0; j < agents->size(); j++) {
    map< string, basictype * >*obsvars = (*agents)[j]->get_obsvars();
    if (obsvars != NULL && obsvars->size() > 0)
      for (map< string, basictype * >::iterator i =
             obsvars->begin(); i != obsvars->end(); i++)
        if ((*i).second->get_type() == 3)
          a *= ((enumerate *) (*i).second)->build_all_BDDs(bddmgr, v);
    map< string, basictype * >*vars = (*agents)[j]->get_vars();
    if (vars != NULL && vars->size() > 0)
      for (map< string, basictype * >::iterator i = vars->begin();
           i != vars->end(); i++)
        if ((*i).second->get_type() == 3)
          a *= ((enumerate *) (*i).second)->build_all_BDDs(bddmgr, v);
  }
  return a;
}

BDD
append_variable_BDD(Cudd * bddmgr, BDDvector * v, BDD a, int j)
{
  map< string, basictype * >*obsvars = (*agents)[j]->get_obsvars();
  if (obsvars != NULL && obsvars->size() > 0)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++)
      if ((*i).second->get_type() == 3)
        a *= ((enumerate *) (*i).second)->build_all_BDDs(bddmgr, v);
  map< string, basictype * >*vars = (*agents)[j]->get_vars();
  if (vars != NULL && vars->size() > 0)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++)
      if ((*i).second->get_type() == 3)
        a *= ((enumerate *) (*i).second)->build_all_BDDs(bddmgr, v);
  return a;
}

void 
produce_witness(bdd_parameters *para, BDD state, string name) {
  vector< BDD * > S;
  int n = 0;
  BDD q = state;
  BDD p;
  BDD sum = q;
  do {
    q = check_EX(q, para) - sum;
    S.push_back(new BDD(q));
    sum += q;
    p = q * *(para->in_st);
    n++;
  } while (p == para->bddmgr->bddZero());
  
  p = p.PickOneMinterm(*para->v);
  vector< BDD *> tmpresult;
  vector< BDD * > tmptrans;
  tmpresult.push_back(new BDD(p));
  for(int k=(int)S.size()-2; k>=0; k--) {
    for (unsigned int i = 0; i < agents->size(); i++)
      p = p * (*para->vRT)[i];
    p = p.SwapVariables(*para->v, *para->pv);
    p = Exists(para->bddmgr, para->a, p);
    p = Exists(para->bddmgr, para->pv, p);
    p = p * (*(S[k]));
    p = p.PickOneMinterm(*para->v);
    tmpresult.push_back(new BDD(p));
  }
  tmpresult.push_back(new BDD(state));
  
  for (unsigned int i = 0; i < tmpresult.size() - 1; i++) {
    BDD to = (tmpresult[i + 1])->SwapVariables(*para->v, *para->pv);
    BDD actions = timesTrans(tmpresult[i], &to, para->vRT);
    actions = Exists(para->bddmgr, para->v, actions);
    actions = Exists(para->bddmgr, para->pv, actions);
    BDD action = actions.PickOneMinterm(*para->a);
    tmptrans.push_back(&action);
  }
  
  if (options["cex"] == 1 || options["cex"] == 3) {
    cout << "Below is a witness execution leading to the state: " << endl;
    for (unsigned int k = 0; k<tmpresult.size(); k++) {
      cout << "------------- State: " << k+1 << " -----------------" << endl;
      print_state(*tmpresult[k], *para->v);
      cout << "----------------------------------------" << endl;
    } 
  } 
  if (options["cex"] == 2 || options["cex"] == 3) {
    string filename = cex_prefix + name + ".dot";
    string filename2 = cex_prefix + name + ".info";
    ofstream myfile(filename.c_str());
    ofstream myfile2(filename2.c_str());
    
    if (myfile.is_open() && myfile2.is_open()) {
      myfile << "digraph " << name << " {\n";
      
      // print states and their description
      for (unsigned int k = 0; k<tmpresult.size(); k++) {
        myfile << " " << k << " [label=\"" << k << "\",shape=ellipse]" << endl;
        myfile2 << "-- State " << k << " --" << endl;
        myfile2 << state_to_str(*tmpresult[k], *para->v) << endl;
      }
      for (unsigned int k = 0; k<tmptrans.size(); k++) {
        myfile << "    " << k << " -> " << k+1 << "[label=\"<";
        for (unsigned int i = 0; i < agents->size(); i++) {
          string act_str = (*agents)[i]->action_to_str(*tmptrans[k], *para->a);
          if (act_str != "") {
            myfile << act_str;
            if (!(i == agents->size() - 1)) {
              myfile << ";";
            }
          }
        }
  
        myfile << ">\"]" << endl;
      }
      myfile << "}\n";
      
      myfile.close();
      myfile2.close();
    } else {
      if(options["quiet"] == 0) 
        cout << "Unable to open file " << filename;
    }
  }
}


int
main(int argc, char *argv[])
{
  //time_t t0 = time(0);
  struct timeb tmb;
  ftime(&tmb);

  is_agents = new map< string, basic_agent * >;
  agents = new vector< basic_agent * >;
  is_evaluation = new map< string, bool_expression * >;
  is_groups = new map< string, set< string > >;
  is_formulae = new vector< modal_formula >;
  is_fairness = new vector< fairness_expression * >;

  string_table = new vector< string * >;
  string_table->push_back(new string("Environment"));
  logic_expression_table = new vector< bool_expression * >;
  logic_expression_table1 = new vector< bool_expression * >;
  variable_table = new vector< variable * >;

  options["verbosity"] = 0;
  options["bdd_stats"] = 0;
  options["cex"] = 0;
  options["simulation"] = 0;
  options["quiet"] = 0;
  options["experiment"] = 2;
  options["smv"] = 0;
  options["fullatl"] = 0;
  options["atlnewstate"] = 0;
  options["atlcex"] = 0;
  options["subset"] = 1;
  options["ordering"] = 2;
  options["dao"] = 3;
  options["bddgroup"] = 3;
  options["deadlock"] = 0;
  options["overflow"] = 0;
  options["nobddcache"] = 0;
  options["exportmodel"] = 0;

  options["trust"] = 0;

  static const std::string verb("-v");
  static const std::string binfo("-bdd_stats");
  static const std::string help("-h");
  static const std::string help2("--help");
  static const std::string cex("-c");
  static const std::string simulation("-s");
  static const std::string quiet("-q");
  static const std::string experiment("-e");
  static const std::string cexoutdir("-cex_prefix");
  static const std::string fullatl("-fullatl");
  static const std::string atlnewstate("-atlnewstate");
  static const std::string atlcex("-atlcex");
  static const std::string subset("-nosubset");
  static const std::string ordering("-o");
  static const std::string dao("-dao");
  static const std::string bddgroup("-bddgroup");
  static const std::string deadlock("-k");
  static const std::string overflow("-a");
  static const std::string exportmodel("-exportmodel");

  static const std::string binfo1("-u");
  static const std::string cexoutdir1("-p");
  static const std::string fullatl1("-f");
  static const std::string atlnewstate1("-w");
  static const std::string atlcex1("-l");
  static const std::string subset1("-n");
  static const std::string dao1("-d");
  static const std::string bddgroup1("-g");
  static const std::string nobddcache("-nobddcache");

  static const std::string trust("-trust");

  std::string filename;

  string s;

  mcmas_driver driver;

  if (argc < 2) {
    print_banner();
    print_help();
    exit(1);
  }

  bool wrongpara = false;

  cex_prefix = "";
  for (int i = 1; i < argc - 1; ++i) {
    if (binfo == argv[i] || binfo1 == argv[i]) {
      options["bdd_stats"] = 1;
    } else if (cex == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["cex"] = atoi(s.c_str());

      if (options["cex"] < 0 || options["cex"] > 3) {
        cout << "Parameter " << options["cex"] <<
          " is not allowed in -c option." << endl;
        wrongpara = true;
      }
    } else if (exportmodel == argv[i]) {
      options["exportmodel"] = 1;
    } else if (verb == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["verbosity"] = atoi(s.c_str());

      if (options["verbosity"] < 0 || options["verbosity"] > 5) {
        cout << "Parameter " << options["verbosity"] <<
          " is not allowed in -v option." << endl;
        wrongpara = true;
      }
    } else if ((help == argv[i]) || (help2 == argv[i])) {
      print_help();
      exit(1);
    } else if (simulation == argv[i]) {
      options["simulation"] = 1;
    } else if (atlcex == argv[i] || atlcex1 == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["atlcex"] = atoi(s.c_str());
      if (options["atlcex"] < 0 || options["atlcex"] > 2) {
        cout << "Parameter " << options["atlcex"] <<
          " is not allowed in -atlcex option." << endl;
        wrongpara = true;
      }
    } else if (fullatl == argv[i] || fullatl1 == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["fullatl"] = atoi(s.c_str());
      if (options["fullatl"] < 0 || options["fullatl"] > 4) {
        cout << "Parameter " << options["fullatl"] <<
          " is not allowed in -fullatl option." << endl;
        wrongpara = true;
      }
    } else if (atlnewstate == argv[i] || atlnewstate1 == argv[i]) {
      options["atlnewstate"] = 1;
    } else if (ordering == argv[i]) {
      string s;
      s = argv[++i];
      options["ordering"] = atoi(s.c_str());
      if (options["ordering"] < 1 || options["ordering"] > 4) {
        cout << "Parameter " << options["ordering"] <<
          " is not allowed in -o option." << endl;
        wrongpara = true;
      }
    } else if (subset == argv[i] || subset1 == argv[i]) {
      options["subset"] = 0;
    } else if (dao == argv[i] || dao1 == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["dao"] = atoi(s.c_str());

      if (options["dao"] < 0 || options["dao"] > 3) {
        cout << "Parameter " << options["verbosity"] <<
          " is not allowed in -dao option." << endl;
        wrongpara = true;
      }
    } else if (bddgroup == argv[i] || bddgroup1 == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["bddgroup"] = atoi(s.c_str());

      if (options["bddgroup"] < 0 || options["bddgroup"] > 3) {
        cout << "Parameter " << options["verbosity"] <<
          " is not allowed in -bddgroup option." << endl;
        wrongpara = true;
      }
    } else if (trust == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["trust"] = atoi(s.c_str());

      if (options["trust"] < 0 || options["trust"] > 2) {
        cout << "Parameter " << options["verbosity"] <<
          " is not allowed in -trust option." << endl;
        wrongpara = true;
      }
    } else if (quiet == argv[i]) {
      options["quiet"] = 1;
    } else if (deadlock == argv[i]) {
      options["deadlock"] = 1;
    } else if (overflow == argv[i]) {
      options["overflow"] = 1;
    } else if (experiment == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["experiment"] = atoi(s.c_str());
      if (options["experiment"] < 1 || options["experiment"] > 3) {
        cout << "Parameter " << options["experiment"] <<
          " is not allowed in -e option." << endl;
        wrongpara = true;
      }
    } else if (cexoutdir == argv[i] || cexoutdir1 == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      cex_prefix = s;
      if(cex_prefix.at(cex_prefix.length()-1) != '\\' || 
         cex_prefix.at(cex_prefix.length()-1) != '/')
        cex_prefix += "/";
    } else if (nobddcache == argv[i]) {
      options["nobddcache"] = 1;
    } else {
      cout << NAME << " invalid option: " << argv[i] << endl;
      print_help();
      exit(1);
    }
  }

  if (wrongpara)
    exit(1);

  if (options["quiet"] == 0)
    print_banner();

  if ((help == argv[argc - 1]) || (help2 == argv[argc - 1])) {
    print_help();
    exit(1);
  }

  filename = argv[argc - 1];

  driver.parse(filename);
  if (!driver.syntax_error) {
    if (options["quiet"] == 0 || options["simulation"] == 0)
      cout << filename << " has been parsed successfully." << endl;
    if (options["quiet"] == 0 || options["simulation"] == 0)
      cout << "Global syntax checking..." << endl;
    if (!global_consistency_check()) {
      cout << filename << " has error(s)." << endl;
      delete is_agents;
      delete agents;
      delete is_evaluation;
      delete is_groups;
      delete is_formulae;
      delete is_fairness;
      delete string_table;
      delete variable_table;
      delete logic_expression_table;
      delete logic_expression_table1;
      exit(-1);
    }
    if (options["quiet"] == 0)
      cout << "Done" << endl;
  } else {
    cout << filename << " has syntax error(s)." << endl;
    delete is_agents;
    delete agents;
    delete is_evaluation;
    delete is_groups;
    delete is_formulae;
    delete is_fairness;
    delete string_table;
    delete variable_table;
    delete logic_expression_table;
    delete logic_expression_table1;
    exit(-1);
  }

  if (options["verbosity"] > 2) {
    cout << "Done" << endl;
  }

  if (options["simulation"] == 0 || options["quiet"] == 0)
    cout << "Encoding BDD parameters..." << endl;

  // Calculate the number of BDD variables for states and actions
  int states_count = 0;
  int actions_count = 0;
  for (unsigned int i = 0; i < agents->size(); i++) {
    states_count += (*agents)[i]->state_BDD_length();
    actions_count += (*agents)[i]->actions_BDD_length();
  }

  // Calculate the position of every variable and every set of actions
  int k1 = 0;
  int k2 = 0;
  for (unsigned int i = 0; i < agents->size(); i++) {
    k1 = (*agents)[i]->allocate_BDD_2_variables(k1);
    k2 = (*agents)[i]->allocate_BDD_2_actions(k2);
  }

  if (options["verbosity"] > 0) {
    cout << endl << "  Building BDDs variables...";
  }

  Cudd *bddmgr = new Cudd(states_count * 2 + actions_count, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0, 0);  // The manager
  BDDvector *v;
  ADDvector *addv;
  BDDvector *pv;
  ADDvector *addpv;
  BDDvector *a;
  BDDvector *vevol, *vprot, *vRT;
  BDD in_st;
  BDD reach;

  v = new BDDvector(states_count, bddmgr);  // Local states
  addv = new ADDvector(states_count, bddmgr);
  pv = new BDDvector(states_count, bddmgr); // "Next" local states
  addpv = new ADDvector(states_count, bddmgr);
  a = new BDDvector(actions_count, bddmgr); // Actions

  // Allocate BDD variables to states and actions
  if (options["ordering"] == 1) {
    for (int i = 0; i < states_count; i++) {
      (*v)[i] = bddmgr->bddVar(i);
      (*pv)[i] = bddmgr->bddVar(states_count + i);
      (*addv)[i] = bddmgr->addVar(i);
      (*addpv)[i] = bddmgr->addVar(states_count + i);
    }
    for (int i = 0; i < actions_count; i++)
      (*a)[i] = bddmgr->bddVar(states_count * 2 + i);
    if (options["bddgroup"] >= 2)
      for (unsigned int i = 0; i < agents->size(); i++) {
        basic_agent *agent = (*agents)[i];
        vector< basictype * >*vec_obsvars = agent->get_vec_obsvars();
        vector< basictype * >*vec_vars = agent->get_vec_vars();
        if (vec_obsvars != NULL)
          for (unsigned int j = 0; j < vec_obsvars->size(); j++) {
            int a1 = (*vec_obsvars)[j]->get_index_begin();
            int a2 = (*vec_obsvars)[j]->get_index_end();
            Cudd_MakeTreeNode(bddmgr->getManager(), a1,
                              a2 - a1 + 1, MTR_DEFAULT);
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              states_count + a1, a2 - a1 + 1,
                              MTR_DEFAULT);
          }
        if (vec_vars != NULL)
          for (unsigned int j = 0; j < vec_vars->size(); j++) {
            int a1 = (*vec_vars)[j]->get_index_begin();
            int a2 = (*vec_vars)[j]->get_index_end();
            Cudd_MakeTreeNode(bddmgr->getManager(), a1,
                              a2 - a1 + 1,
                              MTR_DEFAULT);
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              states_count + a1, a2 - a1 + 1,
                              MTR_DEFAULT);
          }
      }
    if (options["bddgroup"] == 3) {
      int l = 0;
      for (unsigned int i = 0; i < agents->size(); i++) {
        Cudd_MakeTreeNode(bddmgr->getManager(),
                          states_count * 2 + l,
                          (*agents)[i]->actions_BDD_length(),
                          MTR_DEFAULT);
        l += (*agents)[i]->actions_BDD_length();
      }
    }
  } else if (options["ordering"] == 2) {
    int tmp_sum = 0;
    int tmp_states_count = 0;
    int tmp_actions_count = 0;
    for (unsigned int i = 0; i < agents->size(); i++) {
      for (int j = 0; j < (*agents)[i]->state_BDD_length(); j++) {
        (*v)[tmp_states_count + j] = bddmgr->bddVar(tmp_sum + j * 2);
        (*pv)[tmp_states_count + j] = bddmgr->bddVar(tmp_sum + j * 2 + 1);
        (*addv)[tmp_states_count + j] = bddmgr->addVar(tmp_sum + j * 2);
        (*addpv)[tmp_states_count + j] = bddmgr->addVar(tmp_sum + j * 2 + 1);
        if (options["bddgroup"] == 1)
          Cudd_MakeTreeNode(bddmgr->getManager(),
                            tmp_sum + j * 2, 2, MTR_FIXED);
      }
      if (options["bddgroup"] >= 2) {
        basic_agent *agent = (*agents)[i];
        vector< basictype * >*vec_obsvars = agent->get_vec_obsvars();
        vector< basictype * >*vec_vars = agent->get_vec_vars();
        int l = 0;
        if (vec_obsvars != NULL)
          for (unsigned int k = 0; k < vec_obsvars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_obsvars)[k]->BDD_length() * 2,
                              MTR_DEFAULT);
            l += (*vec_obsvars)[k]->BDD_length() * 2;
          }
        if (vec_vars != NULL)
          for (unsigned int k = 0; k < vec_vars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_vars)[k]->BDD_length() * 2,
                              MTR_DEFAULT);
            l += (*vec_vars)[k]->BDD_length() * 2;
          }
      }
      tmp_sum += (*agents)[i]->state_BDD_length() * 2;
      tmp_states_count += (*agents)[i]->state_BDD_length();
      for (unsigned int j = 0; j < (*agents)[i]->actions_BDD_length(); j++) {
        (*a)[tmp_actions_count + j] = bddmgr->bddVar(tmp_sum + j);
      }
      if (options["bddgroup"] == 3)
        Cudd_MakeTreeNode(bddmgr->getManager(), tmp_sum,
                          (*agents)[i]->actions_BDD_length(),
                          MTR_DEFAULT);
      tmp_sum += (*agents)[i]->actions_BDD_length();
      tmp_actions_count += (*agents)[i]->actions_BDD_length();
    }
  } else if (options["ordering"] == 3) {
    int tmp_sum = 0;
    int tmp_states_count = 0;
    int tmp_actions_count = 0;
    for (unsigned int i = 0; i < agents->size(); i++) {
      for (int j = 0; j < (*agents)[i]->state_BDD_length(); j++) {
        (*v)[tmp_states_count + j] = bddmgr->bddVar(tmp_sum + j);
        (*addv)[tmp_states_count + j] = bddmgr->addVar(tmp_sum + j);
      }
      if (options["bddgroup"] >= 2) {
        basic_agent *agent = (*agents)[i];
        vector< basictype * >*vec_obsvars = agent->get_vec_obsvars();
        vector< basictype * >*vec_vars = agent->get_vec_vars();
        int l = 0;
        if (vec_obsvars != NULL)
          for (unsigned int k = 0; k < vec_obsvars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_obsvars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_obsvars)[k]->BDD_length();
          }
        if (vec_vars != NULL)
          for (unsigned int k = 0; k < vec_vars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_vars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_vars)[k]->BDD_length();
          }
      }
      tmp_sum += (*agents)[i]->state_BDD_length();
      for (unsigned int j = 0; j < (*agents)[i]->actions_BDD_length(); j++) {
        (*a)[tmp_actions_count + j] = bddmgr->bddVar(tmp_sum + j);
      }
      if (options["bddgroup"] == 3)
        Cudd_MakeTreeNode(bddmgr->getManager(), tmp_sum,
                          (*agents)[i]->actions_BDD_length(),
                          MTR_DEFAULT);
      tmp_sum += (*agents)[i]->actions_BDD_length();
      tmp_actions_count += (*agents)[i]->actions_BDD_length();
      for (int j = 0; j < (*agents)[i]->state_BDD_length(); j++) {
        (*pv)[tmp_states_count + j] = bddmgr->bddVar(tmp_sum + j);
        (*addpv)[tmp_states_count + j] = bddmgr->addVar(tmp_sum + j);
      }
      if (options["bddgroup"] >= 2) {
        basic_agent *agent = (*agents)[i];
        vector< basictype * >*vec_obsvars = agent->get_vec_obsvars();
        vector< basictype * >*vec_vars = agent->get_vec_vars();
        int l = 0;
        if (vec_obsvars != NULL)
          for (unsigned int k = 0; k < vec_obsvars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_obsvars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_obsvars)[k]->BDD_length();
          }
        if (vec_vars != NULL)
          for (unsigned int k = 0; k < vec_vars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_vars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_vars)[k]->BDD_length();
          }
      }
      tmp_states_count += (*agents)[i]->state_BDD_length();
      tmp_sum += (*agents)[i]->state_BDD_length();
    }
  } else if (options["ordering"] == 4) {
    int tmp_sum = 0;
    int tmp_states_count = 0;
    int tmp_actions_count = 0;
    for (unsigned int i = 0; i < agents->size(); i++) {
      for (int j = 0; j < (*agents)[i]->state_BDD_length(); j++) {
        (*v)[tmp_states_count + j] = bddmgr->bddVar(tmp_sum + j);
        (*pv)[tmp_states_count + j] =
          bddmgr->bddVar(tmp_sum + (*agents)[i]->state_BDD_length() + j);
        (*addv)[tmp_states_count + j] = bddmgr->addVar(tmp_sum + j);
        (*addpv)[tmp_states_count + j] =
          bddmgr->addVar(tmp_sum + (*agents)[i]->state_BDD_length() + j);
      }
      if (options["bddgroup"] >= 2) {
        basic_agent *agent = (*agents)[i];
        vector< basictype * >*vec_obsvars = agent->get_vec_obsvars();
        vector< basictype * >*vec_vars = agent->get_vec_vars();
        int l = 0;
        if (vec_obsvars != NULL)
          for (unsigned int k = 0; k < vec_obsvars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_obsvars)[k]->BDD_length(),
                              MTR_DEFAULT);
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum +
                              (*agents)[i]->state_BDD_length() + l,
                              (*vec_obsvars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_obsvars)[k]->BDD_length();
          }
        if (vec_vars != NULL)
          for (unsigned int k = 0; k < vec_vars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_vars)[k]->BDD_length(),
                              MTR_DEFAULT);
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum +
                              (*agents)[i]->state_BDD_length() + l,
                              (*vec_vars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_vars)[k]->BDD_length();
          }
      }
      tmp_sum += (*agents)[i]->state_BDD_length() * 2;
      tmp_states_count += (*agents)[i]->state_BDD_length();
      for (unsigned int j = 0; j < (*agents)[i]->actions_BDD_length(); j++) {
        (*a)[tmp_actions_count + j] = bddmgr->bddVar(tmp_sum + j);
      }
      if (options["bddgroup"] == 3)
        Cudd_MakeTreeNode(bddmgr->getManager(), tmp_sum,
                          (*agents)[i]->actions_BDD_length(),
                          MTR_DEFAULT);
      tmp_sum += (*agents)[i]->actions_BDD_length();
      tmp_actions_count += (*agents)[i]->actions_BDD_length();
    }
  }

  if (options["verbosity"] > 0) {
    cout << "Done: " << v->count() << " for local states, " << a->
      count() << " for actions." << endl;
  }

  obsvars_bdd_length = (*agents)[0]->obsvars_BDD_length();
  envars_bdd_length = (*agents)[0]->get_var_index_end() + 1;

  // Encode initial states
  in_st = bddmgr->bddOne();

  vprot = new BDDvector((int) agents->size(), bddmgr);
  vevol = new BDDvector((int) agents->size(), bddmgr);
  vRT = new BDDvector((int) agents->size(), bddmgr);

  bdd_parameters *para = new bdd_parameters;
  para->bddmgr = bddmgr;
  para->istates = is_istates;
  para->vRT = vRT;
  para->vevol = vevol;
  para->vprot = vprot;
  para->num_of_agents = agents->size();
  para->id = 0;
  para->v = v;
  para->pv = pv;
  para->addv = addv;
  para->addpv = addpv;
  para->a = a;
  para->BDD_cache = new map< string, BDD > ();
  para->ADD_cache = new map< string, ADD > ();

  if (options["simulation"] == 1)
    exec_simulation(para);

  // REORDERING OF VARIABLES:
  Cudd_ReorderingType REORDERING = CUDD_REORDER_GROUP_SIFT_CONV;
  if (options["dao"] == 0 || options["dao"] >= 2) // 1: all disable
    Cudd_AutodynEnable(bddmgr->getManager(), REORDERING);

  para->reachRT = NULL;
  para->calReachRT = true; //options["nobddcache"];

  if (options["quiet"] == 0 || options["simulation"] == 0) {
    cout << "Building partial transition relation..." << endl;
  }
  for (unsigned int i = 0; i < agents->size(); i++) {
    if (options["verbosity"] > 0) {
      if (i == 0)
        cout << endl;
      cout << "      Processing " << (*agents)[i]->get_name() <<
        ": protocol... ";
      cout.flush();
    }
    time_t tmpt0 = time(0);
    (*para->vprot)[i] = (*agents)[i]->encode_protocol(para);
    if (options["verbosity"] > 0) {
      cout << "done, evolution...";
      cout.flush();
    }
    if (options["smv"] == 0)
      (*para->vevol)[i] = (*agents)[i]->encode_evolution(para);
    else
      (*para->vevol)[i] = (*agents)[i]->encode_evolution_smv(para);
    if (options["verbosity"] > 0) {
      cout << "done, local transition relation...";
      cout.flush();
    }
    (*para->vRT)[i] = (*para->vprot)[i] * (*para->vevol)[i];
    time_t tmpt1 = time(0);
    if (options["verbosity"] > 0) {
      cout << "done. " << difftime(tmpt1, tmpt0) << " seconds" << endl;
    }
  }
  if (options["verbosity"] > 2)
    cout << "Done" << endl;
  if (options["quiet"] == 0 || options["simulation"] == 0) {
    cout << "Building OBDD for initial states..." << endl;
  }
  in_st = is_istates->encode_bdd_flat(para, new BDD(bddmgr->bddOne()));
  in_st = append_variable_BDDs(bddmgr, v, in_st);
  if (options["verbosity"] > 2)
    cout << "Done." << endl;

  para->in_st = new BDD(in_st);

  REORDERING = CUDD_REORDER_SIFT;
  if (options["dao"] == 0 || options["dao"] == 3) // 1: all disable, 2: after transition relation, 3: after reachable states
    Cudd_AutodynEnable(bddmgr->getManager(), REORDERING);
  else
    Cudd_AutodynDisable(bddmgr->getManager());

  if (options["quiet"] == 0 || options["simulation"] == 0) {
    cout << "Building reachable state space..." << endl;
  }
  if (options["experiment"] == 1) {
    reach = bddmgr->bddZero();
    BDD q1 = in_st;
    BDD next1 = bddmgr->bddZero();
    int acounter1 = 1;

    while (q1 != reach) {
      if (options["verbosity"] > 0)
        cout << "    Computing depth " << acounter1 << endl;

      reach = q1;
      next1 = q1;
      for (unsigned int k = 0; k < agents->size(); k++)
        next1 *= (*vRT)[k];
      next1 = Exists(bddmgr, v, next1);
      next1 = next1.SwapVariables(*v, *pv);
      next1 = Exists(bddmgr, a, next1); // Clear actions.

      q1 = q1 + next1;
      acounter1++;
    }

    reach = Exists(bddmgr, a, reach);

    if (options["verbosity"] > 2) {
      cout << "Done" << endl;
    }
  } else if (options["experiment"] == 2) {  // BMC goes here
    reach = in_st;
    BDD q1 = bddmgr->bddZero();
    BDD next1 = in_st;
    int acounter1 = 1;
    while (true) {
      if (options["verbosity"] > 0)
        cout << "    Computing depth " << acounter1 << endl;

      for (unsigned int k = 0; k < agents->size(); k++)
        next1 *= (*vRT)[k];
      next1 = Exists(bddmgr, v, next1);
      next1 = next1.SwapVariables(*v, *pv);
      next1 = Exists(bddmgr, a, next1); // Clear actions.
      q1 = reach + next1;
      acounter1++;

      if (q1 == reach)
        break;
      else
        reach = q1;
    }

    if (options["verbosity"] > 2) {
      cout << "Done" << endl;
    }
  } else {
    reach = in_st;
    BDD next1 = in_st;
    int acounter1 = 1;
    while (true) {
      if (options["verbosity"] > 0)
        cout << "    Computing depth " << acounter1 << endl;

      for (unsigned int k = 0; k < agents->size(); k++)
        next1 *= (*vRT)[k];
      next1 = Exists(bddmgr, v, next1);
      next1 = next1.SwapVariables(*v, *pv);
      next1 = Exists(bddmgr, a, next1); // Clear actions.
      next1 = next1 - reach;
      acounter1++;

      if (next1 == bddmgr->bddZero())
        break;
      else
        reach = reach + next1;
      if (options["verbosity"] > 2) {
        cout << "Done" << endl;
      }
    }
  }

  para->reach = &reach;
  if (options["dao"] > 0) // 1: all disable, 2: after transition relation, 3: after reachable states
    Cudd_AutodynDisable(bddmgr->getManager());

  if (options["verbosity"] > 2)
    cout << "Done." << endl;

  // Check deadlock of the model
  if(options["deadlock"] == 1) {
    BDD ex = check_EX(para->bddmgr->bddOne(), para);
    bool satisfaction = ex == reach;

    if(satisfaction) {
      if(options["quiet"] == 0) 
        cout << "There is no deadlock state in the model!" << endl;
    } else {  
      BDD diff = reach - ex;
      BDD state = diff.PickOneMinterm(*para->v);
      
      if(options["quiet"] == 0) {
        cout << "Attention: there are deadlock states in the model!" << endl;
        cout << "The following state does not have any successors." << endl;
        print_state(state, *para->v);
        cout << "----------------------------------------" << endl;
      }
  
      if(options["cex"] > 0) 
        produce_witness(para, state, "deadlock");   
    }
  }
  
  // Check arithmetic overflow in the model
  if (options["overflow"] == 1) {
    BDD state;
    bool flag = false;
    BDD rc = reach;
    unsigned int i, j=0;
    for(i=0; i<agents->size(); i++)
      rc *= (*para->vprot)[i];
    for(i=0; i<agents->size(); i++) {
      vector< evolution_line * >* evolution = (*agents)[i]->get_evolution();
      for(j=0; j<evolution->size(); j++) {
        BDD bddevline = (*evolution)[j]->encode_bdd_overflow(para);
        bddevline *= rc;
        if(bddevline != para->bddmgr->bddZero()) {
          state = bddevline.PickOneMinterm(*para->v);
          flag = true;
          break;
        }
      }
      if(flag)
        break;
    }
    if(flag) {
      if(options["quiet"] == 0) {
        cout << "Evolution item " << j+1 << " in Agent " << (*agents)[i]->get_name()
             << " can cause overflow in the following state: " << endl;
        print_state(state, *para->v);
        cout << "----------------------------------------" << endl;
      }
      if(options["cex"] > 0) 
        produce_witness(para, state, "overflow");
    }
  }
  
  if(options["exportmodel"] == 1) {
    vector< vector< int >*> *countex = new vector< vector< int >*>;
    map< int, BDD * > *idbdd = new map< int, BDD * >;
    vector< vector< transition * >*> *cextr = new vector< vector< transition * >*>;

    BDD *is_temp = new BDD(*(para->in_st));
    export_model(para, is_temp, countex, idbdd, cextr);
    //string tempstr;
    //transform(filename.begin(), filename.end(), back_inserter(tempstr), ::tolower);
    string fname = cex_prefix + /*filename.substr(0, tempstr.rfind(".ispl")) +*/ "model";
    print_cex(para, fname, "statespace", idbdd, cextr);
    countex->clear();
    idbdd->clear();
    cextr->clear();
    delete countex;
    delete idbdd;
    delete cextr;
    delete is_temp;
  }

  if (options["quiet"] == 0)
    cout << "Checking formulae..." << endl;

  string str = "_init";
  (*is_evaluation)[str] = is_istates;
  modal_formula *init = new modal_formula(new atomic_proposition(&str));
  (*para->BDD_cache)["_init"] = in_st;

  if (is_fairness->size() > 0) {
    if (options["quiet"] == 0 || options["simulation"] == 0)
      cout << "Building set of fair states..." << endl;

    modal_formula *neg_init = new modal_formula(3, init);

    modal_formula *taut = new modal_formula(2, init, neg_init);

    for (vector< fairness_expression * >::iterator i =
           is_fairness->begin(); i != is_fairness->end(); i++) {
      BDD fairset = (*i)->check_formula(para);
      (*i)->set_bdd_representation(fairset);
    }

    modal_formula *eg_true = new modal_formula(11, taut); // This is EG(True)

    // This is a set of "fair" states (the beginning of a fair computation)
    fair_reach = eg_true->check_formula_fair(para, bddmgr->bddOne());

  }       // end if

  countex = new vector< vector< int >*>;
  idbdd = new map< int, BDD * >;
  cextr = new vector< vector< transition * >*>;

  if (options["quiet"] == 0 || options["simulation"] == 0)
    cout << "Verifying properties..." << endl;

  // Check if fair_reach is empty bdd
  if (is_fairness->size() > 0 && fair_reach == bddmgr->bddZero()) {
    if (options["quiet"] == 0)
      cout << "  Warning: ";
    cout << "The fairness constraint does not hold in any paths." << endl;
  }

  BDD result;
  
  get_all_shared_vars(&all_shared_var_names);

  char buff[20];
  for (unsigned int i = 0; i < is_formulae->size(); i++) {
    set< string > trans_set;
    scount = 0;
    bool satisfaction = false;
    modal_formula *f = &((*is_formulae)[i]);

    f = new modal_formula(4, init, &((*is_formulae)[i]));
    result = is_fairness->size() > 0 ?
      f->check_formula_fair(para, fair_reach) : f->check_formula(para);

  
    satisfaction = result == reach;
    if (options["quiet"] == 0)
      cout << "  Formula number " << i+1 << ": " <<
        (*is_formulae)[i].to_string() << ", is " << (satisfaction ?
                                                     "TRUE" : "FALSE")
           << " in the model" << endl;
    else
      cout << (satisfaction ? "TRUE" : "FALSE") << endl;
    
    if ((options["cex"] >= 1)) {
      // Computing counterexample / witness
      BDD *is = new BDD(in_st);
      
      countex->clear();
      idbdd->clear();
      scount = 0;
      cextr->clear();
      
      modal_formula *g = f->push_negations(0);
      
      cextr->clear();
      string str_head;
      bool done = false;
      bool hascex = false;

      if ((satisfaction) && !(g->is_NoCTL()) && (g->is_ECTLK_new())) {
        // True and ECTLK: can print witness
        hascex = true;
        str_head = "witness";
  
        if (options["quiet"] == 0 && (options["cex"] == 1 || options["cex"] == 3))
          cout << "  The following is a witness for the formula: " << endl;
  
        while ((*is) != bddmgr->bddZero()) {
          BDD curinitstate = is->PickOneMinterm(*v);
    
          if (is_valid_state(curinitstate, *v)) {
            bool cexresult = (is_fairness->size() > 0) ?
              g->build_cex_fair(&curinitstate, 0,
                                fair_reach,
                                para) : g->build_cex(&curinitstate, 0,
                                                     para);
            if (cexresult) {
              done = true;
              break;
            } else {
              *is = *is - curinitstate;
              idbdd->clear();
              countex->clear();
              cextr->clear();
              scount = 0;
            }
          }
        }
      } else if (!satisfaction) {
        // False and ACTLK: can print counterexample
        if (options["quiet"] == 0 && (options["cex"] == 1 || options["cex"] == 3))
          cout <<
            "  The following is a counterexample for the formula: " << endl;
        hascex = true;
        str_head = "counterexample";
  
        if(g->is_ACTLK_new()) {
          // Negation of the formula:
          modal_formula *fcex = new modal_formula(3, g);
          fcex = fcex->push_negations(0);
    
          while ((*is) != bddmgr->bddZero()) {
            BDD curinitstate = is->PickOneMinterm(*v);
      
            if (is_valid_state(curinitstate, *v)) {
              bool cexresult = (is_fairness->size() > 0) ?
                fcex->build_cex_fair(&curinitstate, 0,
                                     fair_reach,
                                     para) : fcex->build_cex(&curinitstate,
                                                             0, para);
              if (cexresult) {
                done = true;
                break;
              } else {
                *is = *is - curinitstate;
                idbdd->clear();
                countex->clear();
                cextr->clear();
                scount = 0;
              }
            }
          }
        } else {
          done = true;
          BDD init_state = (in_st - result).PickOneMinterm(*v);
          idbdd->insert(pair < int, BDD * >(0, new BDD(init_state)));
          vector< int >desc;    
          desc.push_back(0);
          countex->push_back(new vector< int >(desc));  
        }
      } else if (satisfaction) {
        if (options["quiet"] == 0)
          cout <<
            "    -- Sorry it is not possible to compute witnesses for non-ECTLK formulae"
               << endl;
      } 
  
      if(hascex) {
        if (!done) {
          if (options["quiet"] == 0) {
            cout <<
              "A " << str_head << " exists but could not be generated." << endl;
          }
        } else {
          if (options["cex"] == 1 || options["cex"] == 3) {
            for (int ac = 0; ac < (int) countex->size(); ac++) {
              cout << "   < ";
              for (int j = 0; j < (int) countex->at(ac)->size(); j++) {
                cout << countex->at(ac)->at(j) << " ";
              }
              cout << "> " << endl;
            }
      
            cout << "  States description: " << endl;
            for (map< int, BDD * >::iterator iter =
                   idbdd->begin(); iter != idbdd->end(); iter++) {
        
              cout << "------------- State: " << (*iter).first <<
                " -----------------" << endl;
              print_state(*(iter->second), *v);
              cout << "----------------------------------------" << endl;
            }
          }
          if (options["cex"] == 2 || options["cex"] == 3) {
            // Writing full witness/counterexample to text file
            sprintf(buff, "formula%1d.dot", i + 1);
            string filename = cex_prefix + buff;
            sprintf(buff, "formula%1d.info", i + 1);
            string filename2 = cex_prefix + buff;
            ofstream myfile(filename.c_str());
            ofstream myfile2(filename2.c_str());
      
            if (myfile.is_open() && myfile2.is_open()) {
              myfile << "digraph " << str_head << i << " {\n";
        
              // print states and their description
              for (map< int, BDD * >::iterator iter =
                     idbdd->begin(); iter != idbdd->end(); iter++) {
                myfile << " " << (*iter).first << " [label=\"" <<
                  (*iter).first << "\",shape=ellipse]" << endl;
                myfile2 << "-- State " << (*iter).first << " --" << endl;
                myfile2 << state_to_str(*(iter->second), *v) << endl;
              }
        
              // printing transitions
              for (int ac = 0; ac < (int) cextr->size(); ac++) {
                for (int j = 0; j < (int) cextr->at(ac)->size(); j++) {
                  string strTran = cextr->at(ac)->at(j)->index_to_string(a);
                  if (trans_set.find(strTran) == trans_set.end()) {
                    cextr->at(ac)->at(j)->to_str(&myfile, a);
                    trans_set.insert(strTran);
                  }
                }
              }
        
              myfile << "}\n";
        
              myfile.close();
              myfile2.close();
            } else
              cout << "Unable to open file";
          }
        }
      } 
    }
  }
  
  if (options["quiet"] == 0)
    cout << "done, " << is_formulae->size() <<
      " formulae successfully read and checked" << endl;
  //time_t t1 = time(0);
  struct timeb tmb1;
  ftime(&tmb1);

  //cout << "execution time = " << difftime(t1, t0) << endl;
  cout << "execution time = " << ((tmb1.time-tmb.time) + (tmb1.millitm-tmb.millitm)/1000.0) << endl;
  double reachablestates = reach.CountMinterm(v->count());
  cout << "number of reachable states = " << reachablestates << endl;
  unsigned long memoryinuse = bddmgr->ReadMemoryInUse();
  cout << "BDD memory in use = " << memoryinuse << endl;
  if (options["bdd_stats"] == 1) {
    bddmgr->info();
  }

  delete(v);
  delete(pv);
  delete(a);
  delete(addv);
  delete(addpv);
  delete(vevol);
  delete(vprot);
  delete(vRT);
  delete(para->in_st);
  delete para->BDD_cache;
  delete para->ADD_cache;
  delete para;
  delete is_agents;
  delete agents;
  delete is_evaluation;
  delete is_groups;
  delete is_formulae;
  delete is_fairness;
  delete string_table;
  delete variable_table;
  delete logic_expression_table;
  delete logic_expression_table1;
}
