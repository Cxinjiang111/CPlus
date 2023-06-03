class GameCharacter;
class HealthCalcFunc{
public:
    virtual int calc(const GameCharacter &gc)const{}
};
HealthCalcFunc defaultHealthCalc;
class GameCharacter{
public:
    explicit GameCharacter(HealthCalcFunc*phfc=&defaultHealthCalc):pHealthCalc(phfc)
    {
    }
    int healthValue()const
    {
        return pHealthCalc->calc(*this);
    }
private:
    HealthCalcFunc *pHealthCalc;
};