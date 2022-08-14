//
// Created by Havelund, Klaus (348B) on 3/29/21.
//

#ifndef LOGSCOPE_TEST5_H
#define LOGSCOPE_TEST5_H

#include "contract.h"
#include "../../src/engine/Binding.h"
#include <unordered_map>

namespace suite5 {

    void test1() {
        SpecObject contract = makeContract();

        list<Event> events = {
                Event(10, "command", {{"cmd",  "TURN"},
                                      {"kind", "FSW"}}),
                Event(20, "command", {{"cmd",  "TRACK"},
                                      {"kind", "FSW"}}),
                Event(30, "succeed", {{"cmd", "TURN"}}),
                Event(40, "succeed", {{"cmd", "TRACK"}}),
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
                Event(10, "command", {{"cmd",  "TURN"},
                                      {"kind", "FSW"}}),
                Event(20, "command", {{"cmd",  "TRACK"},
                                      {"kind", "FSW"}}),
                Event(30, "succeed", {{"cmd", "TURN"}}),
                Event(40, "command", {{"cmd",  "TRACK"},
                                      {"kind", "FSW"}}),
                Event(50, "succeed", {{"cmd", "TRACK"}}),
        };

        for (Event &e : events) {
            contract.eval(e);
        };
        contract.end();

        // === verify ===
        contract.verifyErrors({
                                      ErrorReport("TransitionError", "M2", "Succeed", Binding{{{"c", "TRACK"}}}, 4,
                                                  2),
                              });
        // --------------
    }

    void test3() {
        SpecObject contract = makeContract();

        list<Event> events = {
                Event(10, "command", {{"cmd",  "TURN"},
                                      {"kind", "FSW"}}),
                Event(20, "command", {{"cmd",  "TRACK"},
                                      {"kind", "FSW"}}),
                Event(30, "succeed", {{"cmd", "TURN"}}),
                Event(40, "command", {{"cmd",  "BOOT"},
                                      {"kind", "FSW"}}),
                Event(50, "command", {{"cmd",  "PICT"},
                                      {"kind", "FSW"}}),
                Event(60, "succeed", {{"cmd", "TRACK"}}),
        };

        for (Event &e : events) {
            contract.eval(e);
        };
        contract.end();

        // === verify ===
        contract.verifyErrors({
                                      ErrorReport("EndError", "M2", "Succeed", Binding{{{"c", "BOOT"}}}, -1, -1),
                                      ErrorReport("EndError", "M2", "Succeed", Binding{{{"c", "PICT"}}}, -1, -1),
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
