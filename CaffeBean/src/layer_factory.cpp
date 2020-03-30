//
// Created by Kaiyu Xie on 2020/2/24.
//

#include "../include/layer_factory.h"

LayerFactory::LayerFactory() {
    register_all_layers();
}

/*
 * If you would like to create a new layer,
 * there are 3 steps:
 * 1. Finish my_magic_layer.cpp & my_magic_layer.h
 * 2. Add REGISTER_LAYER(MyMagic) below
 * 3. Add ADD_CREATOR(MyMagic) in LayerFactory::register_all_layers()
 * that's all!
 */

REGISTER_LAYER(Input)

REGISTER_LAYER(FullyConnected)

REGISTER_LAYER(L1Loss)

REGISTER_LAYER(Relu)

REGISTER_LAYER(Pooling)

void LayerFactory::register_all_layers() {
    ADD_CREATOR(Input)
    ADD_CREATOR(FullyConnected)
    ADD_CREATOR(L1Loss)
    ADD_CREATOR(Relu)
    ADD_CREATOR(Pooling)
}

void LayerFactory::add_creator(const std::string &type, Creator creator_func) {
    creator_registry_[type] = creator_func;
}

std::unique_ptr<Layer> LayerFactory::create_layer(const std::shared_ptr<Config> &config) {
    auto type = config->get_type();
    std::unique_ptr<Layer> layer = creator_registry_[type](config);
    CAFFEBEAN_LOG(type << ": " << config->get_name() << " done.");
    return layer;
}

