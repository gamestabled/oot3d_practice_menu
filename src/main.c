/*
 * This file is a distant descendent of a file originally written by n3rdswithgame
 */

#include "menu.h"
#include "MyThread.h"
#include "advance.h"

#include "z3D/z3D.h"

advance_input_t inputs = {};

GlobalContext* gGlobalContext;

void scan_inputs() {
    inputs.cur.val = real_hid.pad.pads[real_hid.pad.index].curr.val;
    inputs.pressed.val = (inputs.cur.val) & (~inputs.old.val);
    inputs.up.val = (~inputs.cur.val) & (inputs.old.val);
    inputs.old.val = inputs.cur.val;
}

void advance_main() {

    scan_inputs();

    if(inputs.cur.l && inputs.cur.r && inputs.cur.sel) {
        MyThread* menuThread = menuCreateThread();
        MyThread_Join(menuThread, -1LL);
    }

}

void setGlobalContext(GlobalContext* globalContext){
    gGlobalContext = globalContext;
}

void area_load_main(){}
