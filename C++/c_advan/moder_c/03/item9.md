Item 9:Prefer alias declarations to typedefs
我相信每个⼈都同意使⽤STL容器是个好主意，并且我希望Item18能说服你让你觉得使⽤
std:unique_ptr也是个好主意，但我猜没有⼈喜欢写上⼏次
std::unique_ptr<std::unordered_map<std::string,std::string>>这样的类型，它可能会让你
患上腕管综合征的⻛险⼤⼤增加。
避免上述医疗悲剧也很简单，引⼊typedef即可：
typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS;
using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;