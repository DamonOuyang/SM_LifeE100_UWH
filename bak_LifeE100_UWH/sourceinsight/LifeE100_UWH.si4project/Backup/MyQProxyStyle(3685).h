﻿#ifndef MYQPROXYSTYLE_H
#define MYQPROXYSTYLE_H

#include <QPainter>
#include <QProxyStyle>

class MyQProxyStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab)
        {
            s.transpose();
            s.rwidth() = 125;             // 设置每个tabBar中item的大小
            s.rheight() = 65;
        }
        return s;
    }
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel)
        {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option))
            {
                QRect allRect = tab->rect; allRect.setWidth(allRect.width() - 5);
                allRect.setHeight(allRect.height() - 2);
                //选中状态
                if (tab->state & QStyle::State_Selected)
                {
                    //save用以保护坐标，restore用来退出状态
                    painter->save();
                    painter->setBrush(QBrush(0x404047));
                                        //painter->setPen(0xF7B000);
                    //矩形
                    painter->drawRect(allRect.adjusted(0, 0, 10, 10));
                    painter->restore();
                }
                //hover状态
                else if(tab->state & QStyle::State_MouseOver)
                {
                    painter->save();
                    painter->setBrush(QBrush(0x404047));
                                        //painter->setPen(0xF7B000);
                    //painter->drawRoundedRect(tab->rect, 8, 8);
                    painter->drawRect(allRect.adjusted(0, 0, 10, 10));
                    painter->restore();
                }
                else
                {
                    painter->save();
                    painter->setBrush(QBrush(0x36363D));
                                        //painter->setPen(0xffffff);
                    //painter->drawRoundedRect(tab->rect 8, 8);
                    painter->drawRect(allRect.adjusted(0, 0, 10, 10));
                    painter->restore();
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                painter->setFont(QFont("simhei", 18, QFont::Normal));
                painter->setPen(0xffffff);
                painter->drawText(allRect, tab->text, option);
                return;
            }
        }
        if (element == CE_TabBarTab)
        {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};


#endif // MYQPROXYSTYLE_H
