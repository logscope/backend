//
// Created by Havelund, Klaus (348B) on 1/17/21.
//

#include "MonitorError.h"

using namespace std;

MonitorError::MonitorError(string monitorName, ast::State* state, Binding binding):
        monitorName(monitorName), stateAST(state), binding(binding) {}

void MonitorError::verifyError(ErrorReport errorExpected) {
  assert(monitorName == errorExpected.monitorName);
  assert(stateAST->name == errorExpected.stateName);
  assert(binding == errorExpected.binding);
}

ostream &operator<<(ostream &os, const MonitorError &error) {
    return error.print(os);
}

ostream& MonitorError::print(ostream& os) const
{
    os << "monitor " + monitorName << " {" << endl;
    os << "  ..." << endl;
    os << "  " << *stateAST << endl;
    os << "  with: "  << binding << endl;
    os << "  ..." << endl;
    os << "}";
    return os;
}

