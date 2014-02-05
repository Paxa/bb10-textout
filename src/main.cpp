
#include "textoutapp.h"
//#include <Qt/qdeclarativedebug.h>

#include <Qt/QString.h>
//#include <Qt/QProcess.h>

#include <mruby.h>
#include <mruby/string.h>
#include <mruby/compile.h>

using namespace bb::cascades;

Q_DECL_EXPORT int main(int argc, char **argv)
{
    // Instantiate the main application constructor.
    Application app(argc, argv);

    // Initialize our application.
    TextOutApp mainApp;

    /*
    QProcess process;
    process.start("ls", QStringList() << "-lah");
    process.waitForFinished(-1);

    QString proc_out = process.readAllStandardOutput();
    */

    mainApp.printText("This line will be printed by ruby:");

    mrb_state *mrb = mrb_open();
    char code[] = "p 'hello world!'";

    mrb_value ruby_string = mrb_load_string(mrb, code);

    struct RString *str;
    char *s;
    int len;

    if (mrb_string_p(ruby_string)) {
      str = mrb_str_ptr(ruby_string);
      s = str->ptr;
      len = str->len;
      fwrite(s, len, 1, stdout);
    }

    s[len] = '\0';

    QString proc_out = s;

    mainApp.appendLines(proc_out);

    return Application::exec();
}

