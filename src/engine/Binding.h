//
// Created by Havelund, Klaus (348B) on 1/12/21.
//

#ifndef LOGSCOPE_BINDING_H
#define LOGSCOPE_BINDING_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include "Option.h"

using namespace std;

/**
 * Represents a binding from field names to values, a mapping in other words.
 * It is represented by an unordered map.
 */

class Binding {

public:

    /**
     * Constructor.
     *
     * The map in the binding will be constructed with additional method calls.
     */

    Binding();

    /**
     * Constructor.
     *
     * @param binding the map contained in the binding.
     */

    Binding(unordered_map<string,string> binding);

    /**
     * Inserts an entry from a key (field name) to a value in the binding.
     *
     * @param key the key (field name).
     * @param value the value that the key maps to.
     */

    void put(string key, string value);

    /**
     * Returns (a reference to) the value mapped to by a key.
     *
     * @param key the key.
     * @return the value the key maps to.
     */

    string& get(string key);

    /**
     * Returns an optional value mapped to by a key. The value is
     * optional since the key may not be defined in the binding.
     *
     * @param key the key.
     * @return the optional value.
     */

    Option<string> getOptionalValue(string key);

    friend ostream &operator<<(ostream &os, const Binding &binding);
    bool operator==(const Binding& other) const;
    struct Hash {size_t operator()(const Binding& b) const;};

private:

    /**
     * The map representing the entries in the binding: a mapping from
     * field names to values.
     */

    unordered_map<string,string> binding;

};

#endif //LOGSCOPE_BINDING_H
