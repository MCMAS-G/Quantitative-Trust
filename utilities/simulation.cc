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
#include "cuddObj.hh"

#define MAXINISTATES 100
#define MAXTRANSITIONS 100
#define MAXSTACKDEPTH 100

extern vector<string *> *string_table;
extern vector<bool_expression *> *logic_expression_table;
extern vector<bool_expression *> *logic_expression_table1;
extern vector<variable *> *variable_table;
extern map<string, basic_agent *> *is_agents;
extern vector<basic_agent *> *agents;
extern map<string, bool_expression *> *is_evaluation;
extern bool_expression *is_istates;
extern map<string, set<string> > *is_groups;
extern vector<modal_formula> *is_formulae;
extern vector<fairness_expression *> *is_fairness;
extern map < string, int > options;

extern BDD append_variable_BDDs(Cudd *bddmgr, BDDvector *v, BDD a);
extern bool is_valid_state(BDD state, BDDvector v);
extern bool is_valid_action(BDD state, BDDvector a);
extern bool find_same_state(map<string, int> *statehash, string state);
extern void print_action_1(BDD state, BDDvector a);
extern string state_to_str(BDD state, BDDvector v);
extern void print_state(BDD state, BDDvector v);
extern void print_action(BDD state, BDDvector a);
extern BDD Exists(Cudd *bddmgr, BDDvector* v, BDD x);

