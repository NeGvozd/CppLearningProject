#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class DataWindow;
}

class DataWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DataWindow(QWidget *parent = nullptr);
    ~DataWindow();


private slots:
    void on_planeButton_clicked();
    void on_zrkButton_clicked();
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_tableView_clicked(const QModelIndex &index);

    void on_zalupa_clicked();

signals:
    void sig_planeButton_clicked();
//    void sig_zrkButton_clicked();
//    void sig_return_model();
//    void sig_addButton_clicked();
//    void sig_deleteButton_clicked();
//    void sig_tableView_clicked(const QModelIndex &index);

private:
    Ui::DataWindow *ui;
};

#endif // DATAWINDOW_H
