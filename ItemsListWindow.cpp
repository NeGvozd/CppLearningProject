#include "ItemsListWindow.h"
#include "ui_ItemsListWindow.h"

ListItem::ListItem(ListItem *parent, QString name) : QListWidgetItem(*parent){
    this->name = name;
    this->setText(name);
}

ListItem::ListItem(QListWidget *parent, QString name): QListWidgetItem(parent){
    this->name = name;
    this->setText(name);
}

ItemsListWindow::ItemsListWindow(QWidget *parent):
    QDialog(parent),
    ui(new Ui::ItemsListWindow)
{
    ui->setupUi(this);
}

ItemsListWindow::~ItemsListWindow()
{
    delete ui;
}


void ItemsListWindow::addElement(QString name){
    ListItem *line = new ListItem(ui->ListWidget, name);
    line->setFlags(line->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

void ItemsListWindow::planeCharacteristics(int id, QString name, QString model, float health, float speed, float x, float y){
    addElement("Имя - " + name);
    addElement("Модель - " + model);
    addElement("Здоровье - " + QString::number(health));
    addElement("Скорость - " + QString::number(speed));
    addElement("Х - " + QString::number(x));
    addElement("Y - " + QString::number(y));
};
void ItemsListWindow::SAMCharacteristics(int id, QString name, QString model, float health, float distance, int ammo, float x, float y){
    addElement("Имя - " + name);
    addElement("Модель - " + model);
    addElement("Здоровье - " + QString::number(health));
    addElement("Радиус - " + QString::number(distance));
    addElement("Заряды - " + QString::number(ammo));
    addElement("Х - " + QString::number(x));
    addElement("Y - " + QString::number(y));
};
void ItemsListWindow::RocketCharacteristics(int id, QString name, QString model, float damage, float speed, float range, float x, float y){
    addElement("Имя - " + name);
    addElement("Модель - " + model);
    addElement("Урон - " + QString::number(damage));
    addElement("Скорость - " + QString::number(speed));
    addElement("Радиус - " + QString::number(range));
    addElement("Х - " + QString::number(x));
    addElement("Y - " + QString::number(y));
};

void ItemsListWindow::reject(){
    ui->ListWidget->clear();
    QDialog::reject();
}