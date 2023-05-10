#include "ItemsListWindow.h"
#include "ui_ItemsListWindow.h"

void ItemsListWindow::planeCharacteristics(int id, QString name, QString model, float health, float speed, float x, float y){
    ui->ListWidget->addItem("Имя - " + name);
    ui->ListWidget->addItem("Модель - " + model);
    ui->ListWidget->addItem("Здоровье - " + QString::number(health));
    ui->ListWidget->addItem("Скорость - " + QString::number(speed));
    ui->ListWidget->addItem("Х - " + QString::number(x));
    ui->ListWidget->addItem("Y - " + QString::number(y));
};
void ItemsListWindow::SAMCharacteristics(int id, QString name, QString model, float health, float distance, int ammo, float x, float y){
    ui->ListWidget->addItem("Имя - " + name);
    ui->ListWidget->addItem("Модель - " + model);
    ui->ListWidget->addItem("Здоровье - " + QString::number(health));
    ui->ListWidget->addItem("Радиус - " + QString::number(distance));
    ui->ListWidget->addItem("Заряды - " + QString::number(ammo));
    ui->ListWidget->addItem("Х - " + QString::number(x));
    ui->ListWidget->addItem("Y - " + QString::number(y));
};
void ItemsListWindow::RocketCharacteristics(int id, QString name, QString model, float damage, float speed, float range, float x, float y){
    ui->ListWidget->addItem("Имя - " + name);
    ui->ListWidget->addItem("Модель - " + model);
    ui->ListWidget->addItem("Урон - " + QString::number(damage));
    ui->ListWidget->addItem("Скорость - " + QString::number(speed));
    ui->ListWidget->addItem("Радиус - " + QString::number(range));
    ui->ListWidget->addItem("Х - " + QString::number(x));
    ui->ListWidget->addItem("Y - " + QString::number(y));
};