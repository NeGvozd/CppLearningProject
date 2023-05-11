#include "chooseline.h"
#include "ui_chooseline.h"

ChooseLine::ChooseLine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseLine)
{
    ui->setupUi(this);
    listWidget = ui->linesList;
    acceptButton = ui->acceptButton;
    cancelButton = ui->cancelButton;
    deleteButton = ui->deleteButton;
    connect(acceptButton, &QPushButton::clicked, this, &ChooseLine::acceptClicked);
    connect(cancelButton, &QPushButton::clicked, this, &ChooseLine::closeWindow);
    connect(listWidget, &QListWidget::itemChanged, this, &ChooseLine::changeName);
    connect(deleteButton, &QPushButton::clicked, this, &ChooseLine::deleteClicked);
}

ChooseLine::~ChooseLine()
{
    delete ui;
}

void ChooseLine::addLine(int id, QString name){
    LineListItem *line = new LineListItem(listWidget, id, name);
    line->setFlags(line->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

void ChooseLine::acceptClicked(){
    if(!listWidget->selectedItems().isEmpty()){
        int itemId = dynamic_cast<LineListItem*>(listWidget->selectedItems()[0])->id;
        emit itemClickSend(itemId);
        this->close();
    }
}

void ChooseLine::deleteClicked(){
    if(!listWidget->selectedItems().isEmpty()){
        QListWidgetItem* it = listWidget->selectedItems()[0];
        emit lineDeleteId(dynamic_cast<LineListItem*>(it)->id);
        delete it;
    }
}

void ChooseLine::closeWindow(){
    this->close();
}

void ChooseLine::changeName(QListWidgetItem *item){
//    qInfo() << "where";
    if(!listWidget->selectedItems().isEmpty()){
        LineListItem* listItem = dynamic_cast<LineListItem*>(item);
        listItem->name = item->text();
        emit itemNameChange(listItem->id, listItem->name);
    }
}

LineListItem::LineListItem(LineListItem *parent, int id, QString name) : QListWidgetItem(*parent){
    this->id=id;
    this->name = name;
    this->setText(name);
}

LineListItem::LineListItem(QListWidget *parent, int id, QString name): QListWidgetItem(parent){
    this->id=id;
    this->name = name;
    this->setText(name);
}
