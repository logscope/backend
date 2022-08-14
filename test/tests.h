//
// Created by Havelund, Klaus (348B) on 3/29/21.
//

#ifndef LOGSCOPE_TESTS_H
#define LOGSCOPE_TESTS_H

#include "suite1/test1.h"
#include "suite2/test2.h"
#include "suite3/test3.h"
#include "suite4/test4.h"
#include "suite5/test5.h"
#include "suite6/test6.h"
#include "suite7/test7.h"
#include "suite8/test8.h"

#define GREEN   "\033[32m"
#define RESET   "\033[0m"

/**
 * Runs all unit tests. If we reach the last print statement
 * of "ALL TESTS VERIFY!", it means all tests verified.
 */

void all_tests() {
    //suite1::test();
    //suite2::test();
    //suite3::test();
    //suite4::test();
    //suite5::test();
    //suite6::test();
    //suite7::test();
    suite8::test();

    cout << endl << GREEN << "ALL TESTS VERIFY!" << RESET << endl;
}

#endif //LOGSCOPE_TESTS_H
