/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * BasicMessageBox.hpp
 */

#pragma once

/*******************************************************************

    VOUS N'AVEZ PAS BESOIN DE MODIFIER CE FICHIER

********************************************************************/

#include <array>
#include <algorithm>
#include <mutex>
#include <condition_variable>

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version sans mécanisme de synchronisation
 */
class BasicMessageBox {
public:
    BasicMessageBox()
        : box_{}
        , put_index_{ 0 }
        , get_index_{ 0 }
    {
        std::fill( box_.begin(), box_.end(), -1 );
    }
    
    void basic_put( int message ) {
        box_[ put_index_ ] = message;
        put_index_ = ( put_index_ + 1 ) % box_size_;
    }
 
    int basic_get() {
        int message{ box_[get_index_] };
        // Pour détecter les erreurs
        box_[get_index_] = -1;
        get_index_ = ( get_index_ + 1 ) % box_size_;
        return message;
    }
protected:
    static const unsigned box_size_ = 2;
    // FIFO réalisée par un tableau géré en tampon circulaire via 2 indices (dépôt et retrait)
    std::array< int, box_size_ > box_;
    unsigned put_index_;
    unsigned get_index_;
};
 
