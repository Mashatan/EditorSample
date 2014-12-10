// Date: 2014
// Author: Ali Mashatan
// Email : ali.mashatan@gmail.com

#include <editor.h>
#include <QPainter>
#include <QtWidgets>
#include <iostream>

CustomEditor::CustomEditor(QWidget *parent /*= 0*/)
    :QPlainTextEdit(parent)
{
    m_ptrTooltip = new ToolTip(this);
    m_ptrTooltip->hide();
    bool result = false;
    result = connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(doCursorPositionChanged()));
    Q_ASSERT(result);
}


CustomEditor::~CustomEditor()
{
    delete m_ptrTooltip;
}

void CustomEditor::doCursorPositionChanged()
{
    QTextCursor cursor = this->textCursor();
    int pos = cursor.position();
    QRect curRect = this->cursorRect();
    
    QString currentText = "";

    //Finding <text> that when the cursor is between <start> and <stop>
    foreach(CustomEditor::Item item, m_List)
    {
        if (pos >= item.start  && pos <= item.end)
        {
            currentText = item.text;
        }
    }

    if (currentText.isEmpty() == true)
    {
        //Hide toolbar
        m_ptrTooltip->hide();
    } else
    {
        //Show toolbar
        m_ptrTooltip->hide();
        m_CurrentText.setHtml(currentText);
        QSizeF size = m_CurrentText.size();
        m_ptrTooltip->resize(size.toSize());
        int halfWidth = size.width() / 2;
        
        QPoint pointCursor = curRect.topLeft();
        pointCursor.setY(pointCursor.y() + 15);
        int startX = pointCursor.x() - halfWidth;
        if (startX <0)
        {
            startX = 0;
        }
        pointCursor.setX(startX);
        m_ptrTooltip->move(pointCursor);

        m_ptrTooltip->show();
    }
}



void CustomEditor::ToolTipPaintEvent(QPaintEvent *event)
{
    QPainter painter(m_ptrTooltip);
    QRect rect = event->rect();
    painter.fillRect(rect, Qt::red);
       
    QAbstractTextDocumentLayout::PaintContext ctx;
    m_CurrentText.documentLayout()->draw(&painter, ctx);
}

void CustomEditor::Append(const int start, const int end, QString text)
{
    Item item;
    item.start = start;
    item.end = end;
    item.text = text;
    m_List.append(item);
}


ToolTip::ToolTip(CustomEditor *editor) :QWidget(editor)
{
    m_ptrEditor = editor;
}

QSize ToolTip::sizeHint() const
{
    return QSize(m_ptrEditor->width(), m_ptrEditor->height());
}

void ToolTip::paintEvent(QPaintEvent *event)
{
    m_ptrEditor->ToolTipPaintEvent(event);
}

