#include "filtersearchwidget.h"
#include "ui_filtersearchwidget.h"

FilterSearchWidget::FilterSearchWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FilterSearchWidget)
{
	ui->setupUi(this);
	/*QRegExp::WildcardUnix will be used for custom search*/
	ui->cboxFilterType->addItem(tr("Custom Expression"), QRegExp::WildcardUnix);
	ui->cboxFilterType->addItem(tr("Regular Expression"), QRegExp::RegExp);
	ui->cboxFilterType->addItem(tr("Wildcard"), QRegExp::Wildcard);
	ui->cboxFilterType->addItem(tr("Fixed String"), QRegExp::FixedString);

	connect(ui->cboxFilterType, SIGNAL(currentIndexChanged(int)), this, SLOT(handleChanges()));

	connect(ui->cbAutomatic, SIGNAL(toggled(bool)), this, SLOT(handleChanges()));
	connect(ui->cbCaseSensitive, SIGNAL(toggled(bool)), this, SLOT(handleChanges()));
	connect(ui->leFilterText, SIGNAL(textChanged(QString)), this, SLOT(handleChanges()));

	this->setFocusProxy(ui->leFilterText);

	ui->tbCloseWidget->setIcon(QIcon::fromTheme("window-close"));
	connect(ui->tbCloseWidget, SIGNAL(clicked()), this, SLOT(hideSelf()));
}

FilterSearchWidget::~FilterSearchWidget()
{
	delete ui;
}

void FilterSearchWidget::handleChanges()
{
	QRegExp::PatternSyntax syntax = (QRegExp::PatternSyntax)ui->cboxFilterType->itemData(ui->cboxFilterType->currentIndex()).toInt();
	Qt::CaseSensitivity caseSensitivity = ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
	emit filterChanged(ui->leFilterText->text(), syntax, caseSensitivity);
}

void FilterSearchWidget::automaticChanged(bool checked)
{
	if(checked)
	{
		connect(ui->leFilterText, SIGNAL(textChanged(QString)), this, SLOT(handleChanges()));
		ui->leFilterText->disconnect(SIGNAL(returnPressed()));
	}
	else
	{
		ui->leFilterText->disconnect(SIGNAL(textChanged(QString)));
		connect(ui->leFilterText, SIGNAL(returnPressed()), this, SLOT(handleChanges()));
	}
}

void FilterSearchWidget::hideSelf()
{
	this->hide();
	emit filterChanged(tr(""), QRegExp::Wildcard, Qt::CaseInsensitive);
}
