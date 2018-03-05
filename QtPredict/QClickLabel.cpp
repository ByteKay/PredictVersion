#ifndef CONSOLE
#include "QClickLabel.h"

QClickLabel::QClickLabel(QWidget * parent) : QLabel(parent)
{

}

QClickLabel::~QClickLabel(void)
{

}

void QClickLabel::mouseReleaseEvent(QMouseEvent * ev)
{
	if (ev->button() == Qt::LeftButton)
	{
		// Q_UNUSED(ev)
		emit clicked();
	}
}
#endif
