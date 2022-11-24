//
// Created by eitan on 23/11/2022.
//

#ifndef WET1_STATUSTYPE_H
#define WET1_STATUSTYPE_H
#include <string>
#include <stdexcept>
using std::string;
using std::runtime_error;


class StatusType: public runtime_error{
public:
    explicit StatusType(const string& what) : runtime_error(what){}
};

class ALLOCATION_ERROR: public StatusType{
public:
    explicit ALLOCATION_ERROR(const string& what) : StatusType(what){}
};

class INVALID_INPUT	: public StatusType{
public:
    explicit INVALID_INPUT	(const string& what) : StatusType(what){}
};

/// is this one necessarily?
class SUCCESS	: public StatusType{
public:
    explicit SUCCESS	(const string& what) : StatusType(what){}
};




#endif //WET1_STATUSTYPE_H
