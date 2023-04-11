## Thread-Safe Header-Only Logging library based on C++17

* Implements Meyers Singleton for threadsafe constructor.
* Uses C++17 `<filesystem>` for monitoring log-files.
* Derives from `std::streambuf` and maintains an internal buffer

## Key protected-methods of `std::streambuf`
* `xsputn()` : For efficiently writing to buffer.
* `overflow()` : For writing to buffer when buffer is full. Flushes the entire buffer to the file by calling `sync()`. 
* `sync()` : For flushing the buffer to the file when logger is destroyed or when buffer is full.

## Thread-Safety
* Meyers Singleton guarantess C++11 and above compilers will create and access the `static` object in a thread-safe manner. 
* Dedicated `mutex` when writing to `std::clog`
* Dedicated `mutex` when accesing the buffer
* Dedicated `mutex` when accesing the logfile

The strength of this library is that it's a single header file.
It does not provide the flexiblity of something like `Boost Logger` i.e it does not allow you to define sinks, sources, and filters. 

As of now, it logs to rotating textfiles and `std::clog`. No support for database. This might change in the future. 

Boost Logger implements the `Observer Design Pattern`. Hence, the source and sink are not as tightly coupled. Thats what gives you the flexbility to log to multiple sinks. But repeatedly calling upon function pointers is less performant than calling a function directly. 

The class is templated on the logging-level. Default `loglevel` = `INFO`. \
`ms_logger<WARN>::get_instance()` is a separate instance from `ms_logger<INFO>::get_instance()`. They write to separate log files. 


Default buffersize is 1024\
A static method `presize_buffer(std::size_t)` can be called before instantaion to increase/decrease buffersize\
A non-static method `set_bufferSize(std::size_t)` can be called after instantiation to increase buffersize (not decrease).