//using extern to make it global 
extern int count;

int getCount()
{
    return count+10;
}

int incrementNum()
{
    static int num = 0;
    return num++;
}

int nonStaticNum()
{
    int non = 0;
    return non++;
}
