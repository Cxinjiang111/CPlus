class House{

};

class HouseBuilder{

public:

    House *GetResult(){
        return pHouse;
    }

    virtual ~HouseBuilder(){}
protected:

    House *pHouse;
    virtual void BuildPart1()=0;
    virtual void BuildPart2()=0;
    virtual void BuildPart3()=0;
    virtual void BuildPart4()=0;
    virtual void BuildPart5()=0;
};
class StoneHouse:public House{

};
class StoneHouseBuilder:public HouseBuilder{
    
protected:
     void BuildPart1(){

     }
     void BuildPart2(){

     }
     void BuildPart3(){

     }
     void BuildPart4(){

     }
     void BuildPart5(){

     }
};
class HouseDirector{

public:
    HouseBuilder *pHouseBuilder;

    HouseDirector(HouseBuilder *pHouseBuilder){
        this->pHouseBuilder=pHouseBuilder;
    }
    House *Construct{

        pHouseBuilder->BuildPart1();
        for(int i=0;i<4;i++){
            pHouseBuilder->BuilderPart2();
        }

        bool flag=pHouseBuilder->BuilderPart3();
        if(flag){
            pHouseBuilder->BuilderPart4();
        }
        pHouseBuilder->BuilderPart5();
        return pHouseBuilder->GetResult();
    }
};

