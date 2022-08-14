//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#ifndef LOGSCOPE_SPECOBJECT_H
#define LOGSCOPE_SPECOBJECT_H

#include "../ast/ast.h"
#include "MonitorObject.h"
#include "Options.h"
#include "ErrorReport.h"

/**
 * Represents the collection of all monitors specified in the specification.
 */

class SpecObject {

public:

    /**
     * Constructor.
     *
     * @param spec the abstract syntax tree for the specification.
     */

    SpecObject(ast::Spec *spec);

    /**
     * Evaluates an event against all monitors.
     *
     * @param e the event to be evaluated.
     */

    void eval(Event &e);

    /**
     * Terminates monitoring.
     */

    void end();

    /**
     * Evaluates a trace, a list of events. At the end it calls
     * the `end()` method.
     *
     * @param events the trace to be evaluated.
     */

    void eval(list<Event> events);

    /**
     * Reports an error.
     *
     * @param error the error to be reported.
     */

    void reportError(MonitorError* error);

    /**
     * Returns all the errors detected during monitoring.
     *
     * @return the errors reported.
     */

    vector<MonitorError*> getAllErrors();

    /**
     * Returns the current number of events evaluated.
     *
     * @return the number of events evaluated.
     */

    unsigned long int getEventCount();

    /**
     * Returns the number of errors detected during monitoring.
     *
     * @return the number of errors detected.
     */

    int getErrorCount();

    /**
     * Returns the reports of all errors detected.
     *
     * @return the reports of all errors detected.
     */

    vector<ErrorReport> getErrorReports();

    /**
     * Verifies the actually detected errors against the error reports provided as
     * argument. Used for unit testing.
     *
     * @param errorsExpected
     */

    void verifyErrors(vector<ErrorReport> errorsExpected);

    /**
     * Prints on standard out a call of `verifyErrors` with the currently detected errors
     * as argument. Is used for creating a test oracle used in unit testing.
     */

    void printVerification();

    /**
     * The options of LogScope.
     */

    Options options;

private:

    /**
     * Prints a welcome message when running the tool, including verison number,
     * and the specification being monitored.
     */

    void printWelcome();

    /**
     * Prints progress on standard out, controlled by the value of the
     * `Options.SHOW_PROGRESS` variable.
     *
     * @param event the current event.
     */

    void showProgress(Event& event);

    /**
     * In case `Options.SHOW_PROGRESS == 1` this method will print
     * the frontier (active states) of each monitor.
     */

    void printStates();

    /**
     * Prints a summary of the monitoring at the end of monitoring.
     */

    void printSummary();

    /**
     * Returns a string containing a number of space determined by the argument.
     *
     * @param number the number of spaces to generate.
     * @return string containing `number` spaces.
     */

    string spaces(int number);

    /**
     * The abstract syntax tree of the specification.
     */

    ast::Spec *specAST;

    /**
     * The monitors of the specification.
     */

    list<MonitorObject*> monitors;

    /**
     * The number of events currently processed.
     */

    unsigned long int eventCount;

    /**
     * The number errors currently detected.
     */

    int errorCount;

};

#endif //LOGSCOPE_SPECOBJECT_H
