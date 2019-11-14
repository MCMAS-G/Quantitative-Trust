#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

basictype::basictype(string * n)
{
  name = n;
  type = 1;
  index_begin = -1;
  index_end = -1;
}

basictype::basictype(string * n, unsigned char t)
{
  name = n;
  type = t;
  index_begin = -1;
  index_end = -1;
}

basictype::~basictype()
{
  delete name;
}

string
basictype::get_name()
{
  if (name == NULL) {
    cout << "type name is unknown" << endl;
    exit(1);
  }
  return *name;
}

unsigned char
basictype::get_type()
{
  return type;
}

string
basictype::to_string()
{
  return *name + ": boolean";
}

int
basictype::BDD_length()
{
  return 1;
}

void
basictype::set_index_begin(int i)
{
  index_begin = i;
  char buff[4];
  sprintf(buff, "%1d", i);
  string str(buff);
  name_index = "_" + *name + "_" + str;
}

void
basictype::set_index_end(int i)
{
  index_end = i;
}

int
basictype::get_index_begin()
{
  return index_begin;
}

int
basictype::get_index_end()
{
  return index_end;
}

void
basictype::print_value_index()
{
  cout << "true: 1" << endl;
  cout << "false: 0" << endl;
}

void
basictype::print_state(string prefix, BDD state, BDDvector v)
{
  cout << prefix << *name << " = ";
  if (state <= v[index_begin])
    cout << "true";
  else
    cout << "false";
}

void
basictype::print_stateXML(ofstream * myfile, BDD state, BDDvector v)
{
  *myfile << "        <variable name=\"" << *name << "\">";
  if (state <= v[index_begin])
    *myfile << "true";
  else
    *myfile << "false";
  *myfile << "</variable>\n";
}

string
basictype::state_to_str(BDD state, BDDvector v)
{
  ostringstream s;
  s << *name << "=";
  if (state <= v[index_begin])
    s << "true";
  else
    s << "false";
  return s.str();
}

bool
basictype::is_valid_state(BDD state, BDDvector v)
{
  return true;
}

ADD
basictype::build_ADD_tree(Cudd * bddmgr, ADDvector * addv, map< string,
                          ADD > *ADD_cache)
{
  if (ADD_cache->find(name_index) != ADD_cache->end())
    return ((*ADD_cache)[name_index]);
  int index_begin = get_index_begin();
  ADD add_tree =
    ((*addv)[index_begin] * bddmgr->constant(1)) +
    (~(*addv)[index_begin] * bddmgr->constant(0));
  (*ADD_cache)[name_index] = add_tree;
  return add_tree;
}

BDD
basictype::build_all_BDDs(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddOne();
}

enumerate::enumerate(string * n, set< string > *s):basictype(n, 3)
{
  enumvalue = s;
  value_index = new map< string, vector< bool > *>;
  bdd_length = enumvalue == NULL ? 0 : log_2((int) enumvalue->size());
  set_value_index();
}

enumerate::~enumerate()
{
  delete enumvalue;
}

set< string > *enumerate::get_enumvalue()
{
  return enumvalue;
}

int
enumerate::is_valid_value(string s)
{
  if (enumvalue == NULL) {
    cout << "enum list is unknown" << endl;
    exit(1);
  }
  return (enumvalue->find(s) != enumvalue->end());
}

string
enumerate::to_string()
{
  string str = ": { ";
  int k = 0;
  int j = (int) enumvalue->size() - 1;
  for (set< string >::iterator i = enumvalue->begin(); i != enumvalue->end();
       i++) {
    if (k == j)
      str += *i + " ";
    else
      str += *i + ", ";
    k++;
  }
  str += "}";
  return get_name() + str;
}

int
enumerate::BDD_length()
{
  return bdd_length;
}

void
enumerate::set_value_index()
{
  int size = BDD_length();
  vector< bool > base(size, false);
  for (set< string >::iterator i = enumvalue->begin(); i != enumvalue->end();
       i++) {
    vector< bool > *temp = new vector< bool > (base);
    pair < string, vector< bool > *>p(*i, temp);
    value_index->insert(p);
    for (int j = size - 1; j >= 0; j--) {
      if (base[j])
        base[j] = false;
      else {
        base[j] = true;
        break;
      }
    }
  }
}

void
enumerate::print_value_index()
{
  for (map< string, vector< bool > *>::iterator i = value_index->begin();
       i != value_index->end(); i++) {
    cout << i->first << ": ";
    for (unsigned int j = 0; j < i->second->size(); j++)
      cout << ((*(i->second))[j] ? 1 : 0);
    cout << endl;
  }
}

vector< bool > *enumerate::get_value_index(string value)
{
  if (value_index != NULL) {
    map< string, vector< bool > *>::iterator i = value_index->find(value);
    if (i != value_index->end())
      return i->second;
  }
  return NULL;
}

string
enumerate::find_value_by_index(vector< bool > index)
{
  for (map< string, vector< bool > *>::iterator i = value_index->begin();
       i != value_index->end(); i++) {
    bool flag = true;
    for (unsigned int j = 0; j < i->second->size(); j++)
      if ((*(i->second))[j] != index[j]) {
        flag = false;
        break;
      }
    if (flag)
      return i->first;
  }
  return "";
}

void
enumerate::print_state(string prefix, BDD state, BDDvector v)
{
  int index_begin = get_index_begin();
  int index_end = get_index_end();
  cout << prefix << get_name() << " = ";
  cout.flush();
  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  string value = find_value_by_index(index);
  cout << value;
}

void
enumerate::print_stateXML(ofstream * myfile, BDD state, BDDvector v)
{
  int index_begin = get_index_begin();
  int index_end = get_index_end();
  *myfile << "        <variable name=\"" << get_name() << "\">";

  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  string value = find_value_by_index(index);
  *myfile << value;
  *myfile << "</variable>\n";
}

string
enumerate::state_to_str(BDD state, BDDvector v)
{
  ostringstream s;
  int index_begin = get_index_begin();
  int index_end = get_index_end();
  s << get_name() << "=";

  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  string value = find_value_by_index(index);
  s << value;
  return s.str();
}

bool
enumerate::is_valid_state(BDD state, BDDvector v)
{
  int index_begin = get_index_begin();
  int index_end = get_index_end();
  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  string value = find_value_by_index(index);
  if (value == "")
    return false;
  else
    return true;
}

ADD
enumerate::build_ADD_tree(Cudd * bddmgr, ADDvector * addv, map< string,
                          ADD > *ADD_cache)
{
  if (ADD_cache->find(name_index) != ADD_cache->end())
    return ((*ADD_cache)[name_index]);
  int index_begin = get_index_begin();
  int index = 1;
  ADD add_tree = bddmgr->addZero();
  for (set< string >::iterator i = enumvalue->begin(); i != enumvalue->end();
       i++) {
    vector< bool > *v = get_value_index(*i);
    ADD path = bddmgr->constant(index);
    index++;
    for (unsigned int j = 0; j < v->size(); j++)
      if ((*v)[j])
        path *= (*addv)[index_begin + j];
      else
        path *= ~(*addv)[index_begin + j];
    add_tree += path;
  }
  (*ADD_cache)[name_index] = add_tree;
  return add_tree;
}

BDD 
enumerate::build_individual_BDD(Cudd * bddmgr, BDDvector *v, 
																vector< bool > *vindex, int index_begin)
{
	BDD path = bddmgr->bddOne();
	for (unsigned int j = 0; j < vindex->size(); j++)
		if ((*vindex)[j])
			path *= (*v)[index_begin + j];
		else 
			path *= ~(*v)[index_begin + j];

	return path;
}

BDD
enumerate::build_all_BDDs(Cudd * bddmgr, BDDvector * v)
{
  unsigned int length = 1;
  length <<= bdd_length;
  if (enumvalue->size() < length) {
    int index_begin = get_index_begin();
    BDD bdd_tree = bddmgr->bddZero();
    int index = 1;
    for (set< string >::iterator i = enumvalue->begin();
         i != enumvalue->end(); i++) {
      vector< bool > *vindex = get_value_index(*i);
      BDD path = bddmgr->bddOne();
      index++;
      for (unsigned int j = 0; j < vindex->size(); j++)
        if ((*vindex)[j])
          path *= (*v)[index_begin + j];
        else
          path *= ~(*v)[index_begin + j];
      bdd_tree += path;
    }
    return bdd_tree;
  } else
    return bddmgr->bddOne();
}

rangedint::rangedint(string * n, int l, int u):basictype(n, 2)
{
  lowerbound = l;
  upperbound = u;
  bdd_length = log_2(upperbound - lowerbound + 1);
  power_two = 1;
  power_two = power_two << bdd_length;
  half_power = 1;
  half_power = half_power << (bdd_length - 1);
  half_power += lowerbound;
}

rangedint::~rangedint()
{
}

int
rangedint::get_lowerbound()
{
  return lowerbound;
}

int
rangedint::get_upperbound()
{
  return upperbound;
}

bool
rangedint::is_valid_value(int i)
{
  return (i <= upperbound && i >= lowerbound);
}

string
rangedint::to_string()
{
  ostringstream o, p;
  o << lowerbound;
  p << upperbound;
  return get_name() + ": " + o.str() + " .. " + p.str();
}

int
rangedint::BDD_length()
{
  return bdd_length;
}

void
rangedint::print_value_index()
{
  for (int k = lowerbound; k <= upperbound; k++) {
    cout << k << ": ";
    vector< int >*v = get_value_index(k);
    for (unsigned int j = 0; j < v->size(); j++)
      cout << ((*v)[j] == 1 ? "1" : ((*v)[j] == -1 ? "0" : "_"));
    cout << endl;
  }
}

vector< int >*
rangedint::get_value_index(int value)
{
  if (value >= lowerbound && value <= upperbound) {
    vector< int >*temp = new vector< int >(bdd_length, -1);
    if (power_two + lowerbound == upperbound + 1) {
      int distance = value - lowerbound;
      for (int i = bdd_length - 1; i >= 0; i--) {
        if ((distance & 1) == 1)
          (*temp)[i] = 1;
        distance >>= 1;
      }
    } else {
      int index = value - half_power;
      if (index < 0) {
        int distance = value - lowerbound;
        for (int i = bdd_length - 2; i >= 0; i--) {
          if ((distance & 1) == 1)
            (*temp)[i] = 1;
          distance >>= 1;
        }
        if (value - lowerbound > upperbound - half_power)
          (*temp)[bdd_length - 1] = 0;
      } else {
        int distance = index;
        for (int i = bdd_length - 2; i >= 0; i--) {
          if ((distance & 1) == 1)
            (*temp)[i] = 1;
          distance >>= 1;
        }
        (*temp)[bdd_length - 1] = 1;
      }
    }
    return temp;
  }
  return NULL;
}

int
rangedint::find_value_by_index(vector< bool > index)
{
  int value = 0;
  if (power_two + lowerbound == upperbound + 1) {
    for (unsigned int i = 0; i < index.size(); i++) {
      value <<= 1;
      value += (index[i] == true ? 1 : 0);
    }
    return value + lowerbound;
  } else {
    for (unsigned int i = 0; i < index.size() - 1; i++) {
      value <<= 1;
      value += (index[i] == true ? 1 : 0);
    }
    if (value > upperbound - half_power || index[bdd_length - 1] == false)
      return value + lowerbound;
    else
      return value + half_power;
  }
}

void
rangedint::print_state(string prefix, BDD state, BDDvector v)
{
  int index_begin = get_index_begin();
  int index_end = get_index_end();
  cout << prefix << get_name() << " = ";
  cout.flush();
  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  int value = find_value_by_index(index);
  cout << value;
}

void
rangedint::print_stateXML(ofstream * myfile, BDD state, BDDvector v)
{
  int index_begin = get_index_begin();
  int index_end = get_index_end();

  *myfile << "        <variable name=\"" << get_name() << "\">";

  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  int value = find_value_by_index(index);
  *myfile << value;
  *myfile << "</variable>\n";

}

string
rangedint::state_to_str(BDD state, BDDvector v)
{
  ostringstream s;
  int index_begin = get_index_begin();
  int index_end = get_index_end();

  s << get_name() << "=";

  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  int value = find_value_by_index(index);
  s << value;
  return s.str();
}

bool
rangedint::is_valid_state(BDD state, BDDvector v)
{
  int index_begin = get_index_begin();
  int index_end = get_index_end();
  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  int value = find_value_by_index(index);
  if (value > upperbound)
    return false;
  else
    return true;
}

ADD
rangedint::build_ADD_tree(Cudd * bddmgr, ADDvector * addv, map< string,
                          ADD > *ADD_cache)
{
  if (ADD_cache->find(name_index) != ADD_cache->end())
    return ((*ADD_cache)[name_index]);
  int index_begin = get_index_begin();
  ADD add_tree = bddmgr->addZero();
  for (int i = lowerbound; i <= upperbound; i++) {
    vector< int >*v = get_value_index(i);
    ADD path = bddmgr->constant(i);
    for (unsigned int j = 0; j < v->size(); j++)
      if ((*v)[j] == 1)
        path *= (*addv)[index_begin + j];
      else if ((*v)[j] == -1)
        path *= ~(*addv)[index_begin + j];
    add_tree += path;
  }
  (*ADD_cache)[name_index] = add_tree;
  return add_tree;
}

BDD
rangedint::build_all_BDDs(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddOne();
}

BDD 
rangedint::build_individual_BDD(Cudd * bddmgr, BDDvector *v, 
																vector< int > *vindex, int index_begin)
{
	BDD path = bddmgr->bddOne();
	for (unsigned int j = 0; j < vindex->size(); j++)
		if ((*vindex)[j] == 1)
			path *= (*v)[index_begin + j];
		else if ((*vindex)[j] == -1)
			path *= ~(*v)[index_begin + j];

	return path;
}

void
rangedint::build_all_individual_BDDs(Cudd * bddmgr, BDDvector *v, vector< BDD* > *bddblocks, unsigned int count) {
  int index_begin = get_index_begin();
  unsigned int length = upperbound - lowerbound + 1;
  if(length > count) {
    unsigned int portion = (unsigned int)(length/count);
    unsigned int reminder = length%count;
    int it = lowerbound;
    for(unsigned int i=0; i<reminder; i++) {
      BDD bdd_tree = bddmgr->bddZero();
      for(unsigned int k=0; k<=portion; k++) {
        vector< int > *vindex = get_value_index(it++);
        bdd_tree += build_individual_BDD(bddmgr, v, vindex, index_begin);
      }
      bddblocks->push_back(new BDD(bdd_tree));
    }
    for(unsigned int i=reminder; i<count; i++) {
      BDD bdd_tree = bddmgr->bddZero();
      for(unsigned int k=0; k<portion; k++) {
        vector< int > *vindex = get_value_index(it++);
        bdd_tree += build_individual_BDD(bddmgr, v, vindex, index_begin);
      }
      bddblocks->push_back(new BDD(bdd_tree));
    }           
  } else {
    for (int i = lowerbound; i <= upperbound; i++) {
      vector< int >*vindex = get_value_index(i);
      bddblocks->push_back(new BDD(build_individual_BDD(bddmgr, v, vindex, index_begin)));
    }
  }
}

Object::~Object()
{
}

string
Object::to_string()
{
  return "";
}

expression::expression(unsigned char i)
{
  type = i;
}

expression::~expression()
{
}

unsigned char
expression::get_type()
{
  return type;
}

string
expression::to_string()
{
  return "";
}

ADD
expression::build_ADD_tree(Cudd * bddmgr, ADDvector * addv, map< string,
                           ADD > *ADD_cache)
{
  return bddmgr->addZero();
}

bool
expression::equal_to(expression * expr)
{
  return type == expr->get_type();
}

BDD
expression::encode_BDD_true(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddZero();
}

BDD
expression::encode_BDD_false(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddZero();
}

variable::variable(string * a_n, string * n):expression(0)
{
  agent_name = a_n;
  name = n;
  var_type = NULL;
}

variable::variable(string * n):expression(0)
{
  agent_name = NULL;
  name = n;
  var_type = NULL;
}

variable::variable(string * a_n, string * n, basictype * v_t):expression(0)
{
  agent_name = a_n;
  name = n;
  var_type = v_t;
}

variable::~variable()
{
}

bool
variable::equal_to(variable * expr)
{
  if (agent_name == NULL && expr->is_agent_name_null())
    return (name->compare(expr->get_variable_name())) == 0;
  else if (agent_name != NULL && !expr->is_agent_name_null())
    return ((name->compare(expr->get_variable_name())) == 0) &&
      ((agent_name->compare(expr->get_agent_name())) == 0);
  return false;
}

bool
variable::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((variable *) expr);
  return false;
}

void
variable::set_agent_name(string * a_n)
{
  agent_name = a_n;
}

string
variable::get_agent_name()
{
  if (agent_name == NULL) {
    cout << "error: the agent name of the given variable is undefined!" <<
      endl;
    exit(1);
  } else
    return *agent_name;
}

string *
variable::get_variable_name_point()
{
  return name;
}

bool
variable::is_agent_name_null()
{
  return agent_name == NULL;
}

string
variable::get_variable_name()
{
  if (name == NULL) {
    cout << "error: the name of the given variable is undefined!" << endl;
    exit(1);
  } else
    return *name;
}

string
variable::to_string()
{
  return (agent_name == NULL ? "" : *agent_name + ".") + get_variable_name();
}

void
variable::set_var_type(basictype * t)
{
  if (var_type == NULL)
    var_type = t;
}

basictype *
variable::get_var_type()
{
  return var_type;
}

ADD
variable::build_ADD_tree(Cudd * bddmgr, ADDvector * addv, map< string,
                         ADD > *ADD_cache)
{
  if (var_type == NULL) {
    if (options["quiet"] == 0)
      cout << "Warning: var_type in " << to_string() << " is NULL" << endl;
    return bddmgr->addZero();
  }
  if (var_type->get_type() == 2)
    return ((rangedint *) var_type)->build_ADD_tree(bddmgr, addv, ADD_cache);
  else
    return bddmgr->addZero();
}

BDD
variable::encode_BDD_true(Cudd * bddmgr, BDDvector * v)
{
  if (var_type->get_type() == 1) {
    int begin = ((rangedint *) var_type)->get_index_begin();
    return (*v)[begin];
  }
  return bddmgr->bddZero();
}

BDD
variable::encode_BDD_false(Cudd * bddmgr, BDDvector * v)
{
  if (var_type->get_type() == 1) {
    int begin = ((rangedint *) var_type)->get_index_begin();
    return !(*v)[begin];
  }
  return bddmgr->bddZero();
}

laction::laction():expression(4)
{
  agent_name = NULL;
  agent = NULL;
}

laction::laction(string * a_n):expression(4)
{
  agent_name = a_n;
  agent = NULL;
}

laction::laction(string * a_n, basic_agent * ag):expression(4)
{
  agent_name = a_n;
  agent = ag;
}

laction::~laction()
{
}

bool
laction::equal_to(laction * expr)
{
  if (agent_name == NULL && expr->is_agent_name_null())
    return true;
  if (agent_name != NULL && !expr->is_agent_name_null())
    return agent_name->compare(expr->get_agent_name()) == 0;
  return false;
}

bool
laction::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((laction *) expr);
  return false;
}

void
laction::set_agent_name(string * a_n)
{
  agent_name = a_n;
}

string
laction::get_agent_name()
{
  if (agent_name == NULL) {
    cout << "agent name in laction is unknown!" << endl;
    exit(1);
  } else
    return *agent_name;
}

void
laction::set_agent(basic_agent * a)
{
  if (agent == NULL)
    agent = a;
}

basic_agent *
laction::get_agent()
{
  return agent;
}

bool
laction::is_agent_name_null()
{
  return agent_name == NULL;
}

string
laction::to_string()
{
  return (agent_name == NULL ? "" : *agent_name + ".") + "Action";
}

ADD
laction::build_ADD_tree(Cudd * bddmgr, ADDvector * addv, map< string,
                        ADD > *ADD_cache)
{
  return bddmgr->addZero();
}

BDD
laction::encode_BDD_true(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddZero();
}

BDD
laction::encode_BDD_false(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddZero();
}

bool_value::bool_value(bool v):expression(1)
{
  value = v;
}

bool_value::~bool_value()
{
}

bool
bool_value::equal_to(bool_value * expr)
{
  return value == expr->get_value();
}

bool
bool_value::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((bool_value *) expr);
  return false;
}

bool
bool_value::get_value()
{
  return value;
}

string
bool_value::to_string()
{
  return (value ? "true" : "false");
}

ADD
bool_value::build_ADD_tree(Cudd * bddmgr, ADDvector * addv, map< string,
                           ADD > *ADD_cache)
{
  if (value)
    return bddmgr->addOne();
  else
    return bddmgr->addZero();
}

BDD
bool_value::encode_BDD_true(Cudd * bddmgr, BDDvector * v)
{
  if (value)
    return bddmgr->bddOne();
  else
    return bddmgr->bddZero();
}

BDD
bool_value::encode_BDD_false(Cudd * bddmgr, BDDvector * v)
{
  if (value)
    return bddmgr->bddZero();
  else
    return bddmgr->bddOne();
}

int_value::int_value(int v):expression(2)
{
  value = v;
}

int_value::~int_value()
{
}

bool
int_value::equal_to(int_value * expr)
{
  return value == expr->get_value();
}

bool
int_value::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((int_value *) expr);
  return false;
}

int
int_value::get_value()
{
  return value;
}

string
int_value::to_string()
{
  ostringstream o;
  o << value;
  return o.str();
}

ADD
int_value::build_ADD_tree(Cudd * bddmgr, ADDvector * addv, map< string,
                          ADD > *ADD_cache)
{
  return bddmgr->constant(value);
}

BDD
int_value::encode_BDD_true(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddZero();
}

BDD
int_value::encode_BDD_false(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddZero();
}

enum_value::enum_value(string * v):expression(3)
{
  value = v;
}

enum_value::~enum_value()
{
}

bool
enum_value::equal_to(enum_value * expr)
{
  return value->compare(expr->get_value()) == 0;
}

bool
enum_value::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((enum_value *) expr);
  return false;
}

string
enum_value::get_value()
{
  if (value == NULL) {
    cout << "enum value is unknown!" << endl;
    exit(1);
  } else
    return *value;
}

string
enum_value::to_string()
{
  return get_value();
}

ADD
enum_value::build_ADD_tree(Cudd * bddmgr, ADDvector * addv, map< string,
                           ADD > *ADD_cache)
{
  return bddmgr->addZero();
}

BDD
enum_value::encode_BDD_true(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddZero();
}

BDD
enum_value::encode_BDD_false(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddZero();
}

/**********************************************
 arithmetic_expression
**********************************************/
arithmetic_expression::arithmetic_expression(unsigned char o, expression * e1, expression * e2):expression(o)
{
  operands[0] = e1;
  operands[1] = e2;
}

arithmetic_expression::~arithmetic_expression()
{
}

expression *
arithmetic_expression::get_operand(unsigned char i)
{
  if (i > 1) {
    cout << "error: arithmetic operand " << i << " does not exist!" << endl;
    exit(1);
  } else if (operands[i] == NULL) {
    cout << "error: arithmetic operand " << i << " is undefined!" << endl;
    exit(1);
  } else
    return (operands[i]);
}

bool
arithmetic_expression::equal_to(arithmetic_expression * expr)
{
  unsigned int op = get_type();
  if (op == expr->get_type())
    return ((expression *) (operands[0]))->equal_to(expr->get_operand(0)) &&
      ((expression *) (operands[1]))->equal_to(expr->get_operand(1));

  return false;
}

bool
arithmetic_expression::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((arithmetic_expression *) expr);
  return false;
}

string
arithmetic_expression::to_string()
{
  string opstr;
  unsigned int op = get_type();
  if (op == 0)
    return ((expression *) (operands[0]))->to_string();
  else if (op == 5)
    opstr = "+";
  else if (op == 6)
    opstr = "-";
  else if (op == 7)
    opstr = "*";
  else if (op == 8)
    opstr = "/";
  return ((expression *) (operands[0]))->to_string() + " " + opstr + " " +
    ((expression *) (operands[1]))->to_string();
}

