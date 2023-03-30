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
        ring_buf(std::size_t len = 30)
        {
            for (int i = 0; i < len; i++)
            {
                _reuse_list.push_back(std::make_shared<T>());
            }
        }

        std::optional<std::shared_ptr<T>> get_new_node()
        {
            check_nodes();
            if (_reuse_list.size())
            {
                std::shared_ptr<T> node = _reuse_list.front();
                _reuse_list.pop_front();
                return node;
            } else {
                return {};
            }
        }

        void push_node(std::shared_ptr<T> node)
        {
            _user_list.push_back(node);
        }

        std::optional<std::shared_ptr<T>> pop_node()
        {
            if(_user_list.size())
            {
                std::shared_ptr<T> node = _user_list.front();
                _user_list.pop_front();
                return node;
            } else {
                return {};
            }
        }

        void ruse_node(std::shared_ptr<T> node)
        {
            _reuse_list.push_back(node);
        }

    private:
        std::list<std::shared_ptr<T>> _user_list;
        std::list<std::shared_ptr<T>> _reuse_list;

        void check_nodes()
        {
            if (!_reuse_list.size())
            {
                _reuse_list.push_back(std::make_shared<T>());
            }
        }
};


#endif