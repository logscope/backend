//
// Created by Havelund, Klaus (348B) on 3/30/21.
//

#include "ErrorReport.h"

ErrorReport::ErrorReport(string kind, string monitorName, string stateName, Binding binding, int eventCount, int transitionCount):
  kind(kind),
  monitorName(monitorName),
  stateName(stateName),
  binding(binding),
  eventCount(eventCount),
  transitionCount(transitionCount)
  {}

ostream &operator<<(ostream &os, const ErrorReport &error) {
    cout <<
         error.kind << ":" <<
         " monitor=" << error.monitorName <<
         " state=" << error.stateName <<
         " binding=" << error.binding;
    if (error.kind != "EndError") {
        cout << " eventNr=" << error.eventCount;
    }
    if (error.kind == "TransitionError") {
        cout << " transtionNr=" << error.transitionCount;
    }

    return os;
}