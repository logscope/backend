/**********************************************/
/* C++ generated from LogScope specification! */
/**********************************************/

#include "contract.h"

using namespace std;

namespace suite5 {

    ast::Monitor *monitorM2() {
        ast::Monitor *M2 = new ast::Monitor("M2");

        ast::State *INTERNAL__1 = new ast::State(
                {ast::Modifier::always, ast::Modifier::init},
                "INTERNAL__1",
                {},
                {
                        new ast::Transition(
                                new ast::Pattern(true, "command", {new ast::Constraint("cmd", new ast::Range(
                                        ast::Range::Kind::NAME, "x")), new ast::Constraint("kind", new ast::Range(
                                        ast::Range::Kind::VALUE, "FSW"))}),
                                {},
                                {
                                        new ast::Pattern(true, "Succeed", {new ast::Constraint("c", new ast::Range(
                                                ast::Range::Kind::NAME, "x"))})
                                }
                        )
                }
        );

        ast::State *Succeed = new ast::State(
                {ast::Modifier::hot},
                "Succeed",
                {"c"},
                {
                        new ast::Transition(
                                new ast::Pattern(true, "succeed", {new ast::Constraint("cmd", new ast::Range(
                                        ast::Range::Kind::NAME, "c"))}),
                                {},
                                {
                                        new ast::Pattern(true, "ok", {})
                                }
                        ),
                        new ast::Transition(
                                new ast::Pattern(true, "command", {new ast::Constraint("cmd", new ast::Range(
                                        ast::Range::Kind::NAME, "c"))}),
                                {},
                                {
                                        new ast::Pattern(true, "error", {})
                                }
                        )
                }
        );

        M2->addEvent("command");
        M2->addEvent("succeed");
        M2->addState(INTERNAL__1);
        M2->addState(Succeed);

        return M2;
    }

    SpecObject makeContract() {
        ast::Spec *spec = new ast::Spec();
        spec->addMonitor(monitorM2());
        SpecObject contract(spec);
        return contract;
    }

}