/**********************************************/
/* C++ generated from LogScope specification! */
/**********************************************/

#include "contract.h"

using namespace std;

namespace suite4 {

    ast::Monitor *monitorM1c() {
        ast::Monitor *M1c = new ast::Monitor("M1c");

        ast::State *INTERNAL__1 = new ast::State(
                {ast::Modifier::always, ast::Modifier::init},
                "INTERNAL__1",
                {},
                {
                        new ast::Transition(
                                new ast::Pattern(true, "command", {}),
                                {},
                                {
                                        new ast::Pattern(true, "Succeed", {})
                                }
                        )
                }
        );

        ast::State *Succeed = new ast::State(
                {ast::Modifier::hot},
                "Succeed",
                {},
                {
                        new ast::Transition(
                                new ast::Pattern(true, "succeed", {}),
                                {},
                                {
                                        new ast::Pattern(true, "ok", {})
                                }
                        ),
                        new ast::Transition(
                                new ast::Pattern(true, "command", {}),
                                {},
                                {
                                        new ast::Pattern(true, "error", {})
                                }
                        )
                }
        );

        M1c->addEvent("command");
        M1c->addEvent("succeed");
        M1c->addState(INTERNAL__1);
        M1c->addState(Succeed);

        return M1c;
    }

    SpecObject makeContract() {
        ast::Spec *spec = new ast::Spec();
        spec->addMonitor(monitorM1c());
        SpecObject contract(spec);
        return contract;
    }

}