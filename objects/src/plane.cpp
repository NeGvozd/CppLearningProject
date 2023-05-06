#include "plane.h"
#include "rocket.h"
#include "point.h"
#include "sam.h"

#include <math.h>

#include <QDebug>

#define KM 0.0115

Plane::Plane(float health, float speed, const QString& model, 
             const std::shared_ptr<QVector<Point*>> tragectory) :
    health_(health), speed_(speed/60), model_(model), tragectory_(tragectory), curTragPoint(-1), //скорость за 15 мин
    Point(-999, -999) {}

void Plane::Move(){
    if(isAlive){
        if(curTragPoint == -1){
            if(tragectory_)
                if(!(x_==(*tragectory_)[(*tragectory_).size()-1]->X() && y_==(*tragectory_)[(*tragectory_).size()-1]->Y())){
                    curTragPoint=prevTragPoint;
                }
        }
        if(curTragPoint != -1){
            if(curTragPoint+1 == (*tragectory_).size()){
                prevTragPoint=curTragPoint;
                curTragPoint=-1;
            }
            else{
                Point* dest = tragectory_->at(curTragPoint+1);
                float dist = this->length(dest);
                float angle_ = this->angle(dest);
                if(dist<speed_*KM){
                    curTragPoint+=1;
                    x_=(*tragectory_)[curTragPoint]->X();
                    y_=(*tragectory_)[curTragPoint]->Y();
                }
                else{
                    y_+=speed_*KM*sin(angle_);
                    x_+=speed_*KM*cos(angle_);
                }
            }
        }
    }
}

void Plane::setTragectory(std::shared_ptr<QVector<Point*>> tragectory){
    if(curTragPoint!= -1) tragectory_->append(*tragectory);
    else{ 
        tragectory_ = tragectory;
        X(tragectory->at(0)->X());
        Y(tragectory->at(0)->Y());
        curTragPoint = 0;
    }
}

std::unique_ptr<Rocket> Plane::Fire(std::weak_ptr<SAM>)
{
//    return std::make_unique<Rocket>();
}

void Plane::ReceiveDamage(float amount)
{
    health_ -= amount;
    if (health_ <= 0) delete this;
}

float Plane::retAngle(){
    return angle_;
}