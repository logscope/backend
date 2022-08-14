//
// Created by Havelund, Klaus (348B) on 2/1/21.
//

#ifndef LOGSCOPE_OPTION_H
#define LOGSCOPE_OPTION_H

/**
 * Represents an optional value.
 *
 * Note that from C++'17 optional values are supported. We had to implement it
 * this (not too satisfactory) way since this application is developed in C++'14.
 *
 * @tparam T the type of the optional value.
 */

template <class T>
struct Option {

    /**
     * Constructor.
     *
     * @param defined true iff. the value is defined, That is, false corresponds to `None`.
     * @param value the optional value. If `defined` is false, some random value is supplied.
     */

    Option(bool defined, T value): defined(defined), value(value) {}

    /**
     * True of the value is defined.
     */

    bool defined;

    /**
     * The value. If `defined` is false, this value has no use.
     */

    T value;

};

#endif //LOGSCOPE_OPTION_H
