//
// Created by MKassem360 on 6/8/2023.
//
#include "recordsCompany.h"
#include "reversedTree.h"

RecordsCompany::RecordsCompany(): Members(),customersHash(), recordsTree(10)
{

}

RecordsCompany::~RecordsCompany()
{

}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if(number_of_records < 0)
        return StatusType::INVALID_INPUT;
    reversedTree *recordsTree = new reversedTree(number_of_records);
    for (int i = 0; i < number_of_records ; ++i) {
        Record *record = new Record(i,records_stocks[i]);
        recordsTree->makeset(i,record);
    }
    for (int i = 0; i < customersHash.getSize() ; ++i) {
        customersHash[i].preorderpath;
    }
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if(c_id < 0 || phone < 0)
        return StatusType::INVALID_INPUT;
    Customer *customer = new Customer (c_id,phone);
    return customersHash.Insert(customer);
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if(c_id <0)
        return StatusType::INVALID_INPUT;
    Customer *customer =customersHash.Search(c_id);
    if(customer == nullptr){
        return StatusType::DOESNT_EXISTS;
    }
    return customer->getPhone();
}

StatusType RecordsCompany::makeMember(int c_id)
{
    if(c_id < 0)
        return StatusType::INVALID_INPUT;
    Customer* VipCustomer = customersHash.Search(c_id);
    if( VipCustomer == nullptr)
        return StatusType::DOESNT_EXISTS;
    if( VipCustomer->getMembership())
        return StatusType::ALREADY_EXISTS;
    VipCustomer->setMembership(true);
    Node<Customer*>* node = new Node<Customer*>(c_id,VipCustomer, nullptr);
    Members.searchAndAdd(node);
    return StatusType::SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if(c_id < 0 )
        return StatusType::INVALID_INPUT;
    Customer* VipCustomer = customersHash.Search(c_id);
    if( VipCustomer == nullptr)
        return StatusType::DOESNT_EXISTS;
    return VipCustomer->getMembership();
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if(c_id < 0 || r_id < 0)
        return StatusType::INVALID_INPUT;

    Customer* VipCustomer = customersHash.Search(c_id);
    if( VipCustomer == nullptr || r_id >= recordsTree.getSize())
        return StatusType::DOESNT_EXISTS;
    if(!VipCustomer->getMembership()) {
        recordsTree.getData()[r_id]->purchaseCountInc();
        return SUCCESS;
    }
    VipCustomer->accumulatedAmountInc(100+recordsTree.getData()[r_id]->getPurchaseCount());
    recordsTree.getData()[r_id]->purchaseCountInc();
    return SUCCESS;
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount)
{
    if(c_id1 <0 || c_id2<0||amount <= 0)
        return StatusType::INVALID_INPUT;
    Members.
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{

}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{

}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{

}