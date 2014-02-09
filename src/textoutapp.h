#ifndef _TEXTOUTAPP_H_
#define _TEXTOUTAPP_H_

#include <bb/cascades/Application>
#include "mruby_runner.h"

namespace bb
{
    namespace cascades
    {
        class Label;
        class Button;
        class TextArea;
    }
}


class TextOutApp: public QObject {
  Q_OBJECT

  public:
    // This is our constructor that sets up the recipe.
    TextOutApp();
    int printText(const QString &string);
    int appendLines(const QString &string);

    MrubyRunner *mruby;
    QString runCode(char *code);

  public slots:
    void onSumbitButtonClicked();

  private:
    bb::cascades::Label *label;
    bb::cascades::Button *sumbitButton;
    bb::cascades::TextArea *textArea;
};

#endif // ifndef _TEXTOUTAPP_H_
