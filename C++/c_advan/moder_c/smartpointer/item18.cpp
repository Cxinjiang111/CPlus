auto delInvmt = [](Investment* pInvestment)
{
    makeLogEntry(pInvestment);
    delete pInvestment;
}
template<typename... Ts> 
std::unique_ptr<Investment, decltype(delInvmt)> 
makeInvestment(Ts&& params)
{ 
    std::unique_ptr<Investment, decltype(delInvmt)> pInv(nullptr, delInvmt);
    if (/*a Stock object should be created*/) 
    { 
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else if ( /* a Bond object should be created */ ) 
    {
         pInv.reset(new Bond(std::forward<Ts>(params)...)); 
    }
    else if ( /* a RealEstate object should be created */ )
    {
         pInv.reset(new RealEstate(std::forward<Ts>(params)...)); 
    }
    return pInv;
}
稍后，我将解释其⼯作原理，但⾸先请考虑如果你是调⽤者，情况如何。
假设你存储 makeInvestment 调⽤结果在auto变量中，那么你将在愉快中忽略在删除过程中需要特殊处理的事实，
当然，你确实幸 福，因为使⽤了 unique_ptr 意味着你不需要考虑在资源释放时的路径，以及确保只释放⼀次， 
std::unique_ptr ⾃动解决了这些问题。从使⽤者⻆度， makeInvestment 接口很棒。 这个实现确实相当棒，
如果你理解了： delInvmt 是⾃定义的从 makeInvestment 返回的析构函数。所有的⾃定义的析构⾏为接受要销毁 对象的原始指针，然后执⾏销毁操作。
如上例⼦。使⽤lambda创建 delInvmt 是⽅便的，而且，正如稍后看到的，⽐编写常规的函数更有效 当使⽤⾃定义删除器时，
必须将其作为第⼆个参数传给 std::unique_ptr 。对于decltype，更多 信息查看Item3
makeInvestment 的基本策略是创建⼀个空的 std::unique_ptr ，然后指向⼀个合适类型的对 象，
然后返回。为了与pInv关联⾃定义删除器，作为构造函数的第⼆个参数 尝试将原始指针（⽐如new创建）赋值给 std::unique_ptr 通不过编译，
因为不存在从原始指针 到智能指针的隐式转换。这种隐式转换会出问题，所以禁⽌。这就是为什么通过 reset 来传递new
指针的原因 使⽤new时，要使⽤ std::forward 作为参数来完美转发给 makeInvestment （查看Item 25）。 
这使调⽤者提供的所有信息可⽤于正在创建的对象的构造函数 ⾃定义删除器的参数类型是 Investment* ，
尽管真实的对象类型是在 makeInvestment 内部创建 的，它最终通过在lambda表达式中，
作为 Investment* 对象被删除。这意味着我们通过基类指针 删除派⽣类实例，为此，基类必须是虚函数析构：、



数组的 std::unique_ptr 的存在应该不被使⽤，因为 std::array , std::vector , std::string 
这些 更好⽤的数据容器应该取代原始数组。原始数组的使⽤唯⼀情况是你使⽤类似C的API返回⼀个指向堆数组的原始指针

std::unique_ptr 是轻量级、快速的、只能move的管理专有所有权语义资源的智能指针 默认情况，资源销毁通过delete，
但是⽀持⾃定义delete函数。有状态的删除器和函数指针会增加std::unique_ptr的⼤小 
将 std::unique_ptr 转化为 std::shared_ptr 是简单的
