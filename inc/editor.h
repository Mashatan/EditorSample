// Date: 2014
// Author: Ali Mashatan
// Email : ali.mashatan@gmail.com

#pragma once

#include <QPlainTextEdit>
#include <QGraphicsProxyWidget>

#include <QDeclarativeItem>

//#include <QtDeclarativeDepends>
//#include <QtQuickDepends>
//#include <QtQuickDepends>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE


class ToolTip;


class CustomEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CustomEditor(QWidget *parent = 0);
    virtual ~CustomEditor();

    void ToolTipPaintEvent(QPaintEvent *event);
    
    void Append(const int start, const int end, QString text);

protected:

private slots :
    void doCursorPositionChanged();

private:
    struct Item
    {
        int start;
        int end;
        QString text;
    };
    QVector <Item> m_List;
    
    ToolTip *m_ptrTooltip;
    QTextDocument m_CurrentText;
};


class ToolTip :public QWidget
{
    Q_OBJECT

public:
    ToolTip(CustomEditor *editor);
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);
private:
    CustomEditor *m_ptrEditor;
};


class EditExtension : public QGraphicsProxyWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)

public:

    EditExtension(QDeclarativeItem * parent = 0)
        : QGraphicsProxyWidget(parent)
    {
        m_ptrEditor = new CustomEditor();
        setWidget(m_ptrEditor);
        //m_ProxyWidget = new QGraphicsProxyWidget(this);
        //m_ProxyWidget->setWidget(m_ptrEditor);
    }
    QString text() { return m_ptrEditor->toPlainText(); }
    void setText(QString value) { m_ptrEditor->setPlainText(value); }

    Q_INVOKABLE void Append(const int start, const int end, QString text)
    {
        m_ptrEditor->Append(start, end, text);
    }

private:
    CustomEditor *m_ptrEditor;
    //QGraphicsProxyWidget *m_ProxyWidget;
  
};
