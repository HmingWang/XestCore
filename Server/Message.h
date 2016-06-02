//
// Created by whaim on 16-5-31.
//

#ifndef XESTCORE_MESSAGE_H
#define XESTCORE_MESSAGE_H

#include <iostream>
#include <string>
#include <memory.h>
#include "Define.h"

class Header
{
private:
    int _serviceId;
    int _dataLength;

public:
    int Get_ServiceId(){return _serviceId;}
    int Get_DataLenth(){return _dataLength;}
    void Set_ServiceId(int value){_serviceId=value;}
    void Set_DataLength(int value){_dataLength=value;}
    int Size(){return sizeof(Header);}

    bool ParseFromArray(const void* Buffer,int size)
    {
        if(size<sizeof(int)*2) return false;

        _serviceId=*(int*)Buffer;
        _dataLength=*((int*)(Buffer)+sizeof(int));
        return true;
    }
    void Print()
    {
        std::cout<<"\n=====================================\n";
        std::cout<<"ServiceId:"<<_serviceId<<std::endl;
        std::cout<<"DataLength:"<<_dataLength<<std::endl;
        std::cout<<"\n=====================================\n";
    }
};

#endif //XESTCORE_MESSAGE_H
