/*
 *  Esta clase es capaz de almacenar los elementos referenciados,
 *  en un vector de tipo mapa. Lo que se pretende es guardar dichos elementos en una
 *  tabla de la bd.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frame.h"
#include "ui_frame.h"
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>

void doAnything(QList<QString> selectedList);
void quantityZones(QList<int> tzIDs);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     ui->setupUi(this);


    // MainWindow::readXml();
    // MainWindow::storeBD();


     DBA *handler = DBA::getInstance();

     const QString q_task = Task::prepareSelect();
     QVector<Task> query_task = handler->select<Task>(q_task);


     QGridLayout *gridlayout = new QGridLayout();


     for(int i = 0; i < query_task.size(); ++i){
         QCheckBox *checkbox = new QCheckBox();
         checkbox->setText(query_task[i].getTaskId());
         QFont font = checkbox->font();
         font.setPointSize(16);
         checkbox->setFont(font);
         checkboxes.append(checkbox);
         gridlayout->addWidget(checkbox, i, 0);
     }

     QPushButton *button = new QPushButton();
     button->setText("Aceptar");
     QFont font = button->font();
     font.setPointSize(16);
     button->setFont(font);
     gridlayout->addWidget(button, 4, 1);

     QPushButton *bt_change = new QPushButton();
     bt_change->setText("Cambiar frame");
     QFont changefont = bt_change->font();
     changefont.setPointSize(18);
     button->setFont(changefont);
     gridlayout->addWidget(bt_change, 2, 1);


    ui->frame->setLayout(gridlayout);
     //frame->setLayout(gridlayout);

     //ui->verticalLayout->addWidget(frame);


    connect(button, SIGNAL(clicked(bool)), this, SLOT(submit()));
    connect(bt_change, SIGNAL(clicked(bool)), this, SLOT(change()));


}

void MainWindow::change(){
    //QFrame *frame = new QFrame();
    QGridLayout *gridlayout = new QGridLayout();

    QLabel *label = new QLabel();
    label->setText("Frame cambiado");

    gridlayout->addWidget(label);
    delete ui->frame->layout();
    ui->frame = new QFrame();
    ui->frame->setLayout(gridlayout);
}


void MainWindow::submit(){
    QList<QString> selectedList;
    for(QCheckBox* box : checkboxes){
        if(box->isChecked()){
            selectedList.append(box->text());
        }
    }
    doAnything(selectedList);
}

void doAnything(QList<QString> selectedList){
    DBA *handler = DBA::getInstance();
    const QString q_tzn = TZN::prepareSelect();
    QVector<TZN> query_tzn = handler->select<TZN>(q_tzn);

    QList<int> tzIDs;

    for(TZN el : query_tzn){
        QString taskId = el.getTaskId();
        for(int i = 0; i < selectedList.size(); ++i){
            if(taskId == selectedList[i])
                tzIDs.append(el.getTZCode());
        }
    }
    quantityZones(tzIDs);

}

void quantityZones(QList<int> tzIDs){
    DBA *handler = DBA::getInstance();
     const QString q_pdv = PDV::prepareSelect();
     QVector<PDV> query_pdv = handler->select<PDV>(q_pdv);

     for(PDV el : query_pdv){
         int tzcode = el.getTZCode();
         for(int i = 0; i < tzIDs.size(); ++i){
             if(tzcode == tzIDs[i])
                 qDebug() << el.getPDVDataValue();
         }
     }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::storeBD(){
    DBA* handler = DBA::getInstance(); //Singleton

    for(int i = 0; i<tasks.size(); ++i){
        if(!handler->insert(tasks[i]->prepareInsert()))
             qDebug() << "Error al insertar entrada de tabla task: ";
        for(int j = 0; j<tasks[i]->TZN_Vector.size(); ++j){
            if(!handler->insert(tasks[i]->TZN_Vector[j]->prepareInsert(tasks[i]->getTaskId())))
                qDebug() << "Error al insertar entrada de tabla tzn: " << tasks[i]->TZN_Vector[j]->prepareInsert(tasks[i]->getTaskId());
            for(int z = 0; z<tasks[i]->TZN_Vector[j]->PDV_Vector.size(); ++z){
                if(!handler->insert(tasks[i]->TZN_Vector[j]->PDV_Vector[z]->prepareInsert(tasks[i]->TZN_Vector[j]->getTZCode())))
                    qDebug() << "Error al insertar entrada de tabla pdv: " << tasks[i]->TZN_Vector[j]->PDV_Vector[z]->prepareInsert(tasks[i]->TZN_Vector[j]->getTZCode());
            }
        }
    }
}

void MainWindow::readXml(){

    // Task Atts
    QString TaskDDI;
    QString PFIdRef;

    // TZN Atts
    qint8 TZCode;

    // PDV Atts
    //qint16 PDataDDi;
    QString PDataDDi; //Hex
    long PDataValue;
    QString PIdRef;
    QString VPNIdRef;

    // Total tasks
    //QVector<Task*> tasks;

    bool flagGRD = false;
    bool flagTZN = false;

    QFile taskdata(":/xml/(A) Mapas Formación XML/TASKDATA.XML");

    if(!taskdata.open(QIODevice::ReadOnly))
        return;

    QXmlStreamReader reader(&taskdata);
    qDebug() << "reader";
    while(!reader.atEnd()){
        reader.readNext();
        if(reader.name() == "TSK" && reader.isStartElement())
        {
            foreach(const QXmlStreamAttribute &att, reader.attributes()){
                if(att.name() == "A")
                    TaskDDI = att.value().toString();
                else if(att.name() == "E")
                    PFIdRef = att.value().toString();

            }

            Task* task = new Task(TaskDDI, PFIdRef);
            TZN* tzn;


            while(!reader.atEnd() && !flagGRD){
                reader.readNext();
                if(reader.name() == "GRD")
                    flagGRD = true;
                if(reader.name() == "TZN" && reader.isStartElement()){
                    foreach(const QXmlStreamAttribute &att, reader.attributes()){
                        if(att.name() == "A")
                            TZCode = att.value().toInt();
                    }
                    flagTZN = false;

                    tzn = new TZN(TZCode);
// P --> Process

                    while(!reader.atEnd() && !flagTZN){
                        reader.readNext();
                        if(reader.name() == "TZN")
                            flagTZN = true;
                        if(reader.name() == "PDV" && reader.isStartElement()){
                            foreach(const QXmlStreamAttribute &att, reader.attributes()){
                                if(att.name() == "A")
                                    PDataDDi = att.value().toString();
                                if(att.name() == "B")
                                    PDataValue = att.value().toLong();
                                if(att.name() == "C")
                                    PIdRef = att.value().toString();
                                if(att.name() == "E")
                                    VPNIdRef = att.value().toString();
                            }

                        } else {
                            continue;
                        }

                        PDV* pdv = new PDV(PDataDDi, PDataValue, PIdRef, VPNIdRef);
                        tzn->PDV_Vector.append(pdv);
                    }

                    task->TZN_Vector.append(tzn);

                } else {
                    continue;
                }
            }


            if(reader.name() == "GRD"){
                foreach(const QXmlStreamAttribute &att, reader.attributes()){
                    if(att.name() == "G"){
                        task->setGridFile(att.value().toString());
                    }else if(att.name() == "I"){
                        task->setGridType(att.value().toInt());
                    }
                }
                flagGRD = false;
            }

            tasks.append(task);
        }
    }
}