bool
arithmetic_expression::check_var_and_value(map< string,
                                           basictype * >*obsvars,
                                           map< string, basictype * >*vars)
{
  bool flag = true;
  unsigned char left = operands[0]->get_type(); // left hand side
  unsigned char right = operands[1]->get_type();  // right hand side
  if (left == 0) {    // left hand side is a variable
    variable *var = (variable *) operands[0];
    string vs = var->get_variable_name();
    if (var->is_agent_name_null()) {
      map< string, basictype * >::iterator p = vars->find(vs);
      if (p == vars->end()) {
        cout << "        variable " << vs << " is not defined." << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    } else if (var->get_agent_name() == "Environment") {
      map< string, basictype * >::iterator p = obsvars->find(vs);
      if (p == obsvars->end()) {
        cout << "        variable " << vs << " is not defined." << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    } else {
      cout << "        variable " << vs << " is not defined." << endl;
      flag = false;
    }
  } else if (left >= 5 && left <= 8) {  //lhs is an arithmetic expression
    flag =
      ((arithmetic_expression *) operands[0])->check_var_and_value(obsvars,
                                                                   vars);
  } else if (left != 2) { // lhs is not an integer
    cout << "        left hand side in" << to_string() << " has a wrong type."
         << endl;
    flag = false;
  }

  if (right == 0) {   // right hand side is a variable
    variable *var = (variable *) operands[1];
    string vs = var->get_variable_name();
    if (var->is_agent_name_null()) {
      map< string, basictype * >::iterator p = vars->find(vs);
      if (p == vars->end()) {
        cout << "        variable " << vs << " is not defined." << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    } else if (var->get_agent_name() == "Environment") {
      map< string, basictype * >::iterator p = obsvars->find(vs);
      if (p == obsvars->end()) {
        cout << "        variable " << vs << " is not defined." << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    } else {
      cout << "        variable " << vs << " is not defined." << endl;
      flag = false;
    }
  } else if (right >= 5 && right <= 8) {  //lhs is an arithmetic expression
    flag =
      ((arithmetic_expression *) operands[1])->check_var_and_value(obsvars,
                                                                   vars)
      && flag;
  } else if (right != 2) {  // lhs is not an integer
    cout << "        right hand side in" << to_string() <<
      " has a wrong type." << endl;
    flag = false;
  }
  return flag;
}

bool
arithmetic_expression::check_var_and_value(map< string, map< string,
                                           basictype * > >*vars)
{
  bool flag = true;
  unsigned char left = operands[0]->get_type(); // left hand side
  unsigned char right = operands[1]->get_type();  // right hand side
  if (left == 0) {    // left hand side is a variable
    variable *var = (variable *) operands[0];
    string vs = var->get_variable_name();
    if (var->is_agent_name_null()) {
      cout << "        variable " << vs << " must be accompanied by agent" <<
        endl;
      flag = false;
    } else {
      string ag_name = var->get_agent_name();
      map< string, map< string, basictype * > >::iterator gp =
        vars->find(ag_name);
      if (gp == vars->end()) {
        cout << "    undefined agent " << ag_name << endl;
        return false;
      }
      map< string, basictype * >::iterator p = gp->second.find(vs);
      if (p == gp->second.end()) {
        cout << "        variable " << vs << " is not defined in agent " <<
          ag_name << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    }
  } else if (left >= 5 && left <= 8) {  //lhs is an arithmetic expression
    flag = ((arithmetic_expression *) operands[0])->check_var_and_value(vars);
  } else if (left != 2) { // lhs is not an integer
    cout << "        left hand side in" << to_string() << " has a wrong type."
         << endl;
    flag = false;
  }

  if (right == 0) {   // right hand side is a variable
    variable *var1 = (variable *) operands[1];
    string vs1 = var1->get_variable_name();
    if (var1->is_agent_name_null()) {
      cout << "        variable " << vs1 << " must be accompanied by agent" <<
        endl;
      flag = false;
    } else {
      string ag_name = var1->get_agent_name();
      map< string, map< string, basictype * > >::iterator gp =
        vars->find(ag_name);
      if (gp == vars->end()) {
        cout << "    undefined agent " << ag_name << endl;
        return false;
      }
      map< string, basictype * >::iterator p = gp->second.find(vs1);
      if (p == gp->second.end()) {
        cout << "        variable " << vs1 << " is not defined in agent " <<
          ag_name << endl;
        flag = false;
      } else
        var1->set_var_type(p->second);
    }
  } else if (right >= 5 && right <= 8) {  //lhs is an arithmetic expression
    flag = ((arithmetic_expression *) operands[1])->check_var_and_value(vars)
      && flag;
  } else if (right != 2) {  // lhs is not an integer
    cout << "        right hand side in" << to_string() <<
      " has a wrong type." << endl;
    flag = false;
  }
  return flag;
}

ADD
arithmetic_expression::build_ADD_tree(Cudd * bddmgr, ADDvector * addv,
                                      map< string, ADD > *ADD_cache)
{
  unsigned char op = get_type();
  ADD res;
  ADD lhs = operands[0]->build_ADD_tree(bddmgr, addv, ADD_cache);
  ADD rhs = operands[1]->build_ADD_tree(bddmgr, addv, ADD_cache);
  if (op == 5) {    // plus
    res = lhs + rhs;
  } else if (op == 6) {   // minus
    res = lhs - rhs;
  } else if (op == 7) {   // times
    res = lhs * rhs;
  } else {      // divide
    res = lhs.Divide(rhs);
  }
  return res;
}

BDD
arithmetic_expression::encode_BDD_true(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddZero();
}

BDD
arithmetic_expression::encode_BDD_false(Cudd * bddmgr, BDDvector * v)
{
  return bddmgr->bddZero();
}

/**********************************************
 * bit_expression
 * Don't be confused with bool_expression
 **********************************************/
bit_expression::bit_expression(unsigned char o, expression * e1, expression * e2):expression(o)
{
  operands[0] = e1;
  operands[1] = e2;
}

bit_expression::~bit_expression()
{
}

expression *
bit_expression::get_operand(unsigned char i)
{
  if (i > 1) {
    cout << "error: boolean operand " << i << " does not exist!" << endl;
    exit(1);
  } else if (operands[i] == NULL) {
    cout << "error: boolean operand " << i << " is undefined!" << endl;
    exit(1);
  } else
    return (operands[i]);
}

bool
bit_expression::equal_to(bit_expression * expr)
{
  unsigned int op = get_type();
  if (op == expr->get_type())
    return ((expression *) (operands[0]))->equal_to(expr->get_operand(0)) &&
      ((expression *) (operands[1]))->equal_to(expr->get_operand(1));

  return false;
}

bool
bit_expression::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((bit_expression *) expr);
  return false;
}

string
bit_expression::to_string()
{
  string opstr;
  unsigned int op = get_type();
  if (op == 0)
    return ((expression *) (operands[0]))->to_string();
  else if (op == 9)
    opstr = "&";
  else if (op == 10)
    opstr = "|";
  else if (op == 11)
    opstr = "~";
  else if (op == 12)
    opstr = "^";
  else
    return NULL;
  if (op == 11)
    return opstr + " " + ((expression *) (operands[0]))->to_string();
  else
    return ((expression *) (operands[0]))->to_string() + " " + opstr + " " +
      ((expression *) (operands[1]))->to_string();
}

bool
bit_expression::check_var_and_value(map< string, basictype * >*obsvars,
                                    map< string, basictype * >*vars)
{
  bool flag = true;
  unsigned char left = operands[0]->get_type(); // left hand side
  if (left == 0) {    // left hand side is a variable
    variable *var = (variable *) operands[0];
    string vs = var->get_variable_name();
    if (var->is_agent_name_null()) {
      map< string, basictype * >::iterator p = vars->find(vs);
      if (p == vars->end()) {
        cout << "        variable " << vs << " is not defined." << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    } else if (var->get_agent_name() == "Environment") {
      map< string, basictype * >::iterator p = obsvars->find(vs);
      if (p == obsvars->end()) {
        cout << "        variable " << vs << " is not defined." << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    } else {
      cout << "        variable " << vs << " is not defined." << endl;
      flag = false;
    }
  } else if (left >= 9 && left <= 12) { //lhs is a boolean expression
    flag =
      ((bit_expression *) operands[0])->check_var_and_value(obsvars, vars);
  } else if (left != 1) { // lhs is not a bool value
    cout << "        left hand side in" << to_string() << " has a wrong type."
         << endl;
    flag = false;
  }

  if(get_type() != 11) {
    unsigned char right = operands[1]->get_type();  // right hand side
    if (right == 0) {   // right hand side is a variable
      variable *var = (variable *) operands[1];
      string vs = var->get_variable_name();
      if (var->is_agent_name_null()) {
        map< string, basictype * >::iterator p = vars->find(vs);
        if (p == vars->end()) {
          cout << "        variable " << vs << " is not defined." << endl;
          flag = false;
        } else
          var->set_var_type(p->second);
      } else if (var->get_agent_name() == "Environment") {
        map< string, basictype * >::iterator p = obsvars->find(vs);
        if (p == obsvars->end()) {
          cout << "        variable " << vs << " is not defined." << endl;
          flag = false;
        } else
          var->set_var_type(p->second);
      } else {
        cout << "        variable " << vs << " is not defined." << endl;
        flag = false;
      }
    } else if (right >= 9 && right <= 12) { //lhs is a boolean expression
      flag =
        ((bit_expression *) operands[1])->check_var_and_value(obsvars, vars)
        && flag;
    } else if (right != 1) {  // lhs is not a bool value
      cout << "        right hand side in" << to_string() <<
        " has a wrong type." << endl;
      flag = false;
    }
  }
  return flag;
}

bool
bit_expression::check_var_and_value(map< string, map< string,
                                    basictype * > >*vars)
{
  bool flag = true;
  unsigned char left = operands[0]->get_type(); // left hand side
  unsigned char right = operands[1]->get_type();  // right hand side
  if (left == 0) {    // left hand side is a variable
    variable *var = (variable *) operands[0];
    string vs = var->get_variable_name();
    if (var->is_agent_name_null()) {
      cout << "        variable " << vs << " must be accompanied by agent" <<
        endl;
      flag = false;
    } else {
      string ag_name = var->get_agent_name();
      map< string, map< string, basictype * > >::iterator gp =
        vars->find(ag_name);
      if (gp == vars->end()) {
        cout << "    undefined agent " << ag_name << endl;
        return false;
      }
      map< string, basictype * >::iterator p = gp->second.find(vs);
      if (p == gp->second.end()) {
        cout << "        variable " << vs << " is not defined in agent " <<
          ag_name << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    }
  } else if (left >= 9 && left <= 12) { //lhs is a bit expression
    flag = ((bit_expression *) operands[0])->check_var_and_value(vars);
  } else if (left != 1) { // lhs is not a bool value
    cout << "        left hand side in" << to_string() << " has a wrong type."
         << endl;
    flag = false;
  }

  if (right == 0) {   // right hand side is a variable
    variable *var1 = (variable *) operands[1];
    string vs1 = var1->get_variable_name();
    if (var1->is_agent_name_null()) {
      cout << "        variable " << vs1 << " must be accompanied by agent" <<
        endl;
      flag = false;
    } else {
      string ag_name = var1->get_agent_name();
      map< string, map< string, basictype * > >::iterator gp =
        vars->find(ag_name);
      if (gp == vars->end()) {
        cout << "    undefined agent " << ag_name << endl;
        return false;
      }
      map< string, basictype * >::iterator p = gp->second.find(vs1);
      if (p == gp->second.end()) {
        cout << "        variable " << vs1 << " is not defined in agent " <<
          ag_name << endl;
        flag = false;
      } else
        var1->set_var_type(p->second);
    }
  } else if (right >= 9 && right <= 12) { //lhs is a boolean expression
    flag = ((bit_expression *) operands[1])->check_var_and_value(vars)
      && flag;
  } else if (right != 1) {  // lhs is not a bool value
    cout << "        right hand side in" << to_string() <<
      " has a wrong type." << endl;
    flag = false;
  }
  return flag;
}

ADD
bit_expression::build_ADD_tree(Cudd * bddmgr, ADDvector * addv, map< string,
                               ADD > *ADD_cache)
{
  unsigned char op = get_type();
  ADD res;
  ADD lhs = operands[0]->build_ADD_tree(bddmgr, addv, ADD_cache);
  ADD rhs = operands[1]->build_ADD_tree(bddmgr, addv, ADD_cache);
  if (op == 9) {    // and "&"
    res = lhs & rhs;
  } else if (op == 10) {  // or "|"
    res = lhs | rhs;
  } else if (op == 11) {  // not "~"
    res = ~lhs;
  } else {      // xor "^"
    res = ~(lhs & rhs) & (lhs | rhs);
  }
  return res;
}

BDD
bit_expression::encode_BDD_true(Cudd * bddmgr, BDDvector * v)
{
  unsigned char op = get_type();
  BDD res;

  if (op == 9) {    // and "&"
    BDD lhs = operands[0]->encode_BDD_true(bddmgr, v);
    BDD rhs = operands[1]->encode_BDD_true(bddmgr, v);
    res = lhs * rhs;
  } else if (op == 10) {  // or "|"
    BDD lhs = operands[0]->encode_BDD_true(bddmgr, v);
    BDD rhs = operands[1]->encode_BDD_true(bddmgr, v);
    res = lhs | rhs;
  } else if (op == 11) {  // not "~"
    BDD lhs = operands[0]->encode_BDD_false(bddmgr, v);
    res = lhs;
  } else {      // xor "^"
    BDD lhs1 = operands[0]->encode_BDD_true(bddmgr, v);
    BDD rhs1 = operands[1]->encode_BDD_true(bddmgr, v);
    BDD lhs2 = operands[0]->encode_BDD_false(bddmgr, v);
    BDD rhs2 = operands[1]->encode_BDD_false(bddmgr, v);
    res = (lhs1 & rhs2) | (lhs2 | rhs1);
  }
  return res;
}

BDD
bit_expression::encode_BDD_false(Cudd * bddmgr, BDDvector * v)
{
  unsigned char op = get_type();
  BDD res;

  if (op == 9) {    // and "&"
    BDD lhs = operands[0]->encode_BDD_false(bddmgr, v);
    BDD rhs = operands[1]->encode_BDD_false(bddmgr, v);
    res = lhs | rhs;
  } else if (op == 10) {  // or "|"
    BDD lhs = operands[0]->encode_BDD_false(bddmgr, v);
    BDD rhs = operands[1]->encode_BDD_false(bddmgr, v);
    res = lhs & rhs;
  } else if (op == 11) {  // not "~"
    BDD lhs = operands[0]->encode_BDD_true(bddmgr, v);
    res = lhs;
  } else {      // xor "^"
    BDD lhs1 = operands[0]->encode_BDD_true(bddmgr, v);
    BDD rhs1 = operands[1]->encode_BDD_true(bddmgr, v);
    BDD lhs2 = operands[0]->encode_BDD_false(bddmgr, v);
    BDD rhs2 = operands[1]->encode_BDD_false(bddmgr, v);
    res = (lhs1 & rhs1) | (lhs2 | rhs2);
  }
  return res;
}

/**********************************************
 logic_expression
**********************************************/
logic_expression::logic_expression(unsigned char o, expression * e1,
                                   expression * e2)
{
  op = o;
  operands[0] = e1;
  operands[1] = e2;
}

logic_expression::~logic_expression()
{
}

unsigned char
logic_expression::get_op()
{
  return op;
}

expression *
logic_expression::get_operand(unsigned char i)
{
  if (i > 1) {
    cout << "error: logic operand " << i << " does not exist!" << endl;
    exit(1);
  } else if (operands[i] == NULL) {
    cout << "error: logic operand " << i << " is undefined!" << endl;
    exit(1);
  } else
    return (operands[i]);
}

bool
logic_expression::equal_to(logic_expression * expr)
{
  if (op == expr->get_op())
    return ((expression *) (operands[0]))->equal_to(expr->get_operand(0)) &&
      ((expression *) (operands[1]))->equal_to(expr->get_operand(1));

  return false;
}

string
logic_expression::to_string()
{
  string opstr;
  if (op == 0)
    opstr = "=";
  else if (op == 1)
    opstr = "<>";
  else if (op == 2)
    opstr = "<";
  else if (op == 3)
    opstr = "<=";
  else if (op == 4)
    opstr = ">";
  else if (op == 5)
    opstr = ">=";
  return ((expression *) (operands[0]))->to_string() + opstr +
    ((expression *) (operands[1]))->to_string();
}

bool
logic_expression::check_evolution(map< string, basictype * >*obsvars,
                                  map< string, basictype * >*vars,
                                  string agent_name, map< string,
                                  basic_agent * >*global_actions)
{
  unsigned char left = operands[0]->get_type(); // left hand side
  unsigned char right = operands[1]->get_type();  // right hand side
  bool left_var = true;
  bool right_var = true;

  if (left == 4) {
    map< string, basic_agent * >::iterator p;
    string act_name = ((variable *) operands[1])->get_variable_name();
    bool f = ((laction *) operands[0])->is_agent_name_null();
    string ag_name =
      f ? agent_name : ((laction *) operands[0])->get_agent_name();

    p = global_actions->find(ag_name);
    if (p == global_actions->end()) {
      cout << "        action " << act_name << " is not found in agent " <<
        ag_name << endl;
      return false;
    }

    if (f) {
      ((laction *) operands[0])->set_agent_name(new string(agent_name));
      ((laction *) operands[0])->set_agent((*p).second);
    } else
      ((laction *) operands[0])->set_agent((*p).second);

    set< string > *acts = (*p).second->get_actions();
    set< string >::iterator s = acts->find(act_name);
    if (s == acts->end()) {
      cout << "        action " << act_name << " is not found in agent " <<
        ag_name << endl;
      return false;
    } else
      return true;
  } else if (left == 0) { // left hand side is a variable, or an enumerate value 
    variable *v1 = ((variable *) operands[0]);
    string vs = v1->get_variable_name();
    map< string, basictype * >::iterator p;
    if (v1->is_agent_name_null()) { // local variable
      p = vars->find(vs);
      if (p == vars->end())
        left_var = false;
    } else {
      p = obsvars->find(vs);
      if (p == obsvars->end())
        left_var = false;
    }
    if (right == 0) {   // right hand side could be a variable or a enumerate value
      variable *v2 = ((variable *) operands[1]);
      string vs1 = v2->get_variable_name();
      map< string, basictype * >::iterator p1;
      if (v2->is_agent_name_null()) { // local variable
        p1 = vars->find(vs1);
        if (p1 == vars->end())
          right_var = false;
      } else {
        p1 = obsvars->find(vs1);
        if (p1 == obsvars->end())
          right_var = false;
      }
      if (left_var && right_var) {  // both sides are variables
        //check if both sides have the same type.
        unsigned char t1 = p->second->get_type(); //lhs' type
        unsigned char t2 = p1->second->get_type();  //rhs' type
        if (t1 == t2) {   // same type
          if (t1 == 3) {  // enumerate type
            if (op != 0 && op != 1) {
              cout <<
                "        only '=' and '<>' are allowed for enumeration variables."
                   << endl;
              return false;
            }
            set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
            set< string > *s2 =
              ((enumerate *) (p1->second))->get_enumvalue();
            if (options["subset"] == 0) {
              if (s1->size() == s2->size()) { // same size
                bool equal = true;
                for (set< string >::iterator i = s1->begin(); i != s1->end();
                     i++)
                  if (s2->find(*i) == s2->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs << " and " << vs1 <<
                    " do not have the same enumerate type." << endl;
                  return false;
                }
              } else {
                cout << "        " << vs << " and " << vs1 <<
                  " do not have the same enumerate type." << endl;
                return false;
              }
            } else {
              bool equal = true;
              if (s1->size() < s2->size()) {  // same size
                for (set< string >::iterator i = s1->begin(); i != s1->end();
                     i++)
                  if (s2->find(*i) == s2->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs << " is not a subset of " << vs1 <<
                    "." << endl;
                  return false;
                }
              } else {
                for (set< string >::iterator i = s2->begin(); i != s2->end();
                     i++)
                  if (s1->find(*i) == s1->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs1 << " is not a subset of " << vs <<
                    "." << endl;
                  return false;
                }
              }
            }
          } else {
            if (t1 == 1 && op != 0 && op != 1) {
              cout <<
                "        only '=' and '<>' are allowed for boolean variables."
                   << endl;
              return false;
            }
            ((variable *) operands[0])->set_var_type(p->second);
            ((variable *) operands[1])->set_var_type(p1->second);
            return true;
          }
        } else {
          cout << "        " << vs << " and " << vs1 <<
            " have different type." << endl;
          return false;
        }
      } else if (left_var && !right_var) {  // lhs is a variable and rhs is an enumerate value
        if (op != 0 && op != 1) {
          cout <<
            "        only '=' and '<>' are allowed for enumeration variables."
               << endl;
          return false;
        }
        unsigned char t1 = p->second->get_type(); //lhs' type
        if (t1 == 3) {    // lhs must be enumerate
          set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
          if (s1->find(vs1) != s1->end()) { //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[0])->set_var_type(p->second);
            //change the rhs to be an enumerate value
            operands[1] = new enum_value(new string(vs1));
            return true;
          } else {
            cout << "        " << vs << " does not have the value " << vs1 <<
              endl;
            return false;
          }
        } else {
          cout << "        " << vs << " must have an enumerate type." << endl;
          return false;
        }
      } else if (!left_var && right_var) {  // lhs is an enumerate value and rhs is a variable
        if (op != 0 && op != 1) {
          cout <<
            "        only '=' and '<>' are allowed for enumeration variables."
               << endl;
          return false;
        }
        unsigned char t2 = p1->second->get_type();  //rhs' type
        if (t2 == 3) {    // rhs must be enumerate
          set< string > *s2 = ((enumerate *) (p1->second))->get_enumvalue();
          if (s2->find(vs) != s2->end()) {  //find a matched value in the enumerate type
            // add a link in rhs to its type
            ((variable *) operands[1])->set_var_type(p1->second);
            //change the lhs to be an enumerate value
            operands[0] = new enum_value(new string(vs));
            return true;
          } else {
            cout << "        " << vs1 << " does not have the value " << vs <<
              endl;
            return false;
          }
        } else {
          cout << "        " << vs1 << " must have an enumerate type." <<
            endl;
          return false;
        }
      } else {
        cout << "        " << vs << " or " << vs1 << " must be a variable." <<
          endl;
        return false;
      }
    } else if (left_var) {
      left = p->second->get_type();
      if (right == 1) {   // right hand side is a boolean value
        if (left != 1) {
          cout << "         " << vs << " in " << to_string() <<
            " is not a Boolean variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          // add a link in variable to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (right == 2) {  // right hand side is an integer
        if (left != 2) {
          cout << "         " << vs << " in " << to_string() <<
            " is not a bounded integer variable." << endl;
          return false;
        }
        int vs1 = ((int_value *) operands[1])->get_value();
        if (((rangedint *) (p->second))->is_valid_value(vs1)) { // the value is in the correct range
          // add a link in variable to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs1 << " is out of bound in " << to_string()
               << "." << endl;
          return false;
        }
      } else if (right == 3) {  // right hand side is an enumerate value. It cannot happen. But we still check it.
        cout << "        enumerate value cannot appear here." << endl;
        if (left != 3) {
          cout << "         " << vs << " in " << to_string() <<
            " is not an enumeration variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          string vs1 = ((enum_value *) operands[1])->get_value();
          set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
          if (s1->find(vs1) != s1->end()) { //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[0])->set_var_type(p->second);
            return true;
          } else {
            cout << "        " << vs << " does not have the value " << vs1 <<
              endl;
            return false;
          }
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (right >= 5 && right <= 8) {  // right hand side is an arithmetic expression
        if (left == 2 &&
            ((arithmetic_expression *) operands[1])->
            check_var_and_value(obsvars, vars)) {
          // add a link in lhs to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs << "does not have integer type or " <<
            ((arithmetic_expression *) operands[1])->to_string() <<
            " is not a correct arithmetic expression." << endl;
          return false;
        }
      } else {      // right hand side is a bit expression
        if (op > 1) {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
        if (left == 1 &&
            ((bit_expression *) operands[1])->check_var_and_value(obsvars,
                                                                  vars)) {
          // add a link in lhs to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs << "does not have boolean type or " <<
            ((bit_expression *) operands[1])->to_string() <<
            " is not a correct bit expression." << endl;
          return false;
        }
      }
    } else {
      cout << "        " << vs << " must be a variable." << endl;
      return false;
    }
  } else if (right == 0) {  // right hand side is a variable 
    variable *v2 = ((variable *) operands[1]);
    string vs1 = ((variable *) operands[1])->get_variable_name();
    map< string, basictype * >::iterator p1;
    if (v2->is_agent_name_null()) { // local variable
      p1 = vars->find(vs1);
      if (p1 == vars->end())
        right_var = false;
    } else {
      p1 = obsvars->find(vs1);
      if (p1 == obsvars->end())
        right_var = false;
    }
    if (right_var) {
      right = p1->second->get_type();
      if (left == 1) {    // left hand side is a boolean value
        if (right != 1) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not a Boolean variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          // add a link in variable to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (left == 2) { // left hand side is an integer
        if (right != 2) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not a bounded integer variable." << endl;
          return false;
        }
        int vs = ((int_value *) operands[0])->get_value();
        if (((rangedint *) (p1->second))->is_valid_value(vs)) { // the value is in the correct range
          // add a link in variable to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs << " is out of bound in " << to_string() <<
            "." << endl;
          return false;
        }
      } else if (left == 3) { // left hand side is an enumerate value. It cannot happen. But we still check it.
        if (right != 3) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not an enumeration  variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          string vs = ((enum_value *) operands[0])->get_value();
          set< string > *s2 = ((enumerate *) (p1->second))->get_enumvalue();
          if (s2->find(vs) != s2->end()) {  //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[1])->set_var_type(p1->second);
            return true;
          } else {
            cout << "        " << vs1 << " does not have the value " << vs <<
              endl;
            return false;
          }
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (left >= 5 && left <= 8) {  // left hand side is an arithmetic expression
        if (right == 2 &&
            ((arithmetic_expression *) operands[0])->
            check_var_and_value(obsvars, vars)) {
          // add a link in lhs to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs1 << "does not have integer type or " <<
            ((arithmetic_expression *) operands[0])->to_string() <<
            " is not a correct arithmetic expression." << endl;
          return false;
        }
      } else {      // left hand side is a bit expression
        if (op > 1) {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
        if (right == 1 &&
            ((bit_expression *) operands[0])->check_var_and_value(obsvars,
                                                                  vars)) {
          // add a link in lhs to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs1 << "does not have boolean type or " <<
            ((bit_expression *) operands[0])->to_string() <<
            " is not a correct bit expression." << endl;
          return false;
        }
      }
    } else {
      cout << "        " << vs1 << " must be a variable." << endl;
      return false;
    }
  } else if (left >= 5 && left <= 8) {  // left hand side is an arithmetic expression
    if (right == 2)   // rhs is an integer
      return ((arithmetic_expression *) operands[0])->
        check_var_and_value(obsvars, vars);
    else if (right >= 5 && right <= 8)  // rhs is an arithmetic expression
      return ((arithmetic_expression *) operands[0])->
        check_var_and_value(obsvars, vars)
        && ((arithmetic_expression *) operands[1])->
        check_var_and_value(obsvars, vars);
    else {
      cout << "        right hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (right >= 5 && right <= 8) {  //right  hand side is an arithmetic expression
    if (left == 2)    // lhs is an integer
      return ((arithmetic_expression *) operands[1])->
        check_var_and_value(obsvars, vars);
    else {
      cout << "        left hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (left >= 9 && left <= 12) { // left hand side is a bit expression
    if (op > 1) {
      cout << "        only equality or inequality test is allowed in " <<
        to_string() << "." << endl;
      return false;
    }
    if (right == 1)   // rhs is a boolean value
      return ((bit_expression *) operands[0])->check_var_and_value(obsvars,
                                                                   vars);
    else if (right >= 9 && right <= 12) // rhs is a bit expression
      return ((bit_expression *) operands[0])->check_var_and_value(obsvars,
                                                                   vars)
        && ((bit_expression *) operands[1])->check_var_and_value(obsvars,
                                                                 vars);
    else {
      cout << "        right hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (right >= 9 && right <= 12) { //right  hand side is a bit expression
    if (op > 1) {
      cout << "        only equality or inequality test is allowed in " <<
        to_string() << "." << endl;
      return false;
    }
    if (left == 1)    // lhs is a boolean value
      return ((bit_expression *) operands[1])->check_var_and_value(obsvars,
                                                                   vars);
    else {
      cout << "        left hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  }

  cout << "        illegal logic expression: " << to_string() << endl;
  return false;
}

bool
logic_expression::check_global_consistency(map< string, map< string,
                                           basictype * > >*vars)
{
  unsigned char left = operands[0]->get_type(); // left hand side
  unsigned char right = operands[1]->get_type();  // right hand side
  bool left_var = true;
  bool right_var = true;

  if (left == 0) {    // left hand side is a variable, or an enumerate value 
    variable *v1 = ((variable *) operands[0]);
    string vs = v1->get_variable_name();
    bool left_defined = true;
    map< string, basictype * >::iterator p;
    if (v1->is_agent_name_null())
      left_var = false;
    else {
      string ag_name = v1->get_agent_name();
      map< string, map< string, basictype * > >::iterator gp =
        vars->find(ag_name);
      if (gp == vars->end()) {
        cout << "    undefined agent " << ag_name << endl;
        left_defined = false;
      } else {
        p = gp->second.find(vs);
        if (p == gp->second.end()) {  // the variable is not defined
          cout << "        variable " << vs << " is not defined in agent " <<
            ag_name << endl;
          left_defined = false;
        }
      }
    }
    if (right == 0) {   // right hand side could be a variable or a enumerate value
      variable *v2 = ((variable *) operands[1]);
      string vs1 = v2->get_variable_name();
      bool right_defined = true;
      map< string, basictype * >::iterator p1;
      if (v2->is_agent_name_null())
        right_var = false;
      else {
        string ag_name = v2->get_agent_name();
        map< string, map< string, basictype * > >::iterator gp =
          vars->find(ag_name);
        if (gp == vars->end()) {
          cout << "    undefined agent " << ag_name << endl;
          right_defined = false;
        } else {
          p1 = gp->second.find(vs1);
          if (p1 == gp->second.end()) { // the variable is not defined
            cout << "        variable " << vs1 << " is not defined in agent "
                 << ag_name << endl;
            right_defined = false;
          }
        }
      }
      if (!left_defined || !right_defined)
        return false;
      if (left_var && right_var) {  // both sides are variables
        //check if both sides have the same type.
        unsigned char t1 = p->second->get_type(); //lhs' type
        unsigned char t2 = p1->second->get_type();  //rhs' type
        if (t1 == t2) {   // same type
          if (t1 == 3) {  // enumerate type
            if (op != 0 && op != 1) {
              cout <<
                "        only '=' and '<>' are allowed for enumeration variables."
                   << endl;
              return false;
            }
            set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
            set< string > *s2 =
              ((enumerate *) (p1->second))->get_enumvalue();
            if (options["subset"] == 0) {
              if (s1->size() == s2->size()) { // same size
                bool equal = true;
                for (set< string >::iterator i = s1->begin(); i != s1->end();
                     i++)
                  if (s2->find(*i) == s2->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs << " and " << vs1 <<
                    " do not have the same enumerate type." << endl;
                  return false;
                }
              } else {
                cout << "        " << vs << " and " << vs1 <<
                  " do not have the same enumerate type." << endl;
                return false;
              }
            } else {
              bool equal = true;
              if (s1->size() < s2->size()) {  // same size
                for (set< string >::iterator i = s1->begin(); i != s1->end();
                     i++)
                  if (s2->find(*i) == s2->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs << " is not a subset of " << vs1 <<
                    "." << endl;
                  return false;
                }
              } else {
                for (set< string >::iterator i = s2->begin(); i != s2->end();
                     i++)
                  if (s1->find(*i) == s1->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs1 << " is not a subset of " << vs <<
                    "." << endl;
                  return false;
                }
              }
            }
          } else {
            if (t1 == 1 && op != 0 && op != 1) {
              cout <<
                "        only '=' and '<>' are allowed for boolean variables."
                   << endl;
              return false;
            }
            ((variable *) operands[0])->set_var_type(p->second);
            ((variable *) operands[1])->set_var_type(p1->second);
            return true;
          }
        } else {
          cout << "        " << vs << " and " << vs1 <<
            " have different type." << endl;
          return false;
        }
      } else if (left_var && !right_var) {  // lhs is a variable and rhs is an enumerate value
        if (op != 0 && op != 1) {
          cout <<
            "        only '=' and '<>' are allowed for enumeration variables."
               << endl;
          return false;
        }
        unsigned char t1 = p->second->get_type(); //lhs' type
        if (t1 == 3) {    // lhs must be enumerate
          set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
          if (s1->find(vs1) != s1->end()) { //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[0])->set_var_type(p->second);
            //change the rhs to be an enumerate value
            operands[1] = new enum_value(new string(vs1));
            return true;
          } else {
            cout << "        " << vs << " does not have the value " << vs1 <<
              endl;
            return false;
          }
        } else {
          cout << "        " << vs << " must have an enumerate type." << endl;
          return false;
        }
      } else if (!left_var && right_var) {  // lhs is an enumerate value and rhs is a variable
        if (op != 0 && op != 1) {
          cout <<
            "        only '=' and '<>' are allowed for enumeration variables."
               << endl;
          return false;
        }
        unsigned char t2 = p1->second->get_type();  //rhs' type
        if (t2 == 3) {    // rhs must be enumerate
          set< string > *s2 = ((enumerate *) (p1->second))->get_enumvalue();
          if (s2->find(vs) != s2->end()) {  //find a matched value in the enumerate type
            // add a link in rhs to its type
            ((variable *) operands[1])->set_var_type(p1->second);
            //change the lhs to be an enumerate value
            operands[0] = new enum_value(new string(vs));
            return true;
          } else {
            cout << "        " << vs1 << " does not have the value " << vs <<
              endl;
            return false;
          }
        } else {
          cout << "        " << vs1 << " must have an enumerate type." <<
            endl;
          return false;
        }
      } else {
        cout << "        " << vs << " or " << vs1 << " must be a variable." <<
          endl;
        return false;
      }
    } else if (left_var) {
      if (!left_defined)
        return false;
      left = p->second->get_type();
      if (right == 1) {   // right hand side is a boolean value
        if (left != 1) {
          cout << "         " << vs << " in " << to_string() <<
            " is not a Boolean variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          // add a link in variable to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (right == 2) {  // right hand side is an integer
        if (left != 2) {
          cout << "         " << vs << " in " << to_string() <<
            " is not a bounded integer variable." << endl;
          return false;
        }
        int vs1 = ((int_value *) operands[1])->get_value();
        if (((rangedint *) (p->second))->is_valid_value(vs1)) { // the value is in the correct range
          // add a link in variable to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs1 << " is out of bound in " << to_string()
               << "." << endl;
          return false;
        }
      } else if (right == 3) {  // right hand side is an enumerate value. It cannot happen. But we still check it.
        if (left != 3) {
          cout << "         " << vs << " in " << to_string() <<
            " is not an enumeration variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          string vs1 = ((enum_value *) operands[1])->get_value();
          set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
          if (s1->find(vs1) != s1->end()) { //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[0])->set_var_type(p->second);
            return true;
          } else {
            cout << "        " << vs << " does not have the value " << vs1 <<
              endl;
            return false;
          }
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (right >= 5 && right <= 8) {  // right hand side is an arithmetic expression
        if (left == 2 &&
            ((arithmetic_expression *) operands[1])->
            check_var_and_value(vars)) {
          // add a link in lhs to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs << "does not have integer type or " <<
            ((arithmetic_expression *) operands[1])->to_string() <<
            " is not a correct arithmetic expression." << endl;
          return false;
        }
      } else {      // right hand side is a bit expression   
        if (op > 1) {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
        if (left == 1 &&
            ((bit_expression *) operands[1])->check_var_and_value(vars)) {
          // add a link in lhs to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs << "does not have boolean type or " <<
            ((bit_expression *) operands[1])->to_string() <<
            " is not a correct bit expression." << endl;
          return false;
        }
      }
    } else {
      cout << "        " << vs << " must be a variable." << endl;
      return false;
    }
  } else if (right == 0) {  // right hand side is a variable 
    variable *v2 = ((variable *) operands[1]);
    string vs1 = ((variable *) operands[1])->get_variable_name();
    map< string, basictype * >::iterator p1;
    if (v2->is_agent_name_null())
      right_var = false;
    else {
      string ag_name = v2->get_agent_name();
      map< string, map< string, basictype * > >::iterator gp =
        vars->find(ag_name);
      if (gp == vars->end()) {
        cout << "    undefined agent " << ag_name << endl;
        return false;
      }
      p1 = gp->second.find(vs1);
      if (p1 == gp->second.end()) { // the variable is not defined
        cout << "        variable " << vs1 << " is not defined in agent " <<
          ag_name << endl;
        return false;
      }
    }
    if (right_var) {
      right = p1->second->get_type();
      if (left == 1) {    // left hand side is a boolean value 
        if (right != 1) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not a Boolean variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          // add a link in variable to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (left == 2) { // left hand side is an integer
        if (right != 2) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not a Boolean variable." << endl;
          return false;
        }
        int vs = ((int_value *) operands[0])->get_value();
        if (((rangedint *) (p1->second))->is_valid_value(vs)) { // the value is in the correct range
          // add a link in variable to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs << " is out of bound in " << to_string() <<
            "." << endl;
          return false;
        }
      } else if (left == 3) { // left hand side is an enumerate value. It cannot happen. But we still check it.
        if (right != 3) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not an enumeration variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          string vs = ((enum_value *) operands[0])->get_value();
          set< string > *s2 = ((enumerate *) (p1->second))->get_enumvalue();
          if (s2->find(vs) != s2->end()) {  //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[1])->set_var_type(p1->second);
            return true;
          } else {
            cout << "        " << vs1 << " does not have the value " << vs <<
              endl;
            return false;
          }
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (left >= 5 && left <= 8) {  // left hand side is an arithmetic expression
        if (right == 2 &&
            ((arithmetic_expression *) operands[0])->
            check_var_and_value(vars)) {
          // add a link in lhs to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs1 << "does not have integer type or " <<
            ((arithmetic_expression *) operands[0])->to_string() <<
            " is not a correct arithmetic expression." << endl;
          return false;
        }
      } else {      // left hand side is a bit expression
        if (op > 1) {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
        if (right == 1 &&
            ((bit_expression *) operands[0])->check_var_and_value(vars)) {
          // add a link in lhs to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs1 << "does not have boolean type or " <<
            ((bit_expression *) operands[0])->to_string() <<
            " is not a correct bit expression." << endl;
          return false;
        }
      }
    } else {
      cout << "        " << vs1 << " must be a variable." << endl;
      return false;
    }
  } else if (left >= 5 && left <= 8) {  // left hand side is an arithmetic expression
    if (right == 2)   // rhs is an integer
      return ((arithmetic_expression *) operands[0])->
        check_var_and_value(vars);
    else if (right >= 5 && right <= 8)  // rhs is an arithmetic expression
      return ((arithmetic_expression *) operands[0])->
        check_var_and_value(vars)
        && ((arithmetic_expression *) operands[1])->check_var_and_value(vars);
    else {
      cout << "        right hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (right >= 5 && right <= 8) {  //right  hand side is an arithmetic expression
    if (left == 2)    // lhs is an integer
      return ((arithmetic_expression *) operands[1])->
        check_var_and_value(vars);
    else {
      cout << "        left hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (left >= 9 && left <= 12) { // left hand side is a bit expression
    if (op > 1) {
      cout << "        only equality or inequality test is allowed in " <<
        to_string() << "." << endl;
      return false;
    }
    if (right == 1)   // rhs is a boolean value
      return ((bit_expression *) operands[0])->check_var_and_value(vars);
    else if (right >= 9 && right <= 12) // rhs is a bit expression
      return ((bit_expression *) operands[0])->check_var_and_value(vars) &&
        ((bit_expression *) operands[1])->check_var_and_value(vars);
    else {
      cout << "        right hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (right >= 9 && right <= 12) { //right  hand side is a bit expression
    if (op > 1) {
      cout << "        only equality or inequality test is allowed in " <<
        to_string() << "." << endl;
      return false;
    }
    if (left == 1)    // lhs is a boolean value
      return ((bit_expression *) operands[1])->check_var_and_value(vars);
    else {
      cout << "        left hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  }

  cout << "        illegal logic expression: " << to_string() << endl;
  return false;
}

BDD
logic_expression::encode_bdd(bdd_parameters * para, BDD * base)
{
  int lhstype = operands[0]->get_type();
  int rhstype = operands[1]->get_type();
  BDD tmpbdd = *base;
  BDD tmpbdd1 = para->bddmgr->bddOne();
  int begin, end, begin1;

  if (lhstype == 4) {   // left hand side is an action
    laction *la = (laction *) operands[0];
    basic_agent *ba = la->get_agent();
    begin = ba->get_action_index_begin();
    end = ba->get_action_index_end();
    string act_name = ((variable *) operands[1])->get_variable_name();
    map< string, vector< bool > *>::iterator k =
      ba->get_action_indices()->find(act_name);
    vector< bool > *b = (*k).second;
    for (int i = begin; i <= end; i++)
      tmpbdd = tmpbdd * ((*b)[i - begin] ? (*para->a)[i] : !(*para->a)[i]);
  } else if (lhstype == 0 && rhstype == 0) {  // two variables
    basictype *var_type = ((variable *) operands[0])->get_var_type();
    basictype *var_type1 = ((variable *) operands[1])->get_var_type();
    if (var_type->get_type() != var_type1->get_type()) {
      cout << "Error: only two variables in both sides of " << to_string() <<
        " have different types" << endl;
      exit(0);
    }
    begin = var_type->get_index_begin();
    begin1 = var_type1->get_index_begin();
    if (var_type->get_type() == 1) {  // bool
      if (op != 0 && op != 1) {
        cout << "Error: only EQ and NEQ on bool types are allowed in " <<
          to_string() << endl;
        exit(0);
      }
      tmpbdd1 *=
        ((!(*para->v)[begin] + (*para->v)[begin1]) * ((*para->v)[begin] +
                                                      !(*para->v)[begin1]));
      if (op == 1)
        tmpbdd *= !tmpbdd1;
      else
        tmpbdd *= tmpbdd1;
    } else if (var_type->get_type() == 2) { // rangedint
      ADD rhs =
        ((rangedint *) var_type1)->build_ADD_tree(para->bddmgr, para->addv,
                                                  para->ADD_cache);
      ADD lhs =
        ((rangedint *) var_type)->build_ADD_tree(para->bddmgr, para->addv,
                                                 para->ADD_cache);
      ADD result;
      if (op == 0)
        result = addEQ(para->bddmgr, lhs, rhs);
      else if (op == 1)
        result = addNEQ(para->bddmgr, lhs, rhs);
      else if (op == 2)
        result = addLT(para->bddmgr, lhs, rhs);
      else if (op == 3)
        result = addLE(para->bddmgr, lhs, rhs);
      else if (op == 4)
        result = addGT(para->bddmgr, lhs, rhs);
      else if (op == 5)
        result = addGE(para->bddmgr, lhs, rhs);
      tmpbdd *= result.BddThreshold(1);
    } else {      // enumerate
      if (op != 0 && op != 1) {
        cout << "Error: only EQ and NEQ on enumerate types are allowed in " <<
          to_string() << endl;
        exit(0);
      }
      set< string > *enums1 = ((enumerate *) var_type)->get_enumvalue();
      set< string > *enums2 = ((enumerate *) var_type1)->get_enumvalue();
      if (enums1->size() == enums2->size()) {
        ADD rhs =
          ((enumerate *) var_type1)->build_ADD_tree(para->bddmgr, para->addv,
                                                    para->ADD_cache);
        ADD lhs =
          ((enumerate *) var_type)->build_ADD_tree(para->bddmgr, para->addv,
                                                   para->ADD_cache);
        ADD result =
          (op == 0) ? addEQ(para->bddmgr, lhs, rhs) : addNEQ(para->bddmgr,
                                                             lhs, rhs);
        tmpbdd *= result.BddThreshold(1);
      } else {
        end = var_type->get_index_end();
        int end1 = var_type1->get_index_end();
        BDD tmpbdd2 = para->bddmgr->bddZero();
        set< string > *enums =
          (enums1->size() < enums2->size())? enums1 : enums2;
        for (set< string >::iterator i = enums->begin(); i != enums->end();
             i++) {
          vector< bool > *vb = ((enumerate *) var_type)->get_value_index(*i);
          vector< bool > *vb1 =
            ((enumerate *) var_type1)->get_value_index(*i);
          BDD tmpbdd3 = para->bddmgr->bddOne();
          for (int i = end; i >= begin; i--)
            if ((*vb)[i - begin])
              tmpbdd3 *= (*para->v)[i];
            else
              tmpbdd3 *= !(*para->v)[i];
          for (int i = end1; i >= begin1; i--)
            if ((*vb1)[i - begin1])
              tmpbdd3 *= (*para->v)[i];
            else
              tmpbdd3 *= !(*para->v)[i];
          tmpbdd2 += tmpbdd3;
        }

        if (op == 1)
          tmpbdd *= !tmpbdd2;
        else
          tmpbdd *= tmpbdd2;
      }
    }
  } else if (lhstype == 1 || rhstype == 1) {  // bool value
    variable *var =
      lhstype == 0 ? (variable *) operands[0] : (variable *) operands[1];
    bool_value *value =
      lhstype == 1 ? (bool_value *) operands[0] : (bool_value *) operands[1];
    basictype *var_type = var->get_var_type();
    begin = var_type->get_index_begin();
    if (value->get_value())
      tmpbdd1 *= (*para->v)[begin];
    else
      tmpbdd1 *= !(*para->v)[begin];
    if (op == 1)
      tmpbdd *= !tmpbdd1;
    else
      tmpbdd *= tmpbdd1;
  } else if (lhstype == 3 || rhstype == 3) {  // enumerate value
    variable *var =
      lhstype == 0 ? (variable *) operands[0] : (variable *) operands[1];
    basictype *var_type = var->get_var_type();
    begin = var_type->get_index_begin();
    end = var_type->get_index_end();
    string value =
      lhstype ==
      3 ? ((enum_value *) operands[0])->
      get_value() : ((enum_value *) operands[1])->get_value();
    vector< bool > *vb = ((enumerate *) var_type)->get_value_index(value);
    for (int i = end; i >= begin; i--)
      if ((*vb)[i - begin])
        tmpbdd1 *= (*para->v)[i];
      else
        tmpbdd1 *= !(*para->v)[i];
    if (op == 1)
      tmpbdd *= !tmpbdd1;
    else
      tmpbdd *= tmpbdd1;
  } else {      // arithmetic expression
    ADD lhs = lhstype == 0 ?
      ((variable *) operands[0])->build_ADD_tree(para->bddmgr, para->addv,
                                                 para->
                                                 ADD_cache) : (lhstype ==
                                                               2 ? para->
                                                               bddmgr->
                                                               constant(((int_value *) operands[0])->get_value()) : ((arithmetic_expression *) operands[0])->build_ADD_tree(para->bddmgr, para->addv, para->ADD_cache));
    ADD rhs =
      rhstype == 0 ? ((variable *) operands[1])->build_ADD_tree(para->bddmgr,
                                                                para->addv,
                                                                para->
                                                                ADD_cache)
      : (rhstype ==
         2 ? para->bddmgr->constant(((int_value *) operands[1])->
                                    get_value()) : ((arithmetic_expression *)
                                                    operands[1])->
         build_ADD_tree(para->bddmgr, para->addv, para->ADD_cache));
    ADD result;

    if (op == 0)
      result = addEQ(para->bddmgr, lhs, rhs);
    else if (op == 1)
      result = addNEQ(para->bddmgr, lhs, rhs);
    else if (op == 2)
      result = addLT(para->bddmgr, lhs, rhs);
    else if (op == 3)
      result = addLE(para->bddmgr, lhs, rhs);
    else if (op == 4)
      result = addGT(para->bddmgr, lhs, rhs);
    else if (op == 5)
      result = addGE(para->bddmgr, lhs, rhs);

    tmpbdd *= result.BddThreshold(1);
  }

  return tmpbdd;
}

bool_expression::bool_expression()
{
  op = 4;     // encode "other" branch in protocol
}

bool_expression::bool_expression(unsigned char o, Object * obj1)
{       // single operand
  op = o;
  operands[0] = obj1;
}

bool_expression::bool_expression(unsigned char o, Object * obj1,
                                 Object * obj2)
{       // two operands
  op = o;
  operands[0] = obj1;
  operands[1] = obj2;
}

bool_expression::~bool_expression()
{
}

unsigned char
bool_expression::get_op()
{
  return op;
}

bool
bool_expression::is_other_branch()
{
  if (op == 4)
    return true;
  else
    return false;
}

Object *
bool_expression::get_operand(unsigned char i)
{
  if (i > 1 || (i == 1 && (op == 0 || op == 3))) {
    cout << "error: bool operand " << i << " does not exist!" << endl;
    exit(1);
  } else if (operands[i] == NULL) {
    cout << "error: bool operand " << i << " is undefined!" << endl;
    exit(1);
  } else
    return (operands[i]);
}

bool
bool_expression::equal_to(bool_expression * expr)
{
  if (op == expr->get_op())
    switch (op) {
    case 0:
      return ((logic_expression *) (operands[0]))->
        equal_to((logic_expression *) expr->get_operand(0));
    case 1:
    case 2:
      return ((bool_expression *) (operands[0]))->
        equal_to((bool_expression *) expr->get_operand(0))
        && ((bool_expression *) (operands[1]))->
        equal_to((bool_expression *) expr->get_operand(1));
    case 3:
      return ((bool_expression *) (operands[0]))->
        equal_to((bool_expression *) expr->get_operand(0));
    case 4:
    case 5:
      return true;
    }

  return false;
}

string
bool_expression::to_string()
{
  if (op == 0)
    return ((logic_expression *) (operands[0]))->to_string();
  else if (op == 1)
    return ((bool_expression *) (operands[0]))->to_string() + " and " +
      ((bool_expression *) (operands[1]))->to_string();
  else if (op == 2)
    return ((bool_expression *) (operands[0]))->to_string() + " or " +
      ((bool_expression *) (operands[1]))->to_string();
  else if (op == 3)
    return "! " + ((bool_expression *) (operands[0]))->to_string();
  else if (op == 4)
    return "Other";
  else if (op == 5)
    return "TRUE";
  else if (op == 6)
    return "FALSE";
  return "error: should not happen.";
}

bool
bool_expression::check_var_and_value_flat(map< string, basictype * >*obsvars,
                                          map< string, basictype * >*vars,
                                          string agent_name, map< string,
                                          basic_agent * >*global_actions)
{
  if (op == 0)      // logic_expression
    return ((logic_expression *) operands[0])->check_evolution(obsvars, vars,
                                                               agent_name,
                                                               global_actions);
  else if (op == 3)   // not operaror
    return ((bool_expression *) operands[0])->
      check_var_and_value_flat(obsvars, vars, agent_name, global_actions);
  else if (op == 1 || op == 2) {
    vector< bool_expression * >*expr_vector =
      new vector< bool_expression * >();
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, op);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, op);
    bool result = true;
    for (unsigned int i = 0; i < expr_vector->size(); i++) {
      result = result
        && (*expr_vector)[i]->check_var_and_value_flat(obsvars, vars,
                                                       agent_name,
                                                       global_actions);
    }
    return result;
  } else if (op == 4)
    return true;
  else
    return false;
}

bool
bool_expression::check_evolution_flat(map< string, basictype * >*obsvars,
                                      map< string, basictype * >*vars,
                                      string agent_name, map< string,
                                      basic_agent * >*global_actions)
{
  if (op == 0)      // logic_expression
    return ((logic_expression *) operands[0])->check_evolution(obsvars, vars,
                                                               agent_name,
                                                               global_actions);
  else if (op == 3)   // not operaror
    return ((bool_expression *) operands[0])->check_evolution_flat(obsvars,
                                                                   vars,
                                                                   agent_name,
                                                                   global_actions);
  else if (op == 1 || op == 2) {
    vector< bool_expression * >*expr_vector =
      new vector< bool_expression * >();
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, op);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, op);
    bool result = true;
    for (unsigned int i = 0; i < expr_vector->size(); i++) {
      result = result
        && (*expr_vector)[i]->check_evolution_flat(obsvars, vars, agent_name,
                                                   global_actions);
    }
    return result;
  } else
    return false;
}

bool
bool_expression::check_global_consistency_flat(map< string, map< string,
                                               basictype * > >*vars)
{
  if (op == 0)      // logic_expression
    return ((logic_expression *) operands[0])->check_global_consistency(vars);
  else if (op == 3)   // not operaror
    return ((bool_expression *) operands[0])->
      check_global_consistency_flat(vars);
  else if (op == 1 || op == 2) {
    vector< bool_expression * >*expr_vector =
      new vector< bool_expression * >();
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, op);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, op);
    bool result = true;
    for (unsigned int i = 0; i < expr_vector->size(); i++) {
      result = result
        && (*expr_vector)[i]->check_global_consistency_flat(vars);
    }
    return result;
  } else
    return false;
}

void
bool_expression::collect_exprs(vector< bool_expression * >*expr_vector,
                               unsigned int type)
{
  if (op == type) {
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, type);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, type);
  } else
    expr_vector->push_back(this);
}

BDD
bool_expression::encode_bdd_flat(bdd_parameters * para, BDD * base)
{
  if (op == 0) {    // logic_expression
    return ((logic_expression *) operands[0])->encode_bdd(para, base);
  } else if (op == 3) {   // not operaror
    return !((bool_expression *) operands[0])->encode_bdd_flat(para, base);
  } else if (op == 1) {   // and operaror
    vector< bool_expression * >*expr_vector =
      new vector< bool_expression * >();
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, op);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, op);
    BDD result = para->bddmgr->bddOne();
    for (unsigned int i = 0; i < expr_vector->size(); i++) {
      result = result * (*expr_vector)[i]->encode_bdd_flat(para, base);
    }
    return result;
  } else if (op == 2) {   // or operaror
    vector< bool_expression * >*expr_vector =
      new vector< bool_expression * >();
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, op);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, op);
    BDD result = para->bddmgr->bddZero();
    for (unsigned int i = 0; i < expr_vector->size(); i++) {
      result = result + (*expr_vector)[i]->encode_bdd_flat(para, base);
    }
    return result;
  } else if (op == 5) {   // true
    return para->bddmgr->bddOne();
  } else if (op == 6) {   // false
    return para->bddmgr->bddZero();
  } else {
    return *base;
  }
}

fairness_expression::fairness_expression(unsigned char o, modal_formula * f1, modal_formula * f2, modal_formula * f3):
  modal_formula(o, f1, f2,
                f3)
{
}

fairness_expression::fairness_expression(unsigned char o, modal_formula * f1,
                                         modal_formula * f2):
  modal_formula(o, f1, f2)
{
}

fairness_expression::fairness_expression(unsigned char o, modal_formula * f1):
  modal_formula(o, f1)
{
}

fairness_expression::fairness_expression(atomic_proposition * obj1):
  modal_formula(obj1)
{
}

BDD
fairness_expression::get_bdd_representation()
{
  return bdd_representation;
}

void
fairness_expression::set_bdd_representation(BDD bddrep)
{
  bdd_representation = bddrep;
}

atomic_proposition::atomic_proposition(string * t)
{
  proposition = t;
}

atomic_proposition::~atomic_proposition()
{
}

string
atomic_proposition::get_proposition()
{
  if (proposition == NULL) {
    cout << "atomic proposition is unknown!" << endl;
    exit(1);
  } else
    return *proposition;
}

string
atomic_proposition::to_string()
{
  return get_proposition();
}

modal_formula::modal_formula(atomic_proposition * obj1)
{       // term
  op = 0;
  obj[0] = obj1;
}

modal_formula::modal_formula(unsigned char o, modal_formula * f1)
{       // sigle operand formula
  op = o;
  obj[0] = f1;
}

modal_formula::modal_formula(unsigned char o, modal_formula * f1,
                             modal_formula * f2)
{       // two operands formula
  op = o;
  obj[0] = f1;
  obj[1] = f2;
}

modal_formula::modal_formula(unsigned char o, modal_formula * f1,
                             modal_formula * f2, modal_formula * f3)
{       // three operands formula
  op = o;
  obj[0] = f1;
  obj[1] = f2;
  obj[2] = f3;
}

modal_formula::modal_formula(unsigned char o, modal_formula * f1,
                             modal_formula * f2, modal_formula * f3, modal_formula * f4)
{       // three operands formula
  op = o;
  obj[0] = f1;
  obj[1] = f2;
  obj[2] = f3;
  obj[3] = f4;
}

modal_formula::modal_formula(unsigned char o, modal_formula * f1, modal_formula * f2, modal_formula * f3, modal_formula * f4, modal_formula * f5)
{	// five operands fomula
  op = o;
  obj[0] = f1;
  obj[1] = f2;
  obj[2] = f3;
  obj[3] = f4;
  obj[4] = f5;
}

modal_formula::modal_formula(unsigned char o, modal_formula * f1, modal_formula * f2, modal_formula * f3, modal_formula * f4, int _equality, int _bound)
{	// five operands fomula
  op = o;
  obj[0] = f1;
  obj[1] = f2;
  obj[2] = f3;
  obj[3] = f4;
  equality = _equality;
  bound = _bound;
}

modal_formula::~modal_formula()
{
}

unsigned char
modal_formula::get_op()
{
  return op;
}

Object *
modal_formula::get_operand(unsigned char i)
{
  if (i == 0 && obj[0] != NULL)
    return (obj[0]);
  else if (i == 1 && obj[1] != NULL &&
           (op == 1 || op == 2 || op == 4 || op == 16 || op == 17 ||
            op == 30 || op == 31 || op == 32 || op == 40 ||
            op == 42 || op == 45 || op == 46 || op == 47 || op == 48 ||
            op == 51 || op == 52 || op == 53 ||
						op == 61 || op == 62 || op == 63 || op == 64 || op == 67 || op == 68 ||
						op == 71 || op == 81 || op == 82))
    return (obj[1]);
  else if (i == 2 && obj[2] != NULL && (op == 48 || op == 51 || op == 52 || op == 53 ||
                                        op == 61 || op == 62 || op == 63 || op == 64 || op == 67 || op == 68 ||
                                        op == 71 || op == 81 || op == 82))
    return (obj[2]);
  else if (i == 3 && obj[3] != NULL && (op == 61 || op == 62 || op == 63 || op == 64 || op == 67 || op == 68 || 
                                        op == 71 || op == 81 || op == 82))
    return (obj[3]);
  else if (i == 4 && obj[4] != NULL && (op == 67 || op == 68))
    return (obj[4]);
  else {
    cout << " error: operand " << i << " not found!" << endl;
    exit(1);
  }
}

string
modal_formula::to_string()
{
  if (op == 0)
    return ((atomic_proposition *) obj[0])->to_string();
  else if (op == 1)
    return "(" + ((modal_formula *) obj[0])->to_string() + " && " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 2)
    return "(" + ((modal_formula *) obj[0])->to_string() + " || " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 3)
    return "(! " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 4)
    return "(" + ((modal_formula *) obj[0])->to_string() + " -> " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 10)
    return "(AG " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 11)
    return "(EG " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 12)
    return "(AX " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 13)
    return "(EX " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 14)
    return "(AF " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 15)
    return "(EF " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 16)
    return "A(" + ((modal_formula *) obj[0])->to_string() + " U " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 17)
    return "E(" + ((modal_formula *) obj[0])->to_string() + " U " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 30)
    return "K(" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 31)
    return "GK(" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 32)
    return "GCK(" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 40)
    return "O(" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 42)
    return "DK(" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 45)
    return "(<" + ((modal_formula *) obj[0])->to_string() + ">X " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 46)
    return "(<" + ((modal_formula *) obj[0])->to_string() + ">F " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 47)
    return "(<" + ((modal_formula *) obj[0])->to_string() + ">G " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 48)
    return "<" + ((modal_formula *) obj[0])->to_string() + ">(" +
      ((modal_formula *) obj[1])->to_string() + " U " +
      ((modal_formula *) obj[2])->to_string() + ")";
  else if (op == 51)
    return "C (" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ")";
  else if (op == 52)
    return "Fu (" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ")";
  else if (op == 61)
    return "WCC (" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ", " +
      ((modal_formula *) obj[3])->to_string() + ")";
  else if (op == 62)
    return "SCC (" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ", " +
      ((modal_formula *) obj[3])->to_string() + ")";
  else if (op == 63)
    return "FuW (" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ", " +
      ((modal_formula *) obj[3])->to_string() + ")";
  else if (op == 64)
    return "FuS (" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ", " +
      ((modal_formula *) obj[3])->to_string() + ")";
  else if (op == 65)
    return "CaS (" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ", " +
      ((modal_formula *) obj[3])->to_string() + ")";
  else if (op == 66)
    return "ReS (" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ", " +
      ((modal_formula *) obj[3])->to_string() + ")";
  else if (op == 67)
    return "DeS (" + 
      ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ", " +
      ((modal_formula *) obj[3])->to_string() + ", " +
      ((modal_formula *) obj[4])->to_string() + ")";
  else if (op == 68)
    return "AsS (" + 
      ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ", " +
      ((modal_formula *) obj[3])->to_string() + ", " +
      ((modal_formula *) obj[4])->to_string() + ")";
  else if (op == 71)
    return "Tr (" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ", " +
      ((modal_formula *) obj[3])->to_string() + ")";
  else if (op == 81) {
     string opstr;
     ostringstream os ;
     os << bound;
		 if (equality == 0)
			 opstr = "=";
		 else if (equality == 1)
			 opstr = "<>";
		 else if (equality == 2)
			 opstr = "<";
		 else if (equality == 3)
			 opstr = "<=";
		 else if (equality == 4)
			 opstr = ">";
		 else if (equality == 5)
			 opstr = ">=";
    return "Tp (" + 
      ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ", " +
      ((modal_formula *) obj[3])->to_string() + ", " +
      opstr                                   + " " + 
      os.str()                                + ")";
  } else if (op == 82) {
     string opstr;
     ostringstream os ;
     os << bound;
		 if (equality == 0)
			 opstr = "=";
		 else if (equality == 1)
			 opstr = "<>";
		 else if (equality == 2)
			 opstr = "<";
		 else if (equality == 3)
			 opstr = "<=";
		 else if (equality == 4)
			 opstr = ">";
		 else if (equality == 5)
			 opstr = ">=";
    return "Tc (" + 
      ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ", " +
      ((modal_formula *) obj[3])->to_string() + ", " +
      opstr                                   + " " + 
      os.str()                                + ")";
  } else 
    return "Vi (" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ", " +
      ((modal_formula *) obj[2])->to_string() + ")";

}

