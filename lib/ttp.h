class Bar;

class Foo
{
    Foo(const Bar& bar);
    bool baz(bool useQux);
protected:
    const Bar& m_bar;
};
