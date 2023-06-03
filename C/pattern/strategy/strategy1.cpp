typedef enum {
    CN_Tax,
    US_Tax,
    DE_Tax
}Tax;
class  SaleOrder
{
Tax tax;
public:
double CalcuateTax(){
    if(tax==CN_Tax){

    }
    else if(tax==US_Tax){

    }
    else if(tax=DE_Tax){

    }
}
     SaleOrder(/* args */);
    ~ SaleOrder();
};


