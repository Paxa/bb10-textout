
#include "mruby_runner.h"

MrubyRunner::MrubyRunner() {
  mrb = mrb_open();

}

mrb_value MrubyRunner::runCodeValue(char *code) {
  mrb_value ruby_string = mrb_load_string(mrb, code);
  return ruby_string;
}

QString MrubyRunner::runCode(char *code) {
  mrb_value ruby_result = runCodeValue(code);
  mrb_value ruby_string = mrb_inspect(mrb, ruby_result);

  struct RString *str;
  char *s = "";

  if (mrb_string_p(ruby_string)) {
    str = mrb_str_ptr(ruby_string);
    s = str->ptr;
  } else {
    s = "- not a string -";
  }

  QString proc_out = s;
  return proc_out;
}
