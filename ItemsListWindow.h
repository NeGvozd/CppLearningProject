#ifndef ITEMSLISTWINDOW_H
#define ITEMSLISTWINDOW_H

#include <QDialog>

namespace Ui {
class ItemsListWindow;
}

class ItemsListWindow : public QDialog
{
    Q_OBJECT
    
public slots:
    void planeCharacteristics(int id, QString name, QString model, float health, float speed, float x, float y);
    void SAMCharacteristics(int id, QString name, QString model, float health, float distance, int ammo, float x, float y);
    void RocketCharacteristics(int id, QString name, QString model, float damage, float speed, float range, float x, float y);
    
private:
    Ui::ItemsListWindow *ui;
};

#endif // ITEMSLISTWINDOW_H
