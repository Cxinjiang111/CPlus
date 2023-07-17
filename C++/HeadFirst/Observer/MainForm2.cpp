class MainForm : public Form, public IProgress //函数实现功能类
{
	TextBox* txtFilePath;
	TextBox* txtFileNumber;

	ProgressBar* progressBar;

public:
	void Button1_Click(){ //可放入主函数

		string filePath = txtFilePath->getText();
		int number = atoi(txtFileNumber->getText().c_str());

		ConsoleNotifier cn;

		FileSplitter splitter(filePath, number);

		splitter.addIProgress(this); //订阅通知
		splitter.addIProgress(&cn); //订阅通知

		splitter.split();

		splitter.removeIProgress(this);

	}

	virtual void DoProgress(float value){
		progressBar->setValue(value);
	}
};
//观察者1
class ConsoleNotifier : public IProgress {  //
public:
	virtual void DoProgress(float value){
		cout << ".";
	}
};

