/*
 * This file is a distant descendent of a file originally written by n3rdswithgame
 */

#include "menu.h"
#include "MyThread.h"
// #include "task_runner.h"
#include "advance.h"

advance_input_t inputs = {};

void scan_inputs() {
    inputs.cur.val = real_hid.pad.pads[real_hid.pad.index].curr.val;
    inputs.pressed.val = (inputs.cur.val) & (~inputs.old.val);
    inputs.up.val = (~inputs.cur.val) & (inputs.old.val);
    inputs.old.val = inputs.cur.val;
}

void advance_main() {

    scan_inputs();

    if(inputs.cur.l && inputs.cur.r && inputs.cur.sel) {
        /* menu stuff goes here i guess */
        // probably looks like making the menu threads and joining them
        MyThread* menuThread = menuCreateThread();
        // MyThread* taskThread = taskRunnerCreateThread();
        MyThread_Join(menuThread, -1LL);
        // MyThread_Join(taskThread, -1LL);
    }

}

void area_load_main(){}
