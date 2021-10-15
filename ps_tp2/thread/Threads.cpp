/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Threads.cpp
 * c++ -std=c++20 Threads.cpp -o Threads -lpthread
 */

#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>
 
 
#include "../Random.hpp"
#include "../osyncstream.hpp"
#include "../BasicMessageBox.hpp"

#include "Producer.hpp"
#include "Consumer.hpp"
#include "MessageBox.hpp" 

std::condition_variable cond_place_empty, cond_place_full;
std::mutex data_mutex;
int nb_data;

 
/*
 * Test avec 1 producteur et 1 consommateur
 */
int main() {
    // Créer un générateur de nombres aléatoires
    Random  generator { 100 };
    // Créer une boîte à lettres
    MessageBox box {};
    // Créer un producteur et un consommateur
    Producer produ(1, box, generator, 20);
    Consumer cons(2, box, generator, 20); 
    // Créer les threads correspondants
    std::thread p(produ), c(cons);
    // Attendre la fin des threads
    c.join();
    p.join();
    return 0;
}

