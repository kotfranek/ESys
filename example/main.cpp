#include "app/SimpleApp.h"
#include "sys/AbstractThread.h"
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
            uint32_t i = 200;
            while ( i != 0U )
            {
                if ( isStopRequested() )
                {
                    ::std::cout << "Thread '" << m_char << "' requested to stop on i = " << i << ::std::endl;
                    break;
                }
                
                ::std::cout << "TH: '" << m_char << "', i = " << i << ::std::endl;
                sleep( 50 + ( m_char * 2U ) );
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
        : ::app::SimpleApp( "dupet" )
    {

    }
    
private:    
    virtual int32_t onRun( const TStringVector& args )
    {       
        const size_t NUM_TH = 26U;
        
        Th1* threads[ NUM_TH ];
        
        for ( size_t i = 0U; i < NUM_TH; i++ )
        {
            threads[ i ] = new Th1( i );
            threads[ i ]->start();      
        }        
        
        waitForSignal( 1500U );
        
        for ( size_t i = 0U; i < NUM_TH; i++ )
        {
            threads[ i ]->requestStop();            
            threads[ i ]->join();
            
            delete threads[ i ];
        }
        
        return 0;
    }
};


int32_t main( int argc, const char * const * argv )
{
    return ::DemoApp().run( argc, argv );
}
