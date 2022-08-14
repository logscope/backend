//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#include "util.h"

bool startsWith(string str, string prefix) {
    return str.rfind(prefix, 0) == 0;
}

string quote(string s) {
    string result;
    result += "\"";
    result += s;
    result += "\"";
    return result;
}
