//
// Created by Havelund, Klaus (348B) on 1/20/21.
//

#ifndef LOGSCOPE_TRANSITIONERROR_H
#define LOGSCOPE_TRANSITIONERROR_H

#include <ostream>
#include "MonitorError.h"
#include "ErrorReport.h"
#include "Event.h"
#include "../ast/ast.h"

/**
 * Represents a transition error. That is an error where a transition leads to the `error` state.
 */

class TransitionError: public MonitorError {

public:

    /**
     * Constructor.
     *
     * @param monitorName the monitor the error occurred in.
     * @param state the state the error occurred in.
     * @param binding the binding of state parameter names to values.
     * @param event the event causing the error.
     * @param eventCount number of the event causing the error.
     * @param transition the transition causing the error.
     */

    TransitionError(string monitorName, ast::State* state, Binding binding, Event event, int eventCount, ast::Transition * transition);

    virtual ErrorReport getErrorReport() override;
    virtual void printVerification() override;
    virtual void verifyError(ErrorReport errorExpected) override;
    virtual ostream& print(ostream& os) const override;

protected:

    /**
     * The event causing the error.
     */

    Event event;

    /**
     * Number of the event causing the error.
     */

    int eventCount;

    /**
     * Abstract syntax tree of the transition causing the error.
     */

    ast::Transition *transitionAST;

};


#endif //LOGSCOPE_TRANSITIONERROR_H
