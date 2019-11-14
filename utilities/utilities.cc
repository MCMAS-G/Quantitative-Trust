#include "utilities.hh"
#include "cuddInt.h"
BDD
Exists(Cudd * bddmgr, BDDvector * v, BDD x)
{
  BDD tmp = bddmgr->bddOne(); // Always true
  for (int j = 0; j < v->count(); j++) {
    tmp = tmp * (*v)[j];
  } return x.ExistAbstract(tmp);
}

ADD
ADDExists(Cudd * bddmgr, ADDvector v, ADD x)
{
  ADD tmp = bddmgr->addOne(); // Always true
  for (int j = 0; j < v.count(); j++) {
    tmp = tmp * v[j];
  } return x.ExistAbstract(tmp);
}

BDD
timesTrans(BDD * from, BDD * to, BDDvector * vRT)
{
  BDD result;
  result = (*from) * (*to) * (*vRT)[0];
  for (unsigned int i = 1; i < agents->size(); i++)
    result *= (*vRT)[i];
  return result;
}

BDD
timesRT(BDD * state, Cudd * bddmgr, BDDvector * vRT, BDDvector * a)
{
  BDD result;
  result = (*state) * (*vRT)[0];
  for (unsigned int i = 1; i < agents->size(); i++)
    result *= (*vRT)[i];
  result = Exists(bddmgr, a, result);
  return result;
}

BDD
check_EX(BDD next, bdd_parameters * para)
{
  // Computes the preimage
	/* if (para->calReachRT) {
    BDD reachRT1 = *para->reach;
    for (unsigned int i = 0; i < agents->size(); i++)
      reachRT1 *= (*para->vRT)[i];
    para->reachRT = new BDD(reachRT1);
    para->calReachRT = false;
  }

  BDD result = next.SwapVariables(*para->v, *para->pv); // Now it's the next state

  result = result * (*para->reachRT);*/

  if(options["nobddcache"] == 0) {
    if (para->calReachRT) {
      BDD reachRT1 = *para->reach;
      for (unsigned int i = 0; i < agents->size(); i++)
        reachRT1 *= (*para->vRT)[i];
      para->reachRT = new BDD(reachRT1);
      para->calReachRT = false;
    }
  }
  BDD result = next.SwapVariables(*para->v, *para->pv); // Now it's the next state
  if(options["nobddcache"] == 0)
    result = result * (*para->reachRT);
  else {
    for (unsigned int i = 0; i < agents->size(); i++)
      result *= (*para->vRT)[i];
  }

  result = Exists(para->bddmgr, para->pv, result);  // States from which...
  result = Exists(para->bddmgr, para->a, result); //Exists a joint action...
  result = result * (*para->reach);
 
  return result;
}

BDD
check_EF(BDD p, bdd_parameters * para)
{
  // Computes the fixpoint iterating false
  BDD tmp = para->bddmgr->bddOne();
  BDD q = para->bddmgr->bddZero();
  while (q != tmp) {
    tmp = q;
    q = p + check_EX(tmp, para);
  }
  return q * (*para->reach);
}

BDD
check_EG(BDD p, bdd_parameters * para)
{
  // Computes the fixpoint iterating false
  BDD tmp = para->bddmgr->bddZero();
  BDD q = para->bddmgr->bddOne();
  while (q != tmp) {
    tmp = q;
    BDD x = check_EX(tmp, para);
    q = p * x;
  }
  return q;
}

BDD
check_EU(BDD p, BDD q, bdd_parameters * para)
{       // See Huth-Ryan, pag. 180
  BDD W = p;
  BDD X = *para->reach;
  BDD Y = q;
  while (X != Y) {
    X = Y;
    Y = Y + (W * check_EX(Y, para));
  }
  return Y;
}

BDD
check_AU(BDD p, BDD q, bdd_parameters * para)
{       // Tricky one, see Huth Ryan pag. 167 and 179
  BDD result =
    !(check_EU(!q, !p * !q, para) + check_EG(!q, para)) * (*para->reach);
  return result;
}

BDD
check_nO(BDD next, string name, bdd_parameters * para)
{
  // Check deontic
  next = next.SwapVariables(*para->v, *para->pv); // Now it's the next state
  BDD RO = (*is_agents)[name]->encode_greenstates(para);
  BDD result = Exists(para->bddmgr, para->pv, RO * next * (*para->reach));  // States from which...
  return result;
}

BDD
check_GK(BDD next, string name, bdd_parameters * para)
{
  set < string > gi = (*is_groups)[name];
  BDD tmp = para->bddmgr->bddZero();
  BDD ntmp = (*para->reach) - next;
  for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
    basic_agent *agent = (*is_agents)[*igs];
    tmp += agent->project_local_state(&ntmp, para->bddmgr, para->v);
  }
  tmp = (*para->reach) - tmp;
  return tmp;
}

BDD
check_DK(BDD next, string name, bdd_parameters * para)
{
  set < string > gi = (*is_groups)[name];
  BDD tmp = para->bddmgr->bddOne();
  BDD ntmp = (*para->reach) - next;
  for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
    basic_agent *agent = (*is_agents)[*igs];
    tmp *= agent->project_local_state(&ntmp, para->bddmgr, para->v);
  }
  tmp = (*para->reach) - tmp;
  return tmp;
}

BDD
check_GCK(BDD next, string name, bdd_parameters * para)
{
  // GCK p = GK(p * GCK(p)) see fhmv:rak, section 11.5
  BDD tmp = *para->reach;
  BDD tmp2 = next;
  set < string > gi = (*is_groups)[name];
  while (tmp != tmp2) {
    tmp2 = tmp;
    tmp = next * tmp;
    BDD ntmp = (*para->reach) - tmp;
    tmp = para->bddmgr->bddZero();
    for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
      basic_agent *agent = (*is_agents)[*igs];
      tmp += agent->project_local_state(&ntmp, para->bddmgr, para->v);
    }
    tmp = (*para->reach) - tmp;
  }
  return tmp;
}

BDD
check_ATLX(BDD next, string grpname, bdd_parameters * para)
{
  BDD result = para->bddmgr->bddZero();
  BDD actagtin = para->bddmgr->bddOne();  // Actions of agents in group
  BDD actagtout = para->bddmgr->bddOne(); // Actions of agents NOT in group
  int begin, end;
  map < string, set < string > >::iterator gi = is_groups->find(grpname);
  set < string > names_g = gi->second;  // the list of agt names in groups
  for (map < string, basic_agent * >::iterator i = is_agents->begin();
       i != is_agents->end(); i++) {
    begin = i->second->get_action_index_begin();
    end = i->second->get_action_index_end();
    if (names_g.find(i->first) == names_g.end()) {
      for (int j = begin; j <= end; j++) {
        actagtout = actagtout * (*para->a)[j];
      }}

    else {
      for (int j = begin; j <= end; j++) {
        actagtin = actagtin * (*para->a)[j];
      }}} BDD partial = (!next) * (*para->reach);
  partial = partial.SwapVariables(*para->v, *para->pv);
  for (unsigned int i = 0; i < agents->size(); i++)
    partial = partial * (*para->vevol)[i];
  partial = Exists(para->bddmgr, para->pv, partial);
  partial = partial * (*para->reach);
  for (unsigned int i = 0; i < agents->size(); i++)
    partial = partial * (*para->vprot)[i];
  partial = partial.ExistAbstract(actagtout);
  partial = (!partial) * (*para->reach);
  for (unsigned int i = 0; i < agents->size(); i++)
    partial = partial * (*para->vprot)[i];
  partial = partial.ExistAbstract(actagtout);
  result = partial.ExistAbstract(actagtin) * (*para->reach);
  return result;
}

BDD
check_ATLG(BDD p, string grpname, bdd_parameters * para)
{
  BDD tmp = p;
  BDD q = para->bddmgr->bddOne();
  while (q != tmp) {
    q = tmp;
    tmp = p * check_ATLX(tmp, grpname, para);
  }
  return q;
}

BDD
check_ATLU(BDD q1, BDD q2, string grpname, bdd_parameters * para)
{
  BDD r = para->bddmgr->bddZero();
  BDD t = q2;
  while (t != r) {
    r = t;
    t = r + check_ATLX(r, grpname, para) * q1;
  }
  return r;
}

BDD
check_ATLX_fair(BDD next, string grpname, BDD fair_reach,
                bdd_parameters * para)
{
  return check_ATLX(next * fair_reach, grpname, para);
}

BDD
check_ATLG_fair(BDD p, string grpname, bdd_parameters * para)
{
  BDD tmp = para->bddmgr->bddZero();
  BDD q = para->bddmgr->bddOne();
  BDD fc_bdd = para->bddmgr->bddOne();
  while (q != tmp) {
    tmp = q;
    for (vector < fairness_expression * >::iterator fi =
           is_fairness->begin(); fi != is_fairness->end(); fi++) {
      BDD hf = (*fi)->get_bdd_representation(); // The BDD for the fairness constraint
      BDD tmp1 = check_ATLU(p, q * hf, grpname, para);
      fc_bdd = fc_bdd * check_ATLX(tmp1, grpname, para);
    }
    q = p * fc_bdd;
  }
  return q;
}