bool
modal_formula::check_atomic_proposition(unsigned char type)
{
  // type=0: atomic proposition, type=1: agent, type=2: group, type=3: agent or group
  bool b1, b2, b3, b4, b5;
  switch (op) {
  case 1:     // AND
  case 2:     // OR
  case 4:     // IMPLIES
  case 16:      // AU
  case 17:      // EU
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(0);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0);
    return (b1 && b2);
  case 3:     // NOT
  case 10:      // AG
  case 11:      // EG
  case 12:      // AX
  case 13:      // EX
  case 14:      // AF
  case 15:      // EF
    return ((modal_formula *) obj[0])->check_atomic_proposition(0);
  case 30:      // K
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(1);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0);
    return (b1 && b2);
  case 40:      // O -- Does it allow a group name to appear? 
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(1);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0);
    return (b1 && b2);
  case 31:      // GK
  case 32:      // GCK
  case 42:      // DK
  case 45:      // ATL X
  case 46:      // ATL F
  case 47:      // ATL G
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(2);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0);
    return (b1 && b2);
  case 48:      // ATL U
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(2);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0);
    b3 = ((modal_formula *) obj[2])->check_atomic_proposition(0);
    return (b1 && b2 && b3);
  case 51:      // SC
  case 52:      // Fu
  case 53:      // Vi
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(1);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(1);
    b3 = ((modal_formula *) obj[2])->check_atomic_proposition(0);
    return (b1 && b2 && b3);
  case 61:      // WCC
  case 62:      // SCC
  case 63:      // FuW
  case 64:      // FuS
  case 65:      // CaS
  case 66:      // ReS
  case 71:      // Trust (Tr)
  case 81:      // Tp
  case 82:      // Tc
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(1);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(1);
    b3 = ((modal_formula *) obj[2])->check_atomic_proposition(0);
		b4 = ((modal_formula *) obj[3])->check_atomic_proposition(0);
    return (b1 && b2 && b3 && b4);
  case 67:      // DeS
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(1);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(1);
    b3 = ((modal_formula *) obj[2])->check_atomic_proposition(1);
    b4 = ((modal_formula *) obj[3])->check_atomic_proposition(0);
    b5 = ((modal_formula *) obj[4])->check_atomic_proposition(0);
    return (b1 && b2 && b3 && b4 && b5);
  case 68:      // AsS
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(1);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(1);
    b3 = ((modal_formula *) obj[2])->check_atomic_proposition(1);
    b4 = ((modal_formula *) obj[3])->check_atomic_proposition(0);
    b5 = ((modal_formula *) obj[4])->check_atomic_proposition(0);
    return (b1 && b2 && b3 && b4 && b5);
  case 0:     // A leaf node
    string name = ((atomic_proposition *) obj[0])->get_proposition();
    switch (type) {
    case 0:
      if (is_evaluation->find(name) == is_evaluation->end()) {
        cout << "    atomic proposition " << name << " is not defined." <<
          endl;
        return false;
      } else
        return true;
    case 1:
      if (is_agents->find(name) == is_agents->end()) {
        cout << "    agent " << name << " is not defined." << endl;
        return false;
      } else
        return true;
    case 2:
      if (is_groups->find(name) == is_groups->end()) {
        cout << "    group " << name << " is not defined." << endl;
        return false;
      } else
        return true;
    case 3:
      if (is_agents->find(name) == is_agents->end() &&
          is_groups->find(name) == is_groups->end()) {
        cout << "    agent " << name << " is not defined." << endl;
        return false;
      } else
        return true;
    }
  }
  return false;
}

BDD
modal_formula::check_formula(bdd_parameters * para)
{
  BDD result, rel, af;
  string name, name1, name2;
  Object *id, *id1, *id2;

  switch (op) {
  case 0:{      // leaf
    name = ((atomic_proposition *) obj[0])->get_proposition();

    if (para->BDD_cache->find(name) != para->BDD_cache->end())
      return ((*para->BDD_cache)[name]);

    bool_expression *simple = is_evaluation->find(name)->second;
    result =
      simple->encode_bdd_flat(para,
                              new BDD(para->bddmgr->bddOne())) * (*para->reach);

    (*para->BDD_cache)[name] = result;

    break;
  }
  case 1:     // AND
    result = ((modal_formula *) obj[0])->check_formula(para) *
      ((modal_formula *) obj[1])->check_formula(para);
    break;
  case 2:     // OR
    result = ((modal_formula *) obj[0])->check_formula(para) +
      ((modal_formula *) obj[1])->check_formula(para);
    break;
  case 3:     // NOT
    result =
      !((modal_formula *) obj[0])->check_formula(para) * (*para->reach);
    break;
  case 4:     // IMPLIES
    {
      BDD res1 = !(((modal_formula *) obj[0])->check_formula(para));
      BDD res2 =
        (((modal_formula *) obj[1])->check_formula(para) * (*para->reach));
      result = res1 * (*para->reach) + res2;

      break;
    }
  case 10:      // AG p = !EF !p
    result =
      (!check_EF
       ((!((modal_formula *) obj[0])->check_formula(para)) * (*para->reach),
        para)) * (*para->reach);
    break;
  case 11:      // EG 
    result = check_EG(((modal_formula *) obj[0])->check_formula(para), para);
    break;
  case 12:      // AX p = ! EX !p
    result = !check_EX(!((modal_formula *) obj[0])->check_formula(para),
                       para) * (*para->reach);
    break;
  case 13:      // EX
    result = check_EX(((modal_formula *) obj[0])->check_formula(para), para);
    break;
  case 14:      // AF p = !EG !p
    result =
      (!check_EG
       ((!((modal_formula *) obj[0])->check_formula(para)) * (*para->reach),
        para)) * (*para->reach);
    break;
  case 15:      // EF p = p \lor EX EF p
     result = check_EF(((modal_formula *) obj[0])->check_formula(para), para);
    break;
  case 16:      // AU (see check_AU)
    result = check_AU(((modal_formula *) obj[0])->check_formula(para),
                      ((modal_formula *) obj[1])->check_formula(para), para);
    break;
  case 17:      // EU
    result = check_EU(((modal_formula *) obj[0])->check_formula(para),
                      ((modal_formula *) obj[1])->check_formula(para), para);
    break;
  case 30:      // K
    {
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      af = !((modal_formula *) obj[1])->check_formula(para) * (*para->reach);
      result = (*para->reach) - get_nK_states(&af, name, para);
      break;
    }
  case 31:      // Everybody knows
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result = check_GK(((modal_formula *) obj[1])->check_formula(para),
                      name, para);
    break;
  case 32:      // Common knowledge
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result = check_GCK(((modal_formula *) obj[1])->check_formula(para),
                       name, para) * (*para->reach);
    break;
  case 40:      // O
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result =
      !check_nO(!((modal_formula *) obj[1])->check_formula(para) *
                (*para->reach), name, para) * (*para->reach);
    break;
  case 42:      // Distributed knowledge
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result = check_DK(((modal_formula *) obj[1])->check_formula(para),
                      name, para);
    break;
  case 45:      // ATL operator X
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result = check_ATLX(((modal_formula *) obj[1])->check_formula(para),
                        name, para);
    break;
  case 46:      // ATL operator F
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result =
      check_ATLU(para->bddmgr->bddOne(),
                 ((modal_formula *) obj[1])->check_formula(para), name, para);
    break;
  case 47:      // ATL operator G
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result = check_ATLG(((modal_formula *) obj[1])->check_formula(para),
                        name, para);
    break;
  case 48:      // ATL operator U
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result = check_ATLU(((modal_formula *) obj[1])->check_formula(para),
                        ((modal_formula *) obj[2])->check_formula(para),
                        name, para);
    break;
  case 51:      // SC
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    //result = check_SC(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    result = get_SC_states(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    /*if(options["verbosity"] >= 1) {
      cout << "--------------- SC states ---------------" << endl;
      print_states(result, *para->v, para->bddmgr);
			}*/
    break;  
  case 52:      // Fu
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    //result = check_Fu(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    result = get_Fu_states(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    /*if(options["verbosity"] >= 1) {
      cout << "--------------- Fu states ---------------" << endl;
      print_states(result, *para->v, para->bddmgr);
			}*/
    break;  
    /*case 53:      // Vi
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    result = check_Vi(((modal_formula *) obj[2])->check_formula(para),
                      name, name1, para);
		      break;  */
  case 61:      // WCC
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    //result = check_SC(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    result = get_WCC_states(((modal_formula *) obj[2])->check_formula(para), ((modal_formula *) obj[3])->check_formula(para), name, name1, para);
    /*if(options["verbosity"] >= 1) {
      cout << "--------------- SC states ---------------" << endl;
      print_states(result, *para->v, para->bddmgr);
			}*/
    break;  
  case 62:      // SCC
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    //result = check_SC(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    result = get_SCC_states(((modal_formula *) obj[2])->check_formula(para), ((modal_formula *) obj[3])->check_formula(para), name, name1, para);
    /*if(options["verbosity"] >= 1) {
      cout << "--------------- SC states ---------------" << endl;
      print_states(result, *para->v, para->bddmgr);
			}*/
    break;  
  case 63:      // FuW
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    //result = check_Fu(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    result = get_FUW_states(((modal_formula *) obj[2])->check_formula(para), ((modal_formula *) obj[3])->check_formula(para), name, name1, para);
    /*if(options["verbosity"] >= 1) {
      cout << "--------------- Fu states ---------------" << endl;
      print_states(result, *para->v, para->bddmgr);
			}*/
    break;  
  case 64:      // FuS
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    //result = check_Fu(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    result = get_FUS_states_new(((modal_formula *) obj[2])->check_formula(para), ((modal_formula *) obj[3])->check_formula(para), name, name1, para);
    /*if(options["verbosity"] >= 1) {
      cout << "--------------- Fu states ---------------" << endl;
      print_states(result, *para->v, para->bddmgr);
			}*/
    break;
case 65:      // CaS
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    //result = check_Fu(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    result = get_CAS_states_new(((modal_formula *) obj[2])->check_formula(para), ((modal_formula *) obj[3])->check_formula(para), name, name1, para);
    /*if(options["verbosity"] >= 1) {
      cout << "--------------- Fu states ---------------" << endl;
      print_states(result, *para->v, para->bddmgr);
			}*/
    break;  
  case 66:      // ReS
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    //result = check_Fu(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    result = get_RES_states_new(((modal_formula *) obj[2])->check_formula(para), ((modal_formula *) obj[3])->check_formula(para), name, name1, para);
    /*if(options["verbosity"] >= 1) {
      cout << "--------------- Fu states ---------------" << endl;
      print_states(result, *para->v, para->bddmgr);
			}*/
    break;  
  case 67:      // DeS
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    id2 = ((modal_formula *) obj[2])->get_operand(0);
    name2 = ((atomic_proposition *) id2)->get_proposition();

    result = get_DES_states_new(((modal_formula *) obj[3])->check_formula(para), ((modal_formula *) obj[4])->check_formula(para), name, name1, name2, para);
    break;
  case 68:
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    id2 = ((modal_formula *) obj[2])->get_operand(0);
    name2 = ((atomic_proposition *) id2)->get_proposition();

    result = get_ASS_states_new(((modal_formula *) obj[3])->check_formula(para), ((modal_formula *) obj[4])->check_formula(para), name, name1, name2, para);
    break;
  case 71:      // Trust (Tr)
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    result = get_TR_states(((modal_formula *) obj[2])->check_formula(para), ((modal_formula *) obj[3])->check_formula(para), name, name1, para);
    /*if(options["verbosity"] >= 1) {
      cout << "--------------- Tr states ---------------" << endl;
      print_states(result, *para->v, para->bddmgr);
			}*/
    break;  
  case 81:      // Tp
    //cout << "--------------- Checking Tp states ---------------" << endl;
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();

    //cout << "--------------- Computing Tp states ---------------" << endl;
    result = get_TP_states(((modal_formula *) obj[2])->check_formula(para), ((modal_formula *) obj[3])->check_formula(para), name, name1, equality, bound, para);
    break;
  case 82:      // Tc
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();

    result = get_TC_states(((modal_formula *) obj[2])->check_formula(para), ((modal_formula *) obj[3])->check_formula(para), name, name1, equality, bound, para);
    break;
  }
  return result * (*para->reach);
}

BDD
modal_formula::check_formula_fair(bdd_parameters * para, BDD fair_reach)
{
  // See "Efficient generation of counterexamples and witnesses in 
  // symbolic model checking", Clarke Grumberg McMillan Zhao, 1995
  // Section 4, p.3

  BDD result, af, rel;
  string name, name1;
  Object *id, *id1;

  switch (op) {
  case 0:     // leaf
    {
      name = ((atomic_proposition *) obj[0])->get_proposition();

      if (para->BDD_cache->find(name) != para->BDD_cache->end())
        return ((*para->BDD_cache)[name]);

      bool_expression *simple = is_evaluation->find(name)->second;
      result =
        simple->encode_bdd_flat(para,
                                new BDD(para->bddmgr->bddOne())) * 
        (*para->reach);

      (*para->BDD_cache)[name] = result;

      break;
    }
  case 1:     // AND
    result =
      ((modal_formula *) obj[0])->check_formula_fair(para,
                                                     fair_reach) *
      ((modal_formula *) obj[1])->check_formula_fair(para, fair_reach);
    break;
  case 2:     // OR
    result =
      ((modal_formula *) obj[0])->check_formula_fair(para,
                                                     fair_reach) +
      ((modal_formula *) obj[1])->check_formula_fair(para, fair_reach);
    break;
  case 3:     // NOT
    result =
      !((modal_formula *) obj[0])->check_formula_fair(para,
                                                      fair_reach) *
      (*para->reach);
    break;
  case 4:     // IMPLIES
    {
      BDD res1 =
        !(((modal_formula *) obj[0])->check_formula_fair(para, fair_reach));

      BDD res2 =
        (((modal_formula *) obj[1])->check_formula_fair(para, fair_reach) *
         (*para->reach));

      result = res1 * (*para->reach) + res2;

      break;
    }

  case 10:      // AG p = !EF !p
    result =
      (!check_EF_fair
       ((!((modal_formula *) obj[0])->check_formula_fair(para,
                                                         fair_reach)) *
        (*para->reach), fair_reach, para)) * (*para->reach);
    break;

  case 11:      // EG 
    {
      result =
        check_EG_fair(((modal_formula *) obj[0])->check_formula_fair(para,
                                                                     fair_reach),
                      para);
      break;
    }
  case 12:      // AX p = ! EX !p
    result =
      !check_EX_fair(!((modal_formula *) obj[0])->check_formula_fair
                     (para, fair_reach), fair_reach, para) * (*para->reach);
    break;
  case 13:      // EX
    result =
      check_EX_fair(((modal_formula *) obj[0])->check_formula_fair(para,
                                                                   fair_reach),
                    fair_reach, para);
    break;
  case 14:      // AF p = !EG !p
    result =
      !check_EG_fair(!((modal_formula *) obj[0])->check_formula_fair
                     (para, fair_reach), para) * (*para->reach);
    break;
  case 15:      // EF p = p \lor EX EF p
    result =
      check_EF_fair(((modal_formula *) obj[0])->check_formula_fair(para,
                                                                   fair_reach),
                    fair_reach, para);
    break;
  case 16:      // AU
    {
      BDD p =
        ((modal_formula *) obj[0])->check_formula_fair(para, fair_reach);
      BDD q =
        ((modal_formula *) obj[1])->check_formula_fair(para, fair_reach);

      result = !(check_EU_fair(!q, !(p + q), fair_reach, para) +
                 check_EG_fair(!q, para)) * (*para->reach);
      break;
    }
  case 17:      // EU
    result =
      check_EU_fair(((modal_formula *) obj[0])->check_formula_fair(para,
                                                                   fair_reach),
                    ((modal_formula *) obj[1])->check_formula_fair(para,
                                                                   fair_reach),
                    fair_reach, para);
    break;
  case 30:      // K
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    af =
      !((modal_formula *) obj[1])->check_formula_fair(para,
                                                      fair_reach) *
      (*para->reach);
    result = (*para->reach) - get_nK_states_fair(&af, name, fair_reach, para);
    break;
  case 31:      // Everybody knows
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result =
      check_GK_fair(((modal_formula *) obj[1])->check_formula_fair(para,
                                                                   fair_reach),
                    name, fair_reach, para);
    break;
  case 32:      // Common knowledge
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result = check_GCK_fair(((modal_formula *)
                             obj[1])->check_formula_fair(para, fair_reach),
                            name, fair_reach, para) * (*para->reach);
    break;
  case 40:      // O
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result =
      !check_nO_fair(!((modal_formula *) obj[1])->check_formula_fair
                     (para, fair_reach) * (*para->reach), name,
                     fair_reach, para) * (*para->reach);
    break;
  case 42:      // Distributed knowledge
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result =
      check_DK_fair(((modal_formula *) obj[1])->check_formula_fair(para,
                                                                   fair_reach),
                    name, fair_reach, para);
    break;
  case 45:      // ATL operator X
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result =
      check_ATLX_fair(((modal_formula *) obj[1])->check_formula_fair(para,
                                                                     fair_reach),
                      name, fair_reach, para);
    break;
  case 46:      // ATL operator F
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result = check_ATLU_fair(para->bddmgr->bddOne(),
                             ((modal_formula *) obj[1])->
                             check_formula_fair(para, fair_reach), name,
                             fair_reach, para);
    break;
  case 47:      // ATL operator G
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result =
      check_ATLG_fair(((modal_formula *) obj[1])->
                      check_formula_fair(para, fair_reach), name, para);
    break;
  case 48:      // ATL operator U
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    result =
      check_ATLU_fair(((modal_formula *) obj[1])->
                      check_formula_fair(para, fair_reach),
                      ((modal_formula *) obj[2])->check_formula_fair(para, fair_reach),
                      name, fair_reach, para);

  case 51:      // SC
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    //result = check_SC(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    result = get_SC_states_fair(((modal_formula *) obj[2])->check_formula_fair(para, fair_reach), name, name1, para, fair_reach);
    /*if(options["verbosity"] >= 1) {
      cout << "--------------- SC states ---------------" << endl;
      print_states(result, *para->v, para->bddmgr);
			}*/
    break;  
  case 52:      // Fu
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    id1 = ((modal_formula *) obj[1])->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    //result = check_Fu(((modal_formula *) obj[2])->check_formula(para), name, name1, para);
    result = get_Fu_states_fair(((modal_formula *) obj[2])->check_formula_fair(para, fair_reach), name, name1, para, fair_reach);
    /*if(options["verbosity"] >= 1) {
      cout << "--------------- Fu states ---------------" << endl;
      print_states(result, *para->v, para->bddmgr);
			}*/
    break;  
    /*case 53:      // Vi
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      id1 = ((modal_formula *) obj[1])->get_operand(0);
      name1 = ((atomic_proposition *) id1)->get_proposition();
      result = check_Vi(((modal_formula *) obj[2])->check_formula(para),
      name, name1, para);
      break;*/  
  default:
    result = check_formula(para);
    break;
  }

  return result * (*para->reach);
}

