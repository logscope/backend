/**********************************************/
/* C++ generated from LogScope specification! */
/**********************************************/

#include "contract.h"

using namespace std;

namespace suite1 {

    ast::Monitor *monitorM1() {
        ast::Monitor *M1 = new ast::Monitor("M1");

        ast::State *Command = new ast::State(
                {ast::Modifier::init},
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
                                        new ast::Pattern(true, "Command", {})
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

        M1->addEvent("command");
        M1->addEvent("succeed");
        M1->addState(Command);
        M1->addState(Succeed);

        return M1;
    }

    SpecObject makeContract() {
        ast::Spec *spec = new ast::Spec();
        spec->addMonitor(monitorM1());
        SpecObject contract(spec);
        return contract;
    }

}