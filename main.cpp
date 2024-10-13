#include <QApplication>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLineEdit *filterEdit = new QLineEdit;
    filterEdit->setPlaceholderText("Filter...");
    layout->addWidget(filterEdit);

    QFileSystemModel *model = new QFileSystemModel;
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    model->setRootPath(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel(model);
    proxyModel->setFilterKeyColumn(0);

    QTreeView *tree = new QTreeView;
    tree->setModel(proxyModel);
    tree->setRootIndex(proxyModel->mapFromSource(model->index(QStandardPaths::writableLocation(QStandardPaths::HomeLocation))));
    layout->addWidget(tree);

    QObject::connect(filterEdit, &QLineEdit::textChanged, proxyModel, &QSortFilterProxyModel::setFilterWildcard);

    window.setLayout(layout);
    window.setWindowTitle("Dir View");
    window.show();

    return app.exec();
}
