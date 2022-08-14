//
// Created by Havelund, Klaus (348B) on 3/29/21.
//

#ifndef LOGSCOPE_EXAMPLE7_H
#define LOGSCOPE_EXAMPLE7_H

#include "../../contract.h"

namespace example7 {

    void test1() {
        SpecObject contract = makeContract();

        list<Event> events = {
                Event(10, "command", {
                        {"cmd",  "TURN"},
                        {"nr",   "1"},
                        {"kind", "FSW"}}),
                Event(10, "command", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"},
                        {"kind", "FSW"}}),
                Event(10, "dispatch", {
                        {"cmd",  "TURN"},
                        {"nr",   "1"}}),
                Event(10, "dispatch", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"}}),
                Event(10, "succeed", {
                        {"cmd",  "TURN"},
                        {"nr",   "1"}}),
                Event(10, "succeed", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"}}),
                Event(10, "close", {
                        {"cmd",  "TURN"},
                        {"nr",   "1"}}),
                Event(10, "close", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"}}),
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
                Event(10, "command", {
                        {"cmd",  "TURN"},
                        {"nr",   "1"},
                        {"kind", "FSW"}}),
                Event(10, "command", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"},
                        {"kind", "FSW"}}),
                Event(10, "command", {
                        {"cmd",  "BOOT"},
                        {"nr",   "3"},
                        {"kind", "FSW"}}),
                Event(10, "dispatch", {
                        {"cmd",  "TURN"},
                        {"nr",   "1"}}),
                Event(10, "dispatch", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"}}),
                Event(10, "cancel", {
                        {"cmd",  "BOOT"},
                        {"nr",   "3"}}),
                Event(10, "fail", {
                        {"cmd",  "TURN"},
                        {"nr",   "1"}}),
                Event(10, "command", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"},
                        {"kind", "FSW"}}),
                Event(10, "succeed", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"}}),
                Event(10, "close", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"}}),
        };

        for (Event &e : events) {
            contract.eval(e);
        };
        contract.end();

        // === verify ===
        contract.verifyErrors({
                                      ErrorReport("TransitionError","M4","Succeed",Binding{{{"sc","TURN"},{"sn","1"}}},7,3),
                                      ErrorReport("TransitionError","M4","Succeed",Binding{{{"sc","TRACK"},{"sn","2"}}},8,2),
                                      ErrorReport("TransitionError","M4","INTERNAL__1",Binding(),9,2),
                                      ErrorReport("EndError","M4","Dispatch",Binding{{{"dc","TRACK"},{"dn","2"}}},-1,-1),
                              });
        // --------------
    }

    void test3() {
        SpecObject contract = makeContract();

        list<Event> events = {
                Event(10, "command", {
                        {"cmd",  "TURN"},
                        {"nr",   "1"},
                        {"kind", "FSW"}}),
                Event(10, "command", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"},
                        {"kind", "FSW"}}),
                Event(10, "dispatch", {
                        {"cmd",  "TURN"},
                        {"nr",   "1"}}),
                Event(10, "dispatch", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"}}),
                Event(10, "succeed", {
                        {"cmd",  "TURN"},
                        {"nr",   "1"}}),
                Event(10, "succeed", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"}}),
                Event(10, "close", {
                        {"cmd",  "TURN"},
                        {"nr",   "1"}}),
                Event(10, "succeed", {
                        {"cmd",  "TRACK"},
                        {"nr",   "2"}}),
        };

        for (Event &e : events) {
            contract.eval(e);
        };
        contract.end();

        // === verify ===
        contract.verifyErrors({
                                      ErrorReport("TransitionError","M4","NoMoreSuccess",Binding{{{"nc","TRACK"},{"nn","2"}}},8,1),
                                      ErrorReport("TransitionError","M4","INTERNAL__1",Binding(),8,2),
                                      ErrorReport("EndError","M4","Close",Binding{{{"cc","TRACK"},{"cn","2"}}},-1,-1),
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
