#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    move((QApplication::desktop()->width() - width()) / 2,
         (QApplication::desktop()->height() - height()) / 2);

    model = new QSqlTableModel(this);
    model->setTable("EParameter");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行
    //不显示name属性列,如果这时添加记录，则该属性的值添加不上
    // model->removeColumn(1);
    //ui->tableView->setColumnWidth(1,80);
    ui->tableView->setModel(model);
    //使其不可编辑
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //! 按钮
    QList<QPushButton*> btnList = this->findChildren<QPushButton*>();
    foreach (QPushButton* b, btnList)
    {
        connect(b, SIGNAL(pressed()), this, SLOT(ui_button_pressed()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_updateChange_clicked() //提交修改
{
    model->database().transaction(); //开始事务操作
    if (model->submitAll()) {
        model->database().commit(); //提交
    } else {
        model->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1")
                             .arg(model->lastError().text()));
    }
}

void MainWindow::on_pushButton_undo_clicked() //撤销修改
{
    model->revertAll();
}

void MainWindow::on_pushButton_search_clicked() //查询
{
    int ID = ui->lineEdit_search->text().toInt();
    //根据内容进行筛选
    model->setFilter(QString("编号 = '%1'").arg(ID));
    //显示结果
    model->select();
}

void MainWindow::on_pushButton_displayAll_clicked() //显示完整数据库
{
    model->setTable("EParameter");   //重新关联表
    model->select();   //这样才能再次显示整个表的内容
}

void MainWindow::on_pushButton_IDup_clicked() //升序排列
{
    model->setSort(0, Qt::AscendingOrder); //id属性即第0列，升序排列
    model->select();
}

void MainWindow::on_pushButton_IDdown_clicked() //降序排列
{
    model->setSort(0, Qt::DescendingOrder);
    model->select();
}


void MainWindow::on_pushButton_delete_clicked() //删除一行
{
    //获取选中的行
    int curRow = ui->tableView->currentIndex().row();

    //删除该行
    model->removeRow(curRow);

    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("确定"
                                                       "删除当前行吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        model->revertAll(); //如果不删除，则撤销
    }
    else model->submitAll(); //否则提交，在数据库中删除该行
}


void MainWindow::on_pushButton_addContent_clicked() //增加一行
{
    int rowNum = model->rowCount(); //获得表的行数
    int id = 10;
    model->insertRow(rowNum); //添加一行
    model->setData(model->index(rowNum,0),id);
    //model->submitAll(); //可以直接提交
}

void MainWindow::on_pushButton_Exit_clicked()
{
    model->revertAll();
    close();
}

void MainWindow::ui_button_pressed() // 按钮按下效果
{
    QPushButton* b = (QPushButton*)(sender());
    b->move(b->pos() + QPoint(3, 3));
    qApp->processEvents();
    QThread::msleep(100);
    b->move(b->pos() + QPoint(-3, -3));
    qApp->processEvents();
}

