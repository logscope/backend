//
// Created by Havelund, Klaus (348B) on 1/12/21.
//

#include "Binding.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

using namespace std;

Binding::Binding() {}

Binding::Binding(unordered_map<string, string> binding) : binding(binding) {}

void Binding::put(string key, string value) {
    binding[key] = value;
}

string &Binding::get(string key) {
    auto pairIt = binding.find(key);
    assert (pairIt != binding.end());
    return pairIt->second;
}

Option<string> Binding::getOptionalValue(string key) {
    auto pairIt = binding.find(key);
    if (pairIt == binding.end()) {
        return Option<string>(false, "");
    } else {
        return Option<string>(true, pairIt->second);
    };
}

ostream &operator<<(ostream &os, const Binding &binding) {
    if (binding.binding.empty()) {
        os << "Binding()";
    } else {
        os << "Binding{";
        string comma = "";
        os << "{";
        for (auto &pair : binding.binding) {
            os << comma << "{" << "\"" << pair.first << "\"" << "," << "\"" << pair.second << "\"" << "}";
            comma = ",";
        }
        os << "}";
        os << "}";
    }
    return os;
}

bool Binding::operator==(const Binding &other) const {
    if (binding.size() != other.binding.size()) return false;
    for (auto &pair : binding) {
        auto otherValueIt = other.binding.find(pair.first);
        if (otherValueIt == other.binding.end()) return false;
        if (otherValueIt->second != pair.second) return false;
    };
    return true;
}

size_t Binding::Hash::operator()(const Binding &b) const {
    hash<string> hashVal;
    size_t hash = 0;
    for (auto &pair : b.binding) {
        hash += hashVal(pair.first) + hashVal(pair.second);
    };
    return hash;
}
