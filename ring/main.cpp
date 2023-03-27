#include <iostream>
#include <memory>
#include <algorithm>
#include <optional>
#include <chrono>

struct CAN
{
    int a;
    int b;
    int c;
};

#include "ring.h"
#include "crossi_ring_buf.h"

#define LEN_ 100000

std::shared_ptr<struct CAN> print_can(std::shared_ptr<struct CAN> can)
{
    std::cout << can.get()->a << " ";
    std::cout << can.get()->b << " ";
    std::cout << can.get()->c << std::endl;

    return can;
}

std::shared_ptr<struct CAN> fill_can(std::shared_ptr<struct CAN> can)
{
    can.get()->a = rand()%20;
    can.get()->b = rand()%20;
    can.get()->c = rand()%20;

    return can;
}

//void test_new_ring(ring_buf<std::shared_ptr<struct CAN>> &m)
void test_new_ring(ring_buf<struct CAN> &m)
{
    

    for (int i = 0; i < LEN_; i++)
    {
        std::optional<std::shared_ptr<struct CAN>> node = m.get_new_node();
        if (node.has_value())
        {
            m.push_node(node.value());
        } else {
            std::cout << "Fail: " << i << std::endl;
        }
    }

    for (int i = 0; i < LEN_; i++)
    {
        std::optional<std::shared_ptr<struct CAN>> node = m.pop_node();
        if (node.has_value())
        {
            m.ruse_node(node.value());
        } else {
            std::cout << "Fail: " << i << std::endl;
        }
    }
}

void test_old_ring(ring<struct CAN> &m)
{
    

    for (int i = 0; i < LEN_; i++)
    {
        m.push_node(m.get_new_node());
    }

    for (int i = 0; i < LEN_; i++)
    {
        m.reuse_node(m.pop_node());
    }
}

int main()
{
    std::cout << "Halo Welt" << std::endl;

    ring_buf<struct CAN> m(LEN_);
    //ring_buf<std::shared_ptr<struct CAN>> m(LEN_);
    ring<struct CAN> n(LEN_);

    auto start_new = std::chrono::high_resolution_clock::now();
    test_new_ring(m);
    auto end_new = std::chrono::high_resolution_clock::now();
    
    auto start_old = std::chrono::high_resolution_clock::now(); 
    test_old_ring(n);
    auto end_old = std::chrono::high_resolution_clock::now();

    auto duration_new = std::chrono::duration_cast<std::chrono::milliseconds>(start_new - end_new).count();
    auto duration_old = std::chrono::duration_cast<std::chrono::milliseconds>(start_old - end_old).count();

    std::cout << "New: " << duration_new << std::endl;
    std::cout << "Old: " << duration_old<< std::endl;

    return EXIT_SUCCESS;
}