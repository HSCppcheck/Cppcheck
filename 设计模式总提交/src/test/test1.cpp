int main()
{
	int *p1 = new int(0);
	delete p1;
	int *p2 = p1;
	*p1 = 0;
	*p2 = 0;
}