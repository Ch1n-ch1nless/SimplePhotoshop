#include "exception.hpp"

#include <cstring>
#include <cmath>
#include <iostream>

static const char* const FILE_LOCATION_MESSAGE = "in file: %s\nin function: %s\non line: %d\n";
static const char* const ERROR_MESSAGE         = "error_message: %s\n";

my_stl::MyException::MyException(ErrorCode      code,  
                                 MyException*   prev_exception, 
                                 const char*    file,
                                 const char*    function,
                                 int            line              ) noexcept(true)                     
:
    prev_exception_ (prev_exception),
    message_        (),
    code_           (code),
    file_           (file),
    function_       (function),
    line_           (line)
{
    getFileLocation();
    getErrorInfo(nullptr);
}

my_stl::MyException::MyException(const char*    msg,  
                                MyException*   prev_exception, 
                                const char*    file,
                                const char*    function,
                                int            line                ) noexcept(true)                 
:
    prev_exception_ (prev_exception),
    message_        (),
    code_           (my_stl::ErrorCode::Unknown),
    file_           (file),
    function_       (function),
    line_           (line)
{
    getFileLocation();
    getErrorInfo(msg);
}

my_stl::MyException::~MyException() noexcept(true)
{
    if (prev_exception_ != nullptr) 
    {
        delete prev_exception_;
    }
}

const my_stl::MyException* my_stl::MyException::getPrev() const noexcept(true)
{
    return prev_exception_;
}

const char* my_stl::MyException::what() const noexcept(true)
{
    return message_.c_str();
}

void my_stl::MyException::getFileLocation()
{
    std::size_t len = static_cast<std::size_t>(log10(static_cast<double>(line_))) + 1;
    len += std::strlen(file_) + std::strlen(function_) + std::strlen(FILE_LOCATION_MESSAGE);

    char* new_str = new char[len];

    snprintf(new_str, len, FILE_LOCATION_MESSAGE, file_, function_, line_);

    message_ += new_str;
    delete[] new_str;
}

void my_stl::MyException::getErrorInfo(const char* error_msg)
{
    if (error_msg == nullptr)
    {
        switch (code_)
        {
        case my_stl::ErrorCode::None :
            error_msg = "None";
            break;

        case my_stl::ErrorCode::BadAlloc :
            error_msg = BAD_ALLOC_MESSAGE;
            break;

        case my_stl::ErrorCode::WrongAccess :
            error_msg = WRONG_ACCESS_MESSAGE;
            break;

        case my_stl::ErrorCode::Unknown :
            error_msg = "Unknown";
            break;
        
        default:
            fprintf(stderr, "ERROR!!!\n");
            break;
        }   
    }

    std::size_t len = std::strlen(ERROR_MESSAGE) + std::strlen(error_msg);
    
    char* new_str = new char[len];
    snprintf(new_str, len, ERROR_MESSAGE, error_msg);

    message_ += new_str;
    delete[] new_str;
}