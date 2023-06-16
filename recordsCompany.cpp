//
// Created by MKassem360 on 6/8/2023.
//
#include "recordsCompany.h"
#include "reversedTree.h"

RecordsCompany::RecordsCompany(): Members(),customersHash(), recordsTree(){
    reversedTree *temp = new reversedTree(10);
    recordsTree = temp;
}

RecordsCompany::~RecordsCompany()
{
    deleteTree(Members.getRoot());
}
StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if(number_of_records < 0)
        return StatusType::INVALID_INPUT;
    //reversedTree *recordsTree = new reversedTree(number_of_records);
    recordsTree = new reversedTree(number_of_records);
    recordsTree->initialize(number_of_records);
    for (int i = 0; i < number_of_records ; ++i) {
        Record *record = new Record(i,records_stocks[i]);
        recordsTree->makeset(i,record);
    }
    for (int i = 0; i < customersHash.getSize() ; ++i) {
        customersHash[i].preOrderPathReset(customersHash[i].getRoot());
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
    VipCustomer->accumulatedAmountInc(-VipCustomer->getAccumulatedAmount());
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
    if( VipCustomer == nullptr || r_id >= recordsTree->getSize())
        return StatusType::DOESNT_EXISTS;
    if(!VipCustomer->getMembership()) {
        recordsTree->getData()[r_id]->purchaseCountInc();
        return SUCCESS;
    }
    VipCustomer->accumulatedAmountInc(100+recordsTree->getData()[r_id]->getPurchaseCount());
    recordsTree->getData()[r_id]->purchaseCountInc();
    return SUCCESS;
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount)
{
    if(c_id1 <0 || c_id2 < c_id1 ||amount <= 0)
        return StatusType::INVALID_INPUT;
    Members.changeExtra(c_id2,amount);
    Members.changeExtra(c_id1,-amount);
    return StatusType::SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if(c_id<0)
        return StatusType::INVALID_INPUT;
    Node<Customer*>* member = Members.search(c_id);
    if(member->content == nullptr)
        return StatusType::DOESNT_EXISTS;
    double discount = Members.calcExtra(c_id);
    return member->content->getAccumulatedAmount()-discount;
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if(r_id1 <0 || r_id2<0)
        return StatusType::INVALID_INPUT;
    if(r_id1 >=recordsTree->getSize() || r_id2 >= recordsTree->getSize())
        return StatusType::DOESNT_EXISTS;
    StatusType status = recordsTree->groupUnion(r_id1,r_id2);
    if (status == FAILURE)
        return status;

    return StatusType::SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if(column == nullptr || hight == nullptr || r_id<0)
        return StatusType::INVALID_INPUT;
    if(r_id >=recordsTree->getSize())
        return StatusType::DOESNT_EXISTS;
    *hight = recordsTree->calcHeight(r_id);
    *column = recordsTree->getColumn(r_id);
    return SUCCESS;
}