/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.cpp
 * c++ -std=c++20 Producer.cpp -o Producer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "../Random.hpp"

#include "ProdOrCons.hpp"
#include "MessageBox.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons {
public:
    // Le constructeur de ProdOrCons peut être utilisé pour Producer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        int     nb;
        using   milliseconds = std::chrono::duration< int, std::milli >;

        for (unsigned int i = 0; i < nb_messages_ ; i++)
        {
            nb = random_engine_();
            box_.put(nb);
            std::cout << "Producteur n°" << name_ << " envoie le message : " << nb << "\n";
            std::this_thread::sleep_for( milliseconds{ random_engine_() });  
        }
    }
};
 
int main()
{
    using namespace boost::interprocess;
    
    // destruction de la mémoire partagée
    struct shm_remove
    {
        shm_remove() { shared_memory_object::remove("shared_memory"); }
        ~shm_remove(){ shared_memory_object::remove("shared_memory"); }
    } remover;

    // création de la mémoire partagée
    shared_memory_object shm_obj (create_only, "shared_memory", read_write);
    // choix de la taille de la mémoire partagée
    shm_obj.truncate(sizeof(MessageBox));
    // mappage de la mémoire partagée
    mapped_region region(shm_obj, read_write);
    void *addr = region.get_address();
    // création de la boîte
    MessageBox * box = new(addr) MessageBox();

    // Code principal :
    Random  generator { 2000 };
    Producer prod(1, *box, generator, 20);

    prod();

    // destruction de la mémoire partagée
    shared_memory_object::remove("shared_memory");
    
    return 0;
}

