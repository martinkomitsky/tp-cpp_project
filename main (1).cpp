#include <iostream>
#include <unistd.h>
#include "EventDispatcher.h"

using namespace std;

class Foo : public EventDispatcher
{
    public:
        void Run ( void )
        {
            for ( int key = 0 ; key < 5 ; key ++ )
            {
                this->DispatchEvent ( "EVENT_1" );
                this->DispatchEvent ( "EVENT_2" );
                usleep ( 500000 );
            };
        };
};

class Bar
{
    public:
        void EventHandler1 ( void )
        {
            cout << "FOO_EVENT_1 listen next\n";
        };

        void EventHandler2 ( void )
        {
            cout << "FOO_EVENT_2 listen prev \n";
        };
};

int main()
{
    Foo* foo = new Foo ( );
    Bar* bar = new Bar ( );

    foo->AddEventListener ( "EVENT_1" , bar , &Bar::EventHandler1 ); //добавляем слушателя (подписываем) объект bar на событие EVENT_1
    foo->Run();
    foo->RemoveEventListener ( "EVENT_1" , bar , &Bar::EventHandler1 ); // Удаляем слушателя
    foo->AddEventListener ( "EVENT_2" , bar , &Bar::EventHandler2 );
    foo->Run();
    foo->RemoveEventListener ( "EVENT_2" , bar , &Bar::EventHandler2 );

    return 1;
};
