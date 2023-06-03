enum { __stl_num_primes = 28 };
//按照质数来设计表格
static const unsigned long __stl_prime_list[__stl_num_primes] =
{
  53ul,         97ul,         193ul,       389ul,       769ul,
  1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
  49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
  1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
  50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul, 
  1610612741ul, 3221225473ul, 4294967291ul
};

//以下找出上述28个质数之中，最接近并大于n的那个质数
inline unsigned long __stl_next_prime(unsigned long __n)
{
  const unsigned long* __first = __stl_prime_list;
  const unsigned long* __last = __stl_prime_list + (int)__stl_num_primes;
  const unsigned long* pos = lower_bound(__first, __last, __n);//已__n为下限
  return pos == __last ? *(__last - 1) : *pos;
}

//hashtable桶的最大数量
size_type max_bucket_count() const
{ return __stl_prime_list[(int)__stl_num_primes - 1]; } 