BDD
check_ATLU_fair(BDD q1, BDD q2, string grpname, BDD fair_reach,
                bdd_parameters * para)
{
  return check_ATLU(q1, q2 * fair_reach, grpname, para);
}

BDD
check_EG_fair(BDD p, bdd_parameters * para)
{
  // Computes the fixpoint iterating false
  // See "Efficient generation of counterexamples and witnesses in
  // symbolic model checking", Clarke Grumberg McMillan Zhao, 1995
  // Section 4, p.3
  BDD tmp = para->bddmgr->bddZero();
  BDD q = para->bddmgr->bddOne();
  BDD fc_bdd = para->bddmgr->bddOne();
  while (q != tmp) {
    tmp = q;
    for (vector < fairness_expression * >::iterator fi =
           is_fairness->begin(); fi != is_fairness->end(); fi++) {
      BDD hf = (*fi)->get_bdd_representation(); // The BDD for the fairness constraint
      BDD tmp1 = check_EU(p, q * hf, para);
      fc_bdd = fc_bdd * check_EX(tmp1, para);
    }
    q = p * fc_bdd;
  }
  return q;
}

BDD
check_EF_fair(BDD p, BDD fair_reach, bdd_parameters * para)
{
  return check_EU_fair(*para->reach, p, fair_reach, para);
}

BDD
check_EX_fair(BDD p, BDD fair_reach, bdd_parameters * para)
{
  return check_EX(p * fair_reach, para);
}

BDD
check_EU_fair(BDD p, BDD q, BDD fair_reach, bdd_parameters * para)
{
  return check_EU(p, q * fair_reach, para);
}

BDD
check_nO_fair(BDD next, string name, BDD fair_reach, bdd_parameters * para)
{
  // Check deontic
  next = next.SwapVariables(*para->v, *para->pv); // Now it's the next state
  BDD RO = (*is_agents)[name]->encode_greenstates(para);
  BDD result = Exists(para->bddmgr, para->pv, RO * next * fair_reach);  // States from which...
  return result;
}

BDD
check_GK_fair(BDD next, string name, BDD fair_reach, bdd_parameters * para)
{
  set < string > gi = (*is_groups)[name];
  BDD tmp = para->bddmgr->bddZero();
  BDD ntmp = fair_reach - next;
  for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
    basic_agent *agent = (*is_agents)[*igs];
    tmp += agent->project_local_state(&ntmp, para->bddmgr, para->v);
  }
  tmp = (*para->reach) - tmp;
  return tmp;
}

BDD
check_DK_fair(BDD next, string name, BDD fair_reach, bdd_parameters * para)
{
  set < string > gi = (*is_groups)[name];
  BDD tmp = para->bddmgr->bddOne();
  BDD ntmp = fair_reach - next;
  for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
    basic_agent *agent = (*is_agents)[*igs];
    tmp *= agent->project_local_state(&ntmp, para->bddmgr, para->v);
  }
  tmp = (*para->reach) - tmp;
  return tmp;
}

BDD
check_GCK_fair(BDD next, string name, BDD fair_reach,
               bdd_parameters * para)
{
  // GCK p = GK(p * GCK(p)) see fhmv:rak, section 11.5
  BDD tmp = *para->reach;
  BDD tmp2 = next;
  set < string > gi = (*is_groups)[name];
  while (tmp != tmp2) {
    tmp2 = tmp;
    tmp = next * tmp;
    BDD ntmp = fair_reach - tmp;
    tmp = para->bddmgr->bddZero();
    for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
      basic_agent *agent = (*is_agents)[*igs];
      tmp += agent->project_local_state(&ntmp, para->bddmgr, para->v);
    }
    tmp = (*para->reach) - tmp;
  }
  return tmp;
}

BDD 
get_non_unique(BDD p, string name, bdd_parameters * para)
{
  basic_agent *agent = (*is_agents)[name];
  BDD s = para->bddmgr->bddZero();
  BDD tmp = agent->project_local_state(&p, para->bddmgr, para->v);
  BDDvector *localv = agent->get_local_state_vector(para->bddmgr, para->v);
  BDD tmp1, tmp2, tmp3;
  while(tmp != para->bddmgr->bddZero()) {
    tmp1 = tmp.PickOneMinterm(*localv);
    tmp = tmp - tmp1;
    tmp2 = tmp1 * p;
    if((tmp2 - tmp2.PickOneMinterm(*para->v)) != para->bddmgr->bddZero()) 
      s += tmp2; 
  }
  return s;
}

BDD
get_K2_states(BDD * state, string name, string name1, bdd_parameters * para)
{
  basic_agent *agent = (*is_agents)[name];
  basic_agent *agent1 = (*is_agents)[name1];
  map< string, variable * >* lobsvars = agent->get_lobsvars();
  map< string, variable * >* lobsvars1 = agent1->get_lobsvars();
  int index_begin = agent->get_var_index_begin();
  int index_end = agent->get_var_index_end();
  int index_begin1 = agent1->get_var_index_begin();
  int index_end1 = agent1->get_var_index_end();

  BDD tmp = para->bddmgr->bddOne(); // Always true

  if (lobsvars != NULL && lobsvars->size() > 0 && lobsvars1 != NULL && lobsvars1->size() > 0) {
    map< string, basictype * >*envars = (*agents)[0]->get_vars();
    for (map< string, basictype * >::iterator i = envars->begin();
         i != envars->end(); i++) {
      if (lobsvars->find(i->first) == lobsvars->end() && 
          lobsvars1->find(i->first) == lobsvars1->end()) {  // i->first is not local observable variable 
        basictype *bt = i->second;
        int index_begin = bt->get_index_begin();
        int index_end = bt->get_index_end();
        for (int j = index_begin; j <= index_end; j++)
          tmp = tmp * (*para->v)[j];
      }
    }
  } else if (lobsvars != NULL && lobsvars->size() > 0) {
    map< string, basictype * >*envars = (*agents)[0]->get_vars();
    for (map< string, basictype * >::iterator i = envars->begin();
         i != envars->end(); i++) {
      if (lobsvars->find(i->first) == lobsvars->end()) {  // i->first is not local observable variable 
        basictype *bt = i->second;
        int index_begin = bt->get_index_begin();
        int index_end = bt->get_index_end();
        for (int j = index_begin; j <= index_end; j++)
          tmp = tmp * (*para->v)[j];
      }
    }
  } else if (lobsvars1 != NULL && lobsvars1->size() > 0) {
    map< string, basictype * >*envars = (*agents)[0]->get_vars();
    for (map< string, basictype * >::iterator i = envars->begin();
         i != envars->end(); i++) {
      if (lobsvars1->find(i->first) == lobsvars1->end()) {  // i->first is not local observable variable 
        basictype *bt = i->second;
        int index_begin = bt->get_index_begin();
        int index_end = bt->get_index_end();
        for (int j = index_begin; j <= index_end; j++)
          tmp = tmp * (*para->v)[j];
      }
    }
  } 

  if(index_begin > index_begin1) {
    int i = index_begin;
    index_begin = index_begin1;
    index_begin1 = i;
    i = index_end;
    index_end = index_end1;
    index_end1 = i;
  }

  for (int j = envars_bdd_length; j < index_begin; j++) {
    tmp = tmp * (*para->v)[j];
  }

  for (int j = index_end + 1; j < index_begin1; j++) {
    tmp = tmp * (*para->v)[j];
  }

  for (int j = index_end1 + 1; j < para->v->count(); j++) {
    tmp = tmp * (*para->v)[j];
  }

  BDD states = state->ExistAbstract(tmp);
  return (*para->reach) * states;
}

BDD 
get_Rsc_Future(BDD p, string name, string name1, bdd_parameters * para)
{
  basic_agent *agent = (*is_agents)[name];
  BDD s = para->bddmgr->bddZero();
  BDD tmp = agent->project_local_state(&p, para->bddmgr, para->v);
  BDDvector *localv = agent->get_local_state_vector(para->bddmgr, para->v);
  BDD tmp1, tmp2, tmp3;
  while(tmp != para->bddmgr->bddZero()) {
    tmp1 = tmp.PickOneMinterm(*localv);
    tmp2 = *para->reach * tmp1;
    //cout << "--------------- tmp2 ---------------" << endl;
    //print_states(tmp2, *para->v, para->bddmgr);
    if((tmp2 - tmp2.PickOneMinterm(*para->v)) != para->bddmgr->bddZero()) {
      BDD tmp7 = tmp1 * p;
      while (tmp7 != para->bddmgr->bddZero()) {
        BDD tmp6 = tmp7.PickOneMinterm(*para->v);
        tmp7 = tmp7 - tmp6;
        BDD tmp8 = tmp2 - tmp6;
        /*BDD tmp31 = get_nK_states(&tmp8, name1, para);
          BDD tmp32 = get_nK_states(&tmp8, name, para);
          BDD tmp3 = tmp31 * tmp32;*/
        BDD tmp3 = get_K2_states(&tmp8, name, name1, para);
        //cout << "--------------- tmp3 ---------------" << endl;
        //print_states(tmp3, *para->v, para->bddmgr);
        BDD tmp4 = get_Future(tmp6, para);
        //cout << "--------------- tmp4 ---------------" << endl;
        //print_states(tmp4, *para->v, para->bddmgr);
        BDD tmp5 = tmp3 * tmp4;
        s += tmp5; 
      }
    }
    tmp = tmp - tmp1;
  }
  return s;
}

