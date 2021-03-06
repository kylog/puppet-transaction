#pragma once

#include "internal/ruby/value_registry.hpp"

#include <puppet-transaction/value.hpp>

#include <leatherman/ruby/api.hpp>
#include <memory>

namespace puppet_transaction { namespace ruby {
    class value_wrapper : public value {
    public:
        value_wrapper(leatherman::ruby::VALUE, value_registry*);
        virtual ~value_wrapper();

        leatherman::ruby::VALUE self() const { return _self; }

        template <typename T>
        static std::shared_ptr<T> wrap(leatherman::ruby::VALUE value, value_registry *registry) {
            auto ptr = std::dynamic_pointer_cast<T>(registry->get(value));
            if (!ptr) {
                 ptr = std::make_shared<T>(value, registry);
                 registry->add(value, ptr);
            }
            return ptr;
        }

    protected:
        leatherman::ruby::VALUE _self;
        mutable value_registry* _registry;
    };
}}
