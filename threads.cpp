#include <iostream>
#include <list>
#include <pthread.h>

using std::cout;
using std::endl;
using std::list;

struct block {
    int unit;

    block(int unit) {
        this->unit = unit;
    }
};

list<block*> freelist;
list<block*> list1;
list<block*> list2;

std::ostream& operator<<(std::ostream& os, const block* blk)
{
    os << blk->unit << endl;
    return os;
}

int randomNum() {
    static thread_local std::mt19937 gen;
    std::uniform_int_distribution<int> distribution(1, 1000);
    return distribution(gen);
}

block* unlink(int lst) {
    block* rv;
    if (lst == 0) {
        rv = freelist.back();
        freelist.pop_back();
    } 
    else if (lst == 1) {
        rv = list1.back();
        list1.pop_back();
    } 
    else {
        rv = list2.back();
       list2.pop_back();
    }

    return rv;
}

void link(block* toLink, int lst) {
    block* rv;
    if (lst == 0) {
        rv = freelist.back();
        freelist.pop_back();
    } 
    else if (lst == 1) {
        rv = list1.back();
        list1.pop_back();
    } 
    else {
       rv = list2.back();
       list2.pop_back();
    }

    return rv;
}

void produce_information_in_block(block* n) {
    n->unit = randomNum();
}

void consume_information_in_block(block* n) {
    n->unit = 0;
}

void use_block_x_to_produce_info_in_y(block* x, block* y) {
    y->unit = x->unit;
    x->unit = 0;
}


void* thread1(void* ptr) {
    // block* b;
    // while (1) {
    //     b = unlink(0);
    //     produce_information_in_block(b);
    //     link(b, 1); 
    // }

}

void* thread2(void* ptr) {
    // block *x,*y;
    // while (1) {
    //     x = unlink(1);
    //     y = unlink(0);
    //     use_block_x_to_produce_info_in_y(x, y);
    //     link(x, 0);
    //     link(y, 2);
    // }

}

void* thread3(void* ptr) {
    // block* c;
    // while(1) {
    //     c = unlink(2);
    //     consume_information_in_block(c);
    //     link(c, 0);
    // }
  
}

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Usage: ./a.out <N>" << endl;
        return 0;
    }

    int N = atoi(argv[1]);

    for (int i = 0; i < N; i++) {
        freelist.push_back(new block(0));
    }

    pthread_t threads[3];

    int rc;

    rc = pthread_create(&threads[0], NULL, thread1, NULL);
    if (rc) {
         cout << "Unable to create thread" << rc << endl;
         exit(-1);
      }

    rc = pthread_create(&threads[1], NULL, thread2, NULL);
    if (rc) {
        cout << "Unable to create thread" << rc << endl;
        exit(-1);
    }

    rc = pthread_create(&threads[2], NULL, thread3, NULL);
    if (rc) {
        cout << "Unable to create thread" << rc << endl;
        exit(-1);
    }

     pthread_exit(NULL);

    return 0;
}