BDD
check_SC(BDD p, string name, string name1, bdd_parameters * para)
{
  BDD X1 = *para->reach - p;
  if(options["verbosity"] == 1) {
    cout << "--------------- X1 ---------------" << endl;
    print_states(X1, *para->v, para->bddmgr);
  }
  /*BDD X11 = get_nK_states(&X1, name1, para);
    BDD X12 = get_nK_states(&X1, name, para);
    BDD X2 = X11 * X12;*/
  BDD X2 = get_K2_states(&X1, name, name1, para);
  if(options["verbosity"] == 1) {
    cout << "--------------- X2 ---------------" << endl;
    print_states(X2, *para->v, para->bddmgr);
  }
  BDD X21 = get_nK_states(&X2, name, para) - X2;
  if(options["verbosity"] == 1) {
    cout << "--------------- X21 ---------------" << endl;
    print_states(X21, *para->v, para->bddmgr);
  }
  BDD X22 = get_non_unique(X2, name, para);
  if(options["verbosity"] == 1) {
    cout << "--------------- X22 ---------------" << endl;
    print_states(X22, *para->v, para->bddmgr);
  }
  BDD X3 = X21 + X22;
  if(options["verbosity"] == 1) {
    cout << "--------------- X3 ---------------" << endl;
    print_states(X3, *para->v, para->bddmgr);
  }
  basic_agent *agent = (*is_agents)[name];
  BDD X5 = agent->get_SC(para);
  if(options["verbosity"] == 1) {
    cout << "--------------- X5 ---------------" << endl;
    print_states(X5, *para->v, para->bddmgr);
  }
  BDD X6 = (*para->reach - X3) * X5;
  if(options["verbosity"] == 1) {
    cout << "--------------- X6 ---------------" << endl;
    print_states(X6, *para->v, para->bddmgr);
  }
  return X6;
}

BDD 
get_Future(BDD p, bdd_parameters * para) 
{
  BDD reach = p;
  BDD q1 = para->bddmgr->bddZero();
  BDD next1 = p;
  int acounter1 = 1;
  while (true) {
    //if (options["verbosity"] > 0)
    //  cout << "    Computing depth " << acounter1 << endl;
    
    for (unsigned int k = 0; k < agents->size(); k++)
      next1 *= (*para->vRT)[k];
    next1 = Exists(para->bddmgr, para->v, next1);
    next1 = next1.SwapVariables(*para->v, *para->pv);
    next1 = Exists(para->bddmgr, para->a, next1); // Clear actions.
    q1 = reach + next1;
    acounter1++;
    
    if (q1 == reach)
      break;
    else
      reach = q1;
  }
  return reach;
}

BDD 
get_Past(BDD p, bdd_parameters * para) 
{
  return check_EF(p, para);
}

BDD
check_Fu(BDD p, string name, string name1, bdd_parameters * para)
{
  BDD X1 = check_SC(p, name, name1, para);
  if(options["verbosity"] == 1) {
    cout << "--------------- X1 ---------------" << endl;
    print_states(X1, *para->v, para->bddmgr);
  }
  BDD X2 = get_nK_states(&X1, name, para) - X1;
  if(options["verbosity"] == 1) {
    cout << "--------------- X2 ---------------" << endl;
    print_states(X2, *para->v, para->bddmgr);
  }
  BDD X3 = get_non_unique(X1, name, para);
  if(options["verbosity"] == 1) {
    cout << "--------------- X3 ---------------" << endl;
    print_states(X3, *para->v, para->bddmgr);
  }
  BDD X4 = X2 + X3;
  if(options["verbosity"] == 1) {
    cout << "--------------- X4 ---------------" << endl;
    print_states(X4, *para->v, para->bddmgr);
  }
  /*BDD X51 = get_nK_states(&X4, name1, para);
    BDD X52 = get_nK_states(&X4, name, para);
    BDD X5 = X51 * X52;*/
  BDD X5 = get_K2_states(&X4, name, name1, para);
  if(options["verbosity"] == 1) {
    cout << "--------------- X5 ---------------" << endl;
    print_states(X5, *para->v, para->bddmgr);
  }
  BDD reach = get_Future(X1, para);

  BDD X6 = reach * X4;
  if(options["verbosity"] == 1) {
    cout << "--------------- X6 ---------------" << endl;
    print_states(X6, *para->v, para->bddmgr);
  }
  return X6;
}

BDD
check_Vi(BDD p, string name, string name1, bdd_parameters * para)
{
  BDD X1 = check_SC(p, name, name1, para);
  if(options["verbosity"] == 1) {
    cout << "--------------- X1 ---------------" << endl;
    print_states(X1, *para->v, para->bddmgr);
  }
  /*BDD X2 = get_nK_states(&X1, name, para) - X1;
    BDD X3 = get_non_unique(X1, name, para);
    BDD X4 = X2 + X3;
    BDD X5 = get_nK_states(&X4, name1, para);
    cout << "--------------- X2 ---------------" << endl;
    print_states(X5, *para->v, para->bddmgr);*/

  BDD X2 = get_Rsc_Future(X1, name, name1, para);
  if(options["verbosity"] == 1) {
    cout << "--------------- X2 ---------------" << endl;
    print_states(X2, *para->v, para->bddmgr);
  }
  BDD X1_Future = get_Future(X1, para);
  if(options["verbosity"] == 1) {
    cout << "--------------- X3 ---------------" << endl;
    print_states(X1_Future, *para->v, para->bddmgr);
  }
  BDD X2_Future = get_Future(X2, para);
  BDD X2_Past = get_Past(X2, para);
  BDD X6 = *para->reach - (X2_Future + X2_Past);
  if(options["verbosity"] == 1) {
    cout << "--------------- X4 ---------------" << endl;
    print_states(X6, *para->v, para->bddmgr);
  }
  BDD X7 = X1_Future * X6;
  if(options["verbosity"] == 1) {
    cout << "--------------- return ---------------" << endl;
    print_states(X7, *para->v, para->bddmgr);
  }
  return X7;
}

//========================================================================
void get_shared_vars(string name1, string name2, vector<basictype *> *shared) {
  basic_agent *ag1 = (*is_agents)[name1];
  basic_agent *ag2 = (*is_agents)[name2];

  // we only allow shared variables to be local variables;
  // otherwise, they have to have the same value all the time

  // get local variables in the first agent ag1
  // here we use the vector of variables since we 
  // enumerate each variable
  vector< basictype * > *vars1 = ag1->get_vec_vars();
  // get local variables in the second agent ag2
  // here we use the hash map of variables to speed up 
  // the search
  map< string, basictype * > *vars2 = ag2->get_vars();

  if (vars1 != NULL && vars2 != NULL) {
    for(unsigned i=0; i<vars1->size(); i++) {
      // get the name of a variable in ag1
      string varname = (*vars1)[i]->get_name();
      // check if the variable is defined in ag2
      if (vars2->find(varname) != vars2->end()) {
        // the variable is defined in both agents
        // get the defintion in both agents
        shared->push_back((*vars1)[i]);
        shared->push_back((*vars2)[varname]);
        
        //cout << "found a shared variable: " << varname << endl;
      }
    }
  }
} 

BDD build_shared_equivalence(vector<basictype *> *shared, bdd_parameters * para) {
  BDD eq = para->bddmgr->bddOne();
  // each shared variable has a pair of definitions in shared
  for(unsigned int i=0; i<shared->size(); i=i+2) {
    BDD tmp = para->bddmgr->bddOne();
    // get the definition in ag1
    basictype *var1 = (*shared)[i];
    // get the definition in ag2
    basictype *var2 = (*shared)[i+1];
    // get the starting location of BDD variables for the definition in ag1
    int begin1 = var1->get_index_begin();
    // get the end location of BDD variables for the definition in ag1
    int end1 = var1->get_index_end();
    // get the starting location of BDD variables for the definition in ag2
    // the end location can be computed since the number of BDD variables 
    // is the same in both agents
    int begin2 = var2->get_index_begin();
    // compute the distance between two groups of BDD variables
    int delta = begin2 - begin1;

    for(int j=begin1; j<=end1; j++)
      // Build the equivalence relation between two definitions of the shared variable
      tmp = tmp * ( ( !(*para->v)[j] + (*para->v)[j+delta] ) *
                    ( (*para->v)[j] + !(*para->v)[j+delta] ) );

		// build the conjunction of each equivalence relation
    eq *= tmp;
  }

  return eq;
}

