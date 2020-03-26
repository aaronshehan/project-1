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


// need to consider empty list
block* unlink(int lst) {
    if (lst == 0) {
        
    } 
    else if (lst == 1) {

    } 
    else {

    }
}

void link(block* toLink, int lst) {
    if (lst == 0) {
        freelist.push_back(toLink);
    } 
    else if (lst == 1) {
        list1.push_back(toLink);
    } 
    else {
        list2.push_back(toLink);
    }
}

void produce_information_in_block(block* n) {

}

void consume_information_in_block(block* n) {

}

void use_block_x_to_produce_info_in_y(block* x, block* y) {

}


void* thread1(void* ptr) {
    // block* b;
    // while (1) {
    //     b = unlink(0);
    //     produce_information_in_block(b);
    //     link(b, 1); 
    // }

    cout << "thread 1" << endl;
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
     cout << "thread 2" << endl;
}

void* thread3(void* ptr) {
    // block* c;
    // while(1) {
    //     c = unlink(2);
    //     consume_information_in_block(c);
    //     link(c, 0);
    // }
     cout << "thread 3" << endl;
}

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Usage: ./a.out <N>" << endl;
        return 0;
    }

    int N = atoi(argv[1]);

    for (int i = 0; i < N; i++) {
        freelist.push_back(new block(i));
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
