
#include "textoutapp.h"
//#include <Qt/qdeclarativedebug.h>

#include <Qt/QString.h>
#include <Qt/QProcess.h>

using namespace bb::cascades;

Q_DECL_EXPORT int main(int argc, char **argv)
{
    // Instantiate the main application constructor.
    Application app(argc, argv);

    // Initialize our application.
    TextOutApp mainApp;

    QProcess process;
    process.start("ls", QStringList() << "-lah");
    process.waitForFinished(-1);

    QString proc_out = process.readAllStandardOutput();

    mainApp.printText("");
    mainApp.appendLines(proc_out);

    return Application::exec();
}

