//
// Created by antoine on 22/09/20.
//

#ifndef CODE_PLUGIN_H
#define CODE_PLUGIN_H

#include <gcc-plugin.h>
#include <tree.h>
#include <tree-pass.h>
#include <context.h>
#include <function.h>
#include <basic-block.h>
#include <gimple.h>
#include <gimple-iterator.h>
#include <bitmap.h>
#include <c-family/c-pragma.h>

int plugin_is_GPL_compatible;

#endif //CODE_PLUGIN_H
