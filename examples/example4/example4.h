//
// Created by Havelund, Klaus (348B) on 3/29/21.
//

#ifndef LOGSCOPE_EXAMPLE4_H
#define LOGSCOPE_EXAMPLE4_H

#include "../../contract.h"

namespace example4 {

    void test1() {
        SpecObject contract = makeContract();

        list<Event> events = {
                Event(10, "command", {}),
                Event(20, "succeed", {}),
                Event(30, "command", {}),
                Event(40, "succeed", {})
        };

        for (Event &e : events) {
            contract.eval(e);
        };
        contract.end();

        // === verify ===
        contract.verifyErrors({});
        // --------------
    }

    void test2() {
        SpecObject contract = makeContract();

        list<Event> events = {
                Event(10, "command", {}),
                Event(20, "command", {}),
                Event(30, "succeed", {}),
                Event(40, "succeed", {})
        };

        for (Event &e : events) {
            contract.eval(e);
        };
        contract.end();

        // === verify ===
        contract.verifyErrors({
                                      ErrorReport("TransitionError","M1c","Succeed",Binding(),2,2),
                              });
        // --------------
    }

    void test3() {
        SpecObject contract = makeContract();

        list<Event> events = {
                Event(10, "command", {}),
                Event(20, "succeed", {}),
                Event(30, "command", {})
        };

        for (Event &e : events) {
            contract.eval(e);
        };
        contract.end();

        // === verify ===
        contract.verifyErrors({
                                      ErrorReport("EndError","M1c","Succeed",Binding(),-1,-1),
                              });
        // --------------
    }

    void test() {
        test1();
        test2();
        test3();
    }

}

#endif