void exec_simulation(void *ptr) {
  bdd_parameters *para;
  para = (bdd_parameters *)ptr;
  Cudd* bddmgr = para->bddmgr; 
  BDDvector *v = para->v;
  ADDvector *addv = para->addv;
  BDDvector *pv = para->pv;
  ADDvector *addpv = para->addpv;
  BDDvector *a = para->a;
  BDDvector *vevol = para->vevol;
  BDDvector *vprot = para->vprot;
  BDDvector *vRT = para->vRT;
  BDD in_st;

  Cudd_AutodynEnable(bddmgr->getManager(), CUDD_REORDER_GROUP_SIFT_CONV);
  in_st = is_istates->encode_bdd_flat(para, new BDD(bddmgr->bddOne()));
  in_st = append_variable_BDDs(bddmgr, v, in_st);
  if (in_st==bddmgr->bddZero()) {
    cout << "No initial state. Check your model!" << endl;
    delete(v);
    delete(pv);
    delete(a);
    delete(addv);
    delete(addpv);
    delete(vevol);
    delete(vprot);
    delete(vRT);
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
    delete para->BDD_cache;
    delete para->ADD_cache;
    exit(0);
  }
  for (unsigned int i=0; i<agents->size(); i++) {
    (*vprot)[i] = (*agents)[i]->encode_protocol(para);
    if(options["smv"] == 0)
      (*vevol)[i] = (*agents)[i]->encode_evolution(para);
    else
      (*vevol)[i] = (*agents)[i]->encode_evolution_smv(para);
    (*vRT)[i] = (*vprot)[i] * (*vevol)[i];
  }
  Cudd_AutodynEnable(bddmgr->getManager(), CUDD_REORDER_SIFT);	
  BDDvector inistates(MAXINISTATES, bddmgr);
  int count=0;
  BDD is = in_st;
  map<string, int> statehash;
  while (count<MAXINISTATES && is != bddmgr->bddZero()) {
    inistates[count] = is.PickOneMinterm(*v);
    is = is - inistates[count];
    if (is_valid_state(inistates[count], *v)) {
      string state = state_to_str(inistates[count], *v);
      if(!find_same_state(&statehash, state)) {
	statehash[state] = 1;
	count++;
      }
    }
  }
  if(options["quiet"] == 0) {
    if (count==MAXINISTATES && is != bddmgr->bddZero())
      cout << "There are too many initial states. Please specify more initial values."
	   << endl;
    while (true) {
      BDDvector stack(MAXSTACKDEPTH, bddmgr);
      int sp = 0;
      cout << endl << "--------- Initial state ---------" << endl;
      int isindex = 0;
      print_state(inistates[isindex], *v);
      cout << "----------------------------" << endl;
      if (count>1) {
	bool choose = false;
	string c;
	while (!choose) {
	  if (isindex==0)
	    cout << "Is this the initial state? [Y(es), N(ext), E(xit)]: ";
	  else if (isindex==count-1)
	    cout << "Is this the initial state? [Y(es), P(revious), E(xit)]: ";
	  else
	    cout << "Is this the initial state? [Y(es), N(ext), P(revious), E(xit)]: ";
	  cin >> c;
	  transform(c.begin(), c.end(), c.begin(),
		    (int(*)(int))tolower);
	  if (c=="y" || c=="yes") {
	    choose = true;
	    break;
	  } else if ((isindex<count-1) && (c=="n" || c =="next")) {
	    isindex++;
	    cout << endl << "--------- Initial state ---------"
		 << endl;
	    print_state(inistates[isindex], *v);
	    cout << "----------------------------" << endl;
	  } else if (isindex>0 && (c=="p" || c=="previous")) {
	    isindex--;
	    cout << endl << "--------- Initial state ---------"
		 << endl;
	    print_state(inistates[isindex], *v);
	    cout << "----------------------------" << endl;
	  } else if (c=="e" || c=="exit") {
	    delete(v);
	    delete(pv);
	    delete(a);
	    delete(addv);
	    delete(addpv);
	    delete(vevol);
	    delete(vprot);
	    delete(vRT);
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
	    exit(0);
	  }
	  else
	    cout << "Please choose one option!" << endl;
	}
      }
      stack[sp++] = inistates[isindex]; // initial state
      while (true) {
	BDDvector enabled(MAXTRANSITIONS, bddmgr);
	int tcount = 0;
	BDD newstates;
	int tran = -2;
	if (sp>=MAXSTACKDEPTH) {
	  while (tran!=-1 && tran!=0) {
	    cout <<"Maximum stack depth is reached. Please type 0 to backtrack or -1 to quit immediately: ";
	    cin >> tran;
	  }
	} else {
	  newstates = stack[sp-1];// next state
	  for(unsigned int k=0; k<agents->size(); k++)
	    newstates *= (*vRT)[k];
	  BDD transitions = newstates;
	  if(newstates != bddmgr->bddZero()) {
	    while (tcount<MAXTRANSITIONS && transitions != bddmgr->bddZero()) {
	      enabled[tcount] = transitions.PickOneMinterm(*a);
	      transitions-=enabled[tcount];
	      if (is_valid_action(enabled[tcount], *a))
		tcount++;
	    }
	  }
	  if (tcount==MAXTRANSITIONS && transitions != bddmgr->bddZero())
	    cout << "There are too many enabled transitions. We only pick up 100 of them." << endl;
	  if (tcount>0) {
	    cout << "Enabled transtions: "<< endl;
	    for (int i=0; i<tcount; i++) {
	      cout << i+1 << " : ";
	      print_action(enabled[i], *a);
	    }
	    while (tran<-1 || tran>tcount) {
	      cout << "Please choose one, or type 0 to backtrack or -1 to quit: " << endl;
	      cin >> tran;
	    }
	  } else {
	    if(sp > 1 || count > 1) {
	      cout << "There is no enabled transition. Please type 0 to backtrack or -1 to quit immediately: ";
	      cin >> tran;
	      while(tran!=-1 && tran!=0) {
		cout<<"Maximum stack depth is reached. Please type 0 to backtrack or -1 to quit immediately: ";
		cin >> tran;
	      }
	    } else {
	      cout << "There is no enabled transition in the initial state. Simulation exits." << endl;
	      delete(v);
	      delete(pv);
	      delete(a);
	      delete(addv);
	      delete(addpv);
	      delete(vevol);
	      delete(vprot);
	      delete(vRT);
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
	      exit(0);
	    }
	  }
	}
	if(tran==-1) {
	  delete(v);
	  delete(pv);
	  delete(a);
	  delete(addv);
	  delete(addpv);
	  delete(vevol);
	  delete(vprot);
	  delete(vRT);
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
	  exit(0);
	}
	else if(tran==0 && sp>1) {
	  stack[--sp] = bddmgr->bddZero();
	  continue;
	} else if(tran==0 && sp==1) {
	  stack[--sp] = bddmgr->bddZero();
	  break;
	} else {
	  newstates *= enabled[tran-1];
	  BDD tmpstate = Exists(bddmgr, v, newstates); // clear state variables
	  tmpstate = tmpstate.SwapVariables(*v, *pv);
	  tmpstate = Exists(bddmgr, a, tmpstate); // clear action variables
	  tmpstate = append_variable_BDDs(bddmgr, v, tmpstate);
	  int count1=0;
	  BDDvector succstates(MAXINISTATES, bddmgr);
	  statehash.clear();
	  while (count1<MAXINISTATES && tmpstate != bddmgr->bddZero()) {
	    succstates[count1] = tmpstate.PickOneMinterm(*v);
	    tmpstate = tmpstate - succstates[count1];
	    if (is_valid_state(succstates[count1], *v)) {
	      string state = state_to_str(succstates[count1], *v);
	      if(!find_same_state(&statehash, state)) {
		statehash[state] = 1;
		count1++;
	      }
	    }
	  }
	  if (count1==MAXINISTATES && tmpstate != bddmgr->bddZero())
	    cout
	      << "There are too many states. Please refine your model."
	      << endl;
	  else if(count1>1)
	    cout << "Warning: there is more than one successor state." << endl;
	  cout << endl << "--------- Current state ---------" << endl;
	  int succindex = 0;
	  print_state(succstates[succindex], *v);
	  cout << "----------------------------" << endl;
	  if (count1>1) {
	    bool choose = false;
	    string c;
	    while (!choose) {
	      if (succindex==0)
		cout
		  << "Is this the current state? [Y(es), N(ext), E(xit)]: ";
	      else if (succindex==count1 -1)
		cout
		  << "Is this the current state? [Y(es), P(revious), E(xit)]: ";
	      else
		cout
		  << "Is this the current state? [Y(es), N(ext), P(revious), E(xit)]: ";
	      cin >> c;
	      transform(c.begin(), c.end(), c.begin(),
			(int(*)(int))tolower);
	      if (c=="y" || c=="yes") {
		  choose = true;
		  break;
	      } else if ((succindex<count1-1) && (c=="n" || c =="next")) {
		succindex++;
		cout << endl << "--------- Current state ---------"
		     << endl;
		print_state(succstates[succindex], *v);
		cout << "----------------------------" << endl;
	      } else if (succindex>0 && (c=="p" || c=="previous")) {
		succindex--;
		cout << endl << "--------- Initial state ---------"
		     << endl;
		print_state(succstates[succindex], *v);
		cout << "----------------------------" << endl;
	      } else if (c=="e" || c=="exit") {
		delete(v);
		delete(pv);
		delete(a);
		delete(addv);
		delete(addpv);
		delete(vevol);
		delete(vprot);
		delete(vRT);
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
		exit(0);
	      }
	      else
		cout << "Please choose one option!" << endl;
	    }
	  }
	  stack[sp++] = succstates[succindex];
	}
      }
    }
  } else {
    while (true) {
      BDDvector stack(MAXSTACKDEPTH, bddmgr);
      int sp = 0;
      for(int k=0; k<count; k++) {
	cout << endl << "-- State " << (k+1) << " --" << endl;
	print_state(inistates[k], *v);
      }
      cout << "Done." << endl;
      int isindex = 0;;
      cin >> isindex;
      if(isindex==-1) {
	delete(v);
	delete(pv);
	delete(a);
	delete(addv);
	delete(addpv);
	delete(vevol);
	delete(vprot);
	delete(vRT);
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
	exit(0);
      }
      stack[sp++] = inistates[isindex-1]; // initial state
      while (true) {
	BDDvector enabled(MAXTRANSITIONS, bddmgr);
	int tcount = 0;
	BDD newstates;
	int tran = -2;
	if (sp>=MAXSTACKDEPTH) {
	  while (tran!=-1 && tran!=0) {
	    cout <<"Maximum stack depth is reached. Please backtrack or quit.";
	    cin >> tran;
	  }
	} else {
	  newstates = stack[sp-1];// next state
	  for(unsigned int k=0; k<agents->size(); k++)
	    newstates *= (*vRT)[k];
	  BDD transitions = newstates;
	  if(newstates != bddmgr->bddZero()) {
	    while (tcount<MAXTRANSITIONS && transitions != bddmgr->bddZero()) {
	      enabled[tcount] = transitions.PickOneMinterm(*a);
	      transitions-=enabled[tcount];
	      if (is_valid_action(enabled[tcount], *a))
		tcount++;
	    }
	  }
	  if (tcount>0) {
	    for (int i=0; i<tcount; i++) {
	      cout << "-- transition "<< (i+1) << " --" << endl;
	      print_action_1(enabled[i], *a);
	    }
	    cout << "Done." << endl;
	    while (tran<-1 || tran>tcount) {
	      cin >> tran;
	    }
	  } else {
	    if(sp > 1 || count > 1) {
	      cout << "There is no enabled transition. Please backtrack or quit.";
	      cin >> tran;
	    } else {
	      cout << "There is no enabled transition in the initial state." << endl;
	      delete(v);
	      delete(pv);
	      delete(a);
	      delete(addv);
	      delete(addpv);
	      delete(vevol);
	      delete(vprot);
	      delete(vRT);
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
	      exit(0);
	    }
	  }
	}
	if(tran==-1){
	  delete(v);
	  delete(pv);
	  delete(a);
	  delete(addv);
	  delete(addpv);
	  delete(vevol);
	  delete(vprot);
	  delete(vRT);
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
	  exit(0);
	}
	else if(tran==0 && sp>1) {
	  stack[--sp] = bddmgr->bddZero();
	  continue;
	} else if(tran==0 && sp==1) {
	  stack[--sp] = bddmgr->bddZero();
	  break;
	} else {
	  newstates *= enabled[tran-1];
	  BDD tmpstate = Exists(bddmgr, v, newstates); // clear state variables
	  tmpstate = tmpstate.SwapVariables(*v, *pv);
	  tmpstate = Exists(bddmgr, a, tmpstate); // clear action variables
	  tmpstate = append_variable_BDDs(bddmgr, v, tmpstate);
	  int count1=0;
	  BDDvector succstates(MAXINISTATES, bddmgr);
	  statehash.clear();
	  while (count1<MAXINISTATES && tmpstate != bddmgr->bddZero()) {
	    succstates[count1] = tmpstate.PickOneMinterm(*v);
	    tmpstate = tmpstate - succstates[count1];
	    if (is_valid_state(succstates[count1], *v)) {
	      string state = state_to_str(succstates[count1], *v);
	      if(!find_same_state(&statehash, state)) {
		statehash[state] = 1;
		count1++;
	      }
	    }
	  }
	  for(int k=0; k<count1; k++) {
	    cout << endl << "-- State " << (k+1) << " --" << endl;
	    print_state(succstates[k], *v);
	  }
	  cout << "Done." << endl;
	  int succindex = 0;
	  cin >> succindex;
	  if(succindex == -1){
	    delete(v);
	    delete(pv);
	    delete(a);
	    delete(addv);
	    delete(addpv);
	    delete(vevol);
	    delete(vprot);
	    delete(vRT);
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
	    exit(0);
	  }
	  if(succindex > 0)
	    stack[sp++] = succstates[succindex-1];
	}
      }
    }
  }
}
