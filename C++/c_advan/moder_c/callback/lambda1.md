三、函数原型
[capture list] (params list) mutable exception-> return type { function body }
各项具体含义如下：

capture list：捕获外部变量列表
params list：形参列表
mutable指示符：用来说用是否可以修改捕获的变量
exception：异常设定
return type：返回类型
function body：函数体

// 格式1
[capture list] (params list) -> return type {function body}
// 格式2
[capture list] (params list) {function body}
// 格式3
[capture list] {function body}
格式 1 声明了 const 类型的表达式，这种类型的表达式不能修改捕获列表中的值。
格式 2 省略了返回值类型，但编译器可以根据以下规则推断出 Lambda 表达式的返回类型：（1）：如果 function body 中存在 return 语句，则该 Lambda 表达式的返回类型由return语句的返回类型确定；（2）：如果 function body 中没有 return 语句，则返回值为 void 类型。
格式 3 中省略了参数列表，类似普通函数中的无参函数。








