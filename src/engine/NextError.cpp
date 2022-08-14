//
// Created by Havelund, Klaus (348B) on 1/19/21.
//

#include "util.h"
#include "NextError.h"

NextError::NextError(string monitorName, ast::State *state, Binding binding, Event event, int eventCount) :
        MonitorError(monitorName, state, binding), event(event), eventCount(eventCount) {}

ErrorReport NextError::getErrorReport() {
    return ErrorReport("NextError", monitorName, stateAST->name, binding, eventCount, -1);
}

void NextError::printVerification() {
    cout << "ErrorExpected(";
    cout << quote("NextError") << ",";
    cout << quote(monitorName) << ",";
    cout << quote(stateAST->name) << ",";
    cout << binding << ",";
    cout << eventCount << ",";
    cout << -1;
    cout << ")";
}

void NextError::verifyError(ErrorReport errorExpected) {
    MonitorError::verifyError(errorExpected);
    assert("NextError" == errorExpected.kind);
    assert(eventCount == errorExpected.eventCount);
}

ostream& NextError::print(ostream& os) const
{
    os << "event number " << eventCount << ": " << event << endl;
    os << "no transition triggered in next state" << endl;
    MonitorError::print(os);
    return os;
}