BDD
get_eq_states(BDD * state, string name1, string name2, vector<basictype *> *shared, bdd_parameters * para)
{
  basic_agent *agent1 = (*is_agents)[name1];
  basic_agent *agent2 = (*is_agents)[name2];

  BDD localstate1 = agent1->project_local_state(state, para->bddmgr, para->v);

  BDD tmp = para->bddmgr->bddOne(); // Always true
  
  map< string, variable * >*lobsvars = agent2->get_lobsvars();
  if (lobsvars != NULL && lobsvars->size() > 0) {
    map< string, basictype * >*envars = (*agents)[0]->get_vars();
    for (map< string, basictype * >::iterator i = envars->begin();
         i != envars->end(); i++) {
      if (lobsvars->find(i->first) == lobsvars->end()) {  // i->first is not local observable variable 
        basictype *bt = i->second;
        int index_begin = bt->get_index_begin();
        int index_end = bt->get_index_end();
        for (int j = index_begin; j <= index_end; j++)
          tmp = tmp * (*para->v)[j];
      }
    }
    for (int j = envars_bdd_length; j < agent2->get_var_index_begin(); j++) {
      tmp = tmp * (*para->v)[j];
    }
  } else {
    for (int j = obsvars_bdd_length; j < agent2->get_var_index_begin(); j++) {
      tmp = tmp * (*para->v)[j];
    }
  }
  
  for (int j = agent2->get_var_index_end() + 1; j < para->v->count(); j++) {
    tmp = tmp * (*para->v)[j];
  }

  for(unsigned int i=1; i<shared->size(); i=i+2) {
    basictype *var1 = (*shared)[i];
    int begin1 = var1->get_index_begin();
    int end1 = var1->get_index_end();
    for (int j = begin1; j <= end1; j++) {
      tmp = tmp * (*para->v)[j];
    }
  }

  BDD localstate2 = state->ExistAbstract(tmp);
  return (*para->reach) * localstate1 * localstate2;
}

// p is the set of states satisfying \phi
BDD get_SC_states(BDD p, string name1, string name2, bdd_parameters *para) {
  vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);

  //cout << "--------------- get_SC_states ---------------" << endl;
  BDD q = (*para->reach - p);
  if(options["verbosity"] > 1) {
    cout << "---- q ----" << endl;
    print_states(q, *para->v, para->bddmgr);
  }
  BDD tmp =  q * build_shared_equivalence(&shared, para);
  if(options["verbosity"] > 1) {
    cout << "---- tmp ----" << endl;
    print_states(tmp, *para->v, para->bddmgr);
  }
  BDD tmp1 = get_eq_states(&tmp, name1, name2, &shared, para);  
  if(options["verbosity"] > 1) {
    cout << "---- tmp1 ----" << endl;
    print_states(tmp1, *para->v, para->bddmgr);
  }
  BDD result = *para->reach - tmp1;
  /*if(options["verbosity"] == 1) {
    cout << "---- result ----" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/
  return result;
}

// p is the set of states satisfying \phi
BDD get_SC_states_fair(BDD p, string name1, string name2, bdd_parameters *para, BDD fair_reach) {
  vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);

  //cout << "--------------- get_SC_states ---------------" << endl;
  BDD q = (fair_reach - p);
  if(options["verbosity"] > 1) {
    cout << "---- q ----" << endl;
    print_states(q, *para->v, para->bddmgr);
  }
  BDD tmp =  q * build_shared_equivalence(&shared, para);
  if(options["verbosity"] > 1) {
    cout << "---- tmp ----" << endl;
    print_states(tmp, *para->v, para->bddmgr);
  }
  BDD tmp1 = get_eq_states(&tmp, name1, name2, &shared, para) * fair_reach;  
  if(options["verbosity"] > 1) {
    cout << "---- tmp1 ----" << endl;
    print_states(tmp1, *para->v, para->bddmgr);
  }
  BDD result = fair_reach - tmp1;
  /*if(options["verbosity"] == 1) {
    cout << "---- result ----" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/
  return result;
}

// p is the set of states satisfying \phi
BDD get_Fu_states(BDD p, string name1, string name2, bdd_parameters *para) {
  vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);

  BDD tmp = get_SC_states(p, name1, name2, para);
  BDD tmp1 = get_eq_states(&tmp, name1, name2, &shared, para);  
  BDD result = tmp1 * build_shared_equivalence(&shared, para);
  /*if(options["verbosity"] == 1) {
    cout << "--------------- get_Fu_states ---------------" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/

  return result;
}

// p is the set of states satisfying \phi
BDD get_Fu_states_fair(BDD p, string name1, string name2, bdd_parameters *para, BDD fair_reach) {
  vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);

  BDD tmp = get_SC_states_fair(p, name1, name2, para, fair_reach);
  BDD tmp1 = get_eq_states(&tmp, name1, name2, &shared, para) * fair_reach;  
  BDD result = tmp1 * build_shared_equivalence(&shared, para);
  /*if(options["verbosity"] == 1) {
    cout << "--------------- get_Fu_states ---------------" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/

  return result;
}

//------------------------------------------------------------------------
void get_all_shared_vars(set<string> *allshared) {
	vector<basictype *> shared;
	for(unsigned int i=0; i<agents->size(); i++)
		for(unsigned int j=i+1; j<agents->size(); j++) {
			shared.clear();
			get_shared_vars((*agents)[i]->get_name(), (*agents)[j]->get_name(), &shared);
			for(unsigned int k=0; k<shared.size(); k=k+2) {
				allshared->insert(shared[k]->get_name());
			}
		}
}


BDD get_new_accessible_states(BDD *state, string name1, string name2, bdd_parameters *para) {
	vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);

	BDD tmp = (*state) * build_shared_equivalence(&shared, para);
	BDD tmp1 = get_eq_states(state, name1, name2, &shared, para);  

	BDD successors = *state;
	for (unsigned int i = 0; i < agents->size(); i++)
		successors *= (*para->vRT)[i];
  successors = Exists(para->bddmgr, para->v, successors);  
  successors = Exists(para->bddmgr, para->a, successors);
	successors = successors.SwapVariables(*para->v, *para->pv);

	BDD result = tmp * tmp1 * successors;
	return result;
}

BDD build_accessible_equivalence(string name1, string name2, vector<basictype *> *shared, bdd_parameters * para) {
  //cout << "--------------- build_accessible_equivalence ---------------" << endl;

  basic_agent *agent1 = (*is_agents)[name1];
  basic_agent *agent2 = (*is_agents)[name2];
	BDD eq = para->bddmgr->bddOne();

	//cout << "\\forall x\\in (Var_i\\cap Var_j): l_i^x(s) = l_j^x(s')" << endl;
  // each shared variable has a pair of definitions in shared
  for(unsigned int i=0; i<shared->size(); i=i+2) {
    BDD tmp = para->bddmgr->bddOne();
    // get the definition in ag1
    basictype *var1 = (*shared)[i];
    // get the definition in ag2
    basictype *var2 = (*shared)[i+1];
    // get the starting location of BDD variables for the definition in ag1
    int begin1 = var1->get_index_begin();
    // get the end location of BDD variables for the definition in ag1
    int end1 = var1->get_index_end();
    // get the starting location of BDD variables for the definition in ag2
    // the end location can be computed since the number of BDD variables 
    // is the same in both agents
    int begin2 = var2->get_index_begin();
    // compute the distance between two groups of BDD variables
    int delta = begin2 - begin1;

    for(int j=begin1; j<=end1; j++)
      // Build the equivalence relation between two definitions of the shared variable
      tmp = tmp * ( ( !(*para->v)[j] + (*para->pv)[j+delta] ) *
                    ( (*para->v)[j] + !(*para->pv)[j+delta] ) );

		// build the conjunction of each equivalence relation
    eq *= tmp;
  }

	//cout << "l_i(s) = l_i(s')" << endl;
	// obsvars
	for(int j=0; j<obsvars_bdd_length; j++)
		eq *= ( ( !(*para->v)[j] + (*para->pv)[j] ) *
						( (*para->v)[j] + !(*para->pv)[j] ) );

	// lobsvars
  map< string, variable * >*lobsvars = agent1->get_lobsvars();
	if (lobsvars != NULL && lobsvars->size() > 0) {
		map< string, basictype * >*envars = (*agents)[0]->get_vars();
    for (map< string, basictype * >::iterator i = envars->begin();
         i != envars->end(); i++) {
			if (lobsvars->find(i->first) != lobsvars->end()) {
				basictype *bt = i->second;
        for (int j = bt->get_index_begin(); j <= bt->get_index_end(); j++)
					eq *= ( ( !(*para->v)[j] + (*para->pv)[j] ) *
									( (*para->v)[j] + !(*para->pv)[j] ) );
			}
		}
	}

	// local vars
	//for(int j=agent1->get_var_index_begin(); j<=agent1->get_var_index_end(); j++)
	//	eq *= ( ( !(*para->v)[j] + (*para->pv)[j] ) *
	//					( (*para->v)[j] + !(*para->pv)[j] ) );
	vector< basictype *> *vars1 = agent1->get_vec_vars();
	for(unsigned int i=0; i<vars1->size(); i++) {
	  if(all_shared_var_names.find((*vars1)[i]->get_name()) == all_shared_var_names.end())
	    for (int j = (*vars1)[i]->get_index_begin(); j <= (*vars1)[i]->get_index_end(); j++)
	      eq *= ( ( !(*para->v)[j] + (*para->pv)[j] ) *
		      ( (*para->v)[j] + !(*para->pv)[j] ) );
	}

	//cout << "\\forall y\\in (Var_j - Var_i): l_j^y(s) = l_j^y(s')" << endl;
	// no need to deal with obsvars, which have been processed in the previous case
	/*lobsvars = agent2->get_lobsvars();
	if (lobsvars != NULL && lobsvars->size() > 0) {
		map< string, basictype * >*envars = (*agents)[0]->get_vars();
    for (map< string, basictype * >::iterator i = envars->begin();
         i != envars->end(); i++) {
			if (lobsvars->find(i->first) != lobsvars->end()) {
				basictype *bt = i->second;
        for (int j = bt->get_index_begin(); j <= bt->get_index_end(); j++)
					eq *= ( ( !(*para->v)[j] + (*para->pv)[j] ) *
									( (*para->v)[j] + !(*para->pv)[j] ) );
			}
		}
	}

	// local vars
	vector< basictype * > *vars2 = agent2->get_vec_vars();
	for(unsigned int i=0; i<vars2->size(); i++) {
		bool is_shared = false;
		for(unsigned int k=0; k<shared->size(); k=k+2)
			if((*shared)[k]->get_name().compare((*vars2)[i]->get_name()) == 0) {
				is_shared = true;
				break;
			}
		if(!is_shared) {
			for(int j = (*vars2)[i]->get_index_begin(); j <= (*vars2)[i]->get_index_end(); j++)
				eq *= ( ( !(*para->v)[j] + (*para->pv)[j] ) *
								( (*para->v)[j] + !(*para->pv)[j] ) );
		}
		}*/
	//cout << "all_shared_var_names: ";
	//for(set<string>::iterator it=all_shared_var_names.begin(); it!=all_shared_var_names.end(); it++)
	//  cout << *it << " ";
	//cout << endl;

	vector< basictype *> *vars2 = agent2->get_vec_vars();
	for(unsigned int i=0; i<vars2->size(); i++) {
	  //cout << "checkin variable " << (*vars2)[i]->get_name() << endl;
	  if(all_shared_var_names.find((*vars2)[i]->get_name()) != all_shared_var_names.end()) {
	    bool is_shared = false;
	    for(unsigned int j=0; j<shared->size(); j=j+2) {
	      if((*shared)[j]->get_name().compare((*vars2)[i]->get_name()) == 0) {
		is_shared = true;
		break;
	      }
	    }
	    if(!is_shared) {
	      //cout << "find an shared variable " << (*vars2)[i]->get_name() << endl;
	      for(int j = (*vars2)[i]->get_index_begin(); j <= (*vars2)[i]->get_index_end(); j++)
		eq *= ( ( !(*para->v)[j] + (*para->pv)[j] ) *
			( (*para->v)[j] + !(*para->pv)[j] ) );
	    }	
	  }
	}
	
  return eq;
}

