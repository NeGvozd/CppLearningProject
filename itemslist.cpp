#include "itemslist.h"
ItemsListItem::ItemsListItem(ItemsListItem *parent, int id, QString name, QString model, float health, float speed, float x, float y) : 
QTreeWidgetItem(parent), id_(id), name_(name), model_(model), health_(health), speed_(speed), x_(x), y_(y) {this->setText(0, name);};

ItemsListItem::ItemsListItem(ItemsListItem *parent, int id, QString name, QString model, float damage, float speed, float range, float x, float y) :
QTreeWidgetItem(parent), id_(id), name_(name), model_(model), damage_(damage), speed_(speed), range_(range), x_(x), y_(y) {this->setText(0, name);};

ItemsListItem::ItemsListItem(ItemsListItem *parent, int id, QString name, QString model, float health, float distance, int ammo, float x, float y) :
QTreeWidgetItem(parent), id_(id), name_(name), model_(model), health_(health), distance_(distance), ammo_(ammo), x_(x), y_(y) {this->setText(0, name);};

ItemsListItem::ItemsListItem(QTreeWidget *parent, QString name) : QTreeWidgetItem(parent), name_(name){this->setText(0, name);}

int ItemsListItem::id() const{return id_;}

QString ItemsListItem::name() const{return name_;};

QString ItemsListItem::model() const{return model_;};

float ItemsListItem::damage() const{return damage_;};

float ItemsListItem::health() const{return health_;};

float ItemsListItem::range() const{return range_;};

float ItemsListItem::speed() const{return speed_;};

float ItemsListItem::mass() const{return mass_;};

float ItemsListItem::distance() const{return distance_;};

int ItemsListItem::ammo() const{return ammo_;};

float ItemsListItem::x() const{return x_;};

float ItemsListItem::y() const{return y_;}