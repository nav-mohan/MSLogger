#if !defined(MS_LOGGER_H)
#define MS_LOGGER_H

#include <streambuf>
#include <stdio.h>
#include <mutex>
#include <iostream>
#include <filesystem> // C++17
#include <fstream>
#include "utilities.h"

template <LEVELS LOGLEVEL=INFO>
class ms_logger : public std::streambuf
{
private: // member variables
    static std::mutex mutCout_;
    static std::mutex mutFile_;
    static std::mutex mutBuffer_;
    static char *buffer_;
    static std::size_t bufferSize_;
    static std::ofstream file_;
    static uint16_t fileindex_;
    static std::string filepath_;
    void write_to_file();
    static void generate_filename();

protected:
    std::streamsize xsputn(const char_type* __s, std::streamsize __n) override;    
    int_type overflow(int_type __ch = traits_type::eof()) override;
    int sync() override;

public:
    static ms_logger<LOGLEVEL> &get_instance();
    static void presize_buffer(std::size_t bs); // set buffersize before instantiation. can increase/decrease buffersize
    void set_bufferSize(std::size_t bs); // set bufferSize after instantiation of logger. can only increase buffersize
    void log_to_stdout(std::string msg, LEVELS l=LOGLEVEL);
    void log_to_file(std::string msg, LEVELS l=LOGLEVEL);

private: // contructors
    ms_logger<LOGLEVEL>();
    ~ms_logger<LOGLEVEL>();
    ms_logger<LOGLEVEL>(const ms_logger<LOGLEVEL>&) = delete;
    ms_logger<LOGLEVEL>& operator= (const ms_logger<LOGLEVEL>&) = delete;



// public interfaces that would come in handy when running tests
// the alternative is to derive a fixture from ms_logger
#if defined(TESTING)
public:
    std::streamsize pubget_bufferSize() const {return bufferSize_;};
    enum LEVELS pubget_logLevel() const {return LOGLEVEL;};
    char *pubget_buffer() const {return buffer_;};
    void* pubget_pbase() const {return pbase();};
    std::size_t pubget_occupied() const {return (pptr() - pbase());}
    void* pubget_pptr() const {return pptr();};
    void* pubget_epptr() const {return epptr();};
#endif // TESTING

};


// instantating static member variables
template <LEVELS LOGLEVEL>
char *ms_logger<LOGLEVEL>::buffer_ = nullptr;

template <LEVELS LOGLEVEL>
uint16_t ms_logger<LOGLEVEL>::fileindex_ = 1;

template <LEVELS LOGLEVEL>
std::mutex ms_logger<LOGLEVEL>::mutCout_;

template <LEVELS LOGLEVEL>
std::mutex ms_logger<LOGLEVEL>::mutFile_;

template <LEVELS LOGLEVEL>
std::mutex ms_logger<LOGLEVEL>::mutBuffer_;

template <LEVELS LOGLEVEL>
std::ofstream ms_logger<LOGLEVEL>::file_;

template <LEVELS LOGLEVEL>
std::string ms_logger<LOGLEVEL>::filepath_;

template <LEVELS LOGLEVEL>
std::size_t ms_logger<LOGLEVEL>::bufferSize_ = 1024;



// Definitions of Templated Class

template <LEVELS LOGLEVEL>
ms_logger<LOGLEVEL>& ms_logger<LOGLEVEL>::get_instance()
{
    static ms_logger<LOGLEVEL> instance;
    return instance;
}

template<LEVELS LOGLEVEL>
void ms_logger<LOGLEVEL>::presize_buffer(std::size_t bs)
{
    std::lock_guard<std::mutex> blk(mutBuffer_);
    if(buffer_ == nullptr)
        bufferSize_ = bs;
    return; // quietly fails if buffer_ != nullptr
}

template <LEVELS LOGLEVEL>
void ms_logger<LOGLEVEL>::set_bufferSize(std::size_t bs)
{
    std::lock_guard<std::mutex> blk(mutBuffer_);
    if(bs < bufferSize_)
        return; // quietly fails if we try downsizing the buffer
    char *tmp = (char*)malloc(bufferSize_);
    memcpy(tmp,buffer_,bufferSize_);
    delete buffer_;
    buffer_ = (char*)malloc(bs);
    ms_logger<LOGLEVEL>::get_instance().setp(buffer_,buffer_+bs);
    memcpy(buffer_,tmp,bufferSize_);
    bufferSize_ = bs;
}

