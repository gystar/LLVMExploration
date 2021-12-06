int add(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 1;
    int b = 2;
    int c = 0;
    if (a > 1)
        c = add(a, b);
    else
        c = 10;

    return c;
}