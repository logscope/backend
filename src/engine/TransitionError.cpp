//
// Created by Havelund, Klaus (348B) on 1/20/21.
//

#include "util.h"
#include "TransitionError.h"
#include "ErrorReport.h"

TransitionError::TransitionError(string monitorName, ast::State *state, Binding binding, Event event, int eventCount,
                                 ast::Transition *transition):
        MonitorError(monitorName, state, binding), event(event), eventCount(eventCount), transitionAST(transition) {}

ErrorReport TransitionError::getErrorReport() {
    return ErrorReport("TransitionError", monitorName, stateAST->name, binding, eventCount, transitionAST->transitionNr);
}

void TransitionError::printVerification() {
    cout << "ErrorExpected(";
    cout << quote("TransitionError") << ",";
    cout << quote(monitorName) << ",";
    cout << quote(stateAST->name) << ",";
    cout << binding << ",";
    cout << eventCount << ",";
    cout << transitionAST->transitionNr;
    cout << ")";
}

void TransitionError::verifyError(ErrorReport errorExpected) {
    MonitorError::verifyError(errorExpected);
    assert("TransitionError" == errorExpected.kind);
    assert(eventCount == errorExpected.eventCount);
    assert(transitionAST->transitionNr == errorExpected.transitionCount);
}

ostream& TransitionError::print(ostream& os) const
{
    os << "event number " << eventCount << ": " << event << endl;
    os << "triggers transition: " << endl;
    os << "  " << *transitionAST << endl;
    os << "in:" << endl;
    MonitorError::print(os);
    return os;
}
