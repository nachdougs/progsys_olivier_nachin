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
int main()
{
    // Créer un générateur de nombres aléatoires
    Random  generator { 2000 };
    // Créer une boîte à lettres
    MessageBox box {};
    // Créer un producteur et un consommateur
    Producer produ1(1, box, generator, 10);
    Producer produ2(2, box, generator, 10);
    Producer produ3(3, box, generator, 10);
    Producer produ4(4, box, generator, 10);
    Consumer cons1(1, box, generator, 20); 
    Consumer cons2(2, box, generator, 20); 
    // Créer les threads correspondants
    std::thread p1(produ1), p2(produ2), p3(produ3), p4(produ4), c1(cons1), c2(cons2);
    // Attendre la fin des threads
    p1.join();
    p2.join();
    p3.join();
    p4.join();
    c1.join();
    c2.join();
    return 0;
}

