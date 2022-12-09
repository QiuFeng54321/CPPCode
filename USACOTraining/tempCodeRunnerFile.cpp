string to_base(int i, int b)
{
    string str = "";
    int q = i, r = 0;
    while (q != 0)
    {
        r = q % b;
        q = q / b;
        str.insert(str.begin(), r < 10 ? r + '0' : r - 10 + 'A');
    }
    return str;
}
bool is_palindrome(string str)
{
    int head = 0, tail = str.size() - 1;
    while (head <= tail)
    {
        if (str[head] != str[tail])
            break;
        head++;
        tail--;
    }
    return head > tail;
}