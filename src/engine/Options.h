//
// Created by Havelund, Klaus (348B) on 2/9/21.
//

#ifndef LOGSCOPE_OPTIONS_H
#define LOGSCOPE_OPTIONS_H

/**
 * The options for LogScope.
 */

struct Options {

    /**
     * Controls the amount of output generated during monitoring.
     *
     * Possible values:
     *
     * 0 : minimal output, essentially only the monitored specification, error messages, and status report at the end.
     *     The minimal out is always printed, also for other values on this variable.
     *
     * 1 : additional debugging information is printed for each event:
     *     - the event
     *     - the event number
     *     - the frontier of each monitor after evaluating the event
     *
     * N>1 : prints a count of events processed for each Nth event. Useful
     *     for knowing how far the monitor has gotten when processing a large
     *     log file for example.
     *
     * The default value is 0 but can be set by the user in the main program in `main.cpp`.
     */

    int SHOW_PROGRESS = 0;

};


#endif //LOGSCOPE_OPTIONS_H
