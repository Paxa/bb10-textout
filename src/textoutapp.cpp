
#include "textoutapp.h"
#include <bb/cascades/AbstractPane>

#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/Page>
#include <bb/cascades/Color>
#include <bb/cascades/Label>
#include <bb/cascades/Menu>
#include <bb/cascades/ActionItem>
#include <bb/cascades/LabelAutoSizeProperties>
#include <bb/cascades/ScrollView>

using namespace bb::cascades;

TextOutApp::TextOutApp()
{
    Container *contentContainer = new Container();
    contentContainer->setLayout(StackLayout::create());
    //contentContainer->setLayout(DockLayout::create());
    contentContainer->setTopPadding(20.0f);
    contentContainer->setLeftPadding(20.0f);
    contentContainer->setRightPadding(20.0f);

    contentContainer->setBackground(Color::fromARGB(0xff000000));

    QString labelText = "Label";

    Label *l_label = new Label();
    l_label->setMultiline(true);
    //l_label->setMinWidth(600);
    l_label->setText(labelText);

    //contentContainer->add(l_label);

    label = l_label;

    ScrollView* scrollView = ScrollView::create().scrollMode(ScrollMode::Both);
    scrollView->setContent(l_label);
    contentContainer->add(scrollView);

    //ScrollView* scrollView = ScrollView::create(l_label);
    //scrollView->setScrollMode(ScrollMode::Horizontal);

    Page *page = new Page();
    page->setContent(contentContainer);

    Application::instance()->setScene(page);

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
