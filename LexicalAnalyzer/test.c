int add(int a, int b)
{
	static float inta = 2.5e-3f;
	auto int ret = a + b * 3ULL;
	return ret + (a <= 2 ? (inta -= 1.5F), (inta += -5e+03);
}
