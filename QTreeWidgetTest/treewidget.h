#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <qmenu.h>
#include <qaction.h>
#include <QTreeWidgetItem>
#include <QContextMenuEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class TreeWidget; }
QT_END_NAMESPACE

class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    TreeWidget(QWidget *parent = nullptr);
    ~TreeWidget();

    void initTreeWidget();

    void createMenu();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    //void onSetLabelText(QTreeWidgetItem* item,int);
    void onAddFocusPlane();
    void onAddCadModels();
    void onDelAction();
    void onadd();
private:
    Ui::TreeWidget *ui;

    QMenu *m_PopMenu;
    //QMenu *m_AddFocusPlaneMenu;
    //QMenu *m_AddCadModelsMenu;
    QMenu *m_AddMenu;
    QMenu *m_DelMenu;
    QMenu *myadd;
    QAction *m_AddFocusPlaneAction;
    QAction *m_AddCadModelsAction;
    QAction *myaddaction;
    QAction *m_DelAction;
};
#endif // TREEWIDGET_H
