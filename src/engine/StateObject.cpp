//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#include "SpecObject.h"
#include "MonitorObject.h"
#include "StateObject.h"
#include "EndError.h"
#include "TransitionError.h"
#include "NextError.h"

StateObject::StateObject(string name, Binding binding, ast::State *state, MonitorObject *monitor):
        name(name), binding(binding), stateAST(state), monitor(monitor) {}

bool StateObject::operator==(const StateObject& other) const {
   return name == other.name && binding == other.binding;
 }

size_t StateObject::Hash::operator()(const StateObject& b) const {
    hash<string> idHash;
    Binding::Hash bindingHash;
    return idHash(b.name) + bindingHash(b.binding);
}

void StateObject::eval() {
    DEBUG(cout << "processing state: " << *this)
    bool transitionFired = false;
    for (ast::Transition *transition : stateAST->transitions) {
        TransitionResult result = evalTransition(transition);
        if (result == TransitionResult::FAILED) {
            monitor->reportError(
                    new TransitionError(monitor->name,
                                        stateAST,
                                        binding,
                                        monitor->event,
                                        monitor->spec->getEventCount(),
                                        transition));
        };
        transitionFired = transitionFired || (result != TransitionResult::SILENT);
    };
    if (stateAST->isNext && !transitionFired) {
        monitor->reportError(
                new NextError(monitor->name,
                              stateAST,
                              binding,
                              monitor->event,
                              monitor->spec->getEventCount()));
    };
    if (!stateAST->isAlways && (stateAST->isNext || stateAST->isStep || transitionFired)) {
        monitor->recordStateToDelete(*this);
    }
}

TransitionResult StateObject::evalTransition(ast::Transition *transition) {
    DEBUG(cout << "evaluating transition: " << *transition)
    unordered_set<Binding,Binding::Hash> bindings = evalTransitionLHS(transition);
    DEBUG(
            cout << "bindings from evaluating LHS: ";
            for (Binding binding : bindings) {
                cout << binding;
            }
            )
    if (bindings.size() > 0) {
      bool failed = evalTransitionRHS(bindings, transition);
      if (failed) {
          return TransitionResult::FAILED;
      } else {
          return TransitionResult::MOVED;
      }
    } else {
        return TransitionResult::SILENT;
    };
}

unordered_set<Binding, Binding::Hash> StateObject::evalTransitionLHS(ast::Transition *transition) {
    Option<Binding> optBinding = monitor->evalPatternAgainstFact(binding, transition->eventPattern, monitor->event.name, monitor->event.binding);
    if (!optBinding.defined) {
        return unordered_set<Binding,Binding::Hash>();
    };
    unordered_set<Binding,Binding::Hash> bindings = {optBinding.value};
    for (ast::Pattern* pattern : transition->cond) {
        unordered_set<Binding,Binding::Hash> newBindings = {};
        for (Binding binding : bindings) {
            unordered_set<Binding,Binding::Hash> bindingsForPattern = monitor->evalPattern(binding, pattern);
            for (Binding bindingForPattern : bindingsForPattern) {
                newBindings.insert(bindingForPattern);
            }
        }
        bindings = newBindings;
    };
    return bindings;
}

bool StateObject::evalTransitionRHS(unordered_set<Binding, Binding::Hash> bindings, ast::Transition *transition) {
    bool failed = false;
    for (Binding binding : bindings) {
        for (ast::Pattern *pattern : transition->action) {
            if (pattern->isError) {
                failed = true;
            } else if (!pattern->isOk) {
                StateObject state = mkStateFromPattern(binding, pattern);
                if (pattern->positive) {
                    monitor->recordStateToAdd(state);
                } else {
                    monitor->recordStateToDelete(state);
                }
            }
        }
    }
    return failed;
}

StateObject StateObject::mkStateFromPattern(Binding binding, ast::Pattern *pattern) {
    string nameOfState = pattern->identifier;
    Binding bindingOfState = mkBindingFromPattern(binding, pattern);
    ast::State *astOfState = monitor->monitorAST->getState(nameOfState);
    return StateObject(nameOfState, bindingOfState,astOfState, monitor);
}

Binding StateObject::mkBindingFromPattern(Binding binding, ast::Pattern *pattern) {
    Binding bindingOfNewState;
    for (ast::Constraint *constraint : pattern-> constraints) {
        string fieldName = constraint->identifier;
        switch (constraint->range->kind) {
            case ast::Range::Kind::WILDCARD :
                assert(false);
                break;
            case ast::Range::Kind::NAME :
                {
                    string constraintName = constraint->range->str;
                    string valueInBinding = binding.get(constraintName);
                    bindingOfNewState.put(fieldName, valueInBinding);
                };
                break;
            case ast::Range::Kind::VALUE :
                {
                    string constraintValue = constraint->range->str;
                    bindingOfNewState.put(fieldName, constraintValue);
                };
                break;

        };
    };
    return bindingOfNewState;
}

void StateObject::end() {
    if (stateAST->isHot) {
        EndError *errorEnd = new EndError(monitor->name, stateAST, binding);
        monitor->reportError(errorEnd);
    };
}

ostream &operator<<(ostream &os, const StateObject &object) {
    os << object.name << " with " << object.binding;
    return os;
}
