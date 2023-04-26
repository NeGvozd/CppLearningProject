#ifndef CHOOSELINE_H
#define CHOOSELINE_H

#include <QDialog>

namespace Ui {
class ChooseLine;
}

class ChooseLine : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseLine(QWidget *parent = nullptr);
    ~ChooseLine();

private:
    Ui::ChooseLine *ui;
};

#endif // CHOOSELINE_H
