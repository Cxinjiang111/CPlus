/*intput iterator   output iterator 与此相似
相关型别
value type

different type 
这时一个有正负号的整数，表示某个iterator到另一个iterator的距离，
reference type
这时iterator的value type的reference，如果iterator是mutable，则
此型别为一个mutable reference，如果iterator 是constant ，则此型别为一个const reference
返回时T& const T& 
pointer type
返回时T* const T* 
iterator type 

此型别为以下iterator tag types之一 ： 
input_iterator＿tag 、 forward_iterator＿tag 、
bidirectional_iterator_tag、random_access_iterator_tag。
 所谓iterator category（类 属），
是指对应于该iterator之「最具体(most specific) concept」的一个tag type,而该iterator 便是此 一 concept的一个model。 
例如，int ＊是Random Access Iterator的一个model, 它同 样也是 Bidirectional Iterator和 Forward Iterator的 一个model。 
其 category（类属）是 random_access_iterator_tag, 因为Random Access Iterator对 ＊int而言是最具体(most specific)的concept。 
（噢是的， Random Access Iterator是其他所有iterator concepts的强化。 ）
*/