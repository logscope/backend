//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#ifndef LOGSCOPE_AST_H
#define LOGSCOPE_AST_H

#include <list>
#include <map>
#include "../util/util.h"

using namespace std;

/**
 * The abstract syntax of the Scope specification language.
 */

namespace ast {

// =====
// Range
// =====

    struct Range {
        enum Kind {WILDCARD,NAME,VALUE};
        Range(Kind kind, string str);
        friend ostream& operator<<(std::ostream &out, const Range &r);
        Kind kind;
        string str;
    };

// ==========
// Constraint
// ==========

    struct Constraint
    {
        Constraint(string id, Range *r);
        friend ostream& operator<<(ostream &out, const Constraint &c);
        string identifier;
        Range  *range;
    };

// =======
// Pattern
// =======

    struct Pattern
    {
        Pattern(bool pos, string id, list<Constraint*> cs);
        friend ostream& operator<<(ostream& out, const Pattern& p);
        bool positive;
        string identifier;
        list<Constraint*> constraints;
        bool isError;
        bool isOk;
    };

// ==========
// Transition
// ==========

    struct Transition
    {
        Transition(Pattern *e, list<Pattern*> c, list<Pattern*> a);
        friend ostream& operator<<(ostream& out, const Transition& tr);
        int transitionNr;
        Pattern* eventPattern;
        list<Pattern*> cond;
        list<Pattern*> action;
    };

// ========
// Modifier
// ========

    enum Modifier {init,always,hot,next,step};

    ostream& operator<<(ostream& out, const Modifier& m);

// =====
// State
// =====

    struct State
    {
        State(list<Modifier> ms, string n, list<string> fs, list<Transition*> ts);
        friend ostream& operator<<(ostream& out, const State& s);
        list<Modifier> modifiers;
        bool isInit;
        bool isAlways;
        bool isHot;
        bool isNext;
        bool isStep;
        string name;
        list<string> formals;
        list<Transition*> transitions;
    };

// =======
// Monitor
// =======

    struct Monitor
    {
        Monitor(string n);
        Monitor(string n, list<string> es, list<State*> ss);
        void addEvent(string e);
        void addState(State *s);
        State* getState(string name);
        friend ostream& operator<<(ostream& out, const Monitor& m);
        string name;
        list<string> events;
        list<State*> states; // order of states needed for printing
        map<string,State*> stateMap; // indexed states for fast lookup
    };

// =============
// Spec
// =============

    struct Spec
    {
        Spec();
        Spec(list<Monitor*> ms);
        void addMonitor(Monitor *m);
        friend ostream& operator<<(ostream& out, const Spec& s);
        list<Monitor*> monitors;
    };

}

#endif //LOGSCOPE_AST_H
