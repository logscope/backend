//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#include "SpecObject.h"
#include "MonitorObject.h"
#include "Option.h"
#include "util.h"

MonitorObject::MonitorObject(ast::Monitor *m, SpecObject *s):
        monitorAST(m), spec(s), errors({}), name(m->name), event{}, states({}) {
    if (m->events.empty()) {
        eventNames = getUsedEventNames();
    } else {
        for (string name : m->events) {
            eventNames.insert(name);
        }
    }
    addInitialStates();
}

void MonitorObject::eval(Event e) {
    if (isRelevant(e)) {
        // cout << "@ monitor " << monitorAST->name << endl;
        event = e;
        statesToDelete.clear();
        statesToAdd.clear();
        for (auto state : states) {
            state.eval();
        }
        for (auto &state : statesToDelete) {
            states.erase(state);
        }
        for (auto &state : statesToAdd) {
            states.insert(state);
        }
    }
}

void MonitorObject::end() {
  for (auto state : states) {
    state.end();
  }
}

void MonitorObject::addInitialStates() {
    for (ast::State *stateAST : monitorAST->states) {
      if (stateAST->isInit) {
          StateObject state(stateAST->name, Binding(), stateAST, this);
          states.insert(state);
      }
    }
}

unordered_set<string> MonitorObject::getUsedEventNames() {
    unordered_set<string> names;
    for (ast::State *state : monitorAST->states) {
        for (ast::Transition *transition : state->transitions) {
            names.insert(transition->eventPattern->identifier);
        }
    }
    return names;
}

bool MonitorObject::isRelevant(Event &event) {
    return (eventNames.find(event.name) != eventNames.end());
}

void MonitorObject::reportError(MonitorError *error) {
  errors.push_back(error);
  spec->reportError(error);
}

unordered_set<Binding, Binding::Hash> MonitorObject::evalPattern(Binding binding, ast::Pattern *pattern) {
    unordered_set<Binding, Binding::Hash> positiveBindings = evalAsPositivePattern(binding, pattern);
    if (pattern->positive) {
        return positiveBindings;
    } else {
        if (positiveBindings.empty()) {
            // positive pattern does not match => negative pattern matches
            return unordered_set<Binding,Binding::Hash>({Binding()});
        } else {
            // positive pattern matches => negative pattern does not
            return unordered_set<Binding,Binding::Hash>();
        }
    }
}

unordered_set<Binding, Binding::Hash> MonitorObject::evalAsPositivePattern(Binding binding, ast::Pattern *pattern) {
    unordered_set<Binding,Binding::Hash> bindings = {};
    for (StateObject state : states) {
        Option<Binding> optBinding = evalPatternAgainstFact(binding, pattern, state.name, state.binding);
        if (optBinding.defined) {
            bindings.insert(optBinding.value);
        }
    }
    return bindings;
}

Option<Binding> MonitorObject::evalPatternAgainstFact(Binding sourceBinding, ast::Pattern *pattern, string factName,
                                                 Binding factBinding) {
    if (pattern->identifier != factName) {
        return Option<Binding>(false, Binding());
    } else {
        Binding resultBinding = sourceBinding;
        for (ast::Constraint *constraint : pattern->constraints) {
            string fieldName = constraint->identifier;
            Option<string> optFactValue = factBinding.getOptionalValue(fieldName);
            if (!optFactValue.defined) {
                cout << "*** Warning: In monitor " << name << " in pattern " << *pattern <<
                " fieldName " << fieldName << " not defined in fact " << factName << factBinding << endl;
                return Option<Binding>(false, Binding());
            } else {
                string factValue = optFactValue.value;
                switch (constraint->range->kind) {
                    case ast::Range::Kind::WILDCARD :
                        break;
                    case ast::Range::Kind::NAME :
                        {
                            string constraintName = constraint->range->str;
                            Option<string> optSourceValue = sourceBinding.getOptionalValue(constraintName);
                            if (optSourceValue.defined) {
                                if (optSourceValue.value != factValue) {
                                    return Option<Binding>(false, Binding());
                                }
                            } else {
                                resultBinding.put(constraintName, factValue);
                            }
                        };
                        break;
                    case ast::Range::Kind::VALUE :
                        {
                            string constraintValue = constraint->range->str;
                            if (constraintValue != factValue) {
                                return Option<Binding>(false, Binding());
                            };
                        };
                        break;
                }
            }
        };
        return Option<Binding>(true, resultBinding);
    }
}

void MonitorObject::recordStateToDelete(StateObject state) {
    DEBUG(cout << "record state to delete: " << state)
    statesToDelete.insert(state);
}

void MonitorObject::recordStateToAdd(StateObject state) {
    DEBUG(cout << "record state to add: " << state)
    statesToAdd.insert(state);
}

vector<MonitorError*> MonitorObject::getAllErrors() {
    return errors;
}

ostream &operator<<(ostream &os, const MonitorObject &monitor) {
    os << "monitor " << monitor.name << ":" << endl;
    if (monitor.states.empty()) {
        os << "  NO STATES" << endl;
    } else {
        for (StateObject state : monitor.states) {
            os << "  " << state << endl;
        };
    }
    return os;
}
