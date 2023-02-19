#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <list>
#include "AbstractWrapper.h"
// include your other headers here
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "QPS/Qps.h"
#include "SP/SP.h"
#include <fstream>

class TestWrapper : public AbstractWrapper {
 public:
  // default constructor
  TestWrapper();
  
  // destructor
  ~TestWrapper();
  
  // method for parsing the SIMPLE source
  virtual void parse(std::string filename);
  
  // method for evaluating a query
  virtual void evaluate(std::string query, std::list<std::string>& results);
 private:
  shared_ptr<PKB> pkb_;
};

#endif
