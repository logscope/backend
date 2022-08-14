//
// Created by Havelund, Klaus (348B) on 1/19/21.
//

#ifndef LOGSCOPE_NEXTERROR_H
#define LOGSCOPE_NEXTERROR_H

#include "MonitorError.h"
#include "Event.h"
#include "ErrorReport.h"

/**
 * Represents an error occurring when a monitor is in a `next` state, and the next
 * event does not match any of the transitions of the state.
 */

class NextError: public MonitorError {

public:

    /**
     * Constructor.
     *
     * @param monitorName the monitor the error occurred in.
     * @param state the state the error occurred in.
     * @param binding the binding of state parameter names to values.
     * @param event the event causing the error.
     * @param eventCount number of the event causing the error.
     */

    NextError(string monitorName, ast::State* state, Binding binding, Event event, int eventCount);

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

};


#endif //LOGSCOPE_NEXTERROR_H

