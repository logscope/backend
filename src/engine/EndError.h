//
// Created by Havelund, Klaus (348B) on 1/18/21.
//

#ifndef LOGSCOPE_ENDERROR_H
#define LOGSCOPE_ENDERROR_H

#include <ostream>
#include "MonitorError.h"
#include "ErrorReport.h"

/**
 * Represents an error detected when monitoring terminates. It will be
 * caused by some monitoring being in a hot state.
 */

class EndError : public MonitorError {

public:

    /**
     * Constructor.
     *
     * @param monitorName the monitor the error occurred in.
     * @param state the state the error occurred in.
     * @param binding the binding of state parameter names to values.
     */

    EndError(string monitorName, ast::State* state, Binding binding);

    virtual ErrorReport getErrorReport() override;
    virtual void printVerification() override;
    virtual void verifyError(ErrorReport errorExpected) override;
    virtual ostream& print(ostream& os) const override;

};

#endif //LOGSCOPE_ENDERROR_H
