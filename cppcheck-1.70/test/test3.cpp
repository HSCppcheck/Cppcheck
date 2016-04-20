int main()
{
	int *p1 = new int(0);
	delete p1;
	int *p2 = p1;
	int *p3 = p2;
	int *p4 = p3;
	*p1 = 0;
	*p2 = 0;
	*p3 = 0;
	*p4 = 0;
}