modal_formula *
modal_formula::push_negations(unsigned int level)
{
  switch (op) {
  case 0:     // leaf
    {
      return this;
      break;
    }
  case 1:     // AND
  case 2:     //OR
    {
      modal_formula *m =
        new modal_formula(op,
                          ((modal_formula *) obj[0])->push_negations(level),
                          ((modal_formula *) obj[1])->push_negations(level));
      return m;
      break;
    }
  case 3:     // NOT
    {
      if (((modal_formula *) obj[0])->get_op() == 0) {
        // Just copy and return
        return this;
      } else {
        // Need to push down negation
        modal_formula *nextformula = (modal_formula *) obj[0];
        unsigned char nextop = nextformula->get_op();

        switch (nextop) {
        case 1:   // AND
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *m2 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(1));
            modal_formula *result =
              new modal_formula(2, m1->push_negations(level),
                                m2->push_negations(level));
            return result;
            break;
          }
        case 2:   // OR
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *m2 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(1));
            modal_formula *result =
              new modal_formula(1, m1->push_negations(level),
                                m2->push_negations(level));
            return result;
            break;
          }
        case 3:   // NOT: negation of negation, remove both.
          {
            return ((modal_formula *) nextformula->get_operand(0))->
              push_negations(level);
            break;
          }
        case 4:   // IMPLIES, !(a -> b) = a & !b
          {
            modal_formula *m2 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(1));
            modal_formula *result =
              new modal_formula(1,
                                ((modal_formula *) nextformula->
                                 get_operand(0))->push_negations(level),
                                m2->push_negations(level));
            return result;
            break;
          }
        case 10:    // AG: !AG=EF !
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(15, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 11:    // EG: !EG=AF! 
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(14, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 12:    // AX
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(13, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 13:    // EX
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(12, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 14:    // AF : !AF=EG!
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(11, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 15:    // EF : !EF=AG!
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(10, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 16:    // AU : a messy one: A[aUb] = ! (E[!bU(!a&!b)] | EG(!b)) (p.216 huth-ryan)
          {
            modal_formula *notb =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(1));
            modal_formula *nota =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *egnotb = new modal_formula(11, notb);
            modal_formula *notanotb = new modal_formula(1, nota, notb);
            modal_formula *until =
              new modal_formula(17, notb->push_negations(level + 1),
                                notanotb->push_negations(level + 1));
            modal_formula *result =
              new modal_formula(2, until, egnotb->push_negations(level + 1));
            return result;
            break;
          }
        case 17:    // EU: not sure, see above: E[aUb] = ! (A[!bU(!a&!b)] | AG(!b))
          {
            modal_formula *notb = new modal_formula(3,
                                                    (modal_formula *)
                                                    nextformula->
                                                    get_operand(1));
            modal_formula *nota = new modal_formula(3,
                                                    (modal_formula *)
                                                    nextformula->
                                                    get_operand(0));
            modal_formula *agnotb = new modal_formula(11, notb);
            modal_formula *notanotb = new modal_formula(1, nota, notb);
            modal_formula *until =
              new modal_formula(16, notb->push_negations(level + 1),
                                notanotb->push_negations(level + 1));
            modal_formula *result =
              new modal_formula(2, until, agnotb->push_negations(level + 1));
            return result;
            break;
          }
        case 40:    // not O_i \phi => EF (g_i and not \phi) 
          if (level == 0) {
            Object *id =
              ((modal_formula *) nextformula->get_operand(0))->get_operand(0);
            string name = ((atomic_proposition *) id)->get_proposition();
            string *newap = new string(name + ".GreenStates");
            modal_formula *newformula =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(1));
            modal_formula *newformula1 = newformula->push_negations(1);
            modal_formula *newformula2 =
              new modal_formula(new atomic_proposition(newap));
            modal_formula *newformula3 =
              new modal_formula(15,
                                new modal_formula(1, newformula2,
                                                  newformula1));
            return newformula3;
          }
        default:{
          // Nothing to do for K etc:
          // Just copy and return
          return this;
          break;
        }
        }     // end switch nextop in else:
      }       // end else
    }       // end case 3 (NOT)
  case 4:     // IMPLIES : a->b=!a|b
    {
      modal_formula *m1 = new modal_formula(3, (modal_formula *) obj[0]);
      modal_formula *result =
        new modal_formula(2, m1->push_negations(level),
                          ((modal_formula *) obj[1])->push_negations(level));
      return result;
      break;
    }
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:
    {
      // Temporal is the first
      modal_formula *m =
        new modal_formula(op,
                          ((modal_formula *) obj[0])->push_negations(level +
                                                                     1));
      return m;
      break;
    }
  case 16:
  case 17:
    {
      // EU and AU, binary operators:
      modal_formula *m =
        new modal_formula(op,
                          ((modal_formula *) obj[0])->push_negations(level +
                                                                     1),
                          ((modal_formula *) obj[1])->push_negations(level +
                                                                     1));
      return m;
      break;
    }
  case 48:
    {
      // ATLU are the second and third thing
      modal_formula *m =
        new modal_formula(op, ((modal_formula *) obj[0]),
                          ((modal_formula *) obj[1])->push_negations(level +
                                                                     1),
                          ((modal_formula *) obj[2])->push_negations(level +
                                                                     1));
      return m;
      break;
    }
  case 51:
  case 52:
  case 53:
  {
      // SC and Fu are third thing
      modal_formula *m =
        new modal_formula(op, ((modal_formula *) obj[0]),
                          ((modal_formula *) obj[1]),
                          ((modal_formula *) obj[2])->push_negations(level +
                                                                     1));
      return m;
      break;
    }
  case 61:
  case 62:
  case 63:
  case 64:
  case 65:
  case 66:
  case 71:
  {
      modal_formula *m =
        new modal_formula(op, ((modal_formula *) obj[0]),
                          ((modal_formula *) obj[1]),
                          ((modal_formula *) obj[2])->push_negations(level + 1),
													((modal_formula *) obj[3])->push_negations(level + 1));
      return m;
      break;
    }
  case 67:
  case 68:
  {
      modal_formula *m =
        new modal_formula(op, ((modal_formula *) obj[0]),
                          ((modal_formula *) obj[1]),
                          ((modal_formula *) obj[2]),
                          ((modal_formula *) obj[3])->push_negations(level + 1),
													((modal_formula *) obj[4])->push_negations(level + 1));
      return m;
      break;
    }

  default:
    {
      // Epistemic and deontic, ATLX, ATLG, ATLF, is the second
      modal_formula *m =
        new modal_formula(op, ((modal_formula *) obj[0]),
                          ((modal_formula *) obj[1])->push_negations(level +
                                                                     1));
      return m;
      break;
    }
  }       // end top case
}

bool
modal_formula::is_ACTLK_new()
{
  /* Return TRUE if the first operator in the formula is ACTL (i.e., only A quantifiers and
   * K and negation only in front of propositions.
   * All the negations should have been pushed down already.
   */

  switch (op) {
  case 0:     // leaf
    {
      return true;
      break;
    }
  case 1:     // AND
    {
      return (((modal_formula *) obj[0])->
              is_ACTLK_new() & ((modal_formula *) obj[1])->is_ACTLK_new());
      break;
    }
  case 2:     // OR
    {
      return (((modal_formula *) obj[0])->
              is_ACTLK_new() & ((modal_formula *) obj[1])->is_ACTLK_new());
      break;
    }
  case 3:     // NOT
    {
      return true;
      break;
    }
  case 4:     // IMPLIES
    {
      // Again, this should not be here.
      if (((modal_formula *) obj[0])->get_op() == 0) {
        return ((modal_formula *) obj[1])->is_ACTLK_new();
      } else {
        return false;
      }
      break;
    }

  case 10:      // AG
  case 12:      // AX
  case 14:      // AF
  case 16:      // AU
    {
      return true;
    }
  case 11:      // EG 
  case 13:      // EX
  case 15:      // EF
  case 17:      // EU
    {
      return false;
      break;
    }

  case 30:
  case 31:
  case 32:
  case 40:
  case 42:
  case 51:
  case 52:
  case 53:
  case 61:
  case 62:
  case 63:
  case 64:
  case 71:
    return true;
  case 45:      // ATL 
  case 46:
  case 47:
  case 48:
    if (options["atlcex"] > 0)
      return true;
  }

  return false;
}

bool
modal_formula::is_ECTLK_new()
{
  /* Return TRUE if the first operator in the formula is ECTL (i.e., only E quantifiers and
   * \neg K, i.e., negation only in front of propositions and K operator
   */

  switch (op) {
  case 0:     // leaf
    {
      return true;
      break;
    }
  case 1:     // AND
    {
      return (((modal_formula *) obj[0])->
              is_ECTLK_new() & ((modal_formula *) obj[1])->is_ECTLK_new());
      break;
    }
  case 2:     // OR
    {
      return (((modal_formula *) obj[0])->
              is_ECTLK_new() & ((modal_formula *) obj[1])->is_ECTLK_new());
      break;
    }
  case 3:     // NOT
    {
      return true;
      break;
    }
  case 4:     // IMPLIES
    {
      if (((modal_formula *) obj[0])->get_op() == 0) {
        return ((modal_formula *) obj[1])->is_ECTLK_new();
      } else {
        return false;
      }
      break;
    }

  case 10:      // AG
  case 12:      // AX
  case 14:      // AF
  case 16:      // AU
    {
      return false;
    }
  case 11:      // EG 
  case 13:      // EX
  case 15:      // EF
  case 17:      // EU
    {
      return true;
    }
  case 30:
  case 31:
  case 32:
  case 40:
  case 42:
  case 51:
  case 52:
  case 53:
  case 61:
  case 62:
  case 63:
  case 64:
  case 71:
    // Now we check ATL formulas
  case 45:      // ATL operator X
  case 46:      // ATL operator F
  case 47:      // ATL operator G
  case 48:      // ATL operator U
    return true;
  }
  return false;
}

/** return true if there is no temporal operator in the formula.
 ** do not check the formula inside epistemic operators */
bool
modal_formula::is_NoCTL()
{
  switch (op) {
  case 0:     // leaf
  case 30:
  case 31:
  case 32:
  case 40:
  case 42:
  case 51:
  case 52:
  case 53:
  case 61:
  case 62:
  case 63:
  case 64:
  case 71:
    {
      return true;
    }
  case 1:     // AND
  case 2:     // OR
  case 4:     // IMPLIES
    {
      return (((modal_formula *) obj[0])->
              is_NoCTL() & ((modal_formula *) obj[1])->is_NoCTL());
    }
  case 3:     // NOT
    {
      return ((modal_formula *) obj[0])->is_NoCTL();
    }
  }
  return false;
}

/* Generate a witness for an ECTLK formula (i.e.  acounterexample
 * for an ACTLK formula), see
 * Clarke et al., "Tree-like counterexamples in model checking"
 * See the algorithm in Figure 7. Essentially, this procedure builds a tree 
 * representing a witness for the formula.
 * Returns false if the witness cannot be built (maybe because starting from
 * the wrong initial state)
 */
