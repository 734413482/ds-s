#include "treewidget.h"
#include "ui_treewidget.h"
#include <QTreeWidgetItem>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
TreeWidget::TreeWidget(QWidget *parent): QWidget(parent), ui(new Ui::TreeWidget)
{
    ui->setupUi(this);


    ui->treeWidget->setHeaderLabel("label");
    ui->treeWidget_2->setHeaderLabel("parent label");
    //connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onSetLabelText(QTreeWidgetItem*,int)));

    initTreeWidget();
    createMenu();
}

TreeWidget::~TreeWidget()
{
    delete ui;
}

void TreeWidget::initTreeWidget()
{
    {
        QTreeWidgetItem *mcs = new QTreeWidgetItem(ui->treeWidget);
        mcs->setText(0,"MCS");
        mcs->setIcon(0,QIcon(":/images/mcs.png"));
    }

    {
        QTreeWidgetItem *focusplane = new QTreeWidgetItem(ui->treeWidget);
        focusplane->setText(0,"Focus Plane");
        focusplane->setIcon(0,QIcon(":/images/focusplane.png"));
        QTreeWidgetItem *fpln_1 = new QTreeWidgetItem(focusplane);
        fpln_1->setText(0,"FPLN_1");
    }

    {
        QTreeWidgetItem *reposition = new QTreeWidgetItem(ui->treeWidget);
        reposition->setText(0,"Reposition");
        reposition->setIcon(0,QIcon(":/images/reposition.png"));
    }

    {
        QTreeWidgetItem *cadmodels = new QTreeWidgetItem(ui->treeWidget);
        cadmodels->setText(0,"Cad Models");
        cadmodels->setIcon(0,QIcon(":/images/cadmodels.png"));
        QTreeWidgetItem *cadm_1 = new QTreeWidgetItem(cadmodels);
        cadm_1->setText(0,"CADM_1");
    }

    {
        QTreeWidgetItem *pointclouds = new QTreeWidgetItem(ui->treeWidget);
        pointclouds->setText(0,"Point Clouds");
        pointclouds->setIcon(0,QIcon(":/images/pointclouds.png"));
    }

    {
        QTreeWidgetItem *formerrorreports = new QTreeWidgetItem(ui->treeWidget);
        formerrorreports->setText(0,"Form Error Reports");
        formerrorreports->setIcon(0,QIcon(":/images/formerrorreports.png"));
    }

    {
        QTreeWidgetItem *sensor = new QTreeWidgetItem(ui->treeWidget);
        sensor->setText(0,"Sensor");
        sensor->setIcon(0,QIcon(":/images/sensor.png"));
    }



}

void TreeWidget::createMenu()
{
    m_PopMenu = new QMenu;
    myadd = new QMenu("myadd");

    m_AddMenu = new QMenu("Add Action");
    m_AddMenu->setIcon(QIcon(":/images/add.png"));
    //m_AddFocusPlaneMenu = new QMenu;
    //m_AddCadModelsMenu = new QMenu;
    m_AddFocusPlaneAction = new QAction("Add FocusPlane");
    m_AddCadModelsAction = new QAction("Add CadModels");
    myaddaction = new QAction("myadd");
    myaddaction->setIcon(QIcon(":/images/add.png"));
    //m_AddMenu->addAction(m_AddFocusPlaneAction);
    //m_AddMenu->addAction(m_AddCadModelsAction);

    m_DelAction = new QAction("Del Action");
    m_DelAction->setIcon(QIcon(":/images/del.png"));

    //m_PopMenu->addMenu(m_AddMenu);
    m_PopMenu->addAction(myaddaction);
    m_PopMenu->addAction(m_DelAction);

    connect(m_AddFocusPlaneAction,SIGNAL(triggered(bool)),this,SLOT(onAddFocusPlane()));
    connect(m_AddCadModelsAction,SIGNAL(triggered(bool)),this,SLOT(onAddCadModels()));
    connect(myaddaction,SIGNAL(triggered(bool)),this,SLOT(onadd()));
    connect(m_DelAction,SIGNAL(triggered(bool)),this,SLOT(onDelAction()));
}

void TreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if(ui->treeWidget->hasFocus())
    {
        m_PopMenu->move(cursor().pos());
        m_PopMenu->show();
    }
}
/*
void TreeWidget::onSetLabelText(QTreeWidgetItem *item, int)
{
     if(item->parent()){
         ui->FocusPlaneLabel->setText(item->parent()->text(0));
         ui->CadModelsLabel->setText(item->text(0));
     }
     else{
         ui->FocusPlaneLabel->setText(item->text(0));
         ui->CadModelsLabel->setText(" ");
     }
}*/

void TreeWidget::onAddFocusPlane()
{
    QTreeWidgetItem *focusplaneitem = ui->treeWidget->currentItem();
    if(!focusplaneitem->parent()){
        QMessageBox::information(this,"information","Did Not Choose");
        return;
    }
    if(focusplaneitem->parent()->text(0)=="Focus Plane"){
        bool ok;
        QString focusplanetext = QInputDialog::getText(this,tr("input FocusPlane Name"),tr("FocusPlane Name:"),QLineEdit::Normal,"",&ok);
        if(ok && !focusplanetext.isEmpty()){
             QTreeWidgetItem *cadmodelsitem = new QTreeWidgetItem(focusplaneitem->parent());
             cadmodelsitem->setText(0,focusplanetext);
        }
    }
}

void TreeWidget::onAddCadModels()
{
    QTreeWidgetItem *currentitem = ui->treeWidget->currentItem();
    if(!currentitem->parent()){
        QMessageBox::information(this,"information","Did Not Choose");
        return;
    }
    if(currentitem->parent()->text(0)=="Cad Models"){
        bool ok;
        QString cadmodelstext = QInputDialog::getText(this,tr("input CadModels Name"),tr("CadModels Name:"),QLineEdit::Normal,"",&ok);
        if(ok && !cadmodelstext.isEmpty()){
             QTreeWidgetItem *cadmodelsitem = new QTreeWidgetItem(currentitem->parent());
             cadmodelsitem->setText(0,cadmodelstext);
        }
    }
}

void TreeWidget::onDelAction()
{
    QTreeWidgetItem *currentitem = ui->treeWidget->currentItem();
    if(!currentitem->parent()){
        QMessageBox::information(this,"information","Can Not Delete");
        return;
    }
    else if(currentitem->parent()){
        currentitem->parent()->removeChild(currentitem);
    }
}

void TreeWidget::onadd()
{
    QTreeWidgetItem *currentitem = ui->treeWidget->currentItem();
    if(!currentitem->parent()){
        QMessageBox::information(this,"information","Did Not Choose");
        return;
    }
    else if(currentitem->parent()->text(0)=="Cad Models"){
        bool ok;
        QString cadmodelstext = QInputDialog::getText(this,tr("input CadModels Name"),tr("CadModels Name:"),QLineEdit::Normal,"",&ok);
        if(ok && !cadmodelstext.isEmpty()){
             QTreeWidgetItem *cadmodelsitem = new QTreeWidgetItem(currentitem->parent());
             cadmodelsitem->setText(0,cadmodelstext);
        }
    }
    else if(currentitem->parent()->text(0)=="Focus Plane"){
        bool ok;
        QString focusplanetext = QInputDialog::getText(this,tr("input FocusPlane Name"),tr("FocusPlane Name:"),QLineEdit::Normal,"",&ok);
        if(ok && !focusplanetext.isEmpty()){
             QTreeWidgetItem *cadmodelsitem = new QTreeWidgetItem(currentitem->parent());
             cadmodelsitem->setText(0,focusplanetext);
        }
    }
}
