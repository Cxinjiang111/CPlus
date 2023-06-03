/*
set的特性是，所有元素都会根据元素的键值自动被排序。
set的元素不像map那样可以同时拥有实值(value)和键值(key),set元素的键值就是实值，
实值就是键值。set不允许两个元素有相同的键值。
我们可以通过set的迭代器改变set的元素值吗？不行，因为set元素值就
是其键值，关系到set兀素的排列规则。如果任意改变set元素值，会严重破坏 set组织。稍后你会在set源代码之中看到，set<T>:: i tera七or被定义为底层
RB-tree的const_iterator,杜绝写人操作。换句话说，setiterators是一种
constant iterators（相对于mutableiterators)
set拥有与list相同的某些性质：当客户端对它进行元素新增操作
(inse江）或删除操作(erase)时，操作之前的所有迭代器，在操作完成之后都依然有效。
当然，被删除的那个元素的迭代器必然是个例外。
set拥有与list相同的某些性质：当客户端对它进行元素新增操作
(inse江）或删除操作(erase)时，操作之前的所有迭代器，
在操作完成之后都依然有效。当然，被删除的那个元素的迭代器必然是个例外。
syrnmetric_difference,详见6.5节。
由于RB-tree是一种平衡二叉搜索树，自动排序的效果很不错，所以标准的STL
set即以RB-tree为底层机制9又由千set所开放的各种操作接口，RB-tree也
都提供了，所以几乎所有的set操作行为，都只是转调用RB-tree的操作行为而已。
*/