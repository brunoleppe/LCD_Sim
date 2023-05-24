//
// Created by bruno on 23/05/23.
//

#ifndef LCDTEST_ITEMVIEWMODEL_H
#define LCDTEST_ITEMVIEWMODEL_H


#include "ViewModel.h"
#include "MVC/States/StateMenu.h"

class ItemViewModel : public ViewModel{
private:
    StateMenu *stateMenu;
public:
    explicit ItemViewModel(StateMenu* menu) : ViewModel(menu), stateMenu(menu){

    }
    bru::vector<const char*>* get_items(){
        return stateMenu->get_items();
    }
    void set_selected_index(int i){
        stateMenu->set_index(i);
    }
};


#endif //LCDTEST_ITEMVIEWMODEL_H
