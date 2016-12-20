#include "maineditor.h"
#include "ui_maineditor.h"
#include <QtWidgets>

MainEditor::MainEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainEditor)
{
    ui->setupUi(this);
}

MainEditor::~MainEditor()
{
    delete ui;
}

void MainEditor::on_toolButton_clicked()
{
    xdxfFileName = QFileDialog::getOpenFileName(this, tr("Select XDXF File"), "../German-Idioms/", "XDXF (*.xdxf)");
    ui->lineEdit->setText(xdxfFileName);
}

void MainEditor::on_commandLinkButton_clicked()
{
    QDomDocument document;

    QFile file(xdxfFileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        document.setContent(&file);
        file.close();
    }

    QDomNodeList el = document.elementsByTagName("k");
    for(int i = 0; i < el.count(); i++)
    {
        ui->textEdit->append(el.at(i).toElement().text());
    }

    el = document.elementsByTagName("def");
    for(int i = 0; i < el.count(); i++)
    {
        if(el.at(i).isElement())
        {
            ui->textEdit_2->append(el.at(i).toElement().text());
        }
    }
}
