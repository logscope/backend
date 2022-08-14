//
// Created by Havelund, Klaus (348B) on 1/11/21.
//

#ifndef LOGSCOPE_STATEOBJECT_H
#define LOGSCOPE_STATEOBJECT_H

#include <ostream>
#include "../ast/ast.h"
#include "Binding.h"
#include "unordered_set"

class MonitorObject;

enum class TransitionResult {SILENT, MOVED, FAILED};

/**
 * Represents a state.
 */

class StateObject {

public:

    /**
     * Constructor.
     *
     * @param name name of the state.
     * @param binding the binding of formal parameters of the state to values.
     * @param state the abstract syntax tree of the state.
     * @param monitor the monitor that the state is part of.
     */

    StateObject(string name, Binding binding, ast::State *state, MonitorObject *monitor);

    bool operator==(const StateObject& other) const;
    struct Hash {size_t operator()(const StateObject& s) const;};

    /**
     * Evaluates the state against the current event, stored in `monitor->event`.
     */

    void eval();

    /**
     * Terminates monitoring for this state. This will cause an error message if the state is hot.
     */

    void end();

    friend ostream &operator<<(ostream &os, const StateObject &object);

    /**
     * The name of the state.
     */

    string name;

    /**
     * The binding of formal state parameters to values.
     */

    Binding binding;

private:

    /**
     * Evaluates a transition in the state against the current event in `monitor->event` and the
     * frontier of the `monitor`.
     *
     * @param transition the transition to be evaluated.
     * @return the result of evaluating the transition.
     */

    TransitionResult evalTransition(ast::Transition * transition);

    /**
     * Evaluates the left-hand side of a transition against the current event in
     * `monitor->event` and the frontier in `monitor`.
     *
     * @param transition the transition, the left-hand side of which is evaluated.
     * @return the set of bindings corresponding to all the matches of the
     * left-hand side againts the event and the frontier of the monitor.
     */

    unordered_set<Binding,Binding::Hash> evalTransitionLHS(ast::Transition * transition);

    /**
     * Evaluates the right-hand side of a transition for each binding that the left-hand side
     * generated. This means adding and/or deleting facts, or reporting an error message in
     * case `error` is the target state.
     *
     * @param bindings the set of bindings generated by the left-hand side of the transition.
     * @param transition the transition, the right-hand side of which is evaluated.
     * @return true iff. `error` is the target state.
     */

    bool evalTransitionRHS(unordered_set<Binding,Binding::Hash> bindings, ast::Transition * transition);

    /**
     * Creates a state from a binding and the abstract syntax tree of a pattern.
     * This method is called from `evalTransitionRHS` that evaluates the right-hand
     * side of a transition.
     *
     * @param binding the binding of the new state.
     * @param pattern the pattern describing the new state: its name and data bindings.
     * @return the new state.
     */

    StateObject mkStateFromPattern(Binding binding, ast::Pattern *pattern);

    /**
     * From a binding and a pattern this method generates a new binding representing
     * the binding of a new state. E.g. if the `binding` binds `x` to 42, then
     * the from the pattern `Succeed(c : x)` a new binding mapping `c` to 42 is generated
     * and returned.
     *
     * @param binding the incoming binding.
     * @param pattern the pattern used to create a new binding.
     * @return teh resulting binding.
     */

    Binding mkBindingFromPattern(Binding binding, ast::Pattern *pattern);

    /**
     * The abstract syntax tree of the state.
     */

    ast::State *stateAST;

    /**
     * The abstract syntax tree of the monitor that the state is part of.
     */

    MonitorObject *monitor;

};

#endif //LOGSCOPE_STATEOBJECT_H

