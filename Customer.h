//
// Created by MKassem360 on 6/8/2023.
//

#ifndef HW2_WET_ Customer_H
#define HW2_WET_ Customer_H

// stored in a tree
class  Customer {
int c_id;
int phoneNum;
bool Membership;
int numOfOrders;
int accumulatedAmount; // for members

public:
    Customer(int c_id, int phoneNum):c_id(c_id),phoneNum(phoneNum),Membership(0),numOfOrders(0){};
    int getID() const{return this->c_id;};
    int getPhone() const {return phoneNum;};
    bool getMembership() const{return Membership;};
    void setMembership(const bool state){ this->Membership=state;};
    int getAccumulatedAmount() const{return accumulatedAmount;};
    int accumulatedAmountInc(int value){accumulatedAmount+=value;};
};

// stored in an array
class Record {
    int r_id; // a number between 0 - (numOfRecords-1)
    int numOfRecords;
    int purchaseCount;
public:
    Record():r_id(0),numOfRecords(0),purchaseCount(0){};
    Record(int r_id,int numOfRecords):r_id(r_id),numOfRecords(numOfRecords),purchaseCount(0){};
    void purchaseCountInc(){purchaseCount++;};
    int getPurchaseCount(){return purchaseCount;};
};

#endif //HW2_WET_ Customer_H
