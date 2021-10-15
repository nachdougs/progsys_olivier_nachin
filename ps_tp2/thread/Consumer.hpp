/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"
 
/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons {
public:
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        using   milliseconds = std::chrono::duration< int, std::milli >;

        for (unsigned int i = 0 ; i < nb_messages_ ; i++) 
        {
            osyncstream(std::cout) << "--- Lecture du message numéro : "
            << i << " par le consommateur qui contient le nombre : " << box_.get() << " ---\n";
            std::this_thread::sleep_for( milliseconds{ random_engine_() });
        }
    }
};

