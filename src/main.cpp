// Date: 2014
// Author: Ali Mashatan
// Email : ali.mashatan@gmail.com

#include <QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeView>
#include <QtDeclarative>

#include <editor.h>

#include <iostream>

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    qmlRegisterType<EditExtension>("Editor", 1, 0, "EditExtension");
    QDeclarativeView view;
    view.setSource(QUrl("qrc:qml/editor.qml"));
    view.show();
    
    EditExtension * editor = NULL;
    QList<QObject*> list = view.rootObject()->findChildren<QObject*>(QRegExp("^*objEditor01$"));
    if (list.count() > 0)
    {
        editor = dynamic_cast<EditExtension*>(list[0]);
    }
    if (editor != NULL)
    {
        editor->Append(5, 20, "<span style=color:#FFFFFF> Section <b>One</b></span>");
        editor->Append(50, 80, "<span style=color:#FFFFFF> Section <b>Two</b></span>");
        editor->setText(
            "    import Editor 1.0\n"
            "    import QtQuick 1.0\n"
            "\n"
            "    Rectangle\n"
            "{\n"
            "width: 360\n"
            "   height : 360\n"
            "            Text{\n"
            "id: txt\n"
            "text : \"This is a Text\"\n"
            "       anchors.centerIn : parent\n"
            "}\n"
            "}\n"
            "  \n"
            "    \n");

    }
    return app.exec();
}
