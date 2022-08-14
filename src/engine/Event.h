//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#ifndef LOGSCOPE_EVENT_H
#define LOGSCOPE_EVENT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "Binding.h"

using namespace std;

/**
 * Represents an event submitted to the monitor.
 * An event consists of a time stamp, a name, and a map
 * from field names to values.
 */

class Event {

public:

    /**
     * Constructor of empty event.
     */

    Event();

    /**
     * Constructor.
     *
     * @param time the time stamp.
     * @param name the event name.
     * @param data the map from field names to values.
     */

    Event(int time, string name, unordered_map<string,string> data);

    friend ostream& operator<<(ostream& out, const Event& ev);

    int time;
    string name;
    Binding binding;

};

#endif //LOGSCOPE_EVENT_H

