#include <__MiniNebula/App.h>

int main(int argc, char *argv[] ) {
    App app;

    if (!app.init(argc, argv)) {
        return -1;
    }


    if (!app.run()) {
        return -1;
    }

    return 0;
}
