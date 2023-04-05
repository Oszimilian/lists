#include <iostream>
#include <mutex>
#include <memory>
#include <string>
#include <list>
#include <optional>

template<class T>
class list_mtx
{
    public: 
        void push_node(T &node)
        {
            std::lock_guard<std::mutex> lock(_mtx);
            _list.push_front(node);
        }

        std::optional<std::shared_ptr<T>> get_node()
        {
            std::shared_ptr<T> node = std::make_shared<T> (_list.front());
            if (node)
            {
                _list.pop_front();
                return node;
            } else {
                return {};
            }
        }

    private:
        std::mutex _mtx;
        std::list<T> _list;
};