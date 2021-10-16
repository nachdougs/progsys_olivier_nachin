/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.cpp
 * c++ -std=c++20 Consumer.cpp -o Consumer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "../Random.hpp"
#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"
#include "MessageBox.hpp"

/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        using   milliseconds = std::chrono::duration< int, std::milli >;

        for (unsigned int i = 0 ; i < nb_messages_ ; i++) 
        {
            std::cout << "Consommateur n°" << name_ << " lit le message : " << box_.get() << "\n";
            std::this_thread::sleep_for( milliseconds{ random_engine_() });
        }
    }
};

int main ()
{
    // TODO : accéder à la mémoire partagée, la projeter en mémoire,
    // y accéder comme boîte à lettres, lancer le consommateur

    using namespace boost::interprocess;
    shared_memory_object shm_obj (open_only, "shared_memory", read_only);
    mapped_region region(shm_obj, read_only);
    void *addr = region.get_address();
    MessageBox * box = static_cast<MessageBox*>(addr);
    // code principal
    Random  generator { 2000 };
    Consumer cons(1, *box, generator, 20);
    cons();
    shared_memory_object::remove("shared_memory");
    
    return 0;
}