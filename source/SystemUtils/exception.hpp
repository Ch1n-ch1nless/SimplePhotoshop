#ifndef  MY_EXCEPTION_IMPLEMENTATION_HPP
#define  MY_EXCEPTION_IMPLEMENTATION_HPP

#include <exception>
#include <string>

#define MY_EXCEPTION(arg, prev_exception) my_stl::MyException(arg, prev_exception, __FILE__, (const char*)__FUNCTION__, __LINE__)

namespace my_stl
{
    enum class ErrorCode : int
    {
        Unknown     = -1,
        None        =  0,
        BadAlloc    =  1,
        WrongAccess =  2,
    };

    const char* const   BAD_ALLOC_MESSAGE       = "Memory allocation problem\n";
    const char* const   WRONG_ACCESS_MESSAGE    = "Access problem\n";

    class MyException : public std::exception
    {
    public:
         MyException(ErrorCode      code,  
                     MyException*   prev_exception, 
                     const char*    file,
                     const char*    function,
                     int            line                        ) noexcept(true);
         MyException(const char*    msg, 
                     MyException*   prev_exception,
                     const char*    file,
                     const char*    function,
                     int            line                        ) noexcept(true);

        virtual ~MyException() noexcept(true);

        virtual const char* what()      const noexcept(true) override;
        const MyException*  getPrev()   const noexcept(true);

    private:
        void                getFileLocation();
        void                getErrorInfo   (const char* error_msg);

        MyException*    prev_exception_;
        std::string     message_;
        ErrorCode       code_;

        const char*     file_;
        const char*     function_;
        int             line_;
    };
}

#endif //MY_EXCEPTION_IMPLEMENTATION_HPP