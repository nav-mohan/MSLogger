#define BOOST_TEST_MODULE MSLogger MultiThread tests on streambuf pointers to Buffers
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/thread.hpp>
#include <boost/mutex.hpp>
#include <boost/regex.hpp>

#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <streambuf>
#include "ms_logger.h"
#include <thread>
#include <mutex>

// a test to see if pointers to buffers are updated properly in multithreaded operation

BOOST_AUTO_TEST_CASE(test_check_update_pptr_multithread)
{
    ms_logger<INFO>& msl1 = ms_logger<INFO>::get_instance();
    ms_logger<INFO>& msl2 = ms_logger<INFO>::get_instance();
    ms_logger<INFO>& msl3 = ms_logger<INFO>::get_instance();

    std::mutex mut;
    std::condition_variable cond;
    int counter = 0;
    
    boost::atomic<bool> ready;


}

