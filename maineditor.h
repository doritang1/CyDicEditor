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

private:
    Ui::MainEditor *ui;
    QString xdxfFileName;
};

#endif // MAINEDITOR_H
