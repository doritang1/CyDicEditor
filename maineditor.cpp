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
    fileName = QFileDialog::getOpenFileName(this, tr("Select a File to open"), "../German-Idioms/", "XDXF (*.xdxf);; HTML (*.htm*);; All (*.*)");
    ui->lineEdit->setText(fileName);
}

void MainEditor::on_commandLinkButton_clicked()
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if(fileName.endsWith("xdxf"))
        {
            xdxfParser(&file);
            file.close();
        }else if(fileName.endsWith("htm")|fileName.endsWith("html")){
            htmlParser(&file);
            file.close();
        }
    }
}

void MainEditor::xdxfParser(QFile *file)
{
    document.setContent(file);

    //get the root element: <xdxf>
    QDomElement elem_xdxf = document.documentElement();

    //get the body element: <lexicon>
    QDomElement elem_lexicon = elem_xdxf.firstChildElement("lexicon");


    //parse the ar element: <ar>
    QDomNode node_ar = elem_lexicon.firstChild();
    while(!node_ar.isNull()){
        QDomNode node_value = node_ar.firstChild();
        while(!node_value.isNull()){
            //process the <k> tags
            if(node_value.toElement().tagName() == "k")
            {
                ui->listWidget->addItem(node_value.toElement().text());
            }

            //process the <def> tags
            else if(node_value.toElement().tagName() == "def")
             {
                ui->textEdit->append(node_value.toElement().text());
             }

            //<k> tags can come up several times in an article
            node_value = node_value.nextSibling();
        }
        node_ar = node_ar.nextSibling();
    }
}

void MainEditor::htmlParser(QFile *file)
{
    QXmlStreamReader reader(file);
Read(reader);


}

void MainEditor::Read(QXmlStreamReader &r)
{
    while(r.readNextStartElement()){
        if(r.name()=="head"){
            Read(r);
        }else if(r.name()=="title"){
            ui->listWidget->addItem(r.readElementText());
        }else if(r.name()=="body"){
            Read(r);
        }else if(r.name()=="p"){
            ui->textEdit->append(r.readElementText());
        }
    }
}

void MainEditor::on_listWidget_doubleClicked(const QModelIndex &index)
{
    ui->textEdit->setText(index.data().toString());
}
