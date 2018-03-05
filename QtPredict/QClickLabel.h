#ifndef CONSOLE
#ifndef QCLIKLABEL_H
#define QCLIKLABEL_H
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
class QClickLabel : public QLabel
{
	Q_OBJECT
public:
	QClickLabel(QWidget * parent = 0);
	~QClickLabel(void);

protected:
	void mouseReleaseEvent(QMouseEvent * ev);

signals:
	void clicked();
};
#endif
#endif