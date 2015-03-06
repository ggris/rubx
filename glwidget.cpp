#include "glwidget.h"
#include "ui_glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GLWidget)
{
    ui->setupUi(this);
}

GLWidget::~GLWidget()
{
    delete ui;
}
