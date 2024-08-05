module;

export module move_semantics_03;

import boxcontainer;

namespace move_semantics_03{

    void populate_box(box::BoxContainer<int>& box, int modifier){
        for(size_t i{0} ; i < 20 ; ++i){
            box.add((i+1)*modifier);
        }
    }

    export box::BoxContainer<int> make_box(int modifier){
        box::BoxContainer<int> local_int_box(20);
        populate_box(local_int_box,modifier);
        return local_int_box;
    }

}  // namespace move_semantics_03