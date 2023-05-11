#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QDialog>
#include <QSqlTableModel>
#include <QKeyEvent>

#include <database.h>


namespace Ui {
class DataWindow;
}

class DataWindow : public QDialog
{
    Q_OBJECT

public:
    void disabled_buttons(QPushButton * btn);
    explicit DataWindow(QWidget *parent = nullptr);
    ~DataWindow();

protected:
    void keyPressEvent(QKeyEvent *e) override;

signals:
    void sig_typeTable_clicked(Table table);
    void sig_addButton_clicked();
    void sig_deleteButton_clicked();
    void sig_tableView_clicked(const QModelIndex &index);
    void sig_UserPressedEnterToSaveChanges();


private slots:
    void on_planeButton_clicked();
    void on_zrkButton_clicked();
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void slot_table(QSqlTableModel *model);
    void slot_block_db();
    void slot_unblock_db();
    void on_rocketButton_clicked();

    void on_spriteButton_clicked();

private:
    Ui::DataWindow *ui;
};

#endif // DATAWINDOW_H
