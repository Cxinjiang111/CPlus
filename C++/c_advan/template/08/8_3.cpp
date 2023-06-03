/*
Strict Weak Ordering 
Strict Weak Ordering是 种Binary Predicate,可用来比较两个objects:
如果第个object位于第二个object之剒 就返回true。这个predicate必须满足
strict weak ordering的标准定义。 以下正是其精确的条件描述， 大略意思是：
 Strict Weak Ordering必须满足传统的（例如less than)次序(ordering) 关系。
  举个例子， 如果 a 小于 b, 则 b 必定不小于 a 。

Strict Weak Ordering和Strict Weakly Comparable这两个concepts都和strict weak ordering有关，
只是形式稍微不同。 其中一个是以operator<定义出来的次序条件」所形成的集合，
另一个则是以某个functionobject定义出来的次序条件」所形成的集合。
这两个concepts互补， 因为凡使用次序关系的算法， 通常都会成对出现， 
其中一个版本使用 operator<来比较数值， 另一个版本使用外界提供的functionobject作为评量标准。
这种情况下， 第 一版本使用Strict Weakly Comparable, 第二版本使用Strict Weak Ordering。
比如：
    less<T>
    greater<T>
    less<string>
    greater<string>
*/