BDD get_accessible_preimage(BDD X, BDD Z, bdd_parameters *para) {
  BDD predecessors = X.SwapVariables(*para->v, *para->pv);
  for (unsigned int i = 0; i < agents->size(); i++)
    predecessors *= (*para->vRT)[i];
  BDD preimage = Exists(para->bddmgr, para->a, predecessors); 
  
  preimage *= Z;
  preimage = Exists(para->bddmgr, para->pv, preimage); 
  return preimage;
}

BDD get_accessible_image(BDD X, BDD Z, bdd_parameters *para) {
  BDD successors = X;
  for (unsigned int i = 0; i < agents->size(); i++)
    successors *= (*para->vRT)[i];
  BDD image = Exists(para->bddmgr, para->a, successors); 
  
  image *= Z;
  image = Exists(para->bddmgr, para->v, image); 
  
  return image.SwapVariables(*para->v, *para->pv);
}

BDD get_accessible_image_new(BDD X, BDD Z, BDD a, bdd_parameters *para) {
  BDD successors = X;
  for (unsigned int i = 0; i < agents->size(); i++)
    successors *= (*para->vRT)[i];
	successors *= a;
  BDD image = Exists(para->bddmgr, para->a, successors); 
  
  image *= Z;
  image = Exists(para->bddmgr, para->v, image); 
  
  return image.SwapVariables(*para->v, *para->pv);
}

