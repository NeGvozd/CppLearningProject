#ifndef CHOOSELINE_H
#define CHOOSELINE_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QDebug>

class LineListItem : public QListWidgetItem{
public:
    LineListItem(LineListItem * parent, int id, QString name);
    LineListItem(QListWidget * parent, int id, QString name);
    void setName(QString name);
    int Id() const;
    QString Name() const;
private:
    int id_;
    QString name_;
};

namespace Ui {
class ChooseLine;
}

class ChooseLine : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseLine(QWidget *parent = nullptr);
    ~ChooseLine();
signals:
    void itemClickSend(int id);
    void itemNameChange(int id, QString name);
public slots:
    void addLine(int id, QString name);
private slots:
    void acceptClicked();
    void closeWindow();
    void changeName(QListWidgetItem *item);

private:
    Ui::ChooseLine *ui;
    QListWidget* listWidget;

    QPushButton* acceptButton;
    QPushButton* cancelButton;

};

#endif // CHOOSELINE_H
