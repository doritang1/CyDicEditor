#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include <QDialog>
#include <QtXml>


namespace Ui {
class MainEditor;
}

class MainEditor : public QDialog
{
    Q_OBJECT

public:
    explicit MainEditor(QWidget *parent = 0);
    ~MainEditor();

private slots:
    void on_toolButton_clicked();

    void on_commandLinkButton_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MainEditor *ui;

    QString fileName;

    QDomDocument document;
    void xdxfParser(QFile *file);

    void htmlParser(QFile *file);
    void Read(QXmlStreamReader &r);
};

#endif // MAINEDITOR_H