// p is the set of states satisfying \phi
// q is the set of states satisfying \varphi
BDD get_WCC_states(BDD p, BDD q, string name1, string name2, bdd_parameters *para) {	
  //cout << "--------------- get_WCC_states ---------------" << endl;
	vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);

	BDD X = p * (*para->reach - q);
	//cout << "X = " << endl;
	//print_states(X, *para->v, para->bddmgr);

	BDD Z = build_accessible_equivalence(name1, name2, &shared, para);

	BDD preimageX = get_accessible_preimage(X, Z, para) * (*para->reach);
	//cout << "preimageX = " << endl;
	//print_states(preimageX, *para->v, para->bddmgr);

  BDD result = *para->reach - preimageX;
  /*if(options["verbosity"] == 1) {
    cout << "---- result ----" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/
  //cout << "result: ";
  //result.print(para->v->count(), 1);
	//print_states(result, *para->v, para->bddmgr);
  return result;
}

// p is the set of states satisfying \phi
// q is the set of states satisfying \varphi
BDD get_SCC_states(BDD p, BDD q, string name1, string name2, bdd_parameters *para) {	
  //cout << "--------------- get_SCC_states ---------------" << endl;
	vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);

	BDD X = p;
	BDD Y = *para->reach - q;
	BDD Z = build_accessible_equivalence(name1, name2, &shared, para);

	BDD preimageX = get_accessible_preimage(X, Z, para);
	// A change in the latest version: replace Y by X * Y
	BDD preimageY = get_accessible_preimage(X * Y, Z, para);

  BDD result = *para->reach *(preimageX - preimageY);
  /*if(options["verbosity"] == 1) {
    cout << "---- result ----" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/
  //cout << "result: ";
  //result.print(para->v->count(), 1);
	//print_states(result, *para->v, para->bddmgr);
  return result;
}

// p is the set of states satisfying \phi
// q is the set of states satisfying \varphi
BDD get_FUW_states(BDD p, BDD q, string name1, string name2, bdd_parameters *para) {	
  //cout << "--------------- get_FUW_states ---------------" << endl;
	vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);

	BDD X = get_WCC_states(p, q, name1, name2, para);
	BDD Y = q * (*para->reach - X);
	BDD Z = build_accessible_equivalence(name1, name2, &shared, para);

	BDD result = Y * get_accessible_image(X, Z, para);

  /*if(options["verbosity"] == 1) {
    cout << "---- result ----" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/
	//cout << "result: ";
	//result.print(para->v->count(), 1);
	//print_states(result, *para->v, para->bddmgr);
  return result;
}

// p is the set of states satisfying \phi
// q is the set of states satisfying \varphi
BDD get_FUS_states(BDD p, BDD q, string name1, string name2, bdd_parameters *para) {	
  //cout << "--------------- get_FUS_states ---------------" << endl;
	vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);

	BDD X = get_SCC_states(p, q, name1, name2, para);
	BDD Y = p * (*para->reach - X);
	BDD Z = build_accessible_equivalence(name1, name2, &shared, para);

	BDD result = Y * get_accessible_image(X, Z, para);

  /*if(options["verbosity"] == 1) {
    cout << "---- result ----" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/
	//cout << "result: ";
	//result.print(para->v->count(), 1);
	//print_states(result, *para->v, para->bddmgr);
  return result;
}

BDD get_FUS_states_new(BDD p, BDD q, string name1, string name2, bdd_parameters *para) {	
  //cout << "--------------- get_FUS_states ---------------" << endl;
	vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);

	BDD X = get_SCC_states(p, q, name1, name2, para);
	BDD Y = p * (*para->reach - X);
	BDD Z = build_accessible_equivalence(name1, name2, &shared, para);

	string action_name = "Fulfill_" + name1;
  basic_agent *agent = (*is_agents)[name1];
	BDD a = agent->encode_action(para, action_name);

	BDD result = Y * get_accessible_image_new(X, Z, a, para);

  /*if(options["verbosity"] == 1) {
    cout << "---- result ----" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/
	//cout << "result: ";
	//result.print(para->v->count(), 1);
	//print_states(result, *para->v, para->bddmgr);
  return result;
}

BDD get_CAS_states_new(BDD p, BDD q, string name1, string name2, bdd_parameters *para) {	
  //cout << "--------------- get_FUS_states ---------------" << endl;
	vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);

	BDD X = get_SCC_states(p, q, name1, name2, para);
	BDD Y = (*para->reach - p) * (*para->reach - X);
	BDD Z = build_accessible_equivalence(name1, name2, &shared, para);

	string action_name = "Cancel_" + name1;
  basic_agent *agent = (*is_agents)[name1];
	BDD a = agent->encode_action(para, action_name);

	BDD result = Y * get_accessible_image_new(X, Z, a, para);

  /*if(options["verbosity"] == 1) {
    cout << "---- result ----" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/
	//cout << "result: ";
	//result.print(para->v->count(), 1);
	//print_states(result, *para->v, para->bddmgr);
  return result;
}

BDD get_RES_states_new(BDD p, BDD q, string name1, string name2, bdd_parameters *para) {	
  //cout << "--------------- get_FUS_states ---------------" << endl;
  vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);
  
  BDD X = get_SCC_states(p, q, name1, name2, para);
  BDD Y = (*para->reach - p) * (*para->reach - X);
  BDD Z = build_accessible_equivalence(name1, name2, &shared, para);

  string action_name = "Release_" + name2;
  basic_agent *agent = (*is_agents)[name2];
  BDD a = agent->encode_action(para, action_name);
	
  BDD result = Y * get_accessible_image_new(X, Z, a, para);

  /*if(options["verbosity"] == 1) {
    cout << "---- result ----" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/
	//cout << "result: ";
	//result.print(para->v->count(), 1);
	//print_states(result, *para->v, para->bddmgr);
  return result;
}

BDD get_DES_states_new(BDD p, BDD q, string name1, string name2, string name3,  bdd_parameters *para) {	
  //cout << "--------------- get_FUS_states ---------------" << endl;
  vector<basictype *> shared;
  vector<basictype *> shared1;
  get_shared_vars(name1, name2, &shared);
  get_shared_vars(name3, name2, &shared1);
  
  BDD W = get_SCC_states(p, q, name1, name2, para);
  BDD X = get_SCC_states(p, q, name3, name2, para);
  
  BDD Y = (*para->reach - p) * (*para->reach - W) * X;
  BDD Z = build_accessible_equivalence(name1, name2, &shared, para);
  
  string action_name = "Delegate_" + name1;
  basic_agent *agent = (*is_agents)[name1];
  BDD a = agent->encode_action(para, action_name);
  
  BDD result = Y * get_accessible_image_new(W, Z, a, para);
  
  /*if(options["verbosity"] == 1) {
    cout << "---- result ----" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/
	//cout << "result: ";
	//result.print(para->v->count(), 1);
	//print_states(result, *para->v, para->bddmgr);
  return result;
}

BDD get_ASS_states_new(BDD p, BDD q, string name1, string name2, string name3,  bdd_parameters *para) {	
  //cout << "--------------- get_ASS_states ---------------" << endl;
  vector<basictype *> shared;
  vector<basictype *> shared1;
  get_shared_vars(name1, name2, &shared);
  get_shared_vars(name1, name3, &shared1);
  
  BDD W = get_SCC_states(p, q, name1, name2, para);
  BDD X = get_SCC_states(p, q, name1, name3, para);
  
  BDD Y = (*para->reach - p) * (*para->reach - W) * X;
  BDD Z = build_accessible_equivalence(name1, name2, &shared, para);
  
  string action_name = "Assign_" + name2;
  basic_agent *agent = (*is_agents)[name2];
  BDD a = agent->encode_action(para, action_name);
  
  BDD result = Y * get_accessible_image_new(W, Z, a, para);
  
  /*if(options["verbosity"] == 1) {
    cout << "---- result ----" << endl;
    print_states(result, *para->v, para->bddmgr);
    }*/
	//cout << "result: ";
	//result.print(para->v->count(), 1);
	//print_states(result, *para->v, para->bddmgr);
  return result;
}

BDD get_all_preimage(BDD X, BDD Z, bdd_parameters *para) {
	
  BDD predecessors = X.SwapVariables(*para->v, *para->pv);
  for (unsigned int i = 0; i < agents->size(); i++)
    predecessors *= (*para->vRT)[i];
  BDD preimage = Exists(para->bddmgr, para->a, predecessors); 
  
  preimage -= Z;
  preimage = Exists(para->bddmgr, para->pv, preimage); 
  return preimage;
}

BDD get_Past(BDD p, BDD Z, bdd_parameters * para) 
{
  BDD reach = p * Z;
  BDD next1 = reach;
  int acounter1 = 1;
  while (true) {
    //if (options["verbosity"] > 0)
    //  cout << "    Computing depth " << acounter1 << endl;
    
		next1 = next1.SwapVariables(*para->v, *para->pv);
    for (unsigned int k = 0; k < agents->size(); k++)
      next1 *= (*para->vRT)[k];
    next1 = Exists(para->bddmgr, para->pv, next1);
		next1 = Exists(para->bddmgr, para->a, next1); // Clear actions.
    next1 = (next1 - reach) * Z;
    acounter1++;
    
    if (next1 == para->bddmgr->bddZero())
      break;
    else
      reach += next1;
  }
  return reach;
}

BDD get_TR_states_Aux(BDD W, BDD X, BDD X_reachable, BDD selfloop, basictype *shared_var, bdd_parameters *para) {	
  //cout << "--------------------------- get_TR_states_Aux ---------------------------" << endl;
	BDD Z = para->bddmgr->bddZero();
	int index_begin = shared_var->get_index_begin();
	//cout << "index_begin = " << index_begin << endl;
	BDD all = para->bddmgr->bddZero();

	if(shared_var->get_type() == 0) {
		for(int i=0; i<=1; i++) {
			BDD value = i==1 ? (*para->v)[index_begin] : ~(*para->v)[index_begin];
			BDD W_prime = W * value;

			BDD states = W_prime;
			while (states != para->bddmgr->bddZero()) {
				BDD Q = states.PickOneMinterm(*para->v);
				states -= Q;
				BDD V_prime = get_Past(Q, X_reachable, para) - Q;
				
				Z += V_prime * X * value;
			}
		} 
	} else if(shared_var->get_type() == 1) {
		rangedint *var = (rangedint *)shared_var;
		int lowerbound = var->get_lowerbound();
		int upperbound = var->get_upperbound();

		for(int i=lowerbound; i<=upperbound; i++) {
			BDD V = para->bddmgr->bddZero();
			vector< int >*vindex = var->get_value_index(i);			
			BDD value = var->build_individual_BDD(para->bddmgr, para->v, vindex, index_begin);
			BDD W_prime = W * value;

			BDD states = W_prime;
			while (states != para->bddmgr->bddZero()) {
				BDD Q = states.PickOneMinterm(*para->v);
				states -= Q;
				BDD V_prime = get_Past(Q, X_reachable, para) - Q;
				
				Z += V_prime * X * value;
			}
		} 
	} else {
		enumerate *var = (enumerate *)shared_var;
		set< string > *enum_values = var->get_enumvalue();

		for(set<string>::iterator i=enum_values->begin(); i!=enum_values->end(); i++) {
			//cout << "          enum_value = " << *i << endl;
			vector< bool >*vindex = var->get_value_index(*i);			
			BDD value = var->build_individual_BDD(para->bddmgr, para->v, vindex, index_begin);
			BDD W_prime = W * value;
			
			/*cout << "............... States W_prime: ..............." << endl;
			print_states(W_prime, *para->v, para->bddmgr);
			cout << "----------------------------------------" << endl;*/
			
			BDD states = W_prime;
			while (states != para->bddmgr->bddZero()) {
				BDD Q = states.PickOneMinterm(*para->v);
				
				/*cout << "............... State Q: ..............." << endl;
				print_states(Q, *para->v, para->bddmgr);
				cout << "----------------------------------------" << endl;*/
				
				states -= Q;
				BDD V_prime = get_Past(Q, X_reachable, para) - Q;
				
				/*cout << "............... States V_prime: ..............." << endl;
				print_states(V_prime, *para->v, para->bddmgr);
				cout << "----------------------------------------" << endl;*/
				
				Z += V_prime * X * value;
				
				/*cout << "............... States Z: ..............." << endl;
				print_states(Z, *para->v, para->bddmgr);
				cout << "----------------------------------------" << endl;*/
			}
		} 
	}

  //cout << "--------------------------- End of get_TR_states_Aux ---------------------------" << endl;
	return Z;
}

