
// -------------
// Main program:
// -------------

#include "contract.h"

int mainINACTIVE() {
    // Create a monitor from the generated code in contract.cpp:
    SpecObject contract = makeContract();

    // Set options for debugging purposes if needed:
    contract.options.SHOW_PROGRESS = 1;
    // value 0 : no debugging information printed.
    // value 1 : every event processed is printed together with internal monitor states.
    // value N > 1 : event count printed for every N'th event.

    // An example trace:
    list<Event> events = {
            Event(10, "command", {{"cmd",  "TURN"},
                                  {"kind", "FSW"}}),
            Event(20, "command", {{"cmd",  "TRACK"},
                                  {"kind", "FSW"}}),
            Event(30, "succeed", {{"cmd", "TURN"}}),
            Event(40, "command", {{"cmd",  "PICT"},
                                  {"kind", "FSW"}}),
            Event(50, "succeed", {{"cmd", "SEND"}}),
            Event(60, "command", {{"cmd",  "PICT"},
                                  {"kind", "FSW"}})
    };

    // Monutor the trace, event by event:
    for (Event &e : events) {
        contract.eval(e);
    };

    // Terminate monitoring:
    contract.end();

    // Process detected errors manually if needed:
    cout << endl << endl << "Processing the result:" << endl << endl;
    cout << contract.getEventCount() << " events processed" << endl;
    cout << contract.getErrorCount() << " errors encountered" << endl;
    cout << endl;
    vector<ErrorReport> errors = contract.getErrorReports();
    for (ErrorReport error : errors) {
        cout <<
             error.kind << ", " <<
             error.monitorName << ", " <<
             error.stateName << ", " <<
             error.binding << ", " <<
             error.eventCount << ", " <<
             error.transitionCount <<
             endl;
    }

    // To run examples in examples directory, e.g. example 7:
    // #include "examples/example7/example7.h"
    // Run all examples in example 7:
    // example7::test();
    // Run one of the examples:
    // example7::test1();

    return 0;
 }
