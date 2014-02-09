#ifndef _MRUBY_RUNNER_H_
#define _MRUBY_RUNNER_H_

#include <mruby.h>
#include <mruby/string.h>
#include <mruby/compile.h>
#include <Qt/QString.h>

class MrubyRunner {

  public:
    // This is our constructor that sets up the recipe.
    MrubyRunner();
    mrb_value runCodeValue(char *code);
    QString runCode(char *code);
  private:
    mrb_state *mrb;
};

#endif // ifndef _MRUBY_RUNNER_H_