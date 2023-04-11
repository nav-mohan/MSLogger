#define BOOST_TEST_MODULE MSLogger Constructor
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/thread.hpp>
#include <string>
#include "ms_logger.h"

#include <boost/atomic.hpp>

// assert singleton in multi-threaded case
BOOST_AUTO_TEST_CASE(test_singleton_multithread)
{
    printf("Starting Test 2 %s\n","test_singleton_multithread");
    void* ptr1a = nullptr;
    void* ptr1b = nullptr;
    void* ptr2a = nullptr;
    void* ptr2b = nullptr;
    void* ptr3a = nullptr;
    void* ptr3b = nullptr;
    boost::atomic<bool> ready; // this is just to kick-start all threads as-simultaneously-as-possible
    boost::thread thread1a([&ptr1a,&ready]{while(!ready.load()){}; ptr1a = (void*)&ms_logger<INFO>::get_instance();});
    boost::thread thread1b([&ptr1b,&ready]{while(!ready.load()){}; ptr1b = (void*)&ms_logger<INFO>::get_instance();});
    
    boost::thread thread2a([&ptr2a,&ready]{while(!ready.load()){}; ptr2a = (void*)&ms_logger<INFO>::get_instance();});
    boost::thread thread2b([&ptr2b,&ready]{while(!ready.load()){}; ptr2b = (void*)&ms_logger<INFO>::get_instance();});
    
    boost::thread thread3a([&ptr3a,&ready]{while(!ready.load()){}; ptr3a = (void*)&ms_logger<DEBUG>::get_instance();});
    boost::thread thread3b([&ptr3b,&ready]{while(!ready.load()){}; ptr3b = (void*)&ms_logger<DEBUG>::get_instance();});

    boost::thread verifier
    (
        [&ptr1a,&ptr1b,&ptr2a,&ptr2b,&ptr3a,&ptr3b,&ready]
        {
            while((!ready.load()) || (ptr1a == nullptr) || (ptr1b==nullptr) || (ptr2a == nullptr) || (ptr2b == nullptr) || (ptr3a == nullptr) || (ptr3b == nullptr)){;}; 
            BOOST_TEST(ptr1a==ptr1b);
            BOOST_TEST(ptr2a==ptr2b);
            BOOST_TEST(ptr3a==ptr3b);
            BOOST_TEST(ptr1a!=ptr2a);
            BOOST_TEST(ptr2a!=ptr3a);
        }
    );
    ready.store(true); // kick-start all threads simultaneously
    thread1a.join();
    thread1b.join();
    thread2a.join();
    thread2b.join();
    thread3a.join();
    thread3b.join();
    verifier.join();
    
}