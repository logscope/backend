//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#ifndef LOGSCOPE_MONITOROBJECT_H
#define LOGSCOPE_MONITOROBJECT_H

#include <unordered_set>
#include <vector>
#include <ostream>
#include "../ast/ast.h"
#include "Event.h"
#include "StateObject.h"
#include "MonitorError.h"
#include "Option.h"

class SpecObject;

/**
 * Represents a monitor.
 */

class MonitorObject {

public:

    /**
     * Constructor.
     *
     * @param m the abstract syntax tree corresponding to the monitor.
     * @param s the specification object (specification) it is part of.
     */

    MonitorObject(ast::Monitor *m, SpecObject * s);

    /**
     * The name of the monitor.
     */

    const string name;

    /**
     * Evaluates the monitor on a submitted event.
     *
     * @param e the submitted event.
     */

    void eval(Event e);

    /**
     * Ends monitoring.
     */

    void end();

    /**
     * Reports an error.
     *
     * @param error the error to be reported.
     */

    void reportError(MonitorError * error);

    /**
     * Given a binding, determined by the current state and previous pattern matches in the
     * current transition: evaluates the pattern against the frontier of states of the monitor.
     * The resulting set of bindings represent all the possible matches.
     *
     * Note that if the pattern is negated, a match is returned as a set containing an empty binding
     * if there are no matches. If there is a match, an empty set is returned.
     *
     * @param binding the current binding, determined by the current state and previous pattern matches in the
     *   current transition.
     * @param pattern the pattern to be matched.
     * @return the set of bindings corresponding to the matches of the pattern against the frontier of the monitor.
     */

    unordered_set<Binding,Binding::Hash> evalPattern(Binding binding, ast::Pattern *pattern);

    /**
     * Matches a pattern against a particular fact.
     *
     * @param sourceBinding the current binding, determined by the current state and previous pattern matches in the
     *   current transition.
     * @param pattern the pattern to be matched.
     * @param factName the name of the fact being matched against.
     * @param factBinding the binding of the fact being matched against.
     * @return the optional binding corresponding to the match of the pattern against the fact. It is
     *   optional since there might not be a match
     */

    Option<Binding> evalPatternAgainstFact(Binding sourceBinding, ast::Pattern * pattern, string factName, Binding factBinding);

    /**
     * During monitoring, we record states to be deleted later after evaluating an event.
     *
     * @param state the state to be deleted.
     */

    void recordStateToDelete(StateObject state);

    /**
     * During monitoring, we record states to be added later after evaluating an event.
     *
     * @param state the state to be added.
     */

    void recordStateToAdd(StateObject state);

    /**
     * Returns all errors detected.
     *
     * @return the errors detected in this monitor.
     */

    vector<MonitorError*> getAllErrors();

    friend ostream &operator<<(ostream &os, const MonitorObject &object);

    /**
     * The current event being evaluated.
     */

    Event event;

    /**
     * The specification object that the monitor is part of.
     */

    SpecObject *spec;

    /**
     * The abstract syntax tree of the monitor.
     */

    ast::Monitor *monitorAST;

private:

    /**
     * Adds initial states to the monitor.
     */

    void addInitialStates();

    /**
     * Returns all event names used in the monitor.
     *
     * @return the set of used event names.
     */

    unordered_set<string> getUsedEventNames();

    /**
     * Returns true of a given event is relevant to this monitor. Only relevant
     * events will be evaluated.
     *
     * @param event the event.
     * @return true iff. the event is relevant to the monitor.
     */

    bool isRelevant(Event& event);

    /**
     * Evaluates a pattern against all facts, and returns the set of bindings corresponding to
     * all the matches.
     *
     * Note that the pattern is here assumed positive (any negation is ignored).
     *
     * @param binding the current binding, determined by the current state and previous pattern matches in the
     *   current transition.
     * @param pattern the pattern to be matched.
     * @return the set of binding corresponding to positive matches.
     */

    unordered_set<Binding, Binding::Hash> evalAsPositivePattern(Binding binding, ast::Pattern *pattern);

    /**
     * Names of events declared or alternatively used (if no event declarations) in the monitor.
     */

    unordered_set<string> eventNames;

    /**
     * Errors detected.
     */

    vector<MonitorError*> errors;

    /**
     * The frontier of the monitor: all active states.
     */

    unordered_set<StateObject,StateObject::Hash> states;

    /**
     * States to delete after an event evaluation.
     */

    unordered_set<StateObject,StateObject::Hash> statesToDelete;

    /**
     * States to add after an event evaluation.
     */

    unordered_set<StateObject,StateObject::Hash> statesToAdd;

};

#endif //LOGSCOPE_MONITOROBJECT_H
