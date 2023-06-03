#include<iostream>
#include<string>
using namespace std;
/*
13.1定义
　　给定一门语言，定义它的文法的一种表示，并定义一个解释器，该解释器使用该表示来解释语言中的句子
13.2 优点
　　■ 简单的语法分析工具。
　　■ 扩展性，修改语法规则只要修改相应的非终结符表达式即可，若扩展语法，则只要增加非终结符类即可。
13.3 缺点
　　■ 解释器模式会引起类膨胀。每个语法都要产生一个非终结符表达式，语法比较复杂时就可能产生大量的类文件，不易维护。
　　■ 采用递归调用方法。每个非终结符表达式只关心与自己有关的表达式，每个表达式需要知道最终的结果，
必须一层一层地剥茧，无论是面向过程的语言还是面向对象的语言，递归都是在必要条件下使用的，不易调试且影响效率。
13.4. 使用场景
　　■ 重复发生的问题可以使用解释器模式。例如，多个应用服务器，每天产生大量的日志，
需要对日志文件进行分析处理，由于各个服务器的日志格式不同，但是数据要素是相同的，
按照解释器的说法就是终结符表达式都是相同的，非终结符表达式就需要制定。
*/
//抽象表达式
class Expression {
public:
  virtual bool interpret(string context) = 0;
};

//终结符表达式
class TerminalExpression:public Expression {
private:
    string m_data;
public:
//构造函数
    TerminalExpression(string data){
      this->m_data = data;
       }
    //重写解释函数
    bool interpret(string context) {
      if(context.find(m_data)!= string::npos){
         return true;
      }
      return false;
   }
};
//非终结符表达式
class OrExpression:public Expression {
private:
    Expression* expr1 = NULL;
    Expression* expr2 = NULL;

public:
//   构造函数
    OrExpression(Expression* expr1, Expression* expr2) {
      this->expr1 = expr1;
      this->expr2 = expr2;
       }
    //重写解释函数
    bool interpret(string context) {
      return expr1->interpret(context) || expr2->interpret(context);
   }
};
//非终结符表达式
class AndExpression:public Expression {
private:
    Expression* expr1 = NULL;
    Expression* expr2 = NULL;

public:
    AndExpression(Expression* expr1, Expression* expr2) {
      this->expr1 = expr1;
      this->expr2 = expr2;
   }
    bool interpret(string context) {
      return expr1->interpret(context) && expr2->interpret(context);
   }
};
