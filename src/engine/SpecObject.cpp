//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#include <algorithm>
#include <utility>
#include "SpecObject.h"
#include "MonitorObject.h"

using namespace std;

SpecObject::SpecObject(ast::Spec *spec) : specAST(spec), eventCount(0), errorCount(0) {
    for (ast::Monitor *monitor : spec->monitors) {
        monitors.push_back(new MonitorObject(monitor, this));
    }
    printWelcome();
}

void SpecObject::eval(Event &e) {
    eventCount++;
    showProgress(e);
    for (MonitorObject *m : monitors) {
        m->eval(e);
    };
    printStates();
}

void SpecObject::end() {
    cout << endl;
    cout << "Ending monitoring!" << endl;
    cout << endl;
    for (MonitorObject *observer : monitors) {
        observer->end();
    };
    printSummary();
}

void SpecObject::eval(list<Event> events) {
    for (Event &event : events) {
        eval(event);
    }
    end();
}

void SpecObject::reportError(MonitorError *error) {
    errorCount++;
    cout << "======= Error " << errorCount << ": =======" << endl;
    cout << *error << endl;
    cout << "----------------------" << endl << endl;
}

void SpecObject::printWelcome() {
    // https://fsymbols.com/generators/carty/
    cout << endl;
    cout << R"(
🅻🅾🅶🆂🅲🅾🅿🅴 Version 1.0.0
        )";
    cout << endl;
    cout << "Monitoring the specification:" << endl << endl;
    cout << "=========================" << endl;
    cout << *specAST;
    cout << "-------------------------" << endl << endl;
    cout << "Monitoring begins!" << endl;
    printStates();
}

void SpecObject::showProgress(Event &event) {
    if (options.SHOW_PROGRESS == 1) {
        cout << endl;
        cout << "=========================" << endl;
        cout << event << " #" << eventCount << endl;
        cout << "-------------------------" << endl;
        cout << endl;
    } else if (options.SHOW_PROGRESS > 1 && (eventCount % options.SHOW_PROGRESS == 0)) {
        cout << "event: " << eventCount << endl;
    }
}

void SpecObject::printStates() {
    if (options.SHOW_PROGRESS == 1) {
        cout << endl;
        cout << "=== monitor states: ===" << endl;
        for (MonitorObject *monitor : monitors) {
            cout << *monitor;
        };
        cout << "-----------------------" << endl;
    }
}

vector<MonitorError *> SpecObject::getAllErrors() {
    vector<MonitorError *> errors;
    for (MonitorObject *monitor : monitors) {
        for (MonitorError *error : monitor->getAllErrors()) {
            errors.push_back(error);
        }
    }
    return errors;
}

void SpecObject::printSummary() {
    int totalNrOfErrors = 0;
    unsigned long maxMonitorNameLength = 0;
    list<pair<string, int>> errorCounts;
    for (MonitorObject *monitor : monitors) {
        int numberOfErrors = monitor->getAllErrors().size();
        totalNrOfErrors += numberOfErrors;
        maxMonitorNameLength = max(maxMonitorNameLength, monitor->name.size());
        errorCounts.push_back(make_pair(monitor->name, numberOfErrors));
    };
    cout << endl;
    cout << "==========================" << endl;
    cout << "Summary of Trace Analysis:" << endl;
    cout << "total number of events : " << eventCount << endl;
    cout << endl;
    for (auto[monitorName, nrErrors] : errorCounts) {
        cout << monitorName << " errors" << spaces(maxMonitorNameLength - monitorName.size()) << " : " << nrErrors
             << endl;
    }
    cout << endl;
    cout << "total number of errors : " << totalNrOfErrors << endl;
    cout << "--------------------------" << endl;
}

string SpecObject::spaces(int number) {
    string result;
    for (int i = 0; i < number; i++) {
        result += " ";
    };
    return result;
}

unsigned long int SpecObject::getEventCount() {
    return eventCount;
}

int SpecObject::getErrorCount() {
    return errorCount;
}

vector<ErrorReport> SpecObject::getErrorReports() {
    vector<ErrorReport> errorReports;
    for (MonitorError* error : getAllErrors()) {
        errorReports.push_back(error->getErrorReport());
    };
    return errorReports;
}

void SpecObject::verifyErrors(vector<ErrorReport> errorsExpected) {
    printVerification();
    vector<MonitorError *> errorsOccurred = getAllErrors();
    assert(errorsOccurred.size() == errorsExpected.size());
    for (int i = 0; i < errorsOccurred.size(); i++) {
        MonitorError *monitorError = errorsOccurred[i];
        ErrorReport errorExpected = errorsExpected[i];
        monitorError->verifyError(errorExpected);
    }
}

void SpecObject::printVerification() {
    cout << endl;
    cout << "    // === verify ===" << endl;
    vector<MonitorError *> errorsOccurred = getAllErrors();
    if (errorsOccurred.empty()) {
        cout << "    contract.verifyErrors({});" << endl;
    } else {
        cout << "    contract.verifyErrors({" << endl;
        for (MonitorError *error : errorsOccurred) {
            cout << "      ";
            error->printVerification();
            cout << ",";
            cout << endl;
        }
        cout << "    });" << endl;
    }
    cout << "    // --------------" << endl;
}
