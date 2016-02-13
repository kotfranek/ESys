#include "app/SimpleApp.h"
#include "esys/AutoString.h"
#include "sys/AbstractThread.h"
#include "sys/StopWatch.h"
#include "sys/SystemInfo.h"

#include <iostream>

namespace
{
    class Th1 : public ::sys::AbstractThread
    {
    public:
        explicit Th1( const uint32_t id )
            : ::sys::AbstractThread( ::std::to_string( id ) )
            , m_char( 'A' + id )
        {
        }
        
    private:        
        virtual void run()
        {
            uint32_t i = 100;
            while ( i != 0U )
            {
                if ( isStopRequested() )
                {
                    ::std::cout << "Thread '" << m_char << "' requested to stop on i = " << i << ::std::endl;
                    break;
                }
                
                ::std::cout << "TH: '" << m_char << "', i = " << i << ::std::endl;
                sleep( 30 + ( m_char * 2U ) );
                --i;
            }
        }
        
        const char m_char;
    };
}



class DemoApp : public ::app::SimpleApp
{
public:
    DemoApp()
        : ::app::SimpleApp( "ESysDemo" )
    {

    }
    
private:    
    virtual int32_t onRun( const TStringVector& args )
    {       
        ::esys::TString31 str1( "0123456789" );
        ::esys::TString63 str2( "ABCDEFGHIJ" );
        
        ::std::cout << "str1 = '" << str1 << "', sr2 = '" << str2 << "'" << ::std::endl;      
        ::std::cout << "str1.length() = " << str1.length() << ", str2.length() = " << str2.length() << ::std::endl; 
        
        ::std::cout << "str1.append( str2 ).append( str2 ).append( str2 );" << ::std::endl;      
        str1.append( str2 ).append( str2 ).append( str2 );
        
        ::std::cout << "str1 = '" << str1 << "', Str2 = '" << str2 << "'" << ::std::endl; 
        ::std::cout << "str1.length() = " << str1.length() << ", str2.length() = " << str2.length() << ::std::endl; 
        
        const size_t offset = str1.find( "AB-C", 12 );
        
        ::std::cout << "First occurence is: " << offset << ::std::endl;        
        
        str1.c_format( "ProcessId = %d", ::sys::SystemInfo::getOwnProcessId() );                   
        ::std::cout << str1 << ::std::endl;
        str1.clear();
        
        
        
        ::sys::StopWatch stW( true );
        
        const size_t NUM_TH = 26U;
        
        Th1* threads[ NUM_TH ];
        
        for ( size_t i = 0U; i < NUM_TH; i++ )
        {
            threads[ i ] = new Th1( i );
            threads[ i ]->start();      
        }        
        
        waitForExit( 200 );
        
        for ( size_t i = 0U; i < NUM_TH; i++ )
        {
            threads[ i ]->requestStop();            
            threads[ i ]->join();
            
            delete threads[ i ];
        }
        
        ::std::cout << "Took: " << stW.stop() << " us" << ::std::endl;
        
        return 0;
    }
};


int32_t main( int argc, const char * const * argv )
{
    return ::DemoApp().run( argc, argv );
}
