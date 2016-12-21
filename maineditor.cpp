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
    xdxfFileName = QFileDialog::getOpenFileName(this, tr("Select XDXF File"), "../German-Idioms/", "XDXF (*.xdxf);HTML (*.htm)");
    ui->lineEdit->setText(xdxfFileName);
}

void MainEditor::on_commandLinkButton_clicked()
{
    QFile file(xdxfFileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        document.setContent(&file);
        file.close();
    }

    //get the root element: <xdxf>, <html>
    QDomElement root = document.documentElement();

    //get the body element: <lexicon>, <body>
    QDomElement body = root.firstChildElement("body");
//qDebug()<<body.tagName();
    valueParser(body);
}

void MainEditor::valueParser(const QDomElement &el)
{
    //parse the ar element: <ar>, <p>
    QDomNode article = el.firstChild();

    while(!article.isNull()){
        QDomNode value = article.firstChild();
        while(!value.isNull()){
            //process the <k> tags
            if(value.toElement().tagName() == "span")
            {
                ui->listWidget->addItem(value.toElement().text());
            }

            //process the <def> tags
            /*else if(value.toElement().tagName() == "def")
             {
                ui->textEdit->append(value.toElement().text());
             }
            */

            //<k> tags can come up several times in an article
            value = value.nextSibling();
        }
        article = article.nextSibling();
    }
}

void MainEditor::on_listWidget_doubleClicked(const QModelIndex &index)
{
    ui->textEdit->setText(index.data().toString());
}
