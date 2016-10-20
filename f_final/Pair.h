#include "testList.h"
#include <iostream>

using namespace std;

template <typename Object>
class Pair {
    public:
        Pair(Object f = Object{}, Object s = Object{}) : fst(f), snd(s)
            {}

        Object first() {
            return fst;
        }

        Object second() {
            return snd;
        }

        Pair & first (Object f) {
            fst = f;
            return *this;
        }

        Pair & second (Object s) {
            snd = s;
            return *this;
        }

    private:
        Object fst;
        Object snd;
};


