//
// Created by Havelund, Klaus (348B) on 3/30/21.
//

#ifndef LOGSCOPE_ERRORREPORT_H
#define LOGSCOPE_ERRORREPORT_H

#include <string>
#include "Binding.h"

using namespace std;

/**
 * Represents an error report. A vector of all error reports can be obtained from
 * a `SpecObject` via a call to the method: `getErrorReports`.
 */

struct ErrorReport {

    /**
     * Constructor.
     *
     * @param kind the kind of error.
     * @param monitorName the monitor the error occurred in.
     * @param state the state the error occurred in.
     * @param binding the binding of state parameter names to values.
     * @param eventCount the number of the event causing the error. -1 if N/A.
     * @param transitionCount the number of the transition causing the error. -1 if N/A.
     */

    ErrorReport(string kind, string monitorName, string stateName, Binding binding, int eventCount, int transitionCount);

    friend ostream &operator<<(ostream &os, const ErrorReport &error);

    string kind;
    string monitorName;
    string stateName;
    Binding binding;
    int eventCount;
    int transitionCount;

};


#endif //LOGSCOPE_ERRORREPORT_H
