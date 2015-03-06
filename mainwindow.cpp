#include "mainwindow.h"
#include "ui_mainwindow.h"
// Write or Read text head document
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

/*    struct PortSettings myComSetting = {BAUD115200,DATA_8,PAR_NONE,STOP_2,FLOW_OFF,500};

    //定义一个结构体，用来存放串口各个参数

//    myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven); //supposed com1~com9

    //定义串口对象，并传递参数，在构造函数里对其进行初始化

//    myCom ->open(QIODevice::ReadWrite);

    //以可读写方式打开串口

//    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));

    //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作*/

    ui->closeMyComBtn->setEnabled(false); //开始“关闭串口”按钮不可用

    ui->sendMsgBtn->setEnabled(false); //开始“发送数据”按钮不可用
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readMyCom() //读串口函数

{

    QByteArray temp = myCom->readAll();

//读取串口缓冲区的所有数据给临时变量temp

    ui->textBrowser->insertPlainText(temp);

//将串口的数据显示在窗口的文本浏览器中

    QFile data("C:/Users/Administrator/Desktop/1234.txt");   //在制定的目录创建一个串口接收信息v
    if(data.open(QFile::WriteOnly|QFile::Append)){
        QTextStream out(&data);
        out<<temp;
    }
    data.close();
}

void MainWindow::on_openMyComBtn_clicked()
{
    QString portName = ui->portNameComboBox->currentText(); //获取串口名


    myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);

    myCom ->open(QIODevice::ReadWrite);

    //以可读写方式打开串口

    if(ui->baudRateComboBox->currentText()==tr("9600")) //根据组合框内容对串口进行设置

    myCom->setBaudRate(BAUD9600);

    else if(ui->baudRateComboBox->currentText()==tr("115200"))

    myCom->setBaudRate(BAUD115200);

    //设置波特率

    if(ui->dataBitsComboBox->currentText()==tr("8"))

    myCom->setDataBits(DATA_8);

    else if(ui->dataBitsComboBox->currentText()==tr("7"))

    myCom->setDataBits(DATA_7);

    //设置数据位

    if(ui->parityComboBox->currentText()==tr("NONE"))

    myCom->setParity(PAR_NONE);

    else if(ui->parityComboBox->currentText()==tr("ODD"))

    myCom->setParity(PAR_ODD);

    else if(ui->parityComboBox->currentText()==tr("EVEN"))

    myCom->setParity(PAR_EVEN);

    //设置奇偶校验

    if(ui->stopBitsComboBox->currentText()==tr("1"))

    myCom->setStopBits(STOP_1);

    else if(ui->stopBitsComboBox->currentText()==tr("2"))

    myCom->setStopBits(STOP_2);

    //设置停止位

    myCom->setFlowControl(FLOW_OFF);

    myCom->setTimeout(500); //设置延时

    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));

    ui->openMyComBtn->setEnabled(false); //打开串口后“打开串口”按钮不可用

    ui->closeMyComBtn->setEnabled(true); //打开串口后“关闭串口”按钮可用

    ui->sendMsgBtn->setEnabled(true); //打开串口后“发送数据”按钮可用

    ui->baudRateComboBox->setEnabled(false); //设置各个组合框不可用

    ui->dataBitsComboBox->setEnabled(false);

    ui->parityComboBox->setEnabled(false);

    ui->stopBitsComboBox->setEnabled(false);

    ui->portNameComboBox->setEnabled(false);
}

void MainWindow::on_closeMyComBtn_clicked()
{
    myCom->close(); //关闭串口，该函数在win_qextserialport.cpp文件中定义

    ui->openMyComBtn->setEnabled(true); //关闭串口后“打开串口”按钮可用

    ui->closeMyComBtn->setEnabled(false); //关闭串口后“关闭串口”按钮不可用

    ui->sendMsgBtn->setEnabled(false); //关闭串口后“发送数据”按钮不可用

    ui->baudRateComboBox->setEnabled(true); //设置各个组合框可用

    ui->dataBitsComboBox->setEnabled(true);

    ui->parityComboBox->setEnabled(true);

    ui->stopBitsComboBox->setEnabled(true);

    ui->portNameComboBox->setEnabled(true);
}

void MainWindow::on_sendMsgBtn_clicked()
{
    myCom->write(ui->sendMsgLineEdit->text().toLocal8Bit());
}
