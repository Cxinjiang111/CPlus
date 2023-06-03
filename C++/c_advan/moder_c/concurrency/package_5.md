std::packaged_task::operator()(Args... args) 介绍

调用该 packaged_task 对象所包装的对象(通常为函数指针，函数对象，lambda 表达式等)，传入的参数为 args. 调用该函数一般会发生两种情况：

如果成功调用 packaged_task 所包装的对象，则返回值（如果被包装的对象有返回值的话）被保存在 packaged_task 的共享状态中。
如果调用 packaged_task 所包装的对象失败，并且抛出了异常，则异常也会被保存在 packaged_task 的共享状态中。
以上两种情况都使共享状态的标志变为 ready，因此其他等待该共享状态的线程可以获取共享状态的值或者异常并继续执行下去。

共享状态的值可以通过在 future 对象(由 get_future获得)上调用 get 来获得。

由于被包装的任务在 packaged_task 构造时指定，因此调用 operator() 的效果由 packaged_task 对象构造时所指定的可调用对象来决定：

如果被包装的任务是函数指针或者函数对象，调用 std::packaged_task::operator() 只是将参数传递给被包装的对象。
如果被包装的任务是指向类的非静态成员函数的指针，那么 std::packaged_task::operator() 的第一个参数应该指定为成员函数被调用的那个对象，剩余的参数作为该成员函数的参数。
如果被包装的任务是指向类的非静态成员变量，那么 std::packaged_task::operator() 只允许单个参数。
std::packaged_task::make_ready_at_thread_exit 介绍

该函数会调用被包装的任务，并向任务传递参数，类似 std::packaged_task 的 operator() 成员函数。但是与 operator() 函数不同的是，make_ready_at_thread_exit 并不会立即设置共享状态的标志为 ready，而是在线程退出时设置共享状态的标志。

如果与该 packaged_task 共享状态相关联的 future 对象在 future::get 处等待，则当前的 future::get 调用会被阻塞，直到线程退出。而一旦线程退出，future::get 调用继续执行，或者抛出异常。

注意，该函数已经设置了 promise 共享状态的值，如果在线程结束之前有其他设置或者修改共享状态的值的操作，则会抛出 future_error( promise_already_satisfied )。

std::packaged_task::reset() 介绍

重置 packaged_task 的共享状态，但是保留之前的被包装的任务。请看例子，该例子中，packaged_task 被重用了多次：