template<typename T>
class shared_ptr{
public:
    template<class Y>
        explicit shared_ptr(Y*p);
    template<class Y>
        explicit shared_ptr(shared_ptr<Y>const&r);
    template<class Y>
        explicit shared_ptr(weak_ptr<Y>const&r);
    template<class Y>
        explicit shared_ptr(auto_ptr<Y>const&r);  
    template<class Y>
        shared_ptr& operator=(shared_ptr<Y>const&r);
    template<class Y>
        shared_ptr& operator=(auto_ptr<Y>&r);      
};