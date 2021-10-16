/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <array>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre threads
 */
class MessageBox : public BasicMessageBox {
public:
    void put( int message )
    {
        {
            std::unique_lock<std::mutex> lock(data_mutex); // on lock le mutex associé à la boîte
            // si on arrive ici : on a accès à la boîte, mais attenion, si ça se trouve la boîte est accessible mais pleine !
            while(nb_data == 2)
            {
                cond_place_available.wait(lock); // signal d’accès que la boîte est vide
            }
            basic_put( message ); // on écrit dans la boîte
            nb_data += 1;
            cond_place_filled.notify_one();
        } 
    }
 
    int get()
    {
        int message;
        {
            std::unique_lock<std::mutex> lock(data_mutex);
            while (nb_data == 0)
            {
                cond_place_filled.wait(lock);
            }
            message = basic_get();
            nb_data -= 1;
            cond_place_available.notify_one();
        }
        return message;
    }
private:
    int nb_data = 0;
    std::condition_variable cond_place_available, cond_place_filled;
    std::mutex data_mutex; 
};
 
