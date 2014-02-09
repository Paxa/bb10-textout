
#include "textoutapp.h"
#include "mruby_runner.h"

#include <bb/cascades/AbstractPane>

#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/Page>
#include <bb/cascades/Color>
#include <bb/cascades/Label>
#include <bb/cascades/TextArea>
#include <bb/cascades/TextStyle>
#include <bb/cascades/TextInputFlag>
#include <bb/cascades/SystemDefaults>
#include <bb/cascades/Button>
#include <bb/cascades/Menu>
#include <bb/cascades/ActionItem>
#include <bb/cascades/LabelAutoSizeProperties>
#include <bb/cascades/ScrollView>

using namespace bb::cascades;

TextOutApp::TextOutApp()
{
    bool connectResult;
    Q_UNUSED(connectResult);

    Container *contentContainer = new Container();
    contentContainer->setLayout(StackLayout::create());
    //contentContainer->setLayout(DockLayout::create());
    contentContainer->setTopPadding(20.0f);
    contentContainer->setLeftPadding(20.0f);
    contentContainer->setRightPadding(20.0f);

    contentContainer->setBackground(Color::fromARGB(0xff000000));

    QString labelText = "Label";

    label = new Label();
    label->setMultiline(true);
    label->setText(labelText);

    ScrollView* scrollView = ScrollView::create().scrollMode(ScrollMode::Both);
    scrollView->setContent(label);
    contentContainer->add(scrollView);

    Container *formContainer = new Container();
    formContainer->setLayout(StackLayout::create());

    // A multi line text input
    textArea = new TextArea();
    textArea->setHintText("Enter a ruby code");
    textArea->setPreferredHeight(40);
    textArea->setBackgroundVisible(true);
    textArea->setTopMargin(30.0);
    textArea->textStyle()->setBase(SystemDefaults::TextStyles::bodyText());
    textArea->input()->setFlags(
      TextInputFlag::AutoCapitalizationOff |
      TextInputFlag::AutoCorrectionOff |
      TextInputFlag::PredictionOff |
      TextInputFlag::SpellCheckOff |
      TextInputFlag::WordSubstitutionOff
    );
    textArea->setHorizontalAlignment(HorizontalAlignment::Fill);
    formContainer->add(textArea);

    sumbitButton = new Button();
    sumbitButton->setText((const char*) "Run");
    sumbitButton->setTopMargin(20.0f);
    formContainer->add(sumbitButton);

    connectResult = connect(sumbitButton, SIGNAL(clicked()), this, SLOT(onSumbitButtonClicked()));
    Q_ASSERT(connectResult);

    contentContainer->add(formContainer);

    //ScrollView* scrollView = ScrollView::create(l_label);
    //scrollView->setScrollMode(ScrollMode::Horizontal);

    Page *page = new Page();
    page->setContent(contentContainer);

    Application::instance()->setScene(page);

    mruby = new MrubyRunner();

    /*
    // Create the application menu
    Menu *menu = new Menu;

    // Create the actions and add them to the menu
    ActionItem *actionOne = ActionItem::create()
                            .title("Action 1");
    ActionItem *actionTwo = ActionItem::create()
                            .title("Action 2");
    menu->addAction(actionOne);
    menu->addAction(actionTwo);

    // Set the menu of the application
    Application::instance()->setMenu(menu);
    */
}

int TextOutApp::printText(const QString &newData) {
  QString newLabelText = newData;
  label->setText(newLabelText);
  return 0;
}

int TextOutApp::appendLines(const QString &newData) {
  QString newLabelText = label->text() + "\n" + newData;
  label->setText(newLabelText);
  return 0;
}

void TextOutApp::onSumbitButtonClicked() {
  QString code = textArea->text();
  QString command = "> " + code;
  appendLines(command);

  appendLines(runCode(code.toUtf8().data()));
  textArea->setText("");
}

QString TextOutApp::runCode(char *code) {
  return mruby->runCode(code);
}