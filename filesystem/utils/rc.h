//
// Created by dalaoshe on 16-10-17.
//

#ifndef RC_H
#define RC_H
class RC {
    int c;
public:
    RC() {
        c = 0;
    }
    RC(int c) {
        this->c = c;
    }
    bool equal(RC r) {
        return this->c == r.c;
    }
};
#endif //RC_H
