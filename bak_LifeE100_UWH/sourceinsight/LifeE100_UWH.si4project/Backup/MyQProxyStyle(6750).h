#ifndef MYQPROXYSTYLE_H
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
            s.rwidth() = m_unWidth;             // 设置每个tabBar中item的大小
            s.rheight() = m_unHeight;
        }
        return s;
    }
	void SetTabWidth(int unWidth)
    {
        m_unWidth = unWidth;
    }
	void SetTabHeigth(int unHeight)
    {
        m_unHeight = unHeight;
    }
	void SetFontB(int unFont)
	{
		m_unFont = unFont;
	}
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
    /*
        if (element == CE_TabBarTabLabel)
        {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option))
            {
                QRect allRect = tab->rect; allRect.setWidth(allRect.width()-2);
                allRect.setHeight(allRect.height()-2);
                //选中状态
                if (tab->state & QStyle::State_Selected)
                {
                    //save用以保护坐标，restore用来退出状态
                    //painter->save();
                    painter->setBrush(QBrush(0x404047));
                    //矩形
                    painter->drawRect(allRect.adjusted(0, 0, 0, 0));
                    //painter->restore();
                    painter->setPen(0xF7B000);
                }
                //hover状态
                else if(tab->state & QStyle::State_MouseOver)
                {
                    //painter->save();
                    painter->setBrush(QBrush(0x404047));
                    //painter->drawRoundedRect(tab->rect, 8, 8);
                    painter->drawRect(allRect.adjusted(0, 0, 0, 0));
                    //painter->restore();
					painter->setPen(0xF7B000);
                }
                else
                {
                    //painter->save();
                    painter->setBrush(QBrush(0x36363D));
                    //painter->drawRoundedRect(tab->rect 8, 8);
                    painter->drawRect(allRect.adjusted(0, 0, 0, 0));
                    //painter->restore();
					painter->setPen(0xffffff);
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                painter->setFont(QFont("simhei", m_unFont, QFont::Normal));
                painter->drawText(allRect, tab->text, option);
                return;
            }
        }*/
		if (element == CE_TabBarTabLabel) {
			if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option))
			{
				QRect allRect = tab->rect;

				if (tab->state & QStyle::State_Selected) 
				{
					painter->save();
					//painter->setPen(0x89cfff);
					painter->setPen(0xF7B000);
					//painter->setBrush(QBrush(0x89cfff));
					painter->setBrush(QBrush(0x404047));
					painter->drawRect(allRect.adjusted(6, 6, -6, -6));
					painter->restore();
				}
				QTextOption option;
				option.setAlignment(Qt::AlignCenter);
				if(tab->state & QStyle::State_Selected) 
				{
					painter->setPen(0xf8fcff);
				}
				else 
				{
					painter->setPen(0x5d5d5d);
				}

				painter->drawText(allRect, tab->text, option);
				return;
			}
		}


        if (element == CE_TabBarTab)
        {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
private:
	int m_unWidth = 160;
	int m_unHeight = 65;
	int m_unFont = 18;
};


#endif // MYQPROXYSTYLE_H
