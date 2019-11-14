#include "utilities.hh"
#include <sys/timeb.h>
#include <queue> 

using namespace std;

map<string, map<string, vector<BDD*>* >* >*
integer_variable_BDDs(Cudd * bddmgr, BDDvector * v)
{
  map<string, map<string, vector<BDD*>* >* >* int_vars = NULL;
  for (unsigned int j = 0; j < agents->size(); j++) {
    map<string, vector<BDD*>* >* int_var = NULL;
    map< string, basictype * >*obsvars = (*agents)[j]->get_obsvars();
    if (obsvars != NULL && obsvars->size() > 0)
      for (map< string, basictype * >::iterator i =
             obsvars->begin(); i != obsvars->end(); i++) {
        if ((*i).second->get_type() == 2) {
          rangedint *x = (rangedint *) (*i).second;
          unsigned int d = (unsigned int) (x->get_upperbound() - x->get_lowerbound() + 1);
          if(d & (d-1)) {
            vector<BDD*> *bddblocks = new vector<BDD*>();
            x->build_all_individual_BDDs(bddmgr, v, bddblocks, d);
            if(int_var == NULL)
              int_var = new map<string, vector<BDD*>* >();
            (*int_var)[i->first] = bddblocks;
          }
        }
      }
    map< string, basictype * >*vars = (*agents)[j]->get_vars();
    if (vars != NULL && vars->size() > 0)
      for (map< string, basictype * >::iterator i = vars->begin();
           i != vars->end(); i++) {
        if ((*i).second->get_type() == 2) {
          rangedint *x = (rangedint *) (*i).second;
          unsigned int d = (unsigned int) (x->get_upperbound() - x->get_lowerbound() + 1);
          if(d & (d-1)) {
            vector<BDD*> *bddblocks = new vector<BDD*>();
            x->build_all_individual_BDDs(bddmgr, v, bddblocks, d);
            if(int_var == NULL)
              int_var = new map<string, vector<BDD*>* >();
            (*int_var)[i->first] = bddblocks;
          }
        }
      }
    if(int_var != NULL) {
      if(int_vars == NULL)
        int_vars = new map<string, map<string, vector<BDD*>* >* >();
      (*int_vars)[(*agents)[j]->get_name()] = int_var;
    }
  }
  return int_vars;
}

void
clear_integer_BDDs(map<string, map<string, vector<BDD*>* >* >* int_vars)
{
  if(int_vars != NULL) {
    for (map<string, map<string, vector<BDD*>* >* >::iterator iter =
           int_vars->begin(); iter != int_vars->end(); iter++) {
      map<string, vector<BDD*>* >* int_var = iter->second;
      for (map<string, vector<BDD*>* >::iterator iter1 =
             int_var->begin(); iter1 != int_var->end(); iter1++) {
        vector<BDD*>* bddblocks = iter1->second;
        for(unsigned int i=0; i<bddblocks->size(); i++)
          delete (*bddblocks)[i];
        delete bddblocks;
      }
      delete int_var;
    }
    delete int_vars;
  }
}

BDD
complete_integer_BDDs(Cudd * bddmgr, BDDvector * v, BDD a, map<string, map<string, vector<BDD*>* >* >* int_vars)
{
  if(int_vars != NULL) {
    BDD b = a;
    for (map<string, map<string, vector<BDD*>* >* >::iterator iter =
           int_vars->begin(); iter != int_vars->end(); iter++) {
      map<string, vector<BDD*>* >* int_var = iter->second;
      basic_agent *agent = (*is_agents)[iter->first];
      map< string, basictype * >*obsvars = agent->get_obsvars();
      map< string, basictype * >*vars = agent->get_vars();
     
      for (map<string, vector<BDD*>* >::iterator iter1 =
             int_var->begin(); iter1 != int_var->end(); iter1++) {
        vector<BDD*>* bddblocks = iter1->second;
        rangedint *x = NULL;
        if(obsvars != NULL) {
          map< string, basictype * >::iterator p = obsvars->find(iter1->first);
          if( p != obsvars->end()) 
            x = (rangedint *)p->second;
        }
        if(x == NULL && vars != NULL) {
          map< string, basictype * >::iterator p = vars->find(iter1->first);
          if( p != vars->end()) 
            x = (rangedint *)p->second;
        }
        int index_begin = x->get_index_begin();
        int index_end = x->get_index_end();
        BDD tmp = bddmgr->bddOne();
        for (int j = index_begin; j <= index_end; j++)
          tmp = tmp * (*v)[j];
        for(unsigned int i=0; i<bddblocks->size(); i++) {
          if(b * (*(*bddblocks)[i]) != bddmgr->bddZero()) {
            b = b.ExistAbstract(tmp);
            b = b * (*(*bddblocks)[i]); 
            break;
          }
        }
      }
    }
    return b;
  } else
    return a;
}

