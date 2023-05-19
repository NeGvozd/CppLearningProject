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
    deleting = true;
    LineListItem *line = new LineListItem(listWidget, id, name);
    line->setFlags(line->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

void ChooseLine::acceptClicked(){
    if(!listWidget->selectedItems().isEmpty()){
        int itemId = dynamic_cast<LineListItem*>(listWidget->selectedItems()[0])->Id();
        emit itemClickSend(itemId);
        this->close();
    }
}

void ChooseLine::deleteClicked(){
    deleting = true;
    if(!listWidget->selectedItems().isEmpty()){
        QListWidgetItem* it = listWidget->selectedItems()[0];
        emit lineDeleteId(dynamic_cast<LineListItem*>(it)->Id());
        delete it;
    }
}

void ChooseLine::closeWindow(){
    this->close();
}

void ChooseLine::changeName(QListWidgetItem *item){
    if(!listWidget->selectedItems().isEmpty() && !deleting){
        LineListItem* listItem = dynamic_cast<LineListItem*>(item);
        listItem->setName(item->text());
        emit itemNameChange(listItem->Id(), listItem->Name());
    }
    if(deleting) deleting = false;
}

LineListItem::LineListItem(LineListItem *parent, int id, QString name) : QListWidgetItem(*parent), id_(id), name_(name){
    this->setText(name);
}

LineListItem::LineListItem(QListWidget *parent, int id, QString name): QListWidgetItem(parent), id_(id), name_(name){
    this->setText(name);
}

void LineListItem::setName(QString name){
    name_ = name;
}

int LineListItem::Id() const{
    return id_;
}

QString LineListItem::Name() const{
    return name_;
}