/** index is used to retrieve the index of the state */
bool
modal_formula::build_cex(BDD * state, unsigned int index,
                         bdd_parameters * para)
{
  vector< BDD * >tmpresult; // a vector to store the states of the witness
  vector< int >desc;    // This is a vector of state id (see global variables countex and idbdd)
  vector< transition * >desctr; // This is a vector of transitions (see golbal var cextr)

  Object *id;
  string name;

  BDD actagtin = para->bddmgr->bddOne();  // Actions of agents in group
  BDD actagtout = para->bddmgr->bddOne(); // Actions of agents NOT in group
  if (op == 45 || op == 46 || op == 47 || op == 48 ||
      (op == 3 && ((modal_formula *) obj[0])->get_op() >= 45
       && ((modal_formula *) obj[0])->get_op() <= 48)) {
    int begin, end;
    id = op != 3 ? ((modal_formula *) obj[0])->get_operand(0) :
      ((modal_formula *) ((modal_formula *) obj[0])->get_operand(0))->
      get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    map< string, set< string > >::iterator gi = is_groups->find(name);
    set< string > names_g = gi->second; // the list of agt names in groups

    for (map< string, basic_agent * >::iterator i = is_agents->begin();
         i != is_agents->end(); i++) {
      begin = i->second->get_action_index_begin();
      end = i->second->get_action_index_end();
      if (names_g.find(i->first) == names_g.end())
        for (int j = begin; j <= end; j++)
          actagtout = actagtout * (*para->a)[j];
      else
        for (int j = begin; j <= end; j++)
          actagtin = actagtin * (*para->a)[j];
    }
  }
  switch (op) {
  case 1:     // AND
    {
      bool r1 = ((modal_formula *) obj[0])->build_cex(state, index, para);
      if (!r1)
        return false;
      bool r2 = ((modal_formula *) obj[1])->build_cex(state, index, para);
      if (!r2)
        return false;
      return true;
      break;
    }
  case 2:     // OR
    {
      bool r1;
      modal_formula *left = ((modal_formula *) obj[1]);
      BDD *res = new BDD();
      (*res) = left->check_formula(para);

      if ((*state) <= (*res)) {
        r1 = left->build_cex(state, index, para);
        if (!r1)
          return false;
      } else {
        modal_formula *right = ((modal_formula *) obj[0]);
        r1 = right->build_cex(state, index, para);
      }
      return r1;
      break;
    }
  case 11:      // EG 
    {
      // Need to find a cycle here

      BDD last = check_formula(para); // the last state of fixpoint computation

      tmpresult.push_back(new BDD(*state));

      vector< BDD * >S; // a vector to store the stages of the computation

      int j = 0;

      BDD Q = para->bddmgr->bddZero();
      BDD T = para->bddmgr->bddZero() + *state;

      while (Q == para->bddmgr->bddZero()) {
        j++;

        BDD reachablefromlast =
          timesRT(tmpresult[j - 1], para->bddmgr, para->vRT, para->a);

        reachablefromlast = Exists(para->bddmgr, para->v, reachablefromlast);
        reachablefromlast =
          reachablefromlast.SwapVariables(*para->v, *para->pv);

        BDD abdd = reachablefromlast * last;
        if (abdd == para->bddmgr->bddZero()) {
          return false;
        }

        Q = abdd * T;   // if this is not false, we found a loop
        if (Q == para->bddmgr->bddZero()) {
          BDD curstate = abdd.PickOneMinterm(*para->v);

          tmpresult.push_back(new BDD(curstate));

          T = T + curstate;
        } else {
          break;
        }
      }

      unsigned int numberofstates = (unsigned int) tmpresult.size() - 1;  // (the last one is NOT repeated)

      int loopstart = -1; // the position where the loop starts
      for (unsigned int acounter = 0; acounter <= numberofstates; acounter++) {
        if ((Q * (*tmpresult[acounter])) != para->bddmgr->bddZero()) {
          loopstart = acounter;
          break;
        }
      }

      if (loopstart == -1) {
        if (options["quiet"] == 0) {
          cout << "Witness generation for EG:" << endl;
          cout << "THERE IS A PROBLEM HERE, PLEASE REPORT THIS ERROR" << endl;
        }
        return false;
      }
      // building transitions
      // first go to the last loop state
      int position1 = scount;
      for (unsigned int acounter = 0; acounter < numberofstates; acounter++) {
        BDD *from = new BDD(*tmpresult[acounter]);
        BDD *to = new BDD(*tmpresult[acounter + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD actions = timesTrans(from, to, para->vRT);
        actions = Exists(para->bddmgr, para->v, actions);
        actions = Exists(para->bddmgr, para->pv, actions);
        BDD action = actions.PickOneMinterm(*para->a);
        if (acounter == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[acounter])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[acounter])));
          desc.push_back(scount++);
        }
      }

      // Now add the loop back

      BDD *from = new BDD(*tmpresult[numberofstates]);
      BDD *to = new BDD(*tmpresult[loopstart]);
      (*to) = to->SwapVariables(*para->v, *para->pv);
      BDD actions = timesTrans(from, to, para->vRT);
      actions = Exists(para->bddmgr, para->v, actions);
      actions = Exists(para->bddmgr, para->pv, actions);
      BDD action = actions.PickOneMinterm(*para->a);

      if (loopstart == 0) {
        if (numberofstates == 0) {
          desctr.push_back(new transition(from, index, to, index, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));

          desc.push_back(index);
        } else {
          desctr.push_back(new transition(from, scount, to, index, &action));
          idbdd->insert(pair < int,
                        BDD * >(scount, (tmpresult[numberofstates])));

          desc.push_back(scount);
        }
        desc.push_back(index);
      } else {
        int loopposition = position1 + loopstart;
        desctr.
          push_back(new transition(from, scount, to, loopposition, &action));

        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[numberofstates])));
        desc.push_back(scount);
        desc.push_back(loopposition);
      }
      countex->push_back(new vector< int >(desc));

      cextr->push_back(new vector< transition * >(desctr));

      // Print witness for all states in the path

      for (vector< BDD * >::iterator tmpri = tmpresult.begin();
           tmpri != tmpresult.end(); tmpri++) {
        if ((*(*tmpri)) <= ((modal_formula *) obj[0])->check_formula(para)) {
          if (tmpri == tmpresult.begin())
            ((modal_formula *) obj[0])->build_cex(*tmpri, index, para);
          else
            ((modal_formula *) obj[0])->build_cex(*tmpri, ++position1, para);
        }
      }

      return true;

    }
  case 13:      // EX
    {
      tmpresult.push_back(state);

      vector< BDD * >S; // a vector to store the stages of the fixpoint computation

      BDD p = ((modal_formula *) obj[0])->check_formula(para);

      p = p.SwapVariables(*para->pv, *para->v); // The set of "next" states where p is true.

      BDD aset1 = timesRT(state, para->bddmgr, para->vRT, para->a);

      aset1 = aset1 * p;  // the set above where, additionally, p holds
      if (aset1 == para->bddmgr->bddZero())
        return false;

      aset1 = aset1.SwapVariables(*para->v, *para->pv); // swap back

      BDD curstate = aset1.PickOneMinterm(*para->v);
      tmpresult.push_back(new BDD(curstate));

      BDD *from = new BDD(*tmpresult[0]);
      BDD *to = new BDD(*tmpresult[1]);
      (*to) = to->SwapVariables(*para->v, *para->pv);
      BDD actions = timesTrans(from, to, para->vRT);
      actions = Exists(para->bddmgr, para->v, actions);
      actions = Exists(para->bddmgr, para->pv, actions);
      BDD action = actions.PickOneMinterm(*para->a);
      desctr.push_back(new transition(from, index, to, scount + 1, &action));
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      desc.push_back(index);
      desc.push_back(++scount);
      countex->push_back(new vector< int >(desc));
      idbdd->insert(pair < int, BDD * >(scount, (tmpresult[1])));
      cextr->push_back(new vector< transition * >(desctr));

      return ((modal_formula *) obj[0])->build_cex(tmpresult[1], scount,
                                                   para);
    }
  case 15:      // EF
    {
      vector< BDD * >S; // a vector to store the stages of the fixpoint computation
      BDD p = ((modal_formula *) obj[0])->check_formula(para);
      BDD tmp = para->bddmgr->bddOne();
      BDD q = p;
      BDD curstate = para->bddmgr->bddOne();  // the current state

      int n = 0;

      do {
        S.push_back(new BDD(q*(*para->reach)));
        tmp = q;
        q = p + check_EX(tmp, para);
        n++;
      } while (q != tmp);

      int j = 0;

      while (!(curstate <= (*(S[0])))) {
        BDD aset1;
        if (j == 0) {
          aset1 = (*state);
        } else {
          aset1 =
            Exists(para->bddmgr, para->v,
                   timesRT(&curstate, para->bddmgr, para->vRT, para->a));
          aset1 = aset1.SwapVariables(*para->v, *para->pv);
        }
        BDD aset2 = aset1 * (*(S[n - j - 1]));

        if (aset2 == para->bddmgr->bddZero()) {
          return false;
        }
        curstate = aset2.PickOneMinterm(*para->v);
        tmpresult.push_back(new BDD(curstate));

        j++;

      }

      // building transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD *from = new BDD(*tmpresult[i]);
        BDD *to = new BDD(*tmpresult[i + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD actions = timesTrans(from, to, para->vRT);
        actions = Exists(para->bddmgr, para->v, actions);
        actions = Exists(para->bddmgr, para->pv, actions);
        BDD action = actions.PickOneMinterm(*para->a);
        if (i == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }
      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));
        cextr->push_back(new vector< transition * >(desctr));
      }

      return ((modal_formula *) obj[0])->
        build_cex(tmpresult[tmpresult.size() - 1],
                  (tmpresult.size() == 1 ? index : scount), para);
    }
  case 17:      // EU
    {
      vector< BDD * >S; // a vector to store the stages of the fixpoint computation

      BDD p = ((modal_formula *) obj[0])->check_formula(para);
      BDD q = ((modal_formula *) obj[1])->check_formula(para);

      BDD tmp1 = para->bddmgr->bddOne();
      BDD curstate = para->bddmgr->bddOne();  // the current state

      int n = 0;

      BDD tmp2 = q;
      while (tmp1 != tmp2) {
        tmp1 = tmp2;
        tmp2 = tmp2 + (p * check_EX(tmp2, para));
        S.push_back(new BDD(tmp1));
        n++;
      }

      int j = 0;

      while (!(curstate <= (*(S[0])))) {
        BDD aset1;
        if (j == 0) {
          aset1 = (*state);
        } else {
          aset1 =
            Exists(para->bddmgr, para->v,
                   timesRT(&curstate, para->bddmgr, para->vRT, para->a));
          aset1 = aset1.SwapVariables(*para->v, *para->pv);
        }
        BDD aset2 = aset1 * (*(S[n - j - 1]));

        if (aset2 == para->bddmgr->bddZero()) {
          return false;
        }
        curstate = aset2.PickOneMinterm(*para->v);

        /* print state */
        tmpresult.push_back(new BDD(curstate));

        j++;

      }

      int position1 = scount;

      // transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD *from = new BDD(*tmpresult[i]);
        BDD *to = new BDD(*tmpresult[i + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD actions = timesTrans(from, to, para->vRT);
        actions = Exists(para->bddmgr, para->v, actions);
        actions = Exists(para->bddmgr, para->pv, actions);
        BDD action = actions.PickOneMinterm(*para->a);
        if (i == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }
      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));

        cextr->push_back(new vector< transition * >(desctr));
      }

      for (unsigned int i = 0; i < tmpresult.size() - 1; i++) {
        if ((*tmpresult[i]) <=
            ((modal_formula *) obj[0])->check_formula(para)) {
          if (i == 0)
            ((modal_formula *) obj[0])->build_cex(tmpresult[i], index, para);
          else
            ((modal_formula *) obj[0])->build_cex(tmpresult[i], ++position1,
                                                  para);
        }
      }
      return ((modal_formula *) obj[1])->
        build_cex(tmpresult[tmpresult.size() - 1],
                  (tmpresult.size() == 1 ? index : scount), para);
    }

  case 45:{     // ATLX witness
    BDD p = ((modal_formula *) obj[1])->check_formula(para);

    tmpresult.push_back(state);

    // get all successor states
    BDD successors = *state;
    for (unsigned int i = 0; i < agents->size(); i++)
      successors = successors * (*para->vRT)[i];

    // get successors that do not satisfy operator[1], i.e., \phi in <name>X \phi
    p = p.SwapVariables(*para->v, *para->pv);
    BDD bad_succ = successors - p;

    // get actions that cannot force the system move the successors that satisfy \phi
    BDD bad_actions = bad_succ.ExistAbstract(actagtout);
    bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
    bad_actions = Exists(para->bddmgr, para->v, bad_actions);

    // get successors that satisfy \phi
    BDD good_succ = successors * p;

    // remove successors that are reached by bad actions
    good_succ = good_succ - (good_succ * bad_actions);
    if (good_succ == para->bddmgr->bddZero())
      return false;
    BDD good_succ_tran = good_succ;
    good_succ = Exists(para->bddmgr, para->v, good_succ);

    // get one successor that reached by good actions
    BDD nextstate = Exists(para->bddmgr, para->a, good_succ);

    //options["fullatl"]=1;

    if (options["fullatl"] == 0) {
      nextstate = nextstate.PickOneMinterm(*para->pv);

      // get the set of actions
      BDD action =
        Exists(para->bddmgr, para->pv,
               good_succ * nextstate).PickOneMinterm(*para->a);

      // put the next state in the stack
      tmpresult.
        push_back(new BDD(nextstate.SwapVariables(*para->v, *para->pv)));

      BDD *from = new BDD(*tmpresult[0]);
      BDD *to = new BDD(*tmpresult[1]);
      (*to) = to->SwapVariables(*para->v, *para->pv);
      desctr.
        push_back(new transition(from, index, to, scount + 1, &action));
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      desc.push_back(index);
      desc.push_back(++scount);
      countex->push_back(new vector< int >(desc));
      idbdd->insert(pair < int, BDD * >(scount, (tmpresult[1])));
      cextr->push_back(new vector< transition * >(desctr));
      return ((modal_formula *) obj[1])->build_cex(tmpresult[1], scount,
                                                   para);
    } else {
      map< string, int >statekeys;

      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);
      statekeys[strkey] = index;

      desc.push_back(index);

      if (options["fullatl"] >= 3) {
        BDD pvstate = state->SwapVariables(*para->v, *para->pv);
        BDD YY = good_succ_tran;
        if (options["atlnewstate"] == 1) {
          BDD tmpYY = good_succ_tran - pvstate;
          if (tmpYY != para->bddmgr->bddZero())
            YY = tmpYY;
        }
        BDD tmpaction = YY.PickOneMinterm(*para->a);
        tmpaction = Exists(para->bddmgr, para->v, tmpaction);
        tmpaction = Exists(para->bddmgr, para->pv, tmpaction);
        tmpaction = tmpaction.ExistAbstract(actagtout);
        good_succ_tran = good_succ_tran * tmpaction;
        good_succ = Exists(para->bddmgr, para->v, good_succ_tran);
        nextstate = Exists(para->bddmgr, para->a, good_succ);
      }

      do {
        BDD successor = nextstate.PickOneMinterm(*para->pv);
        nextstate = nextstate - successor;

        // put the next state in the stack
        tmpresult.
          push_back(new BDD(successor.SwapVariables(*para->v, *para->pv)));

        // get the set of actions
        BDD action = Exists(para->bddmgr, para->pv, good_succ * successor);

        do {
          BDD oneaction = action.PickOneMinterm(*para->a);
          action = action - oneaction;
          BDD *from = new BDD(*tmpresult[0]);
          BDD *to = new BDD(*tmpresult[tmpresult.size() - 1]);
          (*to) = to->SwapVariables(*para->v, *para->pv);
          strkey = state_to_str(*tmpresult[tmpresult.size() - 1], *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          if (gi == statekeys.end()) {
            idbdd->insert(pair < int,
                          BDD * >(++scount,
                                  (tmpresult[tmpresult.size() - 1])));
            statekeys[strkey] = scount;
            desctr.
              push_back(new
                        transition(from, index, to, scount, &oneaction));
            desc.push_back(scount);
          } else {
            desctr.
              push_back(new
                        transition(from, index, to, gi->second,
                                   &oneaction));
            desc.push_back(gi->second);
          }
          countex->push_back(new vector< int >(desc));

          cextr->push_back(new vector< transition * >(desctr));
          desc.pop_back();
          desctr.pop_back();
        } while (action != para->bddmgr->bddZero());
      } while (nextstate != para->bddmgr->bddZero());
      if (options["fullatl"] % 2 == 0) {
        for (unsigned int i = 1; i < tmpresult.size(); i++) {
          string strkey = state_to_str(*tmpresult[i], *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          ((modal_formula *) obj[1])->build_cex(tmpresult[i], /* ++position1 */
                                                gi->second, para);
        }
      }

      return true;
    }
  }

  case 46:{     // ATL operator F
    vector< BDD * >S; // a vector to store the stages of the fixpoint computation
    BDD p = ((modal_formula *) obj[1])->check_formula(para);
    BDD tmp = para->bddmgr->bddOne();
    BDD q = p;
    BDD curstate = *state;  // the current state
    vector< BDD * >tmp_actions;

    if (options["fullatl"] > 0) {
      BDD last = check_formula(para); // the last state of fixpoint computation
      tmpresult.push_back(new BDD(*state));
      map< string, int >statekeys;
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);

      statekeys[strkey] = index;
      if (*tmpresult[0] * p == para->bddmgr->bddZero()) {
        BDD atltree = *state;
        if (atltree * last == para->bddmgr->bddZero())
          return false;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        //int depth = 0;

        BDD paststate;
        if (options["atlnewstate"] == 1)
          paststate = para->bddmgr->bddZero();  // store states that have been visited

        while (Y != para->bddmgr->bddZero()) {
          // Compute all successors
          for (unsigned int i = 0; i < agents->size(); i++)
            Y = Y * (*para->vRT)[i];
          // Compute successors that do not satisfy the ATLG formula
          BDD badstates = Y * (!lastprime);

          // Remove successor states; keep actions and source states only
          badstates = Exists(para->bddmgr, para->pv, badstates);
          badstates = badstates * (*para->reach);

          // Pick up bad actions executed by the opponents
          badstates = badstates.ExistAbstract(actagtout);

          // Pick up successors that either do not satisfy the ATLG formula or cannot reached by any strategy
          Y = Y - badstates;

          // keep only one strategy
          if (options["fullatl"] >= 3) {
            BDD allsources = Exists(para->bddmgr, para->a, Y);
            allsources = Exists(para->bddmgr, para->pv, allsources);
            BDD missed = allsources;
            BDD YY = para->bddmgr->bddZero();
            while (missed != para->bddmgr->bddZero()) {
              BDD source = missed.PickOneMinterm(*para->v);
              BDD trans = source * Y;
              if (options["atlnewstate"] == 1) {
                BDD sourcetarget =
                  source.SwapVariables(*para->v, *para->pv);
                paststate += sourcetarget;
                BDD newtrans = trans - paststate;
                if (newtrans != para->bddmgr->bddZero())
                  trans = newtrans;
              }
              BDD strategy = trans.PickOneMinterm(*para->a);
              strategy = strategy.ExistAbstract(actagtout);
              strategy = Y * strategy;
              YY += strategy;
              BDD heads = Exists(para->bddmgr, para->a, strategy);
              heads = Exists(para->bddmgr, para->pv, heads);
              missed = missed - heads;
            }
            Y = YY;
          }

          BDD Y1 = Exists(para->bddmgr, para->v, Y);
          Y1 = Exists(para->bddmgr, para->a, Y1);

          // Now we need to store the actions
          BDD nextstate = Y1;
          BDD good_succ = Y;
          do {
            BDD successor = nextstate.PickOneMinterm(*para->pv);
            nextstate = nextstate - successor;
            BDD *to = new BDD(successor);
            (*to) = to->SwapVariables(*para->v, *para->pv);
            strkey = state_to_str(*to, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            int to_index;
            if (gi == statekeys.end()) {
              idbdd->insert(pair < int, BDD * >(++scount, to));
              statekeys[strkey] = scount;
              // put the next state in the stack
              tmpresult.push_back(to);
              to_index = scount;
            } else
              to_index = gi->second;

            // compute all predecessors that have the selected successor
            BDD predecessors = good_succ * successor;
            do {
              BDD predecessor = predecessors.PickOneMinterm(*para->v);
              predecessors = predecessors - predecessor;
              BDD *from = new BDD(predecessor);
              strkey = state_to_str(predecessor, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                cout << "  cannot find state: " << strkey << endl;
                exit(0);
              }
              int from_index = gi->second;
              desc.push_back(from_index);

              // get the set of actions
              BDD action =
                Exists(para->bddmgr, para->pv,
                       good_succ * successor * predecessor);
              action = Exists(para->bddmgr, para->v, action);
              do {
                BDD oneaction = action.PickOneMinterm(*para->a);
                action = action - oneaction;

                desctr.
                  push_back(new
                            transition(from, from_index, to, to_index,
                                       &oneaction));
                cextr->push_back(new vector< transition * >(desctr));
                desctr.pop_back();
              } while (action != para->bddmgr->bddZero());
              desc.push_back(to_index);
              countex->push_back(new vector< int >(desc));
              desc.pop_back();
              desc.pop_back();
            } while (predecessors != para->bddmgr->bddZero());
          } while (nextstate != para->bddmgr->bddZero());

          // move the frontier to the good successors
          Y = Y1;
          Y = Y.SwapVariables(*para->v, *para->pv);
          Y = Y - atltree;
          atltree += Y;
          Y -= p;
        }
      }
      // Generate tree for every state in the atl tree
      if (options["fullatl"] % 2 == 0) {
        for (vector< BDD * >::iterator tmpri = tmpresult.begin();
             tmpri != tmpresult.end(); tmpri++) {
          string strkey = state_to_str(*(*tmpri), *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          if (**tmpri * p != para->bddmgr->bddZero())
            ((modal_formula *) obj[1])->build_cex(*tmpri, gi->second, para);
        }
      }
      return true;
    } else {
      int n = 0, j = 0;
      S.push_back(new BDD(q));
      while (*state * q == para->bddmgr->bddZero()) {
        q = check_ATLX(q, name, para);
        S.push_back(new BDD(q));
        n++;
      }

      while (j <= n) {
        BDD aset1;
        BDD good_succ = para->bddmgr->bddZero();
        if (j == 0) {
          aset1 = (*state);
        } else {
          tmp = curstate;
          for (unsigned int i = 0; i < agents->size(); i++)
            tmp = tmp * (*para->vRT)[i];
          BDD pq = S[n - j]->SwapVariables(*para->v, *para->pv);
          BDD bad_succ = tmp - pq;
          BDD bad_actions = bad_succ.ExistAbstract(actagtout);
          bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
          bad_actions = Exists(para->bddmgr, para->v, bad_actions);
          good_succ = tmp * pq;
          good_succ = good_succ - (good_succ * bad_actions);
          good_succ =
            Exists(para->bddmgr, para->v, good_succ).SwapVariables(*para->v,
                                                                   *para->
                                                                   pv);
          aset1 = Exists(para->bddmgr, para->a, good_succ);
        }
        if (aset1 == para->bddmgr->bddZero())
          return false;
        curstate = aset1.PickOneMinterm(*para->v);
        tmpresult.push_back(new BDD(curstate));
        if (j > 0) {
          BDD action =
            Exists(para->bddmgr, para->v,
                   good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(new BDD(action));
        }
        j++;
      }

      // building transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD *from = new BDD(*tmpresult[i]);
        BDD *to = new BDD(*tmpresult[i + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD *action = tmp_actions[i];
        if (i == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }

      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));
        cextr->push_back(new vector< transition * >(desctr));
      }

      return ((modal_formula *) obj[1])->
        build_cex(tmpresult[tmpresult.size() - 1],
                  (tmpresult.size() == 1 ? index : scount), para);
    }
  }

  case 47:{     // ATL operator G
    BDD p = ((modal_formula *) obj[1])->check_formula(para);
    p = p.SwapVariables(*para->v, *para->pv);
    BDD last = check_formula(para); // the last state of fixpoint computation
    tmpresult.push_back(new BDD(*state));
    vector< BDD * >tmp_actions;

    if (options["fullatl"] > 0) {
      map< string, int >statekeys;
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);

      statekeys[strkey] = index;
      BDD atltree = *state;
      if (atltree * last == para->bddmgr->bddZero())
        return false;
      BDD Y = atltree;
      BDD lastprime = last.SwapVariables(*para->v, *para->pv);
      BDD paststate;
      if (options["atlnewstate"] == 1)
        paststate = para->bddmgr->bddZero();  // store states that have been visited
      while (Y != para->bddmgr->bddZero()) {
        // Compute all successors
        for (unsigned int i = 0; i < agents->size(); i++)
          Y = Y * (*para->vRT)[i];
        // Compute successors that do not satisfy the ATLG formula
        BDD badstates = Y * (!lastprime);

        // Remove successor states; keep actions and source states only
        badstates = Exists(para->bddmgr, para->pv, badstates);
        badstates = badstates * (*para->reach);

        // Pick up bad actions executed by the opponents
        badstates = badstates.ExistAbstract(actagtout);

        // Pick up successors that either do not satisfy the ATLG formula or cannot reached by any strategy
        Y = Y - badstates;

        // keep only one strategy
        if (options["fullatl"] >= 3) {
          BDD allsources = Exists(para->bddmgr, para->a, Y);
          allsources = Exists(para->bddmgr, para->pv, allsources);
          BDD missed = allsources;
          BDD YY = para->bddmgr->bddZero();
          while (missed != para->bddmgr->bddZero()) {
            BDD source = missed.PickOneMinterm(*para->v);
            BDD trans = source * Y;
            if (options["atlnewstate"] == 1) {
              BDD sourcetarget = source.SwapVariables(*para->v, *para->pv);
              paststate += sourcetarget;
              BDD newtrans = trans - paststate;
              if (newtrans != para->bddmgr->bddZero())
                trans = newtrans;
            }
            BDD strategy = trans.PickOneMinterm(*para->a);
            strategy = strategy.ExistAbstract(actagtout);
            strategy = Y * strategy;
            YY += strategy;
            BDD heads = Exists(para->bddmgr, para->a, strategy);
            heads = Exists(para->bddmgr, para->pv, heads);
            missed = missed - heads;
          }
          Y = YY;
        }

        BDD Y1 = Exists(para->bddmgr, para->v, Y);
        Y1 = Exists(para->bddmgr, para->a, Y1);

        // Now we need to store the actions
        BDD nextstate = Y1;
        BDD good_succ = Y;
        do {
          BDD successor = nextstate.PickOneMinterm(*para->pv);
          nextstate = nextstate - successor;
          BDD *to = new BDD(successor);
          (*to) = to->SwapVariables(*para->v, *para->pv);
          strkey = state_to_str(*to, *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          int to_index;
          if (gi == statekeys.end()) {
            idbdd->insert(pair < int, BDD * >(++scount, to));
            statekeys[strkey] = scount;
            // put the next state in the stack
            tmpresult.push_back(to);
            to_index = scount;
          } else
            to_index = gi->second;

          // compute all predecessors that have the selected successor
          BDD predecessors = good_succ * successor;
          do {
            BDD predecessor = predecessors.PickOneMinterm(*para->v);
            predecessors = predecessors - predecessor;
            BDD *from = new BDD(predecessor);
            strkey = state_to_str(predecessor, *para->v);
            gi = statekeys.find(strkey);
            if (gi == statekeys.end()) {
              cout << "  cannot find state: " << strkey << endl;
              exit(0);
            }
            int from_index = gi->second;
            desc.push_back(from_index);

            // get the set of actions
            BDD action =
              Exists(para->bddmgr, para->pv,
                     good_succ * successor * predecessor);
            action = Exists(para->bddmgr, para->v, action);
            do {
              BDD oneaction = action.PickOneMinterm(*para->a);
              action = action - oneaction;

              desctr.
                push_back(new
                          transition(from, from_index, to, to_index,
                                     &oneaction));
              cextr->push_back(new vector< transition * >(desctr));
              desctr.pop_back();
            } while (action != para->bddmgr->bddZero());
            desc.push_back(to_index);
            countex->push_back(new vector< int >(desc));
            desc.pop_back();
            desc.pop_back();
          } while (predecessors != para->bddmgr->bddZero());
        } while (nextstate != para->bddmgr->bddZero());

        // move the frontier to the good successors
        Y = Y1;
        Y = Y.SwapVariables(*para->v, *para->pv);
        Y = Y - atltree;
        atltree += Y;
      }
      // Generate tree for every state in the atl tree
      if (options["fullatl"] % 2 == 0) {
        for (vector< BDD * >::iterator tmpri = tmpresult.begin();
             tmpri != tmpresult.end(); tmpri++) {
          string strkey = state_to_str(*(*tmpri), *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          ((modal_formula *) obj[1])->build_cex(*tmpri, gi->second, para);
        }
      }
      return true;
    } else {
      vector< BDD * >S; // a vector to store the stages of the computation
      int j = 0;
      BDD Q = para->bddmgr->bddZero();
      BDD T = *state;
      while (Q == para->bddmgr->bddZero()) {
        j++;
        //BDD reachablefromlast = timesRT(tmpresult[j-1]);
        BDD reachablefromlast = *tmpresult[j - 1];
        for (unsigned int i = 0; i < agents->size(); i++)
          reachablefromlast = reachablefromlast * (*para->vRT)[i];
        // copied from ATLX case
        BDD bad_succ = reachablefromlast - p;
        BDD bad_actions = bad_succ.ExistAbstract(actagtout);
        bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
        bad_actions = Exists(para->bddmgr, para->v, bad_actions);
        BDD good_succ = reachablefromlast * p;
        good_succ = good_succ - (good_succ * bad_actions);
        good_succ =
          Exists(para->bddmgr, para->v, good_succ).SwapVariables(*para->v,
                                                                 *para->pv);
        reachablefromlast = Exists(para->bddmgr, para->a, good_succ);

        BDD abdd = reachablefromlast * last;
        if (abdd == para->bddmgr->bddZero())
          return false;

        Q = abdd * T;   // if this is not false, we found a loop
        if (Q == para->bddmgr->bddZero()) {
          BDD curstate = abdd.PickOneMinterm(*para->v);
          tmpresult.push_back(new BDD(curstate));
          BDD action =
            Exists(para->bddmgr, para->v,
                   good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(new BDD(action));
          T = T + curstate;
        } else {
          BDD curstate = Q.PickOneMinterm(*para->v);
          BDD action =
            Exists(para->bddmgr, para->v,
                   good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(new BDD(action));
          break;
        }
      }
      unsigned int numberofstates = (unsigned int) tmpresult.size() - 1;  // (the last one is NOT repeated)
      int loopstart = -1; // the position where the loop starts
      for (unsigned int acounter = 0; acounter <= numberofstates;
           acounter++) {
        if ((Q * (*tmpresult[acounter])) != para->bddmgr->bddZero()) {
          loopstart = acounter;
          break;
        }
      }

      if (loopstart == -1) {
        if (options["quiet"] == 0) {
          cout << "Witness generation for ATLG:" << endl;
          cout << "THERE IS A PROBLEM HERE, PLEASE REPORT THIS ERROR" <<
            endl;
        }
        return false;
      }
      // building transitions
      // first go to the last loop state
      int position1 = scount;
      for (unsigned int acounter = 0; acounter < numberofstates; acounter++) {
        BDD *from = new BDD(*tmpresult[acounter]);
        BDD *to = new BDD(*tmpresult[acounter + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD *action = tmp_actions[acounter];
        if (acounter == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int,
                          BDD * >(index, (tmpresult[acounter])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[acounter])));
          desc.push_back(scount++);
        }
      }

      // Now add the loop back
      BDD *from = new BDD(*tmpresult[numberofstates]);
      BDD *to = new BDD(*tmpresult[loopstart]);
      (*to) = to->SwapVariables(*para->v, *para->pv);
      BDD *action = tmp_actions[tmp_actions.size() - 1];

      if (loopstart == 0) {
        if (numberofstates == 0) {
          desctr.push_back(new transition(from, index, to, index, action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));

          desc.push_back(index);
        } else {
          desctr.push_back(new transition(from, scount, to, index, action));
          idbdd->insert(pair < int,
                        BDD * >(scount, (tmpresult[numberofstates])));

          desc.push_back(scount);
        }
        desc.push_back(index);
      } else {
        int loopposition = position1 + loopstart;
        desctr.
          push_back(new transition(from, scount, to, loopposition, action));

        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[numberofstates])));
        desc.push_back(scount);
        desc.push_back(loopposition);
      }
      countex->push_back(new vector< int >(desc));

      cextr->push_back(new vector< transition * >(desctr));

      // Print witness for all states in the path
      for (vector< BDD * >::iterator tmpri = tmpresult.begin();
           tmpri != tmpresult.end(); tmpri++) {
        if (tmpri == tmpresult.begin())
          ((modal_formula *) obj[1])->build_cex(*tmpri, index, para);
        else
          ((modal_formula *) obj[1])->build_cex(*tmpri, ++position1, para);
      }

      return true;
    }
  }

  case 48:{     // ATL operator U
    vector< BDD * >S; // a vector to store the stages of the fixpoint computation
    vector< BDD * >tmp_actions;
    BDD p = ((modal_formula *) obj[1])->check_formula(para);
    BDD q = ((modal_formula *) obj[2])->check_formula(para);

    if (options["fullatl"] > 0) {
      BDD last = check_formula(para); // the last state of fixpoint computation
      tmpresult.push_back(new BDD(*state));
      map< string, int >statekeys;
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);

      statekeys[strkey] = index;
      if (*tmpresult[0] * q == para->bddmgr->bddZero()) {
        BDD atltree = *state;
        if (atltree * last == para->bddmgr->bddZero())
          return false;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        //int depth = 0;
        BDD paststate;
        if (options["atlnewstate"] == 1)
          paststate = para->bddmgr->bddZero();  // store states that have been visited

        while (Y != para->bddmgr->bddZero()) {
          for (unsigned int i = 0; i < agents->size(); i++)
            Y = Y * (*para->vRT)[i];
          // Compute successors that do not satisfy the ATLG formula
          BDD badstates = Y * (!lastprime);

          // Remove successor states; keep actions and source states only
          badstates = Exists(para->bddmgr, para->pv, badstates);
          badstates = badstates * (*para->reach);

          // Pick up bad actions executed by the opponents
          badstates = badstates.ExistAbstract(actagtout);

          // Pick up successors that either do not satisfy the ATLG formula or cannot reached by any strategy
          Y = Y - badstates;

          // keep only one strategy
          if (options["fullatl"] >= 3) {
            BDD allsources = Exists(para->bddmgr, para->a, Y);
            allsources = Exists(para->bddmgr, para->pv, allsources);
            BDD missed = allsources;
            BDD YY = para->bddmgr->bddZero();
            while (missed != para->bddmgr->bddZero()) {
              BDD source = missed.PickOneMinterm(*para->v);
              BDD trans = source * Y;
              if (options["atlnewstate"] == 1) {
                BDD sourcetarget =
                  source.SwapVariables(*para->v, *para->pv);
                paststate += sourcetarget;
                BDD newtrans = trans - paststate;
                if (newtrans != para->bddmgr->bddZero())
                  trans = newtrans;
              }
              BDD strategy = trans.PickOneMinterm(*para->a);
              strategy = strategy.ExistAbstract(actagtout);
              strategy = Y * strategy;
              YY += strategy;
              BDD heads = Exists(para->bddmgr, para->a, strategy);
              heads = Exists(para->bddmgr, para->pv, heads);
              missed = missed - heads;
            }
            Y = YY;
          }

          BDD Y1 = Exists(para->bddmgr, para->v, Y);
          Y1 = Exists(para->bddmgr, para->a, Y1);

          // Now we need to store the actions
          BDD nextstate = Y1;
          BDD good_succ = Y;
          do {
            BDD successor = nextstate.PickOneMinterm(*para->pv);
            nextstate = nextstate - successor;
            BDD *to = new BDD(successor);
            (*to) = to->SwapVariables(*para->v, *para->pv);
            strkey = state_to_str(*to, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            int to_index;
            if (gi == statekeys.end()) {
              idbdd->insert(pair < int, BDD * >(++scount, to));
              statekeys[strkey] = scount;
              // put the next state in the stack
              tmpresult.push_back(to);
              to_index = scount;
            } else
              to_index = gi->second;

            // compute all predecessors that have the selected successor
            BDD predecessors = good_succ * successor;
            do {
              BDD predecessor = predecessors.PickOneMinterm(*para->v);
              predecessors = predecessors - predecessor;
              BDD *from = new BDD(predecessor);
              strkey = state_to_str(predecessor, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                cout << "  cannot find state: " << strkey << endl;
                exit(0);
              }
              int from_index = gi->second;
              desc.push_back(from_index);

              // get the set of actions
              BDD action =
                Exists(para->bddmgr, para->pv,
                       good_succ * successor * predecessor);
              action = Exists(para->bddmgr, para->v, action);
              do {
                BDD oneaction = action.PickOneMinterm(*para->a);
                action = action - oneaction;

                desctr.
                  push_back(new
                            transition(from, from_index, to, to_index,
                                       &oneaction));
                cextr->push_back(new vector< transition * >(desctr));
                desctr.pop_back();
              } while (action != para->bddmgr->bddZero());
              desc.push_back(to_index);
              countex->push_back(new vector< int >(desc));
              desc.pop_back();
              desc.pop_back();
            } while (predecessors != para->bddmgr->bddZero());
          } while (nextstate != para->bddmgr->bddZero());

          // move the frontier to the good successors
          Y = Y1;
          Y = Y.SwapVariables(*para->v, *para->pv);
          Y = Y - atltree;
          atltree += Y;
          Y -= q;
        }
      }
      // Generate tree for every state in the atl tree
      if (options["fullatl"] % 2 == 0) {
        for (vector< BDD * >::iterator tmpri = tmpresult.begin();
             tmpri != tmpresult.end(); tmpri++) {
          string strkey = state_to_str(*(*tmpri), *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          if (**tmpri * q == para->bddmgr->bddZero())
            ((modal_formula *) obj[1])->build_cex(*tmpri, gi->second, para);
          else
            ((modal_formula *) obj[2])->build_cex(*tmpri, gi->second, para);
        }
      }
      return true;
    } else {
      BDD tmp1 = q;
      BDD curstate = para->bddmgr->bddOne();  // the current state
      int n = 0, j = 0;
      S.push_back(new BDD(tmp1));
      while (*state * tmp1 == para->bddmgr->bddZero()) {
        tmp1 = check_ATLX(tmp1, name, para) * p;
        S.push_back(new BDD(tmp1));
        n++;
      }
      while (j <= n) {
        BDD aset1;
        BDD good_succ = para->bddmgr->bddZero();
        if (j == 0) {
          aset1 = (*state);
        } else {
          tmp1 = curstate;
          for (unsigned int i = 0; i < agents->size(); i++)
            tmp1 = tmp1 * (*para->vRT)[i];
          BDD pq = S[n - j]->SwapVariables(*para->v, *para->pv);
          BDD bad_succ = tmp1 - pq;
          BDD bad_actions = bad_succ.ExistAbstract(actagtout);
          bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
          bad_actions = Exists(para->bddmgr, para->v, bad_actions);
          good_succ = tmp1 * pq;
          good_succ = good_succ - (good_succ * bad_actions);
          good_succ =
            Exists(para->bddmgr, para->v, good_succ).SwapVariables(*para->v,
                                                                   *para->
                                                                   pv);
          aset1 = Exists(para->bddmgr, para->a, good_succ);
        }
        if (aset1 == para->bddmgr->bddZero())
          return false;
        curstate = aset1.PickOneMinterm(*para->v);
        tmpresult.push_back(new BDD(curstate));
        if (j > 0) {
          BDD action =
            Exists(para->bddmgr, para->v,
                   good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(new BDD(action));
        }
        j++;
      }

      int position1 = scount;

      // transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD *from = new BDD(*tmpresult[i]);
        BDD *to = new BDD(*tmpresult[i + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD *action = tmp_actions[i];
        if (i == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }
      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));

        cextr->push_back(new vector< transition * >(desctr));
      }

      for (unsigned int i = 0; i < tmpresult.size() - 1; i++) {
        if ((*tmpresult[i]) <=
            ((modal_formula *) obj[1])->check_formula(para)) {
          if (i == 0)
            ((modal_formula *) obj[1])->build_cex(tmpresult[i], index,
                                                  para);
          else
            ((modal_formula *) obj[1])->build_cex(tmpresult[i], ++position1,
                                                  para);
        }
      }
      return ((modal_formula *) obj[2])->
        build_cex(tmpresult[tmpresult.size() - 1],
                  (tmpresult.size() == 1 ? index : scount), para);
    }
  }

  case 0:
  case 10:      // AG
  case 12:      // AX
  case 14:      // AF
  case 16:      // AU
  case 30:
  case 31:
  case 32:
  case 40:
  case 42:
  case 51:
  case 53: 
	case 61: 
	case 62: 
	case 63: 
	case 64: 
	case 65: 
	case 66: 
	case 67: 
	case 68: 
	case 71: {
    BDD p = check_formula(para);
    if ((*state) <= p) {
      if (idbdd->size() == 0) {
        idbdd->insert(pair < int, BDD * >(index, state));
        desc.push_back(index);
        countex->push_back(new vector< int >(desc));
      }
      return true;
    } else {
      return false;
    }

  }
  case 52: {
    string name, name1;
    Object *id, *id1;
    tmpresult.push_back(state);
    modal_formula *agentid = (modal_formula *) (get_operand(0));		
    id = agentid->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    modal_formula *agentid1 = (modal_formula *) (get_operand(1));		
    id1 = agentid->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    vector<basictype *> shared;
    get_shared_vars(name, name1, &shared);
    modal_formula *formula = ((modal_formula *) obj[2]);
    BDD p = formula->check_formula(para);
    BDD aset1 = get_eq_states(state, name, name1, &shared, para);  
    aset1 *= p;
    if (aset1 == para->bddmgr->bddZero())
      return false;
    
    BDD curstate = aset1.PickOneMinterm(*para->v);
    if (curstate == *state) {
      aset1 = aset1 - curstate;
      if (aset1 != para->bddmgr->bddZero())
	curstate = aset1.PickOneMinterm(*para->v);
    }
    tmpresult.push_back(new BDD(curstate));
    
    BDD *from = new BDD(*tmpresult[0]);
    BDD *to = new BDD(*tmpresult[1]);
    (*to) = to->SwapVariables(*para->v, *para->pv);
    BDD action = para->bddmgr->bddOne();
    desctr.push_back(new transition(from, index, to, scount + 1, name, &action));
    if (index >= idbdd->size())
      idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
    desc.push_back(index);
    desc.push_back(++scount);
    countex->push_back(new vector< int >(desc));
    idbdd->insert(pair < int, BDD * >(scount, (tmpresult[1])));
    
    cextr->push_back(new vector< transition * >(desctr));
    return formula->build_cex(tmpresult[1], scount, para);
  }
    
    // leaf
  case 3:{
    modal_formula *argument = ((modal_formula *) obj[0]);

    if (argument->get_op() == 0 || 
				argument->get_op() == 61 || argument->get_op() == 62 || argument->get_op() == 63 ||
				argument->get_op() == 64 || argument->get_op() == 65 || argument->get_op() == 66 ||
				argument->get_op() == 67 || argument->get_op() == 68 || argument->get_op() == 71) {

      // It's the negation of an atom

      BDD p = check_formula(para);

      if ((*state) <= p) {
        if (idbdd->size() == 0) {
          idbdd->insert(pair < int, BDD * >(index, state));
          desc.push_back(index);
          countex->push_back(new vector< int >(desc));
        }

        return true;
      } else {
        return false;
      }
    } else if (argument->get_op() == 30 || argument->get_op() == 31
               || argument->get_op() == 40 || argument->get_op() == 32
               || argument->get_op() == 42 || argument->get_op() == 51) {
      // it's the negation of K
      tmpresult.push_back(state);

      // Finding the position of the agent:
      string name, name1;
      Object *id, *id1;
      modal_formula *agentid = (modal_formula *) (argument->get_operand(0));
      BDD aset1;
      BDD rel;
      BDD formula;
      if (argument->get_op() == 30) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula =
          !((modal_formula *) (argument->
                               get_operand(1)))->check_formula(para) *
          (*para->reach);

        aset1 = get_K_states(formula, state, name, para);
      } else if (argument->get_op() == 31) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula =
          ((modal_formula *) (argument->
                              get_operand(1)))->check_formula(para) *
          (*para->reach);
        aset1 = check_GK(formula, name, para);

        aset1 = !aset1 * !formula * (*para->reach);
        aset1 = get_GK_states(aset1, state, name, para);
      } else if (argument->get_op() == 32) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula =
          ((modal_formula *) (argument->
                              get_operand(1)))->check_formula(para);
        aset1 = !check_GCK(formula, name, para) * (*para->reach);

        aset1 = aset1 * !formula;
        aset1 = get_GK_states(aset1, state, name, para);
      } else if (argument->get_op() == 40) {  // O
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula =
          !((modal_formula *) (argument->
                               get_operand(1)))->check_formula(para) *
          (*para->reach);
        aset1 = check_nO(formula, name, para) * (*para->reach);
      } else if (argument->get_op() == 42) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula =
          ((modal_formula *) argument->
           get_operand(1))->check_formula(para) * (*para->reach);
        aset1 = check_DK(formula, name, para);

        aset1 = !aset1 * !formula * (*para->reach);
        aset1 = get_DK_states(aset1, state, name, para);
      } else if (argument->get_op() == 51) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
				modal_formula *agentid1 = (modal_formula *) (argument->get_operand(1));        
				id1 = agentid1->get_operand(0);
        name1 = ((atomic_proposition *) id1)->get_proposition();
				vector<basictype *> shared;
				get_shared_vars(name, name1, &shared);
        formula =
          ((modal_formula *) (argument->
															get_operand(2)))->check_formula(para) * (*para->reach);
        aset1 = get_eq_states(state, name, name1, &shared, para);
	aset1 *= build_shared_equivalence(&shared, para);
	aset1 *= !formula;
      }

      if (aset1 == para->bddmgr->bddZero())
        return false;

      BDD curstate = aset1.PickOneMinterm(*para->v);
      if (curstate == *state) {
        aset1 = aset1 - curstate;
        if (aset1 != para->bddmgr->bddZero())
          curstate = aset1.PickOneMinterm(*para->v);
      }
      tmpresult.push_back(new BDD(curstate));

      BDD *from = new BDD(*tmpresult[0]);
      BDD *to = new BDD(*tmpresult[1]);
      (*to) = to->SwapVariables(*para->v, *para->pv);
      BDD action = para->bddmgr->bddOne();
      if (argument->get_op() == 30 || argument->get_op() == 31
          || argument->get_op() == 32 || argument->get_op() == 40
          || argument->get_op() == 42 || argument->get_op() == 51)
        desctr.
          push_back(new
                    transition(from, index, to, scount + 1, name, &action));
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      desc.push_back(index);
      desc.push_back(++scount);
      countex->push_back(new vector< int >(desc));
      idbdd->insert(pair < int, BDD * >(scount, (tmpresult[1])));

      cextr->push_back(new vector< transition * >(desctr));
      if (argument->get_op() != 40) {
        modal_formula *fcex;
        if (argument->get_op() == 30 || argument->get_op() == 31
            || argument->get_op() == 32 || argument->get_op() == 42)
          fcex =
            new modal_formula(3,
                              ((modal_formula *) (argument->
                                                  get_operand(1))));
        else
          fcex =
            new modal_formula(3,
                              ((modal_formula *) (argument->
                                                  get_operand(2))));
        fcex = fcex->push_negations(1);

        //cout << fcex->to_string() << endl;

        return fcex->build_cex(tmpresult[1], scount, para);
      } else
        return true;
    } else if ((argument->get_op() == 45 || argument->get_op() == 46
                || argument->get_op() == 47 || argument->get_op() == 48)
               && options["atlcex"] > 0) {
      if (argument->get_op() == 45) { // ATLX
        BDD p =
          ((modal_formula *) (argument->get_operand(1)))->
          check_formula(para);

        tmpresult.push_back(state);

        // get all successor states
        BDD successors = *state;
        for (unsigned int i = 0; i < agents->size(); i++)
          successors = successors * (*para->vRT)[i];

        BDD allactions = Exists(para->bddmgr, para->pv, successors);
        allactions = Exists(para->bddmgr, para->v, allactions);
        allactions = allactions.ExistAbstract(actagtout);

        // get successors that do not satisfy operator[1], i.e., \phi in <name>X \phi
        p = p.SwapVariables(*para->v, *para->pv);
        BDD bad_succ = successors - p;

        map< string, int >statekeys;

        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
        string strkey = state_to_str(*tmpresult[0], *para->v);
        statekeys[strkey] = index;

        desc.push_back(index);
        do {
          BDD oneaction = allactions.PickOneMinterm(*para->a);

          BDD onetran = oneaction.ExistAbstract(actagtout);
          allactions = allactions - onetran;

          onetran *= bad_succ;
          BDD successor = onetran.PickOneMinterm(*para->pv);
          oneaction = (onetran * successor).PickOneMinterm(*para->a);

          // put the next state in the stack
          tmpresult.
            push_back(new
                      BDD(successor.SwapVariables(*para->v, *para->pv)));

          // get the set of actions
          BDD *from = new BDD(*tmpresult[0]);
          BDD *to = new BDD(*tmpresult[tmpresult.size() - 1]);
          strkey = state_to_str(*tmpresult[tmpresult.size() - 1], *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          if (gi == statekeys.end()) {
            idbdd->insert(pair < int,
                          BDD * >(++scount,
                                  (tmpresult[tmpresult.size() - 1])));
            statekeys[strkey] = scount;
            desctr.
              push_back(new
                        transition(from, index, to, scount, &oneaction));
            desc.push_back(scount);
          } else {
            desctr.
              push_back(new
                        transition(from, index, to, gi->second,
                                   &oneaction));
            desc.push_back(gi->second);
          }
          countex->push_back(new vector< int >(desc));

          cextr->push_back(new vector< transition * >(desctr));
          desc.pop_back();
          desctr.pop_back();
        } while (allactions != para->bddmgr->bddZero());
        if (options["atlcex"] == 2) {
          for (unsigned int i = 1; i < tmpresult.size(); i++) {
            string strkey = state_to_str(*tmpresult[i], *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            modal_formula nphi(3,
                               (modal_formula *) (argument->
                                                  get_operand(1)));
            nphi.build_cex(tmpresult[i], gi->second, para);
          }
        }

        return true;
      } else if (argument->get_op() == 46) {  // ATLF
        BDD p =
          ((modal_formula *) (argument->get_operand(1)))->
          check_formula(para);
        BDD p1 = p.SwapVariables(*para->v, *para->pv);
        tmpresult.push_back(state);
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
        map< string, int >statekeys;
        string strkey = state_to_str(*tmpresult[0], *para->v);
        statekeys[strkey] = index;

        BDD last = argument->check_formula(para); // the last state of fixpoint computation    

        BDD atltree = *state;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        while (Y != para->bddmgr->bddZero()) {
          BDD tmpy = Y;
          BDD newy = para->bddmgr->bddZero();

          // get all successor states
          while (tmpy != para->bddmgr->bddZero()) {
            BDD predecessor = tmpy.PickOneMinterm(*para->v);
            tmpy -= predecessor;
            BDD *from = new BDD(predecessor);
            strkey = state_to_str(predecessor, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            if (gi == statekeys.end()) {
              cout << "  ATLF counterexample - cannot find state: " <<
                strkey << endl;
              exit(0);
            }
            int from_index = gi->second;
            desc.push_back(from_index);

            BDD successors = predecessor;
            for (unsigned int i = 0; i < agents->size(); i++)
              successors *= (*para->vRT)[i];

            BDD allactions = Exists(para->bddmgr, para->pv, successors);
            allactions = Exists(para->bddmgr, para->v, allactions);
            allactions = allactions.ExistAbstract(actagtout);

            // get successors that do not satisfy operator[1], i.e., \phi in <name>X \phi
            BDD bad_succ1 = successors - lastprime; // \not ATLF p
            do {
              BDD oneaction = allactions.PickOneMinterm(*para->a);

              BDD onetran = oneaction.ExistAbstract(actagtout);
              allactions = allactions - onetran;
              onetran = onetran * bad_succ1;

              BDD successor = onetran.PickOneMinterm(*para->pv);
              BDD succ1 = successor.SwapVariables(*para->v, *para->pv);
              oneaction = (onetran * successor).PickOneMinterm(*para->a);

              // get the set of actions
              BDD *to = new BDD(succ1);
              strkey = state_to_str(succ1, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                newy += succ1;  // succ1 \models \phi
                tmpresult.push_back(new BDD(succ1));

                idbdd->insert(pair < int, BDD * >(++scount, to));
                statekeys[strkey] = scount;
                desctr.
                  push_back(new
                            transition(from, from_index, to, scount,
                                       &oneaction));
                desc.push_back(scount);
              } else {
                desctr.
                  push_back(new
                            transition(from, from_index, to, gi->second,
                                       &oneaction));
                desc.push_back(gi->second);
              }
              countex->push_back(new vector< int >(desc));

              cextr->push_back(new vector< transition * >(desctr));
              desc.pop_back();
              desctr.pop_back();
            } while (allactions != para->bddmgr->bddZero());
            desc.pop_back();
          }
          Y = newy;
        }
        if (options["atlcex"] == 2) {
          for (unsigned int i = 0; i < tmpresult.size(); i++) {
            string strkey = state_to_str(*tmpresult[i], *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            modal_formula nphi(3,
                               (modal_formula *) (argument->
                                                  get_operand(1)));
            nphi.build_cex(tmpresult[i], gi->second, para);
          }
        }

        return true;
      } else if (argument->get_op() == 47) {  // ATLG
        BDD p =
          ((modal_formula *) (argument->get_operand(1)))->
          check_formula(para);
        BDD p1 = p.SwapVariables(*para->v, *para->pv);
        tmpresult.push_back(state);
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
        if (*state * p == para->bddmgr->bddZero()) {
          if (options["atlcex"] == 2) {
            modal_formula nphi(3,
                               (modal_formula *) (argument->
                                                  get_operand(1)));
            nphi.build_cex(state, index, para);
          }
          return true;
        }
        map< string, int >statekeys;
        string strkey = state_to_str(*tmpresult[0], *para->v);
        statekeys[strkey] = index;

        BDD last = argument->check_formula(para); // the last state of fixpoint computation    

        BDD atltree = *state;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        while (Y != para->bddmgr->bddZero()) {
          BDD tmpy = Y;
          BDD newy = para->bddmgr->bddZero();

          // get all successor states
          while (tmpy != para->bddmgr->bddZero()) {
            BDD predecessor = tmpy.PickOneMinterm(*para->v);
            tmpy -= predecessor;
            BDD *from = new BDD(predecessor);
            strkey = state_to_str(predecessor, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            if (gi == statekeys.end()) {
              cout << "  ATLG counterexample - cannot find state: " <<
                strkey << endl;
              exit(0);
            }
            int from_index = gi->second;
            desc.push_back(from_index);

            BDD successors = predecessor;
            for (unsigned int i = 0; i < agents->size(); i++)
              successors *= (*para->vRT)[i];

            BDD allactions = Exists(para->bddmgr, para->pv, successors);
            allactions = Exists(para->bddmgr, para->v, allactions);
            allactions = allactions.ExistAbstract(actagtout);

            // get successors that do not satisfy operator[1], i.e., \phi in <name>X \phi
            BDD bad_succ = successors - p1; // \not \phi
            BDD bad_succ1 = successors - lastprime; // \not ATLG \phi
            do {
              BDD oneaction = allactions.PickOneMinterm(*para->a);
              BDD onetran = oneaction.ExistAbstract(actagtout);
              allactions = allactions - onetran;
              BDD onetran1 = onetran * bad_succ;
              if (onetran1 == para->bddmgr->bddZero())
                onetran = onetran * bad_succ1;
              else
                onetran = onetran1;

              BDD successor = onetran.PickOneMinterm(*para->pv);
              BDD succ1 = successor.SwapVariables(*para->v, *para->pv);
              oneaction = (onetran * successor).PickOneMinterm(*para->a);

              // get the set of actions
              BDD *to = new BDD(succ1);
              strkey = state_to_str(succ1, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                if (onetran1 == para->bddmgr->bddZero())
                  newy += succ1;  // succ1 \models \phi
                else    // put the next state in the stack
                  tmpresult.push_back(new BDD(succ1));

                idbdd->insert(pair < int, BDD * >(++scount, to));
                statekeys[strkey] = scount;
                desctr.
                  push_back(new
                            transition(from, from_index, to, scount,
                                       &oneaction));
                desc.push_back(scount);
              } else {
                desctr.
                  push_back(new
                            transition(from, from_index, to, gi->second,
                                       &oneaction));
                desc.push_back(gi->second);
              }
              countex->push_back(new vector< int >(desc));

              cextr->push_back(new vector< transition * >(desctr));
              desc.pop_back();
              desctr.pop_back();
            } while (allactions != para->bddmgr->bddZero());
            desc.pop_back();
          }
          Y = newy;
        }
        if (options["atlcex"] == 2) {
          for (unsigned int i = 0; i < tmpresult.size(); i++) {
            string strkey = state_to_str(*tmpresult[i], *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            modal_formula nphi(3,
                               (modal_formula *) (argument->
                                                  get_operand(1)));
            nphi.build_cex(tmpresult[i], gi->second, para);
          }
        }

        return true;
      } else {    // ATLU
        BDD p =
          ((modal_formula *) (argument->get_operand(1)))->
          check_formula(para);
        BDD q =
          ((modal_formula *) (argument->get_operand(2)))->
          check_formula(para);
        BDD pq = p + q;
        BDD pq1 = pq.SwapVariables(*para->v, *para->pv);
        tmpresult.push_back(state);
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
        if (*state * p == para->bddmgr->bddZero()) {
          if (options["atlcex"] == 2) {
            modal_formula nphi(3,
                               (modal_formula *) (argument->
                                                  get_operand(1)));
            nphi.build_cex(state, index, para);
          }
          return true;
        }
        map< string, int >statekeys;
        string strkey = state_to_str(*tmpresult[0], *para->v);
        statekeys[strkey] = index;

        BDD last = argument->check_formula(para); // the last state of fixpoint computation    

        BDD atltree = *state;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        while (Y != para->bddmgr->bddZero()) {
          BDD tmpy = Y;
          BDD newy = para->bddmgr->bddZero();

          // get all successor states
          while (tmpy != para->bddmgr->bddZero()) {
            BDD predecessor = tmpy.PickOneMinterm(*para->v);
            tmpy -= predecessor;
            BDD *from = new BDD(predecessor);
            strkey = state_to_str(predecessor, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            if (gi == statekeys.end()) {
              cout << "  ATLU counterexample - cannot find state: " <<
                strkey << endl;
              exit(0);
            }
            int from_index = gi->second;
            desc.push_back(from_index);

            BDD successors = predecessor;
            for (unsigned int i = 0; i < agents->size(); i++)
              successors *= (*para->vRT)[i];

            BDD allactions = Exists(para->bddmgr, para->pv, successors);
            allactions = Exists(para->bddmgr, para->v, allactions);
            allactions = allactions.ExistAbstract(actagtout);

            // get successors that do not satisfy operator[1], i.e., \phi in <name>X \phi
            BDD bad_succ = successors - pq1;  // \not p \and \not q
            BDD bad_succ1 = successors - lastprime; // \not ATL( p U q)
            do {
              BDD oneaction = allactions.PickOneMinterm(*para->a);

              BDD onetran = oneaction.ExistAbstract(actagtout);
              allactions = allactions - onetran;
              BDD onetran1 = onetran * bad_succ;
              if (onetran1 == para->bddmgr->bddZero())
                onetran = onetran * bad_succ1;
              else
                onetran = onetran1;

              BDD successor = onetran.PickOneMinterm(*para->pv);
              BDD succ1 = successor.SwapVariables(*para->v, *para->pv);
              oneaction = (onetran * successor).PickOneMinterm(*para->a);

              // get the set of actions
              BDD *to = new BDD(succ1);
              strkey = state_to_str(succ1, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                if (onetran1 == para->bddmgr->bddZero())
                  newy += succ1;  // succ1 \models \phi
                else    // put the next state in the stack
                  tmpresult.push_back(new BDD(succ1));

                idbdd->insert(pair < int, BDD * >(++scount, to));
                statekeys[strkey] = scount;
                desctr.
                  push_back(new
                            transition(from, from_index, to, scount,
                                       &oneaction));
                desc.push_back(scount);
              } else {
                desctr.
                  push_back(new
                            transition(from, from_index, to, gi->second,
                                       &oneaction));
                desc.push_back(gi->second);
              }
              countex->push_back(new vector< int >(desc));

              cextr->push_back(new vector< transition * >(desctr));
              desc.pop_back();
              desctr.pop_back();
            } while (allactions != para->bddmgr->bddZero());
            desc.pop_back();
          }
          Y = newy;
        }
        if (options["atlcex"] == 2) {
          for (unsigned int i = 0; i < tmpresult.size(); i++) {
            string strkey = state_to_str(*tmpresult[i], *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            modal_formula nphi(3,
                               (modal_formula *) (argument->
                                                  get_operand(2)));
            nphi.build_cex(tmpresult[i], gi->second, para);
          }
        }

        return true;
      }
    }
  }
  default:
    {
      if (options["quiet"] == 0)
        cout << " OPERATOR CURRENTLY NOT SUPPORTED IN WITNESS/COUNTEREXAMPLE";
      return false;
    }
  }
  if (options["quiet"] == 0)
    cout <<
      " AN ERROR HAS OCCURREND IN THE GENERATION OF WITNESS/COUNTEREXAMPLE";
  return false;

}

bool
modal_formula::build_cex_fair(BDD * state, unsigned int index, BDD fair_reach,
                              bdd_parameters * para)
{

  vector< BDD * >tmpresult; // a vector to store the states of the witness
  vector< int >desc;    // This is a vector of state id (see global variables countex and idbdd)
  vector< transition * >desctr; // This is a vector of transitions (see golbal var cextr)

  Object *id;
  string name;

  BDD actagtin = para->bddmgr->bddOne();  // Actions of agents in group
  BDD actagtout = para->bddmgr->bddOne(); // Actions of agents NOT in group
  if (op == 45 || op == 46 || op == 47 || op == 48) {
    int begin, end;
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    map< string, set< string > >::iterator gi = is_groups->find(name);
    set< string > names_g = gi->second; // the list of agt names in groups

    for (map< string, basic_agent * >::iterator i = is_agents->begin();
         i != is_agents->end(); i++) {
      begin = i->second->get_action_index_begin();
      end = i->second->get_action_index_end();
      if (names_g.find(i->first) == names_g.end())
        for (int j = begin; j <= end; j++)
          actagtout = actagtout * (*para->a)[j];
      else
        for (int j = begin; j <= end; j++)
          actagtin = actagtin * (*para->a)[j];
    }
  }

  switch (op) {
  case 1:     // AND
    {
      bool r1 =
        ((modal_formula *) obj[0])->build_cex_fair(state, index, fair_reach,
                                                   para);
      if (!r1)
        return false;
      bool r2 =
        ((modal_formula *) obj[1])->build_cex_fair(state, index, fair_reach,
                                                   para);
      if (!r2)
        return false;
      return true;
      break;
    }
  case 2:     // OR
    {
      bool r1;
      modal_formula *left = ((modal_formula *) obj[1]);
      BDD *res = new BDD();
      (*res) = left->check_formula_fair(para, fair_reach);

      if ((*state) <= (*res)) {
        r1 = left->build_cex_fair(state, index, fair_reach, para);
        if (!r1)
          return false;
      } else {
        modal_formula *right = ((modal_formula *) obj[0]);
        r1 = right->build_cex_fair(state, index, fair_reach, para);
      }
      return r1;
      break;
    }
  case 11:      // EG 
    {
      // Need to find a cycle here

      BDD last = check_formula_fair(para, fair_reach);  // the last state of fixpoint computation

      if (!(*state <= last))
        return false;

      tmpresult.push_back(new BDD(*state));

      vector< BDD * >S; // a vector to store the stages of the computation

      int j = 0;

      BDD Q = para->bddmgr->bddZero();
      BDD T = para->bddmgr->bddZero() + *state;

      while (Q == para->bddmgr->bddZero()) {

        j++;

        BDD reachablefromlast =
          timesRT(tmpresult[j - 1], para->bddmgr, para->vRT, para->a);

        reachablefromlast = Exists(para->bddmgr, para->v, reachablefromlast);
        reachablefromlast =
          reachablefromlast.SwapVariables(*para->v, *para->pv);

        BDD abdd = reachablefromlast * last;
        if (abdd == para->bddmgr->bddZero()) {
          return false;
        }

        Q = abdd * T;   // if this is not false, we found a loop
        if (Q == para->bddmgr->bddZero()) {
          BDD curstate = abdd.PickOneMinterm(*para->v);

          tmpresult.push_back(new BDD(curstate));

          T = T + curstate;
        } else {
          break;
        }
      }

      unsigned int numberofstates = (unsigned int) tmpresult.size() - 1;  // (the last one is NOT repeated)

      int loopstart = -1; // the position where the loop starts

      for (unsigned int acounter = 0; acounter <= numberofstates; acounter++) {
        if ((Q * (*tmpresult[acounter])) != para->bddmgr->bddZero()) {
          loopstart = acounter;
          break;
        }
      }

      if (loopstart == -1) {
        if (options["quiet"] == 0) {
          cout << "Witness generation for EG:" << endl;
          cout << "THERE IS A PROBLEM HERE, PLEASE REPORT THIS ERROR" << endl;
        }
        return false;
      }
      // building transitions
      // first go to the last loop state
      int position1 = scount;
      for (unsigned int acounter = 0; acounter < numberofstates; acounter++) {
        BDD *from = new BDD(*tmpresult[acounter]);
        BDD *to = new BDD(*tmpresult[acounter + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD actions = timesTrans(from, to, para->vRT);
        actions = Exists(para->bddmgr, para->v, actions);
        actions = Exists(para->bddmgr, para->pv, actions);
        BDD action = actions.PickOneMinterm(*para->a);
        if (acounter == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[acounter])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[acounter])));
          desc.push_back(scount++);
        }
      }

      // Now add the loop back

      BDD *from = new BDD(*tmpresult[numberofstates]);
      BDD *to = new BDD(*tmpresult[loopstart]);
      (*to) = to->SwapVariables(*para->v, *para->pv);
      BDD actions = timesTrans(from, to, para->vRT);
      actions = Exists(para->bddmgr, para->v, actions);
      actions = Exists(para->bddmgr, para->pv, actions);
      BDD action = actions.PickOneMinterm(*para->a);

      if (loopstart == 0) {
        if (numberofstates == 0) {
          desctr.push_back(new transition(from, index, to, index, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));

          desc.push_back(index);
        } else {
          desctr.push_back(new transition(from, scount, to, index, &action));
          idbdd->insert(pair < int,
                        BDD * >(scount, (tmpresult[numberofstates])));

          desc.push_back(scount);
        }
        desc.push_back(index);
      } else {
        int loopposition = position1 + loopstart;
        desctr.
          push_back(new transition(from, scount, to, loopposition, &action));

        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[numberofstates])));
        desc.push_back(scount);
        desc.push_back(loopposition);
      }
      countex->push_back(new vector< int >(desc));

      cextr->push_back(new vector< transition * >(desctr));

      // Print witness for all states in the path

      for (vector< BDD * >::iterator tmpri = tmpresult.begin();
           tmpri != tmpresult.end(); tmpri++) {
        if ((*(*tmpri)) <=
            ((modal_formula *) obj[0])->check_formula_fair(para,
                                                           fair_reach)) {
          if (tmpri == tmpresult.begin())
            ((modal_formula *) obj[0])->build_cex_fair(*tmpri, index,
                                                       fair_reach, para);
          else
            ((modal_formula *) obj[0])->build_cex_fair(*tmpri, ++position1,
                                                       fair_reach, para);
        }
      }
      return true;

    }
  case 13:      // EX
    {
      tmpresult.push_back(state);

      vector< BDD * >S; // a vector to store the stages of the fixpoint computation

      BDD p =
        ((modal_formula *) obj[0])->check_formula_fair(para, fair_reach);

      p = p.SwapVariables(*para->pv, *para->v); // The set of "next" states where p is true.

      BDD aset1 = timesRT(state, para->bddmgr, para->vRT, para->a); // the set of states reachable from "state"

      aset1 = aset1 * p;  // the set above where, additionally, p holds
      if (aset1 == para->bddmgr->bddZero())
        return false;

      aset1 = aset1.SwapVariables(*para->v, *para->pv); // swap back

      BDD curstate = aset1.PickOneMinterm(*para->v);
      tmpresult.push_back(new BDD(curstate));

      // Now populate the table with id -> BDD

      BDD *from = new BDD(*tmpresult[0]);
      BDD *to = new BDD(*tmpresult[1]);
      (*to) = to->SwapVariables(*para->v, *para->pv);
      BDD actions = timesTrans(from, to, para->vRT);
      actions = Exists(para->bddmgr, para->v, actions);
      actions = Exists(para->bddmgr, para->pv, actions);
      BDD action = actions.PickOneMinterm(*para->a);
      desctr.push_back(new transition(from, index, to, scount + 1, &action));
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      desc.push_back(index);
      desc.push_back(++scount);
      countex->push_back(new vector< int >(desc));
      idbdd->insert(pair < int, BDD * >(scount, (tmpresult[1])));
      cextr->push_back(new vector< transition * >(desctr));

      if (((modal_formula *) obj[0])->
          build_cex_fair(tmpresult[1], scount, fair_reach, para)) {
        return true;
      } else {
        return false;
      }

    }
  case 15:      // EF
    {
      vector< BDD * >S; // a vector to store the stages of the fixpoint computation

      BDD p =
        ((modal_formula *) obj[0])->check_formula_fair(para, fair_reach);
      BDD tmp = para->bddmgr->bddOne();
      BDD q = p;
      BDD curstate = para->bddmgr->bddOne();  // the current state

      int n = 0;

      do {
        S.push_back(new BDD(q * fair_reach));
        tmp = q;
        q = p + check_EX_fair(tmp, fair_reach, para);
        n++;
      } while (q != tmp);

      int j = 0;

      while (!(curstate <= (*(S[0])))) {
        BDD aset1;
        if (j == 0) {
          aset1 = (*state);
        } else {
          aset1 =
            Exists(para->bddmgr, para->v,
                   timesRT(&curstate, para->bddmgr, para->vRT, para->a));
          aset1 = aset1.SwapVariables(*para->v, *para->pv);
        }
        BDD aset2 = aset1 * (*(S[n - j - 1]));

        if (aset2 == para->bddmgr->bddZero()) {
          return false;
        }
        curstate = aset2.PickOneMinterm(*para->v);
        tmpresult.push_back(new BDD(curstate));

        j++;

      }

      // building transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD *from = new BDD(*tmpresult[i]);
        BDD *to = new BDD(*tmpresult[i + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD actions = timesTrans(from, to, para->vRT);
        actions = Exists(para->bddmgr, para->v, actions);
        actions = Exists(para->bddmgr, para->pv, actions);
        BDD action = actions.PickOneMinterm(*para->a);
        if (i == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }
      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));
        cextr->push_back(new vector< transition * >(desctr));
      }

      return ((modal_formula *) obj[0])->
        build_cex_fair(tmpresult[tmpresult.size() - 1],
                       (tmpresult.size() == 1 ? index : scount), fair_reach,
                       para);

    }
  case 17:      // EU
    {
      vector< BDD * >S; // a vector to store the stages of the fixpoint computation

      BDD p =
        ((modal_formula *) obj[0])->check_formula_fair(para, fair_reach);
      BDD q =
        ((modal_formula *) obj[1])->check_formula_fair(para, fair_reach);

      if (!(*state <= p || *state <= q))
        return false;

      BDD tmp1 = para->bddmgr->bddOne();
      BDD curstate = para->bddmgr->bddOne();  // the current state

      int n = 0;

      BDD tmp2 = q;
      while (tmp1 != tmp2) {
        tmp1 = tmp2;
        tmp2 =
          tmp2 + (p * check_EX_fair(tmp2, fair_reach, para) * fair_reach);
        S.push_back(new BDD(tmp1));
        n++;
      }

      int j = 0;

      while (!(curstate <= (*(S[0])))) {
        BDD aset1;
        if (j == 0) {
          aset1 = (*state);
        } else {
          aset1 =
            Exists(para->bddmgr, para->v,
                   timesRT(&curstate, para->bddmgr, para->vRT, para->a));
          aset1 = aset1.SwapVariables(*para->v, *para->pv);
        }
        BDD aset2 = aset1 * (*(S[n - j - 1]));

        if (aset2 == para->bddmgr->bddZero()) {
          return false;
        }
        curstate = aset2.PickOneMinterm(*para->v);

        tmpresult.push_back(new BDD(curstate));

        j++;

      }

      int position1 = scount;

      // transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD *from = new BDD(*tmpresult[i]);
        BDD *to = new BDD(*tmpresult[i + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD actions = timesTrans(from, to, para->vRT);
        actions = Exists(para->bddmgr, para->v, actions);
        actions = Exists(para->bddmgr, para->pv, actions);
        BDD action = actions.PickOneMinterm(*para->a);
        if (i == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }
      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));

        cextr->push_back(new vector< transition * >(desctr));
      }

      for (unsigned int i = 0; i < tmpresult.size() - 1; i++) {
        if ((*tmpresult[i]) <=
            ((modal_formula *) obj[0])->check_formula_fair(para,
                                                           fair_reach)) {
          if (i == 0)
            ((modal_formula *) obj[0])->build_cex_fair(tmpresult[i], index,
                                                       fair_reach, para);
          else
            ((modal_formula *) obj[0])->build_cex_fair(tmpresult[i],
                                                       ++position1,
                                                       fair_reach, para);
        }
      }
      return ((modal_formula *) obj[1])->
        build_cex_fair(tmpresult[tmpresult.size() - 1],
                       (tmpresult.size() == 1 ? index : scount), fair_reach,
                       para);
    }

  case 45:{     // ATLX witness
    BDD p =
      ((modal_formula *) obj[1])->check_formula_fair(para, fair_reach);

    tmpresult.push_back(state);

    // get all successor states
    BDD successors = *state;
    for (unsigned int i = 0; i < agents->size(); i++)
      successors = successors * (*para->vRT)[i];

    // get successors that do not satisfy operator[1], i.e., \phi in <name>X \phi
    p = p.SwapVariables(*para->v, *para->pv);
    BDD bad_succ = successors - p;

    // get actions that cannot force the system move the successors that satisfy \phi
    BDD bad_actions = bad_succ.ExistAbstract(actagtout);
    bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
    bad_actions = Exists(para->bddmgr, para->v, bad_actions);

    // get successors that satisfy \phi
    BDD good_succ = successors * p;

    // remove successors that are reached by bad actions
    good_succ = good_succ - (good_succ * bad_actions);
    if (good_succ == para->bddmgr->bddZero())
      return false;
    BDD good_succ_tran = good_succ;
    good_succ = Exists(para->bddmgr, para->v, good_succ);

    // get one successor that reached by good actions
    BDD nextstate = Exists(para->bddmgr, para->a, good_succ);

    if (options["fullatl"] == 0) {
      nextstate = nextstate.PickOneMinterm(*para->pv);

      // get the set of actions
      BDD action =
        Exists(para->bddmgr, para->pv,
               good_succ * nextstate).PickOneMinterm(*para->a);

      // put the next state in the stack
      tmpresult.
        push_back(new BDD(nextstate.SwapVariables(*para->v, *para->pv)));

      BDD *from = new BDD(*tmpresult[0]);
      BDD *to = new BDD(*tmpresult[1]);
      (*to) = to->SwapVariables(*para->v, *para->pv);
      desctr.
        push_back(new transition(from, index, to, scount + 1, &action));
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      desc.push_back(index);
      desc.push_back(++scount);
      countex->push_back(new vector< int >(desc));
      idbdd->insert(pair < int, BDD * >(scount, (tmpresult[1])));
      cextr->push_back(new vector< transition * >(desctr));
      return ((modal_formula *) obj[1])->build_cex_fair(tmpresult[1],
                                                        scount, fair_reach,
                                                        para);
    } else {
      map< string, int >statekeys;

      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);
      statekeys[strkey] = index;

      desc.push_back(index);

      if (options["fullatl"] >= 3) {
        BDD pvstate = state->SwapVariables(*para->v, *para->pv);
        BDD YY = good_succ_tran;
        if (options["atlnewstate"] == 1) {
          BDD tmpYY = good_succ_tran - pvstate;
          if (tmpYY != para->bddmgr->bddZero())
            YY = tmpYY;
        }
        BDD tmpaction = YY.PickOneMinterm(*para->a);
        tmpaction = Exists(para->bddmgr, para->v, tmpaction);
        tmpaction = Exists(para->bddmgr, para->pv, tmpaction);
        tmpaction = tmpaction.ExistAbstract(actagtout);
        good_succ_tran = good_succ_tran * tmpaction;
        good_succ = Exists(para->bddmgr, para->v, good_succ_tran);
        nextstate = Exists(para->bddmgr, para->a, good_succ);
      }

      do {
        BDD successor = nextstate.PickOneMinterm(*para->pv);
        nextstate = nextstate - successor;

        // put the next state in the stack
        tmpresult.
          push_back(new BDD(successor.SwapVariables(*para->v, *para->pv)));

        // get the set of actions
        BDD action = Exists(para->bddmgr, para->pv, good_succ * successor);

        do {
          BDD oneaction = action.PickOneMinterm(*para->a);
          action = action - oneaction;
          BDD *from = new BDD(*tmpresult[0]);
          BDD *to = new BDD(*tmpresult[tmpresult.size() - 1]);
          (*to) = to->SwapVariables(*para->v, *para->pv);
          strkey = state_to_str(*tmpresult[tmpresult.size() - 1], *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          if (gi == statekeys.end()) {
            idbdd->insert(pair < int,
                          BDD * >(++scount,
                                  (tmpresult[tmpresult.size() - 1])));
            statekeys[strkey] = scount;
            desctr.
              push_back(new
                        transition(from, index, to, scount, &oneaction));
            desc.push_back(scount);
          } else {
            desctr.
              push_back(new
                        transition(from, index, to, gi->second,
                                   &oneaction));
            desc.push_back(gi->second);
          }
          countex->push_back(new vector< int >(desc));

          cextr->push_back(new vector< transition * >(desctr));
          desc.pop_back();
          desctr.pop_back();
        } while (action != para->bddmgr->bddZero());
      } while (nextstate != para->bddmgr->bddZero());
      if (options["fullatl"] % 2 == 0) {
        for (unsigned int i = 1; i < tmpresult.size(); i++) {
          string strkey = state_to_str(*tmpresult[i], *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          ((modal_formula *) obj[1])->build_cex_fair(tmpresult[i],  /* ++position1 */
                                                     gi->second, fair_reach,
                                                     para);
        }
      }

      return true;
    }
  }

  case 46:{     // ATL operator F
    vector< BDD * >S; // a vector to store the stages of the fixpoint computation
    BDD p =
      ((modal_formula *) obj[1])->check_formula_fair(para, fair_reach);
    BDD tmp = para->bddmgr->bddOne();
    BDD q = p;
    BDD curstate = *state;  // the current state
    vector< BDD * >tmp_actions;

    if (options["fullatl"] > 0) {
      BDD last = check_formula_fair(para, fair_reach);  // the last state of fixpoint computation
      tmpresult.push_back(new BDD(*state));
      map< string, int >statekeys;
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);

      statekeys[strkey] = index;
      if (*tmpresult[0] * p == para->bddmgr->bddZero()) {
        BDD atltree = *state;
        if (atltree * last == para->bddmgr->bddZero())
          return false;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        BDD paststate;
        if (options["atlnewstate"] == 1)
          paststate = para->bddmgr->bddZero();  // store states that have been visited

        while (Y != para->bddmgr->bddZero()) {
          // Compute all successors
          for (unsigned int i = 0; i < agents->size(); i++)
            Y = Y * (*para->vRT)[i];
          // Compute successors that do not satisfy the ATLG formula
          BDD badstates = Y * (!lastprime);

          // Remove successor states; keep actions and source states only
          badstates = Exists(para->bddmgr, para->pv, badstates);
          badstates = badstates * (*para->reach);

          // Pick up bad actions executed by the opponents
          badstates = badstates.ExistAbstract(actagtout);
          // Pick up successors that either do not satisfy the ATLG formula or cannot reached by any strategy
          Y = Y - badstates;

          // keep only one strategy
          if (options["fullatl"] >= 3) {
            BDD allsources = Exists(para->bddmgr, para->a, Y);
            allsources = Exists(para->bddmgr, para->pv, allsources);
            BDD missed = allsources;
            BDD YY = para->bddmgr->bddZero();
            while (missed != para->bddmgr->bddZero()) {
              BDD source = missed.PickOneMinterm(*para->v);
              BDD trans = source * Y;
              if (options["atlnewstate"] == 1) {
                BDD sourcetarget =
                  source.SwapVariables(*para->v, *para->pv);
                paststate += sourcetarget;
                BDD newtrans = trans - paststate;
                if (newtrans != para->bddmgr->bddZero())
                  trans = newtrans;
              }
              BDD strategy = trans.PickOneMinterm(*para->a);
              strategy = strategy.ExistAbstract(actagtout);
              strategy = Y * strategy;
              YY += strategy;
              BDD heads = Exists(para->bddmgr, para->a, strategy);
              heads = Exists(para->bddmgr, para->pv, heads);
              missed = missed - heads;
            }
            Y = YY;
          }

          BDD Y1 = Exists(para->bddmgr, para->v, Y);
          Y1 = Exists(para->bddmgr, para->a, Y1);

          // Now we need to store the actions
          BDD nextstate = Y1;
          BDD good_succ = Y;
          do {
            BDD successor = nextstate.PickOneMinterm(*para->pv);
            nextstate = nextstate - successor;
            BDD *to = new BDD(successor);
            (*to) = to->SwapVariables(*para->v, *para->pv);
            strkey = state_to_str(*to, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            int to_index;
            if (gi == statekeys.end()) {
              idbdd->insert(pair < int, BDD * >(++scount, to));
              statekeys[strkey] = scount;
              // put the next state in the stack
              tmpresult.push_back(to);
              to_index = scount;
            } else
              to_index = gi->second;

            // compute all predecessors that have the selected successor
            BDD predecessors = good_succ * successor;
            do {
              BDD predecessor = predecessors.PickOneMinterm(*para->v);
              predecessors = predecessors - predecessor;
              BDD *from = new BDD(predecessor);
              strkey = state_to_str(predecessor, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                cout << "  cannot find state: " << strkey << endl;
                exit(0);
              }
              int from_index = gi->second;
              desc.push_back(from_index);

              // get the set of actions
              BDD action =
                Exists(para->bddmgr, para->pv,
                       good_succ * successor * predecessor);
              action = Exists(para->bddmgr, para->v, action);
              do {
                BDD oneaction = action.PickOneMinterm(*para->a);
                action = action - oneaction;

                desctr.
                  push_back(new
                            transition(from, from_index, to, to_index,
                                       &oneaction));
                cextr->push_back(new vector< transition * >(desctr));
                desctr.pop_back();
              } while (action != para->bddmgr->bddZero());
              desc.push_back(to_index);
              countex->push_back(new vector< int >(desc));
              desc.pop_back();
              desc.pop_back();
            } while (predecessors != para->bddmgr->bddZero());
          } while (nextstate != para->bddmgr->bddZero());

          // move the frontier to the good successors
          Y = Y1;
          Y = Y.SwapVariables(*para->v, *para->pv);
          Y = Y - atltree;
          atltree += Y;
          Y -= p;
        }
      }
      // Generate tree for every state in the atl tree
      if (options["fullatl"] % 2 == 0) {
        for (vector< BDD * >::iterator tmpri = tmpresult.begin();
             tmpri != tmpresult.end(); tmpri++) {
          string strkey = state_to_str(*(*tmpri), *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          if (**tmpri * p != para->bddmgr->bddZero())
            ((modal_formula *) obj[1])->build_cex_fair(*tmpri, gi->second,
                                                       fair_reach, para);
        }
      }
      return true;
    } else {
      int n = 0, j = 0;
      S.push_back(new BDD(q));
      while (*state * q == para->bddmgr->bddZero()) {
        q = check_ATLX(q, name, para);
        S.push_back(new BDD(q));
        n++;
      }

      while (j <= n) {
        BDD aset1;
        BDD good_succ = para->bddmgr->bddZero();
        if (j == 0) {
          aset1 = (*state);
        } else {
          tmp = curstate;
          for (unsigned int i = 0; i < agents->size(); i++)
            tmp = tmp * (*para->vRT)[i];
          BDD pq = S[n - j]->SwapVariables(*para->v, *para->pv);
          BDD bad_succ = tmp - pq;
          BDD bad_actions = bad_succ.ExistAbstract(actagtout);
          bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
          bad_actions = Exists(para->bddmgr, para->v, bad_actions);
          good_succ = tmp * pq;
          good_succ = good_succ - (good_succ * bad_actions);
          good_succ =
            Exists(para->bddmgr, para->v, good_succ).SwapVariables(*para->v,
                                                                   *para->
                                                                   pv);
          aset1 = Exists(para->bddmgr, para->a, good_succ);
        }
        if (aset1 == para->bddmgr->bddZero())
          return false;
        curstate = aset1.PickOneMinterm(*para->v);
        tmpresult.push_back(new BDD(curstate));
        if (j > 0) {
          BDD action =
            Exists(para->bddmgr, para->v,
                   good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(new BDD(action));
        }
        j++;
      }

      // building transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD *from = new BDD(*tmpresult[i]);
        BDD *to = new BDD(*tmpresult[i + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD *action = tmp_actions[i];
        if (i == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }

      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));
        cextr->push_back(new vector< transition * >(desctr));
      }

      return ((modal_formula *) obj[1])->
        build_cex_fair(tmpresult[tmpresult.size() - 1],
                       (tmpresult.size() == 1 ? index : scount), fair_reach,
                       para);
    }
  }

  case 47:{     // ATL operator G
    BDD p =
      ((modal_formula *) obj[1])->check_formula_fair(para, fair_reach);
    p = p.SwapVariables(*para->v, *para->pv);
    BDD last = check_formula_fair(para, fair_reach);  // the last state of fixpoint computation
    tmpresult.push_back(new BDD(*state));
    vector< BDD * >tmp_actions;

    if (options["fullatl"] > 0) {
      map< string, int >statekeys;
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);

      statekeys[strkey] = index;
      BDD atltree = *state;
      if (atltree * last == para->bddmgr->bddZero())
        return false;
      BDD Y = atltree;
      BDD lastprime = last.SwapVariables(*para->v, *para->pv);
      BDD paststate;
      if (options["atlnewstate"] == 1)
        paststate = para->bddmgr->bddZero();  // store states that have been visited
      while (Y != para->bddmgr->bddZero()) {
        // Compute all successors
        for (unsigned int i = 0; i < agents->size(); i++)
          Y = Y * (*para->vRT)[i];
        // Compute successors that do not satisfy the ATLG formula
        BDD badstates = Y * (!lastprime);

        // Remove successor states; keep actions and source states only
        badstates = Exists(para->bddmgr, para->pv, badstates);
        badstates = badstates * (*para->reach);

        // Pick up bad actions executed by the opponents
        badstates = badstates.ExistAbstract(actagtout);
        // Pick up successors that either do not satisfy the ATLG formula or cannot reached by any strategy
        Y = Y - badstates;

        // keep only one strategy
        if (options["fullatl"] >= 3) {
          BDD allsources = Exists(para->bddmgr, para->a, Y);
          allsources = Exists(para->bddmgr, para->pv, allsources);
          BDD missed = allsources;
          BDD YY = para->bddmgr->bddZero();
          while (missed != para->bddmgr->bddZero()) {
            BDD source = missed.PickOneMinterm(*para->v);
            BDD trans = source * Y;
            if (options["atlnewstate"] == 1) {
              BDD sourcetarget = source.SwapVariables(*para->v, *para->pv);
              paststate += sourcetarget;
              BDD newtrans = trans - paststate;
              if (newtrans != para->bddmgr->bddZero())
                trans = newtrans;
            }
            BDD strategy = trans.PickOneMinterm(*para->a);
            strategy = strategy.ExistAbstract(actagtout);
            strategy = Y * strategy;
            YY += strategy;
            BDD heads = Exists(para->bddmgr, para->a, strategy);
            heads = Exists(para->bddmgr, para->pv, heads);
            missed = missed - heads;
          }
          Y = YY;
        }

        BDD Y1 = Exists(para->bddmgr, para->v, Y);
        Y1 = Exists(para->bddmgr, para->a, Y1);

        // Now we need to store the actions
        BDD nextstate = Y1;
        BDD good_succ = Y;
        do {
          BDD successor = nextstate.PickOneMinterm(*para->pv);
          nextstate = nextstate - successor;
          BDD *to = new BDD(successor);
          (*to) = to->SwapVariables(*para->v, *para->pv);
          strkey = state_to_str(*to, *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          int to_index;
          if (gi == statekeys.end()) {
            idbdd->insert(pair < int, BDD * >(++scount, to));
            statekeys[strkey] = scount;
            // put the next state in the stack
            tmpresult.push_back(to);
            to_index = scount;
          } else
            to_index = gi->second;

          // compute all predecessors that have the selected successor
          BDD predecessors = good_succ * successor;
          do {
            BDD predecessor = predecessors.PickOneMinterm(*para->v);
            predecessors = predecessors - predecessor;
            BDD *from = new BDD(predecessor);
            strkey = state_to_str(predecessor, *para->v);
            gi = statekeys.find(strkey);
            if (gi == statekeys.end()) {
              cout << "  cannot find state: " << strkey << endl;
              exit(0);
            }
            int from_index = gi->second;
            desc.push_back(from_index);

            // get the set of actions
            BDD action =
              Exists(para->bddmgr, para->pv,
                     good_succ * successor * predecessor);
            action = Exists(para->bddmgr, para->v, action);
            do {
              BDD oneaction = action.PickOneMinterm(*para->a);
              action = action - oneaction;

              desctr.
                push_back(new
                          transition(from, from_index, to, to_index,
                                     &oneaction));
              cextr->push_back(new vector< transition * >(desctr));
              desctr.pop_back();
            } while (action != para->bddmgr->bddZero());
            desc.push_back(to_index);
            countex->push_back(new vector< int >(desc));
            desc.pop_back();
            desc.pop_back();
          } while (predecessors != para->bddmgr->bddZero());
        } while (nextstate != para->bddmgr->bddZero());

        // move the frontier to the good successors
        Y = Y1;
        Y = Y.SwapVariables(*para->v, *para->pv);
        Y = Y - atltree;
        atltree += Y;
      }
      // Generate tree for every state in the atl tree
      if (options["fullatl"] % 2 == 0) {
        for (vector< BDD * >::iterator tmpri = tmpresult.begin();
             tmpri != tmpresult.end(); tmpri++) {
          string strkey = state_to_str(*(*tmpri), *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          ((modal_formula *) obj[1])->build_cex_fair(*tmpri, gi->second,
                                                     fair_reach, para);
        }
      }
      return true;
    } else {
      vector< BDD * >S; // a vector to store the stages of the computation
      int j = 0;
      BDD Q = para->bddmgr->bddZero();
      BDD T = *state;
      while (Q == para->bddmgr->bddZero()) {
        j++;
        BDD reachablefromlast = *tmpresult[j - 1];
        for (unsigned int i = 0; i < agents->size(); i++)
          reachablefromlast = reachablefromlast * (*para->vRT)[i];
        // copied from ATLX case
        BDD bad_succ = reachablefromlast - p;
        BDD bad_actions = bad_succ.ExistAbstract(actagtout);
        bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
        bad_actions = Exists(para->bddmgr, para->v, bad_actions);
        BDD good_succ = reachablefromlast * p;
        good_succ = good_succ - (good_succ * bad_actions);
        good_succ =
          Exists(para->bddmgr, para->v, good_succ).SwapVariables(*para->v,
                                                                 *para->pv);
        reachablefromlast = Exists(para->bddmgr, para->a, good_succ);

        BDD abdd = reachablefromlast * last;
        if (abdd == para->bddmgr->bddZero())
          return false;

        Q = abdd * T;   // if this is not false, we found a loop
        if (Q == para->bddmgr->bddZero()) {
          BDD curstate = abdd.PickOneMinterm(*para->v);
          tmpresult.push_back(new BDD(curstate));
          BDD action =
            Exists(para->bddmgr, para->v,
                   good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(new BDD(action));
          T = T + curstate;
        } else {
          BDD curstate = Q.PickOneMinterm(*para->v);
          BDD action =
            Exists(para->bddmgr, para->v,
                   good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(new BDD(action));
          break;
        }
      }
      unsigned int numberofstates = (unsigned int) tmpresult.size() - 1;  // (the last one is NOT repeated)
      int loopstart = -1; // the position where the loop starts
      for (unsigned int acounter = 0; acounter <= numberofstates;
           acounter++) {
        if ((Q * (*tmpresult[acounter])) != para->bddmgr->bddZero()) {
          loopstart = acounter;
          break;
        }
      }

      if (loopstart == -1) {
        if (options["quiet"] == 0) {
          cout << "Witness generation for ATLG:" << endl;
          cout << "THERE IS A PROBLEM HERE, PLEASE REPORT THIS ERROR" <<
            endl;
        }
        return false;
      }
      // building transitions
      // first go to the last loop state
      int position1 = scount;
      for (unsigned int acounter = 0; acounter < numberofstates; acounter++) {
        BDD *from = new BDD(*tmpresult[acounter]);
        BDD *to = new BDD(*tmpresult[acounter + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD *action = tmp_actions[acounter];
        if (acounter == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int,
                          BDD * >(index, (tmpresult[acounter])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[acounter])));
          desc.push_back(scount++);
        }
      }

      // Now add the loop back

      BDD *from = new BDD(*tmpresult[numberofstates]);
      BDD *to = new BDD(*tmpresult[loopstart]);
      (*to) = to->SwapVariables(*para->v, *para->pv);
      BDD *action = tmp_actions[tmp_actions.size() - 1];

      if (loopstart == 0) {
        if (numberofstates == 0) {
          desctr.push_back(new transition(from, index, to, index, action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));

          desc.push_back(index);
        } else {
          desctr.push_back(new transition(from, scount, to, index, action));
          idbdd->insert(pair < int,
                        BDD * >(scount, (tmpresult[numberofstates])));

          desc.push_back(scount);
        }
        desc.push_back(index);
      } else {
        int loopposition = position1 + loopstart;
        desctr.
          push_back(new transition(from, scount, to, loopposition, action));

        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[numberofstates])));
        desc.push_back(scount);
        desc.push_back(loopposition);
      }
      countex->push_back(new vector< int >(desc));

      cextr->push_back(new vector< transition * >(desctr));

      // Print witness for all states in the path
      for (vector< BDD * >::iterator tmpri = tmpresult.begin();
           tmpri != tmpresult.end(); tmpri++) {
        if (tmpri == tmpresult.begin())
          ((modal_formula *) obj[1])->build_cex_fair(*tmpri, index,
                                                     fair_reach, para);
        else
          ((modal_formula *) obj[1])->build_cex_fair(*tmpri, ++position1,
                                                     fair_reach, para);
      }

      return true;
    }
  }

  case 48:{     // ATL operator U
    vector< BDD * >S; // a vector to store the stages of the fixpoint computation
    vector< BDD * >tmp_actions;
    BDD p =
      ((modal_formula *) obj[1])->check_formula_fair(para, fair_reach);
    BDD q =
      ((modal_formula *) obj[2])->check_formula_fair(para, fair_reach);

    if (options["fullatl"] > 0) {
      BDD last = check_formula_fair(para, fair_reach);  // the last state of fixpoint computation
      tmpresult.push_back(new BDD(*state));
      map< string, int >statekeys;
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);

      statekeys[strkey] = index;
      if (*tmpresult[0] * q == para->bddmgr->bddZero()) {
        BDD atltree = *state;
        if (atltree * last == para->bddmgr->bddZero())
          return false;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        BDD paststate;
        if (options["atlnewstate"] == 1)
          paststate = para->bddmgr->bddZero();  // store states that have been visited

        while (Y != para->bddmgr->bddZero()) {
          // Compute all successors
          for (unsigned int i = 0; i < agents->size(); i++)
            Y = Y * (*para->vRT)[i];
          // Compute successors that do not satisfy the ATLG formula
          BDD badstates = Y * (!lastprime);

          // Remove successor states; keep actions and source states only
          badstates = Exists(para->bddmgr, para->pv, badstates);
          badstates = badstates * (*para->reach);

          // Pick up bad actions executed by the opponents
          badstates = badstates.ExistAbstract(actagtout);
          // Pick up successors that either do not satisfy the ATLG formula or cannot reached by any strategy
          Y = Y - badstates;

          // keep only one strategy
          if (options["fullatl"] >= 3) {
            BDD allsources = Exists(para->bddmgr, para->a, Y);
            allsources = Exists(para->bddmgr, para->pv, allsources);
            BDD missed = allsources;
            BDD YY = para->bddmgr->bddZero();
            while (missed != para->bddmgr->bddZero()) {
              BDD source = missed.PickOneMinterm(*para->v);
              BDD trans = source * Y;
              if (options["atlnewstate"] == 1) {
                BDD sourcetarget =
                  source.SwapVariables(*para->v, *para->pv);
                paststate += sourcetarget;
                BDD newtrans = trans - paststate;
                if (newtrans != para->bddmgr->bddZero())
                  trans = newtrans;
              }
              BDD strategy = trans.PickOneMinterm(*para->a);
              strategy = strategy.ExistAbstract(actagtout);
              strategy = Y * strategy;
              YY += strategy;
              BDD heads = Exists(para->bddmgr, para->a, strategy);
              heads = Exists(para->bddmgr, para->pv, heads);
              missed = missed - heads;
            }
            Y = YY;
          }

          BDD Y1 = Exists(para->bddmgr, para->v, Y);
          Y1 = Exists(para->bddmgr, para->a, Y1);

          // Now we need to store the actions
          BDD nextstate = Y1;
          BDD good_succ = Y;
          do {
            BDD successor = nextstate.PickOneMinterm(*para->pv);
            nextstate = nextstate - successor;
            BDD *to = new BDD(successor);
            (*to) = to->SwapVariables(*para->v, *para->pv);
            strkey = state_to_str(*to, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            int to_index;
            if (gi == statekeys.end()) {
              idbdd->insert(pair < int, BDD * >(++scount, to));
              statekeys[strkey] = scount;
              // put the next state in the stack
              tmpresult.push_back(to);
              to_index = scount;
            } else
              to_index = gi->second;

            // compute all predecessors that have the selected successor
            BDD predecessors = good_succ * successor;
            do {
              BDD predecessor = predecessors.PickOneMinterm(*para->v);
              predecessors = predecessors - predecessor;
              BDD *from = new BDD(predecessor);
              strkey = state_to_str(predecessor, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                cout << "  cannot find state: " << strkey << endl;
                exit(0);
              }
              int from_index = gi->second;
              desc.push_back(from_index);

              // get the set of actions
              BDD action =
                Exists(para->bddmgr, para->pv,
                       good_succ * successor * predecessor);
              action = Exists(para->bddmgr, para->v, action);
              do {
                BDD oneaction = action.PickOneMinterm(*para->a);
                action = action - oneaction;

                desctr.
                  push_back(new
                            transition(from, from_index, to, to_index,
                                       &oneaction));
                cextr->push_back(new vector< transition * >(desctr));
                desctr.pop_back();
              } while (action != para->bddmgr->bddZero());
              desc.push_back(to_index);
              countex->push_back(new vector< int >(desc));
              desc.pop_back();
              desc.pop_back();
            } while (predecessors != para->bddmgr->bddZero());
          } while (nextstate != para->bddmgr->bddZero());

          // move the frontier to the good successors
          Y = Y1;
          Y = Y.SwapVariables(*para->v, *para->pv);
          Y = Y - atltree;
          atltree += Y;
          Y -= q;
        }
      }
      // Generate tree for every state in the atl tree
      if (options["fullatl"] % 2 == 0) {
        for (vector< BDD * >::iterator tmpri = tmpresult.begin();
             tmpri != tmpresult.end(); tmpri++) {
          string strkey = state_to_str(*(*tmpri), *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          if (**tmpri * q == para->bddmgr->bddZero())
            ((modal_formula *) obj[1])->build_cex_fair(*tmpri, gi->second,
                                                       fair_reach, para);
          else
            ((modal_formula *) obj[2])->build_cex_fair(*tmpri, gi->second,
                                                       fair_reach, para);
        }
      }
      return true;
    } else {
      BDD tmp1 = q;
      BDD curstate = para->bddmgr->bddOne();  // the current state
      int n = 0, j = 0;
      S.push_back(new BDD(tmp1));
      while (*state * tmp1 == para->bddmgr->bddZero()) {
        tmp1 = check_ATLX(tmp1, name, para) * p;
        S.push_back(new BDD(tmp1));
        n++;
      }
      while (j <= n) {
        BDD aset1;
        BDD good_succ = para->bddmgr->bddZero();
        if (j == 0) {
          aset1 = (*state);
        } else {
          tmp1 = curstate;
          for (unsigned int i = 0; i < agents->size(); i++)
            tmp1 = tmp1 * (*para->vRT)[i];
          BDD pq = S[n - j]->SwapVariables(*para->v, *para->pv);
          BDD bad_succ = tmp1 - pq;
          BDD bad_actions = bad_succ.ExistAbstract(actagtout);
          bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
          bad_actions = Exists(para->bddmgr, para->v, bad_actions);
          good_succ = tmp1 * pq;
          good_succ = good_succ - (good_succ * bad_actions);
          good_succ =
            Exists(para->bddmgr, para->v, good_succ).SwapVariables(*para->v,
                                                                   *para->
                                                                   pv);
          aset1 = Exists(para->bddmgr, para->a, good_succ);
        }
        if (aset1 == para->bddmgr->bddZero())
          return false;
        curstate = aset1.PickOneMinterm(*para->v);
        tmpresult.push_back(new BDD(curstate));
        if (j > 0) {
          BDD action =
            Exists(para->bddmgr, para->v,
                   good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(new BDD(action));
        }
        j++;
      }

      int position1 = scount;

      // transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD *from = new BDD(*tmpresult[i]);
        BDD *to = new BDD(*tmpresult[i + 1]);
        (*to) = to->SwapVariables(*para->v, *para->pv);
        BDD *action = tmp_actions[i];
        if (i == 0) {
          desctr.
            push_back(new transition(from, index, to, ++scount, action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(from, scount, to, scount + 1, action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }
      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));

        cextr->push_back(new vector< transition * >(desctr));
      }

      for (unsigned int i = 0; i < tmpresult.size() - 1; i++) {
        if ((*tmpresult[i]) <=
            ((modal_formula *) obj[1])->check_formula_fair(para,
                                                           fair_reach)) {
          if (i == 0)
            ((modal_formula *) obj[1])->build_cex_fair(tmpresult[i], index,
                                                       fair_reach, para);
          else
            ((modal_formula *) obj[1])->build_cex_fair(tmpresult[i],
                                                       ++position1,
                                                       fair_reach, para);
        }
      }
      return ((modal_formula *) obj[2])->
        build_cex_fair(tmpresult[tmpresult.size() - 1],
                       (tmpresult.size() == 1 ? index : scount), fair_reach,
                       para);
    }
  }

  case 0:
  case 10:      // AG
  case 12:      // AX
  case 14:      // AF
  case 16:      // AU
  case 30:
  case 31:
  case 32:
  case 40:
  case 42:
  case 51:
  case 53:{
    BDD p = check_formula_fair(para, fair_reach);

    if ((*state) <= p) {
      if (idbdd->size() == 0) {
        idbdd->insert(pair < int, BDD * >(index, state));
        desc.push_back(index);
        countex->push_back(new vector< int >(desc));
      }

      return true;
    } else {
      return false;
    }

  }

  case 52: {
    string name, name1;
    Object *id, *id1;
    tmpresult.push_back(state);
    modal_formula *agentid = (modal_formula *) (get_operand(0));		
    id = agentid->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    modal_formula *agentid1 = (modal_formula *) (get_operand(1));		
    id1 = agentid->get_operand(0);
    name1 = ((atomic_proposition *) id1)->get_proposition();
    vector<basictype *> shared;
    get_shared_vars(name, name1, &shared);
    modal_formula *formula = ((modal_formula *) obj[2]);
    BDD p = formula->check_formula_fair(para, fair_reach);
    BDD aset1 = get_eq_states(state, name, name1, &shared, para) * fair_reach;  
    aset1 *= p;
    if (aset1 == para->bddmgr->bddZero())
      return false;
    
    BDD curstate = aset1.PickOneMinterm(*para->v);
    if (curstate == *state) {
      aset1 = aset1 - curstate;
      if (aset1 != para->bddmgr->bddZero())
	curstate = aset1.PickOneMinterm(*para->v);
    }
    tmpresult.push_back(new BDD(curstate));
    
    BDD *from = new BDD(*tmpresult[0]);
    BDD *to = new BDD(*tmpresult[1]);
    (*to) = to->SwapVariables(*para->v, *para->pv);
    BDD action = para->bddmgr->bddOne();
    desctr.push_back(new transition(from, index, to, scount + 1, name, &action));
    if (index >= idbdd->size())
      idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
    desc.push_back(index);
    desc.push_back(++scount);
    countex->push_back(new vector< int >(desc));
    idbdd->insert(pair < int, BDD * >(scount, (tmpresult[1])));
    
    cextr->push_back(new vector< transition * >(desctr));
    return formula->build_cex_fair(tmpresult[1], scount, fair_reach, para);
  }
    // leaf
  case 3:{
    modal_formula *argument = ((modal_formula *) obj[0]);

    if (argument->get_op() == 0) {

      // It's the negation of an atom

      BDD p = check_formula_fair(para, fair_reach);

      if ((*state) <= p) {
        if (idbdd->size() == 0) {
          idbdd->insert(pair < int, BDD * >(index, state));
          desc.push_back(index);
          countex->push_back(new vector< int >(desc));
        }

        return true;
      } else {
        return false;
      }
    } else if (argument->get_op() == 30 || argument->get_op() == 31
               || argument->get_op() == 32 || argument->get_op() == 40
               || argument->get_op() == 42 || argument->get_op() == 51) {
      // it's the negation of K
      tmpresult.push_back(state);

      // Finding the position of the agent:
      string name, name1;
      Object *id, *id1;
      modal_formula *agentid = (modal_formula *) (argument->get_operand(0));
      BDD aset1;
      BDD rel;
      BDD formula;

      if (argument->get_op() == 30) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        aset1 =
          get_K_states(!
                       ((modal_formula *) (argument->
                                           get_operand
                                           (1)))->check_formula_fair(para,
                                                                     fair_reach)
                       * fair_reach, state, name, para);
      } else if (argument->get_op() == 31) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula =
          ((modal_formula *) (argument->
                              get_operand(1)))->check_formula_fair(para,
                                                                   fair_reach);
        aset1 = check_GK_fair(formula, name, fair_reach, para);

        aset1 = !aset1 * !formula * (*para->reach);
        aset1 = get_GK_states(aset1, state, name, para);
      } else if (argument->get_op() == 32) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula =
          ((modal_formula *) (argument->
                              get_operand(1)))->check_formula_fair(para,
                                                                   fair_reach);
        aset1 = !check_GCK_fair(formula, name, fair_reach,
                                para) * (*para->reach);
        aset1 = aset1 * !formula;
        aset1 = get_GK_states(aset1, state, name, para);
      } else if (argument->get_op() == 40) {  // O
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula =
          !((modal_formula *) (argument->
                               get_operand(1)))->check_formula_fair(para,
                                                                    fair_reach)
          * (*para->reach);
        aset1 =
          check_nO_fair(formula, name, fair_reach,
                        para) * (*para->reach);
      } else if (argument->get_op() == 42) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula =
          ((modal_formula *) obj[1])->check_formula_fair(para,
                                                         fair_reach);
        aset1 = check_DK_fair(formula, name, fair_reach, para);

        aset1 = !aset1 * !formula * (*para->reach);
        aset1 = get_DK_states(aset1, state, name, para);
      } else if (argument->get_op() == 51) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
	modal_formula *agentid1 = (modal_formula *) (argument->get_operand(1));        
	id1 = agentid1->get_operand(0);
        name1 = ((atomic_proposition *) id1)->get_proposition();
	vector<basictype *> shared;
	get_shared_vars(name, name1, &shared);
        formula =
          ((modal_formula *) argument->
           get_operand(2))->check_formula_fair(para, fair_reach);
        aset1 = get_eq_states(state, name, name1, &shared, para) * fair_reach;
	aset1 *= build_shared_equivalence(&shared, para);
        aset1 *= (fair_reach - formula);
      }

      if (aset1 == para->bddmgr->bddZero())
        return false;

      BDD curstate = aset1.PickOneMinterm(*para->v);
      tmpresult.push_back(new BDD(curstate));

      BDD *from = new BDD(*tmpresult[0]);
      BDD *to = new BDD(*tmpresult[1]);
      (*to) = to->SwapVariables(*para->v, *para->pv);
      BDD action = para->bddmgr->bddOne();
      if (argument->get_op() == 30 || argument->get_op() == 31
          || argument->get_op() == 32 || argument->get_op() == 42
	  || argument->get_op() == 51)
        desctr.
          push_back(new
                    transition(from, index, to, scount + 1, name, &action));
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      desc.push_back(index);
      desc.push_back(++scount);
      countex->push_back(new vector< int >(desc));
      idbdd->insert(pair < int, BDD * >(scount, (tmpresult[1])));

      cextr->push_back(new vector< transition * >(desctr));
      if (argument->get_op() != 40) {
        modal_formula *fcex;
        if (argument->get_op() == 30 || argument->get_op() == 31
            || argument->get_op() == 40 || argument->get_op() == 32
            || argument->get_op() == 42 || argument->get_op() == 51)
          fcex =
            new modal_formula(3,
                              ((modal_formula *) (argument->
                                                  get_operand(1))));
        else
          fcex =
            new modal_formula(3,
                              ((modal_formula *) (argument->
                                                  get_operand(2))));
        fcex = fcex->push_negations(1);

        return fcex->build_cex_fair(tmpresult[1], scount, fair_reach, para);
      } else
        return true;
    }
  }
  default:
    {
      if (options["quiet"] == 0)
        cout << " OPERATOR CURRENTLY NOT SUPPORTED IN WITNESS/COUNTEREXAMPLE";
      return false;
    }
  }
  if (options["quiet"] == 0)
    cout <<
      " AN ERROR HAS OCCURREND IN THE GENERATION OF WITNESS/COUNTEREXAMPLE";
  return false;

}

