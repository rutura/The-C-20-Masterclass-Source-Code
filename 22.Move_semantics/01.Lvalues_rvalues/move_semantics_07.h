/*
    This file contains code to explore move only types.
    You delete the copy constructor and copy assignment operator in the BoxContainer class.
*/
#pragma once
#include "boxcontainer.h"

namespace move_semantics_07{

    inline void populate_box(box::BoxContainer<int>& box, int modifier){
        for(size_t i{0} ; i < 20 ; ++i){
            box.add((i+1)*modifier);
        }
    }

}   // namespace move_semantics_07