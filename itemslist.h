#include <QTreeWidget>

class ItemsListItem : public QTreeWidgetItem{
public:

    ItemsListItem(ItemsListItem *parent, int id, QString name, QString model, float health, float speed, float x, float y);
    ItemsListItem(ItemsListItem *parent, int id, QString name, QString model, float damage, float speed, float range, float x, float y);
    ItemsListItem(ItemsListItem *parent, int id, QString name, QString model, float health, float distance, int ammo, float x, float y);
    ItemsListItem(QTreeWidget *parent, QString name);

    int id() const;
    QString name() const;
    QString model() const;
    float damage() const;
    float health() const;
    float range() const;
    float speed() const;
    float mass() const;
    float distance() const;
    int ammo() const;
    float x() const;
    float y() const; //мб просто хранить указатель на объект в движке?
private:
    int id_ = -1;
    QString name_ = "none";
    QString model_ = "none";
    float damage_ = -1.;
    float health_ = -1.;
    float range_ = -1.;
    float speed_ = -1.;
    float mass_ = -1.;
    float distance_ = -1.;
    int ammo_ = -1;
    float x_ = -1.;
    float y_ = -1.;
};