/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.hpp
 */

#pragma once

#include <iostream>
#include <chrono>
#include <thread>

#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"
#include "../Random.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons {
public:
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        int     nb;
        using   milliseconds = std::chrono::duration< int, std::milli >;

        for (unsigned int i = 0; i < nb_messages_ ; i++)
        {
            nb = random_engine_();
            osyncstream synced_out(std::cout);
            synced_out << "--- Envoi du message : " << nb << " numéro : " << i << " par le producteur ---\n";
            box_.put(nb);
            std::this_thread::sleep_for( milliseconds{ random_engine_() });         
        }
    }
};
 
