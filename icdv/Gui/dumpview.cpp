#include "dumpview.h"
#include "ui_dumpview.h"

DumpView::DumpView(int id, const QString &source, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DumpView)
{
    ui->setupUi(this);
    SetText(source);
    QGraphicsScene * scene = new QGraphicsScene(ui->DumpLabel->sceneRect());
    scene->addSimpleText(source);
    ui->DumpLabel->setScene(scene);
    ui->DumpLabel->show();
    grabMouse();
    setWindowTitle("Node " + QString::number(id) +" content");
}

const QString & DumpView::SetText(const QString &source)
{
    QString m_source;
    m_source.clear();

    if (source.isEmpty())
        m_source += "No content for this node.";
    else
        m_source += source;

    return m_source;
}

void DumpView::resizeEvent(QResizeEvent * resize) {
    ui->DumpLabel->setGeometry(QRect(0, 0,
                                   resize->size().width(),
                                   resize->size().height()));
}
DumpView::~DumpView()
{
    delete ui;
}
