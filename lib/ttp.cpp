#include "ttp.h"

Foo::Foo(const Bar& bar)
 : m_bar(bar) {};

bool Foo::baz(bool useQux) {
    if (useQux) {
        return true;
    } else {
        return false;
    }
}