BDD get_TR_states_Aux2(BDD W1, BDD X, BDD X_reachable1, BDD selfloop, basictype *shared_var, bdd_parameters *para) {	
  //cout << "--------------------------- get_TR_states_Aux2 ---------------------------" << endl;
	BDD Z = para->bddmgr->bddZero();
	int index_begin = shared_var->get_index_begin();
	//cout << "index_begin = " << index_begin << endl;
	BDD W = W1;	
	BDD X_reachable = X_reachable1;	

	if(shared_var->get_type() == 0) {
		do {
			BDD V = para->bddmgr->bddZero();
			X_reachable -= W;

			for(int i=0; i<=1; i++) {
				BDD value = i==1 ? (*para->v)[index_begin] : ~(*para->v)[index_begin];
				BDD W_prime = W * value;
				BDD V_prime = get_all_preimage(W_prime, selfloop, para) * X_reachable;
				Z += V_prime * X * value;
				V += V_prime;
			} 
			W = V;
		} while(W * X_reachable != para->bddmgr->bddZero());
	} else if(shared_var->get_type() == 1) {
		rangedint *var = (rangedint *)shared_var;
		int lowerbound = var->get_lowerbound();
		int upperbound = var->get_upperbound();

		do {
			BDD V = para->bddmgr->bddZero();
			X_reachable -= W;

			for(int i=lowerbound; i<=upperbound; i++) {
				vector< int >*vindex = var->get_value_index(i);			
				BDD value = var->build_individual_BDD(para->bddmgr, para->v, vindex, index_begin);
				BDD W_prime = W * value;
				BDD V_prime = get_all_preimage(W_prime, selfloop, para) * X_reachable;
				Z += V_prime * X * value;
				V += V_prime;
			} 
			W = V;
		} while(W * X_reachable != para->bddmgr->bddZero());
	} else {
		enumerate *var = (enumerate *)shared_var;
		set< string > *enum_values = var->get_enumvalue();

		do {
			BDD V = para->bddmgr->bddZero();
			X_reachable -= W;

			for(set<string>::iterator i=enum_values->begin(); i!=enum_values->end(); i++) {
				//cout << "          enum_value = " << *i << endl;
				vector< bool >*vindex = var->get_value_index(*i);			
				BDD value = var->build_individual_BDD(para->bddmgr, para->v, vindex, index_begin);
				BDD W_prime = W * value;
			
				/*cout << "............... States W_prime: ..............." << endl;
					print_states(W_prime, *para->v, para->bddmgr);
					cout << "----------------------------------------" << endl;*/
			
				BDD V_prime = get_all_preimage(W_prime, selfloop, para) * X_reachable;
				
				/*cout << "............... States V_prime: ..............." << endl;
						print_states(V_prime, *para->v, para->bddmgr);
						cout << "----------------------------------------" << endl;*/
				
				Z += V_prime * X * value;
				
				/*cout << "............... States Z: ..............." << endl;
						print_states(Z, *para->v, para->bddmgr);
						cout << "----------------------------------------" << endl;*/
				V += V_prime;
			} 
			W = V;
		} while(W * X_reachable != para->bddmgr->bddZero());
	}

  //cout << "--------------------------- End of get_TR_states_Aux2 ---------------------------" << endl;
	return Z;
}

BDD get_TR_states_Aux1(BDD W, BDD X, BDD p, basictype *shared_var, bdd_parameters *para) {	
  //cout << "--------------------------- get_TR_states_Aux1 ---------------------------" << endl;
	BDD Z = para->bddmgr->bddZero();
	
  BDD tmp = para->bddmgr->bddOne(); // Always true
	for (int j = 0; j < shared_var->get_index_begin(); j++) 
		tmp *= (*para->v)[j];
	for (int j = shared_var->get_index_end()+1; j < para->v->count(); j++) 
		tmp *= (*para->v)[j];
	
	BDD X1 = X;
	while (X1 != para->bddmgr->bddZero()) {
		BDD Q = X1.PickOneMinterm(*para->v);
		X1 -= Q;

		/*cout << "............... States Q: ..............." << endl;
	print_states(Q, *para->v, para->bddmgr);
	cout << "----------------------------------------" << endl;*/

		BDD Q_reachable = get_Future(Q, para) - Q;

		/*cout << "............... States Q_reachable: ..............." << endl;
	print_states(Q_reachable, *para->v, para->bddmgr);
	cout << "----------------------------------------" << endl;*/

		BDD value = Q.ExistAbstract(tmp);
		Q_reachable *= value;

		/*cout << "............... States Q_reachable new: ..............." << endl;
	print_states(Q_reachable, *para->v, para->bddmgr);
	cout << "----------------------------------------" << endl;*/

		if(Q_reachable != para->bddmgr->bddZero() && Q_reachable * W == para->bddmgr->bddZero())
			Z += Q;
	}
	
  //cout << "--------------------------- End of get_TR_states_Aux1 ---------------------------" << endl;
	return Z;
}


// p is the set of states satisfying \psi
// q is the set of states satisfying \phi
BDD get_TR_states(BDD p, BDD q, string name1, string name2, bdd_parameters *para) {	
  //cout << "--------------- get_TR_states ---------------" << endl;
	BDD Z;
	vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);
	if (options["verbosity"] > 0) 
		cout << "name1 = " << name1 << ", name2 = " << name2 << endl;

	BDD Y = *para->reach - q;

	/*cout << "............... States Y: ..............." << endl;
	print_states(Y, *para->v, para->bddmgr);
	cout << "----------------------------------------" << endl;*/

	BDD X = p * Y;

	/*cout << "............... States X: ..............." << endl;
	print_states(X, *para->v, para->bddmgr);
	cout << "----------------------------------------" << endl;*/

	BDD X_reachable = get_Future(X, para);

	/*cout << "............... States X_reachable: ..............." << endl;
	print_states(X_reachable, *para->v, para->bddmgr);
	cout << "----------------------------------------" << endl;*/

	BDD W = Y * X_reachable;

	/*cout << "............... States W: ..............." << endl;
	print_states(W, *para->v, para->bddmgr);
	cout << "----------------------------------------" << endl;*/

	//if(W.CountMinterm(para->v->count()) < X.CountMinterm(para->v->count())) {
	if(options["trust"] == 2) {
		BDD selfloop = para->bddmgr->bddOne();
		for (int k = 0; k < para->v->count(); k++) 
			selfloop *=
				((!(*para->v)[k] + (*para->pv)[k]) * ((*para->v)[k] +	!(*para->pv)[k]));

		Z = get_TR_states_Aux2(W, X, X_reachable, selfloop, shared[0], para);
	
		/*cout << "............... States Z: ..............." << endl;
		print_states(Z, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;*/

		X -= Z;

		/*cout << "............... States X: ..............." << endl;
		print_states(X, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;*/

		W = q * X_reachable;

		/*cout << "............... States W: ..............." << endl;
			print_states(W, *para->v, para->bddmgr);*/

		Z = get_TR_states_Aux2(W, X, X_reachable, selfloop, shared[0], para);
	
		/*cout << "............... States Z: ..............." << endl;
		print_states(Z, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;*/
	} else 	if(options["trust"] == 1) {
		BDD selfloop = para->bddmgr->bddOne();
		for (int k = 0; k < para->v->count(); k++) 
			selfloop *=
				((!(*para->v)[k] + (*para->pv)[k]) * ((*para->v)[k] +	!(*para->pv)[k]));

		Z = get_TR_states_Aux(W, X, X_reachable, selfloop, shared[0], para);
	
		/*cout << "............... States Z: ..............." << endl;
		print_states(Z, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;*/

		X -= Z;

		/*cout << "............... States X: ..............." << endl;
		print_states(X, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;*/

		W = q * X_reachable;

		/*cout << "............... States W: ..............." << endl;
			print_states(W, *para->v, para->bddmgr);*/

		Z = get_TR_states_Aux(W, X, X_reachable, selfloop, shared[0], para);
	
		/*cout << "............... States Z: ..............." << endl;
		print_states(Z, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;*/
	} else {
		Z = get_TR_states_Aux1(W, X, p, shared[0], para);
	}
	if (options["verbosity"] > 0) {
		cout << "............... States Z: ..............." << endl;
		print_states(Z, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;
	}
	return Z;
}

BDD get_trust_states(BDD V, BDD s, basictype *shared_var, bdd_parameters *para) {	
  //cout << "--------------------------- get_trust_states ---------------------------" << endl;
	int index_begin = shared_var->get_index_begin();
  int index_end = shared_var->get_index_end();
	//cout << "shared_var = " << shared_var->get_name() << ": index_begin = " << index_begin << ", index_end = " << index_end << endl;
	BDD all;

  BDD tmp = para->bddmgr->bddOne(); // Always true
  for (int j = 0; j < index_begin; j++)
    tmp = tmp * (*para->v)[j];

  for (int j = index_end + 1; j < para->v->count(); j++)
    tmp = tmp * (*para->v)[j];

  //cout << "--------------------------- End of get_trust_states ---------------------------" << endl;
	return V * (s.ExistAbstract(tmp));
}

