#ifndef RING_H_
#define RING_H_

#include <iostream>
#include <mutex>
#include <string>
#include <list>
#include <memory>
#include <algorithm>
#include <optional>



template<class T>
class ring_buf
{
    public:
        ring_buf(std::size_t len)
        {
            _user_list = std::make_shared<std::list<std::shared_ptr<T>>>();
            _reuse_list = std::make_shared<std::list<std::shared_ptr<T>>>();

            for (int i = 0; i < len; i++)
            {
                _reuse_list.get()->push_back(std::make_shared<T>());
            }
        }

        std::optional<std::shared_ptr<T>> get_new_node()
        {
            check_nodes();
            if (_reuse_list.get()->size())
            {
                std::shared_ptr<T> node = _reuse_list.get()->front();
                _reuse_list.get()->pop_front();
                return node;
            } else {
                return {};
            }
        }

        void push_node(std::shared_ptr<T> &node)
        {
            _user_list.get()->push_back(node);
        }

        std::optional<std::shared_ptr<T>> pop_node()
        {
            if(_user_list.get()->size())
            {
                std::shared_ptr<T> node = _user_list.get()->front();
                _user_list.get()->pop_front();
                return node;
            } else {
                return {};
            }
        }

        void ruse_node(std::shared_ptr<T> &node)
        {
            _reuse_list.get()->push_back(node);
        }

    private:
        std::shared_ptr<std::list<std::shared_ptr<T>>> _user_list;
        std::shared_ptr<std::list<std::shared_ptr<T>>> _reuse_list;

        void check_nodes()
        {
            if (!_reuse_list.get()->size())
            {
                _reuse_list.get()->push_back(std::make_shared<T>());
            }
        }
};


#endif