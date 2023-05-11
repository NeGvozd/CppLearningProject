#ifndef ITEMSLISTWINDOW_H
#define ITEMSLISTWINDOW_H

#include <QDialog>
#include <QListWidget>
#include <QTimer>

class ListItem : public QListWidgetItem{
public:
    ListItem(ListItem * parent, QString name);
    ListItem(QListWidget * parent, QString name);
private:
    QString name;
};

namespace Ui {
class ItemsListWindow;
}

class ItemsListWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ItemsListWindow(QWidget *parent = nullptr);
    ~ItemsListWindow();
signals:
    void sendRocketId(int id);
    void sendSAMId(int id);
    void sendPlaneId(int id);
public slots:
    void planeCharacteristics(int id, QString name, QString model, float health, float speed, float x, float y);
    void SAMCharacteristics(int id, QString name, QString model, float health, float distance, int ammo, float x, float y);
    void RocketCharacteristics(int id, QString name, QString model, float damage, float speed, float range, float x, float y);
    void getCoords(float x, float y);
private slots:
    void exchangeRocketCoords();
    void exchangeSAMCoords();
    void exchangePlaneCoords();

private:
    void addElement(QString name);
    virtual void reject();

private:
    Ui::ItemsListWindow *ui;
    QTimer* timer;
    int id;
};

#endif // ITEMSLISTWINDOW_H
