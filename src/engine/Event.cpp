//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#include "Event.h"

using namespace std;

Event::Event(): time(0), name(""), binding{}{}

Event::Event(int time, string name, unordered_map<string, string> data): time(time), name(name), binding(data) {}

ostream &operator<<(ostream &out, const Event &ev) {
    out << ev.name << " with " << ev.binding;
    return out;
}
