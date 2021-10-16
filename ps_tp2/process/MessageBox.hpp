/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <array>
#include <algorithm>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre processus
 */

class MessageBox : public BasicMessageBox
{
public:
    void put( int message )
    {
        {
            using namespace boost::interprocess;
            scoped_lock<interprocess_mutex> lock(mutex_); // on lock le mutex associé à la boîte
            // si on arrive ici : on a accès à la boîte, mais attenion, si ça se trouve la boîte est accessible mais pleine !
            while(nb_data == 2)
            {
                cond_available.wait(lock); // signal d’accès que la boîte est vide
            }
            basic_put( message ); // on écrit dans la boîte
            nb_data += 1;
            cond_filled.notify_one();
        } // mutex unlocked ici
    }
 
    int get()
    {
        int message;
        {
            std::cout << "coucou\n";
            using namespace boost::interprocess;
            std::cout << "before lock\n";
            scoped_lock<interprocess_mutex> lock(mutex_);
            std::cout << "after lock\n";
            while (nb_data == 0)
            {
                std::cout << "inside wait\n";
                cond_filled.wait(lock);
            }
            std::cout << "before basic get\n";
            message = basic_get();
            std::cout << "after basic get\n";
            nb_data -= 1;
            cond_available.notify_one();
        }
        return message;
    }
private:
    boost::interprocess::interprocess_mutex mutex_;
    boost::interprocess::interprocess_condition  cond_available, cond_filled;
    int nb_data = 0;
};
 
