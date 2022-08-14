/**********************************************/
/* C++ generated from LogScope specification! */
/**********************************************/

#include "contract.h"

using namespace std;

ast::Monitor *monitorM3() {
  ast::Monitor *M3 = new ast::Monitor("M3");

  ast::State *INTERNAL__1 = new ast::State(
    {ast::Modifier::always,ast::Modifier::init},
    "INTERNAL__1",
    {},
    {
      new ast::Transition(
        new ast::Pattern(true,"command",{new ast::Constraint("cmd",new ast::Range(ast::Range::Kind::NAME,"x")),new ast::Constraint("kind",new ast::Range(ast::Range::Kind::VALUE,"FSW"))})
        ,
        {}
        ,
        {
          new ast::Pattern(true,"Succeed",{new ast::Constraint("c",new ast::Range(ast::Range::Kind::NAME,"x"))})
        }
      )
      ,
      new ast::Transition(
        new ast::Pattern(true,"succeed",{new ast::Constraint("cmd",new ast::Range(ast::Range::Kind::NAME,"x"))})
        ,
        {
          new ast::Pattern(false,"Succeed",{new ast::Constraint("c",new ast::Range(ast::Range::Kind::NAME,"x"))})
        }
        ,
        {
          new ast::Pattern(true,"error",{})
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
        new ast::Pattern(true,"succeed",{new ast::Constraint("cmd",new ast::Range(ast::Range::Kind::NAME,"c"))})
        ,
        {}
        ,
        {
          new ast::Pattern(true,"ok",{})
        }
      )
      ,
      new ast::Transition(
        new ast::Pattern(true,"command",{new ast::Constraint("cmd",new ast::Range(ast::Range::Kind::NAME,"c"))})
        ,
        {}
        ,
        {
          new ast::Pattern(true,"error",{})
        }
      )
    }
  );

  M3->addEvent("command");
  M3->addEvent("succeed");
  M3->addState(INTERNAL__1);
  M3->addState(Succeed);

  return M3;
}

SpecObject makeContract() {
  ast::Spec *spec = new ast::Spec();
  spec->addMonitor(monitorM3());
  SpecObject contract(spec);
  return contract;
}