int
export_model(bdd_parameters * para, BDD *is, vector< vector< int >*> *countex, map< int, BDD * > *idbdd, vector< vector< transition * >*> *cextr)
{
  int scount = 0;
  map<string, map<string, vector<BDD*>* >* >* int_vars = integer_variable_BDDs(para->bddmgr, para->v);
  queue<BDD> queue1;
  queue<BDD> queue2;
  while ((*is) != para->bddmgr->bddZero()) {
    BDD curinitstate = is->PickOneMinterm(*para->v);
    curinitstate = complete_integer_BDDs(para->bddmgr, para->v, curinitstate, int_vars);
    *is = *is - curinitstate;
    queue1.push(curinitstate);
    (*idbdd)[scount++] = new BDD(curinitstate);
    if(options["debug"] == 1)
      cout << "idbdd[" << scount-1 << "] in queue1" << endl;
  }

  int index = 0;
  do {
    while(!queue1.empty()) {
      BDD state = queue1.front();
      queue1.pop();

      vector<int> desc;
      vector< transition * > desctr;
      desc.push_back(index);

      BDD next1 = state;
      for (unsigned int k = 0; k < agents->size(); k++)
        next1 *= (*para->vRT)[k];

      BDD successors = Exists(para->bddmgr, para->v, next1);
      successors = Exists(para->bddmgr, para->a, successors);
      successors = successors.SwapVariables(*para->v, *para->pv);

      while(successors != para->bddmgr->bddZero()) {
        BDD succ = successors.PickOneMinterm(*para->v);
        succ = complete_integer_BDDs(para->bddmgr, para->v, succ, int_vars);
        successors = successors - succ;
              
        int k = 0;
        for(k=0; k<scount; k++) {
          if(succ == *(*idbdd)[k])
            break;
        }
        if(k == scount) {
          (*idbdd)[scount++] = new BDD(succ);
          queue2.push(succ);
          if(options["debug"] == 1)
            cout << "  idbdd[" << scount-1 << "] in queue2" << endl;
        }
        desc.push_back(k);
        BDD actions = succ.SwapVariables(*para->v, *para->pv);
        actions *= next1;
        actions = Exists(para->bddmgr, para->v, actions);
        actions = Exists(para->bddmgr, para->pv, actions);
        while(actions != para->bddmgr->bddZero()) {
          BDD action = actions.PickOneMinterm(*para->a);
          actions = actions - action;
          desctr.push_back(new transition(&state, index, &succ, k, &action));
          if(options["debug"] == 1)
            cout << " transition: " << index << " -> " << k << endl;
        }
      }
      countex->push_back(new vector< int >(desc));
      cextr->push_back(new vector< transition * >(desctr));
      index++;
    }
    swap(queue1, queue2);
  } while(!queue1.empty());

  clear_integer_BDDs(int_vars);

  return scount;
}

void
print_cex(bdd_parameters * para, string fname, string str_head,  map< int, BDD * > *idbdd, vector< vector< transition * >*> *cextr)
{
  // Writing full witness/counterexample to text file
  //sprintf(buff, "formula%1d.dot", i + 1);
  string filename = fname + ".dot";
  //sprintf(buff, "formula%1d.info", i + 1);
  string filename2 = fname + ".info";
  ofstream myfile(filename.c_str());
  ofstream myfile2(filename2.c_str());
  set< string > trans_set;
      
  if (myfile.is_open() && myfile2.is_open()) {
    myfile << "digraph " << str_head << " {\n";
        
    // print states and their description
    for (map< int, BDD * >::iterator iter =
           idbdd->begin(); iter != idbdd->end(); iter++) {
      myfile << " " << iter->first << " [label=\"" <<
        iter->first << "\",shape=ellipse]" << endl;
      myfile2 << "-- State " << iter->first << " --" << endl;
      myfile2 << state_to_str(*iter->second, *para->v) << endl;
    }
        
    // printing transitions
    for (int ac = 0; ac < (int) cextr->size(); ac++) {
      for (int j = 0; j < (int) cextr->at(ac)->size(); j++) {
        string strTran = cextr->at(ac)->at(j)->index_to_string(para->a);
        if (trans_set.find(strTran) == trans_set.end()) {
          cextr->at(ac)->at(j)->to_str(&myfile, para->a);
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