BDD get_TP_states(BDD p, BDD q, string name1, string name2, int op, int int_bound, bdd_parameters *para) {	
	if (options["verbosity"] > 1) 
		cout << "--------------- get_TP_states ---------------" << endl;
	BDD Z = para->bddmgr->bddZero();
	vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);
	if (options["verbosity"] > 1) 
		cout << "name1 = " << name1 << ", name2 = " << name2 << endl;

	BDD Y = *para->reach - q;

	if (options["verbosity"] > 1) {
		cout << "............... States Y: ..............." << endl;
		print_states(Y, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;
	}

	BDD X = p * Y;

	if (options["verbosity"] > 1) {
		cout << "............... States X: ..............." << endl;
		print_states(X, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;
	}

  BDD W = q;

	if (options["verbosity"] > 1) {
		cout << "............... States W: ..............." << endl;
		print_states(W, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;
	}

  double bound = int_bound/1000.0;

  while (X != para->bddmgr->bddZero()) {
    BDD x = X.PickOneMinterm(*para->v);
    X -= x;

  	BDD V = get_Future(x, para) - x;

		if (options["verbosity"] > 1) {
			cout << "............... States V: ..............." << endl;
			print_states(V, *para->v, para->bddmgr);
			cout << "----------------------------------------" << endl;
		}
    
  	BDD V_prime = get_trust_states(V, x, shared[0], para);

		if (options["verbosity"] > 1) {
			cout << "............... States V_prime: ..............." << endl;
			print_states(V_prime, *para->v, para->bddmgr);
			cout << "----------------------------------------" << endl;
		}
    
    if (V_prime != para->bddmgr->bddZero()) {
      BDD W_prime = V_prime * W;
      double r = W_prime.CountMinterm(para->v->count())/V_prime.CountMinterm(para->v->count());

      cout << "  r = " << r << ", op = " << op << ", bound = " << bound << endl;

      if ((op == 0 && r == bound) || 
          (op == 1 && r != bound) ||
          (op == 2 && r <  bound) ||
          (op == 3 && r <= bound) ||
          (op == 4 && r >  bound) ||
          (op == 5 && r >= bound))
				Z += x;
		}
	}

	if (options["verbosity"] > 0) {
		cout << "............... States Z: ..............." << endl;
		print_states(Z, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;
	}
	return Z;
}

BDD get_TC_states(BDD p, BDD q, string name1, string name2, int op, int int_bound, bdd_parameters *para) {	
	if (options["verbosity"] > 1) 
		cout << "--------------- get_TC_states ---------------" << endl;
	BDD Z = para->bddmgr->bddZero();
	vector<basictype *> shared;
  get_shared_vars(name1, name2, &shared);
	if (options["verbosity"] > 1) 
		cout << "name1 = " << name1 << ", name2 = " << name2 << endl;

	BDD Y = *para->reach - q;

	if (options["verbosity"] > 1) {
		cout << "............... States Y: ..............." << endl;
		print_states(Y, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;
	}

	BDD X = (*para->reach - p) + q;

	if (options["verbosity"] > 1) {
		cout << "............... States X: ..............." << endl;
		print_states(X, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;
	}


  BDD W = p;

	if (options["verbosity"] > 1) {
		cout << "............... States W: ..............." << endl;
		print_states(W, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;
	}

  double bound = int_bound/1000.0;

  while (Y != para->bddmgr->bddZero()) {
    BDD y = Y.PickOneMinterm(*para->v);
    Y -= y;

		if (options["verbosity"] > 1) {
			cout << "............... State y: ..............." << endl;
			print_states(y, *para->v, para->bddmgr);
			cout << "----------------------------------------" << endl;
		}
    
  	BDD V = get_Future(y, para) - y;

		if (options["verbosity"] > 1) {
			cout << "............... States V: ..............." << endl;
			print_states(V, *para->v, para->bddmgr);
			cout << "----------------------------------------" << endl;
		}
    
  	BDD V_prime = get_trust_states(V, y, shared[0], para);

		if (options["verbosity"] > 1) {
			cout << "............... States V_prime: ..............." << endl;
			print_states(V_prime, *para->v, para->bddmgr);
			cout << "----------------------------------------" << endl;
		}
    
    if (V_prime != para->bddmgr->bddZero() && (V_prime * W) != para->bddmgr->bddZero()) {
      BDD W_prime = V_prime * X;
      double r = W_prime.CountMinterm(para->v->count())/V_prime.CountMinterm(para->v->count());

      cout << "  r = " << r << ", op = " << op << ", bound = " << bound << endl;

      if ((op == 0 && r == bound) || 
          (op == 1 && r != bound) ||
          (op == 2 && r <  bound) ||
          (op == 3 && r <= bound) ||
          (op == 4 && r >  bound) ||
          (op == 5 && r >= bound))
				Z += y;
		}
	}

	if (options["verbosity"] > 0) {
		cout << "............... States Z: ..............." << endl;
		print_states(Z, *para->v, para->bddmgr);
		cout << "----------------------------------------" << endl;
	}
	return Z;
}

//------------------------------------------------------------------------
BDD
get_K_states(BDD aset1, BDD * state, string name, bdd_parameters * para)
{
  basic_agent *agent = (*is_agents)[name];
  BDD localstate = agent->project_local_state(state, para->bddmgr, para->v);
  return aset1 * localstate;
}

BDD
get_nK_states(BDD * state, string name, bdd_parameters * para)
{
  basic_agent *agent = (*is_agents)[name];
  BDD localstate = agent->project_local_state(state, para->bddmgr, para->v);
  return (*para->reach) * localstate;
}

BDD
get_nK_states_fair(BDD * state, string name, BDD fair_reach,
                   bdd_parameters * para)
{
  basic_agent *agent = (*is_agents)[name];
  BDD localstate = agent->project_local_state(state, para->bddmgr, para->v);
  return fair_reach * localstate;
}

BDD
get_GK_states(BDD aset1, BDD * state, string name, bdd_parameters * para)
{
  BDD tmpaset1 = para->bddmgr->bddZero();
  set < string > names_g = (*is_groups)[name];
  for (set < string >::iterator igs = names_g.begin(); igs != names_g.end();
       igs++) {
    basic_agent *agent = (*is_agents)[*igs];
    BDD localstate = agent->project_local_state(state, para->bddmgr, para->v);
    tmpaset1 = tmpaset1 + (aset1 * localstate);
  }
  return tmpaset1;
}

BDD
get_DK_states(BDD aset1, BDD * state, string name, bdd_parameters * para)
{
  BDD tmpaset1 = aset1;
  set < string > names_g = (*is_groups)[name];
  for (set < string >::iterator igs = names_g.begin(); igs != names_g.end();
       igs++) {
    basic_agent *agent = (*is_agents)[*igs];
    BDD localstate = agent->project_local_state(state, para->bddmgr, para->v);
    tmpaset1 = tmpaset1 * localstate;
  }
  return tmpaset1;
}

DdNode *
addApplyLT(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value < G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addLT(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyLT, n1, n2);
  ADD res(bddmgr, result);
  return res;
}

DdNode *
addApplyGT(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value > G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addGT(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyGT, n1, n2);
  ADD res(bddmgr, result);
  return res;
}

DdNode *
addApplyEQ(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value == G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addEQ(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyEQ, n1, n2);
  ADD res(bddmgr, result);
  return res;
}

DdNode *
addApplyGE(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value >= G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addGE(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyGE, n1, n2);
  ADD res(bddmgr, result);
  return res;
}

DdNode *
addApplyLE(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value <= G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addLE(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyLE, n1, n2);
  ADD res(bddmgr, result);
  return res;
}

DdNode *
addApplyNEQ(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value != G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addNEQ(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyNEQ, n1, n2);
  ADD res(bddmgr, result);
  return res;
}

int
search_string_table(string * s)
{
  for (unsigned int i = 0; i < string_table->size(); i++)
    if (s->compare(*(*string_table)[i]) == 0)
      return i;
  return -1;
}

int
search_variable_table(variable * v)
{
  for (unsigned int i = 0; i < variable_table->size(); i++)
    if (v->equal_to((*variable_table)[i]))
      return i;
  return -1;
}

int
search_logic_expression_table(bool_expression * le)
{
  for (unsigned int i = 0; i < logic_expression_table->size(); i++)
    if (le->equal_to((*logic_expression_table)[i]))
      return i;
  return -1;
}

int
search_logic_expression_table1(bool_expression * le)
{
  for (unsigned int i = 0; i < logic_expression_table1->size(); i++)
    if (le->equal_to((*logic_expression_table1)[i]))
      return i;
  return -1;
}
