//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#include "ast.h"

using namespace std;

namespace ast {

// =====
// Range
// =====

    Range::Range(Kind kind, string str): kind(kind), str(str) {};

    ostream& operator<<(std::ostream &out, const Range &r)
    {
        switch (r.kind) {
            case Range::Kind::WILDCARD :
                cout << "_";
                break;
            case Range::Kind::NAME :
                cout << r.str;
                break;
            case Range::Kind::VALUE :
                cout << "\"" << r.str << "\"";
                break;
        }
        return out;
    }

// ==========
// Constraint
// ==========

    Constraint::Constraint(string id, Range *r) : identifier(id), range(r) {}

    ostream& operator<<(ostream &out, const Constraint &c)
    {
        out << c.identifier << " : " << *c.range;
        return out;
    }

// =======
// Pattern
// =======

    Pattern::Pattern(bool pos, string id, list<Constraint*> cs) : positive(pos), identifier(id), constraints(cs), isError(id == "error"), isOk(id == "ok") {}

    ostream& operator<<(ostream& out, const Pattern& p)
    {
        if (!p.positive) {
            out << "!";
        };
        out << p.identifier;
        if (p.constraints.size() > 0) {
            out << "(";
            printList(out, p.constraints, ",");
            out << ")";
        }
        return out;
    }

// ==========
// Transition
// ==========

    Transition::Transition(Pattern *e, list<Pattern*> c, list<Pattern*> a) : eventPattern(e), cond(c), action(a) {}

    ostream& operator<<(ostream& out, const Transition& tr)
    {
        out << "[" << tr.transitionNr << "] ";
        out << *tr.eventPattern;
        if (!tr.cond.empty()) {
            out << " & ";
        }
        printList(out, tr.cond, ",");
        out << " => ";
        printList(out, tr.action, ",");
        return out;
    }

// ========
// Modifier
// ========

    ostream& operator<<(ostream& out, const Modifier& m) {
        switch (m) {
            case Modifier::init :
                out << "init";
                break;
            case Modifier::always :
                out << "always";
                break;
            case Modifier::hot :
                out << "hot";
                break;
            case Modifier::next :
                out << "next";
                break;
            case Modifier::step :
                out << "step";
                break;
        }
        return out;
    }

// =====
// State
// =====

    State::State(list<Modifier> ms, string n, list<string> fs, list<Transition*> ts) :
            modifiers(ms), name(n), formals(fs), transitions(ts) {
        isInit = listContains(ms, Modifier::init);
        isAlways = listContains(ms, Modifier::always);
        isHot = listContains(ms, Modifier::hot);
        isNext = listContains(ms, Modifier::next);
        isStep = listContains(ms, Modifier::step);
        int transitionNr = 0;
        for (Transition* transition : ts) {
          transitionNr++;
          transition->transitionNr = transitionNr;
        }
    }

    ostream& operator<<(ostream& out, const State& s)
    {
        if (!s.modifiers.empty()) {
            printList(out, s.modifiers, " ");
            out << ' ';
        };
        if (!startsWith(s.name,"INTERNAL_")) {
            out << s.name;
        };
        if (s.formals.size() > 0) {
            out << "(";
            printList(out, s.formals, ",");
            out << ")";
        }
        out << "{" << endl;
        out << "    ";
        printList(out, s.transitions, "\n    ");
        out << endl;
        out << "  }";
        return out;
    }

// =======
// Monitor
// =======

    Monitor::Monitor(string n) : name(n) {}
    Monitor::Monitor(string n, list<string> es, list<State*> ss) : name(n), events(es), states(ss) {
        for (State* state : ss) {
            stateMap[state->name] = state;
        }
    }

    void Monitor::addEvent(string e) {
       events.push_back(e);
    }

    void Monitor::addState(State *s) {
        states.push_back(s);
        stateMap[s->name] = s;
    }

    State *Monitor::getState(string name) {
        return stateMap[name];
    }

    ostream& operator<<(ostream& out, const Monitor& m)
    {
        out << "monitor " << m.name << "{" << endl;
        if (!m.events.empty()) {
            out << "  event ";
            printList(out, m.events, ", ");
            out << endl << endl;
        }
        out << "  ";
        printList(out, m.states, "\n\n  ");
        out << endl;
        out << "}";
        return out;
    }

// ====
// Spec
// ====

    Spec::Spec() {}
    Spec::Spec(list<Monitor*> ms) : monitors(ms){}

    void Spec::addMonitor(Monitor *m) {
        monitors.push_back(m);
    }

    ostream& operator<<(ostream& out, const Spec& s)
    {
        printList(out, s.monitors, "\n\n");
        out << endl;
        return out;
    }

}
