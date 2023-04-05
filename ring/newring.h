#ifndef NEW_RING_H
#define NEW_RING_H

#include <iostream>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <memory>


template<class T>
class linked_ring
{
    public:


        struct Node
        {
            std::shared_ptr<T> payload;
            std::string socket_name;
            struct Node *next;
            struct Node *prev;
        };
        

        linked_ring(unsigned int start_leangh) : start_leangh(start_leangh)
        {
            user_list =  list_setup(list_create());
            reuse_list = list_setup(list_create());
            init_reuse_list();
        }

        linked_ring()
        {
            this->start_leangh = 30;
            this->usr_list = list_setup(list_create());
            this->reuse_list = list_setup(list_create());
            init_reuse_list();
        }

        ~linked_ring()
        {
            struct Node *node = list_pop_tail(reuse_list);

            while(node != nullptr)
            {
                delete node->payload;
                delete node;

                node = list_pop_tail(reuse_list);
            }

            delete this->usr_list;
            delete this->reuse_list;
        }

        Node *get_new_node()
        {
            std::lock_guard<std::mutex> lock(this->mtx);

            Node *node = list_pick_node();
            return (list_handle_error(node)) ? node : nullptr;
        }

        void push_node(Node *node)
        {
            std::lock_guard<std::mutex> lock(this->mtx);

            list_append(this->usr_list, node);
        }

        Node *pop_node()
        {
            std::lock_guard<std::mutex> lock(this->mtx);

            Node *node = list_pop_tail(this->usr_list);
            return (node != nullptr) ? node : nullptr;
        }

        void reuse_node(Node *node)
        {
            std::lock_guard<std::mutex> lock(this->mtx);

            list_insert_head(this->reuse_list, node);
        }

        int get_size()
        {
            //std::lock_guard<std::mutex> lock(this->mtx);
            return this->usr_list->leangh;
        }

    private:
        std::mutex mtx;


        struct List
        {
            struct Node *head;
            struct Node *tail;
            std::size_t leangh;
        };

        std::shared_ptr<T> user_list;
        std::shared_ptr<T> reuse_list;



        void init_list(std::shared_ptr<List> &list, std::size_t len)
        {


            for (std::size_t i = 0; i < len; i++)
            {
                std::shared_ptr<Node> &node = list_create_node(list_create_payload());
                
            }

            Node *node = nullptr;

            for (unsigned int i = 0; i <  this->start_leangh; i++)
            {


                node = list_create_node(list_create_payload());
                list_insert_head(this->reuse_list, node);
            }
        }

        std::shared_ptr<List>& list_create()
        {
            return std::make_shared<List>();
        }

        int list_handle_error(void *input)
        {
            if (input == nullptr)
            {
                std::cerr << "Error in EffList" << std::endl;
                return false;
            } else {
                return true;
            }
        }

        std::shared_ptr<List>& list_setup(std::shared_ptr<List> &list)
        {
            list.get()->head = nullptr;
            list.get()->tail = nullptr;
            list.get()->leangh = 0;

            return list;
        }

        std::shared_ptr<Node>& list_create_node(std::shared_ptr<T> &payload)
        {
            std::shared_ptr<Node> node = std::make_shared<T>();
            node.get()->payload = payload;
            return node;
        }

        std::shared_ptr<T> list_create_payload()
        {
            retrun std::make_shared<T>();
        }

        Node *list_pick_node()
        {
            return (this->reuse_list->leangh > 0) ? list_pop_tail(this->reuse_list) : list_create_node(list_create_payload());
        }

        //void list_insert_head(List *list, Node *node)
        void list_insert_head(std::shared_ptr<List> &list, std::shared_ptr<Node> node)
        {
            if (list.get()->head = nullptr)
            {
                list.get()->head = 
            }

            if (!list_handle_error(list) || !list_handle_error(node)) return;

            if (list->head == nullptr)
            {
                list->head = node;
                list->tail = node;
                node->next = nullptr;
                node->prev = nullptr;
            } else {
                list->head->prev = node;
                node->next = list->head;
                list->head = node;
                node->prev = nullptr;
            }

            list->leangh++;
        }

        void list_append(List *list, Node *node)
        {

            if (!list_handle_error(list) || !list_handle_error(node)) return;

            list_insert_head(list, node);

            list->leangh++;
        }

        Node *list_pop_tail(List *list)
        {

            Node *node_backup = nullptr;

            if (list->head != nullptr)
            {
                if (list->tail->prev == nullptr)
                {
                    node_backup = list->tail;
                    list->tail = nullptr;
                    list->head = nullptr;
                    node_backup->next = nullptr;
                    node_backup->prev = nullptr;
                } else {
                    node_backup = list->tail;
                    list->tail = list->tail->prev;
                    list->tail->next = nullptr;
                    node_backup->prev = nullptr;
                }

                list->leangh--;

                return node_backup;
            } else {
                return nullptr;
            }
        }

    


};

#endif