//
// Created by Havelund, Klaus (348B) on 1/17/21.
//

#ifndef LOGSCOPE_MONITORERROR_H
#define LOGSCOPE_MONITORERROR_H

#include <ostream>
#include "../ast/ast.h"
#include "Binding.h"
#include "ErrorReport.h"

using namespace std;

/**
 * Superclass for all errors detected. Every error is associated with a monitor,
 * a state, and a binding of parameters in that state.
 */

class MonitorError {

public:

    /**
     * Constructor.
     *
     * @param monitorName the monitor the error occurred in.
     * @param state the state the error occurred in.
     * @param binding the binding of state parameter names to values.
     */

    MonitorError(string monitorName, ast::State* state, Binding binding);

    /*
     * Returns an error report documenting this error. Can be accessed by the user
     * through a call of `SpecObject.getErrorReports()`.
     */

    virtual ErrorReport getErrorReport() = 0;

    /**
     * Verifies the error against an expected error, used for unit testing.
     * @param errorExpected
     */

    virtual void verifyError(ErrorReport errorExpected);

    /**
     * Generates an error report to later be checked with the `verifyError` method
     * (as argument). Used for unit testing.
     */

    virtual void printVerification() = 0;

    /** Methods for printing the error report. The `print` method is needed due
     * to the fact that sub-classes define their own printing, and overloading
     * of `<<` does not support sub-classing.
     */

    friend ostream &operator<<(ostream &os, const MonitorError &error);
    virtual ostream& print(ostream& os) const;

protected:

    /**
     * Name of the monitor the error occurred in.
     */

    string monitorName;

    /**
     * Abstract syntax tree of the state the error occurred in.
     */

    ast::State* stateAST;

    /**
     * The binding of the state in which the error occurred.
     */

    Binding binding;

};


#endif //LOGSCOPE_MONITORERROR_H
