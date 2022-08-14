//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#ifndef LOGSCOPE_UTIL_H
#define LOGSCOPE_UTIL_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

/**
 * Prints a list of values referenced by pointers.
 *
 * @tparam T the type of value.
 * @param out the output stream.
 * @param list the list of pointers to values.
 * @param sep the symbol separating the values.
 * @return the formatted list.
 */

template <class T> ostream& printList(ostream& out, const list<T*>& list, string sep)
{
    bool doSep = false;
    for (T* e : list) {
        if (doSep) {
            out << sep;
        } else {
            doSep = true;
        };
        out << *e;
    }
    return out;
}

/**
 * Prints a list of values.
 *
 * @tparam T the type of value.
 * @param out the output stream.
 * @param list the list of values.
 * @param sep the symbol separating the values.
 * @return the formatted list.
 */

template <class T> ostream& printList(ostream& out, const list<T>& list, string sep)
{
    bool doSep = false;
    for (T e : list) {
        if (doSep) {
            out << sep;
        } else {
            doSep = true;
        };
        out << e;
    }
    return out;
}

/**
 * Returns true of the provided list contains the provided element.
 *
 * @tparam T type of list elements.
 * @param list the list of values.
 * @param elem the value searched for.
 * @return true iff. the list contains the value.
 */

template <class T> bool listContains(list<T> list, T elem) {
    for (auto e : list) {
        if (e == elem) return true;
    };
    return false;
}

/**
 * Returns true of a string starts with a provided prefix.
 *
 * @param str the full string.
 * @param prefix the prefix searched for.
 * @return true iff. `prefix` is indeed a prefix of `str`.
 */

bool startsWith(string str, string prefix);

/**
 * Adds quotes to a string. Needed for printing strings as strings with quotes.
 *
 * @param s the string to be quoted.
 * @return the string `s` with quotes around.
 */

string quote(string s);

//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
  #define DEBUG(code) {cout << "--- "; code; cout << endl;}
#else
  #define DEBUG(code)
#endif

#endif //LOGSCOPE_UTIL_H