protocol_line::protocol_line(bool_expression * c, set< string > *a)
{
  condition = c;
  actions = a;
}

protocol_line::~protocol_line()
{
}

bool_expression *
protocol_line::get_condition()
{
  return condition;
}

set< string > *protocol_line::get_actions()
{
  return actions;
}

string
protocol_line::to_string()
{
  string str = "{ ";
  unsigned int k = 0;
  unsigned int j = (unsigned int) actions->size() - 1;
  for (set< string >::iterator i = actions->begin(); i != actions->end();
       i++) {
    if (k == j)
      str += *i + " ";
    else
      str += *i + ", ";
    k++;
  }
  str += "}";
  return condition->to_string() + ": " + str;
}

assignment::assignment(string * name, expression * value)
{
  var = new variable(name);
  var_value = value;
}

assignment::~assignment()
{
}

variable *
assignment::get_var()
{
  return var;
}

expression *
assignment::get_var_value()
{
  return var_value;
}

string
assignment::to_string()
{
  return var->to_string() + " = " + var_value->to_string();
}

bool
assignment::check_var_and_value(map< string, basictype * >*obsvars,
                                map< string, basictype * >*vars)
{
  unsigned char right = var_value->get_type();  // right hand side
  unsigned char right1 = right;
  string vs = var->get_variable_name();
  map< string, basictype * >::iterator p = vars->find(vs);
  if (p == vars->end()) { // the variable is not defined
    cout << "        variable " << vs << " is not defined." << endl;
    return false;
  }
  // add a link in variable to its type
  var->set_var_type(p->second);
  map< string, basictype * >::iterator p1;
  string vs1;
  if (right == 0) {
    vs1 = ((variable *) var_value)->get_variable_name();
    if (((variable *) var_value)->is_agent_name_null()) {
      p1 = vars->find(vs1);
      if (p1 != vars->end()) {  // the variable is a local variable 
        right = p1->second->get_type();
        ((variable *) var_value)->set_var_type(p1->second);
      }
    } else {
      string ag_name = ((variable *) var_value)->get_agent_name();
      if (ag_name == "Environment") {
        p1 = obsvars->find(vs1);
        if (p1 != obsvars->end()) { // the variable is a global variable 
          right = p1->second->get_type();
          ((variable *) var_value)->set_var_type(p1->second);
        }
      }
    }
  } else if (right >= 9 && right <= 12) { // bit_expression
    bool flag =
      ((bit_expression *) var_value)->check_var_and_value(obsvars, vars);
    if (!flag)
      return false;
  }

  unsigned char t1 = p->second->get_type(); //variable's type
  if ((t1 != right && right < 5 && !(t1 == 3 && right == 0)) ||
      (t1 == 3 && right >= 5) || (t1 == 1 && right >= 5 && right <= 8)) {
    cout << "        variable " << vs << " has a wrong typed value." << endl;
    return false;
  }
  if (t1 == 1)      // bool
    return true;
  else if (t1 == 2) {
    if (right1 == 0) {    // rangedint
      int ub = ((rangedint *) (p->second))->get_upperbound();
      int lb = ((rangedint *) (p->second))->get_lowerbound();
      int ub1 = ((rangedint *) (p1->second))->get_upperbound();
      int lb1 = ((rangedint *) (p1->second))->get_lowerbound();
      if (ub < lb1 || ub1 < lb) {
        cout << "        variable " << vs1 <<
          " cannot be assignment to variable " << vs << "." << endl;
        return false;
      } else
        return true;
    } else if (right1 == 2) { // int_value
      if (((rangedint *) (p->second))->
          is_valid_value(((int_value *) var_value)->get_value()))
        return true;
      else {
        cout << "        variable " << vs << " has a wrong integer value." <<
          endl;
        return false;
      }
    } else {      //arithmetic expression
      if (((arithmetic_expression *) var_value)->
          check_var_and_value(obsvars, vars))
        return true;
    }
  } else if (t1 == 3) {   // enum
    if (right == 0) {   // an enum value
      if (((enumerate *) (p->second))->is_valid_value(vs1)) {
        enum_value *tmp = new enum_value(new string(vs1));
        var_value = tmp;  // change it to enum_value
        return true;
      } else {
        cout << "        variable " << vs << " has a wrong enum value '" <<
          vs1 << "'." << endl;
        return false;
      }
    } else {      // an enumerate variable
      set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
      set< string > *s2 = ((enumerate *) (p1->second))->get_enumvalue();
      if (s1->size() == s2->size()) { // same size
        bool equal = true;
        for (set< string >::iterator i = s1->begin(); i != s1->end(); i++)
          if (s2->find(*i) == s2->end()) {
            equal = false;
            break;
          }
        if (equal) {
          return true;
        } else {
          cout << "        " << vs << " and " << vs1 <<
            " do not have the same enumerate type." << endl;
          return false;
        }
      } else {
        cout << "        " << vs << " and " << vs1 <<
          " do not have the same enumerate type." << endl;
        return false;
      }
    }
  }
  return false;
}

