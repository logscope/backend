/**********************************************/
/* C++ generated from LogScope specification! */
/**********************************************/

#include "contract.h"

using namespace std;

namespace suite2 {

    ast::Monitor *monitorM1a() {
        ast::Monitor *M1a = new ast::Monitor("M1a");

        ast::State *Command = new ast::State(
                {ast::Modifier::init},
                "Command",
                {},
                {
                        new ast::Transition(
                                new ast::Pattern(true, "command", {}),
                                {},
                                {
                                        new ast::Pattern(true, "Succeed", {}),
                                        new ast::Pattern(true, "Command", {})
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

        M1a->addEvent("command");
        M1a->addEvent("succeed");
        M1a->addState(Command);
        M1a->addState(Succeed);

        return M1a;
    }

    SpecObject makeContract() {
        ast::Spec *spec = new ast::Spec();
        spec->addMonitor(monitorM1a());
        SpecObject contract(spec);
        return contract;
    }

}