#ifndef __SOCKET__EXCEPTION__HPP__
    #define __SOCKET__EXCEPTION__HPP__

    #include <exception>
    #include <string>

    class socketException : public std::exception
    {
        public:
            socketException(std::string message);
            const char* what() const noexcept override;
        private:
            std::string message;
    };

#endif