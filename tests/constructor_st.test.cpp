#define BOOST_TEST_MODULE MSLogger Constructor
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <string>
#include "ms_logger.h"

// assert singleton in single-threaded case
BOOST_AUTO_TEST_CASE(test_singleton_singlethread)
{
    printf("Starting Test 1 %s\n","test_singleton_singlethread");
    ms_logger<INFO>& msl1a = ms_logger<INFO>::get_instance();
    ms_logger<INFO>& msl1b = ms_logger<INFO>::get_instance();
    BOOST_TEST(&msl1a == &msl1b);

    ms_logger<INFO>& msl2a = ms_logger<INFO>::get_instance();
    ms_logger<INFO>& msl2b = ms_logger<INFO>::get_instance();
    BOOST_TEST(&msl2a == &msl2b);

    ms_logger<DEBUG>& msl3a = ms_logger<DEBUG>::get_instance();
    ms_logger<DEBUG>& msl3b = ms_logger<DEBUG>::get_instance();
    BOOST_TEST(&msl3a == &msl3b);

    BOOST_TEST((void*)&msl1a != (void*)&msl2a);
    BOOST_TEST((void*)&msl1a != (void*)&msl3a);
    BOOST_TEST((void*)&msl2a != (void*)&msl3a);
}

// validate initialization values
BOOST_AUTO_TEST_CASE(test_initialization_values)
{
    printf("Starting Test %s\n","test_initialization_values");

    ms_logger<WARN>& mslWarn = ms_logger<WARN>::get_instance();
    BOOST_TEST( mslWarn.pubget_pptr() == mslWarn.pubget_buffer() );
    BOOST_TEST( mslWarn.pubget_pbase() ==  mslWarn.pubget_buffer() );
    BOOST_TEST( mslWarn.pubget_epptr() ==  mslWarn.pubget_buffer() + mslWarn.pubget_bufferSize() );
    BOOST_TEST( mslWarn.pubget_logLevel() ==  WARN );

    ms_logger<INFO>& mslInfo = ms_logger<INFO>::get_instance();
    BOOST_TEST(mslInfo.pubget_bufferSize() == 1024);

    printf("Finished Test 3\n");
    
}

