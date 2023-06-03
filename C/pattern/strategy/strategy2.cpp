

class TaxStrategy{
public:
virtual double CalcuateTax()=0;
virtual ~TaxStrategy(){};
};
class StrategyFactory:public TaxStrategy{
public:
    TaxStrategy* NewStrategy();
};
class CN_Tax:public TaxStrategy{
public:
    virtual double CalcuateTax(){

    }    
};
class US_Tax:public TaxStrategy{
public:
    virtual double CalcuateTax(){

    }    
};
//已写好的不同在修改并编译
//可扩展性添加
class DE_Tax:public TaxStrategy{
public:
    virtual double CalcuateTax(){

    }    
};
class  SaleOrder{
private:
    TaxStrategy *strategy;//这儿一定指针
public:
    SaleOrder(StrategyFactory *stratergyFactory){
        this->strategy=stratergyFactory->NewStrategy();
    }
    ~SaleOrder(){
        delete this->strategy;
    }
    public:
     double CalcuateTax(){

     }
};