template<LEVELS LOGLEVEL>
void ms_logger<LOGLEVEL>::generate_filename()
{
    switch (LOGLEVEL)
    {
    case TRACE:
        filepath_ = std::move(generate_date()+(fileindex_>9?"_":"_0") + std::to_string(fileindex_) + ".trace.log");
        break;
    case DEBUG:
        filepath_ = std::move(generate_date()+(fileindex_>9?"_":"_0") + std::to_string(fileindex_) + ".debug.log");
        break;
    case INFO:
        filepath_ = std::move(generate_date()+(fileindex_>9?"_":"_0") + std::to_string(fileindex_) + ".info.log");
        break;
    case WARN:
        filepath_ = std::move(generate_date()+(fileindex_>9?"_":"_0") + std::to_string(fileindex_) + ".warn.log");
        break;
    case ERROR:
        filepath_ = std::move(generate_date()+(fileindex_>9?"_":"_0") + std::to_string(fileindex_) + ".error.log");
        break;
    default:
        filepath_ = std::move(generate_date()+(fileindex_>9?"_":"_0") + std::to_string(fileindex_) + ".log");
        break;
    }
}

template <LEVELS LOGLEVEL>
ms_logger<LOGLEVEL>::ms_logger() 
{
    buffer_ = (char*)malloc(bufferSize_);
    printf("Constructing %p (%ld,%d)\n",this,bufferSize_,LOGLEVEL);
    setp(buffer_,buffer_+bufferSize_);
}

template <LEVELS LOGLEVEL>
ms_logger<LOGLEVEL>::~ms_logger()
{
    printf("Deleting %p (%ld,%d)\n",this,bufferSize_,LOGLEVEL);
    std::lock_guard<std::mutex> blk(mutBuffer_);
    if(buffer_ != nullptr)
    {
        if(pptr()-pbase() > 0)
            sync();
        delete buffer_;
    }
}

template <LEVELS LOGLEVEL>
void ms_logger<LOGLEVEL>::log_to_stdout(std::string msg, LEVELS l)
{
    std::lock_guard<std::mutex>lk(mutCout_);
    std::string tmp(colored.at(l) + generate_timestamp() + std::move(msg) + "\n");
    std::clog.write(tmp.c_str(),tmp.size());
}

template <LEVELS LOGLEVEL>
void ms_logger<LOGLEVEL>::log_to_file(std::string msg, LEVELS l)
{
    std::lock_guard<std::mutex> blk(mutBuffer_);
    std::string tmp(uncolored.at(l) + generate_timestamp() + std::move(msg) + "\n");
    sputn(tmp.c_str(),tmp.size());
}


template <LEVELS LOGLEVEL>
std::streamsize ms_logger<LOGLEVEL>::xsputn(const std::streambuf::char_type* __s, std::streamsize __n)
{
    if(epptr() - pptr() >= __n)
    {
        memcpy(pptr(),__s,__n);
        pbump(__n);
        return __n;
    }
    for(std::streamsize i=0 ; i < __n; i++)
    {
        if(traits_type::eq_int_type(sputc(__s[i]),traits_type::eof()))
            return i;
    }
    return __n;
}

template <LEVELS LOGLEVEL>
std::streambuf::int_type ms_logger<LOGLEVEL>::overflow(std::streambuf::int_type __ch)
{
    sync(); // flush the buffer
    if(traits_type::eq_int_type(__ch,traits_type::eof()))
        return traits_type::not_eof(__ch);
    buffer_[0] = __ch;
    pbump(1);
    return static_cast<int_type>(__ch);
}

template <LEVELS LOGLEVEL>
int ms_logger<LOGLEVEL>::sync()
{
    std::lock_guard<std::mutex> flk(mutFile_);
    write_to_file();
    memset(pbase(),0,epptr()-pbase()); // reset the buffer_
    setp(buffer_,buffer_+bufferSize_);
    return 0;
}

template <LEVELS LOGLEVEL>
void ms_logger<LOGLEVEL>::write_to_file()
{
    printf("write_to_file %d\n",LOGLEVEL);
    if(filepath_.empty())
        generate_filename();

    while(std::__fs::filesystem::exists(filepath_) && std::__fs::filesystem::file_size(filepath_) > 8192)
    {
        fileindex_++;
        generate_filename();
    }

    if(!std::__fs::filesystem::exists(filepath_) || !file_.is_open())
        file_.open(filepath_,std::ios::app);

    log_to_stdout("FILESIZE = " + std::to_string(std::__fs::filesystem::file_size(filepath_)),DEBUG);
    if(std::__fs::filesystem::file_size(filepath_) > 8192)
    {
        log_to_stdout("CREATING NEW FILE = " + std::to_string(fileindex_),DEBUG);
        file_.close();
        fileindex_++;
        generate_filename();
        file_.open(filepath_,std::ios::app);
    }

    file_.write(buffer_,pptr()-pbase());
    // check goodbits, errorbits, failbits, 
    if(file_.good()) return;
    if(file_.bad()) 
        log_to_stdout("BADBIT " + std::to_string(file_.badbit),ERROR);
    if(file_.fail()) 
        log_to_stdout("FAILBIT " + std::to_string(file_.failbit),WARN);
    if(file_.eof()) 
        log_to_stdout("EOFBIT " + std::to_string(file_.eofbit),INFO);

}

#endif // MS_LOGGER_H