BDD
assignment::encode_bdd(bdd_parameters * para, BDD base)
{
  basictype *var_type = var->get_var_type();
  unsigned char value_type = var_type->get_type();
  int begin = var_type->get_index_begin();
  int end = var_type->get_index_end();
  BDD tmpbdd = base;
  unsigned char var_value_type = var_value->get_type();

  if (value_type == 1) {  // boolean type
    if (var_value_type == 1) {
      if (((bool_value *) var_value)->get_value())
        tmpbdd = tmpbdd * (*para->pv)[begin];
      else
        tmpbdd = tmpbdd * !(*para->pv)[begin];
    } else if (var_value_type == 0) {
      basictype *var_type1 = ((variable *) var_value)->get_var_type();
      int begin1 = var_type1->get_index_begin();
      // be careful here. rhs is in v and lhs is in pv
      tmpbdd *=
        ((!(*para->pv)[begin] + (*para->v)[begin1]) * ((*para->pv)[begin] +
                                                       !(*para->v)[begin1]));
    } else {      // bit_operation
      BDD rhstrue =
        ((bit_expression *) var_value)->encode_BDD_true(para->bddmgr,
                                                        para->v);
      BDD rhsfalse =
        ((bit_expression *) var_value)->encode_BDD_false(para->bddmgr,
                                                         para->v);
      BDD result =
        ((!(*para->pv)[begin] + rhstrue) * ((*para->pv)[begin] + rhsfalse));
      tmpbdd *= result;
    }
  } else if (value_type == 2) { // rangedint
    int upperbound = ((rangedint *) var_type)->get_upperbound();
    int lowerbound = ((rangedint *) var_type)->get_lowerbound();

    if (var_value_type == 0) {  // a variable
      basictype *var_type1 = ((variable *) var_value)->get_var_type();
      if (options["quiet"] == 0 && options["verbosity"] > 5) {
        int upperbound1 = ((rangedint *) var_type1)->get_upperbound();
        int lowerbound1 = ((rangedint *) var_type1)->get_lowerbound();
        if (upperbound1 > upperbound) {
          cout << "Warning: \"" << var_value->
            to_string() << "\" might be greater than the upperbound of \"" <<
            var->
            get_variable_name() << "\" in assignment " << to_string() << endl;
        }
        if (lowerbound1 < lowerbound) {
          cout << "Warning: \"" << var_value->
            to_string() << "\"  might be less than the lowerbound of \"" <<
            var->
            get_variable_name() << "\" in assignment " << to_string() << endl;
        }
      }
      ADD rhs =
        ((rangedint *) var_type1)->build_ADD_tree(para->bddmgr, para->addv,
                                                  para->ADD_cache);
      ADD lhs =
        ((rangedint *) var_type)->build_ADD_tree(para->bddmgr, para->addv,
                                                 para->ADD_cache);
      lhs = lhs.SwapVariables(*para->addv, *para->addpv);
      ADD result = addEQ(para->bddmgr, lhs, rhs);
      tmpbdd *= result.BddThreshold(1);
    } else if (var_value_type == 2) { // an integer
      int value = ((int_value *) var_value)->get_value();
      vector< int >*vb = ((rangedint *) var_type)->get_value_index(value);
      for (int i = end; i >= begin; i--)
        if ((*vb)[i - begin] == 1)
          tmpbdd = tmpbdd * (*para->pv)[i];
        else if ((*vb)[i - begin] == -1)
          tmpbdd = tmpbdd * !(*para->pv)[i];
    } else if (var_value_type >= 5 && var_value_type <= 8) {  // arithmetic expression
      ADD rhs =
        ((arithmetic_expression *) var_value)->build_ADD_tree(para->bddmgr,
                                                              para->addv,
                                                              para->
                                                              ADD_cache);
      if (options["quiet"] == 0 && options["verbosity"] > 5) {
        ADD overflow =
          addGT(para->bddmgr, rhs, para->bddmgr->constant(upperbound));
        if (overflow != para->bddmgr->addZero()) {
          cout << "Warning: \"" << var_value->
            to_string() << "\" might be greater than the upperbound of \"" <<
            var->
            get_variable_name() << "\" in assignment " << to_string() << endl;
        }
        ADD underflow =
          addLT(para->bddmgr, rhs, para->bddmgr->constant(lowerbound));
        if (underflow != para->bddmgr->addZero()) {
          cout << "Warning: \"" << var_value->
            to_string() << "\" might be less than the lowerbound of \"" <<
            var->
            get_variable_name() << "\" in assignment " << to_string() << endl;
        }
      }
      ADD lhs =
        ((rangedint *) var_type)->build_ADD_tree(para->bddmgr, para->addv,
                                                 para->ADD_cache);
      lhs = lhs.SwapVariables(*para->addv, *para->addpv);
      ADD result = addEQ(para->bddmgr, lhs, rhs);
      tmpbdd *= result.BddThreshold(1);
    }
  } else {      // enumerate
    if (var_value_type == 3) {
      string value = ((enum_value *) var_value)->get_value();
      vector< bool > *vb = ((enumerate *) var_type)->get_value_index(value);
      for (int i = end; i >= begin; i--)
        if ((*vb)[i - begin])
          tmpbdd = tmpbdd * (*para->pv)[i];
        else
          tmpbdd = tmpbdd * !(*para->pv)[i];
    } else {
      basictype *var_type1 = ((variable *) var_value)->get_var_type();
      ADD rhs =
        ((enumerate *) var_type1)->build_ADD_tree(para->bddmgr, para->addv,
                                                  para->ADD_cache);
      ADD lhs =
        ((enumerate *) var_type)->build_ADD_tree(para->bddmgr, para->addv,
                                                 para->ADD_cache);
      lhs = lhs.SwapVariables(*para->addv, *para->addpv);
      ADD result = addEQ(para->bddmgr, lhs, rhs);
      tmpbdd *= result.BddThreshold(1);
    }
  }
  return tmpbdd;
}

BDD
assignment::encode_bdd_overflow(bdd_parameters * para)
{
  basictype *var_type = var->get_var_type();
  unsigned char value_type = var_type->get_type();
  BDD tmpbdd = para->bddmgr->bddZero();
  unsigned char var_value_type = var_value->get_type();

  if (value_type == 2) {  // rangedint
    int upperbound = ((rangedint *) var_type)->get_upperbound();
    int lowerbound = ((rangedint *) var_type)->get_lowerbound();
    ADD addub = para->bddmgr->constant(upperbound);
    ADD addlb = para->bddmgr->constant(lowerbound);

    if (var_value_type == 0) {  // a variable
      basictype *var_type1 = ((variable *) var_value)->get_var_type();
      ADD rhs =
        ((rangedint *) var_type1)->build_ADD_tree(para->bddmgr, para->addv,
                                                  para->ADD_cache);
      ADD result1 = addGT(para->bddmgr, rhs, addub);
      ADD result2 = addLT(para->bddmgr, rhs, addlb);      
      tmpbdd += result1.BddThreshold(1) + result2.BddThreshold(1);
    } else if (var_value_type >= 5 && var_value_type <= 8) {  // arithmetic expression
      ADD rhs =
        ((arithmetic_expression *) var_value)->build_ADD_tree(para->bddmgr,
                                                              para->addv,
                                                              para->
                                                              ADD_cache);
      ADD result1 = addGT(para->bddmgr, rhs, addub);
      ADD result2 = addLT(para->bddmgr, rhs, addlb);      
      tmpbdd += result1.BddThreshold(1) + result2.BddThreshold(1);
    }
  } 
  return tmpbdd;
}

evolution_line::evolution_line(vector< assignment * >*a, bool_expression * c)
{
  assignments = a;
  condition = c;
}

evolution_line::~evolution_line()
{
}

vector< assignment * >*evolution_line::get_assignments()
{
  return assignments;
}

bool_expression *
evolution_line::get_condition()
{
  return condition;
}

string
evolution_line::to_string()
{
  string str = "";
  for (vector< assignment * >::iterator i = assignments->begin();
       i != assignments->end(); i++)
    str += (*i)->to_string() + (i == assignments->end() - 1 ? " " : " and ");
  str += " if " + condition->to_string();
  return str;
}

BDD
evolution_line::encode_bdd_assignements(bdd_parameters * para)
{
  BDD tmpbdd = para->bddmgr->bddOne();
  for (vector< assignment * >::iterator i = assignments->begin();
       i != assignments->end(); i++)
    tmpbdd = (*i)->encode_bdd(para, tmpbdd);
  return tmpbdd;
}

