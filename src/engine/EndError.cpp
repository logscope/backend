//
// Created by Havelund, Klaus (348B) on 1/18/21.
//

#include "util.h"
#include "EndError.h"

EndError::EndError(string monitorName, ast::State *state, Binding binding) :
        MonitorError(monitorName, state, binding) {}

void EndError::printVerification() {
    cout << "ErrorExpected(";
    cout << quote("EndError") << ",";
    cout << quote(monitorName) << ",";
    cout << quote(stateAST->name) << ",";
    cout << binding << ",";
    cout << -1 << ",";
    cout << -1;
    cout << ")";
}

ErrorReport EndError::getErrorReport() {
    return ErrorReport("EndError", monitorName, stateAST->name, binding, -1, -1);
}

// string kind, string monitorName, string stateName, Binding binding, int eventCount, int transitionCount

void EndError::verifyError(ErrorReport errorExpected) {
    MonitorError::verifyError(errorExpected);
    assert("EndError" == errorExpected.kind);
}

ostream& EndError::print(ostream& os) const
{
    os << "monitoring terminates in non-final state:" << endl;
    MonitorError::print(os);
    return os;
}