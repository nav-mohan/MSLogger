#define BOOST_TEST_MODULE MSLogger SingleThread tests on streambuf pointers
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/regex.hpp>

#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <streambuf>
#include "ms_logger.h"

// a test to see if pointers to buffers are updated properly in multithreaded operation

BOOST_AUTO_TEST_CASE(test_check_update_pptr_singlethread)
{
    ms_logger<INFO>::presize_buffer(128);
    ms_logger<INFO>& msl1 = ms_logger<INFO>::get_instance();
    ms_logger<INFO>& msl2 = ms_logger<INFO>::get_instance();
    ms_logger<INFO>& msl3 = ms_logger<INFO>::get_instance();

    std::string msg("hello world");
    msl1.log_to_file(msg);
    BOOST_TEST( msl1.pubget_pbase() == msl1.pubget_buffer() );
    BOOST_TEST( msl1.pubget_pptr() == msl1.pubget_buffer() + 30 + msg.size());
    BOOST_TEST( msl1.pubget_epptr() == msl1.pubget_buffer() + msl1.pubget_bufferSize() );

    BOOST_TEST(msl1.pubget_occupied() == 30 + msg.size());

}

