class demo;
int main()
{
	demo *p1 = new demo();
    delete p1;
    demo *p2 = p1;
    p1->func();
    p2->func();
}