bool
evolution_line::check_double_assignment()
{
  bool flag = false;
  set< string > reassigned;
  for (unsigned int j = 0; j < assignments->size() - 1; j++) {
    string var_name = (*assignments)[j]->get_var()->get_variable_name();
    for (unsigned int k = j + 1; k < assignments->size(); k++) {
      string var_name1 = (*assignments)[k]->get_var()->get_variable_name();
      if (var_name == var_name1) {
        reassigned.insert(var_name);
        flag = true;
        break;
      }
    }
  }
  if (reassigned.size() > 0) {
    for (set< string >::iterator i = reassigned.begin();
         i != reassigned.end(); i++)
      cout << "      error: variable " << *i << " is assigned twice or more"
           << endl;
  }
  return flag;
}

BDD
evolution_line::encode_bdd_condition(bdd_parameters * para)
{
  BDD tmpbdd = condition->encode_bdd_flat(para, new BDD(para->bddmgr->
                                                        bddOne()));
  return tmpbdd;
}

BDD 
evolution_line::encode_bdd_overflow(bdd_parameters * para)
{
  BDD tmpbdd = para->bddmgr->bddZero();
  for (vector< assignment * >::iterator i = assignments->begin();
       i != assignments->end(); i++) {
    tmpbdd += (*i)->encode_bdd_overflow(para);
  }
  tmpbdd *= encode_bdd_condition(para);
  return tmpbdd;
}

vector< evolution_line * >*
evolution_line::extend_to_all_variables(map<string, basictype*>* allvars)
{
  vector< assignment * >*new_assignments;
  bool_expression *
    new_condition;
  vector< evolution_line * >*els = new vector< evolution_line * >;
  els->push_back(this);
  // extend evolution to include all variables in assignments
  for (map< string, basictype * >::iterator j = allvars->begin();
       j != allvars->end(); j++) {
    bool
      found = false;
    for (unsigned int k = 0; k < assignments->size(); k++) {
      variable *
        var = (*assignments)[k]->get_var();
      string
        varname = var->get_variable_name();
      if (varname == j->first) {
        found = true;
        break;
      }
    }

    if (!found) {   // we add this variable to both sides
      unsigned int
        value_type = j->second->get_type();
      string *
        str = new string(j->first);
      variable *
        newvar = new variable(str);
      newvar->set_var_type(j->second);
      if (value_type == 1) {  // boolean type
        vector< evolution_line * >*newels = new vector< evolution_line * >;
        for (unsigned int k = 0; k < els->size(); k++) {
          assignment *
            tmpass = new assignment(str, new bool_value(false));
          variable *
            vr = tmpass->get_var();
          vr->set_var_type(j->second);
          new_assignments =
            new vector< assignment * >((*els)[k]->get_assignments()->begin(),
                                       (*els)[k]->get_assignments()->end());
          new_assignments->push_back(tmpass);
          logic_expression *
            tmplexp = new logic_expression(0, newvar, new bool_value(false));
          bool_expression *
            tmpbexp = new bool_expression(0, tmplexp);
          new_condition =
            new bool_expression(1, (*els)[k]->get_condition(), tmpbexp);
          evolution_line *
            newline = new evolution_line(new_assignments, new_condition);
          newels->push_back(newline);
          tmpass = new assignment(str, new bool_value(true));
          vr = tmpass->get_var();
          vr->set_var_type(j->second);
          new_assignments =
            new vector< assignment * >((*els)[k]->get_assignments()->begin(),
                                       (*els)[k]->get_assignments()->end());
          new_assignments->push_back(tmpass);
          tmplexp = new logic_expression(0, newvar, new bool_value(true));
          tmpbexp = new bool_expression(0, tmplexp);
          new_condition =
            new bool_expression(1, (*els)[k]->get_condition(), tmpbexp);
          newline = new evolution_line(new_assignments, new_condition);
          newels->push_back(newline);
        }
        els = newels;
      } else if (value_type == 2) { // rangedint
        vector< evolution_line * >*newels = new vector< evolution_line * >;
        rangedint *
          rint = (rangedint *) (j->second);
        for (unsigned int k = 0; k < els->size(); k++)
          for (int t = rint->get_lowerbound(); t <= rint->get_upperbound();
               t++) {
            assignment *
              tmpass = new assignment(str, new int_value(t));
            variable *
              vr = tmpass->get_var();
            vr->set_var_type(j->second);
            new_assignments =
              new vector<
              assignment * >((*els)[k]->get_assignments()->begin(),
                             (*els)[k]->get_assignments()->end());
            new_assignments->push_back(tmpass);
            logic_expression *
              tmplexp = new logic_expression(0, newvar, new int_value(t));
            bool_expression *
              tmpbexp = new bool_expression(0, tmplexp);
            new_condition =
              new bool_expression(1, (*els)[k]->get_condition(), tmpbexp);
            evolution_line *
              newline = new evolution_line(new_assignments, new_condition);
            newels->push_back(newline);
          }
        els = newels;
      } else {      // enumerate
        vector< evolution_line * >*newels = new vector< evolution_line * >;
        enumerate *
          enu = (enumerate *) (j->second);
        set< string > *val = enu->get_enumvalue();
        for (unsigned int k = 0; k < els->size(); k++)
          for (set< string >::iterator t = val->begin(); t != val->end();
               t++) {
            string *
              s = new string(*t);
            assignment *
              tmpass = new assignment(str, new enum_value(s));
            variable *
              vr = tmpass->get_var();
            vr->set_var_type(j->second);
            new_assignments =
              new vector<
              assignment * >((*els)[k]->get_assignments()->begin(),
                             (*els)[k]->get_assignments()->end());
            new_assignments->push_back(tmpass);
            logic_expression *
              tmplexp = new logic_expression(0, newvar, new enum_value(s));
            bool_expression *
              tmpbexp = new bool_expression(0, tmplexp);
            new_condition =
              new bool_expression(1, (*els)[k]->get_condition(), tmpbexp);
            evolution_line *
              newline = new evolution_line(new_assignments, new_condition);
            newels->push_back(newline);
          }
        els = newels;
      }
    }
  }
  return els;
}

basic_agent::basic_agent(string * n,
                         map< string, variable * >*lv,
                         map< string, basictype * >*v0,
                         vector< basictype * >*vecv0,
                         map< string, basictype * >*v1,
                         vector< basictype * >*vecv1,
                         bool_expression * r,
                         set< string > *v2,
                         vector< protocol_line * >*v3,
                         vector< evolution_line * >*v4)
{
  name = n;
  lobsvars = lv;
  obsvars = v0;
  vars = v1;
  vec_obsvars = vecv0;
  vec_vars = vecv1;
  actions = v2;
  protocol = v3;
  evolution = v4;
  redstates = r;
  action_indices = new map< string, vector< bool > *>;
  generate_action_bdd_value();

  sc = NULL;
}

basic_agent::~basic_agent()
{
}

string
basic_agent::get_name()
{
  if (name == NULL) {
    cout << " error: name in agent is undefined!" << endl;
    exit(1);
  } else
    return *name;
}

string *
basic_agent::get_name_point()
{
  return name;
}

map< string, basictype * >*basic_agent::get_obsvars()
{
  return obsvars;
}

vector< basictype * >*basic_agent::get_vec_obsvars()
{
  return vec_obsvars;
}

vector< basictype * >*basic_agent::get_vec_vars()
{
  return vec_vars;
}

map< string, variable * >*basic_agent::get_lobsvars()
{
  return lobsvars;
}

map< string, basictype * >*basic_agent::get_vars()
{
  return vars;
}

basictype *
basic_agent::get_basictype_by_name(string varname)
{
  if (obsvars != NULL) {
    if (obsvars->find(varname) != obsvars->end())
      return (*obsvars)[varname];
  }
  if (vars != NULL) {
    if (vars->find(varname) != vars->end())
      return (*vars)[varname];
  }
  return NULL;
}

set< string > *basic_agent::get_actions()
{
  return actions;
}

vector< protocol_line * >*basic_agent::get_protocol()
{
  return protocol;
}

vector< evolution_line * >*basic_agent::get_evolution()
{
  return evolution;
}

bool_expression *
basic_agent::get_redstates()
{
  return redstates;
}

string
basic_agent::to_string()
{
  string str = "Agent " + *name + "\n";

  if (obsvars != NULL && obsvars->size() > 0) {
    str += "Obsvars:\n";
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++)
      str += "    " + (*i).second->to_string() + ";\n";
    str += "end Obsvars\n";
  }

  str += "Vars:\n";
  for (map< string, basictype * >::iterator i = vars->begin();
       i != vars->end(); i++)
    str += "    " + (*i).second->to_string() + ";\n";
  str += "end Vars\nRedStates:\n    ";
  if (redstates == NULL)
    str += "";
  else
    str += redstates->to_string() + ";";
  str += "\nend RedStates\nActions = { ";
  unsigned int k = 0;
  unsigned int bound = (unsigned int) actions->size() - 1;
  for (set< string >::iterator i = actions->begin(); i != actions->end();
       i++) {
    if (k == bound)
      str += *i + " ";
    else
      str += *i + ", ";
    k++;
  }
  str += "}\nProtocol:\n";
  for (vector< protocol_line * >::iterator i = protocol->begin();
       i != protocol->end(); i++)
    str += "    " + (*i)->to_string() + ";\n";
  str += "end Protocol\nEvolution:\n";
  for (vector< evolution_line * >::iterator i = evolution->begin();
       i != evolution->end(); i++)
    str += "    " + (*i)->to_string() + ";\n";
  str += "end Evolution\n";
  str += "end Agent\n";
  return str;
}

int
basic_agent::state_BDD_length()
{
  int count = 0;
  count += obsvars_BDD_length();
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++)
      count += (*i).second->BDD_length();
  return count;
}

int
basic_agent::obsvars_BDD_length()
{
  int count = 0;
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++)
      count += (*i).second->BDD_length();
  return count;
}

unsigned int
basic_agent::actions_BDD_length()
{
  if (actions == NULL || actions->size() == 0)
    return 0;
  return log_2((unsigned int) actions->size());
}

void
basic_agent::set_action_index_begin(int i)
{
  action_index_begin = i;
}

void
basic_agent::set_action_index_end(int i)
{
  action_index_end = i;
}

void
basic_agent::set_var_index_begin(int i)
{
  var_index_begin = i;
}

void
basic_agent::set_var_index_end(int i)
{
  var_index_end = i;
}

int
basic_agent::get_action_index_begin()
{
  return action_index_begin;
}

int
basic_agent::get_action_index_end()
{
  return action_index_end;
}

int
basic_agent::get_var_index_begin()
{
  return var_index_begin;
}

int
basic_agent::get_var_index_end()
{
  return var_index_end;
}

void
basic_agent::generate_action_bdd_value()
{
  int size = actions_BDD_length();
  if (size == 0)
    return;
  vector< bool > base(size, false);
  for (set< string >::iterator i = actions->begin(); i != actions->end();
       i++) {
    vector< bool > *temp = new vector< bool > (base);
    pair < string, vector< bool > *>p(*i, temp);
    action_indices->insert(p);
    for (int j = size - 1; j >= 0; j--) {
      if (base[j])
        base[j] = false;
      else {
        base[j] = true;
        break;
      }
    }
  }
}

void
basic_agent::print_value_index()
{
  for (map< string, vector< bool > *>::iterator i = action_indices->begin();
       i != action_indices->end(); i++) {
    cout << i->first << ": ";
    for (unsigned int j = 0; j < i->second->size(); j++)
      cout << ((*(i->second))[j] ? 1 : 0);
    cout << endl;
  }
}

map< string, vector< bool > *>*basic_agent::get_action_indices()
{
  return action_indices;
}

int
basic_agent::allocate_BDD_2_variables(int start)
{
  set_var_index_begin(start);
  int count = start;

  if (vec_obsvars != NULL)
    for (unsigned int i = 0; i < vec_obsvars->size(); i++) {
      int l = (*vec_obsvars)[i]->BDD_length();
      (*vec_obsvars)[i]->set_index_begin(count);
      (*vec_obsvars)[i]->set_index_end(count + l - 1);
      count += l;
    }
  if (vec_vars != NULL)
    for (unsigned int i = 0; i < vec_vars->size(); i++) {
      int l = (*vec_vars)[i]->BDD_length();
      (*vec_vars)[i]->set_index_begin(count);
      (*vec_vars)[i]->set_index_end(count + l - 1);
      count += l;
    }

  set_var_index_end(count - 1);
  return count;
}

int
basic_agent::allocate_BDD_2_actions(int start)
{
  set_action_index_begin(start);
  int end = start + actions_BDD_length();
  set_action_index_end(end - 1);
  return end;
}

BDD
basic_agent::encode_action(bdd_parameters * para, string act)
{
  map< string, vector< bool > *>::iterator k = action_indices->find(act);
  if (k != action_indices->end()) {
    BDD temp = para->bddmgr->bddOne();
    vector< bool > *b = (*k).second;
    for (int i = action_index_begin; i <= action_index_end; i++)
      temp =
        temp *
        ((*b)[i - action_index_begin] ? (*para->a)[i] : !(*para->a)[i]);
    return temp;
  }
  return para->bddmgr->bddZero();
}

BDD
basic_agent::encode_protocol(bdd_parameters * para)
{
  BDD bddprot = para->bddmgr->bddZero();
  BDD nullaction = para->bddmgr->bddOne();
  if (protocol->size() == 0)
    return para->bddmgr->bddOne();
  for (vector< protocol_line * >::iterator i = protocol->begin();
       i != protocol->end(); i++) {
    bool_expression *condition = (*i)->get_condition();
    BDD tmpcond = para->bddmgr->bddOne();
    if (!condition->is_other_branch()) {
      tmpcond = condition->encode_bdd_flat(para, new BDD(para->bddmgr->bddOne()));
      nullaction = nullaction * !tmpcond;
    } else
      tmpcond = nullaction;

    BDD tmpact = para->bddmgr->bddZero();
    set< string > *actions = (*i)->get_actions();
    for (set< string >::iterator j = actions->begin(); j != actions->end();
         j++) {
      tmpact = tmpact + encode_action(para, *j);
    }

    BDD oneline = tmpcond * tmpact;

    bddprot = bddprot + oneline;
  }
  return bddprot;
}

BDD
basic_agent::encode_evolution(bdd_parameters * para)
{
  BDD bddevol = para->bddmgr->bddZero();
  BDD lastcond = para->bddmgr->bddOne();

  for (vector< evolution_line * >::iterator i = evolution->begin();
       i != evolution->end(); i++) {
    vector< assignment * >*assignments = (*i)->get_assignments();
    map< string, basictype * >*mp = new map< string, basictype * >;
    if (obsvars != NULL)
      for (map< string, basictype * >::iterator j = obsvars->begin();
           j != obsvars->end(); j++) {
        bool found = false;
        for (unsigned int k = 0; k < assignments->size(); k++) {
          variable *var = (*assignments)[k]->get_var();
          string varname = var->get_variable_name();
          if (varname == j->first) {
            found = true;
            break;
          }
        }

        if (!found)   // we add this variable to both sides
          mp->insert(*j);
      }

    if (vars != NULL)
      for (map< string, basictype * >::iterator j = vars->begin();
           j != vars->end(); j++) {
        bool found = false;
        for (unsigned int k = 0; k < assignments->size(); k++) {
          variable *var = (*assignments)[k]->get_var();
          string varname = var->get_variable_name();
          if (varname == j->first) {
            found = true;
            break;
          }
        }

        if (!found)   // we add this variable to both sides
          mp->insert(*j);
      }

    BDD bddassignment = (*i)->encode_bdd_assignements(para);
    BDD bddcondition = (*i)->encode_bdd_condition(para);
    for (map< string, basictype * >::iterator j = mp->begin();
         j != mp->end(); j++) {
      int begin = j->second->get_index_begin();
      int end = j->second->get_index_end();
      for (int k = begin; k <= end; k++) {
        bddassignment *=
          ((!(*para->v)[k] + (*para->pv)[k]) * ((*para->v)[k] +
                                                !(*para->pv)[k]));
      }
    }
    lastcond = lastcond * !bddcondition;

    bddevol = bddevol + (bddassignment * bddcondition);
  }

  BDD dnc = para->bddmgr->bddOne();
  int begin, end;
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      basictype *var_type = (*i).second;
      begin = var_type->get_index_begin();
      end = var_type->get_index_end();
      for (int j = begin; j <= end; j++)
        dnc =
          dnc * ((!(*para->v)[j] + (*para->pv)[j]) *
                 ((*para->v)[j] + !(*para->pv)[j]));
    }
  if (vars != NULL) {
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      basictype *var_type = (*i).second;
      begin = var_type->get_index_begin();
      end = var_type->get_index_end();
      for (int j = begin; j <= end; j++)
        dnc =
          dnc * ((!(*para->v)[j] + (*para->pv)[j]) *
                 ((*para->v)[j] + !(*para->pv)[j]));
    }
  }
  lastcond *= dnc;
  return bddevol + lastcond;
}

BDD
basic_agent::encode_evolution_smv(bdd_parameters * para)
{
  vector< evolution_line * >tmpevol(evolution->begin(), evolution->end());
  map< string, BDD > tmpbdds;

  while (tmpevol.size() > 0) {
    evolution_line *evoline = tmpevol[0];
    tmpevol.erase(tmpevol.begin());
    vector< assignment * >*assignments = evoline->get_assignments();
    variable *var = (*assignments)[0]->get_var();
    string varname = var->get_variable_name();

    BDD bddassignment = evoline->encode_bdd_assignements(para);
    BDD bddcondition = evoline->encode_bdd_condition(para);
    BDD tmplast = !bddcondition;
    BDD linebdd = bddassignment * bddcondition;

    unsigned int i = 0;
    while (i < tmpevol.size()) {
      evolution_line *evoline1 = tmpevol[i];
      vector< assignment * >*assignments1 = evoline1->get_assignments();
      variable *var1 = (*assignments1)[0]->get_var();
      if (varname.compare(var1->get_variable_name()) == 0) {
        BDD bddassignment1 = evoline1->encode_bdd_assignements(para);
        BDD bddcondition1 = evoline1->encode_bdd_condition(para);
        linebdd += bddassignment1 * bddcondition1;
        tmplast *= !bddcondition1;
        tmpevol.erase(tmpevol.begin() + i);
      } else
        i++;
    }

    basictype *var_type = var->get_var_type();
    int begin = var_type->get_index_begin();
    int end = var_type->get_index_end();
    for (int j = begin; j <= end; j++)
      tmplast *=
        ((!(*para->v)[j] + (*para->pv)[j]) * ((*para->v)[j] +
                                              !(*para->pv)[j]));

    linebdd += tmplast;
    tmpbdds[varname] = linebdd;
  }

  BDD dnc = para->bddmgr->bddOne();
  int begin, end;
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      if (tmpbdds.find(i->first) == tmpbdds.end()) {
        basictype *var_type = (*i).second;
        begin = var_type->get_index_begin();
        end = var_type->get_index_end();
        for (int j = begin; j <= end; j++)
          dnc =
            dnc * ((!(*para->v)[j] + (*para->pv)[j]) *
                   ((*para->v)[j] + !(*para->pv)[j]));
      }
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      if (tmpbdds.find(i->first) == tmpbdds.end()) {
        basictype *var_type = (*i).second;
        begin = var_type->get_index_begin();
        end = var_type->get_index_end();
        for (int j = begin; j <= end; j++)
          dnc =
            dnc * ((!(*para->v)[j] + (*para->pv)[j]) *
                   ((*para->v)[j] + !(*para->pv)[j]));
      }
    }

  for (map< string, BDD >::iterator i = tmpbdds.begin(); i != tmpbdds.end();
       i++)
    dnc *= i->second;

  return dnc;
}

BDD
basic_agent::encode_greenstates(bdd_parameters * para)
{
  if (redstates == NULL)
    return para->bddmgr->bddOne();
  else {
    BDD tmp = redstates->encode_bdd_flat(para, new BDD(para->bddmgr->bddOne()));
    return (!tmp).SwapVariables(*para->v, *para->pv);
  }
}

void
basic_agent::print_variable_BDD_encoding()
{
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      int begin = i->second->get_index_begin();
      int end = i->second->get_index_end();
      cout << "----- " << i->
        first << ": " << begin << " .. " << end << " -----" << endl;
      basictype *b = i->second;
      if (b->get_type() == 2) //rangeint
        ((rangedint *) b)->print_value_index();
      else if (b->get_type() == 3)  //enumerate
        ((enumerate *) b)->print_value_index();
      else
        b->print_value_index();
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      int begin = i->second->get_index_begin();
      int end = i->second->get_index_end();
      cout << "----- " << i->
        first << ": " << begin << " .. " << end << " -----" << endl;
      basictype *b = i->second;
      if (b->get_type() == 2) //rangeint
        ((rangedint *) b)->print_value_index();
      else if (b->get_type() == 3)  //enumerate
        ((enumerate *) b)->print_value_index();
      else
        b->print_value_index();
    }
}

void
basic_agent::print_state(string prefix, BDD state, BDDvector v)
{
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      i->second->print_state(prefix, state, v);
      cout << endl;
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      i->second->print_state(prefix, state, v);
      cout << endl;
    }
}

bool
basic_agent::is_valid_state(BDD state, BDDvector v)
{
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      if (!i->second->is_valid_state(state, v))
        return false;
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      if (!i->second->is_valid_state(state, v))
        return false;
    }
  return true;
}

void
basic_agent::print_action(BDD state, BDDvector a)
{
  vector< bool > index;
  for (int i = action_index_begin; i <= action_index_end; i++)
    if (state <= a[i])
      index.push_back(true);
    else
      index.push_back(false);
  for (map< string, vector< bool > *>::iterator i = action_indices->begin();
       i != action_indices->end(); i++) {
    bool flag = true;
    for (unsigned int j = 0; j < i->second->size(); j++)
      if ((*(i->second))[j] != index[j]) {
        flag = false;
        break;
      }
    if (flag) {
      cout << i->first;
      return;
    }
  }
}

bool
basic_agent::is_valid_action(BDD state, BDDvector a)
{
  if (action_indices->size() == 0)
    return true;
  vector< bool > index;
  for (int i = action_index_begin; i <= action_index_end; i++)
    if (state <= a[i])
      index.push_back(true);
    else
      index.push_back(false);
  for (map< string, vector< bool > *>::iterator i = action_indices->begin();
       i != action_indices->end(); i++) {
    bool flag = true;
    for (unsigned int j = 0; j < i->second->size(); j++)
      if ((*(i->second))[j] != index[j]) {
        flag = false;
        break;
      }
    if (flag) {
      return true;
    }
  }
  return false;
}

set< string > *basic_agent::get_obs_enum_values()
{
  if (obsvars != NULL) {
    set< string > *tmpset = new set< string >;
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++)
      if (i->second->get_type() == 3) {
        set< string > *varset = ((enumerate *) (i->second))->get_enumvalue();
        tmpset->insert(varset->begin(), varset->end());
      }
    return tmpset;
  }
  return NULL;
}

bool
basic_agent::check_var_against_enum_values(set< string > *obsenum)
{
  bool flag = true;
  set< string > *tmpset = new set< string >;
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++)
      if (i->second->get_type() == 3) {
        set< string > *varset = ((enumerate *) (i->second))->get_enumvalue();
        tmpset->insert(varset->begin(), varset->end());
      }
  if (obsenum != NULL)
    tmpset->insert(obsenum->begin(), obsenum->end());
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++)
      if (tmpset->find(i->first) != tmpset->end()) {
        flag = false;
        cout << "variable " << i->
          first << " has been used as a enumerate value." << endl;
      }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++)
      if (tmpset->find(i->first) != tmpset->end()) {
        flag = false;
        cout << "variable " << i->
          first << " has been used as a enumerate value." << endl;
      }
  return flag;
}

bool
basic_agent::check_lobsvars(map< string, basictype * >*envars)
{
  if (lobsvars != NULL && lobsvars->size() > 0)
    for (map< string, variable * >::iterator i = lobsvars->begin();
         i != lobsvars->end(); i++) {
      map< string, basictype * >::iterator j;
      if (envars != NULL && (j = envars->find(i->first)) != envars->end())
        i->second->set_var_type(j->second);
      else {
        cout << "local observable variable " << i->
          first << " is not defined in the environment." << endl;
        return false;
      }
    }
  return true;
}

void
basic_agent::print_stateXML(ofstream * myfile, BDD state, BDDvector v)
{
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      i->second->print_stateXML(myfile, state, v);
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      i->second->print_stateXML(myfile, state, v);
    }
}

string
basic_agent::state_to_str(BDD state, BDDvector v)
{
  ostringstream s;
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      s << "    " << i->second->state_to_str(state, v) << "\n";
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      s << "    " << i->second->state_to_str(state, v) << "\n";
    }
  return s.str();
}

string
basic_agent::action_to_str(BDD state, BDDvector a)
{
  ostringstream s;
  vector< bool > index;
  for (int i = action_index_begin; i <= action_index_end; i++)
    if (state <= a[i])
      index.push_back(true);
    else
      index.push_back(false);
  for (map< string, vector< bool > *>::iterator i = action_indices->begin();
       i != action_indices->end(); i++) {
    bool flag = true;
    for (unsigned int j = 0; j < i->second->size(); j++)
      if ((*(i->second))[j] != index[j]) {
        flag = false;
        break;
      }
    if (flag) {
      s << i->first;
    }
  }
  return s.str();
}

BDD
basic_agent::project_local_state(BDD * state, Cudd * bddmgr, BDDvector * v)
{
  BDD tmp = bddmgr->bddOne(); // Always true

  if (lobsvars != NULL && lobsvars->size() > 0) {
    map< string, basictype * >*envars = (*agents)[0]->get_vars();
    for (map< string, basictype * >::iterator i = envars->begin();
         i != envars->end(); i++) {
      if (lobsvars->find(i->first) == lobsvars->end()) {  // i->first is not local observable variable 
        basictype *bt = i->second;
        int index_begin = bt->get_index_begin();
        int index_end = bt->get_index_end();
        for (int j = index_begin; j <= index_end; j++)
          tmp = tmp * (*v)[j];
      }
    }
    for (int j = envars_bdd_length; j < get_var_index_begin(); j++) {
      tmp = tmp * (*v)[j];
    }
  } else {
    for (int j = obsvars_bdd_length; j < get_var_index_begin(); j++) {
      tmp = tmp * (*v)[j];
    }
  }

  for (int j = get_var_index_end() + 1; j < v->count(); j++) {
    tmp = tmp * (*v)[j];
  }

  return state->ExistAbstract(tmp);
}

BDDvector*
basic_agent::get_local_state_vector(Cudd * bddmgr, BDDvector * v)
{
  int count = var_index_end - var_index_begin + 1;
  
  if (lobsvars != NULL && lobsvars->size() > 0) {
    map< string, basictype * >*envars = (*agents)[0]->get_vars();
    for (map< string, basictype * >::iterator i = envars->begin();
         i != envars->end(); i++) {
      if (lobsvars->find(i->first) != lobsvars->end()) {  // i->first is local observable variable 
        basictype *bt = i->second;
        int index_begin = bt->get_index_begin();
        int index_end = bt->get_index_end();
        count += index_end - index_begin + 1;
      }
    }
  } 
  count += obsvars_bdd_length;
  
  BDDvector *localv = new BDDvector(count, bddmgr);

  int index = 0;
  vector< basictype * > *enobsvars = (*agents)[0]->get_vec_obsvars();
  if(enobsvars != NULL) {
    for (unsigned int i=0; i<enobsvars->size(); i++) {
      basictype *bt = (*enobsvars)[i];
      int index_begin = bt->get_index_begin();
      int index_end = bt->get_index_end();
      for (int j = index_begin; j <= index_end; j++)
        (*localv)[index++] = (*v)[j];
    }
  }

  if (lobsvars != NULL && lobsvars->size() > 0) {
    vector< basictype * > *envars = (*agents)[0]->get_vec_vars();
    for (unsigned int i=0; i<envars->size(); i++) {
      if (lobsvars->find((*envars)[i]->get_name()) != lobsvars->end()) {  // i->first is local observable variable 
        basictype *bt = (*envars)[i];
        int index_begin = bt->get_index_begin();
        int index_end = bt->get_index_end();
        for (int j = index_begin; j <= index_end; j++)
          (*localv)[index++] = (*v)[j];
      }
    }
  }

  for(int i=var_index_begin; i<=var_index_end; i++)
    (*localv)[index++] = (*v)[i];

  return localv;
}

BDD
basic_agent::project_local_trans(BDD * trans, Cudd * bddmgr, BDDvector * v,
                                 BDDvector * pv)
{
  BDD tmp = bddmgr->bddOne(); // Always true

  for (int j = 0; j < get_var_index_begin(); j++) {
    tmp = tmp * (*v)[j];
    tmp = tmp * (*pv)[j];
  }

  for (int j = get_var_index_end() + 1; j < v->count(); j++) {
    tmp = tmp * (*v)[j];
    tmp = tmp * (*pv)[j];
  }

  return trans->ExistAbstract(tmp);
}

/*BDDvector
  basic_agent::get_BDDvector(Cudd * bddmgr, BDDvector * v, BDDvector * pv)
  {
  int begin = get_var_index_begin();
  int end = get_var_index_end();
  BDDvector tmp((end - begin + 1) * 2, bddmgr);
  int k = 0;

  for (int j = begin; j <= end; j++)
  tmp[k++] = (*v)[j];

  for (int j = begin; j <= end; j++)
  tmp[k++] = (*pv)[j];

  return tmp;
  }*/

BDD
basic_agent::get_SC(bdd_parameters * para) {
  if(sc == NULL) {
    sc = new BDD(get_non_unique(*para->reach, get_name(), para));
  }
  return *sc;
}

/**********************************************
 transition (for counterexamples)
**********************************************/
transition::transition(BDD * fr, int frid, BDD * t, int tid, BDD * lab)
{
  from = new BDD((*fr));
  fromid = frid;
  to = new BDD((*t));
  toid = tid;
  label = new BDD((*lab));

  temporal = true;
  epistemic1 = "";
  epistemic2 = "";
}

transition::transition(BDD * fr, int frid, BDD * t, int tid, string name1,
                       BDD * lab)
{
  from = new BDD((*fr));
  fromid = frid;
  to = new BDD((*t));
  toid = tid;
  //type = ty;
  label = new BDD((*lab));

  temporal = false;
  epistemic1 = name1;
  epistemic2 = "";
}

transition::transition(BDD * fr, int frid, BDD * t, int tid, string name1,
                       string name2, BDD * lab)
{
  from = new BDD((*fr));
  fromid = frid;
  to = new BDD((*t));
  toid = tid;
  label = new BDD((*lab));

  temporal = false;
  epistemic1 = name1;
  epistemic2 = name2;
}

transition::transition()
{
  from = new BDD();
  fromid = -1;
  to = new BDD();
  toid = -1;
  label = new BDD();

  temporal = false;
  epistemic1 = "";
  epistemic2 = "";
}

transition::~transition()
{
}

BDD *
transition::getfrom()
{
  return from;
}

BDD *
transition::getto()
{
  return to;
}

BDD *
transition::getlabel()
{
  return label;
}

int
transition::getfromid()
{
  return fromid;
}

int
transition::gettoid()
{
  return toid;
}

void
transition::setfrom(BDD * fr)
{
  from = fr;
}

void
transition::setto(BDD * fr)
{
  to = fr;
}

void
transition::setlabel(BDD * fr)
{
  label = fr;
}

void
transition::setfromid(int frid)
{
  fromid = frid;
}

void
transition::settoid(int frid)
{
  toid = frid;
}

void
transition::print(BDDvector * v, BDDvector * a)
{
  cout << "------- Transition --------" << endl;
  cout << " From (id): " << fromid << endl;
  for (unsigned int i = 0; i < agents->size(); i++) {
    cout << "    Agent " << (*agents)[i]->get_name() << endl;
    (*agents)[i]->print_state("  ", *from, *v);
  }

  cout << " To (id): " << toid << endl;
  for (unsigned int i = 0; i < agents->size(); i++) {
    cout << "    Agent " << (*agents)[i]->get_name() << endl;
    (*agents)[i]->print_state("  ", *to, *v);
  }

  if (isTemporal()) {
    cout << " Joint action: " << endl;
    for (unsigned int i = 0; i < agents->size(); i++) {
      cout << (*agents)[i]->get_name() << " : ";
      (*agents)[i]->print_action(*label, *a);
      if (i < agents->size() - 1)
        cout << "; ";
      else
        cout << endl;
    }
  }

  cout << "---------------------------" << endl;
}

void
transition::printXML(ofstream * myfile, BDDvector * v)
{
  *myfile << "  <transition>\n";
  *myfile << "    <from-id>" << fromid << "</from-id>\n";
  *myfile << "    <to-id>" << toid << "</to-id>\n";
  *myfile << "    <from>\n";
  for (unsigned int i = 0; i < agents->size(); i++) {
    *myfile << "      <agent name=\"" << (*agents)[i]->get_name() << "\">\n";
    (*agents)[i]->print_stateXML(myfile, *from, *v);
    *myfile << "      </agent>\n";
  }
  *myfile << "    </from>\n";
  *myfile << "    <to>\n";
  for (unsigned int i = 0; i < agents->size(); i++) {
    *myfile << "      <agent name=\"" << (*agents)[i]->get_name() << "\">\n";
    (*agents)[i]->print_stateXML(myfile, *to, *v);
    *myfile << "      </agent>\n";
  }
  *myfile << "    </to>\n";
  *myfile << "  </transition>\n";

}

string
transition::index_to_string(BDDvector * a)
{
  char buff[20];
  string s = "";
  for (unsigned int i = 0; i < agents->size(); i++) {
    s += (*agents)[i]->action_to_str(*label, *a) + ";";
  }
  sprintf(buff, "%1d->%1d", fromid, toid);
  s += buff;
  return s;
}

void
transition::to_str(ofstream * myfile, BDDvector * a)
{
  *myfile << "    " << fromid << " -> " << toid;

  if (isTemporal()) {
    // A temporal transition
    *myfile << "[label=\"<";
    for (unsigned int i = 0; i < agents->size(); i++) {
      string act_str = (*agents)[i]->action_to_str(*label, *a);
      if (act_str != "") {
        *myfile << act_str;
        if (!(i == agents->size() - 1)) {
          *myfile << ";";
        }
      }
    }
    *myfile << ">\"]" << endl;
  } else {
    *myfile << "[label=\"" << epistemic1 << (epistemic2.
                                             empty()? "" : ", ") << epistemic2
            << "\", arrowhead=none, style=dotted]" << endl;
  }
}

bool
transition::isTemporal()
{
  return temporal;
}

string
transition::getEpistemic1()
{
  return epistemic1;
}

string
transition::getEpistemic2()
{
  return epistemic2;
}

/*
 * end transition
 */
