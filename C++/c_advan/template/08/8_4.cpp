特化的Concepts
 Random Number Generator是一种function object,可用来产生整数随机数列。
 如果 f 是一个Random Number Generator并且 N 是个正数， 则 f(N) 返回一个小于 N 且大于等于0的整数。
  如果以同一 个 N 多次调用f, 产生的数列在range [0, N) 中将是均匀分布(uniformly distributed) 