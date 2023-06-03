struct Y{
    operator  Y();
    operator int*();//Y is convertible to int*
};
int main()
{
    int *a=Y()+100;//error: no operator+ between pointer and double
}