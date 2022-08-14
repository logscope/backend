/**********************************************/
/* C++ generated from LogScope specification! */
/**********************************************/

#include "contract.h"

using namespace std;

namespace suite3 {

    ast::Monitor *monitorM1b() {
        ast::Monitor *M1b = new ast::Monitor("M1b");

        ast::State *Command = new ast::State(
                {ast::Modifier::always, ast::Modifier::init},
                "Command",
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

        M1b->addEvent("command");
        M1b->addEvent("succeed");
        M1b->addState(Command);
        M1b->addState(Succeed);

        return M1b;
    }

    SpecObject makeContract() {
        ast::Spec *spec = new ast::Spec();
        spec->addMonitor(monitorM1b());
        SpecObject contract(spec);
        return contract;
    }

}