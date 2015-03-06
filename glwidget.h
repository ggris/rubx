#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>

namespace Ui {
class GLWidget;
}

class GLWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

private:
    Ui::GLWidget *ui;
};

#endif // GLWIDGET_H
