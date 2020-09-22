//
// Created by antoine on 22/09/20.
//

#include "plugin.h"

int plugin_is_GPL_compatible;

//void callback_start_unit(
//        void *gcc_data, void *user_data) {
//    printf("Callback start unit\n");
//}


int
plugin_init(struct plugin_name_args *plugin_info,
            struct plugin_gcc_version *version) {
//    register_callback(plugin_info->base_name,
//                      PLUGIN_START_UNIT,
//                      callback_start_unit,
//                      NULL);

    struct register_pass_info pass_info;
    my_pass p(g);
    pass_info.pass = &p;
    pass_info.reference_pass_name =
            "cfg";
    pass_info.ref_pass_instance_number = 0;
    pass_info.pos_op = PASS_POS_INSERT_AFTER;
    register_callback(
            plugin_info->base_name,
            PLUGIN_PASS_MANAGER_SETUP,
            NULL,
            &pass_info);

    return 0;
}

